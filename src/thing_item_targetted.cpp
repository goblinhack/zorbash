//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

bool Thing::item_choose_target(Thingp item, Thingp victim /* can be null */)
{
  dbg("Trying to target a item with: %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (is_monst() || (game->robot_mode && is_player())) {
    if (! victim) {
      victim = best_visible_target_get();
    }
    if (! victim) {
      dbg("No victim found");
      return false;
    }

    dbg("Chosen item target: %s", victim->to_short_string().c_str());
    TRACE_AND_INDENT();

    UseOptions use_options;
    used(item, victim, use_options);

    item_targeted_use_at(item, victim);

    //
    // Get the damage from the enchanted wand, so the blast inflicts that damage.
    //
    dmg_current_set(item->dmg_current());
    return true;
  }

  if (! is_target_select(item)) {
    return false;
  }

  game->request_to_use_item = item;

  return is_target_select(item);
}

Thingp Thing::item_targeted_use_at(Thingp item, Thingp target)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a wand.
  //

  TRACE_AND_INDENT();
  dbg("Use item %s at %s", item->to_short_string().c_str(), target->curr_at.to_string().c_str());

  auto collatoral_dmg = in_the_way_for_shooting(curr_at, target->curr_at, 1);
  if (collatoral_dmg.size()) {
    target = collatoral_dmg[ 0 ];
  }

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    if (is_player()) {
      msg("Failed to use, no start!");
      game->tick_begin("failed to use item");
      game->change_state(Game::STATE_NORMAL, "player used an item");
    }
    return nullptr;
  }

  if (! end.x && ! end.y) {
    if (is_player()) {
      msg("Failed to use, no target!");
      game->tick_begin("failed to use item");
      game->change_state(Game::STATE_NORMAL, "player used an item");
    }
    return nullptr;
  }

  //
  // The attack is immediate when we create the item blast at the target.
  // So, we need to bump the game tick at this point.
  //
  if (is_player()) {
    game->tick_begin("player used an item");
    game->change_state(Game::STATE_NORMAL, "player used an item");
  }

  dbg("Using named item with: %s at %s", item->to_short_string().c_str(), target->to_short_string().c_str());

  if (! item->is_item_targeted()) {
    if (is_player()) {
      msg("I don't know how to use %s.", item->text_the().c_str());
      game->tick_begin("player tried to use something they could not");
    }
    return nullptr;
  }

  return item;
}

Thingp Thing::item_targeted_use_at(Thingp item, point at)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a wand.
  //

  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Use targeted item %s at %s", item->to_short_string().c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  ThingAttackOptions attack_options  = {};
  attack_options.allow_hitting_walls = true;
  if (victim_attack_choose_best(nullptr, at, &best, &best_hit_at, &attack_options)) {
    return item_targeted_use_at(item, best);
  }

  TRACE_NO_INDENT();
  FOR_ALL_GRID_THINGS(level, t, at.x, at.y) { return item_targeted_use_at(item, t); }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  err("No target to use at");
  return nullptr;
}
