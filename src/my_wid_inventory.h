//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
void wid_inventory_fini(void);
uint8_t wid_inventory_init(void);

#include "my_wid.h"

//
// Global widgets.
//
void wid_inventory_mouse_over_b(Widp w, int32_t relx, int32_t rely,
                int32_t wheelx, int32_t wheely);
void wid_inventory_mouse_over_e(Widp w);
uint8_t wid_inventory_item_mouse_up_on_bag(Widp w,
                       int32_t x,
                       int32_t y,
                       uint32_t button);
uint8_t wid_inventory_item_mouse_up(Widp w,
                  int32_t x,
                  int32_t y,
                  uint32_t button);
