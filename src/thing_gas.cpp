//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

void Thing::gas_poison_tick(void)
{
  TRACE_NO_INDENT();

  if (is_fire()) {
    auto intensity = level->is_gas_poison(curr_at.x, curr_at.y) / 10;
    if (intensity) {
      level->poison_gas_explosion(curr_at);
    }
    return;
  }

  if (! is_ait_breather()) {
    return;
  }

  auto intensity = level->is_gas_poison(curr_at.x, curr_at.y) / 10;
  if (! intensity) {
    return;
  }

  dbg("Poison gas tick");
  TRACE_AND_INDENT();

  if (d20() < stat_con()) {
    if (is_player()) {
      msg("You hold your breath in the gas.");
    }
    return;
  }

  poisoned_amount_incr(pcg_random_range(1, intensity));

  if (stamina()) {
    if (is_player()) {
      msg("You choke in the gas.");
    }
    stamina_decr(d20());
  } else {
    if (is_player()) {
      msg("You are trapped in the gas! You feel like a very long nap.");
    }
  }
}
