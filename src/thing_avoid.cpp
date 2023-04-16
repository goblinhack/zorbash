//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::will_avoid_monst(const Thingp it)
{
  TRACE_NO_INDENT();
  auto me = tp();

  // dbg("Avoid %s?", it->to_short_string().c_str());

  //
  // Avoid flaming things; even friends.
  //
  if (! is_fire_elemental()) {
    if (environ_dislikes_fire() > 10) {
      if (it->is_fire()) {
        dbg("Avoid fire: %s", it->to_short_string().c_str());
        return true;
      }

      if (it->is_on_fire()) {
        dbg("Avoid on fire: %s", it->to_short_string().c_str());
        return true;
      }
    }
  }

  //
  // Low on health?
  //
  if (! is_fearless()) {
    if (is_cautious()) {
      if (health() < health_max() / 2) {
        dbg("Avoid %s? yes as low on health", it->to_short_string().c_str());
        return false;
      }
    }

    if (is_daring()) {
      if (health() < health_max() / 3) {
        dbg("Avoid %s? yes as low on health", it->to_short_string().c_str());
        return false;
      }
    }
  }

  //
  // Not moving?
  //
  if (it->idle_count() > 5) {
    dbg("Avoid %s? no it's idle", it->to_short_string().c_str());
    return false;
  }

  //
  // It's stuck?
  //
  if (it->stuck_count() > 5) {
    dbg("Avoid %s? no it's stuck", it->to_short_string().c_str());
    return false;
  }

  if (is_friend(it) || same_mob(it)) {
    dbg("Avoid %s? no it's a friend", it->to_short_string().c_str());
    return false;
  }

  if (is_dangerous(it)) {
    dbg("Avoid dangerous: %s", it->to_short_string().c_str());
    return true;
  }

  if (it->is_edible(this) && is_dangerous(it)) {
    dbg("Avoid dangerous eater: %s", it->to_short_string().c_str());
    return true;
  }

  if (me->is_humanoid()) {
    if (it->attack_humanoid()) {
      if (is_dangerous(it)) {
        dbg("Avoid dangerous humanoid: %s", it->to_short_string().c_str());
        return true;
      }
    }
  }

  if (me->is_living()) {
    if (it->attack_living()) {
      if (is_dangerous(it)) {
        dbg("Avoid dangerous monst: %s", it->to_short_string().c_str());
        return true;
      }
    }
  }

  if (me->is_meat()) {
    if (it->attack_meat()) {
      if (is_dangerous(it)) {
        dbg("Avoid dangerous monst: %s", it->to_short_string().c_str());
        return true;
      }
    }
  }

  if (me->is_red_blooded() || me->is_green_blooded() || me->is_red_blood() || me->is_green_blood()) {
    if (it->attack_blood()) {
      if (is_dangerous(it)) {
        dbg("Avoid dangerous monst: %s", it->to_short_string().c_str());
        return true;
      }
    }
  }

  if (me->is_undead()) {
    if (it->attack_undead()) {
      if (is_dangerous(it)) {
        dbg("Avoid dangerous monst: %s", it->to_short_string().c_str());
        return true;
      }
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

    if (! can_detect(it)) {
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

    if (is_friend(it) || same_mob(it)) {
      return false;
    }

    if (me->is_monst()) {
      if (it->is_player()) {
        if (is_dangerous(it)) {
          if (health() < health_max() / 4) {
            dbg("Avoid dangerous as I am weak: %s", it->to_short_string().c_str());
            return true;
          }
        }
      }
    }

    if (it->is_edible(this) && is_dangerous(it)) {
      if (health() < health_max() / 4) {
        dbg("Avoid meat eater as I am weak: %s", it->to_short_string().c_str());
        return true;
      }
    }

    if (me->is_humanoid()) {
      if (it->attack_humanoid()) {
        if (is_dangerous(it)) {
          if (health() < health_max() / 4) {
            dbg("Avoid humanoid eater as I am weak: %s", it->to_short_string().c_str());
            return true;
          }
        }
      }
    }

    if (me->is_living()) {
      if (it->attack_living()) {
        if (is_dangerous(it)) {
          if (health() < health_max() / 4) {
            dbg("Avoid living eater as I am weak: %s", it->to_short_string().c_str());
            return true;
          }
        }
      }
    }

    if (me->is_meat()) {
      if (it->attack_meat()) {
        if (is_dangerous(it)) {
          if (health() < health_max() / 4) {
            dbg("Avoid meat eater as I am weak: %s", it->to_short_string().c_str());
            return true;
          }
        }
      }
    }

    if (me->is_red_blooded() || me->is_green_blooded() || me->is_red_blood() || me->is_green_blood()) {
      if (it->attack_blood()) {
        if (is_dangerous(it)) {
          if (health() < health_max() / 4) {
            dbg("Avoid blood eater as I am weak: %s", it->to_short_string().c_str());
            return true;
          }
        }
      }
    }

    if (me->is_undead()) {
      if (it->attack_undead()) {
        if (is_dangerous(it)) {
          if (health() < health_max() / 4) {
            dbg("Avoid undead eater as I am weak: %s", it->to_short_string().c_str());
            return true;
          }
        }
      }
    }

    if (is_dangerous(it)) {
      if (health() < health_max() / 4) {
        dbg("Avoid dangerous: %s", it->to_short_string().c_str());
        return true;
      }
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

  return aip()->avoid.find(attacker->id) != aip()->avoid.end();
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
  return f->second >= THING_AI_MAX_AVOID_COUNT;
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
      dbg("Remove avoid, is dead: %s", attacker->to_string().c_str());
      aip()->avoid.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      dbg("Avoid: %s (%d count)", attacker->to_string().c_str(), p.second);
      continue;
    }

    //
    // If far enough away start to forget this enemy
    //
    if (distance(attacker->curr_at, curr_at) > distance_avoid_get()) {
      dbg("Remove avoid: %s", attacker->to_string().c_str());
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
    dbg("Add new avoid %s", attacker->to_string().c_str());
    aip()->avoid[ attacker->id ] += 2;
  } else {
    dbg("Increment old avoid %s", attacker->to_string().c_str());
    aip()->avoid[ attacker->id ] += 2;

    if (aip()->avoid[ attacker->id ] > THING_AI_MAX_AVOID_COUNT) {
      aip()->avoid[ attacker->id ] = THING_AI_MAX_AVOID_COUNT;
    }
  }
}
