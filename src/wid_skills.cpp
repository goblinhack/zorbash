//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_thing_info.hpp"

WidPopup                 *wid_skills;
static std::vector< Tpp > skills;

void wid_choose_skill_destroy(void)
{
  TRACE_AND_INDENT();
  if (wid_skills) {
    delete wid_skills;
    wid_skills = nullptr;
    game->change_state(Game::STATE_NORMAL, "choose skill close");
  }
}

static void wid_skills_slot(int slot)
{
  TRACE_AND_INDENT();
  if (slot >= (int) skills.size()) {
    wid_choose_skill_destroy();
    return;
  }

  auto player = game->level->player;
  if (player) {
    auto tpp = skills[ slot ];
    player->skill_add(tpp);
    game->tick_begin("learned a skill");
  }

  wid_choose_skill_destroy();
}

static uint8_t wid_skills_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  auto level = game->get_current_level();
  if (! level) {
    return true;
  }

  auto player = level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  if (sdlk_eq(*key, game->config.key_drop)) {
    auto what = game->level->inventory_get();
    if (what) {
      if (game->level->player->drop(what)) {
        game->tick_begin("drop");
      }
    }
    CON("INF: Skill choose cancelled");
    game->change_state(Game::STATE_NORMAL, "cancel skill choose");
    wid_choose_skill_destroy();
    return true;
  }

  switch (key->mod) {
    case KMOD_LCTRL:
    case KMOD_RCTRL:
    default:
      switch (key->sym) {
        default:
          {
            auto c = wid_event_to_char(key);
            switch (c) {
              case '1':
              case '2':
              case '3':
              case '4':
              case '5':
              case '6':
              case '7':
              case '8':
              case '9': wid_skills_slot(c - '1'); return true;
              case SDLK_ESCAPE:
                {
                  TRACE_AND_INDENT();
                  CON("INF: Skill choose cancelled");
                  wid_choose_skill_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_skills_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  auto level = game->get_current_level();
  if (! level) {
    return true;
  }

  auto player = level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static uint8_t wid_skills_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto level = game->get_current_level();
  if (! level) {
    return true;
  }

  auto player = level->player;
  if (! player) {
    return true;
  }

  if (player->is_dead) {
    return true;
  }

  wid_skills_slot(wid_get_int_context(w));
  return true;
}

static uint8_t wid_skill_close(Widp w, int x, int y, uint32_t button)
{
  DBG3("Thing skill: close");
  TRACE_AND_INDENT();

  wid_choose_skill_destroy();
  return true;
}

void Game::wid_choose_skill(void)
{
  TRACE_AND_INDENT();
  BOTCON("You lucky thing. Time to learn some new skill.");

  DBG3("Thing skills create");
  wid_thing_info_fini("choose skill");

  auto player = game->level->player;
  if (! player) {
    ERR("No player");
    return;
  }

  //
  // Once skills are maxxed out, that's it
  //
  if (player->itemsp()->skills.size() >= UI_INVENTORY_QUICK_ITEMS_MAX) {
    player->msg("%%fg=red$Your brain is full and cannot fit in any more skillsj%%fg=reset$");
    return;
  }

  skills.clear();
  for (auto tpp : tp_get_skills()) {

    bool add = true;
    for (auto oid : player->itemsp()->skills) {
      auto o = game->level->thing_find(oid);
      if (o) {
        if (o->tp() == tpp) {
          add = false;
          break;
        }
      }
    }
    if (add) {
      skills.push_back(tpp);
    }
  }

  if (skills.empty()) {
    player->msg("%%fg=purple$You have learned all there is to learn.%%fg=reset$");
    return;
  }

  change_state(Game::STATE_CHOOSING_SKILLS, "choose skills");

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;

  auto       m          = TERM_WIDTH / 2;
  static int wid_width  = 80;
  int        left_half  = wid_width / 2;
  int        right_half = wid_width - left_half;

  bool scrollbar = false;
  auto sz        = skills.size();
  if (! sz) {
    sz = 1;
  }
  int height_max = (((int) sz * 3) + 6);
  int height;
  if (height_max > TERM_HEIGHT / 2) {
    height    = TERM_HEIGHT / 2;
    scrollbar = true;
  } else {
    height = height_max;
  }
  point tl   = make_point(m - left_half, TERM_HEIGHT / 2 - height / 2 - 2);
  point br   = make_point(m + right_half, TERM_HEIGHT / 2 + height / 2);
  wid_skills = new WidPopup("Skills", tl, br, nullptr, "", false, scrollbar, height_max);

  wid_skills->log("Choose a skill");

  wid_set_on_key_up(wid_skills->wid_popup_container, wid_skills_key_up);
  wid_set_on_key_down(wid_skills->wid_popup_container, wid_skills_key_down);

  auto width = br.x - tl.x;
  int  y_at  = 3;
  for (auto slot = 0; slot < (int) skills.size(); slot++) {
    Game  tmp;
    auto  p  = wid_skills->wid_text_area->wid_text_area;
    auto  w  = wid_new_container(p, "item slot");
    point tl = make_point(0, y_at);
    point br = make_point(width - 3, y_at + 2);

    if (g_opt_ascii) {
      tl = make_point(0, y_at);
      br = make_point(width - 3, y_at + 2);
    }

    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    auto tpp = skills[ slot ];

    if (! g_opt_ascii) {
      auto wid_icon = wid_new_square_button(w, "skill icon");
      wid_set_int_context(w, slot);
      wid_set_on_mouse_up(w, wid_skills_mouse_up);

      point tl = make_point(0, 0);
      point br = make_point(2, 2);

      wid_set_pos(wid_icon, tl, br);

      auto tiles = &tpp->tiles;
      if (tiles) {
        auto tile = tile_first(tiles);
        wid_set_style(wid_icon, UI_WID_STYLE_DARK);
        wid_set_fg_tile(wid_icon, tile);
      }

      wid_update(wid_icon);
    }

    {
      auto skill_text = wid_new_square_button(w, "skill name");
      wid_set_int_context(w, slot);
      wid_set_on_mouse_up(w, wid_skills_mouse_up);

      if (g_opt_ascii) {
        point tl = make_point(1, 0);
        point br = make_point(width - 2, 0);
        wid_set_pos(skill_text, tl, br);
        wid_set_mode(skill_text, WID_MODE_OVER);
        wid_set_style(skill_text, box_highlight_style);
        wid_set_mode(skill_text, WID_MODE_NORMAL);
        wid_set_style(skill_text, box_style);
      } else {
        point tl = make_point(3, 0);
        point br = make_point(width - 3, 2);
        wid_set_pos(skill_text, tl, br);
        wid_set_style(skill_text, UI_WID_STYLE_DARK);
      }

      if (slot < 9) {
        wid_set_text(skill_text,
                     " " + std::to_string(slot + 1) + ". " + tpp->text_long_name() + ", " + tpp->text_skill());
      } else {
        wid_set_text(skill_text, tpp->text_long_name() + ", " + tpp->text_skill());
      }

      wid_set_text_lhs(skill_text, true);
      wid_update(skill_text);
    }
    wid_update(w);

    if (g_opt_ascii) {
      y_at += 1;
    } else {
      y_at += 3;
    }
  }

  //
  // Close icons
  //
  if (g_opt_ascii) {
    {
      auto  w = wid_new_square_button(wid_skills->wid_popup_container, "wid collect window close");
      point tl(0, 0);
      point br(2, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_skill_close);
    }
    {
      auto  w = wid_new_square_button(wid_skills->wid_popup_container, "wid collect window close");
      point tl(wid_width - 2, 0);
      point br(wid_width - 0, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_skill_close);
    }
  } else {
    {
      auto  w = wid_new_square_button(wid_skills->wid_popup_container, "wid collect window close");
      point tl(0, 0);
      point br(3, 3);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_icon_close");
      wid_set_on_mouse_down(w, wid_skill_close);
    }

    {
      auto  w = wid_new_square_button(wid_skills->wid_popup_container, "wid collect window close");
      point tl(wid_width - 3, 0);
      point br(wid_width - 0, 3);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_icon_close");
      wid_set_on_mouse_down(w, wid_skill_close);
    }
  }

  wid_update(wid_skills->wid_text_area->wid_text_area);
  wid_actionbar_init();
}
