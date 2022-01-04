//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "game_levels_grid.hpp"
#include "my_color.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_time.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_topcon.hpp"

class game_levels_grid_ctx
{
public:
  ~game_levels_grid_ctx()
  {
    TRACE_NO_INDENT();
    if (w) {
      wid_destroy(&w);
    }
    delete nodes;
  }

  /*
   * Parent widget
   */
  Widp w {};

  /*
   * Current button
   */
  Widp b {};

  /*
   * Text input widget
   */
  Widp input {};

  /*
   * Item currently in focus
   */
  int focusx;
  int focusy;

  /*
   * When the level_grid was made.
   */
  uint32_t created;

  /*
   * Items in the level_grid
   */
  Widp buttons[ DUNGEONS_GRID_CHUNK_HEIGHT ][ DUNGEONS_GRID_CHUNK_WIDTH ];

  /*
   * Just created?
   */
  int is_new;

  /*
   * The level construction
   */
  class Nodes *nodes {};
};

static game_levels_grid_ctx *g_ctx;

static void game_levels_grid_destroy(Widp w);
static void game_levels_grid_set_focus(game_levels_grid_ctx *ctx, int focusx, int focusy);

#define ROOM_WIDTH_CHARS  8
#define ROOM_HEIGHT_CHARS 3

static void game_levels_grid_update_buttons(Widp w)
{
  TRACE_NO_INDENT();
  game_levels_grid_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (game_levels_grid_ctx *) wid_get_void_context(w);
  }

  verify(MTYPE_WID, ctx);

  int width  = ROOM_WIDTH_CHARS - 1;
  int height = ROOM_HEIGHT_CHARS - 1;

  int x, y;

  ctx->b = 0;

  for (x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
    for (y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {

      Widp b = ctx->buttons[ y ][ x ];
      if (! b) {
        continue;
      }

      point tl;
      point br;
      color c;

      tl.x = x * (width + 2);
      tl.y = y * (height + 2);

      br.x = tl.x;
      br.y = tl.y;
      br.x += width - 1;
      br.y += height - 1;

      if ((x == ctx->focusx) && (y == ctx->focusy)) {
        c      = GREEN;
        ctx->b = b;
        wid_raise(b);
      } else {
        wid_lower(b);

        c = GRAY70;
      }

      if (ctx->is_new) {
        wid_set_pos(b, tl, br);
      }

      wid_set_color(b, WID_COLOR_TEXT_FG, c);
    }
  }
  wid_update(w);
}

static void game_levels_grid_event(Widp w, int focusx, int focusy) { TRACE_NO_INDENT(); }

static uint8_t game_levels_grid_mouse_event(Widp w, int focusx, int focusy)
{
  TRACE_NO_INDENT();
  game_levels_grid_event(w, focusx, focusy);

  return true;
}

static uint8_t game_levels_grid_button_mouse_event(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  int focus  = wid_get_int_context(w);
  int focusx = (focus & 0xff);
  int focusy = (focus & 0xff00) >> 8;

  return (game_levels_grid_mouse_event(w, focusx, focusy));
}

static void game_levels_grid_set_focus(game_levels_grid_ctx *ctx, int focusx, int focusy)
{
  TRACE_NO_INDENT();
  ctx->focusx = focusx;
  ctx->focusy = focusy;

  game_levels_grid_update_buttons(ctx->w);
}

static void game_levels_grid_mouse_over(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();
  game_levels_grid_ctx *ctx = (game_levels_grid_ctx *) wid_get_void_context(w);
  verify(MTYPE_WID, ctx);

  if (! relx && ! rely && ! wheelx && ! wheely) {
    return;
  }

  /*
   * If we recreate the level_grid with a fixed focus we will be told about
   * a mouse over event immediately which may not be over the focus item
   * and will cause us to move. Annoying.
   */
  if (time_get_time_ms() - ctx->created < 100) {
    return;
  }

  int focus  = wid_get_int_context(w);
  int focusx = (focus & 0xff);
  int focusy = (focus & 0xff00) >> 8;

  game_levels_grid_set_focus(ctx, focusx, focusy);
}

static void game_levels_grid_destroy(Widp w)
{
  TRACE_NO_INDENT();
  game_levels_grid_ctx *ctx;

  if (! w) {
    ctx = g_ctx;
    verify(MTYPE_WID, ctx);
    g_ctx = nullptr;
  } else {
    ctx = (game_levels_grid_ctx *) wid_get_void_context(w);
    verify(MTYPE_WID, ctx);
    wid_set_void_context(w, 0);
  }

  /*
   * Might be in tbe process of destroying.
   */
  if (! ctx->w) {
    return;
  }
  delete ctx;
}

static void game_levels_grid_tick(Widp w)
{
  TRACE_NO_INDENT();
  game_levels_grid_ctx *ctx = (game_levels_grid_ctx *) wid_get_void_context(w);
  verify(MTYPE_WID, ctx);

  static int val;
  static int delta = 1;
  static int step  = 2;

  val += delta * step;

  if (val > 255) {
    val   = 255;
    delta = -1;
  }

  if (val < 200) {
    val   = 200;
    delta = 1;
  }

  int x, y;

  for (x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
    for (y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {

      if ((x != ctx->focusx) || (y != ctx->focusy)) {
        continue;
      }

      Widp b = ctx->buttons[ y ][ x ];

      color c;
      c   = GREEN;
      c.g = val;

      /*
       * Make sure the other widgets look plain in all modes.
       */
      int mode;
      for (mode = WID_MODE_NORMAL; mode < WID_MODE_LAST; mode++) {
        wid_set_mode(b, (wid_mode) mode);
        wid_set_color(b, WID_COLOR_TEXT_FG, c);
      }

      wid_set_mode(w, (wid_mode) WID_MODE_NORMAL);
    }
  }
}

static uint8_t game_levels_grid_go_back(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  game_levels_grid_destroy(wid_get_top_parent(w));
  game->fini();
  game->main_menu_select();
  wid_hide(wid_topcon_window);
  wid_hide(wid_botcon_window);
  return true;
}

#if 0
static uint8_t game_levels_grid_reroll(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  game_levels_grid_destroy(wid_get_top_parent(w));
  game_levels_grid_init();
  return true;
}
#endif

static uint8_t game_levels_grid_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_NO_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'b' :
              case SDLK_ESCAPE : game_levels_grid_go_back(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t game_levels_grid_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

void game_levels_grid_init(void)
{
  TRACE_AND_INDENT();
  /*
   * Create a context to hold button info so we can update it when the focus changes
   */
  game_levels_grid_ctx *ctx = new game_levels_grid_ctx();
  newptr(MTYPE_WID, ctx, "wid level grid ctx");
  g_ctx = ctx;

  ctx->nodes  = new Nodes(10, 10, false /* not a dungeon */);
  ctx->focusx = -1;
  ctx->focusy = -1;

  auto window = wid_new_square_window("wid level grid");
  ctx->w      = window;
  ctx->is_new = true;

  /*
   * Main window
   */
  {
    point tl = make_point(0, 0);
    point br = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);

    wid_set_pos(window, tl, br);
    wid_set_style(window, UI_WID_STYLE_NORMAL);
    wid_set_void_context(window, ctx);
    wid_set_on_key_up(window, game_levels_grid_key_up);
    wid_set_on_key_down(window, game_levels_grid_key_down);
  }

  /*
   * Create the title
   */
  {
    Widp w = wid_new_square_button(window, "wid level_grid title");

    point tl = make_point(0, 1);
    point br = make_point(TERM_WIDTH - 1, 1);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "Aim: collect the Orb of Zorb fragments and reach the bottom level to confront Zorbash.");
    wid_set_shape_none(w);
    wid_set_color(w, WID_COLOR_TEXT_FG, YELLOW);
  }

  /*
   * Create the button container
   */
  {
    Widp button_container = wid_new_square_button(window, "wid level grid buttons");
    wid_set_shape_none(button_container);
    wid_set_on_tick(button_container, game_levels_grid_tick);

    point tl = make_point(0, 0);
    point br = make_point(0, 0);

    br.x = (ROOM_WIDTH_CHARS + 1) * DUNGEONS_GRID_CHUNK_WIDTH;
    br.y = (ROOM_HEIGHT_CHARS + 1) * DUNGEONS_GRID_CHUNK_HEIGHT;

    auto offx = (TERM_WIDTH - (br.x - tl.x)) / 2;
    auto offy = (TERM_HEIGHT - (br.y - tl.y)) / 2;

    tl.x += offx;
    tl.y += offy;
    br.x += offx;
    br.y += offy;

    wid_set_pos(button_container, tl, br);
    wid_set_void_context(button_container, ctx);

    /*
     * Create the buttons
     */
    for (auto y = 0; y < ctx->nodes->grid_height; y++) {
      for (auto x = 0; x < ctx->nodes->grid_width; x++) {
        auto node = ctx->nodes->getn(x, y);
        if (! node) {
          continue;
        }

        std::string text;

        if (node->is_ascend_dungeon) {
          text = "S";
        }
        if (node->is_descend_dungeon) {
          text = "E";
        }
        if (node->is_lock) {
          text = "D";
        }
        if (node->is_key) {
          text = "K";
        }

        if (node->depth > 0) {
          text += (char) ('0' + node->depth);
        }

        if (text.empty()) {
          continue;
        }

        if (node->on_critical_path) {
          text += "*";
        }

        Widp b = wid_new_square_button(button_container, "wid level grid button");

        ctx->buttons[ y ][ x ] = b;

        wid_set_text(b, text);

        wid_set_on_mouse_over_begin(b, game_levels_grid_mouse_over);
        wid_set_on_mouse_down(b, game_levels_grid_button_mouse_event);
        wid_set_style(b, UI_WID_STYLE_DARK);
        wid_set_color(b, WID_COLOR_TEXT_FG, GREEN);
        wid_set_mode(b, WID_MODE_OVER);
        wid_set_color(b, WID_COLOR_TEXT_FG, GREEN);
        wid_set_mode(b, WID_MODE_NORMAL);

        wid_set_void_context(b, ctx);
        int focus = (y << 8) | x;
        wid_set_int_context(b, focus);
      }
    }
  }

  game_levels_grid_update_buttons(window);
  wid_set_do_not_lower(window, 1);
  wid_update(window);
  wid_raise(window);
  wid_set_focus(window);

  ctx->created = time_get_time_ms();
}
