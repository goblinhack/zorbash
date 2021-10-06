//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_GLOBALS_H_
#define _MY_GLOBALS_H_

#include <map>
#include <string>
#include <vector> // linux

extern std::map< std::string, class Tile * > all_tiles;
extern std::vector< class Tile * >           all_tiles_array;

extern char *DATA_PATH;
extern char *EXEC_DIR;
extern char *EXEC_FULL_PATH_AND_NAME;
extern char *EXEC_PYTHONPATH;
extern char *GFX_PATH;
extern char *TTF_PATH;
extern char *WORLD_PATH;

extern FILE *g_log_stdout;
extern FILE *g_log_stderr;

extern bool        g_die_occurred;             // Fatal error has occurred
extern bool        g_do_screenshot;            // Grab a screen shot next fram
extern bool        g_errored;                  // An error has occurred
extern bool        g_grab_next_key;            // Waiting for key input
extern bool        g_need_restart;             // Need to restart game
extern bool        g_loading;                  // Currently loading
extern bool        g_saved_snapshot;           // Just saved a snapshot
extern bool        g_opt_debug1;               // Basic debug
extern bool        g_opt_debug2;               // As above but includes log indentation and more detailed debugs
extern bool        g_opt_debug3;               // As above but show the entire level
extern bool        g_opt_debug4;               // As above but include memory checks
extern bool        g_opt_debug5;               // As above but include out of bounds checks
extern bool        g_opt_override_debug_level; // Temporary, used to disable existing debugs
extern bool        g_opt_fast_start;           // Do not flush after each console log at start
extern bool        g_opt_new_game;             // Start in the game imediately
extern bool        g_opt_resume;               // Load last snapshot
extern bool        g_quitting;                 // Exitting the game
extern bool        g_render_black_and_white;   // Rendering map in black and white
extern std::string g_opt_seed_name;
extern std::string g_opt_player_name;

extern int TILES_ACROSS;
extern int TILES_DOWN;

#define DEBUG1 (unlikely(g_opt_debug1))
#define DEBUG2 (unlikely(g_opt_debug2))
#define DEBUG3 (unlikely(g_opt_debug3))
#define DEBUG4 (unlikely(g_opt_debug4))
#define DEBUG5 (unlikely(g_opt_debug5))

#define NODEBUG1 (likely(! g_opt_debug1))
#define NODEBUG2 (likely(! g_opt_debug2))
#define NODEBUG3 (likely(! g_opt_debug3))
#define NODEBUG4 (likely(! g_opt_debug4))
#define NODEBUG5 (likely(! g_opt_debug5))

#define IF_DEBUG1                                                                                                      \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG1)
#define IF_DEBUG2                                                                                                      \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG2)
#define IF_DEBUG3                                                                                                      \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG3)
#define IF_DEBUG4                                                                                                      \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG4)
#define IF_DEBUG5                                                                                                      \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG5)

#define IF_NODEBUG1                                                                                                    \
  TRACE_NO_INDENT();                                                                                                   \
  if (NODEBUG1)
#define IF_NODEBUG2                                                                                                    \
  TRACE_NO_INDENT();                                                                                                   \
  if (NODEBUG2)
#define IF_NODEBUG3                                                                                                    \
  TRACE_NO_INDENT();                                                                                                   \
  if (NODEBUG3)
#define IF_NODEBUG4                                                                                                    \
  TRACE_NO_INDENT();                                                                                                   \
  if (NODEBUG4)
#define IF_NODEBUG5                                                                                                    \
  TRACE_NO_INDENT();                                                                                                   \
  if (NODEBUG5)

#define ERR                                                                                                            \
  TRACE_NO_INDENT();                                                                                                   \
  myerr

#define dbg                                                                                                            \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG1)                                                                                                          \
  log
#define dbg2                                                                                                           \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG2)                                                                                                          \
  log
#define dbg3                                                                                                           \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG3)                                                                                                          \
  log
#define dbg4                                                                                                           \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG4)                                                                                                          \
  log
#define dbg5                                                                                                           \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG5)                                                                                                          \
  log

#define DBG                                                                                                            \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG1)                                                                                                          \
  LOG
#define DBG2                                                                                                           \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG2)                                                                                                          \
  LOG
#define DBG3                                                                                                           \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG3)                                                                                                          \
  LOG
#define DBG4                                                                                                           \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG4)                                                                                                          \
  LOG
#define DBG5                                                                                                           \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG5)                                                                                                          \
  LOG

#define AI_LOG                                                                                                         \
  TRACE_NO_INDENT();                                                                                                   \
  if (DEBUG3)                                                                                                          \
  ai_log

//
// Used to fill in gaps in log depth
//
extern uint16_t g_last_logged_callframes_depth;

#define MY_STDERR (g_log_stderr ? g_log_stderr : stderr)
#define MY_STDOUT (g_log_stdout ? g_log_stdout : stdout)

#endif
