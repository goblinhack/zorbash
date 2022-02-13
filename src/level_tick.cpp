//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

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

void Level::handle_all_pending_things(int group)
{
  for (auto &i : all_animated_things_pending_remove[ group ]) {
    all_animated_things[ group ].erase(i.first);
  }
  all_animated_things_pending_remove[ group ] = {};

  for (auto &i : all_animated_things_pending_add[ group ]) {
    all_animated_things[ group ].insert(i);
  }
  all_animated_things_pending_add[ group ] = {};

  for (auto &i : all_things_pending_fall[ group ]) {
    i.second->fall_to_next_level();
  }
  all_things_pending_fall[ group ] = {};
}

void Level::handle_all_pending_things(void)
{
  FOR_ALL_THING_GROUPS(group) { handle_all_pending_things(group); }
}

void Level::handle_input_events(void)
{
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

  bool up    = state[ sdlk_to_scancode(game->config.key_move_up) ];
  bool down  = state[ sdlk_to_scancode(game->config.key_move_down) ];
  bool left  = state[ sdlk_to_scancode(game->config.key_move_left) ];
  bool right = state[ sdlk_to_scancode(game->config.key_move_right) ];

  if (up || down || left || right) {
    if (! game->request_player_move) {
      game->request_player_move = time_get_time_ms();
    }
  }

  auto   level  = game->level;
  Thingp player = nullptr;
  if (level) {
    player = level->player;
  }

  //
  // After a small delay handle the player move. This allows for diagonal moves to be handled without generating two
  // key presses.
  //
  if (((player && player->aip()->move_path.size()) || game->request_player_move) &&
      time_have_x_tenths_passed_since(1, game->request_player_move)) {
    //
    // Move time along a bit if the player is waiting to move. This will cause movements and jumps to complete
    // soonet and should result in the flag below being cleared.
    //
    static int time_boost = 0;
    if (game->things_are_moving) {
      if (! time_boost) {
        time_boost = 20;
      } else {
        time_boost += 20;
      }
      if (time_boost > 50) {
        time_boost = 50;
      }

      time_delta += time_boost;
      return;
    }
    time_boost = 0;

    game->request_player_move = 0;

    bool wait_or_collect = false;
    bool jump            = false;
    bool attack          = false;

    up              = up || game->request_player_up;
    down            = down || game->request_player_down;
    right           = right || game->request_player_right;
    left            = left || game->request_player_left;
    wait_or_collect = wait_or_collect || game->request_player_wait_or_collect;

    game->request_player_up              = false;
    game->request_player_down            = false;
    game->request_player_right           = false;
    game->request_player_left            = false;
    game->request_player_wait_or_collect = false;

    if (up || down || left || right || wait_or_collect) {
      // TOPCON("%d%d%d%d", up, down, left, right);
      player_tick(left, right, up, down, attack, wait_or_collect, jump);
    }
  }
}

bool Level::tick(void)
{
  TRACE_NO_INDENT();
  // log("Tick");
  //  TOPCON("monsts %d.", monst_count);

  handle_input_events();

  if (! game->started) {
    return false;
  }

  if (game->paused) {
    return false;
  }

  if (ts_fade_in_begin) {
    return false;
  }

  if (! cursor) {
    if (player) {
      cursor = thing_new("cursor", player->curr_at);
    }
  }

  handle_all_pending_things();
  things_gc_if_possible();

  //
  // Update the player map if needed. It is quite slow.
  //
  if (request_dmap_to_player_update) {
    request_dmap_to_player_update = false;
    dmap_to_player_update();
  }

  //
  // A new game event has occurred?
  //
  if (! game->tick_requested.empty() && ! game->things_are_moving) {
    game->tick_begin_now();

    FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL(this, t)
    {
      //
      // Give things a bit of time to move
      //
      t->movement_left_incr(t->move_speed());
    }
    FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL_END(this)

    FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL(this, t)
    {
      int movement_left = t->movement_left();
      if (movement_left <= 0) {
        continue;
      }

      if (player) {
        movement_left -= player->move_speed();
      } else {
        movement_left -= 100;
      }
      t->movement_left_set(movement_left);

      uint32_t tick_begin_ms = time_get_time_ms();
      t->tick();
      IF_DEBUG2
      {
        if ((time_get_time_ms() - tick_begin_ms) > THING_TICK_DURATION_TOO_LONG * 3) {
          t->log("PERF: Thing took too long, tick duration %u ms, max %u ms", time_get_time_ms() - tick_begin_ms,
                 THING_TICK_DURATION_TOO_LONG);
        }
      }
      IF_NODEBUG2
      {
        if ((time_get_time_ms() - tick_begin_ms) > THING_TICK_DURATION_TOO_LONG) {
          t->con("PERF: Thing took too long, tick duration %u ms, max %u ms", time_get_time_ms() - tick_begin_ms,
                 THING_TICK_DURATION_TOO_LONG);
        }
      }
      // t->con("PERF: Thing took %u ms", time_get_time_ms() - tick_begin_ms);
    }
    FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL_END(this)
  }

  //
  // For all things that move, like monsters, or those that do not, like
  // wands, and even those that do not move but can be destroyed, like
  // walls. Omits things like floors, corridors, the grid; those that
  // generally do nothing or are hidden.
  //
  game->things_are_moving = false;

  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
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
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)

  static const int wait_count_max = THING_TICK_WAIT_TOO_LONG;
  static int       wait_count;
  wait_count++;

  //
  // Animate anything that needs it
  //
  FOR_ALL_THING_GROUPS(group)
  {
    ;
    FOR_ALL_ANIMATED_THINGS_LEVEL(this, group, t)
    {
      t->animate();
      t->update_interpolated_position();
      t->fall_get();

      //
      // We need to check all animated things are finished moving as they
      // may not intersect with all interactive things. i.e a carried
      // sword animation.
      //
      if (t->is_moving) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on animated moving thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
        // t->con("WAIT %d", __LINE__);
      }
    }
    FOR_ALL_ANIMATED_THINGS_LEVEL_END(this)

    FOR_ALL_ANIMATED_THINGS_LEVEL(this, group, t)
    {
      if (t->is_scheduled_for_death) {
        t->is_scheduled_for_death = false;
        t->dead(t->dead_reason_get());
      }
    }
    FOR_ALL_ANIMATED_THINGS_LEVEL_END(this)
  }

  game->tick_update();

  //
  // Update the cursor position. But only if the mouse has moved. So if the
  // player is moving via keyboard alone, we don't pollute the screen.
  //
  if ((wheel_x != 0) || (wheel_y != 0)) {
    cursor_move();
  } else if (! time_have_x_tenths_passed_since(10, wid_last_mouse_motion)) {
    cursor_move();
  }

  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
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
    t->fall_get();

    //
    // Check if we finished moving above. If not, keep waiting.
    //
    if (t->is_moving) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on moving thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      // t->con("WAIT %d", __LINE__);
    }

    //
    // Check if we finished moving above. If not, keep waiting.
    //
    if (t->is_jumping) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on jumping thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      // t->con("WAIT %d", __LINE__);
    }

    //
    // If falling we need to update the z depth and position; and wait.
    //
    if (t->is_falling) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on falling thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
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
      // t->con("WAIT %d", __LINE__);
    }

    FOR_ALL_EQUIP(e)
    {
      auto equip_id = t->equip_id_use_anim(e);
      if (equip_id.ok()) {
        auto w = thing_find(equip_id);
        if (w && ! (w->is_dead || w->is_scheduled_for_death)) {
          if ((wait_count > wait_count_max) && ! game->things_are_moving) {
            w->con("Waiting on this");
            t->con("This is the owner");
          }
          game->things_are_moving = true;
          // w->con("WAIT EQUIP %d", __LINE__);
          // t->con("WAIT %d", __LINE__);
        }
      }
    }

    if (t->ts_flip_start_get() && ! (t->is_dead || t->is_scheduled_for_death)) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on flipping thing longer than expected: %s", t->to_dbg_string().c_str());
      }

      game->things_are_moving = true;
      // t->con("WAIT %d", __LINE__);

      //
      // Make sure offscreen animation occurs.
      //
      if (t->is_offscreen) {
        t->ts_flip_start_set(0);
      }
    }

    if (t->is_waiting_to_leave_level_has_completed_fall) {
      t->fall_to_next_level();
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on waiting to fall thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      // t->con("WAIT %d", __LINE__);
    }

    if (t->is_scheduled_for_death) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on scheduled for death thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
      // t->log("WAIT %d", __LINE__);
    }

    //
    // Make sure weapons keep up
    //
    FOR_ALL_EQUIP(e)
    {
      auto o = t->equip_carry_anim(e);
      if (o) {
        o->update_interpolated_position();
        o->fall_get();
      }
    }
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)

  if (fade_out_finished) {
    if (player && player->is_waiting_to_descend_dungeon) {
      if (! player->descend_dungeon()) {
        player->err("Failed to descend dungeon");
      }
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        player->con("Waiting on descending player thing longer than expected: %s", player->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }
    if (player && player->is_waiting_to_ascend_dungeon) {
      if (! player->ascend_dungeon()) {
        player->err("Failed to ascend dungeon");
      }
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        player->con("Waiting on ascending player thing longer than expected: %s", player->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }
    if (player && player->is_waiting_to_descend_sewer) {
      if (! player->descend_sewer()) {
        player->err("Failed to descend sewer");
      }
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        player->con("Waiting on descending sewer player thing longer than expected: %s",
                    player->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }
    if (player && player->is_waiting_to_ascend_sewer) {
      if (! player->ascend_sewer()) {
        player->err("Failed to ascend sewer");
      }
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        player->con("Waiting on ascending sewer player thing longer than expected: %s",
                    player->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }
    if (player && player->is_waiting_to_leave_level_has_completed_fall) {
      player->fall_to_next_level();
      game->things_are_moving = true;
    }
  }

  if (game->things_are_moving) {
    if (ts_created && time_have_x_tenths_passed_since(10, ts_created)) {
      if (game->request_player_move || (player && player->aip()->move_path.size())) {
        if ((time_get_time_ms() - game->tick_begin_ms) > 100) {
          game->tick_current_is_too_slow = true;
          time_delta += 20;
        } else if ((time_get_time_ms() - game->tick_begin_ms) > 50) {
          game->tick_current_is_too_slow = true;
          time_delta += 10;
        } else if ((time_get_time_ms() - game->tick_begin_ms) > 20) {
          game->tick_current_is_too_slow = true;
          time_delta += 5;
        }
      }
    }

    return false;
  }

  debug_path_clear();

  wait_count = 0;

  //
  // Stop rapid pickup/drop events if particles are still in progress
  // Don't move this priot to update_interpolated_position or see flicker
  // in jumping.
  //
  if (player && player->particle_anim_exists()) {
    return false;
  }

  //
  // The robot needs to be more deterministic and less loosy goosey
  //
  if (game->robot_mode) {
    //
    // No moving if weapons have not finished firing
    //
    if (all_projectiles.size()) {
      return false;
    }

    if (new_projectiles.size()) {
      return false;
    }

    if (all_lasers.size()) {
      return false;
    }

    if (new_lasers.size()) {
      return false;
    }

    if (all_internal_particles.size()) {
      return false;
    }

    if (new_internal_particles.size()) {
      return false;
    }

    if (all_external_particles.size()) {
      return false;
    }

    if (new_external_particles.size()) {
      return false;
    }
  }

  //
  // If things have stopped moving, perform location checks on where they
  // are now. This handles things like shoving a monst into a chasm. We do
  // location checks on the ends of moves, but this is a backup and will
  // also handle things that do not move, like a wand that is now on fire.
  //
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
  {
    //
    // Need to do this even for dead things, so corpses don't hover over
    // chasms.
    //
    t->location_check();
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)

  //
  // We've finished waiting on all things, bump the game tick.
  //
  bool tick_done = game->tick_end();

  if (tick_done) {
    LOG("Level tick done");
    TRACE_AND_INDENT();

    handle_all_pending_things();
    things_gc_if_possible();
    create_wandering_monster();
#if 0
    //
    // For debugging consistent randomness
    //
    float h = 0;
    FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t) {
      h += t->curr_at.x;
      h += t->curr_at.y;
      t->con("at %f,%f", t->curr_at.x, t->curr_at.y);
    } FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)
    CON("TICK %d hash %f random %d", game->tick_current, h, pcg_rand());
#endif
  }

  //
  // If the level has started, we can enter robot mode.
  //
  if (! ts_fade_in_begin) {
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
    if (player && game->robot_mode) {
      LOG("Level tick done and in robot mode");
      TRACE_AND_INDENT();

      if (game->robot_mode_tick_requested) {
        LOG("Robot: tick requested");
        TRACE_AND_INDENT();

        game->robot_mode_tick_requested = false;
        if (game->robot_mode) {
          player->ai_tick();
        } else if (player->aip()->move_path.size()) {
          player->path_pop_next_move();
        }
      }

      if (game->tick_requested.empty()) {
        LOG("Robot: no tick requested");
        TRACE_AND_INDENT();

        //
        // We can get stuck with timing with the inventory open. So make sure we close it.
        //
        if (game->state != Game::STATE_NORMAL) {
          LOG("Robot: reset to normal state");
          player->change_state(MONST_STATE_IDLE, "reset to normal state");
        }

        LOG("Robot: no new tick was requested, so tick anyway");
        game->robot_mode_tick();
      } else {
        LOG("Robot: a new tick was requested");
      }
    } else if (player) {
      if (game->robot_mode) {
        player->ai_tick();
      } else if (player->aip()->move_path.size()) {
        player->path_pop_next_move();
      }
    }
  }

  //
  // Only update robot mode if things have stopped moving so we get
  // consistent random behaviour.
  //
  if (! game->tick_requested.empty()) {
    return true;
  }

  return false;
}

void Level::update_all_ticks(void)
{
  TRACE_AND_INDENT();
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto &i : all_things_of_interest[ group ]) {
      auto t = i.second;
      t->update_tick();
    }
  }
}
