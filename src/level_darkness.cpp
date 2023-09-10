//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

void Level::tick_darkness(void)
{
  TRACE_NO_INDENT();

  std::array< std::array< uint8_t, MAP_HEIGHT_MAX * DUNGEON_GAS_RESOLUTION >, MAP_WIDTH_MAX * DUNGEON_GAS_RESOLUTION >
      old_darkness_cloud {};

#if 0
  IF_DEBUG2
  {
    static int first = 1;
    if (first) {
      first = 0;
      for (uint16_t y = DUNGEON_GAS_RESOLUTION; y < (MAP_HEIGHT * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION;
           y++) {
        for (uint16_t x = DUNGEON_GAS_RESOLUTION; x < (MAP_WIDTH * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION;
             x++) {
          if (pcg_random_range(0, 100) < spread_chance) {
            darkness_cloud[ x ][ y ] = 9;
          }
        }
      }
    }
  }
#endif

  old_darkness_cloud = darkness_cloud;

  display_darkness = false;

  TRACE_NO_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (is_gas_blocker(x, y)) {
        for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
          for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
            uint16_t gx = x * DUNGEON_GAS_RESOLUTION + dx;
            uint16_t gy = y * DUNGEON_GAS_RESOLUTION + dy;
            set_no_check(darkness_cloud, gx, gy, (uint8_t) 255);
          }
        }
      } else {
        //
        // Cater for doors opening
        //
        for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
          for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
            uint16_t gx = x * DUNGEON_GAS_RESOLUTION + dx;
            uint16_t gy = y * DUNGEON_GAS_RESOLUTION + dy;
            if (get_no_check(darkness_cloud, gx, gy) == 255) {
              set_no_check(darkness_cloud, gx, gy, (uint8_t) 0);
            }
          }
        }
      }
    }
  }

#if 0
  printf("\nGAS:\n");
  for (uint16_t y = DUNGEON_GAS_RESOLUTION; y < (MAP_HEIGHT * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION; y++) {
    uint16_t x = DUNGEON_GAS_RESOLUTION;
    for (; x < (MAP_WIDTH * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION; x++) {
      uint8_t n = darkness_cloud[ x ][ y ];
      if (n == 255) {
        printf("XXX");
      } else if (n) {
        printf("%3u", n);
      } else {
        printf("   ");
      }
    }
    printf("\n");
  }
#endif

  //
  // Anything less than 9 will cause gas to spread more
  //
  int reduction;
  int roll = d1000();
  if (roll < 900) {
    reduction = 9;
  } else if (roll < 950) {
    reduction = 8;
  } else if (roll < 995) {
    reduction = 7;
  } else {
    reduction = 2;
  }

  TRACE_NO_INDENT();
  for (uint16_t y = DUNGEON_GAS_RESOLUTION; y < (MAP_HEIGHT * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION; y++) {

    // a b c
    // d e f
    // g h i

    for (uint16_t x = DUNGEON_GAS_RESOLUTION; x < (MAP_WIDTH * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION;
         x++) {
      uint8_t gn = get_no_check(darkness_cloud, x, y);

      //
      // If a rock ignore
      //
      if (gn == 255) {
        continue;
      }

      uint8_t ga = get_no_check(old_darkness_cloud, x - 1, y - 1);
      uint8_t gb = get_no_check(old_darkness_cloud, x, y - 1);
      uint8_t gc = get_no_check(old_darkness_cloud, x + 1, y - 1);
      uint8_t gd = get_no_check(old_darkness_cloud, x - 1, y);
      uint8_t ge = get_no_check(old_darkness_cloud, x, y);
      uint8_t gf = get_no_check(old_darkness_cloud, x + 1, y);
      uint8_t gg = get_no_check(old_darkness_cloud, x - 1, y + 1);
      uint8_t gh = get_no_check(old_darkness_cloud, x, y + 1);
      uint8_t gi = get_no_check(old_darkness_cloud, x + 1, y + 1);

      //
      // If a rock then it does not contribute to gas strength
      //
      if (ga == 255) {
        ga = 0;
      }
      if (gb == 255) {
        gb = 0;
      }
      if (gc == 255) {
        gc = 0;
      }
      if (gd == 255) {
        gd = 0;
      }
      if (ge == 255) {
        ge = 0;
      }
      if (gf == 255) {
        gf = 0;
      }
      if (gg == 255) {
        gg = 0;
      }
      if (gh == 255) {
        gh = 0;
      }
      if (gi == 255) {
        gi = 0;
      }

      uint8_t nn = (ga + gb + gc + gd + ge + gf + gg + gh + gi) / reduction;
      set_no_check(darkness_cloud, x, y, nn);

      if (nn) {
        //
        // Clear out other gas types?
        //
        set_no_check(gas_poison_cloud, x, y, (uint8_t) 0);
        set_no_check(gas_paralysis_cloud, x, y, (uint8_t) 0);
        set_no_check(gas_healing_cloud, x, y, (uint8_t) 0);
      }

      if (nn) {
        display_darkness = true;
      }
    }
  }

  old_darkness_cloud = darkness_cloud;

  //
  // Update the level gas intensity per tile
  //
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      int g = 0;
      for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
        for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
          uint16_t gx = x * DUNGEON_GAS_RESOLUTION + dx;
          uint16_t gy = y * DUNGEON_GAS_RESOLUTION + dy;
          int      i  = darkness_cloud[ gx ][ gy ];
          if (i == 255) {
            continue;
          }
          g += i;
        }
      }
      if (g > 254) {
        g = 254;
      }
      is_darkness_no_check_set(x, y, g);
    }
  }

  if (0) {
    for (auto y = 0; y <= MAP_HEIGHT; y++) {
      std::string debug;
      for (auto x = 0; x <= MAP_WIDTH; x++) {
        if (point(x, y) == player->curr_at) {
          debug += "@";
          continue;
        }
        if (is_wall(x, y)) {
          debug += "#";
          continue;
        }
        if (is_darkness(x, y)) {
          debug += "D";
          continue;
        }
        debug += " ";
      }
      LOG("DARK: %s", debug.c_str());
    }
  }
}

uint8_t Level::is_darkness(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return 0;
  }
  return (get(_is_darkness, p.x, p.y));
}

uint8_t Level::is_darkness_no_check(const point p) const { return (get_no_check(_is_darkness, p.x, p.y)); }

uint8_t Level::is_darkness(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_darkness, x, y));
}

uint8_t Level::is_darkness_no_check(const int x, const int y) const { return (get_no_check(_is_darkness, x, y)); }

void Level::is_darkness_set(const int x, const int y, uint8_t val)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_darkness, x, y, val);
}

void Level::is_darkness_no_check_set(const int x, const int y, uint8_t val) { set_no_check(_is_darkness, x, y, val); }

void Level::is_darkness_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_darkness, x, y, (uint8_t) 0);
}

void Level::is_darkness_no_check_unset(const int x, const int y) { set_no_check(_is_darkness, x, y, (uint8_t) 0); }
