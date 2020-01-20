//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_WID_POPUP_H_
#define _MY_WID_POPUP_H_
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
    Tilep       title_tile;
    std::string background;

public:
    ~WidPopup();
    WidPopup (point tl, point br, Tilep title_tile=nullptr,
              std::string background = "ui_popup");

public:
    void log(std::string s);
    void log(std::wstring s);
};
#endif
