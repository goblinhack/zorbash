//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
void wid_inventory_fini(void);
bool wid_inventory_init(void);
bool wid_inventory_create(void);

#include "my_wid.h"
extern Widp wid_inventory_window;

//
// Global widgets.
//
uint8_t wid_right_bar_inventory_open(Widp w, int32_t x, int32_t y, uint32_t button);
