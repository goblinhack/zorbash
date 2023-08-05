//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

int Thing::health_regenerate(void)
{
  TRACE_NO_INDENT();

  if (! is_able_to_regenerate()) {
    return false;
  }

  if (d1000() > chance_d1000_regenerate()) {
    return false;
  }

  health_boost(nullptr, health_regenerate_amount());

  return true;
}

const Dice &Thing::health_regenerate_amount_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_regenerate_amount_dice());
}

const std::string &Thing::health_regenerate_amount_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_regenerate_amount_dice_str());
}

int Thing::health_regenerate_amount(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_regenerate_amount_dice().roll());
}

int Thing::chance_d1000_regenerate(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_regenerate());
}

int Thing::is_able_to_regenerate(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_regenerate());
}
