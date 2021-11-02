//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

bool Thing::target_select(Thingp what)
{
  TRACE_AND_INDENT();
  if (game->state != Game::STATE_CHOOSING_TARGET) {
    TOPCON("Choose a target to use %s at.", what->text_the().c_str());
  }

  game->change_state(Game::STATE_CHOOSING_TARGET);
  level->cursor_recreate();
  level->cursor->visible();
  level->describe(what);

  return true;
}
