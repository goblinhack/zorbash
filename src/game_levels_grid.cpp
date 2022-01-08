//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "game_levels_grid.hpp"
#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_time.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"

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

  //
  // Parent widget
  //
  Widp w {};

  //
  // Enyer button
  //
  Widp wid_enter {};

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
  // When the level_grid was made.
  //
  uint32_t created;

  //
  // Set when making the dungeons
  //
  bool generating {};
  bool generated {};

  //
  // Items in the level_grid
  //
  Widp buttons[ DUNGEONS_GRID_CHUNK_HEIGHT ][ DUNGEONS_GRID_CHUNK_WIDTH ];

  //
  // Level for this location
  //
  Levelp levels[ DUNGEONS_GRID_CHUNK_HEIGHT ][ DUNGEONS_GRID_CHUNK_WIDTH ] = {};

  //
  // Just created?
  //
  int is_new;

  //
  // The level construction
  //
  class Nodes *nodes {};
};

static game_levels_grid_ctx *g_ctx;

static void game_levels_grid_destroy(Widp w);
static void game_levels_grid_set_focus(game_levels_grid_ctx *ctx, int focusx, int focusy);

#define ROOM_WIDTH_CHARS  7
#define ROOM_HEIGHT_CHARS 7

static void game_levels_grid_update_button(game_levels_grid_ctx *ctx, Widp b, int x, int y)
{
  if (! b) {
    return;
  }

  int width  = ROOM_WIDTH_CHARS - 1;
  int height = ROOM_HEIGHT_CHARS - 1;

  point tl;
  point br;
  color c;

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

  if (ctx->is_new) {
    wid_set_pos(b, tl, br);
  }

  auto node = ctx->nodes->getn(x, y);

  std::string bg_tilename;
  std::string fg_tilename;

  if (! node) {
    return;
  }

  if (node->depth <= 0) {
    return;
  }

  if (ctx->levels[ y ][ x ]) {
    switch (node->depth) {
      case -1 : break;
      case 1 : bg_tilename = "dungeon_icon.1"; break;
      case 2 : bg_tilename = "dungeon_icon.2"; break;
      case 3 : bg_tilename = "dungeon_icon.3"; break;
      case 4 : bg_tilename = "dungeon_icon.4"; break;
      case 5 : bg_tilename = "dungeon_icon.5"; break;
      case 6 : bg_tilename = "dungeon_icon.6"; break;
      case 7 : bg_tilename = "dungeon_icon.7"; break;
      case 8 : bg_tilename = "dungeon_icon.8"; break;
    }
  } else {
    switch (node->depth) {
      case -1 : break;
      case 1 : bg_tilename = "dungeon_icon_loading.1"; break;
      case 2 : bg_tilename = "dungeon_icon_loading.2"; break;
      case 3 : bg_tilename = "dungeon_icon_loading.3"; break;
      case 4 : bg_tilename = "dungeon_icon_loading.4"; break;
      case 5 : bg_tilename = "dungeon_icon_loading.5"; break;
      case 6 : bg_tilename = "dungeon_icon_loading.6"; break;
      case 7 : bg_tilename = "dungeon_icon_loading.7"; break;
      case 8 : bg_tilename = "dungeon_icon_loading.8"; break;
    }
  }

  if (node->is_lock) {
    fg_tilename = "boss_icon.1";
  }

  if (node->is_ascend_dungeon) {
    fg_tilename = "you_icon";
  }

  if (node->is_descend_dungeon) {
    fg_tilename = "boss_icon.2";
  }

  if (node->is_key) {
    switch (node->depth) {
      case -1 : break;
      case 1 : fg_tilename = "crystal.1"; break;
      case 2 : fg_tilename = "crystal.2"; break;
      case 3 : fg_tilename = "crystal.3"; break;
      case 4 : fg_tilename = "crystal.4"; break;
      case 5 : fg_tilename = "crystal.5"; break;
      case 6 : fg_tilename = "crystal.6"; break;
      case 7 : fg_tilename = "crystal.7"; break;
      case 8 : fg_tilename = "crystal.8"; break;
    }
  }

  if (! bg_tilename.empty()) {
    wid_set_bg_tilename(b, bg_tilename);
  }
  if (! fg_tilename.empty()) {
    wid_set_fg_tilename(b, fg_tilename);
  }
}

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

  int x, y;

  ctx->b = 0;

  for (x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
    for (y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
      Widp b = ctx->buttons[ y ][ x ];
      if (! b) {
        continue;
      }
      game_levels_grid_update_button(ctx, b, x, y);
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

  wid_set_style(ctx->wid_enter, UI_WID_STYLE_GRAY);

  if (! ctx->generated) {
    for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
      for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
        Widp b = ctx->buttons[ y ][ x ];
        if (! b) {
          continue;
        }

        if (ctx->levels[ y ][ x ]) {
          continue;
        }

        auto level_at = game->current_level;
        level_at.z += y;
        level_at.x += x;
        level_at.z *= 2;
        level_at.z += 1;

        game->init_level(level_at);
        auto l = get(game->world.levels, level_at.x, level_at.y, level_at.z);
        if (! l) {
          return;
        }
        ctx->levels[ y ][ x ] = l;
        game_levels_grid_update_buttons(ctx->w);

        ctx->generating = true;
        return;
      }
    }
  }

  wid_set_style(ctx->wid_enter, UI_WID_STYLE_OK);

  ctx->generated = true;
}

static uint8_t game_levels_grid_go_back(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  game_levels_grid_destroy(wid_get_top_parent(w));
  game->fini();
  game->main_menu_select();
  return true;
}

static uint8_t game_levels_grid_reroll(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();

  game_levels_grid_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (game_levels_grid_ctx *) wid_get_void_context(w);
  }

  game_levels_grid_destroy(wid_get_top_parent(w));
  game->fini();
  g_opt_seed_name = "";
  game->init();
  game_levels_grid_init();

  ctx->generated  = false;
  ctx->generating = false;

  return true;
}

static uint8_t game_levels_grid_play(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();

#if 0
  game_levels_grid_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (game_levels_grid_ctx *) wid_get_void_context(w);
  }

  game_levels_grid_destroy(wid_get_top_parent(w));
  game->fini();
  g_opt_seed_name = "";
  game->init();
  game_levels_grid_init();

#endif

  return true;
}

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
              case 'r' : game_levels_grid_reroll(nullptr, 0, 0, 0); return true;
              case 'b' :
              case 'q' :
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

void game_grid_node_walk(class Nodes *nodes, int depth, int *furthest_depth, class DungeonNode **furthest,
                         class DungeonNode *node)
{
  if (node->is_walked) {
    return;
  }
  node->is_walked = true;

  depth++;
  if (depth > *furthest_depth) {
    *furthest_depth = depth;
    *furthest       = node;
  }

  if (node->has_door_down) {
    auto next_node = nodes->getn(node->x, node->y + 1);
    if (next_node) {
      node->dir_down = true;
      game_grid_node_walk(nodes, depth, furthest_depth, furthest, next_node);
    }
  }

  if (node->has_door_left) {
    auto next_node = nodes->getn(node->x - 1, node->y);
    if (next_node) {
      node->dir_left = true;
      game_grid_node_walk(nodes, depth, furthest_depth, furthest, next_node);
    }
  }

  if (node->has_door_up) {
    auto next_node = nodes->getn(node->x, node->y - 1);
    if (next_node) {
      node->dir_up = true;
      game_grid_node_walk(nodes, depth, furthest_depth, furthest, next_node);
    }
  }

  if (node->has_door_right) {
    auto next_node = nodes->getn(node->x + 1, node->y);
    if (next_node) {
      node->dir_right = true;
      game_grid_node_walk(nodes, depth, furthest_depth, furthest, next_node);
    }
  }
}

void game_levels_grid_init(void)
{
  TRACE_AND_INDENT();

  if (! game) {
    DIE("No game struct");
  }

  game->pre_init();

  //
  // Create a context to hold button info so we can update it when the focus changes
  //
  game_levels_grid_ctx *ctx = new game_levels_grid_ctx();
  newptr(MTYPE_WID, ctx, "wid level grid ctx");
  g_ctx = ctx;

  ctx->nodes  = new Nodes(10, 10, false /* not a dungeon */);
  ctx->focusx = -1;
  ctx->focusy = -1;

  //
  // Find the entry node
  //
  class DungeonNode *start_node {};
  for (auto y = 0; y < ctx->nodes->grid_height; y++) {
    for (auto x = 0; x < ctx->nodes->grid_width; x++) {
      auto node = ctx->nodes->getn(x, y);
      if (node->is_ascend_dungeon) {
        start_node = node;
      }
      node->dir_up             = false;
      node->dir_down           = false;
      node->dir_left           = false;
      node->dir_right          = false;
      node->is_descend_dungeon = false;
      node->x                  = x;
      node->y                  = y;
    }
  }

  if (! start_node) {
    DIE("No start dungeon node");
  }

  //
  // Assign directions that flow to the end node
  //
  int                depth          = 0;
  int                furthest_depth = 0;
  class DungeonNode *furthest_node  = 0;
  game_grid_node_walk(ctx->nodes, depth, &furthest_depth, &furthest_node, start_node);
  if (! furthest_node) {
    DIE("No furthest dungeon node");
  }
  furthest_node->is_descend_dungeon = true;

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
    wid_set_shape_none(window);
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
    wid_set_text(w, "Aim: Collect all the crystals. Reach the final level. Confront Zorbash.");
    wid_set_shape_none(w);
    wid_set_color(w, WID_COLOR_TEXT_FG, YELLOW);
  }
  {
    Widp w = wid_new_square_button(window, "wid level_grid title");

    point tl = make_point(0, 0);
    point br = make_point(TERM_WIDTH - 1, 0);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "Dungeon seed: " + game->seed_name);
    wid_set_shape_none(w);
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
  }

  point tl    = make_point(TERM_WIDTH - UI_WID_POPUP_WIDTH_NORMAL - 1, TERM_HEIGHT - 26);
  point br    = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  auto  width = br.x - tl.x - 2;
  int   y_at = y_at = TERM_HEIGHT - 18;
  int   x_at = x_at = TERM_WIDTH - width - 2;

  {
    TRACE_NO_INDENT();
    Widp w = wid_new_square_button(window, "wid level_grid reroll");

    point tl = make_point(x_at, y_at);
    point br = make_point(x_at + width, y_at + 8);

    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, game_levels_grid_play);
    wid_set_style(w, UI_WID_STYLE_GRAY);
    wid_set_text(w, "%%fg=white$E%%fg=reset$nter the Dungeon!");
    wid_set_style(w, UI_WID_STYLE_HIGHLIGHTED);
    ctx->wid_enter = w;
  }

  y_at += 10;
  {
    TRACE_NO_INDENT();
    Widp w = wid_new_square_button(window, "wid level_grid reroll");

    point tl = make_point(x_at, y_at);
    point br = make_point(x_at + width, y_at + 2);

    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, game_levels_grid_reroll);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_text(w, "%%fg=white$R%%fg=reset$eroll?");
    wid_set_style(w, UI_WID_STYLE_HIGHLIGHTED);
  }

  y_at += 3;
  {
    TRACE_NO_INDENT();
    Widp w = wid_new_square_button(window, "wid level_grid reroll");

    point tl = make_point(x_at, y_at);
    point br = make_point(x_at + width, y_at + 2);

    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, game_levels_grid_go_back);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack?");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
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

    tl.y += 5;
    br.y += 5;

    wid_set_pos(button_container, tl, br);
    wid_set_void_context(button_container, ctx);

    int32_t ptl_x;
    int32_t ptl_y;
    int32_t pbr_x;
    int32_t pbr_y;
    wid_get_tl_x_tl_y_br_x_br_y(button_container, &ptl_x, &ptl_y, &pbr_x, &pbr_y);

    /*
     * Create the buttons
     */
    for (auto x = 0; x < ctx->nodes->grid_width; x++) {
      for (auto y = 0; y < ctx->nodes->grid_height; y++) {
        auto node = ctx->nodes->getn(x, y);

        if (! node) {
          continue;
        }

        if (node->depth <= 0) {
          continue;
        }

        //
        // Create a button describing the level
        //
        Widp b                 = wid_new_square_button(button_container, "wid level grid button");
        ctx->buttons[ y ][ x ] = b;

        wid_set_on_mouse_over_begin(b, game_levels_grid_mouse_over);
        wid_set_on_mouse_down(b, game_levels_grid_button_mouse_event);
        wid_set_color(b, WID_COLOR_BG, WHITE);
        wid_set_void_context(b, ctx);
        int focus = (y << 8) | x;
        wid_set_int_context(b, focus);

        game_levels_grid_update_button(ctx, b, x, y);

        int32_t tl_x;
        int32_t tl_y;
        int32_t br_x;
        int32_t br_y;
        wid_get_tl_x_tl_y_br_x_br_y(b, &tl_x, &tl_y, &br_x, &br_y);
        tl_x -= ptl_x;
        tl_y -= ptl_y;
        br_x -= pbr_x;
        br_y -= pbr_y;

        tl_y--;

        //
        // Create connectors between levels
        //
        if (node->dir_down) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += (ROOM_WIDTH_CHARS / 2) - 1;
          br.x = tl.x;
          tl.y += ROOM_HEIGHT_CHARS;
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          wid_set_fg2_tilename(b, "ud_icon");
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (node->dir_left) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x--;
          br.x = tl.x;
          tl.y += (ROOM_HEIGHT_CHARS / 2);
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          wid_set_fg2_tilename(b, "lr_icon");
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (node->dir_right) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += ROOM_WIDTH_CHARS - 1;
          br.x = tl.x;
          tl.y += (ROOM_HEIGHT_CHARS / 2);
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          wid_set_fg2_tilename(b, "lr_icon");
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (node->dir_up) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += (ROOM_WIDTH_CHARS / 2) - 1;
          br.x = tl.x;
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          wid_set_fg2_tilename(b, "ud_icon");
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }
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
