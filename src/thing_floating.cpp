//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_math.hpp"
#include "my_thing.hpp"
// REMOVED #include <math.h>

void Thing::floating_tick(void) { is_floating_ = is_floating(); }

bool Thing::is_floating(void)
{
  TRACE_NO_INDENT();

  auto old_is_currently_floating = is_floating_;
  bool new_is_currently_floating = tp()->is_floating();

  if (buff_floating()) {
    new_is_currently_floating = true;
  }

  if (old_is_currently_floating != new_is_currently_floating) {
    level_pop();
    is_floating_ = new_is_currently_floating;
    level_push();
  }

  return is_floating_;
}

bool Thing::is_floating_currently(void) { return is_floating_; }

float Thing::floating_curr(void)
{
  if (! is_floating_) {
    return 0.0;
  }

  if (is_dead_or_dying()) {
    return 0.0;
  }

  auto t = time_ms_cached();

  float time_step = (float) (t);
  float height    = 0.15;
  height *= sin((time_step / 1000.0) * RAD_180);
  height += 0.3;

  return height;
}
