//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::gas_poison_tick(void)
{
  TRACE_NO_INDENT();

  if (! is_breather()) {
    return;
  }

  auto intensity = level->is_gas_poison(curr_at.x, curr_at.y) / 10;
  if (! intensity) {
    return;
  }

  dbg("Poison gas tick");
  TRACE_AND_INDENT();

  if (d20() < get_stat_con()) {
    if (is_player()) {
      msg("You hold your breath in the gas.");
    }
    return;
  }

  incr_poisoned_amount(pcg_random_range(1, intensity));

  if (get_stamina()) {
    if (is_player()) {
      msg("You choke in the gas.");
    }
    decr_stamina(d20());
  } else {
    if (is_player()) {
      msg("You are trapped in the gas! You feel like a very long nap.");
    }
  }
}
