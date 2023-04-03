//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::dmap_modify_terrain_cost(point p, uint8_t *d, bool include_monst, bool include_disliked)
{
  int pref = *d;

  if (is_hated_by_me(p)) {
    *d = DMAP_IS_WALL;
    return;
  }

  std::vector< std::pair< Thingp, int > > possible;

  if (include_monst) {
    static const std::vector< point > all_deltas = {
        point(-1, -1), point(1, -1), point(-1, 1), point(1, 1), point(0, 0),
        point(0, -1),  point(-1, 0), point(1, 0),  point(0, 1),
    };

    for (const auto &d : all_deltas) {
      auto x = p.x + d.x;
      auto y = p.y + d.y;

      if (will_avoid_monst(point(x, y))) {
        pref += DMAP_LESS_PREFERRED_TERRAIN;
        // dbg("Avoid monst, terrain cost now %d", pref);
      }
    }
  }

  if (include_disliked) {
    if (is_disliked_by_me(p)) {
      pref += DMAP_LESS_PREFERRED_TERRAIN / 2;
      // dbg("Location avoid, terrain cost now %d", pref);
    }
  }

  if (pref > DMAP_MAX_LESS_PREFERRED_TERRAIN) {
    pref = DMAP_MAX_LESS_PREFERRED_TERRAIN;
  }

  *d = (uint8_t) pref;
}

uint8_t Thing::terrain_cost_get(point p)
{
  uint8_t pref = 0;
  dmap_modify_terrain_cost(p, &pref, true, true);
  return (uint8_t) pref;
}

bool Thing::will_prefer_terrain(const Thingp itp)
{
  TRACE_NO_INDENT();
  auto me = tp();
  auto it = itp->tp();

  if (me->is_immune_to_water() || me->is_able_to_swim()) {
    if (it->is_shallow_water() || it->is_deep_water()) {
      return true;
    }
  }

  if (me->is_immune_to_acid()) {
    if (it->is_acid()) {
      return true;
    }
  }

  if (me->is_immune_to_fire()) {
    if (it->is_fire() || it->is_lava()) {
      return true;
    }
  }

  return false;
}
