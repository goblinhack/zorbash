//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

std::vector< Lightp > &Thing::get_light(void)
{
  TRACE_NO_INDENT();

  //
  // Faster to avoid the infop API as this is called a lot
  //
  if (_infop) {
    return (_infop->light);
  }
  static std::vector< Lightp > no_light;
  return no_light;
}

void Thing::new_light(point offset, int light_power, float scale, color col, int fbo)
{
  TRACE_NO_INDENT();
  new_infop();
  auto l = light_new(this, offset, light_power, scale, col, fbo);
  get_infop()->light.push_back(l);
  get_infop()->light_power = light_power;
  get_infop()->light_col   = col;
}

void Thing::new_light(point offset, int light_power)
{
  TRACE_NO_INDENT();
  new_infop();
  auto l = light_new(this, offset, light_power);
  get_infop()->light.push_back(l);
  get_infop()->light_power = light_power;
}

void Thing::delete_lights(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    verify(MTYPE_INFOP, maybe_infop());
    for (auto &l : get_infop()->light) {
      delete l;
    }
    get_infop()->light.resize(0);
  }
}

void Thing::init_lights(void)
{
  TRACE_NO_INDENT();
  if (unlikely(is_player())) {
    if (level->player && (level->player != this)) {
      DIE("Player exists in multiple places on map, %d,%d and %d,%d", level->player->curr_at.x,
          level->player->curr_at.y, curr_at.x, curr_at.y);
      return;
    }
    level->player = this;

    //
    // keep the light light_power half the tiles drawn or we get artifacts
    // at the edges of the fbo
    //
    color col = WHITE;

    int light_power = get_initial_light_power();

    //
    // This is a raycast only light to mark things as visible
    //
    float scale = 1.0;
    new_light(point(0, 0), light_power);
    new_light(point(0, 0), light_power, scale, col, FBO_FULLMAP_LIGHT);
    new_light(point(0, 0), light_power, scale, col, FBO_PLAYER_VISIBLE_LIGHTING);
    new_light(point(0, 0), 4, scale, col, FBO_SMALL_POINT_LIGHTS);

    has_light = true;
    dbg("Player created");
  } else {
    if (unlikely(get_light_power())) {
      std::string l = light_color();
      if (l.empty()) {
        l = "white";
      }
      color c = string2color(l);
      new_light(point(0, 0), get_light_power(), 1.0, c, FBO_PLAYER_VISIBLE_LIGHTING);
      has_light = true;
    }
  }
}

void Thing::light_update_power(void)
{
  TRACE_NO_INDENT();
  float light_power_new = get_light_power();
  if (! light_power_new) {
    light_power_new = 1;
  }

  for (auto l : get_light()) {
    if (l->ray_cast_only) {
      continue;
    }

    float light_scale_factor = light_power_new / (float) l->light_power_orig;
    if (! light_scale_factor) {
      light_scale_factor = 0.1;
    }

    l->update_light_scale(light_scale_factor);
  }
}
