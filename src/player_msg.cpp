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

  if (game->tick_current < 1) {
    return false;
  }

  if (level->is_starting || level->is_being_destroyed) {
    return false;
  }
  return true;
}

bool Thing::player_is_ready_for_messages(std::string &why)
{
  verify(MTYPE_THING, this);

  if (! level) {
    why = "no level";
    return false;
  }

  if (! level->player) {
    why = "no player";
    return false;
  }

  if (level->player->is_dead || level->player->is_dying) {
    why = "player is dead";
    return false;
  }

  if (game->tick_current <= 1) {
    why = "first tick";
    return false;
  }

  if (level->is_starting) {
    why = "level is starting";
    return false;
  }

  if (level->is_being_destroyed) {
    why = "level is being destroyed";
    return false;
  }
  return true;
}

bool Thing::player_is_ready_for_thing_info(void)
{
  verify(MTYPE_THING, this);

  if (! level) {
    return false;
  }

  //
  // No popups before the first tick
  //
  if (game->tick_current <= 1) {
    if ((time_get_time_ms() - game->tick_begin_ms) < 100) {
      return false;
    }
  }

  if (! level->player) {
    return false;
  }

  if (level->player->is_dead || level->player->is_dying) {
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
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  va_list args;

  std::string why;

  if (! player_is_ready_for_messages(why)) {
    log("Player not ready for msg: %s", why.c_str());
    TRACE_AND_INDENT();
    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
    return;
  }

  int distance = get_distance_to_player();
  if (distance >= DMAP_IS_PASSABLE) {
    log("Too far for player to see msg:");
    TRACE_AND_INDENT();
    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
    return;
  }

  va_start(args, fmt);
  log_(fmt, args);
  va_end(args);

  va_start(args, fmt);
  ::topcon_(fmt, args);
  va_end(args);
}
