//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_particle.h"

static spoint point_to_grid (const fpoint &p)
{
    return spoint(p.x / PARTICLES_WIDTH, p.y / PARTICLES_HEIGHT);
}

static spoint particle_to_grid (const Particle *p)
{
    return point_to_grid(p->at);
}

void Level::new_particle (const fpoint &at)
{
    static uint32_t next_idx;
    uint32_t tries = PARTICLE_MAX;
    auto s = getptr(all_particles, next_idx);
    auto eop = getptr(all_particles, PARTICLE_MAX);
    do {
        s++;
        next_idx++;
        if (unlikely(s >= eop)) {
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
        attach_particle(s);
        break;
    } while (tries--);
}

void Level::free_particle (Particle *p)
{
    auto idx = p - getptr(all_particles, 0);
    auto s = getptr(all_particles, idx);
    if (!s->in_use) {
        return;
    }
    s->in_use = false;
}

void Level::attach_particle (const Particle *p)
{
    auto at = particle_to_grid(p);
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_particle_ids_at, at.x, at.y, slot);
        if (!*idp) {
            auto idx = p - getptr(all_particles, 0);
            *idp = idx;
            return;
        }
    }
}

void Level::detach_particle (const Particle *p)
{
    auto at = particle_to_grid(p);
    auto idx = p - getptr(all_particles, 0);
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_particle_ids_at, at.x, at.y, slot);
        if (*idp == idx) {
            *idp = 0;
            return;
        }
    }
}

void Level::move_particle (Particle *p, fpoint to)
{
    auto old_at = particle_to_grid(p);
    auto new_at = point_to_grid(to);
    if (old_at == new_at) {
        p->at = to;
        return;
    }

    detach_particle(p);
    p->at = to;
    attach_particle(p);
}
