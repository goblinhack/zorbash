//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
void    wid_skillbox_fini(void);
uint8_t wid_skillbox_init(void);


//
// Global widgets.
//
extern void wid_skillbox_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void        wid_skillbox_mouse_over_end(Widp w);
uint8_t     wid_skillbox_item_mouse_up(Widp w, int x, int y, uint32_t button);
