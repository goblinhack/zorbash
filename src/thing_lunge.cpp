//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::lunge(point to)
{
  if (is_sleeping) {
    return;
  }

  if ((paralysis_count() > 0) || is_frozen || is_burnt || is_dead) {
    return;
  }

  if (! is_able_to_lunge()) {
    return;
  }

  //
  // Already lunging? This can happen when swinging a weapon that hits in multiple
  // directions. Don't make the player dizzy and focus on the intial lunge.
  //
  if (ts_lunge_begin()) {
    return;
  }

  dbg("Lunge to %d,%d", to.x, to.y);
  TRACE_AND_INDENT();

  move_finish();

  //
  // Check if we can lunge
  //
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_OBJ)
  {
    if (t == this) {
      continue;
    }
    if (t->is_spell_of_holding_barrier() && ! is_immune_to_spell_of_holding()) {
      dbg("No lunging when stuck in a magicial hold");
      return;
    }
    if (t->is_block_of_ice()) {
      dbg("No lunging when stuck in ice");
      return;
    }
    if (t->is_very_heavy()) {
      dbg("No lunging when stuck under something heavy");
      return;
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  auto t = ts_lunge_begin_set(time_ms_cached());
  auto p = to - curr_at;
  ts_lunge_end_set(t + 200);
  lunge_to_set(to);
  move_set_dir_from_delta(p);
}

float Thing::lunge_curr(void)
{
  if (! ts_lunge_begin()) {
    return 0;
  }

  auto t = time_ms_cached();

  if (t >= ts_lunge_end()) {
    ts_lunge_begin_set(0);
    ts_lunge_end_set(0);
    return 0;
  }

  float time_step = ((float) (t) -ts_lunge_begin()) / ((float) (ts_lunge_end()) - ts_lunge_begin());

  if (time_step > 0.5) {
    return (1.0 - time_step);
  }
  return time_step;
}

////////////////////////////////////////////////////////////////////////////
// ts_lunge_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_lunge_begin(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_lunge_begin);
  }
  return 0;
}

ts_t Thing::ts_lunge_begin_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin = v);
}

ts_t Thing::ts_lunge_begin_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin -= v);
}

ts_t Thing::ts_lunge_begin_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin += v);
}

ts_t Thing::ts_lunge_begin_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin--);
}

ts_t Thing::ts_lunge_begin_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_lunge_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_lunge_end(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_lunge_end);
  }
  return 0;
}

ts_t Thing::ts_lunge_end_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end = v);
}

ts_t Thing::ts_lunge_end_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end -= v);
}

ts_t Thing::ts_lunge_end_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end += v);
}

ts_t Thing::ts_lunge_end_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end--);
}

ts_t Thing::ts_lunge_end_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end++);
}

int Thing::is_able_to_lunge(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_lunge());
}

////////////////////////////////////////////////////////////////////////////
// lunge_to
////////////////////////////////////////////////////////////////////////////
point Thing::lunge_to_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->lunge_to);
  }
  return (point(0, 0));
}

void Thing::lunge_to_set(point v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->lunge_to = v;
}
