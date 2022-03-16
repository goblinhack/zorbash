//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"
#include <math.h>

//
// Python callback upon being teleport
//
void Thing::on_teleport(void)
{
  TRACE_NO_INDENT();
  auto on_teleport = tp()->on_teleport_do();
  if (std::empty(on_teleport)) {
    return;
  }

  auto t = split_tokens(on_teleport, '.');
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
    ERR("Bad on_teleport call [%s] expected mod:function, got %d elems", on_teleport.c_str(),
        (int) on_teleport.size());
  }
}

float Thing::how_far_i_can_teleport(void)
{
  TRACE_NO_INDENT();
  auto d = (float) distance_teleport() + ceil(0.5 + (pcg_random_range(0, 100) / 100.0));

  if (stamina_get() < stamina_max() / 2) {
    d /= 2;
  }

  if (stamina_get() < stamina_max() / 4) {
    d /= 2;
  }

  return d;
}

float Thing::how_far_i_can_teleport_max(void)
{
  TRACE_NO_INDENT();
  auto d = (float) distance_teleport();
  return d;
}

bool Thing::try_to_teleport(point to, bool be_careful, bool *too_far)
{
  TRACE_NO_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  if (! maybe_aip()) {
    return false;
  }

  //
  // Trying to teleport to the same location
  //
  if (to == curr_at) {
    return false;
  }

  if (be_careful) {
    dbg("Try to teleport carefully %d,%d", to.x, to.y);
  } else {
    dbg("Try to teleport to %d,%d", to.x, to.y);
  }
  TRACE_AND_INDENT();

  //
  // Spider minions need to be leashed
  //
  bool teleporting_home = false;
  if (too_far_from_mob(to)) {
    dbg("No, minion is too far off the leash to teleport");
    TRACE_AND_INDENT();

    auto mob = top_mob();
    if (mob) {
      dbg("Try teleporting home");
      TRACE_AND_INDENT();

      to               = mob->curr_at;
      teleporting_home = true;
    } else {
      return false;
    }
  }

  if (too_far_from_leader(to)) {
    if (distance_from_leader() > too_far_from_leader(to)) {
      dbg("Jumping closer to the leader");
    } else {
      dbg("No, follower is too far from the leader to teleport");
      TRACE_AND_INDENT();

      auto l = leader();
      if (l) {
        dbg("Try teleporting closer to the leader");
        to               = l->curr_at;
        teleporting_home = true;
      } else {
        return false;
      }
    }
  }

  if (is_able_to_tire()) {
    if (! stamina_get()) {
      if (is_player()) {
        msg("You are too tired to teleport.");
      }
      dbg("Too tired to teleport, stamina %d", stamina_get());
      return false;
    }
  }

  auto x = to.x;
  auto y = to.y;

  dbg("Try teleport to %d,%d", x, y);
  TRACE_AND_INDENT();

  if (level->is_oob(x, y)) {
    TRACE_NO_INDENT();
    dbg("No, oob");
    if (is_player()) {
      msg("You can't teleport into the void.");
    }
    return false;
  }

  //
  // Ensure cleaners do not get stuck in themselves!
  //
  if (is_stuck()) {
    //
    // Ok ot move
    //
    if (is_player()) {
      msg("You try to teleport but are stuck fast.");
    }
    wobble(25);
    dbg("You try to teleport but are stuck fast.");
    return false;
  }

  //
  // See if we are prevented from teleporting. i.e. from a spider sitting on us.
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
      dbg("Friends are piling up, but allow teleporting");
      wobble(25);
      continue;
    }

    if (! d20roll(stat_str(), it->stat_str_total())) {
      if (is_player()) {
        msg("You are held in place!");
      }
      dbg("You are held in place");
      wobble(25);
      return false;
    }
  }
  FOR_ALL_THINGS_END()

  //
  // Block teleporting over doors
  //
  if (is_player()) {
    if (map_treasure_count()) {
      //
      // If we have a treasure map, allow wandering
      //
    } else {
      if (! level->is_lit_ever(x, y)) {
        IF_DEBUG2 { dbg("No, is not lit or visited"); }

        if (is_player()) {
          msg("You can't teleport into the unlit regions.");
        }
        dbg("You can't teleport into the unlit regions.");
        return false;
      }
    }
  }

  //
  // Add some random delta for fun and some for diagonals
  //
  float d    = how_far_i_can_teleport();
  float dist = distance(curr_at, to);

  if (dist > d) {
    auto u = (to - curr_at);
    u.unit();
    u *= d;
    to = curr_at + u;
    x  = to.x;
    y  = to.y;

    if (be_careful) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Cannot teleport as far as it would like");
      }
      if (too_far) {
        *too_far = true;
      }
      if (! teleporting_home) {
        dbg("Too far");
        return false;
      }
    }
  }

  //
  // No sneaky teleporting onto doors to get passed them
  //
  if (level->is_obs_wall_or_door(x, y) || level->is_obs_destructable(x, y)) {
    TRACE_AND_INDENT();
    dbg("No, teleport failed, into obstacle");
    if (is_player()) {
      msg("You can't teleport into solid objects.");
    }
    return false;
  }

  if (be_careful) {
    if (! level->is_able_to_stand_on(x, y)) {
      TRACE_AND_INDENT();
      dbg("No, nothing to stand on at target");
      return false;
    }

    if (collision_obstacle(point(x, y))) {
      TRACE_AND_INDENT();
      dbg("No, collision obstacle at target");
      return false;
    }
  }

  point dest(x, y);

  level->thing_new("teleport", curr_at);
  level->thing_new("teleport", dest);

  move_to_immediately(dest);

  //
  // If something moves on the water, make a ripple
  //
  if (is_monst() || is_player()) {
    if (! is_floating() && ! is_flying()) {
      if (level->is_shallow_water((int) curr_at.x, (int) curr_at.y)) {
        dbg("Causes ripples");
        TRACE_AND_INDENT();
        if (game->robot_mode) {
          //
          // Faster
          //
          if (pcg_random_range(0, 1000) > 900) {
            level->thing_new(tp_random_ripple()->name(), curr_at);
          }
        } else {
          if (pcg_random_range(0, 1000) > 500) {
            level->thing_new(tp_random_ripple()->name(), curr_at);
          }
        }
      }
    }
  }

  wobble(25);

  if (! is_able_to_teleport_without_tiring()) {
    if (d20() > stat_str()) {
      stamina_decr(10);
    }
  }

  on_teleport();

  dbg("Jump success.");
  teleport_end();
  return true;
}

bool Thing::try_to_teleport_carefully(point p, bool *too_far)
{
  TRACE_NO_INDENT();
  return try_to_teleport(p, true, too_far);
}

bool Thing::try_to_teleport_carefree(point p, bool *too_far)
{
  TRACE_NO_INDENT();
  return try_to_teleport(p, false, too_far);
}

bool Thing::try_to_teleport_carefully(point p)
{
  TRACE_NO_INDENT();
  return try_to_teleport(p, true, nullptr);
}

bool Thing::try_to_teleport_carefree(point p)
{
  TRACE_NO_INDENT();
  return try_to_teleport(p, false, nullptr);
}

bool Thing::try_to_teleport(void)
{
  TRACE_NO_INDENT();
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  idle_count_set(0);

  float d     = how_far_i_can_teleport();
  int   tries = d * d;

  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);
    if (try_to_teleport_carefully(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::try_to_teleport_towards_player(void)
{
  TRACE_NO_INDENT();
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  idle_count_set(0);

  float d     = how_far_i_can_teleport();
  int   tries = d * d;

  auto player_at = level->player->curr_at;
  auto curr_dist = DISTANCE(curr_at.x, curr_at.y, player_at.x, player_at.y);

  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);

    auto new_dist = DISTANCE(x, y, player_at.x, player_at.y);
    if (new_dist > curr_dist) {
      continue;
    }

    //
    // Don't land on the player
    //
    if (new_dist < 1) {
      continue;
    }

    if (try_to_teleport_carefully(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::try_to_teleport_away_from_player(void)
{
  TRACE_NO_INDENT();
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  float d     = how_far_i_can_teleport();
  int   tries = d * d;

  auto player_at = level->player->curr_at;
  auto curr_dist = DISTANCE(curr_at.x, curr_at.y, player_at.x, player_at.y);

  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);

    auto new_dist = DISTANCE(x, y, player_at.x, player_at.y);
    if (new_dist < curr_dist) {
      continue;
    }

    if (try_to_teleport_carefree(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::try_harder_to_teleport(void)
{
  TRACE_NO_INDENT();
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  float d     = how_far_i_can_teleport();
  int   tries = 100;

  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);
    if (try_to_teleport_carefree(point(x, y))) {
      return true;
    }
  }

  return false;
}

void Thing::teleport_end(void)
{
  dbg("End of teleport");
  TRACE_AND_INDENT();

  move_finish();
  update_interpolated_position();

  //
  // Attack of opportunity
  //
  if (is_player()) {
    auto t = most_dangerous_adjacent_thing();
    if (t) {
      std::string s = t->text_The() + " attacks as you appear";
      game->tick_begin("monst attacked as player appeared");
    }
  }
  wobble(25);

  //
  // We avoid creating particles for item moves when other particles
  // exist to avoid collection loops. This case is safe though, just
  // remove the teleport particle
  //
  delete_particle();

  //
  // To allow landing on items and collecting in one go
  //
  collision_check_do();

  //
  // Need this so that if we land on a chasm we fall immediately
  //
  move_to_immediately(curr_at);
  is_moving = true;
  move_finish();
}

bool Thing::teleport_attack(Thingp maybe_victim)
{
  if (! is_able_to_teleport_attack()) {
    return false;
  }

  if (! maybe_aip()) {
    return false;
  }

  dbg("Teleport attack maybe");
  TRACE_AND_INDENT();

  if (maybe_victim) {
    if (d1000() < tp()->is_able_to_teleport_attack_chance_d1000()) {
      dbg("Try to teleport in direction of escape attack");
      TRACE_AND_INDENT();

      auto delta = maybe_victim->curr_at - maybe_victim->last_at;
      if (delta != point(0, 0)) {
        auto dest = maybe_victim->curr_at + (delta * 2);
        if (! try_to_teleport_carefully(dest)) {
          auto dest = maybe_victim->curr_at + delta;
          return try_to_teleport_carefully(dest);
        }
        return true;
      }
    }

    if (d1000() < tp()->is_able_to_teleport_attack_chance_d1000()) {
      dbg("Try to teleport in front attack");
      TRACE_AND_INDENT();

      auto delta = maybe_victim->curr_at - curr_at;
      auto dest  = curr_at + delta;
      return try_to_teleport_carefully(dest);
    }
  }

  if (d1000() < tp()->is_able_to_teleport_attack_chance_d1000()) {
    dbg("Try to teleport attack");
    TRACE_AND_INDENT();

    auto p             = aip()->move_path;
    auto teleport_dist = pcg_random_range(0, p.size());
    return try_to_teleport_carefully(get(p, teleport_dist));
  }

  point last_at; // Previous hop where we were.
  point curr_at; // Grid coordinates.

  if (maybe_victim && can_eat(maybe_victim)) {
    //
    // If the things is near death, pounce
    //
    if (maybe_victim->health() < maybe_victim->health_initial() / 10) {
      {
        dbg("Try to teleport onto weakly %s", maybe_victim->to_string().c_str());
        TRACE_AND_INDENT();

        if (try_to_teleport_carefree(maybe_victim->curr_at)) {
          return true;
        }
      }
    }
  }

  return false;
}
