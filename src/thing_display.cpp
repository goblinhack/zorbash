//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"

//
// Common to both ascii and pixelart modes. Should we show an outline for the thing?
//
bool Thing::blit_outline_should_be_shown(color &outline_color)
{
  TRACE_NO_INDENT();

  bool outline_shown = false;

  static uint8_t  alpha = 128;
  static int      step  = 10;
  static int      dir   = 1;
  static uint32_t ts;

  if (time_have_x_hundredths_passed_since(2, ts)) {
    alpha += dir * step;
    if (alpha > 240) {
      dir = -1;
    } else if (alpha < 100) {
      dir = 1;
    }
    ts = time_ms_cached();
  }

  //
  // Allow secret doors a chance to be seen
  //
  if (is_secret_door() && discovered()) {
    outline_color = DARKRED;
    outline_shown = true;
  }

  if (! is_dead) {
    //
    // If invisible then show the player. Don't show monsters.
    //
    if (is_invisible_currently()) {
      //
      // Invisible
      //
      if (is_player()) {
        if (is_stuck_currently()) {
          outline_color = DARKRED;
        } else if (is_raging()) {
          outline_color = ORANGE;
        } else {
          outline_color = WHITE;
        }
        outline_shown = true;
      }
    } else {
      //
      // Visible
      //
      if (is_stuck_currently()) {
        outline_color = RED;
        outline_shown = true;
      } else if (is_raging()) {
        if (is_player() || is_monst()) {
          outline_color = ORANGE;
          outline_shown = true;
        }
      }
    }
  }

  //
  // Show phantoms as an outline?
  //
  if (is_monst()) {
    bool is_invisible_show_outline = is_invisible_currently();
    if (tile_curr) {
      auto tile = tile_index_to_tile(tile_curr);
      if (tile && tile->is_invisible) {
        if (level && (level->is_gas_poison(curr_at.x, curr_at.y) || level->is_gas_healing(curr_at.x, curr_at.y))) {
          is_invisible_show_outline = true;
        }
      }
    }

    if (is_invisible_show_outline) {
      outline_color = WHITE;
      outline_shown = true;
    }
  }

  if (gfx_pixelart_show_highlighted() && ! immediate_owner()) {
    if ((this == game->current_wid_thing_info) || (level->cursor && (this->curr_at == level->cursor->curr_at))) {
      outline_color = RED;
      outline_shown = true;
    }
  }

  outline_color.a = alpha;

  return outline_shown;
}
