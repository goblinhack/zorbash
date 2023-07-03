//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_MONST_HPP_
#define _MY_MONST_HPP_

#include <array> // do not remove
#include <list>
#include <map>

#include "my_color.hpp"
#include "my_enums.hpp"
#include "my_level_fov.hpp"
#include "my_light.hpp"
#include "my_point3d.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_id.hpp"
#include "my_time.hpp"

constexpr uint32_t THING_MAGIC_BEGIN = 11221122;
constexpr uint32_t THING_MAGIC_END   = 22112211;
constexpr uint32_t THING_MAGIC_FINAL = 33333333;

//
// Search priorities in order
//
#define MONST_SEARCH_TYPE_MAX                       7
#define MONST_SEARCH_TYPE_CAN_SEE_JUMP_ALLOWED      0
#define MONST_SEARCH_TYPE_LOCAL_NO_JUMP             1
#define MONST_SEARCH_TYPE_LOCAL_JUMP_ALLOWED        2
#define MONST_SEARCH_TYPE_GLOBAL_NO_JUMP            3
#define MONST_SEARCH_TYPE_GLOBAL_JUMP_ALLOWED       4
#define MONST_SEARCH_TYPE_LAST_RESORTS_NO_JUMP      5
#define MONST_SEARCH_TYPE_LAST_RESORTS_JUMP_ALLOWED 6

#define FOR_ALL_BUFFS(_id_)          for (auto _id_ : itemsp()->buffs)
#define FOR_ALL_BUFFS_FOR(_t_, _id_) for (auto _id_ : (_t_)->itemsp()->buffs)

#define FOR_ALL_DEBUFFS(_id_)          for (auto _id_ : itemsp()->debuffs)
#define FOR_ALL_DEBUFFS_FOR(_t_, _id_) for (auto _id_ : (_t_)->itemsp()->debuffs)

#define FOR_ALL_SKILLS(_id_)          for (auto _id_ : itemsp()->skills)
#define FOR_ALL_SKILLS_FOR(_t_, _id_) for (auto _id_ : (_t_)->itemsp()->skills)

#define FOR_ALL_CARRYING(_id_)        for (auto _id_ : itemsp()->carrying)
#define FOR_ALL_CARRIED_BY(_t_, _id_) for (auto _id_ : (_t_)->itemsp()->carrying)

//
// Extra thing info. Needed for monsters and items.
//
typedef struct ThingInfo_ {
public:
  std::vector< Lightp > light = {}; // Has light sources?

  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////

  point3d born; // What level and depth was this born at

  ThingId on_fire_id_anim {};
  ThingId owner_id {};         // Who carries this thing?
  ThingId mob_id {};           // Who generated this thing?
  ThingId leader_id {};        // Who is the current ally leader
  ThingId spawner_owner_id {}; // Who spawned this thing?

  color light_col {};

  float bounce_fade   = {}; // 0.1; rapid, 0.9 slow
  float bounce_height = {}; // Percentage of tile height.
  float fadeup_fade   = {}; // 0.1; rapid, 0.9 slow
  float fadeup_height = {}; // Percentage of tile height.
  float fall_height   = {}; // y offset for falling
  float wobble        = {}; // Fades when set

  point lunge_to; // When a monst attacks something

  // begin sort marker1 {
  int attack_num          = {};
  int capacity_height     = {};
  int capacity_width      = {};
  int distance_throw      = {};
  int enchant             = {};
  int enchant_max         = {};
  int gold                = {-1};
  int health              = {};
  int health_max          = {};
  int hunger              = {THING_HUNGER_FULL};
  int jump_distance_bonus = {};
  int keys                = {};
  int lifespan            = {}; // How many things this thing owns.
  int light_dist          = {}; // Current strength, including torches
  int magic               = {};
  int magic_max           = {};
  int monst_state         = {};
  int move_count          = {};
  int movement_remaining  = {};
  int move_speed_bonus    = {};
  int move_speed_curr     = {};
  int necrosis            = {};
  int noise               = {};
  int nutrition           = {};
  int physical_training   = {};
  int poison              = {};
  int prev_light_dist     = {}; // Current strength, including torches
  int score               = {};
  int shove_bonus         = {};
  int stamina             = {};
  int stamina_max         = {};
  int stat_att            = {};
  int stat_att_bonus      = {};
  int stat_con            = {};
  int stat_con_bonus      = {};
  int stat_def            = {};
  int stat_def_bonus      = {};
  int stat_dex            = {};
  int stat_dex_bonus      = {};
  int stat_luck           = {};
  int stat_luck_bonus     = {};
  int stats02             = {};
  int stats03             = {};
  int stats04             = {};
  int stats05             = {};
  int stats06             = {};
  int stats07             = {};
  int stats09             = {};
  int stat_str            = {};
  int stat_str_bonus      = {};
  int submerged_offset    = {}; // Pixels
  int tick_resurrect_when = {};
  // end sort marker1 }

  int8_t bounce_count       = {}; // Graphical bounce count
  int8_t charge_count       = {}; // Wand charges
  int8_t sleep_count        = {}; // How long asleep
  int8_t damaged_count      = {}; // How much a weapon is damaged.
  int8_t map_treasure_count = {}; // How many treasure maps held. Really only care if > 0
  int8_t map_beast_count    = {}; // How many beast maps held. Really only care if > 0

  std::string msg;           // Text that floats on screen
  std::string dead_reason;   // What defeated me
  std::string poison_reason; // What poisoned me

  // begin sort marker2 {
  ts_t ts_anim_delay_end {};
  ts_t ts_bounce_begin {};
  ts_t ts_bounce_end {};
  ts_t ts_fadeup_begin {};
  ts_t ts_fadeup_end {};
  ts_t ts_fall_begin {};
  ts_t ts_fall_end {};
  ts_t ts_flip_start {}; // Used for animating the steps.
  ts_t ts_lunge_begin {};
  ts_t ts_lunge_end {};
  // end sort marker2 }

  //
  // Used for calling on_idle()
  //
  // Avoiding numeric_limits to reduce the number of headers to pull in.
  //
  int tick_last_did_something {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // When this thing was dropped
  //
  int tick_last_dropped {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // To prevent teleport looping
  //
  int tick_last_teleported {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // If things have stopped moving, perform location checks on where theuy
  // are now. This handles things like shoving a monst into a chasm. We do
  // location checks on the ends of moves, but this is a backup and will
  // also handle things that do not move, like a staff that is now on fire.
  //
  int tick_last_location_check {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // Don't try and escape too often else the player can never kill the monst!
  //
  int tick_last_escape {-1 /* std::numeric_limits< uint32_t >::max() */};
  int tick_last_level_change {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // When we were last attacked
  //
  int tick_last_i_was_attacked {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // Last time we had to hold our breath
  //
  int tick_last_poison_gas_exposure {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // When we last attacked
  //
  int tick_last_i_attacked {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // When we last tried to attack and missed or succeeded
  //
  int tick_last_i_tried_to_attack {-1 /* std::numeric_limits< uint32_t >::max() */};
  //
  // This is to ensure things do not wake and immediately attack
  //
  int tick_last_awoke {-1 /* std::numeric_limits< uint32_t >::max() */};

  //
  // List of things I own:
  //
  std::set< ThingId > owned {};
  //
  // List of things I am the mob owner of:
  //
  std::set< ThingId > minions {};
  //
  // List of things in my team and I am the leader of:
  //
  std::set< ThingId > followers {};
  //
  // List of things I have spawned:
  //
  std::set< ThingId > spawned {};

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
  int dmg_current {}; // Current damage; so it can be modified by python

  ThingId popup_owner_id {}; // Who popped up this thing?
} ThingInfo;

//
// All carried items and buffs etc.. Typically only needed for an intelligent
// monster or the player.
//
typedef struct ThingItem_ {
public:
  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  std::array< ThingId, MONST_EQUIP_MAX > equip_id {};
  std::array< ThingId, MONST_EQUIP_MAX > equip_id_carry_anim {};
  std::array< ThingId, MONST_EQUIP_MAX > equip_id_use_anim {};
  std::array< ThingId, BODYPART_MAX >    bodypart_id {};

  point bag_position {-1, -1};
  point last_bag_position {-1, -1};
  point where_i_dropped_an_item_last {-1, -1};
  point where_i_failed_to_collect_last {-1, -1};

  std::list< ThingId > carrying;
  std::list< ThingId > skills;
  std::list< ThingId > buffs;
  std::list< ThingId > debuffs;

  std::vector< ThingId > inventory_shortcuts; // Which items are in which slot
  std::vector< ThingId > skillbox_id;         // Which skills are in which slot
  std::vector< ThingId > buffbox_id;          // Which buffs are in which slot
  std::vector< ThingId > debuffbox_id;        // Which debuffs are in which slot

  std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > bag {};

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

  //
  // If in transit, this is the wid owning me
  //
  std::set< Widp > thing_wid;
} ThingItem;

typedef struct ThingAi_ {
public:
  AgeMap age_map;          // How old a cell is
  AgeMap interrupt_map;    // If we've ever interrupt this tile and when
  Dmap   dmap_can_see_old; // Used for detecting changes in dmaps

  uint8_t idle_count  = {}; // How long we have not moved
  uint8_t stuck_count = {}; // How long we have not moved due to being stuck

  Dmap dmap_can_see; // What the monster can reach during AI

  //
  // This is flushed when the monster changes level.
  //
  // For the player we store this on the level context so we can see the
  // contents of old levels.
  //
  FovMap can_see_currently; // Shadowcasting of what can be seen currently
  FovMap can_see_ever;      // Shadowcasting of what can be seen ever on this level

  point wander_dest {0, 0};

  std::set< TpId >    perma_enemies {};      // List of thing types that wronged us
  std::set< TpId >    perma_friends {};      // List of friends
  std::set< ThingId > thing_friends {};      // List of friends
                                             //
  std::map< ThingId, int > thing_enemies {}; // List of things that wronged us
  std::map< ThingId, int > avoid {};         // List of things that wronged us and need to be avoided
  std::map< ThingId, int > goal_penalty {};  // Helps to avoid goal oscillation

  std::vector< point > move_path;

  //
  // Not worth saving as is cleared each tick
  //
  std::map< ThingId, int > recently_hit_by {};
} ThingAi;

#endif // _MY_THING_HPP_
