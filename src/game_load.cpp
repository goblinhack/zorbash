//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "minilzo.hpp"
#include "my_alloc.hpp"
#include "my_array_bounds_check.hpp"
#include "my_file.hpp"
#include "my_game.hpp"
#include "my_game_error.hpp"
#include "my_monst.hpp"
#include "my_sdl.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_popup.hpp"
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
std::array< bool, UI_WID_SAVE_SLOTS > slot_valid;

#define READ_MAGIC(what, m)                                                                                          \
  {                                                                                                                  \
    uint32_t magic;                                                                                                  \
    in >> bits(magic);                                                                                               \
    if (magic != m) {                                                                                                \
      game_load_error = "bad " what " magic expected: " + std::to_string(m) + " got " + std::to_string(magic);       \
      return (in);                                                                                                   \
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
   in >> bits(my.t->born);
   in >> bits(my.t->bounce_fade);
   in >> bits(my.t->bounce_height);
   in >> bits(my.t->capacity_height);
   in >> bits(my.t->capacity_width);
   in >> bits(my.t->dead_reason);
   in >> bits(my.t->distance_throw);
   in >> bits(my.t->enchant);
   in >> bits(my.t->enchant_max);
   in >> bits(my.t->fadeup_fade);
   in >> bits(my.t->fadeup_height);
   in >> bits(my.t->fall_height);
   in >> bits(my.t->gold);
   in >> bits(my.t->health);
   in >> bits(my.t->health_max);
   in >> bits(my.t->keys);
   in >> bits(my.t->last_failed_jump_at);
   in >> bits(my.t->leader_id);
   in >> bits(my.t->lifespan);
   in >> bits(my.t->light_col);
   in >> bits(my.t->light_strength);
   in >> bits(my.t->lunge_to);
   in >> bits(my.t->manifestor_id);
   in >> bits(my.t->monst_state);
   in >> bits(my.t->msg);
   in >> bits(my.t->necrosis);
   in >> bits(my.t->on_fire_id_anim);
   in >> bits(my.t->owner_id);
   in >> bits(my.t->poison);
   in >> bits(my.t->score);
   in >> bits(my.t->spawner_owner_id);
   in >> bits(my.t->stamina);
   in >> bits(my.t->stamina_max);
   in >> bits(my.t->stat_armor_class);
   in >> bits(my.t->stat_attack_bonus);
   in >> bits(my.t->stat_constitution);
   in >> bits(my.t->stat_dexterity);
   in >> bits(my.t->stats02);
   in >> bits(my.t->stats03);
   in >> bits(my.t->stats04);
   in >> bits(my.t->stats05);
   in >> bits(my.t->stats06);
   in >> bits(my.t->stats07);
   in >> bits(my.t->stats08);
   in >> bits(my.t->stats09);
   in >> bits(my.t->stats10);
   in >> bits(my.t->stats11);
   in >> bits(my.t->stats12);
   in >> bits(my.t->stats17);
   in >> bits(my.t->stats19);
   in >> bits(my.t->stat_strength);
   in >> bits(my.t->submerged_offset);
   in >> bits(my.t->tick_last_did_something);
   in >> bits(my.t->tick_last_dropped);
   in >> bits(my.t->tick_last_escape);
   in >> bits(my.t->tick_last_level_change);
   in >> bits(my.t->tick_last_location_check);
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
   in >> bits(my.t->follower_count);
   in >> bits(my.t->minion_count);
   in >> bits(my.t->owned_count);
   in >> bits(my.t->spawned_count);
   in >> bits(my.t->treasure_map_count);
   in >> bits(my.t->beast_map_count);
  // clang-format on
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  return (in);
}

std::istream &operator>>(std::istream &in, Bits< ThingItemp & > my)
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
  in >> bits(my.t->bag_position);
  in >> bits(my.t->last_bag_position);
  in >> bits(my.t->where_i_dropped_an_item_last);
  in >> bits(my.t->where_i_failed_to_collect_last);
  in >> bits(my.t->bag);
  in >> bits(my.t->carrying);
  in >> bits(my.t->skills);
  in >> bits(my.t->buffs);
  in >> bits(my.t->debuffs);
  in >> bits(my.t->inventory_shortcuts);
  in >> bits(my.t->skillbox_id);
  in >> bits(my.t->buffbox_id);
  in >> bits(my.t->debuffbox_id);
  /////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  //
  // Keep these sorted alphabetically to make it easier to see additions
  // and always update game_load.cpp and game_save.cpp
  /////////////////////////////////////////////////////////////////////////

  return (in);
}

std::istream &operator>>(std::istream &in, Bits< ThingAip & > my)
{
  TRACE_AND_INDENT();
  in >> bits(my.t->age_map.val);
  in >> bits(my.t->seen_map.val);
  in >> bits(my.t->interrupt_map.val);
  in >> bits(my.t->dmap_can_see.val);
  in >> bits(my.t->can_see_currently.can_see);
  in >> bits(my.t->can_see_ever.can_see);
  in >> bits(my.t->enemies);
  in >> bits(my.t->goal_penalty);
  in >> bits(my.t->avoid);
  in >> bits(my.t->move_path);
  in >> bits(my.t->wander_dest);
  in >> bits(my.t->idle_count);
  in >> bits(my.t->stuck_count);
  return (in);
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
    return (in);
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

  my.t->_itemp            = nullptr;
  bool monst_item_present = false;
  in >> bits(monst_item_present);
  if (monst_item_present) {
    my.t->new_itemp();
    in >> bits(my.t->_itemp);
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
  in >> bits(my.t->frame_count);
  in >> bits(my.t->interpolated_at);
  in >> bits(my.t->last_at);
  in >> bits(my.t->curr_at);
  in >> bits(my.t->last_attached);
  in >> bits(my.t->last_blit_br);
  in >> bits(my.t->last_blit_tl);
  in >> bits(my.t->last_blit_at);
  in >> bits(T);
  my.t->ts_next_frame = load(T);
  in >> bits(my.t->tile_curr);
  in >> bits(my.t->alpha);
  in >> bits(my.t->z_depth);
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
  // CON("LOAD %016LX ",bits64);
  // clang-format off
  my.t->has_ever_moved = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->has_laser = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->has_light = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->has_projectile = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_activated = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_attached = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_being_destroyed = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_scheduled_for_gc = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_bouncing = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_changing_level = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_dead = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_dying = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_facing_left = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_fadeup = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_falling = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_ring2 = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_hidden = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_hungry = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_in_lava = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_in_water = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_jumping = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_moving = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_offscreen = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_open = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_resurrected = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_resurrecting = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_resurrection_blocked = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_scheduled_for_death = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_scheduled_for_jump_end = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_sleeping = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_starving = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_the_grid = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_the_player = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_waiting_to_ascend_dungeon = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_waiting_to_ascend_sewer = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_waiting_to_descend_dungeon = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_waiting_to_descend_sewer = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->is_waiting_to_leave_level_has_completed_fall = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;

  in >> bits(bits64);
  // CON("LOAD %016LX ",bits64);
  shift = 0;

  my.t->i_set_water = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_acid = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_ascend_dungeon = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_ascend_sewer = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_barrel = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_blood = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_brazier = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_bridge = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_chasm = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_corpse = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_corridor = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_deep_water = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_descend_dungeon = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_descend_sewer = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_dirt = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_door = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_dry_grass = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_enchantstone = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_cursor_path_hazard_for_player = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_heavy = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_fire = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_floor = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_foilage = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_food = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_gold = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_hazard = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_key = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_lava = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_light_blocker = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_mob = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_monst = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_obs_wall_or_door = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_obs_destructable = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_poisonous_danger_level = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_necrotic_danger_level = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_potion = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_ripple = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_rock = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_secret_door = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_shallow_water = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_skillstone = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_smoke = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_spiderweb = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_sticky = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_shovable = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_treasure_class_a = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_treasure_class_b = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_treasure_class_c = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_treasure_type = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_wall = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_wand = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
  my.t->i_set_is_ring = ((bits64 >> shift) & 1LLU) ? 1LLU : 0LLU; shift++;
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
    LOG("LOAD %d bytes %s TP %d ID %x last_at %d,%d", (int) diff, name.c_str(), my.t->tp_id, my.t->id.id,
        my.t->last_at.x, my.t->last_at.y);
  }

  return (in);
}

std::istream &operator>>(std::istream &in, Bits< Level *& > my)
{
  TRACE_AND_INDENT();
  auto l = my.t;

  l->player                                = nullptr;
  l->cursor                                = nullptr;
  l->all_things_id_at                      = {};
  l->all_things_ptr_at                     = {};
  l->all_things                            = {};
  l->all_things_of_interest                = {};
  l->all_things_of_interest_pending_add    = {};
  l->all_things_of_interest_pending_remove = {};
  l->all_animated_things                   = {};
  l->all_animated_things_pending_add       = {};
  l->all_animated_things_pending_remove    = {};
  l->all_things_to_be_destroyed            = {};

  uint32_t csum_in = 0;
  in >> bits(csum_in);

  in >> bits(l->ts_created);
  old_ts_created = l->ts_created;
  in >> bits(l->ts_saved);
  auto dungeon_age = l->ts_saved - l->ts_created;
  new_ts_created   = time_get_time_ms() - dungeon_age;
  l->ts_created    = new_ts_created;
  l->ts_saved      = new_ts_created + dungeon_age;
  in >> bits(l->ts_fade_out_begin);
  in >> bits(l->ts_fade_in_begin);

  in >> bits(my.t->_is_light_blocker);
  in >> bits(my.t->_is_lit_ever);
  in >> bits(my.t->_is_obs_wall_or_door);
  in >> bits(my.t->_is_obs_destructable);
  in >> bits(my.t->_fade_in_map);
  in >> bits(my.t->_gfx_water);
  in >> bits(my.t->_heatmap);
  in >> bits(my.t->_is_able_to_stand_on);
  in >> bits(my.t->_is_acid);
  in >> bits(my.t->_is_ascend_dungeon);
  in >> bits(my.t->_is_ascend_sewer);
  in >> bits(my.t->_is_barrel);
  in >> bits(my.t->_is_blood);
  in >> bits(my.t->_is_brazier);
  in >> bits(my.t->_is_bridge);
  in >> bits(my.t->_is_chasm);
  in >> bits(my.t->_is_corpse);
  in >> bits(my.t->_is_corridor);
  in >> bits(my.t->_is_deep_water);
  in >> bits(my.t->_is_descend_dungeon);
  in >> bits(my.t->_is_descend_sewer);
  in >> bits(my.t->_is_dirt);
  in >> bits(my.t->_is_door);
  in >> bits(my.t->_is_dry_grass);
  in >> bits(my.t->_is_enchantstone);
  in >> bits(my.t->_is_cursor_path_hazard_for_player);
  in >> bits(my.t->_is_heavy);
  in >> bits(my.t->_is_fire);
  in >> bits(my.t->_is_floor);
  in >> bits(my.t->_is_foilage);
  in >> bits(my.t->_is_food);
  in >> bits(my.t->_is_gold);
  in >> bits(my.t->_is_hazard);
  in >> bits(my.t->_is_key);
  in >> bits(my.t->_is_lava);
  in >> bits(my.t->_is_lit_currently);
  in >> bits(my.t->_is_mob);
  in >> bits(my.t->_is_monst);
  in >> bits(my.t->_is_potion);
  in >> bits(my.t->_is_ripple);
  in >> bits(my.t->_is_rock);
  in >> bits(my.t->_is_secret_door);
  in >> bits(my.t->_is_shallow_water);
  in >> bits(my.t->_is_skillstone);
  in >> bits(my.t->_is_smoke);
  in >> bits(my.t->_is_spiderweb);
  in >> bits(my.t->_is_sticky);
  in >> bits(my.t->_is_shovable);
  in >> bits(my.t->_is_treasure_class_a);
  in >> bits(my.t->_is_treasure_class_b);
  in >> bits(my.t->_is_treasure_class_c);
  in >> bits(my.t->_is_treasure_type);
  in >> bits(my.t->_is_wall);
  in >> bits(my.t->_is_wand);
  in >> bits(my.t->_is_ring);
  in >> bits(my.t->_is_map_changed);

  in >> bits(l->all_things_id_at);
  in >> bits(l->cursor_at);
  in >> bits(l->cursor_old);
  in >> bits(l->cursor_found);
  in >> bits(l->fbo_light);
  in >> bits(l->is_level_type_dungeon);
  in >> bits(l->is_heatmap_valid);
  in >> bits(l->is_level_type_sewer);
  in >> bits(l->is_starting);
  in >> bits(l->map_at);
  in >> bits(l->map_br);
  in >> bits(l->map_changed);
  in >> bits(l->map_follow_player);
  in >> bits(l->map_tl);
  in >> bits(l->map_wanted_at);
  in >> bits(l->maxx);
  in >> bits(l->maxy);
  in >> bits(l->minimap_valid);
  in >> bits(l->minx);
  in >> bits(l->miny);
  in >> bits(l->monst_count);
  in >> bits(l->mouse_at);
  in >> bits(l->mouse_old);
  in >> bits(l->pixel_map_at);
  in >> bits(l->seed);
  in >> bits(l->world_at);

  l->update_new_level();
  l->ts_redraw_bg      = 1; // Force redraw
  l->ts_fade_in_begin  = time_get_time_ms_cached();
  l->map_changed       = true;
  l->map_follow_player = true;

  auto p = l->world_at;
  LOG("DGN: Loading things for level %d,%d,%d", p.x, p.y, p.z);

#if 0
  LOG("DGN: Loaded slots");
  FOR_ALL_THING_GROUPS(group) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          auto id = get(my.t->all_things_id_at[group], x, y, slot);
          if (id.ok()) {
            CON("Load save slot %d @ %d,%d group %d : %" PRIx32, slot, x, y, group, id.id);
          }
        }
      }
    }
  }
#endif
  TRACE_AND_INDENT();
  //
  // Operate on a copy, not live data that might change as we add things
  //
  FOR_ALL_THING_GROUPS(group)
  {
    auto ids = my.t->all_things_id_at[ group ];

    for (auto x = 0; x < MAP_WIDTH; x++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          auto id = get(ids, x, y, slot);
          if (id.ok()) {
            auto t = new Thing();
            in >> bits(t);

            if (game_load_error != "") {
              return in;
            }

            //
            // Cannot use t->log here as thing is no inited yet
            //
            t->level = l;
            if (t->id != id) {
              game_load_error = string_sprintf(
                  "found different thing than expected at map position "
                  "%d,%d slot %d: found %" PRIx32 ", expected %" PRIx32,
                  x, y, slot, t->id.id, id.id);

              if (0) {
                for (auto slot = 0; slot < MAP_SLOTS; slot++) {
                  auto id = get(ids, x, y, slot);
                  CON("slot %d : %" PRIx32, slot, id.id);
                }
              }

              return in;
            }

            t->reinit();
            // t->con("LOADED @%d,%d %x", t->curr_at.x, t->curr_at.y, t->id.id);

            // CON("From save file  : %s", t->debug_str.c_str());
            // CON("Newly created as: %s", t->to_dbg_saved_string().c_str());
#ifdef ENABLE_DEBUG_THING_SER
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
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : l->all_things[ group ]) {
      auto t = p.second;
      csum += t->curr_at.x + t->curr_at.y + t->id.id;
      // t->con("LOAD %f %f %d", t->curr_at.x, t->curr_at.y, t->id.id);
      t->init_lights();
    }
  }

  if (csum != csum_in) {
    game_load_error = string_sprintf("found different thing checksum %u expected %u", csum, csum_in);
    return in;
  }

  l->update_new_level();

  READ_MAGIC("level end", THING_MAGIC_FINAL);
  LOG("DGN: Loaded things for level %d,%d,%d", p.x, p.y, p.z);

  my.t->update_map();
  LOG("DGN: updated map for level %d,%d,%d", p.x, p.y, p.z);
  return (in);
}

std::istream &operator>>(std::istream &in, Bits< class World & > my)
{
  TRACE_AND_INDENT();
  my.t.levels         = {};
  my.t.all_thing_ptrs = {};

  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        point3d p;
        bool    exists;
        in >> bits(p);
        in >> bits(exists);
        if (p != point3d(x, y, z)) {
          game_load_error =
              string_sprintf("level mismatch expected %d,%d,%d vs found %d,%d,%d", x, y, z, p.x, p.y, p.z);
          return (in);
        }

        if (exists) {
          CON("DGN: Loading level %d,%d,%d", p.x, p.y, p.z);
          auto l = new Level();
          set(my.t.levels, x, y, z, l);
          in >> bits(l);
          if (game_load_error != "") {
            return in;
          }

          int eol;
          in >> bits(eol);
          if (eol != GAME_SAVE_MARKER_EOL) {
            game_load_error = string_sprintf("end of level %d,%d,%d not found", x, y, z);
            return (in);
          }
          CON("DGN: Loaded level %d,%d,%d", p.x, p.y, p.z);
        }
      }
    }
  }
  return (in);
}

std::istream &operator>>(std::istream &in, Bits< Config & > my)
{
  TRACE_AND_INDENT();
  /* uint32_t           header_size                  */ in >> bits(my.t.header_size);
  if (my.t.header_size != sizeof(Config)) {
    game_load_error = "bad save file header version";
    return in;
  }

  in >> bits(my.t.game_pix_scale_height);
  in >> bits(my.t.game_pix_scale_width);
  in >> bits(my.t.game_pix_zoom);
  in >> bits(my.t.one_pixel_height);
  in >> bits(my.t.one_pixel_width);
  in >> bits(my.t.tile_pix_height);
  in >> bits(my.t.tile_pix_width);
  in >> bits(my.t.tile_pixel_height);
  in >> bits(my.t.tile_pixel_width);
  in >> bits(my.t.ui_pix_scale_height);
  in >> bits(my.t.ui_pix_scale_width);
  in >> bits(my.t.ui_pix_zoom);
  in >> bits(my.t.video_w_h_ratio);
  in >> bits(my.t.debug_mode);
  in >> bits(my.t.fps_counter);
  in >> bits(my.t.gfx_allow_highdpi);
  in >> bits(my.t.gfx_borderless);
  in >> bits(my.t.gfx_fullscreen);
  in >> bits(my.t.gfx_fullscreen_desktop);
  in >> bits(my.t.gfx_inverted);
  in >> bits(my.t.gfx_minimap);
  in >> bits(my.t.gfx_show_hidden);
  in >> bits(my.t.gfx_vsync_enable);
  in >> bits(my.t.tile_height);
  in >> bits(my.t.tile_width);
  in >> bits(my.t.config_pix_height);
  in >> bits(my.t.config_pix_width);
  in >> bits(my.t.game_pix_height);
  in >> bits(my.t.game_pix_width);
  in >> bits(my.t.ui_pix_height);
  in >> bits(my.t.ui_pix_width);
  in >> bits(my.t.window_pix_height);
  in >> bits(my.t.window_pix_width);
  in >> bits(my.t.ascii_gl_height);
  in >> bits(my.t.ascii_gl_width);
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
  in >> bits(my.t.key_attack);
  in >> bits(my.t.key_console);
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
  in >> bits(my.t.key_unused4);
  in >> bits(my.t.key_unused5);
  in >> bits(my.t.key_use);
  in >> bits(my.t.key_wait_or_collect);
  in >> bits(my.t.key_zoom_in);
  in >> bits(my.t.key_zoom_out);
  in >> bits(my.t.music_volume);
  in >> bits(my.t.sdl_delay);
  in >> bits(my.t.sound_volume);
  in >> bits(g_opt_player_name);
  // seed name handled below

  if (! g_opt_override_debug_level) {
    if (my.t.debug_mode) {
      g_opt_debug3 = true;
      g_opt_debug2 = true;
      g_opt_debug1 = true;
    }
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

  if (! my.t.game_pix_zoom) {
    ERR("Loading, game_pix_zoom is zero");
    my.t.game_pix_zoom = GAME_DEFAULT_PIX_ZOOM;
    my.t.ui_pix_zoom   = GAME_DEFAULT_UI_ZOOM;
  }

  return (in);
}

std::istream &operator>>(std::istream &in, Bits< class Game & > my)
{
  TRACE_AND_INDENT();
  in >> bits(my.t.version);
  if (my.t.version != MYVER) {
    game_load_error = "old version '" MYVER "' v '" + my.t.version + "'";
    return (in);
  }
  in >> bits(my.t.header_size);
  if (my.t.header_size != (uint32_t) sizeof(Game)) {
    game_load_error = "old version '" MYVER "' v '" + my.t.version + "'";
    return (in);
  }
  in >> bits(my.t.save_slot);
  in >> bits(my.t.save_meta);
  in >> bits(my.t.save_file);
  if (game_load_headers_only) {
    return (in);
  }
  in >> bits(my.t.appdata);
  in >> bits(my.t.saved_dir);
  in >> bits(my.t.config);
  if (game_load_error != "") {
    return in;
  }
  in >> bits(my.t.world);
  if (game_load_error != "") {
    return in;
  }

  in >> bits(my.t.started);
  in >> bits(my.t.things_are_moving);
  in >> bits(my.t.minimap_over);
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
  in >> bits(my.t.robot_mode);
  in >> bits(my.t.skillbox_highlight_slot);

  std::vector< std::wstring > s;
  in >> bits(s);
  wid_topcon_deserialize(s);
  in >> bits(s);
  wid_console_deserialize(s);

  my.t.level = get(my.t.world.levels, my.t.current_level.x, my.t.current_level.y, my.t.current_level.z);
  return (in);
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
  } else {
    std::vector< char > bytes;
    return bytes;
  }
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
    return (bytes);
  } else {
    std::vector< char > bytes;
    return (bytes);
  }
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
      game_error("load error, empty file?");
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
      CON("DGN: Loading %s, decompress %luMb -> %luMb", file_to_load.c_str(),
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
  if (game_load_error != "") {
    if (! game_load_headers_only) {
      game_error("load error, " + game_load_error);
    }
    return false;
  }

  if (! game_load_headers_only) {
    wid_visible(wid_topcon_window);
    wid_visible(wid_botcon_window);
    wid_rightbar_fini();
    wid_rightbar_init();
    wid_actionbar_init();
  }

  free(uncompressed);
  free(compressed);
  return true;
}

void Game::load_config(void)
{
  TRACE_AND_INDENT();
  auto          filename = saved_dir + "config";
  std::ifstream in(filename);
  if (in.is_open()) {
    in >> bits(*(&game->config));
    game->config.dump("READ:");
  }
}

void Game::load(void)
{
  TRACE_AND_INDENT();
  LOG("-");
  CON("DGN: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("DGN: Loaded %s, seed %u", save_file.c_str(), seed);
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

  LOG("-");
  CON("DGN: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
  CON("DGN: Loaded %s, seed %d", save_file.c_str(), seed);
  LOG("-");

  TOPCON("Loaded the game from %s.", save_file.c_str());
}

void Game::load_snapshot(void)
{
  TRACE_AND_INDENT();
  game->fini();

  auto save_file = saved_dir + "saved-snapshot";

  LOG("-");
  CON("DGN: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("DGN: Loaded %s, seed %d", save_file.c_str(), seed);
  LOG("-");

  TOPCON("Loaded the game from %s.", save_file.c_str());
}

void wid_load_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_load;
  wid_load = nullptr;
  game->change_state(Game::STATE_NORMAL);
}

static uint8_t wid_load_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
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
                  CON("PLAYER: Load game cancelled");
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
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

static uint8_t wid_load_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto slot = wid_get_int_context(w);
  game->load(slot);
  wid_load_destroy();
  return true;
}

static uint8_t wid_load_saved_snapshot(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->load_snapshot();
  wid_load_destroy();
  return true;
}

void Game::load_select(void)
{
  TRACE_AND_INDENT();
  CON("PLAYER: Loading a saved game, destroy old");

  if (wid_load) {
    return;
  }

  auto  m     = TERM_WIDTH / 2;
  point tl    = make_point(m - 50, UI_TOPCON_VIS_HEIGHT + 2);
  point br    = make_point(m + 50, tl.y + 52);
  auto  width = br.x - tl.x;

  wid_load = new WidPopup("Game load", tl, br, tile_find_mand("load"), "", false, false);
  wid_set_on_key_up(wid_load->wid_popup_container, wid_load_key_up);
  wid_set_on_key_down(wid_load->wid_popup_container, wid_load_key_down);

  game_load_headers_only = true;

  wid_load->log(UI_LOGGING_EMPTY_LINE);
  wid_load->log("Choose a load slot.");

  int y_at = 3;
  for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
    Game tmp;
    auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);

    if (slot == UI_WID_SAVE_SLOTS - 1) {
      tmp_file = saved_dir + "saved-snapshot";
    }

    auto  p  = wid_load->wid_text_area->wid_text_area;
    auto  w  = wid_new_square_button(p, "load slot");
    point tl = make_point(0, y_at);
    point br = make_point(width - 2, y_at);

    std::string s = std::to_string(slot) + ": ";
    if (! load(tmp_file, tmp)) {
      if (game_load_error != "") {
        s += game_load_error;
      } else {
        if (slot == UI_WID_SAVE_SLOTS - 1) {
          s += "<no-snapshot>";
        } else {
          s += "<empty>";
        }
      }
      set(slot_valid, slot, false);
      wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
    } else {
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        s += "snapshot: " + tmp.save_meta;
      } else {
        s += tmp.save_meta;
      }
      wid_set_style(w, UI_WID_STYLE_HORIZ_LIGHT);
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        wid_set_on_mouse_up(w, wid_load_saved_snapshot);
      } else {
        wid_set_on_mouse_up(w, wid_load_mouse_up);
      }
      set(slot_valid, slot, true);
    }
    wid_set_int_context(w, slot);

    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    y_at += 1;
  }
  game_load_headers_only = false;
  wid_update(wid_load->wid_text_area->wid_text_area);

  wid_actionbar_init();
  game->change_state(Game::STATE_LOAD_MENU);
}
