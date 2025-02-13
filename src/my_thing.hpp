//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_HPP_
#define _MY_THING_HPP_

#include <functional> // for std::function
#include <list>

#include "my_color.hpp"
#include "my_dice.hpp"
#include "my_fwd.hpp"
#include "my_point3d.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_defs.hpp"
#include "my_thing_id.hpp"
#include "my_time.hpp"

typedef enum {
  THING_SHOVE_TRIED_AND_FAILED,
  THING_SHOVE_TRIED_AND_PASSED,
  THING_SHOVE_NEVER_TRIED,
} ThingShoved;

typedef enum {
  THING_MOVE_REASON_MOUSE,
  THING_MOVE_REASON_AI,
} ThingMoveReason;

typedef enum {
  THING_DANGER_LEVEL_WALKOVER,
  THING_DANGER_LEVEL_HARMLESS,
  THING_DANGER_LEVEL_MOSTLY_HARMLESS,
  THING_DANGER_LEVEL_SLIGHT_CAUTION,
  THING_DANGER_LEVEL_MODERATE_CAUTION,
  THING_DANGER_LEVEL_CAUTION_ADVISED,
  THING_DANGER_LEVEL_DANGEROUS,
  THING_DANGER_LEVEL_CRITICAL,
} ThingDangerLevel;

typedef class BlitOptions_
{
public:
  bool reflection {};
} BlitOptions;

typedef struct {
  uint16_t tile_outline;
  uint16_t bl1_tile;
  uint16_t bot1_tile;
  uint16_t br1_tile;
  uint16_t left1_tile;
  uint16_t right1_tile;
  uint16_t tl1_tile;
  uint16_t top1_tile;
  uint16_t tr1_tile;
  uint16_t bl2_tile;
  uint16_t bot2_tile;
  uint16_t bot3_tile;
  uint16_t br2_tile;
  uint16_t left2_tile;
  uint16_t right2_tile;
  uint16_t tl2_tile;
  uint16_t top2_tile;
  uint16_t tr2_tile;
} ThingTiles;

typedef class UseOptions_
{
public:
  int  preferred_equip {};
  bool preferred_equip_set {};
  bool radial_effect {};
  bool is_reflected {};
  bool remove_after_use {};
} UseOptions;

typedef class DropOptions_
{
public:
  bool is_able_to_be_equipped {};
  bool is_being_unequipped {};
  bool is_being_thrown {};
  bool is_being_stolen {};
  bool is_being_used {};
} DropOptions;

typedef class ShoveOptions_
{
public:
  bool force {};
  bool stumble {};
} ShoveOptions;

typedef class CarryOptions_
{
public:
  bool is_being_stolen {};
  bool is_able_to_be_equipped {};
  bool is_auto_collect_allowed {};
} CarryOptions;

typedef class TeleportOptions_
{
public:
  //
  // Self initiated teleport.
  //
  bool teleport_self {};
  //
  // Escaping via teleport.
  //
  bool teleport_escape {};
  //
  // Attacking closer.
  //
  bool teleport_closer {};
  //
  // Teleport a victim.
  //
  bool teleport_attack {};
  //
  // Avoid chasms and hazards/
  //
  bool teleport_carefully {};
  //
  // Limit distance you can teleport.
  //
  bool teleport_limit {};
} TeleportOptions;

typedef class Thing_
{
private:
  //
  // As this is called a lot, probably worth the memory
  //
  Tpp mytp {};

public:
  Thing_(void);
  ~Thing_(void);

public:
  ThingInfop  _infop {};
  ThingItemsp _itemsp {};
  ThingAip    _aip {};

  Levelp level {};

  ThingId    id {}; // Unique per thing.
  ThingTiles tiles {};

  fpoint interpolated_at;

  ts_t ts_next_frame {};

  point last_at;       // Previous hop where we were.
  point curr_at;       // Grid coordinates.
  point last_attached; // Where we were last pushed onto the map
  point last_ascii_at; // Last ascii tile on screen position
  point last_blit_br;  // Last blit coords
  point last_blit_tl;  // Offset from top left of map
  point last_blit_at;  // Center of the above
  point blit_offset;   // Used to arrange for non overlapping popups

  uint16_t tile_curr {};
  int16_t  tp_id {-1}; // Common settings

  uint8_t z_depth {};
  uint8_t laser_count {};

  int16_t temperature {TEMPERATURE_ROOM}; // Celsius

  //
  // Used for alpha fading and giving tiles slightly sifferent colors when
  // in ascii mode; to help with visibility.
  //
  color blit_bg_color;
  color blit_fg_color;

  uint64_t dir : 4 {}; // Direction

  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  // begin sort marker1 {
  uint64_t corpse_cleanup                               : 1 {}; // Used to remove corpses when eaten or burnt
  uint64_t gfx_ascii_animated                           : 1 {}; // Animated in ascii mode?
  uint64_t gfx_pixelart_animated                        : 1 {}; // Animated in pixelart mode?
  uint64_t has_attacked_player                          : 1 {}; // Has it attacked the precious?
  uint64_t has_ever_moved                               : 1 {}; // Has it ever moved? e.g. a gargoyle
  uint64_t has_light                                    : 1 {}; // Has it a light source?
  uint64_t has_projectile                               : 1 {}; // Current projectile being fired
  uint64_t has_seen_player_msg_shown                    : 1 {}; // Seen by player has been shown
  uint64_t _is_able_to_be_resurrected                   : 1 {}; // Can be removed by negation
  uint64_t _is_able_to_regenerate                       : 1 {}; // Can be removed by negation
  uint64_t is_activated                                 : 1 {}; // This skill is activated
  uint64_t is_attached                                  : 1 {}; // Is attached to the level
  uint64_t is_auto_equip_done                           : 1 {}; // Has initially auto equipped itself
  uint64_t is_being_destroyed                           : 1 {}; // In the process of deleting the thing
  uint64_t is_bouncing                                  : 1 {}; // Is graphically bouncing
  uint64_t is_burnt                                     : 1 {}; // Burnt by ice and cannot move
  uint64_t is_changing_level                            : 1 {}; // Is in the process of changing level
  uint64_t is_dead                                      : 1 {}; // It's dead Jim
  uint64_t is_discorded                                 : 1 {}; // Will attack what normally it would not
  uint64_t is_discovered                                : 1 {}; // Can you see that secret door?
  uint64_t is_drained                                   : 1 {}; // E.g. enchant or skillstone used up
  uint64_t is_dying                                     : 1 {}; // Is currently in the throes of death
  uint64_t is_facing_left                               : 1 {}; // It's in the process of dying
  uint64_t is_fadeup                                    : 1 {}; // For text that fades upwards
  uint64_t is_falling                                   : 1 {}; // Falling to a new level
  uint64_t is_floating_                                 : 1 {}; // Updated per tick
  uint64_t is_frozen                                    : 1 {}; // Frozen by ice and cannot move
  uint64_t is_hidden                                    : 1 {}; // Carried perhaps and hence not visible
  uint64_t is_hunger_level_gorged                       : 1 {}; // Hunger levels
  uint64_t is_hunger_level_hungry                       : 1 {}; // Hunger levels
  uint64_t is_hunger_level_satiated                     : 1 {}; // Hunger levels
  uint64_t is_hunger_level_starving                     : 1 {}; // Hunger levels
  uint64_t _is_immune_to_acid                           : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_blinding                       : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_cold                           : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_confusion                      : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_electricity                    : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_entrancement                   : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_fire                           : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_holy_damage                    : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_lightning                      : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_magic_drain                    : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_necrosis                       : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_negation                       : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_non_magical_weapons            : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_paralysis                      : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_poison                         : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_spell_of_beckoning             : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_spell_of_holding               : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_spell_of_repulsion             : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_spell_of_sanctuary             : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_spell_of_slowness              : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_spiderwebs                     : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_stamina_drain                  : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_teleport_attack                : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_vorpal_weapons                 : 1 {}; // Can be removed by negation
  uint64_t _is_immune_to_water                          : 1 {}; // Can be removed by negation
  uint64_t is_invisible_                                : 1 {}; // Updated per tick
  uint64_t is_jumping                                   : 1 {}; // Is mid jump
  uint64_t is_key_in_lock                               : 1 {}; // Key stuck in rusty lock?
  uint64_t is_minion_set                                : 1 {}; // Overrides is_minion in template
  uint64_t is_moving                                    : 1 {}; // Is currently moving tiles
  uint64_t is_open                                      : 1 {}; // Door or chest is open
  uint64_t is_raging_currently                          : 1 {}; // Is raging currently?
  uint64_t is_resurrected                               : 1 {}; // Has finished resurrecting
  uint64_t is_resurrecting                              : 1 {}; // Is currently resurrecing
  uint64_t is_resurrection_blocked                      : 1 {}; // Blocked from resurrection
  uint64_t is_ring2                                     : 1 {}; // For 2nd rings
  uint64_t is_scheduled_for_death                       : 1 {}; // Will die in next game loop
  uint64_t is_scheduled_for_gc                          : 1 {}; // Scheduled for garbage cleanup
  uint64_t is_scheduled_for_jump_end                    : 1 {}; // Particle for jumping is present
  uint64_t is_seen_by_player_msg_shown                  : 1 {}; // Seen by player message
  uint64_t is_sleeping                                  : 1 {}; // Zzz
  uint64_t is_teleporting                               : 1 {}; // Mid teleport
  uint64_t is_the_grid_                                 : 1 {}; // The backbone of the game. cached for speed
  uint64_t is_the_player                                : 1 {}; // Brave player
  uint64_t is_visible_to_player                         : 1 {}; // Can be seen by the player
  uint64_t is_waiting                                   : 1 {}; // Is waiting on this tick
  uint64_t is_waiting_to_ascend_dungeon                 : 1 {}; // Temporary state while changing levels
  uint64_t is_waiting_to_ascend_sewer                   : 1 {}; // Temporary state while changing levels
  uint64_t is_waiting_to_descend_dungeon                : 1 {}; // Temporary state while changing levels
  uint64_t is_waiting_to_descend_sewer                  : 1 {}; // Temporary state while changing levels
  uint64_t is_waiting_to_leave_level_has_completed_fall : 1 {}; // Has fallen to the next level
  uint64_t is_wounded_msg                               : 1 {}; // Avoid duplicate messages
  uint64_t was_frozen                                   : 1 {}; // Was frozen at the start of the tick
  // end sort marker1 }

  //
  // These are flags used to make sure we set or unset flags onto the level only once.
  //

  // begin sort marker2 {
  uint64_t i_set_is_able_to_amplify_footsteps   : 1 {};
  uint64_t i_set_is_able_to_dampen_footsteps    : 1 {};
  uint64_t i_set_is_acid                        : 1 {};
  uint64_t i_set_is_ascend_dungeon              : 1 {};
  uint64_t i_set_is_ascend_sewer                : 1 {};
  uint64_t i_set_is_attackable_by_monst         : 1 {};
  uint64_t i_set_is_attackable_by_player        : 1 {};
  uint64_t i_set_is_barrel                      : 1 {};
  uint64_t i_set_is_basalt                      : 1 {};
  uint64_t i_set_is_block_of_crystal            : 1 {};
  uint64_t i_set_is_block_of_ice                : 1 {};
  uint64_t i_set_is_brazier                     : 1 {};
  uint64_t i_set_is_bridge                      : 1 {};
  uint64_t i_set_is_burnable                    : 1 {}; // may produce a flame
  uint64_t i_set_is_carnivorous_plant           : 1 {};
  uint64_t i_set_is_chasm                       : 1 {};
  uint64_t i_set_is_combustible                 : 1 {}; // may not produce a flame
  uint64_t i_set_is_corpse                      : 1 {};
  uint64_t i_set_is_corridor                    : 1 {};
  uint64_t i_set_is_cursor_path_blocker         : 1 {};
  uint64_t i_set_is_cursor_path_hazard          : 1 {};
  uint64_t i_set_is_deep_water                  : 1 {};
  uint64_t i_set_is_descend_dungeon             : 1 {};
  uint64_t i_set_is_descend_sewer               : 1 {};
  uint64_t i_set_is_dirt                        : 1 {};
  uint64_t i_set_is_door                        : 1 {};
  uint64_t i_set_is_enchantstone                : 1 {};
  uint64_t i_set_is_engulfer                    : 1 {};
  uint64_t i_set_is_fire                        : 1 {};
  uint64_t i_set_is_floor                       : 1 {};
  uint64_t i_set_is_foliage                     : 1 {};
  uint64_t i_set_is_food                        : 1 {};
  uint64_t i_set_is_fungus                      : 1 {};
  uint64_t i_set_is_fungus_edible               : 1 {};
  uint64_t i_set_is_fungus_healing              : 1 {};
  uint64_t i_set_is_fungus_poison               : 1 {};
  uint64_t i_set_is_fungus_withered             : 1 {};
  uint64_t i_set_is_gas_blocker                 : 1 {};
  uint64_t i_set_is_gas_explosion_blocker       : 1 {};
  uint64_t i_set_is_gold                        : 1 {};
  uint64_t i_set_is_grass_dry                   : 1 {};
  uint64_t i_set_is_grass_wet                   : 1 {};
  uint64_t i_set_is_green_blood                 : 1 {};
  uint64_t i_set_is_hazard                      : 1 {};
  uint64_t i_set_is_heavy                       : 1 {};
  uint64_t i_set_is_key                         : 1 {};
  uint64_t i_set_is_lava                        : 1 {};
  uint64_t i_set_is_light_blocker               : 1 {};
  uint64_t i_set_is_light_blocker_for_monst     : 1 {};
  uint64_t i_set_is_mob                         : 1 {};
  uint64_t i_set_is_monst                       : 1 {};
  uint64_t i_set_is_necrotic_danger_level       : 1 {};
  uint64_t i_set_is_obs_destructable            : 1 {};
  uint64_t i_set_is_obs_jump_end                : 1 {};
  uint64_t i_set_is_obs_shoving                 : 1 {};
  uint64_t i_set_is_obs_spawn                   : 1 {};
  uint64_t i_set_is_obs_spawn_monst             : 1 {};
  uint64_t i_set_is_obs_wall_or_door            : 1 {};
  uint64_t i_set_is_obs_when_dead               : 1 {};
  uint64_t i_set_is_ooze                        : 1 {};
  uint64_t i_set_is_poisonous_danger_level      : 1 {};
  uint64_t i_set_is_portal                      : 1 {};
  uint64_t i_set_is_potion                      : 1 {};
  uint64_t i_set_is_red_blood                   : 1 {};
  uint64_t i_set_is_ring                        : 1 {};
  uint64_t i_set_is_ripple                      : 1 {};
  uint64_t i_set_is_rock                        : 1 {};
  uint64_t i_set_is_secret_door                 : 1 {};
  uint64_t i_set_is_shallow_water               : 1 {};
  uint64_t i_set_is_shovable                    : 1 {};
  uint64_t i_set_is_skillstone                  : 1 {};
  uint64_t i_set_is_smoke                       : 1 {};
  uint64_t i_set_is_spectral_blade              : 1 {};
  uint64_t i_set_is_spellbook                   : 1 {};
  uint64_t i_set_is_spell_of_holding_barrier    : 1 {};
  uint64_t i_set_is_spell_of_protection_barrier : 1 {};
  uint64_t i_set_is_spell_of_sanctuary_barrier  : 1 {};
  uint64_t i_set_is_spiderweb                   : 1 {};
  uint64_t i_set_is_staff                       : 1 {};
  uint64_t i_set_is_steam                       : 1 {};
  uint64_t i_set_is_sticky                      : 1 {};
  uint64_t i_set_is_tentacle                    : 1 {};
  uint64_t i_set_is_torch                       : 1 {};
  uint64_t i_set_is_trap                        : 1 {};
  uint64_t i_set_is_treasure_type               : 1 {};
  uint64_t i_set_is_wall                        : 1 {};
  uint64_t i_set_noise_blocker                  : 1 {};
  uint64_t i_set_water                          : 1 {};
  // end sort marker2 }

  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////
  // Fields not worth saving
  uint64_t ai_tried_to_wander    : 1 {}; // tried to wander
  uint64_t debug                 : 1 {};
  uint64_t has_external_particle : 1 {}; // current in motion particle
  uint64_t has_internal_particle : 1 {}; // current in motion particle
  uint64_t inited_tiles          : 1 {};
  uint64_t is_being_dropped      : 1 {};
  uint64_t is_being_thrown       : 1 {};
  uint64_t is_being_used_to_tame : 1 {};
  uint64_t is_being_used         : 1 {};
  uint64_t is_blitted            : 1 {};
  uint64_t is_in_lava            : 1 {}; // Updated on level pop/push
  uint64_t is_in_ooze            : 1 {}; // Updated on level pop/push
  uint64_t is_in_water           : 1 {}; // Updated on level pop/push
#ifdef ENABLE_DEBUG_THING_SER
  std::string debug_str;
#endif

public:
  //
  // Walk all items and bags to get the items
  //
  std::list< Thingp > amulet_list(void);
  std::list< Thingp > armor_list(void);
  std::list< Thingp > boots_list(void);
  std::list< Thingp > cloak_list(void);
  std::list< Thingp > food_list(void);
  std::list< Thingp > gauntlet_list(void);
  std::list< Thingp > helmet_list(void);
  std::list< Thingp > carried_item_only_list(void);
  std::list< Thingp > carried_and_equipped_item_list(void);
  std::list< Thingp > ring_list(void);
  std::list< Thingp > shield_list(void);
  std::list< Thingp > treasure_list(void);
  std::list< Thingp > staff_list(void);
  std::list< Thingp > ranged_weapon_list(void);
  std::list< Thingp > weapon_list(void);

  std::vector< Thingp > amulet_vector(void);
  std::vector< Thingp > armor_vector(void);
  std::vector< Thingp > boots_vector(void);
  std::vector< Thingp > cloak_vector(void);
  std::vector< Thingp > food_vector(void);
  std::vector< Thingp > gauntlet_vector(void);
  std::vector< Thingp > helmet_vector(void);
  std::vector< Thingp > carried_item_only_vector(void);
  std::vector< Thingp > carried_and_equipped_item_vector(void);
  std::vector< Thingp > ring_vector(void);
  std::vector< Thingp > shield_vector(void);
  std::vector< Thingp > treasure_vector(void);
  std::vector< Thingp > staff_vector(void);
  std::vector< Thingp > ranged_weapon_vector(void);
  std::vector< Thingp > weapon_vector(void);

  ThingShoved try_to_shove(Thingp it, point delta, ShoveOptions = {});
  ThingShoved try_to_shove(point future_pos);
  ThingShoved try_to_shove_into_hazard(Thingp it, point delta);

  ThingId on_fire_anim_id(void);
  ThingId on_fire_anim_id_set(ThingId);

  ThingId equip_id(int equip);
  ThingId equip_id_carry_anim(int equip);
  ThingId equip_id_use_anim(int equip);

  void    equip_id_set(ThingId, int equip);
  ThingId equip_id_carry_anim_set(ThingId, int equip);
  ThingId equip_id_use_anim_set(ThingId, int equip);

  ThingId bodypart_id_get(int bodypart);
  void    bodypart_id_set(ThingId, int bodypart);

  ThingDangerLevel danger_level(Thingp it);

  Thingp bag_what_is_at(point pos);
  Thingp best_shoot_at_target_get(void);
  Thingp spawn_next_to(const std::string &what);
  Thingp spawn_next_to_or_on_monst(const std::string &what);
  Thingp best_visible_target_get(void);
  Thingp bodypart_carry_anim(int bodypart);
  Thingp bodypart_get(int bodypart);
  Thingp buff_find(const std::string &);
  Thingp debuff_find(const std::string &);
  Thingp equip_carry_anim(int equip);
  Thingp equip_get(int equip);
  Thingp equip_use_anim(int equip);
  Thingp immediate_mob(void);
  Thingp immediate_owner(void);
  Thingp immediate_spawner(void);
  Thingp in_the_way_for_casting(const point s, const point e, int x, int y);
  Thingp in_the_way_for_jumping(const point s, const point e, int x, int y);
  Thingp in_the_way_for_shooting(const point s, const point e, int x, int y);
  Thingp in_the_way_for_throwing(const point s, const point e, int x, int y);
  Thingp item_targeted_use_at(Thingp wand, point at);
  Thingp item_targeted_use_at(Thingp wand, Thingp target);
  Thingp leader(void);
  Thingp most_dangerous_adjacent_thing(void);
  Thingp most_dangerous_visible_thing(void);
  Thingp projectile_shoot_at(Thingp item, const std::string &proj_name, point at);
  Thingp projectile_shoot_at(Thingp item, const std::string &proj_name, Thingp target);
  Thingp laser_shoot_at(Thingp item, const std::string &laser_name, point at, UseOptions &);
  Thingp laser_shoot_at(Thingp item, const std::string &laser_name, Thingp target, UseOptions &);
  Thingp laser_reflect(Thingp item, const std::string &laser_name, Thingp target, UseOptions &);
  Thingp spawn_at(const std::string &what);
  Thingp spawn_at(const std::string &what, point p);
  Thingp spawn_minion_at_my_position(const std::string &what);
  Thingp spawn_minion_next_to(const std::string &what);
  Thingp spawn_owned_thing_at_my_position(const std::string &what);
  Thingp top_mob(void);
  Thingp top_owner_internal(void);
  Thingp top_owner(void);
  Thingp top_spawner(void);

  std::vector< Thingp > in_the_way_for_jumping(const point s, const point e, size_t max_elems = 0);
  std::vector< Thingp > in_the_way_for_shooting(const point s, const point e, size_t max_elems = 0);
  std::vector< Thingp > in_the_way_for_throwing(const point s, const point e, size_t max_elems = 0);
  std::vector< Thingp > in_the_way_for_casting(const point s, const point e, size_t max_elems = 0);

  // begin sort marker3 {
  bool ai_blocked_completely(void);
  bool ai_blocked(void);
  bool ai_choose_avoid_goals(std::multiset< Goal > &avoid_goals, const Goal &goal);
  bool ai_choose_immediately_adjacent_goal(int dx, int dy);
  bool ai_choose_immediately_adjacent_goal(void);
  bool ai_choose_wander(point &nh);
  bool ai_create_on_fire_path(point &nh, const point start, const point end);
  bool ai_create_path(point &nh, const point start, const point end);
  bool ai_create_path_to_goal(int minx, int miny, int maxx, int maxy, int search_type = 0);
  bool ai_create_path_to_single_goal_do(int, int, int, int, const Goal &goal, const struct Dmap_ *saved_dmap, bool);
  bool ai_create_path_to_single_goal(int, int, int, int, const Goal &goal, const struct Dmap_ *saved_dmap);
  bool ai_escape(void);
  bool ai_on_fire_choose_target(point &nh);
  bool ai_on_fire(void);
  bool ai_tick(bool recursing = false);
  bool ai_wander(void);
  bool any_adjacent_monst(void);
  bool any_unfriendly_monst_visible(void);
  bool ascend_dungeon(bool force = false, point3d next_level = point3d(0, 0, 0));
  bool ascend_dungeon_tick(void);
  bool ascend(int z);
  bool ascend_sewer_tick(void);
  bool ascend_sewer(void);
  bool attack(point future_pos);
  bool attack(Thingp victim, ThingAttackOptionsp);
  bool attempt_to_tame_with(point p, Thingp what);
  bool attempt_to_tame_with(Thingp it, Thingp what);
  bool bag_add_test(Thingp);
  bool bag_add(Thingp);
  bool bag_can_place_anywhere(Thingp item, point &pos);
  bool bag_can_place_at(Thingp item, point pos);
  bool bag_compress(void);
  bool bag_contains(Thingp item);
  bool bag_place_at(Thingp item, point pos);
  bool bag_remove_at(Thingp item, point pos);
  bool bag_remove(Thingp);
  bool beckon(Thingp target);
  bool blit_outline_should_be_shown(color &outline_color);
  bool bodypart_add(Thingp w, int bodypart);
  bool bounce(float bounce_height, float bounce_fade, ts_t ms, int bounce_count);
  bool buff_add_if_not_found(Tpp what);
  bool buff_add(Thingp it);
  bool buff_add(Tpp what);
  bool buff_aquatic(void);
  bool buffbox_id_insert(Thingp what);
  bool buffbox_id_remove(Thingp what);
  bool buff_floating(void);
  bool buff_immune_to_cold(void);
  bool buff_immune_to_fire(void);
  bool buff_immune_to_holy_damage(void);
  bool buff_immune_to_lightning(void);
  bool buff_immune_to_magic_drain(void);
  bool buff_immune_to_necrosis(void);
  bool buff_immune_to_negation(void);
  bool buff_immune_to_poison(void);
  bool buff_immune_to_stamina_drain(void);
  bool buff_immune_to_teleport_attack(void);
  bool buff_immune_to_water(void);
  bool buff_invisible(void);
  bool buff_remove(Thingp it);
  bool buff_remove(Tpp what);
  bool buff_slippery(void);
  bool buff_use(Thingp it);
  bool can_detect(Thingp);
  bool can_eat(const Thingp it);
  bool can_eat_something(void);
  bool can_enchant_something(void);
  bool can_learn_a_skill(void);
  bool can_learn_a_spell(void);
  bool cannot_avoid(Thingp attacker);
  bool can_see_is_invisible(Thingp);
  bool carrying_anything(void);
  bool carry(Thingp w, CarryOptions);
  bool check_anything_to_carry(CarryOptions);
  bool close_door(Thingp door);
  bool close(Thingp it);
  bool close(void);
  bool collision_add_candidates(Thingp it, point future_pos, int x, int y, int dx, int dy);
  bool collision_check_and_handle_at(point future_pos, ThingAttackOptionsp);
  bool collision_check_and_handle_at(ThingAttackOptionsp);
  bool collision_check_and_handle_nearby(point future_pos, ThingAttackOptionsp);
  bool collision_check_and_handle(point future_pos, ThingAttackOptionsp, float radius);
  bool collision_check_and_handle(Thingp it, point future_pos, int x, int y, int dx, int dy);
  bool collision_check_do(void);
  bool collision_check_only(point future_pos);
  bool collision_check_only(Thingp it, int x, int y, int dx, int dy);
  bool collision_check_only(Thingp it, point future_pos);
  bool collision_check_only(void);
  bool collision_find_best_target(ThingAttackOptionsp);
  bool collision_obstacle(point);
  bool collision_obstacle(Thingp);
  bool coords_get(point &blit_tl, point &blit_br, point &pre_blit_tl, point &pre_blit_br, Tilep &tile, bool refl);
  bool d20_ge(int stat_total, int dice_roll_to_exceed);
  bool debuff_add_if_not_found(Tpp what);
  bool debuff_add(Thingp it);
  bool debuff_add(Tpp what);
  bool debuffbox_id_insert(Thingp what);
  bool debuffbox_id_remove(Thingp what);
  bool debuff_remove(Thingp it);
  bool debuff_remove(Tpp what);
  bool debuff_use(Thingp it);
  bool descend_dungeon(bool force = false, point3d next_level = point3d(0, 0, 0));
  bool descend_dungeon_tick(void);
  bool descend_sewer_tick(void);
  bool descend_sewer(void);
  bool describe_when_hovered_over_in_rightbar(void);
  bool describe_when_hovering_over(void);
  bool discovered(void);
  bool drop_from_ether(Thingp w);
  bool drop_into_ether(Thingp w);
  bool drop(Thingp w);
  bool drop(Thingp w, DropOptions);
  bool drop(Thingp w, Thingp target, DropOptions);
  bool eat_something(void);
  bool eat(Thingp it);
  bool enchant_random_item_with_stone(void);
  bool enchant_without_stone(Thingp);
  bool enchant_with_stone(Thingp);
  bool equipped_anything(void);
  bool equip(Thingp w, int equip);
  bool equip_use(bool forced, int equip, ThingAttackOptionsp);
  bool equip_use_may_attack(int equip);
  bool equip_use_must_attack(int equip);
  bool fall_to_next_level(void);
  bool fall(void);
  bool fire_choose_target(Thingp item);
  bool has_skill(Tpp skill);
  bool has_spell(Tpp spell);
  bool has_temperature(void);
  bool health_boost_would_occur(int v);
  bool hunger_boost_would_occur(int v);
  bool idle_check(void);
  bool if_matches_then_dead(const std::string &what, const point p);
  bool initial_temperature_is_set(void);
  bool inventory_shortcuts_insert(Thingp what);
  bool inventory_shortcuts_remove(Thingp what, DropOptions);
  bool inventory_shortcuts_remove(Thingp what, Thingp target, DropOptions);
  bool is_adjacent(const Thingp);
  bool is_attacker(Thingp it);
  bool is_blocking_terrain(const Thingp it);
  bool is_bloodied(void);
  bool is_carrying_an_item(void);
  bool is_carrying_treasure(void);
  bool is_disliked_by_me(const point p);
  bool is_disliked_by_me(const Thingp it);
  bool is_edible(const Thingp it);
  bool is_enemy(Thingp it);
  bool is_equipped(Thingp item);
  bool is_floating_currently(void);
  bool is_floating(void);
  bool is_friend(Thingp it);
  bool is_hated_by_me(const point p);
  bool is_hated_by_me(const Thingp it);
  bool is_invisible_currently(void);
  bool is_invisible(void);
  bool is_obs_ai_for_me(point);
  bool is_obs_ai(fpoint);
  bool is_obs_ai(Thingp);
  bool is_on_fire(void);
  bool is_player_bodypart(Thingp item);
  bool is_raging_set(bool);
  bool is_raging(void);
  bool is_shielded_from_attack_by(Thingp hitter);
  bool is_state_sleeping(void);
  bool is_stuck_check(void);
  bool is_stuck_currently(void);
  bool is_target_select(Thingp item);
  bool is_to_be_avoided(Thingp attacker);
  bool item_choose_target(Thingp item, Thingp victim = nullptr);
  bool jump_attack(Thingp it = nullptr);
  bool laser_anim_exists(void);
  bool laser_choose_target(Thingp item, Thingp victim = nullptr);
  bool learn_random_skill(void);
  bool learn_random_spell(void);
  bool map_offset_coords_get(point &blit_tl, point &blit_br, Tilep &tile, bool reflection);
  bool map_treasure_available(void);
  bool matches(const std::string &what);
  bool move_away_from_entrance(void);
  bool move_no_shove_attack_allowed(point future_pos);
  bool move_no_shove_no_attack(point future_pos);
  bool move(point to);
  bool move(point to, uint8_t u, uint8_t d, uint8_t l, uint8_t r, uint8_t att, uint8_t idl, ThingAttackOptionsp);
  bool move_to_or_attack_check_only(const point nh);
  bool move_to_or_attack(const point);
  bool move_to_or_escape_check_only(const point nh);
  bool move_to_or_escape(const point);
  bool move_to_try(const point, const bool escaping, bool check_only);
  bool nat_att(Thingp victim);
  bool on_fire_set(const std::string &why);
  bool on_tick(void);
  bool on_tick_when_activated(void);
  bool on_tick_when_deactivated(void);
  bool on_want_to_shoot_at(Thingp hitter);
  bool open_door(Thingp door);
  bool open(Thingp it);
  bool open(void);
  bool particle_anim_exists(void);
  bool place(const std::string &what, const point p);
  bool player_cursor_path_pop_first_move(ThingMoveReason);
  bool player_is_player_is_ready_for_messages(std::string &why);
  bool player_is_player_is_ready_for_messages(void);
  bool player_is_ready_for_popups(void);
  bool player_or_monst_path_pop_next_move(ThingMoveReason);
  bool possible_to_attack_at(point at);
  bool possible_to_attack(const Thingp it);
  bool projectile_anim_exists(void);
  bool projectile_choose_target(Thingp item, Thingp victim = nullptr);
  bool raging_set(bool val);
  bool repulse(Thingp target);
  bool resurrect_forced(void);
  bool resurrect(void);
  bool same_leader_or_owner(Thingp it);
  bool same_mob(Thingp it);
  bool shoot_at_and_choose_target(Thingp, UseOptions &);
  bool shoot_at_target(void);
  bool shoot_at(Thingp item, Thingp target);
  bool shoot_at(Thingp target);
  bool shove_ok(point future_pos);
  bool skill_add(Thingp it);
  bool skill_add(Tpp what);
  bool skillbox_id_insert(Thingp what);
  bool skillbox_id_remove(Thingp what);
  bool skill_remove(Thingp it);
  bool skill_use(Thingp it);
  bool spawn_darkness_around_thing(int radius);
  bool spawn_gas_confusion_around_thing(int radius);
  bool spawn_gas_explosive_around_thing(int radius);
  bool spawn_gas_healing_around_thing(int radius);
  bool spawn_gas_paralysis_around_thing(int radius);
  bool spawn_gas_poison_around_thing(int radius);
  bool spawn_radius_range(const std::string &what, int rad_min, int rad_max);
  bool spawn_radius_range(Thingp parent, Thingp target, const std::string &what, int rad_min, int rad_max);
  bool spawn_set_fire_to_things_around_me(const std::string &what, int radius);
  bool spawn_things_around_me(const std::string &what, int radius);
  bool spell_add(Thingp it);
  bool spell_add(Tpp what);
  bool spellbox_id_insert(Thingp what);
  bool spellbox_id_remove(Thingp what);
  bool spell_can_use(Thingp);
  bool spell_cast_at(Thingp w, Thingp target);
  bool spell_cast(Thingp it);
  bool spell_remove(Thingp it);
  bool state_idle(Thingp threat, int minx, int miny, int maxx, int maxy);
  bool state_moving(void);
  bool state_open_inventory(void);
  bool state_repack_inventory(void);
  bool state_resting(bool &do_something, bool &wait);
  bool state_sleeping(bool &do_something, bool &wait);
  bool state_using_enchantstone(void);
  bool state_using_skillstone(void);
  bool state_using_spellbook(void);
  bool steal_item_from(Thingp);
  bool steal_treasure_from(Thingp);
  bool teleport_carefree(TeleportOptions, point to);
  bool teleport_carefree(TeleportOptions, point to, bool *too_far);
  bool teleport_carefully(TeleportOptions, point to);
  bool teleport_carefully(TeleportOptions, point to, bool *too_far);
  bool teleport_portal_find_target(point &target);
  bool teleport_portal(Thingp portal);
  bool teleport_randomly_away_from_player(TeleportOptions);
  bool teleport_randomly(TeleportOptions, float max_distance = 0.0);
  bool teleport_randomly_towards_player(TeleportOptions);
  bool teleport_self(TeleportOptions, Thingp it = nullptr);
  bool teleport(TeleportOptions, point to, bool *too_far);
  bool temperature_max_is_set(void);
  bool temperature_min_is_set(void);
  bool thing_check_for_cold_dmg(void);
  bool thing_check_for_heat_dmg(void);
  bool thing_sound_play_channel(int chan, const std::string &alias);
  bool thing_sound_play(const std::string &alias);
  bool thing_use_distance_is_ok(Thingp what, point target);
  bool throw_at(Thingp w, Thingp target);
  bool throw_item_choose_target(Thingp item);
  bool tile_is_offscreen(void);
  bool too_far_from_leader(point p);
  bool too_far_from_leader(point p, float delta);
  bool too_far_from_leader(void);
  bool too_far_from_mob(point p);
  bool too_far_from_mob(point p, float delta);
  bool too_far_from_mob(void);
  bool torch_tick(void);
  bool try_harder_to_jump(void);
  bool try_harder_to_teleport(TeleportOptions);
  bool try_to_carry_if_worthwhile_dropping_items_if_needed(Thingp it, CarryOptions);
  bool try_to_carry(Thingp w, CarryOptions);
  bool try_to_enchant_items(void);
  bool try_to_escape(void);
  bool try_to_jump_away_from_player(void);
  bool try_to_jump_carefree(point to);
  bool try_to_jump_carefree(point to, bool *too_far);
  bool try_to_jump_carefully(point to);
  bool try_to_jump_carefully(point to, bool *too_far);
  bool try_to_jump(point to, bool carefully, bool *too_far);
  bool try_to_jump_towards_player(void);
  bool try_to_jump(void);
  bool try_to_use_amulet(void);
  bool try_to_use_armor(void);
  bool try_to_use_boots(void);
  bool try_to_use_cloak(void);
  bool try_to_use_gauntlet(void);
  bool try_to_use_helmet(void);
  bool try_to_use_rings(void);
  bool try_to_use_shield(void);
  bool try_to_use_weapon(void);
  bool unequip(const char *why, int equip, bool allowed_to_recarry);
  bool unequip_me_from_owner(const char *why, bool allowed_to_recarry);
  bool use(Thingp w, UseOptions &);
  bool victim_attack_best_at(int equip, ThingAttackOptionsp);
  bool victim_attack_best(int equip, ThingAttackOptionsp);
  bool victim_attack_best_(int equip, ThingAttackOptionsp);
  bool victim_attack_swing(int equip, Thingp best, point best_hit_at, ThingAttackOptionsp);
  bool wake(const std::string &reason);
  bool will_avoid_monst(const point p);
  bool will_avoid_monst(const Thingp it);
  bool will_prefer_terrain(const Thingp it);
  bool worth_eating(const Thingp it);
  // end sort marker3 }

  std::vector< std::string > on_get_text_description_long(void);

  const Dice &dmg_water_dice(void);
  const Dice &dmg_acid_dice(void);
  const Dice &dmg_cold_dice(void);
  const Dice &dmg_crush_dice(void);
  const Dice &dmg_impact_dice(void);
  const Dice &dmg_missile_dice(void);
  const Dice &dmg_digest_dice(void);
  const Dice &dmg_stamina_dice(void);
  const Dice &dmg_magic_drain_dice(void);
  const Dice &dmg_holy_dice(void);
  const Dice &dmg_energy_dice(void);
  const Dice &dmg_negation_dice(void);
  const Dice &dmg_fire_dice(void);
  const Dice &dmg_heat_dice(void);
  const Dice &dmg_drown_dice(void);
  const Dice &dmg_bite_dice(void);
  const Dice &dmg_claw_dice(void);
  const Dice &dmg_lightning_dice(void);
  const Dice &dmg_melee_dice(void);
  const Dice &dmg_nat_att_dice(void);
  const Dice &dmg_necrosis_dice(void);
  const Dice &dmg_poison_dice(void);

  const Dice &gold_value_dice(void);
  const Dice &health_initial_dice(void);
  const Dice &health_regenerate_amount_dice(void);
  const Dice &lifespan_dice(void);
  const Dice &nutrition_dice(void);
  const Dice &on_idle_tick_freq_dice(void);
  const Dice &spawn_group_size_dice(void);
  const Dice &resurrect_dice(void);

  const ThingId &immediate_mob_id(void);
  const ThingId &leader_id(void);
  const ThingId &immediate_owner_id(void);
  const ThingId &immediate_spawner_id(void);
  const ThingId &top_owner_id(void);
  const ThingId &mob_id_set(const ThingId &v);
  const ThingId &leader_id_set(const ThingId &v);
  const ThingId &owner_id_set(const ThingId &v);
  const ThingId &spawner_set(const ThingId &v);

  const Tpp tp_slow(void);

  //
  // It's used a lot, so inline candidate
  //
  const Tpp tp(void)
  {
    if (likely(mytp != nullptr)) {
      return mytp;
    }

    return tp_slow();
  }

  const Tpp tp_or_update(void);

  const fpoint &interpolated_at_get(void);

  // begin sort marker4 {
  const std::string danger_level_str(Thingp); // Cannot return reference
  const std::string dmg_acid_dice_str(void);
  const std::string dmg_bite_dice_str(void);
  const std::string dmg_claw_dice_str(void);
  const std::string dmg_cold_dice_str(void);
  const std::string dmg_crush_dice_str(void);
  const std::string dmg_digest_dice_str(void);
  const std::string dmg_drown_dice_str(void);
  const std::string dmg_energy_dice_str(void);
  const std::string dmg_fire_dice_str(void);
  const std::string dmg_heat_dice_str(void);
  const std::string dmg_holy_dice_str(void);
  const std::string dmg_impact_dice_str(void);
  const std::string dmg_lightning_dice_str(void);
  const std::string dmg_magic_drain_dice_str(void);
  const std::string dmg_melee_dice_str(void);
  const std::string dmg_missile_dice_str(void);
  const std::string dmg_nat_att_dice_str(void);
  const std::string dmg_necrosis_dice_str(void);
  const std::string dmg_negation_dice_str(void);
  const std::string dmg_poison_dice_str(void);
  const std::string dmg_stamina_dice_str(void);
  const std::string dmg_water_dice_str(void);
  const std::string text_description_long2(void);
  const std::string text_description_long3(void);
  const std::string text_description_long4(void);
  const std::string text_description_long5(void);
  const std::string text_description_long(void);
  const std::string text_long_name(size_t max_len = 0);
  const std::string text_short_name(size_t max_len = 0);
  // end sort marker4 {

  // begin sort marker5 {
  const std::string &dead_reason_get(void);
  const std::string &dmg_nat_att_type(void);
  const std::string &equip_carry_anim(void);
  const std::string &gfx_anim_use(void);
  const std::string &gfx_targeted_laser(void);
  const std::string &gfx_targeted_projectile(void);
  const std::string &gold_value_dice_str(void);
  const std::string &health_initial_dice_str(void);
  const std::string &health_regenerate_amount_dice_str(void);
  const std::string &is_allied_with(void);
  const std::string &lifespan_dice_str(void);
  const std::string &light_color(void);
  const std::string &msg_get(void);
  const std::string &name(void);
  const std::string &nutrition_dice_str(void);
  const std::string &on_activated_do(void);
  const std::string &on_attacking_dmg_acid_do(void);
  const std::string &on_attacking_dmg_bite_do(void);
  const std::string &on_attacking_dmg_claw_do(void);
  const std::string &on_attacking_dmg_cold_do(void);
  const std::string &on_attacking_dmg_crush_do(void);
  const std::string &on_attacking_dmg_digest_do(void);
  const std::string &on_attacking_dmg_drown_do(void);
  const std::string &on_attacking_dmg_energy_do(void);
  const std::string &on_attacking_dmg_fire_do(void);
  const std::string &on_attacking_dmg_heat_do(void);
  const std::string &on_attacking_dmg_holy_do(void);
  const std::string &on_attacking_dmg_impact_do(void);
  const std::string &on_attacking_dmg_lightning_do(void);
  const std::string &on_attacking_dmg_magic_drain_do(void);
  const std::string &on_attacking_dmg_melee_do(void);
  const std::string &on_attacking_dmg_missile_do(void);
  const std::string &on_attacking_dmg_nat_att_do(void);
  const std::string &on_attacking_dmg_necrosis_do(void);
  const std::string &on_attacking_dmg_negation_do(void);
  const std::string &on_attacking_dmg_poison_do(void);
  const std::string &on_attacking_dmg_stamina_do(void);
  const std::string &on_attacking_dmg_stat_att_do(void);
  const std::string &on_attacking_dmg_stat_con_do(void);
  const std::string &on_attacking_dmg_stat_str_do(void);
  const std::string &on_attacking_dmg_water_do(void);
  const std::string &on_awake_do(void);
  const std::string &on_born_do(void);
  const std::string &on_close_do(void);
  const std::string &on_death_do(void);
  const std::string &on_death_of_a_follower_do(void);
  const std::string &on_death_of_my_leader_do(void);
  const std::string &on_dropped_do(void);
  const std::string &on_eaten_do(void);
  const std::string &on_eating_do(void);
  const std::string &on_enchant_do(void);
  const std::string &on_enter_do(void);
  const std::string &on_equip_do(void);
  const std::string &on_fall_begin_do(void);
  const std::string &on_fall_do(void);
  const std::string &on_final_use_do(void);
  const std::string &on_get_text_description_long_do(void);
  const std::string &on_hit_and_now_dead_do(void);
  const std::string &on_hit_and_still_alive_do(void);
  const std::string &on_hit_dodge_do(void);
  const std::string &on_idle_tick_freq_dice_str(void);
  const std::string &on_jump_do(void);
  const std::string &on_lifespan_tick_do(void);
  const std::string &on_move_do(void);
  const std::string &on_open_do(void);
  const std::string &on_owner_add_do(void);
  const std::string &on_owner_attack_dmg_acid_do(void);
  const std::string &on_owner_attack_dmg_bite_do(void);
  const std::string &on_owner_attack_dmg_claw_do(void);
  const std::string &on_owner_attack_dmg_cold_do(void);
  const std::string &on_owner_attack_dmg_crush_do(void);
  const std::string &on_owner_attack_dmg_digest_do(void);
  const std::string &on_owner_attack_dmg_drown_do(void);
  const std::string &on_owner_attack_dmg_energy_do(void);
  const std::string &on_owner_attack_dmg_fire_do(void);
  const std::string &on_owner_attack_dmg_heat_do(void);
  const std::string &on_owner_attack_dmg_holy_do(void);
  const std::string &on_owner_attack_dmg_impact_do(void);
  const std::string &on_owner_attack_dmg_lightning_do(void);
  const std::string &on_owner_attack_dmg_magic_drain_do(void);
  const std::string &on_owner_attack_dmg_melee_do(void);
  const std::string &on_owner_attack_dmg_missile_do(void);
  const std::string &on_owner_attack_dmg_nat_att_do(void);
  const std::string &on_owner_attack_dmg_necrosis_do(void);
  const std::string &on_owner_attack_dmg_negation_do(void);
  const std::string &on_owner_attack_dmg_poison_do(void);
  const std::string &on_owner_attack_dmg_stamina_do(void);
  const std::string &on_owner_attack_dmg_stat_att_do(void);
  const std::string &on_owner_attack_dmg_stat_con_do(void);
  const std::string &on_owner_attack_dmg_stat_str_do(void);
  const std::string &on_owner_attack_dmg_water_do(void);
  const std::string &on_owner_rcv_dmg_acid_do(void);
  const std::string &on_owner_rcv_dmg_bite_do(void);
  const std::string &on_owner_rcv_dmg_claw_do(void);
  const std::string &on_owner_rcv_dmg_cold_do(void);
  const std::string &on_owner_rcv_dmg_crush_do(void);
  const std::string &on_owner_rcv_dmg_digest_do(void);
  const std::string &on_owner_rcv_dmg_drown_do(void);
  const std::string &on_owner_rcv_dmg_energy_do(void);
  const std::string &on_owner_rcv_dmg_fire_do(void);
  const std::string &on_owner_rcv_dmg_heat_do(void);
  const std::string &on_owner_rcv_dmg_holy_do(void);
  const std::string &on_owner_rcv_dmg_impact_do(void);
  const std::string &on_owner_rcv_dmg_lightning_do(void);
  const std::string &on_owner_rcv_dmg_magic_drain_do(void);
  const std::string &on_owner_rcv_dmg_melee_do(void);
  const std::string &on_owner_rcv_dmg_missile_do(void);
  const std::string &on_owner_rcv_dmg_nat_att_do(void);
  const std::string &on_owner_rcv_dmg_necrosis_do(void);
  const std::string &on_owner_rcv_dmg_negation_do(void);
  const std::string &on_owner_rcv_dmg_poison_do(void);
  const std::string &on_owner_rcv_dmg_stamina_do(void);
  const std::string &on_owner_rcv_dmg_stat_att_do(void);
  const std::string &on_owner_rcv_dmg_stat_con_do(void);
  const std::string &on_owner_rcv_dmg_stat_str_do(void);
  const std::string &on_owner_rcv_dmg_water_do(void);
  const std::string &on_owner_unset_do(void);
  const std::string &on_polymorphed_do(void);
  const std::string &on_pre_teleport_do(void);
  const std::string &on_rcv_dmg_acid_do(void);
  const std::string &on_rcv_dmg_bite_do(void);
  const std::string &on_rcv_dmg_claw_do(void);
  const std::string &on_rcv_dmg_cold_do(void);
  const std::string &on_rcv_dmg_crush_do(void);
  const std::string &on_rcv_dmg_digest_do(void);
  const std::string &on_rcv_dmg_drown_do(void);
  const std::string &on_rcv_dmg_energy_do(void);
  const std::string &on_rcv_dmg_fire_do(void);
  const std::string &on_rcv_dmg_heat_do(void);
  const std::string &on_rcv_dmg_holy_do(void);
  const std::string &on_rcv_dmg_impact_do(void);
  const std::string &on_rcv_dmg_lightning_do(void);
  const std::string &on_rcv_dmg_magic_drain_do(void);
  const std::string &on_rcv_dmg_melee_do(void);
  const std::string &on_rcv_dmg_missile_do(void);
  const std::string &on_rcv_dmg_nat_att_do(void);
  const std::string &on_rcv_dmg_necrosis_do(void);
  const std::string &on_rcv_dmg_negation_do(void);
  const std::string &on_rcv_dmg_poison_do(void);
  const std::string &on_rcv_dmg_stamina_do(void);
  const std::string &on_rcv_dmg_stat_att_do(void);
  const std::string &on_rcv_dmg_stat_con_do(void);
  const std::string &on_rcv_dmg_stat_str_do(void);
  const std::string &on_rcv_dmg_water_do(void);
  const std::string &on_resting_do(void);
  const std::string &on_stealing_do(void);
  const std::string &on_stuck_do(void);
  const std::string &on_swing_do(void);
  const std::string &on_targeted_do(void);
  const std::string &on_targeted_radially_do(void);
  const std::string &on_teleport_do(void);
  const std::string &on_thrown_do(void);
  const std::string &on_tick_do(void);
  const std::string &on_tick_when_activated_do(void);
  const std::string &on_tick_when_deactivated_do(void);
  const std::string &on_unequip_do(void);
  const std::string &on_use_do(void);
  const std::string &on_use_skill_do(void);
  const std::string &on_waiting_do(void);
  const std::string &on_want_to_shoot_at_do(void);
  const std::string &on_you_are_declared_a_follower_do(void);
  const std::string &on_you_are_declared_leader_do(void);
  const std::string &on_you_are_on_fire_do(void);
  const std::string &on_you_nat_attack_attempt_do(void);
  const std::string &on_you_nat_attack_success_do(void);
  const std::string &poison_reason_get(void);
  const std::string &resurrect_dice_str(void);
  const std::string &runic_name_get(void);
  const std::string &skill_base_name(void);
  const std::string &skill_replaces(void);
  const std::string &spawn_group_size_dice_str(void);
  const std::string &spawn_on_shoved(void);
  const std::string &spell_base_name(void);
  const std::string &spell_replaces(void);
  const std::string &str1(void);
  const std::string &str2(void);
  const std::string &str4(void);
  const std::string &text_debuff(void);
  const std::string &text_description_enchant(void);
  const std::string &text_description_short(void);
  const std::string &text_description_very_short(void);
  const std::string &text_hits(void);
  const std::string &text_real_name(void);
  const std::string &text_title(void);
  const std::string &text_unused1(void);
  const std::string &text_unused2(void);
  const std::string &text_unused3(void);
  const std::string &text_unused(void);
  const std::string &title(void);
  // end sort marker5 {

  float bounce_curr(void);
  float bounce_fade_curr(void);
  float bounce_height_curr(void);
  float distance_avoid_get(void);
  float distance_from_leader(point p);
  float distance_from_leader(void);
  float distance_from_mob(point p);
  float distance_from_mob(void);
  float distance_leader_max_float(point p);
  float distance_leader_max_float(void);
  float distance_minion_from_mob_max_float(point p);
  float distance_minion_from_mob_max_float(void);
  float distance_recruitment_max_float(point p);
  float distance_recruitment_max_float(void);
  float distance_spell_cast_get(void);
  float distance_throw_get(void);
  float distance_vision_get(void);
  float fadeup_curr(void);
  float fadeup_fade_curr(void);
  float fadeup_height_curr(void);
  float fall_curr(void);
  float fall_height_curr(void);
  float floating_curr(void);
  float health_pct(void);
  float jump_distance_current(void);
  float jump_distance_max_get(void);
  float lunge_curr(void);
  float teleport_distance_max_get(void);
  float teleport_distance_with_modifiers_get(void);
  float update_wobble(void);
  float wobble_curr(void);

  // begin sort marker6 {
  int aggression_pct(void);
  int ai_detect_secret_doors(void);
  int ai_dmap_can_see_init(int minx, int miny, int maxx, int maxy, int type, bool check);
  int ai_hit_actual(Thingp hitter, Thingp real_hitter, ThingAttackOptionsp, int damage);
  int ai_resent_count(void);
  int ai_wanderer(void);
  int attack_blood(void);
  int attack_eater(void);
  int attack_humanoid(void);
  int attack_living(void);
  int attack_meat(void);
  int attack_no_msg(void);
  int attack_num_get(void);
  int attack_num_set(int);
  int attack_undead(void);
  int attack(void);
  int blast_min_radius(void);
  int blinded_count_decr(int);
  int blinded_count_decr(void);
  int blinded_count_incr(int);
  int blinded_count_incr(void);
  int blinded_count_set(int);
  int blinded_count(void);
  int bounce_count(void);
  int capacity_height(void);
  int capacity_width(void);
  int carried_amulet_count(void);
  int carried_amulet_highest_value_for_target(Thingp *out, Thingp target);
  int carried_amulet_highest_value(Thingp *out);
  int carried_amulet_least_value(Thingp *out);
  int carried_armor_count(void);
  int carried_armor_highest_value_for_target(Thingp *out, Thingp target);
  int carried_armor_highest_value(Thingp *out);
  int carried_armor_least_value(Thingp *out);
  int carried_boots_count(void);
  int carried_boots_highest_value_for_target(Thingp *out, Thingp target);
  int carried_boots_highest_value(Thingp *out);
  int carried_boots_least_value(Thingp *out);
  int carried_cloak_count(void);
  int carried_cloak_highest_value_for_target(Thingp *out, Thingp target);
  int carried_cloak_highest_value(Thingp *out);
  int carried_cloak_least_value(Thingp *out);
  int carried_food_count(void);
  int carried_food_highest_value(Thingp *out);
  int carried_food_least_value(Thingp *out);
  int carried_gauntlet_count(void);
  int carried_gauntlet_highest_value_for_target(Thingp *out, Thingp target);
  int carried_gauntlet_highest_value(Thingp *out);
  int carried_gauntlet_least_value(Thingp *out);
  int carried_helmet_count(void);
  int carried_helmet_highest_value_for_target(Thingp *out, Thingp target);
  int carried_helmet_highest_value(Thingp *out);
  int carried_helmet_least_value(Thingp *out);
  int carried_ranged_weapon_count(void);
  int carried_ranged_weapon_highest_value_for_target(Thingp *out, Thingp target);
  int carried_ranged_weapon_highest_value(Thingp *out);
  int carried_ranged_weapon_least_value(Thingp *out);
  int carried_ring_count(void);
  int carried_ring_highest_value(Thingp *out);
  int carried_ring_least_value(Thingp *out);
  int carried_shield_count(void);
  int carried_shield_highest_value_for_target(Thingp *out, Thingp target);
  int carried_shield_highest_value(Thingp *out);
  int carried_shield_least_value(Thingp *out);
  int carried_staff_count(void);
  int carried_staff_highest_value_for_target(Thingp *out, Thingp target);
  int carried_staff_highest_value(Thingp *out);
  int carried_staff_least_value(Thingp *out);
  int carried_weapon_count(void);
  int carried_weapon_highest_value(Thingp *out);
  int carried_weapon_least_value(Thingp *out);
  int chance_d10000_crit(void);
  int chance_d10000_damaged(void);
  int chance_d10000_enchanted(void);
  int chance_d10000_runic_class_A(void);
  int chance_d10000_runic_class_B(void);
  int chance_d10000_set_on_fire(void);
  int chance_d1000_appearing(void);
  int chance_d1000_attack_engulf(void);
  int chance_d1000_carrier_of_treasure_class_A(void);
  int chance_d1000_carrier_of_treasure_class_B(void);
  int chance_d1000_carrier_of_treasure_class_C(void);
  int chance_d1000_carrier_of_weapon_class_A(void);
  int chance_d1000_carrier_of_weapon_class_B(void);
  int chance_d1000_carrier_of_weapon_class_C(void);
  int chance_d1000_grapple(void);
  int chance_d1000_jump_attack(void);
  int chance_d1000_jump_on_low_hp(void);
  int chance_d1000_jump_onto(void);
  int chance_d1000_jump_randomly(void);
  int chance_d1000_melting(void);
  int chance_d1000_regenerate(void);
  int chance_d1000_shooting_avoid_friends(void);
  int chance_d1000_shooting(void);
  int chance_d1000_shove(void);
  int chance_d1000_steal_item(void);
  int chance_d1000_tameable(void);
  int chance_d1000_teleport_attack(void);
  int chance_d1000_teleport_self(void);
  int charge_count_decr(int);
  int charge_count_decr(void);
  int charge_count_incr(int);
  int charge_count_incr(void);
  int charge_count_set(int);
  int charge_count(void);
  int collect_penalty_get(Thingp item);
  int collision_check(void);
  int collision_hit_180(void);
  int collision_hit_360(void);
  int collision_hit_adj(void);
  int collision_hit_priority(void);
  int collision_hit_two_tiles_ahead(void);
  int confused_count_decr(int);
  int confused_count_decr(void);
  int confused_count_incr(int);
  int confused_count_incr(void);
  int confused_count_set(int);
  int confused_count(void);
  int consume_per_bite_amount(void);
  int damaged_count_decr(int);
  int damaged_count_decr(void);
  int damaged_count_incr(int);
  int damaged_count_incr(void);
  int damaged_count_set(int);
  int damaged_count(void);
  int danger_current_level(Thingp);
  int danger_current_level(void);
  int danger_initial_level(Thingp);
  int danger_initial_level(void);
  int defence(void);
  int distance_leader_max(void);
  int distance_minion_vision_shared(void);
  int distance_recruitment_max(void);
  int distance_spell_cast_decr(int);
  int distance_spell_cast_decr(void);
  int distance_spell_cast_incr(int);
  int distance_spell_cast_incr(void);
  int distance_spell_cast_set(int);
  int distance_throw_decr(int);
  int distance_throw_decr(void);
  int distance_throw_incr(int);
  int distance_throw_incr(void);
  int distance_throw_set(int);
  int distance_to_player_on_different_level(void);
  int distance_to_player(void);
  int dmg_acid(Thingp victim = nullptr);
  int dmg_bite(Thingp victim = nullptr);
  int dmg_chance_d1000_acid(int);
  int dmg_chance_d1000_bite(int);
  int dmg_chance_d1000_claw(int);
  int dmg_chance_d1000_cold(int);
  int dmg_chance_d1000_crush(int);
  int dmg_chance_d1000_digest(int);
  int dmg_chance_d1000_drown(int);
  int dmg_chance_d1000_energy(int);
  int dmg_chance_d1000_fire(int);
  int dmg_chance_d1000_heat(int);
  int dmg_chance_d1000_holy(int);
  int dmg_chance_d1000_impact(int);
  int dmg_chance_d1000_lightning(int);
  int dmg_chance_d1000_magic_drain(int);
  int dmg_chance_d1000_melee(int);
  int dmg_chance_d1000_missile(int);
  int dmg_chance_d1000_nat_att(int);
  int dmg_chance_d1000_necrosis(int);
  int dmg_chance_d1000_negation(int);
  int dmg_chance_d1000_poison(int);
  int dmg_chance_d1000_stamina_drain(int);
  int dmg_chance_d1000_water(int);
  int dmg_claw(Thingp victim = nullptr);
  int dmg_cold(Thingp victim = nullptr);
  int dmg_crush(Thingp victim = nullptr);
  int dmg_current_decr(int);
  int dmg_current_decr(void);
  int dmg_current_incr(int);
  int dmg_current_incr(void);
  int dmg_current_set(int);
  int dmg_current(Thingp victim = nullptr);
  int dmg_digest(Thingp victim = nullptr);
  int dmg_drown(Thingp victim = nullptr);
  int dmg_energy(Thingp victim = nullptr);
  int dmg_fire(Thingp victim = nullptr);
  int dmg_heat(Thingp victim = nullptr);
  int dmg_holy(Thingp victim = nullptr);
  int dmg_impact(Thingp victim = nullptr);
  int dmg_lightning(Thingp victim = nullptr);
  int dmg_limited_per_tick(void);
  int dmg_magic_drain(Thingp victim = nullptr);
  int dmg_max(Thingp victim = nullptr);
  int dmg_melee(Thingp victim = nullptr);
  int dmg_min(Thingp victim = nullptr);
  int dmg_missile(Thingp victim = nullptr);
  int dmg_nat_att(Thingp victim = nullptr);
  int dmg_necrosis(Thingp victim = nullptr);
  int dmg_negation(Thingp victim = nullptr);
  int dmg_num_of_attacks(void);
  int dmg_poison(Thingp victim = nullptr);
  int dmg_rcv_doubled_from_acid(void);
  int dmg_rcv_doubled_from_cold(void);
  int dmg_rcv_doubled_from_fire(void);
  int dmg_rcv_doubled_from_necrosis(void);
  int dmg_rcv_doubled_from_poison(void);
  int dmg_rcv_doubled_from_water(void);
  int dmg_stamina(Thingp victim = nullptr);
  int dmg_water(Thingp victim = nullptr);
  int effect_has_blast_radius(void);
  int effect_radius(void);
  int enchant_count_decr(int);
  int enchant_count_decr(void);
  int enchant_count_get(void);
  int enchant_count_incr(int);
  int enchant_count_incr(void);
  int enchant_count_set(int);
  int enchant_max_current_decr(int);
  int enchant_max_current_decr(void);
  int enchant_max_current_get(void);
  int enchant_max_current_incr(int);
  int enchant_max_current_incr(void);
  int enchant_max_current_set(int);
  int enchant_max(void);
  int enchantstone_count(void);
  int entranced_count_decr(int);
  int entranced_count_decr(void);
  int entranced_count_incr(int);
  int entranced_count_incr(void);
  int entranced_count_set(int);
  int entranced_count(void);
  int environ_dislikes_acid(void);
  int environ_dislikes_cold(void);
  int environ_dislikes_fire(void);
  int environ_dislikes_necrosis(void);
  int environ_dislikes_poison(void);
  int environ_dislikes_water(void);
  int environ_hates_acid(void);
  int environ_hates_cold(void);
  int environ_hates_fire(void);
  int environ_hates_necrosis(void);
  int environ_hates_poison(void);
  int environ_hates_water(void);
  int environ_likes_deep_water(void);
  int environ_likes_lava(void);
  int environ_likes_shallow_water(void);
  int follower_count(void);
  int gfx_ascii_bg_color_spread_alpha(void);
  int gfx_ascii_bg_color_spread_blue(void);
  int gfx_ascii_bg_color_spread_green(void);
  int gfx_ascii_bg_color_spread_hue(void);
  int gfx_ascii_bg_color_spread_red(void);
  int gfx_ascii_color_bg_unchanged_by_lights(void);
  int gfx_ascii_color_fg_unchanged_by_lights(void);
  int gfx_ascii_color_is_animated(void);
  int gfx_ascii_fade_with_dist(void);
  int gfx_ascii_fg_color_spread_alpha(void);
  int gfx_ascii_fg_color_spread_blue(void);
  int gfx_ascii_fg_color_spread_green(void);
  int gfx_ascii_fg_color_spread_hue(void);
  int gfx_ascii_fg_color_spread_red(void);
  int gfx_ascii_show_light_once_seen(void);
  int gfx_ascii_shown_as_gray_in_shadow(void);
  int gfx_ascii_shown_in_bg(void);
  int gfx_ascii_shown(void);
  int gfx_glows(void);
  int gfx_on_fire_anim(void);
  int gfx_ooze(void);
  int gfx_pixelart_animated_can_hflip(void);
  int gfx_pixelart_animated_can_vflip(void);
  int gfx_pixelart_animated_no_dir(void);
  int gfx_pixelart_anim_synced_with_owner(void);
  int gfx_pixelart_bounce_always(void);
  int gfx_pixelart_bounce_on_move(void);
  int gfx_pixelart_equip_carry_anim(void);
  int gfx_pixelart_flickers(void);
  int gfx_pixelart_health_bar_autohide(void);
  int gfx_pixelart_health_bar_only_when_awake(void);
  int gfx_pixelart_health_bar_shown(void);
  int gfx_pixelart_oversized_and_centered(void);
  int gfx_pixelart_oversized_and_on_floor(void);
  int gfx_pixelart_reflection(void);
  int gfx_pixelart_shadow_long(void);
  int gfx_pixelart_shadow_short(void);
  int gfx_pixelart_shadow_solid(void);
  int gfx_pixelart_shadow_very_short(void);
  int gfx_pixelart_shadow(void);
  int gfx_pixelart_show_asleep_anim(void);
  int gfx_pixelart_show_highlighted(void);
  int gfx_pixelart_shown_in_bg(void);
  int gfx_pixelart_show_outlined(void);
  int gfx_pixelart_show_square_outlined(void);
  int gfx_pixelart_submergible(void);
  int gfx_pixelart_wobbles_when_hit(void);
  int gfx_water(void);
  int goal_penalty_get(Thingp attacker);
  int gold_decr(int);
  int gold_decr(void);
  int gold_incr(int);
  int gold_incr(void);
  int gold_set(int);
  int gold_value(void);
  int gold(void);
  int has_a_head(void);
  int has_tentacles(void);
  int health_boost(Thingp victim, int v);
  int health_decr(int);
  int health_decr(void);
  int health_incr(int);
  int health_incr(void);
  int health_initial(void);
  int health_max_decr(int);
  int health_max_decr(void);
  int health_max_incr(int);
  int health_max_incr(void);
  int health_max_set(int);
  int health_max(void);
  int health_regenerate_amount(void);
  int health_regenerate(void);
  int health_set(int);
  int health(void);
  int hunger_boost(int v);
  int hunger_clock_tick_freq(void);
  int hunger_decr(int);
  int hunger_decr(void);
  int hunger_hunger_pct(void);
  int hunger_incr(int);
  int hunger_incr(void);
  int hunger_is_hunger_level_hungry_at_pct(void);
  int hunger_is_hunger_level_starving_at_pct(void);
  int hunger_is_insatiable(void);
  int hunger_set(int);
  int hunger(void);
  int idle_count_decr(int);
  int idle_count_decr(void);
  int idle_count_incr(int);
  int idle_count_incr(void);
  int idle_count_set(int);
  int idle_count(void);
  int initial_charge_count(void);
  int initial_light_dist_get(void);
  int initial_temperature_get(void);
  int is_able_to_amplify_footsteps(void);
  int is_able_to_attack_mobs(void);
  int is_able_to_attack_owner(void);
  int is_able_to_attack_totems(void);
  int is_able_to_be_equipped(void);
  int is_able_to_be_reflected(void);
  int is_able_to_be_resurrected(void);
  int is_able_to_be_surprised(void);
  int is_able_to_be_teleported(void);
  int is_able_to_break_down_doors(void);
  int is_able_to_break_out_of_crystal(void);
  int is_able_to_break_out_of_ice(void);
  int is_able_to_break_out_of_spell_of_holding(void);
  int is_able_to_break_out_of_spell_of_sanctuary(void);
  int is_able_to_break_out_of_webs(void);
  int is_able_to_change_levels(void);
  int is_able_to_collect_keys(void);
  int is_able_to_dampen_footsteps(void);
  int is_able_to_eat_poisonous_food(void);
  int is_able_to_eat_rotting_food(void);
  int is_able_to_eat_unpleasant_food(void);
  int is_able_to_enchant_items(void);
  int is_able_to_fall_over(void);
  int is_able_to_fall(void);
  int is_able_to_follow(void);
  int is_able_to_freeze(void);
  int is_able_to_grapple(void);
  int is_able_to_have_a_runic_inscribed(void);
  int is_able_to_jump_attack(void);
  int is_able_to_jump_escape(void);
  int is_able_to_jump_onto(void);
  int is_able_to_jump(void);
  int is_able_to_jump_without_tiring(void);
  int is_able_to_learn_skills(void);
  int is_able_to_learn_spells(void);
  int is_able_to_live_out_of_water(void);
  int is_able_to_lunge(void);
  int is_able_to_melt(void);
  int is_able_to_move_diagonally(void);
  int is_able_to_open_doors(void);
  int is_able_to_rage(void);
  int is_able_to_regenerate(void);
  int is_able_to_rest(void);
  int is_able_to_run_away_after_stealing(void);
  int is_able_to_see_in_magical_darkness(void);
  int is_able_to_see_in_the_dark(void);
  int is_able_to_see_invisible(void);
  int is_able_to_see_through_doors(void);
  int is_able_to_shoot_at_close_range(void);
  int is_able_to_shoot_at(void);
  int is_able_to_shove(void);
  int is_able_to_sleep(void);
  int is_able_to_spawn_things(void);
  int is_able_to_spell_cast(void);
  int is_able_to_swim(void);
  int is_able_to_teleport_attack(void);
  int is_able_to_teleport_escape(void);
  int is_able_to_teleport_self(void);
  int is_able_to_teleport_without_tiring(void);
  int is_able_to_tire(void);
  int is_able_to_use_amulet(void);
  int is_able_to_use_armor(void);
  int is_able_to_use_boots(void);
  int is_able_to_use_cloak(void);
  int is_able_to_use_gauntlet(void);
  int is_able_to_use_helmet(void);
  int is_able_to_use_ranged_weapons(void);
  int is_able_to_use_rings(void);
  int is_able_to_use_shield(void);
  int is_able_to_use_staffs(void);
  int is_able_to_use_weapons(void);
  int is_able_to_walk_through_walls(void);
  int is_acid_blob(void);
  int is_acid(void);
  int is_aerodynamic(void);
  int is_air_breather(void);
  int is_alive_monst(void);
  int is_alive_on_end_of_anim(void);
  int is_always_activated(void);
  int is_always_hit(void);
  int is_always_submerged_in_lava(void);
  int is_always_submerged_in_water(void);
  int is_amulet(void);
  int is_animation(void);
  int is_ant(void);
  int is_aquatic(void);
  int is_armor(void);
  int is_ascend_dungeon(void);
  int is_ascend_sewer(void);
  int is_asleep_initially(void);
  int is_attackable_by_magic(void);
  int is_attackable_by_monst(void);
  int is_attackable_by_player(void);
  int is_attacked_with_dmg_acid(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_bite(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_claw(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_cold(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_crush(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_digest(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_drown(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_energy(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_fire(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_heat(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_holy(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_impact(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_lightning(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_magic_drain(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_melee(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_missile(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_nat_att(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_necrosis(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_negation(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_poison(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_stamina(Thingp hitter, Thingp real_hitter, int damage);
  int is_attacked_with_dmg_water(Thingp hitter, Thingp real_hitter, int damage);
  int is_auto_activated(void);
  int is_auto_collect_item(void);
  int is_auto_equipped(void);
  int is_auto_throw(void);
  int is_bag_item_container(void);
  int is_bag_item_not_stackable(void);
  int is_bag_item(void);
  int is_bag(void);
  int is_barrel(void);
  int is_basalt(void);
  int is_bearowl(void);
  int is_bee(void);
  int is_biome_chasms(void);
  int is_biome_dungeon(void);
  int is_biome_flooded(void);
  int is_biome_ice(void);
  int is_biome_lava(void);
  int is_biome_sewer(void);
  int is_biome_swamp(void);
  int is_biome_unused(void);
  int is_bleeder(void);
  int is_block_of_crystal(void);
  int is_block_of_ice(void);
  int is_bloodbug(void);
  int is_blood(void);
  int is_blunt(void);
  int is_bones(void);
  int is_boots(void);
  int is_brazier(void);
  int is_bridge(void);
  int is_brittle(void);
  int is_buffable(void);
  int is_buff(void);
  int is_burnable(void);
  int is_burnt_check(void);
  int is_carnivorous_plant(void);
  int is_cautious(void);
  int is_centipede(void);
  int is_chasm(void);
  int is_cloak(void);
  int is_cold_elemental(void);
  int is_cold(void);
  int is_collectable(void);
  int is_collected_as_gold(void);
  int is_collected_as_keys(void);
  int is_combustible(void);
  int is_corpse_on_death(void);
  int is_corpse(void);
  int is_corpse_with_bones(void);
  int is_corridor(void);
  int is_cowardly(void);
  int is_crab(void);
  int is_critical_to_level(void);
  int is_crushable(void);
  int is_crystalline(void);
  int is_crystal(void);
  int is_cursor_can_hover_over_needs_confirm(void);
  int is_cursor_can_hover_over(void);
  int is_cursor_path_blocker(void);
  int is_cursor_path_hazard(void);
  int is_cursor_path(void);
  int is_cursor(void);
  int is_dagger(void);
  int is_dangerous(Thingp);
  int is_daring(void);
  int is_dead_check(void);
  int is_dead_on_end_of_anim(void);
  int is_dead_on_falling(void);
  int is_dead_on_shove(void);
  int is_dead_or_dying(void);
  int is_death_hornet(void);
  int is_debuff(void);
  int is_debug_path(void);
  int is_debug_type(void);
  int is_deep_water(void);
  int is_demon(void);
  int is_descend_dungeon(void);
  int is_descend_sewer(void);
  int is_described_in_leftbar(void);
  int is_described_when_hovering_over(void);
  int is_destroyed_on_hit_or_miss(void);
  int is_destroyed_on_hitting(void);
  int is_dirt(void);
  int is_dogman(void);
  int is_dog(void);
  int is_door(void);
  int is_dragon_scales(void);
  int is_drinkable(void);
  int is_droppable(void);
  int is_duck(void);
  int is_eater_of_amulets(void);
  int is_eater_of_armor(void);
  int is_eater_of_blood(void);
  int is_eater_of_boots(void);
  int is_eater_of_cloaks(void);
  int is_eater_of_foliage(void);
  int is_eater_of_food(void);
  int is_eater_of_fungus(void);
  int is_eater_of_gauntlets(void);
  int is_eater_of_grass(void);
  int is_eater_of_green_blood(void);
  int is_eater_of_helmets(void);
  int is_eater_of_magical_items(void);
  int is_eater_of_meat(void);
  int is_eater_of_plants(void);
  int is_eater_of_potions(void);
  int is_eater_of_red_blood(void);
  int is_eater_of_rings(void);
  int is_eater_of_shields(void);
  int is_eater_of_slime(void);
  int is_eater_of_staffs(void);
  int is_eater_of_treasure(void);
  int is_eater_of_weapons(void);
  int is_enchantable_as_a_group(void);
  int is_enchantable(void);
  int is_enchantstone(void);
  int is_engulfer(void);
  int is_ethereal_mob(void);
  int is_ethereal(void);
  int is_ettin(void);
  int is_exit_finder(void);
  int is_explorer(void);
  int is_explosion(void);
  int is_fairy(void);
  int is_fearless(void);
  int is_fire_elemental(void);
  int is_firefox(void);
  int is_fire(void);
  int is_flat(void);
  int is_floor_deco(void);
  int is_floor(void);
  int is_flying(void);
  int is_foliage(void);
  int is_food(void);
  int is_four_leaf_clover(void);
  int is_frozen_check(void);
  int is_fungus_edible(void);
  int is_fungus_healing(void);
  int is_fungus_poison(void);
  int is_fungus(void);
  int is_fungus_withered(void);
  int is_gas_blocker(void);
  int is_gas_explosion_blocker(void);
  int is_gauntlet(void);
  int is_gelatinous(void);
  int is_glass(void);
  int is_gnoll(void);
  int is_gnome(void);
  int is_goat(void);
  int is_golden(void);
  int is_gold(void);
  int is_golem(void);
  int is_grass_dead(void);
  int is_grass_dry_trampled(void);
  int is_grass_dry(void);
  int is_grass_trampled(void);
  int is_grass(void);
  int is_grass_wet_trampled(void);
  int is_grass_wet(void);
  int is_green_blooded(void);
  int is_green_blood(void);
  int is_green_splatter(void);
  int is_hard(void);
  int is_hazard(void);
  int is_health_booster(void);
  int is_heavy(void);
  int is_hellpup(void);
  int is_helmet(void);
  int is_herbivore(void);
  int is_hittable(void);
  int is_hit(Thingp hitter, ThingAttackOptionsp, int damage);
  int is_holy(void);
  int is_holy_water(void);
  int is_humanoid(void);
  int is_iceman(void);
  int is_immune_to_acid(void);
  int is_immune_to_blinding(void);
  int is_immune_to_cold(void);
  int is_immune_to_confusion(void);
  int is_immune_to_electricity(void);
  int is_immune_to_entrancement(void);
  int is_immune_to_fire(void);
  int is_immune_to_holy_damage(void);
  int is_immune_to_lightning(void);
  int is_immune_to_magic_drain(void);
  int is_immune_to_necrosis(void);
  int is_immune_to_negation(void);
  int is_immune_to_non_magical_weapons(void);
  int is_immune_to_paralysis(void);
  int is_immune_to_poison(void);
  int is_immune_to_spell_of_beckoning(void);
  int is_immune_to_spell_of_holding(void);
  int is_immune_to_spell_of_repulsion(void);
  int is_immune_to_spell_of_sanctuary(void);
  int is_immune_to_spell_of_slowness(void);
  int is_immune_to_spiderwebs(void);
  int is_immune_to_stamina_drain(void);
  int is_immune_to_teleport_attack(void);
  int is_immune_to_vorpal_weapons(void);
  int is_immune_to_water(void);
  int is_intelligent(void);
  int is_interesting(void);
  int is_internal(void);
  int is_item_carrier(void);
  int is_item_collector(void);
  int is_item_organic(void);
  int is_item_targeted(void);
  int is_item(void);
  int is_kept_after_final_use(void);
  int is_key_special(void);
  int is_key(void);
  int is_laser(void);
  int is_lava(void);
  int is_leech(void);
  int is_lifeless(void);
  int is_light_blocker_for_monst(void);
  int is_light_blocker(void);
  int is_lightning(void);
  int is_light(void);
  int is_limb(void);
  int is_living(void);
  int is_loggable(void);
  int is_mace(void);
  int is_made_of_rock(void);
  int is_magical_effect(void);
  int is_magical(void);
  int is_magic_crystal(void);
  int is_magic_stone(void);
  int is_mantisman(void);
  int is_map_beast(void);
  int is_map_treasure(void);
  int is_meat(void);
  int is_metal(void);
  int is_mimic(void);
  int is_minion(void);
  int is_missile(void);
  int is_mob_class_A(void);
  int is_mob_class_B(void);
  int is_mob_class_C(void);
  int is_mob(void);
  int is_molekin(void);
  int is_monst_class_A(void);
  int is_monst_class_B(void);
  int is_monst_class_C(void);
  int is_monst_class_D(void);
  int is_monst_class_E(void);
  int is_monst_pack(void);
  int is_monst(void);
  int is_moveable(void);
  int is_msg_allowed_hears_something(void);
  int is_msg_allowed_is_dead(void);
  int is_msg_allowed_is_seen(void);
  int is_msg_allowed_is_surprised(void);
  int is_msg_allowed_is_wounded(void);
  int is_msg_allowed_senses_danger(void);
  int is_msg(void);
  int is_mummy(void);
  int is_necrotic_danger_level(void);
  int is_no_tile(void);
  int is_not_shown_as_a_pet(void);
  int is_obj_spawning_monst(void);
  int is_obj_spawning(void);
  int is_obs_ai(void);
  int is_obs_destructable(void);
  int is_obsidian(void);
  int is_obs_jump_end(void);
  int is_obs_jumping(void);
  int is_obs_shooting(void);
  int is_obs_shoving(void);
  int is_obs_spawn_monst(void);
  int is_obs_spawn(void);
  int is_obs_spell_casting(void);
  int is_obs_throwing(void);
  int is_obs_wall_or_door(void);
  int is_obs_when_dead(void);
  int is_ogre(void);
  int is_one_per_tile(void);
  int is_ooze(void);
  int is_openable(void);
  int is_organic(void);
  int is_pillar(void);
  int is_piranha(void);
  int is_plant(void);
  int is_player_bodypart_eyes(void);
  int is_player_bodypart_face(void);
  int is_player_bodypart_hair(void);
  int is_player_bodypart_hat(void);
  int is_player_bodypart_legs(void);
  int is_player_bodypart_torso(void);
  int is_player_bodypart(void);
  int is_player(void);
  int is_pointy(void);
  int is_poisonous_danger_level(void);
  int is_portal(void);
  int is_potion(void);
  int is_pressure_plate(void);
  int is_projectile(void);
  int is_ranged_weapon(void);
  int is_rat(void);
  int is_red_blooded(void);
  int is_red_blood(void);
  int is_red_splatter(void);
  int is_reflective(void);
  int is_removable_if_out_of_slots(void);
  int is_resurrected_or_resurrecting(void);
  int is_ring(void);
  int is_ripple(void);
  int is_rock_ice(void);
  int is_rock_lava(void);
  int is_rock(void);
  int is_runic_defensive_class_A(void);
  int is_runic_defensive_class_B(void);
  int is_runic_offensive_class_A(void);
  int is_runic_offensive_class_B(void);
  int is_rusty(void);
  int is_scorpion(void);
  int is_secret_door(void);
  int is_sewer_wall(void);
  int is_shallow_water(void);
  int is_sheep(void);
  int is_shield(void);
  int is_shootable(void);
  int is_shovable_and_sticky(void);
  int is_shovable(void);
  int is_skeleton(void);
  int is_skillstone(void);
  int is_skill(void);
  int is_slime(void);
  int is_slippery(void);
  int is_sluud(void);
  int is_smoke(void);
  int is_snake(void);
  int is_soft(void);
  int is_spectral_blade(void);
  int is_spell_always_succeeds(void);
  int is_spellbook(void);
  int is_spell_of_beckoning(void);
  int is_spell_of_holding_barrier(void);
  int is_spell_of_holding(void);
  int is_spell_of_protection_barrier(void);
  int is_spell_of_protection(void);
  int is_spell_of_repulsion(void);
  int is_spell_of_sanctuary_barrier(void);
  int is_spell_of_sanctuary(void);
  int is_spell_of_slowness(void);
  int is_spell(void);
  int is_spider(void);
  int is_spiderweb(void);
  int is_splatter(void);
  int is_staff(void);
  int is_steam(void);
  int is_steel(void);
  int is_sticky(void);
  int is_stone(void);
  int is_swimmer_but_land_dweller(void);
  int is_swimmer(void);
  int is_sword(void);
  int is_tameable(void);
  int is_target_radial(void);
  int is_target_select(void);
  int is_tentacle_horror(void);
  int is_tentacle(void);
  int is_tentacleye(void);
  int is_the_grid(void);
  int is_thief(void);
  int is_throwable(void);
  int is_thrown_as_a_weapon(void);
  int is_thylacine(void);
  int is_tickable(void);
  int is_tireless(void);
  int is_tmp_thing(void);
  int is_torch(void);
  int is_totem(void);
  int is_trap(void);
  int is_treasure_chest(void);
  int is_treasure_class_A(void);
  int is_treasure_class_B(void);
  int is_treasure_class_C(void);
  int is_treasure_type(void);
  int is_treasure(void);
  int is_troll(void);
  int is_turret(void);
  int is_undead(void);
  int is_unobtanium(void);
  int is_unused_flag10(void);
  int is_unused_flag11(void);
  int is_unused_flag12(void);
  int is_unused_flag13(void);
  int is_unused_flag142(void);
  int is_unused_flag14(void);
  int is_unused_flag15(void);
  int is_unused_flag16(void);
  int is_unused_flag179(void);
  int is_unused_flag17(void);
  int is_unused_flag18(void);
  int is_unused_flag192(void);
  int is_unused_flag19(void);
  int is_unused_flag1(void);
  int is_unused_flag20(void);
  int is_unused_flag21(void);
  int is_unused_flag22(void);
  int is_unused_flag23(void);
  int is_unused_flag24(void);
  int is_unused_flag25(void);
  int is_unused_flag26(void);
  int is_unused_flag27(void);
  int is_unused_flag28(void);
  int is_unused_flag29(void);
  int is_unused_flag2(void);
  int is_unused_flag30(void);
  int is_unused_flag31(void);
  int is_unused_flag32(void);
  int is_unused_flag33(void);
  int is_unused_flag34(void);
  int is_unused_flag35(void);
  int is_unused_flag36(void);
  int is_unused_flag37(void);
  int is_unused_flag38(void);
  int is_unused_flag39(void);
  int is_unused_flag3(void);
  int is_unused_flag40(void);
  int is_unused_flag41(void);
  int is_unused_flag42(void);
  int is_unused_flag43(void);
  int is_unused_flag4(void);
  int is_unused_flag5(void);
  int is_unused_flag6(void);
  int is_unused_flag7(void);
  int is_unused_flag8(void);
  int is_unused_flag9(void);
  int is_usable_only_after_equipping(void);
  int is_usable(void);
  int is_used_when_thrown(void);
  int is_value_defensive(void);
  int is_value_offensive(void);
  int is_vanquished_on_negation(void);
  int is_very_combustible(void);
  int is_very_hard(void);
  int is_very_heavy(void);
  int is_very_intelligent(void);
  int is_wall_dungeon(void);
  int is_wall(void);
  int is_warhammer(void);
  int is_water(void);
  int is_weapon_class_A(void);
  int is_weapon_class_B(void);
  int is_weapon_class_C(void);
  int is_weapon(void);
  int is_wooden(void);
  int is_yeti(void);
  int is_zorblin(void);
  int item_count_excluding_charges(Tpp item);
  int item_count_including_charges(Tpp item);
  int item_enchant_count(const int slot);
  int item_height(void);
  int item_slot_charge_count(const int slot);
  int item_width(void);
  int jump_distance_bonus_decr(int);
  int jump_distance_bonus_decr(void);
  int jump_distance_bonus_incr(int);
  int jump_distance_bonus_incr(void);
  int jump_distance_bonus_set(int);
  int jump_distance_bonus(void);
  int jump_distance_total(void);
  int jump_distance(void);
  int keys_decr(int);
  int keys_decr(void);
  int keys_incr(int);
  int keys_incr(void);
  int keys_set(int);
  int keys(void);
  int level_get(void);
  int lifespan_decr(int);
  int lifespan_decr(void);
  int lifespan_get(void);
  int lifespan_incr(int);
  int lifespan_incr(void);
  int lifespan_initial(void);
  int lifespan_set(int);
  int light_distance_update(void);
  int light_dist_decr(int);
  int light_dist_decr(void);
  int light_dist_get(void);
  int light_dist_incr(int);
  int light_dist_incr(void);
  int light_dist_initial(void);
  int light_dist_set(int);
  int light_dist(void);
  int magic_decr(int);
  int magic_decr(void);
  int magic_drain_on_using(void);
  int magic_incr(int);
  int magic_incr(void);
  int magic_max_decr(int);
  int magic_max_decr(void);
  int magic_max_incr(int);
  int magic_max_incr(void);
  int magic_max_set(int);
  int magic_max(void);
  int magic_set(int);
  int magic(void);
  int map_beast_carried_count(void);
  int map_beast_count(void);
  int map_treasure_carried_count(void);
  int map_treasure_count(void);
  int minion_count(void);
  int minion_limit(void);
  int move_count_decr(int);
  int move_count_decr(void);
  int move_count_incr(int);
  int move_count_incr(void);
  int move_count_set(int);
  int move_count(void);
  int move_penalty_decr(int);
  int move_penalty_decr(void);
  int move_penalty_incr(int);
  int move_penalty_incr(void);
  int move_penalty_set(int);
  int move_penalty(void);
  int move_speed_bonus_decr(int);
  int move_speed_bonus_decr(void);
  int move_speed_bonus_incr(int);
  int move_speed_bonus_incr(void);
  int move_speed_bonus_set(int);
  int move_speed_bonus(void);
  int move_speed_curr(void);
  int move_speed_total(void);
  int move_speed(void);
  int necrotized_amount_decr(int);
  int necrotized_amount_decr(void);
  int necrotized_amount_incr(int);
  int necrotized_amount_incr(void);
  int necrotized_amount_set(int);
  int necrotized_amount(void);
  int noise_additional_on_jump_end(void);
  int noise_additional_on_teleporting(void);
  int noise_blocker(void);
  int noise_decibels_hearing(void);
  int noise_decr(int);
  int noise_decr(void);
  int noise_incr(int);
  int noise_incr(void);
  int noise_on_born(void);
  int noise_on_dropping(void);
  int noise_on_hit_and_now_dead(void);
  int noise_on_hit_and_still_alive(void);
  int noise_on_jumping(void);
  int noise_on_moving(void);
  int noise_on_open_or_close(void);
  int noise_on_teleporting(void);
  int noise_set(int);
  int noise_total(void);
  int noise(void);
  int normal_placement_rules(void);
  int nutrition_decr(int v);
  int nutrition_get(void);
  int nutrition_init(void);
  int on_attacking_dmg_acid(Thingp victim, int damage);
  int on_attacking_dmg_bite(Thingp victim, int damage);
  int on_attacking_dmg_claw(Thingp victim, int damage);
  int on_attacking_dmg_cold(Thingp victim, int damage);
  int on_attacking_dmg_crush(Thingp victim, int damage);
  int on_attacking_dmg_digest(Thingp victim, int damage);
  int on_attacking_dmg_drown(Thingp victim, int damage);
  int on_attacking_dmg_energy(Thingp victim, int damage);
  int on_attacking_dmg_fire(Thingp victim, int damage);
  int on_attacking_dmg_heat(Thingp victim, int damage);
  int on_attacking_dmg_holy(Thingp victim, int damage);
  int on_attacking_dmg_impact(Thingp victim, int damage);
  int on_attacking_dmg_lightning(Thingp victim, int damage);
  int on_attacking_dmg_magic_drain(Thingp victim, int damage);
  int on_attacking_dmg_melee(Thingp victim, int damage);
  int on_attacking_dmg_missile(Thingp victim, int damage);
  int on_attacking_dmg_nat_att(Thingp victim, int damage);
  int on_attacking_dmg_necrosis(Thingp victim, int damage);
  int on_attacking_dmg_negation(Thingp victim, int damage);
  int on_attacking_dmg_poison(Thingp victim, int damage);
  int on_attacking_dmg_stamina(Thingp victim, int damage);
  int on_attacking_dmg_stat_att(Thingp victim, int damage);
  int on_attacking_dmg_stat_con(Thingp victim, int damage);
  int on_attacking_dmg_stat_str(Thingp victim, int damage);
  int on_attacking_dmg_water(Thingp victim, int damage);
  int on_death_drop_all_items(void);
  int on_death_is_open(void);
  int on_death_is_stone(void);
  int on_idle_tick_freq(void);
  int on_owner_attack_dmg_acid(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_bite(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_claw(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_cold(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_crush(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_digest(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_drown(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_energy(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_fire(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_heat(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_holy(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_impact(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_lightning(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_magic_drain(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_melee(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_missile(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_nat_att(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_necrosis(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_negation(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_poison(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_stamina(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_stat_att(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_stat_con(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_stat_str(Thingp owner, Thingp victim, int damage);
  int on_owner_attack_dmg_water(Thingp owner, Thingp victim, int damage);
  int on_owner_rcv_dmg_acid(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_bite(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_claw(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_cold(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_crush(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_digest(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_drown(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_energy(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_fire(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_heat(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_holy(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_impact(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_lightning(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_magic_drain(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_melee(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_missile(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_nat_att(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_necrosis(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_negation(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_poison(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_stamina(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_stat_att(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_stat_con(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_stat_str(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_owner_rcv_dmg_water(Thingp owner, Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_acid(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_bite(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_claw(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_cold(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_crush(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_digest(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_drown(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_energy(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_fire(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_heat(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_holy(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_impact(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_lightning(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_magic_drain(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_melee(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_missile(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_nat_att(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_necrosis(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_negation(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_poison(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_stamina(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_stat_att(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_stat_con(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_stat_str(Thingp hitter, Thingp real_hitter, int damage);
  int on_rcv_dmg_water(Thingp hitter, Thingp real_hitter, int damage);
  int owned_count(void);
  int paralysis_count_decr(int);
  int paralysis_count_decr(void);
  int paralysis_count_incr(int);
  int paralysis_count_incr(void);
  int paralysis_count_set(int);
  int paralysis_count(void);
  int poisoned_amount_decr(int);
  int poisoned_amount_decr(void);
  int poisoned_amount_incr(int);
  int poisoned_amount_incr(void);
  int poisoned_amount_set(int);
  int poisoned_amount(void);
  int prev_light_dist_decr(int);
  int prev_light_dist_decr(void);
  int prev_light_dist_get(void);
  int prev_light_dist_incr(int);
  int prev_light_dist_incr(void);
  int prev_light_dist_set(int);
  int range_max(void);
  int rarity(void);
  int resurrect_when(void);
  int score_decr(int);
  int score_incr(int);
  int score_set(int);
  int score(void);
  int shove_bonus_decr(int);
  int shove_bonus_decr(void);
  int shove_bonus_incr(int);
  int shove_bonus_incr(void);
  int shove_bonus_set(int);
  int shove_bonus(void);
  int shove_strength_total(void);
  int shove_strength(void);
  int size_modifier(void);
  int skillstone_count(void);
  int sleep_count_decr(int);
  int sleep_count_decr(void);
  int sleep_count_incr(int);
  int sleep_count_incr(void);
  int sleep_count_set(int);
  int sleep_count(void);
  int spawned_count(void);
  int spawn_group_radius(void);
  int spawn_group_size(void);
  int spawn_randomly_in_radius_range(const std::string &what, int amount, int radius_min, int radius_max);
  int spellbook_count(void);
  int spell_cost(void);
  int stamina_decr(int);
  int stamina_decr(void);
  int stamina_drain_on_attacking(void);
  int stamina_drain_on_using(void);
  int stamina_incr(int);
  int stamina_incr(void);
  int stamina_max_decr(int);
  int stamina_max_decr(void);
  int stamina_max_incr(int);
  int stamina_max_incr(void);
  int stamina_max_set(int);
  int stamina_max(void);
  int stamina_set(int);
  int stamina(void);
  int stat_att_bonus_decr(int);
  int stat_att_bonus_decr(void);
  int stat_att_bonus_incr(int);
  int stat_att_bonus_incr(void);
  int stat_att_bonus_set(int);
  int stat_att_bonus(void);
  int stat_att_decr(int);
  int stat_att_decr(void);
  int stat_att_incr(int);
  int stat_att_incr(void);
  int stat_att_penalties_total(void);
  int stat_att_penalty_when_idle_max(void);
  int stat_att_penalty_when_idle(void);
  int stat_att_penalty_when_in_deep_water(void);
  int stat_att_penalty_when_in_shallow_water(void);
  int stat_att_penalty_when_stuck_max(void);
  int stat_att_penalty_when_stuck(void);
  int stat_att_set(int);
  int stat_att_total(void);
  int stat_att(void);
  int stat_con_bonus_decr(int);
  int stat_con_bonus_decr(void);
  int stat_con_bonus_incr(int);
  int stat_con_bonus_incr(void);
  int stat_con_bonus_set(int);
  int stat_con_bonus(void);
  int stat_con_decr(int);
  int stat_con_decr(void);
  int stat_con_incr(int);
  int stat_con_incr(void);
  int stat_con_set(int);
  int stat_con_total(void);
  int stat_con(void);
  int stat_def_bonus_decr(int);
  int stat_def_bonus_decr(void);
  int stat_def_bonus_incr(int);
  int stat_def_bonus_incr(void);
  int stat_def_bonus_set(int);
  int stat_def_bonus(void);
  int stat_def_decr(int);
  int stat_def_decr(void);
  int stat_def_incr(int);
  int stat_def_incr(void);
  int stat_def_penalties_total(void);
  int stat_def_penalty_when_idle_max(void);
  int stat_def_penalty_when_idle(void);
  int stat_def_penalty_when_in_deep_water(void);
  int stat_def_penalty_when_in_shallow_water(void);
  int stat_def_penalty_when_stuck_max(void);
  int stat_def_penalty_when_stuck(void);
  int stat_def_set(int);
  int stat_def_total(void);
  int stat_def(void);
  int stat_dex_bonus_decr(int);
  int stat_dex_bonus_decr(void);
  int stat_dex_bonus_incr(int);
  int stat_dex_bonus_incr(void);
  int stat_dex_bonus_set(int);
  int stat_dex_bonus(void);
  int stat_dex_decr(int);
  int stat_dex_decr(void);
  int stat_dex_incr(int);
  int stat_dex_incr(void);
  int stat_dex_set(int);
  int stat_dex_total(void);
  int stat_dex(void);
  int stat_int_bonus_decr(int);
  int stat_int_bonus_decr(void);
  int stat_int_bonus_incr(int);
  int stat_int_bonus_incr(void);
  int stat_int_bonus_set(int);
  int stat_int_bonus(void);
  int stat_int_decr(int);
  int stat_int_decr(void);
  int stat_int_incr(int);
  int stat_int_incr(void);
  int stat_int_set(int);
  int stat_int_total(void);
  int stat_int(void);
  int stat_luck_bonus_decr(int);
  int stat_luck_bonus_decr(void);
  int stat_luck_bonus_incr(int);
  int stat_luck_bonus_incr(void);
  int stat_luck_bonus_set(int);
  int stat_luck_bonus(void);
  int stat_luck_decr(int);
  int stat_luck_decr(void);
  int stat_luck_incr(int);
  int stat_luck_incr(void);
  int stat_luck_set(int);
  int stat_luck_total(void);
  int stat_luck(void);
  int stat_psi_bonus_decr(int);
  int stat_psi_bonus_decr(void);
  int stat_psi_bonus_incr(int);
  int stat_psi_bonus_incr(void);
  int stat_psi_bonus_set(int);
  int stat_psi_bonus(void);
  int stat_psi_decr(int);
  int stat_psi_decr(void);
  int stat_psi_incr(int);
  int stat_psi_incr(void);
  int stat_psi_set(int);
  int stat_psi_total(void);
  int stat_psi(void);
  int stats02_decr(int);
  int stats02_decr(void);
  int stats02_incr(int);
  int stats02_incr(void);
  int stats02_set(int);
  int stats02(void);
  int stats03_decr(int);
  int stats03_decr(void);
  int stats03_incr(int);
  int stats03_incr(void);
  int stats03_set(int);
  int stats03(void);
  int stats04_decr(int);
  int stats04_decr(void);
  int stats04_incr(int);
  int stats04_incr(void);
  int stats04_set(int);
  int stats04(void);
  int stats05_decr(int);
  int stats05_decr(void);
  int stats05_incr(int);
  int stats05_incr(void);
  int stats05_set(int);
  int stats05(void);
  int stats06_decr(int);
  int stats06_decr(void);
  int stats06_incr(int);
  int stats06_incr(void);
  int stats06_set(int);
  int stats06(void);
  int stats07_decr(int);
  int stats07_decr(void);
  int stats07_incr(int);
  int stats07_incr(void);
  int stats07_set(int);
  int stats07(void);
  int stats09_decr(int);
  int stats09_decr(void);
  int stats09_incr(int);
  int stats09_incr(void);
  int stats09_set(int);
  int stats09(void);
  int stat_str_bonus_decr(int);
  int stat_str_bonus_decr(void);
  int stat_str_bonus_incr(int);
  int stat_str_bonus_incr(void);
  int stat_str_bonus_set(int);
  int stat_str_bonus(void);
  int stat_str_decr(int);
  int stat_str_decr(void);
  int stat_str_incr(int);
  int stat_str_incr(void);
  int stat_str_min(void);
  int stat_str_set(int);
  int stat_str_total(void);
  int stat_str(void);
  int stat_thv_bonus_decr(int);
  int stat_thv_bonus_decr(void);
  int stat_thv_bonus_incr(int);
  int stat_thv_bonus_incr(void);
  int stat_thv_bonus_set(int);
  int stat_thv_bonus(void);
  int stat_thv_decr(int);
  int stat_thv_decr(void);
  int stat_thv_incr(int);
  int stat_thv_incr(void);
  int stat_thv_set(int);
  int stat_thv_total(void);
  int stat_thv(void);
  int stuck_count_decr(int);
  int stuck_count_decr(void);
  int stuck_count_incr(int);
  int stuck_count_incr(void);
  int stuck_count_set(int);
  int stuck_count(void);
  int submerged_offset_get(void);
  int teleport_distance_get(void);
  int teleport_distance(void);
  int temperature_get(void);
  int temperature_max_get(void);
  int temperature_min_get(void);
  int temperature_never_changes(void);
  int temperature_sensitive_to_sudden_changes(void);
  int temperature_sensitive(void);
  int temperature_set(int);
  int thing_size(void);
  int thing_use_distance(Thingp what);
  int tick_prio(void);
  int torch_count(void);
  int total_dmg_for_on_attacking_dmg_acid(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_bite(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_claw(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_cold(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_crush(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_digest(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_drown(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_energy(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_fire(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_heat(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_holy(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_impact(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_lightning(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_magic_drain(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_melee(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_missile(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_nat_att(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_necrosis(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_negation(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_poison(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_stamina(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_stat_att(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_stat_con(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_stat_str(Thingp victim, int damage);
  int total_dmg_for_on_attacking_dmg_water(Thingp victim, int damage);
  int total_dmg_for_on_rcv_dmg_acid(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_bite(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_claw(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_cold(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_crush(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_digest(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_drown(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_energy(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_fire(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_heat(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_holy(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_impact(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_lightning(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_magic_drain(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_melee(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_missile(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_nat_att(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_necrosis(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_negation(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_poison(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_stamina(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_stat_att(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_stat_con(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_stat_str(Thingp hitter, Thingp real_hitter, int damage);
  int total_dmg_for_on_rcv_dmg_water(Thingp hitter, Thingp real_hitter, int damage);
  int unused_chance1_d1000(void);
  int unused_chance2_d1000(void);
  int unused_chance3_d1000(void);
  int unused_chance4_d1000(void);
  int unused_chance5_d1000(void);
  int unused_chance6_d1000(void);
  int value(const Thingp it);
  int value_defensive(Thingp);
  int value_offensive(Thingp);
  int weapon_dmgd_pct(void);
  int weapon_dmg_modify(int damage, Thingp victim = nullptr);
  int weapon_dmg(void);
  int worth_collecting(const Thingp it);
  int worth_collecting(const Thingp it, Thingp *would_need_to_drop);
  // end sort marker6 }

  point3d born_get(void);

  point dest_random_get(int dist = 0);
  point dir_to_direction(void);
  point lunge_to_get(void);
  point vision_source_get(void);
  point where_i_dropped_an_item_last_get(void);

  point where_i_failed_to_collect_last_get(void);
  point where_i_dropped_an_item_last_set(point);
  point where_i_failed_to_collect_last_set(point);

  std::list< ThingId > anything_to_carry(void);
  std::list< ThingId > anything_to_carry_at(point);

  std::size_t light_count(void);

  std::string text_short_and_state_capitalised(size_t max_len = 0);
  std::string text_long_and_state_capitalised(size_t max_len = 0);
  std::string text_short_capitalised(size_t max_len = 0);
  std::string text_long_capitalised(size_t max_len = 0);
  std::string text_short_a_or_an(size_t max_len = 0);
  std::string text_short_the(size_t max_len = 0);
  std::string text_short_The(size_t max_len = 0);
  std::string text_a_or_an(size_t max_len = 0);
  std::string text_A_or_An(size_t max_len = 0);
  std::string text_the(bool include_owner = false);
  std::string text_the_no_dying(bool include_owner = false);
  std::string text_The_no_dying(void);
  std::string text_The(void);
  std::string to_dbg_saved_string(void);
  std::string to_dbg_string(void);
  std::string to_short_string(void);
  std::string to_string(void);

  std::vector< Lightp > &light_get(void);

  struct AgeMap_ *age_map_get(void);
  struct AgeMap_ *interrupt_map_get(void);

  struct Dmap_ *dmap_can_see_old_get(void);
  struct Dmap_ *dmap_can_see_get(void);

  struct FovMap_ *can_see_currently(void);
  struct FovMap_ *can_see_ever(void);

  // begin sort marker7 {
  ts_t ts_anim_delay_end_decr(ts_t);
  ts_t ts_anim_delay_end_decr(void);
  ts_t ts_anim_delay_end_incr(ts_t);
  ts_t ts_anim_delay_end_incr(void);
  ts_t ts_anim_delay_end_set(ts_t);
  ts_t ts_anim_delay_end(void);
  ts_t ts_bounce_begin_decr(ts_t);
  ts_t ts_bounce_begin_decr(void);
  ts_t ts_bounce_begin_incr(ts_t);
  ts_t ts_bounce_begin_incr(void);
  ts_t ts_bounce_begin_set(ts_t);
  ts_t ts_bounce_begin(void);
  ts_t ts_bounce_end_decr(ts_t);
  ts_t ts_bounce_end_decr(void);
  ts_t ts_bounce_end_incr(ts_t);
  ts_t ts_bounce_end_incr(void);
  ts_t ts_bounce_end_set(ts_t);
  ts_t ts_bounce_end(void);
  ts_t ts_fadeup_begin_decr(ts_t);
  ts_t ts_fadeup_begin_decr(void);
  ts_t ts_fadeup_begin_incr(ts_t);
  ts_t ts_fadeup_begin_incr(void);
  ts_t ts_fadeup_begin_set(ts_t);
  ts_t ts_fadeup_begin(void);
  ts_t ts_fadeup_end_decr(ts_t);
  ts_t ts_fadeup_end_decr(void);
  ts_t ts_fadeup_end_incr(ts_t);
  ts_t ts_fadeup_end_incr(void);
  ts_t ts_fadeup_end_set(ts_t);
  ts_t ts_fadeup_end(void);
  ts_t ts_fall_begin_decr(ts_t);
  ts_t ts_fall_begin_decr(void);
  ts_t ts_fall_begin_incr(ts_t);
  ts_t ts_fall_begin_incr(void);
  ts_t ts_fall_begin_set(ts_t);
  ts_t ts_fall_begin(void);
  ts_t ts_fall_end_decr(ts_t);
  ts_t ts_fall_end_decr(void);
  ts_t ts_fall_end_incr(ts_t);
  ts_t ts_fall_end_incr(void);
  ts_t ts_fall_end_set(ts_t);
  ts_t ts_fall_end(void);
  ts_t ts_flip_start_decr(ts_t);
  ts_t ts_flip_start_decr(void);
  ts_t ts_flip_start_get(void);
  ts_t ts_flip_start_incr(ts_t);
  ts_t ts_flip_start_incr(void);
  ts_t ts_flip_start_set(ts_t);
  ts_t ts_lunge_begin_decr(ts_t);
  ts_t ts_lunge_begin_decr(void);
  ts_t ts_lunge_begin_incr(ts_t);
  ts_t ts_lunge_begin_incr(void);
  ts_t ts_lunge_begin_set(ts_t);
  ts_t ts_lunge_begin(void);
  ts_t ts_lunge_end_decr(ts_t);
  ts_t ts_lunge_end_decr(void);
  ts_t ts_lunge_end_incr(ts_t);
  ts_t ts_lunge_end_incr(void);
  ts_t ts_lunge_end_set(ts_t);
  ts_t ts_lunge_end(void);
  // end sort marker7 }

  int tick_last_location_check_decr(uint32_t);
  int tick_last_location_check_decr(void);
  int tick_last_location_check_incr(uint32_t);
  int tick_last_location_check_incr(void);
  int tick_last_location_check_set(uint32_t);
  int tick_last_location_check(void);

  int tick_last_i_was_attacked_decr(uint32_t);
  int tick_last_i_was_attacked_decr(void);
  int tick_last_i_was_attacked_incr(uint32_t);
  int tick_last_i_was_attacked_incr(void);
  int tick_last_i_was_attacked_set(uint32_t);
  int tick_last_i_was_attacked(void);

  int tick_last_gas_poison_exposure_decr(uint32_t);
  int tick_last_gas_poison_exposure_decr(void);
  int tick_last_gas_poison_exposure_incr(uint32_t);
  int tick_last_gas_poison_exposure_incr(void);
  int tick_last_gas_poison_exposure_set(uint32_t);
  int tick_last_gas_poison_exposure(void);

  int tick_last_gas_explosive_exposure_decr(uint32_t);
  int tick_last_gas_explosive_exposure_decr(void);
  int tick_last_gas_explosive_exposure_incr(uint32_t);
  int tick_last_gas_explosive_exposure_incr(void);
  int tick_last_gas_explosive_exposure_set(uint32_t);
  int tick_last_gas_explosive_exposure(void);

  int tick_last_gas_paralysis_exposure_decr(uint32_t);
  int tick_last_gas_paralysis_exposure_decr(void);
  int tick_last_gas_paralysis_exposure_incr(uint32_t);
  int tick_last_gas_paralysis_exposure_incr(void);
  int tick_last_gas_paralysis_exposure_set(uint32_t);
  int tick_last_gas_paralysis_exposure(void);

  int tick_last_gas_confusion_exposure_decr(uint32_t);
  int tick_last_gas_confusion_exposure_decr(void);
  int tick_last_gas_confusion_exposure_incr(uint32_t);
  int tick_last_gas_confusion_exposure_incr(void);
  int tick_last_gas_confusion_exposure_set(uint32_t);
  int tick_last_gas_confusion_exposure(void);

  int tick_last_gas_healing_exposure_decr(uint32_t);
  int tick_last_gas_healing_exposure_decr(void);
  int tick_last_gas_healing_exposure_incr(uint32_t);
  int tick_last_gas_healing_exposure_incr(void);
  int tick_last_gas_healing_exposure_set(uint32_t);
  int tick_last_gas_healing_exposure(void);

  int tick_last_i_attacked_decr(uint32_t);
  int tick_last_i_attacked_decr(void);
  int tick_last_i_attacked_incr(uint32_t);
  int tick_last_i_attacked_incr(void);
  int tick_last_i_attacked_set(uint32_t);
  int tick_last_i_attacked(void);

  int tick_last_i_tried_to_attack_decr(uint32_t);
  int tick_last_i_tried_to_attack_decr(void);
  int tick_last_i_tried_to_attack_incr(uint32_t);
  int tick_last_i_tried_to_attack_incr(void);
  int tick_last_i_tried_to_attack_set(uint32_t);
  int tick_last_i_tried_to_attack(void);

  int tick_last_level_change_decr(uint32_t);
  int tick_last_level_change_decr(void);
  int tick_last_level_change_incr(uint32_t);
  int tick_last_level_change_incr(void);
  int tick_last_level_change_set(uint32_t);
  int tick_last_level_change(void);

  int tick_last_did_something_decr(uint32_t);
  int tick_last_did_something_decr(void);
  int tick_last_did_something_incr(uint32_t);
  int tick_last_did_something_incr(void);
  int tick_last_did_something_set(uint32_t);
  int tick_last_did_something(void);

  int tick_last_decr(uint32_t);
  int tick_last_decr(void);
  int tick_last_incr(uint32_t);
  int tick_last_incr(void);
  int tick_last_set(uint32_t);
  int tick_last(void);

  int tick_last_seen_by_player_decr(uint32_t);
  int tick_last_seen_by_player_decr(void);
  int tick_last_seen_by_player_incr(uint32_t);
  int tick_last_seen_by_player_incr(void);
  int tick_last_seen_by_player_set(uint32_t);
  int tick_last_seen_by_player(void);

  int tick_born_decr(uint32_t);
  int tick_born_decr(void);
  int tick_born_incr(uint32_t);
  int tick_born_incr(void);
  int tick_born_set(uint32_t);
  int tick_born(void);

  int tick_last_dropped_decr(uint32_t);
  int tick_last_dropped_decr(void);
  int tick_last_dropped_incr(uint32_t);
  int tick_last_dropped_incr(void);
  int tick_last_dropped_set(uint32_t);
  int tick_last_dropped(void);

  int tick_last_teleported_decr(uint32_t);
  int tick_last_teleported_decr(void);
  int tick_last_teleported_incr(uint32_t);
  int tick_last_teleported_incr(void);
  int tick_last_teleported_set(uint32_t);
  int tick_last_teleported(void);

  int tick_last_escape_decr(uint32_t);
  int tick_last_escape_decr(void);
  int tick_last_escape_incr(uint32_t);
  int tick_last_escape_incr(void);
  int tick_last_escape_set(uint32_t);
  int tick_last_escape(void);

  int tick_resurrect_when_decr(int);
  int tick_resurrect_when_decr(void);
  int tick_resurrect_when_incr(int);
  int tick_resurrect_when_incr(void);
  int tick_resurrect_when_set(int);
  int tick_resurrect_when(void);

  int movement_remaining_decr(int);
  int movement_remaining_decr(void);
  int movement_remaining_incr(int);
  int movement_remaining_incr(void);
  int movement_remaining_set(int);
  int movement_remaining(void);

  int physical_training_decr(int);
  int physical_training_decr(void);
  int physical_training_incr(int);
  int physical_training_incr(void);
  int physical_training_set(int);
  int physical_training(void);

  uint8_t blit_begin_reflection_submerged(void);
  uint8_t blit_begin_submerged(bool scissors = true);
  uint8_t terrain_cost_get(point p);
  uint8_t is_dir_bl(void);
  uint8_t is_dir_br(void);
  uint8_t is_dir_down(void);
  uint8_t is_dir_left(void);
  uint8_t is_dir_none(void);
  uint8_t is_dir_right(void);
  uint8_t is_dir_tl(void);
  uint8_t is_dir_tr(void);
  uint8_t is_dir_up(void);
  uint8_t is_visible(void);
  uint8_t z_prio(void);

  // begin sort marker8 {
  void achieve_goals_in_death(void);
  void achieve_goals_in_life(void);
  void acid_tick(void);
  void add_attacker(Thingp attacker, bool is_recursing = false);
  void add_avoid(Thingp attacker);
  void add_collect_penalty(Thingp item);
  void add_enemy(Thingp attacker, bool is_recursing = false);
  void add_enemy(Tpp attacker);
  void add_friend(Thingp attacker);
  void add_friend(Tpp attacker);
  void add_goal_penalty(Thingp attacker);
  void add_random_enchants(void);
  void add_random_runic(void);
  void ai_choose_can_see_goals(std::multiset< Goal > &goals, int minx, int miny, int maxx, int maxy);
  void ai_choose_search_goals(std::multiset< Goal > &goals, int search_type);
  void ai_get_next_hop(void);
  void ai_log(const std::string &msg);
  void ai_log(const std::string &msg, Thingp it);
  void animate_choose_tile(Tilemap *tmap, std::vector< Tilep > *tiles, bool *next_frame_please);
  void animate(void);
  void attackers_tick(void);
  void auto_equip(void);
  void avoid_tick(void);
  void awake(void);
  void barrel_tick(void);
  void blinded_tick(void);
  void blinded_update(void);
  void blit_ascii_adjust_color(color &c, bool fg, bool leftbar);
  void blit_ascii_adjust_color_hue(color &c, bool fg);
  void blit_ascii_at(point tl, bool lit = true, bool leftbar = false);
  void blit_ascii_outline(point tl, bool lit = true, bool leftbar = false);
  void blit_ascii(point tl, point br, point p, bool leftbar = false);
  void blit_end_reflection_submerged(uint8_t submerged);
  void blit_end_submerged(uint8_t submerged);
  void blit_floor_chasm(point tl, point br, const ThingTiles *tiles);
  void blit_internal(int fbo, point &blit_tl, point &blit_br, const Tilep tile, color c, BlitOptions *);
  void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile, const point tl, const point br);
  void blit_outline_highlight(const Tilep tile, const point blit_tl, const point blit_br);
  void blit_pixelart_do(int fbo, BlitOptions *);
  void blit_pixelart(int fbo);
  void blit_player_owned_shadow(const Tpp &tp, const Tilep &tile, const point tl, const point br);
  void blit_shadow(const Tpp &tp, const Tilep &tile, const point tl, const point br);
  void blit_text(std::string const &, color c, point tl, point br);
  void blit_tile_at(point tl, bool lit = true, bool leftbar = false);
  void blit_to_tex(void);
  void blit_upside_down(int fbo);
  void blit_wall_cladding(point tl, point br, const ThingTiles *tiles);
  void blit_wall_shadow(point tl, point br, const ThingTiles *tiles);
  void block_of_ice_tick(void);
  void bodypart_remove(int equip);
  void born_set(point3d);
  void botcon(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void botcon_(const char *fmt, va_list args); // compile error without
  void bounce_count_set(int);
  void bounce_fade_set(float);
  void bounce_height_set(float);
  void brazier_tick(void);
  void buff_activate(Thingp what);
  void buff_deactivate(Thingp what);
  void buff_remove_all(void);
  void buff_tick(void);
  void burnt_set(void);
  void can_see_you(point);
  void change_state(int new_state, const std::string &why);
  void chasm_tick(void);
  void check_all_carried_items_are_owned(void);
  void check_all_carried_maps(void);
  void clear_age_map(void);
  void clear_can_see_currently(void);
  void clear_can_see_ever(void);
  void clear_dmap_can_see_old(void);
  void clear_dmap_can_see(void);
  void clear_interrupt_map(void);
  void clear_move_path(const std::string &why);
  void collect_penalty_tick(void);
  void con(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void con_(const char *fmt, va_list args); // compile error without
  void confused_tick(void);
  void confused_update(void);
  void corrode_tick(void);
  void cursor_hover_over_check(void);
  void dbg_(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void dead(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void dead_(const char *fmt, va_list args); // compile error without
  void dead(const std::string &);
  void dead_reason_set(const std::string &);
  void dead_scheduled(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void dead_scheduled(const std::string &);
  void dead(Thingp defeater, const char *fmt, ...) CHECK_FORMAT_STR(printf, 3, 4);
  void dead_(Thingp defeater, const char *fmt, va_list args);
  void dead(Thingp defeater, std::string &);
  void debuff_activate(Thingp what);
  void debuff_deactivate(Thingp what);
  void debuff_remove_all(void);
  void debuff_tick(void);
  void delete_laser(void);
  void delete_lights(void);
  void delete_particle(void);
  void delete_projectile(void);
  void destroyed(void);
  void destroy_minions(Thingp defeater);
  void destroy_spawned(Thingp defeater);
  void destroy(void);
  void die(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void die_(const char *fmt, va_list args); // compile error without
  void dir_set_bl(void);
  void dir_set_br(void);
  void dir_set_down(void);
  void dir_set_left(void);
  void dir_set_none(void);
  void dir_set_right(void);
  void dir_set_tl(void);
  void dir_set_tr(void);
  void dir_set_up(void);
  void discord(void);
  void discovered_set(bool val);
  void discovered_set(Thingp what, bool val);
  void dmap_modify_terrain_cost(point p, uint8_t *d, bool include_monst, bool include_dislike);
  void drop_all(void);
  void dump_equip(void);
  void dump(std::string prefix, std::ostream &out);
  void enchant_common(Thingp);
  void enemies_tick(void);
  void entranced_tick(void);
  void entranced_update(void);
  void equip_carry_anim_id_set(ThingId equip_carry_anim_id, int equip);
  void equip_carry_anim_set(Thingp equip_carry_anim, int equip);
  void equip_remove_anim(int equip);
  void equip_use_anim_id_set(ThingId gfx_anim_use_id, int equip);
  void equip_use_anim_set(Thingp gfx_anim_use, int equip);
  void equip_use_offset_get(int *dx, int *dy, int equip);
  void err(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void err_(const char *fmt, va_list args); // compile error without
  void fadeup_fade_set(float);
  void fadeup(float fadeup_height, float fadeup_fade, ts_t ms);
  void fadeup_height_set(float);
  void fall_height_set(float);
  void fall_into_the_void(void);
  void floating_tick(void);
  void frozen_set(void);
  void frozen_unset(bool quiet = false);
  void gas_confused_tick(void);
  void gas_explosive_tick(void);
  void gas_healing_tick(void);
  void gas_paralysis_tick(void);
  void gas_poison_tick(void);
  void gc(void);
  void goal_penalty_tick(void);
  void grass_tick(void);
  void hide_callback(void);
  void hide(const std::string &);
  void hooks_remove_from(Thingp);
  void hooks_remove(void);
  void hunger_clock_tick(void);
  void hunger_update(void);
  void inherit_from(Thingp it);
  void init_hue(void);
  void init(Levelp, const std::string &name, point at, Thingp owner = nullptr);
  void init_lights(void);
  void interpolated_at_set(fpoint v);
  void inventory_particle(Thingp what, int slot);
  void inventory_particle(Thingp what, int slot, Thingp particle_target);
  void invisible_tick(void);
  void is_stuck_update(void);
  void jump_end(void);
  void killed(Thingp defeater, const char *reason);
  void killed(Thingp defeater, const std::string &reason);
  void leader_set(Thingp leader);
  void leader_unset(void);
  void level_change(Levelp);
  void level_enter(bool rejoin = false);
  void level_leave(void);
  void level_pop(void);
  void level_push(void);
  void level_rejoin(void);
  void lifespan_tick(void);
  void light_distance_upd_with_torch_effect(uint8_t &light_dist);
  void light_dist_including_torch_effect_get(uint8_t &light_dist);
  void location_check_me(void);
  void location_check(Thingp filter_to = nullptr);
  void log(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void log_(const char *fmt, va_list args); // compile error without
  void lunge(point tt);
  void lunge_to_set(point);
  void magic_boost(int v);
  void map_beast_check(void);
  void map_beast_count_set(int);
  void map_treasure_check(void);
  void map_treasure_count_set(int);
  void mob_set(Thingp mob);
  void mob_unset(void);
  void move_carried_items_immediately(void);
  void move_carried_items(void);
  void move_delta(point);
  void move_finish(void);
  void move_set_dir_from_delta(point);
  void move_set_dir_from_dest_or_delta(point delta);
  void move_set_dir_from_target(Thingp target);
  void move_speed_curr_set(int);
  void move_to_immediately(point to);
  void move_to(point to);
  void msg(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void msg_set(const std::string &);
  void necrosis_tick(void);
  void negation_dmg(int damage, bool &is_killed);
  void new_aip(void);
  void new_infop(void);
  void new_itemsp(void);
  void new_light(point offset, int light_dist);
  void new_light(point offset, int light_dist, color col, int fbo);
  void noop(void);
  void notify_followers_of_death_of_my_leader(void);
  void notify_of_death_of_my_leader(void);
  void on_activated(Thingp victim = nullptr);
  void on_born(void);
  void on_close(void);
  void on_death_of_a_follower(Thingp leader);
  void on_death_of_my_leader(void);
  void on_dropped(void);
  void on_eaten(Thingp what);
  void on_eating(Thingp what, int bite);
  void on_enchant(void);
  void on_enter(Thingp victim = nullptr);
  void on_equip(Thingp what);
  void on_fall_begin(void);
  void on_fall(void);
  void on_final_use(Thingp what);
  void on_final_use(Thingp what, Thingp target);
  void on_fire_unset(void);
  void on_fire(void);
  void on_hit_and_now_dead(Thingp hitter, Thingp real_hitter, bool crit, int dmg);
  void on_hit_and_still_alive(Thingp hitter, Thingp real_hitter, bool crit, int dmg);
  void on_hit_dodge_do(Thingp hitter);
  void on_jump(void);
  void on_lifespan_tick(Thingp hitter);
  void on_move_player(void);
  void on_move(void);
  void on_open(void);
  void on_owner_add(Thingp owner);
  void on_owner_unset(Thingp owner);
  void on_polymorphed(void);
  void on_pre_teleport(void);
  void on_resting(void);
  void on_stealing(Thingp from, Thingp what);
  void on_stuck(void);
  void on_swing(Thingp what);
  void on_targeted(point target);
  void on_targeted_radially(void);
  void on_targeted_radial(void);
  void on_targeted(void);
  void on_teleport(void);
  void on_thrown_callback(ThingId owner_id_when_thrown);
  void on_thrown(ThingId owner_id_when_thrown);
  void on_unequip(Thingp what);
  void on_use_skill(Thingp what);
  void on_use_skill(Thingp what, Thingp target);
  void on_use(Thingp what);
  void on_use(Thingp what, Thingp target);
  void on_waiting(void);
  void on_you_are_declared_a_follower(Thingp leader);
  void on_you_are_declared_leader(void);
  void on_you_nat_attack_attempt(void);
  void on_you_nat_attack_success(void);
  void ooze_tick(void);
  void owner_set(Thingp owner);
  void owner_unset(void);
  void paralysis_tick(void);
  void paralysis_update(void);
  void path_shorten(std::vector< point > &path);
  void physical_training_tick(void);
  void place_blood(bool force = false);
  void plant_tick(void);
  void poisoned(void);
  void poison_reason_set(const std::string &);
  void poison_tick(void);
  void polymorph(Tpp);
  void popup(const std::string &);
  void portal_tick(void);
  void rage_tick(void);
  void reinit(void);
  void release_followers(void);
  void remove_all_references(void);
  void reset_collect_penalty(Thingp attacker);
  void reset_goal_penalty(Thingp attacker);
  void resting(void);
  void resurrect_stop(void);
  void resurrect_tick(void);
  void rotting(void);
  void runic_name_set(const std::string &);
  void score_add(Thingp victim = nullptr);
  void secret_door_tick(void);
  void show_botcon_description(void);
  void skill_activate(Thingp what);
  void skill_deactivate(Thingp what);
  void skill_remove_all(void);
  void sleep(void);
  void solid_rock_tick(void);
  void spawned_newborn(Thingp it);
  void spawner_set(Thingp spawner_owner);
  void spawner_unset(void);
  void spell_activate(Thingp what);
  void spell_deactivate(Thingp what);
  void spell_of_holding_tick(void);
  void spell_of_sanctuary_tick(void);
  void spell_remove_all(void);
  void stamina_boost(int v);
  void stats_tick(void);
  void stuck(const std::string &why);
  void submerged_offset_set(int);
  void teleport_end(void);
  void temperature_decr(int);
  void temperature_decr(void);
  void temperature_incr(int);
  void temperature_incr(void);
  void temperature_tick(void);
  void tick(void);
  void tiles_get(void);
  void topcon(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void topcon_(const char *fmt, va_list args); // compile error without
  void trap_tick(void);
  void try_to_carry(const std::list< Thingp > &items, CarryOptions);
  void unleash_minions(void);
  void unleash_spawners_things(void);
  void unstuck(void);
  void update_all(void);
  void update_interpolated_position(void);
  void update_light(void);
  void update_pos(point, bool immediately);
  void update_tick(void);
  void update(void);
  void used(Thingp w, Thingp target, UseOptions &);
  void visible_callback(void);
  void visible(const std::string &);
  void waiting(void);
  void water_tick(void);
  void weapon_check_for_dmg(Thingp weapon, Thingp victim = nullptr);
  void weapon_sheath(void);
  void wobble(float wobble);
  void wobble_set(float);
  // end sort marker8 }

  const std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > *stat_const_bag(void);

  std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > *bag_get(void);

  static std::function< int(Thingp) > matches_to_func(const std::string &what);

  //
  // Followers are things that follow a leaded, typically a captain or some sort.
  //
  std::list< Thingp > all_followers_get(void);

  //
  // Minions are under the control of a mob
  //
  std::list< Thingp > all_minions_get(void);

  std::pair< Path, Path > astar_solve(const class Goal *goal, char path_debug, point s, point g, const Dmap *d,
                                      bool allow_diagonals);

  ThingInfop  get_or_alloc_infop(void);
  ThingItemsp get_or_alloc_itemsp(void);
  ThingAip    get_or_alloc_aip(void);

  inline ThingInfop maybe_infop(void) { return _infop; }

  inline ThingItemsp maybe_itemsp(void) { return _itemsp; }

  inline ThingAip maybe_aip(void) { return _aip; }

  inline ThingInfop infop(void) { return _infop; }

  inline ThingItemsp itemsp(void) { return _itemsp; }

  inline ThingAip aip(void) { return _aip; }

  std::vector< ThingId > copy_of_carrying(void);

  bool victim_attack_best_attempt_1(Thingp item, point at, Thingp *best, point *best_hit_at,
                                    std::vector< point > &all_deltas, ThingAttackOptionsp);
  bool victim_attack_best_attempt_2(Thingp item, point at, Thingp *best, point *best_hit_at,
                                    std::vector< point > &all_deltas, ThingAttackOptionsp);
  bool victim_attack_best_attempt_3(Thingp item, point at, Thingp *best, point *best_hit_at,
                                    std::vector< point > &all_deltas, ThingAttackOptionsp);
  bool victim_attack_choose_best(Thingp item, point at, Thingp *best, point *best_hit_at, ThingAttackOptionsp);
  bool victim_attack_found_best(int equip, Thingp item, Thingp best, point best_hit_at, ThingAttackOptionsp);

  int gfx_pixelart_attack_anim(void);
} Thing;

bool things_overlap(Thingp t, Thingp o);
bool things_overlap(Thingp t, fpoint t_at, Thingp o);

int bag_estimate_volume(const std::list< Thingp > &items);

std::string equip_name(int equip);
std::string bodypart_name(int bodypart);

extern Thingp g_debug_thing;

#endif // _MY_THING_HPP_
