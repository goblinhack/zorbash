//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_light.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::update_light(void)
{
  TRACE_AND_INDENT();
  if (! is_player()) {
    return;
  }

  if (is_hidden) {
    return;
  }

  if (! level) {
    return;
  }

  size_t c = 0;
  for (auto l : get_light()) {
    l->cached_light_pos = point(-1, -1);
    c++;
  }
}
