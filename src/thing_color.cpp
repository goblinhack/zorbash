//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_globals_extra.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::gfx_ascii_color_is_animated(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_color_is_animated());
}

int Thing::gfx_ascii_bg_color_spread_hue(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_bg_color_spread_hue());
}

int Thing::gfx_ascii_bg_color_spread_alpha(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_bg_color_spread_alpha());
}

int Thing::gfx_ascii_bg_color_spread_blue(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_bg_color_spread_blue());
}

int Thing::gfx_ascii_bg_color_spread_green(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_bg_color_spread_green());
}

int Thing::gfx_ascii_bg_color_spread_red(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_bg_color_spread_red());
}

int Thing::gfx_ascii_fg_color_spread_hue(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_fg_color_spread_hue());
}

int Thing::gfx_ascii_fg_color_spread_alpha(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_fg_color_spread_alpha());
}

int Thing::gfx_ascii_fg_color_spread_blue(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_fg_color_spread_blue());
}

int Thing::gfx_ascii_fg_color_spread_green(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_fg_color_spread_green());
}

int Thing::gfx_ascii_fg_color_spread_red(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_fg_color_spread_red());
}

const std::string &Thing::light_color(void)
{
  TRACE_NO_INDENT();
  return (tp()->light_color());
}
