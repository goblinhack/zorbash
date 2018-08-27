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
    uint32_t                roomno {0};
    uint8_t                 width  {ROOM_WIDTH};
    uint8_t                 height {ROOM_HEIGHT};

    char                    data[ROOM_WIDTH][ROOM_HEIGHT][Charmap::DEPTH_MAX];
    
    /*
     * A bitmap of possible exits.
     */
    uint16_t                left_exits;
    uint16_t                right_exits;
    uint16_t                up_exits;
    uint16_t                down_exits;
    
    bool                    dir_up       {false};
    bool                    dir_down     {false};
    bool                    dir_left     {false};
    bool                    dir_right    {false};
    bool                    is_entrance  {false};
    bool                    is_exit      {false};
    bool                    is_lock      {false};
    bool                    is_key       {false};

    /*
     * Set when a node uses this room
     */
    uint32_t                depth {0};

    /*
     * Final placement of this room in the dungeon. 
     */
    bool                    placed {false};

    static Roomp room_new(void);

    void create_h_flip(void);
    void find_exits(void);
    void finalize(void);
    void dump(void);
};
