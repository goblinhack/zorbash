//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
void    wid_skillbox_fini(void);
uint8_t wid_skillbox_init(void);

#include "my_wid.h"

//
// Global widgets.
//
extern void wid_skillbox_mouse_over_begin(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
void        wid_skillbox_mouse_over_end(Widp w);
uint8_t     wid_skillbox_item_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button);
