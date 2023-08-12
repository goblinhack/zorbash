//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_charmap.hpp"

std::vector< Charmap > Charmap::all_charmaps;

void Charmap::init_charmaps(void)
{
  all_charmaps.resize(255);

  auto char_index = Charmap::CHAR_SPACE;
  auto c          = &all_charmaps[ char_index ];
  c->c            = char_index;

  char_index = Charmap::CHAR_NONE;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;

  char_index = Charmap::CHAR_WALL;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_wall = true;

  char_index = Charmap::CHAR_ROCK;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_rock = true;

  char_index  = Charmap::CHAR_FLOOR;
  c           = &all_charmaps[ char_index ];
  c->c        = char_index;
  c->is_floor = true;

  char_index            = Charmap::CHAR_SECRET_CORRIDOR;
  c                     = &all_charmaps[ char_index ];
  c->c                  = char_index;
  c->is_secret_corridor = true;

  char_index   = Charmap::CHAR_TELEPORT;
  c            = &all_charmaps[ char_index ];
  c->c         = char_index;
  c->is_portal = true;

  char_index     = Charmap::CHAR_CORRIDOR;
  c              = &all_charmaps[ char_index ];
  c->c           = char_index;
  c->is_corridor = true;

  char_index   = Charmap::CHAR_BRIDGE;
  c            = &all_charmaps[ char_index ];
  c->c         = char_index;
  c->is_bridge = true;

  char_index = Charmap::CHAR_DIRT;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_dirt = true;

  char_index      = Charmap::CHAR_GRASS_DRY;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_grass_dry = true;

  char_index      = Charmap::CHAR_GRASS_WET;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_grass_wet = true;

  char_index            = Charmap::CHAR_FUNGUS_WITHERED;
  c                     = &all_charmaps[ char_index ];
  c->c                  = char_index;
  c->is_fungus_withered = true;

  char_index           = Charmap::CHAR_FUNGUS_HEALING;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_fungus_healing = true;

  char_index          = Charmap::CHAR_FUNGUS_EDIBLE;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_fungus_edible = true;

  char_index          = Charmap::CHAR_FUNGUS_POISON;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_fungus_poison = true;

  char_index        = Charmap::CHAR_MAGIC_STONE;
  c                 = &all_charmaps[ char_index ];
  c->c              = char_index;
  c->is_magic_stone = true;

  char_index    = Charmap::CHAR_FOLIAGE;
  c             = &all_charmaps[ char_index ];
  c->c          = char_index;
  c->is_foliage = true;

  char_index      = Charmap::CHAR_SPIDERWEB;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_spiderweb = true;

  char_index         = Charmap::CHAR_ICE;
  c                  = &all_charmaps[ char_index ];
  c->c               = char_index;
  c->is_block_of_ice = true;

  char_index = Charmap::CHAR_DOOR;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index = Charmap::CHAR_DOOR_UP;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index = Charmap::CHAR_DOOR_DOWN;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index = Charmap::CHAR_DOOR_LEFT;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index = Charmap::CHAR_DOOR_RIGHT;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_door = true;

  char_index        = Charmap::CHAR_SECRET_DOOR;
  c                 = &all_charmaps[ char_index ];
  c->c              = char_index;
  c->is_secret_door = true;

  char_index           = Charmap::CHAR_ENTRANCE;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_ascend_dungeon = true;

  char_index       = Charmap::CHAR_DECO;
  c                = &all_charmaps[ char_index ];
  c->c             = char_index;
  c->is_floor_deco = true;

  char_index            = Charmap::CHAR_EXIT;
  c                     = &all_charmaps[ char_index ];
  c->c                  = char_index;
  c->is_descend_dungeon = true;

  char_index = Charmap::CHAR_KEY;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_key  = true;

  char_index   = Charmap::CHAR_POTION;
  c            = &all_charmaps[ char_index ];
  c->c         = char_index;
  c->is_potion = true;

  char_index  = Charmap::CHAR_STAFF;
  c           = &all_charmaps[ char_index ];
  c->c        = char_index;
  c->is_staff = true;

  char_index = Charmap::CHAR_RING;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_ring = true;

  char_index = Charmap::CHAR_GOLD;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_gold = true;

  char_index = Charmap::CHAR_LAVA;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_lava = true;

  char_index  = Charmap::CHAR_CHASM;
  c           = &all_charmaps[ char_index ];
  c->c        = char_index;
  c->is_chasm = true;

  char_index          = Charmap::CHAR_SHALLOW_WATER;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_shallow_water = true;

  char_index       = Charmap::CHAR_DEEP_WATER;
  c                = &all_charmaps[ char_index ];
  c->c             = char_index;
  c->is_deep_water = true;

  char_index             = Charmap::CHAR_TREASURE_CLASS_A;
  c                      = &all_charmaps[ char_index ];
  c->c                   = char_index;
  c->is_treasure_class_A = true;

  char_index             = Charmap::CHAR_TREASURE_CLASS_B;
  c                      = &all_charmaps[ char_index ];
  c->c                   = char_index;
  c->is_treasure_class_B = true;

  char_index             = Charmap::CHAR_TREASURE_CLASS_C;
  c                      = &all_charmaps[ char_index ];
  c->c                   = char_index;
  c->is_treasure_class_C = true;

  char_index           = Charmap::CHAR_WEAPON_CLASS_A;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_A = true;

  char_index           = Charmap::CHAR_WEAPON_CLASS_B;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_B = true;

  char_index           = Charmap::CHAR_WEAPON_CLASS_C;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_C = true;

  char_index          = Charmap::CHAR_MONST_CLASS_A;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_A = true;

  char_index          = Charmap::CHAR_MONST_CLASS_B;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_C = true;

  char_index          = Charmap::CHAR_MONST_CLASS_C;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_C = true;

  char_index          = Charmap::CHAR_MONST_CLASS_D;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_D = true;

  char_index          = Charmap::CHAR_MONST_CLASS_E;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_E = true;

  char_index = Charmap::CHAR_FOOD;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_food = true;

  char_index      = Charmap::CHAR_BLOOD;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_red_blood = true;

  char_index    = Charmap::CHAR_BRAZIER;
  c             = &all_charmaps[ char_index ];
  c->c          = char_index;
  c->is_brazier = true;

  char_index   = Charmap::CHAR_BARREL;
  c            = &all_charmaps[ char_index ];
  c->c         = char_index;
  c->is_barrel = true;

  char_index = Charmap::CHAR_TRAP;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;
  c->is_trap = true;

  char_index = Charmap::CHAR_DEBUG;
  c          = &all_charmaps[ char_index ];
  c->c       = char_index;

  char_index                  = Charmap::CHAR_MOB_SPAWNER_CLASS_A;
  c                           = &all_charmaps[ char_index ];
  c->c                        = char_index;
  c->is_mob_challenge_class_A = true;

  char_index                  = Charmap::CHAR_MOB_SPAWNER_CLASS_B;
  c                           = &all_charmaps[ char_index ];
  c->c                        = char_index;
  c->is_mob_challenge_class_A = true;
}
