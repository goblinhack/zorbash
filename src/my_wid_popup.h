//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_UI_WID_POPUP_H_
#define _MY_UI_WID_POPUP_H_

#include "my_main.h"
#include "my_wid_text_box.h"

class WidPopup {
private:
    std::map< unsigned int, std::wstring > wid_popup_lines;
    std::vector<Widp> children;

public:
    Widp wid_popup_container {};
    Widp wid_title {};
    WidTextBox *wid_text_area {};

    point       tl;
    point       br;
    Tilep       title_tile {};
    Thingp      t {};
    std::string background;

public:
    ~WidPopup();
    WidPopup (const std::string name,
              point tl, point br, 
              Tilep title_tile=nullptr,
              const std::string background = "",
              bool horiz_scroll=true,
              bool vert_scoll=true,
              int vert_scroll_size=-1);

public:
    void log(std::string s, bool lhs = false, bool rhs = false);
    void log(std::wstring s, bool lhs = false, bool rhs = false);
};

void wid_popup_test(void);
#endif
