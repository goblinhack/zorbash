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
  FOR_ALL_THINGS_THAT_INTERACT(level, t, p.x, p.y)
  {
    //
    // Display a message when a monster comes into view
    //
    if (is_player()) {
      if (t->is_monst()) {
        if (t->is_dead) {
          if (! t->is_seen_by_player_msg_shown) {
            if (t->is_bloodied()) {
              if (! t->is_wounded_msg) {
                t->is_wounded_msg = true;
                if (t->is_msg_allowed_is_wounded()) {
                  if (t->is_red_blooded()) {
                    msg("%s corpse is covered in blood.", t->text_The().c_str());
                  } else if (t->is_green_blooded()) {
                    msg("%s corpse is covered in goo.", t->text_The().c_str());
                  }
                }
              }
            }

            t->is_seen_by_player_msg_shown = true;
            if (t->is_msg_allowed_is_seen()) {
              msg("%s comes into view.", t->text_A_or_An().c_str());

              FOR_ALL_EQUIP(e)
              {
                auto item = t->equip_get(e);
                if (! item) {
                  continue;
                }
                if (item->is_ring() || item->is_helmet() || item->is_amulet()) {
                  msg("%s was wearing %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_cloak()) {
                  msg("%s was styled in %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_gauntlet() || item->is_armor()) {
                  msg("%s was wearing %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_boots()) {
                  msg("%s was sporting %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_shield()) {
                  msg("%s was carrying %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_weapon()) {
                  msg("%s was wielding %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
              }
            }
          }
        } else {
          if (! t->is_seen_by_player_msg_shown) {
            t->is_seen_by_player_msg_shown = true;
            if (t->is_msg_allowed_is_seen()) {
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
                  msg("%s is wearing %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_cloak()) {
                  msg("%s is styled in %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_gauntlet() || item->is_armor()) {
                  msg("%s is wearing %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_boots()) {
                  msg("%s is sporting %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_shield()) {
                  msg("%s is carrying %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
                if (item->is_weapon()) {
                  msg("%s is wielding %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
                }
              }
            }
          }

          if (t->is_bloodied()) {
            if (! t->is_wounded_msg) {
              t->is_wounded_msg = true;
              if (t->is_msg_allowed_is_wounded()) {
                msg("%s is wounded.", t->text_The().c_str());
              }
            }
          }
        }
      }
    } else if (is_monst()) {
      if (t->is_player()) {
        if (! t->has_seen_player_msg_shown) {
          t->has_seen_player_msg_shown = true;
          if (t->is_msg_allowed_is_seen()) {
            msg("%s can see you!", text_The().c_str());
          }
        }
      }
    }
  }
  FOR_ALL_THINGS_END()
}
