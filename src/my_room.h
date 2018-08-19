/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_charmap.h"

typedef std::shared_ptr< class Room > Roomp;
typedef std::vector<Roomp> Rooms;

class Room
{
private:
public:
    static uint32_t room_count;
    static Rooms all_rooms;

    Room (void)
    {
        this->roomno = this->room_count;
        this->room_count++;

        newptr(this, "room");
    }

    ~Room (void)
    {
        oldptr(this);
    }

    /*
     * Unique per room.
     */
    uint32_t                 roomno {0};
    std::vector<std::string> data[Charmap::DEPTH_MAX];
    int                      width {};
    int                      height {};
    
    /*
     * All possible exits
     */
    std::vector<point>       left_exits;
    std::vector<point>       right_exits;
    std::vector<point>       up_exits;
    std::vector<point>       down_exits;
    
    /***********************************************************************
     * This is all room status that changes when rooms are placed.
     * The above is const.
     ***********************************************************************/
    point                    at {};
    point                    rollback_at {};
    
    /*
     * Set when a node uses this room
     */
    uint32_t                 depth {0};

    /*
     * Final placement of this room in the dungeon. 
     */
    bool                     placed {false};

    
    point                   left_door_at;
    point                   right_door_at;
    point                   up_door_at;
    point                   down_door_at;
    
    point                   left_secret_door_at;
    point                   right_secret_door_at;
    point                   up_secret_door_at;
    point                   down_secret_door_at;
    
    Roomp                   left_room {};
    Roomp                   right_room {};
    Roomp                   up_room {};
    Roomp                   down_room {};
    
    Roomp                   secret_left_room {};
    Roomp                   secret_right_room {};
    Roomp                   secret_up_room {};
    Roomp                   secret_down_room {};

    static Roomp room_new(void);

    void create_rotated_clones(void);
    void find_exits(void);
    void finalize(void);
};
