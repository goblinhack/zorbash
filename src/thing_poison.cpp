//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_topcon.hpp"

void Thing::poison_tick(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return;
  }

  auto old_poison = poisoned_amount();
  if (! old_poison) {
    return;
  }

  dbg("Poison tick");
  TRACE_AND_INDENT();

  poisoned();

  Thingp hitter = this;
  int    poison = old_poison;

  if (poison) {
    auto new_poison = poison / 2;

    if (poison) {
      if (d20() < stat_con()) {
        if (is_player()) {
          msg("You take half damage fron poison due to your sturdy constitution.");
        }
        new_poison = poison / 2;
      }
    }

    //
    // Do not let poison go to zero if still in the gas. This stops messages that
    // look like you have recovered.
    //
    if (is_breather()) {
      auto intensity = level->is_gas_poison(curr_at.x, curr_at.y) / 10;
      if (intensity) {
        if (! new_poison) {
          new_poison = 1;
        }
      }
    }

    poisoned_amount_set(new_poison);

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
