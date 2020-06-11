//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
void game_status_fini(void);
uint8_t game_status_wid_init(void);

#include "my_wid.h"

//
// Global widgets.
//
extern Widp game_status_window;

extern bool is_mouse_over_actionbar(void);
