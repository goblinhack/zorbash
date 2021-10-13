//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_random.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_tile.h"

bool Thing::is_enemy(Thingp attacker) const
{
  TRACE_AND_INDENT();
  if (unlikely(! monst_aip)) {
    return false;
  }

  if (monst_aip->enemies.find(attacker->id) != monst_aip->enemies.end()) {
    return true;
  }
  return false;
}

//
// Timeout enemies so we don't resent them forever.
//
void Thing::enemies_tick(void)
{
  TRACE_AND_INDENT();
  if (! monst_aip) {
    return;
  }

  for (auto &p : monst_aip->enemies) {
    auto attacker = level->thing_find_optional(p.first);
    if (! attacker) {
      monst_aip->enemies.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      if (is_player() && game->robot_mode) {
        CON("Robot: enemy timeout %s (%d timeout)", attacker->to_string().c_str(), p.second);
      }
      continue;
    }

    if (attacker->is_dead) {
      if (is_player() && game->robot_mode) {
        CON("Robot: enemy remove as is dead: %s", attacker->to_string().c_str());
      }
      monst_aip->enemies.erase(p.first);
      return;
    }

    //
    // If far enough away start to forget this enemy
    //
    if (distance(attacker->mid_at, mid_at) > ai_avoid_distance()) {
      if (is_player() && game->robot_mode) {
        CON("Robot: enemy remove as is far away: %s", attacker->to_string().c_str());
      }
      monst_aip->enemies.erase(p.first);
      return;
    }

    //
    // Be resentful a bit longer
    //
    if (is_player() && game->robot_mode) {
      CON("Robot: enemy persists a bit longer: %s", attacker->to_string().c_str());
    }
    p.second = pcg_random_range(0, 10);
  }
}

void Thing::add_enemy(Thingp attacker)
{
  TRACE_AND_INDENT();

  if (unlikely(! attacker->is_monst() && ! attacker->is_player())) {
    return;
  }
  if (unlikely(! is_monst() && ! is_player())) {
    return;
  }
  if (! ai_resent_count()) {
    return;
  }

  if (! monst_aip->enemies[ attacker->id ]) {
    if (is_player() && game->robot_mode) {
      CON("Robot: enemy add %s", attacker->to_string().c_str());
    } else {
      dbg("Add new enemy %s", attacker->to_string().c_str());
    }
    monst_aip->enemies[ attacker->id ] = ai_resent_count();
  } else {
    dbg("Increment old enemy %s", attacker->to_string().c_str());
    monst_aip->enemies[ attacker->id ] *= 2;

    if (monst_aip->enemies[ attacker->id ] > THING_MAX_ENEMY_COUNT) {
      monst_aip->enemies[ attacker->id ] = THING_MAX_ENEMY_COUNT;
    }
  }
}
