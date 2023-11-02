//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::is_reflective(void)
{
  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_reflective()) {
        return true;
      }
    }
  }

  return (tp()->is_reflective());
}
