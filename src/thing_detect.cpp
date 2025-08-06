//
// Copyright goblinhack@gmail.com
//

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
