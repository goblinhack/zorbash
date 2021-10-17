//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_tile.h"

void Thing::poison_tick(void)
{
  if (! is_monst() && ! is_player()) {
    return;
  }

  auto old_poison = get_poison();
  if (! old_poison) {
    return;
  }

  TRACE_AND_INDENT();
  dbg("Poison tick");
  TRACE_AND_INDENT();

  debuff_add(tp_find("debuff_poisoned"));

  Thingp hitter = this;
  bool   crit   = false;
  bool   bite   = false;
  int    poison = old_poison;
  int    damage = 0;
  is_hit_by(hitter, crit, bite, poison, damage);
  set_poison(old_poison / 2);
}
