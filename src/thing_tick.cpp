//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

//
// Python callback upon being tick
//
bool Thing::on_tick(void)
{
  auto on_tick = tp()->on_tick_do();
  if (std::empty(on_tick)) {
    return false;
  }

  auto t = split_tokens(on_tick, '.');
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

    auto owner = top_owner();
    dbg2("Call %s.%s(owner=%s, item=%s, %d, %d)", mod.c_str(), fn.c_str(),
         owner ? owner->to_short_string().c_str() : "<>", to_string().c_str(), (unsigned int) curr_at.x,
         (unsigned int) curr_at.y);
    return py_call_bool_fn(mod.c_str(), fn.c_str(), owner ? owner->id.id : 0, id.id, (unsigned int) curr_at.x,
                           (unsigned int) curr_at.y);
  }

  ERR("Bad on_tick call [%s] expected mod:function, got %d elems", on_tick.c_str(), (int) on_tick.size());
  return false;
}

void Thing::update_tick(void)
{
  tick_last_did_something_set(game->tick_current);
  tick_last_location_check_set(game->tick_current);
}

void Thing::achieve_goals_in_life(void)
{
  //
  // Reset verious temporary flags.
  //
  is_being_dropped = false;
  is_being_thrown  = false;

  TRACE_NO_INDENT();

  if (is_changing_level || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer
      || is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall
      || is_the_grid) {
    return;
  }

  //
  // To handle cases where water or lava spawns under you.
  //
  level_pop();
  level_push();

  //
  // Check torch counts
  //
  light_distance_update();

  //
  // Check if stuck in a web
  //
  is_stuck_update();

  //
  // Check if invisible
  //
  invisible_tick();

  //
  // Lifespan tick for carried torches must be before is_hidden check
  //
  lifespan_tick();
  if (is_dead) {
    return;
  }

  //
  // Regenerate health
  //
  health_regenerate();
  if (is_dead) {
    return;
  }

  //
  // Check stats don't get too low
  //
  stats_tick();
  if (is_dead) {
    return;
  }

  //
  // Periodic health checks
  //
  hunger_clock_tick();
  if (is_dead) {
    return;
  }

  hunger_update();
  if (is_dead) {
    return;
  }

  //
  // Timeout enemies
  //
  enemies_tick();
  if (is_dead) {
    return;
  }

  //
  // Timeout goals
  //
  goal_penalty_tick();
  if (is_dead) {
    return;
  }

  //
  // Timeout enemies to avoid
  //
  avoid_tick();
  if (is_dead) {
    return;
  }

  buff_tick();
  if (is_dead) {
    return;
  }

  debuff_tick();
  if (is_dead) {
    return;
  }

  //
  // Apply poison damage
  //
  poison_tick();
  if (is_dead) {
    return;
  }

  //
  // Apply necrosis damage
  //
  necrosis_tick();
  if (is_dead) {
    return;
  }

  //
  // Check for impacts
  //
  if (collision_check_do()) {
    return;
  }
  if (is_dead) {
    return;
  }

  //
  // Cool down / heat up
  //
  temperature_tick();

  //
  // This is to handle things that do not move, like a weapon that is on fire
  //
  location_check();
  if (is_dead) {
    return;
  }

  //
  // Roll the dice and see if we do anything
  //
  idle_check();
  if (is_dead) {
    return;
  }

  if (! is_player()) {
    if (! is_sleeping) {
      if (try_to_escape()) {
        dbg("Tried to escape");
        return;
      }

      if (shoot_at_target()) {
        dbg("Tried to fire");
        return;
      }

      if (is_able_to_jump()) {
        if (d1000() < tp()->chance_d1000_jump_randomly()) {
          dbg("Try to randomly jump");
          if (! collision_obstacle(level->player)) {
            if (try_to_jump_towards_player()) {
              return;
            }
          } else {
            if (try_to_jump()) {
              return;
            }
          }
        }
      }
    }
  }

  if (on_tick()) {
    dbg("Did something during tick callback");
    return;
  }

  if (on_tick_when_activated()) {
    dbg("Did something during activated tick callback");
    return;
  }

  if (on_tick_when_deactivated()) {
    dbg("Did something during deactivated tick callback");
    return;
  }

  //
  // If this thing has AI, it can try and reach goals
  //
  if (is_monst()) {
    // dbg("Tick %d get next hop", game->tick_current);
    ai_get_next_hop();
    if (is_moving) {
      return;
    }
  }

  //
  // If there is a next hop to go to, do it.
  //
  if (is_player()) {
    //
    // Pop the next player move at the end of the game tick
    //
    if (maybe_aip() && aip()->move_path.empty()) {
      //
      // If resting, keep resting
      //
      if (infop()->monst_state == MONST_STATE_MOVING) {
        change_state(MONST_STATE_IDLE, "move path is empty");
      }
    }
  } else if (is_monst()) {
    //
    // Pop the next monst move.
    //
    if (player_or_monst_path_pop_next_move(THING_MOVE_REASON_AI)) {
      dbg("Popped next move");
      return;
    }
  }
}

void Thing::achieve_goals_in_death(void)
{
  dbg("Achieve death goals at tick %u", game->tick_current);
  TRACE_AND_INDENT();

  resurrect_tick();
  update_tick();
}

//
// Returns true if we attacked something
//
bool Thing::collision_check_do(void)
{
  TRACE_NO_INDENT();

  if (! tp()->collision_check()) {
    return false;
  }

  ThingAttackOptions attack_options = {};
  attack_options.victim_attacked    = false;
  attack_options.victim_overlaps    = false;
  if (collision_check_and_handle_at(&attack_options)) {
    return attack_options.victim_attacked;
  }

  if (attack_options.victim_attacked || attack_options.victim_overlaps) {
    move_finish();
    clear_move_path("Collision");
  }
  return attack_options.victim_attacked;
}

void Thing::tick(void)
{
  // dbg("Tick %d", game->tick_current);
  TRACE_NO_INDENT();

  //
  // Save fields that may change during the tick
  //
  was_frozen = is_frozen;

  //
  // This is expensive to calculate when moving, but it should not change during the tick, so do it now.
  //
  auto infop = maybe_infop();
  if (infop) {
    move_speed_curr_set(move_speed_total());
  }

  //
  // Allow incremental movement
  //
  update_interpolated_position();

  if (unlikely(is_dead)) {
    //
    // Resurrect things unless that can do unless that has been disabled e.g. via minion mob death
    //
    if (! is_resurrection_blocked && is_able_to_be_resurrected()) {
      //
      // Tick on player move/change of the current tick
      //
      achieve_goals_in_death();
    }

    IF_DEBUG3 { dbg("Tick; is dead"); }
    return;
  }

  if (unlikely(is_dead)) {
    IF_DEBUG3 { dbg("Tick; died"); }
    return;
  }

  //
  // Tick on player move/change of the current tick
  //
  achieve_goals_in_life();
  if (is_dead) {
    return;
  }

  if (is_monst() || is_player()) {
    if (curr_at == last_at) {
      idle_count_incr();
    } else {
      idle_count_set(0);
    }
  }
}
