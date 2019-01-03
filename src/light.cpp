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

Thingp debug_thing;
    
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

    l->ray.resize(max_light_rays);
    std::fill(l->ray.begin(), l->ray.end(), Ray{0});

    /*
     * First generate the right ray lengths.
     */
    double dr = RAD_360 / (double) max_light_rays;
    for (auto i = 0; i < max_light_rays; i++) {
        auto r = &l->ray[i];
        double rad = dr * (double)i;
        sincos(rad, &r->sinr, &r->cosr);
    }

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

Lightp light_new (double strength, 
                  fpoint at,
                  LightQuality quality,
                  color col)
{_
    return (light_new(nullptr, 10, strength, at, quality, col));
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

void Light::calculate (void)
{
    glbuf.clear();

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

    /*
     * Walk the light rays in a circle. First pass is to find the nearest
     * walls.
     */
    memset(is_nearest_wall, 0, sizeof(is_nearest_wall));
    for (int i = 0; i < max_light_rays; i++) {
        auto r = &ray[i];
        double step = 0.0;
        for (; step < strength; step += 0.01) {
            double rad = step;
            double p1x = at.x + r->cosr * rad;
            double p1y = at.y + r->sinr * rad;

            int x = (int)p1x;
            int y = (int)p1y;

            if (game.state.map.is_oob(x, y)) {
                break;
            }

            if (game.state.map.is_shadow_caster[x][y]) {
                break;
            }
        }

        r->depth_closest = step;

        /*
         * Let the light leak in a little bit. This handles corners so that
         * a point hitting on or near a corner will light the corner tile.
         */
        double step2 = step;
        for (; step2 < step + 0.9; step2 += 0.01) {
            double rad = step2;
            double p1x = at.x + r->cosr * rad;
            double p1y = at.y + r->sinr * rad;

            int x = (int)p1x;
            int y = (int)p1y;

            if (!game.state.map.is_shadow_caster[x][y]) {
                break;
            }

            is_nearest_wall[x][y] = true;
        }
    }

    /*
     * Now for light penetrating into rock. We stop a bit short due to * the 
     * fuzzing of the light we do when rendering, to avoid light leaking into 
     * tiles we should not see.
     *
     * Cannot merge these two loops as we depend on is_nearest_wall being set
     * for all tiles first.
     */
    for (int i = 0; i < max_light_rays; i++) {
        auto r = &ray[i];
        double radius = r->depth_closest;
        double fade = pow(strength - radius, 0.05);
        double step = 0.0;
        for (; step < 1.0; step += 0.01) {
            fade *= 0.99;
            if (fade < 0.001) {
                break;
            }

            double rad = radius + 0.0 + step;
            double p1x = at.x + r->cosr * rad;
            double p1y = at.y + r->sinr * rad;

            int x = (int)p1x;
            int y = (int)p1y;

            if (game.state.map.is_oob(x, y)) {
                break;
            }

            if (!is_nearest_wall[x][y]) {
                break;
            }
        }

        r->depth_furthest = r->depth_closest + step;
        if (r->depth_furthest < 0.001) {
            r->depth_furthest = strength;
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

        blit_init();
        {
            int i;

            /*
             * Walk the light rays in a circle.
             */
            push_point(light_pos.x, light_pos.y, red, green, blue, alpha);

            for (i = 0; i < max_light_rays; i++) {
                auto r = &ray[i];
                double radius = r->depth_furthest;
                double p1x = light_pos.x + r->cosr * radius * tile_gl_width_pct;
                double p1y = light_pos.y + r->sinr * radius * tile_gl_height_pct;

                // off white looks better
                push_point(p1x, p1y, red, green*0.8, blue*0.8, 0);
            }

            /*
             * Complete the circle with the first point again.
             */
            i = 0; {
                auto r = &ray[0];
                double radius = r->depth_furthest;
                double p1x = light_pos.x + r->cosr * radius * tile_gl_width_pct;
                double p1y = light_pos.y + r->sinr * radius * tile_gl_height_pct;

                // off white looks better
                push_point(p1x, p1y, red, green*0.8, blue*0.8, 0);
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
        /*
         * To account for the blurring in blit_flush_triangle_fan_smoothed.
         */
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

void Light::render_debug_lines (int minx, int miny, int maxx, int maxy)
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

    int i;

    glcolor(GRAY50);

    /*
     * Walk the light rays in a circle.
     */
    uint8_t z = MAP_DEPTH_WALLS;
    for (int16_t x = maxx - 1; x >= minx; x--) {
        for (int16_t y = miny; y < maxy; y++) {
            for (auto p : thing_display_order[x][y][z]) {
                if (is_nearest_wall[x][y]) {
                    double X = x;
                    double Y = y;
                    double p1x = X * tile_gl_width_pct;
                    double p1y = Y * tile_gl_height_pct;
                    double p2x = (X+1) * tile_gl_width_pct;
                    double p2y = (Y+1) * tile_gl_height_pct;
                    gl_blitline(p1x, p1y, p1x, p2y);
                    gl_blitline(p1x, p1y, p2x, p1y);
                    gl_blitline(p2x, p2y, p2x, p1y);
                    gl_blitline(p2x, p2y, p1x, p2y);
                }
            }
        }
    }

    glcolor(GREEN);

    /*
     * Walk the light rays in a circle.
     */
    for (i = 0; i < max_light_rays; i++) {
        auto r = &ray[i];
        double radius = r->depth_furthest;
        double p1x = light_pos.x + r->cosr * radius * tile_gl_width_pct;
        double p1y = light_pos.y + r->sinr * radius * tile_gl_height_pct;

        gl_blitline(light_pos.x, light_pos.y, p1x, p1y);
    }

    glcolor(RED);

    /*
     * Walk the light rays in a circle.
     */
    for (i = 0; i < max_light_rays; i++) {
        auto r = &ray[i];
        double radius = r->depth_closest;
        double p1x = light_pos.x + r->cosr * radius * tile_gl_width_pct;
        double p1y = light_pos.y + r->sinr * radius * tile_gl_height_pct;

        gl_blitline(light_pos.x, light_pos.y, p1x, p1y);
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

    double lw = flicker_radius * tile_gl_width_pct;
    double lh = flicker_radius * tile_gl_height_pct;
    double p1x = light_pos.x - lw;
    double p1y = light_pos.y - lh;
    double p2x = light_pos.x + lw;
    double p2y = light_pos.y + lh;

    glcolor(col);
    blit(light_overlay_texid, 0, 0, 1, 1, p1x - ox, p1y - oy, p2x - ox, p2y - oy);
}

void Light::render (int fbo)
{
    if (flicker > random_range(10, 20)) {
        flicker = 0;
    }

    if (!flicker) {
        flicker_radius = strength * 
                        (1.0 + ((double)(random_range(0, 100) / 1000.0)));
    }
    flicker++;

    if (!light_overlay_tex) {
        light_overlay_tex = tex_load("", "light", GL_NEAREST);
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
        render_point_light();
        break;

    default:
        DIE("unknownd light quality");
    }
}

void Light::render_debug (int minx, int miny, int maxx, int maxy)
{
    switch (quality) {
    case LIGHT_QUALITY_HIGH:
        render_debug_lines(minx, miny, maxx, maxy);
        break;

    case LIGHT_QUALITY_LOW:
        break;

    case LIGHT_QUALITY_POINT:
        break;

    default:
        DIE("unknownd light quality");
    }
}

void lights_render (int minx, int miny, int maxx, int maxy, int fbo)
{
    bool have_low_quality = false;

    for (auto y = miny; y < maxy; y++) {
        for (auto x = maxx - 1; x >= minx; x--) {
            for (auto p : game.state.map.lights[x][y]) {
                auto l = p.second;
                if (l->quality != LIGHT_QUALITY_POINT) {
                    continue;
                }

                /*
                 * Too far away from the player? Skip rendering.
                 */
                if (game.state.player) {
                    auto p = game.state.player;
                    auto len = DISTANCE(l->at.x, l->at.y, p->at.x, p->at.y);

                    if (len > TILES_ACROSS + l->strength) {
                        continue;
                    }
                }

                have_low_quality = true;
            }
        }
    }

    if (!have_low_quality) {
        return;
    }

    blit_fbo_bind(fbo);
    glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
    glcolor(WHITE);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = maxx - 1; x >= minx; x--) {
            for (auto p : game.state.map.lights[x][y]) {
                auto l = p.second;
                if (l->quality != LIGHT_QUALITY_POINT) {
                    continue;
                }

#if 0
                switch (random_range(0, 4)) {
                    case 0:
                        glBlendFunc(GL_DST_COLOR, GL_ONE);           // normal light redder lava
                        break;
                    case 1:
                        glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE); // normal glow
                        break;
                    case 2:
                        glBlendFunc(GL_ONE, GL_ONE);                 // yellow glow
                        break;
                    case 3:
                        glBlendFunc(GL_SRC_COLOR, GL_ONE);           // orange glow
                        break;
                }
#endif
                /*
                 * Too far away from the player? Skip rendering.
                 */
                if (game.state.player) {
                    auto p = game.state.player;
                    auto len = DISTANCE(l->at.x, l->at.y, p->at.x, p->at.y);

                    if (len > TILES_ACROSS + l->strength) {
                        continue;
                    }
                }

                l->render(fbo);
            }
        }
    }
    blit_flush();
    glcolor(WHITE);
}

void lights_render_player (int minx, int miny, int maxx, int maxy, int fbo)
{
    if (!game.state.player) {
        return;
    }

    for (auto y = miny; y < maxy; y++) {
        for (auto x = maxx - 1; x >= minx; x--) {
            for (auto p : game.state.map.lights[x][y]) {
                auto l = p.second;

                if (l->quality != LIGHT_QUALITY_HIGH) {
                    continue;
                }

                l->render(fbo);
            }
        }
    }
}

void lights_render_debug (int minx, int miny, int maxx, int maxy)
{
    for (auto y = miny; y < maxy; y++) {
        for (auto x = maxx - 1; x >= minx; x--) {
            for (auto p : game.state.map.lights[x][y]) {
                auto l = p.second;

                if (l->quality == LIGHT_QUALITY_POINT) {
                    continue;
                }

                /*
                 * Too far away from the player? Skip rendering.
                 */
                if (game.state.player) {
                    auto p = game.state.player;
                    auto len = DISTANCE(l->at.x, l->at.y, p->at.x, p->at.y);

                    if (len > TILES_ACROSS + l->strength) {
                        continue;
                    }
                }

                l->render_debug(minx, miny, maxx, maxy);
            }
        }
    }
}
