//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "minilzo.hpp"
#include "my_alloc.hpp"
#include "my_array_bounds_check.hpp"
#include "my_globals_extra.hpp"
#include "my_sdl_proto.hpp"
#include "my_serialize.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_error.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_progress_bar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_topcon.hpp"

WidPopup *wid_load;
void      wid_load_destroy(void);

static ts_t                           old_ts_created;
static ts_t                           new_ts_created;
static ts_t                           T;
static std::string                    game_load_error;
bool                                  game_load_headers_only;
extern int                            GAME_SAVE_MARKER_EOL;
extern int                            GAME_SAVE_MARKER_CONFIG;
std::array< bool, UI_WID_SAVE_SLOTS > slot_valid;

#define READ_MAGIC(what, m)                                                                                          \
  {                                                                                                                  \
    uint32_t magic;                                                                                                  \
    in >> bits(magic);                                                                                               \
    if (magic != m) {                                                                                                \
      game_load_error = "bad " what " magic expected: " + std::to_string(m) + " got " + std::to_string(magic);       \
      return in;                                                                                                     \
    }                                                                                                                \
  }

//
// Save timestamps as a delta we can restore.
//
static ts_t load(ts_t T)
{
  TRACE_AND_INDENT();
  if (! T) {
    return 0;
  }
  return (T - old_ts_created + new_ts_created);
}

std::istream &operator>>(std::istream &in, Bits< SDL_Keysym & > my)
{
  TRACE_AND_INDENT();
  in >> bits(my.t.scancode);
  in >> bits(my.t.sym);
  in >> bits(my.t.mod);
  in >> bits(my.t.unused);
  return in;
}

std::istream &operator>>(std::istream &in, Bits< ThingInfop & > my)
{
  TRACE_AND_INDENT();
  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  // clang-format off
   in >> bits(my.t->attack_num);
   in >> bits(my.t->born);
   in >> bits(my.t->bounce_fade);
   in >> bits(my.t->bounce_height);
   in >> bits(my.t->capacity_height);
   in >> bits(my.t->capacity_width);
   in >> bits(my.t->damage_this_tick);
   in >> bits(my.t->dead_reason);
   in >> bits(my.t->distance_throw);
   in >> bits(my.t->distance_spell_cast);
   in >> bits(my.t->enchant);
   in >> bits(my.t->enchant_max);
   in >> bits(my.t->fadeup_fade);
   in >> bits(my.t->fadeup_height);
   in >> bits(my.t->fall_height);
   in >> bits(my.t->followers);
   in >> bits(my.t->gold);
   in >> bits(my.t->health);
   in >> bits(my.t->health_max);
   in >> bits(my.t->hunger);
   in >> bits(my.t->jump_distance_bonus);
   in >> bits(my.t->keys);
   in >> bits(my.t->leader_id);
   in >> bits(my.t->lifespan);
   in >> bits(my.t->light_col);
   in >> bits(my.t->light_dist);
   in >> bits(my.t->lunge_to);
   in >> bits(my.t->magic);
   in >> bits(my.t->magic_max);
   in >> bits(my.t->minions);
   in >> bits(my.t->mob_id);
   in >> bits(my.t->monst_state);
   in >> bits(my.t->move_count);
   in >> bits(my.t->move_penalty);
   in >> bits(my.t->movement_remaining);
   in >> bits(my.t->move_speed_bonus);
   in >> bits(my.t->move_speed_curr);
   in >> bits(my.t->msg);
   in >> bits(my.t->necrosis);
   in >> bits(my.t->noise);
   in >> bits(my.t->nutrition);
   in >> bits(my.t->on_fire_id_anim);
   in >> bits(my.t->owned);
   in >> bits(my.t->owner_id);
   in >> bits(my.t->physical_training);
   in >> bits(my.t->poison);
   in >> bits(my.t->poison_reason);
   in >> bits(my.t->runic_name);
   in >> bits(my.t->prev_light_dist);
   in >> bits(my.t->score);
   in >> bits(my.t->shove_bonus);
   in >> bits(my.t->spawned);
   in >> bits(my.t->spawner_owner_id);
   in >> bits(my.t->stamina);
   in >> bits(my.t->stamina_max);
   in >> bits(my.t->stat_att);
   in >> bits(my.t->stat_att_bonus);
   in >> bits(my.t->stat_con);
   in >> bits(my.t->stat_con_bonus);
   in >> bits(my.t->stat_def);
   in >> bits(my.t->stat_def_bonus);
   in >> bits(my.t->stat_dex);
   in >> bits(my.t->stat_dex_bonus);
   in >> bits(my.t->stat_int);
   in >> bits(my.t->stat_int_bonus);
   in >> bits(my.t->stat_luck);
   in >> bits(my.t->stat_luck_bonus);
   in >> bits(my.t->stat_psi);
   in >> bits(my.t->stat_psi_bonus);
   in >> bits(my.t->stats02);
   in >> bits(my.t->stats03);
   in >> bits(my.t->stats04);
   in >> bits(my.t->stats05);
   in >> bits(my.t->stats06);
   in >> bits(my.t->stats07);
   in >> bits(my.t->stats09);
   in >> bits(my.t->stat_str);
   in >> bits(my.t->stat_str_bonus);
   in >> bits(my.t->stat_thv);
   in >> bits(my.t->stat_thv_bonus);
   in >> bits(my.t->submerged_offset);
   in >> bits(my.t->tick_born);
   in >> bits(my.t->tick_last_awoke);
   in >> bits(my.t->tick_last_did_something);
   in >> bits(my.t->tick_last);
   in >> bits(my.t->tick_last_dropped);
   in >> bits(my.t->tick_last_escape);
   in >> bits(my.t->tick_last_gas_healing_exposure);
   in >> bits(my.t->tick_last_gas_poison_exposure);
   in >> bits(my.t->tick_last_i_attacked);
   in >> bits(my.t->tick_last_i_tried_to_attack);
   in >> bits(my.t->tick_last_i_was_attacked);
   in >> bits(my.t->tick_last_level_change);
   in >> bits(my.t->tick_last_location_check);
   in >> bits(my.t->tick_last_seen_by_player);
   in >> bits(my.t->tick_last_teleported);
   in >> bits(my.t->tick_resurrect_when);
   in >> bits(my.t->wobble);
  // clang-format on
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  // clang-format off
  in >> bits(T); my.t->ts_anim_delay_end = load(T);
  in >> bits(T); my.t->ts_bounce_begin = load(T);
  in >> bits(T); my.t->ts_bounce_end = load(T);
  in >> bits(T); my.t->ts_fadeup_begin = load(T);
  in >> bits(T); my.t->ts_fadeup_end = load(T);
  in >> bits(T); my.t->ts_fall_begin = load(T);
  in >> bits(T); my.t->ts_fall_end = load(T);
  in >> bits(T); my.t->ts_flip_start = load(T);
  in >> bits(T); my.t->ts_lunge_begin = load(T);
  in >> bits(T); my.t->ts_lunge_end = load(T);
  // clang-format on
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  // clang-format off
   in >> bits(my.t->bounce_count);
   in >> bits(my.t->charge_count);
   in >> bits(my.t->sleep_count);
   in >> bits(my.t->damaged_count);
   in >> bits(my.t->map_treasure_count);
   in >> bits(my.t->map_beast_count);
  // clang-format on
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  return in;
}

std::istream &operator>>(std::istream &in, Bits< ThingItemsp & > my)
{
  TRACE_AND_INDENT();
  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  in >> bits(my.t->equip_id);
  in >> bits(my.t->equip_id_carry_anim);
  in >> bits(my.t->equip_id_use_anim);
  in >> bits(my.t->bodypart_id);
  in >> bits(my.t->bag_position);
  in >> bits(my.t->last_bag_position);
  in >> bits(my.t->where_i_dropped_an_item_last);
  in >> bits(my.t->where_i_failed_to_collect_last);
  in >> bits(my.t->bag);
  in >> bits(my.t->carrying);
  in >> bits(my.t->skills);
  in >> bits(my.t->spells);
  in >> bits(my.t->buffs);
  in >> bits(my.t->debuffs);
  in >> bits(my.t->inventory_shortcuts);
  in >> bits(my.t->skillbox_id);
  in >> bits(my.t->spellbox_id);
  in >> bits(my.t->buffbox_id);
  in >> bits(my.t->debuffbox_id);
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  return in;
}

std::istream &operator>>(std::istream &in, Bits< ThingAip & > my)
{
  TRACE_AND_INDENT();
  in >> bits(my.t->age_map.val);
  in >> bits(my.t->dmap_can_see_old.val);
  in >> bits(my.t->interrupt_map.val);
  in >> bits(my.t->dmap_can_see.val);
  in >> bits(my.t->can_see_currently.can_see);
  in >> bits(my.t->can_see_ever.can_see);
  in >> bits(my.t->thing_enemies);
  in >> bits(my.t->thing_attackers);
  in >> bits(my.t->perma_enemies);
  in >> bits(my.t->thing_friends);
  in >> bits(my.t->perma_friends);
  in >> bits(my.t->goal_penalty);
  in >> bits(my.t->collect_penalty);
  in >> bits(my.t->avoid);
  in >> bits(my.t->move_path);
  in >> bits(my.t->wander_dest);
  in >> bits(my.t->idle_count);
  in >> bits(my.t->stuck_count);
  in >> bits(my.t->paralysis_count);
  return in;
}

std::istream &operator>>(std::istream &in, Bits< Thingp & > my)
{
  TRACE_AND_INDENT();
  auto start = in.tellg();

  READ_MAGIC("thing begin", THING_MAGIC_BEGIN + (int) sizeof(Thing));

  std::string name;
  in >> bits(name);
  auto tpp = tp_find(name);
  if (unlikely(! tpp)) {
    game_load_error = "unknown thing name '" + name;
    return in;
  }

  my.t->tp_id = tpp->id;
  // CON("READ %s %d", name.c_str(), tpp->id);

  uint64_t bits64 = 0;

  my.t->_infop            = nullptr;
  bool monst_info_present = false;
  in >> bits(monst_info_present);
  if (monst_info_present) {
    my.t->new_infop();
    in >> bits(my.t->_infop);
  }

  my.t->_itemsp           = nullptr;
  bool monst_item_present = false;
  in >> bits(monst_item_present);
  if (monst_item_present) {
    my.t->new_itemsp();
    in >> bits(my.t->_itemsp);
  }

  my.t->_aip            = nullptr;
  bool monst_ai_present = false;
  in >> bits(monst_ai_present);
  if (monst_ai_present) {
    my.t->new_aip();
    in >> bits(my.t->_aip);
  }

  /////////////////////////////////////////////////////////////////////////
  // Keep these in the same order as my_thing.h and save/load
  /////////////////////////////////////////////////////////////////////////
  in >> bits(my.t->tp_id);
  if (my.t->tp_id <= 0) {
    game_load_error = "loaded a thing with no TP ID";
    return in;
  }

  if (! tp_find(my.t->tp_id)) {
    game_load_error = "loaded a thing with invalid TP ID";
    return in;
  }

  in >> bits(my.t->id.id);
  if (! my.t->id.id) {
    game_load_error = "loaded a thing with no ID";
    return in;
  }

  /////////////////////////////////////////////////////////////////////////
  // Keep these in the same order as my_thing.h and save/load
  /////////////////////////////////////////////////////////////////////////
  in >> bits(my.t->interpolated_at);
  in >> bits(my.t->last_at);
  in >> bits(my.t->curr_at);
  in >> bits(my.t->last_attached);
  in >> bits(my.t->last_ascii_at);
  in >> bits(my.t->last_blit_br);
  in >> bits(my.t->last_blit_tl);
  in >> bits(my.t->last_blit_at);
  in >> bits(T);
  my.t->ts_next_frame = load(T);
  in >> bits(my.t->tile_curr);
  in >> bits(my.t->z_depth);
  in >> bits(my.t->laser_count);
  in >> bits(my.t->temperature);
  in >> bits(my.t->blit_bg_color);
  in >> bits(my.t->blit_fg_color);
  uint8_t dir;
  in >> dir;
  my.t->dir = dir;

  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  in >> bits(bits64);
  int shift = 0;
  // clang-format off
  // begin sort marker1 {
             my.t->corpse_cleanup                               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->gfx_ascii_animated                           = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->gfx_pixelart_animated                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->has_attacked_player                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->has_ever_moved                               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->has_light                                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->has_projectile                               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->has_seen_player_msg_shown                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  // end sort marker1 }
  // clang-format on

  in >> bits(bits64);
  shift = 0;
  // clang-format off
  // begin sort marker2 {
             my.t->is_activated                                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_attached                                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_being_destroyed                           = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_bouncing                                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_burnt                                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_changing_level                            = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_dead                                      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_discovered                                = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_drained                                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_dying                                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_facing_left                               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_fadeup                                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_falling                                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_frozen                                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_hidden                                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_hunger_level_gorged                       = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_hunger_level_hungry                       = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_hunger_level_satiated                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_hunger_level_starving                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_invisible_                                = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_jumping                                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_key_in_lock                               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_minion_set                                = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_moving                                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_open                                      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_raging_currently                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_resurrected                               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_resurrecting                              = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_resurrection_blocked                      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_ring2                                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_scheduled_for_death                       = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_scheduled_for_gc                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_scheduled_for_jump_end                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_seen_by_player_msg_shown                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_sleeping                                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_teleporting                               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_the_grid                                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_the_player                                = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_visible_to_player                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_waiting                                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_waiting_to_ascend_dungeon                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_waiting_to_ascend_sewer                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_waiting_to_descend_dungeon                = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_waiting_to_descend_sewer                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_waiting_to_leave_level_has_completed_fall = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->is_wounded_msg                               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->was_frozen                                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  // end sort marker2 }
  // clang-format on

  in >> bits(bits64);
  shift = 0;
  // clang-format off
  // begin sort marker3 {
             my.t->i_set_is_able_to_amplify_footsteps     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_able_to_dampen_footsteps      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_acid                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_ascend_dungeon                = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_ascend_sewer                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_attackable_by_monst           = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_attackable_by_player          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_barrel                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_basalt                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_block_of_ice                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_brazier                       = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_bridge                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_burnable                      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_carnivorous_plant             = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_chasm                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_combustible                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_corpse                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_corridor                      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_cursor_path_blocker           = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_cursor_path_hazard            = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_deep_water                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_descend_dungeon               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_descend_sewer                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_dirt                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_door                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_enchantstone                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_engulfer                      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_fire                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_floor                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_foliage                       = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_food                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_fungus                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_gas_blocker                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_gas_explosion_blocker         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_gold                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_green_blood                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_hazard                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_heavy                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_key                           = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_lava                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_light_blocker                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_light_blocker_for_monst       = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_mob                           = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_monst                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_necrotic_danger_level         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_obs_destructable              = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_obs_jump_end                  = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_obs_shoving                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_obs_spawn                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_obs_spawn_monst               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_obs_wall_or_door              = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_obs_when_dead                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_portal                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_spell_of_holding_barrier      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_trap                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  // end sort marker3 }
  // clang-format on

  in >> bits(bits64);
  shift = 0;
  // clang-format off
  // begin sort marker4 {
             my.t->i_set_is_fungus_edible                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_fungus_healing                = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_fungus_poison                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_fungus_withered               = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_grass_dry                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_grass_wet                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_poisonous_danger_level        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_potion                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_red_blood                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_ring                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_ripple                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_rock                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_secret_door                   = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_shallow_water                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_shovable                      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_skillstone                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_smoke                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_spellbook                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_spiderweb                     = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_staff                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_steam                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_sticky                        = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_tentacle                      = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_torch                         = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_treasure_type                 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_is_wall                          = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_noise_blocker                    = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
             my.t->i_set_water                            = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  // end sort marker4 }
  // clang-format on

  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_DEBUG_THING_SER
  in >> bits(my.t->debug_str);
#endif

  READ_MAGIC("thing end", THING_MAGIC_END);

  IF_DEBUG3
  {
    auto diff = in.tellg() - start;
    LOG("LOAD %d bytes %s TP %d ID %X last_at %d,%d", (int) diff, name.c_str(), my.t->tp_id, my.t->id.id,
        my.t->last_at.x, my.t->last_at.y);
  }

  return in;
}

std::istream &operator>>(std::istream &in, Bits< Level *& > my)
{
  TRACE_AND_INDENT();
  auto l = my.t;

  l->player                            = nullptr;
  l->cursor                            = nullptr;
  l->all_things_id_at                  = {};
  l->all_things_ptr_at                 = {};
  l->all_things                        = {};
  l->interesting_things                = {};
  l->interesting_things_pending_add    = {};
  l->interesting_things_pending_remove = {};
  l->tickable_things                   = {};
  l->tickable_things_pending_add       = {};
  l->tickable_things_pending_remove    = {};
  l->animated_things                   = {};
  l->animated_things_pending_add       = {};
  l->animated_things_pending_remove    = {};
  l->describable_things                = {};
  l->describable_things_pending_add    = {};
  l->describable_things_pending_remove = {};
  l->all_things_to_be_destroyed        = {};
  l->all_things_pending_fall           = {};

  uint32_t csum_in = 0;
  in >> bits(csum_in);

  in >> bits(l->ts_created);
  old_ts_created = l->ts_created;
  in >> bits(l->ts_saved);
  auto dungeon_age = l->ts_saved - l->ts_created;
  new_ts_created   = time_ms() - dungeon_age;
  l->ts_created    = new_ts_created;
  l->ts_saved      = new_ts_created + dungeon_age;
  l->ts_entered    = new_ts_created;
  in >> bits(l->ts_fade_out_begin);
  in >> bits(l->ts_fade_in_begin);

  in >> bits(my.t->darkness_cloud);
  in >> bits(my.t->gas_poison_cloud);
  in >> bits(my.t->gas_healing_cloud);

  // begin sort marker5 {
  in >> bits(my.t->_fade_in_map);
  in >> bits(my.t->_gfx_water);
  in >> bits(my.t->_heatmap);
  in >> bits(my.t->_is_able_to_amplify_footsteps);
  in >> bits(my.t->_is_able_to_dampen_footsteps);
  in >> bits(my.t->_is_able_to_stand_on);
  in >> bits(my.t->_is_acid);
  in >> bits(my.t->_is_ascend_dungeon);
  in >> bits(my.t->_is_ascend_sewer);
  in >> bits(my.t->_is_attackable_by_monst);
  in >> bits(my.t->_is_attackable_by_player);
  in >> bits(my.t->_is_barrel);
  in >> bits(my.t->_is_basalt);
  in >> bits(my.t->_is_block_of_ice);
  in >> bits(my.t->_is_brazier);
  in >> bits(my.t->_is_bridge);
  in >> bits(my.t->_is_burnable);
  in >> bits(my.t->_is_carnivorous_plant);
  in >> bits(my.t->_is_chasm);
  in >> bits(my.t->_is_combustible);
  in >> bits(my.t->_is_corpse);
  in >> bits(my.t->_is_corridor);
  in >> bits(my.t->_is_currently_pixelart_raycast_lit);
  in >> bits(my.t->_is_cursor_path_blocker);
  in >> bits(my.t->_is_cursor_path_hazard);
  in >> bits(my.t->_is_deep_water);
  in >> bits(my.t->_is_descend_dungeon);
  in >> bits(my.t->_is_descend_sewer);
  in >> bits(my.t->_is_dirt);
  in >> bits(my.t->_is_door);
  in >> bits(my.t->_is_enchantstone);
  in >> bits(my.t->_is_engulfer);
  in >> bits(my.t->_is_fire);
  in >> bits(my.t->_is_floor);
  in >> bits(my.t->_is_foliage);
  in >> bits(my.t->_is_food);
  in >> bits(my.t->_is_fungus);
  in >> bits(my.t->_is_fungus_edible);
  in >> bits(my.t->_is_fungus_healing);
  in >> bits(my.t->_is_fungus_withered);
  in >> bits(my.t->_is_gas_blocker);
  in >> bits(my.t->_is_gas_explosion_blocker);
  in >> bits(my.t->_is_gas_healing);
  in >> bits(my.t->_is_gold);
  in >> bits(my.t->_is_grass_dry);
  in >> bits(my.t->_is_grass_wet);
  in >> bits(my.t->_is_green_blood);
  in >> bits(my.t->_is_hazard);
  in >> bits(my.t->_is_heavy);
  in >> bits(my.t->_is_key);
  in >> bits(my.t->_is_lava);
  in >> bits(my.t->_is_light_blocker);
  in >> bits(my.t->_is_light_blocker_for_monst);
  in >> bits(my.t->_is_mob);
  in >> bits(my.t->_is_monst);
  in >> bits(my.t->_is_obs_destructable);
  in >> bits(my.t->_is_obs_jump_end);
  in >> bits(my.t->_is_obs_shoving);
  in >> bits(my.t->_is_obs_spawn);
  in >> bits(my.t->_is_obs_spawn_monst);
  in >> bits(my.t->_is_obs_wall_or_door);
  in >> bits(my.t->_is_obs_when_dead);
  in >> bits(my.t->_is_portal);
  in >> bits(my.t->_is_potion);
  in >> bits(my.t->_is_red_blood);
  in >> bits(my.t->_is_ring);
  in >> bits(my.t->_is_ripple);
  in >> bits(my.t->_is_rock);
  in >> bits(my.t->_is_secret_door);
  in >> bits(my.t->_is_shallow_water);
  in >> bits(my.t->_is_shovable);
  in >> bits(my.t->_is_skillstone);
  in >> bits(my.t->_is_smoke);
  in >> bits(my.t->_is_spellbook);
  in >> bits(my.t->_is_spell_of_holding_barrier);
  in >> bits(my.t->_is_spiderweb);
  in >> bits(my.t->_is_staff);
  in >> bits(my.t->_is_steam);
  in >> bits(my.t->_is_sticky);
  in >> bits(my.t->_is_tentacle);
  in >> bits(my.t->_is_torch);
  in >> bits(my.t->_is_trap);
  in >> bits(my.t->_is_treasure_type);
  in >> bits(my.t->_is_walked);
  in >> bits(my.t->_is_wall);
  in >> bits(my.t->_noise_blocker);
  in >> bits(my.t->_noisemap);
  in >> bits(my.t->_sound_sources);
  // end sort marker5 }

  in >> bits(my.t->can_see_currently);
  in >> bits(my.t->can_see_ever);

  in >> bits(my.t->prev_levels);
  in >> bits(my.t->next_levels);

  in >> bits(l->world_at);
  in >> bits(l->grid_at);
  in >> bits(l->stairs_at);
  in >> bits(l->biome);

  in >> bits(l->difficulty_depth);
  in >> bits(l->dungeon_walk_order_level_no);

  in >> bits(l->is_final_boss_level);
  in >> bits(l->is_crystal_level);
  in >> bits(l->is_entered);

  in >> bits(l->d1000_chance_creating_mob_class_A);
  in >> bits(l->d1000_chance_creating_mob_class_B);
  in >> bits(l->d1000_chance_creating_mob_class_C);
  in >> bits(l->d1000_chance_creating_monst);
  in >> bits(l->d1000_chance_creating_treasure_class_A);
  in >> bits(l->d1000_chance_creating_treasure_class_B);
  in >> bits(l->d1000_chance_creating_treasure_class_C);
  in >> bits(l->d1000_chance_creating_weapon_class_A);
  in >> bits(l->d1000_chance_creating_weapon_class_B);
  in >> bits(l->d1000_chance_creating_weapon_class_C);

  in >> bits(l->maxx);
  in >> bits(l->maxy);
  in >> bits(l->minx);
  in >> bits(l->miny);

  in >> bits(l->is_cursor_found);
  in >> bits(l->is_final_level);
  in >> bits(l->is_first_level);
  in >> bits(l->is_completed);
  in >> bits(l->is_heatmap_valid);
  in >> bits(l->is_map_changed);
  in >> bits(l->is_map_follow_player);
  in >> bits(l->is_map_mini_valid);
  in >> bits(l->is_starting);
  in >> bits(l->is_entered_by_falling);

  in >> bits(l->cursor_at);
  in >> bits(l->cursor_old);
  in >> bits(l->map_br);
  in >> bits(l->map_tl);
  in >> bits(l->pixel_map_at);

  in >> bits(l->map_at);
  in >> bits(l->map_wanted_at);

  in >> bits(l->mouse_at);
  in >> bits(l->mouse_old);

  in >> bits(l->wobble);

  in >> bits(l->monst_count);

  in >> bits(l->seed);

  in >> bits(l->all_things_id_at);

  in >> bits(l->fbo_light);

  l->update_new_level();
  l->ts_redraw_bg         = 1; // Force redraw
  l->ts_fade_in_begin     = time_ms_cached();
  l->is_map_changed       = true;
  l->is_map_follow_player = true;

  auto p = l->world_at;
  LOG("INF: Loading things for level %d,%d,%d", p.x, p.y, p.z);

#ifdef ENABLE_DEBUG_THING_SER
  {
    LOG("INF: Loaded slots");
    TRACE_AND_INDENT();

    for (auto x = 0; x < MAP_WIDTH; x++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          auto id = get(my.t->all_things_id_at, x, y, slot);
          if (id.ok()) {
            CON("Load save slot %d @ %d,%d : %" PRIX32, slot, x, y, id.id);
          }
        }
      }
    }
  }
#endif

  //
  // Operate on a copy, not live data that might change as we add things
  //
  {
    LOG("INF: Load things");
    TRACE_AND_INDENT();

    auto ids = my.t->all_things_id_at;

    for (auto x = 0; x < MAP_WIDTH; x++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          auto id = get(ids, x, y, slot);
          if (id.ok()) {
            auto t = new Thing();
            in >> bits(t);

            if (! game_load_error.empty()) {
              return in;
            }

            //
            // Cannot use t->log here as thing is no inited yet
            //
            t->level = l;
            if (t->id != id) {
              game_load_error = string_sprintf(
                  "found different thing than expected at map position "
                  "%d,%d slot %d: found %" PRIX32 ", expected %" PRIX32,
                  x, y, slot, t->id.id, id.id);

#ifdef ENABLE_DEBUG_THING_SER
              for (auto slot = 0; slot < MAP_SLOTS; slot++) {
                auto id = get(ids, x, y, slot);
                CON("slot %d : %" PRIX32, slot, id.id);
              }
#endif

              return in;
            }

            t->reinit();

#ifdef ENABLE_DEBUG_THING_SER
            t->con("LOADED at %d,%d %X", t->curr_at.x, t->curr_at.y, t->id.id);
            if (t->to_dbg_saved_string() != t->debug_str) {
              CON("From save file  : %s", t->debug_str.c_str());
              CON("Newly created as: %s", t->to_dbg_saved_string().c_str());
              game_load_error = "loaded thing is corrupt";
              return in;
            }
#endif
          }
        }
      }
    }
  }

  TRACE_NO_INDENT();

  //
  // Post thing reinit fixups for things that may carry other items
  // and may not have been loaded yet when reiniting.
  //
  uint32_t csum = 0;
  {
    for (auto p : l->all_things) {
      auto t = p.second;
      csum += t->curr_at.x + t->curr_at.y + t->id.id;
#ifdef ENABLE_DEBUG_THING_SER
      t->con("LOAD %d,%d id %X", t->curr_at.x, t->curr_at.y, t->id.id);
#endif
      t->init_lights();
      t->light_distance_update();

      //
      // Do this to update state like "is_in_water" as the water may have been loaded later.
      //
      t->level_pop();
      t->level_push();
    }
  }

  if (csum != csum_in) {
    game_load_error = string_sprintf("found different thing checksum %u expected %u", csum, csum_in);
    return in;
  }

  l->update_new_level();

  READ_MAGIC("level end", THING_MAGIC_FINAL);
  LOG("INF: Loaded things for level %d,%d,%d", p.x, p.y, p.z);

  my.t->update_map();
  DBG("INF: Updated map for level %d,%d,%d", p.x, p.y, p.z);

  return in;
}

std::istream &operator>>(std::istream &in, Bits< class World & > my)
{
  TRACE_AND_INDENT();
  my.t.levels         = {};
  my.t.all_thing_ptrs = {};

  int count {};
  int step {};

  in >> bits(count);

  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        point3d p;
        bool    exists;
        in >> bits(p);
        in >> bits(exists);
        if (p != point3d(x, y, z)) {
          game_load_error
              = string_sprintf("level mismatch expected %d,%d,%d vs found %d,%d,%d", x, y, z, p.x, p.y, p.z);
          return in;
        }

        if (exists) {
          step++;
          if (count > 1) {
            wid_progress_bar("Loading...", ((float) step) / ((float) count));
          }

          LOG("INF: Loading level %d,%d,%d", p.x, p.y, p.z);
          auto l = new Level(BIOME_UNKNOWN);
          set(my.t.levels, x, y, z, l);
          in >> bits(l);
          if (! game_load_error.empty()) {
            return in;
          }

          int eol;
          in >> bits(eol);
          if (eol != GAME_SAVE_MARKER_EOL) {
            game_load_error = string_sprintf("end of level %d,%d,%d not found", x, y, z);
            return in;
          }
          LOG("INF: Loaded level %d,%d,%d", p.x, p.y, p.z);
        }
      }
    }
  }

  wid_progress_bar_destroy();
  return in;
}

std::istream &operator>>(std::istream &in, Bits< Config & > my)
{
  TRACE_AND_INDENT();

  in >> bits(my.t.version);
  LOG("Read config: version                      = [%s]", my.t.version.c_str());
  in >> bits(my.t.serialized_size);
  LOG("Read config: serialized_size              = %d", my.t.serialized_size);

  if (my.t.serialized_size != sizeof(Config)) {
    game_load_error = "bad save file header version";
    return in;
  }

  in >> bits(g_opt_player_name);
  in >> bits(my.t.ascii_gl_height);
  in >> bits(my.t.ascii_gl_width);
  in >> bits(g_opt_ascii);
  in >> bits(my.t.config_pix_height);
  in >> bits(my.t.config_pix_width);
  in >> bits(my.t.debug_mode);
  in >> bits(my.t.disable_player_warnings);
  in >> bits(my.t.fps_counter);
  in >> bits(my.t.game_pix_height);
  in >> bits(my.t.game_pix_scale_height);
  in >> bits(my.t.game_pix_scale_width);
  in >> bits(my.t.game_pix_width);
  in >> bits(my.t.game_pix_zoom);
  in >> bits(my.t.gfx_allow_highdpi);
  in >> bits(my.t.gfx_borderless);
  in >> bits(my.t.gfx_fullscreen);
  in >> bits(my.t.gfx_fullscreen_desktop);
  in >> bits(my.t.gfx_inverted);
  in >> bits(my.t.gfx_show_hidden);
  in >> bits(my.t.gfx_monochrome);
  in >> bits(my.t.gfx_vsync_enable);
  in >> bits(my.t.mouse_wheel_lr_negated);
  in >> bits(my.t.mouse_wheel_ud_negated);
  in >> bits(my.t.key_action0);
  in >> bits(my.t.key_action1);
  in >> bits(my.t.key_action2);
  in >> bits(my.t.key_action3);
  in >> bits(my.t.key_action4);
  in >> bits(my.t.key_action5);
  in >> bits(my.t.key_action6);
  in >> bits(my.t.key_action7);
  in >> bits(my.t.key_action8);
  in >> bits(my.t.key_action9);
  in >> bits(my.t.key_skill0);
  in >> bits(my.t.key_skill1);
  in >> bits(my.t.key_skill2);
  in >> bits(my.t.key_skill3);
  in >> bits(my.t.key_skill4);
  in >> bits(my.t.key_skill5);
  in >> bits(my.t.key_skill6);
  in >> bits(my.t.key_skill7);
  in >> bits(my.t.key_skill8);
  in >> bits(my.t.key_skill9);
  in >> bits(my.t.key_spell0);
  in >> bits(my.t.key_spell1);
  in >> bits(my.t.key_spell2);
  in >> bits(my.t.key_spell3);
  in >> bits(my.t.key_spell4);
  in >> bits(my.t.key_spell5);
  in >> bits(my.t.key_spell6);
  in >> bits(my.t.key_spell7);
  in >> bits(my.t.key_spell8);
  in >> bits(my.t.key_spell9);
  in >> bits(my.t.key_ascend);
  in >> bits(my.t.key_attack);
  in >> bits(my.t.key_console);
  in >> bits(my.t.key_descend);
  in >> bits(my.t.key_gfx_toggle);
  in >> bits(my.t.key_unused1);
  in >> bits(my.t.key_unused2);
  in >> bits(my.t.key_unused3);
  in >> bits(my.t.key_unused4);
  in >> bits(my.t.key_unused5);
  in >> bits(my.t.key_unused6);
  in >> bits(my.t.key_unused7);
  in >> bits(my.t.key_unused8);
  in >> bits(my.t.key_unused9);
  in >> bits(my.t.key_unused10);
  in >> bits(my.t.key_unused11);
  in >> bits(my.t.key_unused12);
  in >> bits(my.t.key_unused13);
  in >> bits(my.t.key_unused14);
  in >> bits(my.t.key_unused15);
  in >> bits(my.t.key_unused16);
  in >> bits(my.t.key_unused17);
  in >> bits(my.t.key_unused18);
  in >> bits(my.t.key_unused19);
  in >> bits(my.t.key_unused20);
  in >> bits(my.t.key_drop);
  in >> bits(my.t.key_eat);
  in >> bits(my.t.key_help);
  in >> bits(my.t.key_inventory);
  in >> bits(my.t.key_jump);
  in >> bits(my.t.key_load);
  in >> bits(my.t.key_map_down);
  in >> bits(my.t.key_map_left);
  in >> bits(my.t.key_map_right);
  in >> bits(my.t.key_map_up);
  in >> bits(my.t.key_move_down);
  in >> bits(my.t.key_move_left);
  in >> bits(my.t.key_move_right);
  in >> bits(my.t.key_move_up);
  in >> bits(my.t.key_quit);
  in >> bits(my.t.key_robot_mode);
  in >> bits(my.t.key_save);
  in >> bits(my.t.key_screenshot);
  in >> bits(my.t.key_throw);
  in >> bits(my.t.key_use);
  in >> bits(my.t.key_wait_or_collect);
  in >> bits(my.t.key_zoom_in);
  in >> bits(my.t.key_zoom_out);
  in >> bits(my.t.music_volume);
  in >> bits(my.t.one_pixel_height);
  in >> bits(my.t.one_pixel_width);
  in >> bits(my.t.sdl_delay);
  in >> bits(my.t.snapshot_freq);
  in >> bits(my.t.sound_volume);
  in >> bits(my.t.tile_height);
  in >> bits(my.t.tile_pixel_height);
  in >> bits(my.t.tile_pixel_width);
  in >> bits(my.t.tile_pix_height);
  in >> bits(my.t.tile_pix_width);
  in >> bits(my.t.tile_width);
  in >> bits(my.t.ui_pix_height);
  in >> bits(my.t.ui_pix_width);
  in >> bits(my.t.ui_pix_zoom);
  in >> bits(my.t.ui_ascii_term_height);
  in >> bits(my.t.ui_ascii_term_width);
  in >> bits(my.t.ui_gfx_term_height);
  in >> bits(my.t.ui_gfx_term_width);
  in >> bits(my.t.video_w_h_ratio);
  in >> bits(my.t.window_pix_height);
  in >> bits(my.t.window_pix_width);

  LOG("Read config: ascii_gl_height              = %d", my.t.ascii_gl_height);
  LOG("Read config: ascii_gl_width               = %d", my.t.ascii_gl_width);
  LOG("Read config: config_pix_height            = %d", my.t.config_pix_height);
  LOG("Read config: config_pix_width             = %d", my.t.config_pix_width);
  LOG("Read config: debug_mode                   = %d", my.t.debug_mode);
  LOG("Read config: disable_player_warnings      = %d", my.t.disable_player_warnings);
  LOG("Read config: fps_counter                  = %d", my.t.fps_counter);
  LOG("Read config: game_pix_height              = %d", my.t.game_pix_height);
  LOG("Read config: game_pix_scale_height        = %f", my.t.game_pix_scale_height);
  LOG("Read config: game_pix_scale_width         = %f", my.t.game_pix_scale_width);
  LOG("Read config: game_pix_width               = %d", my.t.game_pix_width);
  LOG("Read config: game_pix_zoom                = %f", my.t.game_pix_zoom);
  LOG("Read config: gfx_allow_highdpi            = %d", my.t.gfx_allow_highdpi);
  LOG("Read config: gfx_borderless               = %d", my.t.gfx_borderless);
  LOG("Read config: gfx_fullscreen_desktop       = %d", my.t.gfx_fullscreen_desktop);
  LOG("Read config: gfx_fullscreen               = %d", my.t.gfx_fullscreen);
  LOG("Read config: gfx_inverted                 = %d", my.t.gfx_inverted);
  LOG("Read config: gfx_monochrome               = %d", my.t.gfx_monochrome);
  LOG("Read config: gfx_show_hidden              = %d", my.t.gfx_show_hidden);
  LOG("Read config: gfx_vsync_enable             = %d", my.t.gfx_vsync_enable);
  LOG("Read config: g_opt_ascii                  = %d", g_opt_ascii);
  LOG("Read config: g_opt_player_name            = [%s]", g_opt_player_name.c_str());
  LOG("Read config: mouse_wheel_lr_negated       = %d", my.t.mouse_wheel_lr_negated);
  LOG("Read config: mouse_wheel_ud_negated       = %d", my.t.mouse_wheel_ud_negated);
  LOG("Read config: music_volume                 = %d", my.t.music_volume);
  LOG("Read config: one_pixel_height             = %f", my.t.one_pixel_height);
  LOG("Read config: one_pixel_width              = %f", my.t.one_pixel_width);
  LOG("Read config: sdl_delay                    = %d", my.t.sdl_delay);
  LOG("Read config: snapshot_freq                = %d", my.t.snapshot_freq);
  LOG("Read config: sound_volume                 = %d", my.t.sound_volume);
  LOG("Read config: tile_height                  = %d", my.t.tile_height);
  LOG("Read config: tile_pixel_height            = %f", my.t.tile_pixel_height);
  LOG("Read config: tile_pixel_width             = %f", my.t.tile_pixel_width);
  LOG("Read config: tile_pix_height              = %f", my.t.tile_pix_height);
  LOG("Read config: tile_pix_width               = %f", my.t.tile_pix_width);
  LOG("Read config: tile_width                   = %d", my.t.tile_width);
  LOG("Read config: ui_ascii_term_height         = %d", my.t.ui_ascii_term_height);
  LOG("Read config: ui_ascii_term_width          = %d", my.t.ui_ascii_term_width);
  LOG("Read config: ui_gfx_term_height           = %d", my.t.ui_gfx_term_height);
  LOG("Read config: ui_gfx_term_width            = %d", my.t.ui_gfx_term_width);
  LOG("Read config: ui_pix_height                = %d", my.t.ui_pix_height);
  LOG("Read config: ui_pix_width                 = %d", my.t.ui_pix_width);
  LOG("Read config: ui_pix_zoom                  = %f", my.t.ui_pix_zoom);
  LOG("Read config: video_w_h_ratio              = %f", my.t.video_w_h_ratio);
  LOG("Read config: window_pix_height            = %d", my.t.window_pix_height);
  LOG("Read config: window_pix_width             = %d", my.t.window_pix_width);
  // seed name handled below

  if (! g_opt_override_debug_level) {
    if (my.t.debug_mode) {
      g_opt_debug3 = false;
      g_opt_debug2 = true;
      g_opt_debug1 = true;
    }
  }

  if (my.t.gfx_monochrome) {
    g_opt_gfx_monochrome = true;
  }

  //
  // Allow the command line to override.
  //
  {
    std::string tmp;
    in >> bits(tmp);
    if (g_opt_seed_name.empty()) {
      g_opt_seed_name = tmp;
    }
  }

  in >> bits(my.t.hiscores);
  in >> bits(my.t.player_bodyparts);

  int eol;
  in >> bits(eol);
  if (eol != GAME_SAVE_MARKER_CONFIG) {
    game_load_error += "end of config marker not found";
    return in;
  }

  if (my.t.ascii_gl_height < 0) {
    game_load_error += "ascii_gl_height is invalid";
    return in;
  }
  if (my.t.ascii_gl_width < 0) {
    game_load_error += "ascii_gl_width is invalid";
    return in;
  }
  if (my.t.config_pix_height < 0) {
    game_load_error += "config_pix_height is invalid";
    return in;
  }
  if (my.t.config_pix_width < 0) {
    game_load_error += "config_pix_width is invalid";
    return in;
  }
  if (my.t.game_pix_height < 0) {
    game_load_error += "game_pix_height is invalid";
    return in;
  }
  if (my.t.game_pix_scale_height < 0) {
    game_load_error += "game_pix_scale_height is invalid";
    return in;
  }
  if (my.t.game_pix_scale_width < 0) {
    game_load_error += "game_pix_scale_width is invalid";
    return in;
  }
  if (my.t.game_pix_width < 0) {
    game_load_error += "game_pix_width is invalid";
    return in;
  }
  if (! my.t.game_pix_zoom) {
    game_load_error += "game_pix_zoom is invalid";
    return in;
  }
  if (my.t.one_pixel_height < 0) {
    game_load_error += "one_pixel_height is invalid";
    return in;
  }
  if (my.t.one_pixel_width < 0) {
    game_load_error += "one_pixel_width is invalid";
    return in;
  }
  if (my.t.tile_height < 0) {
    game_load_error += "tile_height is invalid";
    return in;
  }
  if (my.t.tile_pixel_height < 0) {
    game_load_error += "tile_pixel_height is invalid";
    return in;
  }
  if (my.t.tile_pixel_width < 0) {
    game_load_error += "tile_pixel_width is invalid";
    return in;
  }
  if (my.t.tile_pix_height < 0) {
    game_load_error += "tile_pix_height is invalid";
    return in;
  }
  if (my.t.tile_pix_width < 0) {
    game_load_error += "tile_pix_width is invalid";
    return in;
  }
  if (my.t.tile_width < 0) {
    game_load_error += "tile_width is invalid";
    return in;
  }
  if (my.t.ui_ascii_term_height < 0) {
    game_load_error += "ui_ascii_term_height is invalid";
    return in;
  }
  if (my.t.ui_ascii_term_width < 0) {
    game_load_error += "ui_ascii_term_width is invalid";
    return in;
  }
  if (my.t.ui_gfx_term_height < 0) {
    game_load_error += "ui_gfx_term_height is invalid";
    return in;
  }
  if (my.t.ui_gfx_term_width < 0) {
    game_load_error += "ui_gfx_term_width is invalid";
    return in;
  }
  if (my.t.ui_pix_height < 0) {
    game_load_error += "ui_pix_height is invalid";
    return in;
  }
  if (my.t.ui_pix_width < 0) {
    game_load_error += "ui_pix_width is invalid";
    return in;
  }
  if (my.t.ui_pix_zoom < 0) {
    game_load_error += "ui_pix_zoom is invalid";
    return in;
  }
  if (my.t.video_w_h_ratio < 0) {
    game_load_error += "video_w_h_ratio is invalid";
    return in;
  }
  if (my.t.window_pix_height < 0) {
    game_load_error += "window_pix_height is invalid";
    return in;
  }
  if (my.t.window_pix_width < 0) {
    game_load_error += "window_pix_width is invalid";
    return in;
  }

  return in;
}

std::istream &operator>>(std::istream &in, Bits< class Game & > my)
{
  TRACE_AND_INDENT();
  in >> bits(my.t.version);
  in >> bits(my.t.serialized_size);

  if (my.t.serialized_size
      != (uint32_t) (sizeof(Game) + sizeof(Level) + sizeof(Thing) + sizeof(ThingAi) + sizeof(ThingInfo)
                     + sizeof(ThingItem))) {
    if (my.t.version == MYVER) {
      game_load_error = "Incompatible save file for version " + my.t.version;
    } else {
      game_load_error = "Incompatible version. Expected version " MYVER ", found version " + my.t.version;
    }
    return in;
  }

  in >> bits(my.t.save_slot);
  in >> bits(my.t.save_meta);
  in >> bits(my.t.save_file);
  if (game_load_headers_only) {
    return in;
  }
  in >> bits(my.t.appdata);
  in >> bits(my.t.saved_dir);
  in >> bits(my.t.config);
  if (! game_load_error.empty()) {
    return in;
  }
  in >> bits(my.t.world);
  if (! game_load_error.empty()) {
    return in;
  }

  in >> bits(my.t.started);
  in >> bits(my.t.things_are_moving);
  in >> bits(my.t.player_is_ready_for_messages);
  in >> bits(MAP_WIDTH);
  in >> bits(MAP_HEIGHT);

  in >> bits(my.t.map_mini_over);
  in >> bits(my.t.seed);
  in >> bits(my.t.seed_name);
  in >> bits(my.t.tick_requested);
  in >> bits(my.t.current_level);
  in >> bits(my.t.frame_count);
  in >> bits(my.t.fps_value);
  in >> bits(my.t.tick_completed);
  in >> bits(my.t.tick_current);
  in >> bits(my.t.inventory_highlight_slot);
  in >> bits(my.t.previous_slot);
  in >> bits(my.t.skillbox_highlight_slot);
  in >> bits(my.t.spellbox_highlight_slot);

  std::vector< std::wstring > s;
  in >> bits(s);
  wid_topcon_deserialize(s);
  in >> bits(s);
  wid_console_deserialize(s);

  LOG("Current level set to %s", my.t.current_level.to_string().c_str());

  my.t.level = get(my.t.world.levels, my.t.current_level.x, my.t.current_level.y, my.t.current_level.z);
  if (my.t.level) {
    my.t.level->log("This is the current level");
  }

  return in;
}

// binary mode is only for switching off newline translation
// ios::ate, open at end
std::vector< char > read_file(const std::string filename)
{
  TRACE_AND_INDENT();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (ifs.is_open()) {
    ifs.unsetf(std::ios::skipws);

    std::ifstream::pos_type sz = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector< char > bytes(sz);
    ifs.read(bytes.data(), sz);
    return bytes;
  }
  std::vector< char > bytes;
  return bytes;
}

static std::vector< char > read_lzo_file(const std::string filename, lzo_uint *uncompressed_sz, uint32_t *cs)
{
  TRACE_AND_INDENT();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (ifs.is_open()) {
    // tellg is not ideal, look into <filesystem> post mojave
    std::ifstream::pos_type sz = ifs.tellg();
    if (sz < 0) {
      return (std::vector< char >());
    }

    ifs.seekg(0, std::ios::beg);
    ifs.unsetf(std::ios::skipws);
    ifs.read((char *) uncompressed_sz, sizeof(*uncompressed_sz));
    ifs.read((char *) cs, sizeof(*cs));

    sz -= (int) sizeof(*uncompressed_sz);
    sz -= (int) sizeof(*cs);
    std::vector< char > bytes(sz);
    ifs.read(bytes.data(), sz);
    return bytes;
  }
  std::vector< char > bytes;
  return bytes;
}

uint32_t csum(char *mem, uint32_t len)
{
  TRACE_AND_INDENT();
  uint32_t ret = 0;
  while (len--) {
    ret <<= 1;
    ret ^= *mem;
    mem++;
  }
  return ret;
}

bool Game::load(std::string file_to_load, class Game &target)
{
  TRACE_AND_INDENT();
  game_load_error = "";

  //
  // Read to a vector and then copy to a C buffer for LZO to use
  //
  lzo_uint uncompressed_len;
  uint32_t cs;
  auto     vec = read_lzo_file(file_to_load, &uncompressed_len, &cs);
  if (vec.size() <= 0) {
    if (! game_load_headers_only) {
      wid_error("load error, empty file [" + file_to_load + "] ?");
    }
    return false;
  }

  auto     data           = vec.data();
  lzo_uint compressed_len = vec.size();

  HEAP_ALLOC(compressed, compressed_len);
  HEAP_ALLOC(uncompressed, uncompressed_len);
  memcpy(compressed, data, compressed_len);

  lzo_uint new_len = 0;
  int      r = lzo1x_decompress((lzo_bytep) compressed, compressed_len, (lzo_bytep) uncompressed, &new_len, nullptr);
  if (r == LZO_E_OK && new_len == uncompressed_len) {
    if (! game_load_headers_only) {
      CON("INF: Loading %s, decompress %luMb -> %luMb", file_to_load.c_str(),
          (unsigned long) compressed_len / (1024 * 1024), (unsigned long) uncompressed_len / (1024 * 1024));
    }
  } else {
    /* this should NEVER happen */
    ERR("LZO internal error - decompression failed: %d", r);
    return false;
  }

  uint32_t csin = csum((char *) uncompressed, (uint32_t) uncompressed_len);
  if (cs != csin) {
    ERR("Corrupt file, checksum mismatch");
    return false;
  }

#if 0
  IF_DEBUG3 {
    std::cout << "decompressed as ";
    hexdump((const unsigned char *)uncompressed, uncompressed_len);
  }
#endif

  std::string        s((const char *) uncompressed, (size_t) uncompressed_len);
  std::istringstream in(s);

  if (! game_load_headers_only) {
    wid_topcon_fini();
    wid_topcon_init();
  }

  game_load_error = "";
  in >> bits(target);
  if (! game_load_error.empty()) {
    if (! game_load_headers_only) {
      wid_error("load error, " + game_load_error);
    }
    return false;
  }

  if (! game_load_headers_only) {
    if (! game->level) {
      ERR("No level set as current");
      return false;
    }
    game->level->log("This level is set as current");

    wid_visible(wid_topcon_window);
    wid_visible(wid_botcon_window);
    wid_rightbar_fini();
    wid_rightbar_init();
    wid_leftbar_fini();
    wid_leftbar_init();
    wid_actionbar_init();
  }

  free(uncompressed);
  free(compressed);

  game->tick_begin_ms      = time_ms();
  game->tick_begin_game_ms = time_game_ms();

  return true;
}

std::string Game::load_config(void)
{
  TRACE_AND_INDENT();
  game_load_error = "";

  auto          filename = saved_dir + "config";
  std::ifstream in(filename);
  if (in.is_open()) {
    in >> bits(*(&game->config));
  }

  return game_load_error;
}

void Game::load(void)
{
  TRACE_AND_INDENT();
  LOG("-");
  CON("INF: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Loaded %s, seed %u", save_file.c_str(), seed);
  LOG("-");
}

void Game::load(int slot)
{
  TRACE_AND_INDENT();
  if (slot < 0) {
    return;
  }

  if (slot >= UI_WID_SAVE_SLOTS) {
    return;
  }

  if (! get(slot_valid, slot)) {
    TOPCON("No game at that slot.");
    return;
  }

  game->fini();

  auto save_file = saved_dir + "saved-slot-" + std::to_string(slot);

  if (slot == UI_WID_SAVE_SLOTS - 1) {
    save_file = saved_dir + "saved-snapshot";
  }

  LOG("-");
  CON("INF: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Loaded %s, seed %d", save_file.c_str(), seed);
  LOG("-");

  TOPCON("Loaded the game from %s.", save_file.c_str());

  sdl_display_reset();
}

void Game::load_snapshot(void)
{
  TRACE_AND_INDENT();
  game->fini();

  auto save_file = saved_dir + "saved-snapshot";

  LOG("-");
  CON("INF: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Loaded %s, seed %d", save_file.c_str(), seed);
  LOG("-");

  TOPCON("Loaded the game from %s.", save_file.c_str());
}

void wid_load_destroy(void)
{
  TRACE_AND_INDENT();
  if (wid_load) {
    delete wid_load;
    wid_load = nullptr;
    game->change_state(Game::STATE_NORMAL, "load destroy");
  }
}

static uint8_t wid_load_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            auto c = wid_event_to_char(key);
            switch (c) {
              case '0' :
              case '1' :
              case '2' :
              case '3' :
              case '4' :
              case '5' :
              case '6' :
              case '7' :
              case '8' :
              case '9' :
                {
                  int slot = c - '0';
                  if (! get(slot_valid, slot)) {
                    TOPCON("No game at that slot.");
                  } else {
                    game->load(slot);
                    wid_load_destroy();
                  }
                  return true;
                }
              case 'b' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  CON("INF: Load game cancelled");
                  wid_load_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_load_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static uint8_t wid_load_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto slot = wid_get_int_context(w);
  game->load(slot);
  wid_load_destroy();
  return true;
}

static uint8_t wid_load_saved_snapshot(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->load_snapshot();
  wid_load_destroy();
  return true;
}
static uint8_t wid_load_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_load_destroy();
  return true;
}

void Game::wid_load_select(void)
{
  TRACE_AND_INDENT();
  CON("INF: Loading a saved game, destroy old");

  if (wid_load) {
    return;
  }

  game_load_error = "";

  auto  m  = TERM_WIDTH / 2;
  auto  h  = TERM_HEIGHT / 2;
  point tl = make_point(m - 40, h - 7);
  point br = make_point(m + 40, h + 8);
  if (! g_opt_ascii) {
    br.y += 3;
  }
  auto width = br.x - tl.x;

  wid_load = new WidPopup("Game load", tl, br, tile_find_mand("load"), "", false, false);
  wid_set_on_key_up(wid_load->wid_popup_container, wid_load_key_up);
  wid_set_on_key_down(wid_load->wid_popup_container, wid_load_key_down);

  //
  // Close icon
  //
  {
    auto w = wid_new_square_button(wid_load->wid_popup_container, "wid inventory window close");
    if (g_opt_ascii) {
      point tl(width - 2, 0);
      point br(width - 0, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
    } else {
      point tl(width - 3, 0);
      point br(width - 0, 3);
      wid_set_pos(w, tl, br);
      wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_close");
    }
    wid_set_on_mouse_up(w, wid_load_cancel);
  }

  game_load_headers_only = true;

  wid_load->log(UI_LOGGING_EMPTY_LINE);
  wid_load->log("Choose a load slot.");

  int y_at = 3;
  for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
    Game tmp;
    auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);

    wid_progress_bar("Scanning...", ((float) slot) / ((float) UI_WID_SAVE_SLOTS));

    if (slot == UI_WID_SAVE_SLOTS - 1) {
      tmp_file = saved_dir + "saved-snapshot";
    }

    auto  p  = wid_load->wid_text_area->wid_text_area;
    auto  w  = wid_new_square_button(p, "load slot");
    point tl = make_point(0, y_at);
    point br = make_point(width - 2, y_at);

    std::string s = std::to_string(slot) + ": ";
    if (! load(tmp_file, tmp)) {
      if (! game_load_error.empty()) {
        s += game_load_error;
        wid_set_style(w, UI_WID_STYLE_RED);
        CON("GAME LOADING ERROR: %s", game_load_error.c_str());
      } else {
        if (slot == UI_WID_SAVE_SLOTS - 1) {
          s += "<no-snapshot>";
        } else {
          s += "<empty>";
        }
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
      }
      set(slot_valid, slot, false);
    } else {
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        s += "snapshot: " + tmp.save_meta;
      } else {
        s += tmp.save_meta;
      }
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        wid_set_on_mouse_up(w, wid_load_saved_snapshot);
      } else {
        wid_set_on_mouse_up(w, wid_load_mouse_up);
      }
      wid_set_style(w, UI_WID_STYLE_GREEN);
      set(slot_valid, slot, true);
    }
    wid_set_int_context(w, slot);

    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    y_at++;
  }
  game_load_headers_only = false;
  wid_update(wid_load->wid_text_area->wid_text_area);

  wid_progress_bar_destroy();
  game->change_state(Game::STATE_LOAD_MENU, "load select");
  wid_actionbar_init();

  //
  // Not sure why we need this; but the level ends up blank post loading.
  // It's probably a good idea anyway, in case we were in a difference gfx mode.
  //
  sdl_display_reset();
}
