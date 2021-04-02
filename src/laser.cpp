//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include "my_sys.h"
#include "my_game.h"
#include "my_laser.h"
#include "my_level.h"
#include "my_tile.h"
#include "my_point.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_random.h"

void Level::new_laser (ThingId id,
                       point start, point stop, isize sz, uint32_t dur,
                       const Tilep tile)
{
    if (id.ok()) {
        auto t = thing_find(id);
        if (t) {
            if (t->has_laser) {
                return;
            }
            t->has_laser = true;
            t->log("new internal laser");
        }
    }

    uint32_t now = time_update_time_milli();
    new_lasers.push_back(Laser(id, start, stop, pixel_map_at,
                               sz, now, now + dur, tile));
}

void Level::display_lasers (void)
{_
#if 0
    CON("-");
    for (auto p : all_lasers) {
        CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
    for (auto p : new_lasers) {
        CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
#endif

    all_lasers.insert(std::end(all_lasers), 
                      std::begin(new_lasers), 
                      std::end(new_lasers));
    new_lasers.clear();

    if (all_lasers.empty()) {
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
    auto e = std::remove_if(all_lasers.begin(),
                            all_lasers.end(),
        [=, this] (Laser &p) {
            //
            // Different curve height for each laser
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
                        t->log("End of jump laser");
                        t->is_jumping = false;
                        t->has_laser = false;
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

            int oy = sin(RAD_180 * dt) * p.height;

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
                // Not sure why but for internal lasers this ends up
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

            tile_blit_outline(tile, blit_tl, blit_br, WHITE);

            return false;
        });
    all_lasers.erase(e, all_lasers.end());

    blit_flush();
}

bool Thing::laser_anim_exists (void)
{_
    return has_laser;
}

void Thing::delete_laser (void)
{_
    auto e = std::remove_if(level->all_lasers.begin(),
                            level->all_lasers.end(),
        [=, this] (Laser &p) { 
            if (p.id == id) {
                log("Remove laser");
                return true;
            } else {
                return false;
            }
        }
    );

    level->all_lasers.erase(e, 
                                        level->all_lasers.end());
    has_laser = false;
}
