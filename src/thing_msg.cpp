//
// Copyright Neil McGill, goblinhack@gmail.com
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

  auto player = level->player;
  if (! player) {
    return false;
  }

  //
  // Cut down on post death messages.
  //
  if (player->is_dead) {
    return false;
  }

  if (game->tick_current <= 1) {
    if (game->tick_requested.empty()) {
      if (! game->tick_begin_ms || (time_ms() - game->tick_begin_ms) < 50) {
        return false;
      }
    }
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

  auto player = level->player;
  if (! player) {
    why = "no player";
    return false;
  }

  //
  // Cut down on post death messages.
  //
  if (player->is_dead) {
    return false;
  }

  if (game->tick_current <= 1) {
    if (game->tick_requested.empty()) {
      if (! game->tick_begin_ms || (time_ms() - game->tick_begin_ms) < 50) {
        why = "first tick";
        return false;
      }
    }
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

//
// A message generated for the console. Check if we should print it.
//
void Thing::msg(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);

  std::string why = fmt;
  va_list     args;

  auto player = level->player;
  if (! player) {
    dbg("No player for msg: %s", why.c_str());
    TRACE_AND_INDENT();

    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
    return;
  }

  if (! player_is_ready_for_messages(why)) {
    dbg("Player not ready for msg: %s", why.c_str());
    TRACE_AND_INDENT();

    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
    return;
  }

  //
  // If this is a monst attacking, do we want to see the message?
  //
  if (! is_player()) {
    //
    // If a ghost is in a wall and trying to attack the player, we must allow that even though the DMAP will say wall.
    //
    if (! is_ethereal()) {
      int distance = distance_to_player();
      if (distance >= DMAP_IS_PASSABLE) {
        dbg("Too far to see (dist %d) msg: %s", distance, why.c_str());
        TRACE_AND_INDENT();

        va_start(args, fmt);
        log_(fmt, args);
        va_end(args);
        return;
      }
    }

    if (! level->can_see_unimpeded(player->curr_at, curr_at)) {
      dbg("Cannot directly see for msg: %s", why.c_str());
      TRACE_AND_INDENT();

      va_start(args, fmt);
      log_(fmt, args);
      va_end(args);
      return;
    }
  }

  va_start(args, fmt);
  log_(fmt, args);
  va_end(args);

  va_start(args, fmt);
  ::topcon_(fmt, args);
  va_end(args);
}
