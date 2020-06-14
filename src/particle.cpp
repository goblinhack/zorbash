//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include "my_particle.h"
#include "my_level.h"
#include "my_tile.h"
#include "my_point.h"
#include "my_gl.h"

void Level::new_particle (point start, point stop, size sz, uint32_t dur,
                          const Tilep tile)
{
    uint32_t now = time_update_time_milli();
    all_particles.push_back(Particle(start, stop, sz, now, now + dur, tile));
}

void Level::display_particles (void)
{
    if (all_particles.empty()) {
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
    auto e = std::remove_if(all_particles.begin(), all_particles.end(),
        [=] (Particle &p) {
            float t = p.timestamp_stop - p.timestamp_start;
            float dt = ((float)(now - p.timestamp_start)) / t;
            if (dt > 1) {
                return true;
            }

            auto d = p.stop - p.start;
            point at((d.x * dt) + p.start.x, (d.y * dt) + p.start.y);

            point blit_tl(at.x - (p.sz.w / 2), at.y - (p.sz.h / 2));
            point blit_br(at.x + (p.sz.w / 2), at.y + (p.sz.h / 2));

            int oy = sin(RAD_180 * dt) * 50;
            blit_tl.y -= oy;
            blit_br.y -= oy;

            tile_blit_outline(p.tile, blit_tl, blit_br, WHITE);

            return false;
        });
    all_particles.erase(e, all_particles.end());
    blit_flush();
}
