//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <math.h>

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::bounce(float bounce_height, float bounce_fade, ts_t ms, int bounce_count)
{
  auto t = ts_bounce_begin_set(time_get_time_ms_cached());
  ts_bounce_end_set(t + ms);

  bounce_height_set(bounce_height);
  bounce_fade_set(bounce_fade);
  bounce_count_set(bounce_count);
  is_bouncing = true;
}

float Thing::bounce_get(void)
{
  if (! is_bouncing) {
    return (0.0);
  }

  auto t = time_get_time_ms_cached();

  if (t >= ts_bounce_end_get()) {
    is_bouncing = false;

    if (bounce_count_get() == 255) {
      //
      // Bounce forever
      //
      bounce(bounce_height_get() * bounce_fade_get(), bounce_fade_get(),
             (float) (ts_bounce_end_get() - ts_bounce_begin_get()) * bounce_fade_get(), bounce_count_get());
    } else if (bounce_count_get()) {
      bounce(bounce_height_get() * bounce_fade_get(), bounce_fade_get(),
             (float) (ts_bounce_end_get() - ts_bounce_begin_get()) * bounce_fade_get(), bounce_count_get() - 1);
    }

    return 0;
  }

  float time_step = (float) (t - ts_bounce_begin_get()) / (float) (ts_bounce_end_get() - ts_bounce_begin_get());

  float height = 1.0;

  height *= sin(time_step * RAD_180);
  height *= bounce_height_get();

  return (height);
}
