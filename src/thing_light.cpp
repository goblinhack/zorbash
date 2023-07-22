//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

std::vector< Lightp > &Thing::light_get(void)
{
  TRACE_NO_INDENT();

  //
  // Faster to avoid the infop API as this is called a lot
  //
  if (_infop) { return (_infop->light); }
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
    col = YELLOW;
    new_light(point(0, 0), light_dist, col, FBO_PLAYER_VISIBLE_LIGHTING);

    //
    // This small glow around the player is always present, even in low
    // lighting and allows you to see a small amount ahead even with no
    // torch.
    //
    col = WHITE;
    new_light(point(0, 0), light_dist / 2, col, FBO_PLAYER_VISIBLE_LIGHTING);

    col = WHITE;
    new_light(point(0, 0), light_dist / 3, col, FBO_PLAYER_VISIBLE_LIGHTING);

    col = YELLOW;
    new_light(point(0, 0), 4 * TILE_WIDTH, col, FBO_SMALL_POINT_LIGHTS);

    col = WHITE;
    new_light(point(0, 0), 2 * TILE_WIDTH, col, FBO_SMALL_POINT_LIGHTS);

    has_light = true;
    dbg("Player created");
  } else {
    //
    // Not too many lights
    //
    if (is_lava()) {
      if (d100() < 50) { return; }
    }

    if (unlikely(initial_light_dist_get())) {
      std::string l = light_color();
      if (l.empty()) { l = "white"; }
      color c = string2color(l);
      new_light(point(0, 0), initial_light_dist_get() * TILE_WIDTH, c, FBO_PLAYER_VISIBLE_LIGHTING);
      has_light = true;
    }
  }
}

int Thing::light_distance_update(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) { return initial_light_dist_get(); }

  uint8_t light_dist = infop()->light_dist;

  if (! light_dist) { light_dist = initial_light_dist_get(); }

  if (is_player()) {
    light_dist                         = 0;
    level->request_player_light_update = false;
  }

  light_distance_upd_with_torch_effect(light_dist);
  infop()->light_dist = light_dist;

  float light_dist_new = light_dist_get();
  if (! light_dist_new) { light_dist_new = 1; }

  for (auto l : light_get()) {
    if (l->ray_cast_only) { continue; }

    if (l->fbo == FBO_SMALL_POINT_LIGHTS) { continue; }

    //
    // The player has a distance they can see. This allows us to see things that are
    // lit and beyond the current light. The current light distance is scaled by the
    // torch power.
    //
    l->light_power = ((float) light_dist_new) / ((float) initial_light_dist_get());
  }

  if (is_player()) {
    level->fov_calculate(this, &level->can_see_currently, &level->can_see_ever, curr_at.x, curr_at.y, light_dist);

    if (is_debug_type()) {
      con("This is what the player can see:");
      con("  @  - you/it");
      con("  L  - walked and can see currently");
      con("  O  - walked and have seen ever");
      con("  l  - can see currently");
      con("  o  - have seen ever");

      for (int y = 0; y < MAP_HEIGHT; y++) {
        std::string s;
        for (int x = 0; x < MAP_WIDTH; x++) {
          if ((x == (int) curr_at.x) && (y == (int) curr_at.y)) {
            s += "@";
            continue;
          }

          if (level->is_obs_wall_or_door(x, y)) {
            if (get(level->can_see_currently.can_see, x, y)) {
              s += "x";
            } else if (get(level->can_see_ever.can_see, x, y)) {
              s += "x";
            } else {
              s += "x";
            }
          } else if (level->is_floor(x, y) || level->is_corridor(x, y)) {
            if (get(level->can_see_currently.can_see, x, y)) {
              s += "l";
            } else if (get(level->can_see_ever.can_see, x, y)) {
              s += "o";
            } else {
              s += ".";
            }
          } else {
            s += " ";
          }
        }
        con("%s", s.c_str());
      }
    }

    FOR_ALL_INTERESTING_THINGS_ON_LEVEL(level, t)
    {
      if (get_no_check(level->can_see_currently.can_see, t->curr_at.x, t->curr_at.y)) {
        //
        // In chasm levels we can see further and off-screen. Limit to what is onscreen.
        //
        if (t->tile_is_offscreen()) { continue; }

        t->is_visible_to_player = true;

        FOR_ALL_EQUIP(iter)
        {
          auto it = t->equip_carry_anim(iter);
          if (it) { it->is_visible_to_player = true; }
        }

        FOR_ALL_BODYPART(iter)
        {
          if (bodypart_id_get(iter).ok()) {
            auto it = level->thing_find(bodypart_id_get(iter));
            if (it) { it->is_visible_to_player = true; }
          }
        }
      }
    }
    FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(level)
  }

  return light_dist;
}

////////////////////////////////////////////////////////////////////////////
// prev_light_dist
////////////////////////////////////////////////////////////////////////////
int Thing::prev_light_dist_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->prev_light_dist); }
  return 0;
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
  auto light_dist = tp()->light_dist();

  if (is_player()) {
    if (level->biome == BIOME_CHASMS) { light_dist *= 2; }
  }

  return light_dist;
}

int Thing::light_dist_get(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) { return initial_light_dist_get(); }

  uint8_t light_dist = infop()->light_dist;

  if (is_player()) { light_dist = 0; }

  light_dist_including_torch_effect_get(light_dist);
  infop()->light_dist = light_dist;

  if (is_player()) {
    if (level->biome == BIOME_CHASMS) { light_dist *= 2; }
  }

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
