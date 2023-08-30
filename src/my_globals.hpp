//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GLOBALS_HPP_
#define _MY_GLOBALS_HPP_

extern char *DATA_PATH;
extern char *EXEC_DIR;
extern char *EXEC_FULL_PATH_AND_NAME;
extern char *EXEC_PYTHONPATH;
extern char *GFX_PATH;
extern char *TTF_PATH;
extern char *WORLD_PATH;

extern bool g_die_occurred;             // Fatal error has occurred
extern bool g_do_screenshot;            // Grab a screen shot next fram
extern bool g_errored;                  // An error has occurred
extern bool g_grab_next_key;            // Waiting for key input
extern bool g_loading;                  // Currently loading
extern bool g_main_loop_running;        // SDL main loop is running.
extern bool g_need_restart;             // Need to restart game
extern bool g_opt_ascii;                // Ascii mode
extern bool g_opt_ascii_override;       // Ascii mode forced
extern bool g_opt_biome_chasms;         // Force this biome
extern bool g_opt_biome_flooded;        // Force this biome
extern bool g_opt_biome_ice;            // Force this biome
extern bool g_opt_biome_lava;           // Force this biome
extern bool g_opt_biome_swamp;          // Force this biome
extern bool g_opt_dump_monsters;        // Dump monster info
extern bool g_opt_gfx_monochrome;       // Black and white
extern bool g_opt_no_slow_log_flush;    // Do not flush after each console log at start
extern bool g_opt_override_debug_level; // Temporary, used to disable existing debugs
extern bool g_opt_resume;               // Load last snapshot
extern bool g_opt_silent;               // No audio
extern bool g_opt_test_dungeon_gen;     // Enable dungeon tests
extern bool g_opt_test_level_start;     // Start in the game immediately
extern bool g_opt_tests;                // Any test enabled?
extern bool g_opt_test_save_load;       // Enable save load tests
extern bool g_opt_test_skip_main_menu;  // Start in the dungeon menu
extern bool g_quitting;                 // Exitting the game
extern bool g_render_monochrome;        // Rendering map in black and white
extern bool g_saved_snapshot;           // Just saved a snapshot

// --debug  Basic debug
// --debug2 Map is visible and memory checks enabled
// --debug3 All debugs. Slow.
extern bool g_opt_debug1;
extern bool g_opt_debug2;
extern bool g_opt_debug3;

//
// The number of tiles on screen.
//
extern int TILES_VISIBLE_ACROSS;
extern int TILES_VISIBLE_DOWN;

#define DEBUG1 (unlikely(g_opt_debug1))
#define DEBUG2 (unlikely(g_opt_debug2))
#define DEBUG3 (unlikely(g_opt_debug3))

#define NODEBUG1 (likely(! g_opt_debug1))
#define NODEBUG2 (likely(! g_opt_debug2))
#define NODEBUG3 (likely(! g_opt_debug3))

#define IF_DEBUG                                                                                                     \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)
#define IF_DEBUG1                                                                                                    \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)
#define IF_DEBUG2                                                                                                    \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG2)
#define IF_DEBUG3                                                                                                    \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG3)

#define IF_NODEBUG                                                                                                   \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG1)
#define IF_NODEBUG1                                                                                                  \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG1)
#define IF_NODEBUG2                                                                                                  \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG2)
#define IF_NODEBUG2                                                                                                  \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG2)
#define IF_NODEBUG3                                                                                                  \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG3)

#define ERR                                                                                                          \
  TRACE_NO_INDENT();                                                                                                 \
  myerr

#define dbg                                                                                                          \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)                                                                                                        \
  log
#define dbg2                                                                                                         \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG2)                                                                                                        \
  log
#define dbg3                                                                                                         \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG3)                                                                                                        \
  log

#define DBG                                                                                                          \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)                                                                                                        \
  LOG
#define DBG2                                                                                                         \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG2)                                                                                                        \
  LOG
#define DBG3                                                                                                         \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG3)                                                                                                        \
  LOG

#define AI_LOG                                                                                                       \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)                                                                                                        \
  ai_log

//
// Used to fill in gaps in log depth
//
extern int g_last_logged_callframes_depth;

#define MY_STDERR (g_log_stderr ? g_log_stderr : stderr)
#define MY_STDOUT (g_log_stdout ? g_log_stdout : stdout)

void reset_globals(void);

#endif
