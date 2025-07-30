//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"

#define __MAIN__

#ifdef USE_THREADS
#ifdef __MAIN__
thread_local struct callframe callframes[ MAXCALLFRAME ];
thread_local unsigned char    g_callframes_depth;
thread_local unsigned char    g_callframes_indent;
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
