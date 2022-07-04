//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_random.hpp"

void Level::tick_gas_poison(void)
{
  TRACE_NO_INDENT();

  std::array< std::array< uint8_t, MAP_HEIGHT * DUNGEON_GAS_RESOLUTION >, MAP_WIDTH * DUNGEON_GAS_RESOLUTION >
      old_gas_poison_cloud {};

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
          if (pcg_random_range(0, 100) < 10) {
            gas_poison_cloud[ x ][ y ] = 9;
          }
        }
      }
    }
  }
#endif

  old_gas_poison_cloud = gas_poison_cloud;

  TRACE_NO_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (is_gas_blocker(x, y)) {
        for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
          for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
            uint16_t gx = x * DUNGEON_GAS_RESOLUTION + dx;
            uint16_t gy = y * DUNGEON_GAS_RESOLUTION + dy;
            set(gas_poison_cloud, gx, gy, (uint8_t) 255);
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
            if (get(gas_poison_cloud, gx, gy) == 255) {
              set(gas_poison_cloud, gx, gy, (uint8_t) 0);
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
      uint8_t n = gas_poison_cloud[ x ][ y ];
      if (n == 255) {
        printf("X");
      } else if (n) {
        printf("%u", n);
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
#endif

  //
  // Anything less than 9 will cause gas to spread more
  //
  int reduction;
  if (pcg_random_range(0, 100) < 80) {
    reduction = 9;
  } else if (pcg_random_range(0, 100) < 50) {
    reduction = 8;
  } else {
    reduction = 7;
  }

  TRACE_NO_INDENT();
  for (uint16_t y = DUNGEON_GAS_RESOLUTION; y < (MAP_HEIGHT * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION; y++) {
    uint16_t x = DUNGEON_GAS_RESOLUTION;

    // a b c
    // d e f
    // g h i
    uint8_t *a = getptr(old_gas_poison_cloud, x - 1, y - 1);
    uint8_t *b = getptr(old_gas_poison_cloud, x, y - 1);
    uint8_t *c = getptr(old_gas_poison_cloud, x + 1, y - 1);
    uint8_t *d = getptr(old_gas_poison_cloud, x - 1, y);
    uint8_t *e = getptr(old_gas_poison_cloud, x, y);
    uint8_t *f = getptr(old_gas_poison_cloud, x + 1, y);
    uint8_t *g = getptr(old_gas_poison_cloud, x - 1, y + 1);
    uint8_t *h = getptr(old_gas_poison_cloud, x, y + 1);
    uint8_t *i = getptr(old_gas_poison_cloud, x + 1, y + 1);

    uint8_t *n = getptr(gas_poison_cloud, x, y);

    for (; x < (MAP_WIDTH * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION; x++) {
      uint8_t ga = *a++;
      uint8_t gb = *b++;
      uint8_t gc = *c++;
      uint8_t gd = *d++;
      uint8_t ge = *e++;
      uint8_t gf = *f++;
      uint8_t gg = *g++;
      uint8_t gh = *h++;
      uint8_t gi = *i++;

      //
      // If a rock ignore
      //
      uint8_t gn = *n;
      if (gn == 255) {
        n++;
        continue;
      }

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

      *n++ = (ga + gb + gc + gd + ge + gf + gg + gh + gi) / reduction;
    }
  }

  old_gas_poison_cloud = gas_poison_cloud;

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
          int      i  = gas_poison_cloud[ gx ][ gy ];
          if (i == 255) {
            continue;
          }
          g += i;
        }
      }
      if (g > 254) {
        g = 254;
      }
      is_gas_poison_no_check_set(x, y, g);
    }
  }
}

void Level::poison_gas_explosion(point at)
{
  TRACE_NO_INDENT();

  if (is_gas_poison_no_check(at.x, at.y) < 5) {
    return;
  }

  for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
    for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
      uint16_t gx                  = at.x * DUNGEON_GAS_RESOLUTION + dx;
      uint16_t gy                  = at.y * DUNGEON_GAS_RESOLUTION + dy;
      gas_poison_cloud[ gx ][ gy ] = 0;
    }
  }
  is_gas_poison_no_check_set(at.x, at.y, 0);
  thing_new("explosion_major", at);

  poison_gas_explosion(at + point(1, 0));
  poison_gas_explosion(at + point(-1, 0));
  poison_gas_explosion(at + point(1, -1));
  poison_gas_explosion(at + point(-1, 1));
}
