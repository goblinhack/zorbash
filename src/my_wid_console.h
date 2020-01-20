//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


void wid_console_fini(void);
uint8_t wid_console_init(void);
void wid_console_log(std::wstring s);
void wid_console_log(std::string s);
void wid_console_hello(void);

#include "my_wid.h"

//
// Global widgets.
//
extern Widp wid_console_input_line;
extern Widp wid_console_window;
extern Widp wid_console_container;


uint8_t wid_console_receive_input(Widp w, const SDL_KEYSYM *key);

std::vector<std::wstring> wid_console_serialize(void);
void wid_console_deserialize(std::vector<std::wstring> r);
