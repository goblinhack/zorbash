//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_globals.h"

class Game *game;

char *DATA_PATH;
char *EXEC_DIR;
char *EXEC_FULL_PATH_AND_NAME;
char *EXEC_PYTHONPATH;
char *GFX_PATH;
char *TTF_PATH;
char *WORLD_PATH;

FILE *g_log_stdout;
FILE *g_log_stderr;

bool g_die_occurred;           // Fatal error has occurred
bool g_do_screenshot;          // Grab a screen shot next fram
bool g_errored;                // An error has occurred
bool g_grab_next_key;          // Waiting for key input
bool g_need_restart;           // Need to restart game
bool g_opt_debug1;             // Basic debug
bool g_opt_debug2;             // As above but includes log indentation and more detailed debugs
bool g_opt_debug3;             // As above but show the entire level
bool g_opt_debug4;             // As above but include memory checks
bool g_opt_debug5;             // As above but include out of bounds checks
bool g_opt_nodebug;            // Temporary used to disable debugs on load
bool g_opt_fast_start;         // Do not flush after each console log at start
bool g_opt_new_game;           // Start in the game imediately
bool g_quitting;               // Exitting the game
bool g_render_black_and_white; // Rendering map in black and white

std::string g_opt_seed_name;
std::string g_opt_player_name;

int TILES_ACROSS;
int TILES_DOWN;

uint16_t g_last_logged_callframes_depth;
