//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::lunge(point to)
{
  dbg("Lunge to %d,%d", to.x, to.y);
  TRACE_AND_INDENT();

  move_finish();

  auto t = ts_lunge_begin_set(time_get_time_ms_cached());
  auto p = to - curr_at;
  ts_lunge_end_set(t + 200);
  lunge_to_set(to);
  move_set_dir_from_delta(p);
}

float Thing::lunge_get(void)
{
  if (! ts_lunge_begin()) {
    return 0;
  }

  auto t = time_get_time_ms_cached();

  if (t >= ts_lunge_end()) {
    return 0;
  }

  float time_step = (float) (t - ts_lunge_begin()) / (float) (ts_lunge_end() - ts_lunge_begin());

  if (time_step > 0.5) {
    return (1.0 - time_step);
  } else {
    return time_step;
  }
}
