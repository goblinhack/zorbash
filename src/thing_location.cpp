//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

//
// This is called if we move onto or fall onto a new location
//
// It is also called at the end of all moves for the current tick
// to handle things that do not move but something has happened to
// like they caught on fire
//
void Thing::location_check_forced(void)
{
  TRACE_AND_INDENT();

  //
  // Prevent interactions that might generate things like smoke.
  //
  if (level->is_being_destroyed) {
    dbg("Location check, skip, level is being destroyed");
    return;
  }

  if (is_being_destroyed) {
    dbg("Location check, skip, being destroyed");
    return;
  }

  if (is_hidden) {
    dbg("Location check, skip, is hidden");
    return;
  }

  //
  // Put chasm checks first as you can still fall when dead!
  //
  if (is_changing_level || is_the_grid || is_hidden || is_falling || is_waiting_to_ascend_dungeon ||
      is_waiting_to_descend_sewer || is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer ||
      is_waiting_to_leave_level_has_completed_fall || get_immediate_owner() || is_jumping) {
    //
    // Skip interactions
    //
    dbg("Location check, skip");
    return;
  }

  chasm_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  corrode_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  barrel_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  secret_door_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  brazier_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  water_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  lava_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  acid_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  fire_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }
  grass_tick();
  if (is_dead) {
    dbg("Location check, skip, dead");
    return;
  }

  if (! is_able_to_change_levels()) {
    return;
  }

  //
  // If we have a move path then we are perhaps trying to do descend into the
  // level below.
  //
  if (maybe_aip() && get_aip()->move_path.size() <= 1) {
    if (descend_dungeon_tick()) {
      dbg("Location check, descending dungeon");
      return;
    }
    if (ascend_dungeon_tick()) {
      dbg("Location check, ascending dungeon");
      return;
    }
    if (descend_sewer_tick()) {
      dbg("Location check, descending sewer");
      return;
    }
    if (ascend_sewer_tick()) {
      dbg("Location check, ascending sewer");
      return;
    }
  }
}

void Thing::location_check(void)
{
  TRACE_AND_INDENT();

  if (maybe_infop()) {
    if (get_tick_last_location_check() == game->tick_current) {
      return;
    }

    dbg("Do location check. Last %d, game tick %d", get_tick_last_location_check(), game->tick_current);
    set_tick_last_location_check(game->tick_current);
  }

  location_check_forced();
}

//
// Check all things at this location. In this case we check it
// already performed, so we don't for example do a lava check
// again initiated by being set on fire by lava.
//
void Thing::location_check_all_things_at(void)
{
  TRACE_AND_INDENT();
  dbg("Do location checks");

  //
  // Needs to be for all things to stuff that does nothing like bones can fall
  // into a chasm
  //
  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_hidden) {
      continue;
    }
    TRACE_AND_INDENT();
    IF_DEBUG2 { t->log("Do location check"); }
    t->location_check();
  }
  FOR_ALL_THINGS_END()
}

//
// Check all things at this location
//
void Thing::location_check_forced_all_things_at(void)
{
  TRACE_AND_INDENT();
  dbg("Do location checks");

  //
  // Needs to be for all things to stuff that does nothing like bones can fall
  // into a chasm
  //
  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_hidden) {
      continue;
    }
    TRACE_AND_INDENT();
    IF_DEBUG2 { t->log("Do location check"); }
    t->location_check_forced();
  }
  FOR_ALL_THINGS_END()
}
