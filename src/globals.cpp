//
// Copyright goblinhack@gmail.com
// See the README file for license info.
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

bool g_croaked;
bool g_do_screenshot;
bool g_errored;
bool g_grab_next_key;
bool g_need_restart;
bool g_opt_debug_mode;
bool g_opt_fast_start;
bool g_opt_new_game;
bool g_quitting;
bool g_render_black_and_white;
int g_opt_seed;

int TILES_ACROSS;
int TILES_DOWN;

uint16_t g_thing_callframes_depth;
