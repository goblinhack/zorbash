//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

void Thing::portal_tick(void)
{
  if (is_ethereal()) {
    return;
  }

  //
  // No teleport infinite loops
  //
  if (game->tick_current < tick_last_teleported() + 1) {
    return;
  }

  //
  // Prevent items sitting on a portal from teleporting for ever.
  //
  if (curr_at == last_at) {
    //
    // But allow the player to do this so you can check out a new position.
    //
    if (! is_player()) {
      return;
    }
  }

  if (! is_able_to_be_teleported()) {
    return;
  }

  if (! level->is_portal(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Portal tick");
  TRACE_AND_INDENT();

  TeleportReason reason;
  reason.teleport_carefully = false;
  reason.teleport_limit     = false;

  auto radius = 30;

  //
  // Try to find another portal
  //
  for (int dx = -radius; dx < radius; dx++) {
    for (int dy = -radius; dy < radius; dy++) {

      auto px = curr_at.x + dx;
      auto py = curr_at.y + dy;

      if (! level->is_portal(px, py)) {
        continue;
      }

      //
      // Ignore the originating portal
      //
      if ((curr_at.x == px) && (curr_at.y == py)) {
        continue;
      }

      dbg("Found a new portal at: %d,%d", px, py);

      //
      // Found one.
      //
      bool too_far = false;

      teleport(reason, point(px, py), &too_far);

      return;
    }
  }

  dbg("Did not find a portal, teleport randomly");

  teleport_randomly(reason, radius);
}
