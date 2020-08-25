//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include "my_particle.h"
#include "my_level.h"
#include "my_tile.h"
#include "my_point.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_game.h"

void Level::new_internal_particle (
                          ThingId id,
                          point start, point stop, size sz, uint32_t dur,
                          const Tilep tile,
                          bool hflip,
                          bool make_visible_at_end)
{
    uint32_t now = time_update_time_milli();
    all_internal_particles.push_back(Particle(id, start, stop, pixel_map_at,
                                     sz, now, now + dur, tile, hflip,
                                     make_visible_at_end));
}

void Level::new_internal_particle (
                          point start, point stop, size sz, uint32_t dur,
                          const Tilep tile,
                          bool hflip,
                          bool make_visible_at_end)
{
    uint32_t now = time_update_time_milli();
    all_internal_particles.push_back(Particle(NoThingId, start, stop, pixel_map_at,
                                     sz, now, now + dur, tile, hflip,
                                     make_visible_at_end));
}

void Level::display_internal_particles (void)
{
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
    auto now = time_update_time_milli();
    auto e = std::remove_if(all_internal_particles.begin(),
                            all_internal_particles.end(),
        [=, this] (Particle &p) {
            float t = p.timestamp_stop - p.timestamp_start;
            float dt = ((float)(now - p.timestamp_start)) / t;
            if (dt > 1) {
                if (p.id.id) {
                    auto t = thing_find(p.id);
                    if (t) {
                        if (p.make_visible_at_end) {
                            t->visible();
                        }
                        t->log("end of jump");
                        t->is_jumping = false;
                    }
                }
                return true;
            }

            auto d = p.stop - p.start;
            point at((d.x * dt) + p.start.x, (d.y * dt) + p.start.y);

            auto sz = p.sz;
            if (sz.w < 0) { sz.w = -sz.w; }
            if (sz.h < 0) { sz.h = -sz.h; }

            point blit_tl(at.x - (sz.w / 2), at.y - (sz.h / 2));
            point blit_br(at.x + (sz.w / 2), at.y + (sz.h / 2));

            int oy = sin(RAD_180 * dt) * 50;
            blit_tl.y -= oy;
            blit_br.y -= oy;

            Tpp tpp = {};
            if (p.id.id) {
                auto t = thing_find(p.id);
                if (t) {
                    tpp = t->tp();
                }
            }

            auto tile = p.tile;
            float tile_pix_width = tile->pix_width;
            float tile_pix_height = tile->pix_height;
            float tilew = game->config.tile_pix_width;
            float tileh = game->config.tile_pix_height;
            if (unlikely((tile_pix_width != TILE_WIDTH) ||
                         (tile_pix_height != TILE_HEIGHT))) {
                auto xtiles = tile_pix_width / TILE_WIDTH;
                blit_tl.x -= ((xtiles-1) * tilew) / 2;
                blit_br.x += ((xtiles-1) * tilew) / 2;

                auto ytiles = tile_pix_height / TILE_HEIGHT;
                blit_tl.y -= ((ytiles-1) * tileh) / 2;
                blit_br.y += ((ytiles-1) * tileh) / 2;
            }

            if (unlikely(tpp &&
                         tpp->gfx_oversized_but_sitting_on_the_ground())) {
                float y_offset =
                    (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) * tileh) / 2.0;
                blit_tl.y -= y_offset;
                blit_br.y -= y_offset;
            }

            blit_tl -= pixel_map_at - p.pixel_map_at;
            blit_br -= pixel_map_at - p.pixel_map_at;

            if (p.hflip) {
                std::swap(blit_tl.x, blit_br.x);
            }

            tile_blit_outline(tile, blit_tl, blit_br, WHITE);

            return false;
        });
    all_internal_particles.erase(e, all_internal_particles.end());
    blit_flush();
}

void Level::new_external_particle (
                          ThingId id,
                          point start, point stop, size sz, uint32_t dur,
                          const Tilep tile, bool hflip,
                          bool make_visible_at_end)
{
    uint32_t now = time_update_time_milli();
    all_external_particles.push_back(Particle(id, start, stop, pixel_map_at,
                                     sz, now, now + dur, tile, hflip,
                                     make_visible_at_end));
}

void Level::new_external_particle (point start, point stop, size sz, uint32_t dur,
                                   const Tilep tile, bool hflip,
                                   bool make_visible_at_end)
{
    uint32_t now = time_update_time_milli();
    all_external_particles.push_back(Particle(NoThingId, start, stop, pixel_map_at,
                                     sz, now, now + dur, tile, hflip,
                                     make_visible_at_end));
}

void Level::display_external_particles (void)
{
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
    auto now = time_update_time_milli();
    auto e = std::remove_if(all_external_particles.begin(),
                            all_external_particles.end(),
        [=, this] (Particle &p) {
            float t = p.timestamp_stop - p.timestamp_start;
            float dt = ((float)(now - p.timestamp_start)) / t;
            if (dt > 1) {
                if (p.id.id) {
                    auto t = thing_find(p.id);
                    if (t) {
                        if (p.make_visible_at_end) {
                            t->visible();
                        }
                        t->jump_end();
                    }
                }
                return true;
            }

            auto d = p.stop - p.start;
            point at((d.x * dt) + p.start.x, (d.y * dt) + p.start.y);

            auto sz = p.sz;
            if (sz.w < 0) { sz.w = -sz.w; }
            if (sz.h < 0) { sz.h = -sz.h; }

            point blit_tl(at.x - (sz.w / 2), at.y - (sz.h / 2));
            point blit_br(at.x + (sz.w / 2), at.y + (sz.h / 2));

            int oy = sin(RAD_180 * dt) * 50;
            blit_tl.y -= oy;
            blit_br.y -= oy;

            Tpp tpp = {};
            if (p.id.id) {
                auto t = thing_find(p.id);
                if (t) {
                    tpp = t->tp();
                }
            }

            auto tile = p.tile;
            float tile_pix_width = tile->pix_width;
            float tile_pix_height = tile->pix_height;
            float tilew = game->config.tile_pix_width;
            float tileh = game->config.tile_pix_height;
            if (unlikely((tile_pix_width != TILE_WIDTH) ||
                         (tile_pix_height != TILE_HEIGHT))) {
                auto xtiles = tile_pix_width / TILE_WIDTH;
                blit_tl.x -= ((xtiles-1) * tilew) / 2;
                blit_br.x += ((xtiles-1) * tilew) / 2;

                auto ytiles = tile_pix_height / TILE_HEIGHT;
                blit_tl.y -= ((ytiles-1) * tileh) / 2;
                blit_br.y += ((ytiles-1) * tileh) / 2;
            }

            if (unlikely(tpp &&
                         tpp->gfx_oversized_but_sitting_on_the_ground())) {
                float y_offset =
                    (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) * tileh) / 2.0;
                blit_tl.y -= y_offset;
                blit_br.y -= y_offset;
            }

            blit_tl -= pixel_map_at - p.pixel_map_at;
            blit_br -= pixel_map_at - p.pixel_map_at;

            if (p.hflip) {
                std::swap(blit_tl.x, blit_br.x);
            }

            tile_blit_outline(tile, blit_tl, blit_br, WHITE);

            return false;
        });
    all_external_particles.erase(e, all_external_particles.end());
    blit_flush();
}

bool Thing::particle_anim_exists (void)
{
    if (!level) {
        return false;
    }

    for (const auto &p : level->all_external_particles) {
        if (p.id.id) {
            auto t = level->thing_find(p.id);
            if ((t == this) || t->get_owner_id() == id) {
                return true;
            }
        }
    }

    for (const auto &p : level->all_internal_particles) {
        if (p.id.id) {
            auto t = level->thing_find(p.id);
            if ((t == this) || t->get_owner_id() == id) {
                return true;
            }
        }
    }
    return false;
}
