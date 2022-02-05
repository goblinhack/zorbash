//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//
#include "my_level.hpp"
#include "my_random.hpp"

void Level::tick_gas_poison(void)
{
  static std::array< std::array< uint8_t, MAP_HEIGHT * DUNGEON_GAS_RESOLUTION >, MAP_WIDTH * DUNGEON_GAS_RESOLUTION >
      old_gas {};

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
            gas_poison[ x ][ y ] = 9;
          }
        }
      }
    }
  }
#endif

  old_gas = gas_poison;

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (is_gas_blocker(x, y)) {
        for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
          for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
            uint16_t gx            = x * DUNGEON_GAS_RESOLUTION + dx;
            uint16_t gy            = y * DUNGEON_GAS_RESOLUTION + dy;
            gas_poison[ gy ][ gx ] = 255;
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
            if (gas_poison[ gy ][ gx ] == 255) {
              gas_poison[ gy ][ gx ] = 0;
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
      uint8_t n = gas_poison[ y ][ x ];
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

  for (uint16_t y = DUNGEON_GAS_RESOLUTION; y < (MAP_HEIGHT * DUNGEON_GAS_RESOLUTION) - DUNGEON_GAS_RESOLUTION; y++) {
    uint16_t x = DUNGEON_GAS_RESOLUTION;

    // a b c
    // d e f
    // g h i
    uint8_t *a = &old_gas[ y - 1 ][ x - 1 ];
    uint8_t *b = a + 1;
    uint8_t *c = b + 1;
    uint8_t *d = &old_gas[ y ][ x - 1 ];
    uint8_t *e = d + 1;
    uint8_t *f = e + 1;
    uint8_t *g = &old_gas[ y + 1 ][ x - 1 ];
    uint8_t *h = g + 1;
    uint8_t *i = h + 1;

    uint8_t *n = &gas_poison[ y ][ x ];

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

      *n++ = (ga + gb + gc + gd + ge + gf + gg + gh + gi) / 9;
    }
  }

  old_gas = gas_poison;

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
          int      i  = gas_poison[ gy ][ gx ];
          if (i == 255) {
            continue;
          }
          g += i;
        }
      }
      if (g > 254) {
        g = 254;
      }
      set_is_gas_poison_no_check(x, y, g);
    }
  }
}

void Level::poison_gas_explosion(point at)
{
  if (is_gas_poison_no_check(at.x, at.y) < 5) {
    return;
  }

  for (auto dx = 0; dx < DUNGEON_GAS_RESOLUTION; dx++) {
    for (auto dy = 0; dy < DUNGEON_GAS_RESOLUTION; dy++) {
      uint16_t gx            = at.x * DUNGEON_GAS_RESOLUTION + dx;
      uint16_t gy            = at.y * DUNGEON_GAS_RESOLUTION + dy;
      gas_poison[ gy ][ gx ] = 0;
    }
  }
  set_is_gas_poison_no_check(at.x, at.y, 0);
  thing_new("explosion_major", at);

  poison_gas_explosion(at + point(1, 0));
  poison_gas_explosion(at + point(-1, 0));
  poison_gas_explosion(at + point(1, -1));
  poison_gas_explosion(at + point(-1, 1));
}
