//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

//
// Can it see you?
//
void Thing::can_see_you(point p)
{
  //
  // Record we've been here.
  //
  auto age_map = age_map_get();
  set(age_map->val, p.x, p.y, game->tick_current);

  FOR_ALL_THINGS_THAT_INTERACT(level, t, p.x, p.y)
  {
    //
    // Allow a chance to see secret doors
    //
    if (is_player()) {
      if (t->is_secret_door() && ! t->discovered()) {
        if (d20_le(stat_thv_bonus())) {
          t->discovered_set(true);
        }
      }
    }

    //
    // See invisible things?
    //
    if (! can_detect(t)) {
      continue;
    }

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
                  msg("%s is holding %s.", t->text_The().c_str(), item->text_a_or_an().c_str());
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
        if (! has_seen_player_msg_shown) {
          has_seen_player_msg_shown = true;
          if (is_msg_allowed_is_seen()) {
            if (t->is_on_fire()) {
              msg("%s can see your flaming body!", text_The().c_str());
            } else {
              msg("%s can see you!", text_The().c_str());
            }
          }
        }
      }
    }
  }
  FOR_ALL_THINGS_END()
}

//
// Have we ever seen this point? Or is it just out of view?
//
bool Level::can_see_point_or_nearby(point p, int dist)
{
  for (auto dx = -dist; dx <= dist; dx++) {
    for (auto dy = -dist; dy <= dist; dy++) {
      point o(p.x + dx, p.y + dy);
      if (is_oob(o)) {
        continue;
      }
      if (get(can_see_ever.can_see, o.x, o.y)) {
        return true;
      }
      if (get(can_see_currently.can_see, o.x, o.y)) {
        return true;
      }
    }
  }
  return false;
}
