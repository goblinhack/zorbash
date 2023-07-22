//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::gas_poison_tick(void)
{
  TRACE_NO_INDENT();

  if (is_fire() || is_fire_elemental()) {
    auto intensity = level->is_gas_poison(curr_at.x, curr_at.y) / 10;
    if (intensity) { level->poison_gas_explosion(curr_at); }
    return;
  }

  if (! is_air_breather()) { return; }

  //
  // How strong is the gas?
  //
  auto intensity = level->is_gas_poison(curr_at.x, curr_at.y) / 20;
  if (! intensity) { return; }

  dbg("Poison gas tick");
  TRACE_AND_INDENT();

  //
  // Due to location checks, we check the start and end move so we end
  // up being poisoned twice per move. As this is a bit cruel, check
  //
  if (game->tick_current == tick_last_poison_gas_exposure()) { return; }
  tick_last_poison_gas_exposure_set(game->tick_current);

  if (d20() < stat_con()) {
    if (is_player()) { msg("You hold your breath in the poison gas!"); }
    return;
  }

  poisoned_amount_incr(pcg_random_range(1, intensity));

  if (stamina()) {
    if (is_player()) { msg("%%fg=yellow$You choke in the poison gas!%%fg=reset$"); }
    stamina_decr(d20());
  } else {
    if (is_player()) { msg("You are still trapped in the gas! You feel like a very long nap."); }
  }
}

////////////////////////////////////////////////////////////////////////////
// tick_last_poison_gas_exposure
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_poison_gas_exposure(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->tick_last_poison_gas_exposure); }
  return 0;
}

int Thing::tick_last_poison_gas_exposure_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_poison_gas_exposure = v);
}

int Thing::tick_last_poison_gas_exposure_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_poison_gas_exposure -= v);
}

int Thing::tick_last_poison_gas_exposure_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_poison_gas_exposure += v);
}

int Thing::tick_last_poison_gas_exposure_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_poison_gas_exposure--);
}

int Thing::tick_last_poison_gas_exposure_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_poison_gas_exposure++);
}
