//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_sdl.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"

bool Thing::describe_when_hovered_over_in_rightbar(void)
{
  TRACE_AND_INDENT();
  level->describe(this);
  return true;
}

bool Thing::describe_when_hovering_over(void)
{
  TRACE_AND_INDENT();
  level->describe(this);
  return true;
}
