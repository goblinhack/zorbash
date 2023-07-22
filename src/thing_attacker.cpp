//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::is_attacker(Thingp attacker)
{
  TRACE_NO_INDENT();
  if (unlikely(! maybe_aip())) { return false; }

  if (aip()->thing_attackers.find(attacker->id) != aip()->thing_attackers.end()) { return true; }

  return false;
}

//
// Timeout attackers so we don't resent them forever.
//
void Thing::attackers_tick(void)
{
  TRACE_NO_INDENT();
  if (! maybe_aip()) { return; }

  for (auto &p : aip()->thing_attackers) {
    auto attacker = level->thing_find_optional(p.first);
    if (! attacker) {
      aip()->thing_attackers.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      dbg("Enemy timeout %s (%d timeout)", attacker->to_string().c_str(), p.second);
      continue;
    }

    if (attacker->is_dead) {
      dbg("Enemy remove as is dead: %s", attacker->to_string().c_str());
      aip()->thing_attackers.erase(p.first);
      return;
    }

    //
    // If far enough away start to forget this attacker
    //
    if (distance(attacker->curr_at, curr_at) > distance_avoid_get()) {
      dbg("Enemy remove as is far away: %s", attacker->to_string().c_str());
      aip()->thing_attackers.erase(p.first);
      return;
    }

    //
    // Be resentful a bit longer
    //
    dbg("Enemy persists a bit longer: %s", attacker->to_string().c_str());
    p.second = pcg_random_range(0, 10);
  }
}

void Thing::add_attacker(Thingp attacker, bool recursing)
{
  TRACE_NO_INDENT();

  if (attacker == this) { return; }

  if (unlikely(! attacker->is_monst() && ! attacker->is_player())) { return; }

  if (unlikely(! is_monst() && ! is_player())) { return; }

  if (! ai_resent_count()) { return; }

  if (is_friend(attacker) || same_mob(attacker)) { return; }

  auto ai = aip();

  dbg("Add new attacker %s test %s:%d", attacker->to_string().c_str(), __FUNCTION__, __LINE__);
  if (! ai->thing_attackers[ attacker->id ]) {
    dbg("Add new attacker %s", attacker->to_string().c_str());
    ai->thing_attackers[ attacker->id ] = ai_resent_count();
  } else {
    dbg("Increment old attacker %s", attacker->to_string().c_str());
    ai->thing_attackers[ attacker->id ] *= 2;

    if (ai->thing_attackers[ attacker->id ] > THING_AI_MAX_RESENT_COUNT) {
      ai->thing_attackers[ attacker->id ] = THING_AI_MAX_RESENT_COUNT;
    }
  }

  //
  // The attack will wake the monst if it is sleeping anyway. We want to
  // delay waking if already dead to get a better message.
  //
  if (! is_sleeping) { change_state(MONST_STATE_IDLE, "move interrupted by an attacker"); }

  //
  // For friends, also inherit the attacker status
  //
  if (! recursing) {
    if (ai->thing_friends.size() || ai->perma_friends.size()) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
          if (! get(ai->can_see_ever.can_see, x, y)) { continue; }
          FOR_ALL_THINGS_THAT_INTERACT(level, it, x, y)
          {
            if (! can_detect(it)) { continue; }
            if (! it->is_monst()) { continue; }
            if (it == this) { continue; }
            if (! is_friend(it)) { continue; }
            it->add_attacker(attacker, true);
          }
          FOR_ALL_THINGS_END();
        }
      }
    }
  }
}
