/*
 * Copyright (C) 2018 goblinhack@gmail.com
 * See the README file for license info for license.
 */

#include "my_main.h"
#include "my_backtrace.h"

typedef struct traceback_ {
    void *array[MAX_TRACEBACK];
    uint32_t size;
} traceback;

/*
 * Allocate a new traceback.
 */
traceback *traceback_alloc (void)
{_
#ifndef WIN32
    traceback *tb;

    tb = (__typeof__(tb)) malloc(sizeof(*tb));

    tb->size = backtrace(tb->array, MAX_TRACEBACK);

    return (tb);
#else
    return (0);
#endif
}

/*
 * Free a traceback.
 */
void traceback_free (traceback *tb)
{_
#ifndef WIN32
    free(tb);
#endif
}

/*
 * Free a traceback.
 */
void traceback_stdout (traceback *tb)
{_
#ifndef WIN32
    backtrace_print(MY_STDOUT, tb->array, tb->size);
#endif
}

/*
 * Free a traceback.
 */
void traceback_stderr (traceback *tb)
{_
#ifndef WIN32
    backtrace_print(MY_STDERR, tb->array, tb->size);
#endif
}
