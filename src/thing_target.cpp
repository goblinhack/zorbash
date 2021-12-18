//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::target_select(Thingp what)
{
  TRACE_AND_INDENT();
  if (game->state != Game::STATE_CHOOSING_TARGET) {
    TOPCON("Choose a target to use %s at.", what->text_the().c_str());
  }

  game->change_state(Game::STATE_CHOOSING_TARGET);
  level->cursor_recreate();
  level->cursor->visible();
  level->describe(what);

  return true;
}

//
// Find the best thing to attack. Look at our current direction and if nothing
// in that path, look around for something else.
//
bool Thing::target_attack_best(int equip)
{
  TRACE_AND_INDENT();
  dbg("Try to attack with equpped item");
  TRACE_AND_INDENT();

  int  dx, dy;
  auto item = get_equip(equip);
  if (! item) {
    auto d = dir_to_direction();
    dx     = d.x;
    dy     = d.y;
  } else {
    get_equip_use_offset(&dx, &dy, equip);
  }

  bool target_attacked = false;
  bool target_overlaps = false;
  auto hit_at          = curr_at + point(dx, dy);

  dbg("Attack at %d,%d delta %d,%d", hit_at.x, hit_at.y, dx, dy);
  TRACE_AND_INDENT();

  //
  // Lunge at the target
  //
  decr_stamina();

  if (item) {
    dbg("Have equip item %s", item->to_short_string().c_str());
    TRACE_AND_INDENT();
    on_use(item);
    if (item->collision_check_and_handle_at(hit_at, &target_attacked, &target_overlaps)) {
      lunge(hit_at);
      if (target_attacked) {
        dbg("Attacked with equip item");
        return true;
      }
      return false;
    }
  } else {
    dbg("No equip item");
    TRACE_AND_INDENT();
    if (collision_check_and_handle_at(hit_at, &target_attacked, &target_overlaps)) {
      lunge(hit_at);
      if (target_attacked) {
        dbg("No equip item but attacked");
        return true;
      }
      return false;
    }
  }

  //
  // We didn't hit anything. See if there's something else to hit.
  //
  // Look in the chosen dir first, then behind us.
  //
  static std::vector< point > all_deltas = {
      point(dx, dy), point(-dx, -dy), point(-1, -1), point(1, -1), point(-1, 1), point(1, 1),
      point(0, -1),  point(-1, 0),    point(1, 0),   point(0, 1),  point(0, 0), // For spiderwebs
  };

  bool   found_best {};
  point  best_hit_at;
  int    best_priority = -999;
  Thingp best          = nullptr;

  dbg("Try to find something to attack, attempt 1");
  for (const auto &d : all_deltas) {
    auto hit_at = curr_at + point(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;

      //
      // Get the most important thing to hit.
      //
      if (! possible_to_attack(t)) {
        continue;
      }

      if (t->is_dead || t->is_dying) {
        continue;
      } else if (t->is_monst()) {
        prio = t->collision_hit_priority() + get_danger_current_level(t);

        //
        // Make sure we prefer monsts over things like doors if there is
        // a choice.
        //
        prio += 100;
      } else {
        continue;
      }

      if (prio > best_priority) {
        best_priority = prio;
        best_hit_at   = hit_at;
        best          = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    dbg("Best target to hit is %s", best->to_string().c_str());
    if (item) {
      if (item->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    } else {
      if (collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    }
  }

  //
  // Try again but include doors
  //
  found_best    = false;
  best_priority = -999;

  dbg("Try to find something to attack, attempt 2");
  for (const auto &d : all_deltas) {
    auto hit_at = curr_at + point(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;

      //
      // Get the most important thing to hit.
      //
      if (! possible_to_attack(t)) {
        continue;
      }

      if (t->is_dead || t->is_dying) {
        continue;
      } else if (t->is_door()) {
        prio = t->collision_hit_priority();
      } else {
        continue;
      }

      //
      // If being digested, this is high priority...
      //
      if (t->curr_at == curr_at) {
        prio *= 100;
      }

      if (prio > best_priority) {
        best_priority = prio;
        best_hit_at   = hit_at;
        best          = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    dbg("Best target (2nd try) to hit is %s", best->to_string().c_str());
    if (item) {
      if (item->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    } else {
      if (collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    }
  }

  //
  // Try again for anything we might want to hit.
  //
  found_best    = false;
  best_priority = -999;

  dbg("Try to find something to attack, attempt 3");
  for (const auto &d : all_deltas) {
    auto hit_at = curr_at + point(d.x, d.y);

    //
    // Find the alternative best thing to hit
    //
    FOR_ALL_COLLISION_THINGS(level, t, hit_at.x, hit_at.y)
    {
      int prio;

      //
      // Get the most important thing to hit.
      //
      if (! possible_to_attack(t)) {
        continue;
      }

      if (t->is_dead || t->is_dying) {
        continue;
      } else if (t->is_hittable()) {
        prio = t->collision_hit_priority() + get_danger_current_level(t);
      } else {
        continue;
      }

      if (prio > best_priority) {
        best_priority = prio;
        best_hit_at   = hit_at;
        best          = t;
        found_best    = true;
      }
    }
    FOR_ALL_THINGS_END();
  }

  if (found_best) {
    target_attacked = false;
    target_overlaps = false;

    dbg("Best target (3rd try) to hit is %s", best->to_string().c_str());
    if (item) {
      if (item->collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    } else {
      if (collision_check_and_handle_at(best_hit_at, &target_attacked, &target_overlaps)) {
        lunge(best_hit_at);
        return true;
      }
    }
  }

  return false;
}
