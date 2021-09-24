//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_UI_WID_BAG_H_
#define _MY_UI_WID_BAG_H_

#include "my_wid.h"

class WidBag
{
private:
  std::vector< Widp > children;

public:
  Widp wid_bag_container {};
  Widp wid_bag_title {};

  point  tl;
  point  br;
  Thingp bag;

public:
  ~WidBag();
  WidBag(Thingp bag, bool highlight, point tl, point br, const std::string &title);
};

Widp    is_mouse_over_any_bag(void);
uint8_t wid_in_transit_item_place(Widp w, int32_t x, int32_t y, uint32_t button);
uint8_t wid_in_transit_item_drop(void);

#endif
