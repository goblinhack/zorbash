//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include "my_array_bounds_check.hpp"
// REMOVED #include "my_level.hpp"
// REMOVED #include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::can_detect(Thingp it)
{
  //
  // Able to see sleeping mimics as what they are
  //
  if (! is_intelligent()) {
    if (it->is_mimic() && it->is_sleeping) {
      return false;
    }
  }

  //
  // Able to see invisible monsters?
  //
  if (! is_able_to_see_invisible()) {
    if (it->is_invisible()) {
      return false;
    }
  }

  return true;
}
