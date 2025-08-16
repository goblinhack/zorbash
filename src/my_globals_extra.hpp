//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GLOBALS_EXTRA_HPP_
#define _MY_GLOBALS_EXTRA_HPP_

#include <string> // do not remove
#include <unordered_map>
#include <vector> // linux

extern std::unordered_map< std::string, class Tile * > all_tiles;
extern std::vector< class Tile * >                     all_tiles_array;

extern int g_opt_test_level_start_depth;

extern std::string g_opt_seed_name;
extern std::string g_opt_player_name;

extern std::string g_log_stderr_filename;
extern std::string g_log_stdout_filename;

extern FILE *g_log_stdout;
extern FILE *g_log_stderr;

#endif
