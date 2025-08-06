//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

void Level::update_hazard_tile_map(void)
{
  //
  // The water tiles are twice the size of normal tiles, so work out where to draw them to avoid overlaps
  //
  lava_tile_map       = {};
  basalt_tile_map     = {};
  chasm_tile_map      = {};
  water_tile_map      = {};
  ooze_tile_map       = {};
  deep_water_tile_map = {};

  for (auto y = 2; y < MAP_HEIGHT - 2; y++) {
    for (auto x = 2; x < MAP_WIDTH - 2; x++) {
      if (is_shallow_water(x, y) || is_deep_water(x, y)) {
        for (auto dx = -2; dx <= 2; dx++) {
          for (auto dy = -2; dy <= 2; dy++) {
            incr(water_tile_map, x + dx, y + dy, (uint8_t) 1);
            if (is_deep_water(x, y)) {
              incr(deep_water_tile_map, x + dx, y + dy, (uint8_t) 1);
            }
          }
        }
      }

      if (is_ooze(x, y)) {
        for (auto dx = -2; dx <= 2; dx++) {
          for (auto dy = -2; dy <= 2; dy++) {
            incr(ooze_tile_map, x + dx, y + dy, (uint8_t) 1);
          }
        }
      }

      if (is_lava(x, y)) {
        for (auto dx = -2; dx <= 2; dx++) {
          for (auto dy = -2; dy <= 2; dy++) {
            incr(lava_tile_map, x + dx, y + dy, (uint8_t) 1);
          }
        }
      }

      if (is_basalt(x, y)) {
        for (auto dx = -2; dx <= 2; dx++) {
          for (auto dy = -2; dy <= 2; dy++) {
            incr(basalt_tile_map, x + dx, y + dy, (uint8_t) 1);
          }
        }
      }

      if (is_chasm(x, y)) {
        for (auto dx = -2; dx <= 2; dx++) {
          for (auto dy = -2; dy <= 2; dy++) {
            incr(chasm_tile_map, x + dx, y + dy, (uint8_t) 1);
          }
        }
      }
    }
  }
}

void Level::update_water_next_to_lava(bool &changed)
{
  for (auto y = 2; y < MAP_HEIGHT - 2; y++) {
    for (auto x = 2; x < MAP_WIDTH - 2; x++) {
      if (is_shallow_water(x, y) || is_deep_water(x, y)) {
        for (auto dx = -2; dx <= 2; dx++) {
          for (auto dy = -2; dy <= 2; dy++) {
            if (is_deep_water(x + dx, y + dy) || is_block_of_ice(x + dx, y + dy)) {
              FOR_ALL_NON_INTERNAL_THINGS(this, t, x, y)
              {
                if (t->is_lava()) {
                  t->dead("by being too close to deep water");
                  changed = true;
                  if (! is_starting) {
                    if (! is_steam(x, y)) {
                      auto steam = thing_new("steam", point(x, y));
                      if (steam) {
                        changed = true;
                        steam->lifespan_set(pcg_random_range(1, 10));
                      }
                    }
                  }
                }
              }
              FOR_ALL_THINGS_END()
            }
          }
        }
      }
    }
  }

  for (auto y = 2; y < MAP_HEIGHT - 2; y++) {
    for (auto x = 2; x < MAP_WIDTH - 2; x++) {
      if (is_shallow_water(x, y) || is_deep_water(x, y)) {
        for (auto dx = -2; dx <= 2; dx++) {
          for (auto dy = -2; dy <= 2; dy++) {
            if (is_lava(x + dx, y + dy)) {
              FOR_ALL_NON_INTERNAL_THINGS(this, t, x, y)
              {
                if (t->is_shallow_water()) {
                  t->dead("by being too close to lava");
                  changed = true;
                  if (! is_starting) {
                    if (! is_steam(x, y)) {
                      auto steam = thing_new("steam", point(x, y));
                      if (steam) {
                        changed = true;
                        steam->lifespan_set(pcg_random_range(1, 10));
                      }
                    }
                  }
                }
              }
              FOR_ALL_THINGS_END()
            }
          }
        }
      }
    }
  }
}

void Level::update_things_next_to_a_chasm(bool &changed)
{
  for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
      //
      // Things on the edge of a chasm fall in
      //
      if (is_shallow_water(x, y) || is_deep_water(x, y) || is_lava(x, y) || is_basalt(x, y)) {
        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            if (is_chasm(x + dx, y + dy)) {
              bool place_shallow_water = false;

              FOR_ALL_NON_INTERNAL_THINGS(this, t, x, y)
              {
                if (t->is_falling) {
                  continue;
                }

                //
                // Deep water next to a chasm changes to
                // regular water
                //
                if (t->is_deep_water()) {
                  place_shallow_water = true;
                }

                if (t->is_shallow_water() || t->is_deep_water() || t->is_lava()) {
                  IF_DEBUG { t->log("Over a chasm"); }
                  t->fall();
                }
              }
              FOR_ALL_THINGS_END()

              if (place_shallow_water) {
                thing_new("water", point(x, y));
                changed = true;
              }
            }
          }
        }
      }
    }
  }
}

void Level::update_deep_water(bool &changed)
{
  for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
      //
      // Don't remove water a monster is sitting in, else piranhas get stuck
      //
      if (is_monst(x, y)) {
        continue;
      }

      //
      // Deep water must be surrounded by water
      //
      if (is_deep_water(x, y)) {
        if (is_shallow_water(x, y)) {
          FOR_ALL_NON_INTERNAL_THINGS(this, t, x, y)
          {
            if (t->is_shallow_water()) {
              t->dead("by being shallow");
              changed = true;
            }
          }
          FOR_ALL_THINGS_END()
        }

        int nebs = 0;
        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            //
            // Deep water next to a wall is ok
            //
            if (is_wall(x, y) || is_rock(x, y)) {
              nebs++;
            } else {
              nebs += is_shallow_water(x + dx, y + dy) ? 1 : 0;
              nebs += is_deep_water(x + dx, y + dy) ? 1 : 0;
            }
          }
        }

        //
        // Allow placement of intentional deep water in the dungeon
        //
        auto min_nebs = is_floor(x, y) ? 3 : 9;
        if (nebs < min_nebs) {
          bool removed_deep_water = false;
          FOR_ALL_NON_INTERNAL_THINGS(this, t, x, y)
          {
            if (t->is_deep_water()) {
              t->dead("by being too shallow");
              changed            = true;
              removed_deep_water = true;
            }
          }
          FOR_ALL_THINGS_END()

          //
          // Replace with shallow water
          //
          if (removed_deep_water) {
            thing_new("water", point(x, y));
            changed = true;
          }

          IF_DEBUG2
          {
            if (is_deep_water(x, y)) {
              FOR_ALL_NON_INTERNAL_THINGS(this, t, x, y)
              {
                if (t->is_deep_water()) {
                  t->log("Still present; should be removed");
                } else {
                  t->log("Still present; ok");
                }
              }
              FOR_ALL_THINGS_END()

              DIE("deep water (count %d) still present after removal", is_deep_water(x, y));
            }
          }
        }
      }
    }
  }
}

void Level::update_map_things_to_stand_on(void)
{
  TRACE_AND_INDENT();
  _is_able_to_stand_on = {};

  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (is_floor(x, y) || is_corridor(x, y) || is_dirt(x, y) || is_bridge(x, y)) {
        is_able_to_stand_on_set(x, y);
      }
    }
  }
}

void Level::update_map(void)
{
  dbg("Update map");
  TRACE_AND_INDENT();

  bool changed = false;

  update_hazard_tile_map();
  update_water_next_to_lava(changed);
  update_things_next_to_a_chasm(changed);
  update_deep_water(changed);
  update_hazard_tile_map();
  update_map_things_to_stand_on();

  //
  // If we get rid of any water, we need to update the submerged state
  //
  if (changed) {
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
      for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
        FOR_ALL_THINGS(this, t, x, y)
        {
          if (t->is_attached) {
            t->level_pop();
            t->level_push();
          }
        }
        FOR_ALL_THINGS_END()
      }
    }
  }
}
