//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
void wid_collect_fini(void);
uint8_t wid_collect_init(void);

#include "my_wid.h"
#include "my_wid_popup.h"

//
// Global widgets.
//
extern WidPopup *wid_collect_window;
