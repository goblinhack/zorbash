//
// Copyright Neil McGill, goblinhack@gmail.com
//
#pragma once
#ifndef _MY_CALLSTACK_HPP_
#define _MY_CALLSTACK_HPP_

#include "my_globals.hpp"
#include "my_sys.hpp"
#include <string>

#define CAT(A, B)  A##B
#define CAT2(A, B) CAT(A, B)

#ifdef ENABLE_DEBUG_TRACE
#define TRACE_AND_INDENT() tracer_t CAT2(__my_trace__, __LINE__)(SRC_FUNC_NAME, SRC_LINE_NUM);
#define TRACE_NO_INDENT()  tracer_no_indent_t CAT2(__my_trace__, __LINE__)(SRC_FUNC_NAME, SRC_LINE_NUM);
#else
#define TRACE_AND_INDENT()
#define TRACE_NO_INDENT()
#endif

struct callframe {
  const char    *func;
  unsigned short line;
};

//
// I used to use a c++ vector here, but global destructor order meant
// this was unreliable for tracing classes as they are destroyed after
// the callstack vector
//
#define MAXCALLFRAME 255
#ifdef USE_THREADS
#ifdef __MAIN__
thread_local struct callframe callframes[ MAXCALLFRAME ];
thread_local unsigned char    g_callframes_depth;
#else
extern thread_local struct callframe callframes[ MAXCALLFRAME ];
extern thread_local unsigned char    g_callframes_depth;
extern thread_local unsigned char    g_callframes_indent;
#endif
#else
#ifdef __MAIN__
struct callframe callframes[ MAXCALLFRAME ];
unsigned char    g_callframes_depth;
unsigned char    g_callframes_indent;
#else
extern struct callframe callframes[ MAXCALLFRAME ];
extern unsigned char    g_callframes_depth;
extern unsigned char    g_callframes_indent;
#endif
#endif

extern void        callstack_dump(void);
extern std::string callstack_string(void);

struct tracer_t {
  inline tracer_t(const char *func, const unsigned short line)
  {
// useful for code tracing in real time
// fprintf(stderr, "%s %s() line %d\n", file, func, line);
#ifdef ENABLE_DEBUG_TRACE
    if (unlikely(g_callframes_depth < MAXCALLFRAME)) {
      g_callframes_indent++;
      callframe *c = &callframes[ g_callframes_depth++ ];
      c->func      = func;
      c->line      = line;
    }
#endif
  }

  inline ~tracer_t()
  {
#ifdef ENABLE_DEBUG_TRACE
    if (g_callframes_indent > 0) { g_callframes_indent--; }
    if (g_callframes_depth > 0) { g_callframes_depth--; }
#endif
  }
};

struct tracer_no_indent_t {
  inline tracer_no_indent_t(const char *func, const unsigned short line)
  {
// useful for code tracing in real time
// fprintf(stderr, "%s %s() line %d\n", file, func, line);
#ifdef ENABLE_DEBUG_TRACE
    if (unlikely(g_callframes_depth < MAXCALLFRAME)) {
      callframe *c = &callframes[ g_callframes_depth++ ];
      c->func      = func;
      c->line      = line;
    }
#endif
  }

  inline ~tracer_no_indent_t()
  {
#ifdef ENABLE_DEBUG_TRACE
    if (g_callframes_depth > 0) { g_callframes_depth--; }
#endif
  }
};
#endif
