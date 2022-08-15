//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::is_disliked_by_me(const point p)
{
  TRACE_NO_INDENT();
  if (level->is_shallow_water(p) || level->is_deep_water(p)) {
    if (environ_avoids_water()) {
      // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (level->is_acid(p)) {
    if (environ_avoids_acid()) {
      // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (level->is_cold(p)) {
    if (environ_avoids_cold()) {
      // log("%s is disliked line %d", p.to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (! is_floating() && ! is_flying()) {
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
    int  heat        = level->heatmap(p);
    auto avoid_level = environ_avoids_fire();
    if (damage_received_doubled_from_fire()) {
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
  auto avoid_level = environ_avoids_fire();
  if (damage_received_doubled_from_fire()) {
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

  if (me->environ_avoids_water()) {
    if (it->is_shallow_water() || it->is_deep_water()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->environ_avoids_acid()) {
    if (it->is_acid()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->environ_avoids_poison()) {
    if (it->is_poisonous_danger_level()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->environ_avoids_necrosis()) {
    if (it->is_necrotic_danger_level()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->is_meat()) {
    if (it->is_meat_eater() || it->attack_meat()) {
      if (is_dangerous(itp)) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  if (me->is_red_blood()) {
    if (it->is_red_blood_eater()) {
      if (is_dangerous(itp)) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  if (me->is_green_blood()) {
    if (it->is_green_blood_eater()) {
      if (is_dangerous(itp)) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  if (me->is_humanoid()) {
    if (it->attack_humanoid()) {
      if (is_dangerous(itp)) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  if (me->is_living()) {
    if (it->attack_living()) {
      if (is_dangerous(itp)) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  if (me->is_food()) {
    if (it->is_food_eater()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->is_treasure_type()) {
    if (it->is_treasure_eater()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->is_potion()) {
    if (it->is_potion_eater()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->is_item_magical()) {
    if (it->is_item_magical_eater()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (me->is_jelly_baby()) {
    //
    // But allow baby slimes to attack each other!
    //
    if (it->is_jelly_parent()) {
      // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
      return true;
    }
  }

  if (! is_on_fire()) {
    if (me->environ_avoids_fire()) {
      if (it->is_brazier()) {
        return false;
      }
      if (it->is_fire()) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
        return true;
      }
      if (it->is_lava()) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
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
    int  heat        = level->heatmap(itp->curr_at);
    auto avoid_level = environ_avoids_fire();
    if (damage_received_doubled_from_fire()) {
      avoid_level *= 2;
    }
    if (avoid_level >= 100) {
      if (heat >= 1) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
        return true;
      }
    } else if (avoid_level >= 10) {
      if (heat >= 9) {
        // log("%s is disliked line %d", it->to_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  return false;
}
