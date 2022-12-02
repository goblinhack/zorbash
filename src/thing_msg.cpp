//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
// REMOVED #include <stdarg.h>

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

  if (! player->ready_for_messages) {
    return false;
  }

  //
  // Cut down on post death messages.
  //
  if (player->is_dead) {
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

  auto player = level->player;
  if (! player) {
    why = "no player";
    return false;
  }

  if (! player->ready_for_messages) {
    return false;
  }

  //
  // Cut down on post death messages.
  //
  if (player->is_dead) {
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
    return;
  }

  if (! player_is_ready_for_messages(why)) {
    dbg("Player not ready for msg: %s", why.c_str());
    TRACE_AND_INDENT();
    return;
  }

  //
  // If this is a monst attacking, do we want to see the message?
  //
  auto owner = top_owner();
  if (is_player() || (owner && owner->is_player())) {
    //
    // Player messages are normally shown.
    //
  } else {
    //
    // If a ghost is in a wall and trying to attack the player, we must allow that even though the DMAP will say wall.
    //
    if (! is_ethereal()) {
      int distance = distance_to_player();
      if (distance >= DMAP_IS_PASSABLE) {
        dbg("Too far to see (dist %d) msg: %s", distance, why.c_str());
        TRACE_AND_INDENT();
        return;
      }
    }

    if (! level->can_see_unimpeded(player->curr_at, curr_at)) {
      dbg("Cannot directly see for msg: %s", why.c_str());
      TRACE_AND_INDENT();
      return;
    }
  }

  va_start(args, fmt);
  ::topcon_(fmt, args);
  va_end(args);
}
