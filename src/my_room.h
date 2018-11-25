/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
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
    
    bool                    has_door_up    {false};
    bool                    has_door_down  {false};
    bool                    has_door_left  {false};
    bool                    has_door_right {false};
    std::list<point>        door_up_at;
    std::list<point>        door_down_at;
    std::list<point>        door_right_at;
    std::list<point>        door_left_at;
    
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

    Roomp create_h_flip(void);
    Roomp rotate_clockwise(void);
    void find_doors(void);
    void finalize(void);
    void dump(void);
};
