//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include <stdarg.h>

//
// A message generated for the console. Check if we should print it.
//
bool Thing::player_is_ready_for_messages(void)
{
  verify(MTYPE_THING, this);

  if (! level) {
    return false;
  }

  if (! level->player) {
    return false;
  }

  if (level->player->is_dead || level->player->is_dying) {
    return false;
  }

  if (game->tick_current <= 1) {
    return false;
  }

  if (level->is_starting || level->is_being_destroyed) {
    return false;
  }
  return true;
}

//
// A message generated for the console. Check if we should print it.
//
void Thing::msg(const char *fmt, ...)
{
  verify(MTYPE_THING, this);
  va_list args;

  if (! player_is_ready_for_messages()) {
    return;
  }

  va_start(args, fmt);
  ::topcon_(fmt, args);
  va_end(args);
}
