/*
 * Copyright (C) 2011-2015 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#pragma once

#include "my_level.hpp"

void wid_show_dungeon_contents(Levelp l);
void wid_choose_dungeons_bg(void);
void wid_choose_dungeon_border(Widp b, Levelp l);

point3d wid_choose_dungeon_grid_to_level_coord(int x, int y);

extern WidPopup *wid_level_contents;
