//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

void    wid_tp_info_fini(const std::string &why);
uint8_t wid_tp_info_init(void);

#include "my_wid_popup.hpp"

//
// Global widgets.
//
extern std::list< WidPopup * > wid_tp_info_window;
