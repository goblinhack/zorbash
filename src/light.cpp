//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_tex.h"
#include "my_level.h"
#include "my_light.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ptrcheck.h"

static Texp g_light_overlay_tex;
static int g_light_overlay_texid;

static Texp g_glow_overlay_tex;
static int g_glow_overlay_texid;

Light::Light (void)
{_
    newptr(this, "Light");
}

Light::~Light (void)
{_
    verify(this);
    if (is_being_destroyed) {
        die("Death recursion");
    }
    is_being_destroyed = true;
    destroy();
    oldptr(this);
}

void Light::draw_pixel (int16_t index, const point &p0, const point &p1)
{
    RayPoint r;
    r.p = p1;
    r.distance = DISTANCE(p0.x, p0.y, p1.x, p1.y);
    points[index].push_back(r);
}

// http://www.edepot.com/linee.html
void Light::draw_line (int16_t index, const point &p0, const point &p1)
{
    points[index].resize(0);

    const point start = p0; 
    auto x = p0.x;
    auto y = p0.y;
    auto x2 = p1.x;
    auto y2 = p1.y;

    bool yLonger=false;
    int shortLen=y2-y;
    int longLen=x2-x;
    if (abs(shortLen)>abs(longLen)) {
	int swap=shortLen;
	shortLen=longLen;
	longLen=swap;				
	yLonger=true;
    }
    int decInc;
    if (longLen==0) decInc=0;
    else decInc = (shortLen << 16) / longLen;

    if (yLonger) {
	if (longLen>0) {
	    longLen+=y;
	    for (int j=0x8000+(x<<16);y<=longLen;++y) {
		draw_pixel(index, start, point(j >> 16, y));	
		j+=decInc;
	    }
	    return;
	}
	longLen+=y;
	for (int j=0x8000+(x<<16);y>=longLen;--y) {
	    draw_pixel(index, start, point(j >> 16, y));	
	    j-=decInc;
	}
	return;	
    }

    if (longLen>0) {
	longLen+=x;
	for (int j=0x8000+(y<<16);x<=longLen;++x) {
	    draw_pixel(index, start, point(x, j >> 16));
	    j+=decInc;
	}
	return;
    }
    longLen+=x;
    for (int j=0x8000+(y<<16);x>=longLen;--x) {
	draw_pixel(index, start, point(x, j >> 16));
	j-=decInc;
    }
}

Lightp light_new (Thingp owner,
                  point offset,
                  int strength,
                  color col,
                  int fbo)
{_
    auto l = new Light(); // std::make_shared< class Light >();

    l->offset         = offset;
    l->orig_strength  = strength;
    l->owner          = owner;
    l->col            = col;
    l->fbo            = fbo;

    l->update();

    //log("Created");
    return (l);
}

void Light::update (void)
{_
    level    = owner->level;
    strength = orig_strength * TILE_WIDTH;

    max_light_rays = LIGHT_MAX_RAYS;

    ray.resize(max_light_rays);
    std::fill(ray.begin(), ray.end(), Ray{0});

    //
    // First generate the right ray lengths.
    //
    float dr = RAD_360 / (float) max_light_rays;
    for (auto i = 0; i < max_light_rays; i++) {
        double cosr, sinr;
        sincos(dr * i, &sinr, &cosr);
        draw_line(i, point(0, 0), point(strength * cosr, strength * sinr));
    }
}

void Light::destroy (void)
{_
}

void Light::reset (void)
{
    cached_gl_cmds.clear();
    cached_pixel_map_at = point(-1, -1);
    cached_light_pos = point(-1, -1);
}

bool Light::calculate (int first)
{
    auto player = level->player;
    if (!player) {
        return false;
    }

    if (!player->is_blitted) {
        return false;
    }

    //
    // This stops lighting things up when moving to the player on a new level
    //
    if (!player->is_jumping) {
        if (player->is_hidden) {
            return false;
        }
    }

    point light_pos = owner->last_blit_at + offset;

    if (cached_light_pos == light_pos) {
        if (cached_pixel_map_at == level->pixel_map_at) {
            return true;
        }
    }

    cached_gl_cmds.clear();
    cached_pixel_map_at = level->pixel_map_at;
    cached_light_pos = light_pos;

    //
    // Slighly insane optimization
    //
    uint8_t last_x;
    uint8_t last_y;

#define AVOID_LOOKING_AT_THE_SAME_TILE()               \
    {                                                  \
        if (likely((x == last_x) && (y == last_y))) {  \
            rp++;                                      \
            continue;                                  \
        }                                              \
        last_x = x; last_y = y;                        \
    }

#define AVOID_LOOKING_AT_THE_SAME_TILE2()              \
    {                                                  \
        if (likely((x == last_x) && (y == last_y))) {  \
            rp++;                                      \
            step2++;                                   \
            continue;                                  \
        }                                              \
        last_x = x; last_y = y;                        \
    }

    //
    // Walk the light rays in a circle. Find the nearest walls and then let
    // the light leak a little.
    //
    auto d = (strength / TILE_WIDTH) + 1;
    if (likely(((player->mid_at.x >= d) &&
                (player->mid_at.x <= MAP_WIDTH - d) &&
                (player->mid_at.y >= d) &&
                (player->mid_at.y <= MAP_HEIGHT - d)))) {
        if (first) {
            for (int16_t i = 0; i < max_light_rays; i++) {
                auto r = &getref_no_check(ray, i);
                int16_t step = 0;
                const int16_t end_of_points = static_cast<uint16_t>(points[i].size() - 1);
                auto rp = points[i].begin();
                last_x = -1;
                for (; ; step++) {
                    if (unlikely(step >= end_of_points)) { break; }
                    if (unlikely(rp->distance > strength)) { break; }
                    const int16_t p1x = light_pos.x + rp->p.x;
                    const int16_t p1y = light_pos.y + rp->p.y;
                    const uint8_t x = p1x / TILE_WIDTH;
                    const uint8_t y = p1y / TILE_HEIGHT;

                    AVOID_LOOKING_AT_THE_SAME_TILE()
                    level->set_visited_no_check(x, y); // for AI and jumping
                    level->set_is_lit_no_check(x, y); // allows lights to fade
                    rp++;

                    if (level->is_light_blocker_no_check(x, y)) {
                        //
                        // We hit a wall. Keep walking until we exit the wall or
                        // we reach the light limit.
                        //
                        int16_t step2 = step;
                        for (;;) {
                            if (unlikely(step2 >= end_of_points)) { break; }
                            if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) { break; }
                            const int16_t p1x = light_pos.x + rp->p.x;
                            const int16_t p1y = light_pos.y + rp->p.y;
                            const uint8_t x = p1x / TILE_WIDTH;
                            const uint8_t y = p1y / TILE_HEIGHT;
                            AVOID_LOOKING_AT_THE_SAME_TILE2()
                            if (!level->is_light_blocker_no_check(x, y)) { break; }
                            rp++;
                            step2++;
                        }
                        step = step2;
                        break;
                    }
                }
                r->depth_furthest = step;
            }
        } else {
            for (int16_t i = 0; i < max_light_rays; i++) {
                auto r = &getref_no_check(ray, i);
                int16_t step = 0;
                const int16_t end_of_points = static_cast<uint16_t>(points[i].size() - 1);
                auto rp = points[i].begin();
                last_x = -1;
                for (; ; step++) {
                    if (unlikely(step >= end_of_points)) { break; }
                    if (unlikely(rp->distance > strength)) { break; }
                    const int16_t p1x = light_pos.x + rp->p.x;
                    const int16_t p1y = light_pos.y + rp->p.y;
                    const uint8_t x = p1x / TILE_WIDTH;
                    const uint8_t y = p1y / TILE_HEIGHT;

                    AVOID_LOOKING_AT_THE_SAME_TILE()
                    rp++;

                    if (level->is_light_blocker_no_check(x, y)) {
                        //
                        // We hit a wall. Keep walking until we exit the wall or
                        // we reach the light limit.
                        //
                        int16_t step2 = step;
                        for (;;) {
                            if (unlikely(step2 >= end_of_points)) { break; }
                            if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) { break; }
                            const int16_t p1x = light_pos.x + rp->p.x;
                            const int16_t p1y = light_pos.y + rp->p.y;
                            const uint8_t x = p1x / TILE_WIDTH;
                            const uint8_t y = p1y / TILE_HEIGHT;
                            AVOID_LOOKING_AT_THE_SAME_TILE2()
                            if (!level->is_light_blocker_no_check(x, y)) { break; }
                            rp++;
                            step2++;
                        }
                        step = step2;
                        break;
                    }
                }
                r->depth_furthest = step;
            }
        }
    } else {
        for (int16_t i = 0; i < max_light_rays; i++) {
            auto r = &getref_no_check(ray, i);
            int16_t step = 0;
            const int16_t end_of_points = static_cast<uint16_t>(points[i].size() - 1);
            auto rp = points[i].begin();
            last_x = -1;
            for (; ; step++) {
                if (step >= end_of_points) { break; }
                if (rp->distance > strength) { break; }
                const int16_t p1x = light_pos.x + rp->p.x;
                const int16_t p1y = light_pos.y + rp->p.y;
                const uint8_t x = (p1x / TILE_WIDTH) % MAP_WIDTH;
                const uint8_t y = (p1y / TILE_HEIGHT) % MAP_HEIGHT;

                AVOID_LOOKING_AT_THE_SAME_TILE()
                if (level->is_oob(x, y)) { break; }
                level->set_visited(x, y); // for AI and jumping
                level->set_is_lit(x, y); // allows lights to fade
                rp++;

                if (level->is_light_blocker(x, y)) {
                    //
                    // We hit a wall. Keep walking until we exit the wall or
                    // we reach the light limit.
                    //
                    int16_t step2 = step;
                    for (;;) {
                        if (step2 >= end_of_points) { break; }
                        if (rp->distance > step + TILE_WIDTH + offset.x + offset.y) { break; }
                        const int16_t p1x = light_pos.x + rp->p.x;
                        const int16_t p1y = light_pos.y + rp->p.y;
                        const uint8_t x = (p1x / TILE_WIDTH) % MAP_WIDTH;
                        const uint8_t y = (p1y / TILE_HEIGHT) % MAP_HEIGHT;
                        AVOID_LOOKING_AT_THE_SAME_TILE2()
                        if (level->is_oob(x, y)) { break; }
                        if (!level->is_light_blocker(x, y)) { break; }
                        rp++;
                        step2++;
                    }
                    step = step2;
                    break;
                }
            }
            r->depth_furthest = step;
        }
    }

    return true;
}

void Light::render_triangle_fans (int first)
{
    point light_pos = owner->last_blit_at;

    if (fbo == FBO_FULLMAP_LIGHT) {
        light_pos = cached_light_pos;
        gl_enter_2d_mode(MAP_WIDTH * TILE_WIDTH, MAP_HEIGHT * TILE_HEIGHT);
    } else if (fbo == FBO_PLAYER_LIGHT) {
        light_pos -= level->pixel_map_at  - offset;
    } else {
        return;
    }

    if (offset != point(0, 0)) {
        static color l(255, 255, 255, 50);
        glcolor(l);
    } else {
        glcolor(WHITE);
    }

    if (!cached_gl_cmds.size()) {
        blit_init();
        {
            int i;

            //
            // Walk the light rays in a circle.
            //
            push_point(light_pos.x, light_pos.y);

            for (i = 0; i < max_light_rays; i++) {
                auto r = &getref_no_check(ray, i);
                point &p = points[i][r->depth_furthest].p;
                int16_t p1x = light_pos.x + p.x;
                int16_t p1y = light_pos.y + p.y;
                push_point(p1x, p1y);
            }

            //
            // Complete the circle with the first point again.
            //
            i = 0; {
                auto r = &getref_no_check(ray, i);
                point &p = points[i][r->depth_furthest].p;
                int16_t p1x = light_pos.x + p.x;
                int16_t p1y = light_pos.y + p.y;
                push_point(p1x, p1y);
            }
        }

        auto sz = bufp - gl_array_buf;
        cached_gl_cmds.resize(sz);
        std::copy(gl_array_buf, bufp, cached_gl_cmds.begin());
        blit_flush_triangle_fan();
    } else {
        auto *b = &(*cached_gl_cmds.begin());
        auto *e = &(*cached_gl_cmds.end());
        auto light_offset = cached_pixel_map_at - level->pixel_map_at;
        glTranslatef(light_offset.x, light_offset.y, 0);
        blit_flush_triangle_fan(b, e);
        glTranslatef(-light_offset.x, -light_offset.y, 0);
    }

    if (fbo == FBO_FULLMAP_LIGHT) {
        gl_enter_2d_mode(game->config.game_pix_width, 
                         game->config.game_pix_height);
    }
}

void Light::render (int first)
{
    if (!g_light_overlay_tex) {
        g_light_overlay_tex = tex_load("", "light", GL_NEAREST);
        g_light_overlay_texid = tex_get_gl_binding(g_light_overlay_tex);
    }

    if (!g_glow_overlay_tex) {
        g_glow_overlay_tex = tex_load("", "glow", GL_NEAREST);
        g_glow_overlay_texid = tex_get_gl_binding(g_glow_overlay_tex);
    }

    if (!calculate(first)) {
        return;
    }
    render_triangle_fans(first);
}

void Level::lights_render (int minx, int miny, int maxx, int maxy,
                           int fbo)
{_
    if (player) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        bool first = true;
        player->light_update_strength();
        for (auto l : player->get_light()) {
            if (l->fbo == fbo) {
                l->render(first);
                first = false;
            }
        }
    }

    if (fbo != FBO_SMALL_LIGHTS) {
        return;
    }

    //
    // Blit a dark background which we will fill with lights
    //
    glClear(GL_COLOR_BUFFER_BIT);
    if (is_sewer_level) {
        glColor4ub(0,0,0,220);
    } else {
        glColor4ub(0,0,0,180);
    }
    glBlendFunc(GL_ONE, GL_ZERO);
    glDisable(GL_TEXTURE_2D);
    gl_blitquad(0, 0, 
                game->config.game_pix_width, game->config.game_pix_height);
    glEnable(GL_TEXTURE_2D);
    glcolor(WHITE);

    //
    // Draw small light sources
    //
    glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);

    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_LIGHTS_AT_DEPTH(this, t, x, y) {
                for (auto& l : t->get_light()) {

                    if (player && (l->owner == player)) {
                        if (l->fbo != fbo) {
                            continue;
                        }
                    }

                    if (!is_lit_no_check(t->mid_at.x, t->mid_at.y)) {
                        continue;
                    }

                    auto t = l->owner;
                    point blit_tl, blit_br;
                    Tilep tile = {};

                    if (!t->get_map_offset_coords(blit_tl, blit_br, tile, false)) {
                        continue;
                    }

                    auto mid = (blit_br + blit_tl) / 2;
                    auto s = l->strength;
                    auto tlx = mid.x - s;
                    auto tly = mid.y - s;
                    auto brx = mid.x + s;
                    auto bry = mid.y + s;
                    color c = l->col;
                    glcolor(c);
                    blit(g_light_overlay_texid, 0, 0, 1, 1, tlx, tly, brx, bry);
                }
            } FOR_ALL_THINGS_END()
        }
    }
    blit_flush();

    //
    // Add glow to light sources
    //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
    blit_init();
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            FOR_ALL_LIGHTS_AT_DEPTH(this, t, x, y) {
                for (auto& l : t->get_light()) {

                    if (!t->gfx_glows()) {
                        continue;
                    }

                    if (!is_lit_no_check(t->mid_at.x, t->mid_at.y)) {
                        continue;
                    }

                    auto t = l->owner;
                    point blit_tl, blit_br;
                    Tilep tile = {};

                    if (!t->get_map_offset_coords(blit_tl, blit_br, tile, false)) {
                        continue;
                    }

                    auto mid = (blit_br + blit_tl) / 2;
                    auto s = l->strength;
                    auto tlx = mid.x - s;
                    auto tly = mid.y - s;
                    auto brx = mid.x + s;
                    auto bry = mid.y + s;
                    color c = l->col;
                    glcolor(c);
                    blit(g_glow_overlay_texid, 0, 0, 1, 1, tlx, tly, brx, bry);
                }
            } FOR_ALL_THINGS_END()
        }
    }
    blit_flush();

    glcolor(WHITE);
}

//
// Alow distant lights to fade
//
void Level::lights_fade (void)
{_
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            auto v = is_lit_no_check(x, y);
            if (v) {
                set_is_lit_no_check(x, y, v - 1);
            }
        }
    }
}

//
// Refresh lights on a new level. Ignore blitted postion.
//
void Level::lights_update_new_level (void)
{_
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            FOR_ALL_LIGHTS_AT_DEPTH(this, t, x, y) {
                //
                // Need to do this as light position depends on blitting
                //
                t->is_blitted = false;
                for (auto& l : t->get_light()) {
                    l->update();
                    l->reset();
                }
            } FOR_ALL_THINGS_END()
        }
    }
}

//
// Update lights on existing level e.g. torch goes out
//
void Level::lights_update_same_level (void)
{_
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            FOR_ALL_LIGHTS_AT_DEPTH(this, t, x, y) {
                for (auto& l : t->get_light()) {
                    l->update();
                    l->reset();
                }
            } FOR_ALL_THINGS_END()
        }
    }
}
