//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"

void Level::display_pixelart_map(void)
{
  TRACE_NO_INDENT();

  if (! should_display_map()) {
    return;
  }

  bool shake = screen_shake_begin();
  display_pixelart_map_all();
  if (shake) {
    screen_shake_end();
  }

  display_pixelart_external_particles();

  if (ts_redraw_bg && (time_ms_cached() > ts_redraw_bg)) {
    ts_redraw_bg = 0;

    auto delta = 0;
    if (ts_fade_in_begin) {
      delta = time_ms_cached() - ts_fade_in_begin;
    }

    g_render_monochrome = true;
    display_pixelart_map_bg_things();
    g_render_monochrome = false;

    //
    // Reset the fade in timestamp as the above is a bit slow
    //
    if (ts_fade_in_begin) {
      ts_fade_in_begin = time_ms_cached() - delta;
    }
  }

  if (player) {
    //
    // If the player is no longer on the level (maybe choosing the next one)
    // then do not try to display.
    //
    if (player->is_changing_level) {
      return;
    }

    //
    // If a sewer, then also show the level above as it helps navigation
    //
    if (! is_map_mini_valid) {
      if (game->level->biome == BIOME_SEWER) {
        bool showing_two_levels = true;
        auto dungeon_level      = world_at + point3d(0, 0, -1);
        auto dungeon            = get(game->world.levels, dungeon_level.x, dungeon_level.y, dungeon_level.z);
        if (dungeon) {
          dungeon->update_map_mini(showing_two_levels, true /* faded */);
        }
        update_map_mini(showing_two_levels, false /* faded */);
      } else {
        update_map_mini(false /* showing_two_levels */, false /* faded */);
      }
    }
  }
}

void Level::display_pixelart_map_bg_things(void)
{
  TRACE_NO_INDENT();

  auto fbo = FBO_PIXELART_FULLMAP;
  gl_enter_2d_mode(MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  {
    blit_fbo_bind(fbo);
    blit_init();
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto z = 0; z <= MAP_DEPTH_OBJ; z++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
          TRACE_NO_INDENT();
          FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
          {
            if (! t->gfx_pixelart_shown_in_bg()) {
              continue;
            }
            if (z <= MAP_DEPTH_FLOOR2) {
              t->blit_pixelart(fbo);
            }
          }
          TRACE_NO_INDENT();
          FOR_ALL_THINGS_END()
        }
      }
    }
    blit_flush();

    display_pixelart_water(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);
    display_pixelart_deep_water(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);
    display_pixelart_lava(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);
    display_pixelart_basalt(fbo, 0, 0, MAP_WIDTH, MAP_HEIGHT);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    blit_fbo_bind(fbo);
    blit_init();
    int z = MAP_DEPTH_OBJ;
    {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
          TRACE_NO_INDENT();
          FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
          {
            if (! t->gfx_pixelart_shown_in_bg()) {
              continue;
            }
            t->blit_pixelart(fbo);
          }
          TRACE_NO_INDENT();
          FOR_ALL_THINGS_END()
        }
      }
    }
    blit_flush();
    blit_fbo_unbind();
  }

  gl_enter_2d_mode(game->config.game_pix_width, game->config.game_pix_height);
}

void Level::display_pixelart_map_things(int fbo, const int16_t minx, const int16_t miny, const int16_t maxx,
                                        const int16_t maxy)
{
  TRACE_NO_INDENT();

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  TRACE_NO_INDENT();
  FOR_ALL_ANIMATED_THINGS_LEVEL(this, t) { t->animate(); }
  TRACE_NO_INDENT();
  FOR_ALL_ANIMATED_THINGS_LEVEL_END(this)

  //
  // Blit the floor
  //
  blit_fbo_bind(fbo);
  blit_init();

  for (auto z = 0; z <= MAP_DEPTH_FLOOR2; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        //
        // NOTE: if level pop/push happens here then we can end up missing this
        // thing in the blit as we are using the unsafe(faster) walker.
        //
        TRACE_NO_INDENT();
        FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z) { t->blit_pixelart(fbo); }
        TRACE_NO_INDENT();
        FOR_ALL_THINGS_END()
      }
    }
  }
  blit_flush();

  display_pixelart_water(fbo, minx, miny, maxx, maxy);
  display_pixelart_deep_water(fbo, minx, miny, maxx, maxy);
  display_pixelart_lava(fbo, minx, miny, maxx, maxy);
  display_pixelart_basalt(fbo, minx, miny, maxx, maxy);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  //
  // Blit stuff on top of the floor and water
  //
  blit_fbo_bind(fbo);
  blit_init();
  int z = MAP_DEPTH_OBJ;
  {
    for (auto y = miny; y < maxy; y++) {
      for (uint8_t z_prio = MAP_Z_PRIO_ALWAYS_BEHIND; z_prio < MAP_Z_PRIO_LAST; z_prio++) {
        for (auto x = minx; x < maxx; x++) {
          TRACE_NO_INDENT();
          FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
          {
            if (t->z_prio() != z_prio) {
              continue;
            }
            t->blit_pixelart(fbo);
          }
          TRACE_NO_INDENT();
          FOR_ALL_THINGS_END()
        }
      }
    }
  }
  blit_flush();

  glcolor(WHITE);
}

//
// Blit objects that are in front of small lights so that the player is not lost in lava glow
//
void Level::display_pixelart_map_fg_things(int fbo, const int16_t minx, const int16_t miny, const int16_t maxx,
                                           const int16_t maxy)
{
  TRACE_NO_INDENT();

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  blit_fbo_bind(fbo);
  blit_init();
  for (auto z = (int) MAP_DEPTH_OBJ; z <= MAP_DEPTH_OBJ; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (uint8_t z_prio = MAP_Z_PRIO_ALWAYS_BEHIND; z_prio < MAP_Z_PRIO_LAST; z_prio++) {
        for (auto x = minx; x < maxx; x++) {
          TRACE_NO_INDENT();
          FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z)
          {
            if (t->z_prio() != z_prio) {
              continue;
            }

            t->blit_pixelart(fbo);

            //
            // Sanity checks
            //
            IF_DEBUG2
            {
              if (! t->is_teleporting && ! t->is_moving && ! t->is_jumping && ! t->is_falling
                  && ! t->is_tmp_thing()) {
                if (t->curr_at != make_point(t->interpolated_at_get())) {
                  t->die("Thing is not where it is interpolated to be; is at %f,%f", t->interpolated_at_get().x,
                         t->interpolated_at_get().y);
                }
              }
            }
          }
        }
        TRACE_NO_INDENT();
        FOR_ALL_THINGS_END()
      }
    }
  }
  blit_flush();
}

//
// Things above the light
//
void Level::display_pixelart_map_fg2_things(int fbo, const int16_t minx, const int16_t miny, const int16_t maxx,
                                            const int16_t maxy)
{
  TRACE_NO_INDENT();

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  blit_fbo_bind(fbo);
  blit_init();
  for (auto z = (int) MAP_DEPTH_TOP; z < MAP_DEPTH; z++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        TRACE_NO_INDENT();
        FOR_ALL_THINGS_AT_DEPTH_UNSAFE(this, t, x, y, z) { t->blit_pixelart(fbo); }
        TRACE_NO_INDENT();
        FOR_ALL_THINGS_END()
      }
    }
  }
  blit_flush();
}

void Level::display_pixelart_map_all(void)
{
  TRACE_NO_INDENT();

  point tl(minx, miny);
  point br(maxx, maxy);

  //
  // For light sources we need to draw a bit off map as the light has a radius
  //
  int light_border = 4;
  int light_minx   = minx - light_border;
  int light_maxx   = maxx + light_border;
  int light_miny   = miny - light_border;
  int light_maxy   = maxy + light_border;

  if (light_maxx > MAP_WIDTH - 1) {
    light_maxx = MAP_WIDTH - 1;
  }
  if (light_maxy > MAP_HEIGHT - 1) {
    light_maxy = MAP_HEIGHT - 1;
  }
  if (light_minx < 0) {
    light_minx = 0;
  }
  if (light_miny < 0) {
    light_miny = 0;
  }

  display_map_set_bounds();
  display_tick_animation();

  bool fade_out = ts_fade_out_begin != 0;
  bool fade_in  = ts_fade_in_begin != 0;
  bool frozen   = player ? player->is_changing_level : false;

  if (fade_out) {
    if ((time_ms_cached() < ts_fade_out_begin) || (time_ms_cached() - ts_fade_out_begin > LEVEL_FADE_OUT_MS)) {
      is_map_mini_valid = false;
      ts_fade_out_begin = 0;
      fade_out_finished = true;
      if (player) {
        DBG("Fade out of level finished");
      }
    }
  }

  if (fade_in) {
    if ((time_ms_cached() < ts_fade_in_begin) || (time_ms_cached() - ts_fade_in_begin > LEVEL_FADE_IN_MS)) {
      is_map_mini_valid = false;
      ts_fade_in_begin  = 0;
      if (player) {
        DBG("Fade in of level finished");
        request_player_light_update = true;
      }
    }
  }

  pixel_map_at = point(map_at.x * TILE_WIDTH, map_at.y * TILE_HEIGHT);

  if (! frozen) {
    TRACE_NO_INDENT();
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
    blit_fbo_bind(FBO_PIXELART_FULLMAP_LIGHT);
    lights_render(light_minx, light_miny, light_maxx, light_maxy, FBO_PIXELART_FULLMAP_LIGHT);

    //
    // Render a dark background with point lights that look dramatic
    //
    blit_fbo_bind(FBO_SMALL_POINT_LIGHTS);
    lights_render(light_minx, light_miny, light_maxx, light_maxy, FBO_SMALL_POINT_LIGHTS);
  }

  if (! frozen) {
    TRACE_NO_INDENT();
    //
    // Generate the non visited map with the light inverted on it to hide visible areas
    //
    blit_fbo_bind(FBO_MAP_HIDDEN);
    glClear(GL_COLOR_BUFFER_BIT);

    float w = MAP_WIDTH * TILE_WIDTH;
    float h = MAP_HEIGHT * TILE_HEIGHT;
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto  Y     = h - pixel_map_at.y - game->config.game_pix_height;
    float left  = ((float) (pixel_map_at.x)) / w;
    float top   = ((float) (Y) + game->config.game_pix_height) / h;
    float right = ((float) (pixel_map_at.x) + game->config.game_pix_width) / w;
    float bot   = ((float) Y) / h;

    blit_init();
    blit(fbo_tex_id[ FBO_PIXELART_FULLMAP ], left, top, right, bot, 0, 0, game->config.game_pix_width,
         game->config.game_pix_height);
    blit_flush();

    glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);

    blit_init();
    blit(fbo_tex_id[ FBO_PIXELART_FULLMAP_LIGHT ], left, top, right, bot, 0, 0, game->config.game_pix_width,
         game->config.game_pix_height);
    blit_flush();

    glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    blit_fbo_game_pix(FBO_PLAYER_VISIBLE_LIGHTING);

    if (0) {
      sdl_fbo_dump(FBO_PIXELART_FULLMAP_LIGHT, "FULLMAP_LIGHT");
      sdl_fbo_dump(FBO_PIXELART_FULLMAP, "FULLMAP");
    }
  }

  if (! frozen) {
    TRACE_NO_INDENT();
    //
    // Generate the currently visible map
    //
    blit_fbo_bind(FBO_MAP_VISIBLE);
    glClear(GL_COLOR_BUFFER_BIT);
    display_pixelart_map_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);

    //
    // Blit small lights and glow
    //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo_game_pix(FBO_SMALL_POINT_LIGHTS);

    //
    // Blit objects that are in front of small lights so that the player is not lost in lava glow
    //
    display_pixelart_map_fg_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);

    //
    // I want to see lasers on top of things like the entrance and not under.
    //
    display_lasers(tl, br);
    display_projectiles(tl, br);

    //
    // So we can see monsters jump over walls
    //
    display_pixelart_internal_particles();

    if (display_gas_healing) {
      display_pixelart_gas_poison(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
    }
    if (display_gas_poison) {
      display_pixelart_gas_healing(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
    }
    if (display_darkness) {
      display_pixelart_darkness(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glcolor(WHITE);

    IF_NODEBUG2
    {
      glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA_SATURATE);
      blit_fbo_game_pix(FBO_PLAYER_VISIBLE_LIGHTING);
    }

    //
    // Messages and explosions are above the light
    //
    display_pixelart_map_fg2_things(FBO_MAP_VISIBLE, minx, miny, maxx, maxy);

    //
    // If choosing a target, lets see it
    //
    display_target();
  }

  {
    TRACE_NO_INDENT();
    //
    // This is the final map output
    //
    // Generate the merged map with the black and white portions
    // under the visible map
    //
    blit_fbo_bind(FBO_MAP);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    // More ominous lighting
    //
    switch (biome) {
      case BIOME_UNKNOWN : break;
      case BIOME_DUNGEON : glcolor(GRAY50); break;
      case BIOME_FLOODED : glcolor(GRAY50); break;
      case BIOME_SWAMP : glcolor(GRAY10); break;
      case BIOME_SEWER : glcolor(GRAY10); break;
      case BIOME_ICE : glcolor(BLUE); break;
      case BIOME_CHASMS :
        //
        // Looks more ominous
        //
        glcolor(GRAY10);
        break;
      case BIOME_LAVA : glcolor(RED); break;
      case BIOME_DUNGEONS : break;
      case BIOME_MAX : break;
    }

    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
    blit_fbo_game_pix(FBO_MAP_HIDDEN);
    glBlendFunc(GL_ONE, GL_ONE);

    glcolor(WHITE);
    blit_fbo_game_pix(FBO_MAP_VISIBLE);

    IF_NODEBUG2
    {
      if (fade_out) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        display_pixelart_fade_out();
        blit_fbo_bind(FBO_MAP);
        glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_ALPHA);
        blit_fbo_game_pix(FBO_SCREEN_FADE_IN_AND_OUT);
      }

      if (fade_in) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        display_pixelart_fade_in();
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
  cursor_warp_check();
  cursor_find_on_visible_things(minx, miny, maxx, maxy);

  display_pixelart_blood();

  blit_fbo_unbind();

  if (fade_out_finished) {
    if (player) {
      player->log("Level fade out finished");
    }

    blit_fbo_bind(FBO_MAP_HIDDEN);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_MAP_VISIBLE);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_PIXELART_FULLMAP);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_PIXELART_FULLMAP_LIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_PLAYER_VISIBLE_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_bind(FBO_MAP);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_unbind();
  }
}
