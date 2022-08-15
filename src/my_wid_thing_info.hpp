//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#include <string>

void    wid_thing_info_fini(const std::string &why);
uint8_t wid_thing_info_init(void);

#include "my_wid.hpp"
#include "my_wid_popup.hpp"

//
// Global widgets.
//
extern std::list< WidPopup * > wid_thing_info_window;
