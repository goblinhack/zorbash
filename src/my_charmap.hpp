//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_CMAP_HPP_
#define _MY_CMAP_HPP_

#include <vector>

class Charmap
{
public:
  enum {
    // begin sort marker1 {
    CHAR_BARREL              = 'b',
    CHAR_BLOCK_OF_CRYSTAL    = 'c',
    CHAR_BLOCK_OF_ICE        = 'I',
    CHAR_BLOOD               = '_',
    CHAR_BRAZIER             = 'B',
    CHAR_BRIDGE              = '=',
    CHAR_CHASM               = 'C',
    CHAR_CORRIDOR            = '#',
    CHAR_DEBUG               = '@',
    CHAR_DECO                = '|',
    CHAR_DEEP_WATER          = 'W',
    CHAR_DIRT                = ',',
    CHAR_DOOR                = 'D',
    CHAR_DOOR_DOWN           = 'v',
    CHAR_DOOR_LEFT           = '<',
    CHAR_DOOR_RIGHT          = '>',
    CHAR_DOOR_UP             = '^',
    CHAR_ENTRANCE            = 'S',
    CHAR_EXIT                = 'E',
    CHAR_FLOOR               = '.',
    CHAR_FOLIAGE             = '`',
    CHAR_FOOD                = 'f',
    CHAR_FUNGUS_EDIBLE       = 'e',
    CHAR_FUNGUS_HEALING      = 'F',
    CHAR_FUNGUS_POISON       = 'p',
    CHAR_FUNGUS_WITHERED     = 'n',
    CHAR_GOLD                = 'o',
    CHAR_GRASS_DRY           = '\'',
    CHAR_GRASS_WET           = '"',
    CHAR_KEY                 = 'k',
    CHAR_LAVA                = 'L',
    CHAR_MAGIC_STONE         = '*',
    CHAR_MOB_SPAWNER_CLASS_A = 'g',
    CHAR_MOB_SPAWNER_CLASS_B = 'G',
    CHAR_MOB_SPAWNER_CLASS_C = 'P',
    CHAR_MONST_CLASS_A       = 'm',
    CHAR_MONST_CLASS_B       = 'M',
    CHAR_MONST_CLASS_C       = 'h',
    CHAR_MONST_CLASS_D       = 'H',
    CHAR_MONST_CLASS_E       = 'N',
    CHAR_NONE                = '\0',
    CHAR_POTION              = '!',
    CHAR_RING                = 'R',
    CHAR_ROCK                = 'r',
    CHAR_SECRET_CORRIDOR     = '?',
    CHAR_SECRET_DOOR         = 's',
    CHAR_SEWER               = 'O',
    CHAR_SHALLOW_WATER       = 'w',
    CHAR_SPACE               = ' ',
    CHAR_SPIDERWEB           = 'X',
    CHAR_STAFF               = '/',
    CHAR_TELEPORT            = 'T',
    CHAR_TRAP                = 't',
    CHAR_TREASURE_CLASS_A    = '$',
    CHAR_TREASURE_CLASS_B    = '2',
    CHAR_TREASURE_CLASS_C    = '3',
    CHAR_WALL                = 'x',
    CHAR_WEAPON_CLASS_A      = '(',
    CHAR_WEAPON_CLASS_B      = ')',
    CHAR_WEAPON_CLASS_C      = '-',
    // end sort marker1 }
  };

  // begin sort marker2 {
  bool is_ascend_dungeon {false};
  bool is_barrel {false};
  bool is_block_of_crystal {false};
  bool is_block_of_ice {false};
  bool is_brazier {false};
  bool is_bridge {false};
  bool is_chasm {false};
  bool is_corridor {false};
  bool is_deep_water {false};
  bool is_descend_dungeon {false};
  bool is_descend_sewer {false};
  bool is_dirt {false};
  bool is_door {false};
  bool is_floor_deco {false};
  bool is_floor {false};
  bool is_foliage {false};
  bool is_food {false};
  bool is_fungus_edible {false};
  bool is_fungus {false};
  bool is_fungus_healing {false};
  bool is_fungus_poison {false};
  bool is_fungus_withered {false};
  bool is_gold {false};
  bool is_grass_dry {false};
  bool is_grass_wet {false};
  bool is_key {false};
  bool is_lava {false};
  bool is_magic_stone {false};
  bool is_mob_class_A {false};
  bool is_mob_class_B {false};
  bool is_mob_class_C {false};
  bool is_monst_class_A {false};
  bool is_monst_class_B {false};
  bool is_monst_class_C {false};
  bool is_monst_class_D {false};
  bool is_monst_class_E {false};
  bool is_portal {false};
  bool is_potion {false};
  bool is_red_blood {false};
  bool is_ring {false};
  bool is_rock {false};
  bool is_secret_corridor {false};
  bool is_secret_door {false};
  bool is_shallow_water {false};
  bool is_spiderweb {false};
  bool is_staff {false};
  bool is_trap {false};
  bool is_treasure_class_A {false};
  bool is_treasure_class_B {false};
  bool is_treasure_class_C {false};
  bool is_wall {false};
  bool is_weapon_class_A {false};
  bool is_weapon_class_B {false};
  bool is_weapon_class_C {false};
  // end sort marker2 }

  char c;

  static std::vector< Charmap > all_charmaps;
  static void                   init_charmaps(void);
};
#endif
