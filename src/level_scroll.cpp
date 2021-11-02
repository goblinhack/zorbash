//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid.hpp"
#include "my_wid_rightbar.hpp"

void Level::scroll_map_do(bool fast)
{
  TRACE_AND_INDENT();
  if (! fast) {
    //
    // Not sure why I have this :)
    //
    if (wid_find_under_mouse_when_scrolling()) {
      return;
    }
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
  player->topcon("map_at %f %f map_wanted_at %f %f",
          map_at.x,
          map_at.y,
          map_wanted_at.x,
          map_wanted_at.y);
}
#endif

  //
  // If following the player scroll in smaller chunks
  //
  if (map_follow_player) {
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
        // This used to be a thing when I did not have pixel
        // accurate map and rounded pixels were a thing.
        //
        // dx *= TILE_WIDTH;
        // dx = (int) ceil(dx);
        // dx /= TILE_WIDTH;
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
        map_at.y += dy;
      }
    }
  } else {
    //
    // Else following the cursor or mouse. Bigger chunks are less sick
    // inducing.
    //
    if (fast) {
      map_at.x -= dx;
      map_at.y -= dy;
    } else {
      map_at.x -= dx / bigstep;
      map_at.y -= dy / bigstep;
    }
  }

  //
  // Round to pixels
  //
  map_at.x *= TILE_WIDTH;
  map_at.y *= TILE_HEIGHT;
  map_at.x = (int) map_at.x;
  map_at.y = (int) map_at.y;
  map_at.x /= TILE_WIDTH;
  map_at.y /= TILE_HEIGHT;

#ifdef LIMIT_SCROLLING_TO_MAP
  map_at.x = std::max(map_at.x, (float) 0.0);
  map_at.y = std::max(map_at.y, (float) 0.0);
  map_at.x = std::min(map_at.x, (float) MAP_WIDTH - TILES_ACROSS);
  map_at.y = std::min(map_at.y, (float) MAP_HEIGHT - TILES_DOWN);
#endif

  {
    auto dx = map_at.x - map_wanted_at.x;
    auto dy = map_at.y - map_wanted_at.y;

    if (fabs(dx) < 0.1) {
      dx = 0;
    }

    if (fabs(dy) < 0.1) {
      dy = 0;
    }
  }
}

void Level::scroll_map(void)
{
  TRACE_AND_INDENT();
  if (wid_find_under_mouse_when_scrolling()) {
    return;
  }

  scroll_map_do(false);
}

void Level::scroll_map_to_player(void)
{
  TRACE_AND_INDENT();
  if (! player) {
    return;
  }

  mouse_at          = -1;
  mouse_old         = -1;
  ts_redraw_bg      = time_get_time_ms_cached() + 500;
  map_follow_player = true;

  map_wanted_at = make_fpoint(player->mid_at) - fpoint(TILES_ACROSS / 2, TILES_DOWN / 2);

  scroll_map_set_target();
  scroll_map_do(true);
}

void Level::scroll_map_to_player_immediately(void)
{
  TRACE_AND_INDENT();
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
  TRACE_AND_INDENT();
  fpoint follow;
  float  sensitivity;
  float  x_sensitivity;
  float  y_sensitivity;

  if (wid_find_under_mouse_when_scrolling()) {
    return;
  }

  if (player && map_follow_player) {
    follow        = make_fpoint(player->mid_at);
    sensitivity   = 0.5;
    x_sensitivity = sensitivity * game->config.video_w_h_ratio;
    y_sensitivity = sensitivity;

    //
    // Auto scroll if we cross these limits
    //
    float x1 = ((float) TILES_ACROSS / 2) - x_sensitivity;
    float x2 = ((float) TILES_ACROSS / 2) + x_sensitivity;
    float y1 = ((float) TILES_DOWN / 2) - y_sensitivity;
    float y2 = ((float) TILES_DOWN / 2) + y_sensitivity;

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
  } else if (cursor && ! map_follow_player) {
    //
    // Allow the player to scroll around the scene of carnage
    // once dead
    //
    if (player && player->is_dead) {
      return;
    }

    auto d = 0.3;
    if (mouse_x >= game->config.window_pix_width - 1) {
      map_wanted_at.x += d;
    }
    if (mouse_x <= 1) {
      map_wanted_at.x -= d;
    }
    if (mouse_y >= game->config.window_pix_height - 1) {
      map_wanted_at.y += d;
    }
    if (mouse_y <= 1) {
      map_wanted_at.y -= d;
    }
  }

#ifdef LIMIT_SCROLLING_TO_MAP
  //
  // Don't allow scrolling off the map
  //
  if (map_wanted_at.x < 0) {
    map_wanted_at.x = 0;
  }
  if (map_wanted_at.y < 0) {
    map_wanted_at.y = 0;
  }
  if (map_wanted_at.x > MAP_WIDTH - 1) {
    map_wanted_at.x = MAP_WIDTH - 1;
  }
  if (map_wanted_at.y > MAP_HEIGHT - 1) {
    map_wanted_at.y = MAP_HEIGHT - 1;
  }
#endif
}
