//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_console.hpp"

void Level::handle_all_pending_things(void)
{
  handle_internal_particles();
  handle_external_particles();

  for (auto &i : animated_things_pending_remove) {
    // i.second->con("pending remove");
    animated_things.erase(i.first);
  }
  animated_things_pending_remove = {};

  for (auto &i : animated_things_pending_add) {
    // i.second->con("pending add");
    animated_things.insert(i);
  }
  animated_things_pending_add = {};

  for (auto &i : all_things_pending_fall) {
    i.second->fall_to_next_level();
  }
  all_things_pending_fall = {};
}

void Level::handle_input_events(void)
{
  if (game->robot_mode) {
    return;
  }

  //
  // Trying to scroll the map?
  //
  const float    map_move_scroll_delta = 0.2;
  const uint8_t *state                 = SDL_GetKeyboardState(0);

  if (state[ sdlk_to_scancode(game->config.key_map_left) ]) {
    map_wanted_at.x -= map_move_scroll_delta;
    is_cursor_found      = false;
    is_map_follow_player = false;
  }

  if (state[ sdlk_to_scancode(game->config.key_map_right) ]) {
    map_wanted_at.x += map_move_scroll_delta;
    is_cursor_found      = false;
    is_map_follow_player = false;
  }

  if (state[ sdlk_to_scancode(game->config.key_map_up) ]) {
    map_wanted_at.y -= map_move_scroll_delta;
    is_cursor_found      = false;
    is_map_follow_player = false;
  }

  if (state[ sdlk_to_scancode(game->config.key_map_down) ]) {
    map_wanted_at.y += map_move_scroll_delta;
    is_cursor_found      = false;
    is_map_follow_player = false;
  }

  //
  // After a small delay handle the player move. This allows for diagonal moves to be handled without generating two
  // key presses.
  //
  if (((player && player->aip()->move_path.size()) || game->request_player_move)) {
    //
    // Move time along a bit if the player is waiting to move. This will cause movements and jumps to complete
    // sooner and should result in the flag below being cleared.
    //
    if (game->things_are_moving) {
      dbg("Fast forward loop ");
      do {
        time_game_delta += 50;
        display_pixelart_internal_particles();
        display_pixelart_external_particles();
        tick();
      } while (game->things_are_moving);
      dbg("Fast forward end ");
    }

    game->request_player_move = 0;

    bool jump            = false;
    bool attack          = false;
    bool up              = game->request_player_move_up;
    bool down            = game->request_player_move_down;
    bool right           = game->request_player_move_right;
    bool left            = game->request_player_move_left;
    bool wait_or_collect = game->request_player_to_wait_or_collect;

    game->request_player_move_up            = false;
    game->request_player_move_down          = false;
    game->request_player_move_right         = false;
    game->request_player_move_left          = false;
    game->request_player_to_wait_or_collect = false;

    if (up || down || left || right || wait_or_collect) {
      if (player_tick(left, right, up, down, attack, wait_or_collect, jump)) {
        tick_begin_now();
      }
    }
  }
}

void Level::tick_(void)
{
  if (! game->started) {
    return;
  }

  if (game->paused) {
    return;
  }

  if (! g_opt_ascii && ts_fade_in_begin) {
    return;
  }

  game->tick_update();

  handle_all_pending_things();

  things_gc_if_possible();

  //
  // Update the cursor position. But only if the mouse has moved. So if the player is moving via keyboard alone, we
  // don't pollute the screen.
  //
  if (g_opt_ascii) {
    cursor_move();
  } else {
    if ((sdl.wheel_x != 0) || (sdl.wheel_y != 0)) {
      cursor_move();
    } else if (! time_have_x_tenths_passed_since(10, wid_last_mouse_motion)) {
      cursor_move();
    }
  }

  if (! cursor) {
    if (player) {
      cursor = thing_new("cursor", player->curr_at);
    }
  }

  //
  // Even if a tick is not running, we need to animate all things
  //
  {
    ;
    FOR_ALL_ANIMATED_THINGS_LEVEL(this, t)
    {
      t->animate();
      t->update_interpolated_position();
      t->fall_curr();
    }
    FOR_ALL_ANIMATED_THINGS_LEVEL_END(this)

    FOR_ALL_ANIMATED_THINGS_LEVEL(this, t)
    {
      if (t->is_scheduled_for_death) {
        t->is_scheduled_for_death = false;
        t->dead(t->dead_reason_get());
      }
    }
    FOR_ALL_ANIMATED_THINGS_LEVEL_END(this)
  }

  //
  // Is there a tick in progress?
  //
  if (! game->tick_begin_ms) {
    //
    // If the level has started, we can enter robot mode.
    //
    if (g_opt_ascii || ! ts_fade_in_begin) {
      if (game->robot_mode_requested != game->robot_mode) {
        LOG("INF: Pressed requested robot change");
        game->robot_mode                = game->robot_mode_requested;
        game->robot_mode_tick_requested = true;
        wid_actionbar_robot_mode_update();
        if (game->robot_mode) {
          game->tick_begin("robot mode");
          LOG("INF: Robot mode");
        } else {
          LOG("INF: Robot mode off");
        }
      }
    }

    //
    // Check for level transitions
    //
    if (g_opt_ascii || fade_out_finished) {
      if (player && player->is_waiting_to_descend_dungeon) {
        if (! player->descend_dungeon()) {
          player->err("Failed to descend dungeon");
        }
      }
      if (player && player->is_waiting_to_ascend_dungeon) {
        if (! player->ascend_dungeon()) {
          player->err("Failed to ascend dungeon");
        }
      }
      if (player && player->is_waiting_to_descend_sewer) {
        if (! player->descend_sewer()) {
          player->err("Failed to descend sewer");
        }
      }
      if (player && player->is_waiting_to_ascend_sewer) {
        if (! player->ascend_sewer()) {
          player->err("Failed to ascend sewer");
        }
      }
      if (player && player->is_waiting_to_leave_level_has_completed_fall) {
        player->fall_to_next_level();
      }
      fade_out_finished = false;
    }

    if (game->things_are_moving) {
      ERR("No tick in progress but things are still moving");
    }

    //
    // The last tick is done, but there is work to do in the next tick
    //
    if (! game->tick_requested.empty()) {
      tick_begin_now();
    }
    return;
  }

  if (game->things_are_moving) {
    dbg("Tick (things are moving)");
  } else {
    dbg("Tick");
  }
  TRACE_AND_INDENT();

  //
  // Update the player map if needed. It is quite slow.
  //
  if (request_dmap_to_player_update) {
    request_dmap_to_player_update = false;
    dmap_to_player_update();
  }

  //
  // For all things that move, like monsters, or those that do not, like wands, and even those that do not move but
  // can be destroyed, like walls. Omits things like floors, corridors, the grid; those that generally do nothing or
  // are hidden.
  //
  game->things_are_moving = false;

  //
  // Tick things in a priority order, so lasers hit first, then the player,
  // then monsters etc...
  //
  for (uint8_t tick_prio = MAP_TICK_PRIO_VERY_HIGH; tick_prio < MAP_TICK_PRIO; tick_prio++) {
    FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t)
    {
      if (likely(t->tick_prio() != tick_prio)) {
        continue;
      }

      int remaining = t->movement_remaining();
      if (remaining <= 0) {
        continue;
      }

      if (t->is_waiting) {
        continue;
      }

      //
      // While moves remain, things are still moving
      //
      game->things_are_moving = true;

      auto speed = t->move_speed_total();
      if (speed) {
        if (player) {
          remaining -= player->move_speed_total();
        } else {
          remaining -= 100;
        }
        t->movement_remaining_set(remaining);
      } else {
        t->movement_remaining_set(0);
      }

      uint32_t tick_begin_ms = time_ms();
      t->tick();
      {
        if ((time_ms() - tick_begin_ms) > THING_TICK_DURATION_TOO_LONG) {
          t->con("PERF: Thing took too long, tick duration %u ms, max %u ms", time_ms() - tick_begin_ms,
                 THING_TICK_DURATION_TOO_LONG);
        }
      }
    }
    FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)
  }

  FOR_ALL_INTERESTING_THINGS_ON_LEVEL(this, t)
  {
    if (t->is_scheduled_for_jump_end) {
      t->is_scheduled_for_jump_end = false;
      t->jump_end();
    }
    if (t->is_scheduled_for_death) {
      t->is_scheduled_for_death = false;
      t->dead(t->dead_reason_get());
    }
  }
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(this)

  static const int wait_count_max = THING_TICK_WAIT_TOO_LONG;
  static int       wait_count;
  wait_count++;

  FOR_ALL_INTERESTING_THINGS_ON_LEVEL(this, t)
  {
    //
    // Wait for animation end. Only if the thing is onscreen
    //
    if (t->frame_count != game->frame_count) {
      t->is_offscreen = true;
    } else {
      t->is_offscreen = false;
    }

    t->update_interpolated_position();
    t->fall_curr();

    //
    // Check if we finished moving above. If not, keep waiting.
    //
    if (t->is_moving) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on moving thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      t->is_waiting           = true;
      // t->con("WAIT %d moving", __LINE__);
    }

    //
    // Check if we finished moving above. If not, keep waiting.
    //
    if (t->is_jumping) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on jumping thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      t->is_waiting           = true;
      // t->con("WAIT %d jumping", __LINE__);
    }

    //
    // If falling we need to update the z depth and position; and wait.
    //
    if (t->is_falling) {
      game->things_are_moving = true;
      t->is_waiting           = true;
      // t->con("WAIT %d", __LINE__);
    }

    //
    // Wait on dying thing?
    //
    if (t->is_dead_on_end_of_anim() && ! (t->is_dead || t->is_scheduled_for_death || t->is_offscreen)) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on dying thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      t->is_waiting           = true;
      // t->con("WAIT %d", __LINE__);
    }

    //
    // Wait on resurrecting thing?
    //
    if (t->is_alive_on_end_of_anim() && t->is_resurrecting) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on resurrecting thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      t->is_waiting           = true;
      // t->con("WAIT %d", __LINE__);
    }

    FOR_ALL_EQUIP(e)
    {
      //
      // Check for any use animations e.g. a jelly's attack with green splatter anim.
      //
      auto equip_id = t->equip_id_use_anim(e);
      if (equip_id.ok()) {
        auto w = thing_find(equip_id);
        if (w && ! (w->is_dead || w->is_scheduled_for_death || w->is_offscreen)) {
          if ((wait_count > wait_count_max) && ! game->things_are_moving) {
            w->con("Waiting on this");
            t->con("This is the owner");
          }
          game->things_are_moving = true;
          t->is_waiting           = true;
          // w->con("WAIT EQUIP %d", __LINE__);
          // t->con("WAIT %d", __LINE__);
        }
      }
    }

    if (t->is_waiting_to_leave_level_has_completed_fall) {
      t->fall_to_next_level();
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on waiting to fall thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      t->is_waiting           = true;
      // t->con("WAIT %d", __LINE__);
    }

    if (t->is_scheduled_for_death) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on scheduled for death thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      t->is_waiting           = true;
      // t->con("WAIT %d", __LINE__);
    }

    //
    // Make sure weapons keep up
    //
    FOR_ALL_EQUIP(e)
    {
      auto o = t->equip_carry_anim(e);
      if (o) {
        o->update_interpolated_position();
        o->fall_curr();
      }
    }
  }
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(this)

  //
  // If things are still moving, we need to wait.
  //
  if (game->things_are_moving) {
    if (! game->robot_mode) {
      if (ts_entered && time_have_x_tenths_passed_since(10, ts_entered)) {
        //
        // If the player is waiting to move, do we need to bump the time and make things faster.
        //
        if (game->request_player_move || (player && player->aip()->move_path.size())) {
          if ((time_ms() - game->tick_begin_ms) > game->current_move_speed) {
            game->tick_current_is_too_slow = true;
            time_game_delta += 10;
          }
        }
      }
    }

    return;
  }

  debug_path_clear();

  wait_count = 0;

  //
  // If things have stopped moving, perform location checks on where they
  // are now. This handles things like shoving a monst into a chasm. We do
  // location checks on the ends of moves, but this is a backup and will
  // also handle things that do not move, like a wand that is now on fire.
  //
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL(this, t)
  {
    //
    // Need to do this even for dead things, so corpses don't hover over chasms.
    //
    t->location_check();
  }
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(this)

  //
  // Fast moving things may still have stuff to do
  //
  bool work_to_do = game->things_are_moving;
  FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t)
  {
    if (t->movement_remaining() > 0) {
      work_to_do              = true;
      game->things_are_moving = true;
    }
    t->is_waiting = false;
  }
  FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)
  if (work_to_do) {
    return;
  }

  //
  // Stop rapid pickup/drop events if particles are still in progress
  // Don't move this priot to update_interpolated_position or see flicker
  // in jumping.
  //
  if (player && player->particle_anim_exists()) {
    return;
  }

  //
  // The robot needs to be more deterministic and less loosy goosey
  //
  if (0) {
    //
    // No, it slows the game too much. Let's live with some non determinism.
    //
    if (game->robot_mode) {
      //
      // No moving if weapons have not finished firing
      //
      if (all_projectiles.size()) {
        return;
      }

      if (new_projectiles.size()) {
        return;
      }

      if (all_lasers.size()) {
        return;
      }

      if (new_lasers.size()) {
        return;
      }

      if (all_internal_particles.size()) {
        return;
      }

      if (new_internal_particles.size()) {
        return;
      }

      if (all_external_particles.size()) {
        return;
      }

      if (new_external_particles.size()) {
        return;
      }
    }
  }

  //
  // We've finished waiting on all things, bump the game tick.
  //
  dbg("Level tick about to end as finshed on waiting");
  TRACE_AND_INDENT();
  bool tick_done = game->tick_end();

  //
  // Check for robot mode changes
  //
  if (g_opt_ascii || ! ts_fade_in_begin) {
    if (game->robot_mode_requested != game->robot_mode) {
      LOG("INF: Pressed requested robot change");
      game->robot_mode                = game->robot_mode_requested;
      game->robot_mode_tick_requested = true;
      wid_actionbar_robot_mode_update();
      if (game->robot_mode) {
        game->tick_begin("robot mode");
        LOG("INF: Robot mode");
      } else {
        LOG("INF: Robot mode off");
      }
    }
  }

  if (tick_done) {
    dbg("Level tick done");
    TRACE_AND_INDENT();

    handle_all_pending_things();
    things_gc_if_possible();
    create_wandering_monster();
#if 0
    //
    // For debugging consistent randomness
    //
    float h = 0;
    FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t) {
      h += t->curr_at.x;
      h += t->curr_at.y;
      t->con("at %f,%f", t->curr_at.x, t->curr_at.y);
    } FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)
    CON("TICK %d hash %f random %d", game->tick_current, h, pcg_rand());
#endif
  }

  if (tick_done) {
    if (player && game->robot_mode) {
      dbg("Level tick done and in robot mode");
      TRACE_AND_INDENT();

      if (game->robot_mode_tick_requested) {
        dbg("Robot: tick requested");
        TRACE_AND_INDENT();

        game->robot_mode_tick_requested = false;
        if (game->robot_mode) {
          player->ai_tick();
        } else if (player->aip()->move_path.size()) {
          player->path_pop_next_move(THING_MOVE_REASON_AI);
        }
      }

      if (game->tick_requested.empty()) {
        dbg("Robot: no new tick was requested, so tick anyway");
        TRACE_AND_INDENT();
        game->robot_mode_tick();
      } else {
        dbg("Robot: a new tick was requested");
      }
    } else if (player) {
      if (game->robot_mode) {
        player->ai_tick();
      } else if (player->aip()->move_path.size()) {
        player->path_pop_next_move(THING_MOVE_REASON_AI);
      }
    }
  }

  //
  // A new game event has occurred?
  //
  tick_begin_now();
}

void Level::tick(void)
{
  pcg_random_allowed++;
  tick_();
  pcg_random_allowed--;
}

void Level::tick_begin_now(void)
{
  //
  // A new game event has occurred?
  //
  if (game->tick_requested.empty()) {
    return;
  }

  dbg("Tick begin now");
  TRACE_AND_INDENT();

  game->tick_begin_now();

  dbg("Tick add movement to all things");
  TRACE_AND_INDENT();
  FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t)
  {
    //
    // Give things a bit of time to move
    //
    auto speed = t->move_speed_total();
    if (speed) {
      t->movement_remaining_incr(speed);
    } else {
      //
      // Things that do not move need to tick too.
      //
      t->movement_remaining_incr(1);
    }

    //
    // Allow the same thing to hit us again
    //
    if (t->maybe_aip()) {
      t->aip()->recently_hit_by.clear();
    }
  }
  FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)
}

void Level::update_all_ticks(void)
{
  TRACE_NO_INDENT();

  FOR_ALL_INTERESTING_THINGS_ON_LEVEL(this, t)
  {
    for (auto &i : interesting_things) {
      auto t = i.second;
      t->update_tick();
    }
  }
  FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(this)
}
