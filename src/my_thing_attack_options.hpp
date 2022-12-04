//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_ATTACK_OPTIONS_HPP_
#define _MY_THING_ATTACK_OPTIONS_HPP_

#include "my_fwd.hpp"
#include "my_point.hpp"
#include <string>

#define FOR_ALL_ATTACK_TYPES(_attack_) for (auto _attack_ = 0; _attack_ < THING_ATTACK_MAX; _attack_++)

typedef enum {
  THING_ATTACK_WATER,
  THING_ATTACK_ACID,
  THING_ATTACK_COLD,
  THING_ATTACK_CRUSH,
  THING_ATTACK_DIGEST,
  THING_ATTACK_DRAINING,
  THING_ATTACK_ENERGY,
  THING_ATTACK_NEGATION,
  THING_ATTACK_FIRE,
  THING_ATTACK_DROWN,
  THING_ATTACK_BITE,
  THING_ATTACK_CLAW,
  THING_ATTACK_LIGHTNING,
  THING_ATTACK_NATURAL,
  THING_ATTACK_NECROSIS,
  THING_ATTACK_POISON,
  THING_ATTACK_MAX,
} ThingAttack;

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
  bool attack[ THING_ATTACK_MAX ] = {};
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
