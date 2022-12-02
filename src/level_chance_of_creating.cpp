//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"

void Level::chances_of_creating_set(void)
{
  TRACE_AND_INDENT();

  switch (difficulty_depth) {
    default: DIE("Unexpected difficulty depth %d", difficulty_depth);
    case 1:
      for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 1000;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = -1;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = -1;
      }
      d1000_chance_of_creating_mob_challenge_class_a = 500;
      d1000_chance_of_creating_mob_challenge_class_b = 10;
      d1000_chance_of_creating_treasure_class_a      = 1000;
      d1000_chance_of_creating_treasure_class_b      = 10;
      d1000_chance_of_creating_treasure_class_c      = 10;
      d1000_chance_of_creating_weapon_class_a        = 1000;
      d1000_chance_of_creating_weapon_class_b        = 500;
      d1000_chance_of_creating_weapon_class_c        = 10;
      break;
    case 2:
      for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 1000;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = -1;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = -1;
      }
      d1000_chance_of_creating_mob_challenge_class_a = 500;
      d1000_chance_of_creating_mob_challenge_class_b = 500;
      d1000_chance_of_creating_treasure_class_a      = 1000;
      d1000_chance_of_creating_treasure_class_b      = 100;
      d1000_chance_of_creating_treasure_class_c      = 10;
      d1000_chance_of_creating_weapon_class_a        = 1000;
      d1000_chance_of_creating_weapon_class_b        = 500;
      d1000_chance_of_creating_weapon_class_c        = 100;
      break;
    case 3:
      for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 1000;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = -1;
      }
      d1000_chance_of_creating_mob_challenge_class_a = 500;
      d1000_chance_of_creating_mob_challenge_class_b = 500;
      d1000_chance_of_creating_treasure_class_a      = 1000;
      d1000_chance_of_creating_treasure_class_b      = 1000;
      d1000_chance_of_creating_treasure_class_c      = 100;
      d1000_chance_of_creating_weapon_class_a        = 1000;
      d1000_chance_of_creating_weapon_class_b        = 500;
      d1000_chance_of_creating_weapon_class_c        = 200;
      break;
    case 4:
      for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 200;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 10;
      }
      d1000_chance_of_creating_mob_challenge_class_a = 500;
      d1000_chance_of_creating_mob_challenge_class_b = 500;
      d1000_chance_of_creating_treasure_class_a      = 1000;
      d1000_chance_of_creating_treasure_class_b      = 100;
      d1000_chance_of_creating_treasure_class_c      = 1000;
      d1000_chance_of_creating_weapon_class_a        = 1000;
      d1000_chance_of_creating_weapon_class_b        = 500;
      d1000_chance_of_creating_weapon_class_c        = 500;
      break;
    case 5:
      for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 100;
      }
      d1000_chance_of_creating_mob_challenge_class_a = 100;
      d1000_chance_of_creating_mob_challenge_class_b = 500;
      d1000_chance_of_creating_treasure_class_a      = 10;
      d1000_chance_of_creating_treasure_class_b      = 1000;
      d1000_chance_of_creating_treasure_class_c      = 1000;
      d1000_chance_of_creating_weapon_class_a        = 10;
      d1000_chance_of_creating_weapon_class_b        = 100;
      d1000_chance_of_creating_weapon_class_c        = 500;
      break;
    case 6:
      for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 500;
      }
      d1000_chance_of_creating_mob_challenge_class_a = 100;
      d1000_chance_of_creating_mob_challenge_class_b = 500;
      d1000_chance_of_creating_treasure_class_a      = 10;
      d1000_chance_of_creating_treasure_class_b      = 500;
      d1000_chance_of_creating_treasure_class_c      = 1000;
      d1000_chance_of_creating_weapon_class_a        = 10;
      d1000_chance_of_creating_weapon_class_b        = 10;
      d1000_chance_of_creating_weapon_class_c        = 1000;
      break;
    case 7:
      for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 100;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 500;
      }
      d1000_chance_of_creating_mob_challenge_class_a = 10;
      d1000_chance_of_creating_mob_challenge_class_b = 200;
      d1000_chance_of_creating_treasure_class_a      = 10;
      d1000_chance_of_creating_treasure_class_b      = 10;
      d1000_chance_of_creating_treasure_class_c      = 1000;
      d1000_chance_of_creating_weapon_class_a        = 10;
      d1000_chance_of_creating_weapon_class_b        = 500;
      d1000_chance_of_creating_weapon_class_c        = 1000;
      break;
    case 8:
      for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ] = 10;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ] = 500;
        d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ] = 1000;
      }
      d1000_chance_of_creating_mob_challenge_class_a = 10;
      d1000_chance_of_creating_mob_challenge_class_b = 10;
      d1000_chance_of_creating_treasure_class_a      = 10;
      d1000_chance_of_creating_treasure_class_b      = 10;
      d1000_chance_of_creating_treasure_class_c      = 1000;
      d1000_chance_of_creating_weapon_class_a        = 10;
      d1000_chance_of_creating_weapon_class_b        = 10;
      d1000_chance_of_creating_weapon_class_c        = 1000;
      break;
  }

  for (auto monst_type = (int) MONST_TYPE_NORMAL; monst_type < MONST_TYPE_MAX; monst_type++) {
    for (auto monst_class = (int) MONST_CLASS_A; monst_class < MONST_CLASS_MAX; monst_class++) {
      if (d1000_chance_of_creating_monst[ monst_type ][ monst_class ] > 1000) {
        d1000_chance_of_creating_monst[ monst_type ][ monst_class ] = 1000;
      }
    }
  }

  if (d1000_chance_of_creating_mob_challenge_class_a < 0) {
    d1000_chance_of_creating_mob_challenge_class_a = -1;
  }
  if (d1000_chance_of_creating_mob_challenge_class_a > 1000) {
    d1000_chance_of_creating_mob_challenge_class_a = 1000;
  }
  if (d1000_chance_of_creating_mob_challenge_class_b < 0) {
    d1000_chance_of_creating_mob_challenge_class_b = -1;
  }
  if (d1000_chance_of_creating_mob_challenge_class_b > 1000) {
    d1000_chance_of_creating_mob_challenge_class_b = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_a < 0) {
    d1000_chance_of_creating_treasure_class_a = -1;
  }
  if (d1000_chance_of_creating_treasure_class_a > 1000) {
    d1000_chance_of_creating_treasure_class_a = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_b < 0) {
    d1000_chance_of_creating_treasure_class_b = -1;
  }
  if (d1000_chance_of_creating_treasure_class_b > 1000) {
    d1000_chance_of_creating_treasure_class_b = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_c < 0) {
    d1000_chance_of_creating_treasure_class_c = -1;
  }
  if (d1000_chance_of_creating_treasure_class_c > 1000) {
    d1000_chance_of_creating_treasure_class_c = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_a < 0) {
    d1000_chance_of_creating_weapon_class_a = -1;
  }
  if (d1000_chance_of_creating_weapon_class_a > 1000) {
    d1000_chance_of_creating_weapon_class_a = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_b < 0) {
    d1000_chance_of_creating_weapon_class_b = -1;
  }
  if (d1000_chance_of_creating_weapon_class_b > 1000) {
    d1000_chance_of_creating_weapon_class_b = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_c < 0) {
    d1000_chance_of_creating_weapon_class_c = -1;
  }
  if (d1000_chance_of_creating_weapon_class_c > 1000) {
    d1000_chance_of_creating_weapon_class_c = 1000;
  }

  dbg("Chance of creating at difficulty depth %d:", difficulty_depth);
  auto monst_type = MONST_TYPE_NORMAL;
  dbg("- d1000 monst_class_a         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_A ]);
  dbg("- d1000 monst_class_b         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_B ]);
  dbg("- d1000 monst_class_c         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_C ]);
  dbg("- d1000 monst_class_d         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_D ]);
  dbg("- d1000 monst_class_e         %u", d1000_chance_of_creating_monst[ monst_type ][ MONST_CLASS_E ]);
  dbg("- d1000 mob_challenge_class_a %u", d1000_chance_of_creating_mob_challenge_class_a);
  dbg("- d1000 mob_challenge_class_b %u", d1000_chance_of_creating_mob_challenge_class_b);
  dbg("- d1000 treasure_class_a      %u", d1000_chance_of_creating_treasure_class_a);
  dbg("- d1000 treasure_class_b      %u", d1000_chance_of_creating_treasure_class_b);
  dbg("- d1000 treasure_class_c      %u", d1000_chance_of_creating_treasure_class_c);
  dbg("- d1000 weapon_class_a        %u", d1000_chance_of_creating_weapon_class_a);
  dbg("- d1000 weapon_class_b        %u", d1000_chance_of_creating_weapon_class_b);
  dbg("- d1000 weapon_class_c        %u", d1000_chance_of_creating_weapon_class_c);
}
