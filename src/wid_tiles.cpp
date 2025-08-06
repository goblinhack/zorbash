//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_globals_extra.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"
#include "my_wid_tiles.hpp"

static int                                                        wid_tiles_init_done;
static std::map< std::string, std::shared_ptr< class WidTiles > > wid_tiles_all;

uint8_t wid_tiles_init(void)
{
  TRACE_AND_INDENT();
  wid_tiles_init_done = true;

  return true;
}

static void wid_tiles_destroy(wid_tilesp w) { TRACE_AND_INDENT(); }

void wid_tiles_fini(void)
{
  TRACE_AND_INDENT();
  if (wid_tiles_init_done) {
    wid_tiles_init_done = false;

    auto iter = wid_tiles_all.begin();

    while (iter != wid_tiles_all.end()) {
      wid_tiles_destroy(iter->second);
      iter = wid_tiles_all.erase(iter);
    }
  }
}

wid_tilesp wid_tiles_load(std::string name, double scale)
{
  TRACE_AND_INDENT();
  auto t = wid_tiles_find(name);

  if (t) {
    return t;
  }

  if (name == "") {
    DIE("No name for wid_tiles");
    return nullptr;
  }

  t = std::make_shared< class WidTiles >();

  auto result = wid_tiles_all.insert(std::make_pair(name, t));

  if (! result.second) {
    DIE("Wid_tiles insert name [%s] failed", name.c_str());
  }

  char tmp[ 32 ];

  snprintf(tmp, sizeof(tmp) - 1, "%s_tl", name.c_str());
  Tilep tile = tile_find(tmp);
  if (unlikely(! tile)) {
    DIE("Did not find wid %s tile %s", name.c_str(), tmp);
  }

  Texp tex = tile_get_tex(tile);

  double tile_w = tile_get_width(tile);
  double tile_h = tile_get_height(tile);
  double tex_w  = tex_get_width(tex);
  double tex_h  = tex_get_height(tex);

  t->across = tex_w / tile_w;
  t->down   = tex_h / tile_h;
  t->tile_w = tile_w;
  t->tile_h = tile_h;
  t->scale  = scale;

  int i, j, c;

  c = 1;
  for (j = 1; j < t->down - 1; j++) {
    for (i = 1; i < t->across - 1; i++) {
      snprintf(tmp, sizeof(tmp) - 1, "%s_%d", name.c_str(), c);
      Tilep tile = tile_find(tmp);
      if (unlikely(! tile)) {
        DIE("Did not find wid %s tile %s", name.c_str(), tmp);
      }
      set(t->tile, i, j, tile);
      c++;
    }
  }

  c = 1;
  for (i = 1; i < t->across - 1; i++) {
    j = 0;
    snprintf(tmp, sizeof(tmp) - 1, "%s_top%d", name.c_str(), c);
    Tilep tile = tile_find(tmp);
    if (unlikely(! tile)) {
      DIE("Did not find wid %s tile %s", name.c_str(), tmp);
    }

    set(t->tile, i, j, tile);
    c++;
  }

  c = 1;
  for (i = 1; i < t->across - 1; i++) {
    j = t->down - 1;
    ;
    snprintf(tmp, sizeof(tmp) - 1, "%s_bot%d", name.c_str(), c);
    Tilep tile = tile_find(tmp);
    if (unlikely(! tile)) {
      DIE("Did not find wid %s tile %s", name.c_str(), tmp);
    }

    set(t->tile, i, j, tile);
    c++;
  }

  c = 1;
  for (j = 1; j < t->down - 1; j++) {
    i = 0;
    snprintf(tmp, sizeof(tmp) - 1, "%s_left%d", name.c_str(), c);
    Tilep tile = tile_find(tmp);
    if (unlikely(! tile)) {
      DIE("Did not find wid %s tile %s", name.c_str(), tmp);
    }

    set(t->tile, i, j, tile);
    c++;
  }

  c = 1;
  for (j = 1; j < t->down - 1; j++) {
    i = t->across - 1;
    snprintf(tmp, sizeof(tmp) - 1, "%s_right%d", name.c_str(), c);
    Tilep tile = tile_find(tmp);
    if (unlikely(! tile)) {
      DIE("Did not find wid %s tile %s", name.c_str(), tmp);
    }

    set(t->tile, i, j, tile);
    c++;
  }

  i = 0;
  j = 0;
  snprintf(tmp, sizeof(tmp) - 1, "%s_tl", name.c_str());
  tile = tile_find(tmp);
  if (unlikely(! tile)) {
    DIE("Did not find wid %s tile %s", name.c_str(), tmp);
  }

  set(t->tile, i, j, tile);

  i = 0;
  j = t->down - 1;
  snprintf(tmp, sizeof(tmp) - 1, "%s_bl", name.c_str());
  tile = tile_find(tmp);
  if (unlikely(! tile)) {
    DIE("Did not find wid %s tile %s", name.c_str(), tmp);
  }

  set(t->tile, i, j, tile);

  i = t->across - 1;
  j = 0;
  snprintf(tmp, sizeof(tmp) - 1, "%s_tr", name.c_str());
  tile = tile_find(tmp);
  if (unlikely(! tile)) {
    DIE("Did not find wid %s tile %s", name.c_str(), tmp);
  }

  set(t->tile, i, j, tile);

  i = t->across - 1;
  j = t->down - 1;
  snprintf(tmp, sizeof(tmp) - 1, "%s_br", name.c_str());
  tile = tile_find(tmp);
  if (unlikely(! tile)) {
    DIE("Did not find wid %s tile %s", name.c_str(), tmp);
  }

  set(t->tile, i, j, tile);

  return t;
}

wid_tilesp wid_tiles_find(std::string file)
{
  TRACE_AND_INDENT();
  if (file == "") {
    DIE("No filename given for wid_tiles find");
  }

  auto result = wid_tiles_all.find(file);
  if (result == wid_tiles_all.end()) {
    return nullptr;
  }

  return (result->second);
}
