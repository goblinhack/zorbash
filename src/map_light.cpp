/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_tile_info.h"
#include "my_tex.h"
#include "my_game.h"
#include "my_glapi.h"
#include <algorithm>

static const double MAX_LIGHT_STRENGTH = 1000.0;
static double ray_depth[MAX_LIGHT_RAYS];
static double ray_rad[MAX_LIGHT_RAYS];
static uint16_t map_light_count;

typedef struct map_light_ {
    Tpp tp;
    fpoint at;
    double strength;
    uint16_t max_light_rays;
    color col;
    uint8_t hiqual;
} map_light;
        
static map_light map_lights[MAX_LIGHTS];

void map_light_init (void)
{
    map_light_count = 0;
}

void map_light_add (Tpp tp, fpoint at, double strength, color c, bool hiqual)
{
    /*
     * Do a quick dmap check so that lights that are enclosed in a room do not 
     * shine
     */
    if (hiqual) {
    }

    if (unlikely(map_light_count >= MAX_LIGHTS)) {
        CON("light overflow");
        return;
    }

    map_lights[map_light_count].at = at;
    map_lights[map_light_count].strength = strength;
    map_lights[map_light_count].col = c;
    map_lights[map_light_count].tp = tp;
    map_lights[map_light_count].hiqual = hiqual;

    if (hiqual) {
        map_lights[map_light_count].max_light_rays = MAX_LIGHT_RAYS;
    } else {
        map_lights[map_light_count].max_light_rays = MAX_LIGHT_RAYS / 8;
    }

    map_light_count++;
}

static void map_light_add_ray_depth (const map_light *light,
                                     fpoint light_pos,
                                     fpoint light_end,
                                     double rad,
                                     int deg)
{
    auto len = DISTANCE(light_pos.x, light_pos.y, light_end.x, light_end.y);

    if (len > light->strength) {
        len = light->strength;
    }

    if (!ray_depth[deg]) {
        ray_depth[deg] = len;
        ray_rad[deg] = rad;
        ray_depth[deg] = len;
        ray_rad[deg] = rad;
    } else if (len < ray_depth[deg]) {
        ray_depth[deg] = len;
        ray_rad[deg] = rad;
        ray_depth[deg] = len;
        ray_rad[deg] = rad;
    }
}

/*
 * For each face of this obstacle, work out how kuch of the light
 * it blocks i.e. how many rays. For each ray, see if this is the
 * closest ray and if so, update the z depth of this ray. We are
 * building a z buffer of sorts.
 */
static void map_light_calculate_for_single_obstacle (Thingp t,
                                                     Tpp tp,
                                                     int x,
                                                     int y,
                                                     int light_index)
{
    const map_light *light = &map_lights[light_index];
    int otlx = x;
    int otly = y;
    int obrx = x + 1;
    int obry = y + 1;

    /*
     * No blocking our own light.
     */
    if (tp == light->tp) {
        return;
    }

    double etlx;
    double etly;
    double ebrx;
    double ebry;
    double fudge = 0.00;

    etlx = (double)otlx + fudge;
    etly = (double)otly + fudge;
    ebrx = (double)obrx - fudge;
    ebry = (double)obry - fudge;

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
    fpoint light_pos = light->at;

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
        int max_light_rays = light->max_light_rays;
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
         *
         * In essence, this is a depth buffer.
         */
        while (--tot_deg >= 0) {

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            fpoint light_end;
            light_end.x = light_pos.x + cosr * MAX_LIGHT_STRENGTH;
            light_end.y = light_pos.y + sinr * MAX_LIGHT_STRENGTH;

            /*
             * Check the light ray really does hit this obstacle and where
             * so we can work out distance.
             */
            fpoint intersect;
            if (get_line_known_intersection(P[k], P[l], 
                                            light_pos, light_end,
                                            &intersect)) {

                map_light_add_ray_depth(light, light_pos, intersect, 
                                        rad, deg);
            }

            map_light_add_ray_depth(light, light_pos, P[k], p1_rad, p1_deg);

            map_light_add_ray_depth(light, light_pos, P[l], p2_rad, p2_deg);

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

static void map_lighting_calculate (const int light_index)
{
    /*
     * First generate the right ray lengths.
     */
    memset(ray_depth, 0, sizeof(ray_depth));

    auto *light = &map_lights[light_index];
    auto dr = RAD_360 / (double) light->max_light_rays;
    auto rad = 0.0;

    for (auto i = 0; i < light->max_light_rays; i++) {
        ray_rad[i] = rad;
        rad += dr;
    }

    auto light_radius = light->strength;
    auto visible_width = light_radius + 1;
    auto visible_height = light_radius + 1;

    int16_t maxx = light->at.x + visible_width;
    int16_t minx = light->at.x - visible_width;
    int16_t maxy = light->at.y + visible_height;
    int16_t miny = light->at.y - visible_height;

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

    uint8_t z = MAP_DEPTH_WALLS; {
        for (int16_t x = maxx - 1; x >= minx; x--) {
            for (int16_t y = miny; y < maxy; y++) {
                for (auto t : game.state.map.things[x][y][z]) {
                    Tpp tp = t->tp;

                    if (tp_is_shadow_caster(tp) ||
                        unlikely(tp_is_shadow_caster_soft(tp))) {
                        map_light_calculate_for_single_obstacle(t, tp, x, y,
                                                                light_index);
                    }
                }
            }
        }
    }
}

/*
 * Draw the light as a central core of alpha blended light as a fan.
 * Blit the flan multiple times.
 * Combine this with a bitmap of a smoothed light source.
 */
static void map_lighting_render (const int light_index)
{
    auto *light = &map_lights[light_index];
    auto light_tp = light->tp;
    if (!light_tp) {
        return;
    }

    auto light_radius = light->strength;
    auto tx = light->at.x - game.state.map_at.x;
    auto ty = light->at.y - game.state.map_at.y;
    static const double tile_gl_width_pct = 1.0 / (double)TILES_ACROSS;
    static const double tile_gl_height_pct = 1.0 / (double)TILES_DOWN;
    fpoint light_pos(tx * tile_gl_width_pct, ty * tile_gl_height_pct);
    auto max_light_rays = light->max_light_rays;
    auto c = light->col;
    auto red   = ((double)c.r) / 255.0;
    auto green = ((double)c.g) / 255.0;
    auto blue  = ((double)c.b) / 255.0;
    auto alpha = ((double)c.a) / 255.0;

    double pct_tile_len_flicker;
    if (tp_is_candle_light(light_tp)) {
        pct_tile_len_flicker = 0.0 + (0.005 * (myrand() % 100));
    } else {
        pct_tile_len_flicker = 0.0;
    }

    /*
     * How much the light pushes into a block. Too much and you can see
     * below the block which we don't want.
     */
    double light_penetrate = 0.5;

    blit_init();
    {
        int i;

        /*
         * Walk the light rays in a circle.
         */
        push_point(light_pos.x, light_pos.y, red, green, blue, alpha);

        for (i = 0; i < max_light_rays; i++) {
            double radius = ray_depth[i];
            double rad = ray_rad[i];
            if (radius < 0.01) {
                radius = light_radius;
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

            push_point(p1x, p1y, red, green, blue, 0);
        }

        /*
         * Complete the circle with the first point again.
         */
        i = 0; {
            double radius = ray_depth[i];
            double rad = ray_rad[i];
            if (radius < 0.01) {
                radius = light_radius;
            }

            radius += sqrt(light_penetrate / radius);

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            double p1x = light_pos.x + cosr * radius * tile_gl_width_pct;
            double p1y = light_pos.y + sinr * radius * tile_gl_height_pct;

            push_point(p1x, p1y, red, green, blue, 0);
        }
    }

    if (light->hiqual) {
        blit_flush_triangle_fan_smoothed();
    } else {
        blit_flush_triangle_fan();
    }

    if (light->hiqual) {
        static Texp tex;
        static int buf;
        
        if (!tex) {
            tex = tex_load("", "light", GL_LINEAR);
            buf = tex_get_gl_binding(tex);
        }
 
        auto radius = light_radius;

        /*
         * To account for the smoothing in blit_flush_triangle_fan_smoothed.
         */
        radius *= 1.2;
 
        double lw = radius * tile_gl_width_pct;
        double lh = radius * tile_gl_height_pct;
        double p1x = light_pos.x - lw;
        double p1y = light_pos.y - lh;
        double p2x = light_pos.x + lw;
        double p2y = light_pos.y + lh;
 
        blit_init();
        glcolor(WHITE);
        glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
        blit(buf, 0, 0, 1, 1, p1x, p1y, p2x, p2y);
        blit_flush();
   }
}

void map_light_ray_effect (const int light_index, const int light_level)
{
    auto *light = &map_lights[light_index];
    auto light_radius = light->strength;
    auto light_pos = light->at;
    auto light_tp = light->tp;
    if (!light_tp) {
        return;
    }

    double tx = light->at.x - game.state.map_at.x;
    double ty = light->at.y - game.state.map_at.y;
    static const double tile_gl_width_pct = 1.0 / (double)TILES_ACROSS;
    static const double tile_gl_height_pct = 1.0 / (double)TILES_DOWN;
    light_pos.x = tx * tile_gl_width_pct;
    light_pos.y = ty * tile_gl_height_pct;

    auto max_light_rays = light->max_light_rays;

    {
        int i;

        /*
         * Walk the light rays in a circle.
         */
        auto dr = RAD_360 / (double) max_light_rays;
        auto rad = 0.0;
        for (i = 0; i < max_light_rays; i++, rad += dr) {
            auto radius = ray_depth[i];

            if (radius == 0) {
                radius = light_radius;
                continue;
            }

            radius *= 1.1;

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            auto p2x = light_pos.x + cosr * radius * tile_gl_width_pct;
            auto p2y = light_pos.y + sinr * radius * tile_gl_height_pct;
            auto p1x = light_pos.x + cosr * 0.1 * tile_gl_width_pct;
            auto p1y = light_pos.y + sinr * 0.1 * tile_gl_height_pct;

            gl_blitline(p1x, p1y, p2x, p2y);
        }
    }
}

void thing_map_test(void)
{
}

void map_light_display (int fbo)
{
    int i;

    for (i = 0; i < map_light_count; i++) {
        auto *light = &map_lights[i];

        /*
         * Calculate ray lengths for all passes.
         */
        map_lighting_calculate(i);

        if (light->hiqual) {
            blit_fbo_bind(FBO_VISITED_MAP);
            glClearColor(0,0,0,0);
            glClear(GL_COLOR_BUFFER_BIT);
            glcolor(WHITE);

            /*
             * We want to merge successive light sources together.
             */
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

            /*
             * Draw the light sources. First pass is for solid obstacles.
             */
            map_lighting_render(i);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            blit_fbo_bind(fbo);
            blit_fbo(FBO_VISITED_MAP);
            blit_fbo_unbind();
        } else {
            blit_fbo_bind(fbo);

            glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

            /*
             * Draw the light sources. First pass is for solid obstacles.
             */
            map_lighting_render(i);
        }
    }
}
