//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_ATTACK_OPTIONS_HPP_
#define _MY_THING_ATTACK_OPTIONS_HPP_

#include "my_fwd.hpp"
#include "my_point.hpp"
#include <string>

typedef class ThingAttackOptions_
{
public:
  //
  // If given a real hitter, prefer that; for example a player slamming a door on a monster.
  // real_hitter would be the player. hitter would be the door.
  //
  Thingp real_hitter {};
  //
  // Return values
  //
  bool victim_attacked {};
  bool victim_overlaps {};
  //
  // Allowed to hit solid rock. Normally disabled to avoid weapon damage.
  // Enabled if you click on a rock.
  //
  bool allow_hitting_walls {};
  //
  // Monst is using its natural attack.
  //
  bool nat_att {};
  //
  // Prefer natural attack.
  //
  bool prefer_nat_att {};
  //
  // Can also shove.
  //
  bool shove_allowed {};
  //
  // Critical hit.
  //
  bool crit {};
  //
  // Used in moving to pass on intent to attack.
  //
  bool attack_allowed {};
  //
  // If attack_at is not set, we should look around for a target.
  //
  bool attack_at_set {};
  //
  // Attack types;
  //
  bool attack_water {};
  bool attack_acid {};
  bool attack_cold {};
  bool attack_crush {};
  bool attack_digest {};
  bool attack_draining {};
  bool attack_energy {};
  bool attack_negation {};
  bool attack_fire {};
  bool attack_drown {};
  bool attack_bite {};
  bool attack_claw {};
  bool attack_lightning {};
  bool attack_natural {};
  bool attack_necrosis {};
  bool attack_poison {};
  //
  // Set if damage is already pre calculated
  //
  bool dmg_set {};
  int  damage {};
  //
  // For multiple attacks, which one is this?
  //
  unsigned char attack_num {};
  //
  // How many attempts to find a target
  //
  unsigned char attempt {};
  //
  // Where we want to attack
  //
  point attack_at;
  //
  // This is the swing animation.
  //
  std::string used_as;
} ThingAttackOptions;

#endif // _MY_THING_ATTACK_OPTIONS_HPP_
