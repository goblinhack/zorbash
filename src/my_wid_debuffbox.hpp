//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
void    wid_debuffbox_fini(void);
uint8_t wid_debuffbox_init(void);

#include "my_wid.hpp"

//
// Global widgets.
//
extern void wid_debuffbox_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void        wid_debuffbox_mouse_over_end(Widp w);
