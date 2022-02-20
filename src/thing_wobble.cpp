//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <math.h>

#include "my_thing.hpp"

void Thing::wobble(float wobble) { wobble_set(wobble); }

float Thing::update_wobble(void)
{
  auto w = wobble_curr();
  if (w == 0.0) {
    return 0.0;
  }

  if (fabs(w) < 0.01) {
    return 0.0;
  }

  auto new_w = w;
  new_w *= 0.75;
  new_w = -new_w;
  wobble_set(new_w);

  return w;
}
