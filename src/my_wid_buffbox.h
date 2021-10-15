//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
void    wid_buffbox_fini(void);
uint8_t wid_buffbox_init(void);

#include "my_wid.h"

//
// Global widgets.
//
extern void wid_buffbox_mouse_over_b(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
void        wid_buffbox_mouse_over_e(Widp w);
