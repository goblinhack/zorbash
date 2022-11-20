//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Thing::open_door(Thingp door)
{
  if (! is_monst() && ! is_player()) {
    dbg("Cannot open %s", door->to_short_string().c_str());
    return false;
  }

  if (is_on_fire()) {
    if (! door->is_on_fire()) {
      if (is_player()) {
        msg("The door is ablaze!");
      }
      door->on_fire_set("opened flaming door");
    }
  }

  if (! door->is_door()) {
    dbg("Cannot open %s", door->to_short_string().c_str());
    return false;
  }

  if (door->is_open) {
    dbg("Cannot open %s: already open", door->to_short_string().c_str());
    return false;
  }

  if (door->is_dead) {
    dbg("Cannot open %s: is dead", door->to_short_string().c_str());
    return false;
  }

  dbg("Open door: %s", door->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // Check if we need a key or if the door is open already.
  //
  if (door->is_key_in_lock) {
    //
    // If the key is stuck in the door, allow it to be opened again.
    //
    dbg("Door was unlocked: %s", door->to_short_string().c_str());
    TRACE_AND_INDENT();

    if (is_player()) {
      msg("The door was unlocked and creaks open.");
    }
  } else {
    //
    // We need a key to open it.
    //
    dbg("Door needs a key: %s", door->to_short_string().c_str());
    TRACE_AND_INDENT();

    if (keys()) {
      //
      // Yes, have a key
      //
      dbg("Yes have a key: %s", door->to_short_string().c_str());
      TRACE_AND_INDENT();

      keys_decr();
      door->is_key_in_lock = true;

      if (is_player()) {
        msg("You unlock the door.");
      }
    } else {
      //
      // No keys ?
      //
      dbg("No keys to open door: %s", door->to_short_string().c_str());
      TRACE_AND_INDENT();

      if (is_player()) {
        static uint32_t last_told_when;
        if (! last_told_when || (game->tick_current >= last_told_when + 10)) {
          msg("You need a key.");
        }
        last_told_when = game->tick_current;
      }
      return false;
    }
  }

  if (door->is_key_in_lock) {
    dbg("Opened door: %s", door->to_short_string().c_str());
    TRACE_AND_INDENT();

    door->level_pop();
    door->is_open = true;
    door->level_push();

    door->on_open();
    level->noisemap_in_incr(door->curr_at.x, door->curr_at.y, door->noise_on_open());

    update_light();
    level->request_dmap_to_player_update = true;
    return true;
  }

  return false;
}

bool Thing::close_door(Thingp door)
{
  if (is_on_fire()) {
    if (! door->is_on_fire()) {
      if (is_player()) {
        msg("The closed door is ablaze!");
      }
      door->on_fire_set("closed flaming door");
    }
  }

  if (! door->is_door()) {
    return false;
  }

  if (! door->is_open) {
    return false;
  }

  if (door->is_dead) {
    return false;
  }

  dbg("Close door");
  TRACE_AND_INDENT();

  IF_DEBUG1 { door->log("Close"); }
  door->level_pop();
  door->is_open = false;
  door->level_push();

  //
  // Slamming the door on a thing for crush damage
  //
  FOR_ALL_THINGS_THAT_INTERACT(level, t, door->curr_at.x, door->curr_at.y)
  {
    if (t == this) {
      continue;
    }

    if (! t->is_monst() && ! t->is_player()) {
      continue;
    }

    if (t->thing_size() > thing_size()) {
      msg("%s blocks the door from closing.", t->text_The().c_str());
    }

    if (is_player()) {
      if (t->is_ethereal()) {
        msg("The closing door passes through %s.", t->text_the().c_str());
      } else {
        msg("You slam the door on %s.", t->text_the().c_str());
      }
    }

    t->is_attacked_with_dmg_crush(door, this, door->dmg_crush());
  }
  FOR_ALL_THINGS_END()

  if (door->is_key_in_lock) {
    //
    // If we're lucky, give the key back.
    //
    if (d20roll_under(stat_luck_total() - 5)) {
      door->is_key_in_lock = false;
      keys_incr(1);

      if (is_player()) {
        msg("The door closes. You manage to remove the key from the rusty lock.");
      }
    } else {
      //
      // No, the key is stuck.
      //
      if (is_player()) {
        msg("The door closes with the key firmly stuck in the lock.");
      }
    }
  } else {
    msg("The door closes.");
  }

  level->noisemap_in_incr(door->curr_at.x, door->curr_at.y, door->noise_on_open());
  update_light();
  level->request_dmap_to_player_update = true;
  return true;
}
