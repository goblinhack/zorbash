//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::bounce(float bounce_height, float bounce_fade, ts_t ms, int bounce_count)
{
  if (g_opt_ascii) {
    return true;
  }

  if (is_sleeping) {
    return false;
  }

  if (is_frozen || is_burnt || is_dead) {
    return false;
  }

  //
  // Check if we can lunge
  //
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_OBJ)
  {
    if (t == this) {
      continue;
    }
    if (t->is_spell_of_holding_barrier()) {
      dbg("No bouncing when stuck in a spell barrier");
      return false;
    }
    if (t->is_block_of_ice()) {
      dbg("No bouncing when stuck in ice");
      return false;
    }
    if (t->is_block_of_crystal()) {
      dbg("No bouncing when stuck in crystal");
      return false;
    }
    if (t->is_very_heavy()) {
      dbg("No bouncing when stuck under something heavy");
      return false;
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  auto t = ts_bounce_begin_set(time_ms_cached());
  ts_bounce_end_set(t + ms);

  bounce_height_set(bounce_height);
  bounce_fade_set(bounce_fade);
  bounce_count_set(bounce_count);
  is_bouncing = true;

  return true;
}

float Thing::bounce_curr(void)
{
  if (! is_bouncing) {
    return (0.0);
  }

  auto t = time_ms_cached();

  if (t >= ts_bounce_end()) {
    is_bouncing = false;

    if (bounce_count() == 255) {
      //
      // Bounce forever
      //
      bounce(bounce_height_curr() * bounce_fade_curr(), bounce_fade_curr(),
             ((float) (ts_bounce_end()) - ts_bounce_begin()) * bounce_fade_curr(), bounce_count());
    } else if (bounce_count()) {
      bounce(bounce_height_curr() * bounce_fade_curr(), bounce_fade_curr(),
             ((float) (ts_bounce_end()) - ts_bounce_begin()) * bounce_fade_curr(), bounce_count() - 1);
    }

    return 0;
  }

  float time_step = ((float) (t) -ts_bounce_begin()) / ((float) (ts_bounce_end()) - ts_bounce_begin());

  float height = 1.0;

  height *= sin(time_step * RAD_180);
  height *= bounce_height_curr();

  return height;
}

////////////////////////////////////////////////////////////////////////////
// ts_bounce_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_bounce_begin(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_bounce_begin);
  }
  return 0;
}

ts_t Thing::ts_bounce_begin_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin = v);
}

ts_t Thing::ts_bounce_begin_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin -= v);
}

ts_t Thing::ts_bounce_begin_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin += v);
}

ts_t Thing::ts_bounce_begin_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin--);
}

ts_t Thing::ts_bounce_begin_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_bounce_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_bounce_end(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_bounce_end);
  }
  return 0;
}

ts_t Thing::ts_bounce_end_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end = v);
}

ts_t Thing::ts_bounce_end_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end -= v);
}

ts_t Thing::ts_bounce_end_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end += v);
}

ts_t Thing::ts_bounce_end_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end--);
}

ts_t Thing::ts_bounce_end_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end++);
}

////////////////////////////////////////////////////////////////////////////
// bounce_height
////////////////////////////////////////////////////////////////////////////
float Thing::bounce_height_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->bounce_height);
  }
  return 0;
}

void Thing::bounce_height_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->bounce_height = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_fade
////////////////////////////////////////////////////////////////////////////
float Thing::bounce_fade_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->bounce_fade);
  }
  return 0;
}

void Thing::bounce_fade_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->bounce_fade = v;
}

int Thing::gfx_pixelart_bounce_always(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_bounce_always());
}

int Thing::gfx_pixelart_bounce_on_move(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_bounce_on_move());
}

////////////////////////////////////////////////////////////////////////////
// bounce_count
////////////////////////////////////////////////////////////////////////////
int Thing::bounce_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->bounce_count);
  }
  return 0;
}

void Thing::bounce_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->bounce_count = v;
}
