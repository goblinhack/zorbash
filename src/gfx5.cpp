//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_tile.h"

void gfx_init5 (void)
{
    {
        std::initializer_list<std::string> tiles = {
            "ui_popup",
        };
        std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup.tga", "ui_popup", 80, 152, arr);
    }

    {
        std::initializer_list<std::string> tiles = {
            "ui_popup_short",
        };
        std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup_short.tga", "ui_popup_short", 80, 34, arr);
    }

    {
        std::initializer_list<std::string> tiles = {
            "ui_popup_notice",
        };
        std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup_notice.tga", "ui_popup_notice", 80, 34, arr);
    }

    {
        std::initializer_list<std::string> tiles = {
            "ui_popup_wide",
        };
        std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup_wide.tga", "ui_popup_wide", 120, 152, arr);
    }

    {
        std::initializer_list<std::string> tiles = {
            "ui_popup_widest",
        };
        std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup_widest.tga", "ui_popup_widest", 320, 152, arr);
    }
}
