//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

//
// This is called if we move onto or fall onto a new location
//
// It is also called at the end of all moves for the current tick
// to handle things that do not move but something has happened to
// like they caught on fire
//
void Thing::location_check(Thingp filter_to)
{
  TRACE_NO_INDENT();

  //
  // Don't do location checks for the cursor, that's silly
  //
  if (is_internal()) {
    return;
  }

  //
  // Prevent interactions that might generate things like smoke.
  //
  if (level->is_being_destroyed) {
    dbg2("Location check, skip, level is being destroyed");
    return;
  }

  if (is_being_destroyed) {
    dbg2("Location check, skip, being destroyed");
    return;
  }

  if (is_hidden) {
    dbg2("Location check, skip, is hidden");
    return;
  }

  //
  // Put chasm checks first as you can still fall when dead!
  //
  if (is_changing_level || is_the_grid() || is_hidden || is_falling || is_waiting_to_ascend_dungeon
      || is_waiting_to_descend_sewer || is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer
      || is_waiting_to_leave_level_has_completed_fall || is_jumping) {
    //
    // Skip interactions
    //
    dbg2("Location check, skip");
    return;
  }

  TRACE_NO_INDENT();

  //
  // Allow fall through to fall check, so burnt things can fall.
  //

  //
  // Check for calling before the dead check, so dead dogmen can fall.
  //
  if (! filter_to || filter_to->is_chasm()) {
    chasm_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_trap()) {
    trap_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_portal()) {
    portal_tick();
    if (is_dead) {
      return;
    }
  }

  //
  // Embedded in solid rock?
  //
  if (! filter_to || (filter_to->is_wall() || filter_to->is_rock())) {
    solid_rock_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_acid()) {
    corrode_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_barrel()) {
    barrel_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_block_of_ice()) {
    block_of_ice_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_spell_of_holding_barrier()) {
    spell_of_holding_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_spell_of_sanctuary_barrier()) {
    spell_of_sanctuary_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_secret_door()) {
    secret_door_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_brazier()) {
    brazier_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_water()) {
    water_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_acid()) {
    acid_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_ooze()) {
    ooze_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_plant()) {
    plant_tick();
    if (is_dead) {
      return;
    }
  }

  if (! filter_to || filter_to->is_grass_dry()) {
    grass_tick();
    if (is_dead) {
      return;
    }
  }

  //
  // If we drop an item, that triggers a location check. We don't therefore want to
  // check for unrelated things that might spark a fire.
  //
  if (! filter_to) {
    gas_explosive_tick();
    gas_poison_tick();
    gas_paralysis_tick();
    gas_confused_tick();
    gas_healing_tick();
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
        dbg2("Location check, over ascend sewer or dungeon (move path len %d)", (int) ai->move_path.size());
        if (! ai->move_path.size()) {
          dbg2("Location check, set ascend check (1)");
          ascend_check = true;
        }
      } else if (game->request_player_to_ascend_level || (curr_at == game->cursor_move_end)) {
        dbg2("Location check, over ascend sewer or dungeon (move end at %d,%d)", game->cursor_move_end.x,
             game->cursor_move_end.y);
        dbg2("Location check, set ascend check (2)");
        ascend_check = true;
      }
    } else if (pcg_random_range(0, 100) < 10) {
      dbg2("Location check, set ascend check (3)");
      ascend_check = true;
    }
  }

  if (level->is_descend_dungeon(curr_at.x, curr_at.y) || level->is_descend_sewer(curr_at.x, curr_at.y)) {
    if (is_player()) {
      if (game->robot_mode) {
        auto ai = maybe_aip();
        dbg2("Location check, over descend sewer or dungeon (move path len %d)", (int) ai->move_path.size());
        if (! ai->move_path.size()) {
          dbg2("Location check, set descend check (1)");
          descend_check = true;
        }
      } else if (game->request_player_to_descend_level || (curr_at == game->cursor_move_end)) {
        dbg2("Location check, over descend sewer or dungeon (cursor move end at %d,%d)", game->cursor_move_end.x,
             game->cursor_move_end.y);
        dbg2("Location check, set descend check (2)");
        descend_check = true;
      }
    } else if (pcg_random_range(0, 100) < 10) {
      dbg2("Location check, set descend check (3)");
      descend_check = true;
    }
  }

  if (ascend_check) {
    dbg2("Location check, ascend check");
    if (ascend_dungeon_tick()) {
      dbg2("Location check, ascending dungeon");
    } else if (ascend_sewer_tick()) {
      dbg2("Location check, ascending sewer");
    }
  }

  if (descend_check) {
    dbg2("Location check, descend check");
    if (descend_dungeon_tick()) {
      dbg2("Location check, descending dungeon");
    } else if (descend_sewer_tick()) {
      dbg2("Location check, descending sewer");
    }
  }

  if (is_player()) {
    game->request_player_to_ascend_level  = false;
    game->request_player_to_descend_level = false;
  }

  //
  // Not used anymore, remove?
  //
  tick_last_location_check_set(game->tick_current);
}

//
// If a new thing is spawned, like fire, then check against this location.
//
// In addition, walk all other things and location check for them, but filtered to this new thing, fire.
//
void Thing::location_check_me(void)
{
  TRACE_NO_INDENT();

  //
  // Don't do location checks for the cursor, that's silly
  //
  if (is_internal()) {
    return;
  }

  //
  // If we're about to check as part of a tick, do it then.
  //
  if (! game->tick_requested.empty()) {
    return;
  }

  location_check();

  //
  // Check but filter only to this thing
  //
  TRACE_NO_INDENT();
  FOR_ALL_NON_INTERNAL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t == this) {
      continue;
    }

    t->location_check(this);
  }
  FOR_ALL_THINGS_END()
}
