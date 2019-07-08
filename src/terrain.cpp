//https://gamedev.stackexchange.com/questions/12449/midpoint-displacement-algorithm

#include "my_game.h"
#include "my_color.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

static signed char new_map[MAP_WIDTH*2][MAP_HEIGHT*2];
static signed char old_map[MAP_WIDTH*2][MAP_HEIGHT*2];

signed char scrand(signed char r = 127) { return (-r + 2 * (myrand() % r)); }

void midpoint_disp_algo (signed char displacement) 
{
    size_t n = (2 * MAP_WIDTH) - 1;

    // Resize
    // 1 0 1
    // 0 0 0
    // 1 0 1
    for (size_t i = 0; i < n; i += 2) {
        for (size_t j = !(i % 2 == 0); j < n; j += 2) {
            new_map[i][j] = old_map[i / 2][j / 2];
        }
    }

    // Diamond algorithm
    // 0 0 0
    // 0 X 0
    // 0 0 0
    for (size_t i = 1; i < n; i += 2) {
        for (size_t j = 1; j < n; j += 2) {
            signed char& map_ij = new_map[i][j];

            signed char a = new_map[i - 1][j - 1];
            signed char b = new_map[i - 1][j + 1];
            signed char c = new_map[i + 1][j - 1];
            signed char d = new_map[i + 1][j + 1];
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
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = (i % 2 == 0); j < n; j += 2) {
            signed char& map_ij = new_map[i][j];

            // get surrounding values
            signed char a = 0, b = a, c = a, d = a;
            if (i != 0) a = new_map[i - 1][j];
            if (j != 0) b = new_map[i][j - 1];
            if (j + 1 != n) c = new_map[i][j + 1];
            if (i + 1 != n) d = new_map[i + 1][j];

            // average calculation
            if (i == 0) map_ij = (b + c + d) / 3;
            else if (j == 0) map_ij = (a + c + d) / 3;
            else if (j + 1 == n) map_ij = (a + b + d) / 3;
            else if (i + 1 == n) map_ij = (a + b + c) / 3;
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

signed char** createnoise(unsigned n) 
{
    signed char** noise = new signed char*[n];
    for (unsigned i = 0; i < n; ++i) {
        noise[i] = new signed char[n];
        for (unsigned j = 0; j < n; ++j) noise[i][j] = scrand();
    }
    return noise;
}

static void dump (void)
{
    int w = MAP_WIDTH;
    int h = MAP_WIDTH;
    static int count;
    auto filename = dynprintf("map.%d.ppm", ++count);
    auto fp = fopen(filename, "w");
    fprintf(fp, "P6\n%d %d\n255\n",w,h);

    int i, j;

    for (j=h-1;j>=0;j--) {
        for (i=0;i<w;i++) {
            color c;
            c = WHITE;

            if (new_map[i][j] < 120) {
                c = GRAY;
            }
            if (new_map[i][j] < 110) {
                c = GRAY;
            }
            if (new_map[i][j] < 100) {
                c = GREEN1;
            }
            if (new_map[i][j] < 90) {
                c = GREEN2;
            }
            if (new_map[i][j] < 80) {
                c = GREEN3;
            }
            if (new_map[i][j] < 70) {
                c = GREEN4;
            }
            if (new_map[i][j] < 60) {
                c = GREEN;
            }
            if (new_map[i][j] < 50) {
                c = GREEN;
            }
            if (new_map[i][j] < 40) {
                c = YELLOWGREEN;
            }
            if (new_map[i][j] < 35) {
                c = YELLOW;
            }
            if (new_map[i][j] < 30) {
                c = CYAN;
            }
            if (new_map[i][j] < 20) {
                c = LIGHTBLUE;
                c.b += new_map[i][j];
            }
            if (new_map[i][j] < 10) {
                c = BLUE2;
                c.b += new_map[i][j];
            }
            if (new_map[i][j] < 5) {
                c = BLUE;
                c.b += new_map[i][j];
            }

            fputc(c.r, fp);
            fputc(c.g, fp);
            fputc(c.b, fp);
        }
    }

    fclose(fp);
    myfree(filename);
}
#if 0
Fontp
ttf_write_tga (std::string name, int pointsize, int style)
{_
    uint32_t rmask, gmask, bmask, amask;
    int glyph_per_row;
    char filename[200];
    SDL_Surface *dst;
    uint32_t height;
    uint32_t width;
    double max_line_height[TTF_GLYPH_MAX];
    uint32_t c;
    int x;
    int y;
    double h;

    snprintf(filename, sizeof(filename), "%s_pointsize%u.tga",
             name.c_str(), pointsize);

    //
    // x glyphs horizontally and y vertically.
    //
    glyph_per_row = TTF_GLYPH_PER_ROW;

    Fontp f = ttf_new(name, pointsize, style);
    if (!f) {
        ERR("could not create font %s", name.c_str());
    }

    memset(max_line_height, 0, sizeof(max_line_height));

    //
    // Find the largest font glyph pointsize.
    //
    x = 0;
    y = 0;
    height = 0;
    int max_char_height = 0;
    int max_char_width = 0;

    int tot = 0;
    for (c = 0; c < TTF_GLYPH_MAX; c++) {
        if (!f->valid[c]) {
            continue;
        }
        tot++;

        double w = f->glyphs[c].maxx - f->glyphs[c].minx;
        double h = f->glyphs[c].maxy - f->glyphs[c].miny;

        max_line_height[y] = fmax(max_line_height[y], h);
        max_char_height = fmax(max_char_height, max_line_height[y]);
        max_char_width = fmax(max_char_width, w);
    }
    printf("%d total glyphs\n", tot);

    //
    // Use the unicode block char as a guide for largest char.
    //
    //    int u_block = f->u_to_c[0x2588];
    //    max_char_width = f->glyphs[u_block].maxx - f->glyphs[u_block].minx;
    //    max_char_height = f->glyphs[u_block].maxy - f->glyphs[u_block].miny;

    width = glyph_per_row * max_char_width;
    height = ((tot / glyph_per_row) + 1) * max_char_height;

    //
    // Make a large surface for all glyphs.
    //
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

    dst = SDL_CreateRGBSurface(0, width, height, 32,
                               rmask, gmask, bmask, amask);
    if (!dst) {
        ERR("no surface created for size %dx%d font %s", width, height, name.c_str());
    }

    newptr(dst, "SDL_CreateRGBSurface");

    //
    // Blit each glyph to the large surface.
    //
    x = 0;
    y = 0;
    h = 0;

    for (c = 0; c < TTF_GLYPH_MAX; c++) {
        if (!f->valid[c]) {
            continue;
        }

        if (f->tex[c].image) {
            SDL_Rect dstrect = {
                (int)(max_char_width * x), (int)h, (int)max_char_width, (int)max_char_height
            };

            SDL_BlitSurface(f->tex[c].image, 0, dst, &dstrect);
        }

        if (++x >= glyph_per_row) {
            x = 0;
            h += max_char_height;
            y++;
        }
    }

    //
    // Convert the black border smoothing that ttf adds into alpha.
    //
    {
        double x;
        double y;

        for (x = 0; x < dst->w; x++) {
            for (y = 0; y < dst->h; y++) {

                color c;

                c = getPixel(dst, x, y);

                if ((c.a == 255) &&
                    (c.r == 255) &&
                    (c.g == 255) &&
                    (c.b == 255)) {
                    //
                    // Do nothing.
                    //
                } else if ((c.a == 0) &&
                    (c.r == 0) &&
                    (c.g == 0) &&
                    (c.b == 0)) {
                    //
                    // Do nothing.
                    //
                } else {
                    //
                    // Convery gray to white with alpha.
                    //
                    c.a = (c.r + c.g + c.b) / 3;
                    c.r = 255;
                    c.g = 255;
                    c.b = 255;
                }

                putPixel(dst, x, y, c);
            }
        }
    }

#define MAX_TEXTURE_HEIGHT (4096*32)

    if (dst->h > MAX_TEXTURE_HEIGHT) {
        printf("ttf is too large %dx%d @ pointsize %d\n", dst->w, dst->h, pointsize);
        exit(1);
    }

    x = 0;
    y = 0;
    h = 0;

    for (c = 0; c < TTF_GLYPH_MAX; c++) {

        if (!f->valid[c]) {
            continue;
        }

        int x1 = x * max_char_width;
        f->glyphs[c].texMinX = (double)(x1) / (double)dst->w;
        f->glyphs[c].texMaxX = (double)(x1 + max_char_width) / (double)dst->w;

        int y1 = y * max_char_height;
        f->glyphs[c].texMinY = (double)(y1) / (double)dst->h;
        f->glyphs[c].texMaxY = (double)(y1 + max_char_height) / (double)dst->h;

        if (++x >= glyph_per_row) {
            x = 0;
            y++;
        }
    }

    printf("writing %s (unicode char %d to %d) image is %dx%d pixels, glyph_per_row %d char size %dx%d pixels\n",
           filename,
           TTF_GLYPH_MIN, TTF_GLYPH_MAX,
           dst->w, dst->h,
           glyph_per_row,
           max_char_width, max_char_height);

    SDL_LockSurface(dst);
    stbi_write_tga(filename, dst->w, dst->h, STBI_rgb_alpha, dst->pixels);
    SDL_UnlockSurface(dst);

    printf("wrote %s (unicode char %d to %d) image is %dx%d pixels, glyph_per_row %d char size %dx%d pixels\n",
           filename,
           TTF_GLYPH_MIN, TTF_GLYPH_MAX,
           dst->w, dst->h,
           glyph_per_row,
           max_char_width, max_char_height);

    Texp tex;
    tex = tex_from_surface(dst, filename, filename, GL_LINEAR);
    if (!tex) {
        ERR("could not convert %s to tex", filename);
    }

    //
    // Work our the tex co-ords for each glyph in the large tex.
    //
    x = 0;
    y = 0;
    h = 0;

    for (c = 0; c < TTF_GLYPH_MAX; c++) {
        if (!f->valid[c]) {
            continue;
        }

        f->tex[c].image = dst;
        f->tex[c].tex = tex_get_gl_binding(tex);
    }

    return (f);
}
#endif

int terrain (void) 
{
    mysrand(3);

    for (unsigned i = 0; i < MAP_WIDTH; ++i) {
        for (unsigned j = 0; j < MAP_WIDTH; ++j) {
            old_map[i][j] = scrand();
        }
    }

    for (unsigned i = 1; i < 9; ++i)  {
        midpoint_disp_algo(64 / i);
    }

    dump();

    return 0;
}

