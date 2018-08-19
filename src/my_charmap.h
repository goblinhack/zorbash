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
        SECRET_DOOR     = '$',
        DOOR            = 'D',
        WALL            = 'x',
        CWALL           = 'X',
        FLOOR           = '.',
        SECRET_CORRIDOR = '?',
        START           = 'S',
        EXIT            = 'E',
        KEY             = 'k',
        CHASM           = 'C',
        LAVA            = 'L',
        WATER           = '_',
        ROCK            = 'r',
        TREASURE        = '$',
        DEBUG           = '@',
    };

    enum {
        DEPTH_UNDER,
        DEPTH_FLOOR,
        DEPTH_WALLS,
        DEPTH_ITEMS,
        DEPTH_MAX,
    };

    std::string               fg;
    std::string               bg;
    char                      c;
    bool                      is_movement_blocking {false};
    bool                      is_wall              {false};
    bool                      is_cwall             {false};
    bool                      is_floor             {false};
    bool                      is_dusty             {false};
    bool                      is_corridor          {false};
    bool                      is_door              {false};
    bool                      is_secret_door       {false};
    bool                      is_dungeon_way_up    {false};
    bool                      is_dungeon_way_down  {false};
    bool                      is_key               {false};
    bool                      is_chasm             {false};
    bool                      is_dissolves_walls   {false};
    bool                      is_lava              {false};
    bool                      is_water             {false};
    bool                      is_rock              {false};
    bool                      is_treasure          {false};

    static std::vector<Charmap> all_charmaps;
    static void init_charmaps(void);
};
