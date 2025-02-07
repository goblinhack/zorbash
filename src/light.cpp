//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_light.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"

static Texp g_light_overlay_tex;
static int  g_light_overlay_texid;

static Texp g_glow_overlay_tex;
static int  g_glow_overlay_texid;

Light::Light(void)
{
  TRACE_NO_INDENT();

  newptr(MTYPE_LIGHT, this, "Light");
}

Light::~Light(void)
{
  TRACE_NO_INDENT();

  verify(MTYPE_LIGHT, this);
  if (is_being_destroyed) {
    die("Death recursion");
  }
  is_being_destroyed = true;
  destroy();
  oldptr(MTYPE_LIGHT, this);
}

void Light::draw_pixel(int16_t index, const point p0, const point p1)
{
  RayPoint r;
  r.p        = p1;
  r.distance = DISTANCE(p0.x, p0.y, p1.x, p1.y);
  points[ index ].push_back(r);
}

// http://www.edepot.com/linee.html
void Light::draw_line(int16_t index, const point p0, const point p1)
{
  points[ index ].resize(0);

  const point start = p0;
  auto        x     = p0.x;
  auto        y     = p0.y;
  auto        x2    = p1.x;
  auto        y2    = p1.y;

  bool yLonger  = false;
  int  shortLen = y2 - y;
  int  longLen  = x2 - x;
  if (abs(shortLen) > abs(longLen)) {
    int swap = shortLen;
    shortLen = longLen;
    longLen  = swap;
    yLonger  = true;
  }
  int decInc;
  if (longLen == 0)
    decInc = 0;
  else
    decInc = (shortLen << 16) / longLen;

  if (yLonger) {
    if (longLen > 0) {
      longLen += y;
      for (int j = 0x8000 + (x << 16); y <= longLen; ++y) {
        draw_pixel(index, start, point(j >> 16, y));
        j += decInc;
      }
      return;
    }
    longLen += y;
    for (int j = 0x8000 + (x << 16); y >= longLen; --y) {
      draw_pixel(index, start, point(j >> 16, y));
      j -= decInc;
    }
    return;
  }

  if (longLen > 0) {
    longLen += x;
    for (int j = 0x8000 + (y << 16); x <= longLen; ++x) {
      draw_pixel(index, start, point(x, j >> 16));
      j += decInc;
    }
    return;
  }
  longLen += x;
  for (int j = 0x8000 + (y << 16); x >= longLen; --x) {
    draw_pixel(index, start, point(x, j >> 16));
    j -= decInc;
  }
}

Lightp light_new(Thingp owner, point offset, int light_dist, color col, int fbo)
{
  TRACE_NO_INDENT();

  auto l = new Light(); // std::make_shared< class Light >();

  l->offset     = offset;
  l->light_dist = light_dist;
  if (! light_dist) {
    DIE("No light power");
  }

  l->owner = owner;
  l->col   = col;
  l->fbo   = fbo;
  l->update();

  // log("Created");
  return l;
}

Lightp light_new(Thingp owner, point offset, int light_dist)
{
  TRACE_NO_INDENT();

  auto l = new Light(); // std::make_shared< class Light >();

  l->offset        = offset;
  l->light_dist    = light_dist;
  l->owner         = owner;
  l->ray_cast_only = true;
  l->fbo           = -1;
  l->update();

  // log("Created");
  return l;
}

void Light::update(void)
{
  TRACE_NO_INDENT();

  level          = owner->level;
  max_light_rays = LIGHT_MAX_RAYS;

  ray.resize(max_light_rays);
  std::fill(ray.begin(), ray.end(), Ray {0});

  //
  // First generate the right ray lengths.
  //
  float dr = RAD_360 / ((float) max_light_rays);
  for (auto i = 0; i < max_light_rays; i++) {
    float cosr, sinr;
    sincosf(dr * i, &sinr, &cosr);
    draw_line(i, point(0, 0), point(light_dist * cosr, light_dist * sinr));
  }
}

void Light::destroy(void) { TRACE_NO_INDENT(); }

void Light::reset(void)
{
  cached_gl_cmds.clear();
  cached_pixel_map_at = point(-1, -1);
  cached_light_pos    = point(-1, -1);
}

bool Light::calculate(void)
{
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! player->is_blitted) {
    return false;
  }

  //
  // This stops lighting things up when moving to the player on a new level
  //
  if (! player->is_jumping) {
    if (player->is_hidden) {
      return false;
    }
  }

  point light_pos = owner->last_blit_at + offset;

  if (cached_light_pos == light_pos) {
    if (cached_pixel_map_at == level->pixel_map_at) {
      return true;
    }
  }

  cached_gl_cmds.clear();
  cached_pixel_map_at = level->pixel_map_at;
  cached_light_pos    = light_pos;

  //
  // Slighly insane optimization
  //
  uint8_t last_x;
  uint8_t last_y;

#define AVOID_LOOKING_AT_THE_SAME_TILE()                                                                             \
  {                                                                                                                  \
    if (likely((x == last_x) && (y == last_y))) {                                                                    \
      rp++;                                                                                                          \
      continue;                                                                                                      \
    }                                                                                                                \
    last_x = x;                                                                                                      \
    last_y = y;                                                                                                      \
  }

#define AVOID_LOOKING_AT_THE_SAME_TILE2()                                                                            \
  {                                                                                                                  \
    if (likely((x == last_x) && (y == last_y))) {                                                                    \
      rp++;                                                                                                          \
      step2++;                                                                                                       \
      continue;                                                                                                      \
    }                                                                                                                \
    last_x = x;                                                                                                      \
    last_y = y;                                                                                                      \
  }

  float light_dist_current = light_dist;
  if (! light_dist_current) {
    return false;
  }

  //
  // Do not fade ray casting lights as that allows us to see light sources
  // that are distant even if out own light is poor.
  //
  if (! ray_cast_only) {
    if (owner->is_player()) {
      light_dist_current = ((float) light_dist_current) * light_power * 3;
    }
  }

  if (! owner->is_able_to_see_through_doors()) {
    //
    // Walk the light rays in a circle. Find the nearest walls and then let
    // the light leak a little.
    //
    int d = (light_dist_current / TILE_WIDTH) + 1;
    if (likely(((player->curr_at.x >= d) && (player->curr_at.x <= MAP_WIDTH - d) && (player->curr_at.y >= d)
                && (player->curr_at.y <= MAP_HEIGHT - d)))) {
      //
      // If were casting rays, we're wanting to update what is lit currently.
      //
      if (ray_cast_only) {
        for (int16_t i = 0; i < max_light_rays; i++) {
          auto          r             = &getref_no_check(ray, i);
          int16_t       step          = 0;
          const int16_t end_of_points = static_cast< uint16_t >(points[ i ].size() - 1);
          auto          rp            = points[ i ].begin();
          last_x                      = -1;
          last_y                      = -1;
          for (;; step++) {
            if (unlikely(step >= end_of_points)) {
              break;
            }
            if (unlikely(rp->distance > light_dist_current)) {
              break;
            }
            const int16_t p1x = light_pos.x + rp->p.x;
            const int16_t p1y = light_pos.y + rp->p.y;
            const uint8_t x   = p1x / TILE_WIDTH;
            const uint8_t y   = p1y / TILE_HEIGHT;

            AVOID_LOOKING_AT_THE_SAME_TILE()
            level->is_currently_pixelart_raycast_lit_no_check_set(x, y); // allows lights to fade
            rp++;

            //
            // This is for foliage so we don't obscure too much where
            // we stand
            //
            if (step < TILE_WIDTH / 2) {
              continue;
            }

            if (level->is_light_blocker_no_check(x, y)) {
              //
              // We hit a wall. Keep walking until we exit the wall or we reach the light limit.
              //
              int16_t step2 = step;
              for (;;) {
                if (unlikely(step2 >= end_of_points)) {
                  break;
                }
                if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) {
                  break;
                }
                const int16_t p1x = light_pos.x + rp->p.x;
                const int16_t p1y = light_pos.y + rp->p.y;
                const uint8_t x   = p1x / TILE_WIDTH;
                const uint8_t y   = p1y / TILE_HEIGHT;
                AVOID_LOOKING_AT_THE_SAME_TILE2()
                if (! level->is_light_blocker_no_check(x, y)) {
                  break;
                }
                rp++;
                step2++;
              }
              step = step2;
              break;
            }
          }
          r->depth_furthest = step;
        }
      } else {
        for (int16_t i = 0; i < max_light_rays; i++) {
          auto          r             = &getref_no_check(ray, i);
          int16_t       step          = 0;
          const int16_t end_of_points = static_cast< uint16_t >(points[ i ].size() - 1);
          auto          rp            = points[ i ].begin();
          last_x                      = -1;
          last_y                      = -1;
          for (;; step++) {
            if (unlikely(step >= end_of_points)) {
              break;
            }
            if (unlikely(rp->distance > light_dist_current)) {
              break;
            }
            const int16_t p1x = light_pos.x + rp->p.x;
            const int16_t p1y = light_pos.y + rp->p.y;
            const uint8_t x   = p1x / TILE_WIDTH;
            const uint8_t y   = p1y / TILE_HEIGHT;

            AVOID_LOOKING_AT_THE_SAME_TILE()
            rp++;

            if (level->is_light_blocker_no_check(x, y)) {
              //
              // We hit a wall. Keep walking until we exit the wall or
              // we reach the light limit.
              //
              int16_t step2 = step;
              for (;;) {
                if (unlikely(step2 >= end_of_points)) {
                  break;
                }
                if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) {
                  break;
                }
                const int16_t p1x = light_pos.x + rp->p.x;
                const int16_t p1y = light_pos.y + rp->p.y;
                const uint8_t x   = p1x / TILE_WIDTH;
                const uint8_t y   = p1y / TILE_HEIGHT;
                AVOID_LOOKING_AT_THE_SAME_TILE2()
                if (! level->is_light_blocker_no_check(x, y)) {
                  break;
                }
                rp++;
                step2++;
              }
              step = step2;
              break;
            }
          }
          r->depth_furthest = step;
        }
      }
    } else {
      //
      // Slower. Need to handle oob.
      //
      if (ray_cast_only) {
        for (int16_t i = 0; i < max_light_rays; i++) {
          auto          r             = &getref(ray, i);
          int16_t       step          = 0;
          const int16_t end_of_points = static_cast< uint16_t >(points[ i ].size() - 1);
          auto          rp            = points[ i ].begin();
          last_x                      = -1;
          last_y                      = -1;
          for (;; step++) {
            if (unlikely(step >= end_of_points)) {
              break;
            }
            if (unlikely(rp->distance > light_dist_current)) {
              break;
            }
            const int16_t p1x = light_pos.x + rp->p.x;
            const int16_t p1y = light_pos.y + rp->p.y;
            const uint8_t x   = p1x / TILE_WIDTH;
            const uint8_t y   = p1y / TILE_HEIGHT;

            if (level->is_oob(x, y)) {
              break;
            }

            AVOID_LOOKING_AT_THE_SAME_TILE()
            level->is_currently_pixelart_raycast_lit_set(x, y); // allows lights to fade
            rp++;

            //
            // This is for foliage so we don't obscure too much where
            // we stand
            //
            if (step < TILE_WIDTH / 2) {
              continue;
            }

            if (level->is_light_blocker(x, y)) {
              //
              // We hit a wall. Keep walking until we exit the wall or
              // we reach the light limit.
              //
              int16_t step2 = step;
              for (;;) {
                if (unlikely(step2 >= end_of_points)) {
                  break;
                }
                if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) {
                  break;
                }
                const int16_t p1x = light_pos.x + rp->p.x;
                const int16_t p1y = light_pos.y + rp->p.y;
                const uint8_t x   = p1x / TILE_WIDTH;
                const uint8_t y   = p1y / TILE_HEIGHT;
                AVOID_LOOKING_AT_THE_SAME_TILE2()
                if (! level->is_light_blocker(x, y)) {
                  break;
                }
                rp++;
                step2++;
              }
              step = step2;
              break;
            }
          }
          r->depth_furthest = step;
        }
      } else {
        for (int16_t i = 0; i < max_light_rays; i++) {
          auto          r             = &getref(ray, i);
          int16_t       step          = 0;
          const int16_t end_of_points = static_cast< uint16_t >(points[ i ].size() - 1);
          auto          rp            = points[ i ].begin();
          last_x                      = -1;
          last_y                      = -1;
          for (;; step++) {
            if (unlikely(step >= end_of_points)) {
              break;
            }
            if (unlikely(rp->distance > light_dist_current)) {
              break;
            }
            const int16_t p1x = light_pos.x + rp->p.x;
            const int16_t p1y = light_pos.y + rp->p.y;
            const uint8_t x   = p1x / TILE_WIDTH;
            const uint8_t y   = p1y / TILE_HEIGHT;

            AVOID_LOOKING_AT_THE_SAME_TILE()
            rp++;

            if (level->is_light_blocker(x, y)) {
              //
              // We hit a wall. Keep walking until we exit the wall or
              // we reach the light limit.
              //
              int16_t step2 = step;
              for (;;) {
                if (unlikely(step2 >= end_of_points)) {
                  break;
                }
                if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) {
                  break;
                }
                const int16_t p1x = light_pos.x + rp->p.x;
                const int16_t p1y = light_pos.y + rp->p.y;
                const uint8_t x   = p1x / TILE_WIDTH;
                const uint8_t y   = p1y / TILE_HEIGHT;
                AVOID_LOOKING_AT_THE_SAME_TILE2()
                if (! level->is_light_blocker(x, y)) {
                  break;
                }
                rp++;
                step2++;
              }
              step = step2;
              break;
            }
          }
          r->depth_furthest = step;
        }
      }
    }
  } else {
    //
    // This path is a bit slower as we need to check and ignore doors.
    //
    if (ray_cast_only) {
      for (int16_t i = 0; i < max_light_rays; i++) {
        auto          r             = &getref(ray, i);
        int16_t       step          = 0;
        const int16_t end_of_points = static_cast< uint16_t >(points[ i ].size() - 1);
        auto          rp            = points[ i ].begin();
        last_x                      = -1;
        last_y                      = -1;
        for (;; step++) {
          if (unlikely(step >= end_of_points)) {
            break;
          }
          if (unlikely(rp->distance > light_dist_current)) {
            break;
          }
          const int16_t p1x = light_pos.x + rp->p.x;
          const int16_t p1y = light_pos.y + rp->p.y;
          const uint8_t x   = p1x / TILE_WIDTH;
          const uint8_t y   = p1y / TILE_HEIGHT;

          AVOID_LOOKING_AT_THE_SAME_TILE()
          level->is_currently_pixelart_raycast_lit_set(x, y); // allows lights to fade
          rp++;

          //
          // This is for foliage so we don't obscure too much where
          // we stand
          //
          if (step < TILE_WIDTH / 2) {
            continue;
          }

          if (level->is_door(x, y)) {
            continue;
          }

          if (level->is_light_blocker(x, y)) {
            //
            // We hit a wall. Keep walking until we exit the wall or
            // we reach the light limit.
            //
            int16_t step2 = step;
            for (;;) {
              if (unlikely(step2 >= end_of_points)) {
                break;
              }
              if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) {
                break;
              }
              const int16_t p1x = light_pos.x + rp->p.x;
              const int16_t p1y = light_pos.y + rp->p.y;
              const uint8_t x   = p1x / TILE_WIDTH;
              const uint8_t y   = p1y / TILE_HEIGHT;
              AVOID_LOOKING_AT_THE_SAME_TILE2()
              if (! level->is_light_blocker(x, y)) {
                break;
              }
              rp++;
              step2++;
            }
            step = step2;
            break;
          }
        }
        r->depth_furthest = step;
      }
    } else {
      for (int16_t i = 0; i < max_light_rays; i++) {
        auto          r             = &getref(ray, i);
        int16_t       step          = 0;
        const int16_t end_of_points = static_cast< uint16_t >(points[ i ].size() - 1);
        auto          rp            = points[ i ].begin();
        last_x                      = -1;
        last_y                      = -1;
        for (;; step++) {
          if (unlikely(step >= end_of_points)) {
            break;
          }
          if (unlikely(rp->distance > light_dist_current)) {
            break;
          }
          const int16_t p1x = light_pos.x + rp->p.x;
          const int16_t p1y = light_pos.y + rp->p.y;
          const uint8_t x   = p1x / TILE_WIDTH;
          const uint8_t y   = p1y / TILE_HEIGHT;

          AVOID_LOOKING_AT_THE_SAME_TILE()
          rp++;

          if (level->is_door(x, y)) {
            continue;
          }

          if (level->is_light_blocker(x, y)) {
            //
            // We hit a wall. Keep walking until we exit the wall or
            // we reach the light limit.
            //
            int16_t step2 = step;
            for (;;) {
              if (unlikely(step2 >= end_of_points)) {
                break;
              }
              if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) {
                break;
              }
              const int16_t p1x = light_pos.x + rp->p.x;
              const int16_t p1y = light_pos.y + rp->p.y;
              const uint8_t x   = p1x / TILE_WIDTH;
              const uint8_t y   = p1y / TILE_HEIGHT;
              AVOID_LOOKING_AT_THE_SAME_TILE2()
              if (! level->is_light_blocker(x, y)) {
                break;
              }
              rp++;
              step2++;
            }
            step = step2;
            break;
          }
        }
        r->depth_furthest = step;
      }
    }
  }

  return true;
}

void Light::render_triangle_fans(void)
{
  point light_pos = owner->last_blit_at;

  if (fbo == FBO_PIXELART_FULLMAP_LIGHT) {
    light_pos = cached_light_pos;
    gl_enter_2d_mode(MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT);
  } else if (fbo == FBO_PLAYER_VISIBLE_LIGHTING) {
    light_pos -= level->pixel_map_at - offset;
  } else {
    return;
  }

  glcolor(col);

  if (! cached_gl_cmds.size()) {
    blit_init();
    {
      int i;

      //
      // Walk the light rays in a circle.
      //
      push_point(light_pos.x, light_pos.y);

      for (i = 0; i < max_light_rays; i++) {
        auto    r   = &getref_no_check(ray, i);
        point  &p   = points[ i ][ r->depth_furthest ].p;
        int16_t p1x = light_pos.x + p.x;
        int16_t p1y = light_pos.y + p.y;
        push_point(p1x, p1y);
      }

      //
      // Complete the circle with the first point again.
      //
      i = 0;
      {
        auto    r   = &getref_no_check(ray, i);
        point  &p   = points[ i ][ r->depth_furthest ].p;
        int16_t p1x = light_pos.x + p.x;
        int16_t p1y = light_pos.y + p.y;
        push_point(p1x, p1y);
      }
    }

    auto sz = bufp - gl_array_buf;
    cached_gl_cmds.resize(sz);
    std::copy(gl_array_buf, bufp, cached_gl_cmds.begin());
    blit_flush_triangle_fan();
  } else {
    auto *b            = &(*cached_gl_cmds.begin());
    auto *e            = &(*cached_gl_cmds.end());
    auto  light_offset = cached_pixel_map_at - level->pixel_map_at;
    glTranslatef(light_offset.x, light_offset.y, 0);
    blit_flush_triangle_fan(b, e);
    glTranslatef(-light_offset.x, -light_offset.y, 0);
  }

  if (fbo == FBO_PIXELART_FULLMAP_LIGHT) {
    gl_enter_2d_mode(game->config.game_pix_width, game->config.game_pix_height);
  }
}

void Light::render(int ray_cast_only)
{
  if (! g_light_overlay_tex) {
    g_light_overlay_tex   = tex_load("", "light", GL_NEAREST);
    g_light_overlay_texid = tex_get_gl_binding(g_light_overlay_tex);
  }

  if (! g_glow_overlay_tex) {
    g_glow_overlay_tex   = tex_load("", "glow", GL_NEAREST);
    g_glow_overlay_texid = tex_get_gl_binding(g_glow_overlay_tex);
  }

  if (! calculate()) {
    return;
  }

  if (ray_cast_only) {
    return;
  }

  if (g_opt_ascii) {
    return;
  }

  render_triangle_fans();
}

void Level::lights_render(int minx, int miny, int maxx, int maxy, int fbo)
{
  TRACE_NO_INDENT();

  if (player) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

#if 0
    //
    // Paste this code prior to the blend in question
    //
    extern int         vals[];
    extern std::string vals_str[];
    extern int         g_blend_a;
    extern int         g_blend_b;
    CON("glBlendFunc(%s, %s)", vals_str[ g_blend_a ].c_str(), vals_str[ g_blend_b ].c_str());
    glBlendFunc(vals[ g_blend_a ], vals[ g_blend_b ]);
#endif

    for (auto l : player->light_get()) {
      if (l->ray_cast_only) {
        l->render(true);
        continue;
      }

      if (l->fbo == fbo) {
        l->render(false);
      }
    }
  }

  //
  // Small point lights create a glow around the item and are not blocked by obstacles.
  // Useful for when you have no torches and want to see something.
  //
  if (fbo != FBO_SMALL_POINT_LIGHTS) {
    return;
  }

  //
  // Blit a dark background which we will fill with lights
  //
  glClear(GL_COLOR_BUFFER_BIT);
  if (biome == BIOME_SEWER) {
    glColor4ub(0, 0, 0, 220);
  } else {
    glColor4ub(0, 0, 0, 180);
  }
  glBlendFunc(GL_ONE, GL_ZERO);
  glDisable(GL_TEXTURE_2D);
  gl_blitquad(0, 0, game->config.game_pix_width, game->config.game_pix_height);
  glEnable(GL_TEXTURE_2D);
  glcolor(WHITE);

  //
  // Draw small light sources
  //
  glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
  lights_render_small_lights(minx, miny, maxx, maxy, fbo, true);
  glcolor(WHITE);
}

//
// Draw point source lights
//
// Small point lights create a glow around the item and are not blocked by obstacles.
// Useful for when you have no torches and want to see something.
//
void Level::lights_render_small_lights(int minx, int miny, int maxx, int maxy, int fbo, bool include_player_lights)
{
  TRACE_NO_INDENT();

  blit_init();
  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      TRACE_NO_INDENT();
      FOR_ALL_LIGHTS_AT(this, t, x, y)
      {
        //
        // So knocked over braziers do not light
        //
        if (t->is_dead || t->is_corpse()) {
          continue;
        }

        for (auto &l : t->light_get()) {

          if (player && (l->owner == player)) {
            if (! include_player_lights) {
              continue;
            }
            if (l->ray_cast_only) {
              continue;
            }
            if (l->fbo != fbo) {
              continue;
            }
          }

          //
          // Skip lights that are in blocked off rooms the player cannot see
          //
          if (get(dmap_to_player.val, t->curr_at.x, t->curr_at.y) >= DMAP_IS_PASSABLE) {
            continue;
          }

          if (! is_currently_pixelart_raycast_lit_no_check(t->curr_at.x, t->curr_at.y)) {
            continue;
          }

          auto  t = l->owner;
          point blit_tl, blit_br;
          Tilep tile = {};

          if (! t->map_offset_coords_get(blit_tl, blit_br, tile, false)) {
            continue;
          }

          auto mid = (blit_br + blit_tl) / (short) 2;

          float light_scale = l->light_dist;

          if (t->gfx_pixelart_flickers()) {
            if (l->flicker_count++ > LIGHT_FLICKER_SPEED) {
              l->flicker       = ((((float) non_pcg_random_range(0, (int) light_scale))) / 8.0);
              l->flicker_count = 0;
            }
            light_scale -= l->flicker;
          }

          auto tlx = mid.x - light_scale;
          auto tly = mid.y - light_scale;
          auto brx = mid.x + light_scale;
          auto bry = mid.y + light_scale;

          color c = l->col;

          //
          // Fade the lights according to how recently seen.
          //
          auto scale = (((float) t->level->is_currently_pixelart_raycast_lit_no_check(x, y))) / 255.0;
          c.r        = (((float) c.r)) *scale;
          c.g        = (((float) c.g)) *scale;
          c.b        = (((float) c.b)) *scale;
          c.a        = (((float) c.a)) *scale;

          glcolor(c);
          blit(g_light_overlay_texid, 0, 0, 1, 1, tlx, tly, brx, bry);
        }
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }
  blit_flush();

  //
  // Add a bit of a fuzzy glow to light sources
  //
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
  blit_init();

  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      TRACE_NO_INDENT();
      FOR_ALL_LIGHTS_AT(this, t, x, y)
      {
        //
        // So knocked over braziers do not light
        //
        if (t->is_dead || t->is_corpse()) {
          continue;
        }

        for (auto &l : t->light_get()) {

          if (player && (l->owner == player)) {
            if (! include_player_lights) {
              continue;
            }
            if (l->ray_cast_only) {
              continue;
            }
            if (l->fbo != fbo) {
              continue;
            }
          }

          if (! t->gfx_glows()) {
            continue;
          }

          //
          // Skip lights that are in blocked off rooms the player cannot see
          //
          if (get(dmap_to_player.val, t->curr_at.x, t->curr_at.y) >= DMAP_IS_PASSABLE) {
            continue;
          }

          if (! is_currently_pixelart_raycast_lit_no_check(t->curr_at.x, t->curr_at.y)) {
            continue;
          }

          auto  t = l->owner;
          point blit_tl, blit_br;
          Tilep tile = {};

          if (! t->map_offset_coords_get(blit_tl, blit_br, tile, false)) {
            continue;
          }

          if (t->gfx_pixelart_flickers()) {
            if (non_pcg_random_range(0, 100) < 10) {
              l->flicker = non_pcg_random_range(0, 10);
            }
          }

          auto  s   = l->light_dist + l->flicker;
          auto  mid = (blit_br + blit_tl) / (short) 2;
          auto  tlx = mid.x - s;
          auto  tly = mid.y - s;
          auto  brx = mid.x + s;
          auto  bry = mid.y + s;
          color c   = l->col;

          //
          // Fade the lights according to how recently seen.
          //
          auto scale = (((float) t->level->is_currently_pixelart_raycast_lit_no_check(x, y))) / 255.0;
          c.r        = (((float) c.r)) *scale;
          c.g        = (((float) c.g)) *scale;
          c.b        = (((float) c.b)) *scale;
          c.a        = (((float) c.a)) *scale;

          glcolor(c);
          blit(g_glow_overlay_texid, 0, 0, 1, 1, tlx, tly, brx, bry);
        }
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }
  blit_flush();

  glcolor(WHITE);
}

//
// Alow distant lights to fade
//
void Level::lights_fade(void)
{
  TRACE_NO_INDENT();

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto v = is_currently_pixelart_raycast_lit_no_check(x, y);
      if (v > 10) {
        is_currently_pixelart_raycast_lit_no_check_set(x, y, v - 10);
      } else {
        is_currently_pixelart_raycast_lit_no_check_set(x, y, 0);
      }
    }
  }
}

//
// Refresh lights on a new level. Ignore blitted postion.
//
void Level::lights_update_new_level(void)
{
  TRACE_NO_INDENT();

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      TRACE_NO_INDENT();
      FOR_ALL_LIGHTS_AT(this, t, x, y)
      {
        //
        // So knocked over braziers do not light
        //
        if (t->is_dead || t->is_corpse()) {
          continue;
        }

        //
        // Need to do this as light position depends on blitting
        //
        t->is_blitted = false;
        for (auto &l : t->light_get()) {
          l->update();
          l->reset();
        }
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }
}

//
// Update lights on existing level e.g. torch goes out
//
void Level::lights_update_same_level(void)
{
  TRACE_NO_INDENT();

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      TRACE_NO_INDENT();
      FOR_ALL_LIGHTS_AT(this, t, x, y)
      {
        //
        // So knocked over braziers do not light
        //
        if (t->is_dead || t->is_corpse()) {
          continue;
        }

        for (auto &l : t->light_get()) {
          l->update();
          l->reset();
        }
      }
      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }
}
