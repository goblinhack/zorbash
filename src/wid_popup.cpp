//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <SDL.h>

#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_text_box.hpp"
#include "slre.hpp"

WidPopup::~WidPopup()
{
  wid_destroy(&wid_popup_container);
  delete wid_text_area;
}

WidPopup::WidPopup(const std::string name, point tl, point br, Tilep title_tile, const std::string background,
                   bool horiz_scroll, bool vert_scoll, int scroll_height)
    : tl(tl), br(br), title_tile(title_tile), background(background)
{
  TRACE_AND_INDENT();
  int outer_w = br.x - tl.x;
  int outer_h = br.y - tl.y;
  int width   = outer_w;
  int height  = outer_h;

  point inner_tl = point(0, 0);
  point inner_br = point(width, height);
  int   inner_w  = inner_br.x - inner_tl.x;
  int   inner_h  = inner_br.y - inner_tl.y;

  if (g_opt_ascii) {
    title_tile = nullptr;
  }

  int tile_size;
  if (title_tile) {
    tile_size = 4;
  } else {
    tile_size = 0;
  }

  if (title_tile) {
    inner_h -= tile_size;
    inner_tl.y += tile_size;
  }

  {
    wid_popup_container = wid_new_square_window("wid_popup " + name);
    wid_set_pos(wid_popup_container, tl, br);
    wid_set_style(wid_popup_container, UI_WID_STYLE_SOLID_NONE);
    if (background != "") {
      wid_set_bg_tile(wid_popup_container, tile_find_mand(background));
    } else {
      wid_set_style(wid_popup_container, UI_WID_STYLE_NORMAL);
    }
  }

  if (title_tile) {
    auto w       = wid_new_square_button(wid_popup_container, "wid title " + name);
    wid_title    = w;
    auto title_x = (outer_w - tile_size) / 2;
    wid_set_pos(w, point(title_x + 0, 1), point(title_x + tile_size - 1, tile_size));
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_style(w, UI_WID_STYLE_SPARSE_NONE);
    wid_set_fg_tile(w, title_tile);
  }

  {
    point tl      = make_point(0, tile_size);
    point br      = make_point(inner_w, inner_h + tile_size);
    wid_text_area = new WidTextBox(tl, br, wid_popup_container, horiz_scroll, vert_scoll, scroll_height);
  }

  wid_update(wid_popup_container);
}

//
// Log a message to the popup
//
void WidPopup::log(std::string s, wid_text_format format, std::string color)
{
  TRACE_AND_INDENT();
  wid_text_area->log(s, format, color);
}

//
// Log a message to the popup
//
void WidPopup::log(std::wstring s, wid_text_format format, std::string color)
{
  TRACE_AND_INDENT();
  wid_text_area->log(s, format, color);
}

//
// Get rid of trailing empty lines
//
void WidPopup::compress(void)
{
  TRACE_NO_INDENT();

  int utilized = wid_text_area->line_count;
  wid_resize(wid_popup_container, -1, utilized + 1);
}
