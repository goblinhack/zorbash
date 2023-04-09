//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_globals_extra.hpp"

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

bool g_die_occurred;             // Fatal error has occurred
bool g_do_screenshot;            // Grab a screen shot next fram
bool g_errored;                  // An error has occurred
bool g_grab_next_key;            // Waiting for key input
bool g_loading;                  // Currently loading
bool g_main_loop_running;        // SDL main loop running.
bool g_need_restart;             // Need to restart game
bool g_opt_ascii;                // Ascii mode
bool g_opt_ascii_override;       // Ascii mode forced
bool g_opt_new_game;             // Start in the dungeon menu
bool g_opt_no_slow_log_flush;    // Do not flush after each console log at start
bool g_opt_override_debug_level; // Temporary used to disable debugs on load
bool g_opt_quickstart;          // Start in the game imediately
bool g_opt_resume;               // Load last snapshot
bool g_opt_test;                 // Enable some tests at start.
bool g_quitting;                 // Exitting the game
bool g_render_black_and_white;   // Rendering map in black and white
bool g_saved_snapshot;           // Just saved a snapshot
bool g_opt_biome_swamp;          // Test biome swamp

// --debug  Basic debug
// --debug2 Map is visible and memory checks enabled
// --debug3 All debugs. Slow.
bool g_opt_debug1; // Basic debug
bool g_opt_debug2; // As above but includes log indentation and more detailed debugs
bool g_opt_debug3; // As above but show the entire level

std::string g_opt_seed_name;
std::string g_opt_player_name;

//
// The number of tiles on screen.
//
int TILES_VISIBLE_ACROSS;
int TILES_VISIBLE_DOWN;

//
// Flexible map size
//
int MAP_HEIGHT;
int MAP_WIDTH;
int DUNGEON_GRID_CHUNK_HEIGHT;
int DUNGEON_GRID_CHUNK_WIDTH;

int g_last_logged_callframes_depth;
