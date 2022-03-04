//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

void Thing::on_move(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    //
    // Update reachability for the player
    //
    level->request_dmap_to_player_update = true;
  }

  auto on_move = tp()->on_move_do();
  if (std::empty(on_move)) {
    return;
  }

  auto t = split_tokens(on_move, '.');
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

    dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (int) curr_at.x,
        (int) curr_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_move call [%s] expected mod:function, got %d elems", on_move.c_str(), (int) on_move.size());
  }
}

void Thing::move_finish(void)
{
  TRACE_NO_INDENT();
  if (! is_moving) {
    return;
  }
  is_moving = false;

  //
  // Set this so that we can pick up items again at the last location.
  //
  where_i_dropped_an_item_last_set(point(-1, -1));

  if (is_player()) {
    dbg("Check if anything to carry");
    if (check_anything_to_carry(true)) {
      BOTCON("Press %%fg=yellow$%s%%fg=reset$ or click to collect.",
             ::to_string(game->config.key_wait_or_collect).c_str());
      level->describe(curr_at);

      auto items = anything_to_carry();
      game->wid_collect_create(items);
    }
  }

  //
  // Make sure that things that declare they are finished moving really
  // are where they should be.
  //
  update_pos(curr_at, true);

  update_interpolated_position();

  move_carried_items();

  on_move();

  if (maybe_aip()) {
    IF_DEBUG1
    {
      std::string s = "";
      for (auto p1 : aip()->move_path) {
        s += " " + p1.to_string();
      }
      if (s.empty()) {
        dbg("End of move");
      } else {
        dbg("End of move, moves left:%s", s.c_str());
      }
    }

    if (! aip()->move_path.size() && (infop()->monst_state == MONST_STATE_MOVING)) {
      change_state(MONST_STATE_IDLE, "move finished");
    }
  }

  //
  // Something moved
  //
  if (curr_at != last_at) {
    level->noisemap_in_incr(curr_at.x, curr_at.y, noise_total());
    level->is_map_changed_set(curr_at.x, curr_at.y);
  }
}

bool Thing::move(point future_pos)
{
  TRACE_NO_INDENT();
  if (! is_hidden) {
    dbg("Move to %d,%d", future_pos.x, future_pos.y);
  }

  bool up              = future_pos.y < curr_at.y;
  bool down            = future_pos.y > curr_at.y;
  bool left            = future_pos.x < curr_at.x;
  bool right           = future_pos.x > curr_at.x;
  bool attack          = false;
  bool wait_or_collect = false;
  bool shove_allowed   = true;
  bool attack_allowed  = true;

  verify(MTYPE_THING, this);
  return (move(future_pos, up, down, left, right, attack, wait_or_collect, shove_allowed, attack_allowed));
}

bool Thing::move_no_shove_no_attack(point future_pos)
{
  TRACE_NO_INDENT();
  dbg("Move, no shove, no attack to %s", future_pos.to_string().c_str());
  bool up              = future_pos.y < curr_at.y;
  bool down            = future_pos.y > curr_at.y;
  bool left            = future_pos.x < curr_at.x;
  bool right           = future_pos.x > curr_at.x;
  bool attack          = false;
  bool wait_or_collect = false;
  bool shove_allowed   = false;
  bool attack_allowed  = false;

  verify(MTYPE_THING, this);
  return (move(future_pos, up, down, left, right, attack, wait_or_collect, shove_allowed, attack_allowed));
}

bool Thing::move_no_shove_attack_allowed(point future_pos)
{
  TRACE_NO_INDENT();
  dbg("Move, no shove, attack allowed to %s", future_pos.to_string().c_str());
  bool up              = future_pos.y < curr_at.y;
  bool down            = future_pos.y > curr_at.y;
  bool left            = future_pos.x < curr_at.x;
  bool right           = future_pos.x > curr_at.x;
  bool attack          = false;
  bool wait_or_collect = false;
  bool shove_allowed   = false;
  bool attack_allowed  = true;

  verify(MTYPE_THING, this);
  return (move(future_pos, up, down, left, right, attack, wait_or_collect, shove_allowed, attack_allowed));
}

bool Thing::move(point future_pos, uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t must_attack,
                 uint8_t wait_or_collect, bool shove_allowed, bool attack_allowed)
{
  TRACE_NO_INDENT();
  dbg("Move");

  if (! is_moveable()) {
    dbg("Cannot move");
    return false;
  }
  if (is_dead) {
    dbg("Cannot move; dead");
    return false;
  }
  if (is_hidden) {
    dbg("Move; no, is hidden");
    return false;
  }
  if (is_changing_level) {
    dbg("Move; no waiting on level change");
    return false;
  }
  if (is_falling) {
    dbg("Move; no, is falling");
    return false;
  }
  if (is_jumping) {
    dbg("Move; no, is jumping");
    return false;
  }

  //
  // Don't let minions wander too far from their mob.
  //
  auto ai  = maybe_aip();
  auto mob = top_mob();
  if (mob) {
    if (distance_mob_max_float()) {
      auto new_distance  = distance(future_pos, mob->curr_at);
      auto curr_distance = distance(curr_at, mob->curr_at);
      if (new_distance <= curr_distance) {
        //
        // Always allow moves that end up closer to the base
        //
      } else if (new_distance > distance_mob_max_float() + 1) {
        //
        // Too far.
        //
        if (level->is_monst_or_player(future_pos)) {
          //
          // Allow attacking at the edges of movement
          //
        } else {
          dbg("Minion cannot move to %d,%d (new-dist %f, curr-dist %f); it tugs at the leash at %d,%d", future_pos.x,
              future_pos.y, new_distance, curr_distance, mob->curr_at.x, mob->curr_at.y);
          //
          // Don't make spiders (minions to webs) lunge
          //
          if (is_minion()) {
            lunge(future_pos);
          }

          //
          // Choose a new target
          //
          if (ai) {
            ai->wander_dest = point(0, 0);
          }
          return false;
        }
      }
    }
  }

  //
  // Check for being stuck in webs or something else sticky
  //
  if (up || down || left || right) {
    //
    // Too tired to move?
    //
    if (is_able_to_tire()) {
      if (stamina_get() < 5) {
        if (is_player()) {
          if (d20roll_under(stat_con_total())) {
            msg("You are so tired but dig deep into your reserves to move!");
          } else {
            msg("You cannot move, you are so tired!");
            stuck();
            game->tick_begin("too tired to move");
            return false;
          }
        }
      }
    }

    //
    // Blocked from moving by something stronger?
    //
    FOR_ALL_THINGS(level, it, curr_at.x, curr_at.y)
    {
      if (it == this) {
        continue;
      }
      if (! it->is_alive_monst()) {
        continue;
      }

      if (same_mob(it) || same_leader(it)) {
        dbg("Friends are piling up, but allow movement");
        wobble(25);
        continue;
      }

      if (! d20roll(stat_str(), it->stat_str_total())) {
        if (is_player()) {
          msg("You are held in place and cannot move!");
        }
        dbg("You are held in place");
        stuck();
        wobble(25);
        return false;
      }
    }
    FOR_ALL_THINGS_END()

    if (is_immune_to_spiderwebs() && level->is_spiderweb(curr_at.x, curr_at.y)) {
      //
      // No getting stuck in webs
      // Also no cleaners stuck in their own gel
      //
    } else if (is_toughness_soft() && level->is_heavy(curr_at.x, curr_at.y)) {
      //
      // Makes sure ghosts (or the cursor!) do not get stuck under barrels
      //
      if (! is_ethereal() && ! is_cursor() && ! is_cursor_path()) {
        if (is_player()) {
          if (level->is_barrel(curr_at.x, curr_at.y)) {
            msg("You are trapped under a barrel!");
            game->tick_begin("trapped in a barrel");
          } else {
            msg("You cannot move!");
            game->tick_begin("trapped in a barrel");
          }
          popup(string_sprintf("%%fg=red$!"));
        }
        lunge(future_pos);

        //
        // Shake the web
        //
        FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
        {
          if (t->is_barrel()) {
            t->wobble(10);
          }
          if (t->is_player() || t->is_monst()) {
            t->wobble(20);
          }
        }
        FOR_ALL_THINGS_END()

        stuck();
        return false;
      }
    } else if (is_stuck()) {
      if (is_player()) {
        if (level->is_spiderweb(curr_at.x, curr_at.y)) {
          msg("You are trapped in a web!");
          game->tick_begin("trapped in a web");
        } else {
          msg("You cannot move!");
          game->tick_begin("trapped in something sticky");
        }
        popup(string_sprintf("%%fg=red$!"));
      }
      lunge(future_pos);

      //
      // Shake the web
      //
      FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
      {
        if (t->is_spiderweb()) {
          t->wobble(10);
        }
        if (t->is_player() || t->is_monst()) {
          t->wobble(20);
        }
      }
      FOR_ALL_THINGS_END()

      stuck();
      return false;
    }
  }

  stuck_count_set(0);

  //
  // No rest for the undead.
  //
  if (is_monst() || is_player()) {
    if (! must_attack) {
      if (! is_undead() && ! is_ethereal()) {
        if (up || down || left || right) {
          if (d20() > stat_con()) {
            if (pcg_random_range(0, 100) < 10) {
              if (is_able_to_tire()) {
                stamina_decr();
              }
            }
          }
        } else {
          resting();
        }
      }
    }
  }

  //
  // Set this so that we can pick up items again at the last location.
  //
  where_i_dropped_an_item_last_set(point(-1, -1));

  if (is_player() && wait_or_collect) {
    game->tick_begin("player idled");

    if (! game->robot_mode) {
      dbg("Check if there is anything to carry here");
      auto items = anything_to_carry();
      if (! items.empty()) {
        //
        // In mouse mode, it really is better to open a window to allow
        // choosing
        //
#if 0
        if (items.size() > 1) {
          game->wid_collect_create(items);
        } else {
          try_to_carry(items);
        }
#else
        game->wid_collect_create(items);
#endif
      }
      msg("You wait...");
      waiting();
    } else {
      msg("You rest...");
      resting();
    }
    return false;
  }

  //
  // Do this after wait checks, so the player can bump the tick if stuck.
  //
  if (is_waiting_to_ascend_dungeon) {
    dbg("Move; no, is waiting to ascend dungeon");
    if (is_player()) {
      game->tick_begin("player waiting to ascend");
    }
    return false;
  }
  if (is_waiting_to_descend_sewer) {
    dbg("Move; no, is waiting to descend sewer");
    if (is_player()) {
      game->tick_begin("player waiting to descend");
    }
    return false;
  }
  if (is_waiting_to_descend_dungeon) {
    dbg("Move; no, is waiting to descend dungeon");
    if (is_player()) {
      game->tick_begin("player waiting to descend");
    }
    return false;
  }
  if (is_waiting_to_ascend_sewer) {
    dbg("Move; no, is waiting to ascend sewer");
    if (is_player()) {
      game->tick_begin("player waiting to ascend");
    }
    return false;
  }

  auto x     = future_pos.x;
  auto y     = future_pos.y;
  auto delta = point(x, y) - curr_at;

  move_set_dir_from_dest_or_delta(delta);

  //
  // Bounce rings and weapons
  //
  if (gfx_bounce_on_move()) {
    if (bounce_curr() == 0) {
      bounce(0.2 /* height */, 0.1 /* fade */, 200, 3);
    }
  }

  if (must_attack) {
    dbg("Must attack at %s", future_pos.to_string().c_str());
    TRACE_AND_INDENT();

    if (equip_use(must_attack, MONST_EQUIP_WEAPON, &future_pos)) {
      if (is_player()) {
        game->tick_begin("player attacked");
      }
    }
    return false;
  }

  if ((x == curr_at.x) && (y == curr_at.y)) {
    return false;
  }

  if (curr_at != future_pos) {
    //
    // Trail of blood?
    //
    place_blood();

    if (up) {
      dbg("Try to move up; collision check");
    } else if (down) {
      dbg("Try to move down; collision check");
    } else if (left) {
      dbg("Try to move left; collision check");
    } else if (right) {
      dbg("Try to move right; collision check");
    } else if (must_attack) {
      dbg("Try to move (attack); collision check");
    }

    if (collision_check_only(future_pos)) {
      dbg("Collided with something");

      if (shove_allowed) {
        dbg("Try to shove");
        if (is_player()) {
          game->tick_begin("player tried to shove");
        }
        try_to_shove(future_pos);
      } else if (attack_allowed) {
        dbg("Try to attack at %s", future_pos.to_string().c_str());
        TRACE_AND_INDENT();

        if (equip_use(must_attack, MONST_EQUIP_WEAPON, &future_pos)) {
          if (is_player()) {
            game->tick_begin("player tried to attack");
          }
          clear_move_path("Attacked");
          return true;
        }
      }
      dbg("Move failed");
      lunge(future_pos);
      clear_move_path("Move failed");
      return false;
    }

    if (is_player()) {
      game->tick_begin("player moved");
    }
  }

  if (is_player()) {
    where_i_failed_to_collect_last_set(point(-1, -1));

    if (! level->is_map_follow_player) {
      level->is_map_follow_player = true;
    }
  }

  //
  // If we allow the player here to get a free attack, then it looks nuts
  // as we end up attacking without actually attacking
  //
  auto t = most_dangerous_adjacent_thing();
  if (is_monst() && t && ! t->is_player()) {
    auto free_attack = (((t->curr_at.x >= curr_at.x) && left) || ((t->curr_at.x <= curr_at.x) && right) ||
                        ((t->curr_at.y >= curr_at.y) && up) || ((t->curr_at.y <= curr_at.y) && down));

    if (free_attack) {
      TRACE_NO_INDENT();
      dbg("Free attack by %s", t->to_string().c_str());
      if (t->attack(this)) {
        //
        // Too noisy?
        //
        if (is_player()) {
          std::string s = t->text_The() + " free attacks as you move";
          msg("%s.", s.c_str());
        }
      }

      //
      // Even if it misses, it counts
      //
      t->update_tick();
    }
  }

  if (tp()->gfx_animated_can_hflip()) {
    switch (dir) {
      case THING_DIR_NONE:
      case THING_DIR_DOWN:
      case THING_DIR_UP: break;

      case THING_DIR_LEFT:
      case THING_DIR_TL:
      case THING_DIR_BL:
        if (! is_facing_left && ! ts_flip_start_get()) {
          ts_flip_start_set(time_get_time_ms_cached());
        }
        break;

      case THING_DIR_RIGHT:
      case THING_DIR_TR:
      case THING_DIR_BR:
        if (is_facing_left && ! ts_flip_start_get()) {
          ts_flip_start_set(time_get_time_ms_cached());
        }
        break;
    }
  }

  if (up || down || left || right) {
    move_delta(delta);
  }

  return true;
}

void Thing::update_interpolated_position(void)
{
  TRACE_NO_INDENT();
  fpoint new_pos = make_fpoint(curr_at);
  auto   tpp     = tp();
  float  step    = game->tick_dt;

  //
  // Handle fast moving things
  //
  if (level->player) {
    if (move_speed()) {
      step *= ((float) move_speed()) / level->player->move_speed();
      if (step > 1) {
        step = 1;
      }
    }
  }

  auto p = top_owner();
  if ((p && p->is_falling) || is_falling) {
    if (z_depth == MAP_DEPTH_LAVA) {
      //
      // If we change the depth, it is displayed as white
      //
    } else if (z_depth == MAP_DEPTH_WATER) {
      //
      // If we change the depth, it is displayed as white
      //
    } else {
      //
      // Stops monsts falling over the floor tiles
      //
      z_depth = MAP_DEPTH_FLOOR;
    }
  } else {
    z_depth = tpp->z_depth;
  }

  if (is_jumping) {
    float dx = curr_at.x - last_at.x;
    float dy = curr_at.y - last_at.y;

    new_pos.x = last_at.x + dx * step;
    new_pos.y = last_at.y + dy * step;
  } else if (! is_moving) {
    if (curr_at != last_at) {
      if (! is_hidden) {
        dbg("Changed position (new %d,%d, old %d,%d)", curr_at.x, curr_at.y, last_at.x, last_at.y);
      }

      new_pos = make_fpoint(curr_at);
      last_at = curr_at;
    }
  } else if (game->tick_dt >= 1) {
    if (curr_at != last_at) {
      if (! is_hidden) {
        dbg("End of move position (new %d,%d, old %d,%d)", curr_at.x, curr_at.y, last_at.x, last_at.y);
      }

      new_pos = make_fpoint(curr_at);
      last_at = curr_at;

      move_finish();
    }
  } else {
    float dx = curr_at.x - last_at.x;
    float dy = curr_at.y - last_at.y;

    new_pos.x = last_at.x + dx * step;
    new_pos.y = last_at.y + dy * step;
  }

  //
  // Try not to push/pop as it breaks the unsafe walker
  //
  if (curr_at != make_point(new_pos)) {
    level_pop();
    interpolated_at_set(new_pos);
    level_push();
  } else {
    interpolated_at_set(new_pos);
  }

  //
  // For now only the player has a calculated light
  //
  update_light();
}

void Thing::update_pos(point to, bool immediately)
{
  if (! is_hidden) {
    dbg("Update pos to %d,%d", to.x, to.y);
  }
  TRACE_AND_INDENT();

  point new_at((int) to.x, (int) to.y);
  if (level->is_oob(new_at)) {
    return;
  }

  point old_at((int) curr_at.x, (int) curr_at.y);

  last_at        = curr_at;
  has_ever_moved = true;

  //
  // If moving things on the non game level, move non smoothly
  //
  if (level != game->level) {
    immediately = true;
  }

  //
  // Keep track of where this thing is on the grid
  //
  if (old_at == new_at) {
    return;
  }

  if (! is_hidden) {
    dbg("Move to %d,%d", to.x, to.y);
  }

  if (is_player()) {
    if (((int) old_at.x != (int) new_at.x) || ((int) old_at.y != (int) new_at.y)) {
      level->is_map_mini_valid = false;
    }
  }

  //
  // Try not to push/pop as it breaks the unsafe walker
  //
  if (curr_at != to) {
    level_pop();
    curr_at = to;
    level_push();
  }

  if (! immediately) {
    is_moving = true;
  }

  move_carried_items();
}

void Thing::move_to(point to)
{
  TRACE_NO_INDENT();
  move_finish();
  auto delta = to - curr_at;
  move_set_dir_from_dest_or_delta(delta);

  update_pos(to, false);
}

void Thing::move_delta(point delta)
{
  TRACE_NO_INDENT();
  move_finish();
  move_set_dir_from_dest_or_delta(delta);

  //
  // If the move finish ended up doing something like moving into
  // a sewer, then we need to abort the delta move
  //
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_jumping) {
    return;
  }

  update_pos(curr_at + delta, false);
}

void Thing::move_to_immediately(point to)
{
  TRACE_NO_INDENT();
  move_finish();
  auto delta = to - curr_at;
  move_set_dir_from_dest_or_delta(delta);

  //
  // Don't check for descending here as that check will be set when falling
  //

  update_pos(to, true);
  move_finish();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_jumping) {
    //
    // Things like changing level, don't look at the location until
    // the interpolated position is updated else we can look at the
    // old level coords on the new level and collide with the wrong
    // things
    //
  } else {
    location_check_forced();
  }

  if (is_player()) {
    if (! level->is_map_follow_player) {
      level->is_map_follow_player = true;
    }
  }

  update_interpolated_position();

  //
  // If this move was initiated by a jump make sure and clear the move path
  // so we don't try to continua an AI move
  //
  if (maybe_aip()) {
    aip()->move_path.clear();
  }
}

bool Thing::move_to_try(const point nh, const bool escaping, bool check_only)
{
  if (escaping) {
    dbg("Escape to attempt %d,%d", nh.x, nh.y);
  } else {
    dbg("Move to attempt %d,%d", nh.x, nh.y);
  }
  TRACE_AND_INDENT();

  //
  // Check to see if moving to this new location will hit something
  //
  // We need to look at the next-hop at the current time which may
  // be vacant, but also to the future if a thing is moving to that
  // spot; in which case we get an attack of opportunity.
  //
  if (collision_check_only(nh)) {
    //
    // We would hit something and cannot do this move. However,
    // see if we can hit the thing that is in the way.
    //
    dbg("Cannot move to %d,%d will hit obstacle or monst", nh.x, nh.y);
    TRACE_AND_INDENT();

    bool victim_attacked = false;
    bool victim_overlaps = false;
    collision_check_and_handle_nearby(nh, &victim_attacked, &victim_overlaps);
    if (victim_attacked) {
      dbg("Cannot move to %d,%d, must attack", nh.x, nh.y);
      return true;
    } else {
      dbg("Cannot move to %d,%d, obstacle", nh.x, nh.y);
      return false;
    }
  } else {
    dbg("Move to %d,%d is ok", nh.x, nh.y);

    if (! escaping) {
      if (terrain_cost_get(nh) >= DMAP_LESS_PREFERRED_TERRAIN) {
        TRACE_NO_INDENT();
        dbg("But %d,%d is less preferred terrain, avoid", nh.x, nh.y);
        return false;
      }
    }

    if (! check_only) {
      move(nh);
    }
    return true;
  }
}

bool Thing::move_to_or_attack(const point nh)
{
  dbg("Move to or attack");
  TRACE_AND_INDENT();
  return move_to_try(nh, false, false);
}

bool Thing::move_to_or_escape(const point nh)
{
  dbg("Move to or escape");
  TRACE_AND_INDENT();
  return move_to_try(nh, true, false);
}

bool Thing::move_to_or_attack_check_only(const point nh)
{
  dbg("Move to or attack");
  TRACE_AND_INDENT();
  return move_to_try(nh, false, true);
}

bool Thing::move_to_or_escape_check_only(const point nh)
{
  dbg("Move to or escape");
  TRACE_AND_INDENT();
  return move_to_try(nh, true, true);
}

void Thing::clear_move_path(const std::string &why)
{
  if (! maybe_aip()) {
    //
    // Fire can hit this path
    //
    return;
  }

  if (is_player()) {
    game->cursor_move_path.clear();
    if (level) {
      level->cursor_path_clear();
    }
  }

  change_state(MONST_STATE_IDLE, why);
  aip()->move_path.clear();
}
