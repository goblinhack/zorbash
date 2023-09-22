//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Level::create_biome_flooded(point3d at, uint32_t seed)
{
  TRACE_AND_INDENT();
  dbg("INF: Create biome water");

  biome = BIOME_FLOODED;

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
        = new Dungeon(biome, MAP_WIDTH, MAP_HEIGHT, DUNGEON_GRID_CHUNK_WIDTH, DUNGEON_GRID_CHUNK_HEIGHT, seed);
    if (dungeon->failed) {
      log("INF: create dungeon, failed, retry");
      seed++;
      delete dungeon;
      continue;
    }

    if (! g_opt_test_dungeon) {
      log("INF: Create dungeon layout took %u ms", time_ms() - start);
    }

    //
    // Check we have a dungeon start
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
      ERR("Did not find dungeon entrance");
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

#if 0
    //
    // Static level
    //
    auto dungeon = new Dungeon(0);
    if (g_errored) { return false; }
#endif

    int  tries     = 500;
    auto wall_type = tp_random_wall_dungeon();
    if (! wall_type) {
      ERR("No dungeon walls found");
      return false;
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place random walls");
      create_biome_flooded_place_walls(dungeon, wall_type, 1, 6, 6, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 2, 6, 6, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 1, 6, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 1, 3, 6, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 1, 3, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 2, 3, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 1, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 2, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 3, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 1, 2, 1, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 2, 2, 1, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 1, 1, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_walls(dungeon, wall_type, 2, 1, 2, tries);
      if (g_errored) {
        return false;
      }

      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing the walls";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place random floors");
      auto floor_type = pcg_random_range_inclusive(1, 11);

      int  nloops = 100;
      auto s      = "floor";

      while (nloops--) {
        auto tries = 20;
        create_biome_flooded_place_floors(dungeon, s, floor_type, 1, 6, 6, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 2, 6, 6, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 1, 6, 3, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 2, 6, 3, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 1, 3, 6, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 2, 3, 6, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 1, 3, 3, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 2, 3, 3, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 3, 3, 3, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 4, 3, 3, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 1, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 2, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 3, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 4, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 5, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 6, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 1, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 2, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 3, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 4, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 5, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 6, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 7, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 8, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 1, 1, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 2, 1, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 3, 1, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, 4, 1, 2, tries);
        if (g_errored) {
          return false;
        }
        create_biome_flooded_place_floors(dungeon, s, floor_type, pcg_random_range_inclusive(1, 38), 1, 1, tries);
        if (g_errored) {
          return false;
        }
      }

      create_biome_flooded_place_remaining_floor(dungeon, s + std::to_string(floor_type));
      if (g_errored) {
        return false;
      }

      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing the floor";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place corridors");
      create_biome_flooded_place_corridor(dungeon, "corridor1", 0);
      if (g_errored) {
        return false;
      }

      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing the corridors";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place bridges");
      create_biome_flooded_place_bridge(dungeon);
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing bridges";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place rocks");
      create_biome_flooded_place_rocks(dungeon, 1, 6, 6, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 1, 6, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 1, 3, 6, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 1, 3, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 2, 3, 3, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 1, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 2, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 3, 2, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 1, 2, 1, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 2, 2, 1, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 1, 1, 2, tries);
      if (g_errored) {
        return false;
      }
      create_biome_flooded_place_rocks(dungeon, 2, 1, 2, tries);
      if (g_errored) {
        return false;
      }

      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing rocks";
      }
    }

    dbg2("INF: Place remaining rocks");
    create_biome_flooded_place_remaining_rocks(dungeon, "rock1");
    if (g_errored) {
      return false;
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place remaining walls");
      create_biome_flooded_place_remaining_walls(dungeon, wall_type->name());
      if (g_errored) {
        return false;
      }
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "placing remaining walls";
      }
    }

    {
      uint32_t start = time_ms();
      dbg2("INF: Place dirt");
      place_dirt(dungeon);
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
      create_biome_flooded_place_deep_water(dungeon, "deep_water");
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
      create_biome_flooded_place_place_shallow_water(dungeon, "water");
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
    // Update the heatmap to avoid placing monsters next to lava
    //
    {
      uint32_t start = time_ms();
      dbg2("INF: Update heatmap");
      update_heatmap();
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "heatmap calc";
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
    // Final update of the heatmap to account placement of braziers
    //
    dbg2("INF: Final update heatmap");

    //
    // Make sure and place dry grass after this
    //
    {
      uint32_t start = time_ms();
      update_heatmap();
      uint32_t took = time_ms() - start;
      if (took > slowest_so_far) {
        slowest_so_far       = took;
        slowest_so_far_which = "updating the heatmap again";
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
        slowest_so_far_which = "placing swimming monsters";
      }
    }

    dbg2("INF: Place portals");
    place_portals(dungeon);

    delete dungeon;
    break;
  }

  if (g_opt_test_dungeon) {
    dbg("INF: Populated dungeon with %u monsters at world map (%d,%d,%d)", monst_count, at.x, at.y, at.z);
  } else {
    dbg("INF: Populated dungeon with %u monsters at world map (%d,%d,%d) took %u ms, slowest element took %u ms (%s)",
        monst_count, at.x, at.y, at.z, time_ms() - start, slowest_so_far, slowest_so_far_which.c_str());
  }
  return true;
}

void Level::create_biome_flooded_place_walls(Dungeonp d, Tpp tp, int variant, int block_width, int block_height,
                                             int tries)
{
  TRACE_AND_INDENT();
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

        if (! d->is_wall_no_check(X, Y)) {
          can_place_here = false;
          break;
        }

        //
        // We place large blocks and avoid splatting them with
        // smaller ones here.
        //
        if (is_wall(X, Y)) {
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
          ERR("Wall tile %s not found", tilename.c_str());
          return;
        }

        t->tile_curr = tile->global_index;

        //
        // Need this so we can display chasms under walls
        //
        (void) thing_new("wall_floor1", point(X, Y));
      }
    }
  }
}

void Level::create_biome_flooded_place_rocks(Dungeonp d, int variant, int block_width, int block_height, int tries)
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

        if (! d->is_rock(X, Y)) {
          can_place_here = false;
          break;
        }

        //
        // We place large blocks and avoid splatting them with
        // smaller ones here.
        //
        if (is_wall(X, Y)) {
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

        //
        // Need this so we can display chasms under walls
        //
        (void) thing_new("wall_floor1", point(X, Y));
      }
    }
  }
}

void Level::create_biome_flooded_place_floors(Dungeonp d, std::string what, int floor_type, int variant,
                                              int block_width, int block_height, int tries)
{
  TRACE_AND_INDENT();
  while (tries-- > 0) {
    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK - block_width + 1);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK - block_height + 1);

    //
    // Place bridges instead of floor, if we have multiple bridge
    // neighbors. This allows items to be placed on bridges.
    //
    auto bridge_count = 0;
    if ((block_width == 1) && (block_height == 1)) {
      bridge_count += d->is_bridge(x - 1, y);
      bridge_count += d->is_bridge(x + 1, y);
      bridge_count += d->is_bridge(x, y - 1);
      bridge_count += d->is_bridge(x, y + 1);
    }

    auto can_place_here = true;
    for (auto dx = 0; dx < block_width; dx++) {
      auto X = x + dx;
      for (auto dy = 0; dy < block_height; dy++) {
        auto Y = y + dy;

        if (d->is_oob(X, Y)) {
          continue;
        }

        if (! d->is_floor(X, Y)) {
          can_place_here = false;
          break;
        }

        if (is_floor(x, y)) {
          can_place_here = false;
          continue;
        }

        //
        // We place large blocks and avoid splatting them with
        // smaller ones here.
        //
        if (is_floor(X, Y)) {
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

    if (bridge_count > 1) {
      if ((block_width == 1) && (block_height == 1)) {
        if (bridge_count > 2) {
          (void) thing_new("bridge_x", point(x, y));
          continue;
        }

        if (d->is_bridge(x, y - 1) || d->is_bridge(x, y + 1)) {
          (void) thing_new("bridge_ud", point(x, y));
          continue;
        }

        if (d->is_bridge(x - 1, y) || d->is_bridge(x + 1, y)) {
          (void) thing_new("bridge_lr", point(x, y));
          continue;
        }
      }
    }

    auto cnt = 1;
    for (auto dy = 0; dy < block_height; dy++) {
      auto Y = y + dy;
      for (auto dx = 0; dx < block_width; dx++) {
        auto X = x + dx;

        auto new_thing = what + std::to_string(floor_type);
        auto tilename  = new_thing + ".";

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

        auto t = thing_new(new_thing, point(X, Y));
        if (! t) {
          continue;
        }

        auto tile = tile_find(tilename);
        if (unlikely(! tile)) {
          ERR("Floor tile %s not found", tilename.c_str());
          return;
        }

        t->tile_curr = tile->global_index;
      }
    }
  }
}

void Level::create_biome_flooded_place_place_shallow_water(Dungeonp d, const std::string &what)
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

      if (! d->is_floor(x, y)) {
        (void) thing_new("dirt2", point(x, y));
      }
    }
  }
}

void Level::create_biome_flooded_place_deep_water(Dungeonp d, const std::string &what)
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

      if (! d->is_floor(x, y)) {
        (void) thing_new("dirt2", point(x, y));
      }
    }
  }
}

void Level::create_biome_flooded_place_remaining_floor(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_floor(x, y)) {
        continue;
      }

      if (is_floor(x, y)) {
        continue;
      }

      //
      // Place bridges instead of floor, if we have multiple bridge
      // neighbors. This allows items to be placed on bridges.
      //
      auto bridge_count = 0;
      bridge_count += d->is_bridge(x - 1, y);
      bridge_count += d->is_bridge(x + 1, y);
      bridge_count += d->is_bridge(x, y - 1);
      bridge_count += d->is_bridge(x, y + 1);

      if (bridge_count > 1) {
        if (bridge_count > 2) {
          (void) thing_new("bridge_x", point(x, y));
          continue;
        }

        if (d->is_bridge(x, y - 1) || d->is_bridge(x, y + 1)) {
          (void) thing_new("bridge_ud", point(x, y));
          continue;
        }

        if (d->is_bridge(x - 1, y) || d->is_bridge(x + 1, y)) {
          (void) thing_new("bridge_lr", point(x, y));
          continue;
        }
      }

      thing_new(what, point(x, y));
    }
  }
}

void Level::create_biome_flooded_place_corridor(Dungeonp d, const std::string what, int floor_type)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_corridor(x, y) && ! d->is_secret_corridor_at(x, y)) {
        continue;
      }

      (void) thing_new(what, point(x, y));
    }
  }
}

void Level::create_biome_flooded_place_bridge(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (d->is_bridge(x, y)) {
        auto bridge_count = 0;
        bridge_count += d->is_bridge(x - 1, y);
        bridge_count += d->is_bridge(x + 1, y);
        bridge_count += d->is_bridge(x, y - 1);
        bridge_count += d->is_bridge(x, y + 1);

        if (bridge_count > 2) {
          (void) thing_new("bridge_x", point(x, y));
          continue;
        }

        if (d->is_bridge(x, y - 1) || d->is_bridge(x, y + 1)) {
          (void) thing_new("bridge_ud", point(x, y));
          continue;
        }

        if (d->is_bridge(x - 1, y) || d->is_bridge(x + 1, y)) {
          (void) thing_new("bridge_lr", point(x, y));
          continue;
        }
      }
    }
  }
}

void Level::create_biome_flooded_place_remaining_walls(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_rock(x, y) || is_wall(x, y)) {
        continue;
      }

      if (! d->is_rock(x, y) && ! d->is_wall(x, y)) {
        continue;
      }

      if (pcg_random_range(0, 100) < 50) {
        continue;
      }

      (void) thing_new(what, point(x, y));

      //
      // Need this so we can display chasms under walls
      //
      (void) thing_new("wall_floor1", point(x, y));
    }
  }
}

void Level::create_biome_flooded_place_remaining_rocks(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (is_rock(x, y) || is_wall(x, y)) {
        continue;
      }

      if (! d->is_rock(x, y) && ! d->is_wall(x, y)) {
        continue;
      }

      (void) thing_new(what, point(x, y));

      //
      // Need this so we can display chasms under walls
      //
      (void) thing_new("wall_floor1", point(x, y));
    }
  }
}
