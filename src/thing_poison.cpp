//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_thing.h"
#include "my_tile.h"

void Thing::poison_tick(void)
{
  TRACE_AND_INDENT();
  auto old_poison = get_poison();
  if (old_poison) {
    is_hit_by(this, old_poison);
    set_poison(old_poison / 2);
  }
}
