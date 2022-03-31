//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

//
// Trail of blood?
//
void Thing::place_blood(bool force)
{
  if (! is_bleeder()) {
    return;
  }

  if (! force) {
    if (! is_bloodied()) {
      return;
    }
  }

  if (is_red_blooded()) {
    if (! level->is_red_blood(curr_at.x, curr_at.y)) {
      auto tp = tp_random_red_blood();
      (void) level->thing_new(tp->name(), curr_at);
    }
  }

  if (is_green_blooded()) {
    if (! level->is_green_blood(curr_at.x, curr_at.y)) {
      auto tp = tp_random_green_blood();
      (void) level->thing_new(tp->name(), curr_at);
    }
  }

  if (is_pink_blooded()) {
    if (! level->is_pink_blood(curr_at.x, curr_at.y)) {
      auto tp = tp_random_pink_blood();
      (void) level->thing_new(tp->name(), curr_at);
    }
  }
}
