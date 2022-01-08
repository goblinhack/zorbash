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

bool Level::create_dungeon(point3d at, int seed)
{
  TRACE_AND_INDENT();
  dbg("DGN: Create dungeon at (%d,%d,%d)", at.x, at.y, at.z);

  if (player) {
    TOPCON("A new dungeon level is coming into being...");
  }

  is_level_type_dungeon = true;

  uint32_t start = time_get_time_ms();

  while (true) {
    uint32_t start   = time_get_time_ms();
    auto     dungeon = new Dungeon(MAP_WIDTH, MAP_HEIGHT, DUNGEON_GRID_CHUNK_WIDTH, DUNGEON_GRID_CHUNK_HEIGHT, seed);
    if (dungeon->failed) {
      log("DGN: create dungeon, failed, retry");
      seed++;
      delete dungeon;
      continue;
    }

    log("DGN: Create dungeon layout (%d,%d,%d) took %u ms", at.x, at.y, at.z, time_get_time_ms() - start);

    //
    // Check we have a dungeon start
    //
    dbg2("DGN: Look for entrance");
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
    dbg2("DGN: Place the grid");
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

    dbg2("DGN: Place random walls");
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

    dbg2("DGN: Place random floors");
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

    dbg2("DGN: Place corridors");
    create_dungeon_place_corridor(dungeon, "corridor1", 0);
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place bridges");
    create_dungeon_place_bridge(dungeon);
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place rocks");
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

    dbg2("DGN: Place remaining rocks");
    create_dungeon_place_remaining_rocks(dungeon, "rock1");
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place remaining walls");
    create_dungeon_place_remaining_walls(dungeon, wall_type->name());
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place dirt");
    place_dirt(dungeon);
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place chasms");
    create_dungeon_place_chasm(dungeon, "chasm1");
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place deep water");
    create_dungeon_place_deep_water(dungeon, "deep_water1");
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place shallow water");
    create_dungeon_place_place_shallow_water(dungeon, "water1");
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place lava");
    create_dungeon_place_lava(dungeon, "lava1");
    if (g_errored) {
      return false;
    }

    //
    // Place braziers first and then update the heatmap
    //
    dbg2("DGN: Place braziers");
    create_dungeon_place_braziers(dungeon, "brazier1");
    if (g_errored) {
      return false;
    }

    //
    // Update the heatmap to avoid placing monsts next to lava
    //
    dbg2("DGN: Update heatmap");
    update_heatmap();

    //
    // Place the player if we do not have one.
    //
    if (0)
      if (! game->level) {
        dbg2("DGN: Place player");
        for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
          for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (dungeon->is_ascend_dungeon(x, y)) {
              auto t = thing_new("player2", point(x, y));
              {
                auto W = thing_new("wand_lightning", point(x, y));
                t->carry(W);
                t->enchant_without_stone(W);
              }

              {
#if 0
              for (auto m = 0; m < 500; m++) {
                auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK);
                auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK);
                if (is_floor(x, y)) {
                  thing_new("jelly_baby", point(x, y));
                }
              }
#endif
              }
              IF_DEBUG2
              {
                thing_new("spiderweb", point(x + 3, y));
                thing_new("armor_lather", point(x, y - 2));
                thing_new("shield_woodon", point(x + 1, y - 3));
                thing_new("shield_wooden", point(x, y - 3));
                thing_new("fire", point(x - 1, y + 1));
                thing_new("food_frog", point(x, y + 1));
                // thing_new("thunderstone", point(x - 1, y - 1));
                // thing_new("treasure_map", point(x - 1, y - 2));
                // thing_new("beast_map", point(x + 1, y - 2));
                // thing_new("fire", point(x + 2, y - 2));
                // thing_new("zorblin", point(x + 1, y));
                // thing_new("zorb_pack", point(x + 2, y));
#if 0
              thing_new("jelly_baby", point(x + 3, y - 1));
              thing_new("jelly_baby", point(x + 4, y));
              thing_new("jelly_baby", point(x + 5, y));
              thing_new("jelly_baby", point(x + 6, y));
#endif
#if 0
            auto w = thing_new("scythe", point(x, y));
            t->carry(w);

            {
              auto p = thing_new("pot_health", point(x, y));
              t->carry(p);
            }
            {
              auto b = thing_new("food_frog", point(x, y));
              t->carry(b);
            }
#endif

#if 0
            {
              thing_new("sword1_wood", point(x + 1, y));
            }

            {
              thing_new("ring_poison_resist", point(x + 2, y));
            }
#endif

                {
                  auto f = thing_new("enchantstone", point(x, y));
                  t->carry(f);
                }

                {
                  auto f = thing_new("skillstone", point(x, y));
                  t->carry(f);
                }

                {
                  auto W = thing_new("wand_descent", point(x, y));
                  t->carry(W);
                }
                {
                  auto W = thing_new("wand_lightning", point(x, y));
                  t->carry(W);
                }
#if 0
            auto w2 = thing_new("sword_rusty_basic", point(x, y));
            t->carry(w2);


            {
              auto b = thing_new("food_frog", point(x, y));
              t->carry(b);
            }

            {
              auto b = thing_new("chest1", point(x, y));
              t->carry(b);
            }

            {
              auto f = thing_new("skillstone", point(x, y));
              t->carry(f);
            }

            {
              auto p = thing_new("pot_health", point(x, y));
              t->carry(p);
            }



            {
              auto W = thing_new("wand_fire", point(x, y));
              t->carry(W);
            }

            {
              auto W = thing_new("key", point(x, y));
              t->carry(W);
            }
#endif
                {
                  auto W = thing_new("ring_poison_resist", point(x, y));
                  t->carry(W);
                }

                {
                  auto W = thing_new("ring_poison_resist", point(x, y));
                  t->carry(W);
                }

                {
                  auto W = thing_new("key", point(x, y));
                  t->carry(W);
                }
              }

              {
                auto w3 = thing_new("sword1_wood", point(x, y));
                t->carry(w3);
              }

              {
                auto w3 = thing_new("axe", point(x, y));
                t->carry(w3);
              }

              {
                auto W = thing_new("torch", point(x, y));
                t->carry(W);
              }
              if (0) {
                auto i = thing_new("thunderstone", point(x, y));
                t->carry(i);
              }
              if (1) {
                auto b = thing_new("bag_s", point(x, y));
                t->carry(b);
              }

              goto placed_player;
            }
          }
        }
      }

  placed_player:
    //
    // Items that have no special placement rules
    //
    dbg2("DGN: Place items");
    create_dungeon_place_objects_with_normal_placement_rules(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Scary non essential stuff
    //
    dbg2("DGN: Place blood");
    create_dungeon_place_random_blood(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Less important stuff
    //
    dbg2("DGN: Place smoke");
    create_dungeon_place_lava_smoke(dungeon);
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place floor deco");
    place_floor_deco(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Place some pools of blood
    //
    dbg2("DGN: Place random floor deco");
    create_dungeon_place_random_floor_deco(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Place some horrible sewers
    //
    dbg2("DGN: Place sewer pipes");
    create_dungeon_place_sewer_pipes(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Be evil
    //
    dbg2("DGN: Place spiderweb");
    place_spiderweb(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Be nice
    //
    dbg2("DGN: Place random treasure");
    place_random_treasure(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Take pity on the player getting close to the dark
    //
    if (player && (player->get_torch_count() < 3))
      place_random_torches(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Zoom the map to the player
    //
    if (player) {
      dbg2("DGN: Scroll to player");
      scroll_map_to_player();
      if (g_errored) {
        return false;
      }
    }

    //
    // Final update of the heatmap to account placement of braziers
    //
    dbg2("DGN: Final update heatmap");

    //
    // Make sure and place dry grass after this
    //
    update_heatmap();

    //
    // Place some greenery
    //
    dbg2("DGN: Place dry grass");
    place_dry_grass(dungeon);
    if (g_errored) {
      return false;
    }

    dbg2("DGN: Place wet grass");
    place_wet_grass(dungeon);
    if (g_errored) {
      return false;
    }

    //
    // Place some brownery
    //
    dbg2("DGN: Place foilage");
    place_foilage(dungeon);
    if (g_errored) {
      return false;
    }

    delete dungeon;
    break;
  }

  log("DGN: Populated dungeon at (%d,%d,%d) took %u ms", at.x, at.y, at.z, time_get_time_ms() - start);
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
        set_is_wall(X, Y);

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
        set_is_rock(X, Y);

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
        set_is_floor(X, Y);

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

      if (d->is_blood(x, y)) {
        tp = tp_random_blood();
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
      if (d->is_wand(x, y)) {
        tp = tp_random_wand();
      }
      if (d->is_ring(x, y)) {
        tp = tp_random_ring();
      }
      if (d->is_secret_door(x, y)) {
        tp = tp_random_secret_door();
      }

      if (d->is_monst_easy(x, y)) {
        if (pcg_random_range(0, 100) < 50) {
          tp = tp_random_monst_easy(p);
        }
      }

      if (d->is_monst_med(x, y)) {
        if (pcg_random_range(0, 100) < 50) {
          tp = tp_random_monst_med(p);
        }
      }

      if (d->is_monst_hard(x, y)) {
        if (pcg_random_range(0, 100) < 50) {
          tp = tp_random_monst_hard(p);
        }
      }

#if 0
      if (tp && tp->is_monst()) {
        CON("TMP using debug monster");
        tp = tp_find("cleaner");
        if (!tp) {
          DIE("can't find debug monster");
        }
      }
#endif
      //
      // If a hard monst room then always give treasure
      //
      auto r           = d->getr(x, y);
      bool be_generous = false;
      if (r) {
        if (r->is_hard_set) {
          be_generous = r->is_hard;
        } else {
          be_generous    = r->contains(MAP_DEPTH_OBJ, Charmap::MONST_HARD, Charmap::MONST_MED, Charmap::DOOR);
          r->is_hard_set = true;
          r->is_hard     = be_generous;
        }
      }

      if (d->is_mob_spawner_easy(x, y) || d->is_mob_spawner_hard(x, y)) {
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
          if (d->is_mob_spawner_easy(x, y)) {
            if (be_generous) {
              tp = tp_random_mob_easy(p);
            } else {
              if (pcg_random_range(0, 100) < 50) {
                tp = tp_random_mob_easy(p);
              }
            }
          } else if (d->is_mob_spawner_hard(x, y)) {
            tp = tp_random_mob_hard(p);
          }
        }
      }

      if (d->is_barrel(x, y)) {
        tp = tp_random_barrel();
      }

      if (d->is_treasure_type(x, y)) {
        if (be_generous) {
          tp = tp_random_treasure();
        } else {
          if (pcg_random_range(0, 100) < 50) {
            tp = tp_random_treasure();
          }
        }
      }

      if (r && r->is_secret) {
        //
        // For secret rooms, be generous and place the good stuff first.
        // We enchant this later after placing.
        //
        if (d->is_treasure_class_a(x, y) || d->is_treasure_class_b(x, y) || d->is_treasure_class_c(x, y)) {
          if (pcg_random_range(0, 100) < 80) {
            tp = tp_random_item_class_c();
          } else if (pcg_random_range(0, 100) < 80) {
            tp = tp_random_item_class_b();
          } else {
            tp = tp_random_item_class_a();
          }
        }
      } else {
        if (d->is_treasure_class_a(x, y)) {
          if (be_generous) {
            tp = tp_random_item_class_a();
          } else {
            if (pcg_random_range(0, 100) < 50) {
              tp = tp_random_item_class_a();
            }
          }
        }

        if (d->is_treasure_class_b(x, y)) {
          if (be_generous) {
            tp = tp_random_item_class_b();
          } else {
            if (pcg_random_range(0, 100) < 50) {
              tp = tp_random_item_class_b();
            }
          }
        }

        if (d->is_treasure_class_c(x, y)) {
          if (be_generous) {
            tp = tp_random_item_class_c();
          } else {
            if (pcg_random_range(0, 100) < 50) {
              tp = tp_random_item_class_c();
            }
          }
        }

        if (d->is_weapon_class_a(x, y)) {
          if (be_generous) {
            tp = tp_random_weapon_class_a();
          } else {
            if (pcg_random_range(0, 100) < 50) {
              tp = tp_random_weapon_class_a();
            }
          }
        }

        if (d->is_weapon_class_b(x, y)) {
          if (be_generous) {
            tp = tp_random_weapon_class_b();
          } else {
            if (pcg_random_range(0, 100) < 50) {
              tp = tp_random_weapon_class_b();
            }
          }
        }

        if (d->is_weapon_class_c(x, y)) {
          if (be_generous) {
            tp = tp_random_weapon_class_c();
          } else {
            if (pcg_random_range(0, 100) < 50) {
              tp = tp_random_weapon_class_c();
            }
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

      dbg("DGN: Creating %s", tp->name().c_str());
      auto t = thing_new(tp->name(), point(x, y));
      if (t) {
        if (t->is_weapon()) {
          if (r && r->is_secret) {
            t->enchant_randomly();
          }
          dbg("DGN: Placed weapon '%s'", t->short_text_capitalise().c_str());
        } else if (t->is_treasure_type()) {
          if (r && r->is_secret) {
            t->enchant_randomly();
          }
          dbg("DGN: Placed treasure '%s'", t->short_text_capitalise().c_str());
        } else if (t->is_bag()) {
          dbg("DGN: Placed '%s'", t->short_text_capitalise().c_str());
        } else if (t->is_monst()) {
          //
          // Already logged
          //
          // dbg("DGN: Placed random monster '%s'", t->short_text_capitalise().c_str());
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

void Level::create_dungeon_place_random_blood(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_blood(x, y)) {
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

      if (pcg_random_range(0, 1000) > 20) {
        continue;
      }

      auto tp = tp_random_blood();
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

      if (d->is_food(x, y) || d->is_blood(x, y) || d->is_door(x, y) || d->is_ascend_dungeon(x, y) ||
          d->is_descend_dungeon(x, y) || d->is_mob_spawner_any(x, y) || d->is_key(x, y) || d->is_potion(x, y) ||
          d->is_barrel(x, y) || d->is_wand(x, y) || d->is_ring(x, y) || d->is_secret_door(x, y) ||
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

      if (d->is_food(x, y) || d->is_blood(x, y) || d->is_door(x, y) || d->is_ascend_dungeon(x, y) ||
          d->is_descend_dungeon(x, y) || d->is_mob_spawner_any(x, y) || d->is_key(x, y) || d->is_potion(x, y) ||
          d->is_barrel(x, y) || d->is_wand(x, y) || d->is_ring(x, y) || d->is_secret_door(x, y) ||
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

      dbg("DGN: Placed random item '%s'", t->short_text_capitalise().c_str());

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

      dbg("DGN: Placed random torch");
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
