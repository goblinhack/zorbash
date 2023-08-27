//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

//
// Shielded from attack checks
//
bool Thing::is_shielded_from_attack_by(Thingp hitter)
{
  if (hitter->curr_at == curr_at) {
    //
    // Same tile attack?
    //
    if (hitter->is_missile()) {
      //
      // Make an exception for missile attacks as they originate on another tile.
      //
    } else {
      //
      // If the hitter and attacker are at the same tile, then there is no protectio
      //
      return false;
    }
  }

  //
  // If you are the shielded thing, then allow it to be attacked first.
  //
  if (is_spell_of_holding_barrier()) {
    return false;
  }

  if (is_block_of_ice()) {
    return false;
  }

  if (is_barrel()) {
    return false;
  }

  if (is_engulfer()) {
    return false;
  }

  //
  // If you are inside the spell barrier then afford protection.
  //
  if (level->is_spell_of_holding_barrier(curr_at)) {
    dbg("Attack failed, victim is shielded by magic");
    return true;
  }

  if (level->is_block_of_ice(curr_at)) {
    dbg("Attack failed, victim is shielded by ice");
    return true;
  }

  if (level->is_barrel(curr_at)) {
    dbg("Attack failed, victim is in a barrel");
    return true;
  }

  if (level->is_engulfer(curr_at)) {
    dbg("Attack failed, victim is in a engulfer");
    return true;
  }

  return false;
}
