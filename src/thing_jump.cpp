//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <math.h>
#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_monst.h"
#include "my_array_bounds_check.h"

float Thing::how_far_i_can_jump (void)
{_
  auto d = (float) is_jumper_distance() +
        ceil(0.5 + (pcg_random_range(0, 100) / 100.0));

  if (get_stamina() < get_stamina_max() / 2) {
    d /= 2;
  }

  if (get_stamina() < get_stamina_max() / 4) {
    d /= 2;
  }

  return d;
}

bool Thing::try_to_jump (point to, bool be_careful)
{_
  if (is_changing_level ||
    is_hidden ||
    is_falling ||
    is_waiting_to_ascend_dungeon ||
    is_waiting_to_descend_sewer ||
    is_waiting_to_descend_dungeon ||
    is_waiting_to_ascend_sewer ||
    is_waiting_to_fall ||
    is_jumping) {
    return false;
  }

  if (is_stamina_check()) {
    if (!get_stamina()) {
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

  if (level->is_oob(x, y)) {_
    dbg("No, oob");
    if (is_player()) {
      TOPCON("You can't jump into the void.");
    }
    return false;
  }

  //
  // Ensure cleaners do not get stuck in themselves!
  //
  if (!is_sticky() && level->is_sticky(mid_at.x, mid_at.y)) {
    if (is_player()) {
      TOPCON("You try to jump but are stuck fast.");
    }
    return false;
  }

  //
  // Block jumping over doors
  //
  if (is_player()) {
    if (!level->is_lit_ever(x, y)) {
      IF_DEBUG2 {
        log("No, is not lit or visited");
      }

      if (is_player()) {
        TOPCON("You can't jump into the unknown.");
      }
      return false;
    }
  }

  auto fto = make_fpoint(to);

  //
  // Add some random delta for fun and some for diagonals
  //
  float d = how_far_i_can_jump();

  if (distance(mid_at, fto) > d) {
    auto u = (fto - mid_at);
    u.unit();
    u *= d;
    fto = mid_at + u;
    to = make_point(fto);
    x = to.x;
    y = to.y;

    if (be_careful) {
      if (is_player() && game->robot_mode) {
        CON("Robot: cannot jump as far as it would like");
      }
      return false;
    }
  }

  //
  // Don't jump too short a distance.
  //
  if (is_monst()) {
    if (distance(mid_at, fpoint(x, y)) < 2) {_
      dbg("No, too close");
      return false;
    }
  }

  //
  // No sneaky jumping onto doors to get passed them
  //
  if (level->is_obs_wall_or_door(x, y) ||
    level->is_obs_destructable(x, y)) {_
    dbg("No, jump failed, into obstacle");
    if (is_player()) {
      TOPCON("You can't jump into solid objects.");
    }
    return false;
  }

  if (be_careful) {
    if (!level->is_able_to_stand_on(x, y)) {_
      return false;
    }

    if (collision_obstacle(point(x, y))) {_
      return false;
    }
  }

  auto src = (last_blit_tl + last_blit_br) / 2;
  auto dx = x - mid_at.x;
  auto dy = y - mid_at.y;
  auto tw = TILE_WIDTH;
  auto th = TILE_HEIGHT;
  auto sz = isize(last_blit_br.x - last_blit_tl.x, last_blit_br.y - last_blit_tl.y);
  auto delay = THING_JUMP_SPEED;
  auto delay_shorter = delay - 10;
  point dst(src.x + dx * tw , src.y + dy * th );

  if (is_player()) {
    //
    // So the player is visible above light
    //
    level->new_external_particle(id, src, dst, sz, delay,
                   tile_index_to_tile(tile_curr),
                   false,
                   true /* make_visible_at_end */);
  } else {
    delay = MONST_JUMP_SPEED;

    //
    // If offscreen and in robot mode, then jump quicker, so the robot does
    // not have to wait so long/
    //
    if (game->robot_mode) {
      if (!level->is_lit_currently(make_point(mid_at.x, mid_at.y)) &&
        !level->is_lit_currently(make_point(to.x, to.y))) {
        delay = 0;
      }
    }

    level->new_internal_particle(id, src, dst, sz, delay,
                   tile_index_to_tile(tile_curr),
                   false,
                   true /* make_visible_at_end */);
  }

  is_jumping = true;
  move_to_immediately(fpoint(x, y));

  //
  // Weapons follow also.
  //
  if (get_weapon_id_carry_anim().ok()) {
    auto id = get_weapon_id_carry_anim();
    auto w = level->thing_find(id);
    if (w) {
      w->move_to_immediately(mid_at);
      w->is_jumping = true;
      if (is_player()) {
        level->new_external_particle(id, src, dst, sz, delay_shorter,
                       tile_index_to_tile(w->tile_curr),
                       (w->is_dir_br() || w->is_dir_right() ||
                        w->is_dir_tr()),
                       true /* make_visible_at_end */);
      } else {
        level->new_internal_particle(id, src, dst, sz, delay_shorter,
                       tile_index_to_tile(w->tile_curr),
                       (w->is_dir_br() || w->is_dir_right() ||
                        w->is_dir_tr()),
                       true /* make_visible_at_end */);
      }
    }
  }

  if (get_weapon_id_use_anim().ok()) {
    auto id = get_weapon_id_use_anim();
    auto w = level->thing_find(get_weapon_id_use_anim());
    if (w) {
      w->move_to_immediately(mid_at);
      w->is_jumping = true;
      //
      // No, the weapon is shown as carry anim
      //
      if (is_player()) {
        level->new_external_particle(id, src, dst, sz, delay_shorter,
                       tile_index_to_tile(w->tile_curr),
                       (w->is_dir_br() || w->is_dir_right() ||
                        w->is_dir_tr()),
                       true /* make_visible_at_end */);
      } else {
        level->new_internal_particle(id, src, dst, sz, delay_shorter,
                       tile_index_to_tile(w->tile_curr),
                       (w->is_dir_br() || w->is_dir_right() ||
                        w->is_dir_tr()),
                       true /* make_visible_at_end */);
      }
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  for (auto oid : monstp->carrying) {
    auto w = level->thing_find(oid);
    if (w) {
      w->move_to_immediately(mid_at);
      w->is_jumping = true;
    }
  }

  auto on_fire_anim_id = get_on_fire_anim_id();
  if (on_fire_anim_id.ok()) {_
    auto id = on_fire_anim_id;
    auto w = level->thing_find(id);
    if (w) {
      w->move_to_immediately(mid_at);
      w->is_jumping = true;
      if (is_player()) {
        level->new_external_particle(id, src, dst, sz, delay_shorter,
                       tile_index_to_tile(w->tile_curr),
                       (w->is_dir_br() || w->is_dir_right() ||
                        w->is_dir_tr()),
                       false /* make_visible_at_end */);
      } else {
        level->new_internal_particle(id, src, dst, sz, delay_shorter,
                       tile_index_to_tile(w->tile_curr),
                       (w->is_dir_br() || w->is_dir_right()
                        || w->is_dir_tr()),
                       false /* make_visible_at_end */);
      }
    }
  }

  //
  // If something moves on the water, make a ripple
  //
  if (is_monst() || is_player()) {
    if (!is_floating()) {
      if (level->is_shallow_water((int)mid_at.x, (int)mid_at.y)) {
        fpoint at(mid_at.x, mid_at.y);
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

bool Thing::try_to_jump_carefully (point p)
{_
  return try_to_jump(p, true);
}

bool Thing::try_to_jump_carefree (point p)
{_
  return try_to_jump(p, false);
}

bool Thing::try_to_jump (void)
{_
  if (is_changing_level ||
    is_hidden ||
    is_falling ||
    is_waiting_to_ascend_dungeon ||
    is_waiting_to_descend_sewer ||
    is_waiting_to_descend_dungeon ||
    is_waiting_to_ascend_sewer ||
    is_waiting_to_fall ||
    is_jumping) {
    return false;
  }

  float d = how_far_i_can_jump();
  int tries = d * d;

  while (tries-- > 0) {
    int x = pcg_random_range(mid_at.x - d, mid_at.x + d);
    int y = pcg_random_range(mid_at.y - d, mid_at.y + d);
    if (try_to_jump_carefully(point(x, y))) {
      return true;
    }
  }

  return false;
}

bool Thing::try_to_jump_towards_player (void)
{_
  if (is_changing_level ||
    is_hidden ||
    is_falling ||
    is_waiting_to_ascend_dungeon ||
    is_waiting_to_descend_sewer ||
    is_waiting_to_descend_dungeon ||
    is_waiting_to_ascend_sewer ||
    is_waiting_to_fall ||
    is_jumping) {
    return false;
  }

  float d = how_far_i_can_jump();
  int tries = d * d;

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

bool Thing::try_to_jump_away_from_player (void)
{_
  if (is_changing_level ||
    is_hidden ||
    is_falling ||
    is_waiting_to_ascend_dungeon ||
    is_waiting_to_descend_sewer ||
    is_waiting_to_descend_dungeon ||
    is_waiting_to_ascend_sewer ||
    is_waiting_to_fall ||
    is_jumping) {
    return false;
  }

  float d = how_far_i_can_jump();
  int tries = d * d;

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

bool Thing::try_harder_to_jump (void)
{_
  if (is_changing_level ||
    is_hidden ||
    is_falling ||
    is_waiting_to_ascend_dungeon ||
    is_waiting_to_descend_sewer ||
    is_waiting_to_descend_dungeon ||
    is_waiting_to_ascend_sewer ||
    is_waiting_to_fall ||
    is_jumping) {
    return false;
  }

  float d = how_far_i_can_jump();
  int tries = 100;

  while (tries-- > 0) {
    int x = pcg_random_range(mid_at.x - d, mid_at.x + d);
    int y = pcg_random_range(mid_at.y - d, mid_at.y + d);
    if (try_to_jump_carefree(point(x, y))) {
      return true;
    }
  }

  return false;
}

void Thing::jump_end (void)
{_
  if (!is_jumping) {
    return;
  }

  log("End of jump");
  is_jumping = false;
  move_finish();
  update_interpolated_position();

  //
  // Weapons follow also.
  //
  if (get_weapon_id_carry_anim().ok()) {
    auto w = level->thing_find(get_weapon_id_carry_anim());
    if (w) {
      w->is_jumping = false;
    }
  }

  if (get_weapon_id_use_anim().ok()) {
    auto w = level->thing_find(get_weapon_id_use_anim());
    if (w) {
      w->is_jumping = false;
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  for (auto oid : monstp->carrying) {
    auto o = level->thing_find(oid);
    if (o) {
      o->is_jumping = false;
    }
  }

  auto on_fire_anim_id = get_on_fire_anim_id();
  if (on_fire_anim_id.ok()) {_
    auto w = level->thing_find(on_fire_anim_id);
    if (w) {
      w->is_jumping = false;
    }
  }

  //
  // Attack of opportunity
  //
  if (is_player()) {
    auto t = most_dangerous_adjacent_thing_get();
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
}
