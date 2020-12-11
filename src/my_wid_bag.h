//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_UI_WID_BAG_H_
#define _MY_UI_WID_BAG_H_

#include "my_main.h"
#include "my_wid.h"

class WidBag {
private:
    std::vector<Widp> children;

public:
    Widp wid_bag_container {};
    Widp wid_bag_title {};

    point       tl;
    point       br;

public:
    ~WidBag();
    WidBag (Thingp bag, point tl, point br, const std::string &title);
};

bool is_mouse_over_any_bag(void);

#endif
