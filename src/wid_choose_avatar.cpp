//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_spellbox.hpp"
#include "my_wid_thing_info.hpp"

static WidPopup *wid_choose_avatar;
static bool      config_changed;

static void wid_choose_avatar_destroy(void)
{
  TRACE_AND_INDENT();

  delete wid_choose_avatar;
  wid_choose_avatar = nullptr;
  config_changed    = false;
}

static uint8_t wid_choose_avatar_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Reload config for avatar");
  if (config_changed) {
    config_changed = false;
    game->load_config();
    sdl_config_update_all();
  }
  wid_choose_avatar_destroy();
  game->wid_main_menu_select();
  return true;
}

static uint8_t wid_choose_avatar_save(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Save config for avatar");
  game->save_config();

  wid_choose_avatar_destroy();
  game->wid_main_menu_select();

  return true;
}

static uint8_t wid_choose_avatar_back(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_choose_avatar_destroy();
  game->wid_main_menu_select();
  return true;
}

static uint8_t wid_choose_avatar_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'b' :
              case SDLK_ESCAPE : wid_choose_avatar_cancel(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_choose_avatar_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  //
  // So screenshots can work
  //
  return false;
}

static uint8_t wid_choose_avatar_bodypart_next(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();

  config_changed        = true;
  auto bodypart         = wid_get_int_context(w);
  auto current_bodypart = get(game->config.player_bodyparts, bodypart);
  auto next_bodypart    = tp_get_next_bodypart(bodypart, current_bodypart);
  set(game->config.player_bodyparts, bodypart, next_bodypart->name());
  wid_choose_avatar_destroy();
  game->wid_choose_avatar_select();
  return false;
}

static uint8_t wid_choose_avatar_bodypart_prev(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();

  config_changed        = true;
  auto bodypart         = wid_get_int_context(w);
  auto current_bodypart = get(game->config.player_bodyparts, bodypart);
  auto next_bodypart    = tp_get_prev_bodypart(bodypart, current_bodypart);
  set(game->config.player_bodyparts, bodypart, next_bodypart->name());
  wid_choose_avatar_destroy();
  game->wid_choose_avatar_select();
  return false;
}

static void wid_choose_avatar_tick(Widp w)
{
  TRACE_NO_INDENT();

  static auto last = time_ms_cached();
  if (! time_have_x_tenths_passed_since(2, last)) {
    return;
  }
  last = time_ms();

  wid_choose_avatar_destroy();
  game->wid_choose_avatar_select();
}

void Game::wid_choose_avatar_select(void)
{
  TRACE_AND_INDENT();

  wid_rightbar_fini();
  wid_leftbar_fini();
  wid_inventory_fini();
  wid_skillbox_fini();
  wid_spellbox_fini();
  wid_thing_info_fini("choose avatar");

  //
  // The tile needs to be optional, as we do not always have a tile, e.g. hats
  //
  static int avatar_anim_fram = 1;
  if (++avatar_anim_fram > 6) {
    avatar_anim_fram = 1;
  }

  auto avatar_width  = TERM_WIDTH / 4 * 2;
  auto avatar_height = TERM_HEIGHT / 4 * 3;

  point tl;
  point br(avatar_width, avatar_height);
  auto  width  = br.x - tl.x - 2;
  auto  height = br.y - tl.y - 2;

  wid_choose_avatar = new WidPopup("Avatar", tl, br, nullptr, "", true, false);
  wid_choose_avatar->log("Choose an avatar, whimpering mortal!");
  auto avatar_container = wid_choose_avatar->wid_popup_container;
  avatar_container      = wid_choose_avatar->wid_popup_container;
  wid_move_to_pct_centered(avatar_container, 0.5, 0.5);

  wid_set_on_key_up(avatar_container, wid_choose_avatar_key_up);
  wid_set_on_key_down(avatar_container, wid_choose_avatar_key_down);

  auto button_width        = 6;
  auto y_at                = 4;
  auto box_style           = UI_WID_STYLE_DARK;
  auto box_highlight_style = UI_WID_STYLE_NORMAL;

  TRACE_NO_INDENT();
  FOR_ALL_BODYPART(iter)
  {
    TRACE_NO_INDENT();

    switch (iter) {
      case BODYPART_HAT : y_at = 6; break;
      case BODYPART_HAIR : y_at = 10; break;
      case BODYPART_FACE : y_at = 18; break;
      case BODYPART_TORSO : y_at = 32; break;
      case BODYPART_LEGS : y_at = 50; break;
      case BODYPART_EYES : y_at = 14; break;
    }

    {
      TRACE_AND_INDENT();
      auto p = wid_choose_avatar->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "body part");

      point tl = make_point(0, y_at);
      point br = make_point(button_width, y_at);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text_lhs(w, true);
      wid_set_text(w, capitalise(bodypart_name(iter)));
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_choose_avatar->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "<");

      point tl = make_point(button_width + 0, y_at - 1);
      point br = make_point(button_width + 4, y_at + 1);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_choose_avatar_bodypart_prev);
      wid_set_int_context(w, iter);
      wid_set_text(w, "<");
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_choose_avatar->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, ">");

      point tl = make_point(button_width + 5, y_at - 1);
      point br = make_point(button_width + 9, y_at + 1);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_choose_avatar_bodypart_next);
      wid_set_int_context(w, iter);
      wid_set_text(w, ">");
    }
  }

  {
    TRACE_AND_INDENT();
    auto p                = wid_choose_avatar->wid_text_area->wid_text_area;
    auto avatar_container = wid_new_square_button(p, "avatar");

    {
      point tl = make_point(button_width + 11, 3);
      point br = make_point(avatar_width - 2, avatar_height - 6);
      wid_set_mode(avatar_container, WID_MODE_OVER);
      wid_set_color(avatar_container, WID_COLOR_BG, GRAY70);
      wid_set_style(avatar_container, UI_WID_STYLE_SOLID_DEFAULT);
      wid_set_mode(avatar_container, WID_MODE_NORMAL);
      wid_set_color(avatar_container, WID_COLOR_BG, GRAY70);
      wid_set_style(avatar_container, UI_WID_STYLE_SOLID_DEFAULT);
      wid_set_pos(avatar_container, tl, br);
    }

    auto avatar_box = wid_new_square_button(avatar_container, "avatar box");
    {
      point tl(2, 2);
      point br(wid_get_width(avatar_container) - 3, wid_get_height(avatar_container) - 3);
      wid_set_mode(avatar_box, WID_MODE_OVER);
      wid_set_color(avatar_box, WID_COLOR_BG, GRAY50);
      wid_set_style(avatar_box, UI_WID_STYLE_SOLID_DEFAULT);
      wid_set_mode(avatar_box, WID_MODE_NORMAL);
      wid_set_color(avatar_box, WID_COLOR_BG, GRAY50);
      wid_set_style(avatar_box, UI_WID_STYLE_SOLID_DEFAULT);
      wid_set_pos(avatar_box, tl, br);
    }

    TRACE_NO_INDENT();
    FOR_ALL_BODYPART(iter)
    {
      TRACE_NO_INDENT();

      if (game->config.player_bodyparts[ iter ].empty()) {
        auto tp_bodypart = tp_random_bodypart(iter);
        set(game->config.player_bodyparts, iter, tp_bodypart->name());
      }

      int z = MAP_Z_PRIO_PLAYER_FIRST;

      switch (iter) {
        case BODYPART_HAT : z = MAP_Z_PRIO_PLAYER_HAT; break;
        case BODYPART_HAIR : z = MAP_Z_PRIO_PLAYER_HAIR; break;
        case BODYPART_FACE : z = MAP_Z_PRIO_PLAYER_FACE; break;
        case BODYPART_TORSO : z = MAP_Z_PRIO_PLAYER_TORSO; break;
        case BODYPART_LEGS : z = MAP_Z_PRIO_PLAYER_LEGS; break;
        case BODYPART_EYES : z = MAP_Z_PRIO_PLAYER_EYES; break;
      }

      TRACE_NO_INDENT();

      auto tilename = game->config.player_bodyparts[ iter ] + "." + std::to_string(avatar_anim_fram);
      if (tile_find(tilename)) {
        wid_set_tilename(TILE_LAYER_FG_0 + (z - MAP_Z_PRIO_PLAYER_FIRST), avatar_box, tilename);
      }

      //
      // Animate a sword on top
      //
      tilename = "sword_wood_demo_carry." + std::to_string(avatar_anim_fram);
      if (tile_find(tilename)) {
        wid_set_tilename(TILE_LAYER_FG_0 + (MAP_Z_PRIO_PLAYER_EYES - MAP_Z_PRIO_PLAYER_FIRST) + 3, avatar_box,
                         tilename);
      }
    }
  }

  y_at = height - 2;
  {
    TRACE_AND_INDENT();
    auto p = wid_choose_avatar->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(1, y_at);
    point br = make_point(6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_up(w, wid_choose_avatar_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_choose_avatar->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Save");

    point tl = make_point(width - 15, y_at);
    point br = make_point(width - 10, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_choose_avatar_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_choose_avatar->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Cancel");

    point tl = make_point(width - 8, y_at);
    point br = make_point(width - 1, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_choose_avatar_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
  }

  auto w = wid_choose_avatar->wid_text_area->wid_text_area;
  wid_set_on_tick(w, wid_choose_avatar_tick);
  wid_update(w);

  TRACE_NO_INDENT();
}
