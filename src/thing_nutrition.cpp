//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

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

int Thing::nutrition_init(void)
{
  TRACE_NO_INDENT();

  if (tp()->nutrition_dice_str().empty()) {
    return 0;
  }

  new_infop();

  auto n = infop()->nutrition = tp()->nutrition_dice().roll();
  return n;
}

int Thing::nutrition_get(void)
{
  TRACE_NO_INDENT();

  auto infop = maybe_infop();
  if (! infop) {
    return 0;
  }

  return infop->nutrition;
}

int Thing::nutrition_decr(int v)
{
  TRACE_NO_INDENT();

  auto infop = maybe_infop();
  if (! infop) {
    return 0;
  }

  infop->nutrition -= v;
  if (infop->nutrition < 0) {
    infop->nutrition = 0;
  }

  return infop->nutrition;
}
