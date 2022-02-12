//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>
#include <set>

int Thing::goal_penalty_get(Thingp attacker)
{
  TRACE_NO_INDENT();
  auto ai = maybe_aip();
  if (! ai) {
    return 0;
  }

  auto f = ai->goal_penalty.find(attacker->id);
  if (f == ai->goal_penalty.end()) {
    return 0;
  }

  return f->second * 10;
}

void Thing::reset_goal_penalty(Thingp attacker)
{
  TRACE_NO_INDENT();
  auto ai = maybe_aip();
  if (! ai) {
    return;
  }

  auto f = ai->goal_penalty.find(attacker->id);
  if (f == ai->goal_penalty.end()) {
    return;
  }

  f->second = 0;
}

//
// Timeout goal penalty so we don't resent them forever.
//
void Thing::goal_penalty_tick(void)
{
  TRACE_NO_INDENT();
  auto ai = maybe_aip();
  if (! ai) {
    return;
  }

  for (auto &p : ai->goal_penalty) {
    auto attacker = level->thing_find_optional(p.first);
    if (! attacker) {
      ai->goal_penalty.erase(p.first);
      return;
    }

    if (attacker->is_dead) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Remove goal penalty, is dead: %s", attacker->to_string().c_str());
      }
      ai->goal_penalty.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      if (is_player() && game->robot_mode) {
        CON("Robot: goal penalty: %s (%d timeout)", attacker->to_string().c_str(), p.second);
      }
      continue;
    }

    if (is_player() && game->robot_mode) {
      CON("Robot: Remove goal penalty: %s (%d timeout)", attacker->to_string().c_str(), p.second);
    }

    ai->goal_penalty.erase(p.first);
    return;
  }
}

void Thing::add_goal_penalty(Thingp attacker)
{
  TRACE_NO_INDENT();
  auto ai = maybe_aip();
  if (! ai) {
    return;
  }

  auto penalty = ai->goal_penalty[ attacker->id ];

  if (! penalty) {
    penalty = 20;
    if (is_player() && game->robot_mode) {
      CON("Robot: Set new goal penalty %s to %d", attacker->to_string().c_str(), penalty);
    } else {
      dbg("Set new goal penalty %s to %d", attacker->to_string().c_str(), penalty);
    }
  } else {
    if (is_player() && game->robot_mode) {
      CON("Robot: Increment new goal penalty %s to %d", attacker->to_string().c_str(), penalty);
    } else {
      dbg("Increment new goal penalty %s to %d", attacker->to_string().c_str(), penalty);
    }
    penalty += 2;

    if (penalty > THING_AI_MAX_GOAL_PENALTY) {
      penalty = THING_AI_MAX_GOAL_PENALTY;
    }
  }
  ai->goal_penalty[ attacker->id ] = penalty;
}
