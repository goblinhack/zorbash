//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_particle.h"
#include "my_tile.h"
#include "my_point.h"

int Level::particle_box_collision (Particlep p,
                                   fpoint tl,
                                   fpoint br,
                                   fpoint *normal,
                                   fpoint *intersect)
{_
    const fpoint b = (tl + br) / 2;
    const fpoint tr(br.x, tl.y);
    const fpoint bl(tl.x, br.y);
    const auto r = (1.0 / TILE_WIDTH) * PARTICLE_RADIUS;
    const auto c = p->at;

    //
    // Corner collisions, normal is at 45 degrees. Unless there is a wall.
    //
    if (distance(c, tl) < r) {
        if (!level->is_wall(b.x - 1, b.y)) {
            normal->x = c.x - tl.x;
            normal->y = c.y - tl.y;
CON("p %p coll %d p %f,%f b %f,%f .. %f,%f",p,  __LINE__, p->at.x, p->at.y, tl.x, tl.y, br.x, br.y);
            return (true);
        }
    }

    if (distance(c, tr) < r) {
        if (!level->is_wall(b.x + 1, b.y)) {
            normal->x = c.x - tr.x;
            normal->y = c.y - tr.y;
CON("p %p coll %d p %f,%f b %f,%f .. %f,%f",p,  __LINE__, p->at.x, p->at.y, tl.x, tl.y, br.x, br.y);
            return (true);
        }
    }

    if (distance(c, br) < r) {
        if (!level->is_wall(b.x + 1, b.y)) {
            normal->x = c.x - br.x;
            normal->y = c.y - br.y;
CON("p %p coll %d p %f,%f b %f,%f .. %f,%f",p,  __LINE__, p->at.x, p->at.y, tl.x, tl.y, br.x, br.y);
            return (true);
        }
    }

    if (distance(c, bl) < r) {
        if (!level->is_wall(b.x - 1, b.y)) {
            normal->x = c.x - bl.x;
            normal->y = c.y - bl.y;
CON("p %p coll %d p %f,%f b %f,%f .. %f,%f",p,  __LINE__, p->at.x, p->at.y, tl.x, tl.y, br.x, br.y);
            return (true);
        }
    }

    float dist;
    if (distance_to_line(c, tl, tr, &dist, 0)) {
        if (dist < r) {
            goto collided;
        }
    }

    if (distance_to_line(c, tr, br, &dist, 0)) {
        if (dist < r) {
            goto collided;
        }
    }

    if (distance_to_line(c, br, bl, &dist, 0)) {
        if (dist < r) {
            goto collided;
        }
    }

    if (distance_to_line(c, bl, tl, &dist, 0)) {
        if (dist < r) {
            goto collided;
        }
    }

    return (false);

collided:
    fpoint delta;

    if (get_line_intersection(c, b, tl, tr, intersect)) {
        delta.x = tl.x - tr.x;
        delta.y = tl.y - tr.y;
        normal->x = -delta.y;
        normal->y = delta.x;
CON("p %p coll %d p %f,%f b %f,%f .. %f,%f",p,  __LINE__, p->at.x, p->at.y, tl.x, tl.y, br.x, br.y);
        return (true);
    }

    if (get_line_intersection(c, b, tr, br, intersect)) {
        delta.x = tr.x - br.x;
        delta.y = tr.y - br.y;
        normal->x = -delta.y;
        normal->y = delta.x;
CON("p %p coll %d p %f,%f b %f,%f .. %f,%f",p,  __LINE__, p->at.x, p->at.y, tl.x, tl.y, br.x, br.y);
        return (true);
    }

    if (get_line_intersection(c, b, br, bl, intersect)) {
        delta.x = br.x - bl.x;
        delta.y = br.y - bl.y;
        normal->x = -delta.y;
        normal->y = delta.x;
CON("p %p coll %d p %f,%f b %f,%f .. %f,%f",p,  __LINE__, p->at.x, p->at.y, tl.x, tl.y, br.x, br.y);
        return (true);
    }

    if (get_line_intersection(c, b, bl, tl, intersect)) {
        delta.x = bl.x - tl.x;
        delta.y = bl.y - tl.y;
        normal->x = -delta.y;
        normal->y = delta.x;
CON("p %p coll %d p %f,%f b %f,%f .. %f,%f",p,  __LINE__, p->at.x, p->at.y, tl.x, tl.y, br.x, br.y);
        return (true);
    }

    //
    // Particle may be inside box.
    //
    return (false);
}

static spoint point_to_grid (const fpoint &p)
{
    return spoint(p.x * (PARTICLES_WIDTH / MAP_WIDTH),
                  p.y * (PARTICLES_HEIGHT / MAP_HEIGHT));
}

static spoint particle_to_grid (const Particlep p)
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

        s->at = at + fpoint(0, 1); // hack
        s->in_use = true;
        s->is_new = true;
        s->orig_at = at;
        s->force = fpoint(0, 0);
        s->velocity = fpoint(0, 0);

        auto angle = random_range(0, 360) * (1.0 / RAD_360);
        float scale = 0.01;
        sincosf(angle, &s->velocity.x, &s->velocity.y);

        s->velocity.x *= scale;
        s->velocity.y *= scale;

        attach_particle(s);
        break;
    } while (tries--);
}

void Level::free_particle (Particlep p)
{_
    auto idx = p - getptr(all_particles, 0);
    auto s = getptr(all_particles, idx);
    if (!s->in_use) {
        return;
    }
    s->in_use = false;
}

void Level::attach_particle (Particlep p)
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

void Level::detach_particle (Particlep p)
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

void Level::move_particle (Particlep p, fpoint to)
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

                    if (p->is_coll) {
                        glcolorfast(RED);
                    } else {
                        glcolorfast(WHITE);
                    }
                    tile_blit(ptex, tl, br);
                }
            }
        }
    }

    blit_flush();
}

void Level::collision_check_particle (Particlep p)
{
    p->is_coll = false;
    const spoint c((int)p->at.x, (int)p->at.y);
    for (auto x = c.x - 1; x <= c.x + 1; x++) {
        for (auto y = c.y - 1; y <= c.y + 1; y++) {
            if (unlikely(is_oob(x, y))) {
                continue;
            }
            if (level->is_wall(x, y)) {
                fpoint normal;
                fpoint intersect;
                if (particle_box_collision(
                       p,
                       fpoint((float)x - 1.0, (float)y - 1.0),
                       fpoint((float)x + 0.0, (float)y + 0.0),
                       &normal,
                       &intersect)) {
                    p->is_coll = true;
                    return;
                }
            }
        }
    }
}

void Level::tick_particles (void)
{
    auto sop = getptr(all_particles, 1);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
    for (auto p = sop; p <= eop; p++) {
        if (p->in_use) {
            move_particle(p, p->at + p->velocity);
            collision_check_particle(p);
        }
    }
}
