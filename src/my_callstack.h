//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_CALLSTACK_H_
#define _MY_CALLSTACK_H_

#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

#define CAT(A, B) A ## B
#define CAT2(A, B) CAT(A, B)

#undef _

#ifdef ENABLE_TRACING
#define _ tracer_t CAT2(__my_trace__, __LINE__) (__FILE__, __PRETTY_FUNCTION__, __LINE__);
#else
#define _
#endif

struct callframe {
    const char *file;
    const char *func;
    unsigned short line;
};

//
// I used to use a c++ vector here, but global destructor order meant
// this was unreliable for tracing classes as they are destroyed after
// the callstack vector
//
#define MAXCALLFRAME 1024
#ifdef __MAIN__
struct callframe callframes[MAXCALLFRAME];
unsigned short callframes_depth;
#else
extern struct callframe callframes[MAXCALLFRAME];
extern unsigned short callframes_depth;
#endif
extern void callstack_dump(void);

struct tracer_t {
    tracer_t (const char *file,
              const char *func,
              const unsigned short line)
    {
        // useful for code tracing in real time
        // fprintf(stderr, "%s %s() line %d\n", file, func, line);
        if (callframes_depth < MAXCALLFRAME) {
            callframe *c = &callframes[callframes_depth++];
            c->file = file;
            c->func = func;
            c->line = line;
        }
    }

    ~tracer_t()
    {
        if (callframes_depth > 0) {
            callframes_depth--;
        }
    }
};
#endif
