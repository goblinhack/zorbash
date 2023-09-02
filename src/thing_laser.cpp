//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

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

    if (! item->gfx_targeted_laser().empty()) {
      UseOptions use_options = {};

      //
      // Use the radial attack if desperate
      //
      if ((health() < health_max() / 5) && non_pcg_random_range(0, 100) < 10) {
        if (item->is_target_radial()) {
          //
          // You shall not pass!
          //
          use_options.radial_effect = true;
          victim                    = this;
          laser_shoot_at(item, item->gfx_targeted_radial(), victim, &use_options);
        } else {
          laser_shoot_at(item, item->gfx_targeted_laser(), victim, &use_options);
        }
      } else {
        laser_shoot_at(item, item->gfx_targeted_laser(), victim, &use_options);
      }
    } else {
      if (item) {
        err("Unknown beam weapon: %s.", item->text_the().c_str());
      } else {
        err("Unknown beam weapon");
      }
      return false;
    }

    //
    // Get the damage from the enchanted wand, so the blast inflicts that damage.
    //
    dmg_current_set(item->dmg_current());
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

Thingp Thing::laser_shoot_at(Thingp item, const std::string &effect_name, Thingp target, UseOptions *use_options)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a staff.
  //

  //
  // Set the owner. If fork lightning in water, don't set water as the owner!
  //
  auto owner = item ? item : this;
  if (! owner->maybe_infop()) {
    owner = nullptr;
  }

  dbg("Laser shoot %s at %s", effect_name.c_str(), target->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    if (is_player()) {
      msg("Misfire!");
      game->tick_begin("failed to shoot laser");
    }
    return nullptr;
  }

  if (! end.x && ! end.y) {
    if (is_player()) {
      msg("Misfire!");
      game->tick_begin("failed to shoot laser");
    } else {
      msg("%s misfires.", text_The().c_str());
    }
    return nullptr;
  }

  //
  // The attack is immediate when we create the laser blast at the target.
  // Sp, we need to bump the game tick at this point.
  //
  if (is_player()) {
    game->tick_begin("player zapped a laser");
    game->change_state(Game::STATE_NORMAL, "player zapped a laser");
  }

  //
  // Hit all things in the line of sight of the laser
  //
  if (use_options && use_options->radial_effect) {
    if (is_player()) {
      if (use_options && use_options->radial_effect) {
        msg("You zap %s.", item->text_the().c_str());
      } else {
        msg("You zap %s at %s.", item->text_the().c_str(), target->text_the().c_str());
      }
    } else if (use_options && use_options->radial_effect) {
      if (item) {
        msg("%s zaps %s.", text_The().c_str(), item->text_the().c_str());
      } else {
        msg("%s zaps.", text_The().c_str());
      }
    } else {
      if (item) {
        msg("%s zaps %s at %s.", text_The().c_str(), item->text_the().c_str(), target->text_the().c_str());
      } else if (is_water()) {
        msg("%s electrifies %s.", text_The().c_str(), target->text_the().c_str());
      } else {
        msg("%s zaps %s.", text_The().c_str(), target->text_the().c_str());
      }
    }

    dbg("Firing radial effect");
    TRACE_AND_INDENT();

    Thingp laser = nullptr;
    if (! effect_name.empty()) {
      laser = level->thing_new(effect_name, target->curr_at, owner);
      if (! laser) {
        err("No laser to shoot");
        if (is_player()) {
          game->tick_begin("failed to shoot laser");
        }
        return nullptr;
      }
    }

    if (laser) {
      dbg("Firing named laser with: %s", laser->to_string().c_str());
      on_use(laser, target);
    } else {
      dbg("Firing laser");
    }

    item->on_targeted_radially();
  } else {
    dbg("Firing laser effect");
    TRACE_AND_INDENT();

    auto collatoral_dmg = in_the_way_for_shooting(curr_at, target->curr_at);
    if (collatoral_dmg.size()) {
      dbg("Firing laser effect (collatoral damage)");
      TRACE_AND_INDENT();

      for (auto other_target : collatoral_dmg) {
        IF_DEBUG2 { other_target->log("This is in the way"); }
        TRACE_AND_INDENT();

        if (is_player()) {
          if (use_options && use_options->radial_effect) {
            msg("You zap %s.", item->text_the().c_str());
          } else {
            msg("You zap %s at %s.", item->text_the().c_str(), other_target->text_the().c_str());
          }
        } else if (use_options && use_options->radial_effect) {
          if (item) {
            msg("%s zaps %s.", text_The().c_str(), item->text_the().c_str());
          } else {
            msg("%s zaps.", text_The().c_str());
          }
        } else {
          if (item) {
            msg("%s zaps %s at %s.", text_The().c_str(), item->text_the().c_str(), other_target->text_the().c_str());
          } else if (is_water()) {
            msg("%s electrifies %s.", text_The().c_str(), other_target->text_the().c_str());
          } else {
            msg("%s zaps %s.", text_The().c_str(), other_target->text_the().c_str());
          }
        }

        //
        // Ignore things that are too close
        //
        if (other_target->curr_at == curr_at) {
          continue;
        }

        end = other_target->last_blit_at;

        Thingp laser = nullptr;
        if (! effect_name.empty()) {
          laser = level->thing_new(effect_name, other_target->curr_at, owner);
          if (! laser) {
            err("No laser to shoot");
            if (is_player()) {
              game->tick_begin("failed to shoot laser");
            }
            return nullptr;
          }
        }

        //
        // Find the end of the portal which is where we will shoot the new laser.
        //
        if (other_target && other_target->is_portal()) {
          auto  delta = other_target->curr_at - curr_at;
          point destination_of_first_portal;

          //
          // The endpoint may be a portal, or could just be randomly chosen space.
          //
          if (other_target->teleport_portal_find_target(destination_of_first_portal)) {
            //
            // Fire a 2nd laser from the portal end point.
            //
            Thingp second_portal = level->thing_find_portal_at(destination_of_first_portal);
            if (second_portal) {
              point second_portal_target = destination_of_first_portal + delta;
              dbg("Shooting named laser from second portal at %s with other_target at %s",
                  destination_of_first_portal.to_string().c_str(), second_portal_target.to_string().c_str());
              TRACE_AND_INDENT();

              TRACE_NO_INDENT();
              FOR_ALL_GRID_THINGS(level, grid_thing, second_portal_target.x, second_portal_target.y)
              {
                if (grid_thing->is_the_grid) {
                  second_portal->laser_shoot_at(item, effect_name, grid_thing, use_options);
                }
                break;
              }
              TRACE_NO_INDENT();
              FOR_ALL_THINGS_END()
            }
          } else {
            dbg("Failed to shoot named laser from second portal at %s",
                destination_of_first_portal.to_string().c_str());
          }
        }

        if (laser) {
          dbg("Firing named laser (at collatoral damage) with: %s at %s dist %f", laser->to_string().c_str(),
              other_target->to_short_string().c_str(), distance(curr_at, other_target->curr_at));
        } else {
          dbg("Firing laser (at collatoral damage) with: %s dist %f", other_target->to_short_string().c_str(),
              distance(curr_at, other_target->curr_at));
        }
        TRACE_AND_INDENT();

        LaserInfo info {};
        info.pixel_start          = start;
        info.pixel_stop           = end;
        info.map_start            = curr_at;
        info.map_stop             = other_target->curr_at;
        info.follow_moving_target = true;
        info.pixel_map_at         = level->pixel_map_at;

        if (laser) {
          level->new_laser(laser->id, other_target->id, info, game->current_move_speed);

          //
          // This is needed for secondary lasers
          //
          laser->last_blit_at = end;

          on_use(laser, other_target);

          //
          // Set everything in the way on fire.
          //
          if (laser->is_fire()) {
            level->line_set_all_on_fire(curr_at, other_target->curr_at, 0, "laser");
          }

          if (laser->is_holy()) {
            level->line_set_all_undead_on_fire(curr_at, other_target->curr_at, 0, "laser");
          }
        }

        if (item) {
          item->on_targeted(other_target->curr_at);
        }
      }
    } else {
      //
      // Nothing in the way
      //
      dbg("Firing laser effect (nothing in the way)");
      TRACE_AND_INDENT();

      if (is_player()) {
        if (use_options && use_options->radial_effect) {
          msg("You zap %s.", item->text_the().c_str());
        } else {
          msg("You zap %s at %s.", item->text_the().c_str(), target->text_the().c_str());
        }
      } else if (use_options && use_options->radial_effect) {
        if (item) {
          msg("%s zaps %s.", text_The().c_str(), item->text_the().c_str());
        } else {
          msg("%s zaps.", text_The().c_str());
        }
      } else {
        if (item) {
          msg("%s zaps %s %s.", text_The().c_str(), item->text_the().c_str(), target->text_the().c_str());
        } else if (is_water()) {
          msg("%s electrifies %s.", text_The().c_str(), target->text_the().c_str());
        } else {
          msg("%s zaps %s.", text_The().c_str(), target->text_the().c_str());
        }
      }

      auto laser = level->thing_new(effect_name, target->curr_at, owner);
      if (! laser) {
        err("No laser to shoot");
        if (is_player()) {
          game->tick_begin("failed to shoot laser");
        }
        return nullptr;
      }

      if (laser) {
        dbg("Firing named laser with: %s at %s dist %f", laser->to_string().c_str(),
            target->to_short_string().c_str(), distance(curr_at, target->curr_at));
      } else {
        dbg("Firing laser with: %s dist %f", target->to_short_string().c_str(), distance(curr_at, target->curr_at));
      }
      TRACE_AND_INDENT();

      LaserInfo info {};
      info.pixel_start          = start;
      info.pixel_stop           = end;
      info.map_start            = curr_at;
      info.map_stop             = target->curr_at;
      info.follow_moving_target = true;
      info.pixel_map_at         = level->pixel_map_at;

      if (laser) {
        level->new_laser(laser->id, target->id, info, game->current_move_speed);

        //
        // This is needed for secondary lasers
        //
        laser->last_blit_at = end;

        on_use(laser, target);

        //
        // Set everything in the way on fire.
        //
        if (laser->is_fire()) {
          level->line_set_all_on_fire(curr_at, target->curr_at, 0, "laser");
        }

        if (laser->is_holy()) {
          level->line_set_all_undead_on_fire(curr_at, target->curr_at, 0, "laser");
        }
      }

      if (item) {
        item->on_targeted(target->curr_at);
      }
    }
  }

  return target;
}

Thingp Thing::laser_shoot_at(Thingp item, const std::string &effect_name, point at, UseOptions *use_options)
{
  //
  // NOTE: the item can be null here if this is monster firing with its
  // intrinsic ability. Or it might be non null if say a staff.
  //

  Thingp best = nullptr;
  point  best_hit_at;

  dbg("Laser shoot %s at point %s", effect_name.c_str(), at.to_string().c_str());
  TRACE_AND_INDENT();

  //
  // If firing too far, choose a point at the limit of what we can hit.
  //
  if (item->range_max()) {
    float dist = distance(item->curr_at, at);
    if (dist > item->range_max()) {
      dbg("Laser shoot %s at point %s->%s is out of range, dist %f, max %d", effect_name.c_str(),
          item->curr_at.to_string().c_str(), at.to_string().c_str(), dist, item->range_max());
      float dx = (float) at.x - (float) item->curr_at.x;
      float dy = (float) at.y - (float) item->curr_at.y;
      dx /= dist;
      dy /= dist;
      dx *= item->range_max() - 1;
      dy *= item->range_max() - 1;
      at = curr_at + point(dx, dy);

      float dist = distance(item->curr_at, at);
      dbg("Laser shoot %s at new point %s, dist %f, max %d", effect_name.c_str(), at.to_string().c_str(), dist,
          item->range_max());
    }
  }

  ThingAttackOptions attack_options  = {};
  attack_options.allow_hitting_walls = true;
  if (victim_attack_choose_best(nullptr, at, &best, &best_hit_at, &attack_options)) {
    return laser_shoot_at(item, effect_name, best, use_options);
  }

  TRACE_NO_INDENT();
  FOR_ALL_GRID_THINGS(level, t, at.x, at.y)
  {
    if (t->is_the_grid) {
      return laser_shoot_at(item, effect_name, t, use_options);
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  err("No target to shoot at");
  return nullptr;
}
