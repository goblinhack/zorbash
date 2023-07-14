//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

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

void Thing::on_fall_begin(void)
{
  TRACE_NO_INDENT();
  auto on_fall_begin = tp()->on_fall_begin_do();
  if (std::empty(on_fall_begin)) {
    return;
  }

  auto t = split_tokens(on_fall_begin, '.');
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
    ERR("Bad on_fall_begin call [%s] expected mod:function, got %d elems", on_fall_begin.c_str(),
        (int) on_fall_begin.size());
  }
}

bool Thing::fall(void)
{
  TRACE_NO_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer
      || is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall
      || is_jumping) {
    dbg("No");
    return false;
  }

  if (is_critical_to_level()) {
    dbg("No, critical");
    return false;
  }

  if (! is_able_to_fall()) {
    dbg("No, unable to fall");
    return false;
  }

  //
  // Some things like fire die when falling
  //
  if (is_dead_on_falling()) {
    dead("No, dead on falling");
    return false;
  }

  const float fall_height = 1;
  auto        duration    = THING_FALL_SPEED_MS;

  if (g_opt_ascii || ! is_visible_to_player) {
    //
    // Ascii mode, fall is immediate
    //
    duration = 0;
  } else {
    //
    // Check the number of things jumping is not slowing the game too much
    //
    if (game->tick_current_is_too_slow || game->prev_tick_was_too_slow) {
      duration /= 4;
    }
  }

  auto t = ts_fall_begin_set(time_ms_cached());
  ts_fall_end_set(t + duration);

  fall_height_set(fall_height);

  dbg("Begin falling");
  TRACE_AND_INDENT();

  //
  // Gives a chance to play a sound effect before falling begins which can have a delay
  // while the level is setup.
  //
  on_fall_begin();

  //
  // Push pop here is needed to remove items as they are now in freefall
  //
  level_pop();
  is_falling = true;
  level_push();

  //
  // If a mob falls, the connection to the minions is severed
  //
  if (is_mob()) {
    destroy_minions(nullptr);
  }

  if (is_able_to_spawn_things()) {
    destroy_spawned(nullptr);
  }

  if (is_on_fire()) {
    if (is_player()) {
      msg("%%fg=green$The fall puts out the flames!%%fg=reset$");
    }
    on_fire_unset();
  }

  if (is_player() || is_monst() || is_item()) {
    wobble(360);
  }

  return true;
}

float Thing::fall_curr(void)
{
  TRACE_NO_INDENT();

  if (! is_falling) {
    return 0;
  }

  auto ts = time_ms_cached();

  if (ts >= ts_fall_end()) {
    is_falling = false;
    dbg("End of falling timestamp");
    TRACE_AND_INDENT();

    level_push();
    is_waiting_to_leave_level_has_completed_fall = true;

    //
    // Things that do not tick, like bones, need to fall on the end of the tick
    //
    if (! is_tickable()) {
      level->all_things_pending_fall.insert(std::pair(id, this));
    }
    return 0;
  }

  float time_step = ((float) (ts) -ts_fall_begin()) / ((float) (ts_fall_end()) - ts_fall_begin());
  dbg("Is currently falling, dt %f", time_step);

  //
  // This hide things like the sword
  //
  if (time_step > 0.95) {
    is_changing_level = true;

    if (is_player()) {
      dbg("Player is waiting to complete the fall");
      if (! g_opt_ascii) {
        level->ts_fade_out_begin = time_ms_cached();
      }
    }

    is_waiting_to_leave_level_has_completed_fall = true;
  }

  float height = fall_height_curr() * time_step;

  return height;
}

bool Thing::fall_to_next_level(void)
{
  if (! maybe_infop()) {
    return false;
  }

  dbg("Try to fall to next level");
  TRACE_AND_INDENT();

  //
  // Fall to the next level that exists beneath. If nothing exists, fall into the void.
  //
  auto fall_to = level->world_at;
  if (level->biome == BIOME_SEWER) {
    fall_to.z--;
  }

  Levelp l = nullptr;

  for (;;) {
    fall_to.z += 2;

    if (fall_to.z >= LEVELS_DEEP) {
      fall_into_the_void();
      return false;
    }

    l = get(game->world.levels, fall_to.x, fall_to.y, fall_to.z);
    if (l) {
      break;
    }
  }

  if (! l) {
    fall_into_the_void();
    return false;
  }

  if (is_player()) {
    game->current_level = fall_to;
  }

  dbg("Try to fall where to fall in the next level at depth %d", fall_to.z);
  TRACE_AND_INDENT();

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
      x = curr_at.x + pcg_random_range(0, MAP_BORDER_ROCK) - MAP_BORDER_ROCK / 2;
      y = curr_at.y + pcg_random_range(0, MAP_BORDER_ROCK) - MAP_BORDER_ROCK / 2;
    } else if (tries < 100) {
      x = curr_at.x + pcg_random_range(0, MAP_BORDER_ROCK * 2) - MAP_BORDER_ROCK;
      y = curr_at.y + pcg_random_range(0, MAP_BORDER_ROCK * 2) - MAP_BORDER_ROCK;
    } else if (tries < 1000) {
      x = curr_at.x + pcg_random_range(0, MAP_BORDER_ROCK * 4) - MAP_BORDER_ROCK * 2;
      y = curr_at.y + pcg_random_range(0, MAP_BORDER_ROCK * 4) - MAP_BORDER_ROCK * 2;
    } else if (tries < 10000) {
      x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK);
      y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK);
    } else {
      err("Could not fall to next level; tried many times to place this thing and failed");
      return false;
    }
    tries++;

    if (l->is_oob(x, y)) {
      dbg("No, %d,%d is out of dungeon", x, y);
      continue;
    }

    dbg("Try to fall to %d,%d", x, y);
    if (! l->is_able_to_stand_on(x, y)) {
      continue;
    }

    if (l->is_ascend_dungeon(x, y) || l->is_monst(x, y) || l->is_rock(x, y) || l->is_door(x, y)
        || l->is_secret_door(x, y) || l->is_mob(x, y) || l->is_chasm(x, y) || l->is_wall(x, y)
        || l->is_ascend_sewer(x, y) || l->is_descend_sewer(x, y) || l->is_descend_dungeon(x, y)) {
      dbg("No, %d,%d is a special tile", x, y);
      continue;
    }

    if (d20_ge(stat_luck_total(), SAVING_ROLL_MODERATE)) {
      if (l->is_lava(x, y) || l->is_fire(x, y)) {
        dbg("No, %d,%d is an unlucky tile", x, y);
        continue;
      }
    }

    if (l->is_floor(x, y) || l->is_corridor(x, y) || l->is_bridge(x, y) || l->is_water(x, y) || l->is_fire(x, y)
        || l->is_lava(x, y)) {

      if (is_player()) {
        game->level = l;
        msg("%%fg=red$You tumble into the void!%%fg=reset$");
        popup("Aargh!");
      } else {
        if (distance_to_player() >= DMAP_IS_PASSABLE) {
          if (is_monst()) {
            msg("You hear the distant cry of some creature falling");
          } else if (is_item()) {
            msg("You hear the distant crash of something falling");
          } else {
            msg("You hear the distant sound of something falling");
          }
        } else {
          if (is_monst()) {
            msg("%s tumbles into the void!", text_The().c_str());
            if (is_humanoid()) {
              if (! is_dead) {
                popup("Curses!");
              }
            }
          } else if (is_item()) {
            msg("%s falls into the void!", text_The().c_str());
          } else {
            msg("%s fades into the void!", text_The().c_str());
          }
        }
      }

      dbg("Land on the next level, change level then move to %d,%d", x, y);
      TRACE_AND_INDENT();
      level_change(l);

      dbg("Land on the next level, move to %d,%d", x, y);
      TRACE_AND_INDENT();
      move_to_immediately(point(x, y));

      dbg("Level change move carried items");
      TRACE_AND_INDENT();
      move_carried_items_immediately();

      if (is_player()) {
        l->scroll_map_to_player();
        l->update_new_level();
        //
        // Make sure all monsters on the new level are at the
        // same tick or they will get lots of free attacks
        //
        l->update_all_ticks();
      }

      fall_height_set(0);
      if (is_player() || is_monst() || is_item()) {
        wobble(90);
      }
      visible("fall to next level");

      //
      // Allow mobs to fall without damage
      //
      int fall_dmg = 0;
      if (is_player()) {
        fall_dmg = pcg_random_range(5, 30);
      }

      if (is_staff() || is_potion() || is_mob() || is_monst()) {
        fall_dmg = health() / 2;
      }

      if (is_ring()) {
        fall_dmg = 0;
      }

      if (is_brittle()) {
        fall_dmg *= 2;
      }

      dbg("Level change where you landed");
      auto new_pos = make_point(x, y);
      if (l->is_lava(new_pos)) {
        if (is_player()) {
          msg("%%fg=orange$You plunge into lava! This must be the end for you!%%fg=reset$");
        }
        fall_dmg *= 3;
      } else if (l->is_fire(new_pos)) {
        if (is_player()) {
          msg("%%fg=orange$You plunge into flames! Not a good move!%%fg=reset$");
        }
        fall_dmg *= 2;
      } else if (l->is_deep_water(new_pos)) {
        if (is_player()) {
          msg("%%fg=yellow$The deep water lessens the fall!%%fg=reset$");
        }
        fall_dmg /= 4;
      } else if (l->is_shallow_water(new_pos)) {
        if (is_player()) {
          msg("%%fg=yellow$The water lessens the fall!%%fg=reset$");
        }
        fall_dmg /= 2;
      }

      if (is_player()) {
        msg("%%fg=red$You take %u fall damage!%%fg=reset$", fall_dmg);
      }

      if (is_monst() || is_player()) {
        bounce(2.0 /* height */, 0.5 /* fade */, 100, 3);
        if (is_meat()) {
          l->thing_new(tp_random_red_splatter()->name(), new_pos);
        } else if (is_red_blooded()) {
          l->thing_new(tp_random_green_splatter()->name(), new_pos);
        } else if (is_green_blooded()) {
          l->thing_new(tp_random_green_splatter()->name(), new_pos);
        }
      }

      l->scroll_map_to_player();
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
        level->ts_fade_in_begin = time_ms_cached();
        level->update_new_level();
        level->is_entered_by_falling = true;
      }

      //
      // Death from too much fall damage
      //
      if (health_max()) {
        auto h = health_decr(fall_dmg);
        if (h <= 0) {
          h = health_set(0);
          dead("by flying without wings");
        }
      }

      //
      // Falling while frozen is fatal
      //
      if (is_frozen) {
        if (l->is_deep_water(new_pos)) {
          if (is_player()) {
            msg("%%fg=lightblue$You plunge into the water and defrost!%%fg=reset$");
          }
          frozen_unset();
        } else if (l->is_lava(new_pos)) {
          if (is_player()) {
            msg("%%fg=red$You defrost and then vaporize!%%fg=reset$");
          }
          dead("by vaporizing");
        } else {
          if (is_player()) {
            msg("%%fg=red$You shatter into tiny frozen pieces!%%fg=reset$");
          }
          dead("by shattering");
        }
      }

      if (! is_dead) {
        wake("fell");
        movement_remaining_set(0);
      }

      return true;
    }

    dbg("No, not floor or lava");
  }
}

////////////////////////////////////////////////////////////////////////////
// ts_fall_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_fall_begin(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_fall_begin);
  }
  return 0;
}

ts_t Thing::ts_fall_begin_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin = v);
}

ts_t Thing::ts_fall_begin_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin -= v);
}

ts_t Thing::ts_fall_begin_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin += v);
}

ts_t Thing::ts_fall_begin_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin--);
}

ts_t Thing::ts_fall_begin_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fall_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_fall_end(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_fall_end);
  }
  return 0;
}

ts_t Thing::ts_fall_end_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end = v);
}

ts_t Thing::ts_fall_end_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end -= v);
}

ts_t Thing::ts_fall_end_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end += v);
}

ts_t Thing::ts_fall_end_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end--);
}

ts_t Thing::ts_fall_end_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end++);
}

////////////////////////////////////////////////////////////////////////////
// fall_height
////////////////////////////////////////////////////////////////////////////
float Thing::fall_height_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->fall_height);
  }
  return 0;
}

void Thing::fall_height_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->fall_height = v;
}
