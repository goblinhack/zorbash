//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_game.h"

void Thing::msg(std::string const &m)
{
  static point    last_at;
  float           dy;
  float           dx;
  static uint32_t last_tick;

  if (game->tick_current == last_tick) {
    //
    // Stop msgs piling up in the same tick
    //
    if (last_at.y == mid_at.y) {
      dy = 1.0;
    } else {
      dy = 0.0;
    }

    if (last_at.x == mid_at.x) {
      dx = 1.0;
    } else {
      dx = 0.0;
    }
  } else {
    dx = 0.0;
    dy = 0.0;
  }

  last_tick = game->tick_current;

  last_at.x = mid_at.x - dx;
  last_at.y = mid_at.y - dy;

  auto msg = level->thing_new("msg", mid_at - fpoint(dx, dy));
  msg->set_msg(m);
  msg->fadeup(6.0, 0.05, 3000);
}
