//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

#include "my_fwd.hpp"
#include "my_point.hpp"
#include <cstdint>

bool wid_inventory_create_ascii(Thingp, Thingp);
bool wid_inventory_create_pixelart(Thingp, Thingp);
bool wid_inventory_create(Thingp, Thingp);
bool wid_inventory_init(void);
bool wid_inventory_over(Thingp);
bool wid_inventory_select(Thingp);

uint8_t wid_inventory_close(Widp w, int x, int y, uint32_t button);
uint8_t wid_inventory_item_option_drop(Widp w, int x, int y, uint32_t button);
uint8_t wid_inventory_item_option_eat(Widp w, int x, int y, uint32_t button);
uint8_t wid_inventory_item_option_throw(Widp w, int x, int y, uint32_t button);
uint8_t wid_inventory_item_option_use_radial(Widp w, int x, int y, uint32_t button);
uint8_t wid_inventory_item_option_use(Widp w, int x, int y, uint32_t button);
uint8_t wid_inventory_item_option_unequip(Widp w, int x, int y, uint32_t button);
uint8_t wid_inventory_key_down(Widp w, const struct SDL_Keysym *key);
uint8_t wid_inventory_key_up(Widp w, const struct SDL_Keysym *key);
uint8_t wid_right_bar_inventory_open(class Wid *w, int x, int y, uint32_t button);
uint8_t wid_slot_item_mouse_up(Widp w, int x, int y, uint32_t button);

void wid_inventory_add_equip(Widp parent, int equip, point tl, point br, const char *wid_name);
void wid_inventory_add_equip(Widp parent, int equip, point tl, point br, const char *wid_name, const char *tile_name);
void wid_inventory_fini(bool remake = false);
void wid_inventory_mouse_over_tab_bag1(Widp w, int x, int y, int wheelx, int wheely);
void wid_inventory_mouse_over_tab_bag2(Widp w, int x, int y, int wheelx, int wheely);
void wid_inventory_over_requested(Thingp over);
void wid_inventory_select_requested(Thingp selected);
void wid_slot_item_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_slot_item_mouse_over_end(Widp w);

extern class WidBag   *wid_inventory_bag;
extern class WidPopup *wid_inventory_thing_info;
extern class Wid      *wid_inventory_window;

extern Thingp wid_inventory_thing_over;
extern Thingp wid_inventory_thing_selected;

extern int wid_inventory_tab;

enum {
  WID_INVENTORY_TAB_BAG1,
  WID_INVENTORY_TAB_BAG2,
  WID_INVENTORY_TAB_SLOT,
};
