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
    static Rooms all_random_rooms;
    static Rooms all_fixed_rooms;

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
    uint32_t                 roomno {};
    std::vector<std::string> data[Charmap::DEPTH_MAX];
    int                      width {};
    int                      height {};

    static Roomp fixed_room_new(void);
    static Roomp random_room_new(void);
    void finalize(void);
};
