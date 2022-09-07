//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

point Thing::dir_to_direction(void)
{
  TRACE_NO_INDENT();
  if (is_dir_tl()) {
    return point(-1, -1);
  }

  if (is_dir_tr()) {
    return point(1, -1);
  }

  if (is_dir_bl()) {
    return point(-1, 1);
  }

  if (is_dir_br()) {
    return point(1, 1);
  }

  if (is_dir_down()) {
    return point(0, 1);
  }

  if (is_dir_up()) {
    return point(0, -1);
  }

  if (is_dir_right()) {
    return point(1, 0);
  }

  if (is_dir_left()) {
    return point(-1, 0);
  }
  return point(0, 0);
}

void Thing::move_set_dir_from_dest_or_delta(point delta)
{
  //
  // Check if we can lunge
  //
  FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_OBJ)
  {
    if (t->is_block_of_ice()) {
      dbg("No direction change when stuck ice");
      return;
    }
  }
  FOR_ALL_THINGS_END()

  auto ai = maybe_aip();
  if (ai && ai->move_path.size() > 1) {
    auto goal = ai->move_path[ ai->move_path.size() - 1 ];
    move_set_dir_from_delta(goal - curr_at);
  } else {
    move_set_dir_from_delta(delta);
  }
}

void Thing::move_set_dir_from_target(Thingp target)
{
  auto delta = target->curr_at - curr_at;
  move_set_dir_from_delta(delta);
}

void Thing::move_set_dir_from_delta(point delta)
{
  //
  // If not moving and this is the first move then break out of the
  // idle animation.
  //
  if (is_dir_none()) {
    ts_next_frame = time_game_ms_cached();
  }

  if (delta.x < 0) {
    if (delta.y > 0) {
      dir_set_bl();
    } else if (delta.y < 0) {
      dir_set_tl();
    } else {
      dir_set_left();
    }
    has_ever_moved = true;
    return;
  }

  if (delta.x > 0) {
    if (delta.y > 0) {
      dir_set_br();
    } else if (delta.y < 0) {
      dir_set_tr();
    } else {
      dir_set_right();
    }
    has_ever_moved = true;
    return;
  }

  if (delta.y > 0) {
    if (delta.x > 0) {
      dir_set_br();
    } else if (delta.x < 0) {
      dir_set_bl();
    } else {
      dir_set_down();
    }
    has_ever_moved = true;
    return;
  }

  if (delta.y < 0) {
    if (delta.x > 0) {
      dir_set_tr();
    } else if (delta.x < 0) {
      dir_set_tl();
    } else {
      dir_set_up();
    }
    has_ever_moved = true;
    return;
  }
}
