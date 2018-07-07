/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

void wid_console_fini(void);
uint8_t wid_console_init(void);
void wid_console_log(std::wstring s);
void wid_console_log(std::string s);
void wid_console_hello(void);

/*
 * Global widgets.
 */
extern widp wid_console_input_line;
extern widp wid_console_window;
extern widp wid_console_container;

#include "my_sdl.h"

uint8_t wid_console_receive_input(widp w, const SDL_KEYSYM *key);
