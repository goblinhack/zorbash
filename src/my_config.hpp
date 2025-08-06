//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_CONFIG_HPP_
#define _MY_CONFIG_HPP_

#define ENABLE_ASSERT                 // Abort on errors
#define ENABLE_CRASH_HANDLER          // Intercept SEGV and other faults
#define ENABLE_DEBUG_TRACE            // (SLOW) Function tracing
#define ENABLE_PTRCHECK_HISTORY   2   // Per pointer history (when in --debug2 mode)
#define ENABLE_SAVE_SNAPSHOT_FREQ 500 // How often/move count, to save a snapshot

#undef ENABLE_DEBUG_AI_ASTAR            // Astar AI path costs
#undef ENABLE_DEBUG_AI_WANDER           // AI wander path selection
#undef ENABLE_DEBUG_EXTRA_BOUNDS_CHECKS // (SLOW)
#undef ENABLE_DEBUG_GFX_GL_BLEND        // Use to debug specific blends
#undef ENABLE_DEBUG_MEM_LEAKS           // Check for leaks at exit
#undef ENABLE_DEBUG_PTRCHECK            // (VERY SLOW) Debug ptrcheck itself
#undef ENABLE_DEBUG_THING_SER           // Extra debugging in thing save/load
#undef ENABLE_DEBUG_TILE                // Debug tile loading
#undef ENABLE_DEBUG_UI2                 // User interface logs with inheritance
#undef ENABLE_DEBUG_UI_FOCUS            // Which windows we are over
#undef ENABLE_DEBUG_UI                  // User interface logs
#undef ENABLE_LOG_TIMESTAMPS            // Full timestamps with date in logs
#undef ENABLE_UI_ASCII_MOUSE            // Show an in-game mouse, not system mouse

#endif
