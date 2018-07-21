/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_room.h"

uint32_t                    Room::last_id = 0;
std::map< uint32_t, Roomp > Room::all_rooms;

Roomp Room::room_new (void)
{_
    auto r = std::make_shared< class Room >();
    Room::all_rooms.insert(std::make_pair(r->id, r));
    return (r);
}
