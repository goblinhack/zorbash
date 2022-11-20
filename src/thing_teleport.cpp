//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
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

float Thing::teleport_distance_with_modifiers_get(void)
{
  TRACE_NO_INDENT();
  auto d = ((float) teleport_distance_get()) + ceil(0.5 + (pcg_random_range(0, 100) / 100.0));

  if (stamina() < stamina_max() / 2) {
    d /= 2;
  }

  if (stamina() < stamina_max() / 4) {
    d /= 2;
  }

  return d;
}

int Thing::teleport_distance_get(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return 0;
  }

  auto dist = teleport_distance();
  // con("TELEPORT %d", dist);

  FOR_ALL_EQUIP(e)
  {
    auto it = equip_get(e);
    if (it) {
      dist += it->teleport_distance_get();
      // it->con("TELEPORT %d", dist);
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto it = level->thing_find(id);
      if (it) {
        //
        // Don't count boots for example twice
        //
        if (is_equipped(it)) {
          continue;
        }
        dist += it->teleport_distance_get();
        // it->con("TELEPORT %d", dist);
      }
    }

    FOR_ALL_BUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        dist += it->teleport_distance_get();
        // it->con("TELEPORT %d", dist);
      }
    }

    FOR_ALL_DEBUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        dist += it->teleport_distance_get();
        // it->con("TELEPORT %d", dist);
      }
    }

    FOR_ALL_SKILLS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        dist += it->teleport_distance_get();
        // it->con("TELEPORT %d", dist);
      }
    }
  }

  return dist;
}

float Thing::teleport_distance_max_get(void)
{
  TRACE_NO_INDENT();
  auto d = ((float) teleport_distance_get());
  return d;
}

bool Thing::teleport(point to, bool be_careful, bool *too_far)
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
    if (! stamina()) {
      if (is_player()) {
        msg("You are too tired to teleport.");
      }
      dbg("Too tired to teleport, stamina %d", stamina());
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
  // Need to allow teleporting when stuck so there is a way out of barrels!
  //
  if (is_stuck_currently()) {
    dbg("You teleport out of trouble.");
    if (is_player()) {
      msg("You teleport out of your sticky situation!");
      game->tick_begin("teleport");
    }
    wobble(25);
  }

  //
  // See if we are prevented from teleporting. i.e. from a spider sitting on us.
  //
  FOR_ALL_NON_INTERNAL_THINGS(level, it, curr_at.x, curr_at.y)
  {
    if (it == this) {
      continue;
    }

    if (! it->is_alive_monst()) {
      continue;
    }

    if (same_mob(it) || same_leader_or_owner(it)) {
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
  // Add some random delta for fun and some for diagonals
  //
  float d    = teleport_distance_with_modifiers_get();
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
        dbg("Robot: Cannot teleport as far as it would like");
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

  level->thing_new("teleport_out", curr_at);
  level->thing_new("teleport_in", dest);

  dbg("Teleport to destination.");
  TRACE_AND_INDENT();

  is_teleporting = true;
  move_to_immediately(dest);

  //
  // If something moves on the water, make a ripple
  //
  if (is_monst() || is_player()) {
    if (! is_floating() && ! is_flying()) {

      //
      // Ripples at the source
      //
      if (level->is_water((int) curr_at.x, (int) curr_at.y)) {
        dbg("Causes ripples");
        TRACE_AND_INDENT();
        if (thing_size() < (int) THING_SIZE_NORMAL) {
          level->thing_new(tp_random_small_ripple()->name(), curr_at);
        } else {
          level->thing_new(tp_random_large_ripple()->name(), curr_at);
        }
      }

      //
      // And destination
      //
      if (level->is_water((int) dest.x, (int) dest.y)) {
        dbg("Causes ripples");
        TRACE_AND_INDENT();
        if (thing_size() < (int) THING_SIZE_NORMAL) {
          level->thing_new(tp_random_small_ripple()->name(), dest);
        } else {
          level->thing_new(tp_random_large_ripple()->name(), dest);
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

  if (is_player()) {
    msg("You fade out of existance!");
  }

  level->noisemap_in_incr(curr_at.x, curr_at.y, noise_on_teleporting());
  level->noisemap_in_incr(to.x, to.y, noise_on_teleporting());

  movement_remaining_set(0);

  dbg("Teleport success.");
  TRACE_AND_INDENT();

  teleport_end();
  return true;
}

bool Thing::teleport_carefully(point p, bool *too_far)
{
  TRACE_NO_INDENT();
  return teleport(p, true, too_far);
}

bool Thing::teleport_carefree(point p, bool *too_far)
{
  TRACE_NO_INDENT();
  return teleport(p, false, too_far);
}

bool Thing::teleport_carefully(point p)
{
  TRACE_NO_INDENT();
  return teleport(p, true, nullptr);
}

bool Thing::teleport_carefree(point p)
{
  TRACE_NO_INDENT();
  return teleport(p, false, nullptr);
}

bool Thing::teleport_randomly(void)
{
  TRACE_NO_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  idle_count_set(0);

  float d     = teleport_distance_with_modifiers_get();
  int   tries = d * d;

  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);
    if (teleport_carefully(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::teleport_randomly_towards_player(void)
{
  TRACE_NO_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  idle_count_set(0);

  float d     = teleport_distance_with_modifiers_get();
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

    if (teleport_carefully(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::teleport_randomly_away_from_player(void)
{
  TRACE_NO_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  float d     = teleport_distance_with_modifiers_get();
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

    if (teleport_carefree(point(x, y))) {
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

  float d     = teleport_distance_with_modifiers_get();
  int   tries = 100;

  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);
    if (teleport_carefree(point(x, y))) {
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

  if (is_player()) {
    msg("You fade back into existance!");
  }

  //
  // No sneaky teleporting onto doors to get passed them
  //
  if (level->is_obs_wall_or_door(curr_at.x, curr_at.y) || level->is_obs_destructable(curr_at.x, curr_at.y)) {
    TRACE_AND_INDENT();
    dead("teleported into a solid object");
  }

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
  is_teleporting = false;

  //
  // Reset after the teleporting
  //
  temperature_set(TEMPERATURE_ROOM);
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
        auto dest = maybe_victim->curr_at + (delta * (short) 2);
        if (! teleport_carefully(dest)) {
          auto dest = maybe_victim->curr_at + delta;
          return teleport_carefully(dest);
        }
        return true;
      }
    }

    if (d1000() < tp()->is_able_to_teleport_attack_chance_d1000()) {
      dbg("Try to teleport in front attack");
      TRACE_AND_INDENT();

      auto delta = maybe_victim->curr_at - curr_at;
      auto dest  = curr_at + delta;
      return teleport_carefully(dest);
    }
  }

  //
  // Only teleport if moving more that 1 tile
  //
  auto p = aip()->move_path;
  if (p.size() > 1) {
    if (d1000() < tp()->is_able_to_teleport_attack_chance_d1000()) {
      dbg("Try to teleport attack");
      TRACE_AND_INDENT();

      auto teleport_dist = pcg_random_range(1, p.size() - 1);
      return teleport_carefully(get(p, teleport_dist));
    }
  }

  point last_at; // Previous hop where we were.
  point curr_at; // Grid coordinates.

  if (maybe_victim && can_eat(maybe_victim)) {
    //
    // If the things is near death, pounce
    //
    if (maybe_victim->health() < maybe_victim->health_max() / 10) {
      {
        dbg("Try to teleport onto weakly %s", maybe_victim->to_short_string().c_str());
        TRACE_AND_INDENT();

        if (teleport_carefree(maybe_victim->curr_at)) {
          return true;
        }
      }
    }
  }

  return false;
}
