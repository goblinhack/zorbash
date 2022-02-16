//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
// REMOVED #include "my_sprintf.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::popup(std::string const &m)
{
  static point    last_at;
  float           dy;
  float           dx;
  static uint32_t last_tick;

  if (game->tick_current == last_tick) {
    //
    // Stop msgs piling up in the same tick
    //
    if (last_at.y == curr_at.y) {
      dy = 10.0;
    } else {
      dy = 0.0;
    }

    if (last_at.x == curr_at.x) {
      dx = 1.0;
    } else {
      dx = 0.0;
    }
  } else {
    dx = 0.0;
    dy = 0.0;
  }

  last_tick = game->tick_current;

  last_at.x = curr_at.x - dx;
  last_at.y = curr_at.y - dy;

  auto msg = level->thing_new("msg", curr_at - point(dx, dy));
  msg->msg_set(m);
  msg->fadeup(6.0, 0.05, 3000);
}
