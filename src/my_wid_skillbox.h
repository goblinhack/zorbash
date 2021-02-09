//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
void wid_skillbox_fini(void);
uint8_t wid_skillbox_init(void);

#include "my_wid.h"

//
// Global widgets.
//
extern Widp wid_skillbox_window;

extern bool is_mouse_over_skillbox(void);
extern bool is_mouse_over_skillbox_slot(int &slot);
