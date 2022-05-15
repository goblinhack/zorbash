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

void Thing::blit_ascii(point tl, point br, point p)
{
  TRACE_NO_INDENT();

  auto tpp  = tp();
  auto blit = true;

  if (unlikely(is_changing_level)) {
    blit = false;
  } else if (unlikely(is_hidden)) {
    blit = false;
  } else if (unlikely(tpp->gfx_attack_anim() || tpp->gfx_equip_carry_anim())) {
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
    auto tmap = &tpp->tiles;
    tile      = tile_first(tmap);
  }

  int x = tl.x + (p.x - level->minx);
  int y = tl.y + (p.y - level->miny);

  auto lit = get(level->can_see_currently.can_see, curr_at.x, curr_at.y);
  IF_DEBUG2 { lit = true; }

  if (lit) {
    if (tile->ascii_bg_col_value != COLOR_NONE) {
      ascii_set_bg(x, y, UNICODE_BLOCK);
      ascii_set_bg(x, y, tile->ascii_bg_col_value);
    }

    if (tile->ascii_bg_char) {
      ascii_set_bg(x, y, tile->ascii_bg_char);
      ascii_set_bg(x, y, tile->ascii_bg_col_value);
    }

    if (tile->ascii_fg_char) {
      ascii_set_fg(x, y, tile->ascii_fg_char);
      ascii_set_fg(x, y, tile->ascii_fg_col_value);
    }
  } else if (get(level->can_see_ever.can_see, curr_at.x, curr_at.y)) {
    if (gfx_shown_in_bg()) {

      if (tile->ascii_bg_col_value != COLOR_NONE) {
        ascii_set_bg(x, y, UNICODE_BLOCK);
        color c = tile->ascii_bg_col_value;
        c.r     = ((int) (c.r / 4) * 1);
        c.g     = ((int) (c.g / 5) * 1);
        c.b     = ((int) (c.b / 2) * 1);
        ascii_set_bg(x, y, c);
      }

      if (tile->ascii_bg_char) {
        ascii_set_bg(x, y, tile->ascii_bg_char);
        color c = tile->ascii_bg_col_value;
        c.r     = ((int) (c.r / 4) * 1);
        c.g     = ((int) (c.g / 5) * 1);
        c.b     = ((int) (c.b / 2) * 1);
        ascii_set_bg(x, y, c);
      }

      if (tile->ascii_fg_char) {
        ascii_set_fg(x, y, tile->ascii_fg_char);
        color c = tile->ascii_fg_col_value;
        c.r     = ((int) (c.r / 2) * 1);
        c.g     = ((int) (c.g / 2) * 1);
        c.b     = ((int) (c.b / 2) * 1);
        ascii_set_fg(x, y, c);
      }
    }
  }

  last_ascii_at = point(x, y);
  last_blit_tl  = point(curr_at.x * TILE_WIDTH, curr_at.y * TILE_HEIGHT);
  last_blit_br  = point((curr_at.x + 1) * TILE_WIDTH, (curr_at.y + 1) * TILE_HEIGHT);
  last_blit_at  = (last_blit_tl + last_blit_br) / 2;
  is_blitted    = true;
}
