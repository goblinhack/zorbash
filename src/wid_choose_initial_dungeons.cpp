//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>
#include <map>

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals_extra.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_time.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"

static uint8_t wid_choose_initial_dungeons_enter(Widp w, int32_t x, int32_t y, uint32_t button);
static uint8_t wid_choose_initial_dungeons_shortcut_enter(Widp w, int32_t x, int32_t y, uint32_t button);

static WidPopup *wid_level_description;
static WidPopup *wid_level_contents;

class wid_choose_initial_dungeons_ctx
{
public:
  ~wid_choose_initial_dungeons_ctx()
  {
    TRACE_NO_INDENT();
    if (w) {
      wid_destroy(&w);

      delete wid_level_description;
      wid_level_description = nullptr;
      delete wid_level_contents;
      wid_level_contents = nullptr;
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
  int  generating_level {};
  int  max_generating_level {};

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

  //
  // First level
  //
  class DungeonNode *start_node {};
};

static wid_choose_initial_dungeons_ctx *g_ctx;

static void wid_choose_initial_dungeons_destroy(Widp w);
static void wid_choose_initial_dungeons_set_focus(wid_choose_initial_dungeons_ctx *ctx, int focusx, int focusy);

#define WID_LEVEL_WIDTH_CHARS  7
#define WID_LEVEL_HEIGHT_CHARS 7

static point3d wid_choose_initial_dungeons_grid_to_level_coord(int x, int y)
{
  point3d level_at;

  level_at.x = x;
  level_at.z = (y * 2) + 1;

  return level_at;
}

static void wid_choose_initial_dungeons_update_button(wid_choose_initial_dungeons_ctx *ctx, Widp b, int x, int y)
{
  TRACE_NO_INDENT();
  if (! b) {
    return;
  }

  int width  = WID_LEVEL_WIDTH_CHARS - 1;
  int height = WID_LEVEL_HEIGHT_CHARS - 1;

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

  std::string fg_tilename;

  if (node->is_lock) {
    fg_tilename = "boss_icon.1";
  }

  if (node->is_ascend_dungeon) {
    fg_tilename = "you_icon";
    wid_set_on_mouse_down(b, wid_choose_initial_dungeons_shortcut_enter);
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

  auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(x, y);
  auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
  if (l) {
    if (! fg_tilename.empty()) {
      wid_set_fg_tilename(b, fg_tilename);
    }

    if (node->is_lock) {
      l->is_boss_level = true;
    }

    if (node->is_descend_dungeon) {
      l->is_final_boss_level = true;
    }

    if (node->is_key) {
      l->is_crystal_level = true;
    }
  }

  char tmp[ MAXSHORTSTR ];
  snprintf(tmp, sizeof(tmp) - 1, "%d", node->walk_order_level_no);
  wid_set_text(b, tmp);
  wid_set_text_lhs(b, true);
  wid_set_text_top(b, true);
}

static void wid_choose_initial_dungeons_update_buttons(Widp w)
{
  TRACE_NO_INDENT();
  wid_choose_initial_dungeons_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (wid_choose_initial_dungeons_ctx *) wid_get_void_context(w);
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
      wid_choose_initial_dungeons_update_button(ctx, b, x, y);
    }
  }
  wid_update(w);
}

static void wid_choose_initial_dungeons_set_focus(wid_choose_initial_dungeons_ctx *ctx, int focusx, int focusy)
{
  TRACE_NO_INDENT();
  ctx->focusx = focusx;
  ctx->focusy = focusy;

  wid_choose_initial_dungeons_update_buttons(ctx->w);
}

static void wid_choose_initial_dungeons_mouse_over(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();
  wid_choose_initial_dungeons_ctx *ctx = (wid_choose_initial_dungeons_ctx *) wid_get_void_context(w);
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

  int focus = wid_get_int_context(w);
  int x     = (focus & 0xff);
  int y     = (focus & 0xff00) >> 8;

  wid_choose_initial_dungeons_set_focus(ctx, x, y);

  auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(x, y);
  auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
  if (l) {
    delete wid_level_description;
    wid_level_description = nullptr;

    point tl = make_point(TERM_WIDTH - UI_WID_POPUP_WIDTH_NORMAL - 1, TERM_HEIGHT - 48);
    point br = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 38);

    char tmp[ MAXSHORTSTR ];
    wid_level_description = new WidPopup("Level stats", tl, br, nullptr, "", false, false);
    wid_level_description->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Level reconn");
    wid_level_description->log(UI_LOGGING_EMPTY_LINE);

    snprintf(tmp, sizeof(tmp) - 1, "Monst HP estimate %u", l->get_total_monst_hp_level());
    wid_level_description->log(tmp, true);
    wid_level_description->log(UI_LOGGING_EMPTY_LINE);

    snprintf(tmp, sizeof(tmp) - 1, "Monst damage est. %u", l->get_total_monst_damage_level());
    wid_level_description->log(tmp, true);
    wid_level_description->log(UI_LOGGING_EMPTY_LINE);

    snprintf(tmp, sizeof(tmp) - 1, "Loot value est.   %u", l->get_total_loot_level());
    wid_level_description->log(tmp, true);
    wid_level_description->log(UI_LOGGING_EMPTY_LINE);

    snprintf(tmp, sizeof(tmp) - 1, "Food HP est.      %u", l->get_total_food_level());
    wid_level_description->log(tmp, true);

    auto        node = ctx->nodes->getn(x, y);
    std::string bg_tilename;
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

    wid_set_color(wid_level_description->wid_popup_container, WID_COLOR_BG, GRAY30);
    wid_set_bg_tilename(wid_level_description->wid_popup_container, bg_tilename);
  }

  IF_DEBUG
  {
    if (l) {
      delete wid_level_contents;
      wid_level_contents = nullptr;

      std::map< std::string, int > monst_contents;
      std::map< std::string, int > treasure_contents;

      for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_WIDTH; y++) {
          FOR_ALL_THINGS_THAT_INTERACT(l, t, x, y)
          {
            if (t->is_monst() || t->is_mob()) {
              monst_contents[ t->short_text_capitalise() ]++;
            }
            if (t->is_treasure()) {
              treasure_contents[ t->short_text_capitalise() ]++;
            }
          }
          FOR_ALL_THINGS_END();
        }
      }

      auto  total_size = monst_contents.size() + treasure_contents.size();
      point tl         = make_point(0, 3);
      point br         = make_point(40, total_size + 6);

      wid_level_contents = new WidPopup("Contents", tl, br, nullptr, "", true, false);
      wid_level_contents->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Contents");
      wid_level_contents->log(UI_LOGGING_EMPTY_LINE);

      char tmp[ MAXSHORTSTR ];
      {
        auto m = flip_map(monst_contents);
        for (auto p = m.rbegin(); p != m.rend(); ++p) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=red$%d %s", p->first, p->second.c_str());
          wid_level_contents->log(tmp, true);
        }
      }
      {
        auto m = flip_map(treasure_contents);
        for (auto p = m.rbegin(); p != m.rend(); ++p) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gold$%d %s", p->first, p->second.c_str());
          wid_level_contents->log(tmp, true);
        }
      }

      wid_set_color(wid_level_contents->wid_popup_container, WID_COLOR_BG, GRAY30);
    }
  }
}

static void wid_choose_initial_dungeons_destroy(Widp w)
{
  TRACE_NO_INDENT();
  wid_choose_initial_dungeons_ctx *ctx;

  if (! w) {
    ctx = g_ctx;
    verify(MTYPE_WID, ctx);
    g_ctx = nullptr;
  } else {
    ctx = (wid_choose_initial_dungeons_ctx *) wid_get_void_context(w);
    verify(MTYPE_WID, ctx);
    wid_set_void_context(w, 0);
  }

  /*
   * Might be in tbe process of destroying.
   */
  if (! ctx->w) {
    return;
  }

  if (ctx) {
    delete ctx;
    oldptr(MTYPE_WID, ctx);
  }
}

static void game_display_grid_bg(void)
{
  TRACE_NO_INDENT();
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "grid";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

static void wid_choose_initial_dungeons_create_level_at(wid_choose_initial_dungeons_ctx *ctx, int x, int y)
{
  TRACE_NO_INDENT();

  auto node     = ctx->nodes->getn(x, y);
  auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(x, y);

  //
  // Create a level of the given difficulty at a fixed location
  //
  if (! game->init_level(level_at, point(x, y), node->depth, node->walk_order_level_no)) {
    ERR("Could not create level");
    return;
  }

  auto l = get(game->world.levels, level_at.x, level_at.y, level_at.z);
  if (! l) {
    return;
  }

  ctx->levels[ y ][ x ] = l;

  if (node->is_ascend_dungeon) {
    game->level         = l;
    game->current_level = level_at;
    l->is_first_level   = true;
  }

  if (node->is_descend_dungeon) {
    l->is_final_level = true;
  }
}

//
// Create the linkages between levels so we know what is closer to the big
// boss level and what is closer to the start. We use this when choosing the
// next or previous level.
//
static void game_join_levels(wid_choose_initial_dungeons_ctx *ctx)
{
  TRACE_NO_INDENT();

  for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
    for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
      Widp b = ctx->buttons[ y ][ x ];
      if (! b) {
        continue;
      }

      auto node = ctx->nodes->getn(x, y);
      if (! node) {
        continue;
      }

      auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(x, y);
      auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
      if (! l) {
        continue;
      }

      //
      // All possible ways levels can connect
      //
      std::vector< point > deltas = {
          point(0, -1),
          point(-1, 0),
          point(1, 0),
          point(0, 1),
      };

      for (auto delta : deltas) {
        if (x + delta.x < 0) {
          continue;
        }
        if (y + delta.y < 0) {
          continue;
        }
        if (x + delta.x >= DUNGEONS_GRID_CHUNK_WIDTH) {
          continue;
        }
        if (y + delta.y >= DUNGEONS_GRID_CHUNK_HEIGHT) {
          continue;
        }
        auto alt = ctx->nodes->getn(x + delta.x, y + delta.y);
        if (! alt) {
          continue;
        }

        Widp b = ctx->buttons[ y + delta.y ][ x + delta.x ];
        if (! b) {
          continue;
        }

        auto alt_at  = l->world_at;
        auto alt_loc = l->world_at + point3d(delta.x, 0, delta.y * 2);
        CON("at %s alt %s del %d,%d %d,%d,%d", l->world_at.to_string().c_str(), alt_at.to_string().c_str(), delta.x,
            delta.y, alt_loc.x, alt_loc.y, alt_loc.z);
        auto alt_l = get(game->world.levels, alt_loc.x, alt_loc.y, alt_loc.z);
        if (! alt_l) {
          l->err("Have node but no level at %d,%d, delta %d,%d", x, y, delta.x, delta.y);
          DIE("Have node but no level at %d,%d, delta %d,%d", x, y, delta.x, delta.y);
        }

        if (alt->walk_order_level_no < node->walk_order_level_no) {
          //
          // Closer to the start
          //
          l->prev_levels.push_back(alt_l->world_at);
        } else if (alt->walk_order_level_no > node->walk_order_level_no) {
          //
          // Closer to the end
          //
          l->next_levels.push_back(alt_l->world_at);
        } else {
          DIE("Levels have the same walk depth");
        }
      }
    }
  }
}

static void wid_choose_initial_dungeons_tick(Widp w)
{
  TRACE_NO_INDENT();
  wid_choose_initial_dungeons_ctx *ctx = (wid_choose_initial_dungeons_ctx *) wid_get_void_context(w);
  verify(MTYPE_WID, ctx);

  game_display_grid_bg();
  wid_set_style(ctx->wid_enter, UI_WID_STYLE_GRAY);

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

  {
    for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
      for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
        Widp b = ctx->buttons[ y ][ x ];
        if (! b) {
          continue;
        }

        auto node = ctx->nodes->getn(x, y);
        if (node->is_ascend_dungeon) {
          color c = GREEN;
          c.g     = val;
          wid_set_color(b, WID_COLOR_BG, c);
          wid_update(b);
        }
      }
    }
  }

  if (! ctx->generated) {
    //
    // For quick start we only create one level
    //
    if (g_opt_quick_start) {
      for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
        for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
          Widp b = ctx->buttons[ y ][ x ];
          if (! b) {
            continue;
          }

          auto node = ctx->nodes->getn(x, y);
          if (! node->is_ascend_dungeon) {
            continue;
          }

          wid_choose_initial_dungeons_create_level_at(ctx, x, y);
          ctx->generating       = true;
          ctx->generating_level = 1;
          ctx->generated        = true;
          wid_choose_initial_dungeons_enter(w, 0, 0, 0);
          return;
        }
      }
    }

    //
    // For normal start, we make one level per tick so that we get to see
    // some visual progress for the user.
    //
    for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
      for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
        Widp b = ctx->buttons[ y ][ x ];
        if (! b) {
          continue;
        }

        //
        // Skip made levels
        //
        if (ctx->levels[ y ][ x ]) {
          continue;
        }

        auto node = ctx->nodes->getn(x, y);
        if (! node) {
          continue;
        }

        if (node->walk_order_level_no == ctx->generating_level) {
          ctx->generating_level++;
          wid_choose_initial_dungeons_create_level_at(ctx, x, y);
          wid_choose_initial_dungeons_update_buttons(ctx->w);

          ctx->generating = true;
          return;
        }
      }
    }

    //
    // Create the linkages between levels so we know what is closer to the big
    // boss level and what is closer to the start. We use this when choosing the
    // next or previous level.
    //
    game_join_levels(ctx);
  }

  {
    color c = GREEN;
    c.g     = val;

    //
    // Tell the user the dungeons are ready!
    //
    auto b = ctx->wid_enter;
    wid_set_text(b, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$E%%fg=" UI_TEXT_COLOR_STR "$nter the Dungeon");
    wid_set_style(b, UI_WID_STYLE_OK);
    wid_set_color(b, WID_COLOR_BG, c);
    wid_set_shape_square(b);
    wid_update(b);
  }

  ctx->generated = true;
}

static void wid_choose_initial_dungeons_post_display_tick(Widp w)
{
  TRACE_NO_INDENT();
  wid_choose_initial_dungeons_ctx *ctx = (wid_choose_initial_dungeons_ctx *) wid_get_void_context(w);
  verify(MTYPE_WID, ctx);

  for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
    for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
      Widp b = ctx->buttons[ y ][ x ];
      if (! b) {
        continue;
      }

      auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(x, y);
      auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
      if (! l) {
        continue;
      }

      int tlx, tly, brx, bry;
      wid_get_tl_x_tl_y_br_x_br_y(b, &tlx, &tly, &brx, &bry);

      l->map_debug_tl.x = tlx;
      l->map_debug_tl.y = tly;
      l->map_debug_br.x = brx;
      l->map_debug_br.y = bry;

      {
        int tlx = l->map_debug_tl.x * game->config.ascii_gl_width;
        int tly = l->map_debug_tl.y * game->config.ascii_gl_height;

        l->map_debug_br.x++;
        l->map_debug_br.y++;

        int brx = l->map_debug_br.x * game->config.ascii_gl_width;
        int bry = l->map_debug_br.y * game->config.ascii_gl_height;

        tlx--;
        tly--;
        brx++;
        bry++;

        glcolor(GRAY50);
        blit_fbo_bind_locked(FBO_WID);
        glDisable(GL_TEXTURE_2D);
        //
        // Avoids missing pixel at the corner
        //
        glLineWidth(2.0);
        gl_blitsquare(tlx, tly, brx, bry);
        glLineWidth(1.0);
        glEnable(GL_TEXTURE_2D);
        blit_fbo_unbind_locked();
      }
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

        auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(x, y);
        auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
        if (! l) {
          continue;
        }

        if (! l->map_debug_valid) {
          l->update_map_debug(x, y);
        }
      }
    }

    //
    // Too much noise
    //
    if (0) {
      gl_enter_2d_mode(game->config.ui_pix_width, game->config.ui_pix_height);
      for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
        for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
          Widp b = ctx->buttons[ y ][ x ];
          if (! b) {
            continue;
          }

          auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(x, y);
          auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
          if (! l) {
            continue;
          }

          int tlx, tly, brx, bry;
          wid_get_tl_x_tl_y_br_x_br_y(b, &tlx, &tly, &brx, &bry);

          l->map_debug_tl.x = tlx;
          l->map_debug_tl.y = tly;
          l->map_debug_br.x = brx;
          l->map_debug_br.y = bry;

          l->map_debug_br.x -= 2;
          l->map_debug_br.y -= 2;

          glcolor(WHITE);
          blit_fbo_bind_locked(FBO_WID);
          l->display_map_debug(x, y);
          blit_fbo_unbind_locked();
        }
      }
    }
  }

  IF_DEBUG
  {
    if ((ctx->focusx != -1) && (ctx->focusx != -1)) {
      auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(ctx->focusx, ctx->focusy);
      auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);

      if (l) {
        if (wid_level_description) {
          int tlx, tly, brx, bry;
          int sz = MAP_WIDTH * 3;
          tlx    = game->config.ui_pix_width - sz;
          tly    = 0;
          brx    = game->config.ui_pix_width;
          bry    = sz;

          gl_enter_2d_mode(game->config.ui_pix_width, game->config.ui_pix_height);
          glcolor(WHITE);
          blit_fbo_bind_locked(FBO_WID);
          l->display_map_debug(ctx->focusx, ctx->focusy, tlx, tly, brx, bry);
          blit_fbo_unbind_locked();
        }
      }
    }
  }
}

static uint8_t wid_choose_initial_dungeons_go_back(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_choose_initial_dungeons_destroy(wid_get_top_parent(w));
  game->fini();
  game->wid_main_menu_select();
  return true;
}

static uint8_t wid_choose_initial_dungeons_random(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();

  wid_choose_initial_dungeons_destroy(wid_get_top_parent(w));
  game->fini();
  g_opt_seed_name = "";
  game->init();
  game->wid_choose_initial_dungeons();

  return true;
}

static uint8_t wid_choose_initial_dungeons_enter(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();

  wid_choose_initial_dungeons_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (wid_choose_initial_dungeons_ctx *) wid_get_void_context(wid_get_top_parent(w));
  }
  verify(MTYPE_WID, ctx);

  if (! ctx) {
    return true;
  }

  if (! ctx->generated) {
    return true;
  }

  wid_choose_initial_dungeons_destroy(wid_get_top_parent(w));

  if (! game) {
    DIE("No game");
  }

  game->start_requested = true;

  return true;
}

static uint8_t wid_choose_initial_dungeons_shortcut_enter(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();

  wid_choose_initial_dungeons_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (wid_choose_initial_dungeons_ctx *) wid_get_void_context(wid_get_top_parent(w));
  }
  verify(MTYPE_WID, ctx);

  if (! ctx) {
    return true;
  }

  if (! ctx->generated) {
    return true;
  }

  wid_choose_initial_dungeons_destroy(wid_get_top_parent(w));

  if (! game) {
    DIE("No game");
  }

  int focus = wid_get_int_context(w);
  int lx    = (focus & 0xff);
  int ly    = (focus & 0xff00) >> 8;

  auto level_at = wid_choose_initial_dungeons_grid_to_level_coord(lx, ly);
  auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
  if (! l) {
    return true;
  }

  game->level           = l;
  game->start_requested = true;

  return true;
}

static uint8_t wid_choose_initial_dungeons_wid_choose_seed(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_choose_initial_dungeons_destroy(wid_get_top_parent(w));
  game->fini();
  game->wid_choose_seed_select();
  return false;
}

static uint8_t wid_choose_initial_dungeons_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        case SDLK_RETURN : wid_choose_initial_dungeons_enter(nullptr, 0, 0, 0); return true;
        default :
          {
            TRACE_NO_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'c' : wid_choose_initial_dungeons_wid_choose_seed(nullptr, 0, 0, 0); return true;
              case 'r' : wid_choose_initial_dungeons_random(nullptr, 0, 0, 0); return true;
              case 'e' : wid_choose_initial_dungeons_enter(nullptr, 0, 0, 0); return true;
              case ' ' :
              case 'n' : wid_choose_initial_dungeons_enter(nullptr, 0, 0, 0); return true;
              case 'b' :
              case 'q' :
              case SDLK_ESCAPE : wid_choose_initial_dungeons_go_back(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_choose_initial_dungeons_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  //
  // So screenshots can work
  //
  return false;
}

static bool are_nodes_directly_connected(DungeonNode *a, DungeonNode *b)
{
  if (a->has_door_down) {
    if ((a->x == b->x) && (a->y + 1 == b->y)) {
      return true;
    }
  }
  if (a->has_door_up) {
    if ((a->x == b->x) && (a->y - 1 == b->y)) {
      return true;
    }
  }
  if (a->has_door_left) {
    if ((a->x - 1 == b->x) && (a->y == b->y)) {
      return true;
    }
  }
  if (a->has_door_right) {
    if ((a->x + 1 == b->x) && (a->y == b->y)) {
      return true;
    }
  }

  return false;
}

void game_grid_node_walk(wid_choose_initial_dungeons_ctx *ctx)
{
  TRACE_NO_INDENT();

  std::list< DungeonNode * > open;
  std::list< DungeonNode * > same_depth_nodes;
  std::list< DungeonNode * > next_depth_nodes;
  int                        walk_order_level_no = 0;

  for (auto y = 0; y < ctx->nodes->grid_height; y++) {
    for (auto x = 0; x < ctx->nodes->grid_width; x++) {
      auto node = ctx->nodes->getn(x, y);
      if (! node) {
        continue;
      }
      if (node->depth <= 0) {
        continue;
      }
      if (node == ctx->start_node) {
        continue;
      }
      open.push_back(node);
    }
  }

  if (open.empty()) {
    DIE("No node candidates to create dungeon grid");
  }

  same_depth_nodes.push_back(ctx->start_node);
  for (;;) {
    DungeonNode *curr_node = {};

    if (same_depth_nodes.empty()) {
      if (next_depth_nodes.empty()) {
        break;
      } else {
        curr_node = next_depth_nodes.front();
        next_depth_nodes.pop_front();
      }
    } else {
      curr_node = same_depth_nodes.front();
      same_depth_nodes.pop_front();
    }

    TRACE_NO_INDENT();

    //
    // First pass look for the closest node in the same depth
    //
    {
    redo:
      for (auto cand : open) {
        if (! are_nodes_directly_connected(curr_node, cand)) {
          continue;
        }
        if (cand->depth == curr_node->depth) {
          same_depth_nodes.push_back(cand);
          open.remove(cand);
          goto redo;
        }
      }
    }

    //
    // Second pass look for the next depth nodes
    //
    {
    redo2:
      for (auto cand : open) {
        if (! are_nodes_directly_connected(curr_node, cand)) {
          continue;
        }
        if (cand->depth == curr_node->depth + 1) {
          same_depth_nodes.push_back(cand);
          open.remove(cand);
          goto redo2;
        }
      }
    }

    if (! curr_node->walk_order_level_no) {
      curr_node->walk_order_level_no = ++walk_order_level_no;
    }

    //
    // If no next then this is the furthest last node
    //
    if (same_depth_nodes.empty() && next_depth_nodes.empty()) {
      ctx->generating_level         = 1;
      ctx->max_generating_level     = walk_order_level_no;
      curr_node->is_descend_dungeon = true;
      break;
    }
  }
}

void Game::wid_choose_initial_dungeons(void)
{
  TRACE_AND_INDENT();

  if (! game) {
    DIE("No game struct");
  }

  pre_init();

  //
  // Create a context to hold button info so we can update it when the focus changes
  //
  wid_choose_initial_dungeons_ctx *ctx = new wid_choose_initial_dungeons_ctx();
  newptr(MTYPE_WID, ctx, "wid level grid ctx");
  g_ctx = ctx;

  ctx->nodes            = new Nodes(DUNGEONS_GRID_CHUNK_WIDTH, DUNGEONS_GRID_CHUNK_WIDTH, false /* not a dungeon */);
  ctx->focusx           = -1;
  ctx->focusy           = -1;
  ctx->generated        = false;
  ctx->generating       = false;
  ctx->generating_level = 1;

  //
  // Find the entry node
  //
  for (auto y = 0; y < ctx->nodes->grid_height; y++) {
    for (auto x = 0; x < ctx->nodes->grid_width; x++) {
      auto node = ctx->nodes->getn(x, y);
      if (node->is_ascend_dungeon) {
        ctx->start_node = node;
      }
      node->is_descend_dungeon = false;
      node->x                  = x;
      node->y                  = y;
    }
  }

  if (! ctx->start_node) {
    DIE("No start dungeon node");
  }

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
    wid_set_on_key_up(window, wid_choose_initial_dungeons_key_up);
    wid_set_on_key_down(window, wid_choose_initial_dungeons_key_down);
  }

  /*
   * Create the title
   */
  {
    Widp w = wid_new_square_button(window, "wid level_grid title");

    point tl = make_point(0, 1);
    point br = make_point(TERM_WIDTH - 1, 1);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "Collect all the crystals. Reach the final level. Confront Zorbash.");
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
    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
  }

  point tl    = make_point(TERM_WIDTH - UI_WID_POPUP_WIDTH_NORMAL - 1, TERM_HEIGHT - 26);
  point br    = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  auto  width = br.x - tl.x - 2;
  int   y_at  = TERM_HEIGHT - 21;
  int   x_at  = TERM_WIDTH - width - 2;

  y_at += 3;
  {
    TRACE_NO_INDENT();
    Widp w = wid_new_square_button(window, "Enter");

    point tl = make_point(x_at, y_at);
    point br = make_point(x_at + width, y_at + 4);

    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_choose_initial_dungeons_enter);
    wid_set_shape_none(w);
    ctx->wid_enter = w;
  }

  y_at += 5;

  {
    TRACE_NO_INDENT();
    auto w = wid_new_square_button(window, "Choose seed");

    point tl = make_point(x_at, y_at);
    point br = make_point(x_at + width, y_at + 2);

    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_choose_initial_dungeons_wid_choose_seed);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$C%%fg=" UI_TEXT_COLOR_STR "$hange seed");
  }

  y_at += 3;
  {
    TRACE_NO_INDENT();
    Widp w = wid_new_square_button(window, "Reroll");

    point tl = make_point(x_at, y_at);
    point br = make_point(x_at + width, y_at + 2);

    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_choose_initial_dungeons_random);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$R%%fg=" UI_TEXT_COLOR_STR "$andom dungeon");
  }

  y_at += 3;
  {
    TRACE_NO_INDENT();
    Widp w = wid_new_square_button(window, "Back");

    point tl = make_point(x_at, y_at);
    point br = make_point(x_at + width, y_at + 2);

    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_choose_initial_dungeons_go_back);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$B%%fg=" UI_TEXT_COLOR_STR "$ack?");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }

  /*
   * Create the button container
   */
  {
    Widp button_container = wid_new_square_button(window, "wid level grid buttons");
    wid_set_shape_none(button_container);
    wid_set_on_tick(button_container, wid_choose_initial_dungeons_tick);
    wid_set_on_tick_post_display(button_container, wid_choose_initial_dungeons_post_display_tick);

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

    tl.y += 5;
    br.y += 5;

    wid_set_pos(button_container, tl, br);
    wid_set_void_context(button_container, ctx);

    int32_t ptl_x;
    int32_t ptl_y;
    int32_t pbr_x;
    int32_t pbr_y;
    wid_get_tl_x_tl_y_br_x_br_y(button_container, &ptl_x, &ptl_y, &pbr_x, &pbr_y);

    game_grid_node_walk(ctx);

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

        wid_set_on_mouse_over_begin(b, wid_choose_initial_dungeons_mouse_over);
        IF_DEBUG { wid_set_on_mouse_down(b, wid_choose_initial_dungeons_shortcut_enter); }
        wid_set_color(b, WID_COLOR_BG, WHITE);
        wid_set_void_context(b, ctx);
        int focus = (y << 8) | x;
        wid_set_int_context(b, focus);

        wid_choose_initial_dungeons_update_button(ctx, b, x, y);

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
        if (node->has_door_down) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += (WID_LEVEL_WIDTH_CHARS / 2) - 1;
          br.x = tl.x;
          tl.y += WID_LEVEL_HEIGHT_CHARS;
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          wid_set_fg2_tilename(b, "ud_icon");
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (node->has_door_left) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x--;
          br.x = tl.x;
          tl.y += (WID_LEVEL_HEIGHT_CHARS / 2);
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          wid_set_fg2_tilename(b, "lr_icon");
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (node->has_door_right) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += WID_LEVEL_WIDTH_CHARS - 1;
          br.x = tl.x;
          tl.y += (WID_LEVEL_HEIGHT_CHARS / 2);
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          wid_set_fg2_tilename(b, "lr_icon");
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }

        if (node->has_door_up) {
          Widp  b = wid_new_square_button(button_container, "wid level grid connector");
          point tl(tl_x, tl_y);
          point br(br_x, br_y);

          tl.x += (WID_LEVEL_WIDTH_CHARS / 2) - 1;
          br.x = tl.x;
          br.y = tl.y;

          wid_set_pos(b, tl, br);
          wid_set_fg2_tilename(b, "ud_icon");
          wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
        }
      }
    }
  }

  {
    int y = TERM_HEIGHT - 36;

    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 4, tl.y);

      wid_set_pos(b, tl, br);
      wid_set_text(b, "Key:");
    }

    y += 1;
    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 1, tl.y + 1);

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_bg_tilename(b, "dungeon_icon.1");

      tl.x += 2;
      br.x = TERM_WIDTH - 5;

      b = wid_new_square_button(window, "wid key text");

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_text(b, "Easy");
    }
    y += 2;
    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 1, tl.y + 1);

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_bg_tilename(b, "dungeon_icon.2");

      tl.x += 2;
      br.x = TERM_WIDTH - 5;

      b = wid_new_square_button(window, "wid key text");

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_text(b, "...");
    }
    y += 2;
    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 1, tl.y + 1);

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_bg_tilename(b, "dungeon_icon.3");

      tl.x += 2;
      br.x = TERM_WIDTH - 5;

      b = wid_new_square_button(window, "wid key text");

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_text(b, "...");
    }
    y += 2;
    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 1, tl.y + 1);

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_bg_tilename(b, "dungeon_icon.4");

      tl.x += 2;
      br.x = TERM_WIDTH - 5;

      b = wid_new_square_button(window, "wid key text");

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_text(b, "...");
    }
    y += 2;
    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 1, tl.y + 1);

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_bg_tilename(b, "dungeon_icon.5");

      tl.x += 2;
      br.x = TERM_WIDTH - 5;

      b = wid_new_square_button(window, "wid key text");

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_text(b, "...");
    }
    y += 2;
    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 1, tl.y + 1);

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_bg_tilename(b, "dungeon_icon.6");

      tl.x += 2;
      br.x = TERM_WIDTH - 5;

      b = wid_new_square_button(window, "wid key text");

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_text(b, "...");
    }
    y += 2;
    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 1, tl.y + 1);

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_bg_tilename(b, "dungeon_icon.7");

      tl.x += 2;
      br.x = TERM_WIDTH - 5;

      b = wid_new_square_button(window, "wid key text");

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_text(b, "...");
    }
    y += 2;
    {
      Widp  b = wid_new_square_button(window, "wid key");
      point tl(TERM_WIDTH - 12, y);
      point br(tl.x + 1, tl.y + 1);

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_bg_tilename(b, "dungeon_icon.8");

      tl.x += 2;
      br.x = TERM_WIDTH - 5;

      b = wid_new_square_button(window, "wid key text");

      wid_set_pos(b, tl, br);
      wid_set_style(b, UI_WID_STYLE_SPARSE_NONE);
      wid_set_text(b, "Hard");
    }
  }

  if (! g_opt_quick_start) {
    wid_choose_initial_dungeons_update_buttons(window);
    wid_set_do_not_lower(window, 1);
    wid_update(window);
    wid_raise(window);
    wid_set_focus(window);
  }

  ctx->created = time_get_time_ms();
}
