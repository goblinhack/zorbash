//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include <map>

Fontp font_pixelart_small;
Fontp font_pixelart_large;
Fontp font_ascii;
Fontp font_ui;

static std::map< std::string, Fontp > fonts;

void font_fini(void) { TRACE_AND_INDENT(); }

static Fontp font_load(std::string name)
{
  TRACE_AND_INDENT();
  auto f = font_find(name);

  if (f) {
    return f;
  }

  if (name == "") {
    ERR("No name for font %s", __FUNCTION__);
    return nullptr;
  }

  f = new Font();

  auto result = fonts.insert(std::make_pair(name, f));

  if (! result.second) {
    ERR("Font insert name [%s] failed", name.c_str());
    return f;
  }

  uint32_t d = 0;
  uint32_t c = FONT_MIN_CHAR;

  while (d < FONT_MAX_CHAR) {
    if (c >= FONT_MAX_CHAR) {
      break;
    }

    f->u_to_c[ c ] = d;
    c++;
    d++;
  }

  return f;
}

Fontp font_find(std::string file)
{
  TRACE_AND_INDENT();
  if (file == "") {
    ERR("No filename given for font find %s", __FUNCTION__);
    return nullptr;
  }

  auto result = fonts.find(file);
  if (result == fonts.end()) {
    return nullptr;
  }

  return (result->second);
}

Tilep Font::unicode_to_tile(int u)
{
  Font *me = this;
  if (unlikely(! me)) {
    DIE("No font");
  }

  if ((u < 0) || (u >= FONT_MAX_CHAR)) {
    if (u == L'?') {
      ERR("unicode char 0x%X/%d -> bad index", u, u);
      return (unicode_to_tile(L'?'));
    } else {
      ERR("unicode char 0x%X/%d -> bad index", u, u);
      return (unicode_to_tile(L'?'));
    }
    return (unicode_to_tile(L'?'));
  }

  auto index = get(this->u_to_c, u);

  if ((index < 0) || (index >= FONT_MAX_CHAR)) {
    if (u == L'?') {
      ERR("unicode char 0x%X/%d -> bad index %d", u, u, index);
      return (unicode_to_tile(L'?'));
    } else {
      ERR("unicode char 0x%X/%d -> bad index %d", u, u, index);
      return (unicode_to_tile(L'?'));
    }
    return (unicode_to_tile(L'?'));
  }

  auto tile = get(this->cache, index);
  if (tile) {
    return tile;
  }

  char tile_name[ 10 ];
  snprintf(tile_name, sizeof(tile_name), "%d.%d", tile_index, index);

  tile = tile_find(tile_name);
  if (unlikely(! tile)) {
    if (u == L'?') {
      ERR("unicode char 0x%X/%d -> not found as tile %s", u, u, tile_name);
      return (unicode_to_tile(L'?'));
    }
    ERR("unicode char 0x%X/%d -> not found as tile %s", u, u, tile_name);
    return (unicode_to_tile(L'?'));
  }

  set(this->cache, index, tile);

  return tile;
}

uint8_t font_init(void)
{
  TRACE_AND_INDENT();

  font_pixelart_small             = font_load("font-pixelart-small");
  font_pixelart_small->tile_index = 1;

  font_pixelart_large             = font_load("font-pixelart-large");
  font_pixelart_large->tile_index = 2;

  font_ascii             = font_load("font-ascii");
  font_ascii->tile_index = 3;

  if (g_opt_ascii) {
    font_ui = font_ascii;
  } else {
    font_ui = font_pixelart_large;
  }

  return true;
}
