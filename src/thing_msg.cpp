//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

//
// A message generated for the console. Check if we should print it.
//
bool Thing::player_is_player_is_ready_for_messages(void)
{
  verify(MTYPE_THING, this);

  if (! level) {
    return false;
  }

  if (g_opt_test_dungeon) {
    return true;
  }

  auto player = level->player;
  if (! player) {
    dbg("player_is_player_is_ready_for_messages: No player");
    return false;
  }

  if (! game->player_is_ready_for_messages) {
    dbg("player_is_player_is_ready_for_messages: Not ready for messages");
    return false;
  }

  //
  // Cut down on post death messages.
  //
  if (player->is_dead) {
    dbg("player_is_player_is_ready_for_messages: Player is dead");
    return false;
  }

  if (level->is_starting || level->is_being_destroyed) {
    dbg("player_is_player_is_ready_for_messages: Level is starting");
    return false;
  }

  return true;
}

bool Thing::player_is_player_is_ready_for_messages(std::string &why)
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

  if (! game->player_is_ready_for_messages) {
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
    if (why.find('%') != std::string::npos) {
      //
      // Be careful as the fmt string has arguments
      //
      dbg("No player for msg");
    } else {
      dbg("No player for msg: %s", why.c_str());
    }
    TRACE_AND_INDENT();
    return;
  }

  if (! player_is_player_is_ready_for_messages(why)) {
    if (why.find('%') != std::string::npos) {
      //
      // Be careful as the fmt string has arguments
      //
      dbg("Player not ready for msg");
    } else {
      dbg("Player not ready for msg: %s", why.c_str());
    }
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
      //
      // If something is adjacent then always show the message
      //
      if (distance(player->curr_at, curr_at) > 1) {
        //
        // Else use the dmap distance to see if we can see it
        //
        int distance = distance_to_player();
        if (distance >= DMAP_IS_PASSABLE) {
          if (why.find('%') != std::string::npos) {
            //
            // Be careful as the fmt string has arguments
            //
            dbg("Too far to see (dist %d)", distance);
          } else {
            dbg("Too far to see (dist %d) msg: %s", distance, why.c_str());
          }
          TRACE_AND_INDENT();
          return;
        }
      }
    }

    if (! level->can_see_unimpeded(player->curr_at, curr_at)) {
      if (why.find('%') != std::string::npos) {
        //
        // Be careful as the fmt string has arguments
        //
        dbg("Cannot directly see for msg");
      } else {
        dbg("Cannot directly see for msg: %s", why.c_str());
      }
      TRACE_AND_INDENT();
      return;
    }
  }

  va_start(args, fmt);
  ::topcon_(fmt, args);
  va_end(args);
}
