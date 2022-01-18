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
#include "my_game_dungeons.hpp"
#include "my_gl.hpp"
#include "my_globals_extra.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_time.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"

static uint8_t game_dungeons_enter(Widp w, int32_t x, int32_t y, uint32_t button);

static WidPopup *wid_level_description;
static WidPopup *wid_level_contents;

class game_dungeons_ctx
{
public:
  ~game_dungeons_ctx()
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

static game_dungeons_ctx *g_ctx;

static void game_dungeons_destroy(Widp w);
static void game_dungeons_set_focus(game_dungeons_ctx *ctx, int focusx, int focusy);

#define ROOM_WIDTH_CHARS  7
#define ROOM_HEIGHT_CHARS 7

static point3d game_dungeons_grid_to_level_coord(int x, int y)
{
  point3d level_at;

  level_at.z += y;
  level_at.x += x;
  //
  // Need to account for potential sewer levels
  //
  level_at.z *= 2;
  level_at.z += 1;

  return level_at;
}

static void game_dungeons_update_button(game_dungeons_ctx *ctx, Widp b, int x, int y)
{
  TRACE_NO_INDENT();
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

  auto level_at = game_dungeons_grid_to_level_coord(x, y);
  auto l        = get(game->world.levels, level_at.x, level_at.y, level_at.z);
  if (l) {
    if (! fg_tilename.empty()) {
      wid_set_fg_tilename(b, fg_tilename);
    }
  }

  char tmp[ MAXSHORTSTR ];
  snprintf(tmp, sizeof(tmp) - 1, "%d", node->walk_order);
  wid_set_text(b, tmp);
  wid_set_text_lhs(b, true);
  wid_set_text_top(b, true);
}

static void game_dungeons_update_buttons(Widp w)
{
  TRACE_NO_INDENT();
  game_dungeons_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (game_dungeons_ctx *) wid_get_void_context(w);
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
      game_dungeons_update_button(ctx, b, x, y);
    }
  }
  wid_update(w);
}

static void game_dungeons_event(Widp w, int focusx, int focusy) { TRACE_NO_INDENT(); }

static uint8_t game_dungeons_mouse_event(Widp w, int focusx, int focusy)
{
  TRACE_NO_INDENT();
  game_dungeons_event(w, focusx, focusy);

  return true;
}

static uint8_t game_dungeons_button_mouse_event(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  int focus  = wid_get_int_context(w);
  int focusx = (focus & 0xff);
  int focusy = (focus & 0xff00) >> 8;

  return (game_dungeons_mouse_event(w, focusx, focusy));
}

static void game_dungeons_set_focus(game_dungeons_ctx *ctx, int focusx, int focusy)
{
  TRACE_NO_INDENT();
  ctx->focusx = focusx;
  ctx->focusy = focusy;

  game_dungeons_update_buttons(ctx->w);
}

static void game_dungeons_mouse_over(Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{
  TRACE_NO_INDENT();
  game_dungeons_ctx *ctx = (game_dungeons_ctx *) wid_get_void_context(w);
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

  game_dungeons_set_focus(ctx, x, y);

  auto level_at = game_dungeons_grid_to_level_coord(x, y);
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

      std::map< ThingId, int > contents;
      for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_WIDTH; y++) {
          FOR_ALL_THINGS_THAT_INTERACT(l, t, x, y)
          {
            if (t->is_treasure() || t->is_monst() || t->is_mob_spawner()) {
              contents[ t->id ]++;
            }
          }
          FOR_ALL_THINGS_END();
        }
      }

      point tl = make_point(0, TERM_HEIGHT - (contents.size() + 5));
      point br = make_point(40, TERM_HEIGHT - 1);

      wid_level_contents = new WidPopup("Level contents", tl, br, nullptr, "", true, false);
      wid_level_contents->log("%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Level contents");
      wid_level_contents->log(UI_LOGGING_EMPTY_LINE);

      char tmp[ MAXSHORTSTR ];
      for (auto p : contents) {
        auto t = l->thing_find(p.first);
        if (t->is_monst()) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=red$%d %s", p.second, t->short_text_capitalise().c_str());
        } else {
          continue;
        }
        wid_level_contents->log(tmp, true);
      }
      for (auto p : contents) {
        auto t = l->thing_find(p.first);
        if (t->is_mob_spawner()) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=pink$%d %s", p.second, t->short_text_capitalise().c_str());
        } else {
          continue;
        }
        wid_level_contents->log(tmp, true);
      }
      for (auto p : contents) {
        auto t = l->thing_find(p.first);
        if (t->is_treasure()) {
          snprintf(tmp, sizeof(tmp) - 1, "%%fg=gold$%d %s", p.second, t->short_text_capitalise().c_str());
        } else {
          continue;
        }
        wid_level_contents->log(tmp, true);
      }

      wid_set_color(wid_level_contents->wid_popup_container, WID_COLOR_BG, GRAY30);
    }
  }
}

static void game_dungeons_destroy(Widp w)
{
  TRACE_NO_INDENT();
  game_dungeons_ctx *ctx;

  if (! w) {
    ctx = g_ctx;
    verify(MTYPE_WID, ctx);
    g_ctx = nullptr;
  } else {
    ctx = (game_dungeons_ctx *) wid_get_void_context(w);
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

static void game_dungeons_create_level_at(game_dungeons_ctx *ctx, int x, int y)
{
  TRACE_NO_INDENT();

  auto node     = ctx->nodes->getn(x, y);
  auto level_at = game_dungeons_grid_to_level_coord(x, y);

  //
  // Create a level of the given difficulty at a fixed location
  //
  game->init_level(level_at, node->depth, node->depth);
  auto l = get(game->world.levels, level_at.x, level_at.y, level_at.z);
  if (! l) {
    return;
  }

  CON("final node %p %d at %d,%d", node, node->walk_order, x, y);
  ctx->levels[ y ][ x ] = l;

  if (node->is_ascend_dungeon) {
    game->level         = l;
    game->current_level = level_at;
  }
}

//
// Create the linkages between levels so we know what is closer to the big
// boss level and what is closer to the start. We use this when choosing the
// next or previous level.
//
static void game_join_levels(game_dungeons_ctx *ctx)
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

      auto level_at = game_dungeons_grid_to_level_coord(x, y);
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

        auto alt_at = l->world_at;
        auto offset = game_dungeons_grid_to_level_coord(delta.x, delta.y);
        alt_at.x += offset.x;
        alt_at.z += offset.y;

        auto alt_l = get(game->world.levels, alt_at.x, alt_at.y, alt_at.z);
        if (! alt_l) {
          l->err("Have node but no level at %d,%d, delta %d,%d", x, y, delta.x, delta.y);
          DIE("Have node but no level at %d,%d, delta %d,%d", x, y, delta.x, delta.y);
        }

        if (alt->walk_order < node->walk_order) {
          //
          // Closer to the start
          //
          l->prev_levels.push_back(alt_at);
        } else if (alt->walk_order > node->walk_order) {
          //
          // Closer to the end
          //
          l->next_levels.push_back(alt_at);
        } else {
          DIE("Levels have the same walk depth");
        }
      }
    }
  }
}

static void game_dungeons_tick(Widp w)
{
  TRACE_NO_INDENT();
  game_dungeons_ctx *ctx = (game_dungeons_ctx *) wid_get_void_context(w);
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

          game_dungeons_create_level_at(ctx, x, y);
          ctx->generating       = true;
          ctx->generating_level = 0;
          ctx->generated        = true;
          game_dungeons_enter(w, 0, 0, 0);
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

        if (node->depth == ctx->generating_level) {
          game_dungeons_create_level_at(ctx, x, y);
          game_dungeons_update_buttons(ctx->w);

          ctx->generating = true;
          return;
        }
      }
    }

    //
    // We've ran out of levels at the current depth. Try the next depth.
    //
    ctx->generating_level++;

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

        if (node->depth == ctx->generating_level) {
          game_dungeons_create_level_at(ctx, x, y);
          game_dungeons_update_buttons(ctx->w);

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

static void game_dungeons_post_display_tick(Widp w)
{
  TRACE_NO_INDENT();
  game_dungeons_ctx *ctx = (game_dungeons_ctx *) wid_get_void_context(w);
  verify(MTYPE_WID, ctx);

  for (auto x = 0; x < DUNGEONS_GRID_CHUNK_WIDTH; x++) {
    for (auto y = 0; y < DUNGEONS_GRID_CHUNK_HEIGHT; y++) {
      Widp b = ctx->buttons[ y ][ x ];
      if (! b) {
        continue;
      }

      auto level_at = game_dungeons_grid_to_level_coord(x, y);
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

        auto level_at = game_dungeons_grid_to_level_coord(x, y);
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

          auto level_at = game_dungeons_grid_to_level_coord(x, y);
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
      auto level_at = game_dungeons_grid_to_level_coord(ctx->focusx, ctx->focusy);
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

static uint8_t game_dungeons_go_back(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  game_dungeons_destroy(wid_get_top_parent(w));
  game->fini();
  game->main_menu_select();
  return true;
}

static uint8_t game_dungeons_random(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();

  game_dungeons_destroy(wid_get_top_parent(w));
  game->fini();
  g_opt_seed_name = "";
  game->init();
  game->menu_dungeons_select();

  return true;
}

static uint8_t game_dungeons_enter(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();

  game_dungeons_ctx *ctx;
  if (! w) {
    ctx = g_ctx;
  } else {
    ctx = (game_dungeons_ctx *) wid_get_void_context(wid_get_top_parent(w));
  }
  verify(MTYPE_WID, ctx);

  if (! ctx) {
    return true;
  }

  if (! ctx->generated) {
    return true;
  }

  game_dungeons_destroy(wid_get_top_parent(w));

  if (! game) {
    DIE("No game");
  }

  game->start_requested = true;

  return true;
}

static uint8_t game_dungeons_choose_seed(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_NO_INDENT();
  game_dungeons_destroy(wid_get_top_parent(w));
  game->fini();
  game->choose_seed_select();
  return false;
}

static uint8_t game_dungeons_key_up(Widp w, const struct SDL_Keysym *key)
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
              case 'c' : game_dungeons_choose_seed(nullptr, 0, 0, 0); return true;
              case 'r' : game_dungeons_random(nullptr, 0, 0, 0); return true;
              case 'e' : game_dungeons_enter(nullptr, 0, 0, 0); return true;
              case SDLK_RETURN :
              case ' ' :
              case 'n' : game_dungeons_enter(nullptr, 0, 0, 0); return true;
              case 'b' :
              case 'q' :
              case SDLK_ESCAPE : game_dungeons_go_back(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t game_dungeons_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

void game_grid_node_walk(game_dungeons_ctx *ctx)
{
  TRACE_NO_INDENT();

  static std::list< DungeonNode * > open;
  auto                              curr_node  = ctx->start_node;
  int                               walk_order = 0;

  for (auto y = 0; y < ctx->nodes->grid_height; y++) {
    for (auto x = 0; x < ctx->nodes->grid_width; x++) {
      auto node = ctx->nodes->getn(x, y);
      if (! node) {
        continue;
      }
      if (node->depth <= 0) {
        continue;
      }
      if (node == curr_node) {
        continue;
      }
      open.push_back(node);
    }
  }

  if (open.empty()) {
    DIE("No node candidates to create dungeon grid");
  }

  for (;;) {
    DungeonNode *best = nullptr;
    CON("cands %d walk %d,%d depth %d walk %d", (int) open.size(), curr_node->x, curr_node->y, curr_node->depth,
        walk_order);

    //
    // First pass look for the closest node in the same depth
    //
    for (auto cand : open) {
      CON("cand %d,%d depth %d ", cand->x, cand->y, cand->depth);
      if (cand->depth == curr_node->depth) {
        if (! best) {
          best = cand;
        } else if ((distance(point(curr_node->x, curr_node->y), point(cand->x, cand->y))) <
                   (distance(point(curr_node->x, curr_node->y), point(best->x, best->y)))) {
          best = cand;
        }
      }
    }

    //
    // Second pass look for the closest node in the next depth
    //
    if (! best) {
      for (auto cand : open) {
        if (cand->depth == curr_node->depth + 1) {
          if (! best) {
            best = cand;
          } else if ((distance(point(curr_node->x, curr_node->y), point(cand->x, cand->y))) <
                     (distance(point(curr_node->x, curr_node->y), point(best->x, best->y)))) {
            best = cand;
          }
        }
      }
    }

    curr_node->walk_order = ++walk_order;

    //
    // If no best then this is the furthest last node
    //
    if (! best) {
      ctx->generating_level         = 0;
      ctx->max_generating_level     = walk_order;
      curr_node->is_descend_dungeon = true;
      break;
    }

    if (best->x > curr_node->x) {
      curr_node->dir_right = true;
    }
    if (best->x < curr_node->x) {
      curr_node->dir_left = true;
    }
    if (best->y > curr_node->y) {
      curr_node->dir_down = true;
    }
    if (best->y < curr_node->y) {
      curr_node->dir_up = true;
    }

    std::vector< point > deltas = {
        point(0, -1),
        point(-1, 0),
        point(1, 0),
        point(0, 1),
    };

    auto x = curr_node->x;
    auto y = curr_node->y;

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
      if (! alt->depth) {
        continue;
      }

      if (alt->x > curr_node->x) {
        if (! alt->dir_left) {
          curr_node->dir_right = true;
        }
      }
      if (alt->x < curr_node->x) {
        if (! alt->dir_right) {
          curr_node->dir_left = true;
        }
      }
      if (alt->y > curr_node->y) {
        if (! alt->dir_up) {
          curr_node->dir_down = true;
        }
      }
      if (alt->y < curr_node->y) {
        if (! alt->dir_down) {
          curr_node->dir_up = true;
        }
      }
    }

    open.remove(best);
    curr_node = best;
  }
}

void Game::menu_dungeons_select(void)
{
  TRACE_AND_INDENT();

  if (! game) {
    DIE("No game struct");
  }

  pre_init();

  //
  // Create a context to hold button info so we can update it when the focus changes
  //
  game_dungeons_ctx *ctx = new game_dungeons_ctx();
  newptr(MTYPE_WID, ctx, "wid level grid ctx");
  g_ctx = ctx;

  ctx->nodes            = new Nodes(DUNGEONS_GRID_CHUNK_WIDTH, DUNGEONS_GRID_CHUNK_WIDTH, false /* not a dungeon */);
  ctx->focusx           = -1;
  ctx->focusy           = -1;
  ctx->generated        = false;
  ctx->generating       = false;
  ctx->generating_level = 0;

  //
  // Find the entry node
  //
  for (auto y = 0; y < ctx->nodes->grid_height; y++) {
    for (auto x = 0; x < ctx->nodes->grid_width; x++) {
      auto node = ctx->nodes->getn(x, y);
      if (node->is_ascend_dungeon) {
        ctx->start_node = node;
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
    wid_set_on_key_up(window, game_dungeons_key_up);
    wid_set_on_key_down(window, game_dungeons_key_down);
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
    wid_set_on_mouse_up(w, game_dungeons_enter);
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
    wid_set_on_mouse_up(w, game_dungeons_choose_seed);
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
    wid_set_on_mouse_up(w, game_dungeons_random);
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
    wid_set_on_mouse_up(w, game_dungeons_go_back);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$B%%fg=" UI_TEXT_COLOR_STR "$ack?");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
  }

  /*
   * Create the button container
   */
  {
    Widp button_container = wid_new_square_button(window, "wid level grid buttons");
    wid_set_shape_none(button_container);
    wid_set_on_tick(button_container, game_dungeons_tick);
    wid_set_on_tick_post_display(button_container, game_dungeons_post_display_tick);

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

        wid_set_on_mouse_over_begin(b, game_dungeons_mouse_over);
        wid_set_on_mouse_down(b, game_dungeons_button_mouse_event);
        wid_set_color(b, WID_COLOR_BG, WHITE);
        wid_set_void_context(b, ctx);
        int focus = (y << 8) | x;
        wid_set_int_context(b, focus);

        game_dungeons_update_button(ctx, b, x, y);

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
    game_dungeons_update_buttons(window);
    wid_set_do_not_lower(window, 1);
    wid_update(window);
    wid_raise(window);
    wid_set_focus(window);
  }

  ctx->created = time_get_time_ms();
}
