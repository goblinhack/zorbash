//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"

void Game::tick_begin(const std::string &why)
{
  TRACE_NO_INDENT();

  tick_requested = why;

  auto level = game->get_current_level();
  if (level) {
    TRACE_AND_INDENT();
    auto player = level->player;

    if (player) {
      LOG("Seed (%s) tick %d asked (%s): %s", game->seed_name.c_str(), game->tick_current, why.c_str(),
          player->to_string().c_str());
    } else {
      LOG("Seed (%s) tick %d asked (%s): %s", game->seed_name.c_str(), game->tick_current, why.c_str(),
          level->to_string().c_str());
    }
  }
}

void Game::tick_begin_now(void)
{
  TRACE_NO_INDENT();

  std::string why = tick_requested;
  tick_requested  = "";

  //
  // Move when all things are done moving
  //
  game->tick_current++;
  game->tick_dt = 0;

  //
  // Helps to maintain randomness if the user say scrolls around the level we
  // do not want that to change the randomness of the monsters.
  //
  pcg_srand(game->tick_current);

  //
  // Set how long each tick takes.
  //
  tick_set_speed();

  auto level = game->get_current_level();
  if (level) {
    TRACE_AND_INDENT();
    auto player = level->player;
    if (player) {
      CON("Seed (%s) tick %d begin (%s): %s", game->seed_name.c_str(), game->tick_current, why.c_str(),
          player->to_string().c_str());
    } else {
      CON("Seed (%s) tick %d begin (%s): %s", game->seed_name.c_str(), game->tick_current, why.c_str(),
          level->to_string().c_str());
    }
  } else {
    CON("Seed (%s) tick %d begin (%s)", game->seed_name.c_str(), game->tick_current, why.c_str());
  }

  game->tick_begin_ms = time_ms();

  if (level) {
    level->lights_fade();
    level->tick_gas_poison();

    auto player = level->player;
    if (player && ! robot_mode) {
      player->level->fov_calculate(player, &player->aip()->can_see_currently, player->curr_at.x, player->curr_at.y,
                                   player->distance_vision_get());
    }

    //
    // Update the heatmap before the next tick
    //
    if (! level->is_heatmap_valid) {
      level->update_heatmap();
    }

    //
    // Update the noisemap before the next tick
    //
    level->update_noisemap();
  }
}

void Game::tick_set_speed(void)
{
  TRACE_NO_INDENT();

  //
  // Set how long each tick takes.
  //
  if (game->robot_mode) {
    game->current_move_speed = game->fast_move_speed;
  } else if (! game->cursor_move_path.empty()) {
    game->current_move_speed = game->fast_move_speed;
  } else {
    game->current_move_speed = game->slow_move_speed;
  }
}

bool Game::tick_end(void)
{
  TRACE_NO_INDENT();

  //
  // Move when all things are done moving
  //
  if (game->tick_completed == game->tick_current) {
    return false;
  }
  game->tick_completed = game->tick_current;

  save_snapshot_check();

  game->tick_duration            = time_ms() - game->tick_begin_ms;
  game->prev_tick_was_too_slow   = game->tick_current_is_too_slow;
  game->tick_current_is_too_slow = false;

  auto level = game->get_current_level();
  if (level) {
    auto player = level->player;
    if (player) {
      CON("Seed (%s) tick %d end, duration %d ms: %s", game->seed_name.c_str(), game->tick_current,
          time_ms() - game->tick_begin_ms, player->to_string().c_str());
    } else {
      CON("Seed (%s) tick %d end, duration %d ms: %s", game->seed_name.c_str(), game->tick_current,
          time_ms() - game->tick_begin_ms, level->to_string().c_str());
    }
  } else {
    CON("Seed (%s) tick %d end, duration %d ms", game->seed_name.c_str(), game->tick_current,
        time_ms() - game->tick_begin_ms);
  }

  CON("-");

  if (level) {
    level->update();
#if 0
    //
    // For debugging consistent randomness
    //
    uint32_t h = 0;
    FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(level, t) {
      h += (int)t->curr_at.x;
      h += (int)t->curr_at.y;
      t->con("THING AT");
    } FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(level)
    CON("TICK %d hash %u rand %d", tick_current, h, pcg_random_range(1, 10000));
#endif
  }

  //
  // Set how long each tick takes.
  //
  tick_set_speed();

  //
  // Recreate as we might need to show location specific icons, like aacend ot descend
  //
  wid_actionbar_init();

  return true;
}

void Game::tick_update(void)
{
  TRACE_NO_INDENT();

  //
  // Work out the current timestep in this move
  //
  if (game->tick_begin_ms) {
    float move_at       = time_ms() - game->tick_begin_ms;
    float move_duration = game->current_move_speed;
    game->tick_dt       = move_at / move_duration;
    if (game->tick_dt > 1) {
      game->tick_dt = 1;
    }
  }
}
