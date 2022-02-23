//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Thing::laser_choose_target(Thingp item, Thingp victim)
{
  dbg("Trying to target a laser with: %s", item->to_short_string().c_str());
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

    if (! item->target_name_laser().empty()) {
      laser_fire_at(item->target_name_laser(), victim);
    } else {
      err("Unknown beam weapon: %s.", item->text_the().c_str());
      return false;
    }

    //
    // Get the damage from the enchanted wand, so the blast inflicts that damage.
    //
    damage_current_set(item->damage_current());
    return true;
  }

  dbg("Need to select a target");
  TRACE_AND_INDENT();

  if (! is_target_select(item)) {
    dbg("Failed to select a target");
    TRACE_AND_INDENT();
    return false;
  }

  game->request_to_fire_item = item;

  return is_target_select(item);
}

bool Thing::laser_fire_at(const std::string &target_name_laser, Thingp target)
{
  dbg("Laser fire %s at %s", target_name_laser.c_str(), target->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (target_name_laser == "") {
    die("No laser name");
  }

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    msg("Misfire!");
    if (is_player()) {
      game->tick_begin("failed to fire laser");
    }
    return false;
  }

  if (! end.x && ! end.y) {
    msg("Misfire!");
    if (is_player()) {
      game->tick_begin("failed to fire laser");
    }
    return false;
  }

  //
  // The attack is immediate when we create the laser blast at the target.
  // Sp, we need to bump the game tick at this point.
  //
  if (is_player()) {
    game->tick_begin("player zapped a laser");
    game->change_state(Game::STATE_NORMAL);
  }

  //
  // Hit all things in the line of sight of the laser
  //
  auto collatoral_damage = in_the_way(curr_at, target->curr_at);
  for (auto target : collatoral_damage) {
    auto laser = level->thing_new(target_name_laser, target->curr_at, this);
    if (! laser) {
      err("No laser to fire");
      if (is_player()) {
        game->tick_begin("failed to fire laser");
      }
      return false;
    }

    dbg("Firing named laser with: %s at %s dist %f", laser->to_string().c_str(), target->to_string().c_str(),
        distance(curr_at, target->curr_at));

    level->new_laser(laser->id, target->id, start, end, game->current_move_speed, true /* follow */);

    //
    // This is needed for secondary lasers
    //
    laser->last_blit_at = end;

    on_use(laser, target);
  }

  return true;
}

bool Thing::laser_fire_at(const std::string &target_name_laser, point at)
{
  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Laser fire %s at %s", target_name_laser.c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  if (victim_attack_choose_best(nullptr, at, &best, &best_hit_at)) {
    return laser_fire_at(target_name_laser, best);
  }

  FOR_ALL_GRID_THINGS(level, t, at.x, at.y)
  {
    if (t->is_the_grid) {
      return laser_fire_at(target_name_laser, t);
    }
  }
  FOR_ALL_THINGS_END()

  err("No target to fire at");
  return false;
}
