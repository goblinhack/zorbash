//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_CMAP_HPP_
#define _MY_CMAP_HPP_

#include <vector>

class Charmap
{
public:
  enum {
    BARREL              = 'b',
    BLOOD               = '_',
    BRAZIER             = 'B',
    BRIDGE              = '=',
    CHASM               = 'C',
    CORRIDOR            = '#',
    DEBUG               = '@',
    DECO                = '|',
    DEEP_WATER          = 'W',
    DIRT                = ',',
    ENCHANTSTONE        = '*',
    SKILLSTONE          = '&',
    DOOR                = 'D',
    DOOR_DOWN           = 'v',
    DOOR_LEFT           = '<',
    DOOR_RIGHT          = '>',
    DOOR_UP             = '^',
    DRY_GRASS           = '\'',
    WET_GRASS           = '"',
    ENTRANCE            = 'S',
    EXIT                = 'E',
    FLOOR               = '.',
    FOILAGE             = '`',
    SPIDERWEB           = 'X',
    FOOD                = 'f',
    GOLD                = 'o',
    KEY                 = 'k',
    LAVA                = 'L',
    MOB_SPAWNER_CLASS_A = 'g',
    MOB_SPAWNER_CLASS_B = 'G',
    MONST_CLASS_A       = 'm',
    MONST_CLASS_B       = 'M',
    MONST_CLASS_C       = 'h',
    MONST_CLASS_D       = 'H',
    MONST_CLASS_E       = 'N',
    NONE                = '\0',
    POTION              = '!',
    ROCK                = 'r',
    SECRET_CORRIDOR     = '?',
    SECRET_DOOR         = 's',
    SEWER               = 'O',
    SHALLOW_WATER       = 'w',
    SPACE               = ' ',
    TRAP                = 't',
    TREASURE_CLASS_A    = '$',
    TREASURE_CLASS_B    = '2',
    TREASURE_CLASS_C    = '3',
    WEAPON_CLASS_A      = '(',
    WEAPON_CLASS_B      = ')',
    WEAPON_CLASS_C      = '-',
    WALL                = 'x',
    WAND                = '/',
    RING                = 'R',
  };

  char c;
  bool is_blood {false};
  bool is_chasm {false};
  bool is_corridor {false};
  bool is_bridge {false};
  bool is_deep_water {false};
  bool is_dirt {false};
  bool is_dry_grass {false};
  bool is_wet_grass {false};
  bool is_enchantstone {false};
  bool is_skillstone {false};
  bool is_foilage {false};
  bool is_spiderweb {false};
  bool is_door {false};
  bool is_ascend_dungeon {false};
  bool is_descend_dungeon {false};
  bool is_descend_sewer {false};
  bool is_floor {false};
  bool is_floor_deco {false};
  bool is_food {false};
  bool is_gold {false};
  bool is_key {false};
  bool is_lava {false};
  bool is_mob_spawner_class_b {false};
  bool is_mob_spawner_class_a {false};
  bool is_monst_class_a {false};
  bool is_monst_class_b {false};
  bool is_monst_class_c {false};
  bool is_monst_class_d {false};
  bool is_monst_class_e {false};
  bool is_potion {false};
  bool is_wand {false};
  bool is_ring {false};
  bool is_rock {false};
  bool is_secret_corridor {false};
  bool is_secret_door {false};
  bool is_shallow_water {false};
  bool is_brazier {false};
  bool is_barrel {false};
  bool is_trap {false};
  bool is_treasure_class_a {false};
  bool is_treasure_class_b {false};
  bool is_treasure_class_c {false};
  bool is_weapon_class_a {false};
  bool is_weapon_class_b {false};
  bool is_weapon_class_c {false};
  bool is_wall {false};

  static std::vector< Charmap > all_charmaps;
  static void                   init_charmaps(void);
};
#endif
