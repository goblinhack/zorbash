//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

void    wid_botcon_fini(void);
uint8_t wid_botcon_init(void);
void    wid_botcon_log(std::wstring s);
void    wid_botcon_log(std::string s);
void    wid_botcon_flush(void);
void    wid_botcon_clear(void);


//
// Global widgets.
//
extern Widp wid_botcon_input_line;
extern Widp wid_botcon_window;
extern Widp wid_botcon_container;

std::vector< std::wstring > wid_botcon_serialize(void);
void                        wid_botcon_deserialize(std::vector< std::wstring > r);
