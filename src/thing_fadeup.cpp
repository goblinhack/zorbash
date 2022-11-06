//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_math.hpp"
#include "my_thing.hpp"

#include <math.h>

void Thing::fadeup(float fadeup_height, float fadeup_fade, ts_t ms)
{
  auto t = ts_fadeup_begin_set(time_ms_cached());
  ts_fadeup_end_set(t + ms);

  fadeup_height_set(fadeup_height);
  fadeup_fade_set(fadeup_fade);
  is_fadeup = true;
}

float Thing::fadeup_curr(void)
{
  if (! is_fadeup) {
    blit_fg_color.a = 255;
    return (0.0);
  }

  auto t = time_ms_cached();

  if (t >= ts_fadeup_end()) {
    dead("by fadeup finished");
    blit_fg_color.a = 0;
    return (-1);
  }

  float time_step = ((float) (t) -ts_fadeup_begin()) / ((float) (ts_fadeup_end()) - ts_fadeup_begin());

  float height = last_blit_br.y - last_blit_tl.y;

  blit_fg_color.a = (uint8_t) (255.0 - (250.0 * time_step));

  height *= sin(time_step * RAD_90);
  height *= fadeup_height_curr();

  return height;
}
