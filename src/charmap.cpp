/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_charmap.h"

std::vector<Charmap> Charmap::all_charmaps;

void Charmap::init_charmaps (void)
{
    all_charmaps.resize(255);

    auto char_index        = Charmap::SPACE;
    auto c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "black";

    char_index              = Charmap::NONE;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "black";

    char_index             = Charmap::WALL;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "magenta";
    c->fg                   = "black";
    c->is_wall              = true;
    c->is_movement_blocking = true;

    char_index             = Charmap::CWALL;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "blue";
    c->fg                   = "black";
    c->is_cwall             = true;

    char_index             = Charmap::FLOOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "white";
    c->is_floor             = true;

    char_index             = Charmap::DUSTY;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "white";
    c->is_dusty             = true;

    char_index             = Charmap::CORRIDOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "yellow";
    c->is_corridor          = true;

    char_index             = Charmap::DOOR;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "green";
    c->fg                   = "green";
    c->is_door              = true;
    c->is_movement_blocking = true;

    char_index             = Charmap::START;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "white";
    c->fg                   = "red",
    c->is_dungeon_way_up    = true;
    c->is_movement_blocking = true;

    char_index             = Charmap::EXIT;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "white";
    c->fg                   = "red";
    c->is_dungeon_way_down  = true;
    c->is_movement_blocking = true;

    char_index             = Charmap::KEY;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "white";
    c->fg                   = "yellow";
    c->is_key               = true;
    c->is_movement_blocking = true;

    char_index             = Charmap::CHASM;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "black";
    c->is_chasm             = true;
    c->is_dissolves_walls   = true;

    char_index             = Charmap::LAVA;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "red";
    c->fg                   = "yellow";
    c->is_lava              = true;
    c->is_dissolves_walls   = true;

    char_index             = Charmap::WATER;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "blue";
    c->is_dissolves_walls   = true;

    char_index             = Charmap::ROCK;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "red";
    c->is_rock              = true;

    char_index             = Charmap::TREASURE;
    c = &all_charmaps[char_index];
    c->c                    = char_index;
    c->bg                   = "black";
    c->fg                   = "yellow";
    c->is_treasure          = true;
}
