//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"

void Thing::floating_tick(void) { is_floating_ = is_floating(); }

bool Thing::is_floating(void)
{
  TRACE_NO_INDENT();

  auto old_is_currently_floating = is_floating_;
  bool new_is_currently_floating = tp()->is_floating();

  if (buff_floating()) {
    new_is_currently_floating = true;
  }

  if (old_is_currently_floating != new_is_currently_floating) {
    level_pop();
    is_floating_ = new_is_currently_floating;
    level_push();
  }

  return is_floating_;
}

bool Thing::is_floating_currently(void) { return is_floating_; }
