//
// Copyright goblinhack@gmail.com
//

#pragma once

void wid_rightbar_fini(void);
bool wid_rightbar_init(void);
bool wid_rightbar_ascii_create(void);
void wid_rightbar_stats_over_def_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_stat_str_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_stat_att_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_stat_con_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_stat_dex_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_stat_luck_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_stat_thv_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_stat_psi_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_stat_int_b(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_popup_e(Widp w);
void wid_rightbar_inventory_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_inventory_over_end(Widp w);
void wid_rightbar_stats_over_begin(Widp w, int relx, int rely, int wheelx, int wheely);
void wid_rightbar_stats_over_end(Widp w);
bool wid_rightbar_pixelart_create(void);
bool wid_rightbar_asciimap_create(void);

#include "my_wid.hpp"

//
// Global widgets.
//
extern Widp wid_rightbar_window;
extern Widp wid_map_mini;
extern Widp wid_rightbar;

extern bool is_mouse_over_rightbar(void);
