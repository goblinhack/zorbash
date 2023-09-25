//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"

bool Thing::is_disliked_by_me(const point p)
{
  TRACE_NO_INDENT();

  //
  // Intelligent monsters avoid traps
  //
  if (is_intelligent()) {
    if (level->is_trap(p)) {
      return true;
    }
  }

  //
  // Limit krakens to the depths, but allow eels and piranha_giants free roam.
  //
  if (is_swimmer()) {
    if (environ_likes_deep_water() && environ_likes_shallow_water()) {
      if (! level->is_water(p)) {
        return true;
      }
    } else if (environ_likes_deep_water()) {
      if (! level->is_deep_water(p)) {
        return true;
      }
    } else if (environ_likes_shallow_water()) {
      if (! level->is_shallow_water(p)) {
        if (! is_able_to_live_out_of_water()) {
          return true;
        }
      }
    } else {
      if (! level->is_water(p)) {
        return true;
      }
    }
  }

  if (level->is_shallow_water(p) || level->is_deep_water(p)) {
    if (environ_dislikes_water()) {
      // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (level->is_acid(p)) {
    if (environ_dislikes_acid()) {
      // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (level->is_cold(p)) {
    if (environ_dislikes_cold()) {
      // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (! is_floating_currently() && ! is_flying()) {
    if (level->is_chasm(p)) {
      // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (! is_on_fire()) {
    //
    // Single fire looks like:
    // .....
    // .111.
    // .151.
    // .111.
    // .....
    //
    //
    // Lava fire looks like:
    // ..... .....
    // .AAA. .LLL.
    // .A8A. .L.L.
    // .AAA. .LLL.
    // ..... .....
    //
    int  heat        = level->heatmap(p);
    auto avoid_level = environ_dislikes_fire();
    if (dmg_received_doubled_from_fire()) {
      avoid_level *= 2;
    }
    if (avoid_level >= 100) {
      if (heat >= 1) {
        // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
        return true;
      }
    } else if (avoid_level >= 10) {
      if (heat >= 9) {
        // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  return false;
}

bool Tp::is_disliked_by_me(Levelp level, point p) const
{
  TRACE_NO_INDENT();

  //
  // Intelligent monsters avoid traps
  //
  if (is_intelligent()) {
    if (level->is_trap(p)) {
      return true;
    }
  }

  //
  // Limit krakens to the depths, but allow eels and piranha_giants free roam.
  //
  if (is_swimmer()) {
    if (environ_likes_deep_water() && environ_likes_shallow_water()) {
      if (! level->is_water(p)) {
        return true;
      }
    } else if (environ_likes_deep_water()) {
      if (! level->is_deep_water(p)) {
        return true;
      }
    } else if (environ_likes_shallow_water()) {
      if (! level->is_shallow_water(p)) {
        if (! is_able_to_live_out_of_water()) {
          return true;
        }
      }
    } else {
      if (! level->is_water(p)) {
        return true;
      }
    }
  }

  if (level->is_shallow_water(p) || level->is_deep_water(p)) {
    if (environ_dislikes_water()) {
      return true;
    }
  }

  if (level->is_acid(p)) {
    if (environ_dislikes_acid()) {
      return true;
    }
  }

  if (level->is_cold(p)) {
    if (environ_dislikes_cold()) {
      return true;
    }
  }

  if (! is_floating() && ! is_flying()) {
    if (level->is_chasm(p)) {
      return true;
    }
  }

  //
  // Single fire looks like:
  // .....
  // .111.
  // .151.
  // .111.
  // .....
  //
  //
  // Lava fire looks like:
  // ..... .....
  // .AAA. .LLL.
  // .A8A. .L.L.
  // .AAA. .LLL.
  // ..... .....
  //
  int  heat        = level->heatmap(p);
  auto avoid_level = environ_dislikes_fire();
  if (dmg_received_doubled_from_fire()) {
    avoid_level *= 2;
  }
  if (avoid_level >= 100) {
    if (heat >= 1) {
      return true;
    }
  } else if (avoid_level >= 10) {
    if (heat >= 9) {
      return true;
    }
  }

  return false;
}

bool Thing::is_disliked_by_me(const Thingp itp)
{
  TRACE_NO_INDENT();
  auto me = tp();
  auto it = itp->tp();

  //
  // Intelligent monsters avoid traps
  //
  if (is_intelligent()) {
    if (it->is_trap()) {
      return true;
    }
  }

  if (me->environ_dislikes_water()) {
    if (it->is_shallow_water() || it->is_deep_water()) {
      // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->environ_dislikes_acid()) {
    if (it->is_acid()) {
      // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->environ_dislikes_poison()) {
    if (it->is_poisonous_danger_level()) {
      // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->environ_dislikes_necrosis()) {
    if (it->is_necrotic_danger_level()) {
      // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
  }

  if (it->is_edible(this) && is_dangerous(itp)) {
    // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
    return true;
  }

  if (me->is_humanoid()) {
    if (it->attack_humanoid()) {
      if (is_dangerous(itp)) {
        // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  if (me->is_living()) {
    if (it->attack_living()) {
      if (is_dangerous(itp)) {
        // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
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

  if (! is_fire_elemental()) {
    if (! is_on_fire()) {
      if (me->environ_dislikes_fire()) {
        if (it->is_brazier()) {
          return false;
        }
        if (it->is_fire()) {
          // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
          return true;
        }
        if (it->is_lava()) {
          // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
          if (! environ_likes_lava()) {
            return true;
          }
        }
      }

      //
      // Single fire looks like:
      // .....
      // .111.
      // .151.
      // .111.
      // .....
      //
      int  heat        = level->heatmap(itp->curr_at);
      auto avoid_level = environ_dislikes_fire();
      if (dmg_received_doubled_from_fire()) {
        avoid_level *= 2;
      }
      if (avoid_level >= 100) {
        if (heat >= 1) {
          // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
          return true;
        }
      } else if (avoid_level >= 10) {
        if (heat >= 9) {
          // log("%s is disliked line %d", it->to_short_string().c_str(), __LINE__);
          return true;
        }
      }
    }
  }

  return false;
}
