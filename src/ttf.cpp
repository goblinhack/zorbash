//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_gl.h"
#include "my_wid.h"
#include "my_tex.h"
#include "my_tile.h"
#include "my_ttf.h"
#include "my_ramdisk.h"
#include "my_time.h"
#include "my_string.h"
#include "my_font.h"

#include "my_bits.h"
#include "my_math.h"
#include "my_pixel.h"
#include "stb_image.h"
#include "stb_image_write.h"

static void ttf_create_tex_from_char(TTF_Font *ttf, const char *name,
                                     Font *f,
                                     uint16_t c,
                                     uint16_t d);

//
// Load a new font and create textures for each glyph
//
Fontp ttf_new (std::string name, int pointSize, int style)
{_
    TTF_Font *ttf;

    auto f = new Font();

    DBG("Load TTF: %s", name.c_str());

    f->foreground.r = 255;
    f->foreground.g = 255;
    f->foreground.b = 255;
    f->background.r = 0;
    f->background.g = 0;
    f->background.b = 0;

    TTF_Init();
    ttf = TTF_OpenFont(name.c_str(), pointSize);
    if (ttf) {
        TTF_SetFontStyle(ttf, style);
    }

    uint32_t d = 0;
    uint32_t c = TTF_GLYPH_MIN;

    while (d < TTF_GLYPH_MAX) {
        if (c >= TTF_GLYPH_MAX) {
            break;
        }

#if 0
        if (!TTF_GlyphIsProvided(ttf, c)) {
            f->u_to_c[c] = 0;
            c++;
            continue;
        }
#endif

        f->u_to_c[c] = d;
        f->valid[d] = true;
        if (ttf) {
            ttf_create_tex_from_char(ttf, name.c_str(), f, c, d);
        }
        c++;
        d++;
    }

    if (ttf) {
        TTF_CloseFont(ttf);
    }

    return (f);
}

//
// Create a tex from a surface. Set the alpha according to the color key.
// Pixels that match the color key get an alpha of zero while all other pixels
// get an alpha of one. We use black for the color key.
//
static void
ttf_set_color_key (SDL_Surface *glyph_surface,
                   GLfloat *texcoord,
                   uint8_t ckr,
                   uint8_t ckg,
                   uint8_t ckb,
                   double *width,
                   double *height)
{_
    SDL_Surface *tmp;
    uint32_t colorkey;

    //
    // Use the surface width and height expanded to powers of 2
    //
    *width = glyph_surface->w;
    *height = glyph_surface->h;

    texcoord[0] = 0; // Min X
    texcoord[1] = 0; // Min Y
    texcoord[2] =
        (GLfloat)(((double)glyph_surface->w) / ((double)*width));  // Max X
    texcoord[3] =
        (GLfloat)(((double)glyph_surface->h) / ((double)*height)); // Max Y

    tmp = SDL_CreateRGBSurface(glyph_surface->flags,
                               *width, *height, 32,
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
                               0xFF000000,
                               0x00FF0000,
                               0x0000FF00,
                               0x000000FF
#else
                               0x000000FF,
                               0x0000FF00,
                               0x00FF0000,
                               0xFF000000
#endif
                            );

    if (!tmp) {
        ERR("Failed to make RGB surface size %f %f: %s",
            *width, *height, SDL_GetError());
        SDL_ClearError();
        return;
    }

    newptr(tmp, "SDL_CreateRGBSurface");

    //
    // Set up so that colorkey pixels become transparent
    //
    colorkey = SDL_MapRGBA(tmp->format, 0, 0, 0, 0);
    SDL_FillRect(tmp, 0, colorkey);

    colorkey = SDL_MapRGBA(glyph_surface->format, ckr, ckg, ckb, 0);
#if (SDL_MAJOR_VERSION == 2)
    SDL_SetColorKey(glyph_surface, SDL_TRUE, colorkey);
#else
    SDL_SetColorKey(glyph_surface, SDL_SRCCOLORKEY, colorkey);
#endif

    SDL_FreeSurface(tmp);
    oldptr(tmp);
}

//
// Given a single character, make it into an opengl tex
//
static void
ttf_create_tex_from_char (TTF_Font *ttf, const char *name, Font *f,
                          uint16_t c,
                          uint16_t d)
{_
    static uint16_t text[2];
    int e;

    //
    // Load the glyph info
    //
    int minx;
    int maxx;
    int miny;
    int maxy;
    int advance;

    e = TTF_GlyphMetrics(ttf, c,
                         &minx,
                         &maxx,
                         &miny,
                         &maxy,
                         &advance);
    if (e != 0) {
        ERR("error loading font glyph %u %s", c, name);
        return;
    }

    getref(f->glyphs, d).minx = minx;
    getref(f->glyphs, d).maxx = maxx;
    getref(f->glyphs, d).miny = miny;
    getref(f->glyphs, d).maxy = maxy;
    getref(f->glyphs, d).advance = advance;

    text[0] = c;
    text[1] = '\0';

    TTF_SetFontHinting(ttf, TTF_HINTING_NORMAL);
    SDL_Surface *g1 =
            TTF_RenderUNICODE_Blended(ttf, text, f->foreground);
    if (!g1) {
        DBG("Error TTF_RenderUNICODE_Blended failed for font glyph %u in %s, err: %s",
            c, name, TTF_GetError());
        return;
    }

    GLfloat texcoord [4];

    f->tex[d].image = g1;
    f->tex[d].tex = 0;

    ttf_set_color_key(g1, texcoord, 0, 0, 0,
                      &getref(f->glyphs, d).width,
                      &getref(f->glyphs, d).height);

    getref(f->glyphs, d).texMinX = texcoord[0];
    getref(f->glyphs, d).texMinY = texcoord[1];
    getref(f->glyphs, d).texMaxX = texcoord[2];
    getref(f->glyphs, d).texMaxY = texcoord[3];
}

Fontp
ttf_read_tga (Fontp f, const char *name, int pointsize)
{_
    char filename[MAXSTR];
    uint32_t c;
    Texp tex;

    snprintf(filename, sizeof(filename), "%s_pointsize%u.tga",
             name, pointsize);

    tex = tex_load(filename,
                   filename /* to make unique for same point size */,
                   GL_LINEAR);
    if (!tex) {
        ERR("could not load font %s tex", filename);
    }

    for (c = 0; c < TTF_GLYPH_MAX; c++) {
        getref(f->tex, c).tex_p = tex;
        getref(f->tex, c).tex = tex_get_gl_binding(tex);
        getref(f->tex, c).image = tex_get_surface(tex);
    }

    return (f);
}

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
        if (!get(f->valid, c)) {
            continue;
        }
        tot++;

        double w = get(f->glyphs, c).maxx - get(f->glyphs, c).minx;
        double h = get(f->glyphs, c).maxy - get(f->glyphs, c).miny;

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
        if (!get(f->valid, c)) {
            continue;
        }

        if (get(f->tex, c).image) {
            SDL_Rect dstrect = {
                (int)(max_char_width * x), (int)h, (int)max_char_width, (int)max_char_height
            };

            SDL_BlitSurface(get(f->tex, c).image, 0, dst, &dstrect);
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

        if (!get(f->valid, c)) {
            continue;
        }

        int x1 = x * max_char_width;
        getref(f->glyphs, c).texMinX = (double)(x1) / (double)dst->w;
        getref(f->glyphs, c).texMaxX = (double)(x1 + max_char_width) / (double)dst->w;

        int y1 = y * max_char_height;
        getref(f->glyphs, c).texMinY = (double)(y1) / (double)dst->h;
        getref(f->glyphs, c).texMaxY = (double)(y1 + max_char_height) / (double)dst->h;

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
        if (!get(f->valid, c)) {
            continue;
        }

        getref(f->tex, c).image = dst;
        getref(f->tex, c).tex = tex_get_gl_binding(tex);
    }

    return (f);
}
