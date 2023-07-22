//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_charmap.hpp"

std::vector< Charmap > Charmap::all_charmaps;

void Charmap::init_charmaps(void)
{
  all_charmaps.resize(255);

  auto char_index = Charmap::SPACE;
  auto c          = &all_charmaps[ char_index ];
  c->c            = char_index;

  char_index = Charmap::NONE;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;

  char_index = Charmap::WALL;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_wall = true;

  char_index = Charmap::ROCK;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_rock = true;

  char_index  = Charmap::FLOOR;
  c           = &all_charmaps[ char_index ];
  c->c        = char_index;
  c->is_floor = true;

  char_index            = Charmap::SECRET_CORRIDOR;
  c                     = &all_charmaps[ char_index ];
  c->c                  = char_index;
  c->is_secret_corridor = true;

  char_index   = Charmap::TELEPORT;
  c            = &all_charmaps[ char_index ];
  c->c         = char_index;
  c->is_portal = true;

  char_index     = Charmap::CORRIDOR;
  c              = &all_charmaps[ char_index ];
  c->c           = char_index;
  c->is_corridor = true;

  char_index   = Charmap::BRIDGE;
  c            = &all_charmaps[ char_index ];
  c->c         = char_index;
  c->is_bridge = true;

  char_index = Charmap::DIRT;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_dirt = true;

  char_index      = Charmap::GRASS_DRY;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_grass_dry = true;

  char_index      = Charmap::GRASS_WET;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_grass_wet = true;

  char_index            = Charmap::FUNGUS_WITHERED;
  c                     = &all_charmaps[ char_index ];
  c->c                  = char_index;
  c->is_fungus_withered = true;

  char_index          = Charmap::FUNGUS_EDIBLE;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_fungus_edible = true;

  char_index          = Charmap::FUNGUS_POISON;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_fungus_poison = true;

  char_index        = Charmap::MAGIC_STONE;
  c                 = &all_charmaps[ char_index ];
  c->c              = char_index;
  c->is_magic_stone = true;

  char_index    = Charmap::FOLIAGE;
  c             = &all_charmaps[ char_index ];
  c->c          = char_index;
  c->is_foliage = true;

  char_index      = Charmap::SPIDERWEB;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_spiderweb = true;

  char_index         = Charmap::ICE;
  c                  = &all_charmaps[ char_index ];
  c->c               = char_index;
  c->is_block_of_ice = true;

  char_index = Charmap::DOOR;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index = Charmap::DOOR_UP;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index = Charmap::DOOR_DOWN;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index = Charmap::DOOR_LEFT;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index = Charmap::DOOR_RIGHT;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index        = Charmap::SECRET_DOOR;
  c                 = &all_charmaps[ char_index ];
  c->c              = char_index;
  c->is_secret_door = true;

  char_index           = Charmap::ENTRANCE;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_ascend_dungeon = true;

  char_index       = Charmap::DECO;
  c                = &all_charmaps[ char_index ];
  c->c             = char_index;
  c->is_floor_deco = true;

  char_index            = Charmap::EXIT;
  c                     = &all_charmaps[ char_index ];
  c->c                  = char_index;
  c->is_descend_dungeon = true;

  char_index = Charmap::KEY;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_key  = true;

  char_index   = Charmap::POTION;
  c            = &all_charmaps[ char_index ];
  c->c         = char_index;
  c->is_potion = true;

  char_index  = Charmap::STAFF;
  c           = &all_charmaps[ char_index ];
  c->c        = char_index;
  c->is_staff = true;

  char_index = Charmap::RING;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_ring = true;

  char_index = Charmap::GOLD;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_gold = true;

  char_index = Charmap::LAVA;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_lava = true;

  char_index  = Charmap::CHASM;
  c           = &all_charmaps[ char_index ];
  c->c        = char_index;
  c->is_chasm = true;

  char_index          = Charmap::SHALLOW_WATER;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_shallow_water = true;

  char_index       = Charmap::DEEP_WATER;
  c                = &all_charmaps[ char_index ];
  c->c             = char_index;
  c->is_deep_water = true;

  char_index             = Charmap::TREASURE_CLASS_A;
  c                      = &all_charmaps[ char_index ];
  c->c                   = char_index;
  c->is_treasure_class_A = true;

  char_index             = Charmap::TREASURE_CLASS_B;
  c                      = &all_charmaps[ char_index ];
  c->c                   = char_index;
  c->is_treasure_class_B = true;

  char_index             = Charmap::TREASURE_CLASS_C;
  c                      = &all_charmaps[ char_index ];
  c->c                   = char_index;
  c->is_treasure_class_C = true;

  char_index           = Charmap::WEAPON_CLASS_A;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_A = true;

  char_index           = Charmap::WEAPON_CLASS_B;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_B = true;

  char_index           = Charmap::WEAPON_CLASS_C;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_C = true;

  char_index          = Charmap::MONST_CLASS_A;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_A = true;

  char_index          = Charmap::MONST_CLASS_B;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_C = true;

  char_index          = Charmap::MONST_CLASS_C;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_C = true;

  char_index          = Charmap::MONST_CLASS_D;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_D = true;

  char_index          = Charmap::MONST_CLASS_E;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_E = true;

  char_index = Charmap::FOOD;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_food = true;

  char_index      = Charmap::BLOOD;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_red_blood = true;

  char_index    = Charmap::BRAZIER;
  c             = &all_charmaps[ char_index ];
  c->c          = char_index;
  c->is_brazier = true;

  char_index   = Charmap::BARREL;
  c            = &all_charmaps[ char_index ];
  c->c         = char_index;
  c->is_barrel = true;

  char_index = Charmap::TRAP;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_trap = true;

  char_index = Charmap::DEBUG;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;

  char_index                  = Charmap::MOB_SPAWNER_CLASS_A;
  c                           = &all_charmaps[ char_index ];
  c->c                        = char_index;
  c->is_mob_challenge_class_A = true;

  char_index                  = Charmap::MOB_SPAWNER_CLASS_B;
  c                           = &all_charmaps[ char_index ];
  c->c                        = char_index;
  c->is_mob_challenge_class_A = true;
}
