//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

void wid_minicon_fini(void);
uint8_t wid_minicon_init(void);
void wid_minicon_log(std::wstring s);
void wid_minicon_log(std::string s);
void wid_minicon_flush(void);

#include "my_wid.h"

//
// Global widgets.
//
extern widp wid_minicon_input_line;
extern widp wid_minicon_window;
extern widp wid_minicon_container;

#include "my_sdl.h"
