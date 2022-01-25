//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_ttf.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_text_box.hpp"
#include "slre.hpp"

bool wid_popup_exists(void)
{
  return (wid_collect || wid_skills || wid_enchant || wid_load || wid_save || wid_config_keyboard_window ||
          wid_quit_window || wid_inventory_window);
}

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
void WidPopup::log(std::string s, bool lhs, bool rhs)
{
  TRACE_AND_INDENT();
  wid_text_area->log(s, lhs, rhs);
}

//
// Log a message to the popup
//
void WidPopup::log(std::wstring s, bool lhs, bool rhs)
{
  TRACE_AND_INDENT();
  wid_text_area->log(s, lhs, rhs);
}

void wid_popup_test(void)
{
  TRACE_AND_INDENT();
  std::vector< std::string > items;
  items.push_back("text 1111111111111111");
  items.push_back("text 2222222222222222");
  items.push_back("text 3333333333333333");
  items.push_back("text 4444444444444444");
  items.push_back("text 5555555555555555");
  items.push_back("text 1111111111111111");
  items.push_back("text 2222222222222222");
  items.push_back("text 3333333333333333");
  items.push_back("text 4444444444444444");
  items.push_back("text 5555555555555555");
  items.push_back("text 1111111111111111");
  items.push_back("text 2222222222222222");
  items.push_back("text 3333333333333333");
  items.push_back("text 4444444444444444");
  items.push_back("text 5555555555555555");

  point tl    = make_point(20, 20);
  point br    = make_point(50, 45);
  auto  width = br.x - tl.x;

  auto wid_enchant = new WidPopup("Top level", tl, br, nullptr, "", false, true);

  int y_at = 3;
  for (auto slot = 0; slot < (int) items.size(); slot++) {
    auto  p  = wid_enchant->wid_text_area->wid_text_area;
    auto  w  = wid_new_container(p, "item slot");
    point tl = make_point(0, y_at);
    point br = make_point(width - 3, y_at + 2);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);
    wid_set_text(w, "xxxxxxxxx");

    {
      auto  wid_icon = wid_new_square_button(w, "item icon");
      point tl       = make_point(0, 0);
      point br       = make_point(2, 2);
      wid_set_pos(wid_icon, tl, br);

      auto tile = tile_find("player1.1");
      if (tile) {
        wid_set_style(wid_icon, UI_WID_STYLE_DARK);
        wid_set_fg_tile(wid_icon, tile);
      }
    }

    {
      auto  item     = items[ slot ];
      auto  wid_item = wid_new_square_button(w, "item name");
      point tl       = make_point(3, 0);
      point br       = make_point(width - 2, 2);
      wid_set_pos(wid_item, tl, br);
      wid_set_style(wid_item, UI_WID_STYLE_DARK);
      wid_set_int_context(w, slot);
      wid_set_text(wid_item, item.c_str());
      wid_set_text_lhs(wid_item, true);
      wid_update(wid_item);

      if (slot == 0) {
        wid_item->debug = true;
      }
    }

    y_at += 3;
  }

  wid_update(wid_enchant->wid_text_area->wid_text_area);

  wid_actionbar_init();
}
