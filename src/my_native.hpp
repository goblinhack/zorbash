//
// Copyright goblinhack@gmail.com
//
// Native replacement for the embedded python support.
//
// Thing templates, tiles, sounds and level rooms used to be described by python modules that
// were loaded at startup (python/things/...). Those modules are now plain C++ (src/things/...),
// and the functions they used to reach via the python `my` module live in `namespace my`.
//
// Event callbacks (on_hit, on_tick...) are still named by string in a thing template
// ("me.on_hit()"). Each converted module registers its callbacks in the table below at startup
// and the game dispatches to them with native_call_*_fn().
//

#pragma once
#ifndef _MY_NATIVE_HPP_
#define _MY_NATIVE_HPP_

#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "my_ascii.hpp"
#include "my_dice.hpp"
#include "my_enums.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sound.hpp"
#include "my_thing_template.hpp"

//
// Callback registry
//
struct NativeRet {
  int                        value {};   // result of void (0), bool (0/1) and int callbacks
  std::vector< std::string > strings;    // result of callbacks that return a list of strings
};

using NativeFn = std::function< NativeRet(const int64_t *) >;

//
// Register a callback as module.name. nargs is the number of integer arguments the callback takes.
//
void native_register(const char *module, const char *name, int nargs, NativeFn fn);

//
// Called by native_call_*_fn() below. Logs an error and returns a default result if the callback is not
// registered or was registered with a different number of arguments.
//
NativeRet native_dispatch(const char *module, const char *name, const int64_t *args, int nargs);

template < typename... Args > inline void native_call_void_fn(const char *module, const char *name, Args... args)
{
  const int64_t v[] = {static_cast< int64_t >(args)..., 0};
  native_dispatch(module, name, v, static_cast< int >(sizeof...(Args)));
}

template < typename... Args > inline int native_call_int_fn(const char *module, const char *name, Args... args)
{
  const int64_t v[] = {static_cast< int64_t >(args)..., 0};
  return native_dispatch(module, name, v, static_cast< int >(sizeof...(Args))).value;
}

template < typename... Args > inline bool native_call_bool_fn(const char *module, const char *name, Args... args)
{
  const int64_t v[] = {static_cast< int64_t >(args)..., 0};
  return native_dispatch(module, name, v, static_cast< int >(sizeof...(Args))).value != 0;
}

template < typename... Args >
inline std::vector< std::string > native_call_std_vector_string_fn(const char *module, const char *name, Args... args)
{
  const int64_t v[] = {static_cast< int64_t >(args)..., 0};
  return native_dispatch(module, name, v, static_cast< int >(sizeof...(Args))).strings;
}

//
// Registers every converted module (things, tiles, sounds, rooms...) in the order the python loader used.
// The body of this function is generated into native_modules.cpp.
//
void native_init_all(void);

//
// Load all native modules.
//
void native_init(void);

//
// Arguments to my::tile() and friends. Field order matches the order of the former python keywords so
// that they can be used as C++20 designated initializers, e.g.
//
//   my::tile(tp, {.tile = "sword", .delay_ms = 100});
//
struct TileArgs {
  std::optional< std::string > tile;
  std::optional< std::string > ascii_fg_char;
  std::optional< std::string > ascii_bg_char;
  std::optional< std::string > ascii_bg_col_name;
  std::optional< std::string > ascii_fg_col_name;
  int                          ascii_bg_alpha {255};
  int                          ascii_fg_alpha {255};
  int                          delay_ms {};
  int                          frame {};
  int                          is_moving {};
  int                          is_jumping {};
  int                          begin_jump {};
  int                          is_outline {};
  int                          is_dir_left {};
  int                          is_dir_right {};
  int                          is_dir_up {};
  int                          is_dir_down {};
  int                          is_dir_none {};
  int                          is_yyy5 {};
  int                          is_yyy6 {};
  int                          is_yyy7 {};
  int                          is_yyy8 {};
  int                          is_yyy9 {};
  int                          is_invisible {};
  int                          is_hp_25_percent {};
  int                          is_hp_50_percent {};
  int                          is_hp_75_percent {};
  int                          is_hp_100_percent {};
  int                          is_in_water {};
  int                          is_sleeping {};
  int                          is_open {};
  int                          is_dead {};
  int                          is_end_of_anim {};
  int                          is_end_of_ascii_anim {};
  int                          is_dead_on_end_of_anim {};
  int                          is_dead_on_end_of_ascii_anim {};
  int                          is_alive_on_end_of_anim {};
  int                          is_alive_on_end_of_ascii_anim {};
  int                          is_resurrecting {};
};

namespace my {

//
// Create (or find) a thing template. The long name defaults to the name, and the short name to the long name.
//
Tpp tp_load(const std::string &name);
Tpp tp_load(const std::string &name, const std::string &text_long_name);
Tpp tp_load(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);

//
// Add a tile (animation frame) to a thing template. The directional variants add to the per direction frames.
//
bool tile(Tpp tp, const TileArgs &args);
bool top1_tile(Tpp tp, const TileArgs &args);
bool top2_tile(Tpp tp, const TileArgs &args);
bool bot1_tile(Tpp tp, const TileArgs &args);
bool bot2_tile(Tpp tp, const TileArgs &args);
bool bot3_tile(Tpp tp, const TileArgs &args);
bool left1_tile(Tpp tp, const TileArgs &args);
bool left2_tile(Tpp tp, const TileArgs &args);
bool right1_tile(Tpp tp, const TileArgs &args);
bool right2_tile(Tpp tp, const TileArgs &args);
bool tl1_tile(Tpp tp, const TileArgs &args);
bool tl2_tile(Tpp tp, const TileArgs &args);
bool tr1_tile(Tpp tp, const TileArgs &args);
bool tr2_tile(Tpp tp, const TileArgs &args);
bool bl1_tile(Tpp tp, const TileArgs &args);
bool bl2_tile(Tpp tp, const TileArgs &args);
bool br1_tile(Tpp tp, const TileArgs &args);
bool br2_tile(Tpp tp, const TileArgs &args);

//
// Helpers used by converted code. Integer power (python ** on ints) and a cosmetic random choice (python's
// random.choice was not seeded by the game, so this uses the non-deterministic generator).
//
inline int ipow2(int v)
{
  return v * v;
}

int non_pcg_random_inclusive(int lo, int hi);

template < typename T > inline const T &random_choice(const std::vector< T > &v)
{
  return v.at(static_cast< size_t >(non_pcg_random_inclusive(0, static_cast< int >(v.size()) - 1)));
}

//
// Random numbers. These are functions, as the underlying macros evaluate their arguments more than once.
//
int pcg_random_inclusive(int lo, int hi);
int non_pcg_random_inclusive(int lo, int hi);

//
// Console and logging
//
void log(const char *msg);
void topcon(const char *msg);

//
// Game state requests
//
void game_set_request_to_update_same_level(void);

} // namespace my

#include "my_native_api.hpp"

#endif
