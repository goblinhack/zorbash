//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_ptrcheck.h"
#include "stdlib.h"
#include <string.h>

void *myzalloc_ (int size,
                 std::string what,
                 std::string file,
                 std::string func,
                 int line)
{_
    void *ptr = calloc(1, size);

    if (!ptr) {
        DIE("No memory, %s:%s():%u", file.c_str(), func.c_str(), line);
    }

#ifdef ENABLE_PTRCHECK
    ptrcheck_alloc(ptr, what, size, file, func, line);
#endif

    return (ptr);
}

void *mymalloc_ (int size,
                 std::string what,
                 std::string file,
                 std::string func,
                 int line)
{_
    void *ptr = malloc(size);

    if (!ptr) {
        DIE("No memory, %s:%s():%u", file.c_str(), func.c_str(), line);
    }

#ifdef ENABLE_PTRCHECK
    ptrcheck_alloc(ptr, what, size, file, func, line);
#endif

    return (ptr);
}

void *myrealloc_ (void *ptr,
                  int size,
                  std::string what,
                  std::string file,
                  std::string func,
                  int line)
{_
#ifdef ENABLE_PTRCHECK
    ptrcheck_free(ptr, file, func, line);
#endif

    ptr = realloc(ptr, size);
    if (!ptr) {
        DIE("No memory, %s:%s():%u", file.c_str(), func.c_str(), line);
    }

#ifdef ENABLE_PTRCHECK
    ptrcheck_alloc(ptr, what, size, file, func, line);
#endif

    return (ptr);
}

void myfree_ (void *ptr,
              std::string file,
              std::string func,
              int line)
{_
#ifdef ENABLE_PTRCHECK
    ptrcheck_free(ptr, file, func, line);
#endif

    free(ptr);
}

char *dupstr_ (const char *in,
               std::string what,
               std::string file,
               std::string func,
               int line)
{_
    if (!in) {
        ERR("no string to duplicate");
        return (0);
    }

    char *ptr = strdup(in);
#ifdef ENABLE_PTRCHECK
    int size = (__typeof__(size)) strlen(in);
#endif

    if (!ptr) {
        DIE("No memory, %s:%s():%u", file.c_str(), func.c_str(), line);
    }

#ifdef ENABLE_PTRCHECK
    ptrcheck_alloc(ptr, what, size, file, func, line);
#endif

    return (ptr);
}
