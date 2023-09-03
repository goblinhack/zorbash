//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Level::is_obs_wall_or_door(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_wall_or_door, p.x, p.y));
}

bool Level::is_obs_wall_or_door_no_check(const point p) const
{
  return (get_no_check(_is_obs_wall_or_door, p.x, p.y));
}

bool Level::is_obs_wall_or_door(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_wall_or_door, x, y));
}

bool Level::is_obs_wall_or_door_no_check(const int x, const int y) const
{
  return (get_no_check(_is_obs_wall_or_door, x, y));
}

void Level::is_obs_wall_or_door_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_wall_or_door, x, y, true);
}

void Level::is_obs_wall_or_door_no_check_set(const int x, const int y)
{
  set_no_check(_is_obs_wall_or_door, x, y, true);
}

void Level::is_obs_wall_or_door_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_wall_or_door, x, y, false);
}

void Level::is_obs_wall_or_door_no_check_unset(const int x, const int y)
{
  set_no_check(_is_obs_wall_or_door, x, y, false);
}

bool Level::is_obs_when_dead(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_when_dead, p.x, p.y));
}

bool Level::is_obs_when_dead_no_check(const point p) const { return (get_no_check(_is_obs_when_dead, p.x, p.y)); }

bool Level::is_obs_when_dead(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_when_dead, x, y));
}

bool Level::is_obs_when_dead_no_check(const int x, const int y) const
{
  return (get_no_check(_is_obs_when_dead, x, y));
}

void Level::is_obs_when_dead_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_when_dead, x, y, true);
}

void Level::is_obs_when_dead_no_check_set(const int x, const int y) { set_no_check(_is_obs_when_dead, x, y, true); }

void Level::is_obs_when_dead_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_when_dead, x, y, false);
}

void Level::is_obs_when_dead_no_check_unset(const int x, const int y)
{
  set_no_check(_is_obs_when_dead, x, y, false);
}

bool Level::is_obs_shoving(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_shoving, p.x, p.y));
}

bool Level::is_obs_shoving_no_check(const point p) const { return (get_no_check(_is_obs_shoving, p.x, p.y)); }

bool Level::is_obs_shoving(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_shoving, x, y));
}

bool Level::is_obs_shoving_no_check(const int x, const int y) const { return (get_no_check(_is_obs_shoving, x, y)); }

void Level::is_obs_shoving_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_shoving, x, y, true);
}

void Level::is_obs_shoving_no_check_set(const int x, const int y) { set_no_check(_is_obs_shoving, x, y, true); }

void Level::is_obs_shoving_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_shoving, x, y, false);
}

void Level::is_obs_shoving_no_check_unset(const int x, const int y) { set_no_check(_is_obs_shoving, x, y, false); }

bool Level::is_obs_jump_end(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_jump_end, p.x, p.y));
}

bool Level::is_obs_jump_end_no_check(const point p) const { return (get_no_check(_is_obs_jump_end, p.x, p.y)); }

bool Level::is_obs_jump_end(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_jump_end, x, y));
}

bool Level::is_obs_jump_end_no_check(const int x, const int y) const
{
  return (get_no_check(_is_obs_jump_end, x, y));
}

void Level::is_obs_jump_end_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_jump_end, x, y, true);
}

void Level::is_obs_jump_end_no_check_set(const int x, const int y) { set_no_check(_is_obs_jump_end, x, y, true); }

void Level::is_obs_jump_end_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_jump_end, x, y, false);
}

void Level::is_obs_jump_end_no_check_unset(const int x, const int y) { set_no_check(_is_obs_jump_end, x, y, false); }

bool Level::is_obs_spawn_monst(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_spawn_monst, p.x, p.y));
}

bool Level::is_obs_spawn_monst_no_check(const point p) const { return (get_no_check(_is_obs_spawn_monst, p.x, p.y)); }

bool Level::is_obs_spawn_monst(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_spawn_monst, x, y));
}

bool Level::is_obs_spawn_monst_no_check(const int x, const int y) const
{
  return (get_no_check(_is_obs_spawn_monst, x, y));
}

void Level::is_obs_spawn_monst_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_spawn_monst, x, y, true);
}

void Level::is_obs_spawn_monst_no_check_set(const int x, const int y)
{
  set_no_check(_is_obs_spawn_monst, x, y, true);
}

void Level::is_obs_spawn_monst_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_spawn_monst, x, y, false);
}

void Level::is_obs_spawn_monst_no_check_unset(const int x, const int y)
{
  set_no_check(_is_obs_spawn_monst, x, y, false);
}

bool Level::is_obs_spawn(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_spawn, p.x, p.y));
}

bool Level::is_obs_spawn_no_check(const point p) const { return (get_no_check(_is_obs_spawn, p.x, p.y)); }

bool Level::is_obs_spawn(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_spawn, x, y));
}

bool Level::is_obs_spawn_no_check(const int x, const int y) const { return (get_no_check(_is_obs_spawn, x, y)); }

void Level::is_obs_spawn_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_spawn, x, y, true);
}

void Level::is_obs_spawn_no_check_set(const int x, const int y) { set_no_check(_is_obs_spawn, x, y, true); }

void Level::is_obs_spawn_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_spawn, x, y, false);
}

void Level::is_obs_spawn_no_check_unset(const int x, const int y) { set_no_check(_is_obs_spawn, x, y, false); }

bool Level::is_obs_destructable(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_destructable, p.x, p.y));
}

bool Level::is_obs_destructable_no_check(const point p) const
{
  return (get_no_check(_is_obs_destructable, p.x, p.y));
}

bool Level::is_obs_destructable(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_destructable, x, y));
}

bool Level::is_obs_destructable_no_check(const int x, const int y) const
{
  return (get_no_check(_is_obs_destructable, x, y));
}

void Level::is_obs_destructable_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_destructable, x, y, true);
}

void Level::is_obs_destructable_no_check_set(const int x, const int y)
{
  set_no_check(_is_obs_destructable, x, y, true);
}

void Level::is_obs_destructable_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_destructable, x, y, false);
}

void Level::is_obs_destructable_no_check_unset(const int x, const int y)
{
  set_no_check(_is_obs_destructable, x, y, false);
}
