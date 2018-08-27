/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#pragma once

class Charmap;
class Charmap {
public:
    enum {
        NONE            = '\0',
        SPACE           = ' ',
        CORRIDOR        = '#',
        SECRET_DOOR     = 'd',
        DOOR            = 'D',
        WALL            = 'x',
        LADDER          = 'H',
        FLOOR           = '.',
        SECRET_CORRIDOR = '?',
        ENTRANCE        = 'S',
        EXIT            = 'E',
        KEY             = 'k',
        LAVA            = 'L',
        WATER           = '_',
        ROCK            = 'r',
        TREASURE        = '$',
        TRAP            = 'i',
        MONST           = 'm',
        DEBUG           = '@',
    };

    enum {
        DEPTH_UNDER,
        DEPTH_FLOOR,
        DEPTH_WALLS,
        DEPTH_ITEMS,
        DEPTH_MAX,
    };

    char                      c;
    bool                      is_wall              {false};
    bool                      is_ladder            {false};
    bool                      is_floor             {false};
    bool                      is_dusty             {false};
    bool                      is_door              {false};
    bool                      is_secret_door       {false};
    bool                      is_entrance          {false};
    bool                      is_exit              {false};
    bool                      is_key               {false};
    bool                      is_lava              {false};
    bool                      is_water             {false};
    bool                      is_rock              {false};
    bool                      is_treasure          {false};
    bool                      is_monst             {false};
    bool                      is_trap              {false};

    static std::vector<Charmap> all_charmaps;
    static void init_charmaps(void);
};
