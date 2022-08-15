//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

const Dice &Thing::nutrition_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->nutrition_dice());
}

const std::string &Thing::nutrition_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->nutrition_dice_str());
}

int Thing::nutrition_get(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _infop)) {
    new_infop();
  }
  if (infop()->nutrition == -1) {
    infop()->nutrition = tp()->nutrition_dice().roll();
  }
  return infop()->nutrition;
}
