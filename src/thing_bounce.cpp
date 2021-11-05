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
  auto t = set_ts_bounce_begin(time_get_time_ms_cached());
  set_ts_bounce_end(t + ms);

  set_bounce_height(bounce_height);
  set_bounce_fade(bounce_fade);
  set_bounce_count(bounce_count);
  is_bouncing = true;
}

float Thing::get_bounce(void)
{
  if (! is_bouncing) {
    return (0.0);
  }

  auto t = time_get_time_ms_cached();

  if (t >= get_ts_bounce_end()) {
    is_bouncing = false;

    if (get_bounce_count() == 255) {
      //
      // Bounce forever
      //
      bounce(get_bounce_height() * get_bounce_fade(), get_bounce_fade(),
             (float) (get_ts_bounce_end() - get_ts_bounce_begin()) * get_bounce_fade(), get_bounce_count());
    } else if (get_bounce_count()) {
      bounce(get_bounce_height() * get_bounce_fade(), get_bounce_fade(),
             (float) (get_ts_bounce_end() - get_ts_bounce_begin()) * get_bounce_fade(), get_bounce_count() - 1);
    }

    return 0;
  }

  float time_step = (float) (t - get_ts_bounce_begin()) / (float) (get_ts_bounce_end() - get_ts_bounce_begin());

  float height = 1.0;

  height *= sin(time_step * RAD_180);
  height *= get_bounce_height();

  return (height);
}
