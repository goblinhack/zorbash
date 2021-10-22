//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#include "my_fwd.h"
#include "my_sys.h"

void wid_inventory_fini(void);
bool wid_inventory_init(void);
bool wid_inventory_over(Thingp);
bool wid_inventory_select(Thingp);
bool wid_inventory_create(Thingp, Thingp);
void wid_inventory_over_requested(Thingp over);
void wid_inventory_select_requested(Thingp selected);

extern class Wid *     wid_inventory_window;
extern class WidBag *  wid_inventory_bag;
extern class WidPopup *wid_inventory_thing_info;
extern Thingp wid_inventory_thing_selected;
extern Thingp wid_inventory_thing_over;

//
// Global widgets.
//
uint8_t wid_right_bar_inventory_open(class Wid *w, int32_t x, int32_t y, uint32_t button);
