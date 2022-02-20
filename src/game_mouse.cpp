//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_sound.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid.hpp"
#include "my_wid_thing_info.hpp"

uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  LOG("Game mouse down");
  TRACE_AND_INDENT();

  if (! game || ! game->started) {
    return false;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  auto player = level->player;
  if (! player) {
    return false;
  }

  if (player->is_dead) {
    return true;
  }

  //
  // If mid air, we're done. Let other things move.
  //
  if (player->is_jumping) {
    return true;
  }

  if (! level->cursor) {
    TRACE_AND_INDENT();
    return false;
  }

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  player->log("Mouse down");
  wid_thing_info_fini();

  if (game->state == Game::STATE_CHOOSING_TARGET) {
    player->log("Chosen target");
    if (game->request_to_throw_item) {
      auto item = game->request_to_throw_item;
      player->throw_at(item, level->cursor);
    }
    if (game->request_to_fire_item) {
      auto item = game->request_to_fire_item;

      player->used(item, level->cursor, true);

      //
      // The laser name is provided by the likes of wand
      //
      if (! item->laser_name().empty()) {
        player->laser_fire_at(item->laser_name(), level->cursor->curr_at);
      } else if (! item->projectile_name().empty()) {
        player->projectile_fire_at(item->projectile_name(), level->cursor->curr_at);
      } else {
        TOPCON("Unknown beam weapon: %s.", item->text_the().c_str());
      }

      //
      // Get the damage from the enchanted wand, so the laser
      // inflicts that damage.
      //
      player->damage_current_set(item->damage_current());
    }
    return true;
  }

  if (game->state == Game::STATE_NORMAL) {
    //
    // Have we moved close enough to attack? Do this prior to checking for
    // double click so we can attack monsts sitting in lava
    //
    if (level->cursor) {
      if ((std::abs(player->curr_at.x - level->cursor->curr_at.x) <= 1) &&
          (std::abs(player->curr_at.y - level->cursor->curr_at.y) <= 1)) {
        int x = level->cursor->curr_at.x;
        int y = level->cursor->curr_at.y;
        FOR_ALL_THINGS_THAT_INTERACT(level, t, x, y)
        {
          if (t == level->player) {
            continue;
          }

          if (! t->is_dead) {
            //
            // If the door is not broken, we can close it
            //
            if (t->is_door() && t->is_open) {
              t->close_door(t);
              return true;
            }

            //
            // Attack
            //
            if (t->is_door() || t->is_monst() || t->is_mob()) {
              player->log("Close enough to attack");
              player->attack(level->cursor->curr_at);
              return true;
            }
          }
        }
        FOR_ALL_THINGS_END()
      }
    }

    //
    // If hovering over a double click thing then don't jump in unless
    // the user really means it.
    //
    if (! wid_mouse_two_clicks) {
      auto to = level->cursor->curr_at;
      FOR_ALL_THINGS(level, t, to.x, to.y)
      {
        if (t->is_hidden) {
          continue;
        }
        if (t->is_cursor_can_hover_over_x2_click()) {
          player->log("Needs double click");
          if (level->is_chasm(to)) {
            TOPCON("Double click to jump into the abyss.");
          } else if (level->is_lava(to)) {
            TOPCON("Double click to jump into the lava.");
          } else {
            TOPCON("Double click to move to move onto that.");
          }
          return true;
        }
      }
      FOR_ALL_THINGS_END()
    }

    //
    // Have we moved close enough to collect? Do this after the double
    // click check so we do not try to collect things in lava.
    //
    if (level->cursor) {
      if (player->curr_at == level->cursor->curr_at) {
        auto items = player->anything_to_carry_at(player->curr_at);
        if (items.size()) {
          game->wid_collect_create(items);
        }
      }
    }

    //
    // Grab the current move path and start walking toward it. This will
    // consume one move by the player.
    //
    if (player->cursor_path_pop_first_move()) {
      return true;
    }
  }

  return false;
}

uint8_t game_mouse_up(int32_t x, int32_t y, uint32_t button) { return false; }

uint8_t game_mouse_motion(int32_t x, int32_t y, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_AND_INDENT();
  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  if (wid_some_recent_event_occurred()) {
    return false;
  }

  if (level->cursor) {
    TRACE_AND_INDENT();
    if (level->ts_created && time_have_x_tenths_passed_since(10, level->ts_created)) {
      if (level->player && ! level->player->is_dead) {
        level->cursor->visible();
      }
    }
  }

  level->cursor_path_create();

#if 0
{
  g_debug_thing = nullptr;

  point p(level->cursor->curr_at.x, level->cursor->curr_at.y);
  TOPCON("monst %d corpse %d", level->is_monst(p), level->is_corpse(p));
  FOR_ALL_THINGS_THAT_INTERACT(level, t, level->cursor->curr_at.x, level->cursor->curr_at.y) {
    if (level->cursor->curr_at != t->curr_at) {
      continue;
    }
    if (t->is_dead) {
      continue;
    }
    if (t->is_monst()) {
      t->topcon("debug");
      g_debug_thing = t;
    }
  }
  FOR_ALL_THINGS_END()
}
#endif

  return true;
}
