//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::blit_wall_cladding(point tl, point br, const ThingTiles *tiles)
{
  TRACE_NO_INDENT();
  float dw = game->config.one_pixel_width * 2;
  float dh = game->config.one_pixel_height * 2;

  int x = (int) curr_at.x;
  int y = (int) curr_at.y;

  if (unlikely(x <= 0) || unlikely(y <= 0) || unlikely(x >= MAP_WIDTH - 1) || unlikely(y >= MAP_HEIGHT - 1)) {
    return;
  }

  if (tiles->top1_tile && ! level->is_wall(x, y - 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.y -= dh;
    br2.y -= dh;
    tile_blit(tiles->top1_tile, tl2, br2);
  }

  if (tiles->bot1_tile && ! level->is_wall(x, y + 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.y += dh;
    br2.y += dh;
    tile_blit(tiles->bot1_tile, tl2, br2);
  }

  if (tiles->left1_tile && ! level->is_wall(x - 1, y)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x -= dw;
    br2.x -= dw;
    tile_blit(tiles->left1_tile, tl2, br2);
  }

  if (tiles->right1_tile && ! level->is_wall(x + 1, y)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x += dw;
    br2.x += dw;
    tile_blit(tiles->right1_tile, tl2, br2);
  }

  //
  // X---
  // |...
  // |...
  //
  if (tiles->tl1_tile && ! level->is_wall(x - 1, y - 1) && ! level->is_wall(x - 1, y) && ! level->is_wall(x, y - 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x -= dw;
    br2.x -= dw;
    tl2.y -= dh;
    br2.y -= dh;
    tile_blit(tiles->tl1_tile, tl2, br2);
  }

  //
  // ---X
  // ...|
  // ...|
  //
  if (tiles->tr1_tile && ! level->is_wall(x + 1, y - 1) && ! level->is_wall(x + 1, y) && ! level->is_wall(x, y - 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x += dw;
    br2.x += dw;
    tl2.y -= dh;
    br2.y -= dh;
    tile_blit(tiles->tr1_tile, tl2, br2);
  }

  //
  // |...
  // |...
  // X---
  //
  if (tiles->bl1_tile && ! level->is_wall(x - 1, y + 1) && ! level->is_wall(x - 1, y) && ! level->is_wall(x, y + 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x -= dw;
    br2.x -= dw;
    tl2.y += dh;
    br2.y += dh;
    tile_blit(tiles->bl1_tile, tl2, br2);
  }

  //
  // ...|
  // ...|
  // ---X
  //
  if (tiles->br1_tile && ! level->is_wall(x + 1, y + 1) && ! level->is_wall(x + 1, y) && ! level->is_wall(x, y + 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x += dw;
    br2.x += dw;
    tl2.y += dh;
    br2.y += dh;
    tile_blit(tiles->br1_tile, tl2, br2);
  }
}

void Thing::blit_wall_shadow(point tl, point br, const ThingTiles *tiles)
{
  TRACE_NO_INDENT();
  float dw = game->config.one_pixel_width * 2;
  float dh = game->config.one_pixel_height * 2;
  float tw = game->config.tile_pix_width;
  float th = game->config.tile_pix_height;

  int x = (int) curr_at.x;
  int y = (int) curr_at.y;

  if (unlikely(x <= 0) || unlikely(y <= 0) || unlikely(x >= MAP_WIDTH - 1) || unlikely(y >= MAP_HEIGHT - 1)) {
    return;
  }

  if (tiles->top2_tile && ! level->is_wall(x, y - 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.y -= dh;
    br2.y -= dh;
    tl2.y -= dh;
    br2.y -= dh;
    tile_blit(tiles->top2_tile, tl2, br2);
  }

  if (tiles->bot2_tile && ! level->is_wall(x, y + 1) && level->is_wall(x - 1, y)) {
    point tl2 = tl;
    point br2 = br;
    tl2.y += th;
    br2.y += th;
    tile_blit(tiles->bot2_tile, tl2, br2);

    //
    // Darker
    //
    if (level->is_chasm(x, y + 1)) {
      tile_blit(tiles->bot2_tile, tl2, br2);
    }
  }

  if (tiles->left2_tile && ! level->is_wall(x - 1, y)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x -= dw;
    br2.x -= dw;
    tile_blit(tiles->left2_tile, tl2, br2);
  }

  if (tiles->right2_tile && ! level->is_wall(x + 1, y) && level->is_wall(x, y - 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x += tw;
    br2.x += tw;
    tile_blit(tiles->right2_tile, tl2, br2);
  }

  //
  // X---
  // |...
  // |...
  //
  if (tiles->tl2_tile && ! level->is_wall(x - 1, y - 1) && ! level->is_wall(x - 1, y) && ! level->is_wall(x, y - 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x -= dw;
    br2.x -= dw;
    tl2.y -= dh;
    br2.y -= dh;
    tile_blit(tiles->tl2_tile, tl2, br2);
  }

  //
  // ---X
  // ...|
  // ...|
  //
  if (tiles->tr2_tile && ! level->is_wall(x + 1, y - 1) && ! level->is_wall(x + 1, y) && ! level->is_wall(x, y - 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.x += tw;
    br2.x += tw;
    tile_blit(tiles->tr2_tile, tl2, br2);
  }

  //
  // |...
  // |...
  // X---
  //
  if (tiles->bl2_tile && ! level->is_wall(x - 1, y + 1) && ! level->is_wall(x - 1, y) && ! level->is_wall(x, y + 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.y += th;
    br2.y += th;
    tile_blit(tiles->bl2_tile, tl2, br2);
  }

  //
  // ...|
  // ...|
  // ---X
  //
  if (tiles->br2_tile && ! level->is_wall(x + 1, y + 1) && ! level->is_wall(x + 1, y) && ! level->is_wall(x, y + 1)) {
    point tl2 = tl;
    point br2 = br;
    tl2.y += th;
    br2.y += th;
    tl2.x += tw;
    br2.x += tw;
    tile_blit(tiles->br2_tile, tl2, br2);
  }
}
