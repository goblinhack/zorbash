//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"

//
// Trail of blood?
//
void Thing::place_blood(bool force)
{
  if (! is_bleeder()) { return; }

  if (! force) {
    if (! is_bloodied()) { return; }

    //
    // Not too much blood
    //
    if (pcg_random_range(1, 100) <= 80) { return; }
  }

  auto placed_blood = false;

  if (is_red_blooded()) {
    if (! level->is_red_blood(curr_at.x, curr_at.y)) {
      auto tp = tp_random_red_blood();
      (void) level->thing_new(tp->name(), curr_at);
      placed_blood = true;
    }
  }

  if (is_green_blooded()) {
    if (! level->is_green_blood(curr_at.x, curr_at.y)) {
      auto tp = tp_random_green_blood();
      (void) level->thing_new(tp->name(), curr_at);
      placed_blood = true;
    }
  }

  //
  // If the monster was alredy wounded and dies, add some gory text
  //
  if (placed_blood) {
    auto h = health();
    if ((h > 0) && (h < health_max() / 2)) {
      h = health_decr();
      if (h <= 0) {
        h = health_set(0);
        msg("%s bleeds out!", text_The().c_str());
        dead("by bleeding out");
      }
    } else {
      h = health_decr();
      if (h <= 0) { health_set(0); }
    }
  }
}
