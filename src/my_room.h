//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_ROOM_H_
#define _MY_ROOM_H_

#include "my_main.h"
#include "my_point.h"
#include "my_depth.h"
#include "my_charmap.h"
#include <vector>

typedef class Room *Roomp;
typedef std::vector<Roomp> Rooms;

class Room
{
private:
public:
    static Rooms all_rooms;

    Room (void)
    {
        this->roomno = all_rooms.size();
        newptr(this, "room");
    }

    ~Room (void)
    {
        oldptr(this);
    }

    //
    // Unique per room.
    //
    uint32_t                roomno {0};
    uint8_t                 width  {MAP_ROOM_WIDTH};
    uint8_t                 height {MAP_ROOM_HEIGHT};

    std::array<
      std::array<
        std::array<char, MAP_DEPTH>, MAP_ROOM_HEIGHT>, MAP_ROOM_WIDTH> data {};

    bool                    has_door_up    {false};
    bool                    has_door_down  {false};
    bool                    has_door_left  {false};
    bool                    has_door_right {false};

    //
    // All doors in this room. We will choose one for connectivity.
    //
    std::vector<point>      doors_up;
    std::vector<point>      doors_down;
    std::vector<point>      doors_right;
    std::vector<point>      doors_left;

    //
    // And this is which door we chose from the above lists.
    //
    uint8_t                 which_secret_door_up {0};
    uint8_t                 which_secret_door_down {0};
    uint8_t                 which_secret_door_left {0};
    uint8_t                 which_secret_door_right {0};
    uint8_t                 which_door_up {0};
    uint8_t                 which_door_down {0};
    uint8_t                 which_door_left {0};
    uint8_t                 which_door_right {0};

    Roomp                   left_room {};
    Roomp                   right_room {};
    Roomp                   up_room {};
    Roomp                   down_room {};

    Roomp                   secret_left_room {};
    Roomp                   secret_right_room {};
    Roomp                   secret_up_room {};
    Roomp                   secret_down_room {};

    point                   left_door_at;
    point                   right_door_at;
    point                   up_door_at;
    point                   down_door_at;

    point                   left_secret_door_at;
    point                   right_secret_door_at;
    point                   up_secret_door_at;
    point                   down_secret_door_at;

    //
    // Temp used for skipping rooms in dungeon placement
    //
    bool                     skip {false};

    //
    // Direction is the flow of the level, like can a player only go one
    // way and not return
    //
    bool                    dir_up       {false};
    bool                    dir_down     {false};
    bool                    dir_left     {false};
    bool                    dir_right    {false};

    bool                    is_ascend_dungeon  {false};
    bool                    is_descend_dungeon      {false};
    bool                    is_lock      {false};
    bool                    is_key       {false};
    bool                    is_secret    {false};

    uint8_t                 depth {0};

    //
    // Final placement of this room in the dungeon.
    //
    bool                    placed {false};

    ////////////////////////////////////////////////////////////////////////
    // This is all room status that changes when rooms are placed.
    // The above is const.
    /////////////////////////////////////////////////////////////////////////
    point                   at {};
    point                   rollback_at {};

    static Roomp room_new(void);

    Roomp create_w_flip(void);
    Roomp rotate_clockwise(void);
    void find_doors(void);
    void finalize(void);
    void dump(void);
};

void room_init(void);
void room_fini(void);
#endif
