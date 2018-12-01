/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_light.h"
#include "my_thing.h"
#include "my_gl.h"

static uint32_t light_id;

static Texp light_overlay_tex;
static int light_overlay_texid;

static const double tile_gl_width_pct = 1.0 / (double)TILES_ACROSS;
static const double tile_gl_height_pct = 1.0 / (double)TILES_DOWN;
    
Lightp light_new (Thingp owner, 
                  uint16_t max_light_rays, 
                  double strength,
                  fpoint at,
                  LightQuality quality,
                  color col)
{_
    auto id = ++light_id;

    auto l = new Light(); // std::make_shared< class Light >();
    l->id = id;
    auto p = std::make_pair(l->id, l);
    auto result = game.state.map.all_lights.insert(p);
    if (result.second == false) {
        DIE("light insert [%d] failed", id);
    }

    point new_at((int)at.x, (int)at.y);
    auto n = &game.state.map.lights[new_at.x][new_at.y];
    result = n->insert(p);
    if (result.second == false) {
        DIE("light insert into map [%d] failed", id);
    }

    l->at             = at + fpoint(0.5, 0.5);
    l->strength       = strength;
    l->owner          = owner;
    l->quality        = quality;
    l->col            = col;
    l->max_light_rays = max_light_rays;

    l->ray_rad.resize(max_light_rays);
    l->ray_depth_buffer.resize(max_light_rays);

    std::fill(l->ray_depth_buffer.begin(), l->ray_depth_buffer.end(), 0.0);

    //log("created");
    return (l);
}

Lightp light_new (uint16_t max_light_rays, 
                  double strength, 
                  fpoint at,
                  LightQuality quality,
                  color col)
{_
    return (light_new(nullptr, max_light_rays, strength, at, quality, col));
}

void Light::pop (void)
{_
    game.state.map.all_lights.erase(id);

 /*
     * Pop from the map
     */
    point old_at((int)at.x, (int)at.y);
    auto o = &game.state.map.lights[old_at.x][old_at.y];
    auto iter = o->find(id);
    if (iter == o->end()) {
        die("thing not found to destroy");
    }

    o->erase(iter);
}

void Light::move_to (fpoint to)
{_
    to += fpoint(0.5, 0.5);

    point old_at((int)at.x, (int)at.y);
    point new_at((int)to.x, (int)to.y);

    /*
     * Keep track of where this light is on the grid
     */
    if (old_at != new_at) {
        /*
         * Pop
         */
        auto o = &game.state.map.lights[old_at.x][old_at.y];
        auto iter = o->find(id);
        if (iter == o->end()) {
            die("not found on map");
        }
        auto value = (*o)[id];
        o->erase(iter);

        /*
         * Add back
         */
        auto n = &game.state.map.lights[new_at.x][new_at.y];
        n->insert(std::make_pair(id, value));
    }

    at = to;
}

/*
 * Find an existing light.
 */
Lightp light_find (uint32_t id)
{_
    auto result = game.state.map.all_lights.find(id);
    if (result == game.state.map.all_lights.end()) {
        return (0);
    }

    return (result->second);
}

std::string Light::logname (void)
{_
    /*
     * Return constant strings from a small pool.
     */
    static char tmp[10][MAXSTR];
    static int loop;

    if (loop >= 10) {
        loop = 0;
    }

    snprintf(tmp[loop], sizeof(tmp[loop]) - 1, "%u at (%g,%g)", id, at.x, at.y);

    return (tmp[loop++]);
}

void Light::add_z_depth (fpoint &light_pos, fpoint &light_end, double rad,
                         int deg)
{
    auto len = DISTANCE(light_pos.x, light_pos.y, light_end.x, light_end.y);

    if (unlikely(len > strength)) {
        len = strength;
    }

    if (!ray_depth_buffer[deg]) {
        ray_depth_buffer[deg] = len;
        ray_rad[deg] = rad;
    } else if (len < ray_depth_buffer[deg]) {
        ray_depth_buffer[deg] = len;
        ray_rad[deg] = rad;
    }
}

/*
 * For each face of this obstacle, work out how kuch of the light
 * it blocks i.e. how many rays. For each ray, see if this is the
 * closest ray and if so, update the z depth of this ray. We are
 * building a z buffer of sorts.
 */
void Light::calculate_for_obstacle (Thingp t, int x, int y)
{
    int otlx = x;
    int otly = y;
    int obrx = x + 1;
    int obry = y + 1;

    /*
     * No blocking our own light.
     */
    if (t == owner) {
        return;
    }

    double etlx;
    double etly;
    double ebrx;
    double ebry;

    etlx = (double)otlx;
    etly = (double)otly;
    ebrx = (double)obrx;
    ebry = (double)obry;

    fpoint P[4];
    P[0].x = etlx;
    P[0].y = etly;
    P[1].x = ebrx;
    P[1].y = etly;
    P[2].x = ebrx;
    P[2].y = ebry;
    P[3].x = etlx;
    P[3].y = ebry;

    fpoint edge[4];
    edge[0] = P[1] - P[0];
    edge[1] = P[2] - P[1];
    edge[2] = P[3] - P[2];
    edge[3] = P[0] - P[3];

    fpoint normal[4];
    normal[0].x = edge[0].y;
    normal[0].y = -edge[0].x;
    normal[1].x = edge[1].y;
    normal[1].y = -edge[1].x;
    normal[2].x = edge[2].y;
    normal[2].y = -edge[2].x;
    normal[3].x = edge[3].y;
    normal[3].y = -edge[3].x;

    /*
     * For each clockwise side of the tile.
     */
    fpoint light_pos = at;

    /*
     * For each clockwise quadrant.
     */
    uint8_t k;
    for (k = 0; k<4; k++) {
        /*
         * Check if facing the light source.
         */
        fpoint light_dir = light_pos - P[k];
        auto dot = normal[k].x * light_dir.x + normal[k].y * light_dir.y;   
        if (dot <= 0.0f) {
            continue;
        }

        /*
         * Facing the light source. Blocks light.
         */
        int l = (k + 1) % 4;

        fpoint p1 = P[k] - light_pos;
        fpoint p2 = P[l] - light_pos;

        /*
         * Start and end points of the face blocking the light.
         */
        auto p1_rad = p1.anglerot();
        auto p2_rad = p2.anglerot();
        if (p1_rad == RAD_360) {
            p1_rad = 0;
        }
        if (p2_rad == RAD_360) {
            p2_rad = 0;
        }

        /*
         * How many degrees and radians does this face block?
         */
        int p1_deg = p1_rad * (double)max_light_rays / RAD_360;
        int p2_deg = p2_rad * (double)max_light_rays / RAD_360;

        /*
         * How many radians does this obstacle block?
         */
        auto tot_rad = p1_rad - p2_rad;
        int tot_deg = p1_deg - p2_deg;
        if (tot_deg < 0) {
            tot_deg += max_light_rays;
            tot_rad += RAD_360;
        }

        auto dr = tot_rad / tot_deg;
        auto rad = p2_rad;
        int deg = p2_deg;

        /*
         * For each blocking radian, look at the distance to the light.
         * If closer than what is blocking that radian curretly, then use 
         * this value.
         * In essence, this is a depth buffer.
         */
        while (--tot_deg >= 0) {
            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            fpoint light_end;
            light_end.x = light_pos.x + cosr * MAP_WIDTH;
            light_end.y = light_pos.y + sinr * MAP_WIDTH;

            /*
             * Check the light ray really does hit this obstacle and where
             * so we can work out distance.
             */
            fpoint intersect;
            if (get_line_known_intersection(P[k], P[l], 
                                            light_pos, light_end,
                                            &intersect)) {
                add_z_depth(light_pos, intersect, rad, deg);
            }

            /*
             * And make sure we intersect with the edges of the obstacle too.
             */
            add_z_depth(light_pos, P[k], p1_rad, p1_deg);
            add_z_depth(light_pos, P[l], p2_rad, p2_deg);

            rad += dr;
            if (rad >= RAD_360) {
                rad -= RAD_360;
            }

            deg++;
            if (deg >= max_light_rays) {
                deg = 0;
            }
        }
    }
}

void Light::calculate (void)
{
    /*
     * Reset the per light z buffer
     */
    std::fill(ray_depth_buffer.begin(), ray_depth_buffer.end(), 0);

    glbuf.clear();

    /*
     * First generate the right ray lengths.
     */
    auto dr = RAD_360 / (double) max_light_rays;
    auto rad = 0.0;

    for (auto i = 0; i < max_light_rays; i++) {
        ray_rad[i] = rad;
        rad += dr;
    }

    auto light_radius = strength;
    auto visible_width = light_radius + 1;
    auto visible_height = light_radius + 1;

    int16_t maxx = at.x + visible_width;
    int16_t minx = at.x - visible_width;
    int16_t maxy = at.y + visible_height;
    int16_t miny = at.y - visible_height;

    if (unlikely(minx < 0)) {
        minx = 0;
    }

    if (unlikely(maxx > MAP_WIDTH)) {
        maxx = MAP_WIDTH;
    }

    if (unlikely(miny < 0)) {
        miny = 0;
    }

    if (unlikely(maxy > MAP_HEIGHT)) {
        maxy = MAP_HEIGHT;
    }

    uint8_t z = MAP_DEPTH_WALLS;
    for (int16_t x = maxx - 1; x >= minx; x--) {
        for (int16_t y = miny; y < maxy; y++) {
            for (auto p : thing_display_order[x][y][z]) {
                auto t = p.second;
                if (tp_is_shadow_caster(t->tp)) {
                    calculate_for_obstacle(t, x, y);
                }
            }
        }
    }
}

void lights_calculate (void)
{
    for (uint16_t x = 0 ; x < MAP_WIDTH; x++) {
        for (uint16_t y = 0 ; y < MAP_HEIGHT; y++) {
            for (auto p : game.state.map.lights[x][y]) {
                auto l = p.second;

                switch (l->quality) {
                case LIGHT_QUALITY_HIGH:
                case LIGHT_QUALITY_LOW:
                    l->calculate();
                    break;

                case LIGHT_QUALITY_POINT:
                    break;

                default:
                    DIE("unknownd light quality");
                }
            }
        }
    }
}

void Light::render_triangle_fans (void)
{
    static const double tile_gl_width_pct = 1.0 / (double)TILES_ACROSS;
    static const double tile_gl_height_pct = 1.0 / (double)TILES_DOWN;

    auto tx = at.x;
    auto ty = at.y;
    fpoint light_pos(tx * tile_gl_width_pct, ty * tile_gl_height_pct);

    fpoint off(game.state.map_at.x * tile_gl_width_pct, 
               game.state.map_at.y * tile_gl_height_pct);
    auto ox = off.x;
    auto oy = off.y;

    glTranslatef(-ox, -oy, 0);

    if (!glbuf.size()) {
        auto c = col;
        auto red   = ((double)c.r) / 255.0;
        auto green = ((double)c.g) / 255.0;
        auto blue  = ((double)c.b) / 255.0;
        auto alpha = ((double)c.a) / 255.0;

        /*
         * How much the light pushes into a block. Too much and you can see
         * below the block which we don't want.
         */
        double light_penetrate = 0.8;

        blit_init();
        {
            int i;

            /*
             * Walk the light rays in a circle.
             */
            push_point(light_pos.x, light_pos.y, red, green, blue, alpha);

            for (i = 0; i < max_light_rays; i++) {
                double radius = ray_depth_buffer[i];
                double rad = ray_rad[i];
                if (radius < 0.01) {
                    radius = strength;
                }

                /*
                 * This makes the light ray bulge which makes it easier to see
                 * tiles close to the player.
                 */
                radius += sqrt(light_penetrate / radius);

                double cosr;
                double sinr;
                sincos(rad, &sinr, &cosr);

                double p1x = light_pos.x + cosr * radius * tile_gl_width_pct;
                double p1y = light_pos.y + sinr * radius * tile_gl_height_pct;

                // off white looks better
                push_point(p1x, p1y, red, green * 0.8, blue *0.8, 0);
            }

            /*
             * Complete the circle with the first point again.
             */
            i = 0; {
                double radius = ray_depth_buffer[i];
                double rad = ray_rad[i];
                if (radius < 0.01) {
                    radius = strength;
                }

                radius += sqrt(light_penetrate / radius);

                double cosr;
                double sinr;
                sincos(rad, &sinr, &cosr);

                double p1x = light_pos.x + cosr * radius * tile_gl_width_pct;
                double p1y = light_pos.y + sinr * radius * tile_gl_height_pct;

                // off white looks better
                push_point(p1x, p1y, red, green * 0.8, blue *0.8, 0);
            }
        }

        auto sz = bufp - gl_array_buf;
        glbuf.resize(sz);
        std::copy(gl_array_buf, bufp, glbuf.begin());

        if (quality == LIGHT_QUALITY_HIGH) {
            /*
             * This does multiple renders of the fan with blurring.
             */
            blit_flush_triangle_fan_smoothed();
        } else {
            /*
             * Just splat the raw fan, with alpha blended edges.
             */
            blit_flush_triangle_fan();
        }
    } else {
        float *b = &(*glbuf.begin());
        float *e = &(*glbuf.end());
        if (quality == LIGHT_QUALITY_HIGH) {
            /*
             * This does multiple renders of the fan with blurring.
             */
            blit_flush_triangle_fan_smoothed(b, e);
        } else {
            /*
             * Just splat the raw fan, with alpha blended edges.
             */
            blit_flush_triangle_fan(b, e);
        }
    }

    /*
     * Blend a texture on top of all the above blending so we get smooth
     * fade off of the light.
     */
    if (quality == LIGHT_QUALITY_HIGH) {
        auto radius = strength;

        /*
         * To account for the blurring in blit_flush_triangle_fan_smoothed.
         */
        if (flicker > random_range(10, 20)) {
            flicker = 0;
        }

        if (!flicker) {
            flicker_radius = (radius * 1.2) + (random_range(0, 100) / 100.0);
        }
        flicker++;
 
        double lw = flicker_radius * tile_gl_width_pct;
        double lh = flicker_radius * tile_gl_height_pct;
        double p1x = light_pos.x - lw;
        double p1y = light_pos.y - lh;
        double p2x = light_pos.x + lw;
        double p2y = light_pos.y + lh;
 
        blit_init();
        glcolor(WHITE);
        glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
        blit(light_overlay_texid, 0, 0, 1, 1, p1x, p1y, p2x, p2y);
        blit_flush();
   }
   glTranslatef(ox, oy, 0);
}

void Light::render_point_light (void)
{
    auto tx = at.x;
    auto ty = at.y;
    fpoint light_pos(tx * tile_gl_width_pct, ty * tile_gl_height_pct);

    fpoint off(game.state.map_at.x * tile_gl_width_pct, 
               game.state.map_at.y * tile_gl_height_pct);
    auto ox = off.x;
    auto oy = off.y;

    glTranslatef(-ox, -oy, 0);

    double lw = strength * tile_gl_width_pct;
    double lh = strength * tile_gl_height_pct;
    double p1x = light_pos.x - lw;
    double p1y = light_pos.y - lh;
    double p2x = light_pos.x + lw;
    double p2y = light_pos.y + lh;

    blit_init();
    glcolor(col);
    blit(light_overlay_texid, 0, 0, 1, 1, p1x, p1y, p2x, p2y);
    blit_flush();

    glTranslatef(ox, oy, 0);
}

void Light::render (int fbo)
{
    if (!light_overlay_tex) {
        light_overlay_tex = tex_load("", "light", GL_LINEAR);
        light_overlay_texid = tex_get_gl_binding(light_overlay_tex);
    }

    switch (quality) {
    case LIGHT_QUALITY_HIGH:
        /*
         * For high quality we render the light to its own FBO. This gives
         * better light color blending but is slower.
         */
        blit_fbo_bind(FBO_LIGHT_MASK);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glcolor(WHITE);

        /*
         * We want to merge successive light sources together.
         */
        glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

        render_triangle_fans();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        blit_fbo_bind(fbo);
        blit_fbo(FBO_LIGHT_MASK);
        blit_fbo_unbind();
        break;

    case LIGHT_QUALITY_LOW:
        /*
         * Draw direct to the FBO.
         */
        blit_fbo_bind(fbo);
        glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
        render_triangle_fans();
        break;

    case LIGHT_QUALITY_POINT:
        blit_fbo_bind(fbo);
        glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
        render_point_light();
        break;

    default:
        DIE("unknownd light quality");
    }
}

void lights_render (int fbo)
{
    for (uint16_t x = 0 ; x < MAP_WIDTH; x++) {
        for (uint16_t y = 0 ; y < MAP_HEIGHT; y++) {
            for (auto p : game.state.map.lights[x][y]) {
                auto l = p.second;
                /*
                 * Too far away from the player? Skip rendering.
                 */
                if (game.state.player) {
                    auto p = game.state.player;
                    auto len = DISTANCE(l->at.x, l->at.y, p->at.x, p->at.y);

                    if (len > TILES_ACROSS + l->strength) {
//                        continue;
                    }
                }

                l->render(fbo);
            }
        }
    }
}
