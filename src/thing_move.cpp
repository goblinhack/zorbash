//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

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

    dbg2("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (int) curr_at.x,
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

  if (is_player() && ! is_dead) {
    dbg2("Check if anything to carry");
    CarryOptions carry_options;
    carry_options.is_auto_collect_allowed = true;
    if (check_anything_to_carry(carry_options)) {
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

  if (is_internal()) {
    //
    // The cursor does not cause a reaction
    //
  } else {
    //
    // Perform check post movement
    //
    move_carried_items();

    on_move();

    if (maybe_aip()) {
      IF_DEBUG2
      {
        if (is_debug_type()) {
          std::string s = "";
          for (auto p1 : aip()->move_path) {
            s += " " + p1.to_string();
          }
          if (s.empty()) {
            dbg2("End of move");
          } else {
            dbg2("End of move, moves left:%s", s.c_str());
          }
        }
      }

      if (! aip()->move_path.size() && (infop()->monst_state == MONST_STATE_MOVING)) {
        change_state(MONST_STATE_IDLE, "move finished");
      }
    }

    //
    // Did we enter something like a portal? Don't check if already teleporting.
    //
    if (! is_teleporting) {
      //
      // Do not do this for carried items else it is a bit weird for items to teleport by themselves somewhere else.
      //
      if (! immediate_owner()) {
        FOR_ALL_NON_INTERNAL_THINGS(level, it, curr_at.x, curr_at.y)
        {
          if (it == this) {
            continue;
          }

          if (! it->on_enter_do().empty()) {
            it->on_enter(this);
          }
        }
        FOR_ALL_THINGS_END()
      }
    }
  }

  is_being_dropped = false;
  is_being_thrown  = false;
}

bool Thing::move(point future_pos)
{
  TRACE_NO_INDENT();
  if (! is_hidden) {
    dbg2("Move to %d,%d", future_pos.x, future_pos.y);
  }

  bool up              = future_pos.y < curr_at.y;
  bool down            = future_pos.y > curr_at.y;
  bool left            = future_pos.x < curr_at.x;
  bool right           = future_pos.x > curr_at.x;
  bool attack          = false;
  bool wait_or_collect = false;

  ThingAttackOptions attack_options {};
  attack_options.shove_allowed  = true;
  attack_options.attack_allowed = true;

  verify(MTYPE_THING, this);
  return (move(future_pos, up, down, left, right, attack, wait_or_collect, &attack_options));
}

bool Thing::move_no_shove_no_attack(point future_pos)
{
  TRACE_NO_INDENT();
  dbg2("Move, no shove, no attack to %s", future_pos.to_string().c_str());
  bool up              = future_pos.y < curr_at.y;
  bool down            = future_pos.y > curr_at.y;
  bool left            = future_pos.x < curr_at.x;
  bool right           = future_pos.x > curr_at.x;
  bool attack          = false;
  bool wait_or_collect = false;

  ThingAttackOptions attack_options {};
  attack_options.shove_allowed  = false;
  attack_options.attack_allowed = false;

  verify(MTYPE_THING, this);
  return (move(future_pos, up, down, left, right, attack, wait_or_collect, &attack_options));
}

bool Thing::move_no_shove_attack_allowed(point future_pos)
{
  TRACE_NO_INDENT();
  dbg2("Move, no shove, attack allowed to %s", future_pos.to_string().c_str());
  bool up              = future_pos.y < curr_at.y;
  bool down            = future_pos.y > curr_at.y;
  bool left            = future_pos.x < curr_at.x;
  bool right           = future_pos.x > curr_at.x;
  bool attack          = false;
  bool wait_or_collect = false;

  ThingAttackOptions attack_options {};
  attack_options.shove_allowed  = false;
  attack_options.attack_allowed = true;

  verify(MTYPE_THING, this);
  return (move(future_pos, up, down, left, right, attack, wait_or_collect, &attack_options));
}

bool Thing::move(point future_pos, uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t must_attack,
                 uint8_t wait_or_collect, ThingAttackOptionsp attack_options)
{
  TRACE_NO_INDENT();

  if (! is_moveable()) {
    if (is_able_to_lunge()) {
      //
      // Extra 0.5 is to allow diagonal attacks when vision is only 1; e.g. vampire rose.
      //
      if (distance(future_pos, curr_at) <= 1.5) {
        dbg2("Cannot move but can lunge attack");
      } else {
        dbg2("Cannot move; I am not moveable");
        return false;
      }
    } else {
      dbg2("Cannot move; I am not moveable");
      return false;
    }
  }
  if (is_dead) {
    dbg2("Cannot move; dead");
    return false;
  }
  if (is_hidden) {
    dbg2("Move; no, is hidden");
    return false;
  }
  if (is_changing_level) {
    dbg2("Move; no waiting on level change");
    return false;
  }
  if (is_falling) {
    dbg2("Move; no, is falling");
    return false;
  }
  if (is_jumping) {
    dbg2("Move; no, is jumping");
    return false;
  }

  //
  // We need to update the minimap even if they player just waits
  //
  if (is_player()) {
    game->set_request_to_update_same_level();
  }

  //
  // Don't let minions wander too far from their mob.
  //
  auto ai  = maybe_aip();
  auto mob = top_mob();
  if (mob) {
    if (distance_minion_from_mob_max_float()) {
      auto new_distance  = distance(future_pos, mob->curr_at);
      auto curr_distance = distance(curr_at, mob->curr_at);
      if (new_distance <= curr_distance) {
        //
        // Always allow moves that end up closer to the base
        //
      } else if (new_distance > distance_minion_from_mob_max_float() + 1) {
        //
        // Too far.
        //
        if (level->is_monst_or_player(future_pos)) {
          //
          // Allow attacking at the edges of movement
          //
        } else {
          dbg2("Minion cannot move to %d,%d (new-dist %f, curr-dist %f); it tugs at the leash at %d,%d", future_pos.x,
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
      if (stamina() < 5) {
        if (is_player()) {
          if (d20_le(stat_con_total())) {
            msg("You are so tired but dig deep into your reserves to move!");
          } else {
            msg("You cannot move, you are so tired!");
            game->tick_begin("too tired to move");
            return false;
          }
        }
      }
    }

    //
    // Monsters update this when they run AI. The player however we need to do it prior to
    // moving to avoid being able to escape pouncing monsters.
    //
    if (is_player()) {
      move_count_incr();
    }

    is_stuck_update();

    //
    // Able to move?
    //
    if (is_stuck_currently()) {
      if (is_player()) {
        game->tick_begin("could not move");
      }
      lunge(future_pos);
      return false;
    }
  }

  //
  // No rest for the undead.
  //
  if (is_monst() || is_player()) {
    if (! must_attack) {
      if (! is_lifeless() && ! is_undead() && ! is_ethereal()) {
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
      dbg2("Check if there is anything to carry here");
      auto items = anything_to_carry();
      if (! items.empty()) {
        //
        // In mouse mode, it really is better to open a window to allow choosing
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

      if (level->is_gas_poison(curr_at.x, curr_at.y)) {
        msg("You hang out in the gas.");
      } else if (level->is_trap(curr_at.x, curr_at.y)) {
        msg("You wait dangerously.");
      } else if (level->is_lava(curr_at.x, curr_at.y)) {
        msg("You wait in the heat.");
      } else {
        msg("You wait.");
      }

      waiting();
      move_count_incr();
    } else {
      if (level->is_gas_poison(curr_at.x, curr_at.y)) {
        msg("You rest in the poison gas cloud.");
      } else if (level->is_trap(curr_at.x, curr_at.y)) {
        msg("You rest dangerously.");
      } else if (level->is_lava(curr_at.x, curr_at.y)) {
        msg("You rest in the heat.");
      } else {
        msg("You rest.");
      }

      resting();
      move_count_incr();
    }
    return false;
  }

  //
  // Do this after wait checks, so the player can bump the tick if stuck.
  //
  if (is_waiting_to_ascend_dungeon) {
    dbg2("Move; no, is waiting to ascend dungeon");
    if (is_player()) {
      game->tick_begin("player waiting to ascend");
    }
    return false;
  }
  if (is_waiting_to_descend_sewer) {
    dbg2("Move; no, is waiting to descend sewer");
    if (is_player()) {
      game->tick_begin("player waiting to descend");
    }
    return false;
  }
  if (is_waiting_to_descend_dungeon) {
    dbg2("Move; no, is waiting to descend dungeon");
    if (is_player()) {
      game->tick_begin("player waiting to descend");
    }
    return false;
  }
  if (is_waiting_to_ascend_sewer) {
    dbg2("Move; no, is waiting to ascend sewer");
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
  if (gfx_pixelart_bounce_on_move()) {
    if (bounce_curr() == 0) {
      bounce(0.2 /* height */, 0.1 /* fade */, 200, 3);
    }
  }

  if (must_attack) {
    dbg2("Must attack at %s", future_pos.to_string().c_str());
    TRACE_AND_INDENT();

    equip_use(must_attack, MONST_EQUIP_WEAPON, attack_options);
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
    if (is_dead) {
      return false;
    }

    if (up) {
      dbg2("Try to move up; collision check");
    } else if (down) {
      dbg2("Try to move down; collision check");
    } else if (left) {
      dbg2("Try to move left; collision check");
    } else if (right) {
      dbg2("Try to move right; collision check");
    } else if (must_attack) {
      dbg2("Try to move (attack); collision check");
    }

    if (collision_check_only(future_pos)) {
      dbg2("Collided with something");
      TRACE_AND_INDENT();

      if (attack_options->shove_allowed) {
        dbg2("Try to shove");
        if (is_player()) {
          game->tick_begin("player tried to shove");
        }
        try_to_shove(future_pos);
      } else if (attack_options->attack_allowed) {
        dbg2("Try to attack at %s", future_pos.to_string().c_str());
        TRACE_AND_INDENT();

        //
        // If the cursor is where we are trying to attack, then set the
        // attack position; this allows us to hit walls intentionally.
        //
        if (level->cursor) {
          if (level->cursor->curr_at == future_pos) {
            attack_options->attack_at_set = true;
            attack_options->attack_at     = level->cursor->curr_at;
            dbg2("Try to attack at cursor location");
          }
        }

        if (equip_use(must_attack, MONST_EQUIP_WEAPON, attack_options)) {
          clear_move_path("Attacked");
          return true;
        }
      } else {
        dbg2("Cannot shove or attack");
      }
      dbg2("Move failed");
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
    auto free_attack = (((t->curr_at.x >= curr_at.x) && left) || ((t->curr_at.x <= curr_at.x) && right)
                        || ((t->curr_at.y >= curr_at.y) && up) || ((t->curr_at.y <= curr_at.y) && down));

    if (free_attack) {
      TRACE_NO_INDENT();
      dbg2("Free attack by %s", t->to_short_string().c_str());
      ThingAttackOptions attack_options {};
      if (t->attack(this, &attack_options)) {
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

  if (g_opt_ascii || ! is_visible_to_player) {
    //
    // No need to flip
    //
  } else {
    //
    // Flip the character
    //
    if (tp()->gfx_pixelart_animated_can_hflip()) {
      switch (dir) {
        case THING_DIR_NONE :
        case THING_DIR_DOWN :
        case THING_DIR_UP : break;

        case THING_DIR_LEFT :
        case THING_DIR_TL :
        case THING_DIR_BL :
          if (! is_facing_left && ! ts_flip_start_get()) {
            ts_flip_start_set(time_ms_cached());
          }
          break;

        case THING_DIR_RIGHT :
        case THING_DIR_TR :
        case THING_DIR_BR :
          if (is_facing_left && ! ts_flip_start_get()) {
            ts_flip_start_set(time_ms_cached());
          }
          break;
      }
    }
  }

  if (up || down || left || right) {
    //
    // This check is for things that can lunge attack but cannot move; like vampire roses.
    //
    if (is_moveable()) {
      move_delta(delta);
    }
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
    auto player_speed = level->player->move_speed_curr();

    int  speed = 0;
    auto infop = maybe_infop();
    if (infop) {
      speed = move_speed_curr();
    }

    if (speed) {
      step *= (((float) speed)) / player_speed;
      if (step > 1) {
        step = 1;
      }
    }
  }

  auto p = top_owner();
  if ((p && p->is_falling) || is_falling) {
    if (z_depth == MAP_DEPTH_LIQUID) {
      //
      // If we change the depth, it is displayed as white
      //
    } else if (z_depth == MAP_DEPTH_LIQUID) {
      //
      // If we change the depth, it is displayed as white
      //
    } else {
      //
      // Stops monsters falling over the floor tiles
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
  } else if (! is_moving || is_teleporting) {
    if (curr_at != last_at) {
      if (! is_hidden) {
        dbg2("Changed position (new %d,%d, old %d,%d)", curr_at.x, curr_at.y, last_at.x, last_at.y);
      }

      new_pos = make_fpoint(curr_at);
      last_at = curr_at;
    }
  } else if (game->tick_dt >= 1) {
    if (curr_at != last_at) {
      if (! is_hidden) {
        dbg2("End of move position (new %d,%d, old %d,%d)", curr_at.x, curr_at.y, last_at.x, last_at.y);
      }
      level->noisemap_in_incr(curr_at.x, curr_at.y, noise_total());

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
  TRACE_NO_INDENT();

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
    dbg2("Move to %d,%d", to.x, to.y);
  }

  if (is_player()) {
    if (((int) old_at.x != (int) new_at.x) || ((int) old_at.y != (int) new_at.y)) {
      level->is_map_mini_valid = false;
    }

    level->is_walked_set(new_at.x, new_at.y);
    level->is_walked_set(old_at.x, old_at.y);
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

  if (immediately) {
    move_finish();
  }
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
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer
      || is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_jumping) {
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

  // dbg("Move immediately to %s", to.to_string().c_str());

  //
  // Don't check for descending here as that check will be set when falling
  //

  update_pos(to, true);
  move_finish();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer
      || is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_jumping || is_teleporting) {
    //
    // Things like changing level, don't look at the location until
    // the interpolated position is updated else we can look at the
    // old level coords on the new level and collide with the wrong
    // things
    //
  } else {
    location_check_me();
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
    dbg2("Escape to attempt %d,%d", nh.x, nh.y);
  } else {
    dbg2("Move to attempt %d,%d", nh.x, nh.y);
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
    dbg2("Cannot move to %d,%d will hit obstacle or monst", nh.x, nh.y);
    TRACE_AND_INDENT();

    ThingAttackOptions attack_options {};
    attack_options.victim_attacked = false;
    attack_options.victim_overlaps = false;
    collision_check_and_handle_nearby(nh, &attack_options);
    if (attack_options.victim_attacked) {
      dbg2("Cannot move to %d,%d, must attack", nh.x, nh.y);
      return true;
    }
    dbg2("Cannot move to %d,%d, obstacle", nh.x, nh.y);
    return false;
  }
  dbg2("Move to %d,%d is ok", nh.x, nh.y);

  if (! escaping) {
    if (terrain_cost_get(nh) >= DMAP_LESS_PREFERRED_TERRAIN) {
      TRACE_NO_INDENT();
      dbg2("But %d,%d is less preferred terrain, avoid", nh.x, nh.y);
      return false;
    }
  }

  if (! check_only) {
    move(nh);
  }
  return true;
}

bool Thing::move_to_or_attack(const point nh)
{
  dbg2("Move to or attack");
  TRACE_AND_INDENT();
  return move_to_try(nh, false, false);
}

bool Thing::move_to_or_escape(const point nh)
{
  dbg2("Move to or escape");
  TRACE_AND_INDENT();
  return move_to_try(nh, true, false);
}

bool Thing::move_to_or_attack_check_only(const point nh)
{
  dbg2("Move to or attack");
  TRACE_AND_INDENT();
  return move_to_try(nh, false, true);
}

bool Thing::move_to_or_escape_check_only(const point nh)
{
  dbg2("Move to or escape");
  TRACE_AND_INDENT();
  return move_to_try(nh, true, true);
}

void Thing::clear_move_path(const std::string &why)
{
  dbg2("Clear move path: %s", why.c_str());
  TRACE_AND_INDENT();

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

  //
  // Ensure we try to wander elsewhere if we got here due to a failed jump.
  //
  aip()->wander_dest = point(0, 0);
}

////////////////////////////////////////////////////////////////////////////
// movement_remaining
////////////////////////////////////////////////////////////////////////////
int Thing::movement_remaining(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->movement_remaining);
  }
  return 0;
}

int Thing::movement_remaining_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining = v);
  return n;
}

int Thing::movement_remaining_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining -= v);
  return n;
}

int Thing::movement_remaining_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining += v);
  return n;
}

int Thing::movement_remaining_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining--);
  return n;
}

int Thing::movement_remaining_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining++);
  return n;
}

int Thing::is_moveable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_moveable());
}
