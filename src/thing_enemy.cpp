//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_tile.h"

bool Thing::is_enemy(Thingp attacker) const
{
  TRACE_AND_INDENT();
  if (unlikely(! monstp)) {
    return false;
  }

  if (monstp->enemies.find(attacker->id) != monstp->enemies.end()) {
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
  if (! monstp) {
    return;
  }

  for (auto &p : monstp->enemies) {
    if (--p.second > 0) {
      continue;
    }

    auto attacker = level->thing_find_optional(p.first);
    if (attacker) {
      //
      // If far enough away start to forget this enemy
      //
      if (distance(attacker->mid_at, mid_at) > ai_scent_distance()) {
        if (is_player() && game->robot_mode) {
          CON("Robot: Remove enemy: %s", attacker->to_string().c_str());
        }
        monstp->enemies.erase(p.first);
      }
    } else {
      monstp->enemies.erase(p.first);
    }
    return;
  }
}

void Thing::add_enemy(Thingp attacker)
{
  TRACE_AND_INDENT();
  if (unlikely(! attacker->is_monst())) {
    return;
  }

  if (unlikely(! monstp)) {
    return;
  }

  if (! ai_enemy_memory()) {
    return;
  }

  if (unlikely(is_player())) {
    //
    // Allow the robot to make enemies
    //
  } else if (unlikely(! is_monst())) {
    //
    // Only monsts make enemies
    //
    return;
  }

  if (! monstp->enemies[ attacker->id ]) {
    if (is_player() && game->robot_mode) {
      CON("Robot: Add new enemy %s", attacker->to_string().c_str());
    } else {
      dbg("Add new enemy %s", attacker->to_string().c_str());
    }
    monstp->enemies[ attacker->id ] = ai_enemy_memory();
  } else {
    dbg("Increment old enemy %s", attacker->to_string().c_str());
    monstp->enemies[ attacker->id ] *= 2;
  }
}
