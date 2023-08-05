//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::is_enemy(Thingp attacker)
{
  TRACE_NO_INDENT();
  if (unlikely(! maybe_aip())) {
    return false;
  }

  if (aip()->thing_enemies.find(attacker->id) != aip()->thing_enemies.end()) {
    return true;
  }

  if (aip()->perma_enemies.find(attacker->tp()->id) != aip()->perma_enemies.end()) {
    return true;
  }

  return false;
}

//
// Timeout enemies so we don't resent them forever.
//
void Thing::enemies_tick(void)
{
  TRACE_NO_INDENT();
  if (! maybe_aip()) {
    return;
  }

  for (auto &p : aip()->thing_enemies) {
    auto attacker = level->thing_find_optional(p.first);
    if (! attacker) {
      aip()->thing_enemies.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      dbg("Enemy timeout %s (%d timeout)", attacker->to_string().c_str(), p.second);
      continue;
    }

    if (attacker->is_dead) {
      dbg("Enemy remove as is dead: %s", attacker->to_string().c_str());
      aip()->thing_enemies.erase(p.first);
      return;
    }

    //
    // If far enough away start to forget this enemy
    //
    if (distance(attacker->curr_at, curr_at) > distance_avoid_get()) {
      dbg("Enemy remove as is far away: %s", attacker->to_string().c_str());
      aip()->thing_enemies.erase(p.first);
      return;
    }

    //
    // Be resentful a bit longer
    //
    dbg("Enemy persists a bit longer: %s", attacker->to_string().c_str());
    p.second = pcg_random_range(0, 10);
  }
}

void Thing::add_enemy(Thingp attacker, bool recursing)
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

  if (! ai_resent_count()) {
    return;
  }

  if (is_friend(attacker) || same_mob(attacker)) {
    return;
  }

  auto ai = aip();

  if (! ai->thing_enemies[ attacker->id ]) {
    dbg("Add new enemy %s", attacker->to_string().c_str());
    ai->thing_enemies[ attacker->id ] = ai_resent_count();
  } else {
    dbg("Increment old enemy %s", attacker->to_string().c_str());
    ai->thing_enemies[ attacker->id ] *= 2;

    if (ai->thing_enemies[ attacker->id ] > THING_AI_MAX_RESENT_COUNT) {
      ai->thing_enemies[ attacker->id ] = THING_AI_MAX_RESENT_COUNT;
    }
  }

  //
  // The attack will wake the monst if it is sleeping anyway. We want to
  // delay waking if already dead to get a better message.
  //
  if (! is_sleeping) {
    change_state(MONST_STATE_IDLE, "move interrupted by an enemy");
  }

  //
  // For friends, also inherit the enemy status
  //
  if (! recursing) {
    if (ai->thing_friends.size() || ai->perma_friends.size()) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
          if (! get(ai->can_see_ever.can_see, x, y)) {
            continue;
          }
          FOR_ALL_THINGS_THAT_INTERACT(level, it, x, y)
          {
            if (! can_detect(it)) {
              continue;
            }
            if (! it->is_monst()) {
              continue;
            }
            if (it == this) {
              continue;
            }
            if (! is_friend(it)) {
              continue;
            }
            it->add_enemy(attacker, true);
          }
          FOR_ALL_THINGS_END();
        }
      }
    }
  }
}

void Thing::add_enemy(Tpp attacker)
{
  TRACE_NO_INDENT();

  aip()->perma_enemies.insert(attacker->id);
}
