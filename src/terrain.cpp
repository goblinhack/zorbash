#include "my_game.h"
#include "my_math.h"
#include "my_color.h"
#include "my_tex.h"
#include "my_pixel.h"
#include "my_gl.h"
#include "my_math.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <array>

// based on
// https://gamedev.stackexchange.com/questions/12449/midpoint-displacement-algorithm

signed char scrand(signed char r = 127) { return (-r + 2 * (myrand() % r)); }

#define MAX_DROPLETS 50000

typedef struct {
    fpoint at;
    fpoint wind_dir;
    float density;
} Droplet;

// (a % b) in C is a remainder operator and NOT modulo operator.
int mod (int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

class Terrain
{
private:
public:
    Terrain (int width, int height, int seed) : width(width), height(height)
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

    signed char                       new_map[MAP_WIDTH*2][MAP_HEIGHT*2];
    signed char                       old_map[MAP_WIDTH*2][MAP_HEIGHT*2];
    float                             groundwater[MAP_WIDTH][MAP_HEIGHT];
    float                             humidity[MAP_WIDTH][MAP_HEIGHT];
    fpoint                            wind_dir[MAP_WIDTH][MAP_HEIGHT];
    std::array<Droplet, MAX_DROPLETS> droplets;

    uint32_t                          tex_groundwater;
    Texp                              tex_groundwater_p = {};
    uint32_t                          tex_clouds;
    Texp                              tex_clouds_p = {};
    uint32_t                          tex_ground;
    Texp                              tex_ground_p = {};

    int                               width;
    int                               height;
    int                               wind_tick;

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

                int rv = scrand(displacement);
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

                int rv = scrand(displacement);
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

#if 0
    void dump_to_ppm (void)
    {
        static int count;
        auto filename = dynprintf("map.%d.ppm", ++count);
        auto fp = fopen(filename, "w");
        fprintf(fp, "P6\n%d %d\n255\n",width, height);

        for (auto y=height - 1; y>=0; y--) {
            for (auto x=0; x<width; x++) {
                color c;
                c = WHITE;

                if (new_map[x][y] < 120) {
                    c = GRAY90;
                }
                if (new_map[x][y] < 110) {
                    c = GRAY80;
                }
                if (new_map[x][y] < 100) {
                    c = GRAY70;
                }
                if (new_map[x][y] < 90) {
                    c = GRAY60;
                }
                if (new_map[x][y] < 80) {
                    c = GRAY50;
                }
                if (new_map[x][y] < 70) {
                    c = GRAY40;
                }
                if (new_map[x][y] < 60) {
                    c = GRAY30;
                }
                if (new_map[x][y] < 50) {
                    c = GRAY20;
                }
                if (new_map[x][y] < 40) {
                    c = YELLOWGREEN;
                }
                if (new_map[x][y] < 35) {
                    c = YELLOW;
                }
                if (new_map[x][y] < 30) {
                    c = CYAN;
                }
                if (new_map[x][y] < 20) {
                    c = LIGHTBLUE;
                    c.b += new_map[x][y];
                }
                if (new_map[x][y] < 10) {
                    c = BLUE2;
                    c.b += new_map[x][y];
                }
                if (new_map[x][y] < 5) {
                    c = BLUE;
                    c.b += new_map[x][y];
                }

                fputc(c.r, fp);
                fputc(c.g, fp);
                fputc(c.b, fp);
            }
        }

        fclose(fp);
        myfree(filename);
    }
#endif

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

                if (groundwater[x][y] > 0.0) {
                    c = YELLOW;
                }
                if (groundwater[x][y] > 0.5) {
                    c = GREEN1;
                }
                if (groundwater[x][y] > 1.0) {
                    c = GREEN2;
                }
                if (groundwater[x][y] > 2.0) {
                    c = GREEN3;
                }
                if (groundwater[x][y] > 3.0) {
                    c = DARKGREEN;
                }
                if (groundwater[x][y] > 4.0) {
                    c = DARKOLIVEGREEN1;
                }
                if (groundwater[x][y] > 5.0) {
                    c = DARKOLIVEGREEN2;
                }
                if (groundwater[x][y] > 6.0) {
                    c = BLUE;
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

                if (humidity[x][y] > 0) {
                    c = ANTIQUEWHITE1;
                }
                if (humidity[x][y] > 0.5) {
                    c = ANTIQUEWHITE2;
                }
                if (humidity[x][y] > 1) {
                    c = ANTIQUEWHITE3;
                }
                if (humidity[x][y] > 1.5) {
                    c = ANTIQUEWHITE4;
                }
                if (humidity[x][y] > 2) {
                    c = YELLOW;
                }
                if (humidity[x][y] > 3) {
                    c = ORANGE;
                }
                if (humidity[x][y] > 4) {
                    c = RED;
                }

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

                if (new_map[x][y] < 120) {
                    c = GRAY90;
                }
                if (new_map[x][y] < 110) {
                    c = GRAY80;
                }
                if (new_map[x][y] < 100) {
                    c = GRAY70;
                }
                if (new_map[x][y] < 90) {
                    c = GRAY60;
                }
                if (new_map[x][y] < 80) {
                    c = GRAY50;
                }
                if (new_map[x][y] < 70) {
                    c = GRAY40;
                }
                if (new_map[x][y] < 60) {
                    c = GRAY30;
                }
                if (new_map[x][y] < 50) {
                    c = GRAY20;
                }
                if (new_map[x][y] < 40) {
                    c = GRAY10;
                }
                if (new_map[x][y] < 30) {
                    c = GRAY5;
                }
                if (new_map[x][y] < 20) {
                    c = GRAY1;
                }
                if (new_map[x][y] < 15) {
                    c = BLUE;
                    c.b += new_map[x][y];
                }
                if (new_map[x][y] < 10) {
                    c = BLUE;
                    c.b += new_map[x][y];
                }
                if (new_map[x][y] < 5) {
                    c = BLUE;
                    c.b += new_map[x][y];
                }
                if (new_map[x][y] < 4) {
                    c = BLUE;
                    c.b += new_map[x][y];
                }
                if (new_map[x][y] < 3) {
                    c = BLUE;
                    c.b += new_map[x][y];
                }
                if (new_map[x][y] < 2) {
                    c = DARKBLUE;
                    c.b += new_map[x][y];
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

    void init_droplets (void)
    {
        for (auto di = 0; di < MAX_DROPLETS; di++) {
            auto d = &droplets[di];
            float s, c;
            float rad = (((float)random_range(0, 360)) / 360.0) * RAD_360;
            sincosf(rad, &s, &c);
            d->wind_dir = fpoint(s, c);

            d->at.x = random_range(0, MAP_WIDTH);
            //d->at.y = random_range(0, MAP_WIDTH);
            d->at.y = gauss(MAP_WIDTH / 2, 40);
            if (d->at.y < 0) {
                d->at.y = 0;
            }
            if (d->at.y > MAP_WIDTH) {
                d->at.y = MAP_WIDTH;
            }

            d->density = 1.0;
        }
    }

    void deposit_water (point p, float density)
    {
        if (wind_tick < 200) {
            return;
        }

        float delta = 0.05;

        while (density > 0.0) {
            int current_depth = get_map(p.x, p.y);
            if (current_depth < 15) {
                break;
            }

            std::vector<point> best;

            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    point neb = point(dx, dy) + p;
                    int neb_depth = get_map(neb.x, neb.y);
                    int w = get_groundwater(neb.x, neb.y);
                    if ((neb_depth <= current_depth) && (w < 5.0)) {
                        best.push_back(neb);
                    }
                }
            }

            if (!best.size()) {
                groundwater[p.x][p.y] += density;
                break;
            }

            auto b = best[random_range(0, best.size())];
            int neb_depth = get_map(b.x, b.y);

            if (abs(current_depth - neb_depth) < 5) {
                density -= delta;
                groundwater[p.x][p.y] += delta;
            } else if (abs(current_depth - neb_depth) > 15) {
#if 0
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (random_range(0, 100) < 10) {
                            new_map[mod(b.x + dx, MAP_WIDTH)][mod(b.y + dy, MAP_WIDTH)]--;
                        }
                    }
                }
#endif
                if (new_map[b.x][b.y] > 15) {
                    new_map[b.x][b.y]--;
                }
            }

            p = b;
        }
    }

    void droplets_to_map (void)
    {
        memset(humidity, 0, sizeof(humidity));

        for (auto d : droplets) {
            int x = (int)d.at.x;
            int y = (int)d.at.y;

            if (x >= MAP_WIDTH) {
                continue;
            }
            if (y >= MAP_WIDTH) {
                continue;
            }
            if (x < 0) {
                continue;
            }
            if (y < 0) {
                continue;
            }

            humidity[x][y] += d.density;
            wind_dir[x][y] += d.wind_dir;

            float scale = 0.5;

            humidity[mod(x + 1, MAP_WIDTH)][y] += d.density * scale;
            humidity[mod(x - 1, MAP_WIDTH)][y] += d.density * scale;
            humidity[x][mod(y + 1, MAP_WIDTH)] += d.density * scale;
            humidity[x][mod(y - 1, MAP_WIDTH)] += d.density * scale;

            wind_dir[mod(x + 1, MAP_WIDTH)][y] += d.wind_dir * scale;
            wind_dir[mod(x - 1, MAP_WIDTH)][y] += d.wind_dir * scale;
            wind_dir[x][mod(y + 1, MAP_WIDTH)] += d.wind_dir * scale;
            wind_dir[x][mod(y - 1, MAP_WIDTH)] += d.wind_dir * scale;

            scale = 0.2;
            humidity[mod(x - 1, MAP_WIDTH)][mod(y - 1, MAP_WIDTH)] += d.density * scale;
            humidity[mod(x + 1, MAP_WIDTH)][mod(y + 1, MAP_WIDTH)] += d.density * scale;
            humidity[mod(x + 1, MAP_WIDTH)][mod(y - 1, MAP_WIDTH)] += d.density * scale;
            humidity[mod(x - 1, MAP_WIDTH)][mod(y + 1, MAP_WIDTH)] += d.density * scale;

            wind_dir[mod(x - 1, MAP_WIDTH)][mod(y - 1, MAP_WIDTH)] += d.wind_dir * scale;
            wind_dir[mod(x + 1, MAP_WIDTH)][mod(y + 1, MAP_WIDTH)] += d.wind_dir * scale;
            wind_dir[mod(x + 1, MAP_WIDTH)][mod(y - 1, MAP_WIDTH)] += d.wind_dir * scale;
            wind_dir[mod(x - 1, MAP_WIDTH)][mod(y + 1, MAP_WIDTH)] += d.wind_dir * scale;
        }
    }

    fpoint get_wind_dir (int x, int y)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        return (wind_dir[x][y]);
    }

    float get_humidity (int x, int y)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        float height = new_map[x][y];
        height /= 10.0;

        return (humidity[x][y] + height);
    }

    int get_map (int x, int y)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        return (new_map[x][y]);
    }

    float get_groundwater (int x, int y)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        return (groundwater[x][y]);
    }

    void set_humidity (int x, int y, float h)
    {
        x = mod(x, MAP_WIDTH);
        y = mod(y, MAP_WIDTH);

        humidity[x][y] = h;
    }

    void update_wind (void)
    {
        wind_tick++;

        float max_humidity = 5;

        for (auto di = 0; di < MAX_DROPLETS; di++) {
            auto d = &droplets[di];

#if 0
            if ((fabs(d->wind_dir.x) < 0.1) && (fabs(d->wind_dir.y) < 0.1)) {
                float s, c;
                float rad = (((float)random_range(0, 360)) / 360.0) * RAD_360;
                sincosf(rad, &s, &c);
                d->wind_dir = fpoint(s, c);
            }
#endif
            int x = mod(d->at.x, MAP_WIDTH);
            int y = mod(d->at.y, MAP_WIDTH);

            auto wind_speed = 1.0;

            if (new_map[x][y] < 10)  {
                wind_speed = 0.05;
            } else if (new_map[x][y] > 90)  {
                wind_speed = 1.0;
            } else {
                wind_speed = 0.5;
            }

            fpoint new_at = d->at + d->wind_dir * wind_speed;

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

            int nx = mod(new_at.x, MAP_WIDTH);
            int ny = mod(new_at.y, MAP_WIDTH);
            auto h = get_humidity(nx, ny) + d->density;
            if (h > max_humidity) {
                fpoint dir = d->wind_dir;

                if (random_range(0, 100) < 50) {
                    int x = mod(d->at.x, MAP_WIDTH);
                    int y = mod(d->at.y, MAP_WIDTH);
                    fpoint avg_wind_dir;
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (dx && dy) {
                                avg_wind_dir += get_wind_dir(x + dx, y + dy);
                            }
                        }
                    }
                    avg_wind_dir.unit();
                    d->wind_dir = avg_wind_dir;
                }

                d->wind_dir = d->wind_dir.rotate(-0.05);
                d->density *= 0.50;
            }
            d->at = new_at;

            if (new_map[nx][ny] < 10)  {
                // over water
                if (d->density < 0.01) {
                    if (random_range(0, 100) < 5) {
                        d->density  = 1.00;
                        float s, c;
                        float rad = (((float)random_range(0, 360)) / 360.0) * RAD_360;
                        sincosf(rad, &s, &c);
                        d->wind_dir = fpoint(s, c);
                    }
                }
                if (random_range(0, 100) < 50) {
                    d->density  *= 0.50;
                }
            } else if (new_map[nx][ny] > 90)  {
                deposit_water(point(nx, ny), d->density / 2);
                d->density /= 2;
            } else if (new_map[nx][ny] > 80)  {
                // over mountains
                if (random_range(0, 100) < 50) {
                    d->wind_dir = d->wind_dir.rotate(-0.01);
                    deposit_water(point(nx, ny), d->density / 2);
                    d->density /= 2;
                }
            } else {
                // over grass
                d->density  *= 0.50;
                if (random_range(0, 100) < 10) {
                    d->wind_dir = d->wind_dir.rotate(0.05);
                    deposit_water(point(nx, ny), d->density / 2);
                    d->density /= 2;
                }
            }

#if 0
            if ((fabs(d->wind_dir.x) < 0.1) && (fabs(d->wind_dir.y) < 0.1)) {
                float s, c;
                float rad = (((float)random_range(0, 360)) / 360.0) * RAD_360;
                sincosf(rad, &s, &c);
                d->wind_dir = fpoint(s, c);
            }
#endif

            d->wind_dir = d->wind_dir.rotate(-0.015);
            d->at.x += 0.2;

#if 0
            float my =  MAP_WIDTH / 2;
            float new_density = (my - fabs(d->at.y - my)) / my;
            new_density = gauss(new_density / 3.0, 0.1);
            if (new_density > 0) {
                d->density += new_density;
            }
            if ((d->density < 0.1) && (random_range(0, 100) < 10)) {
                float s, c;
                float rad = (((float)random_range(0, 360)) / 360.0) * RAD_360;
                sincosf(rad, &s, &c);
                d->dir = fpoint(s, c);

                float my =  MAP_WIDTH / 2;
                float new_density = (my - fabs(d->at.y - my)) / my;
                new_density = gauss(new_density, 0.1);
                if (new_density > 0) {
                    d->density += new_density;
printf("%f ", new_density);
                }
            }
#endif

#if 0
            if (random_range(0, 100) < 20) {
                float s, c;
                float rad = (((float)random_range(0, 360)) / 360.0) * RAD_360;
                sincosf(rad, &s, &c);
                d->dir = fpoint(s, c);

                float my =  MAP_WIDTH / 2;
                d->density += (my - fabs(d->at.y - my)) / my;
            }
#endif
        }

#if 0
        for (int x = 0; x < MAP_WIDTH; ++x) {
            for (int y = 0; y < MAP_WIDTH; ++y) {
                float angle;
//                if (random_range(0, 100) < 50) {
                //    angle = 0.01;
//                } else {
                    angle = -0.01;
//                }


                if (random_range(0, 100) < 10) {
                    fpoint p = new_wind_dir[x][y];
                    new_wind_dir[x][y] = p.rotate(angle);
                }
            }
        }

#endif
    }

    void tick (void)
    {
        droplets_to_map();
        update_wind();
        to_tex_groundwater();
        to_tex_clouds();
        to_tex_ground();
    }
};

Terrain *terrain_init (int seed)
{
    auto t = new Terrain(MAP_WIDTH, MAP_HEIGHT, seed);

    t->init_droplets();
    t->droplets_to_map();
    t->to_tex_groundwater();
    t->to_tex_clouds();
    t->to_tex_ground();

    return (t);
}

void terrain_blit (Terrainp t)
{
    verify(t);

    t->tick();

    uint32_t tw = game.config.video_pix_width / 2;
    uint32_t th = game.config.video_pix_height / 2;
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
