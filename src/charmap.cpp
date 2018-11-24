/*
 * Copyright (C) 2018 goblinhack@gmail.com
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
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
    
    char_index              = Charmap::FLOOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_floor             = true;

    char_index              = Charmap::SECRET_CORRIDOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_dusty             = true;

    char_index              = Charmap::DOOR;
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
    c->is_entrance    = true;

    char_index              = Charmap::EXIT;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_exit  = true;

    char_index              = Charmap::KEY;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_key               = true;

    char_index              = Charmap::LAVA;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_lava              = true;

    char_index              = Charmap::WATER;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_water             = true;

    char_index              = Charmap::ROCK;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_rock              = true;

    char_index              = Charmap::TREASURE;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_treasure          = true;

    char_index              = Charmap::MONST;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_monst             = true;
    
    char_index              = Charmap::TRAP;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->is_trap              = true;
    
    char_index              = Charmap::DEBUG;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
}
