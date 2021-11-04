//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

std::vector< Lightp > &Thing::get_light(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->light);
  } else {
    static std::vector< Lightp > no_light;
    return no_light;
  }
}

void Thing::new_light(point offset, int strength, color col, int fbo)
{
  TRACE_AND_INDENT();
  new_infop();
  auto l = light_new(this, offset, strength, col, fbo);
  get_infop()->light.push_back(l);
  get_infop()->light_strength = strength;
  get_infop()->light_col      = col;
}

void Thing::new_light(point offset, int strength)
{
  TRACE_AND_INDENT();
  new_infop();
  auto l = light_new(this, offset, strength);
  get_infop()->light.push_back(l);
  get_infop()->light_strength = strength;
}

void Thing::delete_lights(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    for (auto &l : get_infop()->light) {
      delete l;
    }
    get_infop()->light.resize(0);
  }
}

void Thing::init_lights(void)
{
  TRACE_AND_INDENT();
  if (unlikely(is_player())) {
    if (level->player && (level->player != this)) {
      DIE("Player exists in multiple places on map, %d,%d and %d,%d", level->player->mid_at.x,
          level->player->mid_at.y, mid_at.x, mid_at.y);
      return;
    }
    level->player = this;

    //
    // keep the light strength half the tiles drawn or we get artifacts
    // at the edges of the fbo
    //
    color col = WHITE;

    int strength = get_initial_light_strength();
    int d1       = 1;
    int d2       = 2;

    //
    // This is a raycast only light to mark things as visible
    //
    new_light(point(0, 0), strength);

    new_light(point(0, 0), strength, col, FBO_FULLMAP_LIGHT);
    new_light(point(0, 0), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(0, 0), 3, col, FBO_SMALL_POINT_LIGHTS);

    new_light(point(-d1, -d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(d1, -d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(-d1, d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(d1, d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);

    new_light(point(-d2, -d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(d2, -d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(-d2, d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(d2, d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);

    new_light(point(-d1, -d2), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(d1, -d2), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(-d1, d2), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(d1, d2), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);

    {
      d1 = 3;
      d2 = 5;

      new_light(point(-d1, -d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(d1, -d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(-d1, d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(d1, d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);

      new_light(point(-d2, -d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(d2, -d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(-d2, d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(d2, d1), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);

      new_light(point(-d1, -d2), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(d1, -d2), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(-d1, d2), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
      new_light(point(d1, d2), strength, col, FBO_PLAYER_VISIBLE_LIGHTING);
    }

    has_light = true;
    dbg("Player created");
  } else {
    if (unlikely(get_light_strength())) {
      std::string l = light_color();
      if (l.empty()) {
        l = "white";
      }
      bool add_light = true;
      if (is_lava()) {
        //                if (random_range(0, 100) < 80) {
        add_light = true;
        //                }
      }
      if (add_light) {
        color c = string2color(l);
        new_light(point(0, 0), get_light_strength(), c, FBO_PLAYER_VISIBLE_LIGHTING);
        has_light = true;
      }
    }
  }
}

void Thing::light_update_strength(void)
{
  TRACE_AND_INDENT();
  auto str = get_light_strength();
  for (auto l : get_light()) {
    if (l->ray_cast_only) {
      continue;
    }

    if (str != l->prev_strength) {
      l->update(str);
    }
  }
}
