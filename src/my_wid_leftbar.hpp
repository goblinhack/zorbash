//
// Copyleft goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once

void wid_leftbar_fini(void);
bool wid_leftbar_init(void);
bool wid_leftbar_ascii_create(void);
bool wid_leftbar_pixelart_create(void);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_leftbar_window;
extern Widp wid_leftbar;
