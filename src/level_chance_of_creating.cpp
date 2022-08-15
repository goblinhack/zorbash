//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Level::chances_of_creating_set(void)
{
  TRACE_AND_INDENT();

  switch (difficulty_depth) {
    default: DIE("Unexpected difficulty depth %d", difficulty_depth);
    case 1:
      d1000_chance_of_creating_monst_class_a         = 1000;
      d1000_chance_of_creating_monst_class_b         = 10;
      d1000_chance_of_creating_monst_class_c         = 10;
      d1000_chance_of_creating_monst_class_d         = 0;
      d1000_chance_of_creating_monst_class_e         = 0;
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
      d1000_chance_of_creating_monst_class_a         = 1000;
      d1000_chance_of_creating_monst_class_b         = 100;
      d1000_chance_of_creating_monst_class_c         = 10;
      d1000_chance_of_creating_monst_class_d         = 0;
      d1000_chance_of_creating_monst_class_e         = 0;
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
      d1000_chance_of_creating_monst_class_a         = 1000;
      d1000_chance_of_creating_monst_class_b         = 500;
      d1000_chance_of_creating_monst_class_c         = 100;
      d1000_chance_of_creating_monst_class_d         = 10;
      d1000_chance_of_creating_monst_class_e         = 0;
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
      d1000_chance_of_creating_monst_class_a         = 200;
      d1000_chance_of_creating_monst_class_b         = 500;
      d1000_chance_of_creating_monst_class_c         = 500;
      d1000_chance_of_creating_monst_class_d         = 100;
      d1000_chance_of_creating_monst_class_e         = 10;
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
      d1000_chance_of_creating_monst_class_a         = 100;
      d1000_chance_of_creating_monst_class_b         = 500;
      d1000_chance_of_creating_monst_class_c         = 500;
      d1000_chance_of_creating_monst_class_d         = 500;
      d1000_chance_of_creating_monst_class_e         = 100;
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
      d1000_chance_of_creating_monst_class_a         = 10;
      d1000_chance_of_creating_monst_class_b         = 10;
      d1000_chance_of_creating_monst_class_c         = 500;
      d1000_chance_of_creating_monst_class_d         = 500;
      d1000_chance_of_creating_monst_class_e         = 500;
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
      d1000_chance_of_creating_monst_class_a         = 10;
      d1000_chance_of_creating_monst_class_b         = 10;
      d1000_chance_of_creating_monst_class_c         = 100;
      d1000_chance_of_creating_monst_class_d         = 500;
      d1000_chance_of_creating_monst_class_e         = 500;
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
      d1000_chance_of_creating_monst_class_a         = 10;
      d1000_chance_of_creating_monst_class_b         = 10;
      d1000_chance_of_creating_monst_class_c         = 10;
      d1000_chance_of_creating_monst_class_d         = 500;
      d1000_chance_of_creating_monst_class_e         = 1000;
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

  if (d1000_chance_of_creating_monst_class_a < 0) {
    d1000_chance_of_creating_monst_class_a = 0;
  }
  if (d1000_chance_of_creating_monst_class_a > 1000) {
    d1000_chance_of_creating_monst_class_a = 1000;
  }
  if (d1000_chance_of_creating_monst_class_b < 0) {
    d1000_chance_of_creating_monst_class_b = 0;
  }
  if (d1000_chance_of_creating_monst_class_b > 1000) {
    d1000_chance_of_creating_monst_class_b = 1000;
  }
  if (d1000_chance_of_creating_monst_class_c < 0) {
    d1000_chance_of_creating_monst_class_c = 0;
  }
  if (d1000_chance_of_creating_monst_class_c > 1000) {
    d1000_chance_of_creating_monst_class_c = 1000;
  }
  if (d1000_chance_of_creating_monst_class_d < 0) {
    d1000_chance_of_creating_monst_class_d = 0;
  }
  if (d1000_chance_of_creating_monst_class_d > 1000) {
    d1000_chance_of_creating_monst_class_d = 1000;
  }
  if (d1000_chance_of_creating_monst_class_e < 0) {
    d1000_chance_of_creating_monst_class_e = 0;
  }
  if (d1000_chance_of_creating_monst_class_e > 1000) {
    d1000_chance_of_creating_monst_class_e = 1000;
  }
  if (d1000_chance_of_creating_mob_challenge_class_a < 0) {
    d1000_chance_of_creating_mob_challenge_class_a = 0;
  }
  if (d1000_chance_of_creating_mob_challenge_class_a > 1000) {
    d1000_chance_of_creating_mob_challenge_class_a = 1000;
  }
  if (d1000_chance_of_creating_mob_challenge_class_b < 0) {
    d1000_chance_of_creating_mob_challenge_class_b = 0;
  }
  if (d1000_chance_of_creating_mob_challenge_class_b > 1000) {
    d1000_chance_of_creating_mob_challenge_class_b = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_a < 0) {
    d1000_chance_of_creating_treasure_class_a = 0;
  }
  if (d1000_chance_of_creating_treasure_class_a > 1000) {
    d1000_chance_of_creating_treasure_class_a = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_b < 0) {
    d1000_chance_of_creating_treasure_class_b = 0;
  }
  if (d1000_chance_of_creating_treasure_class_b > 1000) {
    d1000_chance_of_creating_treasure_class_b = 1000;
  }
  if (d1000_chance_of_creating_treasure_class_c < 0) {
    d1000_chance_of_creating_treasure_class_c = 0;
  }
  if (d1000_chance_of_creating_treasure_class_c > 1000) {
    d1000_chance_of_creating_treasure_class_c = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_a < 0) {
    d1000_chance_of_creating_weapon_class_a = 0;
  }
  if (d1000_chance_of_creating_weapon_class_a > 1000) {
    d1000_chance_of_creating_weapon_class_a = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_b < 0) {
    d1000_chance_of_creating_weapon_class_b = 0;
  }
  if (d1000_chance_of_creating_weapon_class_b > 1000) {
    d1000_chance_of_creating_weapon_class_b = 1000;
  }
  if (d1000_chance_of_creating_weapon_class_c < 0) {
    d1000_chance_of_creating_weapon_class_c = 0;
  }
  if (d1000_chance_of_creating_weapon_class_c > 1000) {
    d1000_chance_of_creating_weapon_class_c = 1000;
  }

  log("Chance of creating at difficulty depth %d:", difficulty_depth);
  log("- d1000 monst_class_a         %u", d1000_chance_of_creating_monst_class_a);
  log("- d1000 monst_class_b         %u", d1000_chance_of_creating_monst_class_b);
  log("- d1000 monst_class_c         %u", d1000_chance_of_creating_monst_class_c);
  log("- d1000 monst_class_d         %u", d1000_chance_of_creating_monst_class_d);
  log("- d1000 monst_class_e         %u", d1000_chance_of_creating_monst_class_e);
  log("- d1000 mob_challenge_class_a %u", d1000_chance_of_creating_mob_challenge_class_a);
  log("- d1000 mob_challenge_class_b %u", d1000_chance_of_creating_mob_challenge_class_b);
  log("- d1000 treasure_class_a      %u", d1000_chance_of_creating_treasure_class_a);
  log("- d1000 treasure_class_b      %u", d1000_chance_of_creating_treasure_class_b);
  log("- d1000 treasure_class_c      %u", d1000_chance_of_creating_treasure_class_c);
  log("- d1000 weapon_class_a        %u", d1000_chance_of_creating_weapon_class_a);
  log("- d1000 weapon_class_b        %u", d1000_chance_of_creating_weapon_class_b);
  log("- d1000 weapon_class_c        %u", d1000_chance_of_creating_weapon_class_c);
}
