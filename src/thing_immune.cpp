//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

int Thing::is_immune_to_cold(void)
{
  TRACE_NO_INDENT();
  if (buff_is_immune_to_cold()) {
    return true;
  }
  return (tp()->is_immune_to_cold());
}

int Thing::is_immune_to_negation(void)
{
  TRACE_NO_INDENT();
  if (buff_is_immune_to_negation()) {
    return true;
  }
  return (tp()->is_immune_to_negation());
}

int Thing::is_immune_to_teleport_attack(void)
{
  TRACE_NO_INDENT();
  if (buff_is_immune_to_teleport_attack()) {
    return true;
  }
  return (tp()->is_immune_to_teleport_attack());
}

int Thing::is_immune_to_fire(void)
{
  TRACE_NO_INDENT();
  if (buff_is_immune_to_fire()) {
    return true;
  }
  return (tp()->is_immune_to_fire());
}

int Thing::is_immune_to_poison(void)
{
  TRACE_NO_INDENT();
  if (buff_is_immune_to_poison()) {
    return true;
  }
  return (tp()->is_immune_to_poison());
}

int Thing::is_immune_to_water(void)
{
  TRACE_NO_INDENT();
  if (buff_is_immune_to_water()) {
    return true;
  }
  return (tp()->is_immune_to_water());
}

int Thing::is_immune_to_necrosis(void)
{
  TRACE_NO_INDENT();
  if (buff_is_immune_to_necrosis()) {
    return true;
  }
  return (tp()->is_immune_to_necrosis());
}

int Thing::is_immune_to_draining(void)
{
  TRACE_NO_INDENT();
  if (buff_is_immune_to_draining()) {
    return true;
  }
  return (tp()->is_immune_to_draining());
}

int Thing::is_immune_to_spiderwebs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_spiderwebs());
}

int Thing::is_immune_to_electricity(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_electricity());
}
