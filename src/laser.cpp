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

void Level::new_laser (ThingId id, point start, point stop, uint32_t dur)
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
    new_lasers.push_back(Laser(id, start, stop, pixel_map_at, now, now + dur));
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
            float t = p.timestamp_stop - p.timestamp_start;
            float dt = ((float)(now - p.timestamp_start)) / t;
            if (dt > 1) {
                if (p.id.id) {
                    auto t = thing_find(p.id);
                    if (t) {
                        t->log("End of laser");
                        t->has_laser = false;
                    }
                }
                return true;
            }

            auto start = p.start - p.pixel_map_at;
            auto stop = p.stop - p.pixel_map_at;

            //auto tile = tile_find_mand("cursor_select_path.1");
            auto tile = tile_find_mand("player1.1");
            glBindTexture(GL_TEXTURE_2D, tile->gl_binding());

            auto dist = distance(start, stop);
            auto steps = (int)ceil(dist) / TILE_WIDTH;
            fpoint diff(stop.x - start.x, stop.y - start.y);
            fpoint step = diff / steps;
            auto ang = diff.anglerot() * (360.0 / RAD_360);
            ang += 90;

            fpoint perp = step;
            perp = perp.rotate(90);

            for (int t = 0; t < steps; t++) {
                fpoint mid(start.x + step.x * t, start.y + step.y * t);

    glPushAttrib(GL_ENABLE_BIT); 
    blit_fbo_bind(FBO_MAP_VISIBLE);
    glLineWidth(1.0);

    glDisable(GL_TEXTURE_2D);

    gl_blitline(start.x, start.y, mid.x, mid.y);
    gl_blitline(mid.x, mid.y, mid.x + perp.x, mid.y + perp.y);

    glEnable(GL_TEXTURE_2D);
    glcolor(WHITE);
    glPopAttrib();


#if 0
static bool draw; draw = !draw;
if (draw) {
    glPushAttrib(GL_ENABLE_BIT); 
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo_bind(FBO_MAP_VISIBLE);
    glLineWidth(5.0);

    glDisable(GL_TEXTURE_2D);
    gl_blitline(start.x, 
                start.y, 
                mid.x, 
                mid.y);
    glEnable(GL_TEXTURE_2D);
    glcolor(WHITE);
    glPopAttrib();
}
#endif

            }

#if 0
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
#endif

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

    level->all_lasers.erase(e, level->all_lasers.end());
    has_laser = false;
}
