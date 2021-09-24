//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
void    wid_thing_info_fini(void);
uint8_t wid_thing_info_init(void);

#include "my_wid.h"
#include "my_wid_popup.h"

//
// Global widgets.
//
extern std::list< WidPopup * > wid_thing_info_window;
