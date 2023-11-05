//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

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
  if (is_eater_of_slime() && itp->is_slime())
    return true;
  if (is_eater_of_magical_items() && itp->is_magical())
    return true;
  if (is_eater_of_meat() && itp->is_meat())
    return true;
  if (is_eater_of_fungus() && itp->is_fungus())
    return true;
  if (is_eater_of_plants() && itp->is_plant())
    return true;
  if (is_eater_of_foliage() && itp->is_foliage())
    return true;
  if (is_eater_of_grass() && itp->is_grass())
    return true;
  if (is_eater_of_potions() && itp->is_potion())
    return true;
  if (is_eater_of_red_blood() && itp->is_red_blood())
    return true;
  if (is_eater_of_rings() && itp->is_ring())
    return true;
  if (is_eater_of_treasure() && itp->is_treasure_type())
    return true;
  if (is_eater_of_staffs() && itp->is_staff())
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
  if (is_eater_of_slime() && itp->is_slime())
    return true;
  if (is_eater_of_magical_items() && itp->is_magical())
    return true;
  if (is_eater_of_meat() && itp->is_meat())
    return true;
  if (is_eater_of_fungus() && itp->is_fungus())
    return true;
  if (is_eater_of_plants() && itp->is_plant())
    return true;
  if (is_eater_of_foliage() && itp->is_foliage())
    return true;
  if (is_eater_of_grass() && itp->is_grass())
    return true;
  if (is_eater_of_potions() && itp->is_potion())
    return true;
  if (is_eater_of_red_blood() && itp->is_red_blood())
    return true;
  if (is_eater_of_rings() && itp->is_ring())
    return true;
  if (is_eater_of_treasure() && itp->is_treasure_type())
    return true;
  if (is_eater_of_staffs() && itp->is_staff())
    return true;
  if (is_eater_of_weapons() && itp->is_weapon())
    return true;
  return false;
}

void Thing::on_eaten(Thingp what)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot use null thing");
    return;
  }

  what->is_being_used = true;

  auto on_eaten = what->tp()->on_eaten_do();
  if (std::empty(on_eaten)) {
    dbg("Has no on use");
    return;
  }

  auto t = split_tokens(on_eaten, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = what->name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), what->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_eaten call [%s] expected mod:function, got %d elems", on_eaten.c_str(), (int) on_eaten.size());
  }
}

void Thing::on_eating(Thingp what, int bite)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot use null thing");
    return;
  }

  what->is_being_used = true;

  auto on_eating = what->tp()->on_eating_do();
  if (std::empty(on_eating)) {
    dbg("Has no on use");
    return;
  }

  auto t = split_tokens(on_eating, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = what->name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), what->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, (unsigned int) bite, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_eating call [%s] expected mod:function, got %d elems", on_eating.c_str(), (int) on_eating.size());
  }
}

bool Thing::worth_eating(Thingp victim)
{
  TRACE_NO_INDENT();

  if (! victim) {
    err("Cannot check worth eating null thing");
    return false;
  }

  if (! can_eat(victim)) {
    return false;
  }

  return health_boost_would_occur(victim->nutrition_get()) || hunger_boost_would_occur(victim->nutrition_get());
}

bool Thing::can_eat(const Thingp itp)
{
  if (is_edible(itp)) {
    return true;
  }

  return false;
}

bool Tp::can_eat(const Thingp itp)
{
  if (is_edible(itp)) {
    return true;
  }

  return false;
}

bool Thing::eat(Thingp victim)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot eat null thing");
    return false;
  }

  dbg("Consume %s", victim->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // Makes no sense to sleep eat.
  //
  wake("eating");

  auto nutr   = victim->nutrition_get();
  auto poison = victim->dmg_poison();

  //
  // Does the attacker feast on success?
  //
  if (is_player()) {
    int got_health_boost = health_boost(victim, nutr);
    int got_hunger_boost = hunger_boost(nutr);

    if (poison) {
      //
      // Poisoned food?
      //
      if (! is_immune_to_poison()) {
        poisoned_amount_incr(poison);
        msg("You eat %s and feel queasy.", victim->text_the().c_str());
      }
    } else {
      if (got_health_boost) {
        msg("You munch %s for %d additional health.", victim->text_the().c_str(), got_health_boost);
      } else if (got_hunger_boost) {
        msg("You eat %s and feel less hungry.", victim->text_the().c_str());
      } else {
        msg("You eat %s.", victim->text_the().c_str());
      }
    }

    on_eaten(victim);
    return true;
  }

  if (attack_eater() && is_edible(victim)) {
    //
    // Can't eat players until they are dead.
    //
    if (victim->is_player() && ! victim->is_dead_or_dying()) {
      return false;
    }

    //
    // Can't eat monsters until they are dead.
    //
    if (victim->is_monst() && ! victim->is_dead_or_dying()) {
      return false;
    }

    //
    // Allow monsters to eat things in bite sized chunks so the food does not vanish too fast.
    //
    auto bite = consume_per_bite_amount();

    if (bite < nutr) {
      //
      // Here the monster cannot finish eating its meal in one go.
      //

      //
      // Undead do not get sustenance from eating.
      //
      if (! is_undead() && ! is_ethereal()) {
        health_boost(victim, bite);
        hunger_boost(bite);
      }
      victim->nutrition_decr(bite);

      dbg("Is eating %s", victim->to_short_string().c_str());

      if (distance_to_player() < DMAP_IS_PASSABLE) {
        if (victim->is_meat()) {
          level->thing_new(tp_random_red_splatter()->name(), curr_at);
        } else if (victim->is_red_blooded()) {
          level->thing_new(tp_random_green_splatter()->name(), curr_at);
        } else if (victim->is_green_blooded()) {
          level->thing_new(tp_random_green_splatter()->name(), curr_at);
        }

        if (victim->is_visible_to_player) {
          if (victim->is_player()) {
            if (victim->is_dead || victim->is_dying) {
              if (victim->is_burnt) {
                msg("%%fg=red$%s tears a chunk from your toasted corpse!%%fg=reset$", text_The().c_str());
              } else if (victim->is_frozen) {
                msg("%%fg=red$%s tears a chunk from your frozen corpse!%%fg=reset$", text_The().c_str());
              } else {
                msg("%%fg=red$%s tears a chunk from from your corpse!%%fg=reset$", text_The().c_str());
              }
            } else {
              msg("%%fg=orange$%s is eating you!%%fg=reset$", text_The().c_str());
            }
          } else if (victim->is_monst() || victim->is_player()) {
            if (victim->is_dead || victim->is_dying) {
              if (victim->is_burnt) {
                msg("%s feasts on the toasted corpse of %s!", text_The().c_str(), victim->text_the().c_str());
              } else if (victim->is_frozen) {
                msg("%s feasts on the frozen corpse of %s!", text_The().c_str(), victim->text_the().c_str());
              } else {
                msg("%s feasts on the corpse of %s!", text_The().c_str(), victim->text_the().c_str());
              }
            } else {
              msg("%s is eating %s!", text_The().c_str(), victim->text_the().c_str());
            }
          } else if (victim->is_blood()) {
            if (is_humanoid()) {
              msg("%s laps up %s.", text_The().c_str(), victim->text_the().c_str());
            } else {
              msg("%s slurps at %s.", text_The().c_str(), victim->text_the().c_str());
            }
          } else {
            if (bite <= 3) {
              msg("%s nibbles on %s.", text_The().c_str(), victim->text_the().c_str());
            } else if (bite <= 10) {
              msg("%s munches on %s.", text_The().c_str(), victim->text_the().c_str());
            } else {
              msg("%s chomps on %s.", text_The().c_str(), victim->text_the().c_str());
            }
          }
        }
      }
      on_eating(victim, bite);
    } else {
      //
      // Here the monster finishes eating its meal.
      //

      //
      // Undead do not get sustenance from eating.
      //
      if (! is_undead() && ! is_ethereal()) {
        health_boost(victim, nutr);
        hunger_boost(nutr);
      }

      dbg("Consumes %s", victim->to_short_string().c_str());

      if (! is_player()) {
        if (distance_to_player() < DMAP_IS_PASSABLE) {
          if (victim->is_meat()) {
            level->thing_new(tp_random_red_splatter()->name(), curr_at);
          } else if (victim->is_red_blooded()) {
            level->thing_new(tp_random_green_splatter()->name(), curr_at);
          } else if (victim->is_green_blooded()) {
            level->thing_new(tp_random_green_splatter()->name(), curr_at);
          }

          if (victim->is_visible_to_player) {
            if (victim->is_player()) {
              if (victim->is_dead || victim->is_dying) {
                if (victim->is_burnt) {
                  msg("%%fg=red$%s consumes your toasted corpse!%%fg=reset$", text_The().c_str());
                } else if (victim->is_frozen) {
                  msg("%%fg=red$%s consumes your frozen corpse!%%fg=reset$", text_The().c_str());
                } else {
                  msg("%%fg=red$%s consumes your corpse!%%fg=reset$", text_The().c_str());
                }
              } else {
                msg("%%fg=orange$%s consumes you!%%fg=reset$", text_The().c_str());
              }
            } else if (victim->is_monst() || victim->is_player()) {
              if (victim->is_dead || victim->is_dying) {
                if (victim->is_burnt) {
                  msg("%s consumed the toasted corpse of %s!", text_The().c_str(), victim->text_the().c_str());
                } else if (victim->is_frozen) {
                  msg("%s consumed the frozen corpse of %s!", text_The().c_str(), victim->text_the().c_str());
                } else {
                  msg("%s consumes the corpse of %s!", text_The().c_str(), victim->text_the().c_str());
                }
              } else {
                msg("%s consumes %s!", text_The().c_str(), victim->text_the().c_str());
              }
            } else if (victim->is_blood()) {
              if (is_humanoid()) {
                msg("%s laps up %s.", text_The().c_str(), victim->text_the().c_str());
              } else {
                msg("%s slurps at %s.", text_The().c_str(), victim->text_the().c_str());
              }
            } else {
              msg("%s consumes %s.", text_The().c_str(), victim->text_the().c_str());
            }
          }
        }
      }
      on_eaten(victim);
      victim->dead("by being eaten");
    }

    if (poison) {
      //
      // Poisoned food?
      //
      if (! is_immune_to_poison()) {
        poisoned_amount_incr(poison);
        msg("%s looks ill.", text_The().c_str());
      }
    }
    return true;
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
    UseOptions use_options;
    if (use(best, use_options)) {
      return true;
    }
  }

  //
  // Try again but include potions
  //
  TRACE_NO_INDENT();
  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_health_booster()) {
      UseOptions use_options;
      if (use(t, use_options)) {
        return true;
      }
    }
  }

  return false;
}

bool Thing::can_eat_something(void)
{
  TRACE_NO_INDENT();

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
