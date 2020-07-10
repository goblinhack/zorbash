//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#include "my_main.h"
#include "my_point.h"
#include "my_size.h"

void wid_minicon_fini(void);
uint8_t wid_minicon_init(void);
void wid_minicon_log(std::wstring s);
void wid_minicon_log(std::string s);
void wid_minicon_flush(void);

#include "my_wid.h"

//
// Global widgets.
//
extern Widp wid_minicon_input_line;
extern Widp wid_minicon_window;
extern Widp wid_minicon_container;

std::vector<std::wstring> wid_minicon_serialize(void);
void wid_minicon_deserialize(std::vector<std::wstring> r);

