//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"

uint8_t Level::is_currently_pixelart_raycast_lit(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) { return false; }
  return (get(_is_currently_pixelart_raycast_lit, p.x, p.y));
}

uint8_t Level::is_currently_pixelart_raycast_lit_no_check(const point p)
{
  return (get_no_check(_is_currently_pixelart_raycast_lit, p.x, p.y));
}

//
// Note light fades
//
uint8_t Level::is_lit_recently_pixelart_raycast(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { return false; }
  //
  // So anything older than 10 ticks we consider not lit recently
  //
  return (get(_is_currently_pixelart_raycast_lit, x, y) > 250);
}

//
// Note light fades
//
uint8_t Level::is_currently_pixelart_raycast_lit(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { return false; }
  return (get(_is_currently_pixelart_raycast_lit, x, y));
}

uint8_t Level::is_currently_pixelart_raycast_lit_no_check(const int x, const int y)
{
  return (get_no_check(_is_currently_pixelart_raycast_lit, x, y));
}

void Level::is_currently_pixelart_raycast_lit_no_check_set(const int x, const int y)
{
  auto l = getptr_no_check(_is_currently_pixelart_raycast_lit, x, y);
  if (g_opt_ascii) {
    *l = 1;
    return;
  }

  if (*l == 0) {
    *l = 255;
  } else if (*l < 255) {
    (*l)++;
  }
}

void Level::is_currently_pixelart_raycast_lit_set(const int x, const int y)
{
  auto l = getptr(_is_currently_pixelart_raycast_lit, x, y);
  //
  // If not lit, push to full brightness. Else just allow the light to fade in.
  //
  if (*l == 0) {
    *l = 255;
  } else if (*l < 255) {
    (*l)++;
  }
}

void Level::is_currently_pixelart_raycast_lit_no_check_set(const int x, const int y, uint8_t v)
{
  set_no_check(_is_currently_pixelart_raycast_lit, x, y, v);
}

void Level::is_currently_pixelart_raycast_lit_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { return; }
  set(_is_currently_pixelart_raycast_lit, x, y, (uint8_t) 0);
}

void Level::is_currently_pixelart_raycast_lit_no_check_unset(const int x, const int y)
{
  set_no_check(_is_currently_pixelart_raycast_lit, x, y, (uint8_t) 0);
}

fcolor Level::ascii_light_source(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { return FCOLOR_NONE; }
  return (get(_ascii_light_source, x, y));
}

fcolor Level::ascii_light_source(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) { return FCOLOR_NONE; }
  return (get(_ascii_light_source, p.x, p.y));
}

fcolor Level::ascii_light_source_no_check(const int x, const int y)
{
  return (get_no_check(_ascii_light_source, x, y));
}

fcolor Level::ascii_light_source_no_check(const point p) { return (get_no_check(_ascii_light_source, p.x, p.y)); }

void Level::ascii_light_source_set(const point p, fcolor &v)
{
  if (unlikely(is_oob(p.x, p.y))) { return; }
  set(_ascii_light_source, p.x, p.y, v);
}

void Level::ascii_light_source_set(const int x, const int y, fcolor &v)
{
  if (unlikely(is_oob(x, y))) { return; }
  set(_ascii_light_source, x, y, v);
}

void Level::ascii_light_source_set_no_check(const point p, fcolor &v)
{
  if (unlikely(is_oob(p.x, p.y))) { return; }
  set(_ascii_light_source, p.x, p.y, v);
}

void Level::ascii_light_source_set_no_check(const int x, const int y, fcolor &v)
{
  if (unlikely(is_oob(x, y))) { return; }
  set(_ascii_light_source, x, y, v);
}

void Level::ascii_light_source_unset(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) { return; }
  set(_ascii_light_source, p.x, p.y, FCOLOR_NONE);
}

void Level::ascii_light_source_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { return; }
  set(_ascii_light_source, x, y, FCOLOR_NONE);
}

void Level::ascii_light_source_unset_no_check(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) { return; }
  set(_ascii_light_source, p.x, p.y, FCOLOR_NONE);
}

void Level::ascii_light_source_unset_no_check(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { return; }
  set(_ascii_light_source, x, y, FCOLOR_NONE);
}
