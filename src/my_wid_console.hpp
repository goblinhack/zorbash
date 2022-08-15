//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#include "my_main.hpp"

void    wid_console_fini(void);
uint8_t wid_console_init(void);
void    wid_console_log(std::wstring s);
void    wid_console_log(std::string s);
void    wid_console_hello(void);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_console_input_line;
extern Widp wid_console_window;
extern Widp wid_console_container;

uint8_t wid_console_receive_input(Widp w, const SDL_Keysym *key);

std::vector< std::wstring > wid_console_serialize(void);
void                        wid_console_deserialize(std::vector< std::wstring > r);
