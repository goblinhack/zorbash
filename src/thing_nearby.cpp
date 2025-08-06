//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

Thingp Thing::most_dangerous_adjacent_thing(void)
{
  TRACE_NO_INDENT();

  std::vector< std::pair< Thingp, int > > possible;

  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1),
      point(-1, 0),  point(1, 0),  point(0, 1),  point(0, 0), // For spiderwebs
  };

  if (! maybe_aip()) {
    return nullptr;
  }

  for (const auto &d : all_deltas) {
    auto x = curr_at.x + d.x;
    auto y = curr_at.y + d.y;

    point o(x, y);
    if (level->is_oob(o)) {
      continue;
    }

    if (! get(aip()->can_see_currently.can_see, o.x, o.y)) {
      continue;
    }

    TRACE_NO_INDENT();
    FOR_ALL_THINGS_THAT_INTERACT(level, t, x, y)
    {
      if (t == this) {
        continue;
      }

      if (t->is_dead) {
        continue;
      }

      if (! can_detect(t)) {
        continue;
      }

      //
      // Treat as a threat so they attack
      //
      if (! is_immune_to_spiderwebs()) {
        if (t->is_spiderweb()) {
          if (t->curr_at == curr_at) {
            possible.push_back(std::make_pair(t, 666));
            continue;
          }
        }
      }

      if (! t->is_mob() && ! t->is_monst() && ! t->is_player()) {
        continue;
      }

      auto score = t->health();
      if (! will_avoid_monst(t)) {
        continue;
      }

      score += t->health_max();
      possible.push_back(std::make_pair(t, score));
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }

  if (! possible.size()) {
    return nullptr;
  }

  sort(possible.begin(), possible.end(),
       [](const std::pair< Thingp, int > &a, const std::pair< Thingp, int > &b) -> bool {
         return a.second > b.second;
       });

  return possible[ 0 ].first;
}

Thingp Thing::most_dangerous_visible_thing(void)
{
  std::vector< std::pair< Thingp, int > > possible;

  if (! maybe_aip()) {
    return nullptr;
  }

  float d = distance_vision_get();

  for (auto dx = -d; dx <= d; dx++) {
    for (auto dy = -d; dy <= d; dy++) {
      point o(curr_at.x + dx, curr_at.y + dy);
      if (level->is_oob(o)) {
        continue;
      }

      if (! get(aip()->can_see_currently.can_see, o.x, o.y)) {
        continue;
      }

      TRACE_NO_INDENT();
      FOR_ALL_THINGS_THAT_INTERACT(level, t, o.x, o.y)
      {
        if (t == this) {
          continue;
        }

        if (t->is_dead) {
          continue;
        }

        if (! can_detect(t)) {
          continue;
        }

        if (! t->is_monst() && ! t->is_player()) {
          continue;
        }

        if (! is_intelligent()) {
          //
          // Dumb monsters
          //
          if (t->is_mimic() && t->is_sleeping) {
            //
            // Allow intelligent monsts to detect sleeping mimics?
            //
            continue;
          }
        }

        auto score = t->health();

        //
        // If we're being engulfed, this is a serious threat!
        //
        if (t->curr_at == curr_at) {
          score += 100;
        }

        if (! will_avoid_monst(t)) {
          continue;
        }

        score += t->health_max();
        possible.push_back(std::make_pair(t, score));
        dbg("Potential danger: %s", t->to_short_string().c_str());
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }

  if (! possible.size()) {
    return nullptr;
  }

  sort(possible.begin(), possible.end(),
       [](const std::pair< Thingp, int > &a, const std::pair< Thingp, int > &b) -> bool {
         return a.second > b.second;
       });

  return possible[ 0 ].first;
}

bool Thing::any_unfriendly_monst_visible(void)
{
  if (! maybe_aip()) {
    return false;
  }

  float d = distance_vision_get();

  for (auto dx = -d; dx <= d; dx++) {
    for (auto dy = -d; dy <= d; dy++) {
      point o(curr_at.x + dx, curr_at.y + dy);
      if (! dx && ! dy) {
        continue;
      }

      if (level->is_oob(o)) {
        continue;
      }

      if (! get(aip()->can_see_currently.can_see, o.x, o.y)) {
        continue;
      }

      TRACE_NO_INDENT();
      FOR_ALL_THINGS_THAT_INTERACT(level, t, o.x, o.y)
      {
        if (t == this) {
          continue;
        }

        if (t->is_dead) {
          continue;
        }

        if (! can_detect(t)) {
          continue;
        }

        if (! t->is_monst() && ! t->is_player()) {
          continue;
        }

        if (t->possible_to_attack(this)) {
          return true;
        }
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }
  return false;
}

bool Thing::any_adjacent_monst(void)
{
  if (! maybe_aip()) {
    return false;
  }

  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1),
      point(-1, 0),  point(1, 0),  point(0, 1),  point(0, 0), // (0,0) for spiderwebs
  };

  for (const auto &d : all_deltas) {
    auto x = curr_at.x + d.x;
    auto y = curr_at.y + d.y;

    point o(x, y);
    if (level->is_oob(o)) {
      continue;
    }

    if (! get(aip()->can_see_currently.can_see, o.x, o.y)) {
      continue;
    }

    TRACE_NO_INDENT();
    FOR_ALL_THINGS_THAT_INTERACT(level, t, x, y)
    {
      if (t == this) {
        continue;
      }

      if (t->is_dead) {
        continue;
      }

      if (! can_detect(t)) {
        continue;
      }

      if (t->is_monst() || t->is_player()) {
        return true;
      }
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }

  return false;
}

Thingp Thing::best_visible_target_get(void)
{
  if (! maybe_aip()) {
    return nullptr;
  }

  std::vector< std::pair< Thingp, int > > possible;

  float d = distance_vision_get();

  for (auto dx = -d; dx <= d; dx++) {
    for (auto dy = -d; dy <= d; dy++) {
      point o(curr_at.x + dx, curr_at.y + dy);
      if (level->is_oob(o)) {
        continue;
      }

      if (! get(aip()->can_see_currently.can_see, o.x, o.y)) {
        continue;
      }

      TRACE_NO_INDENT();
      FOR_ALL_THINGS_THAT_INTERACT(level, t, o.x, o.y)
      {
        if (t == this) {
          continue;
        }

        if (t->is_dead) {
          continue;
        }

        if (! can_detect(t)) {
          continue;
        }

        if (! t->is_monst() && ! t->is_player()) {
          continue;
        }

        if (! t->possible_to_attack(this)) {
          continue;
        }

        //
        // If no clear shot, then ignore
        //
        if (in_the_way_for_shooting(curr_at, t->curr_at, 1).size()) {
          continue;
        }

        auto score = t->health();

        if (distance(t->curr_at, curr_at) < distance_avoid_get()) {
          score += 100;
        }

        //
        // If we're being engulfed, this is a serious threat!
        //
        if (t->curr_at == curr_at) {
          score += 100;
        }

        if (will_avoid_monst(t)) {
          score += 100;
        }

        score += t->health_max();
        possible.push_back(std::make_pair(t, score));
        dbg("Potential target: %s", t->to_short_string().c_str());
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }

  if (! possible.size()) {
    return nullptr;
  }

  sort(possible.begin(), possible.end(),
       [](const std::pair< Thingp, int > &a, const std::pair< Thingp, int > &b) -> bool {
         return a.second > b.second;
       });

  return possible[ 0 ].first;
}

bool Thing::is_adjacent(const Thingp it)
{
  auto dx = abs(curr_at.x - it->curr_at.x);
  auto dy = abs(curr_at.y - it->curr_at.y);
  return (dx <= 1) && (dy <= 1);
}
