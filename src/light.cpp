/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_gl.h"

static Texp light_overlay_tex_diffuse;
static Texp light_overlay_tex_focused;
static int light_overlay_texid_diffuse;
static int light_overlay_texid_focused;
static int light_overlay_texid;
static const int LIGHT_VISIBLE_DIST = TILES_ACROSS + TILES_ACROSS / 2;

#define LIGHT_FOCUSED 0
#define LIGHT_DIFFUSE 1

Thingp debug_thing;

Light::Light (void)
{_
    newptr(this, "Light");
}

Light::~Light (void)
{_
    verify(this);
    if (is_being_destroyed) {
        die("death recursion");
    }
    is_being_destroyed = true;
    destroy();
    oldptr(this);
}

Lightp light_new (Thingp owner,
                  fpoint at,
                  double strength,
                  LightQuality quality,
                  color col)
{_
    uint16_t max_light_rays;
    if (owner->is_player()) {
        max_light_rays = MAX_LIGHT_RAYS;
    } else {
        max_light_rays = MAX_LIGHT_RAYS / 8;
    }

    auto l = new Light(); // std::make_shared< class Light >();

    point new_at((int)at.x, (int)at.y);

    l->at             = at;
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
        auto r = &getref(l->ray, i);
        double rad = dr * (double)i;
        sincos(rad, &r->sinr, &r->cosr);
    }

    //log("created");
    return (l);
}

void Light::destroy (void)
{_
}

void Light::calculate (void)
{
    //
    // We precalculate the walls a light hits partly for efficency but also
    // to avoid lighting walls behind those immediately visible to us. To
    // do this we do a flood fill of the level and pick the nearest walls.
    //
    static std::array<std::array<uint32_t, MAP_HEIGHT>, MAP_WIDTH> is_nearest_wall = {};
    static uint32_t is_nearest_wall_val;
    is_nearest_wall_val++;

    verify(this);
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
    for (int i = 0; i < max_light_rays; i++) {
        auto r = &getref(ray, i);
        double step = 0.0;
        for (; step < strength; step += 0.01) {
            double rad = step;
            double p1x = at.x + r->cosr * rad;
            double p1y = at.y + r->sinr * rad;

            int x = (int)p1x;
            int y = (int)p1y;

            if (unlikely(world->is_oob(x, y))) {
                continue;
            }

            if (world->is_gfx_large_shadow_caster(x, y)) {
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

            if (unlikely(world->is_oob(x, y))) {
                continue;
            }

            if (!world->is_gfx_large_shadow_caster(x, y)) {
                break;
            }

            set(is_nearest_wall, x, y, is_nearest_wall_val);
        }
    }

    /*
     * Now for light penetrating into rock. We stop a bit short due to the
     * fuzzing of the light we do when rendering, to avoid light leaking into
     * tiles we should not see.
     *
     * Cannot merge these two loops as we depend on is_nearest_wall being set
     * for all tiles first.
     */
    for (int i = 0; i < max_light_rays; i++) {
        auto r = &getref(ray, i);
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

            if (unlikely(world->is_oob(x, y))) {
                continue;
            }

            if (get(is_nearest_wall, x, y) != is_nearest_wall_val) {
                break;
            }
        }

        r->depth_furthest = r->depth_closest + step;
        if (r->depth_furthest < 0.001) {
            r->depth_furthest = strength;
        }
    }
#if 0
    for (int i = 0; i < max_light_rays; i++) {
        auto r = &getref(ray, i);
        printf("%f ", r->depth_furthest);
    }
printf("\n");
#endif
}

void Light::render_triangle_fans (void)
{
    static const double tile_gl_width_pct = 1.0 / (double)TILES_ACROSS;
    static const double tile_gl_height_pct = 1.0 / (double)TILES_DOWN;

    auto tx = at.x + 0.5;
    auto ty = at.y + 0.5;
    fpoint light_pos(tx * game->config.tile_gl_width,
                     ty * game->config.tile_gl_height);

    auto ox = world->map_at.x * game->config.tile_gl_width;
    auto oy = world->map_at.y * game->config.tile_gl_height;

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
                auto r = &getref(ray, i);
                double radius = r->depth_furthest;
                double p1x = light_pos.x + r->cosr * radius * tile_gl_width_pct;
                double p1y = light_pos.y + r->sinr * radius * tile_gl_height_pct;

                push_point(p1x, p1y, red, green, blue, alpha);
            }

            /*
             * Complete the circle with the first point again.
             */
            i = 0; {
                auto r = &getref(ray, i);
                double radius = r->depth_furthest;
                double p1x = light_pos.x + r->cosr * radius * tile_gl_width_pct;
                double p1y = light_pos.y + r->sinr * radius * tile_gl_height_pct;

                push_point(p1x, p1y, red, green, blue, alpha);
            }
        }

        auto sz = bufp - gl_array_buf;
        glbuf.resize(sz);
        std::copy(gl_array_buf, bufp, glbuf.begin());
        blit_flush_triangle_fan();
    } else {
        float *b = &(*glbuf.begin());
        float *e = &(*glbuf.end());
        blit_flush_triangle_fan(b, e);
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
        glBlendFunc(GL_ZERO, GL_SRC_ALPHA); // hard black light
        // glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR); // soft shadows
        blit(light_overlay_texid, 0, 0, 1, 1, p1x, p1y, p2x, p2y);
        blit_flush();
   }
   glTranslatef(ox, oy, 0);
}

void Light::render_point_light (void)
{
    auto tx = at.x;
    auto ty = at.y;
    fpoint light_pos(tx * game->config.tile_gl_width,
                     ty * game->config.tile_gl_height);

    auto ox = world->map_at.x * game->config.tile_gl_width;
    auto oy = world->map_at.y * game->config.tile_gl_height;

    double lw = strength * game->config.tile_gl_width;
    double lh = strength * game->config.tile_gl_height;
    double p1x = light_pos.x - lw;
    double p1y = light_pos.y - lh;
    double p2x = light_pos.x + lw;
    double p2y = light_pos.y + lh;

    glcolor(col);
    blit(light_overlay_texid, 0, 0, 1, 1, p1x - ox, p1y - oy, p2x - ox, p2y - oy);
}

void Light::render (int fbo, int pass)
{
    if (flicker > random_range(10, 20)) {
        flicker = 0;
    }

    if (!flicker) {
        flicker_radius = strength *
                        (1.0 + ((double)(random_range(0, 100) / 1000.0)));
    }
    flicker++;

    if (!light_overlay_tex_diffuse) {
        light_overlay_tex_diffuse = tex_load("", "light", GL_LINEAR);
        light_overlay_texid_diffuse = tex_get_gl_binding(light_overlay_tex_diffuse);
    }
    if (!light_overlay_tex_focused) {
        light_overlay_tex_focused = tex_load("", "light", GL_LINEAR);
        light_overlay_texid_focused = tex_get_gl_binding(light_overlay_tex_focused);
    }

    if (pass == LIGHT_FOCUSED) {
        light_overlay_texid = light_overlay_texid_focused;
    } else {
        light_overlay_texid = light_overlay_texid_diffuse;
    }

    static const color dull = { 255, 255, 255, 50 };

    switch (quality) {
    case LIGHT_QUALITY_LOW:
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
        if (quality == LIGHT_QUALITY_LOW) {
            glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_SRC_COLOR);
        } else {
            glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
        }

        render_triangle_fans();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        blit_fbo_bind(fbo);
        blit_init();
        blit(get(fbo_tex_id, FBO_LIGHT_MASK),
                 0.0, 1.0, 1.0, 0.0,  0.01,  0.01, 0.99, 0.99);
        blit_flush();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glcolor(dull);
        blit_init();
        blit(get(fbo_tex_id, FBO_LIGHT_MASK),
                 0.0, 1.0, 1.0, 0.0, -0.05, -0.05, 1.05, 1.05);
        blit_flush();

        blit_fbo_unbind();

        break;

    case LIGHT_QUALITY_POINT:
        render_point_light();
        break;

    default:
        ERR("unknown light quality");
    }
}

void lights_render_points (int minx, int miny, int maxx, int maxy, 
                           int fbo, int pass)
{
    bool have_low_quality = false;

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_LIGHT_SOURCE_THINGS(world, t, x, y) {
                auto l = t->get_light();
                if (l->quality == LIGHT_QUALITY_POINT) {
                    continue;
                }

                /*
                 * Too far away from the player? Skip rendering.
                 */
                if (world->player) {
                    auto p = world->player;
                    auto len = DISTANCE(l->at.x, l->at.y,
                                        p->mid_at.x, p->mid_at.y);

                    if (len > LIGHT_VISIBLE_DIST + l->strength) {
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
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_LIGHT_SOURCE_THINGS(world, t, x, y) {
                auto l = t->get_light();
                if (l->quality != LIGHT_QUALITY_LOW) {
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
                if (world->player) {
                    auto p = world->player;
                    auto len = DISTANCE(l->at.x, l->at.y,
                                        p->mid_at.x, p->mid_at.y);

                    if (len > LIGHT_VISIBLE_DIST + l->strength) {
                        continue;
                    }
                }

                l->render(fbo, pass);
            }
        }
    }
    blit_flush();
    glcolor(WHITE);
}

void lights_render_high_quality (int minx, int miny, 
                                 int maxx, int maxy, int fbo)
{
    Lightp deferred = nullptr;

    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_LIGHT_SOURCE_THINGS(world, t, x, y) {
                auto l = t->get_light();
                if (l->quality != LIGHT_QUALITY_HIGH) {
                    continue;
                }

                if (world->player && (l->owner == world->player)) {
                    deferred = l;
                    continue;
                }

                /*
                 * Too far away from the player? Skip rendering.
                 */
                if (world->player) {
                    auto p = world->player;
                    auto len = DISTANCE(l->at.x, l->at.y,
                                        p->mid_at.x, p->mid_at.y);

                    if (len > LIGHT_VISIBLE_DIST + l->strength) {
                        continue;
                    }
                }

//                l->render(fbo, LIGHT_DIFFUSE);
                l->render(fbo, LIGHT_FOCUSED);
            }
        }
    }

    if (deferred) {
//        deferred->render(fbo, LIGHT_DIFFUSE);
        deferred->render(fbo, LIGHT_FOCUSED);
    }
}
