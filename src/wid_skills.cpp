//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_tp_info.hpp"

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

  Skillp skill = (Skillp) wid_get_void_context(w);
  if (! skill) {
    return true;
  }

  if (! skill->tpp) {
    return true;
  }

  player->skill_add(skill->tpp);
  wid_choose_skill_destroy();

  return true;
}

static uint8_t wid_skill_close(Widp w, int x, int y, uint32_t button)
{
  DBG3("Thing skill: close");
  TRACE_AND_INDENT();

  wid_choose_skill_destroy();
  return true;
}

void wid_skill_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  DBG2("Skill: Begin over skill");
  TRACE_AND_INDENT();

  Skillp skill = (Skillp) wid_get_void_context(w);
  if (! skill) {
    return;
  }

  TRACE_NO_INDENT();
  if (! skill->tpp) {
    return;
  }

  TRACE_NO_INDENT();
  game->wid_tp_info_create(skill->tpp);
}

void wid_skill_over_end(Widp w)
{
  TRACE_NO_INDENT();
  DBG2("Skill: End over skill");
  TRACE_AND_INDENT();

  game->wid_tp_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}

//
// Is this skill learned only after another?
//
static bool skill_has_precursor(Skillp skill_curr)
{
  for (auto x = 0; x < SKILL_TREE_ACROSS; x++) {
    for (auto y = 0; y < SKILL_TREE_DOWN; y++) {
      auto skill = get(game->skill_tree, x, y);
      if (! skill) {
        continue;
      }

      if (skill->skill_up == skill_curr) {
        return true;
      }
      if (skill->skill_down == skill_curr) {
        return true;
      }
      if (skill->skill_left == skill_curr) {
        return true;
      }
      if (skill->skill_right == skill_curr) {
        return true;
      }
    }
  }
  return false;
}

//
// Have we unlocked a skill?
//
static bool skill_is_available(Skillp skill_next)
{
  for (auto x = 0; x < SKILL_TREE_ACROSS; x++) {
    for (auto y = 0; y < SKILL_TREE_DOWN; y++) {
      auto skill_curr = get(game->skill_tree, x, y);
      if (! skill_curr) {
        continue;
      }

      //
      // We walk all the other skills, looking for one that points at the next skill
      // and that we have activated the precursors
      //
      if ((skill_curr->skill_up == skill_next) || (skill_curr->skill_down == skill_next)
          || (skill_curr->skill_left == skill_next) || (skill_curr->skill_right == skill_next)) {
        FOR_ALL_SKILLS_FOR(game->level->player, id)
        {
          auto known_skill = game->level->thing_find(id);
          if (known_skill && (skill_curr->tpp == known_skill->tp())) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

void Game::wid_choose_skill(void)
{
  TRACE_AND_INDENT();
  BOTCON("You lucky thing. Time to learn some new skill.");

  DBG3("Thing skills create");
  wid_thing_info_fini("choose skill");
  wid_tp_info_fini("choose skill");

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

  int WID_SKILL_BUTTON_WIDTH  = 4;
  int WID_SKILL_BUTTON_HEIGHT = 4;

  if (g_opt_ascii) {
    WID_SKILL_BUTTON_WIDTH  = 12;
    WID_SKILL_BUTTON_HEIGHT = 4;
  } else {
    WID_SKILL_BUTTON_WIDTH  = 6;
    WID_SKILL_BUTTON_HEIGHT = 6;
  }

  //
  // Main window
  //
  auto  skills_width  = (WID_SKILL_BUTTON_WIDTH * SKILL_TREE_ACROSS) + 3;
  auto  skills_height = (WID_SKILL_BUTTON_HEIGHT * SKILL_TREE_DOWN) + 3;
  point tl;
  point br(skills_width, skills_height);
  wid_skills = new WidPopup("Skills", tl, br, nullptr, "", true, false);
  wid_skills->log("Choose a skill, mortal");
  auto skills_container = wid_skills->wid_popup_container;
  skills_container      = wid_skills->wid_popup_container;
  wid_move_to_pct_centered(skills_container, 0.5, 0.5);

  wid_set_on_key_up(wid_skills->wid_popup_container, wid_skills_key_up);
  wid_set_on_key_down(wid_skills->wid_popup_container, wid_skills_key_down);

  //
  // Create the buttons
  //
  for (auto x = 0; x < SKILL_TREE_ACROSS; x++) {
    for (auto y = 0; y < SKILL_TREE_DOWN; y++) {
      auto skill = get(game->skill_tree, x, y);
      if (! skill) {
        continue;
      }

      //
      // Create a button describing the skill
      //
      Widp  b = wid_new_square_button(skills_container, "wid skill grid button");
      point tl;
      point br;
      tl.x = WID_SKILL_BUTTON_WIDTH * x + 2;
      tl.y = WID_SKILL_BUTTON_HEIGHT * y + 3;
      if (! g_opt_ascii) {
        tl.y += 1;
      }
      br.x = tl.x + (WID_SKILL_BUTTON_WIDTH - 1) - 1;
      br.y = tl.y + (WID_SKILL_BUTTON_HEIGHT - 1) - 1;
      wid_set_pos(b, tl, br);

      bool skill_is_active_or_available = false;

      //
      // Do we have this skill?
      //
      if (player->has_skill(skill->tpp)) {
        //
        // Yes
        //
        skill_is_active_or_available = true;
        wid_set_style(b, UI_WID_STYLE_DARK);
      } else if (! skill_has_precursor(skill)) {
        //
        // Can we attain this skill?
        //
        skill_is_active_or_available = true;
        wid_set_style(b, UI_WID_STYLE_GREEN);
        wid_set_on_mouse_up(b, wid_skills_mouse_up);
      } else if (skill_is_available(skill)) {
        //
        // Can we attain this skill?
        //
        skill_is_active_or_available = true;
        wid_set_style(b, UI_WID_STYLE_GREEN);
        wid_set_on_mouse_up(b, wid_skills_mouse_up);
      } else {
        //
        // Can we not yet attain this skill?
        //
        wid_set_style(b, UI_WID_STYLE_DARK);
        wid_set_color(b, WID_COLOR_TEXT_FG, GRAY50);
      }

      //
      // Add the tile for this skill, unless it is an intermediate skill
      //
      auto skill_alias = skill->skill_alias;
      if (! skill_alias.empty()) {
        //
        // Check the alias to skill mapping exists
        //
        if (game->skill_aliases.find(skill_alias) == game->skill_aliases.end()) {
          ERR("Skill alias %s not found", skill_alias.c_str());
        } else {
          //
          // Find the skill template
          //
          auto skill_name = game->skill_aliases[ skill_alias ];
          if (! skill_name.empty()) {
            auto tpp = tp_find(skill_name);
            if (tpp) {
              skill->tpp = tpp;

              if (g_opt_ascii) {
                //
                // And its short description
                //
                wid_set_text(b, skill->tpp->text_description_very_short());
              } else {
                //
                // And its tile
                //
                auto tiles = &tpp->tiles;
                if (tiles) {
                  auto tile = tile_n(tiles, skill_is_active_or_available ? 0 : 1);
                  if (tile) {
                    wid_set_fg_tile(b, tile);
                  }
                }
              }
            } else {
              ERR("Skill alias %s and name %s not found", skill_alias.c_str(), skill_name.c_str());
            }
          }
        }
      }

      wid_set_on_mouse_over_begin(b, wid_skill_over_begin);
      wid_set_on_mouse_over_end(b, wid_skill_over_end);
      wid_set_void_context(b, skill);

      //
      // Create connectors between skills
      //
      if (skill->skill_down) {
        Widp  b   = wid_new_square_button(skills_container, "wid skill grid connector");
        point tl2 = tl;
        point br2 = br;

        tl2.x += WID_SKILL_BUTTON_WIDTH / 2;
        tl2.y += WID_SKILL_BUTTON_HEIGHT - 1;
        tl2.x -= 1;
        br2 = tl2;

        wid_set_pos(b, tl2, br2);
        if (g_opt_ascii) {
          wid_set_text(b, "v");
        } else {
          wid_set_fg2_tilename(b, "tile_down");
        }
        wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      }

      if (skill->skill_up) {
        Widp  b   = wid_new_square_button(skills_container, "wid skill grid connector");
        point tl2 = tl;
        point br2 = br;

        tl2.y -= WID_SKILL_BUTTON_HEIGHT;
        tl2.x += WID_SKILL_BUTTON_WIDTH / 2;
        tl2.y += WID_SKILL_BUTTON_HEIGHT - 1;
        tl2.x -= 1;
        br2 = tl2;

        wid_set_pos(b, tl2, br2);
        if (g_opt_ascii) {
          wid_set_text(b, "^");
        } else {
          wid_set_fg2_tilename(b, "tile_up");
        }
        wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      }

      if (skill->skill_left) {
        Widp  b   = wid_new_square_button(skills_container, "wid skill grid connector");
        point tl2 = tl;
        point br2 = br;

        tl2.x -= 1;
        tl2.y += 2;
        if (g_opt_ascii) {
          tl2.y--;
        }
        br2 = tl2;

        wid_set_pos(b, tl2, br2);
        if (g_opt_ascii) {
          wid_set_text(b, "<");
        } else {
          wid_set_fg2_tilename(b, "tile_left");
        }
        wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      }

      if (skill->skill_right) {
        Widp  b   = wid_new_square_button(skills_container, "wid skill grid connector");
        point tl2 = tl;
        point br2 = br;

        tl2.x += WID_SKILL_BUTTON_WIDTH;
        tl2.x -= 1;
        tl2.y += 1;
        tl2.y += 1;
        if (g_opt_ascii) {
          tl2.y--;
        }
        br2 = tl2;

        wid_set_pos(b, tl2, br2);
        if (g_opt_ascii) {
          wid_set_text(b, ">");
        } else {
          wid_set_fg2_tilename(b, "tile_right");
        }
        wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      }
    }
  }

  if (g_opt_ascii) {
    {
      auto  w = wid_new_square_button(skills_container, "wid skills window close");
      point tl(skills_width - 2, 0);
      point br(skills_width, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_skill_close);
    }

    {
      auto  w = wid_new_square_button(skills_container, "wid skills window close");
      point tl(0, 0);
      point br(2, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_skill_close);
    }
  } else {
    {
      auto  w = wid_new_square_button(skills_container, "wid skills window close");
      point tl(skills_width - 2, 0);
      point br(skills_width, 2);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_icon_close");
      wid_set_on_mouse_up(w, wid_skill_close);
    }

    {
      auto  w = wid_new_square_button(skills_container, "wid skills window close");
      point tl(0, 0);
      point br(2, 2);
      wid_set_pos(w, tl, br);
      wid_set_bg_tilename(w, "ui_icon_close");
      wid_set_on_mouse_up(w, wid_skill_close);
    }
  }

  wid_actionbar_init();
}
