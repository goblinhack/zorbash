//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_particle.h"
#include "my_tile.h"

static spoint point_to_grid (const fpoint &p)
{
    return spoint(p.x * (PARTICLES_WIDTH / MAP_WIDTH),
                  p.y * (PARTICLES_HEIGHT / MAP_HEIGHT));
}

static spoint particle_to_grid (const Particle *p)
{
    return point_to_grid(p->at);
}

void Level::new_particle (const fpoint &at)
{_
    static uint32_t next_idx;
    uint32_t tries = PARTICLE_MAX;
    auto s = getptr(all_particles, next_idx);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
    do {
        s++;
        next_idx++;
        if (unlikely(s > eop)) {
            s = getptr(all_particles, 0);
            next_idx = 0;
            continue;
        }

        if (s->in_use) {
            continue;
        }

        s->at = at;
        s->in_use = true;
        s->is_new = true;
        s->orig_at = at;
        s->force = fpoint(0, 0);
        s->velocity = fpoint(0, 0);

        auto angle = random_range(0, 360) * (1.0 / RAD_360);
        float scale = 0.1;
        sincosf(angle, &s->velocity.x, &s->velocity.y);

        s->velocity.x *= scale;
        s->velocity.y *= scale;

        attach_particle(s);
        break;
    } while (tries--);
}

void Level::free_particle (Particle *p)
{_
    auto idx = p - getptr(all_particles, 0);
    auto s = getptr(all_particles, idx);
    if (!s->in_use) {
        return;
    }
    s->in_use = false;
}

void Level::attach_particle (Particle *p)
{_
    if (unlikely(is_oob(p->at))) {
        return;
    }
    auto at = particle_to_grid(p);
    for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
        auto idp = &getref(all_particle_ids_at, at.x, at.y, slot);
        if (!*idp) {
            auto idx = p - getptr(all_particles, 0);
            *idp = idx;
            return;
        }
    }
}

void Level::detach_particle (Particle *p)
{_
    auto at = particle_to_grid(p);
    auto idx = p - getptr(all_particles, 0);
    for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
        auto idp = &getref(all_particle_ids_at, at.x, at.y, slot);
        if (*idp == idx) {
            *idp = 0;
            return;
        }
    }
}

void Level::move_particle (Particle *p, fpoint to)
{_
    auto old_at = particle_to_grid(p);
    auto new_at = point_to_grid(to);
    if (old_at == new_at) {
        p->at = to;
        return;
    }

    detach_particle(p);

    if (unlikely(is_oob(to))) {
        free_particle(p);
        return;
    }

    p->at = to;
    attach_particle(p);
}

void Level::blit_particles (const uint16_t minx, const uint16_t miny,
                            const uint16_t maxx, const uint16_t maxy)
{_
    static auto ptex = tile_find_mand("particle");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const auto p1 = point_to_grid(fpoint(minx, miny));
    const auto p2 = point_to_grid(fpoint(maxx, maxy));

    const float tilew = game->config.tile_pix_width;
    const float tileh = game->config.tile_pix_height;

    blit_init();

    for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
        for (auto y = p1.y; y < p2.y; y++) {
            for (auto x = p1.x; x < p2.x; x++) {
                auto idx = get(all_particle_ids_at, x, y, slot);
                if (idx){
                    auto p = getptr(all_particles, idx);

                    float dx = - level->map_at.x;
                    float dy = - level->map_at.y;

                    float dpx = PARTICLE_RADIUS * game->config.one_pixel_width;
                    float dpy = PARTICLE_RADIUS * game->config.one_pixel_height;

                    fpoint a(p->at.x + dx, p->at.y + dy);
                    a.x *= tilew;
                    a.y *= tileh;

                    a.x += tilew / 2;
                    a.y += tileh;

                    fpoint tl(a.x - dpx, a.y - dpy);
                    fpoint br(a.x + dpx, a.y + dpy);

                    tile_blit(ptex, tl, br);
                }
            }
        }
    }

    blit_flush();
}

void Level::tick_particles (void)
{
    auto sop = getptr(all_particles, 1);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
    for (auto p = sop; p <= eop; p++) {
        if (p->in_use) {
            move_particle(p, p->at + p->velocity);
        }
    }
}
