//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::lunge(fpoint to)
{
  auto t = set_ts_lunge_begin(time_get_time_ms_cached());
  auto p = to - mid_at;
  set_ts_lunge_end(t + 200);
  set_lunge_to(to);
  move_set_dir_from_delta(p);
}

float Thing::get_lunge(void)
{
  if (! get_ts_lunge_begin()) {
    return (0);
  }

  auto t = time_get_time_ms_cached();

  if (t >= get_ts_lunge_end()) {
    return (0);
  }

  float time_step = (float) (t - get_ts_lunge_begin()) / (float) (get_ts_lunge_end() - get_ts_lunge_begin());

  if (time_step > 0.5) {
    return (1.0 - time_step);
  } else {
    return time_step;
  }
}
