//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_tile.h"
#include "my_globals.h"
#include "my_laser.h"
#include "my_projectile.h"
#include "my_ptrcheck.h"
#include "my_sdl.h"

void Level::display(void) {
  TRACE_AND_INDENT();
  bool shake = screen_shake_begin();
  display_map();
  if (shake) {
    screen_shake_end();
  }

  display_external_particles();

  if (ts_redraw_bg && (time_get_time_ms_cached() > ts_redraw_bg)) {
    ts_redraw_bg = 0;

    auto delta = 0;
    if (ts_fade_in_begin) {
      delta = time_get_time_ms_cached() - ts_fade_in_begin;
    }

    g_render_black_and_white = true;
    display_map_bg_things();
    g_render_black_and_white = false;

    //
    // Reset the fade in timestamp as the above is a bit slow
    //
    if (ts_fade_in_begin) {
      ts_fade_in_begin = time_get_time_ms_cached() - delta;
    }
  }

  if (player) {
    //
    // If a sewer, then also show the level above as it helps navigation
    //
    if (! minimap_valid) {
      if (game->level->is_level_type_sewer) {
        bool showing_two_levels = true;
        auto dungeon_level      = world_at + point3d(0, 0, -1);
        auto dungeon            = get(game->world.levels, dungeon_level.x, dungeon_level.y, dungeon_level.z);
        if (dungeon) {
          dungeon->update_minimap(showing_two_levels, true /* faded */);
        }
        update_minimap(showing_two_levels, false /* faded */);
      } else {
        update_minimap(false /* showing_two_levels */, false /* faded */);
      }
    }

    if (! is_heatmap_valid) {
      update_heatmap();
    }
  }
}

void Level::update(void) {
  TRACE_AND_INDENT();
  if (map_changed) {
    map_changed = false;
    update_map();
  }

  if (game->request_update_same_level) {
    game->request_update_same_level = false;
    update_same_level();
  }
}

void Level::display_map_bg_things(void) {
  TRACE_AND_INDENT();
  auto fbo = FBO_FULLMAP;
  gl_enter_2d_mode(MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  {
    blit_fbo_bind(fbo);
    blit_init();
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto z = 0; z < MAP_DEPTH_LAST_FG_MAP_TYPE; z++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
          FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
            if (! t->gfx_shown_in_bg()) {
              continue;
            }
            if (z <= MAP_DEPTH_FLOOR2) {
              t->blit(fbo);
            }
          }
          FOR_ALL_THINGS_END()
        }
      }
    }
    blit_flush();

    display_water(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);
    display_deep_water(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);
    display_lava(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    blit_fbo_bind(fbo);
    blit_init();
    for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH_LAST_FG_MAP_TYPE; z++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
          FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
            if (! t->gfx_shown_in_bg()) {
              continue;
            }
            t->blit(fbo);
          }
          FOR_ALL_THINGS_END()
        }
      }
    }
    blit_flush();
    blit_fbo_unbind();
  }

  gl_enter_2d_mode(game->config.game_pix_width, game->config.game_pix_height);
}

void Level::display_map_things(int fbo, const int16_t minx, const int16_t miny, const int16_t maxx,
                               const int16_t maxy) {
  TRACE_AND_INDENT();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  //
  // Blit the floor
  //
  blit_fbo_bind(fbo);
  blit_init();
  for (auto z = 0; z < MAP_DEPTH_OBJ; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
          if (z <= MAP_DEPTH_FLOOR2) {
            t->blit(fbo);
          }

          if (unlikely(game->robot_mode)) {
            if (unlikely(t->gfx_animated())) {
              t->animate();
            }
          }
        }
        FOR_ALL_THINGS_END()

        FOR_TMP_THINGS_AT_DEPTH(this, t, x, y, z) { t->blit(fbo); }
        FOR_ALL_THINGS_END()
      }
    }
  }
  blit_flush();

  display_water(fbo, minx, miny, maxx, maxy);
  display_deep_water(fbo, minx, miny, maxx, maxy);
  display_lava(fbo, minx, miny, maxx, maxy);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  //
  // Blit stuff on top of the floor and water
  //
  blit_fbo_bind(fbo);
  blit_init();
  for (auto z = MAP_DEPTH_LAST_FLOOR_TYPE + 1; z < MAP_DEPTH_OBJ; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) { t->blit(fbo); }
        FOR_ALL_THINGS_END()

        FOR_TMP_THINGS_AT_DEPTH(this, t, x, y, z) { t->blit(fbo); }
        FOR_ALL_THINGS_END()
      }
    }
  }
  blit_flush();

  glcolor(WHITE);
}

//
// Things above the floor but behind the light
//
void Level::display_map_fg_things(int fbo, const int16_t minx, const int16_t miny, const int16_t maxx,
                                  const int16_t maxy) {
  TRACE_AND_INDENT();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  blit_fbo_bind(fbo);
  blit_init();
  for (auto z = (int) MAP_DEPTH_OBJ; z <= MAP_DEPTH_LAST_FG_MAP_TYPE; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
          t->blit(fbo);

          if (unlikely(game->robot_mode)) {
            if (unlikely(t->gfx_animated())) {
              t->animate();
            }
          }

          //
          // Sanity checks
          //
          IF_DEBUG3 {
            if (! t->is_moving && ! t->is_jumping && ! t->is_falling) {
              if (t->mid_at != t->get_interpolated_mid_at()) {
                t->die("Thing is not where its interpolated to be; is at %f,%f", t->get_interpolated_mid_at().x,
                       t->get_interpolated_mid_at().y);
              }
            }
          }
        }
        FOR_ALL_THINGS_END()

        FOR_TMP_THINGS_AT_DEPTH(this, t, x, y, z) { t->blit(fbo); }
        FOR_ALL_THINGS_END()
      }
    }
  }
  blit_flush();
}

//
// Things above the light
//
void Level::display_map_fg2_things(int fbo, const int16_t minx, const int16_t miny, const int16_t maxx,
                                   const int16_t maxy) {
  TRACE_AND_INDENT();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  blit_fbo_bind(fbo);
  blit_init();
  for (auto z = (int) MAP_DEPTH_LAST_FG_MAP_TYPE + 1; z < MAP_DEPTH; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        FOR_ALL_THINGS_AT_DEPTH(this, t, x, y, z) {
          t->blit(fbo);

          if (unlikely(game->robot_mode)) {
            if (unlikely(t->gfx_animated())) {
              t->animate();
            }
          }
        }
        FOR_ALL_THINGS_END()

        FOR_TMP_THINGS_AT_DEPTH(this, t, x, y, z) { t->blit(fbo); }
        FOR_ALL_THINGS_END()
      }
    }
  }
  blit_flush();
}

void Level::display_map(void) {
  TRACE_AND_INDENT();
  int light_minx;
  int light_maxx;
  int light_miny;
  int light_maxy;

  //
  // Get the bounds. Needs to be a bit off-map for reflections.
  //
  int border = MAP_BORDER_ROCK;
  minx       = std::max(0, (int) map_at.x - border);
  maxx       = std::min(MAP_WIDTH, (int) map_at.x + TILES_ACROSS + border);

  miny = std::max(0, (int) map_at.y - border);
  maxy = std::min(MAP_HEIGHT, (int) map_at.y + TILES_DOWN + border);

  map_tl = point(minx, miny);
  map_br = point(maxx, maxy);

  //
  // For light sources we need to draw a bit off map as the light
  // has a radius
  //
  light_minx = std::max(0, minx - TILES_ACROSS);
  light_maxx = std::min(MAP_HEIGHT, maxx + TILES_ACROSS);
  light_miny = std::max(0, miny - TILES_DOWN);
  light_maxy = std::min(MAP_HEIGHT, maxy + TILES_DOWN);

  display_anim();
  scroll_map_set_target();
  scroll_map();

  bool fade_out     = ts_fade_out_begin != 0;
  bool fade_in      = ts_fade_in_begin != 0;
  bool frozen       = player ? player->is_changing_level : false;
  fade_out_finished = false;

  if (fade_out) {
    if ((time_get_time_ms_cached() < ts_fade_out_begin) ||
        (time_get_time_ms_cached() - ts_fade_out_begin > LEVEL_FADE_OUT_MS)) {
      minimap_valid     = false;
      ts_fade_out_begin = 0;
      fade_out_finished = true;
      if (player) {
        player->log("Fade out of level finished");
      }
    }
  }

  if (fade_in) {
    if ((time_get_time_ms_cached() < ts_fade_in_begin) ||
        (time_get_time_ms_cached() - ts_fade_in_begin > LEVEL_FADE_IN_MS)) {
      minimap_valid    = false;
      ts_fade_in_begin = 0;
      if (player) {
        player->log("Fade in of level finished");
      }
    }
  }

  pixel_map_at = point(map_at.x * TILE_WIDTH, map_at.y * TILE_HEIGHT);

  if (! frozen) {
    TRACE_AND_INDENT();
    //
    // Generate an FBO with all light sources merged together
    //
    blit_fbo_bind(FBO_PLAYER_VISIBLE_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    // Render the player light sources - but also render the point
    // light sources on a dark background to make things look more
    // dramatic
    //
    lights_render(light_minx, light_miny, light_maxx, light_maxy, FBO_PLAYER_VISIBLE_LIGHTING);
    //
    // Add in point light sources so we can see lave for example that
    // is not directly lit but it hit by ray casting
    //
    lights_render_small_lights(light_minx, light_miny, light_maxx, light_maxy, FBO_SMALL_POINT_LIGHTS,
                               false /* include player lights */);

    //
    // This renders a single player light to the gray background
    // so we can see where we have been
    //
    blit_fbo_bind(FBO_FULLMAP_LIGHT);
    lights_render(light_minx, light_miny, light_maxx, light_maxy, FBO_FULLMAP_LIGHT);

    //
    // Render a dark background with point lights that look dramatic
    //
    blit_fbo_bind(FBO_SMALL_POINT_LIGHTS);
    lights_render(light_minx, light_miny, light_maxx, light_maxy, FBO_SMALL_POINT_LIGHTS);
  }

  if (! frozen) {
    TRACE_AND_INDENT();
    //
    // Generate the non visited map with the light inverted on it
    // to hide visible areas
    //
    blit_fbo_bind(FBO_MAP_HIDDEN);
    glClear(GL_COLOR_BUFFER_BIT);

    float w = MAP_WIDTH * TILE_WIDTH;
    float h = MAP_HEIGHT * TILE_HEIGHT;
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto  Y     = h - pixel_map_at.y - game->config.game_pix_height;
    float left  = (float) (pixel_map_at.x) / w;
    float top   = (float) (Y + game->config.game_pix_height) / h;
    float right = (float) (pixel_map_at.x + game->config.game_pix_width) / w;
    float bot   = (float) Y / h;

    blit_init();
    blit(fbo_tex_id[FBO_FULLMAP], left, top, right, bot, 0, 0, game->config.game_pix_width,
         game->config.game_pix_height);
    blit_flush();

    glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);

    blit_init();
    blit(fbo_tex_id[FBO_FULLMAP_LIGHT], left, top, right, bot, 0, 0, game->config.game_pix_width,
         game->config.game_pix_height);
    blit_flush();

    glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    blit_fbo_game_pix(FBO_PLAYER_VISIBLE_LIGHTING);
    // sdl_fbo_dump(FBO_FULLMAP_LIGHT, "FULLMAP");
  }

  if (! frozen) {
    TRACE_AND_INDENT();
    //
    // Generate the currently visible map
    //
    blit_fbo_bind(FBO_MAP_VISIBLE);
    glClear(GL_COLOR_BUFFER_BIT);
    display_map_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
    display_internal_particles();

    //
    // Blit small lights and glow
    //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo_game_pix(FBO_SMALL_POINT_LIGHTS);

    //
    // Blit objects that are in front of small lights so that the
    // player is not lost in lava glow
    //
    display_lasers();
    display_projectiles();
    display_map_fg_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
    IF_NODEBUG3 {
      glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);
      blit_fbo_game_pix(FBO_PLAYER_VISIBLE_LIGHTING);
    }
    display_map_fg2_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);

    //
    // If choosing a target, lets see it
    //
    display_target();
  }

  {
    TRACE_AND_INDENT();
    //
    // This is the final map output
    //
    // Generate the merged map with the black and white portions
    // under the visible map
    //
    blit_fbo_bind(FBO_MAP);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(GRAY40);

    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
    blit_fbo_game_pix(FBO_MAP_HIDDEN);
    glBlendFunc(GL_ONE, GL_ONE);

    glcolor(WHITE);
    blit_fbo_game_pix(FBO_MAP_VISIBLE);

    IF_NODEBUG3 {
      if (fade_out) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        display_fade_out();
        blit_fbo_bind(FBO_MAP);
        glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_ALPHA);
        blit_fbo_game_pix(FBO_SCREEN_FADE_IN_AND_OUT);
      }

      if (fade_in) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        display_fade_in();
        blit_fbo_bind(FBO_MAP);
        glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_ALPHA);
        blit_fbo_game_pix(FBO_SCREEN_FADE_IN_AND_OUT);
      }
    }
  }

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //
  // If the cursor is too far away, warp it
  //
  cursor_check_if_scroll_needed();
  cursor_find_on_visible_things(minx, miny, maxx, maxy);

  display_blood();

  blit_fbo_unbind();

  if (fade_out_finished) {
    if (player) {
      player->log("Level fade out finished");
    }

    blit_fbo_bind(FBO_MAP_HIDDEN);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_MAP_VISIBLE);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_FULLMAP);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_FULLMAP_LIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_PLAYER_VISIBLE_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_MAP);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_unbind();
  }
}
