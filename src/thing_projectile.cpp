//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Thing::projectile_choose_target(Thingp item, Thingp victim)
{
  TRACE_AND_INDENT();
  dbg("Trying to target a projectile with: %s", item->to_short_string().c_str());

  if (is_monst() || (game->robot_mode && is_player())) {
    if (! victim) {
      victim = best_visible_target_get();
    }
    if (! victim) {
      dbg("No victim found");
      return false;
    }

    dbg("Chosen target: %s", victim->to_short_string().c_str());
    TRACE_AND_INDENT();

    used(item, victim, true);

    if (! item->target_name_projectile().empty()) {
      projectile_fire_at(item, item->target_name_projectile(), victim);
    } else {
      err("Unknown projectile: %s.", item->text_the().c_str());
      return false;
    }

    //
    // Get the damage from the enchanted wand, so the blast inflicts that damage.
    //
    damage_current_set(item->damage_current());
    return true;
  }

  if (! is_target_select(item)) {
    return false;
  }

  game->request_to_use_item = item;

  return is_target_select(item);
}

Thingp Thing::projectile_fire_at(Thingp item, const std::string &target_name_projectile, Thingp target)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a wand.
  //

  TRACE_AND_INDENT();
  if (target_name_projectile == "") {
    die("No projectile name");
  }

  //
  // Projectiles hit the first thing in the way. But ignore if it hits
  // ourselves. i.e. if we're in foilage
  //
  auto collatoral_damage = in_the_way_for_firing(curr_at, target->curr_at, 1);
  if (collatoral_damage.size()) {
    target = collatoral_damage[ 0 ];

    //
    // Choose the next thing, if the thing that is in the way is on
    // our tile
    //
    if (target && (target->curr_at == curr_at)) {
      if (collatoral_damage.size()) {
        target = collatoral_damage[ 0 ];
        if (! target) {
          err("No target after removing things in the way");
          return nullptr;
        }
      }
    }
  }

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    if (is_player()) {
      msg("Misfire!");
      game->tick_begin("failed to fire projectile");
    }
    return nullptr;
  }

  if (! end.x && ! end.y) {
    if (is_player()) {
      msg("Misfire!");
      game->tick_begin("failed to fire projectile");
    }
    return nullptr;
  }

  //
  // The attack is immediate when we create the projectile blast at the target.
  // Sp, we need to bump the game tick at this point.
  //
  if (is_player()) {
    game->tick_begin("player fired a projectile");
    game->change_state(Game::STATE_NORMAL);
  }

  auto projectile = level->thing_new(target_name_projectile, target->curr_at, item ? item : this);
  if (! projectile) {
    err("No projectile to fire");
    if (is_player()) {
      game->tick_begin("failed to fire projectile");
    }
    return nullptr;
  }

  dbg("Firing named projectile with: %s at %s", projectile->to_string().c_str(), target->to_string().c_str());

  if (! projectile->is_projectile()) {
    if (is_player()) {
      msg("I don't know how to fire projectile %s.", projectile->text_the().c_str());
      game->tick_begin("player tried to use something they could not");
    }
    return nullptr;
  }

  level->new_projectile(projectile->id, target->id, start, end, 200, true /* follow the target */);

  on_use(projectile, target);

  return projectile;
}

Thingp Thing::projectile_fire_at(Thingp item, const std::string &target_name_projectile, point at)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a wand.
  //

  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Projectile fire %s at %s", target_name_projectile.c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  AttackOptions attack_options       = {};
  attack_options.allow_hitting_walls = true;
  if (victim_attack_choose_best(nullptr, at, &best, &best_hit_at, &attack_options)) {
    return projectile_fire_at(item, target_name_projectile, best);
  }

  FOR_ALL_GRID_THINGS(level, t, at.x, at.y)
  {
    if (t->is_the_grid) {
      return projectile_fire_at(item, target_name_projectile, t);
    }
  }
  FOR_ALL_THINGS_END()

  err("No target to fire at");
  return nullptr;
}
