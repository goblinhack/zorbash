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

#define LIGHT_LEVELS 2
static const double MAX_LIGHT_STRENGTH = 1000.0;
static double ray_depth[MAX_LIGHT_RAYS][LIGHT_LEVELS];
static double ray_rad[MAX_LIGHT_RAYS][LIGHT_LEVELS];
static fpoint ray_lit[MAX_LIGHT_RAYS][LIGHT_LEVELS];
static uint16_t map_light_count;

typedef struct map_light_ {
    Tpp tp;
    fpoint at;
    double strength;
    uint16_t max_light_rays;
    color col;
} map_light;
        
static map_light map_lights[MAX_LIGHTS];

static bool map_ok (uint16_t x, uint16_t y)
{
    if (unlikely(x < 0)) {
        return (false);
    }

    if (unlikely(y < 0)) {
        return (false);
    }

    if (unlikely(x >= MAP_WIDTH)) {
        return (false);
    }

    if (unlikely(y >= MAP_HEIGHT)) {
        return (false);
    }

    return (true);
}

int map_get_lit_now_by_player (int x, int y)
{
    if (!map_ok(x, y)) {
        return (false);
    }

    return (game.state.map.lit_now_by_player[x][y]);
}

void map_set_lit_now_by_player (int x, int y)
{
    if (!map_ok(x, y)) {
        return;
    }

    game.state.map.lit_now_by_player[x][y] = true;
}

void map_unset_lit_now_by_player (int x, int y)
{
    if (!map_ok(x, y)) {
        return;
    }

    game.state.map.lit_now_by_player[x][y] = false;
}

int map_get_lit_earlier_by_player (int x, int y)
{
    if (!map_ok(x, y)) {
        return (false);
    }

    return(game.state.map.lit_earlier_by_player[x][y]);
}

void map_set_lit_earlier_by_player (int x, int y)
{
    if (!map_ok(x, y)) {
        return;
    }

    game.state.map.lit_earlier_by_player[x][y] = true;
}

void map_unset_lit_earlier_by_player (int x, int y)
{
    if (!map_ok(x, y)) {
        return;
    }

    game.state.map.lit_earlier_by_player[x][y] = false;
}

void map_light_init (void)
{
    map_light_count = 0;
}

static void map_light_add_one (Tpp tp, fpoint at, double strength, color c)
{
    /*
     * Do a quick dmap check so that lights that are enclosed in a room do not 
     * shine
     */
#if 0
    if (tp_is_ethereal(tp)) {
        /*
         * Death is always lit...
         */
    } else if (player && !tp_is_player_or_owned_by_player(tp)) {
        int sx, sy;

        thing_real_to_map(t, &sx, &sy);

        int distance = dmap_distance_to_player(sx, sy);
        if (distance == -1) {
            return;
        }

        /*
         * Cheap effect, make the light fade away with distance.
         */
        double scale = (256.0 - (((double)distance) * 8.0)) / 256.0;
        if (scale <= 0.1) {
            return;
        }

        c.r = (uint8_t) (((double)c.r) * scale);
        c.g = (uint8_t) (((double)c.g) * scale);
        c.b = (uint8_t) (((double)c.b) * scale);
        c.a = (uint8_t) (((double)c.a) * scale);
    }
#endif

    if (map_light_count >= MAX_LIGHTS) {
        return;
    }

    memset(&map_lights[map_light_count].at, 0, sizeof(map_light));

    map_lights[map_light_count].at = at;
    map_lights[map_light_count].strength = strength;
    map_lights[map_light_count].col = c;
    map_lights[map_light_count].tp = tp;

    if (tp_is_player(tp)) {
        map_lights[map_light_count].max_light_rays = MAX_LIGHT_RAYS;
    } else {
        map_lights[map_light_count].max_light_rays = MAX_LIGHT_RAYS / 8;
    }

    map_light_count++;
}

void map_light_add (Tpp tp, fpoint at, double strength, color c)
{
    map_light_add_one(tp, at, strength, c);
}

static void map_light_add_ray_depth (fpoint p,
                                       const map_light *light,
                                       fpoint light_pos,
                                       fpoint light_end,
                                       double rad,
                                       int deg,
                                       int soft_shadow)
{
    auto len = DISTANCE(light_pos.x, light_pos.y, light_end.x, light_end.y);

    if (len > light->strength) {
        len = light->strength;
    }

    if (soft_shadow) {
        if (!ray_depth[deg][0]) {
            ray_depth[deg][1] = len;
            ray_rad[deg][1] = rad;
            ray_lit[deg][1] = p;
        } else if (!ray_depth[deg][1]) {
            ray_depth[deg][1] = len;
            ray_rad[deg][1] = rad;
            ray_lit[deg][1] = p;
        } else if (len < ray_depth[deg][1]) {
            ray_depth[deg][1] = len;
            ray_rad[deg][1] = rad;
            ray_lit[deg][1] = p;
        }
    } else {
        if (!ray_depth[deg][0]) {
            ray_depth[deg][0] = len;
            ray_rad[deg][0] = rad;
            ray_lit[deg][0] = p;

            ray_depth[deg][1] = len;
            ray_rad[deg][1] = rad;
            ray_lit[deg][1] = p;
        } else if (len < ray_depth[deg][0]) {
            ray_depth[deg][0] = len;
            ray_rad[deg][0] = rad;
            ray_lit[deg][0] = p;

            ray_depth[deg][1] = len;
            ray_rad[deg][1] = rad;
            ray_lit[deg][1] = p;
        }
    }
}

/*
 * For each face of this obstacle, work out how kuch of the light
 * it blocks i.e. how many rays. For each ray, see if this is the
 * closest ray and if so, update the z depth of this ray. We are
 * building a z buffer of sorts.
 */
static void map_light_calculate_for_single_obstacle (Tpp tp,
                                                       int x,
                                                       int y,
                                                       int light_index)
{
    const map_light *light = &map_lights[light_index];
    int owidth;
    int oheight;
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

    uint8_t soft_shadow = 0;

    /*
    if (tp_is_shadow_caster_soft(tp)) {
        soft_shadow = 1;
    }
     */

    /*
     * Record the original pre clip sizes for text centering.
     */
    owidth = obrx - otlx;
    oheight = obry - otly;

    double etlx;
    double etly;
    double ebrx;
    double ebry;

    if (soft_shadow) {
        /*
         * Make soft shadow things block less light.
         */
        double fudge = 0.2;

        etlx = (double)otlx + fudge;
        etly = (double)otly + fudge;
        ebrx = (double)obrx - fudge;
        ebry = (double)obry - fudge;
    } else {
        etlx = (double)otlx;
        etly = (double)otly;
        ebrx = (double)obrx;
        ebry = (double)obry;
    }

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
        while (tot_deg-- >= 0) {

            fpoint light_end;
            light_end.x = light_pos.x + cos(rad) * MAX_LIGHT_STRENGTH;
            light_end.y = light_pos.y + sin(rad) * MAX_LIGHT_STRENGTH;

            /*
             * Check the light ray really does hit this obstacle and where
             * so we can work out distance.
             */
            fpoint intersect;
            if (get_line_known_intersection(P[k], P[l], 
                                            light_pos, light_end,
                                            &intersect)) {

                map_light_add_ray_depth(P[0], light, light_pos, intersect, 
                                        rad, deg, soft_shadow);
            }

            map_light_add_ray_depth(P[0], light, light_pos, P[k], 
                                    p1_rad, p1_deg, soft_shadow);

            map_light_add_ray_depth(P[0], light, light_pos, P[l], 
                                    p2_rad, p2_deg, soft_shadow);

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
    memset(ray_lit, 0, sizeof(ray_lit));

    auto *light = &map_lights[light_index];
    auto dr = RAD_360 / (double) light->max_light_rays;
    auto rad = 0.0;

    for (auto i = 0; i < light->max_light_rays; i++) {
        for (auto j = 0; j < LIGHT_LEVELS; j++) {
            ray_rad[i][j] = rad;
        }
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
                        map_light_calculate_for_single_obstacle(tp, x, y,
                                                                light_index);
                    }
                }
            }
        }
    }
}

/*
 * Given a previously calculated light depth map, see which squares are lit
 */
static void map_lighting_set_visible (const int level,
                                      const int light_index,
                                      const int light_level)
{
    map_light *light = &map_lights[light_index];
    double light_radius = light->strength;
    double lx = light->at.x;
    double ly = light->at.y;
    double x1 = lx - light_radius;
    double x2 = lx + light_radius;
    double y1 = ly - light_radius;
    double y2 = ly + light_radius;
    double x, y;
    int max_light_rays = light->max_light_rays;

    for (x = x1; x <= x2; x++) {
        for (y = y1; y <= y2; y++) {

            if (!map_ok(x, y)) {
                continue;
            }

            /*
             * For each corner of this tile, see if it is lit
             */
            int dx, dy;
            for (dx = 0; dx <= 1; dx++) for (dy = 0; dy <= 1; dy++)  {

                /*
                 * Get the integer co-ordinates of each corner of this square 
                 * tile.
                 */
                double X = floor(x) + dx;
                double Y = floor(y) + dy;

                /*
                 * How far is this corner from the light. Too far?
                 */
                double dist = DISTANCE(X, Y, lx, ly);
                if (dist > light_radius) {
                    continue;
                }

                /*
                 * How much is this corner point rotated around the light 
                 * source.
                 */
                fpoint p;
                p.x = X - lx;
                p.y = Y - ly;
                auto pa = p.anglerot();

                /*
                 * Convert to a light array index
                 */
                int d = pa * (double) max_light_rays / RAD_360;
                d = d % max_light_rays;

                /*
                 * Is this tile within the light, plus a small delta. As the 
                 * light ends at the intersection point with the object we 
                 * need to let the light leak in a bit so we can see it.
                 */
                double depth = ray_depth[d][light_level];
                if (dist <= depth + 0.1) {
                    map_set_lit_now_by_player((int)x, (int)y);
                    goto done;
                }

                /*
                 * Ok, onto the corner cases. As we cannot cast an infinite 
                 * number of light rays, we look at the two rays surrounding
                 * our idealised ray. If we are within the distance of both
                 * of those then we say we are visible too.
                 *
                 * So first find the two rays.
                 */
                int ray_index_lower, ray_index_higher;

                ray_index_lower = d;
                for (;;) {
                    double r = ray_rad[ray_index_lower][light_level];
                    if (r <= pa) {
                        break;
                    } else if (r - pa > RAD_180) {
                        break;
                    }

                    ray_index_lower--;
                    if (ray_index_lower < 0) {
                        ray_index_lower += max_light_rays;
                    }
                }

                ray_index_higher = d;
                for (;;) {
                    double r = ray_rad[ray_index_higher][light_level];
                    if (r >= pa) {
                        break;
                    } else if (pa - r > RAD_180) {
                        break;
                    }

                    ray_index_higher++;
                    if (ray_index_higher >= max_light_rays) {
                        ray_index_higher -= max_light_rays;
                    }
                }

                /*
                 * Check that the gap between rays is at most one light ray.
                 * Else we would ignore blocked light rays and think we are
                 * visible.
                 */
                int delta;

                if (ray_index_higher - ray_index_lower < 0) {
                    delta = (max_light_rays - ray_index_lower) + ray_index_higher;
                } else {
                    delta = ray_index_higher - ray_index_lower;
                }

                if (delta > 1) {
                    continue;
                }

                double depth1 = ray_depth[ray_index_lower][light_level];
                double depth2 = ray_depth[ray_index_higher][light_level];

                if ((dist <= depth1) || (dist <= depth2)) {
                    map_set_lit_now_by_player((int)x, (int)y);
                    goto done;
                }
            }
done:
            continue;
        }
    }

    /*
     * Finally ensure that all rays that hit something, that something is lit
     */
    int i;

    for (i = 0; i < MAX_LIGHT_RAYS; i++) {
        double depth = ray_depth[i][light_level];
        if ((depth > 0.0) && (light_radius > depth + 0.1)) {
            fpoint p = ray_lit[i][light_level];

            map_set_lit_now_by_player(p.x, p.y);

        }
    }
}

static void map_lighting_render (const int light_index,
                                 const int light_level)
{
    auto *light = &map_lights[light_index];
    auto light_radius = light->strength;
    auto light_tp = light->tp;
    if (!light_tp) {
        return;
    }

    double tx = light->at.x - game.state.map_at.x;
    double ty = light->at.y - game.state.map_at.y;
    static const double tdx = 1.0 / (double)TILES_ACROSS;
    static const double tdy = 1.0 / (double)TILES_DOWN;
    fpoint light_pos(tx * tdx, ty * tdy);
    auto max_light_rays = light->max_light_rays;
    auto c = light->col;
    auto red   = ((double)c.r) / 255.0;
    auto green = ((double)c.g) / 255.0;
    auto blue  = ((double)c.b) / 255.0;
    auto alpha = ((double)c.a) / 255.0;

    /*
     * Draw the light in three stages. 
     *
     * 1. Central core of light as a fan
     * 2. Strip of dimmer light at the edges
     * 3. Strip of flickering even dimmer light
     */

    auto pct_light_radius_bright = 1.0;
    auto pct_light_radius_dimmer = 1.0;
    double pct_tile_len_flicker;

    if (tp_is_candle_light(light_tp)) {
        pct_tile_len_flicker = 0.0 + (0.005 * (myrand() % 100));
    } else {
        pct_tile_len_flicker = 0.0;
    }

    /*
     * Now blit to the FBO, drawing the central core of the light rays
     */
    blit_init();

    {
        int i;

        /*
         * Walk the light rays in a circle.
         */
        push_point(light_pos.x, light_pos.y, red, green, blue, alpha);

        for (i = 0; i < max_light_rays; i++) {
            double radius = ray_depth[i][light_level];
            double rad = ray_rad[i][light_level];
            if (radius == 0) {
                radius = light_radius;
            }

            radius *= pct_light_radius_bright;

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            double p1x = light_pos.x + cosr * radius * tdx;
            double p1y = light_pos.y + sinr * radius * tdy;

            push_point(p1x, p1y, red, green, blue, alpha);
        }

        /*
         * Complete the circle with the first point again.
         */
        i = 0; {
            double radius = ray_depth[i][light_level];
            double rad = ray_rad[i][light_level];
            if (radius == 0) {
                radius = light_radius;
            }

            radius *= pct_light_radius_bright;

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            double p1x = light_pos.x + cosr * radius * tdx;
            double p1y = light_pos.y + sinr * radius * tdy;

            push_point(p1x, p1y, red, green, blue, alpha);
        }
    }

    blit_flush_triangle_fan();

    {
        static Texp tex;
        static int buf;
        
        if (!tex) {
            tex = tex_load("", "light", GL_LINEAR);
            buf = tex_get_gl_binding(tex);
        }
        blit_init();
        glcolor(WHITE);

        auto radius = light_radius;
        radius *= pct_light_radius_bright;

        double lw = light_radius * tdx;
        double lh = light_radius * tdy;
        double p1x = light_pos.x - lw;
        double p1y = light_pos.y - lh;
        double p2x = light_pos.x + lw;
        double p2y = light_pos.y + lh;

        glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
        blit(buf, 0, 0, 1, 1, p1x, p1y, p2x, p2y);
        blit_flush();
    }

    return;
    {
        int i;

        /*
         * Walk the light rays in a circle.
         */
        push_point(light_pos.x, light_pos.y, red, green, blue, alpha);

        for (i = 0; i < max_light_rays; i++) {
            double p1_len = ray_depth[i][light_level];
            double rad = ray_rad[i][light_level];
            if (p1_len == 0) {
                p1_len = light_radius;
            }

            p1_len *= pct_light_radius_bright;

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            double p1x = light_pos.x + cosr * p1_len * tdx;
            double p1y = light_pos.y + sinr * p1_len * tdy;

            push_point(p1x, p1y, red, green, blue, pct_light_radius_bright * alpha);
        }

        /*
         * Complete the circle with the first point again.
         */
        i = 0; {
            double p1_len = ray_depth[i][light_level];
            double rad = ray_rad[i][light_level];
            if (p1_len == 0) {
                p1_len = light_radius;
            }

            p1_len *= pct_light_radius_bright;

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            double p1x = light_pos.x + cosr * p1_len * tdx;
            double p1y = light_pos.y + sinr * p1_len * tdy;

            push_point(p1x, p1y, red, green, blue, pct_light_radius_bright * alpha);
        }
    }

    blit_flush_triangle_fan();

    /*
     * Draw dimmer light
     */
    blit_init();

    {
        int i;

        /*
         * Walk the light rays in a circle.
         */
        for (i = 0; i < max_light_rays; i++) {
            double p1_len = ray_depth[i][light_level];
            double rad = ray_rad[i][light_level];
            double p3_len;
            if (p1_len == 0) {
                p1_len = light_radius;
            }

            p3_len = p1_len * pct_light_radius_dimmer;
            p1_len *= pct_light_radius_bright;

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            double p1x = light_pos.x + cosr * p1_len * tdx;
            double p1y = light_pos.y + sinr * p1_len * tdy;

            double p3x = light_pos.x + cosr * p3_len * tdx;
            double p3y = light_pos.y + sinr * p3_len * tdy;

            push_point(p1x, p1y, red, green, blue, pct_light_radius_bright * alpha);
            push_point(p3x, p3y, red, green, blue, pct_light_radius_dimmer * alpha * 0.35);
        }

        /*
         * Complete the strip with 1.5 triangles.
         */
        i = 0; {
            double p1_len = ray_depth[i][light_level];
            double rad = ray_rad[i][light_level];
            double p3_len;
            if (p1_len == 0) {
                p1_len = light_radius;
            }

            p3_len = p1_len * pct_light_radius_dimmer;
            p1_len *= pct_light_radius_bright;

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            double p1x = light_pos.x + cosr * p1_len * tdx;
            double p1y = light_pos.y + sinr * p1_len * tdy;

            double p3x = light_pos.x + cosr * p3_len * tdx;
            double p3y = light_pos.y + sinr * p3_len * tdy;

            push_point(p1x, p1y, red, green, blue, pct_light_radius_bright * alpha);
            push_point(p3x, p3y, red, green, blue, pct_light_radius_dimmer * alpha * 0.35);
        }
    }

    /*
     * Flush non shaded triangles.
     */
    blit_flush_triangle_strip();

    if (pct_tile_len_flicker > 0.0) {
        /*
         * Now draw the fuzzy edge of the light as a trigangle strip.
         */
        blit_init();

        {
            int i;

            /*
             * Walk the light rays in a circle.
             */
            for (i = 0; i < max_light_rays; i++) {
                double p1_len = ray_depth[i][light_level];
                double rad = ray_rad[i][light_level];

                if (p1_len == 0) {
                    p1_len = light_radius;
                }

                double p3_len = p1_len;

                double cosr;
                double sinr;
                sincos(rad, &sinr, &cosr);

                double p1x = light_pos.x + cosr * p1_len * tdx;
                double p1y = light_pos.y + sinr * p1_len * tdy;

                double p3x = light_pos.x + cosr * p3_len * tdx;
                double p3y = light_pos.y + sinr * p3_len * tdy;

                p3x += cosr * tdx * pct_tile_len_flicker;
                p3y += sinr * tdy * pct_tile_len_flicker;

                push_point(p1x, p1y, red, green, blue, alpha * 0.35);
                push_point(p3x, p3y, red, green, blue, alpha * 0.05);
            }

            /*
             * Complete the strip with 1.5 triangles.
             */
            i = 0; {
                double p1_len = ray_depth[i][light_level];
                double rad = ray_rad[i][light_level];

                if (p1_len == 0) {
                    p1_len = light_radius;
                }

                double p3_len = p1_len;

                double cosr;
                double sinr;
                sincos(rad, &sinr, &cosr);

                double p1x = light_pos.x + cosr * p1_len * tdx;
                double p1y = light_pos.y + sinr * p1_len * tdy;

                double p3x = light_pos.x + cosr * p3_len * tdx;
                double p3y = light_pos.y + sinr * p3_len * tdy;

                p3x += cosr * tdx * pct_tile_len_flicker;
                p3y += sinr * tdy * pct_tile_len_flicker;

                push_point(p1x, p1y, red, green, blue, alpha * 0.35);
                push_point(p3x, p3y, red, green, blue, alpha * 0.05);
            }
        }

        /*
         * Flush non shaded triangles.
         */
        blit_flush_triangle_strip();
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
    static const double tdx = 1.0 / (double)TILES_ACROSS;
    static const double tdy = 1.0 / (double)TILES_DOWN;
    light_pos.x = tx * tdx;
    light_pos.y = ty * tdy;

    auto max_light_rays = light->max_light_rays;

    {
        int i;

        /*
         * Walk the light rays in a circle.
         */
        auto dr = RAD_360 / (double) max_light_rays;
        auto rad = 0.0;
        for (i = 0; i < max_light_rays; i++, rad += dr) {
            auto p1_len = ray_depth[i][light_level];

            if (p1_len == 0) {
                p1_len = light_radius;
                continue;
            }

            p1_len *= 1.1;

            double cosr;
            double sinr;
            sincos(rad, &sinr, &cosr);

            auto p2x = light_pos.x + cosr * p1_len * tdx;
            auto p2y = light_pos.y + sinr * p1_len * tdy;
            auto p1x = light_pos.x + cosr * 0.1 * tdx;
            auto p1y = light_pos.y + sinr * 0.1 * tdy;

            gl_blitline(p1x, p1y, p2x, p2y);
        }
    }
}

/*
 * Whatever is visible by the current players light source, set it as
 * historical.
 */
static void map_light_change_visible_now_to_earlier (void)
{
    int x, y;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            if (map_get_lit_now_by_player(x, y)) {
                map_set_lit_earlier_by_player(x, y);
                map_unset_lit_now_by_player(x, y);
            }
        }
    }
}

void map_light_calculate_visible (int level)
{
    map_light_change_visible_now_to_earlier();

    int i;

    for (i = 0; i < map_light_count; i++) {
        /*
         * Calculate ray lengths for all passes.
         */
        map_lighting_calculate(i);

        map_lighting_set_visible(level, i, 0);
    }
}

void map_light_display (int level, int fbo, int clear)
{
    blit_fbo_bind(fbo);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glcolor(WHITE);

    /*
     * We want to merge successive light sources together.
     */
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    //blit_init();

    int i;

    for (i = 0; i < map_light_count; i++) {
#if 0
        map_light *light = &map_lights[i];

        if (fbo == FBO_CURRENT_VISIBLE_MAP_SHADOW) {
            if (light->is_historical) {
                continue;
            }
        }
#endif

        /*
         * Calculate ray lengths for all passes.
         */
        map_lighting_calculate(i);

        /*
         * Draw the light sources. First pass is for solid obstacles.
         */
        blit_fbo_bind(FBO_CURRENT_VISIBLE_MAP_SHADOW);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glcolor(WHITE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        map_lighting_render(i, 0);
        blit_fbo_unbind();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        blit_fbo_bind(FBO_VISITED_MAP_MERGED);
        blit_fbo(FBO_CURRENT_VISIBLE_MAP_SHADOW);
        blit_fbo_unbind();

        /*
         * This for soft shadows.
         */
//        map_lighting_render(i, 1);
    }

    blit_fbo_unbind();
}

void map_light_glow_display (int level)
{
    int i;

    /*
     * Redraw light sources on top of the light they cast.
     */
    for (i = 0; i < map_light_count; i++) {
        map_light *light = &map_lights[i];

        if (!tp_is_player(light->tp)) {
            continue;
        }

#if 0
        if (light->is_historical) {
            continue;
        }
#endif

        /*
         * Calculate ray lengths for all passes.
         */
        map_lighting_calculate(i);

        /*
         * Draw the light sources. First pass is for solid obstacles.
         */
        color c = WHITE;
        c.a = 10;
        glcolor(c);

#ifdef ENABLE_DEBUG_LIGHT
        c = RED;
        c.a = 200;
        glcolor(c);
#endif

        map_light_ray_effect(i, 0);
    }
}
