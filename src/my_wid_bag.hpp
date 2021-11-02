//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_UI_WID_BAG_HPP_
#define _MY_UI_WID_BAG_HPP_

#include "my_wid.hpp"

class WidBag
{
private:
  std::vector< Widp > children;

public:
  Widp wid_bag_container {};

  point  tl;
  point  br;
  Thingp bag;

public:
  ~WidBag();
  WidBag(Widp parent, Thingp bag, bool highlight, point tl, point br, const std::string &title);
};

Widp is_mouse_over_any_bag(void);

void wid_bag_item_mouse_over_begin(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
void wid_bag_item_mouse_over_end(Widp w);

uint8_t wid_in_transit_item_place(Widp w, int32_t x, int32_t y, uint32_t button);
uint8_t wid_in_transit_item_drop(void);
uint8_t wid_bag_item_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button);
uint8_t wid_bag_item_mouse_held(Widp w, int32_t x, int32_t y, uint32_t button);
uint8_t wid_bag_item_key_down(Widp w, const struct SDL_Keysym *key);

#endif
