//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::gas_healing_tick(void)
{
  TRACE_NO_INDENT();

  if (is_lava() || is_fire() || is_fire_elemental()) {
    auto intensity = level->is_gas_healing(curr_at.x, curr_at.y) / 10;
    if (intensity) {
      dbg("Healing gas explosion due to fire");
      TRACE_AND_INDENT();
      level->gas_healing_explosion(curr_at);
    }
    return;
  }

  if (! is_air_breather()) {
    return;
  }

  //
  // How strong is the gas?
  //
  auto intensity = level->is_gas_healing(curr_at.x, curr_at.y) / 20;
  if (! intensity) {
    return;
  }

  dbg("Healing gas tick");
  TRACE_AND_INDENT();

  //
  // Due to location checks, we check the start and end move so we end
  // up being healing twice per move. As this is a bit cruel, check
  //
  if (game->tick_current == tick_last_gas_healing_exposure()) {
    return;
  }
  tick_last_gas_healing_exposure_set(game->tick_current);

  if (is_alive_monst() || is_player()) {
    if (is_player()) {
      msg("%%fg=pink$You breath in the healing gas!%%fg=reset$");
    } else {
      msg("%s breathes in the healing gas!", text_The().c_str());
    }
    health_incr(d6());
    stamina_incr(d6());
  }
}

////////////////////////////////////////////////////////////////////////////
// tick_last_gas_healing_exposure
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_gas_healing_exposure(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_gas_healing_exposure);
  }
  return 0;
}

int Thing::tick_last_gas_healing_exposure_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_gas_healing_exposure = v);
}

int Thing::tick_last_gas_healing_exposure_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_gas_healing_exposure -= v);
}

int Thing::tick_last_gas_healing_exposure_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_gas_healing_exposure += v);
}

int Thing::tick_last_gas_healing_exposure_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_gas_healing_exposure--);
}

int Thing::tick_last_gas_healing_exposure_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_gas_healing_exposure++);
}
