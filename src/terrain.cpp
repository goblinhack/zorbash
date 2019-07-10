#include "my_game.h"
#include "my_color.h"
#include "my_tex.h"
#include "my_pixel.h"
#include "my_gl.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

// based on
// https://gamedev.stackexchange.com/questions/12449/midpoint-displacement-algorithm

signed char scrand(signed char r = 127) { return (-r + 2 * (myrand() % r)); }

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

        for (unsigned x = 1; x < 9; ++x)  {
            midpoint_disp_algo(64 / x);
        }

    }

    ~Terrain (void)
    {
        if (tex_p) {
            tex_free(tex_p);
            tex_p = nullptr;
            tex = 0;
        }
        oldptr(this);
    }

    signed char new_map[MAP_WIDTH*2][MAP_HEIGHT*2];
    signed char old_map[MAP_WIDTH*2][MAP_HEIGHT*2];

    signed char groundwater[MAP_WIDTH][MAP_HEIGHT];
    signed char humidity[MAP_WIDTH][MAP_HEIGHT];

    uint32_t    tex;
    Texp        tex_p = {};
    int         width;
    int         height;

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
                    c = GRAY;
                }
                if (new_map[x][y] < 110) {
                    c = GRAY;
                }
                if (new_map[x][y] < 100) {
                    c = GREEN1;
                }
                if (new_map[x][y] < 90) {
                    c = GREEN2;
                }
                if (new_map[x][y] < 80) {
                    c = GREEN3;
                }
                if (new_map[x][y] < 70) {
                    c = GREEN4;
                }
                if (new_map[x][y] < 60) {
                    c = GREEN;
                }
                if (new_map[x][y] < 50) {
                    c = GREEN;
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

    void to_tex (void)
    {
        uint32_t rmask, gmask, bmask, amask;

        if (tex_p) {
            tex_free(tex_p);
            tex_p = nullptr;
            tex = 0;
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
                c = WHITE;

                if (new_map[x][y] < 120) {
                    c = GRAY;
                }
                if (new_map[x][y] < 110) {
                    c = GRAY;
                }
                if (new_map[x][y] < 100) {
                    c = GREEN1;
                }
                if (new_map[x][y] < 90) {
                    c = GREEN2;
                }
                if (new_map[x][y] < 80) {
                    c = GREEN3;
                }
                if (new_map[x][y] < 70) {
                    c = GREEN4;
                }
                if (new_map[x][y] < 60) {
                    c = GREEN;
                }
                if (new_map[x][y] < 50) {
                    c = GREEN;
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

                putPixel(image, x, y, c);
            }
        }

        static const char *name = "terrain";
        tex_p = tex_from_surface(image, name, name, GL_LINEAR);
        if (!tex_p) {
            DIE("could not convert terrain to tex");
        }

        tex = tex_get_gl_binding(tex_p);

        SDL_FreeSurface(image);
    }
};

Terrain *terrain_init (int seed)
{
    auto t = new Terrain(MAP_WIDTH, MAP_HEIGHT, seed);

    t->to_tex();

    return (t);
}

void terrain_blit (Terrainp t)
{
    verify(t);

    uint32_t tw = game.config.video_pix_width / 2;
    uint32_t th = game.config.video_pix_height / 2;
    double window_w = tw;
    double window_h = th;
    double square = window_w / window_h;
    window_w = 1;
    window_h = square;

    color c = WHITE;
    c.a = 100;
    glcolor(c);
    blit_init();
    blit(t->tex, 0.0, 1.0, 1.0, 0.0, 0, 0, window_w / 2, window_h / 2);
    blit_flush();
}
