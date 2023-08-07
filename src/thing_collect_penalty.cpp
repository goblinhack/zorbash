//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::collect_penalty_get(Thingp item)
{
  TRACE_NO_INDENT();
  auto ai = maybe_aip();
  if (! ai) {
    return 0;
  }

  auto f = ai->collect_penalty.find(item->id);
  if (f == ai->collect_penalty.end()) {
    return 0;
  }

  return f->second * 10;
}

void Thing::reset_collect_penalty(Thingp item)
{
  TRACE_NO_INDENT();
  auto ai = maybe_aip();
  if (! ai) {
    return;
  }

  auto f = ai->collect_penalty.find(item->id);
  if (f == ai->collect_penalty.end()) {
    return;
  }

  f->second = 0;
}

//
// Timeout collect penalty so we don't penalize them forever.
//
void Thing::collect_penalty_tick(void)
{
  TRACE_NO_INDENT();
  auto ai = maybe_aip();
  if (! ai) {
    return;
  }

  for (auto &p : ai->collect_penalty) {
    auto item = level->thing_find_optional(p.first);
    if (! item) {
      ai->collect_penalty.erase(p.first);
      return;
    }

    if (item->is_dead) {
      dbg("Remove collect penalty, is dead: %s", item->to_string().c_str());
      ai->collect_penalty.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      dbg("Goal penalty: %s (%d timeout)", item->to_string().c_str(), p.second);
      continue;
    }

    dbg("Remove collect penalty: %s (%d timeout)", item->to_string().c_str(), p.second);
    ai->collect_penalty.erase(p.first);
    return;
  }
}

void Thing::add_collect_penalty(Thingp item)
{
  TRACE_NO_INDENT();
  auto ai = maybe_aip();
  if (! ai) {
    return;
  }

  auto penalty = ai->collect_penalty[ item->id ];

  if (! penalty) {
    penalty = 20;
    dbg("Set new collect penalty %s to %d", item->to_string().c_str(), penalty);
  } else {
    dbg("Increment new collect penalty %s to %d", item->to_string().c_str(), penalty);
    penalty += 2;

    if (penalty > THING_AI_MAX_GOAL_PENALTY) {
      penalty = THING_AI_MAX_GOAL_PENALTY;
    }
  }
  ai->collect_penalty[ item->id ] = penalty;
}
