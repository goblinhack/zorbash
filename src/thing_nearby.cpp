//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>
#include <set>

Thingp Thing::get_most_dangerous_adjacent_thing(void)
{
  std::vector< std::pair< Thingp, int > > possible;

  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1),
      point(-1, 0),  point(1, 0),  point(0, 1),  point(0, 0), // For spiderwebs
  };

  for (const auto &d : all_deltas) {
    auto x = mid_at.x + d.x;
    auto y = mid_at.y + d.y;

    point o(x, y);
    if (level->is_oob(o)) {
      continue;
    }

    if (! get(get_aip()->can_see_currently.can_see, o.x, o.y)) {
      continue;
    }

    FOR_ALL_THINGS_THAT_INTERACT(level, it, x, y)
    {
      if (it == this) {
        continue;
      }

      if (it->is_dead) {
        continue;
      }

      //
      // Treat as a threat so they attack
      //
      if (it->is_spiderweb()) {
        if (it->mid_at == mid_at) {
          possible.push_back(std::make_pair(it, 666));
          continue;
        }
      }

      if (! it->is_monst() && ! it->is_player()) {
        continue;
      }

      auto score = it->get_health();
      if (will_avoid_monst(point(x, y))) {
        score += it->get_health_max();
      }

      possible.push_back(std::make_pair(it, score));
    }
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

Thingp Thing::get_most_dangerous_visible_thing(void)
{
  std::vector< std::pair< Thingp, int > > possible;

  int d = ai_avoid_distance();

  for (auto dx = -d; dx <= d; dx++) {
    for (auto dy = -d; dy <= d; dy++) {
      point o(mid_at.x + dx, mid_at.y + dy);
      if (level->is_oob(o)) {
        continue;
      }

      if (! get(get_aip()->can_see_currently.can_see, o.x, o.y)) {
        continue;
      }

      FOR_ALL_THINGS_THAT_INTERACT(level, t, o.x, o.y)
      {
        if (t == this) {
          continue;
        }

        if (t->is_dead) {
          continue;
        }

        if (! t->is_monst() && ! t->is_player()) {
          continue;
        }

        auto score = t->get_health();

        //
        // If we're being engulfed, this is a serious threat!
        //
        if (t->mid_at == mid_at) {
          score += 100;
        }

        if (will_avoid_monst(o)) {
          score += t->get_health_max();
        }

        possible.push_back(std::make_pair(t, score));
        dbg("Potential danger: %s", t->to_string().c_str());
      }
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
  int d = ai_avoid_distance();

  for (auto dx = -d; dx <= d; dx++) {
    for (auto dy = -d; dy <= d; dy++) {
      point o(mid_at.x + dx, mid_at.y + dy);
      if (! dx && ! dy) {
        continue;
      }

      if (level->is_oob(o)) {
        continue;
      }

      if (! get(get_aip()->can_see_currently.can_see, o.x, o.y)) {
        continue;
      }

      FOR_ALL_THINGS_THAT_INTERACT(level, t, o.x, o.y)
      {
        if (t == this) {
          continue;
        }

        if (t->is_dead) {
          continue;
        }

        if (! t->is_monst() && ! t->is_player()) {
          continue;
        }

        if (t->possible_to_attack(this)) {
          return true;
        }
      }
      FOR_ALL_THINGS_END()
    }
  }
  return false;
}

bool Thing::any_adjacent_monst(void)
{
  static const std::vector< point > all_deltas = {
      point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, -1),
      point(-1, 0),  point(1, 0),  point(0, 1),  point(0, 0), // For spiderwebs
  };

  for (const auto &d : all_deltas) {
    auto x = mid_at.x + d.x;
    auto y = mid_at.y + d.y;

    point o(x, y);
    if (level->is_oob(o)) {
      continue;
    }

    if (! get(get_aip()->can_see_currently.can_see, o.x, o.y)) {
      continue;
    }

    FOR_ALL_THINGS_THAT_INTERACT(level, t, x, y)
    {
      if (t == this) {
        continue;
      }

      if (t->is_dead) {
        continue;
      }

      if (t->is_monst() || t->is_player()) {
        return true;
      }
    }
    FOR_ALL_THINGS_END()
  }

  return false;
}
