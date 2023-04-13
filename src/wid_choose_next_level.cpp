//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_choose_level.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_topcon.hpp"

static int WID_LEVEL_WIDTH_CHARS  = 7;
static int WID_LEVEL_HEIGHT_CHARS = 7;

uint8_t     wid_choose_next_dungeons_enter(Widp w, int x, int y, uint32_t button);
static void wid_choose_next_dungeons_update_buttons(Widp w);

static WidPopup *wid_level_description;

class wid_choose_next_dungeons_ctx
{
public:
  ~wid_choose_next_dungeons_ctx()
  {
    TRACE_NO_INDENT();
    if (w) {
      wid_destroy(&w);

      delete wid_level_description;
      wid_level_description = nullptr;
      delete wid_level_contents;
      wid_level_contents = nullptr;
      if (game) {
        game->paused = false;
        game->change_state(Game::STATE_NORMAL, "chose next dungeon");
      }
    }
  }

  //
  // Parent widget
  //
  Widp w {};

  //
  // Current button
  //
  Widp b {};

  //
  // Item currently in focus
  //
  int focusx;
  int focusy;

  //
  // Items in the level_grid
  //
  Widp buttons[ DUNGEONS_GRID_CHUNK_HEIGHT ][ DUNGEONS_GRID_CHUNK_WIDTH ];

  std::vector< Levelp > next_levels[ DUNGEONS_GRID_CHUNK_HEIGHT ][ DUNGEONS_GRID_CHUNK_WIDTH ];
  std::vector< Levelp > prev_levels[ DUNGEONS_GRID_CHUNK_HEIGHT ][ DUNGEONS_GRID_CHUNK_WIDTH ];

  //
  // Level for this location
  //
  Levelp levels[ DUNGEONS_GRID_CHUNK_HEIGHT ][ DUNGEONS_GRID_CHUNK_WIDTH ] = {};

  Levelp current_level {};

  //
  // First level
  //
  class DungeonNode *start_node {};

  //
  // Which direction are we moving in?
  //
  bool is_descending {};
  bool is_ascending {};
};

static wid_choose_next_dungeons_ctx *g_ctx;

static void wid_choose_next_dungeons_destroy(Widp w);
static void wid_choose_next_dungeons_set_focus(wid_choose_next_dungeons_ctx *ctx, int focusx, int focusy);

static void wid_choose_next_dungeons_set_focus(wid_choose_next_dungeons_ctx *ctx, int focusx, int focusy)
{
  TRACE_NO_INDENT();
  ctx->focusx = focusx;
  ctx->focusy = focusy;

  wid_choose_next_dungeons_update_buttons(ctx->w);
}

static void wid_choose_next_dungeons_mouse_over(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  auto *ctx = (wid_choose_next_dungeons_ctx *) wid_get_void_context(w);
  verify(MTYPE_WID, ctx);

  if (! relx && ! rely && ! wheelx && ! wheely) {
    return;
  }

  int focus = wid_get_int_context(w);
  int x     = (focus & 0xff);
  int y     = (focus & 0xff00) >> 8;

  wid_choose_next_dungeons_set_focus(ctx, x, y);

  auto level_at = wid_choose_level_grid_to_level_coord(x, y);
  auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
  if (l) {
    delete wid_level_description;
    wid_level_description = nullptr;

    point tl = make_point(TERM_WIDTH - UI_WID_POPUP_WIDTH_NORMAL - 1, TERM_HEIGHT - 12);
    point br = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);

    char tmp[ MAXSHORTSTR ];
    wid_level_description = new WidPopup("Level stats", tl, br, nullptr, "", false, false);
    wid_level_description->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Level reconn");
    wid_level_description->log(UI_LOGGING_EMPTY_LINE);

    snprintf(tmp, sizeof(tmp) - 1, "Monst HP estimate %u", l->total_monst_hp_level());
    wid_level_description->log(tmp, TEXT_FORMAT_LHS);
    wid_level_description->log(UI_LOGGING_EMPTY_LINE);

    snprintf(tmp, sizeof(tmp) - 1, "Monst damage est. %u", l->total_monst_dmg_level());
    wid_level_description->log(tmp, TEXT_FORMAT_LHS);
    wid_level_description->log(UI_LOGGING_EMPTY_LINE);

    snprintf(tmp, sizeof(tmp) - 1, "Loot value est.   %u", l->total_loot_level());
    wid_level_description->log(tmp, TEXT_FORMAT_LHS);
    wid_level_description->log(UI_LOGGING_EMPTY_LINE);

    snprintf(tmp, sizeof(tmp) - 1, "Food HP est.      %u", l->total_food_level());
    wid_level_description->log(tmp, TEXT_FORMAT_LHS);

    auto        l = ctx->levels[ y ][ x ];
    std::string bg_tilename;
    switch (l->difficulty_depth) {
      case -1: break;
      case 0: bg_tilename = "dungeon_icon.1"; break;
      case 1: bg_tilename = "dungeon_icon.2"; break;
      case 2: bg_tilename = "dungeon_icon.3"; break;
      case 3: bg_tilename = "dungeon_icon.4"; break;
      case 4: bg_tilename = "dungeon_icon.5"; break;
      case 5: bg_tilename = "dungeon_icon.6"; break;
      case 6: bg_tilename = "dungeon_icon.7"; break;
      case 7: bg_tilename = "dungeon_icon.8"; break;
    }

    if (g_opt_ascii) {
      switch (l->difficulty_depth) {
        case -1: break;
        case 0:
          wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, get_difficulty_depth_color(0));
          break;
        case 1:
          wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, get_difficulty_depth_color(1));
          break;
        case 2:
          wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, get_difficulty_depth_color(2));
          break;
        case 3:
          wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, get_difficulty_depth_color(3));
          break;
        case 4:
          wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, get_difficulty_depth_color(4));
          break;
        case 5:
          wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, get_difficulty_depth_color(5));
          break;
        case 6:
          wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, get_difficulty_depth_color(6));
          break;
        case 7:
          wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, get_difficulty_depth_color(7));
          break;
      }

      wid_set_style(wid_level_description->wid_popup_container, UI_WID_STYLE_SOLID_DEFAULT);
    } else {
      wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, WHITE);
      wid_set_style(wid_level_description->wid_popup_container, UI_WID_STYLE_SPARSE_NONE);
    }
  }

  IF_DEBUG
  {
    if (l) {
      wid_show_dungeon_contents(l);
    }
  }
}

static void wid_choose_next_dungeons_destroy(Widp w)
{
  TRACE_NO_INDENT();
  wid_choose_next_dungeons_ctx *ctx;

  if (! w) {
    ctx = g_ctx;
    verify(MTYPE_WID, ctx);
    g_ctx = nullptr;
  } else {
    ctx = (wid_choose_next_dungeons_ctx *) wid_get_void_context(w);
    verify(MTYPE_WID, ctx);
    wid_set_void_context(w, nullptr);
  }

  /*
   * Might be in tbe process of destroying.
   */
  if (! ctx->w) {
    return;
  }

  if (ctx) {
    oldptr(MTYPE_WID, ctx);
    delete ctx;
  }
}

static void wid_choose_next_dungeons_tick(Widp w)
{
  TRACE_NO_INDENT();
  auto *ctx = (wid_choose_next_dungeons_ctx *) wid_get_void_context(w);
  verify(MTYPE_WID, ctx);

  wid_choose_levels_bg();

  static int val;
  static int delta = 1;
  static int step  = 2;

  val += delta * step;

  if (val > 250) {
    val   = 250;
    delta = -2;
  }

  if (val < 100) {
    val   = 100;
    delta = 2;
  }

  {
    for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
      for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
        Widp b = ctx->buttons[ y ][ x ];
        if (! b) {
          continue;
        }

        auto l = ctx->levels[ y ][ x ];

        if (g_opt_debug1) {
          color c = WHITE;
          c.a     = val;
          wid_set_color(b, WID_COLOR_BG, c);
          wid_update(b);
          wid_set_on_mouse_down(b, wid_choose_next_dungeons_enter);

          if (game->robot_mode) {
            if (non_pcg_random_range(0, 1000) <= 10) {
              game->request_to_choose_level = b;
            }
          }

          continue;
        }

        wid_set_color(b, WID_COLOR_BG, GRAY30);
        wid_update(b);

        if (game->level == l) {
          //
          // Is the player descending?
          //
          // Limit to the next levels.
          //
          if (ctx->is_descending || g_opt_debug1) {
            for (auto n : ctx->next_levels[ y ][ x ]) {
              auto n_at = n->grid_at;
              Widp b    = ctx->buttons[ n_at.y ][ n_at.x ];
              if (b) {
                color c = WHITE;
                if (g_opt_ascii) {
                  c = UI_DUNGEONS_CURRENT_LEVEL_COLOR;
                }
                c.a = val;
                wid_set_color(b, WID_COLOR_BG, c);
                wid_update(b);
                wid_set_on_mouse_down(b, wid_choose_next_dungeons_enter);

                if (game->robot_mode) {
                  if (non_pcg_random_range(0, 1000) <= 10) {
                    game->request_to_choose_level = b;
                  }
                }
              }
            }
          }

          //
          // Is the player ascending?
          //
          // Limit to the levels we have previously completed; unless we fell
          // in which case we are more lenient.
          //
          if (ctx->is_ascending) {
            for (auto n : ctx->prev_levels[ y ][ x ]) {
              //
              // Only allow ascension to levels we've finished.
              //
              if (! ctx->current_level->is_entered_by_falling) {
                //
                // Unless we fell here, in which case we may have no exit
                //
                if (! n->is_completed) {
                  continue;
                }
              }

              auto n_at = n->grid_at;
              Widp b    = ctx->buttons[ n_at.y ][ n_at.x ];
              if (b) {
                color c = WHITE;
                if (g_opt_ascii) {
                  c = UI_DUNGEONS_CURRENT_LEVEL_COLOR;
                }
                c.a = val;
                wid_set_color(b, WID_COLOR_BG, c);
                wid_update(b);
                wid_set_on_mouse_down(b, wid_choose_next_dungeons_enter);
              }
            }
          }
        }
      }
    }
  }
}

static void wid_choose_next_dungeons_post_display_tick(Widp w)
{
  TRACE_NO_INDENT();
  auto *ctx = (wid_choose_next_dungeons_ctx *) wid_get_void_context(w);
  verify(MTYPE_WID, ctx);

  for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
    for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
      Widp b = ctx->buttons[ y ][ x ];
      if (! b) {
        continue;
      }

      auto level_at = wid_choose_level_grid_to_level_coord(x, y);
      auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
      if (! l) {
        continue;
      }

      wid_choose_level_border(b, l);
    }
  }

  IF_DEBUG
  {
    for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
      for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
        Widp b = ctx->buttons[ y ][ x ];
        if (! b) {
          continue;
        }

        auto level_at = wid_choose_level_grid_to_level_coord(x, y);
        auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
        if (! l) {
          continue;
        }

        if (! l->map_debug_valid) {
          l->update_map_debug(x, y);
        }
      }
    }
  }

  if (! g_opt_ascii) {
    IF_DEBUG
    {
      if ((ctx->focusx != -1) && (ctx->focusx != -1)) {
        auto level_at = wid_choose_level_grid_to_level_coord(ctx->focusx, ctx->focusy);
        auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);

        if (l) {
          if (wid_level_description) {
            int tlx, tly, brx, bry;
            int szh = MAP_HEIGHT * 3;
            int szw = MAP_WIDTH * 3;
            tlx     = game->config.ui_pix_width - szw;
            tly     = 0;
            brx     = game->config.ui_pix_width;
            bry     = szh;

            gl_enter_2d_mode(game->config.ui_pix_width, game->config.ui_pix_height);
            glcolor(WHITE);
            blit_fbo_bind_locked(FBO_WID);
            l->display_pixelart_map_debug(ctx->focusx, ctx->focusy, tlx, tly, brx, bry);
            blit_fbo_unbind_locked();
          }
        }
      }
    }
  }
}

uint8_t wid_choose_next_dungeons_enter(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();

  wid_choose_next_dungeons_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (wid_choose_next_dungeons_ctx *) wid_get_void_context(wid_get_top_parent(w));
  }

  verify(MTYPE_WID, ctx);
  if (! ctx) {
    ERR("No ctx");
    return true;
  }

  auto level = game->level;
  if (! level) {
    ERR("No level");
    return true;
  }
  auto player = level->player;
  if (! player) {
    ERR("No player");
    return true;
  }

  {
    int focus = wid_get_int_context(w);
    int x     = (focus & 0xff);
    int y     = (focus & 0xff00) >> 8;

    LOG("Chose level at %d,%d", x, y);

    auto next_level = ctx->levels[ y ][ x ];
    if (! next_level) {
      LOG("No level at %d,%d", x, y);
      return true;
    }

    if (ctx->is_ascending) {
      LOG("Ascend to %s", next_level->world_at.to_string().c_str());
      player->ascend_dungeon(true, next_level->world_at);
    }

    if (ctx->is_descending) {
      LOG("Descend to %s", next_level->world_at.to_string().c_str());
      player->descend_dungeon(true, next_level->world_at);
    }

    wid_choose_next_dungeons_destroy(wid_get_top_parent(w));

    wid_actionbar_init();
    wid_visible(wid_topcon_window);
  }

  return true;
}

static void wid_choose_next_dungeons_update_button(wid_choose_next_dungeons_ctx *ctx, Widp b, int x, int y)
{
  TRACE_NO_INDENT();
  if (! b) {
    return;
  }

  int width  = WID_LEVEL_WIDTH_CHARS - 1;
  int height = WID_LEVEL_HEIGHT_CHARS - 1;

  point tl;
  point br;

  tl.x = x * (width + 1);
  tl.y = y * (height + 1);

  br.x = tl.x;
  br.y = tl.y;
  br.x += width - 1;
  br.y += height - 1;

  if ((x == ctx->focusx) && (y == ctx->focusy)) {
    ctx->b = b;
    wid_raise(b);
  } else {
    wid_lower(b);
  }

  wid_set_pos(b, tl, br);

  auto l = ctx->levels[ y ][ x ];
  if (! l) {
    return;
  }

  std::string bg_tilename;
  if (ctx->levels[ y ][ x ]) {
    switch (l->difficulty_depth) {
      case -1: break;
      case 0:
        bg_tilename = "dungeon_icon.1";
        if (g_opt_ascii) {
          wid_set_color(b, WID_COLOR_BG, get_difficulty_depth_color(0));
        }
        break;
      case 1:
        bg_tilename = "dungeon_icon.2";
        if (g_opt_ascii) {
          wid_set_color(b, WID_COLOR_BG, get_difficulty_depth_color(1));
        }
        break;
      case 2:
        bg_tilename = "dungeon_icon.3";
        if (g_opt_ascii) {
          wid_set_color(b, WID_COLOR_BG, get_difficulty_depth_color(2));
        }
        break;
      case 3:
        bg_tilename = "dungeon_icon.4";
        if (g_opt_ascii) {
          wid_set_color(b, WID_COLOR_BG, get_difficulty_depth_color(3));
        }
        break;
      case 4:
        bg_tilename = "dungeon_icon.5";
        if (g_opt_ascii) {
          wid_set_color(b, WID_COLOR_BG, get_difficulty_depth_color(4));
        }
        break;
      case 5:
        bg_tilename = "dungeon_icon.6";
        if (g_opt_ascii) {
          wid_set_color(b, WID_COLOR_BG, get_difficulty_depth_color(5));
        }
        break;
      case 6:
        bg_tilename = "dungeon_icon.7";
        if (g_opt_ascii) {
          wid_set_color(b, WID_COLOR_BG, get_difficulty_depth_color(6));
        }
        break;
      case 7:
        bg_tilename = "dungeon_icon.8";
        if (g_opt_ascii) {
          wid_set_color(b, WID_COLOR_BG, get_difficulty_depth_color(7));
        }
        break;
    }
  }

  wid_set_style(b, UI_WID_STYLE_GRAY);

  std::string fg_tilename;

  if (l->is_boss_level) {
    fg_tilename = "boss_icon";
  }

  if (l->is_final_boss_level) {
    fg_tilename = "final_boss_icon";
  }

  if (l->is_crystal_level) {
    switch (l->difficulty_depth) {
      case -1: break;
      case 1: fg_tilename = "crystal.1"; break;
      case 2: fg_tilename = "crystal.2"; break;
      case 3: fg_tilename = "crystal.3"; break;
      case 4: fg_tilename = "crystal.4"; break;
      case 5: fg_tilename = "crystal.5"; break;
      case 6: fg_tilename = "crystal.6"; break;
      case 7: fg_tilename = "crystal.7"; break;
    }
  }

  if (! g_opt_ascii) {
    if (! bg_tilename.empty()) {
      wid_set_bg_tilename(b, bg_tilename);
    }
  }

  if (game->level == l) {
    fg_tilename = "you_are_here_icon";
  }

  if (! g_opt_ascii) {
    if (! bg_tilename.empty()) {
      wid_set_bg_tilename(b, bg_tilename);
    }

    if (! fg_tilename.empty()) {
      wid_set_fg_tilename(b, fg_tilename);
    }
  }

  char tmp[ MAXSHORTSTR ];
  snprintf(tmp, sizeof(tmp) - 1, "%d", l->dungeon_walk_order_level_no);
  wid_set_text(b, tmp);
  wid_set_text_lhs(b, true);
  wid_set_text_top(b, true);
}

static void wid_choose_next_dungeons_update_buttons(Widp w)
{
  TRACE_NO_INDENT();
  wid_choose_next_dungeons_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (wid_choose_next_dungeons_ctx *) wid_get_void_context(w);
  }

  verify(MTYPE_WID, ctx);

  int x, y;

  ctx->b = nullptr;

  for (x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
    for (y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
      Widp b = ctx->buttons[ y ][ x ];
      if (! b) {
        continue;
      }
      wid_choose_next_dungeons_update_button(ctx, b, x, y);
    }
  }
  wid_update(w);
}

void Game::wid_choose_next_dungeons(Levelp current, bool is_ascending, bool is_descending)
{
  TRACE_AND_INDENT();

  auto level = game->level;
  if (! level) {
    ERR("No level");
    return;
  }
  auto player = level->player;
  if (! player) {
    ERR("No player");
    return;
  }

  py_call_void_fn("events", "on_initial_dungeon_menu_select", 0);

  paused                    = true;
  player->is_changing_level = true;

  if (g_opt_ascii) {
    WID_LEVEL_WIDTH_CHARS  = 3;
    WID_LEVEL_HEIGHT_CHARS = 3;
  } else {
    WID_LEVEL_WIDTH_CHARS  = 7;
    WID_LEVEL_HEIGHT_CHARS = 7;
  }

  //
  // Create a context to hold button info so we can update it when the focus changes
  //
  auto *ctx = new wid_choose_next_dungeons_ctx();
  newptr(MTYPE_WID, ctx, "wid level grid ctx");
  g_ctx = ctx;

  auto y = current->world_at.y;
  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto z = 0; z < LEVELS_DEEP; ++z) {
      auto l = get(world.levels, x, y, z);
      if (l) {
        auto gx                 = l->grid_at.x;
        auto gy                 = l->grid_at.y;
        ctx->levels[ gy ][ gx ] = l;
      }
    }
  }

  ctx->focusx        = -1;
  ctx->focusy        = -1;
  ctx->is_descending = is_descending;
  ctx->is_ascending  = is_ascending;
  ctx->current_level = current;

  auto window = wid_new_square_window("wid level grid");
  ctx->w      = window;

  /*
   * Main window
   */
  {
    point tl = make_point(0, 0);
    point br = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);

    wid_set_pos(window, tl, br);
    wid_set_shape_none(window);
    wid_set_void_context(window, ctx);
  }

  /*
   * Create the title
   */
  {
    Widp w = wid_new_square_button(window, "wid level_grid title");

    point tl = make_point(0, 1);
    point br = make_point(TERM_WIDTH - 1, 1);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "Choose your next level, mortal!");
    wid_set_shape_none(w);
    wid_set_color(w, WID_COLOR_TEXT_FG, YELLOW);
  }
  {
    Widp w = wid_new_square_button(window, "wid level_grid title");

    point tl = make_point(0, 0);
    point br = make_point(TERM_WIDTH - 1, 0);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "Dungeon seed: " + seed_name);
    wid_set_shape_none(w);
    wid_set_color(w, WID_COLOR_TEXT_FG, UI_DUNGEONS_SEED_COLOR);
  }

  /*
   * Create the button container
   */
  {
    Widp button_container = wid_new_square_button(window, "wid level grid buttons");
    wid_set_shape_none(button_container);
    wid_set_on_tick(button_container, wid_choose_next_dungeons_tick);
    wid_set_on_tick_post_display(button_container, wid_choose_next_dungeons_post_display_tick);

    point tl = make_point(0, 0);
    point br = make_point(0, 0);

    br.x = (WID_LEVEL_WIDTH_CHARS + 1) * DUNGEONS_GRID_CHUNK_WIDTH;
    br.y = (WID_LEVEL_HEIGHT_CHARS + 1) * DUNGEONS_GRID_CHUNK_HEIGHT;

    auto offx = (TERM_WIDTH - (br.x - tl.x)) / 2;
    auto offy = (TERM_HEIGHT - (br.y - tl.y)) / 2;

    tl.x += offx;
    tl.y += offy;
    br.x += offx;
    br.y += offy;

    tl.y += 9;
    br.y += 9;

    wid_set_pos(button_container, tl, br);
    wid_set_void_context(button_container, ctx);

    int ptl_x;
    int ptl_y;
    int pbr_x;
    int pbr_y;
    wid_get_tl_x_tl_y_br_x_br_y(button_container, &ptl_x, &ptl_y, &pbr_x, &pbr_y);

    //
    // Create the buttons
    //
    for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
      for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
        auto l = ctx->levels[ y ][ x ];
        if (! l) {
          continue;
        }

        //
        // Create a button describing the level
        //
        Widp b                 = wid_new_square_button(button_container, "wid level grid button");
        ctx->buttons[ y ][ x ] = b;

        wid_set_on_mouse_over_begin(b, wid_choose_next_dungeons_mouse_over);
        wid_set_color(b, WID_COLOR_BG, WHITE);
        wid_set_void_context(b, ctx);
        int focus = (y << 8) | x;
        wid_set_int_context(b, focus);

        wid_choose_next_dungeons_update_button(ctx, b, x, y);

        int tl_x;
        int tl_y;
        int br_x;
        int br_y;
        wid_get_tl_x_tl_y_br_x_br_y(b, &tl_x, &tl_y, &br_x, &br_y);
        tl_x -= ptl_x;
        tl_y -= ptl_y;
        br_x -= pbr_x;
        br_y -= pbr_y;

        tl_y--;

        bool has_door_down {};
        bool has_door_up {};
        bool has_door_left {};
        bool has_door_right {};

        for (auto p : l->next_levels) {
          auto alt = get(game->world.levels, p.x, p.y, p.z);
          if (! alt) {
            continue;
          }
          if (l->grid_at == alt->grid_at + point(0, -1)) {
            has_door_down = true;
            ctx->next_levels[ y ][ x ].push_back(alt);
          }
          if (l->grid_at == alt->grid_at + point(0, 1)) {
            has_door_up = true;
            ctx->next_levels[ y ][ x ].push_back(alt);
          }
          if (l->grid_at == alt->grid_at + point(-1, 0)) {
            has_door_right = true;
            ctx->next_levels[ y ][ x ].push_back(alt);
          }
          if (l->grid_at == alt->grid_at + point(1, 0)) {
            has_door_left = true;
            ctx->next_levels[ y ][ x ].push_back(alt);
          }
        }

        for (auto p : l->prev_levels) {
          auto alt = get(game->world.levels, p.x, p.y, p.z);
          if (! alt) {
            continue;
          }
          if (l->grid_at == alt->grid_at + point(0, -1)) {
            has_door_down = true;
            ctx->prev_levels[ y ][ x ].push_back(alt);
          }
          if (l->grid_at == alt->grid_at + point(0, 1)) {
            has_door_up = true;
            ctx->prev_levels[ y ][ x ].push_back(alt);
          }
          if (l->grid_at == alt->grid_at + point(-1, 0)) {
            has_door_right = true;
            ctx->prev_levels[ y ][ x ].push_back(alt);
          }
          if (l->grid_at == alt->grid_at + point(1, 0)) {
            has_door_left = true;
            ctx->prev_levels[ y ][ x ].push_back(alt);
          }
        }

        if (g_opt_ascii) {
          if (l->is_boss_level) {
            Widp  b = wid_new_square_button(button_container, "wid level grid connector");
            point tl(tl_x, tl_y);
            point br(br_x, br_y);

            br.x = tl.x;
            br.y = tl.y;
            tl.y += WID_LEVEL_HEIGHT_CHARS - 1;
            br.y += WID_LEVEL_HEIGHT_CHARS - 1;

            wid_set_pos(b, tl, br);
            wid_set_color(b, WID_COLOR_BG, UI_DUNGEONS_BOSS_COLOR);
            wid_set_text(b, "B");
            wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
          }

          if (l->is_crystal_level) {
            Widp  b = wid_new_square_button(button_container, "wid level grid connector");
            point tl(tl_x, tl_y);
            point br(br_x, br_y);

            br.x = tl.x;
            br.y = tl.y;
            tl.y += WID_LEVEL_HEIGHT_CHARS - 1;
            br.y += WID_LEVEL_HEIGHT_CHARS - 1;

            wid_set_pos(b, tl, br);
            wid_set_color(b, WID_COLOR_BG, UI_DUNGEONS_CRYSTAL_COLOR);
            wid_set_text(b, "*");
            wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
          }

          if (l == game->level) {
            Widp  b = wid_new_square_button(button_container, "wid level grid connector");
            point tl(tl_x, tl_y);
            point br(br_x, br_y);

            br.x = tl.x;
            br.y = tl.y;
            tl.y += WID_LEVEL_HEIGHT_CHARS - 1;
            br.y += WID_LEVEL_HEIGHT_CHARS - 1;

            wid_set_pos(b, tl, br);
            wid_set_color(b, WID_COLOR_BG, UI_DUNGEONS_PLAYER_COLOR);
            wid_set_text(b, "@");
            wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
          }

          if (l->is_final_boss_level) {
            Widp  b = wid_new_square_button(button_container, "wid level grid connector");
            point tl(tl_x, tl_y);
            point br(br_x, br_y);

            br.x = tl.x;
            br.y = tl.y;
            tl.y += WID_LEVEL_HEIGHT_CHARS - 1;
            br.y += WID_LEVEL_HEIGHT_CHARS - 1;

            wid_set_pos(b, tl, br);
            wid_set_color(b, WID_COLOR_BG, UI_DUNGEONS_FINAL_BOSS_COLOR);
            wid_set_text(b, "Z");
            wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
          }
        }

        //
        // Create connectors between levels
        //
        if (has_door_down) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += (WID_LEVEL_WIDTH_CHARS / 2) - 1;
          br.x = tl.x;
          tl.y += WID_LEVEL_HEIGHT_CHARS;
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          if (! g_opt_ascii) {
            wid_set_fg2_tilename(b, "ud_icon");
          } else {
            wid_set_text(b, "|");
          }
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (has_door_left) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x--;
          br.x = tl.x;
          tl.y += (WID_LEVEL_HEIGHT_CHARS / 2);
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          if (! g_opt_ascii) {
            wid_set_fg2_tilename(b, "lr_icon");
          } else {
            wid_set_text(b, "_");
          }
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (has_door_right) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += WID_LEVEL_WIDTH_CHARS - 1;
          br.x = tl.x;
          tl.y += (WID_LEVEL_HEIGHT_CHARS / 2);
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          if (! g_opt_ascii) {
            wid_set_fg2_tilename(b, "lr_icon");
          } else {
            wid_set_text(b, "_");
          }
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (has_door_up) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += (WID_LEVEL_WIDTH_CHARS / 2) - 1;
          br.x = tl.x;
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          if (! g_opt_ascii) {
            wid_set_fg2_tilename(b, "ud_icon");
          } else {
            wid_set_text(b, "|");
          }
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }
      }
    }
  }

  wid_choose_next_dungeons_update_buttons(window);
  wid_update(window);
  wid_raise(window);
  wid_set_focus(window);

  game->change_state(Game::STATE_CHOOSING_LEVEL, "choose next level");
}
