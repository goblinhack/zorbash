//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

Thingp Level::thing_new(Tpp tp, const point at, Thingp owner)
{
  if (unlikely(! tp)) {
    err("No tp provided for thing creation");
    return nullptr;
  }
  return thing_new(tp->name(), at, owner);
}

Thingp Level::thing_new(const std::string &tp_name, Thingp owner)
{
  return thing_new(tp_name, owner->curr_at, owner);
}

Thingp Level::thing_new(const std::string &name, const point at, Thingp owner)
{
  auto t = new class Thing_();
  t->init(this, name, at, owner);
  return t;
}

Thing::Thing_(void) { newptr(MTYPE_THING, this, "thing"); }

void Thing::on_born(void)
{
  TRACE_NO_INDENT();

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

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (int) curr_at.x,
        (int) curr_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_born call [%s] expected mod:function, got %d elems", on_born.c_str(), (int) on_born.size());
  }
}

void Thing::init(Levelp level, const std::string &name, const point born, Thingp owner)
{
  verify(MTYPE_THING, this);

  this->level = level;
  curr_at     = born;
  last_at     = born;

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

  /*
   * Cache this flag so that polymorphing works
   */
  is_the_player = tp()->is_player();

  //
  // Make sure we have the ability to carry items.
  //
  if (is_player() || is_monst() || is_item() || is_cursor()) {
    new_infop();

    //
    // This is useful for treasure maps to tell if they work on this level
    //
    born_set(point3d(born.x, born.y, level->world_at.z));
  }

  if (is_player() || is_monst() || is_item()) {
    new_itemsp();
  }

  if (is_player() || is_monst() || is_cursor()) {
    new_aip();
  }

  //
  // Init the z depth
  //
  z_depth = tp()->z_depth;

  //
  // Change state prior to choosing the first tile so we get the
  // sleep anim immediately.
  //
  if (is_asleep_initially()) {
    change_state(MONST_STATE_SLEEPING, "asleep initially");
  }

  //
  // Start off up to data with the player
  //
  if (is_tickable()) {
    //
    // Newly spawned things, don't make them do something immediately
    // This can lead to recursion
    //
    tick_last_location_check_set(game->tick_current);
    tick_last_did_something_set(game->tick_current);
  }

  //
  // Must do this after TP assignment or logging will fail
  //
  if (game->robot_mode) {
    if (! pcg_random_allowed) {
      err("Error, trying to create a thing outside of game loop");
      backtrace_dump();
      DIE("Error, trying to create a thing outside of game loop");
    }
  }

  if (is_tmp_thing()) {
    game->world.alloc_tmp_thing_id(this);
    pcg_random_allowed = false;
  } else {
    game->world.alloc_thing_id(this);
  }
  if (curr_at != point(-1, -1)) {
    level_enter();
    level_push();
  }

  if (tpp->is_loggable()) {
    if (owner) {
      dbg("Creating with owner %s", owner->to_string().c_str());
    } else {
      dbg("Creating");
    }
  }

  //
  // Important to set the owner before the on_born call as we use that for lasers.
  //
  if (owner) {
    owner_set(owner);
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

  if (owner) {
    dir            = owner->dir;
    is_facing_left = owner->is_facing_left;
  }

  update();

  if (unlikely(tpp->is_ascend_dungeon())) {
    if (level->world_at.z > 1) {
      is_open = true;
    }
  }

  if (unlikely(tpp->charge_count())) {
    charge_count_set(tpp->charge_count());
  }

  //
  // Set position prior to attach
  //
  if (curr_at != point(-1, -1)) {
    interpolated_at_set(make_fpoint(curr_at));
    update_interpolated_position();
  }

  if (gfx_bounce_always()) {
    bounce(0.3, 1.0, 400 + pcg_random_range(0, 100), 255);
  }

  init_lights();

  if (is_monst()) {
    level->monst_count++;
  }

  is_the_grid = tp()->is_the_grid();

  if (is_tmp_thing()) {
    pcg_random_allowed = true;
  }

  on_born();

  //
  // In case we carry something here, check for equipping
  //
  update();

  //
  // Mainly for explosions
  //
  level->noisemap_in_incr(curr_at.x, curr_at.y, noise_on_born());

  //
  // Spawn zorblin packs
  //
  static bool spawning_group;
  if (! spawning_group) {
    spawning_group = true;
    if (spawn_group_size()) {
      spawn_randomly_in_radius_range(name, spawn_group_size(), 1, spawn_group_radius());
    }
    spawning_group = false;
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
  TRACE_NO_INDENT();

  verify(MTYPE_THING, this);
  const auto tpp = tp_or_update();
  if (unlikely(! tpp)) {
    ERR("No tp found for reinitialized thing ID %X tp_id %d", id.id, tp_id);
    return;
  }

  game->world.realloc_thing_id(this);

  //
  // Probably safest to reset this else things might expire on load
  //
  ts_next_frame = 0;

  if (unlikely(is_player())) {
    if (level->player && (level->player != this)) {
      DIE("Player exists in multiple places on map, %d,%d and %d,%d", level->player->curr_at.x,
          level->player->curr_at.y, curr_at.x, curr_at.y);
      return;
      game->level = level;
    }
    level->player = this;

    //
    // game->level is set in game_load via current_level
    //
    dbg("Player placed on new level");
  }

  point new_at((int) curr_at.x, (int) curr_at.y);
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
