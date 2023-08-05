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

    if (! item->gfx_targeted_projectile().empty()) {
      projectile_shoot_at(item, item->gfx_targeted_projectile(), victim);
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

Thingp Thing::projectile_shoot_at(Thingp item, const std::string &gfx_targeted_projectile, Thingp target)
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

  if (gfx_targeted_projectile == "") {
    die("No projectile name");
  }

  //
  // Projectiles hit the first thing in the way. But ignore if it hits
  // ourselves. i.e. if we're in foliage
  //
  auto collatoral_dmg = in_the_way_for_shooting(curr_at, target->curr_at, 1);
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

  if (is_player()) {
    msg("You shoot %s at %s.", item->text_the().c_str(), target->text_the().c_str());
  } else if (item) {
    msg("%s shoots %s at %s.", text_The().c_str(), item->text_the().c_str(), target->text_the().c_str());
  } else {
    msg("%s shoots at %s.", text_The().c_str(), target->text_the().c_str());
  }
  TRACE_AND_INDENT();

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    if (is_player()) {
      msg("Misfire!");
      game->tick_begin("failed to shoot projectile");
    } else {
      msg("%s misfires.", text_The().c_str());
    }
    return nullptr;
  }

  if (! end.x && ! end.y) {
    if (is_player()) {
      msg("Misfire!");
      game->tick_begin("failed to shoot projectile");
    } else {
      msg("%s misfires.", text_The().c_str());
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

  auto projectile = level->thing_new(gfx_targeted_projectile, target->curr_at, owner);
  if (! projectile) {
    err("No projectile to shoot");
    if (is_player()) {
      game->tick_begin("failed to shoot projectile");
    }
    return nullptr;
  }

  //
  // Find the end of the portal which is where we will shoot the new projectile.
  //
  if (target && target->is_portal()) {
    auto  delta = target->curr_at - curr_at;
    point destination_of_first_portal;

    //
    // The endpoint may be a portal, or could just be randomly chosen space.
    //
    if (target->teleport_portal_find_target(destination_of_first_portal)) {
      //
      // Fire a 2nd projectile from the portal end point.
      //
      Thingp second_portal = level->thing_find_portal_at(destination_of_first_portal);
      if (second_portal) {
        point second_portal_target = destination_of_first_portal + delta;
        dbg("Shooting named projectile from second portal at %s with target at %s",
            destination_of_first_portal.to_string().c_str(), second_portal_target.to_string().c_str());
        TRACE_AND_INDENT();

        FOR_ALL_GRID_THINGS(level, grid_thing, second_portal_target.x, second_portal_target.y)
        {
          if (grid_thing->is_the_grid) {
            second_portal->projectile_shoot_at(item, gfx_targeted_projectile, grid_thing);
          }
          break;
        }
        FOR_ALL_THINGS_END()
      }
    } else {
      dbg("Failed to shoot named projectile from second portal at %s",
          destination_of_first_portal.to_string().c_str());
    }
  }

  dbg("Shooting named projectile with: %s at %s", projectile->to_string().c_str(), target->to_short_string().c_str());

  if (! projectile->is_projectile()) {
    if (is_player()) {
      msg("I don't know how to shoot projectile %s.", projectile->text_the().c_str());
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
  level->new_projectile(projectile->id, target->id, info, game->current_move_speed * 2);

  on_use(projectile, target);

  if (item) {
    item->on_targeted(target->curr_at);
  }

  if (projectile->is_fire()) {
    level->line_set_all_on_fire(curr_at, target->curr_at, 0, "projectile");
  }

  if (projectile->is_holy()) {
    level->line_set_all_undead_on_fire(curr_at, target->curr_at, 0, "projectile");
  }

  return projectile;
}

Thingp Thing::projectile_shoot_at(Thingp item, const std::string &gfx_targeted_projectile, point at)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a wand.
  //

  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Projectile shoot %s at %s", gfx_targeted_projectile.c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  //
  // If firing too far, choose a point at the limit of what we can hit.
  //
  if (item->range_max()) {
    float dist = distance(item->curr_at, at);
    if (dist > item->range_max()) {
      dbg("Projectile shoot %s at point %s->%s is out of range, dist %f, max %d", gfx_targeted_projectile.c_str(),
          item->curr_at.to_string().c_str(), at.to_string().c_str(), dist, item->range_max());
      float dx = (float) at.x - (float) item->curr_at.x;
      float dy = (float) at.y - (float) item->curr_at.y;
      dx /= dist;
      dy /= dist;
      dx *= item->range_max() - 1;
      dy *= item->range_max() - 1;
      at = curr_at + point(dx, dy);

      float dist = distance(item->curr_at, at);
      dbg("Projectile shoot %s at new point %s, dist %f, max %d", gfx_targeted_projectile.c_str(),
          at.to_string().c_str(), dist, item->range_max());
    }
  }

  ThingAttackOptions attack_options  = {};
  attack_options.allow_hitting_walls = true;
  if (victim_attack_choose_best(nullptr, at, &best, &best_hit_at, &attack_options)) {
    return projectile_shoot_at(item, gfx_targeted_projectile, best);
  }

  FOR_ALL_GRID_THINGS(level, t, at.x, at.y)
  {
    if (t->is_the_grid) {
      return projectile_shoot_at(item, gfx_targeted_projectile, t);
    }
  }
  FOR_ALL_THINGS_END()

  err("No target to shoot at");
  return nullptr;
}
