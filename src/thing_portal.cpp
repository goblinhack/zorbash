//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"

void Thing::portal_tick(void)
{
  if (is_ethereal()) {
    return;
  }

  //
  // No teleport infinite loops
  //
  if (tick_last_teleported() != -1) {
    if (tick_last_teleported() >= game->tick_current - 1) {
      return;
    }
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

  TeleportOptions teleport_options;
  teleport_options.teleport_carefully = false;
  teleport_options.teleport_limit     = false;

  auto radius = TELEPORT_DISTANCE_MAX;

  std::vector< point > choices;

  //
  // Try to find another portal
  //
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {

      if (! level->is_portal(x, y)) {
        continue;
      }

      //
      // Ignore the originating portal
      //
      if ((curr_at.x == x) && (curr_at.y == y)) {
        continue;
      }

      dbg("Found a new portal at: %d,%d", x, y);

      //
      // Found one.
      //
      choices.push_back(point(x, y));
    }
  }

  if (choices.size()) {
    bool too_far;
    auto to = pcg_one_of(choices);
    teleport(teleport_options, to, &too_far);
    return;
  }

  dbg("Did not find a portal, teleport randomly");

  teleport_randomly(teleport_options, radius);
}

bool Thing::teleport_portal(Thingp portal)
{
  TRACE_NO_INDENT();

  dbg("Entering a portal: %s", portal->to_short_string().c_str());

  TeleportOptions teleport_options;
  teleport_options.teleport_carefully = false;
  teleport_options.teleport_limit     = false;

  auto radius = TELEPORT_DISTANCE_MAX;

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
      if ((portal->curr_at.x == px) && (portal->curr_at.y == py)) {
        continue;
      }

      dbg("Found a new portal at: %d,%d", px, py);

      //
      // Found one.
      //
      bool too_far = false;

      return teleport(teleport_options, point(px, py), &too_far);
    }
  }

  dbg("Did not find a portal, teleport randomly");

  return teleport_randomly(teleport_options, radius);
}

bool Thing::teleport_portal_find_target(point &other_end_of_portal)
{
  TRACE_NO_INDENT();

  auto radius = TELEPORT_DISTANCE_MAX;

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

      other_end_of_portal = point(px, py);
      return true;
    }
  }

  int tries = radius * radius;

  while (tries-- > 0) {
    int x = pcg_random_range(curr_at.x - radius, curr_at.x + radius);
    int y = pcg_random_range(curr_at.y - radius, curr_at.y + radius);

    if (level->is_oob(x, y)) {
      continue;
    }

    other_end_of_portal = point(x, y);
    return true;
  }

  return false;
}

Thingp Level::thing_find_portal_at(point at)
{
  FOR_ALL_THINGS_THAT_INTERACT(this, t, at.x, at.y)
  {
    if (t->is_portal()) {
      return t;
    }
  }
  FOR_ALL_THINGS_END()

  return nullptr;
}
