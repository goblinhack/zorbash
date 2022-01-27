//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::fall_into_the_void(void)
{
  if (is_dead()) {
    return;
  }

  level_pop();
  is_falling        = false;
  is_changing_level = false;
  is_hidden         = true;
  update_interpolated_position();
  level_push();

  if (is_player()) {
    msg("You fall into nothingness!");
  }
  dead("by falling into the void");
}
