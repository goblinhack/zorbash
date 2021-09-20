//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <algorithm>
#include <set>

#include "my_sys.h"
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void Thing::dmap_modify_terrain_cost (point p, uint8_t *d)
{_
  int pref = *d;

  if (collision_obstacle(p)) {
    pref++;
  }

  std::vector<std::pair<Thingp, int> > possible;

  {
    static const std::vector<point> all_deltas = {
      point(-1, -1),
      point( 1, -1),
      point(-1,  1),
      point( 1,  1),
      point(0, 0),
      point(0, -1),
      point(-1, 0),
      point(1, 0),
      point(0, 1),
    };

    for (const auto& d : all_deltas) {
      auto x = p.x + d.x;
      auto y = p.y + d.y;

      if (will_avoid_monst(point(x, y))) {
        pref += DMAP_LESS_PREFERRED_TERRAIN;
      }
    }
  }

  if (is_hazardous_to_me(p)) {
    pref += DMAP_LESS_PREFERRED_TERRAIN;
  }

  if (pref > DMAP_MAX_LESS_PREFERRED_TERRAIN) {
    pref = DMAP_MAX_LESS_PREFERRED_TERRAIN;
  }

  *d = (uint8_t) pref;
}

uint8_t Thing::get_terrain_cost (point p)
{_
  uint8_t pref = 0;

  dmap_modify_terrain_cost(p, &pref);

  return (uint8_t) pref;
}

bool Thing::will_prefer_terrain (const Thingp itp)
{_
  auto me = tp();
  auto it = itp->tp();

  if (me->is_water_lover()) {
    if (it->is_shallow_water() || it->is_deep_water()) {
      return true;
    }
  }

  if (me->is_acid_lover()) {
    if (it->is_acid()) {
      return true;
    }
  }

  return false;
}
