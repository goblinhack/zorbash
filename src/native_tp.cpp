//
// Copyright goblinhack@gmail.com
//
// Native thing template and tile loading, formerly the python `my.tp_load()` / `my.tile()` family.
//

#include "my_native.hpp"

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_thing_template.hpp"
#include "my_unicode.hpp"

namespace my {

Tpp tp_load(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  TRACE_NO_INDENT();
  BIG_LOCK();

  int id;
  tp_get_id(name, &id);
  auto tp = ::tp_load(id, name, text_long_name, text_short_name);

  BIG_UNLOCK();
  return tp;
}

Tpp tp_load(const std::string &name)
{
  return tp_load(name, name, name);
}

Tpp tp_load(const std::string &name, const std::string &text_long_name)
{
  return tp_load(name, text_long_name, text_long_name);
}

static bool tile_dir(Tpp tp, const TileArgs &a, int dir, int level)
{
  const char *tp_name           = tp->name().c_str();
  [[maybe_unused]] int delay_ms = a.delay_ms;
  [[maybe_unused]] int ascii_fg_alpha = a.ascii_fg_alpha;
  [[maybe_unused]] int ascii_bg_alpha = a.ascii_bg_alpha;
  [[maybe_unused]] int frame = a.frame;
  [[maybe_unused]] int is_moving = a.is_moving;
  [[maybe_unused]] int is_jumping = a.is_jumping;
  [[maybe_unused]] int begin_jump = a.begin_jump;
  [[maybe_unused]] int is_outline = a.is_outline;
  [[maybe_unused]] int is_yyy5 = a.is_yyy5;
  [[maybe_unused]] int is_yyy6 = a.is_yyy6;
  [[maybe_unused]] int is_yyy7 = a.is_yyy7;
  [[maybe_unused]] int is_yyy8 = a.is_yyy8;
  [[maybe_unused]] int is_yyy9 = a.is_yyy9;
  [[maybe_unused]] int is_invisible = a.is_invisible;
  [[maybe_unused]] int is_hp_25_percent = a.is_hp_25_percent;
  [[maybe_unused]] int is_hp_50_percent = a.is_hp_50_percent;
  [[maybe_unused]] int is_hp_75_percent = a.is_hp_75_percent;
  [[maybe_unused]] int is_hp_100_percent = a.is_hp_100_percent;
  [[maybe_unused]] int is_in_water = a.is_in_water;
  [[maybe_unused]] int is_sleeping = a.is_sleeping;
  [[maybe_unused]] int is_open = a.is_open;
  [[maybe_unused]] int is_dead = a.is_dead;
  [[maybe_unused]] int is_end_of_anim = a.is_end_of_anim;
  [[maybe_unused]] int is_end_of_ascii_anim = a.is_end_of_ascii_anim;
  [[maybe_unused]] int is_dead_on_end_of_anim = a.is_dead_on_end_of_anim;
  [[maybe_unused]] int is_dead_on_end_of_ascii_anim = a.is_dead_on_end_of_ascii_anim;
  [[maybe_unused]] int is_alive_on_end_of_anim = a.is_alive_on_end_of_anim;
  [[maybe_unused]] int is_alive_on_end_of_ascii_anim = a.is_alive_on_end_of_ascii_anim;
  [[maybe_unused]] int is_resurrecting = a.is_resurrecting;
  [[maybe_unused]] int left  = a.is_dir_left;
  [[maybe_unused]] int right = a.is_dir_right;
  [[maybe_unused]] int up    = a.is_dir_up;
  [[maybe_unused]] int down  = a.is_dir_down;
  [[maybe_unused]] int none  = a.is_dir_none;
  const char *tile_name = a.tile ? a.tile->c_str() : nullptr;
  const char *ascii_fg_char_str = a.ascii_fg_char ? a.ascii_fg_char->c_str() : nullptr;
  const char *ascii_bg_char_str = a.ascii_bg_char ? a.ascii_bg_char->c_str() : nullptr;
  const char *ascii_bg_col_name = a.ascii_bg_col_name ? a.ascii_bg_col_name->c_str() : nullptr;
  const char *ascii_fg_col_name = a.ascii_fg_col_name ? a.ascii_fg_col_name->c_str() : nullptr;

  Tilemap *tiles = nullptr;
  switch (dir) {
    case THING_DIR_NONE : tiles = &tp->tiles; break;
    case THING_DIR_DOWN :
      if (level == 1) {
        tiles = &tp->bot1_tiles;
      } else if (level == 2) {
        tiles = &tp->bot2_tiles;
      } else if (level == 3) {
        tiles = &tp->bot3_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_UP :
      if (level == 1) {
        tiles = &tp->top1_tiles;
      } else if (level == 2) {
        tiles = &tp->top2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_LEFT :
      if (level == 1) {
        tiles = &tp->left1_tiles;
      } else if (level == 2) {
        tiles = &tp->left2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_RIGHT :
      if (level == 1) {
        tiles = &tp->right1_tiles;
      } else if (level == 2) {
        tiles = &tp->right2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_TL :
      if (level == 1) {
        tiles = &tp->tl1_tiles;
      } else if (level == 2) {
        tiles = &tp->tl2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_BL :
      if (level == 1) {
        tiles = &tp->bl1_tiles;
      } else if (level == 2) {
        tiles = &tp->bl2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_TR :
      if (level == 1) {
        tiles = &tp->tr1_tiles;
      } else if (level == 2) {
        tiles = &tp->tr2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_BR :
      if (level == 1) {
        tiles = &tp->br1_tiles;
      } else if (level == 2) {
        tiles = &tp->br2_tiles;
      } else {
        DIE("Bug");
      }
      break;
  }

  if (! tiles) {
    ERR("No tiles for [%s]", tile_name);
    return false;
  }

  {
    if (tile_name && *tile_name) {
      Tilep tile;

      tile = tile_find(std::string(tile_name));
      if (unlikely(! tile)) {
        DIE("%s: Cannot find tile '%s' for tp %s", __FUNCTION__, tile_name, tp_name);
        return false;
      }

      //
      // Copy thie tile and make a unique copy if someone has grabbed it.
      //
      if (tile->in_use) {
        tile = new Tile(tile);
      }

      tile->index = (*tiles).size();
      (*tiles).push_back(tile);
      tile->in_use = true;

      tile->delay_ms  = delay_ms;
      tile->frame     = frame;
      tile->is_moving = is_moving;

      tile->ascii_bg_alpha = ascii_bg_alpha;
      tile->ascii_fg_alpha = ascii_fg_alpha;

      if (ascii_fg_char_str) {
        tile->ascii_set     = true;
        tile->ascii_fg_char = unicode_alias_to_char(ascii_fg_char_str);
      }

      if (ascii_bg_char_str) {
        tile->ascii_set     = true;
        tile->ascii_bg_char = unicode_alias_to_char(ascii_bg_char_str);
      }

      tile->ascii_bg_col_value = COLOR_NONE;
      tile->ascii_fg_col_value = WHITE;

      if (ascii_bg_col_name && *ascii_bg_col_name) {
        tile->ascii_set          = true;
        tile->ascii_bg_col_name  = ascii_bg_col_name;
        tile->ascii_bg_col_value = color_find(ascii_bg_col_name);
      }

      if (ascii_fg_col_name && *ascii_fg_col_name) {
        tile->ascii_set          = true;
        tile->ascii_fg_col_name  = ascii_fg_col_name;
        tile->ascii_fg_col_value = color_find(ascii_fg_col_name);
      }

      tile->is_yyy5                = is_yyy5;
      tile->is_yyy6                = is_yyy6;
      tile->is_yyy7                = is_yyy7;
      tile->is_yyy8                = is_yyy8;
      tile->is_yyy9                = is_yyy9;
      tile->is_invisible           = is_invisible;
      tile->is_hp_25_percent       = is_hp_25_percent;
      tile->is_hp_50_percent       = is_hp_50_percent;
      tile->is_hp_75_percent       = is_hp_75_percent;
      tile->is_hp_100_percent      = is_hp_100_percent;
      tile->is_sleeping            = is_sleeping;
      tile->is_open                = is_open;
      tile->is_dead                = is_dead;
      tile->is_end_of_anim         = is_end_of_anim;
      tile->is_end_of_ascii_anim   = is_end_of_ascii_anim;
      tile->is_dead_on_end_of_anim = is_dead_on_end_of_anim;
      if (is_dead_on_end_of_anim) {
        tp->is_dead_on_end_of_anim_set(true);
      }
      tile->is_dead_on_end_of_ascii_anim = is_dead_on_end_of_ascii_anim;
      if (is_alive_on_end_of_anim) {
        tp->is_alive_on_end_of_anim_set(true);
      }
      tile->is_alive_on_end_of_anim       = is_alive_on_end_of_anim;
      tile->is_alive_on_end_of_ascii_anim = is_alive_on_end_of_ascii_anim;
      tile->is_resurrecting               = is_resurrecting;

      if (tile->is_hp_25_percent || tile->is_hp_50_percent || tile->is_hp_75_percent || tile->is_hp_100_percent) {
        tp->internal_has_hp_anim_set(true);
      }

      if (up) {
        if (left) {
          tile->dir                   = THING_DIR_TL;
          tile->internal_has_dir_anim = true;
        } else if (right) {
          tile->dir                   = THING_DIR_TR;
          tile->internal_has_dir_anim = true;
        } else {
          tile->dir                   = THING_DIR_UP;
          tile->internal_has_dir_anim = true;
        }
      } else if (down) {
        if (left) {
          tile->dir                   = THING_DIR_BL;
          tile->internal_has_dir_anim = true;
        } else if (right) {
          tile->dir                   = THING_DIR_BR;
          tile->internal_has_dir_anim = true;
        } else {
          tile->dir                   = THING_DIR_DOWN;
          tile->internal_has_dir_anim = true;
        }
      } else if (left) {
        tile->dir                   = THING_DIR_LEFT;
        tile->internal_has_dir_anim = true;
      } else if (right) {
        tile->dir                   = THING_DIR_RIGHT;
        tile->internal_has_dir_anim = true;
      } else if (none) {
        tile->dir = THING_DIR_NONE;
      }

      if (tile->internal_has_dir_anim) {
        tp->internal_has_dir_anim_set(true);
      }
    } else {
      (*tiles).push_back(nullptr);
    }
  }


  return true;
}

bool tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_NONE, 1); }
bool top1_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_UP, 1); }
bool bot1_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_DOWN, 1); }
bool left1_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_LEFT, 1); }
bool right1_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_RIGHT, 1); }
bool tl1_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_TL, 1); }
bool tr1_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_TR, 1); }
bool bl1_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_BL, 1); }
bool br1_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_BR, 1); }
bool top2_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_UP, 2); }
bool bot2_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_DOWN, 2); }
bool bot3_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_DOWN, 3); }
bool left2_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_LEFT, 2); }
bool right2_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_RIGHT, 2); }
bool tl2_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_TL, 2); }
bool tr2_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_TR, 2); }
bool bl2_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_BL, 2); }
bool br2_tile(Tpp tp, const TileArgs &args) { TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_BR, 2); }

int pcg_random_inclusive(int lo, int hi)
{
  TRACE_NO_INDENT();
  return pcg_random_range_inclusive(lo, hi);
}

int non_pcg_random_inclusive(int lo, int hi)
{
  TRACE_NO_INDENT();
  return non_pcg_random_range_inclusive(lo, hi);
}

void log(const char *msg)
{
  TRACE_NO_INDENT();
  if (msg) {
    LOG("%s", msg);
  }
}

void topcon(const char *msg)
{
  TRACE_NO_INDENT();
  if (msg) {
    auto b = string_to_wstring(msg);
    ::topcon(b.c_str());
  }
}

void game_set_request_to_update_same_level(void)
{
  TRACE_NO_INDENT();
  if (! game) {
    return;
  }
  game->set_request_to_update_same_level();
}

} // namespace my
