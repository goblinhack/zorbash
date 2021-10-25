//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_tile.h"

bool Thing::eat(Thingp what)
{
  verify(what);
  if (! what) {
    err("Cannot eat null thing");
    return false;
  }

  TRACE_AND_INDENT();
  //
  // Does the attacker feast on success?
  //
  if (is_player()) {
    auto boost = health_boost(what->get_nutrition());
    TOPCON("You munch %s for %d health.", what->text_the().c_str(), boost);
    return true;
  }

  if (attack_eater()) {
    if ((is_jelly_eater() && what->is_jelly()) || (is_meat_eater() && what->is_meat()) ||
        (is_blood_eater() && what->is_blood()) || (is_food_eater() && what->is_food()) ||
        (is_treasure_type_eater() && what->is_treasure_type()) || (is_wand_eater() && what->is_wand()) ||
        (is_potion_eater() && what->is_potion())) {

      //
      // For treasure what should the boost be?
      //
      if (! health_boost(what->get_nutrition())) {
        dbg("No health boost from eating %s", what->text_the().c_str());
        return false;
      }

      dbg("Eats %s", what->text_the().c_str());

      if (! is_player()) {
        if (distance_to_player() < DMAP_IS_PASSABLE) {
          if (what->is_meat()) {
            level->thing_new(tp_random_blood_splatter()->name(), mid_at);
          }

          TOPCON("%s eats %s.", text_The().c_str(), what->text_the().c_str());
        }
      }

      what->dead("by being eaten");
      return true;
    }
  }
  return false;
}

bool Thing::worth_eating(Thingp what)
{
  verify(what);
  if (! what) {
    err("Cannot check worth eating null thing");
    return false;
  }

  TRACE_AND_INDENT();
  if (! can_eat(what)) {
    return false;
  }

  return health_boost_would_occur(what->get_nutrition());
}

bool Thing::can_eat(const Thingp itp)
{
  TRACE_AND_INDENT();
  auto me = tp();
  auto it = itp->tp();

  if (me->is_meat_eater()) {
    if (it->is_meat()) {
      return true;
    }
  }
  if (me->is_blood_eater()) {
    if (it->is_blood()) {
      return true;
    }
  }
  if (me->is_food_eater()) {
    if (it->is_food()) {
      return true;
    }
  }
  if (me->is_treasure_type_eater()) {
    if (it->is_treasure_type()) {
      return true;
    }
  }
  if (me->is_potion_eater()) {
    if (it->is_potion()) {
      return true;
    }
  }
  if (me->is_wand_eater()) {
    if (it->is_wand()) {
      return true;
    }
  }
  if (me->is_jelly_baby_eater()) {
    if (it->is_jelly_baby()) {
      return true;
    }
  }
  if (is_player()) {
    if (it->is_food()) {
      return true;
    }
  }
  return false;
}

bool Thing::eat_something(void)
{
  TRACE_AND_INDENT();
  Thingp best = nullptr;

  //
  // Try for food first, ignoring potions
  //
  for (const auto t : get_item_vector()) {
    if (! can_eat(t)) {
      continue;
    }
    if (! worth_eating(t)) {
      continue;
    }

    if (! best) {
      best = t;
    } else if (t->get_nutrition() > best->get_nutrition()) {
      best = t;
    }
  }

  if (best) {
    if (use(best)) {
      return true;
    }
  }

  //
  // Try again but include potions
  //
  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_health_booster()) {
      if (use(t)) {
        return true;
      }
    }
  }

  return false;
}

bool Thing::can_eat_something(void)
{
  TRACE_AND_INDENT();
  //
  // Try for food first, ignoring potions
  //
  for (const auto t : get_item_vector()) {
    if (! can_eat(t)) {
      continue;
    }
    if (! worth_eating(t)) {
      continue;
    }
    return true;
  }

  //
  // Try again but include potions
  //
  for (const auto t : get_item_vector()) {
    if (t->is_health_booster()) {
      return true;
    }
  }

  return false;
}
