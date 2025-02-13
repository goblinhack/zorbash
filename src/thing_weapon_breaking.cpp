//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_english.hpp"
#include "my_thing.hpp"

#include <math.h>

//
// See if the weapon crumbles
//
int Thing::weapon_dmgd_pct(void)
{
  if (! damaged_count()) {
    return 0;
  }
  return int(((((float) damaged_count())) / (((float) health_max()))) * 100.0);
}

//
// Take account of the state of the weapon
//
int Thing::weapon_dmg_modify(int damage, Thingp victim)
{
  if (! damaged_count()) {
    return damage;
  }

  //
  // Allow already damaged weapons to hit soft victims
  //
  if (victim && victim->is_soft()) {
    //
    // War-hammer versus soft slimes!
    //
    if (is_blunt()) {
      return damage * 2;
    }

    return damage;
  }

  int dmg_in = damage;
  damage -= (int) ceil(((((float) damage)) / 100.0) * ((float) weapon_dmgd_pct()));

  //
  // If this is zero then we can get into endless robot loops trying to escape and
  // hitting a web and making no progress.
  //
  if (damage < 1) {
    damage = 1;
  }

  dbg("Weapon is damaged, hits for %d -> %d", dmg_in, damage);

  return damage;
}

//
// See if the weapon crumbles
//
void Thing::weapon_check_for_dmg(Thingp weapon, Thingp victim)
{
  auto my_owner = weapon->top_owner();
  if (! my_owner) {
    return;
  }

  bool corrode = false;
  bool damaged = false;

  //
  // Enchantment is already factored in here
  //
  auto damaged_chance = weapon->chance_d10000_damaged();

  //
  // Less chance of damage of hitting something soft.
  //
  if (victim->is_soft()) {
    //
    // Unless it is a pile of acid!
    //
    if (! victim->is_acid()) {
      damaged_chance /= 4;
    }
  }

  //
  // If we are attacking something that is of a form that we cannot withstand, then double damage
  //
  if (! is_acid()) {
    if (victim->is_acid()) {
      if (! weapon->is_immune_to_acid()) {
        damaged_chance *= 2;
        if (weapon->dmg_rcv_doubled_from_acid()) {
          damaged_chance *= 2;
        }

        //
        // Wooden items corrode faster
        //
        if (weapon->is_wooden()) {
          damaged_chance *= 2;
        }
      }
    }
  }

  if (! is_cold()) {
    if (victim->is_cold()) {
      if (! weapon->is_immune_to_cold()) {
        damaged_chance *= 2;
        if (weapon->dmg_rcv_doubled_from_cold()) {
          damaged_chance *= 2;
        }
      }
    }
  }

  if (! is_fire()) {
    if (victim->is_fire()) {
      if (! weapon->is_immune_to_fire()) {
        damaged_chance *= 2;
        if (weapon->dmg_rcv_doubled_from_fire()) {
          damaged_chance *= 2;
        }
      }
    }
  }

  if (! is_water()) {
    if (victim->is_water()) {
      if (! weapon->is_immune_to_water()) {
        damaged_chance *= 2;
        if (weapon->dmg_rcv_doubled_from_water()) {
          damaged_chance *= 2;
        }
      }
    }
  }

  if (is_wooden()) {
    damaged_chance *= 2;
  }

  if (is_rusty()) {
    damaged_chance *= 2;
  }

  //
  // If the thing we're hitting is harder than us, then increase
  // the chance of damage.
  //
  if (! is_hard()) {
    if (victim->is_hard()) {
      damaged_chance *= 2;
      damaged = true;
    }
  }

  if (! is_very_hard()) {
    if (victim->is_very_hard()) {
      //
      // This will be * 4 as the above will pass too.
      //
      damaged_chance *= 2;
      damaged = true;
    }
  }

  //
  // If lucky, no damage.
  //
  if (d20_ge(stat_luck_total(), SAVING_ROLL_HARD)) {
    damaged_chance = 0;
  }

  //
  // See if the weapon is damaged.
  //
  auto roll = d10000();
  if (roll > damaged_chance) {
    return;
  }

  weapon->damaged_count_incr(1);

  //
  // Decrement the items health. If it gets too damaged, it is dead.
  //
  if (weapon->health_decr(1) > 0) {
    if (my_owner->is_player()) {
      if (damaged) {
        if (weapon->is_wooden()) {
          my_owner->msg("%%fg=orange$Your %s is splintering on %s.%%fg=reset$", weapon->text_long_name().c_str(),
                        victim->text_the().c_str());
        } else {
          my_owner->msg("%%fg=orange$Your %s is buckling on %s.%%fg=reset$", weapon->text_long_name().c_str(),
                        victim->text_the().c_str());
        }
      } else if (corrode) {
        my_owner->msg("%%fg=orange$Your %s is corroding on %s.%%fg=reset$", weapon->text_long_name().c_str(),
                      victim->text_the().c_str());
      } else if (victim->is_hard()) {
        my_owner->msg("%%fg=orange$Your %s is damaged by %s.%%fg=reset$", weapon->text_long_name().c_str(),
                      victim->text_the().c_str());
      } else {
        my_owner->msg("%%fg=orange$Your %s is damaged by %s.%%fg=reset$", weapon->text_long_name().c_str(),
                      victim->text_the().c_str());
      }
    } else {
      if (damaged) {
        if (weapon->is_wooden()) {
          my_owner->msg("%%fg=orange$%s %s is splintering on %s.%%fg=reset$",
                        apostrophise(my_owner->text_The()).c_str(), weapon->text_long_name().c_str(),
                        victim->text_the().c_str());
        } else {
          my_owner->msg("%%fg=orange$%s %s is buckling on %s.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
                        weapon->text_long_name().c_str(), victim->text_the().c_str());
        }
      } else if (corrode) {
        my_owner->msg("%%fg=orange$%s %s is corroding on %s.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
                      weapon->text_long_name().c_str(), victim->text_the().c_str());
      } else {
        my_owner->msg("%%fg=orange$%s %s is damaged by %s.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
                      weapon->text_long_name().c_str(), victim->text_the().c_str());
      }
    }
    return;
  }

  if (my_owner->is_player()) {
    if (damaged) {
      if (weapon->is_wooden()) {
        my_owner->msg("%%fg=red$Your %s shatters on %s.%%fg=reset$", weapon->text_long_name().c_str(),
                      victim->text_the().c_str());
      } else {
        my_owner->msg("%%fg=red$Your %s buckles on %s.%%fg=reset$", weapon->text_long_name().c_str(),
                      victim->text_the().c_str());
      }
    } else if (corrode) {
      my_owner->msg("%%fg=red$Your %s is dissolves on %s.%%fg=reset$", weapon->text_long_name().c_str(),
                    victim->text_the().c_str());
    } else {
      my_owner->msg("%%fg=red$Your %s breaks on %s.%%fg=reset$", weapon->text_long_name().c_str(),
                    victim->text_the().c_str());
    }
  } else {
    if (damaged) {
      if (weapon->is_wooden()) {
        my_owner->msg("%%fg=orange$%s %s shatters.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
                      weapon->text_long_name().c_str());
      } else {
        my_owner->msg("%%fg=orange$%s %s is buckled.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
                      weapon->text_long_name().c_str());
      }
    } else if (corrode) {
      my_owner->msg("%%fg=orange$%s %s is corroded.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
                    weapon->text_long_name().c_str());
    } else {
      my_owner->msg("%%fg=orange$%s %s is destroyed.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
                    weapon->text_long_name().c_str());
    }
  }
  weapon->dead("broken");
}
