//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_gl.h"
#include "my_tex.h"
#include "my_thing.h"

Thingp debug_thing;

static Texp light_overlay_tex;
static int light_overlay_texid;
static float light_dim = 1.0;
#undef DEBUG_LIGHT

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
                  fpoint offset,
                  float strength,
                  color col)
{_
    uint16_t max_light_rays;
    if (owner->is_player()) {
        max_light_rays = MAX_LIGHT_RAYS;
    } else {
        max_light_rays = MAX_LIGHT_RAYS / 16;
        max_light_rays = 32;
        max_light_rays = std::max(8, (int)max_light_rays);
    }

    auto l = new Light(); // std::make_shared< class Light >();

    l->at             = at;
    l->offset         = offset;
    l->strength       = strength;
    l->owner          = owner;
    l->col            = col;
    l->max_light_rays = max_light_rays;

    l->ray.resize(max_light_rays);
    std::fill(l->ray.begin(), l->ray.end(), Ray{0});

    //
    // First generate the right ray lengths.
    //
    float dr = RAD_360 / (float) max_light_rays;
    for (auto i = 0; i < max_light_rays; i++) {
        auto r = &getref(l->ray, i);
        float rad = dr * (float)i;
        sincosf(rad, &r->sinr, &r->cosr);
    }

    //log("created");
    return (l);
}

void Light::destroy (void)
{_
}

void Light::calculate (int last)
{
    //
    // We precalculate the walls a light hits partly for efficency but also
    // to avoid lighting walls behind those immediately visible to us. To
    // do this we do a flood fill of the level and pick the nearest walls.
    //
    static std::array<std::array<uint16_t, MAP_HEIGHT>, MAP_WIDTH> is_nearest_wall = {};
    static uint16_t is_nearest_wall_val;
    is_nearest_wall_val++;

    verify(this);
    cached_gl_cmds.clear();

    auto light_radius = strength;
    auto visible_width = light_radius + 1;
    auto visible_height = light_radius + 1;

    auto light_pos = at + fpoint(0.5, 0.5) + offset;

    int16_t maxx = light_pos.x + visible_width;
    int16_t minx = light_pos.x - visible_width;
    int16_t maxy = light_pos.y + visible_height;
    int16_t miny = light_pos.y - visible_height;

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

    //
    // Walk the light rays in a circle. First pass is to find the nearest
    // walls.
    //
    bool do_set_visited = (level->player && (owner == level->player));
    float step_delta1 = 0.02;
    float step_delta2 = 0.05;

    for (int i = 0; i < max_light_rays; i++) {
        auto r = &getref(ray, i);
        float step = 0.0;
        for (; step < strength; step += step_delta1) {
            float rad = step;
            float p1x = light_pos.x + r->cosr * rad;
            float p1y = light_pos.y + r->sinr * rad;

            int x = (int)p1x;
            int y = (int)p1y;

            if (unlikely(level->is_oob(x, y))) {
                continue;
            }

            if (do_set_visited) {
                level->set_visited_unsafe(x, y);
            }

            if (level->is_gfx_large_shadow_unsafe(x, y)) {
                break;
            }
        }

        r->depth_closest = step;

        //
        // Let the light leak in a little bit. This handles corners so that
        // a point hitting on or near a corner will light the corner tile.
        //
        float step2 = step;
        for (; step2 < step + 0.5; step2 += step_delta2) {
            float rad = step2;
            float p1x = light_pos.x + r->cosr * rad;
            float p1y = light_pos.y + r->sinr * rad;

            int x = (int)p1x;
            int y = (int)p1y;

            if (unlikely(level->is_oob(x, y))) {
                continue;
            }

            if (do_set_visited) {
                level->set_visited_unsafe(x, y);
            }

            if (!level->is_gfx_large_shadow_unsafe(x, y)) {
                break;
            }

            set_unsafe(is_nearest_wall, x, y, is_nearest_wall_val);
        }
    }

    //
    // Now for light penetrating into rock. We stop a bit short due to the
    // fuzzing of the light we do when rendering, to avoid light leaking into
    // tiles we should not see.
    //
    // Cannot merge these two loops as we depend on is_nearest_wall being set
    // for all tiles first.
    //
    {
        for (int i = 0; i < max_light_rays; i++) {
            auto r = &getref(ray, i);
            float radius = r->depth_closest;
            float fade = pow(strength - radius, 0.05);
            float step = 0.0;
            for (; step < 1.0; step += step_delta2) {
                fade *= 0.90;
                if (fade < 0.0001) {
                    break;
                }

                float rad = radius + 0.0 + step;
                float p1x = light_pos.x + r->cosr * rad;
                float p1y = light_pos.y + r->sinr * rad;

                int x = (int)p1x;
                int y = (int)p1y;

                if (unlikely(level->is_oob(x, y))) {
                    continue;
                }

                if (do_set_visited) {
                    level->set_visited_unsafe(x, y);
                }

                if (get_unsafe(is_nearest_wall, x, y) != is_nearest_wall_val) {
                    break;
                }
            }

            r->depth_furthest = r->depth_closest + step;
            if (r->depth_furthest < 0.0001) {
                r->depth_furthest = strength;
            }
        }
    }
}

void Light::render_triangle_fans (int last, int count)
{
    spoint blit_tl, blit_br;
    Tilep tile = {};
    if (!owner->get_pre_effect_map_offset_coords(blit_tl, blit_br, tile, 
                                                 false)) {
        return;
    }

    spoint sz = blit_tl - blit_br;
    if (sz.x < 0) { sz.x = -sz.x; }
    if (sz.y < 0) { sz.y = -sz.x; }
    spoint light_pos = (blit_tl + blit_br) / 2;
    float tilew = game->config.tile_pix_width;
    float tileh = game->config.tile_pix_height;
    light_pos.x += offset.x * tilew;
    light_pos.y += offset.y * tileh;

    auto light_offset = light_pos - cached_light_pos;

#ifdef DEBUG_LIGHT
    blit_fbo_bind(FBO_MAP);
    color c = RED;
    c.a = 150;
#if 0
    glcolor(c);
    gl_blitline(blit_tl.x, blit_tl.y, blit_br.x, blit_tl.y);
    gl_blitline(blit_tl.x, blit_tl.y, blit_tl.x, blit_br.y);
    gl_blitline(blit_br.x, blit_br.y, blit_br.x, blit_tl.y);
    gl_blitline(blit_br.x, blit_br.y, blit_tl.x, blit_br.y);
    gl_blitline(blit_tl.x, blit_tl.y, light_pos.x, light_pos.y);
    gl_blitline(blit_br.x, blit_tl.y, light_pos.x, light_pos.y);
    gl_blitline(blit_tl.x, blit_br.y, light_pos.x, light_pos.y);
    gl_blitline(blit_br.x, blit_br.y, light_pos.x, light_pos.y);
#endif

    c = GREEN;
    c.a = 150;
    glcolor(c);

    if (1) {
#else
    if (!cached_gl_cmds.size()) {
#endif
        auto c = col;
        uint8_t red   = c.r;
        uint8_t green = c.g;
        uint8_t blue  = c.b;
        uint8_t alpha = c.a;

        cached_light_pos = light_pos;

        red *= light_dim;
        green *= light_dim;
        blue *= light_dim;
        alpha *= 1.0 / (float)count;

        blit_init();
        {
            int i;

            //
            // Walk the light rays in a circle.
            //
            push_point(light_pos.x, light_pos.y, red, green, blue, alpha);

            //
            // Non player lights fade
            //
            if (level->player && (owner != level->player)) {
                alpha = 0.0;
            }

            for (i = 0; i < max_light_rays; i++) {
                auto r = &getref(ray, i);
                float radius = r->depth_furthest;
                float p1x = light_pos.x + r->cosr * radius * tilew;
                float p1y = light_pos.y + r->sinr * radius * tileh;

                push_point(p1x, p1y, red, green, blue, alpha);
#ifdef DEBUG_LIGHT
                gl_blitline(light_pos.x, light_pos.y, p1x, p1y);
#endif
            }

            //
            // Complete the circle with the first point again.
            //
            i = 0; {
                auto r = &getref(ray, i);
                float radius = r->depth_furthest;
                float p1x = light_pos.x + r->cosr * radius * tilew;
                float p1y = light_pos.y + r->sinr * radius * tileh;

                push_point(p1x, p1y, red, green, blue, alpha);
#ifdef DEBUG_LIGHT
                gl_blitline(light_pos.x, light_pos.y, p1x, p1y);
#endif
            }
        }

        auto sz = bufp - gl_array_buf;
        cached_gl_cmds.resize(sz);
        std::copy(gl_array_buf, bufp, cached_gl_cmds.begin());
#ifndef DEBUG_LIGHT
        blit_flush_triangle_fan();
        //
        // Makes non player lights more intense
        //
        if (level->player && (owner != level->player)) {
            blit_flush_triangle_fan();
            blit_flush_triangle_fan();
            blit_flush_triangle_fan();
        }
#endif
    } else {
        float *b = &(*cached_gl_cmds.begin());
        float *e = &(*cached_gl_cmds.end());

        glTranslatef(light_offset.x, light_offset.y, 0);

        //
        // Lights glow more with more blends
        //
        blit_flush_triangle_fan(b, e);

        //
        // Makes non player lights more intense
        //
        if (level->player && (owner != level->player)) {
            blit_flush_triangle_fan(b, e);
            blit_flush_triangle_fan(b, e);
            blit_flush_triangle_fan(b, e);
        }
        glTranslatef(-light_offset.x, -light_offset.y, 0);
    }

    //
    // Blend a texture on top of all the above blending so we get smooth
    // fade off of the light.
    //
    if (last && (level->player && (owner == level->player))) {
        if (flicker > random_range(20, 30)) {
            flicker = 0;
        }

        if (!flicker) {
            flicker_radius = strength *
                            (1.0 + ((float)(random_range(0, 10) / 100.0)));
        }
        flicker++;

        float lw = flicker_radius * tilew;
        float lh = flicker_radius * tileh;
        float p1x = light_pos.x - lw;
        float p1y = light_pos.y - lh;
        float p2x = light_pos.x + lw;
        float p2y = light_pos.y + lh;

        glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA); // hard black light

        blit_init();
        glTranslatef(light_offset.x, light_offset.y, 0);
        blit(light_overlay_texid, 0, 0, 1, 1, p1x, p1y, p2x, p2y);
        glTranslatef(-light_offset.x, -light_offset.y, 0);
        blit_flush();
   }
}

void Light::render (int fbo, int last, int count)
{
    if (!light_overlay_tex) {
        light_overlay_tex = tex_load("", "light", GL_LINEAR);
        light_overlay_texid = tex_get_gl_binding(light_overlay_tex);
    }

    render_triangle_fans(last, count);
}

void lights_render (int minx, int miny, int maxx, int maxy, int fbo)
{
    light_dim = 1.0;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    if (player) {
        auto lc = player->get_light_count();
        size_t c = 0;
        for (auto l : player->get_light()) {
            l->render(fbo, (c == lc - 1), lc);
            c++;
        }
    }

    glBlendFunc(GL_ZERO, GL_ONE); // good
#if 0
extern int vals[];
extern std::string vals_str[];
extern int g_blend_a;
extern int g_blend_b;
CON("glBlendFunc(%s, %s)", vals_str[g_blend_a].c_str(), vals_str[g_blend_b].c_str());
glBlendFunc(vals[g_blend_a], vals[g_blend_b]);
#endif
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_LIGHTS_AT_DEPTH(level, t, x, y) {
                for (auto& l : t->get_light()) {
                    if (level->player && (l->owner == level->player)) {
                        continue;
                    }

                    //
                    // Too far away from the player? Skip rendering.
                    //
                    light_dim = 1.0;

                    if (level->player) {
                        auto p = level->player;
                        auto len = DISTANCE(l->at.x, l->at.y,
                                            p->mid_at.x, p->mid_at.y);
                        if (len > MAX_LIGHT_PLAYER_DISTANCE + l->strength) {
                            continue;
                        }

                        auto dist =
                          thing_can_reach_player(point(l->at.x, l->at.y));
                        if (dist >= MAX_LIGHT_PLAYER_DISTANCE) {
                            continue;
                        }

                        if (!dist) {
                            continue;
                        }

                        if (dist > 0) {
                            light_dim = 1.0 - (0.05 * (float)dist);
                            if (light_dim <= 0) {
                                continue;
                            }
                        }
                    }

                    l->render(fbo, false, 1);
                }
            } FOR_ALL_THINGS_END()
        }
    }
}
