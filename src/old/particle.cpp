//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


static const float p_radius = 5 * ((1.0 / TILE_WIDTH) * PARTICLE_RADIUS);
static const float viscocity1 = 0.90;
static const float viscocity2 = 0.30;
static const float gravity = 0.006;
static const float rest_density = 6.4;
static const float stiffness = 0.0015;
static const float near_stiffness = 0.26;
static const float damping = 0.2;
static const float delta = 1.0;
static const int near_radius = 2;

static spoint point_to_grid (const fpoint &p)
{
    return spoint(p.x * (PARTICLES_WIDTH / MAP_WIDTH),
                  p.y * (PARTICLES_HEIGHT / MAP_HEIGHT));
}

static spoint particle_to_grid (const Particlep p)
{
    return point_to_grid(p->at);
}

#if 1
static void blit_text (std::string const& text,
                       fpoint& blit_tl, fpoint& blit_br)
{_
    Tilep tile;
    auto text_iter = text.begin();
    color fg = WHITE;

// printf("ascii_putf__ [%S]/%ld scissors x %d y %d scissors %d %d %d %d %d\n", text.c_str(), text.size(), x, y, scissors_tl.x, scissors_tl.y, scissors_br.x, scissors_br.y, scissors_enabled);
    tile = nullptr;

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
#if 0
    int idx = C - getptr(all_particles, 0);
#endif
    const float radius = (1.0 / TILE_WIDTH) * PARTICLE_RADIUS;
    fpoint start = C->old_at;
    fpoint end = C->at;
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
#if 0
                CON("%d line %d left", idx, __LINE__);
#endif
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
#if 0
                CON("%d line %d right", idx, __LINE__);
#endif
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
#if 0
                CON("%d line %d top", idx, __LINE__);
#endif
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
#if 0
                CON("%d line %d bot", idx, __LINE__);
#endif
                return (true);
            }
        }
        cornerY = B;
    }

    if ((cornerX == std::numeric_limits<float>::max()) &&
        (cornerY == std::numeric_limits<float>::max())) {
#if 0
        CON("%d line %d no overlap", idx, __LINE__);
#endif
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
#if 0
        CON("%d line %d too close", idx, __LINE__);
#endif
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
#if 0
            CON("%d line %d hit corner straight on", idx, __LINE__);
#endif
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

#if 0
        CON("%d line %d hit corner straight on", idx, __LINE__);
#endif
        return (true);
    }

    float innerAngleSin = sin(innerAngle);
    float angle1Sin = innerAngleSin * cornerDistance * inverseRadius;

    // The angle is too large, there cannot be an intersection
    if (abs(angle1Sin) > 1.0f) {
#if 0
        CON("%d line %d hit corner, angle too large angle1Sin %f", idx, __LINE__, angle1Sin);
#endif
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
#if 0
        CON("%d line %d hit corner future or past", idx, __LINE__);
#endif
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
#if 0
    CON("%d line %d hit corner a1 %f a2 %f", idx, __LINE__, (angle1 / RAD_360) * 360, (angle2 / RAD_360) * 360);
#endif
    return (true);
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
        s->old_at = at;
        s->force = fpoint(0, 0);
        s->velocity = fpoint(0, 0);
        s->density = 0;
        s->near_density = 0;

        auto angle = random_range(0, 360) * (1.0 / RAD_360);
        float scale = 0.05;
        sincosf(angle, &s->force.x, &s->force.y);

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
    ERR("out of slots");
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
        //p->old_at = p->at;
        p->at = to;
        return;
    }

    detach_particle(p);
    if (unlikely(is_oob(to))) {
        free_particle(p);
        return;
    }

    //p->old_at = p->at;
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
#if 0
                    if (0) {
                        fpoint a(p->prev_at.x + dx, p->prev_at.y + dy);
                        a.x *= tilew;
                        a.y *= tileh;
                        a.x += tilew / 2;
                        a.y += tileh / 2;

                        fpoint tl(a.x - dpx, a.y - dpy);
                        fpoint br(a.x + dpx, a.y + dpy);

                        glcolor(BLUE);
                        tile_blit(ptex, tl, br);
                    }
#endif
                    fpoint a(p->at.x + dx, p->at.y + dy);
                    a.x *= tilew;
                    a.y *= tileh;
                    a.x += tilew / 2;
                    a.y += tileh / 2;

                    fpoint tl(a.x - dpx, a.y - dpy);
                    fpoint br(a.x + dpx, a.y + dpy);
#if 0
                    if (p->is_coll) {
                        glcolor(RED);
                    } else {
                        glcolor(WHITE);
                    }
#endif
                    tile_blit(ptex, tl, br);

#if 1
                    if (0) {
                        br.x += (br.x - tl.x) * 0.5;
                        br.y += (br.y - tl.y) * 0.5;
                        blit_text(std::to_string(idx), tl, br);
                    }
#endif
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

    move_particle(p, p->old_at);
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
    p->velocity.x *= damping;
    p->velocity.y *= damping;

    return (true);
}

bool Level::collision_check_particle (Particlep p)
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
                return (true);
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
    return (false);
}

void Level::apply_particle_forces (void)
{
    auto sop = getptr(all_particles, 1);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        p->old_at = p->at;
        move_particle(p, p->at + p->force);

        p->force = fpoint(0, 0);
        p->near_density = 0.0;
        p->density = 0.0;

        if (!p->is_new) {
//            p->velocity = p->at - p->old_at;
        }

        p->is_new = false;

        // apply gravity.
        p->velocity.y += gravity;

        //
        // do viscosity impules to modify velocity(algorithm 5 from the paper)
        //
        auto sp = particle_to_grid(p);
        if (unlikely((sp.x <= 1) || (sp.x >= PARTICLES_WIDTH - 1) ||
                     (sp.y <= 1) || (sp.y >= PARTICLES_HEIGHT - 1))) {
            detach_particle(p);
            free_particle(p);
            continue;
        }

        //
        // For all nearby particles
        //
        auto pidx = p - getptr(all_particles, 0);
        for (auto ox = sp.x - near_radius; ox <= sp.x + near_radius; ox++) {
            for (auto oy = sp.y - near_radius; oy <= sp.y + near_radius; oy++) {
                for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
                    auto qidx = get(all_particle_ids_at, ox, oy, slot);
                    if (likely(!qidx)) { // ignore empty cells
                        continue;
                    }

                    if (unlikely(qidx == pidx)) { // ignore our own particle
                        continue;
                    }

                    auto q = getptr(all_particles, qidx);
                    if (!q->in_use) { // remove this
                        continue;
                    }

                    auto dp = p->at - q->at;
                    auto r2 = dp.dot(dp);
                    if (r2 <= 0.0 || r2 > p_radius * p_radius) {
                        continue;
                    }

                    auto r = sqrt(r2);
                    fpoint normalized_r = dp * (1.0 / r);
                    float one_minus_q = 1 - r / p_radius;

                    fpoint vi_minus_vj = p->velocity - q->velocity;
                    float u = vi_minus_vj.dot(normalized_r);
                    float T = 0;
                    if (u > 0) {
                        T = delta * one_minus_q * (viscocity1 * u + viscocity2 * u * u) * 0.5;
                        if (T < u) {
                            // T = T;
                        } else {
                            T = u;
                        }
                    } else {
                        T = delta * one_minus_q * (viscocity1 * u - viscocity2 * u * u) * 0.5;
                        if (T > u) {
                            // T = T;
                        } else {
                            T = u;
                        }
                    }

                    fpoint I_div2 = normalized_r * T;

                    p->velocity += I_div2 * -1.0;
                    q->velocity += I_div2 * +1.0;
                }
            }
        }
    }
}

void Level::apply_particle_velocity (void)
{
    auto sop = getptr(all_particles, 1);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        // save the original particle position, then apply velocity.
        // p->old_at = p->at;
        move_particle(p, p->at + p->velocity);
#if 0
CON("%f %f   v %f %f", p->at.x,p->at.y, p->velocity.x, p->velocity.y);
#endif
    }

    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }
        auto sp = particle_to_grid(p);
        auto pidx = p - getptr(all_particles, 0);
        for (auto ox = sp.x - near_radius; ox <= sp.x + near_radius; ox++) {
            for (auto oy = sp.y - near_radius; oy <= sp.y + near_radius; oy++) {
                for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
                    auto qidx = get(all_particle_ids_at, ox, oy, slot);
                    if (likely(!qidx)) { // ignore empty cells
                        continue;
                    }

                    if (unlikely(qidx == pidx)) { // ignore our own particle
                        continue;
                    }

                    auto q = getptr(all_particles, qidx);
                    if (!q->in_use) { // remove this
                        continue;
                    }

                    auto dp = p->at - q->at;
                    auto r2 = dp.dot(dp);
                    if (r2 <= 0.0 || r2 > p_radius * p_radius) {
                        continue;
                    }

                    float r = sqrt(r2);
                    float a = 1 - r / p_radius;
                    float aa = a * a;
                    float aaa = aa * a;

                    p->density += aa;
                    q->density += aa;

                    p->near_density += aaa;
                    q->near_density += aaa;
#if 0
                    if (p->density > 10) {
                        detach_particle(p);
                        free_particle(p);
                    }
#endif
                }
            }
        }

        if (collision_check_particle(p)) {
        }
    }
}

void Level::apply_density_relaxation (void)
{
    auto sop = getptr(all_particles, 1);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
#if 0
    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }
        auto pidx = p - getptr(all_particles, 0);
        CON("before %d at %f,%f force %f,%f v %f,%f", (int)pidx, p->at.x, p->at.y, p->force.x, p->force.y, p->velocity.x, p->velocity.y);
    }
#endif
    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        p->nebs = 0;
        float pressure = stiffness * (p->density - rest_density);
        float near_pressure = near_stiffness * p->near_density;

        auto sp = particle_to_grid(p);
        auto pidx = p - getptr(all_particles, 0);
#if 0
CON("p %d dens %f ndens %f", (int)pidx, p->density, p->near_density);
#endif
        for (auto ox = sp.x - near_radius; ox <= sp.x + near_radius; ox++) {
            for (auto oy = sp.y - near_radius; oy <= sp.y + near_radius; oy++) {
                for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
                    auto qidx = get(all_particle_ids_at, ox, oy, slot);
                    if (likely(!qidx)) { // ignore empty cells
                        continue;
                    }

                    if (unlikely(qidx == pidx)) { // ignore our own particle
                        continue;
                    }

                    auto q = getptr(all_particles, qidx);
                    if (!q->in_use) { // remove this
                        continue;
                    }

                    auto dp = p->at - q->at;
                    auto r2 = dp.dot(dp);
                    if (r2 <= 0.0 || r2 > p_radius * p_radius) {
                        continue;
                    }

                    float r = sqrt(r2);
                    float a = 1 - r / p_radius;

                    float D = delta * delta * (pressure * a + near_pressure * a * a) * 0.05;
                    fpoint DA = dp * (D / r);
#if 0
CON("  q %d r %f DA %f %f", (int)qidx, r, DA.x,DA.y);
#endif
                    p->force += DA;

                    q->force -= DA;
                    p->nebs ++;

                    float m = 0.1;
                    if (p->force.x > m) { p->force.x = m; }
                    if (p->force.x < -m) { p->force.x = -m; }
                    if (p->force.y > m) { p->force.y = m; }
                    if (p->force.y < -m) { p->force.y = -m; }
                    if (q->force.x > m) { q->force.x = m; }
                    if (q->force.x < -m) { q->force.x = -m; }
                    if (q->force.y > m) { q->force.y = m; }
                    if (q->force.y < -m) { q->force.y = -m; }
                }
            }
        }
    }
#if 0
    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }
        auto pidx = p - getptr(all_particles, 0);
        CON("after %d nebs %d at %f,%f force %f,%f v %f,%f", (int)pidx, p->nebs, p->at.x, p->at.y, p->force.x, p->force.y, p->velocity.x, p->velocity.y);
    }
#endif
}

static const float REST_DENSITY = 1;
static const float STIFFNESS = 10;
static const float VISCOCITY = 12;
static const float PARTICLE_SPACING = p_radius;
static const float PARTICLE_MASS = 1;
static const float KERNEL_RANGE = 2 * PARTICLE_SPACING;
static const float GRAVITY = 0.3;
static const float TIMESTEP = 0.01f;

#if 0
#define PI_FLOAT 3.1415927410125732421875f
#define PARTICLE_RESTING_DENSITY 1000
// Mass = Density * Volume
#define SMOOTHING_LENGTH (4 * p_radius)
#define PARTICLE_STIFFNESS 2000
#define PARTICLE_VISCOSITY 3000.f
#define GRAVITY_FORCE fpoint(0, 1.0)
#define TIME_STEP 1.0f
#endif

// Poly6 Kernel
float kernel(fpoint x, float h)
{
    float r2 = x.x * x.x + x.y * x.y;
    float h2 = h * h;

    if (r2 < 0 || r2 > h2) return 0.0f;

    return 315.0f / (64.0f * M_PI * pow(h, 9)) * pow(h2 - r2, 3);
}

// Gradient of Spiky Kernel
fpoint gradKernel(fpoint x, float h)
{
    float r = sqrt(x.x * x.x + x.y * x.y);
    if (r == 0.0f) return fpoint(0.0f, 0.0f);

    float t1 = -45.0f / (M_PI * pow(h, 6));
    fpoint t2 = x / r;
    float t3 = pow(h - r, 2);

    return t2 * (t1 * t3);
}

// Laplacian of Viscosity Kernel
float laplaceKernel(fpoint x, float h)
{
    float r = sqrt(x.x * x.x + x.y * x.y);
    return 45.0f / (M_PI * pow(h, 6)) * (h - r);
}

void Level::calculate_density (void)
{
    auto sop = getptr(all_particles, 1);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        auto sp = particle_to_grid(p);

        float density_sum = 0.1f;
        for (auto ox = sp.x - near_radius; ox <= sp.x + near_radius; ox++) {
            for (auto oy = sp.y - near_radius; oy <= sp.y + near_radius; oy++) {
                for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
                    auto qidx = get(all_particle_ids_at, ox, oy, slot);
                    if (likely(!qidx)) { // ignore empty cells
                        continue;
                    }

                    auto q = getptr(all_particles, qidx);
                    fpoint delta = p->at - q->at;
                    density_sum += PARTICLE_MASS * kernel(delta, KERNEL_RANGE);
                }
            }
        }
        if (!density_sum) {
            DIE("no density");
        }
        p->density = density_sum;
        p->pressure = fmax(STIFFNESS * (p->density - REST_DENSITY), 0.0f);
    }

    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        auto sp = particle_to_grid(p);

        fpoint fPressure(0.0f, 0.0f);
        fpoint fViscosity(0.0f, 0.0f);
        fpoint fGravity(0.0f, 0.0f);

        for (auto ox = sp.x - near_radius; ox <= sp.x + near_radius; ox++) {
            for (auto oy = sp.y - near_radius; oy <= sp.y + near_radius; oy++) {
                for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
                    auto qidx = get(all_particle_ids_at, ox, oy, slot);
                    if (likely(!qidx)) { // ignore empty cells
                        continue;
                    }

                    auto q = getptr(all_particles, qidx);
                    fpoint delta = p->at - q->at;

                    // Pressure force density
                    fPressure += gradKernel(delta, KERNEL_RANGE) *
                                 (PARTICLE_MASS * (p->pressure + q->pressure) / (2.0f * q->density));

                    // Viscosity force density
                    fpoint dv = (q->velocity - p->velocity);
                    fViscosity += dv * PARTICLE_MASS / q->density * laplaceKernel(delta, KERNEL_RANGE);

                    // Color field
                    //p->color += q->mass / q->density * kernel(x, KERNEL_RANGE);
                }
            }
        }

        // Gravitational force density
        fGravity = fpoint(0, GRAVITY) * p->density;
        fPressure *= -1.0f;
        fViscosity *= VISCOCITY;

        //p->force += fPressure + fViscosity + fGravity + fSurface;
        p->force += fPressure + fViscosity + fGravity;
    }

    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        p->velocity += p->force * TIMESTEP / p->density;
        p->old_at = p->at;
        move_particle(p, p->at + p->velocity * TIMESTEP);
    }

    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        collision_check_particle(p);
    }
}

void Level::tick_particles (void)
{
    if (1) {
        calculate_density();
    }
    if (0) {
        apply_particle_forces();
        apply_particle_velocity();
        apply_density_relaxation();
    }
#if 0
    auto sop = getptr(all_particles, 1);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }
        if (!collision_check_particle(p)) {
            move_particle(p, p->at + p->velocity);
        }
    }
#endif

#if 0
    auto sop = getptr(all_particles, 1);
    auto eop = getptr(all_particles, PARTICLE_MAX - 1);
    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        auto sp = particle_to_grid(p);
        auto pidx = p - getptr(all_particles, 0);

        float density_sum = 0.f;
        for (auto ox = sp.x - near_radius; ox <= sp.x + near_radius; ox++) {
            for (auto oy = sp.y - near_radius; oy <= sp.y + near_radius; oy++) {
                for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
                    auto qidx = get(all_particle_ids_at, ox, oy, slot);
                    if (likely(!qidx)) { // ignore empty cells
                        continue;
                    }

                    if (unlikely(qidx == pidx)) { // ignore our own particle
                        continue;
                    }

                    auto q = getptr(all_particles, qidx);
                    if (!q->in_use) { // remove this
                        continue;
                    }

                    fpoint delta = p->at - q->at;
                    float r = delta.length();
                    if (r < SMOOTHING_LENGTH) {
                        density_sum += 
                           PARTICLE_MASS * /* poly6 kernel */ 315.f *
                           pow(SMOOTHING_LENGTH * SMOOTHING_LENGTH - r * r, 3) /
                           (64.f * PI_FLOAT * pow(SMOOTHING_LENGTH, 9));
                    }
                }
            }
        }
        p->density = density_sum;
        // compute pressure
        p->pressure = fmax(PARTICLE_STIFFNESS *
                          (density_sum - PARTICLE_RESTING_DENSITY), 0.f);
    }

    for (auto p = sop; p <= eop; p++) {
        if (!p->in_use) {
            continue;
        }

        fpoint pressure_force(0, 0);
        fpoint viscosity_force(0, 0);

        auto sp = particle_to_grid(p);
        auto pidx = p - getptr(all_particles, 0);

        for (auto ox = sp.x - near_radius; ox <= sp.x + near_radius; ox++) {
            for (auto oy = sp.y - near_radius; oy <= sp.y + near_radius; oy++) {
                for (auto slot = 0; slot < PARTICLE_SLOTS; slot++) {
                    auto qidx = get(all_particle_ids_at, ox, oy, slot);
                    if (likely(!qidx)) { // ignore empty cells
                        continue;
                    }

                    if (unlikely(qidx == pidx)) { // ignore our own particle
                        continue;
                    }

                    auto q = getptr(all_particles, qidx);
                    if (!q->in_use) { // remove this
                        continue;
                    }

                    fpoint delta = p->at - q->at;
                    fpoint u = delta; u.unit();
                    float r = delta.length();

                    if (r < SMOOTHING_LENGTH) {
                        pressure_force -=
                            u *
                            PARTICLE_MASS * (p->pressure + q->pressure) / (2.f * q->density) *
                            // gradient of spiky kernel
                            -45.f / (PI_FLOAT * (float) pow(SMOOTHING_LENGTH, 6)) *
                            pow(SMOOTHING_LENGTH - r, 2);

                        auto dv = (q->velocity - p->velocity);
                        dv /= q->density;

                        viscosity_force += dv * PARTICLE_MASS *
                             // Laplacian of viscosity kernel
                            45.f / (PI_FLOAT * (float) pow(SMOOTHING_LENGTH, 6)) *
                        (SMOOTHING_LENGTH - r);
                    }
                }
            }
        }
        viscosity_force *= PARTICLE_VISCOSITY;
        fpoint external_force = GRAVITY_FORCE * p->density;

        p->force = pressure_force + viscosity_force + external_force;

        fpoint acceleration = p->force / p->density;

        fpoint new_velocity = p->velocity + (acceleration * TIME_STEP);

        fpoint new_position = p->at + (new_velocity * TIME_STEP);

        move_particle(p, new_position);
        p->velocity = new_velocity;

        if (collision_check_particle(p)) {
        }
    }
#endif
}
