//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_backtrace.hpp"

Thingp Level::thing_new(Tpp tp, const point at)
{
  if (unlikely(! tp)) {
    err("No tp provided for thing creation");
    return nullptr;
  }
  return thing_new(tp->name(), at);
}

Thingp Level::thing_new(const std::string &tp_name, Thingp owner) { return thing_new(tp_name, owner->mid_at); }

Thingp Level::thing_new(const std::string &name, const point at)
{
  auto t = new class Thing_();
  t->init(this, name, at);
  return (t);
}

Thing::Thing_(void) { newptr(MTYPE_THING, this, "thing"); }

void Thing::on_born(void)
{
  TRACE_AND_INDENT();
  auto on_born = tp()->on_born_do();
  if (std::empty(on_born)) {
    return;
  }

  auto t = split_tokens(on_born, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), (int) mid_at.x, (int) mid_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
  } else {
    ERR("Bad on_born call [%s] expected mod:function, got %d elems", on_born.c_str(), (int) on_born.size());
  }
}

void Thing::init(Levelp level, const std::string &name, const point born)
{
  verify(MTYPE_THING, this);

  this->level = level;
  mid_at      = born;
  last_mid_at = born;

  ts_next_frame = 0;
  if (name == "") {
    DIE("Thing template cannot be created: No name given");
  }

  const auto tpp = tp_find(name);
  if (unlikely(! tpp)) {
    ERR("Thing template [%s] not found", name.c_str());
    return;
  }

  tp_id = tpp->id;
  tp_or_update();

  //
  // Make sure we have the ability to carry items.
  //
  if (is_player() || is_monst() || is_item() || is_cursor()) {
    new_infop();
  }

  if (is_player() || is_monst() || is_item()) {
    new_itemp();
  }

  if (is_player() || is_monst() || is_cursor()) {
    new_aip();
  }

  //
  // Init the z depth
  //
  z_depth = tp()->z_depth;

  //
  // Start off up to data with the player
  //
  if (is_tickable()) {
    //
    // Newly spawned things, don't make them do something immediately
    // This can lead to recursion
    //
    set_tick_last_location_check(game->tick_current);
    set_tick_last_did_something(game->tick_current);
  }

  //
  // Must do this after TP assignment or logging will fail
  //
  if (game->robot_mode) {
    if (! pcg_random_allowed) {
      con("Error, trying to create a thing outside of game loop");
      backtrace_dump();
    }
  }

  if (is_tmp_thing()) {
    game->world.alloc_tmp_thing_id(this);
    pcg_random_allowed = false;
  } else {
    game->world.alloc_thing_id(this);
  }
  if (mid_at != point(-1, -1)) {
    level_enter();
    level_push();
  }

  if (tpp->is_loggable()) {
    dbg("Creating");
  }

  //
  // Add AI ability
  //
  if (tpp->is_monst() || tpp->is_player()) {
    clear_age_map();
    clear_seen_map();
    clear_interrupt_map();
    clear_dmap_can_see();
    clear_can_see_currently();
    clear_can_see_ever();
  }

  if (tpp->is_player()) {
    level->player = this;
    level->dmap_to_player_update();
  }

  if (tpp->gfx_animated_can_hflip()) {
    dir            = THING_DIR_LEFT;
    is_facing_left = true;
  } else {
    dir            = THING_DIR_NONE;
    is_facing_left = false;
  }

  is_hungry = tpp->is_hunger_insatiable();

  {
    TRACE_AND_INDENT();
    auto v = tpp->get_health_initial();
    if (unlikely(v)) {
      set_health(v);
      set_health_max(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stamina();
    if (unlikely(v)) {
      set_stamina(v);
      set_stamina_max(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->enchant_level();
    if (unlikely(v)) {
      set_enchant(v);
      set_enchant_max(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->enchant_max();
    if (unlikely(v)) {
      set_enchant_max(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_armor_class();
    if (unlikely(v)) {
      set_stat_armor_class(v);
      set_stats19(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->lifespan();
    if (unlikely(v)) {
      set_lifespan(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_dexterity();
    if (unlikely(v)) {
      set_stat_dexterity(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats02();
    if (unlikely(v)) {
      set_stats02(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats03();
    if (unlikely(v)) {
      set_stats03(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats04();
    if (unlikely(v)) {
      set_stats04(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats05();
    if (unlikely(v)) {
      set_stats05(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats06();
    if (unlikely(v)) {
      set_stats06(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats07();
    if (unlikely(v)) {
      set_stats07(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats08();
    if (unlikely(v)) {
      set_stats08(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats09();
    if (unlikely(v)) {
      set_stats09(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats10();
    if (unlikely(v)) {
      set_stats10(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats11();
    if (unlikely(v)) {
      set_stats11(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats12();
    if (unlikely(v)) {
      set_stats12(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_constitution();
    if (unlikely(v)) {
      set_stat_constitution(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_attack_bonus();
    if (unlikely(v)) {
      set_stat_attack_bonus(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_constitution();
    if (unlikely(v)) {
      set_stat_constitution(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats17();
    if (unlikely(v)) {
      set_stats17(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->distance_throw();
    if (unlikely(v)) {
      set_distance_throw(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_strength();
    if (unlikely(v)) {
      set_stat_strength(v);
    }
  }

  if (unlikely(tpp->is_ascend_dungeon())) {
    if (level->world_at.z > 1) {
      is_open = true;
    }
  }

  if (unlikely(tpp->charge_count())) {
    set_charge_count(tpp->charge_count());
  }

  auto tiles = &tpp->tiles;
  if (tpp->gfx_animated()) {
    auto tile = tile_first(tiles);
    if (tile) {
      tile_curr = tile->global_index;
    } else {
      tile_curr = 0;
    }
  } else {
    auto tile = tile_random(tiles);
    if (tile) {
      tile_curr = tile->global_index;
    } else {
      tile_curr = 0;
    }
  }

  //
  // Set position prior to attach
  //
  if (mid_at != point(-1, -1)) {
    set_interpolated_mid_at(make_fpoint(mid_at));
    update_interpolated_position();
  }

  if (gfx_bounce_always()) {
    bounce(0.2, 1.0, 500 + pcg_random_range(0, 50), 255);
  }

  init_lights();

  auto on_birth = on_birth_do();
  if (! std::empty(on_birth)) {
    auto t = split_tokens(on_birth, '.');
    if (t.size() == 2) {
      auto        mod   = t[ 0 ];
      auto        fn    = t[ 1 ];
      std::size_t found = fn.find("()");
      if (found != std::string::npos) {
        fn = fn.replace(found, 2, "");
      }
      py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
    } else {
      ERR("Bad on_birth call [%s] expected mod:function, got %d elems", on_birth.c_str(), (int) on_birth.size());
    }
  }

  if (is_monst()) {
    level->monst_count++;
  }

  is_the_grid = tp()->is_the_grid();

  //
  // Auto carry of weapons?
  //
  if (is_weapon_equiper()) {
    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_weapon_class_a(), mid_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_weapon_class_b(), mid_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_weapon_class_c(), mid_at);
      if (W) {
        carry(W);
      }
    }
  }

  if (is_bag_item_container()) {
    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_a(), mid_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_b(), mid_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_c(), mid_at);
      if (W) {
        carry(W);
      }
    }
  } else if (is_item_carrier()) {
    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_item_class_a(), mid_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_item_class_b(), mid_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_item_class_c(), mid_at);
      if (W) {
        carry(W);
      }
    }
  }

  on_born();

  if (is_tmp_thing()) {
    pcg_random_allowed = true;
  }

  //
  // We should not create things until we have fully loaded.
  //
  if (g_loading) {
    err("Trying to create a thing during loading.");
  }
}

void Thing::reinit(void)
{
  TRACE_AND_INDENT();
  verify(MTYPE_THING, this);
  const auto tpp = tp_or_update();
  if (unlikely(! tpp)) {
    ERR("No tp found for reinitialized thing ID %x tp_id %d", id.id, tp_id);
    return;
  }

  game->world.realloc_thing_id(this);

  //
  // Probably safest to reset this else things might expire on load
  //
  ts_next_frame = 0;

  if (unlikely(is_player())) {
    if (level->player && (level->player != this)) {
      DIE("Player exists in multiple places on map, %d,%d and %d,%d", level->player->mid_at.x,
          level->player->mid_at.y, mid_at.x, mid_at.y);
      return;
    }
    level->player = this;
  }

  point new_at((int) mid_at.x, (int) mid_at.y);
  if ((new_at.x >= MAP_WIDTH) || (new_at.y >= MAP_HEIGHT)) {
    DIE("New thing is oob at %d, %d", new_at.x, new_at.y);
    return;
  }

  if (is_loggable()) {
    dbg("Recreated");
  }

  //
  // Upon a load it was attached at save time but not now
  //
  if (is_attached) {
    level_enter();
    level_push();
  }

  if (is_cursor()) {
    level->cursor = this;
  }
}
