//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

//
// One level above dislike!
//

bool Thing::is_hated_by_me(const point &p)
{
  TRACE_AND_INDENT();
  if (level->is_shallow_water(p) || level->is_deep_water(p)) {
    if (environ_hates_water()) {
      return true;
    }
  }

  if (level->is_acid(p)) {
    if (environ_hates_acid()) {
      return true;
    }
  }

  if (level->is_poisonous(p)) {
    if (environ_hates_poison()) {
      return true;
    }
  }

  if (! is_floating()) {
    if (level->is_chasm(p)) {
      return true;
    }
  }

  if (! is_on_fire()) {
    int heat = level->heatmap(p);
    if (damage_value_doubled_from_fire()) {
      if (heat > 0) {
        if (environ_hates_fire()) {
          return true;
        }
      }
    } else {
      if (heat >= 1) {
        if (environ_hates_fire()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Tp::is_hated_by_me(Levelp level, point p) const
{
  TRACE_AND_INDENT();
  if (level->is_shallow_water(p) || level->is_deep_water(p)) {
    if (environ_hates_water()) {
      return true;
    }
  }

  if (level->is_acid(p)) {
    if (environ_hates_acid()) {
      return true;
    }
  }

  if (level->is_poisonous(p)) {
    if (environ_hates_poison()) {
      return true;
    }
  }

  if (! is_floating()) {
    if (level->is_chasm(p)) {
      return true;
    }
  }

  if (environ_hates_fire()) {
    int heat = level->heatmap(p);
    if (damage_value_doubled_from_fire()) {
      if (heat > 0) { // avoid if hotter
        return true;
      }
    } else {
      if (heat >= 1) { // avoid if hotter
        return true;
      }
    }
  }

  return false;
}

bool Thing::is_hated_by_me(const Thingp itp)
{
  TRACE_AND_INDENT();
  auto me = tp();
  auto it = itp->tp();

  if (me->environ_hates_water()) {
    if (it->is_shallow_water() || it->is_deep_water()) {
      return true;
    }
  }

  if (me->environ_hates_acid()) {
    if (it->is_acid()) {
      return true;
    }
  }

  if (me->environ_hates_poison()) {
    if (it->is_poisonous()) {
      return true;
    }
  }

  if (me->is_meat()) {
    if (it->is_meat_eater() || it->attack_meat()) {
      if (is_dangerous(itp)) {
        return true;
      }
    }
  }

  if (me->is_blood()) {
    if (it->is_blood_eater() || it->attack_blood()) {
      if (is_dangerous(itp)) {
        return true;
      }
    }
  }

  if (me->is_humanoid()) {
    if (it->attack_humanoid()) {
      if (is_dangerous(itp)) {
        return true;
      }
    }
  }

  if (me->is_living()) {
    if (it->attack_living()) {
      if (is_dangerous(itp)) {
        return true;
      }
    }
  }

  if (me->is_food()) {
    if (it->is_food_eater()) {
      return true;
    }
  }

  if (me->is_treasure_type()) {
    if (it->is_treasure_type_eater()) {
      return true;
    }
  }

  if (me->is_potion()) {
    if (it->is_potion_eater()) {
      return true;
    }
  }

  if (me->is_item_magical()) {
    if (it->is_item_magical_eater()) {
      return true;
    }
  }

  if (me->is_jelly_baby()) {
    //
    // But allow baby slimes to attack each other!
    //
    if (it->is_jelly_parent()) {
      return true;
    }
  }

  if (! is_on_fire()) {
    if (me->environ_hates_fire()) {
      if (it->is_brazier()) {
        return false;
      }
      if (it->is_fire()) {
        return true;
      }
      if (it->is_lava()) {
        return true;
      }
    }
  }

  return false;
}
