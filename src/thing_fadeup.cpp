//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <math.h>

#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::fadeup (float fadeup_height,
          float fadeup_fade,
          ts_t ms)
{
  auto t = set_ts_fadeup_begin(time_get_time_ms_cached());
  set_ts_fadeup_end(t + ms);

  set_fadeup_height(fadeup_height);
  set_fadeup_fade(fadeup_fade);
  is_fadeup = true;
}

float Thing::get_fadeup (void)
{
  if (!is_fadeup) {
    alpha = 255;
    return (0.0);
  }

  auto t = time_get_time_ms_cached();

  if (t >= get_ts_fadeup_end()) {
    dead("by fadeup finished");
    alpha = 0;
    return (-1);
  }

  float time_step =
    (float)(t - get_ts_fadeup_begin()) /
    (float)(get_ts_fadeup_end() - get_ts_fadeup_begin());

  float height = last_blit_br.y - last_blit_tl.y;

  alpha = (uint8_t)(255.0 - (250.0 * time_step));

  height *= sin(time_step * RAD_90);
  height *= get_fadeup_height();

  return (height);
}
