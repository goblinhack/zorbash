//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include <math.h>

#include "my_sys.h"
#include "my_game.h"
#include "my_particle.h"
#include "my_level.h"
#include "my_tile.h"
#include "my_point.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_random.h"

void Level::new_internal_particle (
                          ThingId id,
                          point start, point stop, isize sz, uint32_t dur,
                          const Tilep tile,
                          bool hflip,
                          bool make_visible_at_end)
{_
    if (!tile) {
        err("No particle tile");
        return;
    }

    if (id.ok()) {
        auto t = thing_find(id);
        if (t) {
            if (t->is_being_destroyed) {
                t->log("Do not internal create particle, as being destroyed");
                return;
            }

            if (t->has_internal_particle) {
                return;
            }

            t->log("New internal particle");
            t->has_internal_particle = true;
        }
    }

    uint32_t now = time_update_time_milli();
    new_internal_particles.push_back(Particle(id, start, stop, pixel_map_at,
                                     sz, now, now + dur, tile, hflip,
                                     make_visible_at_end));
}

void Level::new_internal_particle (
                          point start, point stop, isize sz, uint32_t dur,
                          const Tilep tile,
                          bool hflip,
                          bool make_visible_at_end)
{_
    if (!tile) {
        err("No particle tile");
        return;
    }

    uint32_t now = time_update_time_milli();
    new_internal_particles.push_back(Particle(NoThingId, start, stop, pixel_map_at,
                                     sz, now, now + dur, tile, hflip,
                                     make_visible_at_end));
}

void Level::display_internal_particles (void)
{_
#if 0
    CON("-");
    for (auto p : all_internal_particles) {
        CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
    for (auto p : new_internal_particles) {
        CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
#endif

    all_internal_particles.insert(std::end(all_internal_particles), 
                                  std::begin(new_internal_particles), 
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
    auto now = time_update_time_milli();
    auto e = std::remove_if(all_internal_particles.begin(),
                            all_internal_particles.end(),
        [=, this] (Particle &p) {
            //
            // Different curve height for each particle
            //
            if (!p.height) {
                p.height = random_range(30, 50);
            }

            float t = p.timestamp_stop - p.timestamp_start;
            float dt = ((float)(now - p.timestamp_start)) / t;
            if (dt > 1) {
                if (p.id.id) {
                    auto t = thing_find(p.id);
                    if (t) {
                        if (p.make_visible_at_end) {
                            t->visible();
                        }
                        t->log("End of jump particle");
                        t->is_jumping = false;
                        t->has_internal_particle = false;
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

            int oy = sin(RAD_180 * dt) * (float)p.height;

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
            float tile_pix_height = tile->pix_height;
            float tileh = game->config.tile_pix_height;

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
                          point start, point stop, isize sz, uint32_t dur,
                          const Tilep tile, bool hflip,
                          bool make_visible_at_end)
{_
    if (!tile) {
        err("No particle tile");
        return;
    }

    //
    // We hit here for player jumps
    //
    if (id.ok()) {
        auto t = thing_find(id);
        if (t) {
            if (t->is_being_destroyed) {
                t->log("Do not create external particle, as being destroyed");
                return;
            }

            if (t->has_external_particle) {
                return;
            }

            t->log("New external particle");
            t->has_external_particle = true;
        }
    }

    uint32_t now = time_update_time_milli();
    new_external_particles.push_back(Particle(id, start, stop, pixel_map_at,
                                     sz, now, now + dur, tile, hflip,
                                     make_visible_at_end));
}

void Level::new_external_particle (point start, point stop, isize sz, uint32_t dur,
                                   const Tilep tile, bool hflip,
                                   bool make_visible_at_end)
{_
    if (!tile) {
        err("No particle tile");
        return;
    }

    uint32_t now = time_update_time_milli();
    new_external_particles.push_back(Particle(NoThingId, start, stop, pixel_map_at,
                                     sz, now, now + dur, tile, hflip,
                                     make_visible_at_end));
}

void Level::display_external_particles (void)
{_
#if 0
    CON("-");
    for (auto p : all_external_particles) {
        CON("all ext p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
    for (auto p : new_external_particles) {
        CON("new ext p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
#endif

    all_external_particles.insert(std::end(all_external_particles), 
                                  std::begin(new_external_particles), 
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
    auto now = time_update_time_milli();
    auto e = std::remove_if(all_external_particles.begin(),
                            all_external_particles.end(),
        [=, this] (Particle &p) {
            //
            // Different curve height for each particle
            //
            if (!p.height) {
                p.height = random_range(30, 50);

                //
                // Make a thing and its items jump the same height.
                //
                if (p.id.id) {
                    auto t = thing_find(p.id);
                    if (t) {
                        auto owner = t->get_top_owner();
                        if (t->is_player() || (owner && owner->is_player())) {
                            p.height = 40;
                        }
                    }
                }
            }

            float t = p.timestamp_stop - p.timestamp_start;
            float dt = ((float)(now - p.timestamp_start)) / t;
            if (dt > 1) {
                if (p.id.id) {
                    auto t = thing_find(p.id);
                    if (t) {
                        if (p.make_visible_at_end) {
                            if (!t->get_immediate_owner_id().ok()) {
                                t->visible();
                            }
                        }
                        t->jump_end();
                        t->has_external_particle = false;
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

            int oy = sin(RAD_180 * dt) * (float)p.height;

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
{_
    return has_internal_particle || has_external_particle;
}

void Thing::delete_particle (void)
{_
    if (has_internal_particle) {
        log("Delete particle: has internal particle");
        auto e = std::remove_if(level->all_internal_particles.begin(),
                                level->all_internal_particles.end(),
            [=, this] (Particle &p) { 
                if (p.id == id) {
                    log("Remove particle");
                    return true;
                } else {
                    return false;
                }
            }
        );

        if (e == level->all_internal_particles.end()) {
            err("Delete internal particle failed");
        }

        level->all_internal_particles.erase(e, 
                                            level->all_internal_particles.end());
        has_internal_particle = false;
    }

    if (has_external_particle) {
        log("Delete particle: has external particle");
        auto e = std::remove_if(level->all_external_particles.begin(),
                                level->all_external_particles.end(),
            [=, this] (Particle &p) { 
                if (p.id == id) {
                    log("Remove particle");
                    return true;
                } else {
                    return false;
                }
            }
        );

        if (e == level->all_external_particles.end()) {
            err("Delete internal particle failed");
        }

        level->all_external_particles.erase(e, 
                                            level->all_external_particles.end());
        has_external_particle = false;
    }
}
