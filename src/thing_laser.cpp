//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_random.hpp"
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
      UseOptions use_options = {};
      if (non_pcg_random_range(0, 100) < 10) {
        if (! item->target_name_radial().empty()) {
          //
          // You shall not pass!
          //
          use_options.radial_effect = true;
          victim                    = this;
          laser_fire_at(item, item->target_name_radial(), victim, &use_options);
        } else {
          laser_fire_at(item, item->target_name_laser(), victim, &use_options);
        }
      } else {
        laser_fire_at(item, item->target_name_laser(), victim, &use_options);
      }
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

  game->request_to_use_item = item;

  return is_target_select(item);
}

bool Thing::laser_fire_at(Thingp item, const std::string &target_name_laser, Thingp target, UseOptions *use_options)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a staff.
  //

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
  if (use_options && use_options->radial_effect) {
    dbg("Firing radial effect");
    TRACE_AND_INDENT();

    auto laser = level->thing_new(target_name_laser, target->curr_at, item ? item : this);
    if (! laser) {
      err("No laser to fire");
      if (is_player()) {
        game->tick_begin("failed to fire laser");
      }
      return false;
    }

    dbg("Firing named laser with: %s", laser->to_string().c_str());

    on_use(laser, target);
  } else {
    dbg("Firing laser effect");
    TRACE_AND_INDENT();

    auto collatoral_damage = in_the_way_for_firing(curr_at, target->curr_at);
    if (collatoral_damage.size()) {
      dbg("Firing laser effect (collatoral damage)");
      TRACE_AND_INDENT();

      for (auto target : collatoral_damage) {
        //
        // Ignore things that are too close
        //
        if (target->curr_at == curr_at) {
          continue;
        }

        auto laser = level->thing_new(target_name_laser, target->curr_at, item ? item : this);
        if (! laser) {
          err("No laser to fire");
          if (is_player()) {
            game->tick_begin("failed to fire laser");
          }
          return false;
        }

        dbg("Firing named laser (at collatoral damage) with: %s at %s dist %f", laser->to_string().c_str(),
            target->to_string().c_str(), distance(curr_at, target->curr_at));
        TRACE_AND_INDENT();

        level->new_laser(laser->id, target->id, start, end, game->current_move_speed, true /* follow */);

        //
        // This is needed for secondary lasers
        //
        laser->last_blit_at = end;

        on_use(laser, target);
      }
    } else {
      //
      // Nothing in the way
      //
      dbg("Firing laser effect (nothing in the way)");
      TRACE_AND_INDENT();

      auto laser = level->thing_new(target_name_laser, target->curr_at, item ? item : this);
      if (! laser) {
        err("No laser to fire");
        if (is_player()) {
          game->tick_begin("failed to fire laser");
        }
        return false;
      }

      dbg("Firing named laser with: %s at %s dist %f", laser->to_string().c_str(), target->to_string().c_str(),
          distance(curr_at, target->curr_at));
      TRACE_AND_INDENT();

      level->new_laser(laser->id, target->id, start, end, game->current_move_speed, true /* follow */);

      //
      // This is needed for secondary lasers
      //
      laser->last_blit_at = end;

      on_use(laser, target);
    }
  }

  return true;
}

bool Thing::laser_fire_at(Thingp item, const std::string &target_name_laser, point at, UseOptions *use_options)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a staff.
  //

  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Laser fire %s at point %s", target_name_laser.c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  AttackOptions attack_options       = {};
  attack_options.allow_hitting_walls = true;
  if (victim_attack_choose_best(nullptr, at, &best, &best_hit_at, &attack_options)) {
    return laser_fire_at(item, target_name_laser, best, use_options);
  }

  FOR_ALL_GRID_THINGS(level, t, at.x, at.y)
  {
    if (t->is_the_grid) {
      return laser_fire_at(item, target_name_laser, t, use_options);
    }
  }
  FOR_ALL_THINGS_END()

  err("No target to fire at");
  return false;
}
