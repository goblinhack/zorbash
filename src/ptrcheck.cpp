/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_slre.h"

#include "my_main.h"
#include "my_backtrace.h"
#include "my_time_util.h"
#include "my_command.h"

/*
 * How many times we've seen a given pointer and record a traceback at that
 * point.
 */
#define MAX_PER_PTR_HISTORY 3

/*
 * A single event in the life of a pointer.
 */
typedef struct ptrcheck_history_ {
    const char *file;
    const char *func;
    uint32_t    line;
    uint32_t    ms;
    tracebackp tb;
} ptrcheck_history;

/*
 * The life of a single pointer.
 */
typedef struct ptrcheck_ {
    /*
     * For sanity, the pointer itself.
     */
    void *ptr;

    /*
     * The type of memory.
     */
    const char *what;

    /*
     * How much memory it is using.
     */
    uint32_t size;

    /*
     * Where did the pointer get allocated/freed/last_seen from?
     */
    ptrcheck_history allocated_by;
    ptrcheck_history freed_by;
    ptrcheck_history last_seen[MAX_PER_PTR_HISTORY];

    /*
     * Where in the history buffer we are.
     */
    uint16_t last_seen_at;
    uint16_t last_seen_size;

    /*
     * Ignore when looking for leaks.
     */
    uint8_t leak_ignore:1;

} ptrcheck;

/*
 * A hash table so we can check pointers fast.
 */
typedef struct hash_elem_t_ {
    struct hash_elem_t_ *next;
    ptrcheck *context;
} hash_elem_t;

typedef struct hash_t_ {
    uint32_t hash_size;
    hash_elem_t **elements;
} hash_t;

static hash_t *hash;

/*
 * Ring buffer, used for pointer history.
 */
static ptrcheck *ringbuf_next;
static ptrcheck *ringbuf_base;

/*
 * How many old/freed pointers do we keep track of. We use this when we find
 * an unknown pointer to find when it last lived.
 */
static uint32_t ringbuf_max_size = 200000;
static uint32_t ringbuf_current_size;

/*
 * Prototypes.
 */
static void ptrcheck_usage_cleanup(void);

static uint8_t ptrcheck_init_done;

uint8_t ptrcheck_init (void)
{_
    ptrcheck_init_done = true;

    return (true);
}

void ptrcheck_fini (void)
{_
    /*
     * Print memory leaks.
     */
    ptrcheck_leak_print();

    ptrcheck_usage_cleanup();
}

/*
 * local_zalloc
 *
 * Wrapper for calloc.
 */
static void *local_zalloc (uint32_t size)
{_
    void *p;

    p = calloc(1, size);
    if (!p) {
        ERR("calloc");
    }

    return (p);
}

/*
 * local_free
 *
 * Wrapper for free.
 */
static void local_free (void *ptr)
{_
    free(ptr);
}

/*
 * ptr2hash
 *
 * Map a pointer to a hash slot.
 */
static hash_elem_t ** ptr2hash (hash_t *hash_table, void *ptr)
{_
    uint32_t slot;

    /*
     * Knock lower 2 bits off of pointer - these are always 0.
     */
    slot = (uint32_t)((((uintptr_t)(ptr)) >> 2) % hash_table->hash_size);

    return (&hash_table->elements[slot]);
}

/*
 * hash_init
 *
 * Create a hash table for all pointers.
 */
static hash_t *hash_init (uint32_t hash_size)
{_
    hash_t *hash_table;

    hash_table =
        (__typeof__(hash_table))
            local_zalloc(sizeof(hash_t));

    hash_table->hash_size = hash_size;

    hash_table->elements =
        (__typeof__(hash_table->elements))
                local_zalloc(hash_size * sizeof(hash_elem_t *));

    return (hash_table);
}

/*
 * hash_add
 *
 * Store a pointer in our hash.
 */
static void hash_add (hash_t *hash_table, ptrcheck *context)
{_
    hash_elem_t **slot;
    hash_elem_t *elem;

    if (!context) {
        return;
    }

    if (!hash_table) {
        local_free(context);
        return;
    }

    slot = ptr2hash(hash_table, context->ptr);
    elem = *slot;
    while (elem && (elem->context->ptr != context->ptr)) {
        elem = elem->next;
    }

    if (elem != 0) {
        local_free(context);
        return;
    }

    elem = (__typeof__(elem)) local_zalloc(sizeof(*elem));
    elem->context = context;
    elem->next = *slot;
    *slot = elem;
}

/*
 * hash_find
 *
 * Find a pointer in our hash.
 */
static hash_elem_t *hash_find (hash_t *hash_table, void *ptr)
{_
    hash_elem_t **slot;
    hash_elem_t *elem;

    if (!hash_table) {
        return (0);
    }

    if (!ptr) {
        return (0);
    }

    slot = ptr2hash(hash_table, ptr);
    elem = *slot;
    while (elem && (elem->context->ptr != ptr)) {
        elem = elem->next;
    }

    return (elem);
}

/*
 * hash_free
 *
 * Free a pointer from our hash.
 */
static void hash_free (hash_t *hash_table, void *ptr)
{_
    hash_elem_t **slot;
    hash_elem_t *prev;
    hash_elem_t *elem;

    if (!hash_table) {
        return;
    }

    if (!ptr) {
        return;
    }

    slot = ptr2hash(hash_table, ptr);
    elem = *slot;
    prev = 0;

    while (elem && (elem->context->ptr != ptr)) {
        prev = elem;
        elem = elem->next;
    }

    if (!elem) {
        return;
    }

    if (prev) {
        prev->next = elem->next;
    } else {
        *slot = elem->next;
    }

    local_free(elem->context);
    local_free(elem);
}

/*
 * ptrcheck_verify_pointer
 *
 * Check a pointer for validity.
 */
static ptrcheck *ptrcheck_verify_pointer (const void *ptr,
                                          const char *func,
                                          const char *file,
                                          const uint32_t line,
                                          uint8_t dont_store)
{_
    static const char *bad_pointer_warning = "**BAD POINTER** ";
    static const char *null_pointer_warning = "**NULL POINTER** ";
    uint32_t ring_ptr_size;
    ptrcheck *context;
    hash_elem_t *e;
    uint32_t i;

    if (!hash) {
        return (0);
    }

    if (!ptr) {
        global_callstack.dump();
        DIE("%s%p NULL pointer %s:%s():%u", null_pointer_warning, ptr, file, func, line);
    }

    /*
     * Check the robust handle is valid.
     */
    e = hash_find(hash, (void*) ptr);
    if (e) {
        context = e->context;

#ifndef ENABLE_PTRCHECK_HISTORY
        return (context);
#else
        if (dont_store) {
            return (context);
        }

        /*
         * Add some free information that we know the pointer is safe at this
         * point in time.
         */
        context->last_seen[context->last_seen_at].file = file;
        context->last_seen[context->last_seen_at].func = func;
        context->last_seen[context->last_seen_at].line = line;

        if (context->last_seen[context->last_seen_at].tb) {
            local_free(context->last_seen[context->last_seen_at].tb);
        }

        context->last_seen[context->last_seen_at].tb = traceback_alloc();
        context->last_seen[context->last_seen_at].ms = time_get_time_ms();

        context->last_seen_at++;
        context->last_seen_size++;

        if (context->last_seen_at >= MAX_PER_PTR_HISTORY) {
            context->last_seen_at = 0;
        }

        if (context->last_seen_size >= MAX_PER_PTR_HISTORY) {
            context->last_seen_size = MAX_PER_PTR_HISTORY;
        }

        return (context);
#endif
    }

    /*
     * We may be about to crash. Complain!
     */
    global_callstack.dump();
    ERR("%s%p %s:%s():%u", bad_pointer_warning, ptr, file, func, line);

    /*
     * Check the ring buffer to see if we've seen this pointer before.
     */
    context = ringbuf_next;
    context--;

    if (context < ringbuf_base) {
        context = ringbuf_base + ringbuf_max_size - 1;
    }

    ring_ptr_size = ringbuf_current_size;

    /*
     * Walk back through the ring buffer.
     */
    while (ring_ptr_size) {
        /*
         * Found a match?
         */
        if (context->ptr == ptr) {
            fprintf(MY_STDERR,
                    "Allocated \"%s\" (%u bytes) at %s:%s():%u at %s\n",
                    context->what,
                    context->size,
                    context->allocated_by.file,
                    context->allocated_by.func,
                    context->allocated_by.line,
                    time2str(context->allocated_by.ms, 0, 0));

            traceback_stderr(context->allocated_by.tb);

            fprintf(MY_STDERR, "Freed at %s:%s():%u at %s\n",
                    context->freed_by.file,
                    context->freed_by.func,
                    context->freed_by.line,
                    time2str(context->freed_by.ms, 0, 0));

            traceback_stderr(context->freed_by.tb);

            /*
             * Dump the pointer history.
             */
            ptrcheck_history *history;

            history = &context->last_seen[context->last_seen_at];

            for (i=0; i < context->last_seen_size; i++) {
                if (--history < context->last_seen) {
                    history = &context->last_seen[MAX_PER_PTR_HISTORY-1];
                }

                fprintf(MY_STDERR, "Last seen at [%u] at %s:%s():%u at %s\n",
                        i,
                        history->file,
                        history->func,
                        history->line,
                        time2str(history->ms, 0, 0));

                traceback_stderr(history->tb);
            }

            /*
             * Memory reuse can cause a lot of false hits, so stop after
             * the first match.
             */
            break;
        }

        ring_ptr_size--;
        context--;

        /*
         * Handle wraps.
         */
        if (context < ringbuf_base) {
            context = ringbuf_base + ringbuf_max_size - 1;
        }
    }

    DIE("Fatal error");

    return (0);
}

/*
 * ptrcheck_alloc
 *
 * Record this pointer.
 */
void *ptrcheck_alloc (const void *ptr,
                      const char *what,
                      const uint32_t size,
                      const char *func,
                      const char *file,
                      const uint32_t line)
{_
    ptrcheck *context;

    if (!ptr) {
        global_callstack.dump();

        ERR("null pointer");
    }

    /*
     * Create a hash table to store pointers.
     */
    if (!hash) {
        /*
         * Create enough space for lots of pointers.
         */
        hash = hash_init(1046527 /* prime */);

        if (!hash) {
            return ((void*) ptr);
        }
    }

    /*
     * Missing an earlier free?
     */
    if (hash_find(hash, (void*) ptr)) {
        DIE("pointer %p already exists and attempting to add again", ptr);
        return ((void*) ptr);
    }

    /*
     * And a ring buffer to store old pointer into.
     */
    if (!ringbuf_next) {
        ringbuf_next =
            (__typeof__(ringbuf_next))
                local_zalloc(sizeof(ptrcheck) * ringbuf_max_size);

        ringbuf_base = ringbuf_next;
        ringbuf_current_size = 0;
    }

    /*
     * Allocate a block of data to describe the pointer and owner.
     */
    context =
        (__typeof__(context))
            local_zalloc(sizeof(ptrcheck));

    /*
     * Populate the data block.
     */
    context->ptr = (void*) ptr;
    context->what = what;
    context->size = size;
    context->allocated_by.func = func;
    context->allocated_by.file = file;
    context->allocated_by.line = line;
    context->allocated_by.ms = time_get_time_ms();
    context->allocated_by.tb = traceback_alloc();

    /*
     * Add it to the hash. Not the ring buffer (only when freed).
     */
    hash_add(hash, context);

    return ((void*) ptr);
}

/*
 * ptrcheck_free
 *
 * Check a pointer is valid and if so add it to the ring buffer. If not,
 * return false and avert the myfree(), just in case.
 */
uint8_t ptrcheck_free (void *ptr,
                       const char *func,
                       const char *file,
                       const uint32_t line)
{_
    ptrcheck *context;

    if (!ptr) {
        global_callstack.dump();

        ERR("null pointer");

        return (false);;
    }

    context = ptrcheck_verify_pointer(ptr, file, func, line,
                                      true /* dont store */);
    if (!context) {
        return (false);
    }

    /*
     * Add some free information that we know the pointer is safe at this
     * point in time.
     */
    context->freed_by.file = file;
    context->freed_by.func = func;
    context->freed_by.line = line;
    context->freed_by.tb = traceback_alloc();
    context->freed_by.ms = time_get_time_ms();

    /*
     * Add the free info to the ring buffer.
     */
    memcpy(ringbuf_next, context, sizeof(ptrcheck));

    /*
     * Take care of wraps.
     */
    ringbuf_next++;
    if (ringbuf_next >= ringbuf_base + ringbuf_max_size) {
        ringbuf_next = ringbuf_base;
    }

    /*
     * Increment the ring buffer used size up to the limit.
     */
    if (ringbuf_current_size < ringbuf_max_size) {
        ringbuf_current_size++;
    }

    hash_free(hash, ptr);

    return (true);
}

/*
 * ptrcheck_verify
 *
 * Check a pointer for validity with no recording of history.
 */
uint8_t ptrcheck_verify (const void *ptr,
                              const char *func,
                              const char *file,
                              const uint32_t line)
{_
    return (ptrcheck_verify_pointer(ptr, file, func, line,
                                    true /* don't store */) != 0);
}

/*
 * ptrcheck_leak_print
 *
 * Free a pointer from our hash.
 */
void ptrcheck_leak_print (void)
{_
    hash_elem_t **slot;
    hash_elem_t *elem;
    ptrcheck *context;
    uint32_t i;
    uint32_t j;
    uint32_t leak;

    leak = 0;

    if (!hash) {
        return;
    }

    for (i = 0; i < hash->hash_size; i++) {
        slot = &hash->elements[i];
        elem = *slot;

        while (elem) {
            context = elem->context;

            if (context->leak_ignore) {
                elem = elem->next;
                continue;
            }

            leak++;

            fprintf(MY_STDERR, "Leak %p \"%s\" (%u bytes) at %s:%s():%u at %s\n",
                    context->ptr,
                    context->what,
                    context->size,
                    context->allocated_by.file,
                    context->allocated_by.func,
                    context->allocated_by.line,
                    time2str(context->allocated_by.ms, 0, 0));

            traceback_stderr(context->allocated_by.tb);

            /*
             * Dump the pointer history.
             */
            ptrcheck_history *history;

            history = &context->last_seen[context->last_seen_at];

            for (j=0; j < context->last_seen_size; j++) {
                if (--history < context->last_seen) {
                    history = &context->last_seen[MAX_PER_PTR_HISTORY-1];
                }

                fprintf(MY_STDERR, "Last seen at [%u] at %s:%s():%u at %s\n",
                        j,
                        history->file,
                        history->func,
                        history->line,
                        time2str(history->ms, 0, 0));

                traceback_stderr(history->tb);
            }

            elem = elem->next;
        }
    }

    if (!leak) {
        DIE("No memory leaks!");
    }
}

/*
 * ptrcheck_leak_snapshot
 *
 * Set so we only see leaks since now.
 */
void ptrcheck_leak_snapshot (void)
{_
    hash_elem_t **slot;
    hash_elem_t *elem;
    ptrcheck *context;
    uint32_t i;

    if (!hash) {
        return;
    }

    for (i = 0; i < hash->hash_size; i++) {
        slot = &hash->elements[i];
        elem = *slot;

        while (elem) {
            context = elem->context;

            context->leak_ignore = true;

            elem = elem->next;
        }
    }
}

/*
 * ptrcheck_usage_cleanup
 *
 * Print top memory allocators
 */
static void ptrcheck_usage_cleanup (void)
{_
    hash_elem_t **slot;
    hash_elem_t *elem;
    hash_elem_t *next;
    ptrcheck *context;
    uint32_t i;
    uint32_t j;

    if (!hash) {
        return;
    }

    for (i = 0; i < hash->hash_size; i++) {
        slot = &hash->elements[i];
        elem = *slot;

        while (elem) {
            context = elem->context;

            if (context->allocated_by.tb) {
                local_free(context->allocated_by.tb);
            }

            if (context->freed_by.tb) {
                local_free(context->freed_by.tb);
            }

            for (j=0; j < MAX_PER_PTR_HISTORY; j++) {
                if (context->last_seen[j].tb) {
                    local_free(context->last_seen[j].tb);
                }
            }

            next = elem->next;
            local_free(elem);
            elem = next;
        }
    }

    local_free(hash->elements);
    local_free(hash);

    hash = 0;
}
