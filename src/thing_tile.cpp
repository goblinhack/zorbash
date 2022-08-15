//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::tiles_get()
{
  TRACE_AND_INDENT();
  auto n   = (uint32_t) id.id;
  auto tpp = tp();
  auto out = &tiles;

  if (inited_tiles) {
    return;
  }
  inited_tiles = true;

  auto tiles = &tpp->left1_tiles;
  auto tile  = tile_n(tiles, n++);
  if (tile) {
    out->left1_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->left1_tile = 0;
  }

  tiles = &tpp->right1_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->right1_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->right1_tile = 0;
  }

  tiles = &tpp->top1_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->top1_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->top1_tile = 0;
  }

  tiles = &tpp->bot1_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->bot1_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->bot1_tile = 0;
  }

  tiles = &tpp->tl1_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->tl1_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->tl1_tile = 0;
  }

  tiles = &tpp->tr1_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->tr1_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->tr1_tile = 0;
  }

  tiles = &tpp->br1_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->br1_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->br1_tile = 0;
  }

  tiles = &tpp->bl1_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->bl1_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->bl1_tile = 0;
  }

  tiles = &tpp->left2_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->left2_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->left2_tile = 0;
  }

  tiles = &tpp->right2_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->right2_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->right2_tile = 0;
  }

  tiles = &tpp->top2_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->top2_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->top2_tile = 0;
  }

  tiles = &tpp->bot2_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->bot2_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->bot2_tile = 0;
  }

  tiles = &tpp->bot3_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->bot3_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->bot3_tile = 0;
  }

  tiles = &tpp->tl2_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->tl2_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->tl2_tile = 0;
  }

  tiles = &tpp->tr2_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->tr2_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->tr2_tile = 0;
  }

  tiles = &tpp->br2_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->br2_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->br2_tile = 0;
  }

  tiles = &tpp->bl2_tiles;
  tile  = tile_n(tiles, n++);
  if (tile) {
    out->bl2_tile = tile_index_to_tile(tile->global_index)->global_index;
  } else {
    out->bl2_tile = 0;
  }
}

uint8_t tile_is_dir_down(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_DOWN);
}

uint8_t tile_is_dir_up(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_UP);
}

uint8_t tile_is_dir_left(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_LEFT);
}

uint8_t tile_is_dir_right(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_RIGHT);
}

uint8_t tile_is_dir_none(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_NONE);
}

uint8_t tile_is_dir_tl(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_TL);
}

uint8_t tile_is_dir_bl(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_BL);
}

uint8_t tile_is_dir_tr(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_TR);
}

uint8_t tile_is_dir_br(Tilep t)
{
  TRACE_NO_INDENT();
  return (t->dir == THING_DIR_BR);
}
