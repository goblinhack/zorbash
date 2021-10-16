//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_sdl.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_ui.h"
#include "my_wid_actionbar.h"
#include "my_wid_bag.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_wid_thing_info.h"

WidPopup *                wid_skills;
static std::vector< Tpp > skills;

void wid_skill_choose_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_skills;
  wid_skills = nullptr;
  game->change_state(Game::STATE_NORMAL);
}

static void wid_skills_slot(int slot)
{
  TRACE_AND_INDENT();
  if (slot >= (int) skills.size()) {
    wid_skill_choose_destroy();
    return;
  }

  auto player = game->level->player;
  if (player) {
    auto tpp = skills[ slot ];
    player->skill_add(tpp);
    game->tick_begin("learned a skill");
  }

  wid_skill_choose_destroy();
}

static uint8_t wid_skills_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  auto level = game->level;
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
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  if (key->scancode == (SDL_Scancode) game->config.key_drop) {
    auto what = game->level->inventory_get();
    if (what) {
      if (game->level->player->drop(what)) {
        game->tick_begin("drop");
      }
    }
    CON("PLAYER: Skill choose cancelled");
    game->change_state(Game::STATE_NORMAL);
    wid_skill_choose_destroy();
    return true;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            auto c = wid_event_to_char(key);
            switch (c) {
              case '1' :
              case '2' :
              case '3' :
              case '4' :
              case '5' :
              case '6' :
              case '7' :
              case '8' :
              case '9' : wid_skills_slot(c - '1'); return true;
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  CON("PLAYER: Skill choose cancelled");
                  wid_skill_choose_destroy();
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
  auto level = game->level;
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

  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

static uint8_t wid_skills_mouse_up(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto level = game->level;
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

void Game::wid_skill_choose(void)
{
  TRACE_AND_INDENT();
  BOTCON("You lucky thing. Time to learn some new skill.");

  DBG3("Thing skills create");
  wid_thing_info_fini();
  change_state(Game::STATE_CHOOSING_SKILLS);

  auto player = game->level->player;
  if (! player) {
    change_state(Game::STATE_NORMAL);
    ERR("No player");
    return;
  }

  //
  // In case a scancode was used to open this widget
  //
  wid_ignore_events_briefly();

  //
  // Once skills are maxxed out, that's it
  //
  if (player->monst_infop->skills.size() >= UI_ACTIONBAR_MAX_ITEMS) {
    TOPCON("%%fg=red$Your brain is full and cannot fit in any more skillsj%%fg=reset$");
    change_state(Game::STATE_NORMAL);
    return;
  }

  skills.clear();
  for (auto tpp : tp_get_skills()) {

    bool add = true;
    for (auto oid : player->monst_infop->skills) {
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
    TOPCON("%%fg=purple$You have nothing left to learn. You are now the manifestor.%%fg=reset$");
    change_state(Game::STATE_NORMAL);
    return;
  }

  auto  m     = TERM_WIDTH / 2;
  point tl    = make_point(m - 35, UI_TOPCON_VIS_HEIGHT + 10);
  point br    = make_point(m + 35, tl.y + 25);
  auto  width = br.x - tl.x;

  wid_skills = new WidPopup("skills", tl, br, nullptr, "", false, true, skills.size() * 3);

  wid_set_on_key_up(wid_skills->wid_popup_container, wid_skills_key_up);
  wid_set_on_key_down(wid_skills->wid_popup_container, wid_skills_key_down);

  wid_skills->log("Choose a skill");

  int y_at = 3;
  for (auto slot = 0; slot < (int) skills.size(); slot++) {
    Game  tmp;
    auto  p  = wid_skills->wid_text_area->wid_text_area;
    auto  w  = wid_new_container(p, "item slot");
    point tl = make_point(0, y_at);
    point br = make_point(width - 3, y_at + 2);
    wid_set_pos(w, tl, br);
    wid_set_shape_none(w);

    auto tpp = skills[ slot ];

    {
      auto wid_icon = wid_new_square_button(w, "skill icon");
      wid_set_int_context(w, slot);
      wid_set_on_mouse_up(w, wid_skills_mouse_up);

      point tl = make_point(0, 0);
      point br = make_point(2, 2);
      wid_set_pos(wid_icon, tl, br);

      auto tiles = &tpp->tiles;
      if (tiles) {
        auto tile = tile_first(tiles);
        if (tile) {
          wid_set_style(wid_icon, UI_WID_STYLE_DARK);
          wid_set_fg_tile(wid_icon, tile);
        }
      }
      wid_update(wid_icon);
    }

    {
      auto wid_skill = wid_new_square_button(w, "skill name");
      wid_set_int_context(w, slot);
      wid_set_on_mouse_up(w, wid_skills_mouse_up);

      point tl = make_point(3, 0);
      point br = make_point(width - 3, 2);
      wid_set_pos(wid_skill, tl, br);
      wid_set_style(wid_skill, UI_WID_STYLE_DARK);

      if (slot < 9) {
        wid_set_text(wid_skill, " " + std::to_string(slot + 1) + ". " + tpp->text_name() + ", " + tpp->text_skill());
      } else {
        wid_set_text(wid_skill, tpp->text_name() + ", " + tpp->text_skill());
      }

      wid_set_text_lhs(wid_skill, true);
      wid_update(wid_skill);
    }
    wid_update(w);

    y_at += 3;
  }

  wid_update(wid_skills->wid_text_area->wid_text_area);
  wid_actionbar_init();
}
