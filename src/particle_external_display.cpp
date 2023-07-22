//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_thing.hpp"

void Level::display_pixelart_external_particles(void)
{
  TRACE_NO_INDENT();

#if 0
  CON("-");
  for (auto p : all_external_particles) {
    CON("all ext p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
  for (auto p : new_external_particles) {
    CON("new ext p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
#endif

  all_external_particles.insert(std::end(all_external_particles), std::begin(new_external_particles),
                                std::end(new_external_particles));
  new_external_particles.clear();

  if (all_external_particles.empty()) { return; }

  //
  // std::remove_if iterates over the whole vector and moves all "selected"
  // entries "to the end". std::erase resizes the container.
  //
  // Future: std::erase_if();
  //
  blit_fbo_bind(FBO_MAP);
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  blit_init();
  auto now = time_game_ms();
  for (auto &p : all_external_particles) {
    //
    // Different curve height for each particle
    //
    if (! p.height) {
      //
      // Make a thing and its items jump the same height.
      //
      p.height = THING_JUMP_HEIGHT;
    }

    float t  = p.ts_stop - p.ts_start;
    float dt = (((float) (now) -p.ts_start)) / t;
    // con("dt %f", dt);

    auto  d = p.stop - p.start;
    point at((d.x * dt) + p.start.x, (d.y * dt) + p.start.y);

    auto sz = p.sz;
    if (sz.w < 0) { sz.w = -sz.w; }
    if (sz.h < 0) { sz.h = -sz.h; }

    point blit_tl(at.x - (sz.w / 2), at.y - (sz.h / 2));
    point blit_br(at.x + (sz.w / 2), at.y + (sz.h / 2));

    int arcing_height = sin(RAD_180 * dt) * ((float) p.height);

    Tpp tpp = {};
    if (p.id.id) {
      auto t = thing_find(p.id);
      if (t) {
        tpp = t->tp();
        if (t->is_thrown_as_a_weapon()) { arcing_height = 0; }
      }
    }

    blit_tl.y -= arcing_height;
    blit_br.y -= arcing_height;

    auto  tile            = p.tile;
    float tile_pix_width  = tile->pix_width;
    float tile_pix_height = tile->pix_height;
    float tilew           = game->config.tile_pix_width;
    float tileh           = game->config.tile_pix_height;
    if (unlikely((tile_pix_width != TILE_WIDTH) || (tile_pix_height != TILE_HEIGHT))) {
      auto xtiles = tile_pix_width / TILE_WIDTH;
      blit_tl.x -= ((xtiles - 1) * tilew) / 2;
      blit_br.x += ((xtiles - 1) * tilew) / 2;

      auto ytiles = tile_pix_height / TILE_HEIGHT;
      blit_tl.y -= ((ytiles - 1) * tileh) / 2;
      blit_br.y += ((ytiles - 1) * tileh) / 2;
    }

    if (unlikely(tpp && tpp->gfx_pixelart_oversized_and_on_floor())) {
      float y_offset = (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) * tileh) / 2.0;
      blit_tl.y -= y_offset;
      blit_br.y -= y_offset;
    }

    blit_tl -= pixel_map_at - p.pixel_map_at;
    blit_br -= pixel_map_at - p.pixel_map_at;

    if (p.hflip) { std::swap(blit_tl.x, blit_br.x); }

    if (! g_opt_ascii) { tile_blit_outline(tile, blit_tl, blit_br, WHITE); }
  }

  blit_flush();

#if 0
  for (auto p : all_external_particles) {
    CON("end ext p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
#endif
}
