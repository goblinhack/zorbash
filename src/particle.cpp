//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_particle.h"
#include "my_tile.h"
#include "my_point.h"
#include "my_font.h"

static void blit_text (std::string const& text,
                       fpoint& blit_tl, fpoint& blit_br)
{_
    Tilep tile;
    auto text_iter = text.begin();
    color fg = WHITE;

// printf("ascii_putf__ [%S]/%ld scissors x %d y %d scissors %d %d %d %d %d\n", text.c_str(), text.size(), x, y, scissors_tl.x, scissors_tl.y, scissors_br.x, scissors_br.y, scissors_enabled);
    tile = nullptr;

    auto a = gl_last_color.a;
    float w = blit_br.x - blit_tl.x;
    float h = blit_br.y - blit_tl.y;
    float cw = w / 4.0;
    float ch = h / 3.0;
    float l = text.length();

    blit_tl.x -= cw * (l / 2);
    blit_br.x = blit_tl.x + cw;
    blit_br.y = blit_tl.y + ch;

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

        if (unlikely(c == L'%')) {
            if (std::string(text_iter, text_iter + 3) == "fg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());
                int len = 0;
                fg = string2color(tmp, &len);
                text_iter += len + 1;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                auto tp = string2tp(tmp, &len);
                text_iter += len;

                tile = tp_first_tile(tp);
                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                tile = string2tile(tmp, &len);
                text_iter += len;
                continue;
            }
            continue;
        }

        tile = fixed_font->unicode_to_tile(c);

        fg.a = a;
        glcolor(fg);
        tile_blit_outline(tile, blit_tl, blit_br);

        tile = nullptr;
        blit_tl.x += cw;
        blit_br.x += cw;
    }
}
#if 0
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
        return (true);
    }

    if (get_line_intersection(c, b, tr, br, intersect)) {
        delta.x = tr.x - br.x;
        delta.y = tr.y - br.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return (true);
    }

    if (get_line_intersection(c, b, br, bl, intersect)) {
        delta.x = br.x - bl.x;
        delta.y = br.y - bl.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return (true);
    }

    if (get_line_intersection(c, b, bl, tl, intersect)) {
        delta.x = bl.x - tl.x;
        delta.y = bl.y - tl.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return (true);
    }

    //
    // Particle may be inside box.
    //
    return (false);
}
#endif

#if 0
int Level::particle_box_collision (Particlep C,
                                   fpoint tl,
                                   fpoint br,
                                   fpoint *normal_out,
                                   fpoint *penetration_out)
{
    const fpoint B_at = (tl + br) / 2;
    const fpoint B_tr(br.x, tl.y);
    const fpoint B_bl(tl.x, br.y);

    // Vector from A(box) to B(circle)
    fpoint n = C->at - B_at;

    // Closest point on A to center of B(circle)
    fpoint closest = n;

    // Calculate half extents along each axis
    float x_extent = (br.x - tl.x) / 2;
    float y_extent = (br.y - tl.y) / 2;

    // Clamp point to edges of the AABB
    closest.x = std::min(x_extent, std::max(closest.x, -x_extent));
    closest.y = std::min(y_extent, std::max(closest.y, -y_extent));

    bool inside = false;

    // Circle is inside the AABB, so we need to clamp the circle's center
    // to the closest edge
    if (n == closest) {
        inside = true;

CON("inside");
        // Find closest axis
        if (abs(n.x) > abs(n.y)) {
            // Clamp to closest extent
            if(closest.x > 0) {
                closest.x = x_extent;
            } else {
                closest.x = -x_extent;
            }
        } else {
            // y axis is shorter
            // Clamp to closest extent
            if (closest.y > 0) {
                closest.y = y_extent;
            } else {
                closest.y = -y_extent;
            }
        }
    }

    fpoint normal = n - closest;
    float d = normal.length(); d = d * d;
    const float r = (1.0 / TILE_WIDTH) * PARTICLE_RADIUS;

    // Early out of the radius is shorter than distance to closest point and
    // Circle not inside the AABB
    if (d > r * r && !inside) {
        return false;
    }

    // Avoided sqrt until we needed
    d = sqrt(d);

    // Collision normal needs to be flipped to point outside if circle was
    // inside the AABB
    if (inside) {
        *normal_out = n * -1;
        //*penetration_out = r - d;
    } else {
        *normal_out = n;
        //*penetration_out = r - d;
    }

CON("coll");
    return true;
}
#endif

//
// Adapted from
// https://stackoverflow.com/questions/18704999/how-to-fix-circle-and-rectangle-overlap-in-collision-response/18790389#18790389
//
int Level::particle_box_collision (Particlep C,
                                   fpoint tl,
                                   fpoint br,
                                   fpoint *normal,
                                   fpoint *intersection)
{
    //int idx = C - getptr(all_particles, 0);
    const float radius = (1.0 / TILE_WIDTH) * PARTICLE_RADIUS;
    fpoint start = C->prev_at;
    fpoint end = C->at + C->velocity;
    const float L = tl.x;
    const float T = tl.y;
    const float R = br.x;
    const float B = br.y;

    // If the bounding box around the start and end points (+radius on all
    // sides) does not intersect with the rectangle, definitely not an
    // intersection
    if ((std::max(start.x, end.x) + radius < L) ||
        (std::min(start.x, end.x) - radius > R) ||
        (std::max(start.y, end.y) + radius < T) ||
        (std::min(start.y, end.y) - radius > B)) {
        return (false);
    }

    const float dx = end.x - start.x;
    const float dy = end.y - start.y;
    const float invdx = (dx == 0.0f ? 0.0f : 1.0f / dx);
    const float invdy = (dy == 0.0f ? 0.0f : 1.0f / dy);
    float cornerX = std::numeric_limits<float>::max();
    float cornerY = std::numeric_limits<float>::max();

    // Calculate intersection times with each side's plane
    // Check each side's quadrant for single-side intersection
    // Calculate Corner
    /** Left Side **/
    // Does the circle go from the left side to the right side of the rectangle's left?
    if (start.x - radius < L && end.x + radius > L) {
        float ltime = ((L - radius) - start.x) * invdx;
        if (ltime >= 0.0f && ltime <= 1.0f) {
            float ly = dy * ltime + start.y;
            // Does the collisions point lie on the left side?
            if (ly >= T && ly <= B) {
                normal->x = -1;
                normal->y = 0;
                intersection->x = L;
                intersection->y = ly;
                //CON("%d line %d left", idx, __LINE__);
                return (true);
            }
        }
        cornerX = L;
    }

    /** Right Side **/
    // Does the circle go from the right side to the left side of the rectangle's right?
    if (start.x + radius > R && end.x - radius < R ) {
        float rtime = (start.x - (R + radius)) * -invdx;
        if (rtime >= 0.0f && rtime <= 1.0f) {
            float ry = dy * rtime + start.y;
            // Does the collisions point lie on the right side?
            if (ry >= T && ry <= B) {
                normal->x = 1;
                normal->y = 0;
                intersection->x = R;
                intersection->y = ry;
                //CON("%d line %d right", idx, __LINE__);
                return (true);
            }
        }
        cornerX = R;
    }

    /** Top Side **/
    // Does the circle go from the top side to the bottom side of the rectangle's top?
    if (start.y - radius < T && end.y + radius > T) {
        float ttime = ((T - radius) - start.y) * invdy;
        if (ttime >= 0.0f && ttime <= 1.0f) {
            float tx = dx * ttime + start.x;
            // Does the collisions point lie on the top side?
            if (tx >= L && tx <= R) {
                normal->x = 0;
                normal->y = -1;
                intersection->x = tx;
                intersection->y = T;
                //CON("%d line %d top", idx, __LINE__);
                return (true);
            }
        }
        cornerY = T;
    }

    /** Bottom Side **/
    // Does the circle go from the bottom side to the top side of the rectangle's bottom?
    if (start.y + radius > B && end.y - radius < B) {
        float btime = (start.y - (B + radius)) * -invdy;
        if (btime >= 0.0f && btime <= 1.0f) {
            float bx = dx * btime + start.x;
            // Does the collisions point lie on the bottom side?
            if (bx >= L && bx <= R) {
                normal->x = 0;
                normal->y = 1;
                intersection->x = bx;
                intersection->y = B;
                //CON("%d line %d bot", idx, __LINE__);
                return (true);
            }
        }
        cornerY = B;
    }

    if ((cornerX == std::numeric_limits<float>::max()) &&
        (cornerY == std::numeric_limits<float>::max())) {
        //CON("%d line %d no overlap", idx, __LINE__);
        return (false);
    }

    // Account for the times where we don't pass over a side but we do hit
    // it's corner
    if (cornerX != std::numeric_limits<float>::max() &&
        cornerY == std::numeric_limits<float>::max()) {
        cornerY = (dy > 0.0f ? B : T);
    }

    if (cornerY != std::numeric_limits<float>::max() &&
        cornerX == std::numeric_limits<float>::max()) {
        cornerX = (dx > 0.0f ? R : L);
    }

    /* Solve the triangle between the start, corner, and intersection point.
     *
     *           +-----------T-----------+
     *           |                       |
     *          L|                       |R
     *           |                       |
     *           C-----------B-----------+
     *          / \
     *         /   \r     _.-E
     *        /     \ _.-'
     *       /    _.-I
     *      / _.-'
     *     S-'
     *
     * S = start of circle's path
     * E = end of circle's path
     * LTRB = sides of the rectangle
     * I = {ix, iY} = point at which the circle intersects with the rectangle
     * C = corner of intersection (and collision point)
     * C=>I (r) = {nx, ny} = radius and intersection normal
     * S=>C = cornerdist
     * S=>I = intersectionDistance
     * S=>E = lineLength
     * <S = innerAngle
     * <I = angle1
     * <C = angle2
     */

    float inverseRadius = 1.0 / radius;
    float lineLength = sqrt(dx * dx + dy * dy);
    float cornerdx = cornerX - start.x;
    float cornerdy = cornerY - start.y;
    float cornerDistance = sqrt(cornerdx * cornerdx + cornerdy * cornerdy);
    float innerAngle = acos((cornerdx * dx + cornerdy * dy) /
                            (lineLength * cornerDistance));

    // If the circle is too close, no intersection.
    if (cornerDistance < radius) {
        //CON("%d line %d too close", idx, __LINE__);
        C->velocity.x = 0;
        C->velocity.y = 0;
        return (false);
    }

    // If inner angle is zero, it's going to hit the corner straight on.
    if (innerAngle == 0.0f) {
        float time = (float)((cornerDistance - radius) / lineLength);

        // If time is outside the boundaries, return null. This algorithm can
        // return a negative time which indicates a previous intersection, and
        // can also return a time > 1.0f which can predict a corner intersection.
        if (time > 1.0f || time < 0.0f) {
            //CON("%d line %d hit corner straight on", idx, __LINE__);
            normal->x = -C->velocity.x;
            normal->y = -C->velocity.y;
            return (true);
        }

        //float ix = time * dx + start.x;
        //float iy = time * dy + start.y;
        float nx = (float)(cornerdx / cornerDistance);
        float ny = (float)(cornerdy / cornerDistance);

        normal->x = nx;
        normal->y = ny;
        intersection->x = cornerX;
        intersection->y = cornerY;

        //CON("%d line %d hit corner straight on", idx, __LINE__);
        return (true);
    }

    float innerAngleSin = sin(innerAngle);
    float angle1Sin = innerAngleSin * cornerDistance * inverseRadius;

    // The angle is too large, there cannot be an intersection
    if (abs(angle1Sin) > 1.0f) {
        //CON("%d line %d hit corner, angle too large angle1Sin %f", idx, 
        //__LINE__, angle1Sin);
        return (false);
    }

    float angle1 = M_PI - asin(angle1Sin);
    float angle2 = M_PI - innerAngle - angle1;

    float intersectionDistance = radius * sin(angle2) / innerAngleSin;

    // Solve for time
    float time = (float)(intersectionDistance / lineLength);

    // If time is outside the boundaries, return null. This algorithm can
    // return a negative time which indicates a previous intersection, and
    // can also return a time > 1.0f which can predict a corner intersection.
    if (time > 1.0f || time < 0.0f) {
        //CON("%d line %d hit corner future or past", idx, __LINE__);
        return (false);
    }

    // Solve the intersection and normal
    float ix = time * dx + start.x;
    float iy = time * dy + start.y;
    float nx = (float)((ix - cornerX) * inverseRadius);
    float ny = (float)((iy - cornerY) * inverseRadius);

    normal->x = nx;
    normal->y = ny;
    intersection->x = cornerX;
    intersection->y = cornerY;
    //CON("%d line %d hit corner a1 %f a2 %f", idx, __LINE__,
    //    (angle1 / RAD_360) * 360, (angle2 / RAD_360) * 360);
    return (true);
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
        float scale = 0.05;
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
        p->prev_at = p->at;
        p->at = to;
        return;
    }

    detach_particle(p);

    if (unlikely(is_oob(to))) {
        free_particle(p);
        return;
    }

    p->prev_at = p->at;
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

                    if (0) {
                        fpoint a(p->prev_at.x + dx, p->prev_at.y + dy);
                        a.x *= tilew;
                        a.y *= tileh;
                        a.x += tilew / 2;
                        a.y += tileh / 2;

                        fpoint tl(a.x - dpx, a.y - dpy);
                        fpoint br(a.x + dpx, a.y + dpy);

                        glcolorfast(BLUE);
                        tile_blit(ptex, tl, br);
                    }

                    fpoint a(p->at.x + dx, p->at.y + dy);
                    a.x *= tilew;
                    a.y *= tileh;
                    a.x += tilew / 2;
                    a.y += tileh / 2;

                    fpoint tl(a.x - dpx, a.y - dpy);
                    fpoint br(a.x + dpx, a.y + dpy);

                    if (p->is_coll) {
                        glcolorfast(RED);
                    } else {
                        glcolorfast(WHITE);
                    }
                    tile_blit(ptex, tl, br);

                    br.x += (br.x - tl.x) * 1;
                    br.y += (br.y - tl.y) * 0.5;
                    if (0) {
                    blit_text(std::to_string(idx), tl, br);
                    }
                }
            }
        }
    }

    blit_flush();
}

bool Level::collision_check_particle (Particlep p, int16_t x, int16_t y)
{
    fpoint normal;
    fpoint intersect;

    if (!particle_box_collision(p,
                                fpoint((float)x - 0.5, (float)y - 0.5),
                                fpoint((float)x + 0.5, (float)y + 0.5),
                                &normal,
                                &intersect)) {
        return (false);
    }

    fpoint normal_unit = unit(normal);
    fpoint tangent_unit = { -normal_unit.y, normal_unit.x };
    fpoint vA = p->velocity;
    fpoint vB(0, 0);

    float normal_A_len = normal_unit.dot(vA);
    float normal_B_len = normal_unit.dot(vB);

    float tangent_A_len = tangent_unit.dot(vA);

    /*
     * Tangent velocity doesn't change.after collision.
     */
    float tangent_A_velocity = tangent_A_len;

    /*
     * Do one dimensional elastic collision.
     */
    const float mA = 1;
    const float mB = 1000;
    float normal_A_velocity =
        (normal_A_len * (mA - mB) + 2.0 * mB * normal_B_len) / (mA + mB);

    fpoint normal_velocity_A  = normal_unit * normal_A_velocity;
    fpoint tangent_velocity_A = tangent_unit * tangent_A_velocity;

    p->velocity.x = normal_velocity_A.x + tangent_velocity_A.x;
    p->velocity.y = normal_velocity_A.y + tangent_velocity_A.y;

    return (true);
}

void Level::collision_check_particle (Particlep p)
{
    const spoint c((int)p->at.x, (int)p->at.y);
    for (auto x = c.x - 1; x <= c.x + 1; x++) {
        for (auto y = c.y - 1; y <= c.y + 1; y++) {
            if (unlikely(is_oob(x, y))) {
                continue;
            }

            if (!level->is_wall(x, y)) {
                continue;
            }

            if (collision_check_particle(p, x, y)) {
                return;
            }
        }
    }

#if 0
    for (auto x = c.x - 2; x <= c.x + 2; x++) {
        for (auto y = c.y - 2; y <= c.y + 2; y++) {
            if (unlikely(is_oob(x, y))) {
                continue;
            }
            if (level->is_wall(x, y)) {
                fpoint tl((float)x - 0.5, (float)y - 0.5);
                fpoint br((float)x + 0.5, (float)y + 0.5);

                if ((p->at.x >= tl.x) &&
                    (p->at.x <= br.x) &&
                    (p->at.y >= tl.y) &&
                    (p->at.y <= br.y)) {
                    int idx = p - getptr(all_particles, 0);
                    ERR("idx %d", idx);
                    p->is_coll = false;
                    p->velocity.x = 0;
                    p->velocity.y = 0;
                }
            }
        }
    }
#endif
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
