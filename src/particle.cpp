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

void Level::new_particle (point start, point stop, uint32_t dur,
                          const Tilep tile)
{
CON("new particle ");
    uint32_t now = time_update_time_milli();
    all_particles.push_back(Particle(start, stop, now, now + dur, tile));
}

void Level::display_particles (void)
{
    return;
CON("display particle ");
    if (!all_particles.size()) {
        return;
    }
CON("display particle size %d",(int)all_particles.size());

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
    all_particles.erase(
        std::remove_if(all_particles.begin(), all_particles.end(),
            [=] (Particle &p) {
                float t = p.timestamp_stop - p.timestamp_start;
                float dt = (now - p.timestamp_start) / t;
CON("start %u stop %u", p.timestamp_start, p.timestamp_stop);
CON("dt %f", dt);
                if (dt > 1) {
                    return true;
                }

                auto d = p.stop - p.start;
                point at((d.x * dt) + p.start.x, (d.y * dt) + p.start.y);

                point blit_tl(at.x - (TILE_WIDTH / 2), at.y - (TILE_HEIGHT / 2));
                point blit_br(at.x + (TILE_WIDTH / 2), at.y + (TILE_HEIGHT / 2));

CON("%d %d", at.x, at.y);
                tile_blit(p.tile, blit_tl, blit_br);

                return false;
            }));
    blit_flush();
}
