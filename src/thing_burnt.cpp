//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::burnt_set(void)
{
  TRACE_NO_INDENT();

  if (is_burnt) {
    return;
  }

  is_burnt = true;
  msg("%s is burnt", text_The().c_str());

  //
  // Burnt things are more tasty.
  //
  if (maybe_infop()) {
    infop()->nutrition *= 2;
  }
}
