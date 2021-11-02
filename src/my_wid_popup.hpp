//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_UI_WID_POPUP_HPP_
#define _MY_UI_WID_POPUP_HPP_

#include "my_main.hpp"
#include "my_wid_text_box.hpp"

class WidPopup
{
private:
  std::map< unsigned int, std::wstring > wid_popup_lines;
  std::vector< Widp >                    children;

public:
  Widp        wid_popup_container {};
  Widp        wid_title {};
  WidTextBox *wid_text_area {};

  point       tl;
  point       br;
  Tilep       title_tile {};
  Thingp      t {};
  std::string background;

public:
  ~WidPopup();
  WidPopup(const std::string name, point tl, point br, Tilep title_tile = nullptr, const std::string background = "",
           bool horiz_scroll = true, bool vert_scoll = true, int vert_scroll_size = -1);

public:
  void log(std::string s, bool lhs = false, bool rhs = false);
  void log(std::wstring s, bool lhs = false, bool rhs = false);
};

extern void wid_popup_test(void);

extern void wid_collect_destroy(void);
extern void wid_enchant_destroy(void);
extern void wid_skill_choose_destroy(void);
extern void wid_load_destroy(void);
extern void wid_save_destroy(void);
extern void game_quit_destroy(void);
extern void game_config_keyboard_destroy(void);
extern bool wid_popup_exists(void);

extern WidPopup *wid_collect;
extern WidPopup *wid_skills;
extern WidPopup *wid_enchant;
extern WidPopup *wid_load;
extern WidPopup *wid_save;
extern WidPopup *game_quit_window;
extern WidPopup *game_config_keyboard_window;

#endif
