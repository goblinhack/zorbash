//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_CMAP_H_
#define _MY_CMAP_H_

#include <vector>

class Charmap {
public:
    enum {
        BLOOD            =            '_',
        BRAZIER          =            'B',
        BARREL           =            'b',
        CHASM            =            'C',
        CORRIDOR         =            '#',
        BRIDGE           =            '=',
        DEBUG            =            '@',
        DECO             =            '|',
        DEEP_WATER       =            'W',
        DIRT             =            ',',
        DRY_GRASS        =            '\'',
        DOOR             =            'D',
        DOOR_DOWN        =            'v',
        DOOR_LEFT        =            '<',
        DOOR_RIGHT       =            '>',
        DOOR_UP          =            '^',
        ENTRANCE         =            'S',
        EXIT             =            'E',
        SEWER            =            'O',
        FLOOR            =            '.',
        FOOD             =            'f',
        MINION_GENERATOR_EASY =       'g',
        MINION_GENERATOR_HARD =       'G',
        GOLD             =            'o',
        KEY              =            'k',
        LAVA             =            'L',
        MONST_EASY       =            'm',
        MONST_HARD       =            'M',
        NONE             =            '\0',
        POTION           =            '!',
        WAND             =            '/',
        ROCK             =            'r',
        SECRET_CORRIDOR  =            '?',
        SECRET_DOOR      =            's',
        SPACE            =            ' ',
        TRAP             =            't',
        TREASURE_CLASS_A =            '$',
        TREASURE_CLASS_B =            '2',
        TREASURE_CLASS_C =            '3',
        WALL             =            'x',
        SHALLOW_WATER    =            'w',
    };

    char                      c;
    bool                      is_blood                        {false};
    bool                      is_chasm                        {false};
    bool                      is_corridor                     {false};
    bool                      is_bridge                       {false};
    bool                      is_deep_water                   {false};
    bool                      is_dirt                         {false};
    bool                      is_dry_grass                    {false};
    bool                      is_door                         {false};
    bool                      is_ascend_dungeon               {false};
    bool                      is_descend_dungeon              {false};
    bool                      is_descend_sewer                {false};
    bool                      is_floor                        {false};
    bool                      is_floor_deco                   {false};
    bool                      is_food                         {false};
    bool                      is_gold                         {false};
    bool                      is_key                          {false};
    bool                      is_lava                         {false};
    bool                      is_minion_generator_hard        {false};
    bool                      is_minion_generator_easy        {false};
    bool                      is_monst_easy                   {false};
    bool                      is_monst_hard                   {false};
    bool                      is_potion                       {false};
    bool                      is_wand                         {false};
    bool                      is_rock                         {false};
    bool                      is_secret_corridor              {false};
    bool                      is_secret_door                  {false};
    bool                      is_shallow_water                {false};
    bool                      is_brazier                      {false};
    bool                      is_barrel                       {false};
    bool                      is_trap                         {false};
    bool                      is_treasure_class_a             {false};
    bool                      is_treasure_class_b             {false};
    bool                      is_treasure_class_c             {false};
    bool                      is_wall                         {false};

    static std::vector<Charmap> all_charmaps;
    static void init_charmaps(void);
};
#endif
