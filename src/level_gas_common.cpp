//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"

bool Level::is_gas_blocker(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_gas_blocker, p.x, p.y));
}

bool Level::is_gas_blocker_no_check(const point p) const { return (get_no_check(_is_gas_blocker, p.x, p.y)); }

bool Level::is_gas_blocker(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_gas_blocker, x, y));
}

bool Level::is_gas_blocker_no_check(const int x, const int y) const { return (get_no_check(_is_gas_blocker, x, y)); }

void Level::is_gas_blocker_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_gas_blocker, x, y, true);
}

void Level::is_gas_blocker_no_check_set(const int x, const int y) { set_no_check(_is_gas_blocker, x, y, true); }

void Level::is_gas_blocker_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_gas_blocker, x, y, false);
}

void Level::is_gas_blocker_no_check_unset(const int x, const int y) { set_no_check(_is_gas_blocker, x, y, false); }

bool Level::is_gas_explosion_blocker(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_gas_explosion_blocker, p.x, p.y));
}

bool Level::is_gas_explosion_blocker_no_check(const point p) const
{
  return (get_no_check(_is_gas_explosion_blocker, p.x, p.y));
}

bool Level::is_gas_explosion_blocker(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_gas_explosion_blocker, x, y));
}

bool Level::is_gas_explosion_blocker_no_check(const int x, const int y) const
{
  return (get_no_check(_is_gas_explosion_blocker, x, y));
}

void Level::is_gas_explosion_blocker_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_gas_explosion_blocker, x, y, true);
}

void Level::is_gas_explosion_blocker_no_check_set(const int x, const int y)
{
  set_no_check(_is_gas_explosion_blocker, x, y, true);
}

void Level::is_gas_explosion_blocker_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_gas_explosion_blocker, x, y, false);
}

void Level::is_gas_explosion_blocker_no_check_unset(const int x, const int y)
{
  set_no_check(_is_gas_explosion_blocker, x, y, false);
}
