//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"
#include "my_wid_topcon.hpp"

void Thing::poison_tick(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return;
  }

  auto old_poison = get_poisoned_amount();
  if (! old_poison) {
    return;
  }

  dbg("Poison tick");
  TRACE_AND_INDENT();

  poisoned();

  Thingp hitter = this;
  int    poison = old_poison;

  if (poison) {
    poison /= 2;
    set_poisoned_amount(poison);

    if (poison) {
      if (d20() < get_stat_con()) {
        if (is_player()) {
          msg("You take half damage fron poison due to your sturdy con.");
        }
        poison /= 2;
        set_poisoned_amount(poison);
      }
    }

    if (poison) {
      is_attacked_with_damage_poison(hitter, poison);
    }
  }
}

void Thing::poisoned(void)
{
  if (is_player()) {
    debuff_add_if_not_found(tp_find("debuff_poisoned"));
  }
}
