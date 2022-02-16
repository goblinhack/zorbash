//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
// REMOVED #include "my_sdl.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"

bool Thing::describe_when_hovered_over_in_rightbar(void)
{
  TRACE_NO_INDENT();
  level->describe(this);
  return true;
}

bool Thing::describe_when_hovering_over(void)
{
  TRACE_NO_INDENT();
  level->describe(this);
  return true;
}
