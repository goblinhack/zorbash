//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_thing.hpp"
#include "my_wid_rightbar.hpp"

//
// Stop the map scrolling off the edges of the screen.
//
// If we did allow that then we need to clamp the FBO_PIXELART_FULLMAP* textures to avoid drawing negative
// co-ordinates; and I can't be bothered fixing that; but also I think it's quite nice not to scroll too far
// so the player knows the edges of the map.
//
void Level::scroll_map_set_bounds(void)
{
  if (g_opt_ascii) {
    map_at.x = 0;
    map_at.y = 0;
  } else {
    if (map_at.x > MAP_WIDTH - 1) {
      map_at.x = MAP_WIDTH - 1;
    }
    if (map_at.y > MAP_HEIGHT - 1) {
      map_at.y = MAP_HEIGHT - 1;
    }
  }
  if (map_at.x < 0) {
    map_at.x = 0;
  }
  if (map_at.y < 0) {
    map_at.y = 0;
  }

  if (map_wanted_at.x > MAP_WIDTH - 1) {
    map_wanted_at.x = MAP_WIDTH - 1;
  }
  if (map_wanted_at.y > MAP_HEIGHT - 1) {
    map_wanted_at.y = MAP_HEIGHT - 1;
  }
  if (map_wanted_at.x < 0) {
    map_wanted_at.x = 0;
  }
  if (map_wanted_at.y < 0) {
    map_wanted_at.y = 0;
  }
}

void Level::scroll_map_do(bool fast)
{
  TRACE_NO_INDENT();

  if (game->is_being_destroyed || is_being_destroyed) {
    return;
  }

  const float vbigstep  = 1;
  const float bigstep   = 4;
  const float medstep   = 16;
  const float smallstep = 32;

  auto dx = map_at.x - map_wanted_at.x;
  auto dy = map_at.y - map_wanted_at.y;

  if (fabs(dx) < 0.1) {
    dx = 0;
  }

  if (fabs(dy) < 0.1) {
    dy = 0;
  }

  if ((dx == 0) && (dy == 0)) {
    return;
  }

#if 0
  if (player) {
    player->topcon("map_at %f %f map_wanted_at %f %f", map_at.x, map_at.y, map_wanted_at.x, map_wanted_at.y);
  }
#endif

  //
  // If following the player scroll in smaller chunks
  //
  if (is_map_follow_player) {
    if (fast) {
      map_at.x -= dx;
      map_at.y -= dy;
    } else {
      float step;

      if (fabs(dx) > 32) {
        step = vbigstep;
      } else if (fabs(dx) > 16) {
        step = bigstep;
      } else if (fabs(dx) > 8) {
        step = medstep;
      } else if (fabs(dx) > 0) {
        step = smallstep;
      } else {
        step = 0;
      }

      if (step > 0) {
        auto dx = (map_wanted_at.x - map_at.x) / step;
        //
        // This used to be a thing when I did not have pixel accurate map and rounded pixels were a thing.
        //
        // dx *= TILE_WIDTH;
        // dx = (int) ceil(dx);
        // dx /= TILE_WIDTH;
        if (g_opt_ascii) {
          if (dx < 0) {
            dx = -1;
          } else if (dx > 0) {
            dx = 1;
          }
        }
        map_at.x += dx;
      }

      if (fabs(dy) > 32) {
        step = vbigstep;
      } else if (fabs(dy) > 16) {
        step = bigstep;
      } else if (fabs(dy) > 8) {
        step = medstep;
      } else if (fabs(dy) > 0) {
        step = smallstep;
      } else {
        step = 0;
      }

      if (step > 0) {
        auto dy = (map_wanted_at.y - map_at.y) / step;
        //
        // This used to be a thing when I did not have pixel
        // accurate map and rounded pixels were a thing.
        //
        // dy *= TILE_HEIGHT;
        // dy = (int) ceil(dy);
        // dy /= TILE_HEIGHT;
        if (g_opt_ascii) {
          if (dy < 0) {
            dy = -1;
          } else if (dy > 0) {
            dy = 1;
          }
        }
        map_at.y += dy;
      }
    }
  } else {
    //
    // Else following the cursor or mouse. Bigger chunks are less sick inducing.
    //
    if (g_opt_ascii) {
      map_at.x -= dx;
      map_at.y -= dy;
    } else {
      if (fast) {
        map_at.x -= dx;
        map_at.y -= dy;
      } else {
        map_at.x -= dx / bigstep;
        map_at.y -= dy / bigstep;
      }
    }
  }

  //
  // Round to pixels
  //
  if (! g_opt_ascii) {
    map_at.x *= TILE_WIDTH;
    map_at.y *= TILE_HEIGHT;
    map_at.x = (int) map_at.x;
    map_at.y = (int) map_at.y;
    map_at.x /= TILE_WIDTH;
    map_at.y /= TILE_HEIGHT;
  }

  //
  // Do not scroll off the map
  //
  scroll_map_set_bounds();
}

void Level::scroll_map(void)
{
  TRACE_NO_INDENT();

  scroll_map_do(false);
}

void Level::scroll_map_to_player(void)
{
  TRACE_NO_INDENT();

  if (! player) {
    return;
  }

  mouse_at             = -1;
  mouse_old            = -1;
  ts_redraw_bg         = time_ms_cached() + 500;
  is_map_follow_player = true;

  //
  // Make sure we know the map size before trying to scroll
  //
  wid_rightbar_init();

  map_wanted_at = make_fpoint(player->curr_at) - fpoint(TILES_VISIBLE_ACROSS / 2, TILES_VISIBLE_DOWN / 2);

  scroll_map_set_target();
  scroll_map_do(true);
}

void Level::scroll_map_to_player_immediately(void)
{
  TRACE_NO_INDENT();

  if (! player) {
    return;
  }
  scroll_map_to_player();

  int tries = 0;
  while (tries++ < 10000) {
    auto dx = map_at.x - map_wanted_at.x;
    auto dy = map_at.y - map_wanted_at.y;

    if ((dx == 0) && (dy == 0)) {
      return;
    }

    scroll_map_to_player();

    //
    // Can't move anymore?
    //
    auto ndx = map_at.x - map_wanted_at.x;
    auto ndy = map_at.y - map_wanted_at.y;
    if ((ndx == dx) && (ndy == dy)) {
      return;
    }
  }
  err("Could not scroll map to player");
}

//
// Make the map scroll to the cursor (or the player)
//
void Level::scroll_map_set_target(void)
{
  TRACE_NO_INDENT();

  fpoint follow;

  //
  // Do not have this. This prevents us scrolling when over the minimap.
  //
  // if (wid_find_under_mouse_when_scrolling()) {
  //   return;
  // }

  if (player && is_map_follow_player) {
    follow = make_fpoint(player->curr_at);

    //
    // The smaller the number, the further from the edge of the map we scroll.
    //
    int x_sensitivity = 1;
    int y_sensitivity = 1;

    bool auto_scroll = true;
    if (g_opt_ascii) {
      //
      // Ideally no scrolling in ascii mode, to help those with limited vision
      //
      auto_scroll = false;

      //
      // Unless we are really at the edges.
      //
      int scroll_border = MAP_BORDER_ASCII_AUTO_SCROLL;

      //
      // Scroll if at the edges of the map
      //
      if (player->curr_at.x >= MAP_WIDTH - scroll_border) {
        auto_scroll = true;
      }
      if (player->curr_at.x < scroll_border) {
        auto_scroll = true;
      }
      if (player->curr_at.y >= MAP_HEIGHT - scroll_border) {
        auto_scroll = true;
      }
      if (player->curr_at.y < scroll_border) {
        auto_scroll = true;
      }

      //
      // Scroll if at the edges of the screen
      //
      if (player->last_ascii_at.x >= TERM_WIDTH - scroll_border) {
        auto_scroll = true;
      }
      if (player->last_ascii_at.x < scroll_border) {
        auto_scroll = true;
      }
      if (player->last_ascii_at.y >= TERM_HEIGHT - scroll_border) {
        auto_scroll = true;
      }
      if (player->last_ascii_at.y < scroll_border) {
        auto_scroll = true;
      }
    }

    //
    // Auto scroll the map ?
    //
    if (auto_scroll) {
      //
      // Auto scroll if we cross these limits
      //
      float x1 = (((float) TILES_VISIBLE_ACROSS) / 2) - x_sensitivity;
      float x2 = (((float) TILES_VISIBLE_ACROSS) / 2) + x_sensitivity;
      float y1 = (((float) TILES_VISIBLE_DOWN) / 2) - y_sensitivity;
      float y2 = (((float) TILES_VISIBLE_DOWN) / 2) + y_sensitivity;

      //
      // Auto scroll
      //
      float dx = follow.x - map_wanted_at.x;
      if (dx > x2) {
        map_wanted_at.x++;
      }
      if (dx < x1) {
        map_wanted_at.x--;
      }

      float dy = follow.y - map_wanted_at.y;
      if (dy > y2) {
        map_wanted_at.y++;
      }
      if (dy < y1) {
        map_wanted_at.y--;
      }
    }
  } else if (cursor && ! is_map_follow_player) {
    //
    // Allow the player to scroll around the scene of carnage once dead
    //
    if (player && player->is_dead) {
      return;
    }

    auto d = 0.3;

    if (sdl.mouse_x >= game->config.window_pix_width - 1) {
      map_wanted_at.x += d;
    }
    if (sdl.mouse_x <= 1) {
      map_wanted_at.x -= d;
    }
    if (sdl.mouse_y >= game->config.window_pix_height - 1) {
      map_wanted_at.y += d;
    }
    if (sdl.mouse_y <= 1) {
      map_wanted_at.y -= d;
    }
  }

  //
  // Don't allow scrolling off the map
  //
  scroll_map_set_bounds();
}
