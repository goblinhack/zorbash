//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

std::vector< Lightp > &Thing::light_get(void)
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

void Thing::new_light(point offset, int light_power, int delta, color col, int fbo)
{
  TRACE_NO_INDENT();
  new_infop();
  auto l = light_new(this, offset, light_power, delta, col, fbo);
  infop()->light.push_back(l);
  infop()->light_power = light_power;
  infop()->light_col   = col;
}

void Thing::new_light(point offset, int light_power)
{
  TRACE_NO_INDENT();
  new_infop();
  auto l = light_new(this, offset, light_power);
  infop()->light.push_back(l);
  infop()->light_power = light_power;
}

void Thing::delete_lights(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    verify(MTYPE_INFOP, maybe_infop());
    for (auto &l : infop()->light) {
      delete l;
    }
    infop()->light.resize(0);
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

    int light_power = initial_light_power_get();

    //
    // This is a raycast only light to mark things as visible
    //
    float alpha_scale = 1.0;

    new_light(point(0, 0), light_power);
    new_light(point(0, 0), light_power, 0, col, FBO_FULLMAP_LIGHT);
    new_light(point(0, 0), light_power, 0, col, FBO_PLAYER_VISIBLE_LIGHTING);

    //
    // Helps when the light is really low. Gives some local intensity.
    //
    new_light(point(0, 0), 2, 1, col, FBO_SMALL_POINT_LIGHTS);

    alpha_scale = 0.75;
    col.a       = (int) (255.0 * alpha_scale);
    new_light(point(0, 0), light_power, 0, col, FBO_PLAYER_VISIBLE_LIGHTING);

    alpha_scale = 0.5;
    col.a       = (int) (255.0 * alpha_scale);
    new_light(point(0, 0), light_power, 1, col, FBO_PLAYER_VISIBLE_LIGHTING);

    alpha_scale = 0.2;
    col.a       = (int) (255.0 * alpha_scale);
    new_light(point(0, 0), light_power, 2, col, FBO_PLAYER_VISIBLE_LIGHTING);

    alpha_scale = 0.1;
    col.a       = (int) (255.0 * alpha_scale);
    new_light(point(0, 0), light_power, 3, col, FBO_PLAYER_VISIBLE_LIGHTING);

    alpha_scale = 0.05;
    col.a       = (int) (255.0 * alpha_scale);
    new_light(point(0, 0), light_power, 4, col, FBO_PLAYER_VISIBLE_LIGHTING);

    has_light = true;
    dbg("Player created");
  } else {
    if (unlikely(initial_light_power_get())) {
      std::string l = light_color();
      if (l.empty()) {
        l = "white";
      }
      color c = string2color(l);
      new_light(point(0, 0), initial_light_power_get(), 1, c, FBO_PLAYER_VISIBLE_LIGHTING);
      has_light = true;
    }
  }
}

void Thing::light_scale_update(void)
{
  TRACE_NO_INDENT();
  float light_power_new = light_power_get();
  if (! light_power_new) {
    light_power_new = 1;
  }

  for (auto l : light_get()) {
    if (l->ray_cast_only) {
      continue;
    }

    if (l->fbo == FBO_SMALL_POINT_LIGHTS) {
      continue;
    }

    float light_scale_factor = light_power_new / (float) l->light_power_orig;
    if (! light_scale_factor) {
      light_scale_factor = 0.1;
    }

    l->light_scale_update(light_scale_factor);
  }
}

int Thing::light_power_update(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return initial_light_power_get();
  }

  uint8_t light_power = infop()->light_power;

  if (! light_power) {
    light_power = initial_light_power_get();
  }

  if (is_player()) {
    light_power = 0;
  }

  light_power_update_including_torch_effect(light_power);
  infop()->light_power = light_power;

  light_scale_update();
  return light_power;
}

////////////////////////////////////////////////////////////////////////////
// prev_light_power
////////////////////////////////////////////////////////////////////////////
int Thing::prev_light_power_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->prev_light_power);
  } else {
    return 0;
  }
}

int Thing::prev_light_power_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power = v);
}

int Thing::prev_light_power_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power -= v);
}

int Thing::prev_light_power_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power += v);
}

int Thing::prev_light_power_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power--);
}

int Thing::prev_light_power_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power++);
}

////////////////////////////////////////////////////////////////////////////
// light_power
////////////////////////////////////////////////////////////////////////////
int Thing::initial_light_power_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->light_power());
}

int Thing::light_power_get(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return initial_light_power_get();
  }

  uint8_t light_power = infop()->light_power;

  if (is_player()) {
    light_power = 0;
  }

  light_power_including_torch_effect_get(light_power);
  infop()->light_power = light_power;

  return light_power;
}

int Thing::light_power_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power = v);
}

int Thing::light_power_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power -= v);
}

int Thing::light_power_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power += v);
}

int Thing::light_power_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power--);
}

int Thing::light_power_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power++);
}
