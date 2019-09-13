#include "my_game.h"
#include "my_math.h"
#include "my_color.h"
#include "my_tex.h"
#include "my_pixel.h"
#include "my_gl.h"
#include "my_math.h"
#include "my_ascii.h"
#include "my_point.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <array>

// based on
// https://gamedev.stackexchange.com/questions/12449/midpoint-displacement-algorithm

signed char scrand(signed char r = 127) { return (-r + 2 * (myrand() % r)); }

#define MAX_DROPLETS 20000 // max uint16_t
#define MAX_GRAVITY_DISTANCE  3
#define MAX_VELOCITY 1.0

typedef struct {
    fpoint at;
    fpoint velocity;
    fpoint force;
    float weight;
} Droplet;

// (a % b) in C is a remainder operator and NOT modulo operator.
static inline int16_t mod (int16_t a, int16_t b)
{
    int16_t r = a % b;
    return r < 0 ? r + b : r;
}

class Terrain
{
private:
public:
    signed char new_map[MAP_WIDTH*2][MAP_HEIGHT*2]  = {{0}};
    signed char old_map[MAP_WIDTH*2][MAP_HEIGHT*2]  = {{0}};
    signed char merged_map[MAP_WIDTH][MAP_HEIGHT]   = {{0}};
    float       final_map[MAP_WIDTH][MAP_HEIGHT]    = {{0}};
    float       groundwater[MAP_WIDTH][MAP_HEIGHT]  = {{0}};
    float       river[MAP_WIDTH][MAP_HEIGHT]  = {{0}};
    float       humidity[MAP_WIDTH][MAP_HEIGHT]     = {{0}};
    float       old_humidity[MAP_WIDTH][MAP_HEIGHT] = {{0}};
    uint16_t    droplet_map[MAP_WIDTH][MAP_HEIGHT]  = {{0}};

    std::array<Droplet, MAX_DROPLETS> droplets;
    uint32_t                          tex_groundwater;
    Texp                              tex_groundwater_p = {};
    uint32_t                          tex_clouds;
    Texp                              tex_clouds_p = {};
    uint32_t                          tex_ground;
    Texp                              tex_ground_p = {};
    int16_t                           width;
    int16_t                           height;
    int16_t                           wind_tick;

    Terrain (int16_t width, int16_t height, int16_t seed) : 
        width(width), height(height)
    {
        newptr(this, "terrain");
        mysrand(seed);

        for (unsigned x = 0; x < MAP_WIDTH; ++x) {
            for (unsigned y = 0; y < MAP_WIDTH; ++y) {
                old_map[x][y] = scrand();
            }
        }

        for (unsigned x = 1; x < 8; ++x)  {
            midpoint_disp_algo(64 / x);
        }
    }

    ~Terrain (void)
    {
        if (tex_groundwater_p) {
            tex_free(tex_groundwater_p);
            tex_groundwater_p = nullptr;
            tex_groundwater = 0;
        }
        if (tex_clouds_p) {
            tex_free(tex_clouds_p);
            tex_clouds_p = nullptr;
            tex_clouds = 0;
        }
        if (tex_ground_p) {
            tex_free(tex_ground_p);
            tex_ground_p = nullptr;
            tex_ground = 0;
        }
        oldptr(this);
    }

    void init_land (void)
    {
        for (unsigned loops = 0; loops < 4; loops++) {
            for (unsigned x = 0; x < MAP_WIDTH; ++x) {
                for (unsigned y = 0; y < MAP_WIDTH; ++y) {
                    old_map[x][y] = scrand();
                }
            }

            for (unsigned x = 1; x < 7 + loops; ++x)  {
                midpoint_disp_algo(64 / x);
            }

            for (unsigned x = 0; x < MAP_WIDTH; ++x) {
                for (unsigned y = 0; y < MAP_WIDTH; ++y) {
                    merged_map[x][y] = std::max(merged_map[x][y], new_map[x][y]);
                }
            }
        }

        for (unsigned x = 0; x < MAP_WIDTH; ++x) {
            for (unsigned y = 0; y < MAP_WIDTH; ++y) {
                new_map[x][y] = merged_map[x][y];
            }
        }
    }

    void midpoint_disp_algo (signed char displacement) 
    {
        size_t n = (2 * MAP_WIDTH) - 1;

        // Resize
        // 1 0 1
        // 0 0 0
        // 1 0 1
        for (size_t x = 0; x < n; x += 2) {
            for (size_t y = !(x % 2 == 0); y < n; y += 2) {
                new_map[x][y] = old_map[x / 2][y / 2];
            }
        }

        // Diamond algorithm
        // 0 0 0
        // 0 X 0
        // 0 0 0
        for (size_t x = 1; x < n; x += 2) {
            for (size_t y = 1; y < n; y += 2) {
                signed char& map_ij = new_map[x][y];

                signed char a = new_map[x - 1][y - 1];
                signed char b = new_map[x - 1][y + 1];
                signed char c = new_map[x + 1][y - 1];
                signed char d = new_map[x + 1][y + 1];
                map_ij = (a + b + c + d) / 4;

                int16_t rv = scrand(displacement);
                if (map_ij + rv > 127 )
                    map_ij = 127;
                else if(map_ij + rv < -128)
                    map_ij = -128;
                else
                    map_ij += rv;
            }
        }

        // Square algorithm
        // 0 1 0
        // 1 0 1
        // 0 1 0
        for (size_t x = 0; x < n; ++x) {
            for (size_t y = (x % 2 == 0); y < n; y += 2) {
                signed char& map_ij = new_map[x][y];

                // get surrounding values
                signed char a = 0, b = a, c = a, d = a;
                if (x != 0) a = new_map[x - 1][y];
                if (y != 0) b = new_map[x][y - 1];
                if (y + 1 != n) c = new_map[x][y + 1];
                if (x + 1 != n) d = new_map[x + 1][y];

                // average calculation
                if (x == 0) map_ij = (b + c + d) / 3;
                else if (y == 0) map_ij = (a + c + d) / 3;
                else if (y + 1 == n) map_ij = (a + b + d) / 3;
                else if (x + 1 == n) map_ij = (a + b + c) / 3;
                else map_ij = (a + b + c + d) / 4;

                int16_t rv = scrand(displacement);
                if (map_ij + rv > 127 )
                    map_ij = 127;
                else if(map_ij + rv < -128)
                    map_ij = -128;
                else
                    map_ij += rv;
            }
        }
        std::swap(new_map, old_map);
    }

    void to_tex_groundwater (void)
    {
        uint32_t rmask, gmask, bmask, amask;

        if (tex_groundwater_p) {
            tex_free(tex_groundwater_p);
            tex_groundwater_p = nullptr;
            tex_groundwater = 0;
        }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif

        auto image = SDL_CreateRGBSurface(0, MAP_WIDTH, MAP_HEIGHT, 32,
                                          rmask, gmask, bmask, amask);
        if (!image) {
            DIE("no image surface created for size %dx%d", 
                width, height);
        }

        newptr(image, "SDL_CreateRGBSurface");

        for (auto y=height - 1; y>=0; y--) {
            for (auto x=0; x<width; x++) {
                color c;
                c = BLACK;
                c.a = 0;

                if (final_map[x][y] > 100.0) {
                    if (groundwater[x][y] > 0.0) { c = WHITE; }
                } else {
                    if ((final_map[x][y] > 15.0) && (final_map[x][y] < 30.0)) {
                        c = YELLOW;
                    }
                    if (groundwater[x][y] > 0.0) { c = FORESTGREEN; }
                    if (groundwater[x][y] > 0.5) { c = GREEN; }
                    if (groundwater[x][y] > 1.0) { c = GREEN2; }
                    if (groundwater[x][y] > 2.0) { c = GREEN3; }
                    if (groundwater[x][y] > 3.0) { c = DARKOLIVEGREEN1; }

                    if (river[x][y] > 0.0) { c = CYAN; }
                }

                putPixel(image, x, y, c);
            }
        }

        static const char *name = "groundwater";
        tex_groundwater_p = tex_from_surface(image, name, name, GL_NEAREST);
        if (!tex_groundwater_p) {
            DIE("could not convert terrain to tex_groundwater");
        }

        tex_groundwater = tex_get_gl_binding(tex_groundwater_p);
    }

    void to_tex_clouds (void)
    {
        uint32_t rmask, gmask, bmask, amask;

        if (tex_clouds_p) {
            tex_free(tex_clouds_p);
            tex_clouds_p = nullptr;
            tex_clouds = 0;
        }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif

        auto image = SDL_CreateRGBSurface(0, MAP_WIDTH, MAP_HEIGHT, 32,
                                          rmask, gmask, bmask, amask);
        if (!image) {
            DIE("no image surface created for size %dx%d", 
                width, height);
        }

        newptr(image, "SDL_CreateRGBSurface");

        for (auto y=height - 1; y>=0; y--) {
            for (auto x=0; x<width; x++) {
                color c;
                c = BLACK;
                c.a = 0;

                if (humidity[x][y] > 0)   { c = WHITE; }

                putPixel(image, x, y, c);
            }
        }

        static const char *name = "clouds";
        tex_clouds_p = tex_from_surface(image, name, name, GL_NEAREST);
        if (!tex_clouds_p) {
            DIE("could not convert terrain to tex_clouds");
        }

        tex_clouds = tex_get_gl_binding(tex_clouds_p);
    }

    void to_tex_ground (void)
    {
        uint32_t rmask, gmask, bmask, amask;

        if (tex_ground_p) {
            tex_free(tex_ground_p);
            tex_ground_p = nullptr;
            tex_ground = 0;
        }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif

        auto image = SDL_CreateRGBSurface(0, MAP_WIDTH, MAP_HEIGHT, 32,
                                          rmask, gmask, bmask, amask);
        if (!image) {
            DIE("no image surface created for size %dx%d", 
                width, height);
        }

        newptr(image, "SDL_CreateRGBSurface");

        for (auto y=height - 1; y>=0; y--) {
            for (auto x=0; x<width; x++) {
                color c= WHITE;

                if (final_map[x][y] < 120) { c = GRAY90; }
                if (final_map[x][y] < 110) { c = GRAY80; }
                if (final_map[x][y] < 100) { c = GRAY70; }
                if (final_map[x][y] < 90) { c = GRAY60; }
                if (final_map[x][y] < 80) { c = GRAY50; }
                if (final_map[x][y] < 70) { c = GRAY40; }
                if (final_map[x][y] < 60) { c = GRAY30; }
                if (final_map[x][y] < 50) { c = GRAY20; }
                if (final_map[x][y] < 40) { c = GRAY10; }
                if (final_map[x][y] < 30) { c = GRAY5; }
                if (final_map[x][y] < 20) { c = GRAY1; }
                if (final_map[x][y] < 15) {
                    c = BLUE;
                    c.b += final_map[x][y];
                }
                if (final_map[x][y] < 10) {
                    c = BLUE;
                    c.b += final_map[x][y];
                }
                if (final_map[x][y] < 5) {
                    c = BLUE;
                    c.b += final_map[x][y];
                }
                if (final_map[x][y] < 4) {
                    c = BLUE;
                    c.b += final_map[x][y];
                }
                if (final_map[x][y] < 3) {
                    c = BLUE;
                    c.b += final_map[x][y];
                }
                if (final_map[x][y] < 2) {
                    c = DARKBLUE;
                    c.b += final_map[x][y];
                }

                putPixel(image, x, y, c);
            }
        }

        static const char *name = "ground";
        tex_ground_p = tex_from_surface(image, name, name, GL_NEAREST);
        if (!tex_ground_p) {
            DIE("could not convert terrain to tex_ground");
        }

        tex_ground = tex_get_gl_binding(tex_ground_p);
    }

    void place_drop (int di, int pass)
    {
        auto d = &droplets[di];
        int tries = 0;

        d->weight = 1.0;
        for (;;) {
#if 0
redo:
#endif
            d->at.x = random_range(0, MAP_WIDTH);
            d->at.y = random_range(0, MAP_WIDTH);
            //d->at.y = gauss(MAP_WIDTH / 2, 40);

            if (d->at.y < 0) {
                d->at.y = 0;
            }
            if (d->at.y >= MAP_WIDTH) {
                d->at.y = MAP_WIDTH - 1;
            }

            int x = (int)d->at.x;
            int y = (int)d->at.y;

            int ix = mod(x, MAP_WIDTH);
            int iy = mod(y, MAP_WIDTH);

            if (pass == 1) {
                if ((tries++ < 1000) && (final_map[ix][iy] > 5)) {
                    continue;
                }
            } else {
                if (final_map[ix][iy] >= 1.0) {
                    continue;
                }

                d->at.x = gauss(ix, 10.0);
                d->at.y = gauss(iy, 10.0);
                x = (int)d->at.x;
                y = (int)d->at.y;
            }

#if 0
            for (auto dx = -MAX_GRAVITY_DISTANCE; dx < MAX_GRAVITY_DISTANCE; dx++) {
                for (auto dy = -MAX_GRAVITY_DISTANCE; dy < MAX_GRAVITY_DISTANCE; dy++) {
                    float cx = x + dx;
                    float cy = y + dy;
                    auto ix = mod(cx, MAP_WIDTH);
                    auto iy = mod(cy, MAP_WIDTH);
                    if (droplet_map[ix][iy]) {
                        goto redo;
                    }
                }
            }

            for (auto dx = -MAX_GRAVITY_DISTANCE; dx < MAX_GRAVITY_DISTANCE; dx++) {
                for (auto dy = -MAX_GRAVITY_DISTANCE; dy < MAX_GRAVITY_DISTANCE; dy++) {
                    float cx = x + dx;
                    float cy = y + dy;
                    auto ix = mod(cx, MAP_WIDTH);
                    auto iy = mod(cy, MAP_WIDTH);
                    droplet_map[ix][iy] = di;
                }
            }
#endif

            break;
        }

        float s, c;
        float rad = (((float)random_range(0, 360)) / 360.0) * RAD_360;
        sincosf(rad, &s, &c);
        d->velocity = fpoint(s, c);
    }

    void init_droplets (void)
    {
        for (auto di = 1; di < MAX_DROPLETS; di++) {
            place_drop(di, 1);
        }

        for (unsigned x = 0; x < MAP_WIDTH; ++x) {
            for (unsigned y = 0; y < MAP_WIDTH; ++y) {
                final_map[x][y] = new_map[x][y];
            }
        }
    }

    void deposit_water (point p, float weight)
    {
        if (wind_tick < 30) {
            return;
        }

        float delta = 0.01;

        while (weight > 0.0) {
            int16_t current_depth = get_map(p.x, p.y);
            if (current_depth < 1) {
                break;
            }

            static point best[9];
            int8_t besti = 0;
            float most_w = 0;
            float lowest_depth = 999;

            for (int16_t dx = -1; dx <= 1; dx++) {
                for (int16_t dy = -1; dy <= 1; dy++) {
                    if (dx && dy) {
                        continue;
                    }
                    if (!dx && !dy) {
                        continue;
                    }
                    point neb = point(dx, dy) + p;
                    neb.x = mod(neb.x, MAP_WIDTH);
                    neb.y = mod(neb.y, MAP_WIDTH);

                    float w = get_groundwater(neb.x, neb.y);
                    if (w > most_w) {
                        most_w = w;
                        best[besti++] = neb;
                        continue;
                    }
                }
            }

            if (!besti) {
                for (int16_t dx = -1; dx <= 1; dx++) {
                    for (int16_t dy = -1; dy <= 1; dy++) {
                        if (dx && dy) {
                            continue;
                        }
                        if (!dx && !dy) {
                            continue;
                        }
                        point neb = point(dx, dy) + p;
                        neb.x = mod(neb.x, MAP_WIDTH);
                        neb.y = mod(neb.y, MAP_WIDTH);

                        int16_t neb_depth = get_map(neb.x, neb.y);
                        if (neb_depth < lowest_depth) {
                            lowest_depth = neb_depth;
                            best[besti++] = neb;
                        }
                    }
                }

                if (!besti) {
                    break;
                }
            }

            auto b = best[random_range(0, besti)];

            weight -= delta;

            groundwater[p.x][p.y] += delta;

#if 0
            int16_t neb_depth = get_map(b.x, b.y);
            if (abs(current_depth - neb_depth) > 15) {
                for (int16_t dx = -2; dx <= 2; dx++) {
                    for (int16_t dy = -2; dy <= 2; dy++) {
                        point neb = point(b.x + dx, b.y + dy);
                        neb.x = mod(neb.x, MAP_WIDTH);
                        neb.y = mod(neb.y, MAP_WIDTH);

                        final_map[neb.x][neb.y] *= 0.99;
                    }
                }

                for (int16_t dx = -1; dx <= 1; dx++) {
                    for (int16_t dy = -1; dy <= 1; dy++) {
                        point neb = point(b.x + dx, b.y + dy);
                        neb.x = mod(neb.x, MAP_WIDTH);
                        neb.y = mod(neb.y, MAP_WIDTH);

                        final_map[neb.x][neb.y] *= 0.99;
                    }
                }
                final_map[b.x][b.y] *= 0.99;
            }
#endif

            p = b;
        }
    }

    void make_river (void)
    {
        int x = random_range(0, MAP_WIDTH);
        int y = random_range(0, MAP_WIDTH);

        if (final_map[x][y] < 50) {
            return;
        }
        if (final_map[x][y] > 60) {
            return;
        }

        point p(x, y);

        for (;;) {
            int16_t current_depth = get_map(p.x, p.y);
            if (current_depth < 15) {
                break;
            }


            static point best[9];
            int8_t besti = 0;
            float lowest_depth = 999;

#if 0
            float most_w = 0;
            for (int16_t dx = -1; dx <= 1; dx++) {
                for (int16_t dy = -1; dy <= 1; dy++) {
                    if (dx && dy) {
                        continue;
                    }
                    if (!dx && !dy) {
                        continue;
                    }
                    point neb = point(dx, dy) + p;
                    neb.x = mod(neb.x, MAP_WIDTH);
                    neb.y = mod(neb.y, MAP_WIDTH);

                    float w = get_groundwater(neb.x, neb.y);
                    if (w > most_w) {
                        most_w = w;
                        best[besti++] = neb;
                        continue;
                    }
                }
            }
#endif

            if (!besti) {
                for (int16_t dx = -1; dx <= 1; dx++) {
                    for (int16_t dy = -1; dy <= 1; dy++) {
                        if (!dx && !dy) {
                            continue;
                        }
                        point neb = point(dx, dy) + p;
                        neb.x = mod(neb.x, MAP_WIDTH);
                        neb.y = mod(neb.y, MAP_WIDTH);

                        if (river[neb.x][neb.y] > 0) {
                            continue;
                        }

                        int16_t neb_depth = get_map(neb.x, neb.y);
                        if (neb_depth < lowest_depth) {
                            lowest_depth = neb_depth;
                            best[besti++] = neb;
                        }
                    }
                }

                if (!besti) {
                    break;
                }
            }

            auto b = best[random_range(0, besti)];

            final_map[p.x][p.y] = 15;
            river[p.x][p.y] = 5;
            p = b;
        }
    }

    float get_humidity (int16_t x, int16_t y)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        float height = final_map[x][y];
        //height /= 1000.0;

        return (humidity[x][y] + height);
    }

    int16_t get_map (int16_t x, int16_t y)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        return (final_map[x][y]);
    }

    float get_groundwater (int16_t x, int16_t y)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        return (groundwater[x][y]);
    }

    void set_humidity (int16_t x, int16_t y, float h)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        humidity[x][y] = h;
    }

    void calculate_attraction (void)
    {
        memset(humidity, 0, sizeof(humidity));
        memset(droplet_map, 0, sizeof(droplet_map));

        for (auto di = 1; di < MAX_DROPLETS; di++) {
            auto d = &droplets[di];
            int16_t x = (int16_t)d->at.x;
            int16_t y = (int16_t)d->at.y;
            x = mod(x, MAP_WIDTH);
            y = mod(y, MAP_WIDTH);
            droplet_map[x][y] = di;
        }

        for (auto di = 1; di < MAX_DROPLETS; di++) {
            auto d = &droplets[di];
            d->force.x = 0;
            d->force.y = 0;

            int16_t x = (int16_t)d->at.x;
            int16_t y = (int16_t)d->at.y;
            x = mod(x, MAP_WIDTH);
            y = mod(y, MAP_WIDTH);

            humidity[x][y] += d->weight;

            for (auto dx = -MAX_GRAVITY_DISTANCE; dx < MAX_GRAVITY_DISTANCE; dx++) {
                int16_t ox = x + dx;
                ox = mod(ox, MAP_WIDTH);
                for (auto dy = -MAX_GRAVITY_DISTANCE; dy < MAX_GRAVITY_DISTANCE; dy++) {
                    int16_t oy = y + dy;
                    oy = mod(oy, MAP_WIDTH);

                    if (!dx && !dy) {
                        continue;
                    }

                    auto odi = droplet_map[ox][oy];
                    if (!odi) {
                        continue;
                    }

                    float dist = (dx * dx) + (dy * dy);

                    // Compute the force of attraction
                    auto od = &droplets[odi];
                    float f = (d->weight * od->weight) / (dist * dist);

                    // Compute the direction of the force.
                    float theta = atan2((float)dy, (float)dx);

                    fpoint force;
                    sincosf(theta, &force.y, &force.x);

                    force.x *= f;
                    force.y *= f;

                    d->force.x += force.x;
                    d->force.y += force.y;
                }
            }
        }
    }

    void update_wind (void)
    {
        wind_tick++;

        ascii_putf(1, 2, ORANGE, WHITE, L"%u tick", wind_tick);

        for (auto di = 1; di < MAX_DROPLETS; di++) {
            auto d = &droplets[di];
            if (d->velocity.length() > MAX_VELOCITY) {
                d->velocity.unit();
                d->velocity *= MAX_VELOCITY;
            }
            d->velocity += d->force / d->weight;
            fpoint new_at = d->at + d->velocity;

            new_at.x += 1.0;

            if (new_at.x >= MAP_WIDTH) {
                new_at.x -= MAP_WIDTH;
            }
            if (new_at.y >= MAP_WIDTH) {
                new_at.y -= MAP_WIDTH;
            }
            if (new_at.x < 0) {
                new_at.x += MAP_WIDTH;
            }
            if (new_at.y < 0) {
                new_at.y += MAP_WIDTH;
            }

            int16_t nx = mod(new_at.x, MAP_WIDTH);
            int16_t ny = mod(new_at.y, MAP_WIDTH);

#if 0
            if (humidity[nx][ny] > 3) {
                d->velocity = d->velocity.rotate(0.45);
                continue;
            }
#endif

            d->at = new_at;

                if (final_map[nx][ny] < 15)  {
                    // over deep water
//                    if (random_range(0, 100) < 50) {
//                        d->weight *= 1.01;
//                        d->velocity *= 1.01;
                } else if (final_map[nx][ny] < 90)  {
                    // over grass
                    if (random_range(0, 100) < 40) {
                        auto delta = d->weight / 2;
                        deposit_water(point(nx, ny), delta);
                        d->weight -= delta;
                    }
                } else {
                    // over nountains
//d->velocity *= 2.0;
//d->weight *= 0.50;
                    if (random_range(0, 100) < 40) {
                        auto delta = d->weight / 2;
                        deposit_water(point(nx, ny), delta);
                        d->weight -= delta;
                    }
                }
//            }

#if 0
            if (humidity[nx][ny] > 1) {
                d->velocity *= 0.9;
            }
#endif

            if (d->weight < 0.01) {
                place_drop(di, 2);
            }

#if 0
if (random_range(0, 100) < 10) {
d->velocity = d->velocity.rotate(0.1);
}
if (random_range(0, 100) < 10) {
d->velocity = d->velocity.rotate(-0.1);
}
#endif
        }
        make_river();
    }

    void tick (void)
    {
        calculate_attraction();
        update_wind();
        to_tex_groundwater();
        to_tex_clouds();
        to_tex_ground();
    }
};

Terrain *terrain_init (int16_t seed)
{
    auto t = new Terrain(MAP_WIDTH, MAP_HEIGHT, seed);

    t->init_land();
    t->init_droplets();

#if 0
    for (auto i = 0; i < 400; i++) {
        t->calculate_attraction();
        t->update_wind();
    }
#endif

    return (t);
}

void terrain_blit (Terrainp t)
{
    verify(t);

    t->tick();

    uint32_t tw = game->config.video_pix_width / 2;
    uint32_t th = game->config.video_pix_height / 2;
    double window_w = tw;
    double window_h = th;
    double square = window_w / window_h;
    window_w = 1;
    window_h = square;

    color c = WHITE;
    c.a = 200;
    glcolor(c);
    blit_init();
    blit(t->tex_ground, 0.0, 1.0, 1.0, 0.0, 0, 0, window_w / 2, window_h / 2);
    blit(t->tex_ground, 0.0, 1.0, 1.0, 0.0, window_w / 2, 0, window_w, window_h / 2);
    blit(t->tex_groundwater, 0.0, 1.0, 1.0, 0.0, 0, 0, window_w / 2, window_h / 2);
    blit(t->tex_clouds, 0.0, 1.0, 1.0, 0.0, window_w / 2, 0, window_w, window_h / 2);
    blit_flush();
}
