//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"


void Thing::wobble(float wobble)
{
  if ((paralysis_count() > 0) || is_frozen || is_burnt || is_dead) {
    return;
  }

  if (non_pcg_random_range(0, 100) < 50) {
    wobble_set(wobble);
  } else {
    wobble_set(-wobble);
  }
}

float Thing::update_wobble(void)
{
  auto w = wobble_curr();
  if (w == 0.0) {
    return 0.0;
  }

  if (fabs(w) < 2.0) {
    return 0.0;
  }

  auto new_w = w;
  new_w *= 0.90;
  new_w = -new_w;
  wobble_set(new_w);

  return w;
}

////////////////////////////////////////////////////////////////////////////
// wobble
////////////////////////////////////////////////////////////////////////////
float Thing::wobble_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->wobble);
  }
  return 0;
}

void Thing::wobble_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->wobble = v;
}

int Thing::gfx_pixelart_wobbles_when_hit(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_wobbles_when_hit());
}
