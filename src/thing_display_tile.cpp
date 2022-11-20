//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_thing.hpp"

//
// Blit pixel art or ascii representation.
//
void Thing::blit_tile_at(point p, bool lit, bool left_bar)
{
  TRACE_NO_INDENT();

  if (is_no_tile()) {
    return;
  }

  auto tile = tile_index_to_tile(tile_curr);
  if (! tile) {
    return;
  }

  if (! g_opt_ascii) {
    ascii_set_fg4(p.x, p.y, tile);
    return;
  }

  blit_ascii_at(p, lit, left_bar);
}
