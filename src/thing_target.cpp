//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

bool Thing::is_target_select(Thingp item)
{
  TRACE_NO_INDENT();

  if (game->state != Game::STATE_CHOOSING_TARGET) {
    msg("Choose a target to use %s at.", item->text_the().c_str());
  }

  game->change_state(Game::STATE_CHOOSING_TARGET);
  level->cursor_recreate();
  if (level->cursor) {
    level->cursor->visible();
  }
  level->describe(item);

  return true;
}

//
// Find the best thing to attack. Look at our current direction and if nothing
// in that path, look around for something else.
//
bool Thing::victim_attack_best_attempt_1(Thingp item, point at, Thingp *best, point *best_hit_at,
                                         std::vector< point > &all_deltas)
{
  bool found_best {};
  int  best_priority = -999;

  dbg2("Target-attack-best: Try to find something to attack, attempt 1");
  TRACE_AND_INDENT();

  *best = nullptr;
  for (const auto &d : all_deltas) {
    //
    // Find the alternative best thing to hit
    //
    auto hit_at = at + d;

    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio = t->collision_hit_priority();
      dbg2("Target-attack-best: %s prio %d", t->to_short_string().c_str(), prio);

      if (t->is_dead || t->is_dying) {
        dbg2("Target-attack-best: %s no dead or dying", t->to_short_string().c_str());
        continue;
      }

      if (same_mob(t) || same_leader(t)) {
        dbg2("Target-attack-best: %s no same leader", t->to_short_string().c_str());
        continue;
      }

      if (t->is_mob() || t->is_monst() || t->is_player()) {
        prio += danger_current_level(t);
        dbg2("Target-attack-best: %s mob prio %d", t->to_short_string().c_str(), prio);

        //
        // Make sure we prefer monsts over things like doors if there is
        // a choice.
        //
        prio += 100;
        dbg2("Target-attack-best: %s monst prio %d", t->to_short_string().c_str(), prio);
      } else {
        dbg2("Target-attack-best: %s ignore1 %d", t->to_short_string().c_str(), prio);
        continue;
      }

      //
      // Get the most important thing to hit.
      //
      if (item && item->possible_to_attack(t)) {
        //
        // Sword can attack
        //
      } else if (! possible_to_attack(t)) {
        dbg2("Target-attack-best: %s no cannot attack", t->to_short_string().c_str());
        continue;
      }

      dbg2("Target-attack-best: %s final prio %d", t->to_short_string().c_str(), prio);
      if (prio > best_priority) {
        dbg2("Target-attack-best: %s is best prio %d", t->to_short_string().c_str(), prio);
        best_priority = prio;
        *best_hit_at  = hit_at;
        *best         = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  return found_best;
}

bool Thing::victim_attack_best_attempt_2(Thingp item, point at, Thingp *best, point *best_hit_at,
                                         std::vector< point > &all_deltas)
{
  bool found_best {};
  int  best_priority = -999;

  dbg2("Target-attack-best: Try to find something to attack, attempt 2");
  TRACE_AND_INDENT();

  *best = nullptr;
  for (const auto &d : all_deltas) {
    //
    // Find the alternative best thing to hit
    //
    auto hit_at = at + d;

    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio = t->collision_hit_priority();
      dbg2("Target-attack-best: %s prio %d", t->to_short_string().c_str(), prio);

      //
      // Get the most important thing to hit.
      //
      if (item && item->possible_to_attack(t)) {
        //
        // Ok. Sword can attack
        //
      } else if (! possible_to_attack(t)) {
        dbg2("Target-attack-best: %s no cannot attack", t->to_short_string().c_str());
        continue;
      }

      if (t->is_dead || t->is_dying) {
        dbg2("Target-attack-best: %s no dead or dying", t->to_short_string().c_str());
        continue;
      }

      if (same_mob(t) || same_leader(t)) {
        dbg2("Target-attack-best: %s no same leader", t->to_short_string().c_str());
        continue;
      }

      if (t->is_door()) {
        //
        // Ok
        //
      } else {
        dbg2("Target-attack-best: %s ignore2 %d", t->to_short_string().c_str(), prio);
        continue;
      }

      //
      // If being digested, this is high priority...
      //
      if (t->curr_at == curr_at) {
        prio *= 100;
        dbg2("Target-attack-best: %s digest prio %d", t->to_short_string().c_str(), prio);
      }

      dbg2("Target-attack-best: %s final prio %d", t->to_short_string().c_str(), prio);
      if (prio > best_priority) {
        dbg2("Target-attack-best: %s is best prio %d", t->to_short_string().c_str(), prio);
        best_priority = prio;
        *best_hit_at  = hit_at;
        *best         = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  return found_best;
}

bool Thing::victim_attack_best_attempt_3(Thingp item, point at, Thingp *best, point *best_hit_at,
                                         std::vector< point > &all_deltas)
{
  bool found_best {};
  int  best_priority = -999;

  dbg2("Target-attack-best: Try to find something to attack, attempt 3");
  TRACE_AND_INDENT();

  *best = nullptr;
  for (const auto &d : all_deltas) {
    //
    // Find the alternative best thing to hit
    //
    auto hit_at = at + d;

    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio = t->collision_hit_priority();
      dbg2("Target-attack-best: %s prio %d", t->to_short_string().c_str(), prio);

      //
      // Get the most important thing to hit.
      //
      if (item && item->possible_to_attack(t)) {
        //
        // Sword can attack
        //
      } else if (! possible_to_attack(t)) {
        dbg2("Target-attack-best: %s no cannot attack", t->to_short_string().c_str());
        continue;
      }

      if (t->is_dead || t->is_dying) {
        dbg2("Target-attack-best: %s no dead or dying", t->to_short_string().c_str());
        continue;
      }

      if (same_mob(t) || same_leader(t)) {
        dbg2("Target-attack-best: %s no same leader", t->to_short_string().c_str());
        continue;
      }

      if (t->is_hittable()) {
        prio += danger_current_level(t);
        dbg2("Target-attack-best: %s monst prio %d", t->to_short_string().c_str(), prio);
      } else {
        dbg2("Target-attack-best: %s ignore3 %d", t->to_short_string().c_str(), prio);
        continue;
      }

      dbg2("Target-attack-best: %s final prio %d", t->to_short_string().c_str(), prio);
      if (prio > best_priority) {
        dbg2("Target-attack-best: %s is best prio %d", t->to_short_string().c_str(), prio);
        best_priority = prio;
        *best_hit_at  = hit_at;
        *best         = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  return found_best;
}

bool Thing::victim_attack_found_best(Thingp item, Thingp best, point best_hit_at, bool &victim_attacked,
                                     bool &victim_overlaps)
{
  victim_attacked = false;
  victim_overlaps = false;

  dbg2("Target-attack-best: Best target to hit is %s at %s", best->to_string().c_str(),
       best_hit_at.to_string().c_str());
  TRACE_AND_INDENT();

  if (item) {
    on_use(item, best);
    if (item->collision_check_and_handle_at(best_hit_at, &victim_attacked, &victim_overlaps)) {
      lunge(best_hit_at);
      return true;
    }
  } else {
    if (collision_check_and_handle_at(best_hit_at, &victim_attacked, &victim_overlaps)) {
      lunge(best_hit_at);
      return true;
    }
  }
  return true;
}

bool Thing::victim_attack_choose_best(Thingp item, point at, Thingp *best, point *best_hit_at)
{
  std::vector< point > all_deltas = {point(0, 0)};

  if (victim_attack_best_attempt_1(item, curr_at, best, best_hit_at, all_deltas)) {
    return true;
  }

  if (victim_attack_best_attempt_2(item, curr_at, best, best_hit_at, all_deltas)) {
    return true;
  }

  if (victim_attack_best_attempt_3(item, curr_at, best, best_hit_at, all_deltas)) {
    return true;
  }

  return false;
}

bool Thing::victim_attack_best_at(int equip, point *at, int attempt, bool &victim_attacked, bool &victim_overlaps)
{
  if (at) {
    dbg("Target-attack-best-at: Try to attack with equipped item at %s", at->to_string().c_str());
  } else {
    dbg("Target-attack-best-at: Try to attack with equipped item");
  }
  TRACE_AND_INDENT();

  int  dx, dy;
  auto item = equip_get(equip);
  if (! item) {
    auto d = dir_to_direction();
    dx     = d.x;
    dy     = d.y;
  } else if (at) {
    dx = 0;
    dy = 0;
  } else {
    equip_use_offset_get(&dx, &dy, equip);
  }

  victim_attacked = false;
  victim_overlaps = false;

  dbg("Target-attack-best: Attack delta %d,%d", dx, dy);
  TRACE_AND_INDENT();

  //
  // Look in the chosen dir first for something to hit, then behind us.
  //
  std::vector< point > all_deltas = {
      point(dx, dy), point(-dx, -dy), point(-1, -1), point(1, -1), point(-1, 1), point(1, 1),
      point(0, -1),  point(-1, 0),    point(1, 0),   point(0, 1),  point(0, 0), // For spiderwebs
  };

  //
  // If stuck in a web we can only hit the web
  //
  if (level->is_spiderweb(curr_at)) {
    std::vector< point > local_only = {point(0, 0)};

    all_deltas = local_only;
  }

  //
  // If we clicked on a target we must attack only there.
  // If we pressed space then the target is where we are at, so look around
  // for the best thing to hit.
  //
  if (at && (*at != curr_at)) {
    auto                 delta      = *at - curr_at;
    std::vector< point > local_only = {delta};

    all_deltas = local_only;
  }

  Thingp best = nullptr;
  point  best_hit_at;

  //
  // Look in the chosen dir first
  //
  if (dx || dy) {
    std::vector< point > all_deltas = {
        point(dx, dy),
    };
    if (victim_attack_best_attempt_1(item, curr_at, &best, &best_hit_at, all_deltas)) {
      return victim_attack_found_best(item, best, best_hit_at, victim_attacked, victim_overlaps);
    }
  }

  if (attempt) {
    if (attempt == 1) {
      if (victim_attack_best_attempt_1(item, curr_at, &best, &best_hit_at, all_deltas)) {
        return victim_attack_found_best(item, best, best_hit_at, victim_attacked, victim_overlaps);
      }
    }
    if (attempt == 2) {
      if (victim_attack_best_attempt_2(item, curr_at, &best, &best_hit_at, all_deltas)) {
        return victim_attack_found_best(item, best, best_hit_at, victim_attacked, victim_overlaps);
      }
    }
    if (attempt == 3) {
      if (victim_attack_best_attempt_3(item, curr_at, &best, &best_hit_at, all_deltas)) {
        return victim_attack_found_best(item, best, best_hit_at, victim_attacked, victim_overlaps);
      }
    }
  } else {
    if (victim_attack_best_attempt_1(item, curr_at, &best, &best_hit_at, all_deltas)) {
      return victim_attack_found_best(item, best, best_hit_at, victim_attacked, victim_overlaps);
    }

    if (victim_attack_best_attempt_2(item, curr_at, &best, &best_hit_at, all_deltas)) {
      return victim_attack_found_best(item, best, best_hit_at, victim_attacked, victim_overlaps);
    }

    if (victim_attack_best_attempt_3(item, curr_at, &best, &best_hit_at, all_deltas)) {
      return victim_attack_found_best(item, best, best_hit_at, victim_attacked, victim_overlaps);
    }
  }

  if (attempt) {
    return false;
  }

  dbg("Target-attack-best: Last resorts");
  TRACE_AND_INDENT();

  //
  // Last resort where we just try and hit where we are pointing.
  //
  auto hit_at = curr_at + point(dx, dy);
  if (item) {
    dbg("Target-attack-best: Have equip item %s", item->to_short_string().c_str());
    TRACE_AND_INDENT();

    on_use(item);
    if (item->collision_check_and_handle_at(hit_at, &victim_attacked, &victim_overlaps)) {
      lunge(hit_at);
      if (victim_attacked) {
        dbg("Target-attack-best: Attacked with equip item");
        return true;
      }
      return false;
    }
  } else {
    dbg("Target-attack-best: No equip item");
    TRACE_AND_INDENT();

    if (collision_check_and_handle_at(hit_at, &victim_attacked, &victim_overlaps)) {
      lunge(hit_at);
      if (victim_attacked) {
        dbg("Target-attack-best: No equip item but attacked");
        return true;
      }
      return false;
    }
  }

  dbg("Target-attack-best: No target found");
  return false;
}

bool Thing::victim_attack_best(int equip, point *at)
{
  if (at) {
    dbg("Target-attack-best: Try to attack with equipped item at %s", at->to_string().c_str());
  } else {
    dbg("Target-attack-best: Try to attack with equipped item");
  }
  TRACE_AND_INDENT();

  int  dx, dy;
  auto item = equip_get(equip);
  if (! item) {
    auto d = dir_to_direction();
    dx     = d.x;
    dy     = d.y;
  } else {
    equip_use_offset_get(&dx, &dy, equip);
  }

  //
  // Always make the sword swishy noise.
  //
  if (item) {
    on_swing(item);
  }

  //
  // Axe hits all around
  //
  bool victim_attacked = false;
  bool victim_overlaps = false;

  if (item && item->collision_hit_360()) {
    std::vector< point > all_deltas = {
        point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1),
        point(-1, 0),  point(1, 0),  point(0, 1),  point(0, 0), // For spiderwebs
    };

    bool ret = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
      for (const auto &d : all_deltas) {
        point at = curr_at + d;
        dbg("Target-attack-best: Try to attack 360 with equipped item at %s", at.to_string().c_str());
        TRACE_AND_INDENT();
        if (victim_attack_best_at(equip, &at, attempt, victim_attacked, victim_overlaps)) {
          ret = true;
        }
        if (victim_attacked) {
          ret = true;
        }
      }
      if (ret) {
        break;
      }
    }
    return ret;
  }

  if (item && item->collision_hit_180()) {
    std::vector< point > all_deltas = {
        point(dx, dy), point(-dx, -dy), point(0, 0), // For spiderwebs
    };

    bool ret = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
      for (const auto &d : all_deltas) {
        point at = curr_at + d;
        dbg("Target-attack-best: Try to attack 180 adj with equipped item at %s", at.to_string().c_str());
        TRACE_AND_INDENT();
        if (victim_attack_best_at(equip, &at, attempt, victim_attacked, victim_overlaps)) {
          ret = true;
        }
        if (victim_attacked) {
          ret = true;
        }
      }
      if (ret) {
        break;
      }
    }
    return ret;
  }

  if (item && item->collision_hit_adj()) {
    std::vector< point > all_deltas;

    if ((dx == -1) && (dy == -1)) {
      all_deltas = {
          point(-1, -1), point(-1, 0), point(0, -1), point(0, 0), // For spiderwebs
      };
    } else if ((dx == 1) && (dy == 1)) {
      all_deltas = {
          point(1, 1), point(1, 0), point(0, 1), point(0, 0), // For spiderwebs
      };
    } else if ((dx == 1) && (dy == -1)) {
      all_deltas = {
          point(1, -1), point(1, 0), point(0, -1), point(0, 0), // For spiderwebs
      };
    } else if ((dx == -1) && (dy == 1)) {
      all_deltas = {
          point(-1, 1), point(-1, 0), point(0, 1), point(0, 0), // For spiderwebs
      };
    } else if ((dx == -1) && (dy == 0)) {
      all_deltas = {
          point(-1, 0), point(-1, -1), point(-1, 1), point(0, 0), // For spiderwebs
      };
    } else if ((dx == 1) && (dy == 0)) {
      all_deltas = {
          point(1, 0), point(1, -1), point(1, 1), point(0, 0), // For spiderwebs
      };
    } else if ((dx == 0) && (dy == -1)) {
      all_deltas = {
          point(0, -1), point(-1, -1), point(1, -1), point(0, 0), // For spiderwebs
      };
    } else if ((dx == 0) && (dy == 1)) {
      all_deltas = {
          point(0, 1), point(-1, 1), point(1, 1), point(0, 0), // For spiderwebs
      };
    }

    bool ret = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
      for (const auto &d : all_deltas) {
        point at = curr_at + d;
        dbg("Target-attack-best: Try to attack 180 adj with equipped item at %s", at.to_string().c_str());
        dbg("TARG %d,%d %d,%d", d.x, d.y, at.x, at.y);
        TRACE_AND_INDENT();
        if (victim_attack_best_at(equip, &at, attempt, victim_attacked, victim_overlaps)) {
          ret = true;
        }
        if (victim_attacked) {
          ret = true;
        }
      }
      if (ret) {
        break;
      }
    }
    return ret;
  }

  if (victim_attack_best_at(equip, at, 0 /* All attempts */, victim_attacked, victim_overlaps)) {
    return true;
  }

  return false;
}
