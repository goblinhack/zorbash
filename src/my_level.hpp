//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LEVEL_HPP_
#define _MY_LEVEL_HPP_

#include <deque>
#include <list>

#include "my_dmap.hpp"
#include "my_enums.hpp"
#include "my_fcolor.hpp"
#include "my_fwd.hpp"
#include "my_laser.hpp"
#include "my_level_fov.hpp"
#include "my_particle.hpp"
#include "my_point3d.hpp"
#include "my_projectile.hpp"
#include "my_thing_template.hpp"
#include "my_time.hpp"

class Level
{
public:
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX * DUNGEON_GAS_RESOLUTION >, MAP_WIDTH_MAX * DUNGEON_GAS_RESOLUTION >
      gas_poison_cloud {};

  //
  // These are caches for fast lookup in display code
  //
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_gas_blocker {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_light_blocker {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_light_blocker_for_monst {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_obs_destructable {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_obs_wall_or_door {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_obs_when_dead {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_obs_for_jump_landing {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_walked {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _noise_blocker {};

  // begin sort marker1 {
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _fade_in_map {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _gfx_water {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _heatmap {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_able_to_amplify_footsteps {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_able_to_dampen_footsteps {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_able_to_stand_on {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_acid {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_ascend_dungeon {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_ascend_sewer {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_attackable_by_monst {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_attackable_by_player {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_barrel {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_basalt {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_block_of_ice {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_brazier {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_bridge {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_burnable {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_carnivorous_plant {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_chasm {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_cold {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_combustible {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_corpse {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_corridor {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_currently_pixelart_raycast_lit {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_cursor_path_blocker {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_cursor_path_hazard {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_deep_water {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_descend_dungeon {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_descend_sewer {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_dirt {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_door {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_dry_grass {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_enchantstone {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_fire {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_floor {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_foliage {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_food {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_gas_poison {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_gold {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_green_blood {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_hazard {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_heavy {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_key {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_lava {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_mob {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_monst {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_portal {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_potion {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_red_blood {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_ring {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_ripple {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_rock {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_secret_door {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_shallow_water {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_shovable {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_skillstone {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_smoke {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_spiderweb {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_staff {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_steam {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_sticky {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_tentacle {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_torch {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_trap {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_treasure_type {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_wall {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _is_wet_grass {};
  // end sort marker1 }

  //
  // This is what the player has seen on this level, now and forever.
  //
  FovMap can_see_currently; // Shadowcasting of what can be seen currently
  FovMap can_see_ever;      // Shadowcasting of what can be seen ever on this level

  //
  // Holds noise as it fades around the level
  //
  Dmap _noisemap {};
  Dmap _noisemap_in {};

  //
  // For level transitions
  //
  std::vector< point3d > prev_levels;
  std::vector< point3d > next_levels;

  //
  // When this Level was made. Used to restore timestamps relative to this.
  //
  ts_t ts_created {};
  //
  // When the player/sucker entered this level.
  //
  ts_t ts_entered {};
  //
  // When we saved this level. Used to restore other timestamps.
  //
  ts_t ts_saved {};
  //
  // Fade in/out (only for pixel art mode)
  //
  ts_t ts_fade_out_begin {};
  ts_t ts_fade_in_begin {};

  uint32_t tick_created {};

  //
  // Where we are in the world
  //
  point3d world_at;

  //
  // Where in the 2d grid presented at game start, we are
  //
  point grid_at;

  //
  // What type of level
  //
  biome_t biome = {BIOME_UNKNOWN};

  //
  // Levels are grouped into difficulty levels
  //
  int difficulty_depth {};
  int dungeon_walk_order_level_no {};

  bool is_shop_level {};
  bool is_boss_level {};
  bool is_final_boss_level {};
  bool is_crystal_level {};

  //
  // Chances for various things to appear
  //
  std::array< std::array< int, MONST_CLASS_MAX >, MONST_ENVIRON_MAX > d1000_chance_of_creating_monst {};

  //
  // Set to -1 to mean no chance
  //
  int d1000_chance_of_creating_mob_challenge_class_A {};
  int d1000_chance_of_creating_mob_challenge_class_B {};
  int d1000_chance_of_creating_treasure_class_A {};
  int d1000_chance_of_creating_treasure_class_B {};
  int d1000_chance_of_creating_treasure_class_C {};
  int d1000_chance_of_creating_weapon_class_A {};
  int d1000_chance_of_creating_weapon_class_B {};
  int d1000_chance_of_creating_weapon_class_C {};

  //
  // Current on screen map limits in tile coords
  //
  int minx {};
  int maxx {};
  int miny {};
  int maxy {};

  bool is_cursor_found {};
  bool is_final_level {};
  bool is_first_level {};
  bool is_completed {}; // Player exited this level
  bool is_heatmap_valid {};
  bool is_map_changed {}; // Something moved on the map
  bool is_map_follow_player {};
  bool is_map_mini_valid {};
  bool is_starting {}; // Loading level
  bool is_entered_by_falling {};

  point cursor_at;
  point cursor_old;
  point map_br;       // visible map br
  point map_tl;       // visible map tl
  point pixel_map_at; // map pixel location

  fpoint map_at;        // map tile location
  fpoint map_wanted_at; // map scroll desired at

  int mouse_at {-1}; // ticks for every move
  int mouse_old {-1};

  //
  // Level shake
  //
  float wobble = {};

  //
  // Monsters on the level
  //
  int monst_count {};

  //
  // All randomness jumps off of this as the root
  //
  uint32_t seed {};

  //
  // Everything thing on the level. Not all in the game, just this level.
  //
  std::map< ThingId, Thingp > all_things {};

  //
  // For all things that move, like monsters, or those that do not, like wands, and even those that do not move but
  // can be destroyed, like walls. Omits things like floors, corridors, the grid; those that generally do nothing or
  // are hidden.
  //
  bool                        interesting_things_walk_in_progress {};
  std::map< ThingId, Thingp > interesting_things {};
  std::map< ThingId, Thingp > interesting_things_pending_add {};
  std::map< ThingId, Thingp > interesting_things_pending_remove {};

  //
  // Only things that actively do something in the level tick, like
  // monsters or maybe magical items that do something per tick.
  //
  bool                        tickable_things_walk_in_progress {};
  std::map< ThingId, Thingp > tickable_things {};
  std::map< ThingId, Thingp > tickable_things_pending_add {};
  std::map< ThingId, Thingp > tickable_things_pending_remove {};

  //
  // A smaller set of things that are animated. This is more efficient to
  // talk as it is called per frame.
  //
  bool                        animated_things_walk_in_progress {};
  std::map< ThingId, Thingp > animated_things {};
  std::map< ThingId, Thingp > animated_things_pending_add {};
  std::map< ThingId, Thingp > animated_things_pending_remove {};

  //
  // Only things that have a description when we hover over.
  //
  bool                        describable_things_walk_in_progress {};
  std::map< ThingId, Thingp > describable_things {};
  std::map< ThingId, Thingp > describable_things_pending_add {};
  std::map< ThingId, Thingp > describable_things_pending_remove {};

  //
  // This is for things that do not tick, like water; that need to fall
  //
  std::map< ThingId, Thingp > all_things_pending_fall {};

  //
  // All things that are to be destroyed
  //
  std::map< ThingId, Thingp > all_things_to_be_destroyed {};

  //
  // All thing IDs at a given map cell
  //
  std::array< std::array< std::array< ThingId, MAP_SLOTS >, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > all_things_id_at {};

  //
  // All thing pointers at a given map cell
  //
  std::array< std::array< std::vector< Thingp >, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > all_things_ptr_at {};

  //
  // This is what we've lit on this level, so we can restore it
  // when we return
  //
  std::vector< uint8_t > fbo_light;

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////

  //
  // Only used in ascii mode and updated per frame
  //
  std::array< std::array< fcolor, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > _ascii_light_source {};

  //
  // Update thing_fini.cpp when adding more references to Thingp
  //
  Thingp player     = {};
  Thingp cursor     = {};
  Thingp highlight  = {};
  Thingp hover_over = {};

  //
  // Things that are shown on the left bar.
  //
  std::list< ThingId > wid_leftbar_things;

  //
  // Tile maps for rendering solid blocks of water etc...
  //
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX + 8 >, MAP_WIDTH_MAX + 8 > water_tile_map      = {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX + 8 >, MAP_WIDTH_MAX + 8 > deep_water_tile_map = {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX + 8 >, MAP_WIDTH_MAX + 8 > lava_tile_map       = {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX + 8 >, MAP_WIDTH_MAX + 8 > basalt_tile_map     = {};
  std::array< std::array< uint8_t, MAP_HEIGHT_MAX + 8 >, MAP_WIDTH_MAX + 8 > chasm_tile_map      = {};

  bool is_being_destroyed {};
  bool cursor_update_needed {};
  bool fade_out_finished {};
  bool request_dmap_to_player_update {};
  bool request_player_light_update {};

  //
  // Animation loop counters for surface effects
  //
  int   water_step1 {};
  float water_step2 {};
  int   deep_water_step1 {};
  float deep_water_step2 {};
  int   lava_step1 {};
  float lava_step2 {};

  //
  // If set, redraw the background; allows for dampening
  //
  ts_t ts_redraw_bg {};

  //
  // For thing effects, like jumping
  //
  std::vector< Particle > all_internal_particles;
  std::vector< Particle > new_internal_particles;

  //
  // For things like move of items into inventory
  //
  std::vector< Particle > all_external_particles;
  std::vector< Particle > new_external_particles;

  std::vector< Projectile > all_projectiles;
  std::vector< Projectile > new_projectiles;

  std::vector< Laser > all_lasers;
  std::vector< Laser > new_lasers;

  //
  // Where the map_mini widget ois
  //
  point map_mini_tl;
  point map_mini_br;
  point map_debug_tl;
  point map_debug_br;
  bool  map_debug_valid {};

  //
  // We regenerate this map every player move, and indicates the shortest path to the player. Used for sound effects
  // and lighting checks.
  //
  Dmap dmap_to_player;

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  /////////////////////////////////////////////////////////////////////////

  Level(biome_t);
  ~Level(void);

  void remove_thing(int x, int y, ThingId id);
  void remove_thing(point p, ThingId id);
  void put_thing(int x, int y, ThingId id);
  void put_thing(point p, ThingId id);
  void check_thing(Thingp t);

#define JOIN1(X, Y) X##Y
#define JOIN(X, Y)  JOIN1(X, Y)

#define FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)                                                                   \
  if (! (level)->is_oob(x, y)) {                                                                                     \
    static Thingp things_to_walk[ MAP_SLOTS ];                                                                       \
    {                                                                                                                \
      auto _vec_               = getptr(level->all_things_ptr_at, x, y);                                             \
      auto things_to_walk_size = _vec_->size();                                                                      \
      for (size_t idx = 0; idx < things_to_walk_size; idx++)                                                         \
        things_to_walk[ idx ] = (*_vec_)[ idx ];                                                                     \
      for (size_t idx = 0; idx < things_to_walk_size; idx++) {                                                       \
        Thingp t;                                                                                                    \
        t = things_to_walk[ idx ];                                                                                   \
  /* verify(MTYPE_THING, t); */

#define FOR_ALL_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                 \
  if (! (level)->is_oob(x, y)) {                                                                                     \
    {                                                                                                                \
      for (auto t : level->all_things_ptr_at[ x ][ y ]) {

#define FOR_ALL_THINGS(level, t, x, y) FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)

#define FOR_ALL_THINGS(level, t, x, y) FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)

#define FOR_ALL_THINGS_END()                                                                                         \
  }                                                                                                                  \
  }                                                                                                                  \
  }

//
// Things that can move or fall or catch fire etc...
//
#define FOR_ALL_INTERESTING_THINGS_ON_LEVEL(level, t)                                                                \
  {                                                                                                                  \
    level->interesting_things_walk_in_progress = true;                                                               \
    auto c                                     = level->interesting_things;                                          \
    auto i                                     = level->interesting_things.begin();                                  \
    while (i != level->interesting_things.end()) {                                                                   \
      auto t = i->second;                                                                                            \
      /* LOG("ID %08x -> %p", i->first.id, t); */                                                                    \
      i++;                                                                                                           \
      if (t->is_hidden) {                                                                                            \
        t->tick_last_did_something_set(game->tick_current);                                                          \
        continue;                                                                                                    \
      }                                                                                                              \
                                                                                                                     \
    /* verify(MTYPE_THING, t); */

#define FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(level)                                                               \
  if (i == level->interesting_things.end()) {                                                                        \
    break;                                                                                                           \
  }                                                                                                                  \
  }                                                                                                                  \
  level->interesting_things_walk_in_progress = false;                                                                \
  level->handle_all_pending_things();                                                                                \
  }

//
// Things that can move or fall or catch fire etc...
//
#define FOR_ALL_TICKABLE_THINGS_ON_LEVEL(level, t)                                                                   \
  {                                                                                                                  \
    level->tickable_things_walk_in_progress = true;                                                                  \
    auto c                                  = level->tickable_things;                                                \
    auto i                                  = level->tickable_things.begin();                                        \
    while (i != level->tickable_things.end()) {                                                                      \
      auto t = i->second;                                                                                            \
      /* LOG("ID %08x -> %p", i->first.id, t); */                                                                    \
      i++;                                                                                                           \
    /* verify(MTYPE_THING, t); */

#define FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(level)                                                                  \
  if (i == level->tickable_things.end()) {                                                                           \
    break;                                                                                                           \
  }                                                                                                                  \
  }                                                                                                                  \
  level->tickable_things_walk_in_progress = false;                                                                   \
  level->handle_all_pending_things();                                                                                \
  }

//
// Things that can move or fall or catch fire etc...
//
#define FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL(level, t)                                                                \
  {                                                                                                                  \
    level->describable_things_walk_in_progress = true;                                                               \
    auto c                                     = level->describable_things;                                          \
    auto i                                     = level->describable_things.begin();                                  \
    while (i != level->describable_things.end()) {                                                                   \
      auto t = i->second;                                                                                            \
      /* LOG("ID %08x -> %p", i->first.id, t); */                                                                    \
      i++;                                                                                                           \
    /* verify(MTYPE_THING, t); */

#define FOR_ALL_DESCRIBABLE_THINGS_ON_LEVEL_END(level)                                                               \
  if (i == level->describable_things.end()) {                                                                        \
    break;                                                                                                           \
  }                                                                                                                  \
  }                                                                                                                  \
  level->describable_things_walk_in_progress = false;                                                                \
  level->handle_all_pending_things();                                                                                \
  }

#define FOR_ALL_ANIMATED_THINGS_LEVEL(level, t)                                                                      \
  {                                                                                                                  \
    level->animated_things_walk_in_progress = true;                                                                  \
    auto c                                  = level->animated_things;                                                \
    auto i                                  = level->animated_things.begin();                                        \
    while (i != level->animated_things.end()) {                                                                      \
      auto t = i->second;                                                                                            \
      i++;                                                                                                           \
    /* verify(MTYPE_THING, t); */

#define FOR_ALL_ANIMATED_THINGS_LEVEL_END(level)                                                                     \
  if (i == level->animated_things.end()) {                                                                           \
    break;                                                                                                           \
  }                                                                                                                  \
  }                                                                                                                  \
  level->animated_things_walk_in_progress = false;                                                                   \
  }

#define FOR_ALL_NON_INTERNAL_THINGS(level, t, x, y)                                                                  \
  FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)                                                                         \
  if (t->is_internal()) {                                                                                            \
    continue;                                                                                                        \
  }

#define FOR_ALL_GRID_THINGS(level, t, x, y)                                                                          \
  FOR_ALL_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (! t->is_the_grid) {                                                                                            \
    continue;                                                                                                        \
  }

#define FOR_ALL_THINGS_AT_DEPTH_UNSAFE(level, t, x, y, z)                                                            \
  FOR_ALL_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (t->z_depth != z) {                                                                                             \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }

#define FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z)                                                                   \
  FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)                                                                         \
  if (t->z_depth != z) {                                                                                             \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }

#define FOR_ALL_LIGHTS_AT(level, t, x, y)                                                                            \
  FOR_ALL_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (likely(! t->has_light)) {                                                                                      \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }

//
// Things that move around
//
#define FOR_ALL_THINGS_THAT_DO_STUFF(level, t, x, y)                                                                 \
  FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)                                                                         \
  if (t->is_internal()) {                                                                                            \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_floor() || t->is_corridor()) {                                                                           \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (! t->is_tickable()) {                                                                                          \
    continue;                                                                                                        \
  }

//
// Things that move around and things that do not, but are interesting
// like food or walls that can be destroyed
//
#define FOR_ALL_THINGS_THAT_INTERACT(level, t, x, y)                                                                 \
  FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)                                                                         \
  if (t->is_internal()) {                                                                                            \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_floor() || t->is_corridor()) {                                                                           \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (! t->is_interesting()) {                                                                                       \
    continue;                                                                                                        \
  }

#define FOR_ALL_THINGS_THAT_INTERACT_UNSAFE(level, t, x, y)                                                          \
  FOR_ALL_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (t->is_internal()) {                                                                                            \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_floor() || t->is_corridor()) {                                                                           \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (! t->is_interesting()) {                                                                                       \
    continue;                                                                                                        \
  }

//
// Things you can bump into
//
#define FOR_ALL_COLLISION_THINGS(level, t, x, y)                                                                     \
  FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)                                                                         \
  if (t->is_internal()) {                                                                                            \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_floor() || t->is_corridor()) {                                                                           \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_interesting() || t->is_attackable_by_monst() || t->is_attackable_by_player() || t->is_obs_for_ai()) {    \
  } else {                                                                                                           \
    continue;                                                                                                        \
  }

#define FOR_ALL_MONSTS(level, t, x, y)                                                                               \
  FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)                                                                         \
  if (! t->is_monst()) {                                                                                             \
    continue;                                                                                                        \
  }

//
// Cursor path is the highlighted path the player follows.
//
#define FOR_ALL_CURSOR_PATH_THINGS(level, t, x, y)                                                                   \
  FOR_ALL_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (! t->is_cursor_path()) {                                                                                       \
    continue;                                                                                                        \
  }

#define FOR_ALL_DEBUG_PATH_THINGS(level, t, x, y)                                                                    \
  FOR_ALL_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (! t->is_debug_path()) {                                                                                        \
    continue;                                                                                                        \
  }

  Thingp buffbox_describe(const int slot);
  Thingp buffbox_get(const int slot);
  Thingp debuffbox_describe(const int slot);
  Thingp debuffbox_get(const int slot);
  Thingp inventory_describe(const int slot);
  Thingp inventory_get(const int slot);
  Thingp inventory_get(void);
  Thingp skillbox_describe(const int slot);
  Thingp skillbox_get(const int slot);
  Thingp skillbox_get(void);
  Thingp thing_find(const ThingId id);
  Thingp thing_find_optional(const ThingId id);
  Thingp thing_new(Tpp, const point at, Thingp owner = nullptr);
  Thingp thing_new(const std::string &tp_name, Thingp owner = nullptr);
  Thingp thing_new(const std::string &tp_name, const point at, Thingp owner = nullptr);
  Thingp thing_find_portal_at(point at);

  Tpp tp_random_mob(const point p);
  Tpp tp_random_mob_challenge_class_A(const point p);
  Tpp tp_random_mob_challenge_class_B(const point p);
  Tpp tp_random_treasure_class_A(const point p);
  Tpp tp_random_treasure_class_C(const point p);
  Tpp tp_random_treasure_class_B(const point p);
  Tpp tp_random_weapon_class_A(const point p);
  Tpp tp_random_weapon_class_C(const point p);
  Tpp tp_random_weapon_class_B(const point p);

  Tpp get_biome_dungeon_random_monst(Dungeonp d, point p, monst_environ_t);
  Tpp get_biome_swamp_random_monst(Dungeonp d, point p, monst_environ_t);
  Tpp get_biome_sewer_random_monst(point p, monst_environ_t);
  Tpp get_random_monst(point p, monst_environ_t, monst_class_t, int difficulty_offset);
  Tpp get_random_monst(point p, monst_environ_t, int difficulty_offset);

  // begin sort marker2 {
  bool buffbox_over(const int slot);
  bool can_see_obstacle(int x, int y);
  bool can_see_point_or_nearby(point, int dist);
  bool can_see_unimpeded(const point &start, const point &end);
  bool can_see_unimpeded(int x0, int y0, int x1, int y1);
  bool create_biome_dungeon(point3d at, uint32_t seed);
  bool create_biome_sewer_pipes(point3d at);
  bool create_biome_sewer(point3d at, uint32_t seed);
  bool create_biome_sewer_pools(void);
  bool create_biome_swamp(point3d at, uint32_t seed);
  bool create_wandering_monster(void);
  bool cursor_path_draw_line(Thingp, const std::vector< point > &move_path);
  bool cursor_path_draw_line(Thingp, point start, point end);
  bool debuffbox_over(const int slot);
  bool inventory_assign(const int slot, Thingp);
  bool inventory_chosen(const int slot);
  bool inventory_over(const int slot);
  bool is_gas_blocker(const int x, const int y) const;
  bool is_gas_blocker(const point p) const;
  bool is_gas_blocker_no_check(const int x, const int y) const;
  bool is_gas_blocker_no_check(const point p) const;
  bool is_light_blocker(const int x, const int y) const;
  bool is_light_blocker(const point p) const;
  bool is_light_blocker_for_monst(const int x, const int y) const;
  bool is_light_blocker_for_monst(const point p) const;
  bool is_light_blocker_for_monst_no_check(const int x, const int y) const;
  bool is_light_blocker_for_monst_no_check(const point p) const;
  bool is_light_blocker_no_check(const int x, const int y) const;
  bool is_light_blocker_no_check(const point p) const;
  bool is_obs_destructable(const int x, const int y) const;
  bool is_obs_destructable(const point p) const;
  bool is_obs_destructable_no_check(const int x, const int y) const;
  bool is_obs_destructable_no_check(const point p) const;
  bool is_obs_for_jump_landing(const int x, const int y) const;
  bool is_obs_for_jump_landing(const point p) const;
  bool is_obs_for_jump_landing_no_check(const int x, const int y) const;
  bool is_obs_for_jump_landing_no_check(const point p) const;
  bool is_obs_wall_or_door(const int x, const int y) const;
  bool is_obs_wall_or_door(const point p) const;
  bool is_obs_wall_or_door_no_check(const int x, const int y) const;
  bool is_obs_wall_or_door_no_check(const point p) const;
  bool is_obs_when_dead(const int x, const int y) const;
  bool is_obs_when_dead(const point p) const;
  bool is_obs_when_dead_no_check(const int x, const int y) const;
  bool is_obs_when_dead_no_check(const point p) const;
  bool is_oob(const fpoint p) const;
  bool is_oob(const int x, const int y) const;
  bool is_oob(const int x, const int y, const int z) const;
  bool is_oob(const point p) const;
  bool is_walked(const int x, const int y) const;
  bool is_walked(const point p) const;
  bool is_walked_no_check(const int x, const int y) const;
  bool is_walked_no_check(const point p) const;
  bool noise_blocker(const int x, const int y) const;
  bool noise_blocker(const point p) const;
  bool noise_blocker_no_check(const int x, const int y) const;
  bool noise_blocker_no_check(const point p) const;
  bool screen_shake_begin(void);
  bool should_display_map(void);
  bool skillbox_chosen(const int slot);
  bool skillbox_over(const int slot);
  bool update_map_mini_should_show_monst(int x, int y);
  // end sort marker2 }

  int total_monst_hp_level(void);
  int total_monst_dmg_level(void);
  int total_loot_level(void);
  int total_food_level(void);

  float wobble_curr(void) const;
  float update_wobble(void);

  int inventory_slot(Thingp item);

  std::string to_string(void);

  uint32_t num(void);

  // begin sort marker3 {
  uint8_t fade_in_map(const int x, const int y);
  uint8_t fade_in_map(const point p);
  uint8_t fade_in_map_no_check(const int x, const int y);
  uint8_t fade_in_map_no_check(const point p);
  uint8_t gfx_water(const int x, const int y);
  uint8_t gfx_water(const point p);
  uint8_t heatmap(const int x, const int y);
  uint8_t heatmap(const point p);
  uint8_t heatmap_no_check(const int x, const int y);
  uint8_t heatmap_no_check(const point p);
  uint8_t is_able_to_amplify_footsteps(const int x, const int y);
  uint8_t is_able_to_amplify_footsteps(const point p);
  uint8_t is_able_to_dampen_footsteps(const int x, const int y);
  uint8_t is_able_to_dampen_footsteps(const point p);
  uint8_t is_able_to_stand_on(const int x, const int y);
  uint8_t is_able_to_stand_on(const point p);
  uint8_t is_acid(const int x, const int y);
  uint8_t is_acid(const point p);
  uint8_t is_ascend_dungeon(const int x, const int y);
  uint8_t is_ascend_dungeon(const point p);
  uint8_t is_ascend_sewer(const int x, const int y);
  uint8_t is_ascend_sewer(const point p);
  uint8_t is_attackable_by_monst(const int x, const int y);
  uint8_t is_attackable_by_monst(const point p);
  uint8_t is_attackable_by_player(const int x, const int y);
  uint8_t is_attackable_by_player(const point p);
  uint8_t is_barrel(const int x, const int y);
  uint8_t is_barrel(const point p);
  uint8_t is_blocker(const int x, const int y);
  uint8_t is_blocker(const point p);
  uint8_t is_block_of_ice(const int x, const int y);
  uint8_t is_block_of_ice(const point p);
  uint8_t is_brazier(const int x, const int y);
  uint8_t is_brazier(const point p);
  uint8_t is_brazier_no_check(const int x, const int y);
  uint8_t is_bridge(const int x, const int y);
  uint8_t is_bridge(const point p);
  uint8_t is_burnable(const int x, const int y);
  uint8_t is_burnable(const point p);
  uint8_t is_carnivorous_plant(const int x, const int y);
  uint8_t is_carnivorous_plant(const point p);
  uint8_t is_chasm(const int x, const int y);
  uint8_t is_chasm(const point p);
  uint8_t is_cold(const int x, const int y);
  uint8_t is_cold(const point p);
  uint8_t is_combustible(const int x, const int y);
  uint8_t is_combustible(const point p);
  uint8_t is_corpse(const int x, const int y);
  uint8_t is_corpse(const point p);
  uint8_t is_corridor(const int x, const int y);
  uint8_t is_corridor(const point p);
  uint8_t is_currently_pixelart_raycast_lit(const int x, const int y);
  uint8_t is_currently_pixelart_raycast_lit(const point p);
  uint8_t is_currently_pixelart_raycast_lit_no_check(const int x, const int y);
  uint8_t is_currently_pixelart_raycast_lit_no_check(const point p);
  uint8_t is_cursor_path_blocker(Thingp, const int x, const int y);
  uint8_t is_cursor_path_blocker(Thingp, const point p);
  uint8_t is_cursor_path_hazard(const int x, const int y);
  uint8_t is_cursor_path_hazard(const point p);
  uint8_t is_deep_water(const int x, const int y);
  uint8_t is_deep_water(const point p);
  uint8_t is_descend_dungeon(const int x, const int y);
  uint8_t is_descend_dungeon(const point p);
  uint8_t is_descend_sewer(const int x, const int y);
  uint8_t is_descend_sewer(const point p);
  uint8_t is_dirt(const int x, const int y);
  uint8_t is_dirt(const point p);
  uint8_t is_door(const int x, const int y);
  uint8_t is_door(const point p);
  uint8_t is_dry_grass(const int x, const int y);
  uint8_t is_dry_grass(const point p);
  uint8_t is_enchantstone(const int x, const int y);
  uint8_t is_enchantstone(const point p);
  uint8_t is_fire(const int x, const int y);
  uint8_t is_fire(const point p);
  uint8_t is_fire_no_check(const int x, const int y);
  uint8_t is_floor(const int x, const int y);
  uint8_t is_floor(const point p);
  uint8_t is_foliage(const int x, const int y);
  uint8_t is_foliage(const point p);
  uint8_t is_food(const int x, const int y);
  uint8_t is_food(const point p);
  uint8_t is_gas_poison(const int x, const int y) const;
  uint8_t is_gas_poison(const point p) const;
  uint8_t is_gas_poison_no_check(const int x, const int y) const;
  uint8_t is_gas_poison_no_check(const point p) const;
  uint8_t is_gold(const int x, const int y);
  uint8_t is_gold(const point p);
  uint8_t is_green_blood(const int x, const int y);
  uint8_t is_green_blood(const point p);
  uint8_t is_hazard(const int x, const int y);
  uint8_t is_hazard(const point p);
  uint8_t is_heavy(const int x, const int y);
  uint8_t is_heavy(const point p);
  uint8_t is_key(const int x, const int y);
  uint8_t is_key(const point p);
  uint8_t is_lit_recently_pixelart_raycast(const int x, const int y);
  uint8_t is_mob(const int x, const int y);
  uint8_t is_mob(const point p);
  uint8_t is_monst(const int x, const int y);
  uint8_t is_monst(const point p);
  uint8_t is_monst_or_player(const point p);
  uint8_t is_portal(const int x, const int y);
  uint8_t is_portal(const point p);
  uint8_t is_potion(const int x, const int y);
  uint8_t is_potion(const point p);
  uint8_t is_red_blood(const int x, const int y);
  uint8_t is_red_blood(const point p);
  uint8_t is_ring(const int x, const int y);
  uint8_t is_ring(const point p);
  uint8_t is_ripple(const int x, const int y);
  uint8_t is_ripple(const point p);
  uint8_t is_rock(const int x, const int y);
  uint8_t is_rock(const point p);
  uint8_t is_secret_door(const int x, const int y);
  uint8_t is_secret_door(const point p);
  uint8_t is_shallow_water(const int x, const int y);
  uint8_t is_shallow_water(const point p);
  uint8_t is_shovable(const int x, const int y);
  uint8_t is_shovable(const point p);
  uint8_t is_skillstone(const int x, const int y);
  uint8_t is_skillstone(const point p);
  uint8_t is_smoke(const int x, const int y);
  uint8_t is_smoke(const point p);
  uint8_t is_spiderweb(const int x, const int y);
  uint8_t is_spiderweb(const point p);
  uint8_t is_staff(const int x, const int y);
  uint8_t is_staff(const point p);
  uint8_t is_steam(const int x, const int y);
  uint8_t is_steam(const point p);
  uint8_t is_sticky(const int x, const int y);
  uint8_t is_sticky(const point p);
  uint8_t is_tentacle(const int x, const int y);
  uint8_t is_tentacle(const point p);
  uint8_t is_torch(const int x, const int y);
  uint8_t is_torch(const point p);
  uint8_t is_trap(const int x, const int y);
  uint8_t is_trap(const point p);
  uint8_t is_treasure_type(const int x, const int y);
  uint8_t is_treasure_type(const point p);
  uint8_t is_wall(const int x, const int y);
  uint8_t is_wall(const point p);
  uint8_t is_water(const int x, const int y);
  uint8_t is_water(const point p);
  uint8_t is_weapon_class_A(const int x, const int y);
  uint8_t is_weapon_class_A(const point p);
  uint8_t is_weapon_class_B(const int x, const int y);
  uint8_t is_weapon_class_B(const point p);
  uint8_t is_weapon_class_C(const int x, const int y);
  uint8_t is_weapon_class_C(const point p);
  uint8_t is_weapon_type(const int x, const int y);
  uint8_t is_weapon_type(const point p);
  uint8_t is_wet_grass(const int x, const int y);
  uint8_t is_wet_grass(const point p);
  uint8_t noisemap(const int x, const int y);
  uint8_t noisemap(const point p);
  uint8_t noisemap_in(const int x, const int y);
  uint8_t noisemap_in(const point p);
  uint8_t noisemap_in_no_check(const int x, const int y);
  uint8_t noisemap_in_no_check(const point p);
  uint8_t noisemap_no_check(const int x, const int y);
  uint8_t noisemap_no_check(const point p);
  // end sort marker3 }

  // begin sort marker4 {
  void assign_leaders_and_followers(void);
  void chances_of_creating_set(void);
  void clear(void);
  void con(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void con_(const char *fmt, va_list args); // compile error without
  void create_biome_dungeon_place_braziers(Dungeonp d, const std::string &what);
  void create_biome_dungeon_place_bridge(Dungeonp d);
  void create_biome_dungeon_place_chasm(Dungeonp d, const std::string &what);
  void create_biome_dungeon_place_corridor(Dungeonp d, const std::string what, int depth);
  void create_biome_dungeon_place_deep_water(Dungeonp d, const std::string &what);
  void create_biome_dungeon_place_floors(Dungeonp d, const std::string, int depth, int var, int w, int h, int tries);
  void create_biome_dungeon_place_lava(Dungeonp d, const std::string &what);
  void create_biome_dungeon_place_lava_smoke(Dungeonp d);
  void create_biome_dungeon_place_place_shallow_water(Dungeonp d, const std::string &what);
  void create_biome_dungeon_place_random_floor_deco(Dungeonp d);
  void create_biome_dungeon_place_random_red_blood(Dungeonp d);
  void create_biome_dungeon_place_remaining_floor(Dungeonp d, const std::string &what);
  void create_biome_dungeon_place_remaining_rocks(Dungeonp d, const std::string &what);
  void create_biome_dungeon_place_remaining_walls(Dungeonp d, const std::string &what);
  void create_biome_dungeon_place_rocks(Dungeonp d, int variant, int block_width, int block_height, int tries);
  void create_biome_dungeon_place_sewer_pipes(Dungeonp d);
  void create_biome_dungeon_place_walls(Dungeonp d, Tpp tp, int, int block_width, int block_height, int tries);
  void create_biome_sewer_place_remaining_walls(const std::string &what);
  void create_biome_sewer_place_walls(int variant, int block_width, int block_height, int tries);
  void create_biome_swamp_place_deep_water(Dungeonp d, const std::string &what);
  void create_biome_swamp_place_floors(Dungeonp d, const std::string, int depth, int var, int w, int h, int tries);
  void create_biome_swamp_place_place_shallow_water(Dungeonp d, const std::string &what);
  void create_biome_swamp_place_remaining_floor(Dungeonp d, const std::string &what);
  void create_biome_swamp_place_remaining_rocks(Dungeonp d, const std::string &what);
  void create_biome_swamp_place_rocks(Dungeonp d, int variant, int block_width, int block_height, int tries);
  void created(void);
  void create(point3d world_at, point grid_at, uint32_t seed, int difficulty_depth, int dungeon_walk_order_level_no);
  void cursor_describe(void);
  void cursor_find_on_visible_things(const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
  void cursor_move(void);
  void cursor_path_clear(void);
  void cursor_path_create(Thingp);
  void cursor_path_create(Thingp, const std::vector< point > &move_path);
  void cursor_path_draw_circle(void);
  void cursor_path_draw_straight_line(Thingp, point start, point end);
  void cursor_path_draw(Thingp);
  void cursor_path_draw(Thingp, const std::vector< point > &move_path);
  void cursor_path_draw(Thingp, point start, point end);
  void cursor_recreate(point curr_at = point(-1, -1));
  void cursor_warp_check(void);
  void debug_path_clear(void);
  void debug_path_create(const std::vector< point > &move_path);
  void debug_path_draw(const std::vector< point > &move_path);
  void debug_path_draw_line(const std::vector< point > &move_path);
  void describe(point at);
  void describe(Thingp);
  void display_ascii_beast_map(point tl, point br);
  void display_ascii_gas(point tl, point br, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_ascii_lasers(point tl, point br);
  void display_ascii_map(point tl, point br);
  void display_ascii_projectiles(point tl, point br);
  void display_ascii_treasure_map(point tl, point br);
  void display_lasers(point tl, point br);
  void display_map_set_bounds(void);
  void display_map(void);
  void display_pixelart_basalt(const int fbo, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_pixelart_blood(void);
  void display_pixelart_deep_water(const int fbo, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_pixelart_external_particles(void);
  void display_pixelart_fade_in(void);
  void display_pixelart_fade_out(void);
  void display_pixelart_gas(const int fbo, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_pixelart_internal_particles(void);
  void display_pixelart_lasers(point tl, point br);
  void display_pixelart_lava(const int fbo, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_pixelart_map_all(void);
  void display_pixelart_map_bg_things(void);
  void display_pixelart_map_debug(int x, int y);
  void display_pixelart_map_debug(int x, int y, int tlx, int tly, int brx, int bly);
  void display_pixelart_map_fg2_things(const int fbo, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_pixelart_map_fg_things(const int fbo, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_pixelart_map_mini(void);
  void display_pixelart_map_things(const int, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_pixelart_map(void);
  void display_pixelart_projectiles(point tl, point br);
  void display_pixelart_water(const int fbo, const int16_t, const int16_t, const int16_t, const int16_t);
  void display_projectiles(point tl, point br);
  void display_target(void);
  void display_tick_animation(void);
  void dmap_to_player_update(void);
  void err(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void err_(const char *fmt, va_list args); // compile error without
  void fade_in_incr(const int x, const int y);
  void fade_in_no_check_incr(const int x, const int y);
  void fade_in_no_check_unset(const int x, const int y);
  void fade_in_unset(const int x, const int y);
  void fini(void);
  void gfx_water_set(const int x, const int y);
  void gfx_water_unset(const int x, const int y);
  void handle_all_pending_things(void);
  void handle_external_particles(void);
  void handle_input_events(void);
  void handle_internal_particles(void);
  void heatmap_incr(const int x, const int y);
  void heatmap_no_check_incr(const int x, const int y);
  void heatmap_no_check_incr(const int x, const int y, int dv);
  void heatmap_no_check_unset(const int x, const int y);
  void heatmap_print(point at, point tl, point br);
  void heatmap_unset(const int x, const int y);
  void inventory_dump(void);
  void is_able_to_amplify_footsteps_set(const int x, const int y);
  void is_able_to_amplify_footsteps_unset(const int x, const int y);
  void is_able_to_dampen_footsteps_set(const int x, const int y);
  void is_able_to_dampen_footsteps_unset(const int x, const int y);
  void is_able_to_stand_on_set(const int x, const int y);
  void is_able_to_stand_on_unset(const int x, const int y);
  void is_acid_set(const int x, const int y);
  void is_acid_unset(const int x, const int y);
  void is_ascend_dungeon_set(const int x, const int y);
  void is_ascend_dungeon_unset(const int x, const int y);
  void is_ascend_sewer_set(const int x, const int y);
  void is_ascend_sewer_unset(const int x, const int y);
  void is_attackable_by_monst_set(const int x, const int y);
  void is_attackable_by_monst_unset(const int x, const int y);
  void is_attackable_by_player_set(const int x, const int y);
  void is_attackable_by_player_unset(const int x, const int y);
  void is_barrel_set(const int x, const int y);
  void is_barrel_unset(const int x, const int y);
  void is_blocker_set(const int x, const int y);
  void is_blocker_unset(const int x, const int y);
  void is_block_of_ice_set(const int x, const int y);
  void is_block_of_ice_unset(const int x, const int y);
  void is_brazier_set(const int x, const int y);
  void is_brazier_unset(const int x, const int y);
  void is_bridge_set(const int x, const int y);
  void is_bridge_unset(const int x, const int y);
  void is_burnable_set(const int x, const int y);
  void is_burnable_unset(const int x, const int y);
  void is_carnivorous_plant_set(const int x, const int y);
  void is_carnivorous_plant_unset(const int x, const int y);
  void is_chasm_set(const int x, const int y);
  void is_chasm_unset(const int x, const int y);
  void is_cold_set(const int x, const int y);
  void is_cold_unset(const int x, const int y);
  void is_combustible_set(const int x, const int y);
  void is_combustible_unset(const int x, const int y);
  void is_corpse_set(const int x, const int y);
  void is_corpse_unset(const int x, const int y);
  void is_corridor_set(const int x, const int y);
  void is_corridor_unset(const int x, const int y);
  void is_currently_pixelart_raycast_lit_no_check_set(const int x, const int y);
  void is_currently_pixelart_raycast_lit_no_check_set(const int x, const int y, uint8_t v);
  void is_currently_pixelart_raycast_lit_no_check_unset(const int x, const int y);
  void is_currently_pixelart_raycast_lit_set(const int x, const int y);
  void is_currently_pixelart_raycast_lit_unset(const int x, const int y);
  void is_cursor_path_blocker_set(const int x, const int y);
  void is_cursor_path_blocker_unset(const int x, const int y);
  void is_cursor_path_hazard_set(const int x, const int y);
  void is_cursor_path_hazard_unset(const int x, const int y);
  void is_deep_water_set(const int x, const int y);
  void is_deep_water_unset(const int x, const int y);
  void is_descend_dungeon_set(const int x, const int y);
  void is_descend_dungeon_unset(const int x, const int y);
  void is_descend_sewer_set(const int x, const int y);
  void is_descend_sewer_unset(const int x, const int y);
  void is_dirt_set(const int x, const int y);
  void is_dirt_unset(const int x, const int y);
  void is_door_set(const int x, const int y);
  void is_door_unset(const int x, const int y);
  void is_dry_grass_set(const int x, const int y);
  void is_dry_grass_unset(const int x, const int y);
  void is_enchantstone_set(const int x, const int y);
  void is_enchantstone_unset(const int x, const int y);
  void is_fire_set(const int x, const int y);
  void is_fire_unset(const int x, const int y);
  void is_floor_set(const int x, const int y);
  void is_floor_unset(const int x, const int y);
  void is_foliage_set(const int x, const int y);
  void is_foliage_unset(const int x, const int y);
  void is_food_set(const int x, const int y);
  void is_food_unset(const int x, const int y);
  void is_gas_blocker_no_check_set(const int x, const int y);
  void is_gas_blocker_no_check_unset(const int x, const int y);
  void is_gas_blocker_set(const int x, const int y);
  void is_gas_blocker_unset(const int x, const int y);
  void is_gas_poison_no_check_set(const int x, const int y, uint8_t val);
  void is_gas_poison_no_check_unset(const int x, const int y);
  void is_gas_poison_set(const int x, const int y, uint8_t val);
  void is_gas_poison_unset(const int x, const int y);
  void is_gold_set(const int x, const int y);
  void is_gold_unset(const int x, const int y);
  void is_green_blood_set(const int x, const int y);
  void is_green_blood_unset(const int x, const int y);
  void is_hazard_set(const int x, const int y);
  void is_hazard_unset(const int x, const int y);
  void is_heavy_set(const int x, const int y);
  void is_heavy_unset(const int x, const int y);
  void is_key_set(const int x, const int y);
  void is_key_unset(const int x, const int y);
  void is_light_blocker_for_monst_no_check_set(const int x, const int y);
  void is_light_blocker_for_monst_no_check_unset(const int x, const int y);
  void is_light_blocker_for_monst_set(const int x, const int y);
  void is_light_blocker_for_monst_unset(const int x, const int y);
  void is_light_blocker_no_check_set(const int x, const int y);
  void is_light_blocker_no_check_unset(const int x, const int y);
  void is_light_blocker_set(const int x, const int y);
  void is_light_blocker_unset(const int x, const int y);
  void is_lit_ever_no_check_set(const int x, const int y);
  void is_lit_ever_no_check_unset(const int x, const int y);
  void is_lit_ever_set(const int x, const int y);
  void is_lit_ever_unset(const int x, const int y);
  void is_mob_set(const int x, const int y);
  void is_mob_unset(const int x, const int y);
  void is_monst_set(const int x, const int y);
  void is_monst_unset(const int x, const int y);
  void is_obs_destructable_no_check_set(const int x, const int y);
  void is_obs_destructable_no_check_unset(const int x, const int y);
  void is_obs_destructable_set(const int x, const int y);
  void is_obs_destructable_unset(const int x, const int y);
  void is_obs_for_jump_landing_no_check_set(const int x, const int y);
  void is_obs_for_jump_landing_no_check_unset(const int x, const int y);
  void is_obs_for_jump_landing_set(const int x, const int y);
  void is_obs_for_jump_landing_unset(const int x, const int y);
  void is_obs_wall_or_door_no_check_set(const int x, const int y);
  void is_obs_wall_or_door_no_check_unset(const int x, const int y);
  void is_obs_wall_or_door_set(const int x, const int y);
  void is_obs_wall_or_door_unset(const int x, const int y);
  void is_obs_when_dead_no_check_set(const int x, const int y);
  void is_obs_when_dead_no_check_unset(const int x, const int y);
  void is_obs_when_dead_set(const int x, const int y);
  void is_obs_when_dead_unset(const int x, const int y);
  void is_portal_set(const int x, const int y);
  void is_portal_unset(const int x, const int y);
  void is_potion_set(const int x, const int y);
  void is_potion_unset(const int x, const int y);
  void is_red_blood_set(const int x, const int y);
  void is_red_blood_unset(const int x, const int y);
  void is_ring_set(const int x, const int y);
  void is_ring_unset(const int x, const int y);
  void is_ripple_set(const int x, const int y);
  void is_ripple_unset(const int x, const int y);
  void is_rock_set(const int x, const int y);
  void is_rock_unset(const int x, const int y);
  void is_secret_door_set(const int x, const int y);
  void is_secret_door_unset(const int x, const int y);
  void is_shallow_water_set(const int x, const int y);
  void is_shallow_water_unset(const int x, const int y);
  void is_shovable_set(const int x, const int y);
  void is_shovable_unset(const int x, const int y);
  void is_skillstone_set(const int x, const int y);
  void is_skillstone_unset(const int x, const int y);
  void is_smoke_set(const int x, const int y);
  void is_smoke_unset(const int x, const int y);
  void is_spiderweb_set(const int x, const int y);
  void is_spiderweb_unset(const int x, const int y);
  void is_staff_set(const int x, const int y);
  void is_staff_unset(const int x, const int y);
  void is_steam_set(const int x, const int y);
  void is_steam_unset(const int x, const int y);
  void is_sticky_set(const int x, const int y);
  void is_sticky_unset(const int x, const int y);
  void is_tentacle_set(const int x, const int y);
  void is_tentacle_unset(const int x, const int y);
  void is_torch_set(const int x, const int y);
  void is_torch_unset(const int x, const int y);
  void is_trap_set(const int x, const int y);
  void is_trap_unset(const int x, const int y);
  void is_treasure_type_set(const int x, const int y);
  void is_treasure_type_unset(const int x, const int y);
  void is_walked_no_check_set(const int x, const int y);
  void is_walked_no_check_unset(const int x, const int y);
  void is_walked_set(const int x, const int y);
  void is_walked_unset(const int x, const int y);
  void is_wall_set(const int x, const int y);
  void is_wall_unset(const int x, const int y);
  void is_wet_grass_set(const int x, const int y);
  void is_wet_grass_unset(const int x, const int y);
  void lights_fade(void);
  void lights_render(int minx, int miny, int maxx, int maxy, int fbo);
  void lights_render_small_lights(int minx, int miny, int maxx, int maxy, int fbo, bool include_player_lights);
  void lights_update_new_level(void);
  void lights_update_same_level(void);
  void log(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void log_(const char *fmt, va_list args); // compile error without
  void l_shaped_path_to_diag(std::vector< point > &path);
  void new_external_particle(ThingId, point, point, isize, uint32_t dur, Tilep, bool, MyCallback = NoCallback);
  void new_internal_particle(ThingId, point, point, isize, uint32_t dur, Tilep, bool, MyCallback = NoCallback);
  void new_laser(ThingId id, ThingId victim_id, LaserInfo, uint32_t dur);
  void new_projectile(ThingId id, ThingId victim_id, ProjectileInfo, uint32_t dur);
  void noise_blocker_no_check_set(const int x, const int y);
  void noise_blocker_no_check_unset(const int x, const int y);
  void noise_blocker_set(const int x, const int y);
  void noise_blocker_unset(const int x, const int y);
  void noisemap_incr(const int x, const int y);
  void noisemap_in_incr(const int x, const int y);
  void noisemap_in_incr(const int x, const int y, int dv);
  void noisemap_in_no_check_incr(const int x, const int y);
  void noisemap_in_no_check_incr(const int x, const int y, int dv);
  void noisemap_in_no_check_set(const int x, const int y, uint8_t v);
  void noisemap_in_no_check_unset(const int x, const int y);
  void noisemap_in_set(const int x, const int y, uint8_t v);
  void noisemap_in_unset(const int x, const int y);
  void noisemap_no_check_incr(const int x, const int y);
  void noisemap_no_check_incr(const int x, const int y, int dv);
  void noisemap_no_check_set(const int x, const int y, uint8_t v);
  void noisemap_no_check_unset(const int x, const int y);
  void noisemap_print(void);
  void noisemap_set(const int x, const int y, uint8_t v);
  void noisemap_unset(const int x, const int y);
  void place_dirt(Dungeonp d);
  void place_dry_grass(Dungeonp d);
  void place_floor_deco(Dungeonp d);
  void place_foliage(Dungeonp d);
  void place_objects_with_normal_placement_rules(Dungeonp d);
  void place_portals(Dungeonp d);
  void place_random_torches(Dungeonp d);
  void place_random_treasure(Dungeonp d);
  void place_random_water_monsters(void);
  void place_spiderweb(Dungeonp d);
  void place_swimming_monsters(void);
  void place_the_grid(void);
  void place_wet_grass(Dungeonp d);
  void poison_gas_explosion(point at);
  void screen_shake_end(void);
  void scroll_map_do(bool fast);
  void scroll_map_set_bounds(void);
  void scroll_map_set_target(void);
  void scroll_map_to_player_immediately(void);
  void scroll_map_to_player(void);
  void scroll_map(void);
  void things_gc(bool force);
  void things_gc_force(void);
  void things_gc_if_possible(void);
  void things_tick(void);
  void tick_begin_now(void);
  void tick_gas_poison(void);
  void tick(void);
  void tick_(void);
  void tiles_get(void);
  void update_all_ticks(void);
  void update_deep_water(void);
  void update_hazard_tile_map(void);
  void update_heatmap(void);
  void update_light_ascii_map(void);
  void update_map_debug(int x, int y);
  void update_map_mini(bool showing_two_levels, bool show_faded);
  void update_map_things_to_stand_on(void);
  void update_map(void);
  void update_new_level(void);
  void update_noisemap(void);
  void update_same_level_immediately(void);
  void update_same_level(void);
  void update_things_next_to_a_chasm(void);
  void update(void);
  void update_water_next_to_lava(void);
  void wobble_set(float);
  // end sort marker4 }

  uint8_t is_lava(const int x, const int y);
  uint8_t is_lava(const point p);
  uint8_t is_lava_no_check(const int x, const int y);
  void    is_lava_set(const int x, const int y);
  void    is_lava_unset(const int x, const int y);

  uint8_t is_basalt(const int x, const int y);
  uint8_t is_basalt(const point p);
  uint8_t is_basalt_no_check(const int x, const int y);
  void    is_basalt_set(const int x, const int y);
  void    is_basalt_unset(const int x, const int y);

  fcolor ascii_light_source(const int x, const int y);
  fcolor ascii_light_source(const point p);
  fcolor ascii_light_source_no_check(const int x, const int y);
  fcolor ascii_light_source_no_check(const point p);
  void   ascii_light_source_set(const point p, fcolor &v);
  void   ascii_light_source_set(const int x, const int y, fcolor &v);
  void   ascii_light_source_set_no_check(const point p, fcolor &v);
  void   ascii_light_source_set_no_check(const int x, const int y, fcolor &v);
  void   ascii_light_source_unset(const point p);
  void   ascii_light_source_unset(const int x, const int y);
  void   ascii_light_source_unset_no_check(const point p);
  void   ascii_light_source_unset_no_check(const int x, const int y);

  std::deque< point >  flood_fill(point) const;
  std::deque< point >  flood_fill_points(point, std::function< int(Thingp) > filter);
  std::deque< Thingp > flood_fill_things(point, std::function< int(Thingp) > filter);
  std::deque< Thingp > flood_fill_grid_things(point, int distance);

  std::vector< point >  cursor_path_draw_line_attempt(Thingp, point start, point end, int);
  std::vector< Thingp > line(const point s, const point e, size_t max_elems = 0);
  void                  line_set_all_on_fire(const point s, const point e, size_t max_elems, const std::string &why);

  void scan(Thingp me, struct FovMap_ *fov_curr, struct FovMap_ *fov_ever, int pov_x, int pov_y,
            int   distance, // Polar distance from POV.
            float view_slope_high, float view_slope_low, int max_radius, int octant, bool light_walls);

  bool fov_calculate(Thingp me, struct FovMap_ *fov_curr, struct FovMap_ *fov_ever, int pov_x, int pov_y,
                     int max_radius, bool light_walls = true);
};

#endif
