//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"

void Thing::fall_into_the_void(void)
{
  dbg("Try to fall into the void");

  level_pop();
  is_falling                                   = false;
  is_changing_level                            = false;
  is_hidden                                    = true;
  is_waiting_to_leave_level_has_completed_fall = false;
  update_interpolated_position();
  level_push();

  if (is_dead) { return; }

  on_fall();
  if (is_player()) { msg("You fall into nothingness!"); }
  dead("by falling into the void");
}
