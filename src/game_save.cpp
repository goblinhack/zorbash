//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "minilzo.hpp"
#include "my_alloc.hpp"
#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_sdl.hpp"
#include "my_serialize.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_console.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_progress_bar.hpp"
#include "my_wid_topcon.hpp"

WidPopup *wid_save;
void      wid_save_destroy(void);

extern bool     game_load_headers_only;
bool            game_save_config_only;
int             GAME_SAVE_MARKER_EOL = 123456;
extern uint32_t csum(char *mem, uint32_t len);

#define WRITE_MAGIC(m)                                                                                               \
  {                                                                                                                  \
    uint32_t magic = m;                                                                                              \
    out << bits(magic);                                                                                              \
  }

std::ostream &operator<<(std::ostream &out, Bits< const SDL_Keysym & > const my)
{
  TRACE_AND_INDENT();
  out << bits(my.t.scancode);
  out << bits(my.t.sym);
  out << bits(my.t.mod);
  out << bits(my.t.unused);
  return (out);
}

std::ostream &operator<<(std::ostream &out, Bits< ThingInfop & > const my)
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
  out << bits(my.t->born);
  out << bits(my.t->bounce_fade);
  out << bits(my.t->bounce_height);
  out << bits(my.t->capacity_height);
  out << bits(my.t->capacity_width);
  out << bits(my.t->dead_reason);
  out << bits(my.t->distance_throw);
  out << bits(my.t->enchant);
  out << bits(my.t->enchant_max);
  out << bits(my.t->fadeup_fade);
  out << bits(my.t->fadeup_height);
  out << bits(my.t->fall_height);
  out << bits(my.t->gold);
  out << bits(my.t->move_count);
  out << bits(my.t->health);
  out << bits(my.t->health_max);
  out << bits(my.t->hunger);
  out << bits(my.t->jump_distance_mod);
  out << bits(my.t->keys);
  out << bits(my.t->leader_id);
  out << bits(my.t->lifespan);
  out << bits(my.t->light_col);
  out << bits(my.t->light_dist);
  out << bits(my.t->lunge_to);
  out << bits(my.t->mob_id);
  out << bits(my.t->monst_state);
  out << bits(my.t->movement_remaining);
  out << bits(my.t->move_speed_curr);
  out << bits(my.t->move_speed_mod);
  out << bits(my.t->msg);
  out << bits(my.t->necrosis);
  out << bits(my.t->noise);
  out << bits(my.t->nutrition);
  out << bits(my.t->on_fire_id_anim);
  out << bits(my.t->owner_id);
  out << bits(my.t->physical_training);
  out << bits(my.t->poison);
  out << bits(my.t->poison_reason);
  out << bits(my.t->prev_light_dist);
  out << bits(my.t->score);
  out << bits(my.t->shove_strength_mod);
  out << bits(my.t->spawner_owner_id);
  out << bits(my.t->stamina);
  out << bits(my.t->stamina_max);
  out << bits(my.t->stat_att);
  out << bits(my.t->stat_att_mod);
  out << bits(my.t->stat_con);
  out << bits(my.t->stat_con_mod);
  out << bits(my.t->stat_def);
  out << bits(my.t->stat_def_mod);
  out << bits(my.t->stat_dex);
  out << bits(my.t->stat_dex_mod);
  out << bits(my.t->stat_luck);
  out << bits(my.t->stat_luck_mod);
  out << bits(my.t->stats02);
  out << bits(my.t->stats03);
  out << bits(my.t->stats04);
  out << bits(my.t->stats05);
  out << bits(my.t->stats06);
  out << bits(my.t->stats07);
  out << bits(my.t->stats09);
  out << bits(my.t->stat_str);
  out << bits(my.t->stat_str_mod);
  out << bits(my.t->submerged_offset);
  out << bits(my.t->tick_last_awoke);
  out << bits(my.t->tick_last_did_something);
  out << bits(my.t->tick_last_dropped);
  out << bits(my.t->tick_last_escape);
  out << bits(my.t->tick_last_i_attacked);
  out << bits(my.t->tick_last_i_was_attacked);
  out << bits(my.t->tick_last_level_change);
  out << bits(my.t->tick_last_location_check);
  out << bits(my.t->tick_resurrect_when);
  out << bits(my.t->wobble);
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
     out << bits(my.t->ts_anim_delay_end);
     out << bits(my.t->ts_bounce_begin);
     out << bits(my.t->ts_bounce_end);
     out << bits(my.t->ts_fadeup_begin);
     out << bits(my.t->ts_fadeup_end);
     out << bits(my.t->ts_fall_begin);
     out << bits(my.t->ts_fall_end);
     out << bits(my.t->ts_flip_start);
     out << bits(my.t->ts_lunge_begin);
     out << bits(my.t->ts_lunge_end);
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
  out << bits(my.t->bounce_count);
  out << bits(my.t->charge_count);
  out << bits(my.t->sleep_count);
  out << bits(my.t->damaged_count);
  out << bits(my.t->follower_count);
  out << bits(my.t->minion_count);
  out << bits(my.t->owned_count);
  out << bits(my.t->spawned_count);
  out << bits(my.t->map_treasure_count);
  out << bits(my.t->map_beast_count);
  // clang-format on
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  return (out);
}

std::ostream &operator<<(std::ostream &out, Bits< ThingItemsp & > const my)
{
  TRACE_AND_INDENT();
  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  out << bits(my.t->equip_id);
  out << bits(my.t->equip_id_carry_anim);
  out << bits(my.t->equip_id_use_anim);
  out << bits(my.t->bag_position);
  out << bits(my.t->last_bag_position);
  out << bits(my.t->where_i_dropped_an_item_last);
  out << bits(my.t->where_i_failed_to_collect_last);
  out << bits(my.t->bag);
  out << bits(my.t->carrying);
  out << bits(my.t->skills);
  out << bits(my.t->buffs);
  out << bits(my.t->debuffs);
  out << bits(my.t->inventory_shortcuts);
  out << bits(my.t->skillbox_id);
  out << bits(my.t->buffbox_id);
  out << bits(my.t->debuffbox_id);
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  return (out);
}

std::ostream &operator<<(std::ostream &out, Bits< ThingAip & > const my)
{
  TRACE_AND_INDENT();
  out << bits(my.t->age_map.val);
  out << bits(my.t->seen_map.val);
  out << bits(my.t->interrupt_map.val);
  out << bits(my.t->dmap_can_see.val);
  out << bits(my.t->can_see_currently.can_see);
  out << bits(my.t->can_see_ever.can_see);
  out << bits(my.t->thing_enemies);
  out << bits(my.t->perma_enemies);
  out << bits(my.t->thing_friends);
  out << bits(my.t->perma_friends);
  out << bits(my.t->goal_penalty);
  out << bits(my.t->avoid);
  out << bits(my.t->move_path);
  out << bits(my.t->wander_dest);
  out << bits(my.t->idle_count);
  out << bits(my.t->stuck_count);
  return (out);
}

std::ostream &operator<<(std::ostream &out, Bits< const Thingp & > const my)
{
  TRACE_AND_INDENT();
  auto start = out.tellp();
  WRITE_MAGIC(THING_MAGIC_BEGIN + (int) sizeof(Thing));

  const std::string name(tp_id_map[ my.t->tp_id - 1 ]->name());
  out << bits(name);
  // CON("WRITE %s %d", name.c_str(), my.t->tp_id);

  bool monst_info_present = (my.t->maybe_infop() != nullptr);
  out << bits(monst_info_present);
  if (monst_info_present) {
    out << bits(my.t->_infop);
  }

  bool monst_item_present = (my.t->maybe_itemsp() != nullptr);
  out << bits(monst_item_present);
  if (monst_item_present) {
    out << bits(my.t->_itemsp);
  }

  bool monst_ai_present = (my.t->maybe_aip() != nullptr);
  out << bits(monst_ai_present);
  if (monst_ai_present) {
    out << bits(my.t->_aip);
  }

  out << bits(my.t->tp_id);
  out << bits(my.t->id);

  /////////////////////////////////////////////////////////////////////////
  // Keep these in the same order as my_thing.h and save/load
  /////////////////////////////////////////////////////////////////////////
  out << bits(my.t->frame_count);
  out << bits(my.t->interpolated_at);
  out << bits(my.t->last_at);
  out << bits(my.t->curr_at);
  out << bits(my.t->last_attached);
  out << bits(my.t->last_ascii_at);
  out << bits(my.t->last_blit_br);
  out << bits(my.t->last_blit_tl);
  out << bits(my.t->last_blit_at);
  out << bits(my.t->ts_next_frame);
  out << bits(my.t->tile_curr);
  out << bits(my.t->z_depth);
  out << bits(my.t->laser_count);
  out << bits(my.t->temperature);
  out << bits(my.t->blit_bg_color);
  out << bits(my.t->blit_fg_color);
  uint8_t dir = my.t->dir;
  out << bits(dir);

  /////////////////////////////////////////////////////////////////////////
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  //
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////
  uint64_t bits64 = 0;
  int      shift  = 0;
  // clang-format off
  // begin sort marker1 {
  bits64 |= (my.t->corpse_cleanup                               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->has_ever_moved                               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->has_light                                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->has_projectile                               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->has_seen_player_msg_shown                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->has_attacked_player                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_activated                                 ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_attached                                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_being_destroyed                           ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_bouncing                                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_burnt                                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_changing_level                            ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_dead                                      ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_dying                                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_facing_left                               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_fadeup                                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_falling                                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_frozen                                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_gfx_ascii_animated                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_gfx_pixelart_animated                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_hidden                                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_hunger_level_gorged                       ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_hunger_level_hungry                       ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_hunger_level_satiated                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_hunger_level_starving                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_in_lava                                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_in_water                                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_jumping                                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_key_in_lock                               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_moving                                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_offscreen                                 ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_open                                      ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_resurrected                               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_resurrecting                              ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_resurrection_blocked                      ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_ring2                                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_scheduled_for_death                       ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_scheduled_for_gc                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_scheduled_for_jump_end                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_seen_by_player_msg_shown                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_sleeping                                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_teleporting                               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_the_grid                                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_the_player                                ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_waiting                                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_waiting_to_ascend_dungeon                 ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_waiting_to_ascend_sewer                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_waiting_to_descend_dungeon                ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_waiting_to_descend_sewer                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_waiting_to_leave_level_has_completed_fall ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->is_wounded_msg                               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->was_frozen                                   ? 1LLU : 0LLU) << shift; shift++;
  // end sort marker1 {

  if (shift >= (int) (sizeof(bits64) * 8)) {
    ERR("Ran out of bits in serialization");
  }
  out << bits(bits64);
  // CON("SAVE %016LX ",bits64);

  bits64 = 0;
  shift  = 0;
  // begin sort marker2 {
  bits64 |= (my.t->i_set_is_able_to_burn                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_acid                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_ascend_dungeon                ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_ascend_sewer                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_barrel                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_basalt                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_block_of_ice                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_brazier                       ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_bridge                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_carnivorous_plant             ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_chasm                         ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_combustible                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_corpse                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_corridor                      ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_cursor_path_blocker           ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_cursor_path_hazard            ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_deep_water                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_descend_dungeon               ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_descend_sewer                 ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_dirt                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_door                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_dry_grass                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_enchantstone                  ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_fire                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_floor                         ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_foilage                       ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_food                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_gas_blocker                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_gold                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_green_blood                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_hazard                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_heavy                         ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_key                           ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_lava                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_light_blocker                 ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_light_blocker_for_monst       ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_mob                           ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_monst                         ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_necrotic_danger_level         ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_obs_destructable              ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_obs_wall_or_door              ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_poisonous_danger_level        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_potion                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_red_blood                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_ring                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_ripple                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_rock                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_secret_door                   ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_shallow_water                 ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_shovable                      ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_skillstone                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_smoke                         ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_spiderweb                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_staff                         ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_sticky                        ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_torch                         ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_treasure_type                 ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_wall                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_wand                          ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_is_wet_grass                     ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_noise_blocker                    ? 1LLU : 0LLU) << shift; shift++;
  bits64 |= (my.t->i_set_water                            ? 1LLU : 0LLU) << shift; shift++;
  // end sort marker2 {
  // clang-format on

  if (shift >= (int) (sizeof(bits64) * 8)) {
    ERR("Ran out of bits in serialization");
  }
  out << bits(bits64);
  // CON("SAVE %016LX ",bits64);

  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_DEBUG_THING_SER
  out << bits(my.t->to_dbg_saved_string());
#endif

  WRITE_MAGIC(THING_MAGIC_END);

  IF_DEBUG3
  {
    auto diff = out.tellp() - start;
    LOG("SAVE %d bytes %s TP %d ID %X last_at %d,%d infop %p", (int) diff, name.c_str(), my.t->tp_id, my.t->id.id,
        my.t->last_at.x, my.t->last_at.y, my.t->maybe_infop());
  }
  return (out);
}

std::ostream &operator<<(std::ostream &out, Bits< Levelp & > const my)
{
  TRACE_AND_INDENT();
  IF_DEBUG3 { my.t->log("Save"); }

  if (game->currently_saving_snapshot) {
    //
    // Faster
    //
    LOG("INF: Save level snapshot");
    game->level->fbo_light.clear();
  } else if (game->level == my.t) {
    if (! g_opt_ascii) {
      LOG("INF: Save lightmap");
      game->level->fbo_light = sdl_fbo_save(FBO_PIXELART_FULLMAP_LIGHT);
    }
    LOG("INF: Saved lightmap");
  } else {
    //
    // No light for non current levels
    //
    game->level->fbo_light.clear();
  }

  uint32_t csum = 0;
  {
    for (auto p : my.t->all_things) {
      auto t = p.second;
      csum += t->curr_at.x + t->curr_at.y + t->id.id;
      // t->con("SAVE %d,%d %d", t->curr_at.x, t->curr_at.y, t->id.id);
    }
  }
  out << bits(csum);

  out << bits(my.t->ts_created);
  ts_t ts_saved = time_ms();
  out << bits(ts_saved);
  out << bits(my.t->ts_fade_out_begin);
  out << bits(my.t->ts_fade_in_begin);

  out << bits(my.t->gas_poison_cloud);

  out << bits(my.t->_is_gas_blocker);
  out << bits(my.t->_noise_blocker);
  out << bits(my.t->_is_light_blocker);
  out << bits(my.t->_is_light_blocker_for_monst);
  out << bits(my.t->_is_obs_destructable);
  out << bits(my.t->_is_obs_wall_or_door);

  out << bits(my.t->_fade_in_map);
  out << bits(my.t->_gfx_water);
  out << bits(my.t->_heatmap);
  out << bits(my.t->_is_able_to_stand_on);
  out << bits(my.t->_is_acid);
  out << bits(my.t->_is_ascend_dungeon);
  out << bits(my.t->_is_ascend_sewer);
  out << bits(my.t->_is_barrel);
  out << bits(my.t->_is_basalt);
  out << bits(my.t->_is_brazier);
  out << bits(my.t->_is_bridge);
  out << bits(my.t->_is_able_to_burn);
  out << bits(my.t->_is_chasm);
  out << bits(my.t->_is_combustible);
  out << bits(my.t->_is_corpse);
  out << bits(my.t->_is_corridor);
  out << bits(my.t->_is_currently_pixelart_raycast_lit);
  out << bits(my.t->_is_cursor_path_blocker);
  out << bits(my.t->_is_cursor_path_hazard);
  out << bits(my.t->_is_deep_water);
  out << bits(my.t->_is_descend_dungeon);
  out << bits(my.t->_is_descend_sewer);
  out << bits(my.t->_is_dirt);
  out << bits(my.t->_is_door);
  out << bits(my.t->_is_dry_grass);
  out << bits(my.t->_is_enchantstone);
  out << bits(my.t->_is_fire);
  out << bits(my.t->_is_floor);
  out << bits(my.t->_is_foilage);
  out << bits(my.t->_is_carnivorous_plant);
  out << bits(my.t->_is_food);
  out << bits(my.t->_is_gas_poison);
  out << bits(my.t->_is_gold);
  out << bits(my.t->_is_green_blood);
  out << bits(my.t->_is_hazard);
  out << bits(my.t->_is_heavy);
  out << bits(my.t->_is_block_of_ice);
  out << bits(my.t->_is_key);
  out << bits(my.t->_is_lava);
  out << bits(my.t->_is_mob);
  out << bits(my.t->_is_monst);
  out << bits(my.t->_is_potion);
  out << bits(my.t->_is_red_blood);
  out << bits(my.t->_is_ring);
  out << bits(my.t->_is_ripple);
  out << bits(my.t->_is_rock);
  out << bits(my.t->_is_secret_door);
  out << bits(my.t->_is_shallow_water);
  out << bits(my.t->_is_shovable);
  out << bits(my.t->_is_skillstone);
  out << bits(my.t->_is_smoke);
  out << bits(my.t->_is_spiderweb);
  out << bits(my.t->_is_sticky);
  out << bits(my.t->_is_sticky);
  out << bits(my.t->_is_treasure_type);
  out << bits(my.t->_is_wall);
  out << bits(my.t->_is_wand_or_staff);
  out << bits(my.t->_is_wet_grass);
  out << bits(my.t->_noisemap);
  out << bits(my.t->_noisemap_in);

  out << bits(my.t->can_see_currently);
  out << bits(my.t->can_see_ever);

  out << bits(my.t->prev_levels);
  out << bits(my.t->next_levels);

  out << bits(my.t->world_at);
  out << bits(my.t->grid_at);
  out << bits(my.t->biome);

  out << bits(my.t->difficulty_depth);
  out << bits(my.t->dungeon_walk_order_level_no);

  out << bits(my.t->is_boss_level);
  out << bits(my.t->is_shop_level);
  out << bits(my.t->is_final_boss_level);
  out << bits(my.t->is_crystal_level);

  out << bits(my.t->d1000_chance_of_creating_mob_challenge_class_a);
  out << bits(my.t->d1000_chance_of_creating_mob_challenge_class_b);
  out << bits(my.t->d1000_chance_of_creating_monst);
  out << bits(my.t->d1000_chance_of_creating_treasure_class_a);
  out << bits(my.t->d1000_chance_of_creating_treasure_class_b);
  out << bits(my.t->d1000_chance_of_creating_treasure_class_c);
  out << bits(my.t->d1000_chance_of_creating_weapon_class_a);
  out << bits(my.t->d1000_chance_of_creating_weapon_class_b);
  out << bits(my.t->d1000_chance_of_creating_weapon_class_c);

  out << bits(my.t->maxx);
  out << bits(my.t->maxy);
  out << bits(my.t->minx);
  out << bits(my.t->miny);

  out << bits(my.t->is_cursor_found);
  out << bits(my.t->is_final_level);
  out << bits(my.t->is_first_level);
  out << bits(my.t->is_completed);
  out << bits(my.t->is_heatmap_valid);
  out << bits(my.t->is_map_changed);
  out << bits(my.t->is_map_follow_player);
  out << bits(my.t->is_map_mini_valid);
  out << bits(my.t->is_starting);
  out << bits(my.t->is_entered_by_falling);

  out << bits(my.t->cursor_at);
  out << bits(my.t->cursor_old);
  out << bits(my.t->map_br);
  out << bits(my.t->map_tl);
  out << bits(my.t->pixel_map_at);

  out << bits(my.t->map_at);
  out << bits(my.t->map_wanted_at);

  out << bits(my.t->mouse_at);
  out << bits(my.t->mouse_old);

  out << bits(my.t->wobble);

  out << bits(my.t->monst_count);

  out << bits(my.t->seed);

  out << bits(my.t->all_things_id_at);

  out << bits(my.t->fbo_light);

#ifdef ENABLE_DEBUG_THING_SER
  {
    LOG("INF: Check things");
    TRACE_AND_INDENT();

    for (auto p : my.t->all_things) {
      auto t = p.second;
      my.t->check_thing(t);
    }
  }
#endif

#ifdef ENABLE_DEBUG_THING_SER
  {
    LOG("INF: Saved slots");
    TRACE_AND_INDENT();

    for (auto x = 0; x < MAP_WIDTH; x++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          auto id = get(my.t->all_things_id_at, x, y, slot);
          if (id.ok()) {
            CON("save slot %d @ %d,%d : %" PRIX32, slot, x, y, id.id);
          }
        }
      }
    }
  }
#endif

  {
    LOG("INF: Save things");
    TRACE_AND_INDENT();

    for (auto x = 0; x < MAP_WIDTH; x++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          auto id = get(my.t->all_things_id_at, x, y, slot);
          if (id.ok()) {
            const Thingp t = my.t->thing_find(id);
            if (unlikely(! t)) {
              ERR("Found a thing I could not save %" PRIX32, id.id);
              return out;
            }

#ifdef ENABLE_DEBUG_THING_SER
            t->con("Save");
#endif
            out << bits(t);
          }
        }
      }
    }
  }

  WRITE_MAGIC(THING_MAGIC_FINAL);
  LOG("INF: Saved things");

  return (out);
}

std::ostream &operator<<(std::ostream &out, Bits< const class World & > const my)
{
  TRACE_AND_INDENT();

  int count {};
  int step {};

  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        point3d p(x, y, z);
        auto    l = get(my.t.levels, x, y, z);
        if (l) {
          count++;
        }
      }
    }
  }
  out << bits(count);

  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        point3d p(x, y, z);
        bool    exists;
        auto    l = get(my.t.levels, x, y, z);
        if (l) {
          step++;
          if (count > 1) {
            wid_progress_bar("Saving...", ((float) step) / ((float) count));
          }

          exists = true;
          LOG("INF: Save level %d,%d,%d", p.x, p.y, p.z);
          out << bits(p);
          out << bits(exists);
          out << bits(l);
          auto eol = GAME_SAVE_MARKER_EOL;
          out << bits(eol);
          LOG("INF: Saved level %d,%d,%d", p.x, p.y, p.z);
        } else {
          exists = false;
          out << bits(p);
          out << bits(exists);
        }
      }
    }
  }
  wid_progress_bar_destroy();
  return (out);
}

std::ostream &operator<<(std::ostream &out, Bits< const Config & > const my)
{
  TRACE_AND_INDENT();
  uint32_t serialized_size = sizeof(Config);
  out << bits(serialized_size);

  out << bits(g_opt_player_name);
  out << bits(my.t.ascii_gl_height);
  out << bits(my.t.ascii_gl_width);
  out << bits(g_opt_ascii);
  out << bits(my.t.config_pix_height);
  out << bits(my.t.config_pix_width);
  out << bits(my.t.debug_mode);
  out << bits(my.t.fps_counter);
  out << bits(my.t.game_pix_height);
  out << bits(my.t.game_pix_scale_height);
  out << bits(my.t.game_pix_scale_width);
  out << bits(my.t.game_pix_width);
  out << bits(my.t.game_pix_zoom);
  out << bits(my.t.gfx_allow_highdpi);
  out << bits(my.t.gfx_borderless);
  out << bits(my.t.gfx_fullscreen);
  out << bits(my.t.gfx_fullscreen_desktop);
  out << bits(my.t.gfx_inverted);
  out << bits(my.t.gfx_show_hidden);
  out << bits(my.t.gfx_vsync_enable);
  out << bits(my.t.mouse_wheel_lr_negated);
  out << bits(my.t.mouse_wheel_ud_negated);
  out << bits(my.t.key_action0);
  out << bits(my.t.key_action1);
  out << bits(my.t.key_action2);
  out << bits(my.t.key_action3);
  out << bits(my.t.key_action4);
  out << bits(my.t.key_action5);
  out << bits(my.t.key_action6);
  out << bits(my.t.key_action7);
  out << bits(my.t.key_action8);
  out << bits(my.t.key_action9);
  out << bits(my.t.key_skill0);
  out << bits(my.t.key_skill1);
  out << bits(my.t.key_skill2);
  out << bits(my.t.key_skill3);
  out << bits(my.t.key_skill4);
  out << bits(my.t.key_skill5);
  out << bits(my.t.key_skill6);
  out << bits(my.t.key_skill7);
  out << bits(my.t.key_skill8);
  out << bits(my.t.key_skill9);
  out << bits(my.t.key_ascend);
  out << bits(my.t.key_attack);
  out << bits(my.t.key_console);
  out << bits(my.t.key_descend);
  out << bits(my.t.key_gfx_toggle);
  out << bits(my.t.key_drop);
  out << bits(my.t.key_eat);
  out << bits(my.t.key_help);
  out << bits(my.t.key_inventory);
  out << bits(my.t.key_jump);
  out << bits(my.t.key_load);
  out << bits(my.t.key_map_down);
  out << bits(my.t.key_map_left);
  out << bits(my.t.key_map_right);
  out << bits(my.t.key_map_up);
  out << bits(my.t.key_move_down);
  out << bits(my.t.key_move_left);
  out << bits(my.t.key_move_right);
  out << bits(my.t.key_move_up);
  out << bits(my.t.key_quit);
  out << bits(my.t.key_robot_mode);
  out << bits(my.t.key_save);
  out << bits(my.t.key_screenshot);
  out << bits(my.t.key_throw);
  out << bits(my.t.key_use);
  out << bits(my.t.key_wait_or_collect);
  out << bits(my.t.key_zoom_in);
  out << bits(my.t.key_zoom_out);
  out << bits(my.t.music_volume);
  out << bits(my.t.one_pixel_height);
  out << bits(my.t.one_pixel_width);
  out << bits(my.t.sdl_delay);
  out << bits(my.t.snapshot_freq);
  out << bits(my.t.sound_volume);
  out << bits(my.t.tile_height);
  out << bits(my.t.tile_pixel_height);
  out << bits(my.t.tile_pixel_width);
  out << bits(my.t.tile_pix_height);
  out << bits(my.t.tile_pix_width);
  out << bits(my.t.tile_width);
  out << bits(my.t.ui_pix_height);
  out << bits(my.t.ui_pix_width);
  out << bits(my.t.ui_pix_zoom);
  out << bits(my.t.ui_ascii_term_height);
  out << bits(my.t.ui_ascii_term_width);
  out << bits(my.t.ui_gfx_term_height);
  out << bits(my.t.ui_gfx_term_width);
  out << bits(my.t.video_w_h_ratio);
  out << bits(my.t.window_pix_height);
  out << bits(my.t.window_pix_width);

  out << bits(g_opt_seed_name);
  out << bits(my.t.hiscores);

  return (out);
}

std::ostream &operator<<(std::ostream &out, Bits< const class Game & > const my)
{
  TRACE_AND_INDENT();
  uint32_t serialized_size = sizeof(Game);
  out << bits(my.t.version);
  out << bits(serialized_size);
  out << bits(my.t.save_slot);
  out << bits(my.t.save_meta);
  out << bits(my.t.save_file);
  out << bits(my.t.appdata);
  out << bits(my.t.saved_dir);
  out << bits(my.t.config);
  out << bits(my.t.world);

  out << bits(my.t.started);
  out << bits(my.t.things_are_moving);
  out << bits(false); // robot_mode

  out << bits(my.t.map_mini_over);
  out << bits(my.t.seed);
  out << bits(my.t.seed_name);
  out << bits(my.t.tick_requested);
  out << bits(my.t.current_level);
  out << bits(my.t.frame_count);
  out << bits(my.t.fps_value);
  out << bits(my.t.tick_completed);
  out << bits(my.t.tick_current);
  out << bits(my.t.inventory_highlight_slot);
  out << bits(my.t.previous_slot);
  out << bits(my.t.skillbox_highlight_slot);

  out << bits(wid_topcon_serialize());
  out << bits(wid_console_serialize());

  return (out);
}

bool Game::save(std::string file_to_save)
{
  TRACE_AND_INDENT();
  std::stringstream s(std::ios::in | std::ios::out | std::ios::binary);

  const class Game &c = *this;
  s << bits(c);

  //
  // Get the pre compress buffer
  //
  auto data = s.str();
  s.seekg(0, std::ios::end);
  lzo_uint uncompressed_len = s.tellg();
  s.seekg(0, std::ios::beg);

  HEAP_ALLOC(uncompressed, uncompressed_len);
  HEAP_ALLOC(compressed, uncompressed_len);
  memcpy(uncompressed, data.c_str(), uncompressed_len);

#if 0
  IF_DEBUG3 {
    std::cout << "before compression ";
    (void) hexdump((const unsigned char*)uncompressed, uncompressed_len);
  }
#endif

  if (lzo_init() != LZO_E_OK) {
    ERR("LZO init fail: Enable '-DLZO_DEBUG' for diagnostics)");
  }

  HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

  lzo_uint compressed_len = 0;
  int      r =
      lzo1x_1_compress((lzo_bytep) uncompressed, uncompressed_len, (lzo_bytep) compressed, &compressed_len, wrkmem);
  if (r == LZO_E_OK) {
    LOG("INF: Saved as %s, compress %luMb -> %luMb", file_to_save.c_str(),
        (unsigned long) uncompressed_len / (1024 * 1024), (unsigned long) compressed_len / (1024 * 1024));
  } else {
    ERR("LZO internal error - compression failed: %d", r);
    return false;
  }

  //
  // Uncompress and check the data matches
  //
  IF_DEBUG3
  {
    HEAP_ALLOC(tmp_compressed, compressed_len);
    HEAP_ALLOC(tmp_uncompressed, uncompressed_len);
    memcpy(tmp_compressed, compressed, compressed_len);

    lzo_uint new_len = 0;
    int      r =
        lzo1x_decompress((lzo_bytep) tmp_compressed, compressed_len, (lzo_bytep) tmp_uncompressed, &new_len, nullptr);
    if (r == LZO_E_OK && new_len == uncompressed_len) {
      if (memcmp(tmp_uncompressed, uncompressed, uncompressed_len)) {
        ERR("LZO compress-decompress failed");
      }
    } else {
      /* this should NEVER happen */
      ERR("LZO internal error - decompression failed: %d", r);
      return false;
    }
  }

  //
  // Dump the post compress buffer
  //
#if 0
  IF_DEBUG3 {
    std::cout << "after compression ";
    (void) hexdump((const unsigned char *)compressed, compressed_len);
  }
#endif

  //
  // Save the post compress buffer
  //
  uint32_t cs = csum((char *) uncompressed, uncompressed_len);

  auto ofile = fopen(file_to_save.c_str(), "wb");
  fwrite((char *) &uncompressed_len, sizeof(uncompressed_len), 1, ofile);
  fwrite((char *) &cs, sizeof(cs), 1, ofile);
  fwrite(compressed, compressed_len, 1, ofile);
  fclose(ofile);

  free(uncompressed);
  free(compressed);
  free(wrkmem);

  return true;
}

void Game::save(void)
{
  TRACE_AND_INDENT();
  LOG("-");
  CON("INF: Saving %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  save(save_file);

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Saved %s, seed %u", save_file.c_str(), seed);
  LOG("-");
}

void Game::save(int slot)
{
  TRACE_AND_INDENT();
  if (slot < 0) {
    return;
  }

  if (slot >= UI_WID_SAVE_SLOTS) {
    return;
  }

  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        point3d p(x, y, z);
        auto    l = get(game->world.levels, x, y, z);
        if (l) {
          l->things_gc_force();
        }
      }
    }
  }

  auto save_file = saved_dir + "saved-slot-" + std::to_string(slot);

  LOG("-");
  CON("INF: Saving %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  save(save_file);

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Saved %s, seed %u", save_file.c_str(), seed);
  LOG("-");

  TOPCON("Saved the game to %s.", save_file.c_str());
}

void Game::save_snapshot(void)
{
  TOPCON("Autosaving...");

  TRACE_AND_INDENT();
  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        point3d p(x, y, z);
        auto    l = get(game->world.levels, x, y, z);
        if (l) {
          l->things_gc_force();
        }
      }
    }
  }

  auto save_file = saved_dir + "saved-snapshot";

  LOG("-");
  CON("INF: Saving %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  save(save_file);

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Saved %s, seed %u", save_file.c_str(), seed);
  LOG("-");

  TOPCON("%%fg=green$Autosaved.%%fg=reset$");
}

void Game::save_config(void)
{
  TRACE_AND_INDENT();
  auto          filename = saved_dir + "config";
  std::ofstream out(filename, std::ios::binary);
  const Config &c = game->config;
  out << bits(c);
}

void wid_save_destroy(void)
{
  TRACE_AND_INDENT();
  if (wid_save) {
    delete wid_save;
    wid_save = nullptr;
    game->change_state(Game::STATE_NORMAL, "save destroy");
  }
}

static uint8_t wid_save_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL:
    case KMOD_RCTRL:
    default:
      switch (key->sym) {
        default:
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case '0':
              case '1':
              case '2':
              case '3':
              case '4':
              case '5':
              case '6':
              case '7':
              case '8':
              case '9':
                {
                  TRACE_AND_INDENT();
                  int slot = c - '0';
                  game->save(slot);
                  wid_save_destroy();
                  return true;
                }
              case 'b':
              case SDLK_ESCAPE:
                {
                  TRACE_AND_INDENT();
                  CON("INF: Save game cancelled");
                  wid_save_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_save_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static uint8_t wid_save_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto slot = wid_get_int_context(w);
  game->save(slot);
  wid_save_destroy();
  return true;
}

static uint8_t wid_save_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_save_destroy();
  return true;
}

void Game::wid_save_select(void)
{
  TRACE_AND_INDENT();
  if (wid_save) {
    return;
  }

  auto  m  = TERM_WIDTH / 2;
  auto  h  = TERM_HEIGHT / 2;
  point tl = make_point(m - 40, h - 7);
  point br = make_point(m + 40, h + 8);
  if (! g_opt_ascii) {
    br.y += 3;
  }
  auto width = br.x - tl.x;

  wid_save = new WidPopup("Game save", tl, br, tile_find_mand("save"), "", false, false);
  wid_set_on_key_up(wid_save->wid_popup_container, wid_save_key_up);
  wid_set_on_key_down(wid_save->wid_popup_container, wid_save_key_down);

  //
  // Close icon
  //
  {
    auto w = wid_new_square_button(wid_save->wid_popup_container, "wid inventory window close");
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
      wid_set_bg_tilename(w, "ui_icon_close");
    }
    wid_set_on_mouse_up(w, wid_save_cancel);
  }

  game_load_headers_only = true;

  wid_save->log(UI_LOGGING_EMPTY_LINE);
  wid_save->log("Choose a save slot.");

  int y_at = 3;
  for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
    Game tmp;
    auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);

    if (slot == UI_WID_SAVE_SLOTS - 1) {
      tmp_file = saved_dir + "saved-snapshot";
    }

    auto  p  = wid_save->wid_text_area->wid_text_area;
    auto  w  = wid_new_square_button(p, "save slot");
    point tl = make_point(0, y_at);
    point br = make_point(width - 2, y_at);

    std::string s = std::to_string(slot) + " ";
    if (! load(tmp_file, tmp)) {
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        s += "<no snapshot>";
      } else {
        s += "<empty>";
      }
      wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
    } else {
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        s += "snapshot: " + tmp.save_meta;
      } else {
        s += tmp.save_meta;
      }
      wid_set_style(w, UI_WID_STYLE_HORIZ_LIGHT);
    }

    if (slot == UI_WID_SAVE_SLOTS - 1) {
      //
      // Cannot save over
      //
    } else {
      wid_set_on_mouse_up(w, wid_save_mouse_up);
      wid_set_int_context(w, slot);
    }

    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    y_at++;
  }
  game_load_headers_only = false;
  wid_update(wid_save->wid_text_area->wid_text_area);

  game->change_state(Game::STATE_SAVE_MENU, "save select");
  wid_actionbar_init();
}
