//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_CMAP_H_
#define _MY_CMAP_H_

class Charmap;
class Charmap {
public:
    enum {
        NONE            = '\0',
        SPACE           = ' ',
        CORRIDOR        = '#',
        SECRET_DOOR     = 'd',
        DOOR            = 'D',
        DOOR_UP         = '^',
        DOOR_DOWN       = 'v',
        DOOR_LEFT       = '<',
        DOOR_RIGHT      = '>',
        WALL            = 'x',
        DECO            = '|',
        WALL_DECO       = 'X',
        FLOOR           = '.',
        DIRT            = ',',
        SECRET_CORRIDOR = '?',
        ENTRANCE        = 'S',
        EXIT            = 'E',
        KEY             = 'k',
        LAVA            = 'L',
        WATER           = 'w',
        DEEP_WATER      = 'W',
        ROCK            = 'r',
        TREASURE        = '$',
        TRAP            = 'i',
        MONST           = 'm',
        FOOD            = 'f',
        BLOOD           = 'b',
        DEBUG           = '@',
    };

    char                      c;
    bool                      is_wall              {false};
    bool                      is_rock              {false};
    bool                      is_floor             {false};
    bool                      is_corridor          {false};
    bool                      is_dirt              {false};
    bool                      is_secret_corridor   {false};
    bool                      is_door              {false};
    bool                      is_secret_door       {false};
    bool                      is_entrance          {false};
    bool                      gfx_is_floor_deco    {false};
    bool                      gfx_is_wall_deco     {false};
    bool                      is_exit              {false};
    bool                      is_key               {false};
    bool                      is_lava              {false};
    bool                      is_water             {false};
    bool                      is_deep_water        {false};
    bool                      is_treasure          {false};
    bool                      is_monst             {false};
    bool                      is_food              {false};
    bool                      is_blood             {false};
    bool                      is_trap              {false};

    static std::vector<Charmap> all_charmaps;
    static void init_charmaps(void);
};
#endif
