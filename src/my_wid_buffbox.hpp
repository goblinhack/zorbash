//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
void    wid_buffbox_fini(void);
uint8_t wid_buffbox_init(void);

// REMOVED #include "my_wid.hpp"

//
// Global widgets.
//
extern void wid_buffbox_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void        wid_buffbox_mouse_over_end(Widp w);
