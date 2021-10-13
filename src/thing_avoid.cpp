//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_dmap.h"
#include "my_game.h"
#include "my_level.h"
#include "my_main.h"
#include "my_math.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_random.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_vector_bounds_check.h"
#include <algorithm>
#include <set>

bool Thing::will_avoid_monst(const Thingp it)
{
  TRACE_AND_INDENT();
  auto me = tp();

  if (is_dangerous(it)) {
    return true;
  }

  if (me->is_meat()) {
    if (it->is_meat_eater() || it->attack_meat()) {
      if (is_dangerous(it)) {
        return true;
      }
    }
  }

  if (me->is_blood()) {
    if (it->is_blood_eater() || it->attack_blood()) {
      if (is_dangerous(it)) {
        return true;
      }
    }
  }

  if (me->is_humanoid()) {
    if (it->attack_humanoid()) {
      if (is_dangerous(it)) {
        return true;
      }
    }
  }

  if (me->is_living()) {
    if (it->attack_living()) {
      if (is_dangerous(it)) {
        return true;
      }
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

bool Thing::will_avoid_monst(const point &p)
{
  TRACE_AND_INDENT();
  auto me = tp();

  FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y)
  {
    if (it == this) {
      continue;
    }
    if (me->is_monst()) {
      if (it->is_player()) {
        if (is_dangerous(it)) {
          return true;
        }
      }
    }

    if (me->is_meat()) {
      if (it->is_meat_eater() || it->attack_meat()) {
        if (is_dangerous(it)) {
          return true;
        }
      }
    }

    if (me->is_humanoid()) {
      if (it->attack_humanoid()) {
        if (is_dangerous(it)) {
          return true;
        }
      }
    }

    if (me->is_living()) {
      if (it->attack_living()) {
        if (is_dangerous(it)) {
          return true;
        }
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

    if (is_dangerous(it)) {
      return true;
    }
  }
  FOR_ALL_THINGS_END()

  return false;
}

bool Thing::is_to_be_avoided(Thingp attacker) const
{
  TRACE_AND_INDENT();
  if (unlikely(! monst_aip)) {
    return false;
  }

  if (monst_aip->avoid.find(attacker->id) != monst_aip->avoid.end()) {
    return true;
  }
  return false;
}

bool Thing::cannot_avoid(Thingp attacker) const
{
  TRACE_AND_INDENT();
  if (unlikely(! monst_aip)) {
    return false;
  }

  auto f = monst_aip->avoid.find(attacker->id);
  if (f == monst_aip->avoid.end()) {
    return false;
  }

  //
  // If we hit this limit, then we're really failing to avoid
  //
  if (f->second >= THING_MAX_AVOID_COUNT) {
    return true;
  }

  return false;
}

//
// Timeout avoid so we don't resent them forever.
//
void Thing::avoid_tick(void)
{
  TRACE_AND_INDENT();
  if (! monst_aip) {
    return;
  }

  for (auto &p : monst_aip->avoid) {
    auto attacker = level->thing_find_optional(p.first);
    if (! attacker) {
      monst_aip->avoid.erase(p.first);
      return;
    }

    if (attacker->is_dead) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Remove avoid, is dead: %s", attacker->to_string().c_str());
      }
      monst_aip->avoid.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Avoid: %s (%d count)", attacker->to_string().c_str(), p.second);
      }
      continue;
    }

    //
    // If far enough away start to forget this enemy
    //
    if (distance(attacker->mid_at, mid_at) > ai_avoid_distance()) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Remove avoid: %s", attacker->to_string().c_str());
      }
      monst_aip->avoid.erase(p.first);
      return;
    }

    monst_aip->avoid.erase(p.first);
    return;
  }
}

void Thing::add_avoid(Thingp attacker)
{
  TRACE_AND_INDENT();

  if (attacker == this) {
    return;
  }
  if (unlikely(! attacker->is_monst() && ! attacker->is_player())) {
    return;
  }
  if (unlikely(! is_monst() && ! is_player())) {
    return;
  }
  if (! ai_avoid_distance()) {
    return;
  }

  if (! monst_aip->avoid[ attacker->id ]) {
    if (is_player() && game->robot_mode) {
      CON("Robot: Add new avoid %s", attacker->to_string().c_str());
    } else {
      dbg("Add new avoid %s", attacker->to_string().c_str());
    }
    monst_aip->avoid[ attacker->id ] += 2;
  } else {
    dbg("Increment old avoid %s", attacker->to_string().c_str());
    monst_aip->avoid[ attacker->id ] += 2;

    if (monst_aip->avoid[ attacker->id ] > THING_MAX_AVOID_COUNT) {
      monst_aip->avoid[ attacker->id ] = THING_MAX_AVOID_COUNT;
    }
  }
}
