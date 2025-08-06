//
// Copyright goblinhack@gmail.com
//

#pragma once
void    wid_spellbox_fini(void);
uint8_t wid_spellbox_init(void);

//
// Global widgets.
//
extern void wid_spellbox_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void        wid_spellbox_mouse_over_end(Widp w);
uint8_t     wid_spellbox_item_mouse_up(Widp w, int x, int y, uint32_t button);
extern void wid_spell_mouse_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void        wid_spell_mouse_over_end(Widp w);
uint8_t     wid_spell_item_mouse_up(Widp w, int x, int y, uint32_t button);
