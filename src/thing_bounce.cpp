//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <math.h>

#include "my_thing.hpp"

void Thing::bounce(float bounce_height, float bounce_fade, ts_t ms, int bounce_count)
{
  if (g_opt_ascii) {
    return;
  }

  if (is_sleeping) {
    return;
  }

  auto t = ts_bounce_begin_set(time_ms_cached());
  ts_bounce_end_set(t + ms);

  bounce_height_set(bounce_height);
  bounce_fade_set(bounce_fade);
  bounce_count_set(bounce_count);
  is_bouncing = true;
}

float Thing::bounce_curr(void)
{
  if (! is_bouncing) {
    return (0.0);
  }

  auto t = time_ms_cached();

  if (t >= ts_bounce_end()) {
    is_bouncing = false;

    if (bounce_count() == 255) {
      //
      // Bounce forever
      //
      bounce(bounce_height_curr() * bounce_fade_curr(), bounce_fade_curr(),
             (float) (ts_bounce_end() - ts_bounce_begin()) * bounce_fade_curr(), bounce_count());
    } else if (bounce_count()) {
      bounce(bounce_height_curr() * bounce_fade_curr(), bounce_fade_curr(),
             (float) (ts_bounce_end() - ts_bounce_begin()) * bounce_fade_curr(), bounce_count() - 1);
    }

    return 0;
  }

  float time_step = (float) (t - ts_bounce_begin()) / (float) (ts_bounce_end() - ts_bounce_begin());

  float height = 1.0;

  height *= sin(time_step * RAD_180);
  height *= bounce_height_curr();

  return (height);
}
