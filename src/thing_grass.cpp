//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::grass_tick(void)
{
  TRACE_NO_INDENT();

  if (! is_alive_monst() && ! is_player()) {
    return;
  }

  if (is_floating() || is_flying() || is_ethereal()) {
    return;
  }

  if (level->is_wet_grass(curr_at.x, curr_at.y)) {
    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_FLOOR2)
    {
      if (t->is_dead) {
        continue;
      }

      if (t->name() == "wet_grass1") {
        if (t->is_wet_grass()) {
          t->dead("trampled");
          level->thing_new("wet_grass_trampled1", t->curr_at);
        }
      }
      if (t->name() == "wet_grass2") {
        if (t->is_wet_grass()) {
          t->dead("trampled");
          level->thing_new("wet_grass_trampled2", t->curr_at);
        }
      }
      if (t->name() == "wet_grass3") {
        if (t->is_wet_grass()) {
          t->dead("trampled");
          level->thing_new("wet_grass_trampled3", t->curr_at);
        }
      }
      if (t->name() == "wet_grass4") {
        if (t->is_wet_grass()) {
          t->dead("trampled");
          level->thing_new("wet_grass_trampled4", t->curr_at);
        }
      }
      if (t->name() == "wet_grass5") {
        if (t->is_wet_grass()) {
          t->dead("trampled");
          level->thing_new("wet_grass_trampled5", t->curr_at);
        }
      }
      if (t->name() == "wet_grass6") {
        if (t->is_wet_grass()) {
          t->dead("trampled");
          level->thing_new("wet_grass_trampled6", t->curr_at);
        }
      }
    }
    FOR_ALL_THINGS_END()
  }

  if (level->is_dry_grass(curr_at.x, curr_at.y)) {
    FOR_ALL_THINGS_AT_DEPTH(level, t, curr_at.x, curr_at.y, MAP_DEPTH_FLOOR2)
    {
      if (t->is_dead) {
        continue;
      }

      if (t->is_dry_grass()) {
        t->dead("trampled");
        level->thing_new("dry_grass_trampled", t->curr_at);
      }
    }
    FOR_ALL_THINGS_END()
  }
}

uint8_t Level::is_dry_grass(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_dry_grass, p.x, p.y));
}

uint8_t Level::is_dry_grass(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_dry_grass, x, y));
}

void Level::is_dry_grass_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_dry_grass, x, y, (uint8_t) 1);
}

void Level::is_dry_grass_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_dry_grass, x, y, (uint8_t) 1);
}

uint8_t Level::is_wet_grass(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_wet_grass, p.x, p.y));
}

uint8_t Level::is_wet_grass(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_wet_grass, x, y));
}

void Level::is_wet_grass_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_wet_grass, x, y, (uint8_t) 1);
}

void Level::is_wet_grass_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_wet_grass, x, y, (uint8_t) 1);
}

int Thing::is_dry_grass_trampled(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dry_grass_trampled());
}

int Thing::is_wet_grass_trampled(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wet_grass_trampled());
}

int Thing::is_dry_grass(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dry_grass());
}

int Thing::is_wet_grass(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wet_grass());
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

