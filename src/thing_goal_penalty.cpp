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

int Thing::get_goal_penalty(Thingp attacker) const
{
  TRACE_AND_INDENT();
  if (unlikely(! monst_aip)) {
    return 0;
  }

  auto f = monst_aip->goal_penalty.find(attacker->id);
  if (f == monst_aip->goal_penalty.end()) {
    return 0;
  }

  return f->second * 10;
}

//
// Timeout goal penalty so we don't resent them forever.
//
void Thing::goal_penalty_tick(void)
{
  TRACE_AND_INDENT();
  if (! monst_aip) {
    return;
  }

  for (auto &p : monst_aip->goal_penalty) {
    auto attacker = level->thing_find_optional(p.first);
    if (! attacker) {
      monst_aip->goal_penalty.erase(p.first);
      return;
    }

    if (attacker->is_dead) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Remove goal penalty, is dead: %s", attacker->to_string().c_str());
      }
      monst_aip->goal_penalty.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      if (is_player() && game->robot_mode) {
        CON("Robot: goal penalty: %s (%d timeout)", attacker->to_string().c_str(), p.second);
      }
      continue;
    }
  }
}

void Thing::add_goal_penalty(Thingp attacker)
{
  TRACE_AND_INDENT();

  if (unlikely(! attacker->is_monst() && ! attacker->is_player())) {
    return;
  }
  if (unlikely(! is_monst() && ! is_player())) {
    return;
  }

  if (! monst_aip->goal_penalty[ attacker->id ]) {
    if (is_player() && game->robot_mode) {
      CON("Robot: Add new goal penalty %s", attacker->to_string().c_str());
    } else {
      dbg("Add new goal penalty %s", attacker->to_string().c_str());
    }
    monst_aip->goal_penalty[ attacker->id ] += 1;
  } else {
    dbg("Increment old goal penalty %s", attacker->to_string().c_str());
    monst_aip->goal_penalty[ attacker->id ] += 1;

    if (monst_aip->goal_penalty[ attacker->id ] > THING_MAX_GOAL_PENALTY) {
      monst_aip->goal_penalty[ attacker->id ] = THING_MAX_GOAL_PENALTY;
    }
  }
}
