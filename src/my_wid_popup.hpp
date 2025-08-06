//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_UI_WID_POPUP_HPP_
#define _MY_UI_WID_POPUP_HPP_

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
  Tpp         tpp {};
  std::string background;
  std::string name;
  int         outer_w {};
  int         outer_h {};
  int         inner_w {};
  int         inner_h {};

public:
  ~WidPopup();
  WidPopup(const std::string name, point tl, point br, Tilep title_tile = nullptr, const std::string background = "",
           bool horiz_scroll = true, bool vert_scoll = true, int vert_scroll_size = -1);

public:
  void log(std::string s, wid_text_format format = TEXT_FORMAT_NONE, std::string color = "");
  void log(std::wstring s, wid_text_format format = TEXT_FORMAT_NONE, std::string color = "");

  //
  // Get rid of trailing empty lines
  //
  void compress(void);
};

#endif
