//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::grass_tick(void)
{
  TRACE_NO_INDENT();

  if (! is_alive_monst() && ! is_player()) {
    return;
  }

  if (is_floating_currently() || is_flying() || is_ethereal()) {
    return;
  }

  if (level->is_grass_wet(curr_at.x, curr_at.y)) {
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_FLOOR2)
    {
      if (t->is_dead) {
        continue;
      }

      if (level->is_lava(curr_at) || level->is_fire(curr_at)) {
        //
        // Burnt grass
        //
        if (t->is_grass_wet()) {
          t->dead("trampled");
          level->thing_new("grass_dry_dead", t->curr_at);
        }
      } else {
        //
        // Flattened grass
        //
        if (t->name() == "grass_wet1") {
          if (t->is_grass_wet()) {
            t->dead("trampled");
            level->thing_new("grass_wet_trampled1", t->curr_at);
          }
        }
        if (t->name() == "grass_wet2") {
          if (t->is_grass_wet()) {
            t->dead("trampled");
            level->thing_new("grass_wet_trampled2", t->curr_at);
          }
        }
        if (t->name() == "grass_wet3") {
          if (t->is_grass_wet()) {
            t->dead("trampled");
            level->thing_new("grass_wet_trampled3", t->curr_at);
          }
        }
        if (t->name() == "grass_wet4") {
          if (t->is_grass_wet()) {
            t->dead("trampled");
            level->thing_new("grass_wet_trampled4", t->curr_at);
          }
        }
        if (t->name() == "grass_wet5") {
          if (t->is_grass_wet()) {
            t->dead("trampled");
            level->thing_new("grass_wet_trampled5", t->curr_at);
          }
        }
        if (t->name() == "grass_wet6") {
          if (t->is_grass_wet()) {
            t->dead("trampled");
            level->thing_new("grass_wet_trampled6", t->curr_at);
          }
        }
      }
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }

  if (level->is_grass_dry(curr_at.x, curr_at.y)) {
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_FLOOR2)
    {
      if (t->is_dead) {
        continue;
      }

      if (t->is_grass_dry()) {
        t->dead("trampled");
        level->thing_new("grass_dry_trampled", t->curr_at);
      }
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }
}

uint8_t Level::is_grass_dry(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_grass_dry, p.x, p.y));
}

uint8_t Level::is_grass_dry(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_grass_dry, x, y));
}

void Level::is_grass_dry_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_grass_dry, x, y, (uint8_t) 1);
}

void Level::is_grass_dry_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_grass_dry, x, y, (uint8_t) 1);
}

uint8_t Level::is_grass_wet(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_grass_wet, p.x, p.y));
}

uint8_t Level::is_grass_wet(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_grass_wet, x, y));
}

void Level::is_grass_wet_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_grass_wet, x, y, (uint8_t) 1);
}

void Level::is_grass_wet_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_grass_wet, x, y, (uint8_t) 1);
}

int Thing::is_grass_dry_trampled(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_grass_dry_trampled());
}

int Thing::is_grass_wet_trampled(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_grass_wet_trampled());
}

int Thing::is_grass_dry(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_grass_dry());
}

int Thing::is_grass_wet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_grass_wet());
}

int Thing::is_grass(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_grass());
}

int Thing::is_eater_of_grass(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_grass());
}

int Thing::is_foliage(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_foliage());
}

int Thing::is_eater_of_foliage(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_foliage());
}
