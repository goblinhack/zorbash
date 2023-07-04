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

WidPopup                 *wid_spells;
static std::vector< Tpp > spells;
static std::string        current_spell_tree;

void wid_choose_spell_destroy(void)
{
  TRACE_AND_INDENT();
  if (wid_spells) {
    delete wid_spells;
    wid_spells = nullptr;
    game->change_state(Game::STATE_NORMAL, "choose spell close");
  }
}

static void wid_spells_slot(int slot)
{
  TRACE_AND_INDENT();
  if (slot >= (int) spells.size()) {
    wid_choose_spell_destroy();
    return;
  }

  auto player = game->level->player;
  if (player) {
    auto tpp = spells[ slot ];
    player->spell_add(tpp);
    game->tick_begin("learned a spell");
  }

  wid_choose_spell_destroy();
}

static uint8_t wid_spells_key_up(Widp w, const struct SDL_Keysym *key)
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
    CON("INF: Spell choose cancelled");
    game->change_state(Game::STATE_NORMAL, "cancel spell choose");
    wid_choose_spell_destroy();
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
              case '9' : wid_spells_slot(c - '1'); return true;
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  CON("INF: Spell choose cancelled");
                  wid_choose_spell_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_spells_key_down(Widp w, const struct SDL_Keysym *key)
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

static uint8_t wid_spells_mouse_up(Widp w, int x, int y, uint32_t button)
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

  Spellp spell = (Spellp) wid_get_void_context(w);
  if (! spell) {
    return true;
  }

  if (! spell->tpp) {
    return true;
  }

  player->spell_add(spell->tpp);
  wid_choose_spell_destroy();

  return true;
}

static uint8_t wid_spell_close(Widp w, int x, int y, uint32_t button)
{
  DBG3("Thing spell: close");
  TRACE_AND_INDENT();

  wid_choose_spell_destroy();
  return true;
}

void wid_spell_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  DBG2("Spell: Begin over spell");
  TRACE_AND_INDENT();

  Spellp spell = (Spellp) wid_get_void_context(w);
  if (! spell) {
    return;
  }

  TRACE_NO_INDENT();
  if (! spell->tpp) {
    return;
  }

  TRACE_NO_INDENT();
  game->wid_tp_info_create(spell->tpp);
}

void wid_spell_tree_over_begin(Widp w, int relx, int rely, int wheelx, int wheely)
{
  auto new_spell_tree = wid_get_string_context(w);

  if (new_spell_tree == current_spell_tree) {
    return;
  }

  current_spell_tree = new_spell_tree;
  wid_choose_spell_destroy();
  game->wid_choose_spell();
}

void wid_spell_over_end(Widp w)
{
  TRACE_NO_INDENT();
  DBG2("Spell: End over spell");
  TRACE_AND_INDENT();

  game->wid_tp_info_destroy_deferred();

  //
  // Do not create new wids in here
  //
}

//
// Is this spell learned only after another?
//
static bool spell_has_precursor(Spellp spell_curr)
{
  for (auto iter : game->spell_tree) {
    auto tree_name = iter.first;
    for (auto x = 0; x < SPELL_TREE_ACROSS; x++) {
      for (auto y = 0; y < SPELL_TREE_DOWN; y++) {
        auto spell = get(game->spell_tree[ tree_name ], x, y);
        if (! spell) {
          continue;
        }

        if (spell->spell_up == spell_curr) {
          return true;
        }
        if (spell->spell_down == spell_curr) {
          return true;
        }
        if (spell->spell_left == spell_curr) {
          return true;
        }
        if (spell->spell_right == spell_curr) {
          return true;
        }
      }
    }
  }
  return false;
}

//
// Have we unlocked a spell?
//
static bool spell_is_available(Spellp spell_next)
{
  for (auto iter : game->spell_tree) {
    auto tree_name = iter.first;
    for (auto x = 0; x < SPELL_TREE_ACROSS; x++) {
      for (auto y = 0; y < SPELL_TREE_DOWN; y++) {
        auto spell_curr = get(game->spell_tree[ tree_name ], x, y);
        if (! spell_curr) {
          continue;
        }

        //
        // We walk all the other spells, looking for one that points at the next spell
        // and that we have activated the precursors
        //
        if ((spell_curr->spell_up == spell_next) || (spell_curr->spell_down == spell_next)
            || (spell_curr->spell_left == spell_next) || (spell_curr->spell_right == spell_next)) {
          FOR_ALL_SPELLS_FOR(game->level->player, id)
          {
            auto known_spell = game->level->thing_find(id);
            if (known_spell && (spell_curr->tpp == known_spell->tp())) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

void Game::wid_choose_spell(void)
{
  //
  // Default tree
  //
  if (current_spell_tree == "") {
    current_spell_tree = "combat";
  }

  wid_choose_from_spell_tree(current_spell_tree);
}

void Game::wid_choose_from_spell_tree(std::string current_tree_name)
{
  TRACE_AND_INDENT();
  BOTCON("You lucky thing. Time to learn some new spell.");

  DBG3("Thing spells create");
  wid_thing_info_fini("choose spell");
  wid_tp_info_fini("choose spell");

  auto player = game->level->player;
  if (! player) {
    ERR("No player");
    return;
  }

  //
  // Once spells are maxxed out, that's it
  //
  if (player->itemsp()->spells.size() >= UI_INVENTORY_QUICK_ITEMS_MAX) {
    player->msg("%%fg=red$Your brain is full and cannot fit in any more spells%%fg=reset$");
    return;
  }

  spells.clear();
  for (auto tpp : tp_get_spells()) {

    bool add = true;
    for (auto oid : player->itemsp()->spells) {
      auto o = game->level->thing_find(oid);
      if (o) {
        if (o->tp() == tpp) {
          add = false;
          break;
        }
      }
    }
    if (add) {
      spells.push_back(tpp);
    }
  }

  if (spells.empty()) {
    player->msg("%%fg=purple$You have learned all there is to learn.%%fg=reset$");
    return;
  }

  change_state(Game::STATE_CHOOSING_SPELLS, "choose spells");

  int WID_SPELL_LEFT_PADDING  = 15;
  int WID_SPELL_LEFT_BUTTON   = 13;
  int WID_SPELL_BUTTON_WIDTH  = 4;
  int WID_SPELL_BUTTON_HEIGHT = 4;

  if (g_opt_ascii) {
    WID_SPELL_BUTTON_WIDTH  = 12;
    WID_SPELL_BUTTON_HEIGHT = 4;
  } else {
    WID_SPELL_BUTTON_WIDTH  = 6;
    WID_SPELL_BUTTON_HEIGHT = 6;
  }

  //
  // Main window
  //
  auto  spells_width  = (WID_SPELL_BUTTON_WIDTH * SPELL_TREE_ACROSS) + 3 + WID_SPELL_LEFT_PADDING;
  auto  spells_height = (WID_SPELL_BUTTON_HEIGHT * SPELL_TREE_DOWN) + 3;
  point tl;
  point br(spells_width, spells_height);
  wid_spells = new WidPopup("Spells", tl, br, nullptr, "", true, false);
  wid_spells->log("Choose a spell, mortal");
  auto spells_container = wid_spells->wid_popup_container;
  spells_container      = wid_spells->wid_popup_container;
  wid_move_to_pct_centered(spells_container, 0.5, 0.5);

  wid_set_on_key_up(wid_spells->wid_popup_container, wid_spells_key_up);
  wid_set_on_key_down(wid_spells->wid_popup_container, wid_spells_key_down);

  //
  // Create the buttons
  //
  for (auto x = 0; x < SPELL_TREE_ACROSS; x++) {
    for (auto y = 0; y < SPELL_TREE_DOWN; y++) {
      auto spell = get(game->spell_tree[ current_tree_name ], x, y);
      if (! spell) {
        continue;
      }

      //
      // Create a button describing the spell
      //
      Widp  b = wid_new_square_button(spells_container, "wid spell grid button");
      point tl;
      point br;
      tl.x = WID_SPELL_BUTTON_WIDTH * x + 2 + WID_SPELL_LEFT_PADDING;
      tl.y = WID_SPELL_BUTTON_HEIGHT * y + 3;
      if (! g_opt_ascii) {
        tl.y += 1;
      }
      br.x = tl.x + (WID_SPELL_BUTTON_WIDTH - 1) - 1;
      br.y = tl.y + (WID_SPELL_BUTTON_HEIGHT - 1) - 1;
      wid_set_pos(b, tl, br);

      bool spell_is_active_or_available = false;

      //
      // Do we have this spell?
      //
      if (player->has_spell(spell->tpp)) {
        //
        // Yes
        //
        spell_is_active_or_available = true;
        wid_set_style(b, UI_WID_STYLE_DARK);
      } else if (! spell_has_precursor(spell)) {
        //
        // Can we attain this spell?
        //
        spell_is_active_or_available = true;
        wid_set_style(b, UI_WID_STYLE_GREEN);
        wid_set_on_mouse_up(b, wid_spells_mouse_up);
      } else if (spell_is_available(spell)) {
        //
        // Can we attain this spell?
        //
        spell_is_active_or_available = true;
        wid_set_style(b, UI_WID_STYLE_GREEN);
        wid_set_on_mouse_up(b, wid_spells_mouse_up);
      } else {
        //
        // Can we not yet attain this spell?
        //
        wid_set_style(b, UI_WID_STYLE_DARK);
        wid_set_color(b, WID_COLOR_TEXT_FG, GRAY50);
      }

      //
      // Add the tile for this spell, unless it is an intermediate spell
      //
      auto spell_alias = spell->spell_alias;
      if (! spell_alias.empty()) {
        //
        // Check the alias to spell mapping exists
        //
        if (game->spell_aliases.find(spell_alias) == game->spell_aliases.end()) {
          ERR("Spell alias %s not found", spell_alias.c_str());
        } else {
          //
          // Find the spell template
          //
          auto spell_name = game->spell_aliases[ spell_alias ];
          if (! spell_name.empty()) {
            auto tpp = tp_find(spell_name);
            if (tpp) {
              spell->tpp = tpp;

              if (g_opt_ascii) {
                //
                // And its short description
                //
                wid_set_text(b, spell->tpp->text_description_very_short());
              } else {
                //
                // And its tile
                //
                auto tiles = &tpp->tiles;
                if (tiles) {
                  auto tile = tile_n(tiles, spell_is_active_or_available ? 0 : 1);
                  if (tile) {
                    wid_set_tile(TILE_LAYER_FG_0, b, tile);
                  }
                }
              }
            } else {
              ERR("Spell alias %s and name %s not found", spell_alias.c_str(), spell_name.c_str());
            }
          }
        }
      }

      wid_set_on_mouse_over_begin(b, wid_spell_over_begin);
      wid_set_on_mouse_over_end(b, wid_spell_over_end);
      wid_set_void_context(b, spell);

      //
      // Create connectors between spells
      //
      if (spell->spell_down) {
        Widp  b   = wid_new_square_button(spells_container, "wid spell grid connector");
        point tl2 = tl;
        point br2 = br;

        tl2.x += WID_SPELL_BUTTON_WIDTH / 2;
        tl2.y += WID_SPELL_BUTTON_HEIGHT - 1;
        tl2.x -= 1;
        br2 = tl2;

        wid_set_pos(b, tl2, br2);
        if (g_opt_ascii) {
          wid_set_text(b, "v");
        } else {
          wid_set_tilename(TILE_LAYER_FG_1, b, "tile_down");
        }
        wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      }

      if (spell->spell_up) {
        Widp  b   = wid_new_square_button(spells_container, "wid spell grid connector");
        point tl2 = tl;
        point br2 = br;

        tl2.y -= WID_SPELL_BUTTON_HEIGHT;
        tl2.x += WID_SPELL_BUTTON_WIDTH / 2;
        tl2.y += WID_SPELL_BUTTON_HEIGHT - 1;
        tl2.x -= 1;
        br2 = tl2;

        wid_set_pos(b, tl2, br2);
        if (g_opt_ascii) {
          wid_set_text(b, "^");
        } else {
          wid_set_tilename(TILE_LAYER_FG_1, b, "tile_up");
        }
        wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      }

      if (spell->spell_left) {
        Widp  b   = wid_new_square_button(spells_container, "wid spell grid connector");
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
          wid_set_tilename(TILE_LAYER_FG_1, b, "tile_left");
        }
        wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      }

      if (spell->spell_right) {
        Widp  b   = wid_new_square_button(spells_container, "wid spell grid connector");
        point tl2 = tl;
        point br2 = br;

        tl2.x += WID_SPELL_BUTTON_WIDTH;
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
          wid_set_tilename(TILE_LAYER_FG_1, b, "tile_right");
        }
        wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      }
    }
  }

  if (g_opt_ascii) {
    {
      auto  w = wid_new_square_button(spells_container, "wid spells window close");
      point tl(spells_width - 2, 0);
      point br(spells_width, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_spell_close);
    }

    {
      auto  w = wid_new_square_button(spells_container, "wid spells window close");
      point tl(0, 0);
      point br(2, 2);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "X");
      wid_set_style(w, UI_WID_STYLE_RED);
      wid_set_on_mouse_up(w, wid_spell_close);
    }
  } else {
    {
      auto  w = wid_new_square_button(spells_container, "wid spells window close");
      point tl(spells_width - 2, 0);
      point br(spells_width, 2);
      wid_set_pos(w, tl, br);
      wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_close");
      wid_set_on_mouse_up(w, wid_spell_close);
    }

    {
      auto  w = wid_new_square_button(spells_container, "wid spells window close");
      point tl(0, 0);
      point br(2, 2);
      wid_set_pos(w, tl, br);
      wid_set_tilename(TILE_LAYER_BG_0, w, "ui_icon_close");
      wid_set_on_mouse_up(w, wid_spell_close);
    }
  }

  //
  // Buttons on the left for the various spell trees
  //
  int                      y = 1;
  std::list< std::string > spell_trees;

  for (auto iter : game->spell_tree) {
    auto tree_name = iter.first;
    spell_trees.push_back(tree_name);
  }

  for (auto tree_name : spell_trees) {
    y += 4;
    auto  w = wid_new_square_button(spells_container, "wid spells window close");
    point tl(1, y);
    point br(WID_SPELL_LEFT_BUTTON, y + 2);
    wid_set_pos(w, tl, br);

    if (tree_name == current_tree_name) {
      wid_set_style(w, UI_WID_STYLE_GREEN);
    } else {
      wid_set_style(w, UI_WID_STYLE_DARK);
    }
    wid_set_text(w, tree_name);
    wid_set_string_context(w, tree_name);
    wid_set_on_mouse_over_begin(w, wid_spell_tree_over_begin);
  }

  wid_update(spells_container);

  wid_actionbar_init();
}
