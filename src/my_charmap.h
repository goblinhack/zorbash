//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_CMAP_H_
#define _MY_CMAP_H_

class Charmap;
class Charmap {
public:
    enum {
        NONE            = '\0',
        BLOOD           = 'b',
        BRAZIER         = 'B',
        CHASM           = 'C',
        CORRIDOR        = '#',
        DEBUG           = '@',
        DECO            = '|',
        DEEP_WATER      = 'W',
        DIRT            = ',',
        DOOR            = 'D',
        DOOR_DOWN       = 'v',
        DOOR_LEFT       = '<',
        DOOR_RIGHT      = '>',
        DOOR_UP         = '^',
        ENTRANCE        = 'S',
        EXIT            = 'E',
        FLOOR           = '.',
        FOOD            = 'f',
        GOLD            = 'g',
        KEY             = 'k',
        POTION          = 'p',
        LAVA            = 'L',
        MONST           = 'm',
        ROCK            = 'r',
        SECRET_CORRIDOR = '?',
        SECRET_DOOR     = 'd',
        SPACE           = ' ',
        TRAP            = 'i',
        TREASURE        = '$',
        WALL            = 'x',
        WATER           = 'w',
        GENERATOR       = '%',
    };

    char                      c;
    bool                      is_blood             {false};
    bool                      is_chasm             {false};
    bool                      is_corridor          {false};
    bool                      is_deep_water        {false};
    bool                      is_dirt              {false};
    bool                      is_door              {false};
    bool                      is_entrance          {false};
    bool                      is_exit              {false};
    bool                      is_floor             {false};
    bool                      is_floor_deco        {false};
    bool                      is_food              {false};
    bool                      is_gold              {false};
    bool                      is_key               {false};
    bool                      is_potion            {false};
    bool                      is_lava              {false};
    bool                      is_monst             {false};
    bool                      is_rock              {false};
    bool                      is_secret_corridor   {false};
    bool                      is_secret_door       {false};
    bool                      is_torch             {false};
    bool                      is_trap              {false};
    bool                      is_treasure          {false};
    bool                      is_wall              {false};
    bool                      is_wall_deco         {false};
    bool                      is_water             {false};
    bool                      is_generator         {false};

    static std::vector<Charmap> all_charmaps;
    static void init_charmaps(void);
};
#endif
