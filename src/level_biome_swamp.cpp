//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Level::create_biome_swamp(point3d at, uint32_t seed)
{
  TRACE_AND_INDENT();
  dbg("INF: Create swamp");

  if (player) {
    TOPCON("A new swamp level is coming into being...");
  }

  biome = BIOME_SWAMP;

  //
  // Setup the various chances of things appearing.
  //
  chances_of_creating_set();

  uint32_t start = time_ms();

  uint32_t    slowest_so_far = 0;
  std::string slowest_so_far_which;

  while (true) {
    uint32_t start = time_ms();
    auto     dungeon
        = new Dungeon(BIOME_SWAMP, MAP_WIDTH, MAP_HEIGHT, DUNGEON_GRID_CHUNK_WIDTH, DUNGEON_GRID_CHUNK_HEIGHT, seed);
    if (dungeon->failed) {
      log("INF: create swamp, failed, retry");
      seed++;
      delete dungeon;
      continue;
    }

    if (! g_opt_test_dungeon) {
      log("INF: Create swamp layout took %u ms", time_ms() - start);
    }

    //
    // Check we have a swamp start
    //
    dbg2("INF: Look for entrance");
    {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
          if (dungeon->is_ascend_dungeon(x, y)) {
            goto have_dungeon_start;
          }
        }
      }
      ERR("Did not find swamp entrance");
      return false;
    }
  have_dungeon_start:

    slowest_so_far = 0;

    //
    // The grid is the basis of all reality.
    //
    {
      uint32_t start = time_ms();
      dbg2("INF: Place the grid");
      place_the_grid();
      if (g_errored) {
        return false;
      }

      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing the grid";
      }
    }

    int tries = 500;

    {
      uint32_t start = time_ms();
      dbg2("INF: Place rocks");
      create_biome_swamp_place_rocks(dungeon, 1, 6, 6, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 1, 6, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 1, 3, 6, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 1, 3, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 2, 3, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 1, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 2, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 3, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 1, 2, 1, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 2, 2, 1, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 1, 1, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_swamp_place_rocks(dungeon, 2, 1, 2, tries);
      if (g_errored) {
        return false;
      }

      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing rocks";
      }
    }

    create_biome_swamp_place_remaining_rocks(dungeon);

    {
      uint32_t start = time_ms();
      dbg2("INF: Place dirt");
      create_biome_swamp_place_dirt(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing dirt";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place deep water");
      create_biome_swamp_place_deep_water(dungeon, "deep_water");
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing deep water";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place shallow water");
      create_biome_swamp_place_place_shallow_water(dungeon, "water");
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing shallow water";
      }
    }

    //
    // Items that have no special placement rules
    //
    {
      uint32_t start = time_ms();
      dbg2("INF: Place items");
      place_objects_with_normal_placement_rules(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing items";
      }
    }

    //
    // Be nice
    //
    {
      uint32_t start = time_ms();
      dbg2("INF: Place random treasure");
      place_random_treasure(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing treasure";
      }
    }

    //
    // Be even nicer
    //
    if (d100() < 25) {
      uint32_t start = time_ms();
      dbg2("INF: Place random treasure");
      place_random_named(dungeon, "potion_of_life");
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing potion of life";
      }
    }

    //
    // Final update of the heat-map to account placement of braziers
    //
    dbg2("INF: Final update heatmap");

    {
      uint32_t start = time_ms();
      update_heatmap();
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "updating the heat-map again";
      }
    }

    //
    // Place some greenery
    //
    {
      uint32_t start = time_ms();
      dbg2("INF: Place dry grass");
      create_biome_swamp_place_grass_dry(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing dry grass";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place wet grass");
      create_biome_swamp_place_grass_wet(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing wet grass";
      }
    }

    //
    // Place some fungus
    //
    {
      uint32_t start = time_ms();
      dbg2("INF: Place withered fungus");
      create_biome_swamp_place_fungus_withered(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing withered fungus";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place healing fungus");
      create_biome_swamp_place_fungus_healing(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing healing fungus";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place edible fungus");
      create_biome_swamp_place_fungus_edible(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing edible fungus";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place poison fungus");
      create_biome_swamp_place_fungus_poison(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing poison fungus";
      }
    }

    //
    // Place some brownery
    //
    {
      uint32_t start = time_ms();
      dbg2("INF: Place foliage");
      create_biome_swamp_place_foliage(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing foliage";
      }
    }

    //
    // Place some eels etc...
    //
    {
      uint32_t start = time_ms();
      dbg("INF: Place swimming monsters");
      place_swimming_monsters();
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing dry grass";
      }
    }

    dbg2("INF: Place portals");
    place_portals(dungeon);

    delete dungeon;
    break;
  }

  if (g_opt_test_dungeon) {
    dbg("INF: Populated swamp with %u monsters at world map (%d,%d,%d)", monst_count, at.x, at.y, at.z);
  } else {
    dbg("INF: Populated swamp with %u monsters at world map (%d,%d,%d) took %u ms, slowest element took %u ms (%s)",
        monst_count, at.x, at.y, at.z, time_ms() - start, slowest_so_far, slowest_so_far_which.c_str());
  }
  return true;
}

void Level::create_biome_swamp_place_rocks(Dungeonp d, int variant, int block_width, int block_height, int tries)
{
  TRACE_AND_INDENT();
  //
  // Have the same rock type for the level
  //
  auto tp = tp_random_rock();
  if (unlikely(! tp)) {
    ERR("Place rocks failed");
    return;
  }
  auto what = tp->name();

  while (tries-- > 0) {
    auto x = pcg_random_range(0, MAP_WIDTH - block_width + 1);
    auto y = pcg_random_range(0, MAP_HEIGHT - block_height + 1);

    auto can_place_here = true;
    for (auto dx = 0; dx < block_width; dx++) {
      auto X = x + dx;
      for (auto dy = 0; dy < block_height; dy++) {
        auto Y = y + dy;

        if (d->is_oob(X, Y)) {
          continue;
        }

        if (! d->is_rock(X, Y) && ! d->is_wall(X, Y)) {
          can_place_here = false;
          break;
        }

        if (is_rock(X, Y) || is_wall(X, Y)) {
          can_place_here = false;
          continue;
        }
      }

      if (! can_place_here) {
        break;
      }
    }

    if (! can_place_here) {
      continue;
    }

    auto cnt = 1;
    for (auto dy = 0; dy < block_height; dy++) {
      auto Y = y + dy;
      for (auto dx = 0; dx < block_width; dx++) {
        auto X = x + dx;

        auto tilename = what + ".";
        tilename += std::to_string(variant);
        if (! ((block_width == 1) && (block_height == 1))) {
          tilename += ".";
          tilename += std::to_string(block_width);
          tilename += "x";
          tilename += std::to_string(block_height);
          tilename += ".";
          tilename += std::to_string(cnt);
          cnt++;
        }

        auto t = thing_new(what, point(X, Y));
        if (! t) {
          continue;
        }

        auto tile = tile_find(tilename);
        if (unlikely(! tile)) {
          ERR("Rock tile %s not found", tilename.c_str());
          return;
        }

        t->tile_curr = tile->global_index;
      }
    }
  }
}

void Level::create_biome_swamp_place_place_shallow_water(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_shallow_water(x, y)) {
        continue;
      }

      if (! d->is_shallow_water(x, y)) {
        continue;
      }

      (void) thing_new(what, point(x, y));
    }
  }
}

void Level::create_biome_swamp_place_deep_water(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_deep_water(x, y)) {
        continue;
      }

      if (! d->is_deep_water(x, y)) {
        continue;
      }

      (void) thing_new(what, point(x, y));
    }
  }
}

void Level::create_biome_swamp_place_remaining_rocks(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (is_rock(x, y)) {
        continue;
      }

      if (! is_dirt(x, y)) {
        auto tp = tp_random_dirt();
        if (tp) {
          (void) thing_new(tp->name(), point(x, y));
        }
      }

      if (d->is_wall(x, y) || d->is_rock(x, y)) {
        //
        // If any doors are nearby, then we need some rock surrounding the door.
        //
        bool needed        = false;
        int  door_distance = MAP_BORDER_ROCK;
        for (auto dx = -door_distance; dx <= door_distance; dx++) {
          for (auto dy = -door_distance; dy <= door_distance; dy++) {
            if (d->is_oob(x + dx, y + dy)) {
              continue;
            }

            if (d->is_door(x + dx, y + dy)) {
              needed = true;
              break;
            }

            if (d->is_secret_door(x + dx, y + dy)) {
              needed = true;
              break;
            }
          }
          if (needed) {
            break;
          }
        }

        if (needed) {
          (void) thing_new("rock1", point(x, y));
          continue;
        }

        if (d->is_wall(x, y)) {
          if (d100() < 50) {
            (void) thing_new("rock1", point(x, y));
            continue;
          }
        }

        if (d->is_rock(x, y)) {
          (void) thing_new("rock1", point(x, y));
          continue;
        }
      }
    }
  }
}

void Level::create_biome_swamp_place_dirt(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (d->is_floor(x, y) || d->is_dirt(x, y) || d->is_corridor(x, y)) {
        auto tp = tp_random_dirt();
        if (tp) {
          (void) thing_new(tp->name(), point(x, y));
        }

        if (d100() < 20) {
          (void) thing_new("water", point(x, y));
        }
      }
    }
  }
}

void Level::create_biome_swamp_place_foliage(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_foliage(x, y)) {
        continue;
      }
      if (d->is_ascend_dungeon(x, y)) {
        continue;
      }
      if (d->is_descend_dungeon(x, y)) {
        continue;
      }
      if (d->is_floor(x, y)) {
        if (d100() < 50) {
          continue;
        }
      }
      if (d->is_corridor(x, y)) {
        if (d100() < 50) {
          continue;
        }
      }

      //
      // No foliage next to the entrance which obscures the player.
      //
      bool skip              = false;
      int  entrance_distance = MAP_BORDER_AROUND_STAIRS_SMALL - 1;
      for (auto dx = -entrance_distance; dx <= entrance_distance; dx++) {
        for (auto dy = -entrance_distance; dy <= entrance_distance; dy++) {
          if (d->is_ascend_dungeon(x + dx, y + dy)) {
            skip = true;
            break;
          }
          if (d->is_descend_dungeon(x + dx, y + dy)) {
            skip = true;
            break;
          }
        }
        if (skip) {
          break;
        }
      }

      if (skip) {
        continue;
      }
      if (is_rock(x, y)) {
        continue;
      }
      if (is_wall(x, y)) {
        continue;
      }
      auto tp = tp_random_foliage();
      if (unlikely(! tp)) {
        return;
      }

      (void) thing_new(tp->name(), point(x, y));
    }
  }
}

void Level::create_biome_swamp_place_grass_dry(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_rock(x, y)) {
        continue;
      }
      if (d->is_grass_dry(x, y)) {
        auto tp = tp_random_grass_dry();
        if (unlikely(! tp)) {
          return;
        }

        //
        // Omit trampled grass. It is useful to see what things have passed.
        //
        if (tp->is_grass_trampled()) {
          continue;
        }
        if (tp->is_grass_dead()) {
          continue;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::create_biome_swamp_place_grass_wet(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_rock(x, y)) {
        continue;
      }
      if (d->is_grass_wet(x, y)) {
        auto tp = tp_random_grass_wet();
        if (unlikely(! tp)) {
          return;
        }

        //
        // Omit trampled grass. It is useful to see what things have passed.
        //
        if (tp->is_grass_trampled()) {
          continue;
        }
        if (tp->is_grass_dead()) {
          continue;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::create_biome_swamp_place_fungus_withered(Dungeonp d)
{
  TRACE_AND_INDENT();
  //
  // Have the same fungus type for the level
  //
  auto tp = tp_random_fungus_withered();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_rock(x, y)) {
        continue;
      }
      if (d->is_fungus_withered(x, y)) {
        if (unlikely(! tp)) {
          return;
        }

        if (is_fungus(x, y)) {
          continue;
        }

        //
        // Change mushroom type
        //
        if (d100() < 10) {
          tp = tp_random_fungus_withered();
        }
        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::create_biome_swamp_place_fungus_healing(Dungeonp d)
{
  TRACE_AND_INDENT();
  //
  // Have the same fungus type for the level
  //
  auto tp = tp_random_fungus_healing();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_rock(x, y)) {
        continue;
      }
      if (d->is_fungus_healing(x, y)) {
        if (unlikely(! tp)) {
          return;
        }

        if (is_fungus(x, y)) {
          continue;
        }

        //
        // Change mushroom type
        //
        if (d100() < 10) {
          tp = tp_random_fungus_healing();
        }
        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::create_biome_swamp_place_fungus_poison(Dungeonp d)
{
  TRACE_AND_INDENT();
  //
  // Have the same fungus type for the level
  //
  auto tp = tp_random_fungus_poison();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_rock(x, y)) {
        continue;
      }
      if (d->is_fungus_poison(x, y)) {
        if (unlikely(! tp)) {
          return;
        }

        if (is_fungus(x, y)) {
          continue;
        }

        //
        // Change mushroom type
        //
        if (d100() < 10) {
          tp = tp_random_fungus_poison();
        }
        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::create_biome_swamp_place_fungus_edible(Dungeonp d)
{
  TRACE_AND_INDENT();
  //
  // Have the same rock type for the level
  //
  auto tp = tp_random_fungus_edible();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_rock(x, y)) {
        continue;
      }
      if (d->is_fungus_edible(x, y)) {
        if (unlikely(! tp)) {
          return;
        }

        if (is_fungus(x, y)) {
          continue;
        }

        //
        // Change mushroom type
        //
        if (d100() < 10) {
          tp = tp_random_fungus_edible();
        }
        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}
