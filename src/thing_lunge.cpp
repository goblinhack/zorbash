//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::lunge(point to)
{
  if (is_sleeping) {
    return;
  }

  if (is_frozen || is_burnt || is_dead) {
    return;
  }

  //
  // Already lunging? This can happen when swinging a weapon that hits in multiple
  // directions. Don't make the player dizzy and focus on the intial lunge.
  //
  if (ts_lunge_begin()) {
    return;
  }

  dbg("Lunge to %d,%d", to.x, to.y);
  TRACE_AND_INDENT();

  move_finish();

  //
  // Check if we can lunge
  //
  FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_OBJ)
  {
    if (t == this) {
      continue;
    }
    if (t->is_block_of_ice()) {
      dbg("No lunging when stuck in ice");
      return;
    }
    if (t->is_very_heavy()) {
      dbg("No lunging when stuck under something heavy");
      return;
    }
  }
  FOR_ALL_THINGS_END()

  auto t = ts_lunge_begin_set(time_ms_cached());
  auto p = to - curr_at;
  ts_lunge_end_set(t + 200);
  lunge_to_set(to);
  move_set_dir_from_delta(p);
}

float Thing::lunge_curr(void)
{
  if (! ts_lunge_begin()) {
    return 0;
  }

  auto t = time_ms_cached();

  if (t >= ts_lunge_end()) {
    ts_lunge_begin_set(0);
    ts_lunge_end_set(0);
    return 0;
  }

  float time_step = ((float) (t) -ts_lunge_begin()) / ((float) (ts_lunge_end()) - ts_lunge_begin());

  if (time_step > 0.5) {
    return (1.0 - time_step);
  }
  return time_step;
}
