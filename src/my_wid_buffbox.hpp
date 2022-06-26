//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
void    wid_buffbox_fini(void);
uint8_t wid_buffbox_init(void);

#include "my_wid.hpp"

//
// Global widgets.
//
extern void wid_buffbox_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void        wid_buffbox_mouse_over_end(Widp w);
