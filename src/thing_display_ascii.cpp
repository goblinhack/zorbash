//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_ascii.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"
#include "my_unicode.hpp"

//
// For things like walls we color them differently so it is easier to see.
//
void Thing::blit_ascii_adjust_color_hue(color &c, bool fg)
{
  if (fg) {
    if (gfx_ascii_fg_color_spread_hue()) {
      if (fg) {
        c = color_change_hue(c, ((int) blit_fg_color.r) - 128);
      } else {
        c = color_change_hue(c, ((int) blit_fg_color.g) - 128);
      }
      c.a = 255;
      return;
    }

    if (c.r) {
      if (gfx_ascii_fg_color_spread_red()) {
        int adjust  = ((int) blit_fg_color.r - 128);
        int new_col = ((int) c.r) + adjust;
        if (new_col < 0) {
          new_col = 0;
        }
        if (new_col > 255) {
          new_col = 255;
        }
        c.r = new_col;
      }
    }

    if (c.g) {
      if (gfx_ascii_fg_color_spread_green()) {
        int adjust  = ((int) blit_fg_color.g - 128);
        int new_col = ((int) c.g) + adjust;
        if (new_col < 0) {
          new_col = 0;
        }
        if (new_col > 255) {
          new_col = 255;
        }
        c.g = new_col;
      }
    }

    if (c.b) {
      if (gfx_ascii_fg_color_spread_blue()) {
        int adjust  = ((int) blit_fg_color.b - 128);
        int new_col = ((int) c.b) + adjust;
        if (new_col < 0) {
          new_col = 0;
        }
        if (new_col > 255) {
          new_col = 255;
        }
        c.b = new_col;
      }
    }

    if (c.a) {
      if (gfx_ascii_fg_color_spread_alpha()) {
        int adjust  = ((int) blit_fg_color.a - 128);
        int new_col = ((int) c.a) + adjust;
        if (new_col < 0) {
          new_col = 0;
        }
        if (new_col > 255) {
          new_col = 255;
        }
        c.a = new_col;
      }
    }
  } else {
    if (gfx_ascii_bg_color_spread_hue()) {
      if (fg) {
        c = color_change_hue(c, ((int) blit_bg_color.r) - 128);
      } else {
        c = color_change_hue(c, ((int) blit_bg_color.g) - 128);
      }
      c.a = 255;
      return;
    }

    if (c.r) {
      if (gfx_ascii_bg_color_spread_red()) {
        int adjust  = ((int) blit_bg_color.r - 128);
        int new_col = ((int) c.r) + adjust;
        if (new_col < 0) {
          new_col = 0;
        }
        if (new_col > 255) {
          new_col = 255;
        }
        c.r = new_col;
      }
    }

    if (c.g) {
      if (gfx_ascii_bg_color_spread_green()) {
        int adjust  = ((int) blit_bg_color.g - 128);
        int new_col = ((int) c.g) + adjust;
        if (new_col < 0) {
          new_col = 0;
        }
        if (new_col > 255) {
          new_col = 255;
        }
        c.g = new_col;
      }
    }

    if (c.b) {
      if (gfx_ascii_bg_color_spread_blue()) {
        int adjust  = ((int) blit_bg_color.b - 128);
        int new_col = ((int) c.b) + adjust;
        if (new_col < 0) {
          new_col = 0;
        }
        if (new_col > 255) {
          new_col = 255;
        }
        c.b = new_col;
      }
    }

    if (c.a) {
      if (gfx_ascii_bg_color_spread_alpha()) {
        int adjust  = ((int) blit_bg_color.a - 128);
        int new_col = ((int) c.a) + adjust;
        if (new_col < 0) {
          new_col = 0;
        }
        if (new_col > 255) {
          new_col = 255;
        }
        c.a = new_col;
      }
    }
  }
}

//
// Adjust tile for light source color
//
void Thing::blit_ascii_adjust_color(color &c, bool fg, bool left_bar)
{
  //
  // Poor thing is frozen?
  //
  if (fg) {
    if (is_frozen) {
      if (! is_icecube()) {
        c = LIGHTBLUE;
      }
    } else if (is_burnt) {
      c = BROWN;
    }
  }

  //
  // If shown on the left bar we want the original color
  //
  if (left_bar) {
    return;
  }

  //
  // Adjust for hue etc
  //
  blit_ascii_adjust_color_hue(c, fg);

  //
  // Do not brighten things like wall fg that is black
  //
  if (c == BLACK) {
    return;
  }

  //
  // For monsters and the like, if we combine colors then we lose information, like what type of snake it is. It's
  // better instead to just fade the colors with distance.
  //
  if (gfx_ascii_fade_with_dist()) {
    float light_dist = level->player ? level->player->light_dist_get() : 1.0;
    if (light_dist <= 0.1) {
      light_dist = 0.1;
    }
    float brightness = 1.0 - (((float) distance_to_player() - 1) / light_dist);

    IF_DEBUG2 { brightness = 1.0; }

    c.r = ((float) c.r) * brightness;
    c.g = ((float) c.g) * brightness;
    c.b = ((float) c.b) * brightness;
  } else {
    //
    // Else combine the light sources, so we get a nice lava glow.
    //

    //
    // This prevents the L in lave from appearing reddish. Not sure if I want this for other things too.
    //
    if (fg) {
      if (is_lava()) {
        return;
      }
    }

    //
    // Get the combined light on this tile
    //
    fcolor combined_light = level->ascii_light_source_no_check(curr_at);
    if (combined_light == COLOR_NONE) {
      return;
    }

    float dim                  = 0.5;
    color combined_light_color = combined_light.tocolor();

    int r = (((float) c.r) * dim) + combined_light_color.r;
    if (r > 255) {
      r = 255;
    }
    c.r = r;

    int g = (((float) c.g) * dim) + combined_light_color.g;
    if (g > 255) {
      g = 255;
    }
    c.g = g;

    int b = (((float) c.b) * dim) + combined_light_color.b;
    if (b > 255) {
      b = 255;
    }
    c.b = b;
  }
}

void Thing::blit_ascii_at(point p, bool lit, bool left_bar)
{
  TRACE_NO_INDENT();

  if (is_no_tile()) {
    return;
  }

  auto tile = tile_index_to_tile(tile_curr);
  if (! tile) {
    return;
  }

  //
  // This is for walls that can be composed of multiple tiles.
  //
  if (! tile->ascii_set) {
    auto tpp  = tp();
    auto tmap = &tpp->tiles;
    tile      = tile_first(tmap);
  }

  const bool bg = false;
  const bool fg = true;

  //
  // In debug mode, show all monsters
  //
  bool shown_in_bg = gfx_ascii_shown_in_bg();

  IF_DEBUG2 { shown_in_bg = true; }

  if (gfx_ascii_shown()) {
    if (lit) {
      //
      // e.g dungeon floor
      //
      if (tile->ascii_bg_col_value != COLOR_NONE) {
        ascii_set_bg(p.x, p.y, UNICODE_BLOCK);
        color c = tile->ascii_bg_col_value;
        c.a     = tile->ascii_bg_alpha;
        blit_ascii_adjust_color(c, bg, left_bar);
        ascii_set_bg(p.x, p.y, c);
      }

      if (tile->ascii_bg_char) {
        ascii_set_bg(p.x, p.y, tile->ascii_bg_char);
      }

      if (tile->ascii_bg_col_value != COLOR_NONE) {
        color c = tile->ascii_bg_col_value;
        c.a     = tile->ascii_bg_alpha;
        blit_ascii_adjust_color(c, bg, left_bar);
        ascii_set_bg(p.x, p.y, c);
      }

      color c = tile->ascii_fg_col_value;
      c.a     = tile->ascii_fg_alpha;
      blit_ascii_adjust_color(c, fg, left_bar);

      if (tile->ascii_fg_char) {
        if (c.a != 255) {
          ascii_set_fg2(p.x, p.y, tile->ascii_fg_char);
        } else {
          ascii_set_fg(p.x, p.y, tile->ascii_fg_char);
        }
      }

      if (tile->ascii_fg_col_value != COLOR_NONE) {
        if (c.a != 255) {
          ascii_set_fg2(p.x, p.y, c);
        } else {
          ascii_set_fg(p.x, p.y, c);
        }
      }
    } else if (get(level->can_see_ever.can_see, curr_at.x, curr_at.y) || g_opt_debug2) {
      //
      // e.g unlit areas like the dungeon floor
      //
      if (shown_in_bg) {
        if (tile->ascii_bg_col_value != COLOR_NONE) {
          ascii_set_bg(p.x, p.y, UNICODE_BLOCK);
          color c = tile->ascii_bg_col_value;
          //
          // Apply a nice tint.
          //
          c.r = ((int) (c.r / 4));
          c.g = ((int) (c.g / 5));
          c.b = ((int) (c.b / 2));
          c.a = tile->ascii_fg_alpha;
          blit_ascii_adjust_color(c, bg, left_bar);

          IF_DEBUG2
          {
            if (! get(level->can_see_ever.can_see, curr_at.x, curr_at.y)) {
              c.r = ((int) (c.r / 4));
              c.g = c.r;
              c.b = c.b;
            }
          }
          ascii_set_bg(p.x, p.y, c);
        }

        if (tile->ascii_bg_char) {
          ascii_set_bg(p.x, p.y, tile->ascii_bg_char);
          color c = tile->ascii_bg_col_value;
          //
          // Apply a nice tint.
          //
          c.r = ((int) (c.r / 4));
          c.g = ((int) (c.g / 5));
          c.b = ((int) (c.b / 2));
          c.a = tile->ascii_fg_alpha;
          blit_ascii_adjust_color(c, bg, left_bar);

          //
          // This allows us to see the unvisited areas when in debug mode in a different color
          //
          IF_DEBUG2
          {
            if (! get(level->can_see_ever.can_see, curr_at.x, curr_at.y)) {
              c.r = ((int) (c.r / 4));
              c.g = c.r;
              c.b = c.b;
            }
          }
          ascii_set_bg(p.x, p.y, c);
        }

        if (tile->ascii_fg_char) {
          ascii_set_fg(p.x, p.y, tile->ascii_fg_char);
          color c = tile->ascii_fg_col_value;

          //
          // Don't hue adjust fg chars in the shadows. It just makes it harder to see.
          //
          if (gfx_ascii_shown_as_gray_in_shadow()) {
            //
            // Show items plainly so it is easier to see.
            //
            c = GRAY20;
          } else {
            //
            // Dim the char substantially.
            //
            c.r = ((int) (c.r / 4));
            c.g = ((int) (c.g / 4));
            c.b = ((int) (c.b / 4));
            c.a = tile->ascii_fg_alpha;
          }
          blit_ascii_adjust_color(c, fg, left_bar);

          //
          // This allows us to see the unvisited areas when in debug mode in a different color
          //
          IF_DEBUG2
          {
            if (! get(level->can_see_ever.can_see, curr_at.x, curr_at.y)) {
              c.r = ((int) (c.r / 4));
              c.g = c.r;
              c.b = c.b;
            }
          }
          ascii_set_fg(p.x, p.y, c);
        }
      }
    }
  }
}

void Thing::blit_ascii(point tl, point br, point p, bool left_bar)
{
  TRACE_NO_INDENT();

  is_offscreen = false;
  frame_count  = game->frame_count;

  auto tpp  = tp();
  auto blit = true;

  if (unlikely(is_changing_level)) {
    blit = false;
  } else if (unlikely(is_hidden)) {
    blit = false;
  } else if (unlikely(tpp->gfx_pixelart_attack_anim() || tpp->gfx_pixelart_equip_carry_anim())) {
    //
    // Hide weapons that have swung
    //
    if (is_dead) {
      blit = false;
    }
  } else if (is_cursor() || is_cursor_path() || is_the_grid) {
    blit = true;
  }

  auto owner = immediate_owner();
  if (owner) {
    //
    // Prevent items inside bags/chests being seen. This also works for falling.
    //
    if (owner->is_bag_item_container()) {
      blit = false;
    }

    //
    // In ascii mode we do not show equipped items
    //
    if (is_usable() && owner->is_equipped(this)) {
      blit = false;
    }

    //
    // In ascii mode we do not show carried items
    //
    if (gfx_pixelart_equip_carry_anim()) {
      blit = false;
    }
  }

  if (! blit) {
    return;
  }

  int x = tl.x + (p.x - level->minx);
  int y = tl.y + (p.y - level->miny);

  //
  // Can we see it?
  //
  bool lit;
  if (has_light) {
    lit = get(level->can_see_ever.can_see, curr_at.x, curr_at.y);
  } else {
    lit = get(level->can_see_currently.can_see, curr_at.x, curr_at.y);
  }

  if (left_bar || is_cursor() || is_cursor_path()) {
    lit = true;
  }

  blit_ascii_at(point(x, y), lit, left_bar);

  last_ascii_at = point(x, y);
  last_blit_tl  = point(curr_at.x * TILE_WIDTH, curr_at.y * TILE_HEIGHT);
  last_blit_br  = point((curr_at.x + 1) * TILE_WIDTH, (curr_at.y + 1) * TILE_HEIGHT);
  last_blit_at  = (last_blit_tl + last_blit_br) / 2;
  is_blitted    = true;
}
