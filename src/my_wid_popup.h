//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#include "my_wid.h"

class WidPopup : Wid {
private:
    std::map< unsigned int, std::wstring > wid_popup_lines;

    widp wid_popup_container {};
    widp wid_popup_vert_scroll {};
    widp wid_popup_horiz_scroll {};
    widp wid_popup_input_line {};
    widp wid_popup_window {};

public:
    point tl;
    point br;

public:
    ~WidPopup();
    WidPopup(point tl, point br);

private:
    void log_(std::wstring str);

public:
    void log(std::string s);
    void log(std::wstring s);
};
