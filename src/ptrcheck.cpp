//
// Copyright goblinhack@gmail.com
//

#include "my_main.h"
#include "my_traceback.h"
#include "my_sprintf.h"
#include "my_time.h"
#include <ctime>
#include <iostream>

bool ptr_check_some_pointers_changed;

//
// A single event in the life of a pointer.
//
class Ptrcheck_history {
public:
    std::string file;
    std::string func;
    int         line {};
    std::string ts;
    Traceback   *tb {};

    Ptrcheck_history() { }
    Ptrcheck_history(const Ptrcheck_history& other) {
        file = other.file;
        func = other.func;
        line = other.line;
        ts = other.ts;
        if (other.tb) {
            tb = new Traceback(other.tb);
        }
    }
};

//
// The life of a single pointer.
//
class Ptrcheck {
public:
    Ptrcheck(void) {}

    //
    // For sanity, the pointer itself.
    //
    void *ptr {};

    //
    // The type of memory.
    //
    std::string what;

    //
    // How much memory it is using.
    //
    int size {};

    //
    // Where did the pointer get allocated/freed/last_seen from?
    //
    Ptrcheck_history *allocated_by {};
    Ptrcheck_history *freed_by {};
#ifdef ENABLE_PTRCHECK_HISTORY
    std::array<Ptrcheck_history *, ENABLE_PTRCHECK_HISTORY> last_seen {};
#endif

    //
    // Where in the history buffer we are.
    //
    int last_seen_at {};
    int last_seen_size {};
};

std::string &timestamp(void)
{
    static timestamp_t time_last;
    static std::string last_timestamp;
    auto time_now = time_get_time_ms_cached();

    if (time_now - time_last < 1000) {
        return last_timestamp;
    }

    time_last = time_now;
    std::time_t result = std::time(nullptr);
    auto s = std::string(std::asctime(std::localtime(&result)));
    s.pop_back();
    last_timestamp = s;
    return last_timestamp;
}

#ifndef DIE
static void die (void)
{
    std::cerr << "exit(1) error" << std::endl;
    exit(1);
}

static void croak_ (const char *fmt, va_list args)
{
    static int croaked;
    if (croaked) {
        std::cerr <<
          string_sprintf("\nPTRCHECK: NESTED FATAL ERROR %s %s %d ",
                         __FILE__, __FUNCTION__, __LINE__);
        exit(1);
    }
    croaked = 1;

    auto err = "\n" + timestamp();
    err += ": PTRCHECK: FATAL ERROR: ";
    err += string_sprintf(fmt, args);
    std::cerr << err << std::endl;
    croaked = true;
    die();
}

void CROAK(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void CROAK (const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    croak_(fmt, args);
    va_end(args);
}

static void error_ (const char *fmt, va_list args)
{
    auto err = timestamp();
    err += ": PTRCHECK: ERROR: ";
    err += string_sprintf(fmt, args);
    std::cerr << err << std::endl;
}

void ERROR(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void ERROR (const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    error_(fmt, args);
    va_end(args);
}

#define DIE(args...)                                           \
    std::cerr <<                                               \
      string_sprintf("Died at %s:%s line %u",                  \
                     __FILE__, __PRETTY_FUNCTION__, __LINE__); \
    CROAK(args);                                               \

#define ERR(args...)                                           \
    std::cerr <<                                               \
      string_sprintf("Error at %s:%s line %u",                 \
                     __FILE__, __PRETTY_FUNCTION__, __LINE__); \
    ERROR(args);                                               \

#endif

//
// A hash table so we can check pointers fast.
//
typedef struct hash_elem_t_ {
    struct hash_elem_t_ *next;
    Ptrcheck *pc;
} hash_elem_t;

typedef struct hash_t_ {
    int hash_size;
    hash_elem_t **elements;
} hash_t;

static hash_t *hash;

//
// How many old/freed pointers do we keep track of. We use this when we find
// an unknown pointer to find when it last lived.
//
static const int ringbuf_max_size = 200000;
static int ringbuf_current_size;
static std::array<class Ptrcheck, ringbuf_max_size> ringbuf;
static Ptrcheck *ringbuf_next;
static Ptrcheck *ringbuf_base;

//
// Wrapper for calloc.
//
static void *local_zalloc (int size)
{
    void *p;
    p = calloc(1, size);
    return (p);
}

//
// Wrapper for free.
//
static void local_free (void *ptr)
{
    free(ptr);
}

//
// World a pointer to a hash slot.
//
static hash_elem_t ** ptr2hash (hash_t *hash_table, void *ptr)
{
    int slot;

    //
    // Knock lower 2 bits off of pointer - these are always 0.
    //
    slot = (int)((((uintptr_t)(ptr)) >> 2) % hash_table->hash_size);

    return (&hash_table->elements[slot]);
}

//
// Create a hash table for all pointers.
//
static hash_t *hash_init (int hash_size)
{
    hash_t *hash_table;

    hash_table = (__typeof__(hash_table)) local_zalloc(sizeof(hash_t));

    hash_table->hash_size = hash_size;

    hash_table->elements =
        (__typeof__(hash_table->elements))
                local_zalloc(hash_size * sizeof(hash_elem_t *));

    return (hash_table);
}

//
// Store a pointer in our hash.
//
static void hash_add (hash_t *hash_table, Ptrcheck *pc)
{
    hash_elem_t **slot;
    hash_elem_t *elem;

    if (!pc) {
        return;
    }

    if (!hash_table) {
        local_free(pc);
        return;
    }

    slot = ptr2hash(hash_table, pc->ptr);
    elem = *slot;
    while (elem && (elem->pc->ptr != pc->ptr)) {
        elem = elem->next;
    }

    if (elem != 0) {
        local_free(pc);
        return;
    }

    elem = (__typeof__(elem)) local_zalloc(sizeof(*elem));
    elem->pc = pc;
    elem->next = *slot;
    *slot = elem;

    ptr_check_some_pointers_changed = true;
}

//
// Find a pointer in our hash.
//
static hash_elem_t *hash_find (hash_t *hash_table, void *ptr)
{
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
    while (elem && (elem->pc->ptr != ptr)) {
        elem = elem->next;
    }

    return (elem);
}

//
// Free a pointer from our hash.
//
static void hash_free (hash_t *hash_table, void *ptr)
{
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

    while (elem && (elem->pc->ptr != ptr)) {
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

    local_free(elem->pc);
    local_free(elem);

    ptr_check_some_pointers_changed = true;
}

//
// Check a pointer for validity.
//
static Ptrcheck *ptrcheck_verify_pointer (const void *ptr,
                                          std::string &func,
                                          std::string &file,
                                          int line,
                                          int dont_store)
{
    static const char *unknown_ptr_warning = "** UNKNOWN POINTER ** ";
    static const char *null_pointer_warning = "** NULL POINTER ** ";
    int ring_ptr_size;
    Ptrcheck *pc;
    hash_elem_t *e;

    if (!hash) {
        return (0);
    }

    if (!ptr) {
        ERR("%s%p NULL pointer %s:%s line %u",
            null_pointer_warning, ptr, file.c_str(), func.c_str(), line);
    }

    //
    // Check the robust handle is valid.
    //
    e = hash_find(hash, (void*) ptr);
    if (e) {
        pc = e->pc;

        if (dont_store) {
            return (pc);
        }

        //
        // Add some free information that we know the pointer is safe at this
        // point in time.
        //
#ifdef ENABLE_PTRCHECK_HISTORY
        auto l = pc->last_seen[pc->last_seen_at];
        if (!l) {
            l = pc->last_seen[pc->last_seen_at] = new Ptrcheck_history();
        }
        l->file = file;
        l->func = func;
        l->line = line;
        if (l->tb) {
            delete l->tb;
        }

        l->tb = new Traceback();
        l->tb->init();
        l->ts = timestamp();

        pc->last_seen_at++;
        pc->last_seen_size++;

        if (pc->last_seen_at >= ENABLE_PTRCHECK_HISTORY) {
            pc->last_seen_at = 0;
        }

        if (pc->last_seen_size >= ENABLE_PTRCHECK_HISTORY) {
            pc->last_seen_size = ENABLE_PTRCHECK_HISTORY;
        }
#endif
        return (pc);
    }

    //
    // We may be about to crash. Complain!
    //
    ERR("%s%p %s:%s line %u",
        unknown_ptr_warning, ptr, file.c_str(), func.c_str(), line);

    //
    // Check the ring buffer to see if we've seen this pointer before.
    //
    pc = &ringbuf_next[0];
    pc--;

    if (pc < ringbuf_base) {
        pc = ringbuf_base + ringbuf_max_size - 1;
    }

    ring_ptr_size = ringbuf_current_size;

    CON("vvvvv Pointer history for %p vvvvv", ptr);

    //
    // Walk back through the ring buffer.
    //
    while (ring_ptr_size) {
        //
        // Found a match?
        //
        if (pc->ptr == ptr) {
            auto a = pc->allocated_by;
            auto ts = timestamp();
            if (a) {
                std::cerr <<
                    string_sprintf(
                        "PTRCHECK: %p allocated at \"%s\" (%u bytes) at %s:%s line %u at %s\n",
                        ptr,
                        pc->what.c_str(),
                        pc->size,
                        a->file.c_str(),
                        a->func.c_str(),
                        a->line,
                        a->ts.c_str());
                std::cerr << a->tb->to_string() << std::endl;
            }

            auto f = pc->freed_by;
            if (f) {
                std::cerr <<
                    string_sprintf(
                        "PTRCHECK: %p freed at %s:%s line %u at %s\n",
                        ptr,
                        f->file.c_str(),
                        f->func.c_str(),
                        f->line,
                        f->ts.c_str());
                std::cerr << f->tb->to_string() << std::endl;
            }

            //
            // Dump the pointer history.
            //
#ifdef ENABLE_PTRCHECK_HISTORY
            int h = pc->last_seen_at;
            for (auto i=0; i < pc->last_seen_size; i++) {
                if (--h < 0) {
                    h = ENABLE_PTRCHECK_HISTORY-1;
                }

                auto H = pc->last_seen[h];
                if (H) {
                    std::cerr <<
                        string_sprintf(
                            "PTRCHECK: %p last seen at [%u] at %s:%s line %u at %s\n",
                            ptr,
                            i,
                            H->file.c_str(),
                            H->func.c_str(),
                            H->line,
                            H->ts.c_str());
                    std::cerr << H->tb->to_string() << std::endl;
                }
            }
#endif
            //
            // Memory reuse can cause a lot of false hits, so stop after
            // the first match.
            //
            break;
        }

        ring_ptr_size--;
        pc--;

        //
        // Handle wraps.
        //
        if (pc < ringbuf_base) {
            pc = ringbuf_base + ringbuf_max_size - 1;
        }
    }

    CON("^^^^^ End of pointer history for %p ^^^^^", ptr);
    exit(1);
}

//
// Record this pointer.
//
void *ptrcheck_alloc (const void *ptr,
                      std::string what, int size, std::string func,
                      std::string file, int line)
{
    Ptrcheck *pc;

#ifdef ENABLE_PTRCHECK_DEBUG
    auto ts = timestamp();
    fprintf(stderr, "%s: PTRCHECK: Alloc %p \"%s\" (%u bytes) at %s:%s line %u\n",
            ts.c_str(),
            ptr,
            what.c_str(),
            size,
            file.c_str(),
            func.c_str(),
            line);
#endif

    if (!ptr) {
        ERR("null pointer");
    }

    //
    // Create a hash table to store pointers.
    //
    if (!hash) {
        //
        // Create enough space for lots of pointers.
        //
        hash = hash_init(1046527 * 11/* prime */);

        if (!hash) {
            return ((void*) ptr);
        }
    }

    //
    // Missing an earlier free?
    //
    if (hash_find(hash, (void*) ptr)) {
        ERR("pointer %p already exists and attempting to add again", ptr);
        return ((void*) ptr);
    }

    //
    // And a ring buffer to store old pointer into.
    //
    ringbuf_next = &ringbuf[0];
    ringbuf_base = &ringbuf[0];
    ringbuf_current_size = 0;

    //
    // Allocate a block of data to describe the pointer and owner.
    //
    pc = new Ptrcheck();

    //
    // Populate the data block.
    //
    pc->ptr = (void*) ptr;
    pc->what = what;
    pc->size = size;

    auto a = pc->allocated_by = new Ptrcheck_history();
    a->func = func;
    a->file = file;
    a->line = line;
    a->ts = timestamp();
    a->tb = new Traceback();
    a->tb->init();

    //
    // Add it to the hash. Not the ring buffer (only when freed).
    //
    hash_add(hash, pc);

    return ((void*) ptr);
}

//
// Check a pointer is valid and if so add it to the ring buffer. If not,
// return false and avert the myfree(), just in case.
//
int ptrcheck_free (void *ptr, std::string func, std::string file, int line)
{
    Ptrcheck *pc;

#ifdef ENABLE_PTRCHECK_DEBUG
    auto ts = timestamp();
    fprintf(stderr, "%s: PTRCHECK: Free %p at %s:%s line %u\n",
            ts.c_str(),
            ptr,
            file.c_str(),
            func.c_str(),
            line);
#endif

    if (!ptr) {
        ERR("null pointer");
        return (false);
    }

    pc = ptrcheck_verify_pointer(ptr, file, func, line, true /* dont store */);
    if (!pc) {
        return (false);
    }

    //
    // Add some free information that we know the pointer is safe at this
    // point in time.
    //
    auto f = pc->freed_by = new Ptrcheck_history();
    f->file = file;
    f->func = func;
    f->line = line;
    f->tb = new Traceback();
    f->tb->init();
    f->ts = timestamp();

    //
    // Add the free info to the ring buffer.
    //
    *ringbuf_next = *pc;

    //
    // Take care of wraps.
    //
    ringbuf_next++;
    if (ringbuf_next >= ringbuf_base + ringbuf_max_size) {
        ringbuf_next = ringbuf_base;
    }

    //
    // Increment the ring buffer used size up to the limit.
    //
    if (ringbuf_current_size < ringbuf_max_size) {
        ringbuf_current_size++;
    }

    hash_free(hash, ptr);

    return (true);
}

//
// Check a pointer for validity with no recording of history.
//
int ptrcheck_verify (const void *ptr, std::string &func, std::string &file,
                     int line)
{
    if (!ptr_check_some_pointers_changed) {
        return (true);
    }

    return (ptrcheck_verify_pointer(ptr, file, func, line,
                                    false /* don't store */) != 0);
}

//
// Show any leaks
//
void ptrcheck_leak_print (void)
{
    hash_elem_t **slot;
    hash_elem_t *elem;
    Ptrcheck *pc;
    int i;
    int leak;

    leak = 0;

    if (!hash) {
        return;
    }

    for (i = 0; i < hash->hash_size; i++) {
        slot = &hash->elements[i];
        elem = *slot;

        while (elem) {
            pc = elem->pc;
            leak++;

            auto a = pc->allocated_by;
            if (a) {
                std::cerr <<
                    string_sprintf(
                    "PTRCHECK: Leak %p \"%s\" (%u bytes) at %s:%s line %u at %s\n",
                    pc->ptr,
                    pc->what.c_str(),
                    pc->size,
                    a->file.c_str(),
                    a->func.c_str(),
                    a->line,
                    a->ts.c_str());

                std::cerr << a->tb->to_string() << std::endl;
            } else {
                std::cerr <<
                    string_sprintf("PTRCHECK: Leak \"%s\" (%u bytes)\n",
                                   pc->what.c_str(), pc->size);
            }

            //
            // Dump the pointer history.
            //
#ifdef ENABLE_PTRCHECK_HISTORY
            int h = pc->last_seen_at;
            for (auto j=0; j < pc->last_seen_size; j++) {
                if (--h < 0) {
                    h = ENABLE_PTRCHECK_HISTORY-1;
                }

                auto H = pc->last_seen[h];
                if (H) {
                    std::cerr << string_sprintf(
                        "PTRCHECK: Last seen at [%u] at %s:%s line %u at %s\n",
                        j,
                        H->file.c_str(),
                        H->func.c_str(),
                        H->line,
                        H->ts.c_str());
                    std::cerr << H->tb->to_string() << std::endl;
                }
            }
#endif
            if (elem->next == elem) {
                ERR("hash table corruption");
            }

            elem = elem->next;
        }
    }

    if (!leak) {
        CON("No memory leaks!");
    }
}

#if 0
void ptrcheck_usage_cleanup (void)
{
    hash_elem_t //slot;
    hash_elem_t *elem;
    hash_elem_t *next;
    Ptrcheck *pc;
    int i;
    int j;

    if (!hash) {
        return;
    }

    for (i = 0; i < hash->hash_size; i++) {
        slot = &hash->elements[i];
        elem = *slot;

        while (elem) {
            pc = elem->pc;

            if (pc->allocated_by) {
                delete (pc->allocated_by);
            }

            if (pc->freed_by) {
                delete (pc->freed_by);
            }

            for (j=0; j < ENABLE_PTRCHECK_HISTORY; j++) {
                if (pc->last_seen[j]) {
                    delete (pc->last_seen[j]);
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
#endif
