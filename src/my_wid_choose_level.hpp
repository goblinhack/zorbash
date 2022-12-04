/*
 * Copyright (C) 2011-2015 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#pragma once

void wid_show_dungeon_contents(Levelp l);
void wid_choose_levels_bg(void);
void wid_choose_level_border(Widp b, Levelp l);

point3d wid_choose_level_grid_to_level_coord(int x, int y);
uint8_t wid_choose_next_dungeons_enter(Widp w, int x, int y, uint32_t button);

extern WidPopup *wid_level_contents;
