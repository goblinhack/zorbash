//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_WID_TEXT_BOX_H_
#define _MY_WID_TEXT_BOX_H_

#include "my_wid.h"

class WidTextBox {
private:
    std::map< unsigned int, std::wstring > wid_text_box_lines;
    int width {};
    int height {};
    int line_count {};
    int scroll_height {};

    std::vector<Widp> children;

public:
    point tl;
    point br;
    Widp wid_horiz_scroll {};
    Widp wid_parent {};
    Widp wid_text_area {};
    Widp wid_text_box_container {};
    Widp wid_text_last {};
    Widp wid_vert_scroll {};

    ~WidTextBox();
    WidTextBox (point tl, point br, Widp);

private:
    void log_(std::wstring str);

public:
    void log(std::string s);
    void log(std::wstring s);
};
#endif
