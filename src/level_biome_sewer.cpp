//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
// REMOVED #include "my_globals.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_ai.hpp"
// REMOVED #include "my_thing_template.hpp"

bool Level::create_biome_sewer(point3d at, uint32_t seed)
{
  TRACE_AND_INDENT();
  log("Create sewer at (%d,%d,%d)", at.x, at.y, at.z);

  biome = BIOME_SEWER;

  place_the_grid();
  if (g_errored) {
    return false;
  }

  place_the_grid();
  if (g_errored) {
    return false;
  }

  if (! create_biome_sewer_pipes(at)) {
    return false;
  }
  if (g_errored) {
    return false;
  }

  auto tries = 10000;
  create_biome_sewer_place_walls(1, 6, 6, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(1, 6, 3, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(1, 3, 6, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(1, 3, 3, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(2, 3, 3, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(1, 2, 2, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(2, 2, 2, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(3, 2, 2, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(1, 2, 1, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(2, 2, 1, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(1, 1, 2, tries);
  if (g_errored) {
    return false;
  }
  create_biome_sewer_place_walls(2, 1, 2, tries);
  if (g_errored) {
    return false;
  }

  create_biome_sewer_place_remaining_walls("sewer_wall");

  place_swimming_monsters();

  return ! g_errored;
}

void Level::place_swimming_monsters(void)
{
  TRACE_AND_INDENT();

  int tries  = 500;
  int placed = 0;

  while (tries-- > 0) {
    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK + 1);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK + 1);

    if (is_shallow_water(x, y)) {
      auto tp = get_sewer_biome_random_monst(point(x, y), biome, MONST_TYPE_SHALLOW_WATER);
      if (unlikely(! tp)) {
        continue;
      }

      (void) thing_new(tp->name(), point(x, y));
      if (placed++ > 10) {
        break;
      }

      //
      // This is for packs so that the monster count increases
      //
      assign_leaders_and_followers();
      if (monst_count >= LEVEL_MONST_COUNT_INIT_MAX) {
        return;
      }
    }

    if (is_deep_water(x, y)) {
      auto tp = get_sewer_biome_random_monst(point(x, y), biome, MONST_TYPE_DEEP_WATER);
      if (unlikely(! tp)) {
        continue;
      }

      (void) thing_new(tp->name(), point(x, y));
      if (placed++ > 10) {
        break;
      }

      //
      // This is for packs so that the monster count increases
      //
      assign_leaders_and_followers();
      if (monst_count >= LEVEL_MONST_COUNT_INIT_MAX) {
        return;
      }
    }
  }
}

bool Level::create_biome_sewer_pipes(point3d at)
{
  TRACE_NO_INDENT();

  auto prev = get(game->world.levels, at.x, at.y, at.z - 1);
  if (! prev) {
    err("no previous level for sewer");
    return false;
  }

  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > pipes_template = {};
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > sewer_pipe     = {};
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > final_pipes    = {};
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > failed         = {};

  //
  // Draw some random pipes
  //
  auto min_pipe_distance = 10;
  auto max_pipe_distance = 20;
  TRACE_NO_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK;
       x += pcg_random_range(min_pipe_distance, max_pipe_distance)) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      set(pipes_template, x, y, true);
    }
  }

  TRACE_NO_INDENT();
  for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK;
       y += pcg_random_range(min_pipe_distance, max_pipe_distance)) {
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
      set(pipes_template, x, y, true);
    }
  }

  //
  // Place the sewers
  //
  std::vector< point > sewers;
  auto                 got_count = 0;

  TRACE_NO_INDENT();
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      FOR_ALL_NON_INTERNAL_THINGS(prev, t, x, y)
      {
        if (t->is_descend_sewer()) {
          point p(x, y);
          sewers.push_back(p);
          set(sewer_pipe, x, y, true);
          got_count++;
        }
      }
      FOR_ALL_THINGS_END()
    }
  }

  if (got_count <= 1) {
    sewers.push_back(point(pcg_random_range(0, MAP_WIDTH), pcg_random_range(0, MAP_HEIGHT)));
    sewers.push_back(point(pcg_random_range(0, MAP_WIDTH), pcg_random_range(0, MAP_HEIGHT)));
    sewers.push_back(point(pcg_random_range(0, MAP_WIDTH), pcg_random_range(0, MAP_HEIGHT)));
  }

  //
  // Draw a line from the sewer to a nearby pipe
  //
  TRACE_NO_INDENT();
  for (auto p : sewers) {
    int dx = 0, dy = 0;
    switch (pcg_random_range_inclusive(0, 3)) {
      case 0:
        dx = -1;
        dy = 0;
        break;
      case 1:
        dx = 1;
        dy = 0;
        break;
      case 2:
        dx = 0;
        dy = -1;
        break;
      case 3:
        dx = 0;
        dy = 1;
        break;
    }

    while (true) {
      if (p.x >= MAP_WIDTH - MAP_BORDER_ROCK) {
        break;
      }
      if (p.y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
        break;
      }
      if (p.x < MAP_BORDER_ROCK) {
        break;
      }
      if (p.y < MAP_BORDER_ROCK) {
        break;
      }

      //
      // Try to follow the pipe template
      //
      if (get(pipes_template, p.x, p.y)) {
        break;
      }
      set(pipes_template, p.x, p.y, true);
      p.x += dx;
      p.y += dy;
    }
  }

  //
  // For each sewer, try to find another
  //
  TRACE_NO_INDENT();
  for (auto n = 0U; n < sewers.size(); n++) {
    auto a = sewers[ n ];
    auto b = sewers[ pcg_random_range(0, sewers.size()) ];
    while (a == b) {
      b = sewers[ pcg_random_range(0, sewers.size()) ];
    }

    std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > walked = {};
    int                                                     tries  = 0;
    while (tries < 1000) {
      set(final_pipes, a.x, a.y, true);
      set(walked, a.x, a.y, true);
      if (a.x >= MAP_WIDTH - MAP_BORDER_ROCK) {
        break;
      }
      if (a.y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
        break;
      }
      if (a.x < MAP_BORDER_ROCK) {
        break;
      }
      if (a.y < MAP_BORDER_ROCK) {
        break;
      }

      //
      // Try to follow the pipe template
      //
      if ((a.x < b.x) && get(pipes_template, a.x + 1, a.y)) {
        a.x++;
        continue;
      }
      if ((a.x > b.x) && get(pipes_template, a.x - 1, a.y)) {
        a.x--;
        continue;
      }
      if ((a.y < b.y) && get(pipes_template, a.x, a.y + 1)) {
        a.y++;
        continue;
      }
      if ((a.y > b.y) && get(pipes_template, a.x, a.y - 1)) {
        a.y--;
        continue;
      }
      if (! get(walked, a.x + 1, a.y) && get(pipes_template, a.x + 1, a.y)) {
        a.x++;
        continue;
      }
      if (! get(walked, a.x - 1, a.y) && get(pipes_template, a.x - 1, a.y)) {
        a.x--;
        continue;
      }
      if (! get(walked, a.x, a.y + 1) && get(pipes_template, a.x, a.y + 1)) {
        a.y++;
        continue;
      }
      if (! get(walked, a.x, a.y - 1) && get(pipes_template, a.x, a.y - 1)) {
        a.y--;
        continue;
      }
      if (! get(walked, a.x + 1, a.y)) {
        a.x++;
        continue;
      }
      if (! get(walked, a.x - 1, a.y)) {
        a.x--;
        continue;
      }
      if (! get(walked, a.x, a.y + 1)) {
        a.y++;
        continue;
      }
      if (! get(walked, a.x, a.y - 1)) {
        a.y--;
        continue;
      }
      set(failed, a.x, a.y, true);
      break;
    }
  }

  TRACE_NO_INDENT();
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      point p(x, y);
      if (get(final_pipes, x, y)) {
        (void) thing_new("corridor2", p);
        if (pcg_random_range(0, 100) < 25) {
          (void) thing_new("water", p);
        }
      }
      if (get(sewer_pipe, x, y)) {
        (void) thing_new("ascend_sewer1", p);
      }
    }
  }

#if 0
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if (get(failed, x, y)) {
        printf("F");
      } else if (get(sewer_pipe, x, y)) {
        printf("S");
      } else if (get(final_pipes, x, y)) {
        printf("p");
      } else if (get(pipes_template, x, y)) {
        printf(".");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
#endif

  return true;
}

void Level::create_biome_sewer_place_walls(int variant, int block_width, int block_height, int tries)
{
  TRACE_AND_INDENT();
  auto tp = tp_random_sewer_wall();
  if (unlikely(! tp)) {
    ERR("Place walls failed");
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

        if (is_bridge(X, Y) || is_corridor(X, Y) || is_shallow_water(X, Y) || is_ascend_sewer(X, Y) ||
            is_deep_water(X, Y)) {
          can_place_here = false;
          continue;
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
          ERR("wall tile %s not found", tilename.c_str());
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

void Level::create_biome_sewer_place_remaining_walls(const std::string &what)
{
  TRACE_AND_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {

      if (is_bridge(x, y) || is_corridor(x, y) || is_shallow_water(x, y) || is_ascend_sewer(x, y) ||
          is_deep_water(x, y)) {
        continue;
      }

      if (is_wall(x, y)) {
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
