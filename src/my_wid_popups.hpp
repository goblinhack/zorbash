//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_UI_WID_POPUPS_HPP_
#define _MY_UI_WID_POPUPS_HPP_


extern void wid_collect_destroy(void);
extern void wid_enchant_destroy(void);
extern void wid_choose_skill_destroy(void);
extern void wid_load_destroy(void);
extern void wid_save_destroy(void);
extern void wid_quit_destroy(void);
extern void wid_config_keyboard_destroy(void);
extern bool wid_popup_exists(void);

extern WidPopup *wid_collect;
extern WidPopup *wid_skills;
extern WidPopup *wid_enchant;
extern WidPopup *wid_load;
extern WidPopup *wid_save;
extern WidPopup *wid_quit_window;
extern WidPopup *wid_config_keyboard_window;
extern WidPopup *wid_config_top_window;
extern WidPopup *wid_main_menu_window;

#endif
