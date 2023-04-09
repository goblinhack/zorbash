//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"

void Level::chances_of_creating_set(void)
{
  TRACE_AND_INDENT();

  if (biome == BIOME_UNKNOWN) {
    ERR("Biome type not set");
    return;
  }

  switch (difficulty_depth) {
    default: DIE("Unexpected difficulty depth %d", difficulty_depth);
    case 1:
      for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 1000;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = -1;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = -1;
      }
      d1000_chance_of_creating_mob_challenge_class_A = 500;
      d1000_chance_of_creating_mob_challenge_class_B = 10;
      d1000_chance_of_creating_treasure_class_A      = 1000;
      d1000_chance_of_creating_treasure_class_B      = 10;
      d1000_chance_of_creating_treasure_class_C      = 10;
      d1000_chance_of_creating_weapon_class_A        = 1000;
      d1000_chance_of_creating_weapon_class_B        = 500;
      d1000_chance_of_creating_weapon_class_C        = 10;
      break;
    case 2:
      for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 1000;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = -1;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = -1;
      }
      d1000_chance_of_creating_mob_challenge_class_A = 500;
      d1000_chance_of_creating_mob_challenge_class_B = 500;
      d1000_chance_of_creating_treasure_class_A      = 1000;
      d1000_chance_of_creating_treasure_class_B      = 100;
      d1000_chance_of_creating_treasure_class_C      = 10;
      d1000_chance_of_creating_weapon_class_A        = 1000;
      d1000_chance_of_creating_weapon_class_B        = 500;
      d1000_chance_of_creating_weapon_class_C        = 100;
      break;
    case 3:
      for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 1000;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = -1;
      }
      d1000_chance_of_creating_mob_challenge_class_A = 500;
      d1000_chance_of_creating_mob_challenge_class_B = 500;
      d1000_chance_of_creating_treasure_class_A      = 1000;
      d1000_chance_of_creating_treasure_class_B      = 1000;
      d1000_chance_of_creating_treasure_class_C      = 100;
      d1000_chance_of_creating_weapon_class_A        = 1000;
      d1000_chance_of_creating_weapon_class_B        = 500;
      d1000_chance_of_creating_weapon_class_C        = 200;
      break;
    case 4:
      for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 200;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 10;
      }
      d1000_chance_of_creating_mob_challenge_class_A = 500;
      d1000_chance_of_creating_mob_challenge_class_B = 500;
      d1000_chance_of_creating_treasure_class_A      = 1000;
      d1000_chance_of_creating_treasure_class_B      = 100;
      d1000_chance_of_creating_treasure_class_C      = 1000;
      d1000_chance_of_creating_weapon_class_A        = 1000;
      d1000_chance_of_creating_weapon_class_B        = 500;
      d1000_chance_of_creating_weapon_class_C        = 500;
      break;
    case 5:
      for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 100;
      }
      d1000_chance_of_creating_mob_challenge_class_A = 100;
      d1000_chance_of_creating_mob_challenge_class_B = 500;
      d1000_chance_of_creating_treasure_class_A      = 10;
      d1000_chance_of_creating_treasure_class_B      = 1000;
      d1000_chance_of_creating_treasure_class_C      = 1000;
      d1000_chance_of_creating_weapon_class_A        = 10;
      d1000_chance_of_creating_weapon_class_B        = 100;
      d1000_chance_of_creating_weapon_class_C        = 500;
      break;
    case 6:
      for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 500;
      }
      d1000_chance_of_creating_mob_challenge_class_A = 100;
      d1000_chance_of_creating_mob_challenge_class_B = 500;
      d1000_chance_of_creating_treasure_class_A      = 10;
      d1000_chance_of_creating_treasure_class_B      = 500;
      d1000_chance_of_creating_treasure_class_C      = 1000;
      d1000_chance_of_creating_weapon_class_A        = 10;
      d1000_chance_of_creating_weapon_class_B        = 10;
      d1000_chance_of_creating_weapon_class_C        = 1000;
      break;
    case 7:
      for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 500;
      }
      d1000_chance_of_creating_mob_challenge_class_A = 10;
      d1000_chance_of_creating_mob_challenge_class_B = 200;
      d1000_chance_of_creating_treasure_class_A      = 10;
      d1000_chance_of_creating_treasure_class_B      = 10;
      d1000_chance_of_creating_treasure_class_C      = 1000;
      d1000_chance_of_creating_weapon_class_A        = 10;
      d1000_chance_of_creating_weapon_class_B        = 500;
      d1000_chance_of_creating_weapon_class_C        = 1000;
      break;
    case 8:
      for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 1000;
      }
      d1000_chance_of_creating_mob_challenge_class_A = 10;
      d1000_chance_of_creating_mob_challenge_class_B = 10;
      d1000_chance_of_creating_treasure_class_A      = 10;
      d1000_chance_of_creating_treasure_class_B      = 10;
      d1000_chance_of_creating_treasure_class_C      = 1000;
      d1000_chance_of_creating_weapon_class_A        = 10;
      d1000_chance_of_creating_weapon_class_B        = 10;
      d1000_chance_of_creating_weapon_class_C        = 1000;
      break;
  }

  for (auto monst_type = (int) MONST_ENVIRON_NORMAL; monst_type < MONST_ENVIRON_MAX; monst_type++) {
    for (auto monst_class = (int) MONST_CLASS_A; monst_class < MONST_CLASS_MAX; monst_class++) {
      if (d1000_chance_of_creating_monst[ monst_type ][ monst_class ] > 1000) {
        d1000_chance_of_creating_monst[ monst_type ][ monst_class ] = 1000;
      }
    }
  }

  if (d1000_chance_of_creating_mob_challenge_class_A < 0) {
    d1000_chance_of_creating_mob_challenge_class_A = -1;
  }
  if (d1000_chance_of_creating_mob_challenge_class_A > 1000) {
    d1000_chance_of_creating_mob_challenge_class_A = 1000;
  }
  if (d1000_chance_of_creating_mob_challenge_class_B < 0) {
    d1000_chance_of_creating_mob_challenge_class_B = -1;
  }
  if (d1000_chance_of_creating_mob_challenge_class_B > 1000) {
    d1000_chance_of_creating_mob_challenge_class_B = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_A < 0) {
    d1000_chance_of_creating_treasure_class_A = -1;
  }
  if (d1000_chance_of_creating_treasure_class_A > 1000) {
    d1000_chance_of_creating_treasure_class_A = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_B < 0) {
    d1000_chance_of_creating_treasure_class_B = -1;
  }
  if (d1000_chance_of_creating_treasure_class_B > 1000) {
    d1000_chance_of_creating_treasure_class_B = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_C < 0) {
    d1000_chance_of_creating_treasure_class_C = -1;
  }
  if (d1000_chance_of_creating_treasure_class_C > 1000) {
    d1000_chance_of_creating_treasure_class_C = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_A < 0) {
    d1000_chance_of_creating_weapon_class_A = -1;
  }
  if (d1000_chance_of_creating_weapon_class_A > 1000) {
    d1000_chance_of_creating_weapon_class_A = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_B < 0) {
    d1000_chance_of_creating_weapon_class_B = -1;
  }
  if (d1000_chance_of_creating_weapon_class_B > 1000) {
    d1000_chance_of_creating_weapon_class_B = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_C < 0) {
    d1000_chance_of_creating_weapon_class_C = -1;
  }
  if (d1000_chance_of_creating_weapon_class_C > 1000) {
    d1000_chance_of_creating_weapon_class_C = 1000;
  }

  dbg("Chance of creating at difficulty depth %d:", difficulty_depth);
  auto monst_type = MONST_ENVIRON_NORMAL;
  dbg("- d1000 monst_class_A         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ]);
  dbg("- d1000 monst_class_B         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ]);
  dbg("- d1000 monst_class_C         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ]);
  dbg("- d1000 monst_class_D         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ]);
  dbg("- d1000 monst_class_E         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ]);
  dbg("- d1000 mob_challenge_class_A %u", d1000_chance_of_creating_mob_challenge_class_A);
  dbg("- d1000 mob_challenge_class_B %u", d1000_chance_of_creating_mob_challenge_class_B);
  dbg("- d1000 treasure_class_A      %u", d1000_chance_of_creating_treasure_class_A);
  dbg("- d1000 treasure_class_B      %u", d1000_chance_of_creating_treasure_class_B);
  dbg("- d1000 treasure_class_C      %u", d1000_chance_of_creating_treasure_class_C);
  dbg("- d1000 weapon_class_A        %u", d1000_chance_of_creating_weapon_class_A);
  dbg("- d1000 weapon_class_B        %u", d1000_chance_of_creating_weapon_class_B);
  dbg("- d1000 weapon_class_C        %u", d1000_chance_of_creating_weapon_class_C);
}
