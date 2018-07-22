/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

typedef std::shared_ptr< class Room > Roomp;
typedef std::map< uint32_t, Roomp > Rooms;

class Room
{
private:
public:
    static uint32_t last_id;
    static Rooms all_rooms;

    Room (void)
    {
        this->id = ++this->last_id;

        newptr(this, "room");
    }

    ~Room (void)
    {
        oldptr(this);
    }

    /*
     * Unique per room.
     */
    uint32_t                 id {};
    std::vector<std::string> floor_data;
    std::vector<std::string> walls_data;
    std::vector<std::string> items_data;
    int                      width {};
    int                      height {};

    static Roomp room_new (void);
    void finalize(void);
};
