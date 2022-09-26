//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::can_see(point p)
{
  if (! is_player()) {
    return;
  }

  FOR_ALL_THINGS_THAT_INTERACT(level, t, p.x, p.x)
  {
    //
    // Display a message when a monster comes into view
    //
    if (t->is_monst()) {
      if (t->is_bloodied()) {
        if (! t->is_wounded_msg) {
          t->is_wounded_msg = true;
          if (! t->is_seen_msg) {
            t->is_seen_msg = true;
            if (t->msg_is_seen()) {
              msg("%s wounded comes into view.", t->text_A_or_An().c_str());
            }
          } else {
            if (t->msg_is_wounded()) {
              msg("%s is wounded.", t->text_A_or_An().c_str());
            }
          }
        }
      }

      if (! t->is_seen_msg) {
        t->is_seen_msg = true;
        if (t->msg_is_seen()) {
          msg("%s comes into view.", t->text_A_or_An().c_str());
        }
      }
    }
  }
  FOR_ALL_THINGS_END()
}
