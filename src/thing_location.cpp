//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
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
  TRACE_NO_INDENT();

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
      is_waiting_to_leave_level_has_completed_fall || is_jumping) {
    //
    // Skip interactions
    //
    dbg("Location check, skip");
    return;
  }

  //
  // Cool down / heat up
  //
  temperature_tick();
  if (is_dead) {
    return;
  }

  //
  // Check for calling before the dead check, so dead dogmen can fall.
  //
  chasm_tick();
  if (is_dead) {
    return;
  }

  //
  // Embedded in solid rock?
  //
  solid_rock_tick();
  if (is_dead) {
    return;
  }

  corrode_tick();
  if (is_dead) {
    return;
  }

  barrel_tick();
  if (is_dead) {
    return;
  }

  icecube_tick();
  if (is_dead) {
    return;
  }

  secret_door_tick();
  if (is_dead) {
    return;
  }

  brazier_tick();
  if (is_dead) {
    return;
  }

  water_tick();
  if (is_dead) {
    return;
  }

  lava_tick();
  if (is_dead) {
    return;
  }

  acid_tick();
  if (is_dead) {
    return;
  }

  plant_tick();
  if (is_dead) {
    return;
  }

  grass_tick();
  if (is_dead) {
    return;
  }

  gas_poison_tick();
  if (is_dead) {
    return;
  }

  if (! is_able_to_change_levels()) {
    return;
  }

  auto descend_check = false;
  auto ascend_check  = false;

  //
  // If we have a move path then we are perhaps trying to descend into the
  // level below.
  //
  if (level->is_ascend_dungeon(curr_at.x, curr_at.y) || level->is_ascend_sewer(curr_at.x, curr_at.y)) {
    if (is_player()) {
      if (game->robot_mode) {
        auto ai = maybe_aip();
        dbg("Location check, over ascend sewer or dungeon (move path len %d)", (int) ai->move_path.size());
        if (! ai->move_path.size()) {
          dbg("Location check, set ascend check (1)");
          ascend_check = true;
        }
      } else if (game->request_ascend || (curr_at == game->cursor_move_end)) {
        dbg("Location check, over ascend sewer or dungeon (move end @%d,%d)", game->cursor_move_end.x,
            game->cursor_move_end.y);
        dbg("Location check, set ascend check (2)");
        ascend_check = true;
      }
    } else if (pcg_random_range(0, 100) < 10) {
      dbg("Location check, set ascend check (3)");
      ascend_check = true;
    }
  }

  if (level->is_descend_dungeon(curr_at.x, curr_at.y) || level->is_descend_sewer(curr_at.x, curr_at.y)) {
    if (is_player()) {
      if (game->robot_mode) {
        auto ai = maybe_aip();
        dbg("Location check, over descend sewer or dungeon (move path len %d)", (int) ai->move_path.size());
        if (! ai->move_path.size()) {
          dbg("Location check, set descend check (1)");
          descend_check = true;
        }
      } else if (game->request_descend || (curr_at == game->cursor_move_end)) {
        dbg("Location check, over descend sewer or dungeon (cursor move end @%d,%d)", game->cursor_move_end.x,
            game->cursor_move_end.y);
        dbg("Location check, set descend check (2)");
        descend_check = true;
      }
    } else if (pcg_random_range(0, 100) < 10) {
      dbg("Location check, set descend check (3)");
      descend_check = true;
    }
  }

  if (ascend_check) {
    dbg("Location check, ascend check");
    if (ascend_dungeon_tick()) {
      dbg("Location check, ascending dungeon");
    } else if (ascend_sewer_tick()) {
      dbg("Location check, ascending sewer");
    }
  }

  if (descend_check) {
    dbg("Location check, descend check");
    if (descend_dungeon_tick()) {
      dbg("Location check, descending dungeon");
    } else if (descend_sewer_tick()) {
      dbg("Location check, descending sewer");
    }
  }

  if (is_player()) {
    game->request_ascend  = false;
    game->request_descend = false;
  }
}

void Thing::location_check(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) {
    if (tick_last_location_check() == game->tick_current) {
      return;
    }

    dbg("Do location check. Last %d, game tick %d", tick_last_location_check(), game->tick_current);
    tick_last_location_check_set(game->tick_current);
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
  dbg("Do location checks");
  TRACE_AND_INDENT();

  //
  // Needs to be for all things to stuff that does nothing like bones can fall
  // into a chasm
  //
  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_hidden) {
      continue;
    }
    IF_DEBUG2 { t->log("Do location check"); }
    TRACE_AND_INDENT();
    t->location_check();
  }
  FOR_ALL_THINGS_END()
}

//
// Check all things at this location
//
void Thing::location_check_forced_all_things_at(void)
{
  dbg("Do location checks");
  TRACE_AND_INDENT();

  //
  // Needs to be for all things to stuff that does nothing like bones can fall
  // into a chasm
  //
  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_hidden) {
      continue;
    }
    IF_DEBUG2 { t->log("Do location check"); }
    TRACE_AND_INDENT();
    t->location_check_forced();
  }
  FOR_ALL_THINGS_END()
}
