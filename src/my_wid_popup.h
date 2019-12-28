//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#include "my_wid.h"
#include "my_wid_text_box.h"

class WidPopup {
private:
    std::map< unsigned int, std::wstring > wid_popup_lines;

    Widp wid_popup_container {};
    Widp wid_title {};

    std::vector<Widp> children;

public:
    WidTextBox *wid_text_area {};

    point tl;
    point br;
    Tilep title_tile;

public:
    ~WidPopup();
    WidPopup (point tl, point br, Tilep title_tile=nullptr);

public:
    void log(std::string s);
    void log(std::wstring s);
};
