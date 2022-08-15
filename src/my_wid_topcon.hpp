//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_sdl.hpp"
#include "my_size.hpp"

void    wid_topcon_fini(void);
uint8_t wid_topcon_init(void);
void    wid_topcon_log(std::wstring s);
void    wid_topcon_log(std::string s);
void    wid_topcon_flush(void);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_topcon_input_line;
extern Widp wid_topcon_window;
extern Widp wid_topcon_container;

extern std::vector< std::wstring > wid_topcon_serialize(void);
extern void                        wid_topcon_deserialize(std::vector< std::wstring > r);
extern uint8_t                     wid_topcon_input(Widp w, const SDL_Keysym *key);
