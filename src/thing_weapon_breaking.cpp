//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_english.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

#include <math.h>

//
// See if the weapon crumbles
//
int Thing::weapon_damaged_pct(void)
{
  if (! damaged_count()) {
    return 0;
  }
  return int(((((float) damaged_count())) / (((float) health_max()))) * 100.0);
}

//
// Take account of the state of the weapon
//
int Thing::weapon_damage_modify(int damage)
{
  if (! damaged_count()) {
    return damage;
  }

  int damage_in = damage;
  damage -= (int) ceil(((((float) damage)) / 100.0) * ((float) weapon_damaged_pct()));
  dbg("Weapon is damaged, hits for %d -> %d", damage_in, damage);
  if (damage < 0) {
    damage = 0;
  }
  return damage;
}

//
// See if the weapon crumbles
//
void Thing::weapon_check_for_damage(Thingp weapon, Thingp victim)
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
  auto damaged_chance = weapon->damaged_chance_d10000();
  if (victim->is_soft()) {
    damaged_chance /= 2;
  }

  //
  // If we are attacking something that is of a form that we cannot withstand, then double damage
  //
  if (! is_acid()) {
    if (victim->is_acid()) {
      if (! weapon->is_immune_to_acid()) {
        damaged_chance *= 2;
        if (weapon->damage_received_doubled_from_acid()) {
          damaged_chance *= 2;
        }
      }
    }
  }

  if (! is_cold()) {
    if (victim->is_cold()) {
      if (! weapon->is_immune_to_cold()) {
        damaged_chance *= 2;
        if (weapon->damage_received_doubled_from_cold()) {
          damaged_chance *= 2;
        }
      }
    }
  }

  if (! is_fire()) {
    if (victim->is_fire()) {
      if (! weapon->is_immune_to_fire()) {
        damaged_chance *= 2;
        if (weapon->damage_received_doubled_from_fire()) {
          damaged_chance *= 2;
        }
      }
    }
  }

  if (! is_water()) {
    if (victim->is_water()) {
      if (! weapon->is_immune_to_water()) {
        damaged_chance *= 2;
        if (weapon->damage_received_doubled_from_water()) {
          damaged_chance *= 2;
        }
      }
    }
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
  // If you roll under luck, no damage.
  //
  if (d20roll_under(stat_luck_total())) {
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
          msg("%%fg=orange$Your %s is splintering.%%fg=reset$", weapon->text_long_name().c_str());
        } else {
          msg("%%fg=orange$Your %s is buckling.%%fg=reset$", weapon->text_long_name().c_str());
        }
      } else if (corrode) {
        msg("%%fg=orange$Your %s is corroding.%%fg=reset$", weapon->text_long_name().c_str());
      } else {
        msg("%%fg=orange$Your %s is damaged.%%fg=reset$", weapon->text_long_name().c_str());
      }
    } else {
      if (damaged) {
        if (weapon->is_wooden()) {
          msg("%%fg=orange$%s %s is splintering.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
              weapon->text_long_name().c_str());
        } else {
          msg("%%fg=orange$%s %s is buckling.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
              weapon->text_long_name().c_str());
        }
      } else if (corrode) {
        msg("%%fg=orange$%s %s is corroding.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
            weapon->text_long_name().c_str());
      } else {
        msg("%%fg=orange$%s %s is damaged.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
            weapon->text_long_name().c_str());
      }
    }
    return;
  }

  if (my_owner->is_player()) {
    if (damaged) {
      if (weapon->is_wooden()) {
        msg("%%fg=red$Your %s is shattered.%%fg=reset$", weapon->text_long_name().c_str());
      } else {
        msg("%%fg=red$Your %s is buckled.%%fg=reset$", weapon->text_long_name().c_str());
      }
    } else if (corrode) {
      msg("%%fg=red$Your %s is corroded.%%fg=reset$", weapon->text_long_name().c_str());
    } else {
      msg("%%fg=red$Your %s is destroyed.%%fg=reset$", weapon->text_long_name().c_str());
    }
  } else {
    if (damaged) {
      if (weapon->is_wooden()) {
        msg("%%fg=orange$%s %s is shattered.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
            weapon->text_long_name().c_str());
      } else {
        msg("%%fg=orange$%s %s is buckled.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
            weapon->text_long_name().c_str());
      }
    } else if (corrode) {
      msg("%%fg=orange$%s %s is corroded.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
          weapon->text_long_name().c_str());
    } else {
      msg("%%fg=orange$%s %s is destroyed.%%fg=reset$", apostrophise(my_owner->text_The()).c_str(),
          weapon->text_long_name().c_str());
    }
  }
  weapon->dead("broken");
}
