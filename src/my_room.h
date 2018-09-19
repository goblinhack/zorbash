/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_charmap.h"
#include "my_game.h"

typedef std::shared_ptr< class Room > Roomp;
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

    /*
     * Unique per room.
     */
    uint32_t                roomno {0};
    uint8_t                 width  {ROOM_WIDTH};
    uint8_t                 height {ROOM_HEIGHT};

    char                    data[ROOM_WIDTH][ROOM_HEIGHT][MAP_DEPTH] = {{{' '}}};
    
    /*
     * A bitmap of possible exits.
     */
    uint16_t                left_exits;
    uint16_t                right_exits;
    uint16_t                up_exits;
    uint16_t                down_exits;

    bool                    has_exit_up    {false};
    bool                    has_exit_down  {false};
    bool                    has_exit_left  {false};
    bool                    has_exit_right {false};
    
    /*
     * Direction is the flow of the level, like can a player only go one
     * way and not return
     */
    bool                    dir_up       {false};
    bool                    dir_down     {false};
    bool                    dir_left     {false};
    bool                    dir_right    {false};

    bool                    is_entrance  {false};
    bool                    is_exit      {false};
    bool                    is_lock      {false};
    bool                    is_key       {false};
    bool                    is_secret    {false};

    uint8_t                 depth {0};

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
