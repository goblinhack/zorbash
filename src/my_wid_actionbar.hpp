//
// Copyright goblinhack@gmail.com
//

#pragma once

void wid_actionbar_fini(void);
void wid_actionbar_init(void);
void wid_actionbar_robot_mode_toggle(void);
void wid_actionbar_robot_mode_off(void);
void wid_actionbar_close_all_popups(void);
void wid_actionbar_robot_mode_update(void);

extern Widp wid_actionbar;

uint8_t wid_actionbar_ascend(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_close(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_collect(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_configure(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_descend(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_inventory(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_load(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_quit(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_repeat_wait(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_robot(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_save(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_wait(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_zoom_in(Widp w, int x, int y, uint32_t button);
uint8_t wid_actionbar_zoom_out(Widp w, int x, int y, uint32_t button);
void    wid_actionbar_ai_tick(Widp w);
void    wid_actionbar_ascend_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_ascend_over_end(Widp w);
void    wid_actionbar_close_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_close_over_end(Widp w);
void    wid_actionbar_collect_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_collect_over_end(Widp w);
void    wid_actionbar_configure_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_configure_over_end(Widp w);
void    wid_actionbar_descend_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_descend_over_end(Widp w);
void    wid_actionbar_inventory_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_inventory_over_end(Widp w);
void    wid_actionbar_load_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_load_over_end(Widp w);
void    wid_actionbar_quit_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_quit_over_end(Widp w);
void    wid_actionbar_robot_mode_off(void);
void    wid_actionbar_robot_mode_toggle(void);
void    wid_actionbar_robot_mode_update(void);
void    wid_actionbar_robot_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_robot_over_end(Widp w);
void    wid_actionbar_save_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_save_over_end(Widp w);
void    wid_actionbar_wait_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_wait_over_end(Widp w);
void    wid_actionbar_zoom_in_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_zoom_in_over_end(Widp w);
void    wid_actionbar_zoom_out_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void    wid_actionbar_zoom_out_over_end(Widp w);
void    wid_actionbar_ascii_init(void);
void    wid_actionbar_pixelart_init(void);
