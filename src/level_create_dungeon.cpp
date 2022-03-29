//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_room.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Level::create_dungeon(point3d at, uint32_t seed)
{
  TRACE_AND_INDENT();
  dbg("INF: Create dungeon");

  if (player) {
    TOPCON("A new dungeon level is coming into being...");
  }

  is_level_type_dungeon = true;

  uint32_t start = time_game_ms();

  while (true) {
    uint32_t start   = time_game_ms();
    auto     dungeon = new Dungeon(MAP_WIDTH, MAP_HEIGHT, DUNGEON_GRID_CHUNK_WIDTH, DUNGEON_GRID_CHUNK_HEIGHT, seed);
    if (dungeon->failed) {
      log("INF: create dungeon, failed, retry");
      seed++;
      delete dungeon;
      continue;
    }

    log("INF: Create dungeon layout took %u ms", time_game_ms() - start);

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

    //
    // The grid is the basis of all reality.
    //
    dbg2("INF: Place the grid");
    place_the_grid();
    if (g_errored) {
      return false;
    }
#if 0
    //
    // Static level
    //
    auto dungeon = new Dungeon(0);
    if (g_errored) { return false; }
#endif
    auto tries = 500;

    auto wall_type = tp_random_wall_dungeon();
    if (! wall_type) {
      ERR("No dungeon walls found");
      return false;
    }

    dbg2("INF: Place random walls");
    create_dungeon_place_walls(dungeon, wall_type, 1, 6, 6, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 2, 6, 6, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 1, 6, 3, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 1, 3, 6, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 1, 3, 3, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 2, 3, 3, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 1, 2, 2, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 2, 2, 2, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 3, 2, 2, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 1, 2, 1, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 2, 2, 1, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 1, 1, 2, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_walls(dungeon, wall_type, 2, 1, 2, tries);
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place random floors");
    {
      auto floor_type = pcg_random_range_inclusive(1, 11);

      int  nloops = 100;
      auto s      = "floor";

      while (nloops--) {
        auto tries = 20;
        create_dungeon_place_floors(dungeon, s, floor_type, 1, 6, 6, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 2, 6, 6, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 1, 6, 3, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 2, 6, 3, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 1, 3, 6, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 2, 3, 6, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 1, 3, 3, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 2, 3, 3, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 3, 3, 3, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 4, 3, 3, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 1, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 2, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 3, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 4, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 5, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 6, 2, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 1, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 2, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 3, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 4, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 5, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 6, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 7, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 8, 2, 1, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 1, 1, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 2, 1, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 3, 1, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, 4, 1, 2, tries);
        if (g_errored) {
          return false;
        }
        create_dungeon_place_floors(dungeon, s, floor_type, pcg_random_range_inclusive(1, 38), 1, 1, tries);
        if (g_errored) {
          return false;
        }
      }

      create_dungeon_place_remaining_floor(dungeon, s + std::to_string(floor_type));
      if (g_errored) {
        return false;
      }
    }

    dbg2("INF: Place corridors");
    create_dungeon_place_corridor(dungeon, "corridor1", 0);
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place bridges");
    create_dungeon_place_bridge(dungeon);
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place rocks");
    create_dungeon_place_rocks(dungeon, 1, 6, 6, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 1, 6, 3, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 1, 3, 6, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 1, 3, 3, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 2, 3, 3, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 1, 2, 2, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 2, 2, 2, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 3, 2, 2, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 1, 2, 1, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 2, 2, 1, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 1, 1, 2, tries);
    if (g_errored) {
      return false;
    }
    create_dungeon_place_rocks(dungeon, 2, 1, 2, tries);
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place remaining rocks");
    create_dungeon_place_remaining_rocks(dungeon, "rock1");
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place remaining walls");
    create_dungeon_place_remaining_walls(dungeon, wall_type->name());
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place dirt");
    place_dirt(dungeon);
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place chasms");
    create_dungeon_place_chasm(dungeon, "chasm1");
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place deep water");
    create_dungeon_place_deep_water(dungeon, "deep_water1");
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place shallow water");
    create_dungeon_place_place_shallow_water(dungeon, "water1");
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place lava");
    create_dungeon_place_lava(dungeon, "lava");
    if (g_errored) {
      return false;
    }

    //
    // Place braziers first and then update the heatmap
    //
    dbg2("INF: Place braziers");
    create_dungeon_place_braziers(dungeon, "brazier");
    if (g_errored) {
      return false;
    }

    //
    // Update the heatmap to avoid placing monsts next to lava
    //
    dbg2("INF: Update heatmap");
    update_heatmap();

    //
    // Items that have no special placement rules
    //
    dbg2("INF: Place items");
    create_dungeon_place_objects_with_normal_placement_rules(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Scary non essential stuff
    //
    dbg2("INF: Place blood");
    create_dungeon_place_random_red_blood(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Less important stuff
    //
    dbg2("INF: Place smoke");
    create_dungeon_place_lava_smoke(dungeon);
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place floor deco");
    place_floor_deco(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Place some pools of blood
    //
    dbg2("INF: Place random floor deco");
    create_dungeon_place_random_floor_deco(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Place some horrible sewers
    //
    dbg2("INF: Place sewer pipes");
    create_dungeon_place_sewer_pipes(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Be evil
    //
    dbg2("INF: Place spiderweb");
    place_spiderweb(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Be nice
    //
    dbg2("INF: Place random treasure");
    place_random_treasure(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Take pity on the player getting close to the dark
    //
    if (player && (player->torch_count() < 3))
      place_random_torches(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Final update of the heatmap to account placement of braziers
    //
    dbg2("INF: Final update heatmap");

    //
    // Make sure and place dry grass after this
    //
    update_heatmap();

    //
    // Place some greenery
    //
    dbg2("INF: Place dry grass");
    place_dry_grass(dungeon);
    if (g_errored) {
      return false;
    }

    dbg2("INF: Place wet grass");
    place_wet_grass(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Place some brownery
    //
    dbg2("INF: Place foilage");
    place_foilage(dungeon);
    if (g_errored) {
      return false;
    }

    delete dungeon;
    break;
  }

  log("INF: Populated dungeon at (%d,%d,%d) took %u ms", at.x, at.y, at.z, time_game_ms() - start);
  return true;
}

void Level::create_dungeon_place_walls(Dungeonp d, Tpp tp, int variant, int block_width, int block_height, int tries)
{
  TRACE_AND_INDENT();
  auto what = tp->name();

  while (tries--) {
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

        auto t    = thing_new(what, point(X, Y));
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

void Level::create_dungeon_place_rocks(Dungeonp d, int variant, int block_width, int block_height, int tries)
{
  TRACE_AND_INDENT();
  auto tp = tp_random_rock();
  if (unlikely(! tp)) {
    ERR("Place rocks failed");
    return;
  }
  auto what = tp->name();

  while (tries--) {
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

        auto t    = thing_new(what, point(X, Y));
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

void Level::create_dungeon_place_floors(Dungeonp d, std::string what, int floor_type, int variant, int block_width,
                                        int block_height, int tries)
{
  TRACE_AND_INDENT();
  while (tries--) {
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

        auto t    = thing_new(new_thing, point(X, Y));
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

void Level::create_dungeon_place_objects_with_normal_placement_rules(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      Tpp tp {};

      //
      // Reset the seed for each cell to increase the chances
      // of repeatability if other small things change in the
      // game
      //
      pcg_srand(seed + x + (y * MAP_WIDTH));

      point p(x, y);

      if (d->is_red_blood(x, y)) {
        tp = tp_random_red_blood();
      }
      if (d->is_door(x, y)) {
        tp = tp_random_door();
      }
      if (d->is_ascend_dungeon(x, y)) {
        tp = tp_random_ascend_dungeon();
      }
      if (d->is_descend_dungeon(x, y)) {
        tp = tp_random_descend_dungeon();
      }
      if (d->is_food(x, y)) {
        tp = tp_random_food();
      }
      if (d->is_gold(x, y)) {
        tp = tp_random_gold();
      }
      if (d->is_key(x, y)) {
        tp = tp_random_key();
      }
      if (d->is_potion(x, y)) {
        tp = tp_random_potion();
      }
      if (d->is_wand_or_staff(x, y)) {
        tp = tp_random_wand_or_staff();
      }
      if (d->is_ring(x, y)) {
        tp = tp_random_ring();
      }
      if (d->is_secret_door(x, y)) {
        tp = tp_random_secret_door();
      }

      if (d->is_monst_class_a(x, y)) {
        if (d1000() < d1000_chance_of_creating_monst_class_a) {
          tp = tp_random_monst_class_a(p);
        }
      }
      if (d->is_monst_class_b(x, y)) {
        if (d1000() < d1000_chance_of_creating_monst_class_b) {
          tp = tp_random_monst_class_b(p);
        }
      }
      if (d->is_monst_class_c(x, y)) {
        if (d1000() < d1000_chance_of_creating_monst_class_c) {
          tp = tp_random_monst_class_c(p);
        }
      }
      if (d->is_monst_class_d(x, y)) {
        if (d1000() < d1000_chance_of_creating_monst_class_d) {
          tp = tp_random_monst_class_d(p);
        }
      }
      if (d->is_monst_class_e(x, y)) {
        if (d1000() < d1000_chance_of_creating_monst_class_e) {
          tp = tp_random_monst_class_e(p);
        }
      }

      //
      // If a hard monst room then always give treasure
      //
      auto r                     = d->getr(x, y);
      bool is_more_generous_room = false;
      if (r) {
        if (r->is_more_generous_room_set) {
          is_more_generous_room = r->is_more_generous_room;
        } else {
          is_more_generous_room        = r->contains(MAP_DEPTH_OBJ, Charmap::DOOR);
          r->is_more_generous_room_set = true;
          r->is_more_generous_room     = is_more_generous_room;
        }
      }

      if (d->is_mob_challenge_class_a(x, y) || d->is_mob_challenge_class_b(x, y)) {
        //
        // If surrounded by hazards then choose an ethereal mob
        //
        if (d->is_hazard(x - 1, y) && d->is_hazard(x + 1, y) && d->is_hazard(x, y - 1) && d->is_hazard(x, y + 1) &&
            d->is_hazard(x - 1, y - 1) && d->is_hazard(x + 1, y - 1) && d->is_hazard(x - 1, y + 1) &&
            d->is_hazard(x + 1, y + 1)) {

          tp = tp_random_ethereal_mob();
        } else {
          //
          // Else choose a normal mob
          //
          if (d->is_mob_challenge_class_a(x, y)) {
            if (d1000() < d1000_chance_of_creating_mob_challenge_class_a) {
              tp = tp_random_mob_challenge_class_a(p);
            }
          }
          if (d->is_mob_challenge_class_b(x, y)) {
            if (d1000() < d1000_chance_of_creating_mob_challenge_class_b) {
              tp = tp_random_mob_challenge_class_b(p);
            }
          }
        }
      }

      if (d->is_barrel(x, y)) {
        tp = tp_random_barrel();
      }

      if (r && r->is_secret) {
        //
        // For secret rooms, be generous and place the good stuff first.
        // We enchant this later after placing.
        //
        if (d->is_treasure_class_a(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_a * 3) {
            tp = tp_random_treasure_class_a(p);
          }
        }
        if (d->is_treasure_class_b(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_b * 3) {
            tp = tp_random_treasure_class_b(p);
          }
        }
        if (d->is_treasure_class_c(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_c * 3) {
            tp = tp_random_treasure_class_c(p);
          }
        }
      } else if (is_more_generous_room) {
        if (d->is_treasure_class_a(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_a * 2) {
            tp = tp_random_treasure_class_a(p);
          }
        }
        if (d->is_treasure_class_b(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_b * 2) {
            tp = tp_random_treasure_class_b(p);
          }
        }
        if (d->is_treasure_class_c(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_c * 2) {
            tp = tp_random_treasure_class_c(p);
          }
        }
      } else {
        if (d->is_treasure_class_a(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_a) {
            tp = tp_random_treasure_class_a(p);
          }
        }
        if (d->is_treasure_class_b(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_b) {
            tp = tp_random_treasure_class_b(p);
          }
        }
        if (d->is_treasure_class_c(x, y)) {
          if (d1000() < d1000_chance_of_creating_treasure_class_c) {
            tp = tp_random_treasure_class_c(p);
          }
        }
      }

      if (r && r->is_secret) {
        //
        // For secret rooms, be generous and place the good stuff first.
        // We enchant this later after placing.
        //
        if (d->is_weapon_class_a(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_a * 3) {
            tp = tp_random_weapon_class_a(p);
          }
        }
        if (d->is_weapon_class_b(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_b * 3) {
            tp = tp_random_weapon_class_b(p);
          }
        }
        if (d->is_weapon_class_c(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_c * 3) {
            tp = tp_random_weapon_class_c(p);
          }
        }
      } else if (is_more_generous_room) {
        if (d->is_weapon_class_a(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_a * 2) {
            tp = tp_random_weapon_class_a(p);
          }
        }
        if (d->is_weapon_class_b(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_b * 2) {
            tp = tp_random_weapon_class_b(p);
          }
        }
        if (d->is_weapon_class_c(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_c * 2) {
            tp = tp_random_weapon_class_c(p);
          }
        }
      } else {
        if (d->is_weapon_class_a(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_a) {
            tp = tp_random_weapon_class_a(p);
          }
        }
        if (d->is_weapon_class_b(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_b) {
            tp = tp_random_weapon_class_b(p);
          }
        }
        if (d->is_weapon_class_c(x, y)) {
          if (d1000() < d1000_chance_of_creating_weapon_class_c) {
            tp = tp_random_weapon_class_c(p);
          }
        }
      }

      if (d->is_enchantstone(x, y)) {
        tp = tp_random_enchantstone();
      }

      if (d->is_skillstone(x, y)) {
        tp = tp_random_skillstone();
      }

      if (unlikely(! tp)) {
        continue;
      }

      if (! tp->is_biome_dungeon()) {
        // fix when swamp added
        log("INF: Dropping %s for dungeon biome", tp->name().c_str());
        continue;
      }

      //
      // Don't place items where they would catch fire immediately.
      //
      if (heatmap(x, y)) {
        if (tp->is_very_combustible()) {
          continue;
        }
      }

      if (heatmap(x, y) > 2) {
        if (tp->is_combustible()) {
          continue;
        }
      }

      dbg("INF: Creating %s", tp->name().c_str());
      auto t = thing_new(tp->name(), point(x, y));
      if (t) {
        if (t->is_weapon()) {
          if (r && r->is_secret) {
            t->enchant_randomly();
          }
          dbg("INF: Placed weapon '%s'", t->short_text_capitalise().c_str());
        } else if (t->is_treasure_type()) {
          if (r && r->is_secret) {
            t->enchant_randomly();
          }
          dbg("INF: Placed treasure '%s'", t->short_text_capitalise().c_str());
        } else if (t->is_bag()) {
          dbg("INF: Placed '%s'", t->short_text_capitalise().c_str());
        } else if (t->is_monst()) {
          //
          // Already logged
          //
          // dbg("INF: Placed random monster '%s'", t->short_text_capitalise().c_str());
        } else {
          //
          // Doors etc... don't log, not as interesting
          //
        }
      }
    }
  }
}

void Level::create_dungeon_place_lava(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_lava(x, y)) {
        continue;
      }

      if (! d->is_lava(x, y)) {
        continue;
      }

      (void) thing_new(what, point(x, y));
    }
  }
}

void Level::create_dungeon_place_lava_smoke(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! is_lava(x, y)) {
        continue;
      }

      //
      // Place smoke over lava but not if next to water as it will
      // just boil off anyway
      //
      if (pcg_random_range(0, 100) < 20) {
        for (auto dx = -2; dx <= 2; dx++) {
          for (auto dy = -2; dy <= 2; dy++) {
            if (is_shallow_water(x + dx, y + dy)) {
              goto next;
            }
            if (is_deep_water(x + dx, y + dy)) {
              goto next;
            }
          }
        }
        thing_new("smoke", point(x, y));
      }
    next:
      continue;
    }
  }
}

void Level::create_dungeon_place_chasm(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_chasm(x, y)) {
        continue;
      }

      if (! d->is_chasm(x, y)) {
        continue;
      }

      (void) thing_new(what, point(x, y));
    }
  }
}

void Level::create_dungeon_place_braziers(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_brazier(x, y)) {
        continue;
      }

      if (! d->is_brazier(x, y)) {
        continue;
      }

      (void) thing_new(what, point(x, y));
    }
  }
}

void Level::create_dungeon_place_random_red_blood(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_red_blood(x, y)) {
        continue;
      }

      if (! d->is_floor(x, y) || ! d->is_floor(x - 1, y) || ! d->is_floor(x + 1, y) || ! d->is_floor(x, y - 1) ||
          ! d->is_floor(x, y + 1) || ! d->is_floor(x - 1, y - 1) || ! d->is_floor(x + 1, y - 1) ||
          ! d->is_floor(x - 1, y + 1) || ! d->is_floor(x + 1, y + 1)) {
        continue;
      }

      if (d->is_hazard(x, y) || d->is_hazard(x - 1, y) || d->is_hazard(x + 1, y) || d->is_hazard(x, y - 1) ||
          d->is_hazard(x, y + 1) || d->is_hazard(x - 1, y - 1) || d->is_hazard(x + 1, y - 1) ||
          d->is_hazard(x - 1, y + 1) || d->is_hazard(x + 1, y + 1)) {
        continue;
      }

      if (pcg_random_range(0, 1000) > 50) {
        continue;
      }

      auto tp = tp_random_red_blood();
      (void) thing_new(tp->name(), point(x, y));
    }
  }
}

void Level::create_dungeon_place_place_shallow_water(Dungeonp d, const std::string &what)
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

void Level::create_dungeon_place_deep_water(Dungeonp d, const std::string &what)
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
        (void) thing_new("dirt3", point(x, y));
      }
    }
  }
}

void Level::place_floor_deco(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_floor(x, y)) {
        continue;
      }

      if (! d->is_floor_deco_at(x, y)) {
        continue;
      }

      if (d->is_food(x, y) || d->is_red_blood(x, y) || d->is_door(x, y) || d->is_ascend_dungeon(x, y) ||
          d->is_descend_dungeon(x, y) || d->is_mob_any(x, y) || d->is_key(x, y) || d->is_potion(x, y) ||
          d->is_barrel(x, y) || d->is_wand_or_staff(x, y) || d->is_ring(x, y) || d->is_secret_door(x, y) ||
          d->is_weapon_class_a(x, y) || d->is_weapon_class_b(x, y) || d->is_treasure_type(x, y) ||
          d->is_treasure_class_a(x, y) || d->is_treasure_class_b(x, y) || d->is_treasure_class_c(x, y) ||
          d->is_monst_any(x, y)) {
        continue;
      }

      //
      // Reset the seed for each cell to increase the chances
      // of repeatability if other small things change in the
      // game
      //
      pcg_srand(seed + x + (y * MAP_WIDTH));

      auto tp = tp_random_deco();
      if (unlikely(! tp)) {
        return;
      }

      thing_new(tp->name(), point(x, y));
    }
  }
}

void Level::create_dungeon_place_random_floor_deco(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_floor(x, y)) {
        continue;
      }

      if (d->is_floor_deco_at(x, y)) {
        continue;
      }

      if (pcg_random_range(0, 100) < 99) {
        continue;
      }

      if (d->is_food(x, y) || d->is_red_blood(x, y) || d->is_door(x, y) || d->is_ascend_dungeon(x, y) ||
          d->is_descend_dungeon(x, y) || d->is_mob_any(x, y) || d->is_key(x, y) || d->is_potion(x, y) ||
          d->is_barrel(x, y) || d->is_wand_or_staff(x, y) || d->is_ring(x, y) || d->is_secret_door(x, y) ||
          d->is_weapon_class_a(x, y) || d->is_weapon_class_b(x, y) || d->is_treasure_type(x, y) ||
          d->is_treasure_class_a(x, y) || d->is_treasure_class_b(x, y) || d->is_treasure_class_c(x, y) ||
          d->is_monst_any(x, y)) {
        continue;
      }

      if (! d->is_floor(x - 1, y) || ! d->is_floor(x + 1, y) || ! d->is_floor(x, y - 1) || ! d->is_floor(x, y + 1) ||
          ! d->is_floor(x - 1, y - 1) || ! d->is_floor(x + 1, y - 1) || ! d->is_floor(x - 1, y + 1) ||
          ! d->is_floor(x + 1, y + 1)) {
        continue;
      }

      if (d->is_hazard(x, y) || d->is_hazard(x - 1, y) || d->is_hazard(x + 1, y) || d->is_hazard(x, y - 1) ||
          d->is_hazard(x, y + 1) || d->is_hazard(x - 1, y - 1) || d->is_hazard(x + 1, y - 1) ||
          d->is_hazard(x - 1, y + 1) || d->is_hazard(x + 1, y + 1)) {
        continue;
      }

      //
      // Reset the seed for each cell to increase the chances
      // of repeatability if other small things change in the
      // game
      //
      pcg_srand(seed + x + (y * MAP_WIDTH));

      auto tp = tp_random_deco();
      if (unlikely(! tp)) {
        return;
      }

      //
      // Don't place items where they would catch fire immediately.
      //
      if (heatmap(x, y)) {
        if (tp->is_very_combustible()) {
          continue;
        }
      }

      if (heatmap(x, y) > 2) {
        if (tp->is_combustible()) {
          continue;
        }
      }

      thing_new(tp->name(), point(x, y));
    }
  }
}

void Level::create_dungeon_place_sewer_pipes(Dungeonp d)
{
  TRACE_AND_INDENT();
  //
  // Sometimes we have sewer pipes
  //
  auto r = pcg_random_range(0, 100);
  if (r < 80) {
    return;
  }

  int  sewer_count        = 0;
  int  min_sewer_dist     = 10;
  int  sewer_count_target = 2 + pcg_random_range(0, 5);
  auto tries              = 10000;

  while (sewer_count < sewer_count_target) {
  redo:
    if (! tries--) {
      return;
    }

    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK + 1);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK + 1);

    if (d->is_wall(x, y)) {
      continue;
    }

    if (d->is_rock(x, y)) {
      continue;
    }

    if (! d->is_floor(x, y) || ! d->is_floor(x - 1, y) || ! d->is_floor(x + 1, y) || ! d->is_floor(x, y - 1) ||
        ! d->is_floor(x, y + 1) || ! d->is_floor(x - 1, y - 1) || ! d->is_floor(x + 1, y - 1) ||
        ! d->is_floor(x - 1, y + 1) || ! d->is_floor(x + 1, y + 1)) {
      continue;
    }

    if (d->is_hazard(x, y) || d->is_hazard(x - 1, y) || d->is_hazard(x + 1, y) || d->is_hazard(x, y - 1) ||
        d->is_hazard(x, y + 1) || d->is_hazard(x - 1, y - 1) || d->is_hazard(x + 1, y - 1) ||
        d->is_hazard(x - 1, y + 1) || d->is_hazard(x + 1, y + 1)) {
      continue;
    }

    if (d->is_ascend_dungeon(x, y) || d->is_ascend_dungeon(x - 1, y) || d->is_ascend_dungeon(x + 1, y) ||
        d->is_ascend_dungeon(x, y - 1) || d->is_ascend_dungeon(x, y + 1) || d->is_ascend_dungeon(x - 1, y - 1) ||
        d->is_ascend_dungeon(x + 1, y - 1) || d->is_ascend_dungeon(x - 1, y + 1) ||
        d->is_ascend_dungeon(x + 1, y + 1)) {
      continue;
    }

    if (d->is_descend_dungeon(x, y) || d->is_descend_dungeon(x - 1, y) || d->is_descend_dungeon(x + 1, y) ||
        d->is_descend_dungeon(x, y - 1) || d->is_descend_dungeon(x, y + 1) || d->is_descend_dungeon(x - 1, y - 1) ||
        d->is_descend_dungeon(x + 1, y - 1) || d->is_descend_dungeon(x - 1, y + 1) ||
        d->is_descend_dungeon(x + 1, y + 1)) {
      continue;
    }

    for (auto dx = -min_sewer_dist; dx < min_sewer_dist; dx++) {
      auto X = x + dx;
      for (auto dy = -min_sewer_dist; dy < min_sewer_dist; dy++) {
        auto Y = y + dy;

        if (d->is_oob(X, Y)) {
          continue;
        }

        if (is_descend_sewer(X, Y)) {
          goto redo;
        }
      }
    }

    //
    // Reset the seed for each cell to increase the chances
    // of repeatability if other small things change in the
    // game
    //
    pcg_srand(seed + x + (y * MAP_WIDTH));

    auto tp = tp_random_descend_sewer();
    if (unlikely(! tp)) {
      return;
    }

    thing_new(tp->name(), point(x, y));
    sewer_count++;
  }
}

void Level::create_dungeon_place_remaining_floor(Dungeonp d, const std::string &what)
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

void Level::create_dungeon_place_corridor(Dungeonp d, const std::string what, int floor_type)
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

void Level::create_dungeon_place_bridge(Dungeonp d)
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

void Level::place_dirt(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_anything_at(x, y) || d->is_dirt(x, y)) {
        auto tp = tp_random_dirt();
        if (unlikely(! tp)) {
          return;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::place_random_treasure(Dungeonp d)
{
  TRACE_AND_INDENT();
  int tries        = 1000;
  int treasure_max = pcg_random_range(1, 10);

  while (tries--) {
    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK);

    if (d->is_dirt(x, y) || d->is_weapon_class_a(x, y) || d->is_weapon_class_b(x, y) || d->is_weapon_class_c(x, y) ||
        d->is_treasure_class_a(x, y) || d->is_treasure_class_b(x, y) || d->is_treasure_class_c(x, y) ||
        d->is_deep_water(x, y) || d->is_spiderweb(x, y) || d->is_foilage(x, y)) {
      auto tp = tp_random_treasure();
      if (unlikely(! tp)) {
        return;
      }

      if (tp->is_torch()) {
        if (d->is_deep_water(x, y) || d->is_foilage(x, y)) {
          continue;
        }
      }

      //
      // Be nice and enchant this lost treasure.
      //
      auto t = thing_new(tp->name(), point(x, y));
      if (pcg_random_range(0, 100) < 20) {
        t->enchant_randomly();
      }

      //
      // Double enchant swords in lakes :)
      //
      if (t->is_sword()) {
        if (d->is_shallow_water(x, y)) {
          t->enchant_randomly();
        }

        if (d->is_deep_water(x, y)) {
          t->enchant_randomly();
        }
      }

      dbg("INF: Placed random item '%s'", t->short_text_capitalise().c_str());

      if (treasure_max-- < 0) {
        return;
      }
    }
  }
}

void Level::place_random_torches(Dungeonp d)
{
  TRACE_AND_INDENT();
  int tries     = 1000;
  int torch_max = pcg_random_range(1, 10);

  while (tries--) {
    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK);

    if (d->is_dirt(x, y) || d->is_weapon_class_a(x, y) || d->is_weapon_class_b(x, y) || d->is_weapon_class_c(x, y) ||
        d->is_treasure_class_a(x, y) || d->is_treasure_class_b(x, y) || d->is_treasure_class_c(x, y) ||
        d->is_deep_water(x, y) || d->is_spiderweb(x, y) || d->is_foilage(x, y)) {

      if (d->is_deep_water(x, y) || d->is_foilage(x, y)) {
        continue;
      }

      //
      // Be nice and enchant this lost treasure.
      //
      (void) thing_new("torch", point(x, y));

      dbg("INF: Placed random torch");
      if (torch_max-- < 0) {
        return;
      }
    }
  }
}

void Level::place_dry_grass(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_anything_at(x, y) || d->is_dry_grass(x, y)) {
        auto tp = tp_random_dry_grass();
        if (unlikely(! tp)) {
          return;
        }

        if (heatmap(x, y)) {
          continue;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::place_wet_grass(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_anything_at(x, y) || d->is_wet_grass(x, y)) {
        auto tp = tp_random_wet_grass();
        if (unlikely(! tp)) {
          return;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::place_foilage(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_anything_at(x, y) || d->is_foilage(x, y)) {
        auto tp = tp_random_foilage();
        if (unlikely(! tp)) {
          return;
        }

        if (heatmap(x, y)) {
          continue;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::place_spiderweb(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_anything_at(x, y) || d->is_spiderweb(x, y)) {
        auto tp = tp_random_spiderweb();
        if (unlikely(! tp)) {
          return;
        }

        if (! tp->normal_placement_rules()) {
          continue;
        }

        if (heatmap(x, y)) {
          continue;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::create_dungeon_place_remaining_walls(Dungeonp d, const std::string &what)
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

void Level::create_dungeon_place_remaining_rocks(Dungeonp d, const std::string &what)
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
