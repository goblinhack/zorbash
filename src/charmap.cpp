//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
// REMOVED #include "my_tile.h"
#include "my_charmap.h"

std::vector<Charmap> Charmap::all_charmaps;

void Charmap::init_charmaps (void)
{
    all_charmaps.resize(255);

    auto char_index         = Charmap::SPACE;
    auto c = &all_charmaps[char_index];
    c->c                    = char_index;

    char_index              = Charmap::NONE;
    c = &all_charmaps[char_index];
    c->c                    = char_index;

    char_index              = Charmap::WALL;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_wall              = true;

    char_index              = Charmap::ROCK;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_rock              = true;

    char_index              = Charmap::FLOOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_floor             = true;

    char_index              = Charmap::SECRET_CORRIDOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_secret_corridor   = true;

    char_index              = Charmap::CORRIDOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_corridor          = true;

    char_index              = Charmap::DIRT;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_dirt              = true;

    char_index              = Charmap::DOOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_door              = true;

    char_index              = Charmap::DOOR_UP;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_door              = true;

    char_index              = Charmap::DOOR_DOWN;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_door              = true;

    char_index              = Charmap::DOOR_LEFT;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_door              = true;

    char_index              = Charmap::DOOR_RIGHT;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_door              = true;

    char_index              = Charmap::SECRET_DOOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_secret_door       = true;

    char_index              = Charmap::ENTRANCE;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_entrance          = true;

    char_index              = Charmap::DECO;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_floor_deco        = true;

    char_index              = Charmap::EXIT;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_exit              = true;

    char_index              = Charmap::KEY;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_key               = true;

    char_index              = Charmap::POTION;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_potion            = true;

    char_index              = Charmap::GOLD;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_gold              = true;

    char_index              = Charmap::LAVA;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_lava              = true;

    char_index              = Charmap::CHASM;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_chasm             = true;

    char_index              = Charmap::WATER;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_water             = true;

    char_index              = Charmap::DEEP_WATER;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_deep_water        = true;

    char_index              = Charmap::TREASURE_CLASS_A;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_treasure_class_a  = true;

    char_index              = Charmap::TREASURE_CLASS_B;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_treasure_class_b  = true;

    char_index              = Charmap::TREASURE_CLASS_C;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_treasure_class_c  = true;

    char_index              = Charmap::MONST;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_monst             = true;

    char_index              = Charmap::FOOD;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_food              = true;

    char_index              = Charmap::BLOOD;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_blood             = true;

    char_index              = Charmap::BRAZIER;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_torch           = true;

    char_index              = Charmap::TRAP;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_trap              = true;

    char_index              = Charmap::DEBUG;
    c = &all_charmaps[char_index];
    c->c                    = char_index;

    char_index              = Charmap::GENERATOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_generator         = true;
}
