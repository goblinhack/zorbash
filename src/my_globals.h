//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_GLOBALS_H_
#define _MY_GLOBALS_H_

#include <stdio.h> // FILE
#include <map>
#include <vector>
#include <unordered_map>

//
// Forward references
//
struct Thing_;
class Light;
class World;
class Level;
struct Monst_;
class Tile;
class Tex;

using Lightp = class Light*;
using Thingp = struct Thing_*;
using Worldp = class World*;
using Levelp = class Level*;
using Monstp = struct Monst_*;
using Tilep  = class Tile*;
using Texp   = class Tex*;
using Tpp    = class Tp*;

using Tilemap = std::vector<Tilep>;
using Tpidmap = std::vector<Tpp>;
using Tpnamemap = std::unordered_map< std::string, Tpp >;

extern class Game *game;

extern Tpidmap tp_id_map;
extern Tpnamemap tp_name_map;
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

extern bool g_croaked;
extern bool g_do_screenshot;
extern bool g_errored;
extern bool g_grab_next_key;
extern bool g_need_restart;
extern bool g_opt_ascii_mode;
extern bool g_opt_debug;
extern bool g_opt_fast_start;
extern bool g_opt_new_game;
extern bool g_quitting;
extern bool g_render_black_and_white;
extern int g_opt_seed;

extern int TILES_ACROSS;
extern int TILES_DOWN;

//
// Shorter callstack indent printing logs inside thing code
//
extern uint16_t g_thing_callframes_depth;

#endif
