//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_MONST_H_
#define _MY_MONST_H_

#include "my_level_shadow_casting.h"
#include "my_light.h"
#include "my_thing_ai.h"
#include "my_thing_id.h"
#include "my_time.h"
#include <list>

constexpr uint32_t THING_MAGIC_BEGIN = 11221122;
constexpr uint32_t THING_MAGIC_END   = 22112211;
constexpr uint32_t THING_MAGIC_FINAL = 33333333;

enum {
  MONST_SIZE_TINY,
  MONST_SIZE_SMALL,
  MONST_SIZE_NORMAL,
  MONST_SIZE_LARGE,
  MONST_SIZE_GIANT,
  MONST_SIZE_GARGANTUAN,
};

enum {
  MONST_STATE_IDLE,
  MONST_STATE_MOVING,
  MONST_STATE_RESTING,
  MONST_STATE_OPEN_INVENTORY,
  MONST_STATE_USING_ENCHANTSTONE,
  MONST_STATE_USING_SKILLSTONE,
};

typedef struct MonstInfo_ {
public:
  std::vector< Lightp > light = {}; // Has light sources?

  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  ThingId                 on_fire_id_anim {};
  ThingId                 owner_id {};         // Who carries this thing?
  ThingId                 minion_owner_id {};  // Who generated this thing?
  ThingId                 spawner_owner_id {}; // Who spawned this thing?
  ThingId                 weapon_id {};        // Current weapon
  ThingId                 weapon_id_carry_anim {};
  ThingId                 weapon_id_use_anim {};
  color                   light_col {};
  float                   bounce_fade   = {}; // 0.1; rapid, 0.9 slow
  float                   bounce_height = {}; // Percentage of tile height.
  float                   fadeup_fade   = {}; // 0.1; rapid, 0.9 slow
  float                   fadeup_height = {}; // Percentage of tile height.
  float                   fall_height   = {}; // y offset for falling
  float                   wobble        = {}; // Fades when set
  fpoint                  lunge_to;           // When a monst attacks something
  int                     bounce_count = {};
  int                     capacity_height {};
  int                     capacity_width {};
  int                     charge_count = {}; // How many things this thing spawned.
  int                     enchant      = {};
  int                     enchant_max  = {};
  int                     gold         = {};
  int                     health       = {};
  int                     health_max   = {};
  int                     keys         = {};
  int                     lifespan     = {}; // How many things this thing owns.
  int                     light_quality {};
  int                     light_strength {}; // Current strength, including torches
  int                     minion_count = {}; // How many things this thing spawned.
  int                     owned_count  = {}; // How many things this thing owns.
  int                     poison       = {};
  int                     monst_state {};
  int                     score               = {};
  int                     spawned_count       = {}; // How many things this thing owns.
  int                     stamina             = {};
  int                     stamina_max         = {};
  int                     stat_attack         = {};
  int                     stat_constitution   = {};
  int                     stat_defence        = {};
  int                     stats01             = {};
  int                     stats02             = {};
  int                     stats03             = {};
  int                     stats04             = {};
  int                     stats05             = {};
  int                     stats06             = {};
  int                     stats07             = {};
  int                     stats08             = {};
  int                     stats09             = {};
  int                     stats10             = {};
  int                     stats11             = {};
  int                     stats12             = {};
  int                     stats17             = {};
  int                     stats19             = {};
  int                     stat_strength       = {};
  int                     submerged_offset    = {}; // Pixels
  int                     throw_distance      = {};
  int                     tick_resurrect_when = {};
  point                   bag_position {-1, -1};
  point                   wander_target {-1, -1};
  point                   where_i_dropped_an_item_last {-1, -1};
  point                   where_i_failed_to_collect_last {-1, -1};
  std::list< ThingId >    carrying;
  std::list< ThingId >    skills;
  std::list< ThingId >    buffs;
  std::list< ThingId >    debuffs;
  std::string             msg;          // Text that floats on screen
  std::string             dead_reason;  // What defeated me
  std::vector< uint16_t > inventory_id; // Which items are in which slot
  std::vector< uint16_t > skillbox_id;  // Which skills are in which slot
  std::vector< uint16_t > buffbox_id;   // Which buffs are in which slot
  std::vector< uint16_t > debuffbox_id; // Which debuffs are in which slot
  std::array< std::array< ThingId, MAX_BAG_WIDTH >, MAX_BAG_HEIGHT > bag {};
  ts_t                                                               ts_bounce_begin {};
  ts_t                                                               ts_bounce_end {};
  ts_t                                                               ts_fadeup_begin {};
  ts_t                                                               ts_fadeup_end {};
  ts_t                                                               ts_fall_begin {};
  ts_t                                                               ts_fall_end {};
  ts_t                                                               ts_flip_start {}; // Used for animating the steps.
  ts_t                                                               ts_lunge_begin {};
  ts_t                                                               ts_lunge_end {};
  ts_t                                                               ts_anim_delay_end {};
  //
  // Used for calling on_idle()
  //
  uint32_t tick_last_did_something {};
  //
  // When this thing was dropped
  //
  uint32_t tick_last_dropped {};
  //
  // If things have stopped moving, perform location checks on where theuy
  // are now. This handles things like shoving a monst into a chasm. We do
  // location checks on the ends of moves, but this is a backup and will
  // also handle things that do not move, like a wand that is now on fire.
  //
  uint32_t tick_last_location_check {};
  //
  // Don't try and escape too often else the player can never kill the monst!
  //
  uint32_t tick_last_escape {};
  uint32_t tick_last_level_change {};
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  //
  // Things not worth saving
  //
  point preferred_bag_position {-1, -1};
  int   current_damage {}; // Current damage; so it can be modified by python
} MonstInfo;
std::ostream &operator<<(std::ostream &out, Bits< const MonstInfop & > const my);
std::istream &operator>>(std::istream &in, Bits< MonstInfop & > my);

typedef struct MonstAi_ {
public:
  AgeMap                   age_map;           // How old a cell is
  AgeMap                   seen_map;          // If we've ever seen this tile and when
  AgeMap                   interrupt_map;     // If we've ever interrupt this tile and when
  Dmap                     dmap_can_see;      // What the monster can reach during AI
  FovMap                   can_see_currently; // Shadowcasting of what can be seen currently
  FovMap                   can_see_ever;      // Shadowcasting of what can be seen ever on this level
  std::map< ThingId, int > enemies {};        // List of things that wronged us
  std::map< ThingId, int > avoid {};          // List of things that wronged us and need to be avoided
  std::vector< point >     move_path;
} MonstAi;
std::ostream &operator<<(std::ostream &out, Bits< const MonstAip & > const my);
std::istream &operator>>(std::istream &in, Bits< MonstAip & > my);

#endif // _MY_THING_H_
