//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include <math.h>

float Thing::how_far_i_can_jump(void)
{
  TRACE_AND_INDENT();
  auto d = (float) ai_is_able_to_jump_distance() + ceil(0.5 + (pcg_random_range(0, 100) / 100.0));

  if (get_stamina() < get_stamina_max() / 2) {
    d /= 2;
  }

  if (get_stamina() < get_stamina_max() / 4) {
    d /= 2;
  }

  return d;
}

float Thing::how_far_i_can_jump_max(void)
{
  TRACE_AND_INDENT();
  auto d = (float) ai_is_able_to_jump_distance() + 1;
  return d;
}

bool Thing::try_to_jump(point to, bool be_careful, bool *too_far)
{
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  if (! maybe_aip()) {
    return false;
  }

  TRACE_AND_INDENT();
  if (be_careful) {
    dbg("Try to jump to %d,%d", to.x, to.y);
  } else {
    dbg("Try to jump carefully %d,%d", to.x, to.y);
  }

  if (is_able_to_tire()) {
    if (! get_stamina()) {
      if (is_player()) {
        TOPCON("You are too tired to jump. You need to rest.");
      }
      return false;
    }
  }

  auto x = to.x;
  auto y = to.y;

  if (is_player()) {
    dbg("Try jump to %d,%d", x, y);
  }

  if (level->is_oob(x, y)) {
    TRACE_AND_INDENT();
    dbg("No, oob");
    if (is_player()) {
      TOPCON("You can't jump into the void.");
    }
    return false;
  }

  //
  // Ensure cleaners do not get stuck in themselves!
  //
  if (! is_sticky() && level->is_sticky(mid_at.x, mid_at.y)) {
    if (is_player()) {
      TOPCON("You try to jump but are stuck fast.");
    }
    return false;
  }

  //
  // Block jumping over doors
  //
  if (is_player()) {
    if (! level->is_lit_ever(x, y)) {
      IF_DEBUG2 { log("No, is not lit or visited"); }

      if (is_player()) {
        TOPCON("You can't jump into the unknown.");
      }
      return false;
    }
  }

  //
  // Add some random delta for fun and some for diagonals
  //
  float d    = how_far_i_can_jump();
  float dist = distance(mid_at, to);

  if (dist > d) {
    auto u = (to - mid_at);
    u.unit();
    u *= d;
    to = mid_at + u;
    x  = to.x;
    y  = to.y;

    if (be_careful) {
      if (is_player() && game->robot_mode) {
        CON("Robot: Cannot jump as far as it would like");
      }
      if (too_far) {
        *too_far = true;
      }
      return false;
    }
  }

  //
  // Don't jump too short a distance.
  //
  if (is_monst()) {
    if (distance(mid_at, point(x, y)) < 2) {
      TRACE_AND_INDENT();
      dbg("No, too close");
      return false;
    }
  }

  //
  // No sneaky jumping onto doors to get passed them
  //
  if (level->is_obs_wall_or_door(x, y) || level->is_obs_destructable(x, y)) {
    TRACE_AND_INDENT();
    dbg("No, jump failed, into obstacle");
    if (is_player()) {
      TOPCON("You can't jump into solid objects.");
    }
    return false;
  }

  if (be_careful) {
    if (! level->is_able_to_stand_on(x, y)) {
      TRACE_AND_INDENT();
      return false;
    }

    if (collision_obstacle(point(x, y))) {
      TRACE_AND_INDENT();
      return false;
    }
  }

  auto src   = (last_blit_tl + last_blit_br) / 2;
  auto dx    = x - mid_at.x;
  auto dy    = y - mid_at.y;
  auto tw    = TILE_WIDTH;
  auto th    = TILE_HEIGHT;
  auto sz    = isize(last_blit_br.x - last_blit_tl.x, last_blit_br.y - last_blit_tl.y);
  auto delay = THING_JUMP_SPEED_MS;

  if (is_offscreen) {
    delay /= 2;
  }

  point dest(src.x + dx * tw, src.y + dy * th);

  if (is_player()) {
    //
    // So the player is visible above light
    //
    level->new_external_particle(id, src, dest, sz, delay, tile_index_to_tile(tile_curr), false,
                                 true /* make_visible_at_end */);
  } else {
    //
    // If offscreen and in robot mode, then jump quicker, so the robot does
    // not have to wait so long/
    //
    if (game->robot_mode) {
      if (! level->is_lit_currently(make_point(mid_at.x, mid_at.y)) &&
          ! level->is_lit_currently(make_point(to.x, to.y))) {
        delay = 0;
      }
    }

    level->new_internal_particle(id, src, dest, sz, delay, tile_index_to_tile(tile_curr), false,
                                 true /* make_visible_at_end */);
  }

  is_jumping = true;
  move_to_immediately(point(x, y));

  //
  // Weapons follow also.
  //
  FOR_ALL_EQUIP(e)
  {
    if (get_equip_id_carry_anim(e).ok()) {
      auto id = get_equip_id_carry_anim(e);
      auto w  = level->thing_find(id);
      if (w) {
        w->move_to_immediately(mid_at);
        w->is_jumping = true;
        if (is_player()) {
          level->new_external_particle(id, src, dest, sz, delay, tile_index_to_tile(w->tile_curr),
                                       (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()),
                                       true /* make_visible_at_end */);
        } else {
          level->new_internal_particle(id, src, dest, sz, delay, tile_index_to_tile(w->tile_curr),
                                       (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()),
                                       true /* make_visible_at_end */);
        }
      }
    }

    if (get_equip_id_use_anim(e).ok()) {
      auto id = get_equip_id_use_anim(e);
      auto w  = level->thing_find(get_equip_id_use_anim(e));
      if (w) {
        w->move_to_immediately(mid_at);
        w->is_jumping = true;
        //
        // No, the weapon is shown as carry anim
        //
        if (is_player()) {
          level->new_external_particle(id, src, dest, sz, delay, tile_index_to_tile(w->tile_curr),
                                       (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()),
                                       true /* make_visible_at_end */);
        } else {
          level->new_internal_particle(id, src, dest, sz, delay, tile_index_to_tile(w->tile_curr),
                                       (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()),
                                       true /* make_visible_at_end */);
        }
      }
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  for (const auto w : get_item_vector()) {
    w->move_to_immediately(mid_at);
    w->is_jumping = true;
  }

  auto on_fire_anim_id = get_on_fire_anim_id();
  if (on_fire_anim_id.ok()) {
    TRACE_AND_INDENT();
    auto id = on_fire_anim_id;
    auto w  = level->thing_find(id);
    if (w) {
      w->move_to_immediately(mid_at);
      w->is_jumping = true;
      if (is_player()) {
        level->new_external_particle(id, src, dest, sz, delay, tile_index_to_tile(w->tile_curr),
                                     (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()),
                                     false /* make_visible_at_end */);
      } else {
        level->new_internal_particle(id, src, dest, sz, delay, tile_index_to_tile(w->tile_curr),
                                     (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()),
                                     false /* make_visible_at_end */);
      }
    }
  }

  //
  // If something moves on the water, make a ripple
  //
  if (is_monst() || is_player()) {
    if (! is_floating()) {
      if (level->is_shallow_water((int) mid_at.x, (int) mid_at.y)) {
        point at(mid_at.x, mid_at.y);
        dbg("Causes ripples");
        if (game->robot_mode) {
          //
          // Faster
          //
          if (pcg_random_range(0, 1000) > 900) {
            level->thing_new(tp_random_ripple()->name(), at);
          }
        } else {
          if (pcg_random_range(0, 1000) > 500) {
            level->thing_new(tp_random_ripple()->name(), at);
          }
        }
      }
    }
  }

  wobble(25);

  decr_stamina(10);

  return true;
}

bool Thing::try_to_jump_carefully(point p, bool *too_far)
{
  TRACE_AND_INDENT();
  return try_to_jump(p, true, too_far);
}

bool Thing::try_to_jump_carefree(point p, bool *too_far)
{
  TRACE_AND_INDENT();
  return try_to_jump(p, false, too_far);
}

bool Thing::try_to_jump_carefully(point p)
{
  TRACE_AND_INDENT();
  return try_to_jump(p, true, nullptr);
}

bool Thing::try_to_jump_carefree(point p)
{
  TRACE_AND_INDENT();
  return try_to_jump(p, false, nullptr);
}

bool Thing::try_to_jump(void)
{
  TRACE_AND_INDENT();
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  set_idle_count(0);

  float d     = how_far_i_can_jump();
  int   tries = d * d;

  while (tries-- > 0) {
    int x = pcg_random_range(mid_at.x - d, mid_at.x + d);
    int y = pcg_random_range(mid_at.y - d, mid_at.y + d);
    if (try_to_jump_carefully(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::try_to_jump_towards_player(void)
{
  TRACE_AND_INDENT();
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  set_idle_count(0);

  float d     = how_far_i_can_jump();
  int   tries = d * d;

  auto player_at = level->player->mid_at;
  auto curr_dist = DISTANCE(mid_at.x, mid_at.y, player_at.x, player_at.y);

  while (tries-- > 0) {
    int x = pcg_random_range(mid_at.x - d, mid_at.x + d);
    int y = pcg_random_range(mid_at.y - d, mid_at.y + d);

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
  TRACE_AND_INDENT();
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  float d     = how_far_i_can_jump();
  int   tries = d * d;

  auto player_at = level->player->mid_at;
  auto curr_dist = DISTANCE(mid_at.x, mid_at.y, player_at.x, player_at.y);

  while (tries-- > 0) {
    int x = pcg_random_range(mid_at.x - d, mid_at.x + d);
    int y = pcg_random_range(mid_at.y - d, mid_at.y + d);

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
  TRACE_AND_INDENT();
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_jumping) {
    return false;
  }

  float d     = how_far_i_can_jump();
  int   tries = 100;

  while (tries-- > 0) {
    int x = pcg_random_range(mid_at.x - d, mid_at.x + d);
    int y = pcg_random_range(mid_at.y - d, mid_at.y + d);
    if (try_to_jump_carefree(point(x, y))) {
      return true;
    }
  }

  return false;
}

void Thing::jump_end(void)
{
  TRACE_AND_INDENT();
  if (! is_jumping) {
    return;
  }

  dbg("End of jump");
  is_jumping = false;
  move_finish();
  update_interpolated_position();

  //
  // Weapons follow also.
  //
  FOR_ALL_EQUIP(e)
  {
    if (get_equip_id_carry_anim(e).ok()) {
      auto w = level->thing_find(get_equip_id_carry_anim(e));
      if (w) {
        w->is_jumping = false;
      }
    }

    if (get_equip_id_use_anim(e).ok()) {
      auto w = level->thing_find(get_equip_id_use_anim(e));
      if (w) {
        w->is_jumping = false;
      }
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  for (const auto o : get_item_vector()) {
    o->is_jumping = false;
  }

  auto on_fire_anim_id = get_on_fire_anim_id();
  if (on_fire_anim_id.ok()) {
    TRACE_AND_INDENT();
    auto w = level->thing_find(on_fire_anim_id);
    if (w) {
      w->is_jumping = false;
    }
  }

  //
  // Attack of opportunity
  //
  if (is_player()) {
    auto t = get_most_dangerous_adjacent_thing();
    if (t) {
      std::string s = t->text_The() + " attacks as you land";
      game->tick_begin("monst attacked as player landed");
    }
  }
  wobble(25);

  move_carried_items();

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

  get_infop()->last_failed_jump_at = point(-1, -1);
}
