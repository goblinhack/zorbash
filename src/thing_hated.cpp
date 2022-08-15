//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

//
// One level above dislike!
//

bool Thing::is_hated_by_me(const point p)
{
  TRACE_NO_INDENT();
  if (level->is_shallow_water(p) || level->is_deep_water(p)) {
    if (environ_avoids_water()) {
      return true;
    }
  }

  if (level->is_acid(p)) {
    if (environ_avoids_acid()) {
      return true;
    }
  }

  if (level->is_cold(p)) {
    if (environ_avoids_cold()) {
      return true;
    }
  }

  if (! is_floating() && ! is_flying() && ! is_able_to_jump()) {
    if (level->is_chasm(p)) {
      return true;
    }
    if (environ_avoids_fire()) {
      if (level->is_fire(p)) {
        return true;
      }
      if (level->is_lava(p)) {
        return true;
      }
    }
  }

  return false;
}

bool Tp::is_hated_by_me(Levelp level, point p) const
{
  TRACE_NO_INDENT();
  if (level->is_shallow_water(p) || level->is_deep_water(p)) {
    if (environ_avoids_water()) {
      return true;
    }
  }

  if (level->is_acid(p)) {
    if (environ_avoids_acid()) {
      return true;
    }
  }

  if (level->is_cold(p)) {
    if (environ_avoids_cold()) {
      return true;
    }
  }

  if (! is_floating() && ! is_flying() && ! is_able_to_jump()) {
    if (level->is_chasm(p)) {
      return true;
    }
    if (environ_avoids_fire()) {
      if (level->is_fire(p)) {
        return true;
      }
      if (level->is_lava(p)) {
        return true;
      }
    }
  }

  return false;
}

bool Thing::is_hated_by_me(const Thingp itp)
{
  TRACE_NO_INDENT();
  auto me = tp();
  auto it = itp->tp();

  if (me->environ_avoids_water()) {
    if (it->is_shallow_water() || it->is_deep_water()) {
      return true;
    }
  }

  if (me->environ_avoids_acid()) {
    if (it->is_acid()) {
      return true;
    }
  }

  if (me->environ_avoids_cold()) {
    if (it->is_cold()) {
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

  if (me->is_red_blood()) {
    if (it->is_red_blood_eater()) {
      if (is_dangerous(itp)) {
        return true;
      }
    }
  }

  if (me->is_green_blood()) {
    if (it->is_green_blood_eater()) {
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
    if (it->is_treasure_eater()) {
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

  return false;
}
