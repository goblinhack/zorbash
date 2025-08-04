//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
// REMOVED #include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"

Thingp Level::thing_new(Tpp tp, const point at, Thingp owner)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp)) {
    err("No tp provided for thing creation");
    return nullptr;
  }

  return thing_new(tp->name(), at, owner);
}

Thingp Level::thing_new(const std::string &tp_name, Thingp owner)
{
  TRACE_NO_INDENT();
  return thing_new(tp_name, owner->curr_at, owner);
}

Thingp Level::thing_new(const std::string &name, const point at, Thingp owner)
{
  //
  // Find a thing appropriate for the level and position (if it is something
  // like "random_monst_class_A") Else just find the named thing.
  //
  TRACE_NO_INDENT();
  auto tp_cands = tp_find_wildcard(this, at, name);
  if (! tp_cands.size()) {
    DIE("Could not find thing '%s'", name.c_str());
    return nullptr;
  }

  if (! tp_cands.size()) {
    err("Cannot find any %s to spawn", name.c_str());
    return nullptr;
  }

  auto tp = pcg_one_of(tp_cands);
  if (! tp) {
    DIE("Could not create thing '%s'", name.c_str());
    return nullptr;
  }

  //
  // Ensure things like chasms don't pile up on the same tile.
  //
  if (tp->is_one_per_tile()) {
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_AT_DEPTH(this, o, at.x, at.y, tp->z_depth)
    {
      if (o->tp() == tp) {
        dbg("Do not create %s as already exist at %s", name.c_str(), at.to_string().c_str());
        return nullptr;
      }
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }

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

void Thing::init(Levelp level, const std::string &name_in, const point born, Thingp owner)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, this);

  this->level = level;
  curr_at     = born;
  last_at     = born;

  //
  // Try to find the thing by name
  //
  if (name_in == "") {
    DIE("Thing template cannot be created: No name given");
  }

  auto tp_cands = tp_find_wildcard(name_in);
  if (! tp_cands.size()) {
    err("Cannot find any %s to spawn", name_in.c_str());
    return;
  }

  auto tpp = pcg_one_of(tp_cands);
  if (unlikely(! tpp)) {
    ERR("Thing template [%s] not found", name_in.c_str());
    return;
  }

  //
  // If the wildcard was "random_xxx" then use the real name from now on
  //
  auto name = tpp->name();

  //
  // Templates are shared for all things
  //
  tp_id = tpp->id;
  tp_or_update();

  ts_next_frame = 0;

  //
  // Cached as used often
  //
  gfx_pixelart_animated = tp()->gfx_pixelart_animated();
  gfx_ascii_animated    = tp()->gfx_ascii_animated();

  //
  // Cache this flag so that polymorphing works
  //
  is_the_player = tp()->is_player();

  //
  // Make sure we have the ability to carry items.
  //
  TRACE_NO_INDENT();
  if (gfx_pixelart_attack_anim() || is_buff() || is_debuff() || is_msg() || is_player() || is_monst() || is_item()
      || is_splatter() || is_cursor() || is_laser() || is_projectile() || is_weapon() || is_fire()
      || is_magical_effect() || is_tentacle()) {
    new_infop();

    //
    // This is useful for treasure maps to tell if they work on this level
    //
    born_set(point3d(born.x, born.y, level->world_at.z));
  }

  TRACE_NO_INDENT();
  if (is_player() || is_monst() || is_item() || is_turret()) {
    new_itemsp();
  }

  TRACE_NO_INDENT();
  if (is_totem() || is_player() || is_trap() || is_monst() || is_cursor()) {
    new_aip();
  }

  //
  // Init the z depth
  //
  z_depth = tp()->z_depth;

  if (is_tmp_thing()) {
    game->world.alloc_tmp_thing_id(this);
  } else {
    game->world.alloc_thing_id(this);
  }

  if (curr_at != point(-1, -1)) {
    level_enter();
    level_push();
  }

  if (tpp->is_loggable()) {
    if (owner) {
      dbg("Creating with owner %s", owner->to_short_string().c_str());
    } else {
      dbg("Creating");
    }
  }

  //
  // Important to set the owner before the on_born call as we use that for
  // lasers.
  //
  if (owner) {
    owner_set(owner);
  }

  //
  // Some things are symetrical and can flip.
  //
  if (gfx_pixelart_animated_can_hflip()) {
    dir            = THING_DIR_LEFT;
    is_facing_left = true;
  } else {
    dir            = THING_DIR_NONE;
    is_facing_left = false;
  }

  //
  // Make sure you face teh ame was as your owner
  //
  if (owner) {
    dir            = owner->dir;
    is_facing_left = owner->is_facing_left;
  }

  //
  // Change state prior to choosing the first tile so we get the
  // sleep anim immediately.
  //
  if (is_asleep_initially()) {
    change_state(MONST_STATE_SLEEPING, "asleep initially");
  }

  //
  // Make sure and call this after any state changes so we get the
  // sleeping tile assigned if needed.
  //
  update();

  //
  // Set the initial nutrition.
  //
  nutrition_init();

  //
  // Some things start life open
  //
  if (unlikely(is_ascend_dungeon())) {
    if (level->dungeon_walk_order_level_no > 1) {
      is_open = true;
    }
  }

  //
  // Set position prior to attach
  //
  if (curr_at != point(-1, -1)) {
    interpolated_at_set(make_fpoint(curr_at));
    update_interpolated_position();
  }

  //
  // The grid is the perma background matrix like substrate that is the ether of
  // this universe!
  //
  is_the_grid_ = tp()->is_the_grid();
  if (is_the_grid_) {
    return;
  }

  //
  // Create the large player dmap
  //
  if (is_player()) {
    level->player = this;
    level->dmap_to_player_update();
  }

  //
  // Add AI ability
  //
  if (is_monst() || is_player()) {
    clear_age_map();
    clear_dmap_can_see_old();
    clear_interrupt_map();
    clear_dmap_can_see();
    clear_can_see_currently();
    clear_can_see_ever();
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
    tick_born_set(game->tick_current);

    //
    // Need to set this, or newly born things will immediately do something.
    //
    tick_last_set(game->tick_current);
  }

  //
  // e.g. keys
  //
  if (gfx_pixelart_bounce_always()) {
    bounce(0.3, 1.0, 400 + pcg_random_range(0, 100), 255);
  }

  //
  // Init light sources like torches
  //
  init_lights();

  //
  // Initialize random color spread.
  //
  init_hue();

  //
  // e.g. staff charges
  //
  if (unlikely(tpp->charge_count())) {
    charge_count_set(tpp->charge_count());
  }

  //
  // Do on born actions.
  //
  on_born();

  //
  // In case we carry something here, check for equipping
  //
  if (is_player() || is_monst()) {
    update();
  }

  //
  // Mainly for explosions
  //
  level->sound_sources_incr(curr_at.x, curr_at.y, noise_on_born());

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
  // Items have gold set to -1 until we determine how many coins they have.
  //
  if (is_player() || is_monst()) {
    gold_value();
  }

  //
  // Initially visible?
  //
  if (get_no_check(level->can_see_currently.can_see, curr_at.x, curr_at.y)) {
    is_visible_to_player = true;
  }

  //
  // Copy the owner offscreen status.
  //
  if (is_player()) {
    is_visible_to_player = true;
  }

  if (owner) {
    is_visible_to_player = owner->is_visible_to_player;
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
    //
    // Update the minimap for the new cursor location.
    //
    level->is_map_mini_valid = false;

    level->cursor = this;
  }
}
