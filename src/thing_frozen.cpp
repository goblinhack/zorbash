//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::frozen_set(void)
{
  TRACE_NO_INDENT();

  if (is_frozen) {
    return;
  }

  is_frozen = true;
  msg("%s is frozen", text_The().c_str());
}
