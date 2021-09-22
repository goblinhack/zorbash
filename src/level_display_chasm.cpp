//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_font.h"
#include "my_level.h"
#include "my_tex.h"
#include "my_gl.h"

//
// NOTE: chasm tiles are not blitted explicitly. Instead a floor tile
// will check for the presence of a chasm beneath it and blit the chasm
//
void Thing::blit_floor_chasm (point &tl, point &br, const ThingTiles *tiles)
{ TRACE_AND_INDENT();
  float th = game->config.tile_pix_height;

  int x = (int) mid_at.x;
  int y = (int) mid_at.y;

  if (unlikely(x <= 0) ||
    unlikely(y <= 0) ||
    unlikely(x >= MAP_WIDTH - 1) ||
    unlikely(y >= MAP_HEIGHT - 1)) {
    return;
  }

  auto tilen = tiles->bot3_tile;
  auto tile = tile_index_to_tile(tilen);
  auto maxdepth = tex_get_height(tile->tex) / TILE_HEIGHT;
  auto depth = 0U;
  while ((y < MAP_HEIGHT - 1) &&
       level->is_chasm(x, y + 1) &&
       (depth < maxdepth)) {
    depth++;
    y++;
  }

  auto dh = 5;
  float fdh = ((1.0 / maxdepth) / (float) TILE_HEIGHT) * dh;

  if (depth) {
    point tl2 = tl;
    point br2 = br;
    tl2.y += th;
    br2.y += th * depth;
    tl2.y -= dh;
    tile_blit_section_colored(tilen,
              fpoint(0, 0),
              fpoint(1, ((1.0 / maxdepth) * depth) + fdh),
              tl2, br2,
              WHITE,
              WHITE,
              WHITE,
              WHITE);
  }
}
