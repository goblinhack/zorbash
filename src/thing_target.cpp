//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

bool Thing::is_target_select(Thingp item)
{
  TRACE_NO_INDENT();

  if (game->state != Game::STATE_CHOOSING_TARGET) {
    msg("Choose a target to use %s at.", item->text_the().c_str());
  }

  game->change_state(Game::STATE_CHOOSING_TARGET, "choosing a target");
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
                                         std::vector< point > &all_deltas, AttackOptions *attack_options)
{
  bool found_best {};
  int  best_priority = -999;

  dbg2("Target-attack-best: Try to find something to attack at (%d,%d), attempt 1", at.x, at.y);
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
      TRACE_AND_INDENT();

      if (t->is_dead || t->is_dying) {
        dbg2("Target-attack-best: %s no dead or dying", t->to_short_string().c_str());
        continue;
      }

      if (same_mob(t) || same_leader_or_owner(t)) {
        dbg2("Target-attack-best: %s no same leader", t->to_short_string().c_str());
        continue;
      }

      if (t->is_wall()) {
        if (! attack_options->allow_hitting_walls) {
          dbg2("Target-attack-best: %s no not allowed to hit walls", t->to_short_string().c_str());
          continue;
        }
      }

      if (t->is_block_of_ice() || t->is_mob() || t->is_monst() || t->is_player()) {
        prio += danger_current_level(t);

        //
        // Make sure we prefer monsts over things like doors if there is a choice.
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

//
// The only difference here is that we allow the hitting of item
//
bool Thing::victim_attack_best_attempt_2(Thingp item, point at, Thingp *best, point *best_hit_at,
                                         std::vector< point > &all_deltas, AttackOptions *attack_options)
{
  bool found_best {};
  int  best_priority = -999;

  dbg2("Target-attack-best: Try to find something to attack at (%d,%d), attempt 2", at.x, at.y);
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
      TRACE_AND_INDENT();

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

      if (same_mob(t) || same_leader_or_owner(t)) {
        dbg2("Target-attack-best: %s no same leader", t->to_short_string().c_str());
        continue;
      }

      if (t->is_wall()) {
        if (! attack_options->allow_hitting_walls) {
          dbg2("Target-attack-best: %s no not allowed to hit walls", t->to_short_string().c_str());
          continue;
        }
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

//
// The difference here from the above is that we mostly allow hitting anything,
// including things like rock.
//
bool Thing::victim_attack_best_attempt_3(Thingp item, point at, Thingp *best, point *best_hit_at,
                                         std::vector< point > &all_deltas, AttackOptions *attack_options)
{
  bool found_best {};
  int  best_priority = -999;

  dbg2("Target-attack-best: Try to find something to attack at (%d,%d), attempt 3", at.x, at.y);
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
      TRACE_AND_INDENT();

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

      if (same_mob(t) || same_leader_or_owner(t)) {
        dbg2("Target-attack-best: %s no same leader", t->to_short_string().c_str());
        continue;
      }

      if (t->is_wall()) {
        if (! attack_options->allow_hitting_walls) {
          dbg2("Target-attack-best: %s no not allowed to hit walls", t->to_short_string().c_str());
          continue;
        }
      }

      if (can_eat(t)) {
        prio += t->nutrition_get();
        dbg2("Target-attack-best: %s monst prio %d eat", t->to_short_string().c_str(), prio);
      } else if (t->is_hittable()) {
        prio += danger_current_level(t);
        dbg2("Target-attack-best: %s monst prio %d hittable", t->to_short_string().c_str(), prio);
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

bool Thing::victim_attack_swing(int equip, Thingp best, point best_hit_at, AttackOptions *attack_options)
{
  dbg2("Target-attack-best: Best target to swing at %s", best_hit_at.to_string().c_str());
  TRACE_AND_INDENT();

  //
  // If attacking something like blood, then do a natural attack instead.
  //
  if (is_monst()) {
    if (best && can_eat(best)) {
      //
      // Eat attack; but only if it is dead if it is a monster.
      //
      if (is_dead) {
        dbg2("Target-attack-best: Dead monster");
        attack_options->used_as        = gfx_anim_use();
        attack_options->prefer_nat_att = true;
      } else {
        dbg2("Target-attack-best: Something I can eat");
        attack_options->used_as        = gfx_anim_use();
        attack_options->prefer_nat_att = true;
      }
    } else if (! level->is_monst(best_hit_at) && ! level->is_wall(best_hit_at) && ! level->is_door(best_hit_at) &&
               ! level->is_mob(best_hit_at)) {
      //
      // Prefer claws
      //
      if (level->player && (level->player->curr_at == best_hit_at)) {
        if (pcg_random_range(0, 100) < 10) {
          dbg2("Target-attack-best: Player, use claws randomly");
          attack_options->used_as        = gfx_anim_use();
          attack_options->prefer_nat_att = true;
        }
      } else {
        dbg2("Target-attack-best: No monsts at target location, prefer nat attack");
        attack_options->used_as        = gfx_anim_use();
        attack_options->prefer_nat_att = true;
      }
    }
  }

  auto use_anim = equip_use_anim(equip);
  if (! use_anim) {
    //
    // If no swing animation, then swing.
    //
    dbg2("Target-attack-best: No equipment use animation, so lunge");
    TRACE_AND_INDENT();

    if (attack_lunge()) {
      lunge(best_hit_at);
    }

    //
    // A monst only wielding a wand can have no swing anim
    //
    if (! attack_options->used_as.empty()) {
      auto use_anim = level->thing_new(attack_options->used_as, best_hit_at);
      use_anim->owner_set(this);
      equip_use_anim_set(use_anim, equip);
    }
  } else if (use_anim && (best_hit_at != use_anim->curr_at)) {
    //
    // Or, if there is a swing animation, don't create a duplicate
    //
    dbg2("Target-attack-best: Have equipment use animation");
    TRACE_AND_INDENT();

    //
    // A monst only wielding a wand can have no swing anim
    //
    if (! attack_options->used_as.empty()) {
      auto use_anim = level->thing_new(attack_options->used_as, best_hit_at);
      use_anim->owner_set(this);
      equip_use_anim_set(use_anim, equip);
    }
  }

  return true;
}

bool Thing::victim_attack_found_best(int equip, Thingp item, Thingp best, point best_hit_at,
                                     AttackOptions *attack_options)
{
  attack_options->victim_attacked = false;
  attack_options->victim_overlaps = false;

  if (best) {
    dbg2("Target-attack-best: Best target to hit is %s at %s", best->to_short_string().c_str(),
         best_hit_at.to_string().c_str());
  } else {
    dbg2("Target-attack-best: Best target to hit is at %s", best_hit_at.to_string().c_str());
  }
  TRACE_AND_INDENT();

  //
  // Swing the weapon
  //
  dbg2("Target-attack-best: Swing weapon?");
  TRACE_AND_INDENT();

  victim_attack_swing(equip, best, best_hit_at, attack_options);

  //
  // If carrying a weapon, but attacking food, then do not use the weapon.
  //
  if (attack_options->prefer_nat_att) {
    item = nullptr;
  }

  //
  // Try to attack
  //
  if (item) {
    dbg2("Target-attack-best: Try to attack with item");
    TRACE_AND_INDENT();

    if (best) {
      on_use(item, best);
    } else {
      on_use(item);
    }

    if (item->collision_check_and_handle_at(best_hit_at, attack_options)) {
      lunge(best_hit_at);
    }
  } else {
    dbg2("Target-attack-best: Try to attack with no item");
    TRACE_AND_INDENT();

    if (collision_check_and_handle_at(best_hit_at, attack_options)) {
      lunge(best_hit_at);
    }
  }
  return attack_options->victim_attacked;
}

bool Thing::victim_attack_choose_best(Thingp item, point at, Thingp *best, point *best_hit_at,
                                      AttackOptions *attack_options)
{
  std::vector< point > all_deltas = {point(0, 0)};

  if (victim_attack_best_attempt_1(item, at, best, best_hit_at, all_deltas, attack_options)) {
    return true;
  }

  if (victim_attack_best_attempt_2(item, at, best, best_hit_at, all_deltas, attack_options)) {
    return true;
  }

  if (victim_attack_best_attempt_3(item, at, best, best_hit_at, all_deltas, attack_options)) {
    return true;
  }

  return false;
}

bool Thing::victim_attack_best_at(int equip, AttackOptions *attack_options)
{
  if (attack_options->attack_at_set) {
    dbg("Target-attack-best-at: Try to attack with equipped item at %s",
        attack_options->attack_at.to_string().c_str());
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
  } else if (attack_options->attack_at_set) {
    dx = 0;
    dy = 0;
  } else {
    equip_use_offset_get(&dx, &dy, equip);
  }

  attack_options->victim_attacked = false;
  attack_options->victim_overlaps = false;

  dbg("Target-attack-best: Attack delta %d,%d", dx, dy);
  TRACE_AND_INDENT();

  //
  // Look in the chosen dir first for something to hit, then behind us.
  //
  std::vector< point > all_deltas = {
      point(dx, dy), point(-dx, -dy), point(-1, -1), point(1, -1), point(-1, 1), point(1, 1),
      point(0, -1),  point(-1, 0),    point(1, 0),   point(0, 1),  point(0, 0), // (0,0) for spiderwebs
  };

  //
  // If stuck in a web we can only hit the web
  //
  std::vector< point > local_only = {point(0, 0)};
  if (level->is_block_of_ice(curr_at) || level->is_spiderweb(curr_at)) {
    all_deltas = local_only;
  }

  //
  // If trapped in an engulfer, you can only attack locally
  //
  FOR_ALL_COLLISION_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t == this) {
      continue;
    }

    if (t->is_engulfer()) {
      all_deltas = local_only;
      break;
    }
  }
  FOR_ALL_THINGS_END();

  //
  // If we clicked on a target we must attack only there.
  // If we pressed space then the target is where we are at, so look around
  // for the best thing to hit.
  //
  if (attack_options->attack_at_set) {
    dbg("Target-attack-best: Attack only at location %s", attack_options->attack_at.to_string().c_str());
    auto                 delta      = attack_options->attack_at - curr_at;
    std::vector< point > local_only = {delta};

    all_deltas = local_only;
  }

  Thingp best = nullptr;
  point  best_hit_at;

  //
  // Look in the chosen dir first
  //
  if (attack_options->attack_at_set) {
    if (victim_attack_best_attempt_1(item, curr_at, &best, &best_hit_at, all_deltas, attack_options)) {
      return victim_attack_found_best(equip, item, best, best_hit_at, attack_options);
    }
  }

  if (dx || dy) {
    std::vector< point > all_deltas = {
        point(dx, dy),
    };
    if (victim_attack_best_attempt_1(item, curr_at, &best, &best_hit_at, all_deltas, attack_options)) {
      return victim_attack_found_best(equip, item, best, best_hit_at, attack_options);
    }
  }

  if (attack_options->attempt) {
    if (attack_options->attempt == 1) {
      if (victim_attack_best_attempt_1(item, curr_at, &best, &best_hit_at, all_deltas, attack_options)) {
        return victim_attack_found_best(equip, item, best, best_hit_at, attack_options);
      }
    }
    if (attack_options->attempt == 2) {
      if (victim_attack_best_attempt_2(item, curr_at, &best, &best_hit_at, all_deltas, attack_options)) {
        return victim_attack_found_best(equip, item, best, best_hit_at, attack_options);
      }
    }
    if (attack_options->attempt == 3) {
      if (victim_attack_best_attempt_3(item, curr_at, &best, &best_hit_at, all_deltas, attack_options)) {
        return victim_attack_found_best(equip, item, best, best_hit_at, attack_options);
      }
    }
  } else {
    if (victim_attack_best_attempt_1(item, curr_at, &best, &best_hit_at, all_deltas, attack_options)) {
      return victim_attack_found_best(equip, item, best, best_hit_at, attack_options);
    }

    if (victim_attack_best_attempt_2(item, curr_at, &best, &best_hit_at, all_deltas, attack_options)) {
      return victim_attack_found_best(equip, item, best, best_hit_at, attack_options);
    }

    if (victim_attack_best_attempt_3(item, curr_at, &best, &best_hit_at, all_deltas, attack_options)) {
      return victim_attack_found_best(equip, item, best, best_hit_at, attack_options);
    }
  }

  if (attack_options->attempt) {
    return false;
  }

  //
  // If we clicked on a specific bit to hit, do not fallback to last resorts
  // as we end up swinging twice.
  //
  if (attack_options->attack_at_set) {
    return false;
  }

  //
  // Last resort where we just try and hit where we are pointing.
  //
  if (is_player()) {
    dbg("Target-attack-best: Last resorts");
    TRACE_AND_INDENT();

    auto hit_at = curr_at + point(dx, dy);
    victim_attack_found_best(equip, item, nullptr, hit_at, attack_options);
    return attack_options->victim_attacked;
  }

  return false;
}

bool Thing::victim_attack_best_(int equip, AttackOptions *attack_options)
{
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
  // Are we allowed to target walls?
  //
  if (attack_options->attack_at_set) {
    if (level->is_obs_wall_or_door(attack_options->attack_at)) {
      attack_options->allow_hitting_walls = true;
    }
  }

  //
  // Axe hits all around
  //
  if (item && item->collision_hit_360()) {
    std::vector< point > all_deltas = {
        point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1),
        point(-1, 0),  point(1, 0),  point(0, 1),  point(0, 0), // (0,0) for spiderwebs
    };

    bool ret = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
      for (const auto &d : all_deltas) {
        point at = curr_at + d;
        dbg("Target-attack-best: Try to attack 360 with equipped item at %s", at.to_string().c_str());
        TRACE_AND_INDENT();

        attack_options->attempt       = attempt;
        attack_options->attack_at_set = true;
        attack_options->attack_at     = at;

        if (victim_attack_best_at(equip, attack_options)) {
          ret = true;
        }
        if (attack_options->victim_attacked) {
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
        point(dx, dy), point(-dx, -dy), point(0, 0), // (0,0) for spiderwebs
    };

    bool ret = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
      for (const auto &d : all_deltas) {
        point at = curr_at + d;
        dbg("Target-attack-best: Try to attack 180 adj with equipped item at %s", at.to_string().c_str());
        TRACE_AND_INDENT();

        attack_options->attempt       = attempt;
        attack_options->attack_at_set = true;
        attack_options->attack_at     = at;

        if (victim_attack_best_at(equip, attack_options)) {
          ret = true;
        }
        if (attack_options->victim_attacked) {
          ret = true;
        }
      }
      if (ret) {
        break;
      }
    }
    return ret;
  }

  if (item && item->collision_hit_two_tiles_ahead()) {
    std::vector< point > all_deltas = {
        point(dx, dy), point(dx * 2, dy * 2), point(0, 0), // (0,0) for spiderwebs
    };

    bool ret = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
      for (const auto &d : all_deltas) {
        point at = curr_at + d;
        dbg("Target-attack-best: Try to attack two ahead adj (%d,%d) with equipped item at %s", d.x, d.y,
            at.to_string().c_str());
        TRACE_AND_INDENT();

        attack_options->attempt       = attempt;
        attack_options->attack_at_set = true;
        attack_options->attack_at     = at;

        if (victim_attack_best_at(equip, attack_options)) {
          ret = true;
        }
        if (attack_options->victim_attacked) {
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
          point(-1, -1), point(-1, 0), point(0, -1), point(0, 0), // (0, 0) for spiderwebs
      };
    } else if ((dx == 1) && (dy == 1)) {
      all_deltas = {
          point(1, 1),
          point(1, 0),
          point(0, 1),
          point(0, 0),
      };
    } else if ((dx == 1) && (dy == -1)) {
      all_deltas = {
          point(1, -1),
          point(1, 0),
          point(0, -1),
          point(0, 0),
      };
    } else if ((dx == -1) && (dy == 1)) {
      all_deltas = {
          point(-1, 1),
          point(-1, 0),
          point(0, 1),
          point(0, 0),
      };
    } else if ((dx == -1) && (dy == 0)) {
      all_deltas = {
          point(-1, 0),
          point(-1, -1),
          point(-1, 1),
          point(0, 0),
      };
    } else if ((dx == 1) && (dy == 0)) {
      all_deltas = {
          point(1, 0),
          point(1, -1),
          point(1, 1),
          point(0, 0),
      };
    } else if ((dx == 0) && (dy == -1)) {
      all_deltas = {
          point(0, -1),
          point(-1, -1),
          point(1, -1),
          point(0, 0),
      };
    } else if ((dx == 0) && (dy == 1)) {
      all_deltas = {
          point(0, 1),
          point(-1, 1),
          point(1, 1),
          point(0, 0),
      };
    }

    bool ret = false;
    for (int attempt = 1; attempt <= 3; attempt++) {
      for (const auto &d : all_deltas) {
        point at = curr_at + d;
        dbg("Target-attack-best: Try to attack 180 adj with equipped item at %s", at.to_string().c_str());
        TRACE_AND_INDENT();

        attack_options->attempt       = attempt;
        attack_options->attack_at_set = true;
        attack_options->attack_at     = at;
        if (victim_attack_best_at(equip, attack_options)) {
          ret = true;
        }
        if (attack_options->victim_attacked) {
          ret = true;
        }
      }
      if (ret) {
        break;
      }
    }
    return ret;
  }

  return victim_attack_best_at(equip, attack_options);
}

bool Thing::victim_attack_best(int equip, AttackOptions *attack_options)
{
  if (attack_options->attack_at_set) {
    dbg("Target-attack-best: Try to attack with equipped item at %s", attack_options->attack_at.to_string().c_str());
  } else {
    dbg("Target-attack-best: Try to attack with equipped item");
  }
  TRACE_AND_INDENT();

  //
  // Save the direction as it can change if attacking surrounding things
  //
  auto old_dir = dir;

  auto ret = victim_attack_best_(equip, attack_options);

  dir = old_dir;

  return ret;
}
