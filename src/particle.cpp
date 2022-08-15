//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <iterator>
#include <math.h>
#include <vector>

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_particle.hpp"
#include "my_point.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

void Level::new_internal_particle(ThingId id, point start, point stop, isize sz, uint32_t dur, const Tilep tile,
                                  bool hflip, bool make_visible_at_end)
{
  if (g_opt_ascii) {
    return;
  }

  TRACE_NO_INDENT();

  DBG3("Create new internal particle");

  if (unlikely(! tile)) {
    err("No internal particle tile");
    return;
  }

  if (id.ok()) {
    auto t = thing_find(id);
    if (t) {
      if (t->is_being_destroyed) {
        return;
      }

      if (t->has_internal_particle) {
        return;
      }

      IF_DEBUG3
      t->log("New internal particle");
      t->has_internal_particle = true;
    }
  }

  uint32_t now = time_game_ms();
  new_internal_particles.push_back(
      Particle(id, start, stop, pixel_map_at, sz, now, now + dur, tile, hflip, make_visible_at_end));
}

void Level::new_internal_particle(point start, point stop, isize sz, uint32_t dur, const Tilep tile, bool hflip,
                                  bool make_visible_at_end)
{
  if (g_opt_ascii) {
    return;
  }

  TRACE_NO_INDENT();

  DBG3("Create new internal particle");

  if (unlikely(! tile)) {
    err("No internal particle tile");
    return;
  }

  uint32_t now = time_game_ms();
  new_internal_particles.push_back(
      Particle(NoThingId, start, stop, pixel_map_at, sz, now, now + dur, tile, hflip, make_visible_at_end));
}

void Level::display_pixelart_internal_particles(void)
{
  TRACE_NO_INDENT();

#if 0
  CON("-");
  for (auto p : all_internal_particles) {
    CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
  for (auto p : new_internal_particles) {
    CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
#endif

  all_internal_particles.insert(std::end(all_internal_particles), std::begin(new_internal_particles),
                                std::end(new_internal_particles));
  new_internal_particles.clear();

  if (all_internal_particles.empty()) {
    return;
  }

  //
  // std::remove_if iterates over the whole vector and moves all "selected"
  // entries "to the end". std::erase resizes the container.
  //
  // Future: std::erase_if();
  //
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  blit_init();
  auto now = time_game_ms();
  auto e   = std::remove_if(all_internal_particles.begin(), all_internal_particles.end(), [ =, this ](Particle &p) {
    if (p.removed) {
      return true;
    }

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
    if (dt >= 1) {
      if (p.id.id) {
        auto t = thing_find(p.id);
        if (t) {
          if (p.make_visible_at_end) {
            t->visible();
          }
          // t->con("end jump");
          t->is_scheduled_for_jump_end = true;
          t->has_internal_particle     = false;
        }
      }
      return true;
    }

    auto  d = p.stop - p.start;
    point at((d.x * dt) + p.start.x, (d.y * dt) + p.start.y);

    auto sz = p.sz;
    if (sz.w < 0) {
      sz.w = -sz.w;
    }
    if (sz.h < 0) {
      sz.h = -sz.h;
    }

    point blit_tl(at.x - (sz.w / 2), at.y - (sz.h / 2));
    point blit_br(at.x + (sz.w / 2), at.y + (sz.h / 2));

    int oy = sin(RAD_180 * dt) * ((float) p.height);

    blit_tl.y -= oy;
    blit_br.y -= oy;

    Tpp tpp = {};
    if (p.id.id) {
      auto t = thing_find(p.id);
      if (t) {
        tpp = t->tp();
      }
    }

    auto  tile            = p.tile;
    float tile_pix_height = tile->pix_height;
    float tileh           = game->config.tile_pix_height;

#if 0
      {
        //
        // Not sure why but for internal particles this ends up
        // making jumping slimes too large
        //
        float tile_pix_width = tile->pix_width;
        float tilew = game->config.tile_pix_width;
        if (unlikely((tile_pix_width != TILE_WIDTH) ||
               (tile_pix_height != TILE_HEIGHT))) {
          auto xtiles = tile_pix_width / TILE_WIDTH;
          blit_tl.x -= ((xtiles-1) * tilew) / 2;
          blit_br.x += ((xtiles-1) * tilew) / 2;

          auto ytiles = tile_pix_height / TILE_HEIGHT;
          blit_tl.y -= ((ytiles-1) * tileh) / 2;
          blit_br.y += ((ytiles-1) * tileh) / 2;
        }
      }
#endif

    if (unlikely(tpp && tpp->gfx_oversized_and_on_floor())) {
      float y_offset = (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) * tileh) / 2.0;
      blit_tl.y -= y_offset;
      blit_br.y -= y_offset;
    }

    blit_tl -= pixel_map_at - p.pixel_map_at;
    blit_br -= pixel_map_at - p.pixel_map_at;

    if (p.hflip) {
      std::swap(blit_tl.x, blit_br.x);
    }

    if (! g_opt_ascii) {
      tile_blit_outline(tile, blit_tl, blit_br, WHITE);
    }

    return false;
  });
  all_internal_particles.erase(e, all_internal_particles.end());

  blit_flush();
}

void Level::new_external_particle(ThingId id, point start, point stop, isize sz, uint32_t dur, const Tilep tile,
                                  bool hflip, bool make_visible_at_end)
{
  if (g_opt_ascii) {
    return;
  }

  TRACE_NO_INDENT();

  if (unlikely(! tile)) {
    err("No external particle tile");
    return;
  }

  //
  // We hit here for player jumps
  //
  if (id.ok()) {
    auto t = thing_find(id);
    if (t) {
      if (t->is_being_destroyed) {
        return;
      }

      if (t->has_external_particle) {
        return;
      }

      IF_DEBUG3
      t->log("New external particle");
      t->has_external_particle = true;
    }
  }

  uint32_t now = time_game_ms();
  new_external_particles.push_back(
      Particle(id, start, stop, pixel_map_at, sz, now, now + dur, tile, hflip, make_visible_at_end));
}

void Level::new_external_particle(point start, point stop, isize sz, uint32_t dur, const Tilep tile, bool hflip,
                                  bool make_visible_at_end)
{
  if (g_opt_ascii) {
    return;
  }

  TRACE_NO_INDENT();

  DBG3("Create new external particle");

  if (unlikely(! tile)) {
    err("No external particle tile");
    return;
  }

  uint32_t now = time_game_ms();
  new_external_particles.push_back(
      Particle(NoThingId, start, stop, pixel_map_at, sz, now, now + dur, tile, hflip, make_visible_at_end));
}

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

  if (all_external_particles.empty()) {
    return;
  }

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
  auto e   = std::remove_if(all_external_particles.begin(), all_external_particles.end(), [ =, this ](Particle &p) {
    if (p.removed) {
      return true;
    }

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
    if (dt >= 1) {
      if (p.id.id) {
        auto t = thing_find(p.id);
        if (t) {
          if (p.make_visible_at_end) {
            if (! t->immediate_owner_id().ok()) {
              t->visible();
            }
          }
          IF_DEBUG3
          t->log("Particle end");
          // t->con("end jump");
          t->is_scheduled_for_jump_end = true;
          t->has_external_particle     = false;
        }
      }
      return true;
    }

    auto  d = p.stop - p.start;
    point at((d.x * dt) + p.start.x, (d.y * dt) + p.start.y);

    auto sz = p.sz;
    if (sz.w < 0) {
      sz.w = -sz.w;
    }
    if (sz.h < 0) {
      sz.h = -sz.h;
    }

    point blit_tl(at.x - (sz.w / 2), at.y - (sz.h / 2));
    point blit_br(at.x + (sz.w / 2), at.y + (sz.h / 2));

    int oy = sin(RAD_180 * dt) * ((float) p.height);

    blit_tl.y -= oy;
    blit_br.y -= oy;

    Tpp tpp = {};
    if (p.id.id) {
      auto t = thing_find(p.id);
      if (t) {
        tpp = t->tp();
      }
    }

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

    if (unlikely(tpp && tpp->gfx_oversized_and_on_floor())) {
      float y_offset = (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) * tileh) / 2.0;
      blit_tl.y -= y_offset;
      blit_br.y -= y_offset;
    }

    blit_tl -= pixel_map_at - p.pixel_map_at;
    blit_br -= pixel_map_at - p.pixel_map_at;

    if (p.hflip) {
      std::swap(blit_tl.x, blit_br.x);
    }

    if (! g_opt_ascii) {
      tile_blit_outline(tile, blit_tl, blit_br, WHITE);
    }

    return false;
  });
  all_external_particles.erase(e, all_external_particles.end());

  blit_flush();

#if 0
  for (auto p : all_external_particles) {
    CON("end ext p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
#endif
}

bool Thing::particle_anim_exists(void) { return has_internal_particle || has_external_particle; }

void Thing::delete_particle(void)
{
  TRACE_NO_INDENT();

  //
  // Don't remove immediately in case we are walking the particles.
  //
  if (has_internal_particle) {
    dbg3("Delete particle: Has internal particle");
    for (auto &p : level->all_internal_particles) {
      if (p.id == id) {
        dbg3("Remove particle");
        p.id      = NoThingId;
        p.removed = true;
        break;
      }
    }

    has_internal_particle = false;
  }

  if (has_external_particle) {
    dbg3("Delete particle: Has external particle");
    for (auto &p : level->all_external_particles) {
      if (p.id == id) {
        dbg3("Remove particle");
        p.id      = NoThingId;
        p.removed = true;
        break;
      }
    }

    has_external_particle = false;
  }
}
