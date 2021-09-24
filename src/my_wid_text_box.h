//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_WID_TEXT_BOX_H_
#define _MY_WID_TEXT_BOX_H_

#include "my_main.h"
#include "my_wid.h"

class WidTextBox
{
private:
  std::map< unsigned int, std::wstring > wid_text_box_lines;
  int                                    width {};
  int                                    height {};
  int                                    scroll_height {};

  std::vector< Widp > children;

public:
  int   line_count {};
  point tl;
  point br;
  Widp  wid_horiz_scroll {};
  Widp  wid_parent {};
  Widp  wid_text_area {};
  Widp  wid_text_box_container {};
  Widp  wid_text_last {};
  Widp  wid_vert_scroll {};

  ~WidTextBox();
  WidTextBox(point tl, point br, Widp, bool horiz_scroll = true, bool vert_scoll = true, int scroll_height = -1);

private:
  void log_(std::wstring str, bool lhs, bool rhs);

public:
  void log(std::string s, bool lhs = false, bool rhs = false);
  void log(std::wstring s, bool lhs = false, bool rhs = false);
};
#endif
