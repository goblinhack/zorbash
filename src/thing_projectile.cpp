//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"

bool Thing::projectile_choose_target(Thingp item, Thingp victim)
{
  TRACE_AND_INDENT();
  dbg("Trying to target a projectile with: %s", item->to_short_string().c_str());

  if (is_monst() || (game->robot_mode && is_player())) {
    if (! victim) {
      victim = get_best_visible_target();
    }
    if (! victim) {
      dbg("No victim found");
      return false;
    }

    dbg("Chosen target: %s", victim->to_short_string().c_str());
    TRACE_AND_INDENT();

    used(item, victim, true);

    if (! item->projectile_name().empty()) {
      projectile_fire_at(item->projectile_name(), victim);
    } else {
      err("Unknown projectile: %s.", item->text_the().c_str());
      return false;
    }

    //
    // Get the damage from the enchanted wand, so the blast inflicts that damage.
    //
    set_current_damage(item->get_current_damage());
    return true;
  }

  if (! target_select(item)) {
    return false;
  }

  game->request_to_fire_item = item;

  return target_select(item);
}

Thingp Thing::projectile_fire_at(const std::string &projectile_name, Thingp target)
{
  TRACE_AND_INDENT();
  if (projectile_name == "") {
    die("No projectile name");
  }

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    msg("Misfire!");
    if (is_player()) {
      game->tick_begin("failed to fire projectile");
    }
    return nullptr;
  }

  if (! end.x && ! end.y) {
    msg("Misfire!");
    if (is_player()) {
      game->tick_begin("failed to fire projectile");
    }
    return nullptr;
  }

  auto projectile = level->thing_new(projectile_name, target->curr_at, this);
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

  if (is_player()) {
    game->tick_begin("player fired " + projectile->text_the());
    game->change_state(Game::STATE_NORMAL);
  }

  level->new_projectile(projectile->id, target->id, start, end, 200, true /* follow the target */);

  on_use(projectile, target);

  return projectile;
}

Thingp Thing::projectile_fire_at(const std::string &laser_name, point at)
{
  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Projectile fire %s at %s", laser_name.c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  if (target_attack_choose_best(nullptr, at, &best, &best_hit_at)) {
    return projectile_fire_at(laser_name, best);
  }

  FOR_ALL_GRID_THINGS(level, t, at.x, at.y)
  {
    if (t->is_the_grid) {
      return projectile_fire_at(laser_name, t);
    }
  }
  FOR_ALL_THINGS_END()

  err("No target to fire at");
  return nullptr;
}
