//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"
#include "my_thing_template.h"
#include "my_sdl.h"

bool Thing::describe_when_hovered_over_in_rightbar (void)
{_
  level->describe(this);
  return true;
}

bool Thing::describe_when_hovering_over (void)
{_
  level->describe(this);
  return true;
}
