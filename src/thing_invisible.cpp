//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::invisible_tick(void) { is_currently_invisible = is_invisible(); }

bool Thing::is_invisible(void)
{
  TRACE_NO_INDENT();

  if (buff_is_invisible()) {
    return true;
  }

  return (tp()->is_invisible());
}
