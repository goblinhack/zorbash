//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

//
// Python callback upon being fall
//
void Thing::on_fall(void)
{
  TRACE_NO_INDENT();
  auto on_fall = tp()->on_fall_do();
  if (std::empty(on_fall)) {
    return;
  }

  auto t = split_tokens(on_fall, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%ss)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_fall call [%s] expected mod:function, got %d elems", on_fall.c_str(), (int) on_fall.size());
  }
}

void Thing::fall(float fall_height, ts_t ms)
{
  TRACE_NO_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    dbg("No");
    return;
  }

  if (is_critical_to_level()) {
    dbg("No, critical");
    return;
  }

  if (! is_able_to_fall()) {
    dbg("No, unable to fall");
    return;
  }

  auto t = set_ts_fall_begin(time_get_time_ms_cached());
  set_ts_fall_end(t + ms);

  set_fall_height(fall_height);

  dbg("Begin falling");
  TRACE_AND_INDENT();

  //
  // Push pop here is needed to remove items as they are now in freefall
  //
  level_pop();
  is_falling = true;
  level_push();

  //
  // If a mob falls, the connection to the minions is severed
  //
  if (is_mob_spawner()) {
    destroy_minions(nullptr);
  }

  if (is_spawner()) {
    destroy_spawned(nullptr);
  }

  if (is_on_fire()) {
    if (is_player()) {
      TOPCON("%%fg=green$The fall puts out the flames!%%fg=reset$");
    }
    unset_on_fire();
  }

  if (is_player() || is_monst() || is_item()) {
    wobble(360);
  }
}

float Thing::get_fall(void)
{
  if (! is_falling) {
    return 0;
  }

  auto ts = time_get_time_ms_cached();

  if (ts >= get_ts_fall_end()) {
    is_falling = false;
    dbg("End of falling timestamp");
    TRACE_AND_INDENT();

    level_push();
    is_waiting_to_leave_level_has_completed_fall = true;

    //
    // Things that do not tick, like bones, need to fall on the end of the tick
    //
    if (! is_tickable()) {
      level->all_things_pending_fall[ get_group() ].insert(std::pair(id, this));
    }
    return 0;
  }

  float time_step = (float) (ts - get_ts_fall_begin()) / (float) (get_ts_fall_end() - get_ts_fall_begin());
  dbg("Is currently falling, dt %f", time_step);

  //
  // This hide things like the sword
  //
  if (time_step > 0.95) {
    is_changing_level = true;

    if (is_player()) {
      dbg("Player is waiting to complete the fall");
      level->ts_fade_out_begin = time_get_time_ms_cached();
    }

    is_waiting_to_leave_level_has_completed_fall = true;
  }

  float height = get_fall_height() * time_step;

  return (height);
}

bool Thing::fall_to_next_level(void)
{
  if (! maybe_infop()) {
    return false;
  }

  dbg("Try to fall to next level");
  TRACE_AND_INDENT();

  //
  // Fall from a dungeon to the next dungeon, 2 levels down
  //
  auto where_to = level->world_at + point3d(0, 0, 2);
  if (level->is_level_type_sewer) {
    //
    // If in a sewer then we drop only one level to the next dungeon.
    //
    where_to = level->world_at + point3d(0, 0, 1);
  }

  game->init_level(where_to);
  if (is_player()) {
    game->current_level = where_to;
  }

  auto next_level = get(game->world.levels, where_to.x, where_to.y, where_to.z);
  if (! next_level) {
    if (is_player()) {
      TOPCON("The chasm is permanently blocked!");
    }
    dbg("No, no next level");
    return false;
  }

  auto tries = 0;
  for (;;) {
    int x;
    int y;

    //
    // Try close to where we are first; failing that anywhere will do.
    //
    if (tries < 1) {
      x = curr_at.x;
      y = curr_at.y;
    } else if (tries < 10) {
      x = curr_at.x + pcg_random_range(0, MAP_BORDER_ROOM) - MAP_BORDER_ROOM / 2;
      y = curr_at.y + pcg_random_range(0, MAP_BORDER_ROOM) - MAP_BORDER_ROOM / 2;
    } else if (tries < 100) {
      x = curr_at.x + pcg_random_range(0, MAP_BORDER_ROOM * 2) - MAP_BORDER_ROOM;
      y = curr_at.y + pcg_random_range(0, MAP_BORDER_ROOM * 2) - MAP_BORDER_ROOM;
    } else if (tries < 1000) {
      x = curr_at.x + pcg_random_range(0, MAP_BORDER_ROOM * 4) - MAP_BORDER_ROOM * 2;
      y = curr_at.y + pcg_random_range(0, MAP_BORDER_ROOM * 4) - MAP_BORDER_ROOM * 2;
    } else if (tries < 10000) {
      x = pcg_random_range(MAP_BORDER_ROOM, MAP_WIDTH - MAP_BORDER_ROOM);
      y = pcg_random_range(MAP_BORDER_ROOM, MAP_HEIGHT - MAP_BORDER_ROOM);
    } else {
      err("Could not fall to next level; tried many times to place this thing and failed");
      return false;
    }
    tries++;

    if (next_level->is_oob(x, y)) {
      dbg("No, %d,%d is out of dungeon", x, y);
      continue;
    }

    dbg("Try to fall to %d,%d", x, y);
    if (! next_level->is_able_to_stand_on(x, y)) {
      continue;
    }

    if (next_level->is_ascend_dungeon(x, y) || next_level->is_monst(x, y) || next_level->is_rock(x, y) ||
        next_level->is_door(x, y) || next_level->is_secret_door(x, y) || next_level->is_mob_spawner(x, y) ||
        next_level->is_chasm(x, y) || next_level->is_wall(x, y) || next_level->is_ascend_sewer(x, y) ||
        next_level->is_descend_sewer(x, y) || next_level->is_descend_dungeon(x, y)) {
      dbg("No, %d,%d is a special tile", x, y);
      continue;
    }

    if (next_level->is_floor(x, y) || next_level->is_corridor(x, y) || next_level->is_bridge(x, y) ||
        next_level->is_water(x, y) || next_level->is_fire(x, y) || next_level->is_lava(x, y)) {

      IF_DEBUG1
      {
        FOR_ALL_THINGS(next_level, t, x, y) { t->log("Landed under thing on new level"); }
        FOR_ALL_THINGS_END()
      }

      if (is_player()) {
        game->level = next_level;
        TOPCON("%%fg=red$You tumble into the void!%%fg=reset$");
      } else {
        if (get_distance_to_player() >= DMAP_IS_PASSABLE) {
          if (is_monst()) {
            TOPCON("You hear the distant cry of some creature falling");
          } else if (is_item()) {
            TOPCON("You hear the distant crash of something falling");
          } else {
            TOPCON("You hear the distant sound of something falling");
          }
        } else {
          if (is_monst()) {
            TOPCON("%s tumbles into the void!", text_The().c_str());
          } else if (is_item()) {
            TOPCON("%s falls into the void!", text_The().c_str());
          } else {
            TOPCON("%s slips into the void!", text_The().c_str());
          }
        }
      }

      dbg("Land on the next level, change level then move to %d,%d", x, y);
      TRACE_AND_INDENT();
      level_change(next_level);

      dbg("Land on the next level, move to %d,%d", x, y);
      TRACE_AND_INDENT();
      move_to_immediately(point(x, y));

      dbg("Level change move carried items");
      TRACE_AND_INDENT();
      move_carried_items_immediately();

      if (is_player()) {
        next_level->scroll_map_to_player();
        next_level->update_new_level();
        //
        // Make sure all monsts on the new level are at the
        // same tick or they will get lots of free attacks
        //
        next_level->update_all_ticks();
      }

      set_fall_height(0);
      if (is_player() || is_monst() || is_item()) {
        wobble(90);
      }
      visible();

      //
      // Allow mobs to fall without damage
      //
      int fall_damage = 0;
      if (is_player()) {
        fall_damage = pcg_random_range(20, 50);
      }

      if (is_wand() || is_potion() || is_mob_spawner() || is_monst()) {
        fall_damage = get_health() / 2;
      }

      if (is_ring()) {
        fall_damage = 0;
      }

      auto new_pos = make_point(x, y);
      if (next_level->is_lava(new_pos)) {
        if (is_player()) {
          TOPCON("%%fg=orange$You plunge into lava! This must be the end for you!%%fg=reset$");
        }
        fall_damage *= 3;
      } else if (next_level->is_fire(new_pos)) {
        if (is_player()) {
          TOPCON("%%fg=orange$You plunge into flames! Not a good move!%%fg=reset$");
        }
        fall_damage *= 2;
      } else if (next_level->is_deep_water(new_pos)) {
        if (is_player()) {
          TOPCON("%%fg=yellow$The deep water lessens the fall!%%fg=reset$");
        }
        fall_damage /= 4;
      } else if (next_level->is_shallow_water(new_pos)) {
        if (is_player()) {
          TOPCON("%%fg=yellow$The water lessens the fall!%%fg=reset$");
        }
        fall_damage /= 2;
      }

      if (is_player()) {
        TOPCON("%%fg=red$You take %u fall damage!%%fg=reset$", fall_damage);
      }

      if (is_monst() || is_player()) {
        bounce(2.0 /* height */, 0.5 /* fade */, 100, 3);
        next_level->thing_new(tp_random_blood_splatter()->name(), new_pos);
      }

      next_level->scroll_map_to_player();
      update_light();

      //
      // Update the z depth when falling
      //
      dbg("End of falling to next level");
      TRACE_AND_INDENT();

      level_pop();
      is_falling        = false;
      is_changing_level = false;
      update_interpolated_position();
      level_push();

      if (is_player()) {
        game->tick_begin("finished fall to next level");
        level->ts_fade_in_begin = time_get_time_ms_cached();
        level->update_new_level();
      }

      if (tp()->get_health_initial_dice_str() != "") {
        auto h = decr_health(fall_damage);
        if (h <= 0) {
          h = set_health(0);
          dead("by flying without wings");
        }
      }

      if (! is_dead) {
        on_fall();
      }

      return true;
    }

    dbg("No, not floor or lava");
  }
}
