//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
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

  if (keys()) {
    keys_decr();
    IF_DEBUG1 { door->log("Open"); }
    door->level_pop();
    door->is_open = true;
    door->level_push();

    if (is_player()) {
      msg("The door creaks open.");
    }

    door->on_open();
    level->noisemap_in_incr(door->curr_at.x, door->curr_at.y, door->noise_on_open());

    update_light();
    level->request_dmap_to_player_update = true;
    return true;
  }

  if (is_player()) {
    static uint32_t last_told_when;
    if (! last_told_when || (game->tick_current >= last_told_when + 10)) {
      msg("You need a key.");
    }
    last_told_when = game->tick_current;
  }

  return false;
}

bool Thing::close_door(Thingp door)
{
  if (is_on_fire()) {
    if (! door->is_on_fire()) {
      if (is_player()) {
        msg("The door is ablaze!");
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

    t->log("Is in the way of a door being closed");
    TRACE_AND_INDENT();
    t->is_attacked_with_damage_crush(door, door, door->damage_crush());
  }
  FOR_ALL_THINGS_END()

  //
  // Give a key back
  //
  keys_incr(1);

  if (is_player()) {
    msg("The door slams shut.");
  }

  level->noisemap_in_incr(door->curr_at.x, door->curr_at.y, door->noise_on_open());

  update_light();
  level->request_dmap_to_player_update = true;
  return true;
}
