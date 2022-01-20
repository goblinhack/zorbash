//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_LEVEL_HPP_
#define _MY_LEVEL_HPP_

#include <deque>
#include <functional>
#include <map>

#include "my_dmap.hpp"
#include "my_fwd.hpp"
#include "my_game_defs.hpp"
#include "my_laser.hpp"
#include "my_particle.hpp"
#include "my_point3d.hpp"
#include "my_projectile.hpp"
#include "my_time.hpp"

class Level
{
public:
  //
  // These are caches for fast lookup in display code
  //
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH >    _is_light_blocker {};
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH >    _is_lit_ever {};
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH >    _is_obs_wall_or_door {};
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH >    _is_obs_destructable {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _fade_in_map {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _gfx_water {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _heatmap {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_able_to_stand_on {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_acid {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_ascend_dungeon {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_ascend_sewer {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_barrel {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_blood {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_brazier {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_bridge {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_chasm {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_corpse {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_corridor {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_deep_water {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_descend_dungeon {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_descend_sewer {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_dirt {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_door {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_dry_grass {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_wet_grass {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_enchantstone {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_cursor_path_hazard_for_player {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_heavy {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_fire {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_floor {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_foilage {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_food {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_gold {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_hazard {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_key {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_lava {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_lit_currently {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_mob_spawner {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_monst {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_potion {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_ripple {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_rock {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_secret_door {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_shallow_water {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_skillstone {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_smoke {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_spiderweb {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_sticky {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_shovable {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_treasure_type {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_wall {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_wand {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > _is_ring {};
  //
  // Something moved
  //
  std::array< std::array< uint32_t, MAP_HEIGHT >, MAP_WIDTH > _is_map_changed {};

  //
  // For level transitions
  //
  std::vector< point3d > prev_levels;
  std::vector< point3d > next_levels;

  //
  // When this Level was made. Used to restore timestamps relative to this.
  //
  ts_t ts_created {};
  ts_t ts_saved {};
  ts_t ts_fade_out_begin {};
  ts_t ts_fade_in_begin {};

  uint32_t tick_created {};

  //
  // Where we are in the world
  //
  point3d world_at;

  //
  // Levels are group into difficulty levels
  //
  int difficulty_depth {};
  int dungeon_depth {};

  //
  // Chances for various things to appear
  //
  int d1000_chance_of_creating_monst_class_a {};
  int d1000_chance_of_creating_monst_class_b {};
  int d1000_chance_of_creating_monst_class_c {};
  int d1000_chance_of_creating_monst_class_d {};
  int d1000_chance_of_creating_monst_class_e {};
  int d1000_chance_of_creating_mob_spawner_class_a {};
  int d1000_chance_of_creating_mob_spawner_class_b {};
  int d1000_chance_of_creating_treasure_class_a {};
  int d1000_chance_of_creating_treasure_class_b {};
  int d1000_chance_of_creating_treasure_class_c {};
  int d1000_chance_of_creating_weapon_class_a {};
  int d1000_chance_of_creating_weapon_class_b {};
  int d1000_chance_of_creating_weapon_class_c {};

  //
  // Current on screen map limits in tile coords
  //
  int minx {};
  int maxx {};
  int miny {};
  int maxy {};

  bool cursor_found {};
  bool is_heatmap_valid {};
  bool is_starting {}; // Loading level
  bool map_changed {}; // Something moved on the map
  bool map_follow_player {};
  bool map_mini_valid {};
  bool is_level_type_sewer {};
  bool is_level_type_dungeon {};

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

#define MAX_THING_GROUPS              3
#define THING_GROUP_PRIO_HIGH         0
#define THING_GROUP_PRIO_NORMAL       1
#define THING_GROUP_TMP               2
#define FOR_ALL_THING_GROUPS(_group_) for (auto _group_ = 0; _group_ < MAX_THING_GROUPS; _group_++)

#define FOR_ALL_THING_PRIO_GROUPS                                                                                    \
  for (auto _group_ = THING_GROUP_PRIO_HIGH; _group_ <= THING_GROUP_PRIO_NORMAL; _group_++)

  //
  // Everything thing on the level. Not all in the game, just this level.
  //
  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_things {};

  //
  // For all things that move, like monsters, or those that do not, like
  // wands, and even those that do not move but can be destroyed, like
  // walls. Omits things like floors, corridors, the grid; those that
  // generally do nothing or are hidden.
  //
  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_things_of_interest {};

  //
  // These are used to add/remove to all_things_of_interest when walking
  // is done; aboids the map becoming invalidated due to changes.
  //
  bool all_things_of_interest_walk_in_progress {};

  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_things_of_interest_pending_add {};
  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_things_of_interest_pending_remove {};
  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_animated_things {};

  bool all_animated_things_walk_in_progress {};

  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_animated_things_pending_add {};
  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_animated_things_pending_remove {};

  //
  // This is for things that do not tick, like water; that need to fall
  //
  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_things_pending_fall {};

  //
  // All things that are to be destroyed
  //
  std::array< std::map< ThingId, Thingp >, MAX_THING_GROUPS > all_things_to_be_destroyed {};

  //
  // All thing IDs
  //
  std::array< std::array< std::array< std::array< ThingId, MAP_SLOTS >, MAP_HEIGHT >, MAP_WIDTH >, MAX_THING_GROUPS >
      all_things_id_at {};

  std::array< std::array< std::array< std::vector< Thingp >, MAP_HEIGHT >, MAP_WIDTH >, MAX_THING_GROUPS >
      all_things_ptr_at {};

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
  // Update thing_fini.cpp when adding more references to Thingp
  //
  Thingp player     = {};
  Thingp cursor     = {};
  Thingp highlight  = {};
  Thingp hover_over = {};

  //
  // Tile maps for rendering solid blocks of water etc...
  //
  std::array< std::array< uint8_t, MAP_HEIGHT + 8 >, MAP_WIDTH + 8 > water_tile_map      = {};
  std::array< std::array< uint8_t, MAP_HEIGHT + 8 >, MAP_WIDTH + 8 > deep_water_tile_map = {};
  std::array< std::array< uint8_t, MAP_HEIGHT + 8 >, MAP_WIDTH + 8 > lava_tile_map       = {};
  std::array< std::array< uint8_t, MAP_HEIGHT + 8 >, MAP_WIDTH + 8 > chasm_tile_map      = {};

  bool is_being_destroyed {};
  bool cursor_update_needed {};
  bool fade_out_finished {};
  bool request_dmap_to_player_update;

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
  // We regenerate this map every player move, and indicates the shortest
  // path to the player. Used for sound effects and lighting checks.
  //
  Dmap dmap_to_player;

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  /////////////////////////////////////////////////////////////////////////

  Level(void);
  ~Level(void);

  void remove_thing(int x, int y, ThingId id, int group);
  void remove_thing(point p, ThingId id, int group);
  void put_thing(int x, int y, ThingId id, int group);
  void put_thing(point p, ThingId id, int group);
  void check_thing(Thingp t);

#define JOIN1(X, Y) X##Y
#define JOIN(X, Y)  JOIN1(X, Y)

#define FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)                                                                   \
  if (! (level)->is_oob(x, y)) {                                                                                     \
    static Thingp things_to_walk[ MAP_SLOTS ];                                                                       \
    FOR_ALL_THING_PRIO_GROUPS                                                                                        \
    {                                                                                                                \
      auto _vec_               = getptr(level->all_things_ptr_at[ _group_ ], x, y);                                  \
      auto things_to_walk_size = _vec_->size();                                                                      \
      for (size_t idx = 0; idx < things_to_walk_size; idx++)                                                         \
        things_to_walk[ idx ] = (*_vec_)[ idx ];                                                                     \
      for (size_t idx = 0; idx < things_to_walk_size; idx++) {                                                       \
        Thingp t;                                                                                                    \
        t = things_to_walk[ idx ];                                                                                   \
        verify(MTYPE_THING, t);

#define FOR_ALL_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                 \
  if (! (level)->is_oob(x, y)) {                                                                                     \
    FOR_ALL_THING_PRIO_GROUPS                                                                                        \
    {                                                                                                                \
      for (auto t : getref(level->all_things_ptr_at[ _group_ ], x, y)) {

#define FOR_ALL_THINGS(level, t, x, y) FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)

#define FOR_TMP_THINGS_WALKER(level, t, x, y)                                                                        \
  if (! (level)->is_oob(x, y)) {                                                                                     \
    static Thingp things_to_walk[ MAP_SLOTS ];                                                                       \
    {                                                                                                                \
      auto _vec_               = getptr(level->all_things_ptr_at[ THING_GROUP_TMP ], x, y);                          \
      auto things_to_walk_size = _vec_->size();                                                                      \
      for (size_t idx = 0; idx < things_to_walk_size; idx++)                                                         \
        things_to_walk[ idx ] = (*_vec_)[ idx ];                                                                     \
      for (size_t idx = 0; idx < things_to_walk_size; idx++) {                                                       \
        Thingp t;                                                                                                    \
        t = things_to_walk[ idx ];                                                                                   \
        verify(MTYPE_THING, t);

#define FOR_TMP_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                 \
  if (! (level)->is_oob(x, y)) {                                                                                     \
    {                                                                                                                \
      for (auto t : getref(level->all_things_ptr_at[ THING_GROUP_TMP ], x, y)) {

#define FOR_ALL_THINGS(level, t, x, y) FOR_ALL_THINGS_SAFE_WALKER(level, t, x, y)

#define FOR_ALL_THINGS_END()                                                                                         \
  }                                                                                                                  \
  }                                                                                                                  \
  }

//
// Things that can move or fall or catch fire etc...
//
#define FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(level, t)                                                              \
  FOR_ALL_THING_PRIO_GROUPS                                                                                          \
  {                                                                                                                  \
    level->all_things_of_interest_walk_in_progress = true;                                                           \
    auto c                                         = level->all_things_of_interest[ _group_ ];                       \
    auto i                                         = level->all_things_of_interest[ _group_ ].begin();               \
    while (i != level->all_things_of_interest[ _group_ ].end()) {                                                    \
      auto t = i->second;                                                                                            \
      /* LOG("ID %08x -> %p", i->first.id, t); */                                                                    \
      i++;                                                                                                           \
      if (t->is_hidden) {                                                                                            \
        t->set_tick_last_did_something(game->tick_current);                                                          \
        continue;                                                                                                    \
      }                                                                                                              \
                                                                                                                     \
      verify(MTYPE_THING, t);

#define FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(level)                                                             \
  if (i == level->all_things_of_interest[ _group_ ].end()) {                                                         \
    break;                                                                                                           \
  }                                                                                                                  \
  }                                                                                                                  \
  level->all_things_of_interest_walk_in_progress = false;                                                            \
  level->handle_all_pending_things(_group_);                                                                         \
  }

#define FOR_ALL_ANIMATED_THINGS_LEVEL(level, group, t)                                                               \
  {                                                                                                                  \
    level->all_animated_things_walk_in_progress = true;                                                              \
    auto c                                      = level->all_animated_things[ group ];                               \
    auto i                                      = level->all_animated_things[ group ].begin();                       \
    while (i != level->all_animated_things[ group ].end()) {                                                         \
      auto t = i->second;                                                                                            \
      i++;                                                                                                           \
      verify(MTYPE_THING, t);

#define FOR_ALL_ANIMATED_THINGS_LEVEL_END(level)                                                                     \
  if (i == level->all_animated_things[ group ].end()) {                                                              \
    break;                                                                                                           \
  }                                                                                                                  \
  }                                                                                                                  \
  level->all_animated_things_walk_in_progress = false;                                                               \
  level->handle_all_pending_things(group);                                                                           \
  }

//
// Things that make decisions or have a lifespan
//
#define FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL(level, t)                                                              \
  FOR_ALL_THING_PRIO_GROUPS                                                                                          \
  {                                                                                                                  \
    level->all_things_of_interest_walk_in_progress = true;                                                           \
    auto c                                         = level->all_things_of_interest[ _group_ ];                       \
    auto i                                         = level->all_things_of_interest[ _group_ ].begin();               \
    while (i != level->all_things_of_interest[ _group_ ].end()) {                                                    \
      auto t = i->second;                                                                                            \
      /* LOG("ID %08x -> %p", i->first.id, t); */                                                                    \
      i++;                                                                                                           \
      if (t->is_hidden) {                                                                                            \
        if (! t->is_tickable()) { /* e.g. carried wand */                                                            \
          continue;                                                                                                  \
        }                                                                                                            \
      }                                                                                                              \
                                                                                                                     \
      verify(MTYPE_THING, t);

#define FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL_END(level)                                                             \
  if (i == level->all_things_of_interest[ _group_ ].end()) {                                                         \
    break;                                                                                                           \
  }                                                                                                                  \
  }                                                                                                                  \
  level->all_things_of_interest_walk_in_progress = false;                                                            \
  level->handle_all_pending_things(_group_);                                                                         \
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

#define FOR_TMP_THINGS_AT_DEPTH(level, t, x, y, z)                                                                   \
  FOR_TMP_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (t->z_depth != z) {                                                                                             \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }

#define FOR_ALL_LIGHTS_AT_DEPTH(level, t, x, y)                                                                      \
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
  if (t->is_the_grid) {                                                                                              \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_floor()) {                                                                                               \
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
  if (t->is_the_grid) {                                                                                              \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_floor()) {                                                                                               \
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
  if (t->is_the_grid) {                                                                                              \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_floor()) {                                                                                               \
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
  if (t->is_the_grid) {                                                                                              \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_floor()) {                                                                                               \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_hidden) {                                                                                                \
    continue;                                                                                                        \
  }                                                                                                                  \
  if (t->is_interesting() || t->is_attackable_by_monst() || t->is_attackable_by_player() || t->ai_obstacle()) {      \
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
  FOR_TMP_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (! t->is_cursor_path()) {                                                                                       \
    continue;                                                                                                        \
  }

#define FOR_ALL_DEBUG_PATH_THINGS(level, t, x, y)                                                                    \
  FOR_TMP_THINGS_WALKER_UNSAFE(level, t, x, y)                                                                       \
  if (! t->is_debug_path()) {                                                                                        \
    continue;                                                                                                        \
  }

  Thingp buffbox_describe(const uint32_t slot);
  Thingp buffbox_get(const uint32_t slot);
  Thingp debuffbox_describe(const uint32_t slot);
  Thingp debuffbox_get(const uint32_t slot);
  Thingp inventory_describe(const uint32_t slot);
  Thingp inventory_get(const uint32_t slot);
  Thingp inventory_get(void);
  Thingp skillbox_describe(const uint32_t slot);
  Thingp skillbox_get(const uint32_t slot);
  Thingp skillbox_get(void);
  Thingp thing_find(const ThingId id);
  Thingp thing_find_optional(const ThingId id);
  Thingp thing_new(Tpp, const point at, Thingp owner = nullptr);
  Thingp thing_new(const std::string &tp_name, Thingp owner = nullptr);
  Thingp thing_new(const std::string &tp_name, const point at, Thingp owner = nullptr);

  Tpp tp_random_mob(const point p);
  Tpp tp_random_mob_spawner_class_a(const point p);
  Tpp tp_random_mob_spawner_class_b(const point p);
  Tpp tp_random_monst(const point p);
  Tpp tp_random_monst_class_a(const point p);
  Tpp tp_random_monst_class_c(const point p);
  Tpp tp_random_monst_class_b(const point p);
  Tpp tp_random_monst_class_d(const point p);
  Tpp tp_random_monst_class_e(const point p);
  Tpp tp_random_treasure_class_a(const point p);
  Tpp tp_random_treasure_class_c(const point p);
  Tpp tp_random_treasure_class_b(const point p);
  Tpp tp_random_weapon_class_a(const point p);
  Tpp tp_random_weapon_class_c(const point p);
  Tpp tp_random_weapon_class_b(const point p);

  bool buffbox_over(const uint32_t slot);
  bool can_see_(int x0_in, int y0_in, int x1_in, int y1_in, int flag);
  bool can_see_obstacle(int x, int y);
  bool can_see_unimpeded(int x0, int y0, int x1, int y1);
  bool create_dungeon(point3d at, uint32_t seed);
  bool create_sewer_pipes(point3d at);
  bool create_sewer(point3d at, uint32_t seed);
  bool create_sewer_pools(void);
  bool create_wandering_monster(void);
  bool debuffbox_over(const uint32_t slot);
  bool inventory_assign(const uint32_t slot, Thingp);
  bool inventory_chosen(const uint32_t slot);
  bool inventory_over(const uint32_t slot);
  bool is_light_blocker(const int x, const int y) const;
  bool is_light_blocker(const point p) const;
  bool is_light_blocker_no_check(const int x, const int y) const;
  bool is_light_blocker_no_check(const point p) const;
  bool is_obs_destructable(const int x, const int y) const;
  bool is_obs_destructable(const point p) const;
  bool is_obs_destructable_no_check(const int x, const int y) const;
  bool is_obs_destructable_no_check(const point p) const;
  bool is_obs_wall_or_door(const int x, const int y) const;
  bool is_obs_wall_or_door(const point p) const;
  bool is_obs_wall_or_door_no_check(const int x, const int y) const;
  bool is_obs_wall_or_door_no_check(const point p) const;
  bool is_oob(const fpoint p) const;
  bool is_oob(const int x, const int y) const;
  bool is_oob(const int x, const int y, const int z) const;
  bool is_oob(const point p) const;
  bool screen_shake_begin(void);
  bool skillbox_chosen(const uint32_t slot);
  bool skillbox_over(const uint32_t slot);
  bool tick(void);

  int get_total_monst_hp_level(void);
  int get_total_monst_damage_level(void);
  int get_total_loot_level(void);
  int get_total_food_level(void);

  float get_wobble(void) const;
  float update_wobble(void);

  friend std::istream &operator>>(std::istream &in, Bits< Levelp & > my);
  friend std::ostream &operator<<(std::ostream &out, Bits< Levelp & > const my);

  int inventory_get_slot(Thingp item);

  std::string to_string(void);

  uint32_t num(void);

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
  uint8_t is_able_to_stand_on(const int x, const int y);
  uint8_t is_able_to_stand_on(const point p);
  uint8_t is_acid(const int x, const int y);
  uint8_t is_acid(const point p);
  uint8_t is_ascend_dungeon(const int x, const int y);
  uint8_t is_ascend_dungeon(const point p);
  uint8_t is_ascend_sewer(const int x, const int y);
  uint8_t is_ascend_sewer(const point p);
  uint8_t is_barrel(const int x, const int y);
  uint8_t is_barrel(const point p);
  uint8_t is_blood(const int x, const int y);
  uint8_t is_blood(const point p);
  uint8_t is_brazier(const int x, const int y);
  uint8_t is_brazier_no_check(const int x, const int y);
  uint8_t is_brazier(const point p);
  uint8_t is_bridge(const int x, const int y);
  uint8_t is_bridge(const point p);
  uint8_t is_chasm(const int x, const int y);
  uint8_t is_chasm(const point p);
  uint8_t is_corpse(const int x, const int y);
  uint8_t is_corpse(const point p);
  uint8_t is_corridor(const int x, const int y);
  uint8_t is_corridor(const point p);
  uint8_t is_cursor_path_hazard_for_player(const int x, const int y);
  uint8_t is_cursor_path_hazard_for_player(const point p);
  uint8_t is_heavy(const int x, const int y);
  uint8_t is_heavy(const point p);
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
  uint8_t is_wet_grass(const int x, const int y);
  uint8_t is_wet_grass(const point p);
  uint8_t is_enchantstone(const int x, const int y);
  uint8_t is_enchantstone(const point p);
  uint8_t is_fire(const int x, const int y);
  uint8_t is_fire_no_check(const int x, const int y);
  uint8_t is_fire(const point p);
  uint8_t is_floor(const int x, const int y);
  uint8_t is_floor(const point p);
  uint8_t is_foilage(const int x, const int y);
  uint8_t is_foilage(const point p);
  uint8_t is_food(const int x, const int y);
  uint8_t is_food(const point p);
  uint8_t is_gold(const int x, const int y);
  uint8_t is_gold(const point p);
  uint8_t is_hazard(const int x, const int y);
  uint8_t is_hazard(const point p);
  uint8_t is_key(const int x, const int y);
  uint8_t is_key(const point p);
  uint8_t is_lava(const point p);
  uint8_t is_lava(const int x, const int y);
  uint8_t is_lava_no_check(const int x, const int y);
  uint8_t is_lit_ever(const int x, const int y);
  uint8_t is_lit_ever(const point p);
  uint8_t is_lit_ever_no_check(const int x, const int y);
  uint8_t is_lit_ever_no_check(const point p);
  uint8_t is_lit_recently(const int x, const int y);
  uint8_t is_mob_spawner(const int x, const int y);
  uint8_t is_mob_spawner(const point p);
  uint8_t is_monst(const int x, const int y);
  uint8_t is_monst_or_player(const point p);
  uint8_t is_monst(const point p);
  uint8_t is_potion(const int x, const int y);
  uint8_t is_potion(const point p);
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
  uint8_t is_sticky(const int x, const int y);
  uint8_t is_sticky(const point p);
  uint8_t is_treasure_type(const int x, const int y);
  uint8_t is_treasure_type(const point p);
  uint8_t is_weapon_class_a(const int x, const int y);
  uint8_t is_weapon_class_a(const point p);
  uint8_t is_weapon_class_b(const int x, const int y);
  uint8_t is_weapon_class_b(const point p);
  uint8_t is_weapon_class_c(const int x, const int y);
  uint8_t is_weapon_class_c(const point p);
  uint8_t is_weapon_type(const int x, const int y);
  uint8_t is_weapon_type(const point p);
  uint8_t is_wall(const int x, const int y);
  uint8_t is_wall(const point p);
  uint8_t is_wand(const int x, const int y);
  uint8_t is_wand(const point p);
  uint8_t is_ring(const int x, const int y);
  uint8_t is_ring(const point p);
  uint8_t is_water(const int x, const int y);
  uint8_t is_water(const point p);
  uint8_t is_lit_currently(const int x, const int y);
  uint8_t is_lit_currently(const point p);
  uint8_t is_lit_currently_no_check(const int x, const int y);
  uint8_t is_lit_currently_no_check(const point p);

  void assign_leaders_and_followers(void);
  void clear(void);
  void con(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void con_(const char *fmt, va_list args); // compile error without
  void create_dungeon_place_braziers(Dungeonp d, const std::string &what);
  void create_dungeon_place_bridge(Dungeonp d);
  void create_dungeon_place_chasm(Dungeonp d, const std::string &what);
  void create_dungeon_place_corridor(Dungeonp d, const std::string what, int depth);
  void create_dungeon_place_deep_water(Dungeonp d, const std::string &what);
  void create_dungeon_place_floors(Dungeonp d, const std::string what, int depth, int var, int w, int h, int tries);
  void create_dungeon_place_lava(Dungeonp d, const std::string &what);
  void create_dungeon_place_lava_smoke(Dungeonp d);
  void create_dungeon_place_objects_with_normal_placement_rules(Dungeonp d);
  void create_dungeon_place_place_shallow_water(Dungeonp d, const std::string &what);
  void create_dungeon_place_random_blood(Dungeonp d);
  void create_dungeon_place_random_floor_deco(Dungeonp d);
  void create_dungeon_place_remaining_floor(Dungeonp d, const std::string &what);
  void create_dungeon_place_remaining_rocks(Dungeonp d, const std::string &what);
  void create_dungeon_place_remaining_walls(Dungeonp d, const std::string &what);
  void create_dungeon_place_rocks(Dungeonp d, int variant, int block_width, int block_height, int tries);
  void create_dungeon_place_sewer_pipes(Dungeonp d);
  void create_dungeon_place_walls(Dungeonp d, Tpp tp, int variant, int block_width, int block_height, int tries);
  void created(void);
  void create(point3d at, uint32_t seed, int difficulty_depth, int dungeon_depth);
  void create_sewer_place_remaining_walls(const std::string &what);
  void create_sewer_place_walls(int variant, int block_width, int block_height, int tries);
  void cursor_check_if_scroll_needed(void);
  void cursor_describe(void);
  void cursor_find_on_visible_things(const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
  void cursor_move(void);
  void cursor_path_clear(void);
  void cursor_path_create(const std::vector< point > &move_path);
  void cursor_path_create(void);
  void cursor_path_draw_circle(void);
  void cursor_path_draw(const std::vector< point > &move_path);
  void cursor_path_draw_line(const std::vector< point > &move_path);
  void cursor_path_draw_line(point start, point end);
  void cursor_path_draw(point start, point end);
  void cursor_path_draw(void);
  void cursor_recreate(void);
  void debug_path_clear(void);
  void debug_path_create(const std::vector< point > &move_path);
  void debug_path_draw(const std::vector< point > &move_path);
  void debug_path_draw_line(const std::vector< point > &move_path);
  void describe(point at);
  void describe(Thingp);
  void display_anim(void);
  void display_blood(void);
  void display_deep_water(const int fbo, const int16_t minx, const int16_t miny, const int16_t, const int16_t maxy);
  void display_external_particles(void);
  void display_fade_in(void);
  void display_fade_out(void);
  void display_internal_particles(void);
  void display_lasers(void);
  void display_lava(const int fbo, const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t);
  void display_map_bg_things(void);
  void display_map_fg2_things(const int fbo, const int16_t minx, const int16_t miny, const int16_t, const int16_t);
  void display_map_fg_things(const int fbo, const int16_t minx, const int16_t miny, const int16_t, const int16_t);
  void display_map_things(const int fbo, const int16_t minx, const int16_t miny, const int16_t, const int16_t);
  void display_map(void);
  void display_map_mini(void);
  void display_map_debug(int x, int y);
  void display_map_debug(int x, int y, int tlx, int tly, int brx, int bly);
  void display_projectiles(void);
  void display_target(void);
  void display(void);
  void display_water(const int fbo, const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
  void dmap_to_player_update(void);
  void dump(std::string prefix);
  void dump(std::string prefix, std::ostream &out);
  void err(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void err_(const char *fmt, va_list args); // compile error without
  void fini(void);
  void get_tiles(void);
  void handle_all_pending_things(int group);
  void handle_all_pending_things(void);
  void handle_input_events(void);
  void heatmap_print(point at, point tl, point br);
  void incr_fade_in(const int x, const int y);
  void incr_fade_in_no_check(const int x, const int y);
  void incr_heatmap(const int x, const int y);
  void incr_heatmap_no_check(const int x, const int y);
  void incr_heatmap_no_check(const int x, const int y, int dv);
  void inventory_dump(void);
  void lights_fade(void);
  void lights_render(int minx, int miny, int maxx, int maxy, int fbo);
  void lights_render_small_lights(int minx, int miny, int maxx, int maxy, int fbo, bool include_player_lights);
  void lights_update_new_level(void);
  void lights_update_same_level(void);
  void log(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
  void log_(const char *fmt, va_list args); // compile error without
  void l_shaped_path_to_diag(std::vector< point > &path);
  void new_external_particle(point start, point end, isize sz, uint32_t dur, Tilep, bool hflip, bool vis);
  void new_external_particle(ThingId, point start, point end, isize sz, uint32_t dur, Tilep, bool hflip, bool vis);
  void new_internal_particle(point start, point end, isize sz, uint32_t dur, Tilep tile, bool, bool vis);
  void new_internal_particle(ThingId, point start, point end, isize sz, uint32_t dur, Tilep, bool hflip, bool vis);
  void new_laser(ThingId id, ThingId target_id, point start, point stop, uint32_t dur, bool follow);
  void new_projectile(ThingId id, ThingId target_id, point start, point stop, uint32_t dur, bool follow);
  void place_dirt(Dungeonp d);
  void place_dry_grass(Dungeonp d);
  void place_floor_deco(Dungeonp d);
  void place_foilage(Dungeonp d);
  void place_random_torches(Dungeonp d);
  void place_random_treasure(Dungeonp d);
  void place_spiderweb(Dungeonp d);
  void place_the_grid(void);
  void place_wet_grass(Dungeonp d);
  void screen_shake_end(void);
  void scroll_map_do(bool fast);
  void scroll_map_set_target(void);
  void scroll_map_to_player_immediately(void);
  void scroll_map_to_player(void);
  void scroll_map(void);
  void set_chances_of_creating(void);
  void set_gfx_water(const int x, const int y);
  void set_is_able_to_stand_on(const int x, const int y);
  void set_is_acid(const int x, const int y);
  void set_is_ascend_dungeon(const int x, const int y);
  void set_is_ascend_sewer(const int x, const int y);
  void set_is_barrel(const int x, const int y);
  void set_is_blood(const int x, const int y);
  void set_is_brazier(const int x, const int y);
  void set_is_bridge(const int x, const int y);
  void set_is_chasm(const int x, const int y);
  void set_is_corpse(const int x, const int y);
  void set_is_corridor(const int x, const int y);
  void set_is_cursor_path_hazard_for_player(const int x, const int y);
  void set_is_deep_water(const int x, const int y);
  void set_is_descend_dungeon(const int x, const int y);
  void set_is_descend_sewer(const int x, const int y);
  void set_is_dirt(const int x, const int y);
  void set_is_door(const int x, const int y);
  void set_is_dry_grass(const int x, const int y);
  void set_is_enchantstone(const int x, const int y);
  void set_is_fire(const int x, const int y);
  void set_is_floor(const int x, const int y);
  void set_is_foilage(const int x, const int y);
  void set_is_food(const int x, const int y);
  void set_is_gold(const int x, const int y);
  void set_is_hazard(const int x, const int y);
  void set_is_heavy(const int x, const int y);
  void set_is_key(const int x, const int y);
  void set_is_lava(const int x, const int y);
  void set_is_light_blocker(const int x, const int y);
  void set_is_light_blocker_no_check(const int x, const int y);
  void set_is_lit_currently(const int x, const int y);
  void set_is_lit_currently_no_check(const int x, const int y);
  void set_is_lit_currently_no_check(const int x, const int y, uint8_t v);
  void set_is_lit_ever(const int x, const int y);
  void set_is_lit_ever_no_check(const int x, const int y);
  void set_is_map_changed(const int x, const int y);
  void set_is_map_changed_no_check(const int x, const int y);
  void set_is_map_changed_no_check(const int x, const int y, uint32_t v);
  void set_is_mob_spawner(const int x, const int y);
  void set_is_monst(const int x, const int y);
  void set_is_obs_destructable(const int x, const int y);
  void set_is_obs_destructable_no_check(const int x, const int y);
  void set_is_obs_wall_or_door(const int x, const int y);
  void set_is_obs_wall_or_door_no_check(const int x, const int y);
  void set_is_potion(const int x, const int y);
  void set_is_ring(const int x, const int y);
  void set_is_ripple(const int x, const int y);
  void set_is_rock(const int x, const int y);
  void set_is_secret_door(const int x, const int y);
  void set_is_shallow_water(const int x, const int y);
  void set_is_shovable(const int x, const int y);
  void set_is_skillstone(const int x, const int y);
  void set_is_smoke(const int x, const int y);
  void set_is_spiderweb(const int x, const int y);
  void set_is_sticky(const int x, const int y);
  void set_is_treasure_type(const int x, const int y);
  void set_is_wall(const int x, const int y);
  void set_is_wand(const int x, const int y);
  void set_is_wet_grass(const int x, const int y);
  void set_wobble(float);
  void things_gc(bool force);
  void things_gc_force(void);
  void things_gc_if_possible(void);
  void things_tick(void);
  void unset_fade_in(const int x, const int y);
  void unset_fade_in_no_check(const int x, const int y);
  void unset_gfx_water(const int x, const int y);
  void unset_heatmap(const int x, const int y);
  void unset_heatmap_no_check(const int x, const int y);
  void unset_is_able_to_stand_on(const int x, const int y);
  void unset_is_acid(const int x, const int y);
  void unset_is_ascend_dungeon(const int x, const int y);
  void unset_is_ascend_sewer(const int x, const int y);
  void unset_is_barrel(const int x, const int y);
  void unset_is_blood(const int x, const int y);
  void unset_is_brazier(const int x, const int y);
  void unset_is_bridge(const int x, const int y);
  void unset_is_chasm(const int x, const int y);
  void unset_is_corpse(const int x, const int y);
  void unset_is_corridor(const int x, const int y);
  void unset_is_cursor_path_hazard_for_player(const int x, const int y);
  void unset_is_deep_water(const int x, const int y);
  void unset_is_descend_dungeon(const int x, const int y);
  void unset_is_descend_sewer(const int x, const int y);
  void unset_is_dirt(const int x, const int y);
  void unset_is_door(const int x, const int y);
  void unset_is_dry_grass(const int x, const int y);
  void unset_is_enchantstone(const int x, const int y);
  void unset_is_fire(const int x, const int y);
  void unset_is_floor(const int x, const int y);
  void unset_is_foilage(const int x, const int y);
  void unset_is_food(const int x, const int y);
  void unset_is_gold(const int x, const int y);
  void unset_is_hazard(const int x, const int y);
  void unset_is_heavy(const int x, const int y);
  void unset_is_key(const int x, const int y);
  void unset_is_lava(const int x, const int y);
  void unset_is_light_blocker(const int x, const int y);
  void unset_is_light_blocker_no_check(const int x, const int y);
  void unset_is_lit_currently(const int x, const int y);
  void unset_is_lit_currently_no_check(const int x, const int y);
  void unset_is_lit_ever(const int x, const int y);
  void unset_is_lit_ever_no_check(const int x, const int y);
  void unset_is_map_changed(const int x, const int y);
  void unset_is_map_changed_no_check(const int x, const int y);
  void unset_is_mob_spawner(const int x, const int y);
  void unset_is_monst(const int x, const int y);
  void unset_is_obs_destructable(const int x, const int y);
  void unset_is_obs_destructable_no_check(const int x, const int y);
  void unset_is_obs_wall_or_door(const int x, const int y);
  void unset_is_obs_wall_or_door_no_check(const int x, const int y);
  void unset_is_potion(const int x, const int y);
  void unset_is_ring(const int x, const int y);
  void unset_is_ripple(const int x, const int y);
  void unset_is_rock(const int x, const int y);
  void unset_is_secret_door(const int x, const int y);
  void unset_is_shallow_water(const int x, const int y);
  void unset_is_shovable(const int x, const int y);
  void unset_is_skillstone(const int x, const int y);
  void unset_is_smoke(const int x, const int y);
  void unset_is_spiderweb(const int x, const int y);
  void unset_is_sticky(const int x, const int y);
  void unset_is_treasure_type(const int x, const int y);
  void unset_is_wall(const int x, const int y);
  void unset_is_wand(const int x, const int y);
  void unset_is_wet_grass(const int x, const int y);
  void update_all_ticks(void);
  void update_deep_water(void);
  void update_hazard_tile_map(void);
  void update_heatmap(void);
  void update_map_things_to_stand_on(void);
  void update_map(void);
  void update_map_mini(bool showing_two_levels, bool show_faded);
  void update_map_debug(int x, int y);
  void update_new_level(void);
  void update_same_level_immediately(void);
  void update_same_level(void);
  void update_things_next_to_a_chasm(void);
  void update(void);
  void update_water_next_to_lava(void);

  uint32_t is_map_changed(const int x, const int y);
  uint32_t is_map_changed(const point p);
  uint32_t is_map_changed_no_check(const int x, const int y);
  uint32_t is_map_changed_no_check(const point p);

  std::deque< point >  flood_fill(point) const;
  std::deque< point >  flood_fill_points(point, std::function< int(Thingp) > filter);
  std::deque< Thingp > flood_fill_things(point, std::function< int(Thingp) > filter);

  void scan(struct FovMap_ *fov, int pov_x, int pov_y,
            int   distance, // Polar distance from POV.
            float view_slope_high, float view_slope_low, int max_radius, int octant, bool light_walls);

  bool fov_calculete(struct FovMap_ *fov, int pov_x, int pov_y, int max_radius, bool light_walls = true);
};

#endif
