//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#include "my_wid.h"

class WidPopup {
private:
    std::map< unsigned int, std::wstring > wid_popup_lines;
    int width {};
    int height {};
    int line_count {};
    int scroll_height {};

    Widp wid_popup_container {};
    Widp wid_popup_vert_scroll {};
    Widp wid_popup_horiz_scroll {};
    Widp wid_popup_input_line {};
    Widp wid_popup_window {};

    std::vector<Widp> children;

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
