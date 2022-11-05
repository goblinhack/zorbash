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
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_vector_bounds_check.hpp"

#include <math.h>

//
// Python callback upon being jump
//
void Thing::on_jump(void)
{
  TRACE_NO_INDENT();
  auto on_jump = tp()->on_jump_do();
  if (std::empty(on_jump)) {
    return;
  }

  auto t = split_tokens(on_jump, '.');
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
    ERR("Bad on_jump call [%s] expected mod:function, got %d elems", on_jump.c_str(), (int) on_jump.size());
  }
}

bool Thing::try_to_jump(point to, bool be_careful, bool *too_far)
{
  TRACE_NO_INDENT();

  point original_destination = to;
  point original_start       = curr_at;

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  if (! maybe_aip()) {
    return false;
  }

  //
  // Trying to jump to the same location
  //
  if (to == curr_at) {
    if (is_player()) {
      //
      // This happens if the player clicks on the character.
      //
    } else {
      //
      // Not sure why a monster would do this.
      //
      return false;
    }
  }

  if (be_careful) {
    dbg("Try to jump carefully %d,%d", to.x, to.y);
  } else {
    dbg("Try to jump to %d,%d", to.x, to.y);
  }
  TRACE_AND_INDENT();

  //
  // Spider minions need to be leashed
  //
  bool jumping_home = false;
  if (too_far_from_mob(to)) {
    dbg("No, minion is too far off the leash to jump");
    TRACE_AND_INDENT();

    auto mob = top_mob();
    if (mob) {
      dbg("Try jumping home");
      TRACE_AND_INDENT();

      to           = mob->curr_at;
      jumping_home = true;
    } else {
      return false;
    }
  }

  if (too_far_from_leader(to)) {
    if (distance_from_leader() > too_far_from_leader(to)) {
      dbg("Jumping closer to the leader");
    } else {
      dbg("No, follower is too far from the leader to jump");
      TRACE_AND_INDENT();

      auto l = leader();
      if (l) {
        dbg("Try jumping closer to the leader");
        to           = l->curr_at;
        jumping_home = true;
      } else {
        return false;
      }
    }
  }

  if (is_able_to_tire()) {
    if (! stamina()) {
      if (is_player()) {
        msg("You are too tired to jump.");
      }
      dbg("Too tired to jump, stamina %d", stamina());
      return false;
    }
  }

  auto x = to.x;
  auto y = to.y;

  dbg("Try jump to %d,%d", x, y);
  TRACE_AND_INDENT();

  if (level->is_oob(x, y)) {
    TRACE_NO_INDENT();
    dbg("No, oob");
    if (is_player()) {
      msg("You can't jump into the void.");
    }
    return false;
  }

  //
  // If stuck in a web, cannot jump
  //
  if (! is_immune_to_spiderwebs()) {
    if (level->is_spiderweb(curr_at)) {
      msg("You try to jump but are stuck in a web.");
      wobble(25);
      return false;
    }
  }

  //
  // Ensure cleaners do not get stuck in themselves!
  //
  if (is_stuck_currently()) {
    //
    // Ok to move
    //
    if (is_player()) {
      if (is_frozen) {
        msg("You try to jump but are frozen to the bone.");
      } else {
        msg("You try to jump but are stuck fast.");
      }
    }
    wobble(25);
    dbg("You try to jump but are stuck fast.");
    return false;
  }

  //
  // If stuck in ice, cannot jump
  //
  if (level->is_block_of_ice(curr_at)) {
    dbg("Cannot jump, stuck in ice");
    return false;
  }

  //
  // If trapped in an engulfer, you can only attack locally
  //
  FOR_ALL_COLLISION_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t == this) {
      continue;
    }

    //
    // If stuck in an engulfer, cannot jump
    //
    if (t->is_engulfer()) {
      dbg("Cannot jump, stuck in an engulfer");
      return false;
    }
  }
  FOR_ALL_THINGS_END();

  //
  // See if we are prevented from jumping. i.e. from a spider sitting on us.
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
      dbg("Friends are piling up, but allow jumping");
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
  // Block jumping over walls.
  //
  auto obstacles = in_the_way_for_jumping(curr_at, to, 1);
  if (obstacles.size()) {
    if (is_player()) {
      //
      // Too noisy when the robot tries to jump.
      //
      if (! game->robot_mode) {
        auto t = obstacles[ 0 ];
        msg("You can't jump over %s!", t->text_the().c_str());
      }
    }
    dbg("You can't jump over that");
    return false;
  }

  //
  // Block jumping over doors into dark rooms.
  //
  if (is_player()) {
    if (map_treasure_count()) {
      //
      // If we have a treasure map, allow wandering
      //
    } else {
      if (! get(level->can_see_ever.can_see, x, y)) {
        IF_DEBUG2 { dbg("No, is not lit or visited"); }

        if (is_player()) {
          msg("You can't jump into the unlit regions.");
        }
        dbg("You can't jump into the unlit regions.");
        return false;
      }
    }
  }

  //
  // Add some random delta for fun and some for diagonals
  //
  float d    = jump_distance_current();
  float dist = distance(curr_at, to);

  //
  // Check if trying to jump too far.
  //
  if (dist > d) {
    //
    // Yep. Trying to jump too far.
    //
    fpoint u = (make_fpoint(to) - make_fpoint(curr_at));
    u.unit();
    u *= d;

    fpoint fto = make_fpoint(curr_at) + u;

    to = make_point(fto);
    x  = to.x;
    y  = to.y;

    if (be_careful) {
      if (is_player() && game->robot_mode) {
        dbg("Robot: Cannot jump as far as it would like");
      }
      if (too_far) {
        *too_far = true;
      }
      if (! jumping_home) {
        dbg("Too far");
        return false;
      }
    }
  }

  //
  // No sneaky jumping onto doors to get passed them. But we do need to allow jumping into secret doors.
  //
  if (level->is_obs_for_jump_landing(x, y)) {
    TRACE_AND_INDENT();
    dbg("No, jump failed, into obstacle");
    if (is_player()) {
      if (point(x, y) == original_destination) {
        msg("You can't jump into solid objects.");
      } else {
        msg("You can't jump there; something is in the way.");
      }
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

  auto  src = (last_blit_tl + last_blit_br) / (short) 2;
  auto  dx  = x - curr_at.x;
  auto  dy  = y - curr_at.y;
  auto  tw  = TILE_WIDTH;
  auto  th  = TILE_HEIGHT;
  auto  sz  = isize(last_blit_br.x - last_blit_tl.x, last_blit_br.y - last_blit_tl.y);
  point dest(src.x + dx * tw, src.y + dy * th);
  auto  duration = THING_JUMP_SPEED_MS;

  if (g_opt_ascii || ! is_visible_to_player) {
    //
    // Ascii mode, jump is immediate
    //
    duration = 0;
  } else {
    //
    // Check the number of things jumping is not slowing the game too much
    //
    if (game->tick_current_is_too_slow || game->prev_tick_was_too_slow) {
      duration /= 4;
    }

    if (is_player()) {
      //
      // So the player is visible above light
      //
      auto callback = std::bind(&Thing::visible, this);
      if (! is_being_destroyed) {
        level->new_external_particle(id, src, dest, sz, duration, tile_index_to_tile(tile_curr), false, callback);
      }
    } else {
      //
      // If offscreen, then jump quicker, so the we do not have to wait so long.
      //
      if (! get(level->can_see_currently.can_see, curr_at.x, curr_at.y) &&
          ! get(level->can_see_currently.can_see, to.x, to.y)) {
        duration = 0;
      }

      auto callback = std::bind(&Thing::visible, this);
      level->new_internal_particle(id, src, dest, sz, duration, tile_index_to_tile(tile_curr), false, callback);
    }

    is_jumping = true;
  }

  //
  // In ascii mode jumps look like immediate moves, so give more feedback but only for monsters.
  //
  if (! is_player() && level->player) {
    if (! get(level->player->aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
      auto old_distance = DISTANCE(curr_at.x, curr_at.y, level->player->curr_at.x, level->player->curr_at.y);
      auto new_distance = DISTANCE(to.x, to.y, level->player->curr_at.x, level->player->curr_at.y);
      if (old_distance > new_distance) {
        msg("%s jumps closer!", text_The().c_str());
      } else if (old_distance < new_distance) {
        msg("%s jumps away!", text_The().c_str());
      } else {
        msg("%s jumps!", text_The().c_str());
      }
    } else if (! get(level->player->aip()->can_see_currently.can_see, to.x, to.y)) {
      msg("%s lands!", text_The().c_str());
    }
  }

  //
  // Make sure the jump messages come before this.
  //
  move_to_immediately(point(x, y));

  //
  // Weapons follow also.
  //
  FOR_ALL_EQUIP(e)
  {
    if (equip_id_carry_anim(e).ok()) {
      auto id = equip_id_carry_anim(e);
      auto w  = level->thing_find(id);
      if (w) {
        w->move_to_immediately(curr_at);
        if (g_opt_ascii || ! is_visible_to_player) {
          //
          // Ascii mode, jump is immediate
          //
        } else {
          w->is_jumping = true;

          auto callback = std::bind(&Thing::visible, this);
          if (! is_being_destroyed) {
            if (is_player()) {
              level->new_external_particle(id, src, dest, sz, duration, tile_index_to_tile(w->tile_curr),
                                           (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()), callback);
            } else {
              level->new_internal_particle(id, src, dest, sz, duration, tile_index_to_tile(w->tile_curr),
                                           (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()), callback);
            }
          }
        }
      }
    }

    if (equip_id_use_anim(e).ok()) {
      auto id = equip_id_use_anim(e);
      auto w  = level->thing_find(equip_id_use_anim(e));
      if (w) {
        w->move_to_immediately(curr_at);
        if (g_opt_ascii || ! is_visible_to_player) {
          //
          // Ascii mode, jump is immediate
          //
        } else {
          w->is_jumping = true;

          //
          // No, the weapon is shown as carry anim
          //
          auto callback = std::bind(&Thing::visible, this);
          if (! is_being_destroyed) {
            if (is_player()) {
              level->new_external_particle(id, src, dest, sz, duration, tile_index_to_tile(w->tile_curr),
                                           (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()), callback);
            } else {
              level->new_internal_particle(id, src, dest, sz, duration, tile_index_to_tile(w->tile_curr),
                                           (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()), callback);
            }
          }
        }
      }
    }
  }

  auto on_fire_id = on_fire_anim_id();
  if (on_fire_id.ok()) {
    TRACE_NO_INDENT();
    auto id = on_fire_id;
    auto w  = level->thing_find(id);
    if (w) {
      w->move_to_immediately(curr_at);
      if (g_opt_ascii || ! is_visible_to_player) {
        //
        // Ascii mode, jump is immediate
        //
      } else {
        w->is_jumping = true;
      }
      if (! is_being_destroyed) {
        if (is_player()) {
          level->new_external_particle(id, src, dest, sz, duration, tile_index_to_tile(w->tile_curr),
                                       (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()));
        } else {
          level->new_internal_particle(id, src, dest, sz, duration, tile_index_to_tile(w->tile_curr),
                                       (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()));
        }
      }
    }
  }

  //
  // If something moves on the water, make a ripple
  //
  if (is_monst() || is_player()) {
    if (! is_floating() && ! is_flying()) {
      if (level->is_shallow_water((int) curr_at.x, (int) curr_at.y)) {
        point at(curr_at.x, curr_at.y);
        dbg("Causes ripples");
        TRACE_AND_INDENT();

        if (pcg_random_range(0, 1000) > 500) {
          if (thing_size() < (int) THING_SIZE_NORMAL) {
            level->thing_new(tp_random_small_ripple()->name(), at);
          } else {
            level->thing_new(tp_random_large_ripple()->name(), at);
          }
        }
      }
    }
  }

  wobble(25);

  if (! is_able_to_jump_without_tiring()) {
    if (d20() > stat_str()) {
      stamina_decr(10);
    }
  }

  //
  // It looks weird to allow multiple jumps
  //
  movement_remaining_set(0);

  on_jump();

  level->noisemap_in_incr(to.x, to.y, noise_on_jumping());

  dbg("Jump success to %d,%d.", curr_at.x, curr_at.y);

  if (is_player()) {
    move_count_incr();

    if (curr_at == original_start) {
      msg("You jump on the spot.");
    } else if (curr_at == original_destination) {
      msg("You jump.");
    } else {
      if (level->is_lava(curr_at)) {
        msg("You jump joyfully into the lava!");
      } else if (level->is_lava(curr_at)) {
        msg("You jump into the chasm!");
      } else if (level->is_hazard(curr_at)) {
        msg("You jump into the unexpected.");
      } else {
        msg("You jump, but not as far as you'd like.");
      }
    }
  }

  return true;
}

bool Thing::try_to_jump_carefully(point p, bool *too_far)
{
  TRACE_NO_INDENT();
  return try_to_jump(p, true, too_far);
}

bool Thing::try_to_jump_carefree(point p, bool *too_far)
{
  TRACE_NO_INDENT();
  return try_to_jump(p, false, too_far);
}

bool Thing::try_to_jump_carefully(point p)
{
  TRACE_NO_INDENT();
  return try_to_jump(p, true, nullptr);
}

bool Thing::try_to_jump_carefree(point p)
{
  TRACE_NO_INDENT();
  return try_to_jump(p, false, nullptr);
}

bool Thing::try_to_jump(void)
{
  TRACE_NO_INDENT();

  if (! is_able_to_jump_attack()) {
    return false;
  }

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  idle_count_set(0);

  float d      = jump_distance_current();
  int   ntries = 10 + (d * d);
  int   tries;

  tries = ntries;
  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);
    if (try_to_jump_carefully(point(x, y))) {
      return true;
    }
  }

  tries = ntries;
  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = curr_at.y;
    if (try_to_jump_carefully(point(x, y))) {
      return true;
    }
  }

  tries = ntries;
  while (tries-- > 0) {
    int x = curr_at.x;
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);
    if (try_to_jump_carefully(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::try_to_jump_towards_player(void)
{
  TRACE_NO_INDENT();

  if (! is_able_to_jump_attack()) {
    return false;
  }

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  idle_count_set(0);

  float d     = jump_distance_current();
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

    if (try_to_jump_carefully(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::try_to_jump_away_from_player(void)
{
  TRACE_NO_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  float d     = jump_distance_current();
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

    if (try_to_jump_carefree(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::try_harder_to_jump(void)
{
  TRACE_NO_INDENT();

  if (! is_able_to_jump_attack()) {
    return false;
  }

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  float d     = jump_distance_current();
  int   tries = 100;

  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - d, curr_at.x + d);
    int y = pcg_random_range(curr_at.y - d, curr_at.y + d);
    if (try_to_jump_carefree(point(x, y))) {
      return true;
    }
  }

  return false;
}

void Thing::jump_end(void)
{
  TRACE_NO_INDENT();
  if (! is_jumping) {
    return;
  }

  dbg("End of jump");
  TRACE_AND_INDENT();

  is_jumping = false;
  move_finish();

  update_interpolated_position();

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  move_carried_items();

  //
  // Weapons follow also.
  //
  FOR_ALL_EQUIP(e)
  {
    auto w = equip_get(e);
    if (w) {
      w->is_jumping = false;
    }

    if (equip_id_carry_anim(e).ok()) {
      auto w = level->thing_find(equip_id_carry_anim(e));
      if (w) {
        w->is_jumping = false;
      }
    }

    if (equip_id_use_anim(e).ok()) {
      auto w = level->thing_find(equip_id_use_anim(e));
      if (w) {
        w->is_jumping = false;
      }
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  for (const auto o : carried_item_only_vector()) {
    o->is_jumping = false;
  }

  auto on_fire_id = on_fire_anim_id();
  if (on_fire_id.ok()) {
    TRACE_NO_INDENT();
    auto w = level->thing_find(on_fire_id);
    if (w) {
      w->is_jumping = false;
    }
  }

  //
  // Attack of opportunity
  //
  if (is_player()) {
    auto t = most_dangerous_adjacent_thing();
    if (t) {
      std::string s = t->text_The() + " attacks as you land";
      game->tick_begin("monst attacked as player landed");
    }
  }
  wobble(25);

  //
  // We avoid creating particles for item moves when other particles
  // exist to avoid collection loops. This case is safe though, just
  // remove the jump particle
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

bool Thing::jump_attack(Thingp maybe_victim)
{
  if (! is_able_to_jump_attack()) {
    return false;
  }

  if (! maybe_aip()) {
    return false;
  }

  dbg("Jump attack maybe");
  TRACE_AND_INDENT();

  if (maybe_victim) {
    if (d1000() < tp()->is_able_to_jump_attack_chance_d1000()) {
      dbg("Try to jump in direction of escape attack");
      TRACE_AND_INDENT();

      auto delta = maybe_victim->curr_at - maybe_victim->last_at;
      if (delta != point(0, 0)) {
        auto dest = maybe_victim->curr_at + (delta * (short) 2);
        if (! try_to_jump_carefully(dest)) {
          auto dest = maybe_victim->curr_at + delta;
          return try_to_jump_carefully(dest);
        }
        return true;
      }
    }

    if (d1000() < tp()->is_able_to_jump_attack_chance_d1000()) {
      dbg("Try to jump in front attack");
      TRACE_AND_INDENT();

      auto delta = maybe_victim->curr_at - curr_at;
      auto dest  = curr_at + delta;
      return try_to_jump_carefully(dest);
    }
  }

  if (d1000() < tp()->is_able_to_jump_attack_chance_d1000()) {
    dbg("Try to jump attack");
    TRACE_AND_INDENT();

    auto p         = aip()->move_path;
    auto jump_dist = pcg_random_range(0, p.size());
    return try_to_jump_carefully(get(p, jump_dist));
  }

  point last_at; // Previous hop where we were.
  point curr_at; // Grid coordinates.

  if (maybe_victim && can_eat(maybe_victim)) {
    //
    // If the things is near death, pounce
    //
    if (maybe_victim->health() < maybe_victim->health_max() / 10) {
      {
        dbg("Try to jump onto weakly %s", maybe_victim->to_short_string().c_str());
        TRACE_AND_INDENT();

        if (try_to_jump_carefree(maybe_victim->curr_at)) {
          return true;
        }
      }

      if (d1000() < tp()->is_able_to_jump_onto_chance_d1000()) {
        dbg("Try to jump onto %s", maybe_victim->to_short_string().c_str());
        TRACE_AND_INDENT();

        if (try_to_jump_carefree(maybe_victim->curr_at)) {
          return true;
        }
      }
    }
  }

  return false;
}
