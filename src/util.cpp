/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */


#include "my_main.h"
#include "my_ptrcheck.h"
#include "stdlib.h"

void *myzalloc_ (uint32_t size,
                 const char *what,
                 const char *file,
                 const char *func,
                 const uint32_t line)
{_
    void *ptr = calloc(1, size);

    if (!ptr) {
        DIE("No memory, %s:%s():%u", file, func, line);
    }

#ifdef ENABLE_PTRCHECK
    ptrcheck_alloc(ptr, what, size, file, func, line);
#endif

    return (ptr);
}

void *mymalloc_ (uint32_t size,
                 const char *what,
                 const char *file,
                 const char *func,
                 const uint32_t line)
{_
    void *ptr = malloc(size);

    if (!ptr) {
        DIE("No memory, %s:%s():%u", file, func, line);
    }

#ifdef ENABLE_PTRCHECK
    ptrcheck_alloc(ptr, what, size, file, func, line);
#endif

    return (ptr);
}

void *myrealloc_ (void *ptr,
                  uint32_t size,
                  const char *what,
                  const char *file,
                  const char *func,
                  const uint32_t line)
{_
#ifdef ENABLE_PTRCHECK
    ptrcheck_free(ptr, file, func, line);
#endif

    ptr = realloc(ptr, size);
    if (!ptr) {
        DIE("No memory, %s:%s():%u", file, func, line);
    }

#ifdef ENABLE_PTRCHECK
    ptrcheck_alloc(ptr, what, size, file, func, line);
#endif

    return (ptr);
}

void myfree_ (void *ptr,
              const char *file,
              const char *func,
              const uint32_t line)
{_
#ifdef ENABLE_PTRCHECK
    ptrcheck_free(ptr, file, func, line);
#endif

    free(ptr);
}

char *dupstr_ (const char *in,
               const char *what,
               const char *file,
               const char *func,
               const uint32_t line)
{_
    if (!in) {
        ERR("no string to duplicate");
        return (0);
    }

    char *ptr = strdup(in);
#ifdef ENABLE_PTRCHECK
    uint32_t size = (__typeof__(size)) strlen(in);
#endif

    if (!ptr) {
        DIE("No memory, %s:%s():%u", file, func, line);
    }

#ifdef ENABLE_PTRCHECK
    ptrcheck_alloc(ptr, what, size, file, func, line);
#endif

    return (ptr);
}
