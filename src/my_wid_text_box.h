//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#include "my_wid.h"

class WidTextBox {
private:
    std::map< unsigned int, std::wstring > wid_text_box_lines;
    int width {};
    int height {};
    int line_count {};
    int scroll_height {};

    Widp wid_text_box_container {};
    Widp wid_vert_scroll {};
    Widp wid_horiz_scroll {};
    Widp wid_text_last {};
    Widp wid_text_area {};
    Widp wid_text_inner_area {};

    std::vector<Widp> children;

public:
    point tl;
    point br;
    Widp wid_parent {};

public:
    ~WidTextBox();
    WidTextBox (point tl, point br, Widp parent=nullptr);

private:
    void log_(std::wstring str);

public:
    void log(std::string s);
    void log(std::wstring s);
};
