//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include <algorithm>
#include <set>

bool Thing::will_avoid_monst(const Thingp it)
{
  TRACE_NO_INDENT();
  auto me = tp();

  //
  // Not moving?
  //
  if (it->idle_count() > 5) {
    return false;
  }

  //
  // It's stuck?
  //
  if (it->stuck_count() > 5) {
    return false;
  }

  if (same_leader(it)) {
    return false;
  }

  if (it->is_minion() && (it->top_mob() == top_mob())) {
    return false;
  }

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

  if (me->is_red_blood()) {
    if (it->is_red_blood_eater()) {
      if (is_dangerous(it)) {
        return true;
      }
    }
  }

  if (me->is_green_blood()) {
    if (it->is_green_blood_eater()) {
      if (is_dangerous(it)) {
        return true;
      }
    }
  }

  if (me->is_pink_blood()) {
    if (it->is_pink_blood_eater()) {
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

bool Thing::will_avoid_monst(const point p)
{
  TRACE_NO_INDENT();
  auto me = tp();

  FOR_ALL_THINGS_THAT_INTERACT_UNSAFE(level, it, p.x, p.y)
  {
    if (it == this) {
      continue;
    }

    //
    // Not moving?
    //
    if (it->idle_count() > 5) {
      continue;
    }

    //
    // It's stuck?
    //
    if (it->stuck_count() > 5) {
      continue;
    }

    if (same_leader(it)) {
      return false;
    }

    if (it->is_minion() && (it->top_mob() == top_mob())) {
      return false;
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

bool Thing::is_to_be_avoided(Thingp attacker)
{
  TRACE_NO_INDENT();
  if (unlikely(! maybe_aip())) {
    return false;
  }

  if (aip()->avoid.find(attacker->id) != aip()->avoid.end()) {
    return true;
  }
  return false;
}

bool Thing::cannot_avoid(Thingp attacker)
{
  TRACE_NO_INDENT();
  if (unlikely(! maybe_aip())) {
    return false;
  }

  auto f = aip()->avoid.find(attacker->id);
  if (f == aip()->avoid.end()) {
    return false;
  }

  //
  // If we hit this limit, then we're really failing to avoid
  //
  if (f->second >= THING_AI_MAX_AVOID_COUNT) {
    return true;
  }

  return false;
}

//
// Timeout avoid so we don't resent them forever.
//
void Thing::avoid_tick(void)
{
  TRACE_NO_INDENT();
  if (! maybe_aip()) {
    return;
  }

  for (auto &p : aip()->avoid) {
    auto attacker = level->thing_find_optional(p.first);
    if (! attacker) {
      aip()->avoid.erase(p.first);
      return;
    }

    if (attacker->is_dead) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Remove avoid, is dead: %s", attacker->to_string().c_str());
      }
      aip()->avoid.erase(p.first);
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
    if (distance(attacker->curr_at, curr_at) > distance_avoid_get()) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Remove avoid: %s", attacker->to_string().c_str());
      }
      aip()->avoid.erase(p.first);
      return;
    }

    aip()->avoid.erase(p.first);
    return;
  }
}

void Thing::add_avoid(Thingp attacker)
{
  TRACE_NO_INDENT();

  if (attacker == this) {
    return;
  }
  if (unlikely(! attacker->is_monst() && ! attacker->is_player())) {
    return;
  }
  if (unlikely(! is_monst() && ! is_player())) {
    return;
  }
  if (! distance_avoid_get()) {
    return;
  }

  if (! aip()->avoid[ attacker->id ]) {
    if (is_player() && game->robot_mode) {
      CON("Robot: Add new avoid %s", attacker->to_string().c_str());
    } else {
      dbg("Add new avoid %s", attacker->to_string().c_str());
    }
    aip()->avoid[ attacker->id ] += 2;
  } else {
    dbg("Increment old avoid %s", attacker->to_string().c_str());
    aip()->avoid[ attacker->id ] += 2;

    if (aip()->avoid[ attacker->id ] > THING_AI_MAX_AVOID_COUNT) {
      aip()->avoid[ attacker->id ] = THING_AI_MAX_AVOID_COUNT;
    }
  }
}
