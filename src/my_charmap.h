//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#ifndef _MY_CMAP_H_
#define _MY_CMAP_H_

#include <vector>

class Charmap
{
public:
  enum {
    BARREL                = 'b',
    BLOOD                 = '_',
    BRAZIER               = 'B',
    BRIDGE                = '=',
    CHASM                 = 'C',
    CORRIDOR              = '#',
    DEBUG                 = '@',
    DECO                  = '|',
    DEEP_WATER            = 'W',
    DIRT                  = ',',
    ENCHANTSTONE          = '*',
    SKILLSTONE            = '&',
    DOOR                  = 'D',
    DOOR_DOWN             = 'v',
    DOOR_LEFT             = '<',
    DOOR_RIGHT            = '>',
    DOOR_UP               = '^',
    DRY_GRASS             = '\'',
    ENTRANCE              = 'S',
    EXIT                  = 'E',
    FLOOR                 = '.',
    FOILAGE               = '`',
    SPIDERWEB             = 'X',
    FOOD                  = 'f',
    GOLD                  = 'o',
    KEY                   = 'k',
    LAVA                  = 'L',
    MINION_GENERATOR_EASY = 'g',
    MINION_GENERATOR_HARD = 'G',
    MONST_EASY            = 'm',
    MONST_MED             = 'M',
    MONST_HARD            = 'H',
    NONE                  = '\0',
    POTION                = '!',
    ROCK                  = 'r',
    SECRET_CORRIDOR       = '?',
    SECRET_DOOR           = 's',
    SEWER                 = 'O',
    SHALLOW_WATER         = 'w',
    SPACE                 = ' ',
    TRAP                  = 't',
    TREASURE_CLASS_A      = '$',
    TREASURE_CLASS_B      = '2',
    TREASURE_CLASS_C      = '3',
    WALL                  = 'x',
    WAND                  = '/',
  };

  char c;
  bool is_blood {false};
  bool is_chasm {false};
  bool is_corridor {false};
  bool is_bridge {false};
  bool is_deep_water {false};
  bool is_dirt {false};
  bool is_dry_grass {false};
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
  bool is_minion_generator_hard {false};
  bool is_minion_generator_easy {false};
  bool is_monst_easy {false};
  bool is_monst_med {false};
  bool is_monst_hard {false};
  bool is_potion {false};
  bool is_wand {false};
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
  bool is_wall {false};

  static std::vector< Charmap > all_charmaps;
  static void                   init_charmaps(void);
};
#endif
