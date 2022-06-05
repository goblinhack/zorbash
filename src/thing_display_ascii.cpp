//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
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
// For things liek walls we color them differently so it is easier to see.
//
void Thing::blit_ascii_adjust_color(color &c, bool fg)
{
  if (gfx_ascii_mode_color_spread_hue()) {
    if (fg) {
      c = color_change_hue(c, ((int) blit_color.r) - 128);
    } else {
      c = color_change_hue(c, ((int) blit_color.g) - 128);
    }
    c.a = 255;
    return;
  }

  if (c.r) {
    if (gfx_ascii_mode_color_spread_red()) {
      int adjust  = ((int) blit_color.r - 128);
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
    if (gfx_ascii_mode_color_spread_green()) {
      int adjust  = ((int) blit_color.g - 128);
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
    if (gfx_ascii_mode_color_spread_blue()) {
      int adjust  = ((int) blit_color.b - 128);
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
    if (gfx_ascii_mode_color_spread_alpha()) {
      int adjust  = ((int) blit_color.a - 128);
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

void Thing::blit_ascii_at(point p, bool lit)
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

  if (gfx_ascii_mode_shown()) {
    if (lit) {
      //
      // e.g dungeon floor
      //
      if (tile->ascii_bg_col_value != COLOR_NONE) {
        ascii_set_bg(p.x, p.y, UNICODE_BLOCK);
        color c = tile->ascii_bg_col_value;
        c.a     = tile->ascii_alpha;
        blit_ascii_adjust_color(c, bg);
        ascii_set_bg(p.x, p.y, c);
      }

      if (tile->ascii_bg_char) {
        ascii_set_bg(p.x, p.y, tile->ascii_bg_char);
      }

      if (tile->ascii_bg_col_value != COLOR_NONE) {
        color c = tile->ascii_bg_col_value;
        c.a     = tile->ascii_alpha;
        blit_ascii_adjust_color(c, bg);
        ascii_set_bg(p.x, p.y, c);
      }

      if (tile->ascii_fg_char) {
        ascii_set_fg(p.x, p.y, tile->ascii_fg_char);
      }

      if (tile->ascii_fg_col_value != COLOR_NONE) {
        color c = tile->ascii_fg_col_value;
        c.a     = tile->ascii_alpha;
        blit_ascii_adjust_color(c, fg);
        ascii_set_fg(p.x, p.y, c);
      }
    } else if (get(level->can_see_ever.can_see, curr_at.x, curr_at.y)) {
      //
      // e.g unlit dungeon floor
      //
      if (gfx_shown_in_bg()) {
        if (tile->ascii_bg_col_value != COLOR_NONE) {
          ascii_set_bg(p.x, p.y, UNICODE_BLOCK);
          color c = tile->ascii_bg_col_value;
          c.r     = ((int) (c.r / 4) * 1);
          c.g     = ((int) (c.g / 5) * 1);
          c.b     = ((int) (c.b / 2) * 1);
          c.a     = tile->ascii_alpha;
          blit_ascii_adjust_color(c, bg);
          ascii_set_bg(p.x, p.y, c);
        }

        if (tile->ascii_bg_char) {
          ascii_set_bg(p.x, p.y, tile->ascii_bg_char);
          color c = tile->ascii_bg_col_value;
          c.r     = ((int) (c.r / 4) * 1);
          c.g     = ((int) (c.g / 5) * 1);
          c.b     = ((int) (c.b / 2) * 1);
          c.a     = tile->ascii_alpha;
          blit_ascii_adjust_color(c, bg);
          ascii_set_bg(p.x, p.y, c);
        }

        if (tile->ascii_fg_char) {
          ascii_set_fg(p.x, p.y, tile->ascii_fg_char);
          color c = tile->ascii_fg_col_value;
          c.r     = ((int) (c.r / 2) * 1);
          c.g     = ((int) (c.g / 2) * 1);
          c.b     = ((int) (c.b / 2) * 1);
          c.a     = tile->ascii_alpha;
          blit_ascii_adjust_color(c, fg);
          ascii_set_fg(p.x, p.y, c);
        }
      }
    }
  }
}

void Thing::blit_ascii(point tl, point br, point p)
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

  if (! blit) {
    return;
  }

  int x = tl.x + (p.x - level->minx);
  int y = tl.y + (p.y - level->miny);

  auto lit = get(level->can_see_currently.can_see, curr_at.x, curr_at.y);
  IF_DEBUG2 { lit = true; }

  if (is_cursor() || is_cursor_path()) {
    lit = true;
  }

  blit_ascii_at(point(x, y), lit);

  last_ascii_at = point(x, y);
  last_blit_tl  = point(curr_at.x * TILE_WIDTH, curr_at.y * TILE_HEIGHT);
  last_blit_br  = point((curr_at.x + 1) * TILE_WIDTH, (curr_at.y + 1) * TILE_HEIGHT);
  last_blit_at  = (last_blit_tl + last_blit_br) / 2;
  is_blitted    = true;
}
