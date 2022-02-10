//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::open_door(Thingp it)
{
  if (! is_monst() && ! is_player()) {
    return false;
  }

  if (is_on_fire()) {
    if (! it->is_on_fire()) {
      if (is_player()) {
        msg("The door is ablaze!");
      }
      it->set_on_fire("opened flaming door");
    }
  }

  if (! it->is_door()) {
    return false;
  }

  if (it->is_open) {
    return false;
  }

  if (it->is_dead) {
    return false;
  }

  dbg("Open door");
  TRACE_AND_INDENT();

  if (get_keys()) {
    decr_keys();
    IF_DEBUG1 { it->log("Open"); }
    it->level_pop();
    it->is_open = true;
    it->level_push();

    if (is_player()) {
      msg("The door creaks open.");
    }

    it->on_open();
    level->incr_noisemap_in(it->curr_at.x, it->curr_at.y, it->noise_on_open());

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

bool Thing::close_door(Thingp it)
{
  if (is_on_fire()) {
    if (! it->is_on_fire()) {
      if (is_player()) {
        msg("The door is ablaze!");
      }
      it->set_on_fire("closed flaming door");
    }
  }

  if (! it->is_door()) {
    return false;
  }

  if (! it->is_open) {
    return false;
  }

  if (it->is_dead) {
    return false;
  }

  dbg("Close door");
  TRACE_AND_INDENT();

  IF_DEBUG1 { it->log("Close"); }
  it->level_pop();
  it->is_open = false;
  it->level_push();

  //
  // Slamming the door on a thing for crush damage
  //
  FOR_ALL_THINGS_THAT_INTERACT(level, t, it->curr_at.x, it->curr_at.y)
  {
    if (t == this) {
      continue;
    }

    if (t->is_monst() || t->is_player()) {
      continue;
    }

    is_attacked_with_damage_crush(it, it->get_damage_crush());
  }
  FOR_ALL_THINGS_END()

  //
  // Give a key back
  //
  incr_keys(1);

  if (is_player()) {
    msg("The door slams shut.");
  }

  level->incr_noisemap_in(it->curr_at.x, it->curr_at.y, it->noise_on_open());

  update_light();
  level->request_dmap_to_player_update = true;
  return true;
}
