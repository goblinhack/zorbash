//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"

//
// One level above dislike!
//

bool Thing::is_hated_by_me(const point p)
{
  TRACE_NO_INDENT();

  //
  // Limit krakens to the depths, but allow eels and pirhana_giants free roam.
  //
  if (is_swimmer()) {
    if (environ_deep_water() && environ_shallow_water()) {
      if (! level->is_water(p)) {
        return true;
      }
    } else if (environ_deep_water()) {
      if (! level->is_deep_water(p)) {
        return true;
      }
    } else if (environ_shallow_water()) {
      if (! level->is_shallow_water(p)) {
        return true;
      }
    } else {
      if (! level->is_water(p)) {
        return true;
      }
    }
  }

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
        if (! is_fire_elemental()) {
          return true;
        }
      }
      if (level->is_lava(p)) {
        if (! environ_prefer_lava()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Tp::is_hated_by_me(Levelp level, point p) const
{
  TRACE_NO_INDENT();

  //
  // Limit krakens to the depths, but allow eels and pirhana_giants free roam.
  //
  if (is_swimmer()) {
    if (environ_deep_water() && environ_shallow_water()) {
      if (! level->is_water(p)) {
        return true;
      }
    } else if (environ_deep_water()) {
      if (! level->is_deep_water(p)) {
        return true;
      }
    } else if (environ_shallow_water()) {
      if (! level->is_shallow_water(p)) {
        return true;
      }
    } else {
      if (! level->is_water(p)) {
        return true;
      }
    }
  }

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
        if (! is_fire_elemental()) {
          return true;
        }
      }
      if (level->is_lava(p)) {
        if (! environ_prefer_lava()) {
          return true;
        }
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

  if (it->is_edible(this)) {
    if (is_dangerous(itp)) {
      return true;
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

  if (me->is_meat()) {
    if (it->attack_meat()) {
      if (is_dangerous(itp)) {
        return true;
      }
    }
  }

  if (me->is_red_blooded() || me->is_green_blooded() || me->is_red_blood() || me->is_green_blood()) {
    if (it->attack_blood()) {
      if (is_dangerous(itp)) {
        return true;
      }
    }
  }

  if (me->is_undead()) {
    if (it->attack_undead()) {
      if (is_dangerous(itp)) {
        return true;
      }
    }
  }

  return false;
}
