//
// Copyright goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::size_modifier(void)
{
  switch (thing_size()) {
    case THING_SIZE_GARGANTUAN : return 4; break;
    case THING_SIZE_GIANT : return 2; break;
    case THING_SIZE_LARGE : return 1; break;
    case THING_SIZE_NORMAL : return 0; break;
    case THING_SIZE_SMALL : return 1; break;
    case THING_SIZE_TINY : return 2; break;
  }
  return 0;
}
