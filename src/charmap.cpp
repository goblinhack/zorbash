//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_charmap.hpp"
#include "my_sys.hpp"

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

  char_index      = Charmap::DRY_GRASS;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_dry_grass = true;

  char_index      = Charmap::WET_GRASS;
  c               = &all_charmaps[ char_index ];
  c->c            = char_index;
  c->is_wet_grass = true;

  char_index         = Charmap::ENCHANTSTONE;
  c                  = &all_charmaps[ char_index ];
  c->c               = char_index;
  c->is_enchantstone = true;

  char_index       = Charmap::SKILLSTONE;
  c                = &all_charmaps[ char_index ];
  c->c             = char_index;
  c->is_skillstone = true;

  char_index    = Charmap::FOILAGE;
  c             = &all_charmaps[ char_index ];
  c->c          = char_index;
  c->is_foilage = true;

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

  char_index          = Charmap::WAND_OR_STAFF;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_wand_or_staff = true;

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
  c->is_treasure_class_a = true;

  char_index             = Charmap::TREASURE_CLASS_B;
  c                      = &all_charmaps[ char_index ];
  c->c                   = char_index;
  c->is_treasure_class_b = true;

  char_index             = Charmap::TREASURE_CLASS_C;
  c                      = &all_charmaps[ char_index ];
  c->c                   = char_index;
  c->is_treasure_class_c = true;

  char_index           = Charmap::WEAPON_CLASS_A;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_a = true;

  char_index           = Charmap::WEAPON_CLASS_B;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_b = true;

  char_index           = Charmap::WEAPON_CLASS_C;
  c                    = &all_charmaps[ char_index ];
  c->c                 = char_index;
  c->is_weapon_class_c = true;

  char_index          = Charmap::MONST_CLASS_A;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_a = true;

  char_index          = Charmap::MONST_CLASS_B;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_c = true;

  char_index          = Charmap::MONST_CLASS_C;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_c = true;

  char_index          = Charmap::MONST_CLASS_D;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_d = true;

  char_index          = Charmap::MONST_CLASS_E;
  c                   = &all_charmaps[ char_index ];
  c->c                = char_index;
  c->is_monst_class_e = true;

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
  c->is_mob_challenge_class_a = true;

  char_index                  = Charmap::MOB_SPAWNER_CLASS_B;
  c                           = &all_charmaps[ char_index ];
  c->c                        = char_index;
  c->is_mob_challenge_class_a = true;
}
