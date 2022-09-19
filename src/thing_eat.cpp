//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::is_edible(Thingp itp)
{
  if (is_eater_of_amulets() && itp->is_amulet())
    return true;
  if (is_eater_of_armor() && itp->is_armor())
    return true;
  if (is_eater_of_boots() && itp->is_boots())
    return true;
  if (is_eater_of_cloaks() && itp->is_cloak())
    return true;
  if (is_eater_of_food() && itp->is_food())
    return true;
  if (is_eater_of_gauntlets() && itp->is_gauntlet())
    return true;
  if (is_eater_of_green_blood() && itp->is_green_blood())
    return true;
  if (is_eater_of_helmets() && itp->is_helmet())
    return true;
  if (is_eater_of_jelly() && itp->is_jelly())
    return true;
  if (is_eater_of_magical_items() && itp->is_magical())
    return true;
  if (is_eater_of_meat() && itp->is_meat())
    return true;
  if (is_eater_of_potions() && itp->is_potion())
    return true;
  if (is_eater_of_red_blood() && itp->is_red_blood())
    return true;
  if (is_eater_of_rings() && itp->is_ring())
    return true;
  if (is_eater_of_staffs() && itp->is_staff())
    return true;
  if (is_eater_of_treasure() && itp->is_treasure_type())
    return true;
  if (is_eater_of_wands() && itp->is_wand())
    return true;
  if (is_eater_of_weapons() && itp->is_weapon())
    return true;
  return false;
}

bool Tp::is_edible(Thingp itp)
{
  if (is_eater_of_amulets() && itp->is_amulet())
    return true;
  if (is_eater_of_armor() && itp->is_armor())
    return true;
  if (is_eater_of_boots() && itp->is_boots())
    return true;
  if (is_eater_of_cloaks() && itp->is_cloak())
    return true;
  if (is_eater_of_food() && itp->is_food())
    return true;
  if (is_eater_of_gauntlets() && itp->is_gauntlet())
    return true;
  if (is_eater_of_green_blood() && itp->is_green_blood())
    return true;
  if (is_eater_of_helmets() && itp->is_helmet())
    return true;
  if (is_eater_of_jelly() && itp->is_jelly())
    return true;
  if (is_eater_of_magical_items() && itp->is_magical())
    return true;
  if (is_eater_of_meat() && itp->is_meat())
    return true;
  if (is_eater_of_potions() && itp->is_potion())
    return true;
  if (is_eater_of_red_blood() && itp->is_red_blood())
    return true;
  if (is_eater_of_rings() && itp->is_ring())
    return true;
  if (is_eater_of_staffs() && itp->is_staff())
    return true;
  if (is_eater_of_treasure() && itp->is_treasure_type())
    return true;
  if (is_eater_of_wands() && itp->is_wand())
    return true;
  if (is_eater_of_weapons() && itp->is_weapon())
    return true;
  return false;
}

bool Thing::worth_eating(Thingp victim)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot check worth eating null thing");
    return false;
  }

  if (! can_eat(victim)) {
    return false;
  }

  return health_boost_would_occur(victim->nutrition_get());
}

bool Thing::can_eat(const Thingp itp)
{
  dbg("Can eat? %s", itp->to_short_string().c_str());

  if (is_edible(itp)) {
    TRACE_AND_INDENT();
    dbg("Yes, can eat: %s", itp->to_short_string().c_str());
    return true;
  }

  return false;
}

bool Tp::can_eat(const Thingp itp)
{
  dbg("Can eat? %s", itp->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (is_edible(itp)) {
    dbg("Can eat jelly: %s", itp->to_short_string().c_str());
    return true;
  }

  return false;
}

//
// Try to eat
//
bool Thing::eat(Thingp victim)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot eat null thing");
    return false;
  }

  dbg("Eat %s", victim->text_the().c_str());
  TRACE_AND_INDENT();

  //
  // Does the attacker feast on success?
  //
  if (is_player()) {
    auto boost = health_boost(victim->nutrition_get());
    msg("You munch %s for %d health.", victim->text_the().c_str(), boost);
    return true;
  }

  if (attack_eater()) {
    if (is_edible(victim)) {
      //
      // Worth eating?
      //
      if (hunger_is_insatiable()) {
        //
        // Munch munch. Always try to eat.
        //
      } else if (! health_boost(victim->nutrition_get())) {
        dbg("No health boost from eating %s", victim->text_the().c_str());
        return false;
      }

      dbg("Eating %s", victim->text_the().c_str());

      if (victim->is_monst() || victim->is_player()) {
        return nat_att(victim);
      } else {
        return consume(victim);
      }
    }
  }
  return false;
}

bool Thing::consume(Thingp victim)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot eat null thing");
    return false;
  }

  dbg("Consume %s", victim->text_the().c_str());
  TRACE_AND_INDENT();

  //
  // Does the attacker feast on success?
  //
  if (is_player()) {
    auto boost = health_boost(victim->nutrition_get());
    msg("You munch %s for %d health.", victim->text_the().c_str(), boost);
    return true;
  }

  if (attack_eater()) {
    if (is_edible(victim)) {
      dbg("Consumes %s", victim->text_the().c_str());

      if (! is_player()) {
        if (distance_to_player() < DMAP_IS_PASSABLE) {
          if (victim->is_meat()) {
            level->thing_new(tp_random_red_splatter()->name(), curr_at);
          } else if (victim->is_red_blooded()) {
            level->thing_new(tp_random_green_splatter()->name(), curr_at);
          } else if (victim->is_green_blooded()) {
            level->thing_new(tp_random_green_splatter()->name(), curr_at);
          }

          if (! victim->is_offscreen) {
            if (victim->is_player()) {
              if (victim->is_dead || victim->is_dying) {
                msg("%%fg=red$%s feasts on your corpse!%%fg=reset$", text_The().c_str());
              } else {
                msg("%%fg=orange$%s is eating you!%%fg=reset$", text_The().c_str());
              }
            } else if (victim->is_monst() || victim->is_player()) {
              if (victim->is_dead || victim->is_dying) {
                msg("%s feasts on the corpse of %s!", text_The().c_str(), victim->text_the().c_str());
              } else {
                msg("%s is eating %s!", text_The().c_str(), victim->text_the().c_str());
              }
            } else {
              msg("%s consumes %s.", text_The().c_str(), victim->text_the().c_str());
            }
          }
        }
      }

      victim->dead("by being eaten");
      return true;
    }
  }
  return false;
}

bool Thing::eat_something(void)
{
  TRACE_NO_INDENT();

  Thingp best = nullptr;

  //
  // Try for food first, ignoring potions
  //
  for (const auto t : carried_item_only_vector()) {
    if (! can_eat(t)) {
      continue;
    }
    if (! worth_eating(t)) {
      continue;
    }

    if (! best) {
      best = t;
    } else if (t->nutrition_get() > best->nutrition_get()) {
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
  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
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
  for (const auto t : carried_item_only_vector()) {
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
  for (const auto t : carried_item_only_vector()) {
    if (t->is_health_booster()) {
      return true;
    }
  }

  return false;
}
