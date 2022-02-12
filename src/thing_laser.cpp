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

bool Thing::laser_choose_target(Thingp item, Thingp victim)
{
  dbg("Trying to target a laser with: %s", item->to_short_string().c_str());
  TRACE_AND_INDENT();

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

    if (! item->laser_name().empty()) {
      laser_fire_at(item->laser_name(), victim);
    } else {
      err("Unknown beam weapon: %s.", item->text_the().c_str());
      return false;
    }

    //
    // Get the damage from the enchanted wand, so the blast inflicts that damage.
    //
    set_current_damage(item->get_current_damage());
    return true;
  }

  dbg("Need to select a target");
  TRACE_AND_INDENT();

  if (! victim_select(item)) {
    dbg("Failed to select a target");
    TRACE_AND_INDENT();
    return false;
  }

  game->request_to_fire_item = item;

  return victim_select(item);
}

Thingp Thing::laser_fire_at(const std::string &laser_name, Thingp target)
{
  dbg("Laser fire %s at %s", laser_name.c_str(), target->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (laser_name == "") {
    die("No laser name");
  }

  auto collatoral_damage = in_the_way(curr_at, target->curr_at);
  if (collatoral_damage) {
    target = collatoral_damage;
  }

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    msg("Misfire!");
    if (is_player()) {
      game->tick_begin("failed to fire laser");
    }
    return nullptr;
  }

  if (! end.x && ! end.y) {
    msg("Misfire!");
    if (is_player()) {
      game->tick_begin("failed to fire laser");
    }
    return nullptr;
  }

  //
  // The attack is immediate when we create the laser blast at the target.
  // Sp, we need to bump the game tick at this point.
  //
  if (is_player()) {
    game->tick_begin("player zapped a laser");
    game->change_state(Game::STATE_NORMAL);
  }

  auto laser = level->thing_new(laser_name, target->curr_at, this);
  if (! laser) {
    err("No laser to fire");
    if (is_player()) {
      game->tick_begin("failed to fire laser");
    }
    return nullptr;
  }

  dbg("Firing named laser with: %s at %s dist %f", laser->to_string().c_str(), target->to_string().c_str(),
      distance(curr_at, target->curr_at));

  level->new_laser(laser->id, target->id, start, end, game->current_move_speed, true /* follow */);

  //
  // This is needed for secondary lasers
  //
  laser->last_blit_at = end;

  on_use(laser, target);

  return laser;
}

Thingp Thing::laser_fire_at(const std::string &laser_name, point at)
{
  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Laser fire %s at %s", laser_name.c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  if (victim_attack_choose_best(nullptr, at, &best, &best_hit_at)) {
    return laser_fire_at(laser_name, best);
  }

  FOR_ALL_GRID_THINGS(level, t, at.x, at.y)
  {
    if (t->is_the_grid) {
      return laser_fire_at(laser_name, t);
    }
  }
  FOR_ALL_THINGS_END()

  err("No target to fire at");
  return nullptr;
}
