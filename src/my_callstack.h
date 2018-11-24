/*
 * Copyright (C) 2018 goblinhack@gmail.com
 
 * See the README file for license info for license.
 */

#pragma once

#ifndef _MY_CALLSTACK_H_
#define _MY_CALLSTACK_H_

#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>

#define CAT(A, B) A ## B
#define CAT2(A, B) CAT(A, B)

#undef _
#define _ tracer_t CAT2(__my_trace__, __LINE__) (__FILE__, __PRETTY_FUNCTION__, __LINE__);

struct callframe {
    const char *const file;
    const char *const func;
    unsigned int line;
};

class callstack {
public:
    callstack(void) {
    }
    void dump(void);

    std::vector<struct callframe> my_stack;
};

/*
 * Using thread_local here was ok, but caused crashes in destructors
 */
#ifdef __MAIN__
class callstack global_callstack;
#else
extern class callstack global_callstack;
#endif

struct tracer_t {
    tracer_t (const char *const file, 
              const char *const func, 
              const unsigned int line) :
              file(file), func(func), line(line)
    {
        // useful for code tracing in real time
        // fprintf(stderr, "%s %s() line %d\n", file, func, line);
        callframe c = { file, func, line };
        global_callstack.my_stack.push_back(c);
    }

    ~tracer_t()
    {
        global_callstack.my_stack.pop_back();
    }

    std::string file;
    std::string func;
    unsigned int line;
};
#endif
