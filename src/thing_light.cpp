//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
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

void Thing::new_light(point offset, int light_dist, color col, int fbo)
{
  TRACE_NO_INDENT();
  new_infop();
  auto l = light_new(this, offset, light_dist, col, fbo);
  infop()->light.push_back(l);
  infop()->light_dist = light_dist;
  infop()->light_col  = col;
}

void Thing::new_light(point offset, int light_dist)
{
  TRACE_NO_INDENT();
  new_infop();
  auto l = light_new(this, offset, light_dist);
  infop()->light.push_back(l);
  infop()->light_dist = light_dist;
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
    // keep the light light_dist half the tiles drawn or we get artifacts
    // at the edges of the fbo
    //
    color col = WHITE;

    int light_dist = initial_light_dist_get() * TILE_WIDTH;

    //
    // This is a raycast only light to mark things as visible
    //
    new_light(point(0, 0), light_dist);

    //
    // This is the light to show areas we have been
    //
    new_light(point(0, 0), light_dist, col, FBO_PIXELART_FULLMAP_LIGHT);

    //
    // And this is the player visible light; this diminishes according
    // to the number of torch charges.
    //
    new_light(point(0, 0), light_dist, col, FBO_PLAYER_VISIBLE_LIGHTING);

    //
    // This small glow around the player is always present, even in low
    // lighting and allows you to see a small amount ahead even with no
    // torch.
    //
    new_light(point(0, 0), 2 * TILE_WIDTH, col, FBO_SMALL_POINT_LIGHTS);

    has_light = true;
    dbg("Player created");
  } else {
    if (unlikely(initial_light_dist_get())) {
      std::string l = light_color();
      if (l.empty()) {
        l = "white";
      }
      color c = string2color(l);
      new_light(point(0, 0), initial_light_dist_get() * TILE_WIDTH, c, FBO_PLAYER_VISIBLE_LIGHTING);
      has_light = true;
    }
  }
}

int Thing::light_dist_update(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return initial_light_dist_get();
  }

  uint8_t light_dist = infop()->light_dist;

  if (! light_dist) {
    light_dist = initial_light_dist_get();
  }

  if (is_player()) {
    light_dist = 0;
  }

  light_dist_update_including_torch_effect(light_dist);
  infop()->light_dist = light_dist;

  float light_dist_new = light_dist_get();
  if (! light_dist_new) {
    light_dist_new = 1;
  }

  for (auto l : light_get()) {
    if (l->ray_cast_only) {
      continue;
    }

    if (l->fbo == FBO_SMALL_POINT_LIGHTS) {
      continue;
    }

    //
    // The player has a distance they can see. This allows us to see things that are
    // lit and beyond the current light. The current light distance is scaled by the
    // torch power.
    //
    l->light_power = ((float) light_dist_new) / ((float) initial_light_dist_get());
  }

  if (is_player()) {
    level->fov_calculate(this, &level->can_see_currently, &level->can_see_ever, curr_at.x, curr_at.y, light_dist);
  }

  return light_dist;
}

////////////////////////////////////////////////////////////////////////////
// prev_light_dist
////////////////////////////////////////////////////////////////////////////
int Thing::prev_light_dist_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->prev_light_dist);
  } else {
    return 0;
  }
}

int Thing::prev_light_dist_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_dist = v);
}

int Thing::prev_light_dist_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_dist -= v);
}

int Thing::prev_light_dist_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_dist += v);
}

int Thing::prev_light_dist_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_dist--);
}

int Thing::prev_light_dist_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_dist++);
}

////////////////////////////////////////////////////////////////////////////
// light_dist
////////////////////////////////////////////////////////////////////////////
int Thing::initial_light_dist_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->light_dist());
}

int Thing::light_dist_get(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return initial_light_dist_get();
  }

  uint8_t light_dist = infop()->light_dist;

  if (is_player()) {
    light_dist = 0;
  }

  light_dist_including_torch_effect_get(light_dist);
  infop()->light_dist = light_dist;

  return light_dist;
}

int Thing::light_dist_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_dist = v);
}

int Thing::light_dist_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_dist -= v);
}

int Thing::light_dist_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_dist += v);
}

int Thing::light_dist_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_dist--);
}

int Thing::light_dist_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_dist++);
}
