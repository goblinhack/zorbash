//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
void wid_inventory_fini(void);
uint8_t wid_inventory_init(void);

#include "my_wid.h"

//
// Global widgets.
//
extern Widp wid_inventory_window;

extern bool is_mouse_over_inventory(void);
