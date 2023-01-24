//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

bool Thing::projectile_choose_target(Thingp item, Thingp victim /* can be null */)
{
  dbg("Trying to target a projectile with: %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

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
      fire_projectile_at(item, item->target_name_projectile(), victim);
    } else {
      err("Unknown projectile: %s.", item->text_the().c_str());
      return false;
    }

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

Thingp Thing::fire_projectile_at(Thingp item, const std::string &target_name_projectile, Thingp target)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a wand.
  //

  //
  // Set the owner. If fork lightning in water, don't set water as the owner!
  //
  auto owner = item ? item : this;
  if (! owner->maybe_infop()) {
    owner = nullptr;
  }

  if (target_name_projectile == "") {
    die("No projectile name");
  }

  if (is_player()) {
    msg("You fire %s at %s.", item->text_the().c_str(), target->text_the().c_str());
  }
  TRACE_AND_INDENT();

  //
  // Projectiles hit the first thing in the way. But ignore if it hits
  // ourselves. i.e. if we're in foliage
  //
  auto collatoral_dmg = in_the_way_for_firing(curr_at, target->curr_at, 1);
  if (collatoral_dmg.size()) {
    target = collatoral_dmg[ 0 ];

    //
    // Choose the next thing, if the thing that is in the way is on
    // our tile
    //
    if (target && (target->curr_at == curr_at)) {
      if (collatoral_dmg.size()) {
        target = collatoral_dmg[ 0 ];
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
    game->change_state(Game::STATE_NORMAL, "player fired a projectile");
  }

  auto projectile = level->thing_new(target_name_projectile, target->curr_at, owner);
  if (! projectile) {
    err("No projectile to fire");
    if (is_player()) {
      game->tick_begin("failed to fire projectile");
    }
    return nullptr;
  }

  dbg("Firing named projectile with: %s at %s", projectile->to_string().c_str(), target->to_short_string().c_str());

  if (! projectile->is_projectile()) {
    if (is_player()) {
      msg("I don't know how to fire projectile %s.", projectile->text_the().c_str());
      game->tick_begin("player tried to use something they could not");
    }
    return nullptr;
  }

  ProjectileInfo info {};
  info.pixel_start          = start;
  info.pixel_stop           = end;
  info.map_start            = curr_at;
  info.map_stop             = target->curr_at;
  info.follow_moving_target = true;
  info.pixel_map_at         = level->pixel_map_at;
  level->new_projectile(projectile->id, target->id, info, 200);

  on_use(projectile, target);

  if (item) {
    item->on_targetted(target->curr_at);
  }

  if (projectile->is_fire()) {
    level->line_set_all_on_fire(curr_at, target->curr_at, 0, "projectile");
  }

  return projectile;
}

Thingp Thing::fire_projectile_at(Thingp item, const std::string &target_name_projectile, point at)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a wand.
  //

  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Projectile fire %s at %s", target_name_projectile.c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  //
  // If firing too far, choose a point at the limit of what we can hit.
  //
  if (item->range_max()) {
    float dist = distance(item->curr_at, at);
    if (dist > item->range_max()) {
      dbg("Projectile fire %s at point %s is out of range, dist %f, max %d", target_name_projectile.c_str(),
          at.to_string().c_str(), dist, item->range_max());
      float dx = (float) at.x - (float) item->curr_at.x;
      float dy = (float) at.y - (float) item->curr_at.y;
      dx /= dist;
      dy /= dist;
      dx *= item->range_max() - 1;
      dy *= item->range_max() - 1;
      at = curr_at + point(dx, dy);

      float dist = distance(item->curr_at, at);
      dbg("Projectile fire %s at new point %s, dist %f, max %d", target_name_projectile.c_str(),
          at.to_string().c_str(), dist, item->range_max());
    }
  }

  ThingAttackOptions attack_options  = {};
  attack_options.allow_hitting_walls = true;
  if (victim_attack_choose_best(nullptr, at, &best, &best_hit_at, &attack_options)) {
    return fire_projectile_at(item, target_name_projectile, best);
  }

  FOR_ALL_GRID_THINGS(level, t, at.x, at.y)
  {
    if (t->is_the_grid) {
      return fire_projectile_at(item, target_name_projectile, t);
    }
  }
  FOR_ALL_THINGS_END()

  err("No target to fire at");
  return nullptr;
}
