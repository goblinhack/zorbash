//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::can_see(point p)
{
  if (! is_player()) {
    return;
  }

  FOR_ALL_THINGS_THAT_INTERACT(level, t, p.x, p.y)
  {
    //
    // Display a message when a monster comes into view
    //
    if (t->is_monst()) {
      if (! t->is_seen_msg) {
        t->is_seen_msg = true;
        if (t->msg_is_seen()) {
          if (t->is_sleeping) {
            msg("A snoozing %s comes into view.", t->text_long_name().c_str());
          } else if (t->is_stuck_currently()) {
            msg("A stuck %s comes into view.", t->text_long_name().c_str());
          } else {
            msg("%s comes into view.", t->text_A_or_An().c_str());
          }

          FOR_ALL_EQUIP(e)
          {
            auto item = t->equip_get(e);
            if (! item) {
              continue;
            }
            if (item->is_ring() || item->is_helmet() || item->is_amulet()) {
              msg("%s is wearing a %s.", t->text_The().c_str(), item->text_long_name().c_str());
            }
            if (item->is_cloak()) {
              msg("%s is styled in a %s.", t->text_The().c_str(), item->text_long_name().c_str());
            }
            if (item->is_gauntlet() || item->is_armor()) {
              msg("%s is wearing %s.", t->text_The().c_str(), item->text_long_name().c_str());
            }
            if (item->is_boots()) {
              msg("%s is sporting %s.", t->text_The().c_str(), item->text_long_name().c_str());
            }
            if (item->is_shield()) {
              msg("%s is carrying a %s.", t->text_The().c_str(), item->text_long_name().c_str());
            }
            if (item->is_weapon()) {
              msg("%s is wielding %s.", t->text_The().c_str(), item->text_long_name().c_str());
            }
          }
        }
      }

      if (t->is_bloodied()) {
        if (! t->is_wounded_msg) {
          t->is_wounded_msg = true;
          if (t->msg_is_wounded()) {
            msg("%s is wounded.", t->text_The().c_str());
          }
        }
      }
    }
  }
  FOR_ALL_THINGS_END()
}
