/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_room.h"

uint32_t                    Room::last_id = 0;
std::map< uint32_t, Roomp > Room::all_rooms;
