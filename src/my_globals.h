//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_GLOBALS_H_
#define _MY_GLOBALS_H_

#include <map>
#include <vector> // linux
#include <unordered_map>
#include <string>

extern std::map<std::string, class Tile* > all_tiles;
extern std::vector<class Tile* > all_tiles_array;

extern char *DATA_PATH;
extern char *EXEC_DIR;
extern char *EXEC_FULL_PATH_AND_NAME;
extern char *EXEC_PYTHONPATH;
extern char *GFX_PATH;
extern char *TTF_PATH;
extern char *WORLD_PATH;

extern FILE *g_log_stdout;
extern FILE *g_log_stderr;

extern bool g_die_occurred;           // Fatal error has occurred
extern bool g_do_screenshot;          // Grab a screen shot next fram
extern bool g_errored;                // An error has occurred
extern bool g_grab_next_key;          // Waiting for key input
extern bool g_need_restart;           // Need to restart game
extern bool g_opt_debug1;             // Basic debug
extern bool g_opt_debug2;             // As above but includes log indentation and more detailed debugs
extern bool g_opt_debug3;             // As above but show the entire level
extern bool g_opt_debug4;             // As above but include memory checks
extern bool g_opt_debug5;             // As above but include out of bounds checks
extern bool g_opt_nodebug;            // Temporary, used to disable existing debugs
extern bool g_opt_fast_start;         // Do not flush after each console log at start
extern bool g_opt_new_game;           // Start in the game imediately
extern bool g_quitting;               // Exitting the game
extern bool g_render_black_and_white; // Rendering map in black and white
extern std::string g_opt_seed_name;
extern std::string g_opt_player_name;

extern int TILES_ACROSS;
extern int TILES_DOWN;

//
// Used to fill in gaps in log depth
//
extern uint16_t g_last_logged_callframes_depth;

#define MY_STDERR (g_log_stderr ? g_log_stderr : stderr)
#define MY_STDOUT (g_log_stdout ? g_log_stdout : stdout)

#endif
