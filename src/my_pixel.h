//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_GETPUT_PIXEL_MACROS_H_
#define _MY_GETPUT_PIXEL_MACROS_H_


//
// Quick row-color bit-shift lookups for certain common color screen size widths:

// <<1  2
// <<2  4
// <<3  8
// <<4  16
// <<5  32
// <<6  64
// <<7  128
// <<8  256
// <<9  512
// <<10 1024
//

#define pixel_16w(y)     ((y)<<4)
#define pixel_24w(y)     ((y)<<4)+((y)<<3)
#define pixel_32w(y)     ((y)<<5)
#define pixel_48w(y)     ((y)<<5)+((y)<<4)
#define pixel_64w(y)     ((y)<<6)
#define pixel_128w(y)    ((y)<<7)
#define pixel_256w(y)    ((y)<<8)
#define pixel_320w(y)    (((y)<<8)+((y)<<6))
#define pixel_512w(y)    ((y)<<9)
#define pixel_640w(y)    (((y)<<9)+((y)<<7))
#define pixel_800w(y)    (((y)<<9)+((y)<<8)+((y)<<5))
#define pixel_1024w(y)   (((y)<<10))
#define pixel_ANYw(s,y)  ((y)*(s->pitch/s->format->BytesPerPixel))

//
// 32 bpp macros:
//
#define pixel_16x32bpp(s, x, y) ((uint32_t*)s->pixels+(x)+pixel_16w(y))
#define pixel_24x32bpp(s, x, y) ((uint32_t*)s->pixels+(x)+pixel_24w(y))
#define pixel_32x32bpp(s, x, y) ((uint32_t*)s->pixels+(x)+pixel_32w(y))
#define pixel_48x32bpp(s, x, y) ((uint32_t*)s->pixels+(x)+pixel_48w(y))
#define pixel_64x32bpp(s, x, y) ((uint32_t*)s->pixels+(x)+pixel_64w(y))
#define pixel_128x32bpp(s, x, y)    ((uint32_t*)s->pixels+(x)+pixel_128w(y))
#define pixel_256x32bpp(s, x, y)    ((uint32_t*)s->pixels+(x)+pixel_256w(y))
#define pixel_320x32bpp(s, x, y)    ((uint32_t*)s->pixels+(x)+pixel_320w(y))
#define pixel_640x32bpp(s, x, y)    ((uint32_t*)s->pixels+(x)+pixel_640w(y))
#define pixel_800x32bpp(s, x, y)    ((uint32_t*)s->pixels+(x)+pixel_800w(y))
#define pixel_1024x32bpp(s, x, y)   ((uint32_t*)s->pixels+(x)+pixel_1024w(y))
#define pixel_32bpp(s, x, y)        ((uint32_t*)s->pixels+(x)+pixel_ANYw(s,y))

#define putPixel_16x32bpp(s, x, y, rgb)     *pixel_16x32bpp(s, x, y) = rgb
#define putPixel_24x32bpp(s, x, y, rgb)     *pixel_24x32bpp(s, x, y) = rgb
#define putPixel_32x32bpp(s, x, y, rgb)     *pixel_32x32bpp(s, x, y) = rgb
#define putPixel_48x32bpp(s, x, y, rgb)     *pixel_48x32bpp(s, x, y) = rgb
#define putPixel_64x32bpp(s, x, y, rgb)     *pixel_64x32bpp(s, x, y) = rgb
#define putPixel_128x32bpp(s, x, y, rgb)    *pixel_128x32bpp(s, x, y) = rgb
#define putPixel_256x32bpp(s, x, y, rgb)    *pixel_256x32bpp(s, x, y) = rgb
#define putPixel_320x32bpp(s, x, y, rgb)    *pixel_320x32bpp(s, x, y) = rgb
#define putPixel_640x32bpp(s, x, y, rgb)    *pixel_640x32bpp(s, x, y) = rgb
#define putPixel_800x32bpp(s, x, y, rgb)    *pixel_800x32bpp(s, x, y) = rgb
#define putPixel_1024x32bpp(s, x, y, rgb)   *pixel_1024x32bpp(s, x, y) = rgb
#define putPixel_32bpp(s, x, y, rgb)        *pixel_32bpp(s, x, y) = rgb

#define getPixel_16x32bpp(s, x, y, rgb)     *(rgb) = *pixel_16x32bpp(s, x, y)
#define getPixel_24x32bpp(s, x, y, rgb)     *(rgb) = *pixel_24x32bpp(s, x, y)
#define getPixel_32x32bpp(s, x, y, rgb)     *(rgb) = *pixel_32x32bpp(s, x, y)
#define getPixel_48x32bpp(s, x, y, rgb)     *(rgb) = *pixel_48x32bpp(s, x, y)
#define getPixel_64x32bpp(s, x, y, rgb)     *(rgb) = *pixel_64x32bpp(s, x, y)
#define getPixel_128x32bpp(s, x, y, rgb)    *(rgb) = *pixel_128x32bpp(s, x, y)
#define getPixel_256x32bpp(s, x, y, rgb)    *(rgb) = *pixel_256x32bpp(s, x, y)
#define getPixel_320x32bpp(s, x, y, rgb)    *(rgb) = *pixel_320x32bpp(s, x, y)
#define getPixel_640x32bpp(s, x, y, rgb)    *(rgb) = *pixel_640x32bpp(s, x, y)
#define getPixel_800x32bpp(s, x, y, rgb)    *(rgb) = *pixel_800x32bpp(s, x, y)
#define getPixel_1024x32bpp(s, x, y, rgb)   *(rgb) = *pixel_1024x32bpp(s, x, y)
#define getPixel_32bpp(s, x, y, rgb)        *(rgb) = *pixel_32bpp(s, x, y)

//
// Lock a SDL_Surface for safe color access
//
static inline void lock (SDL_Surface *surface)
{
#if 0
 //
    // Is this needed? unlocking seems slow
    //
    if (SDL_MUSTLOCK(surface)) {
        SDL_LockSurface(surface);
    }
#endif
}

//
// Unlock a SDL_Surface, after lock()
//
static inline void unlock (SDL_Surface *surface)
{
#if 0
 //
    // Is this needed? unlocking seems slow
    //
    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
#endif
}

//
// This function sets the specified color on a SDL_Surface. Sanity checks are
// performed on the co-ordinates and the SDL_Surface is locked for you.
// Safe, but slow. For more speed, try the lower level access function.
//
static void inline putPixel (SDL_Surface * surface, uint32_t x, uint32_t y, color col)
{
    uint8_t   bpp = surface->format->BytesPerPixel;
    uint16_t pitch = surface->pitch/bpp;
    uint32_t rgb;

    if (x >= (uint32_t)surface->w) {
        ERR("out of range x %u, max %u", x, surface->w);
    }

    if (y >= (uint32_t)surface->h) {
        ERR("out of range y %u, max %u", y, surface->h);
    }

    lock(surface);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rgb = ((col.r << 24) | (col.g << 16) | (col.b << 8) | col.a);
#else
    rgb = (col.r | (col.g << 8) | (col.b << 16) | (col.a << 24));
#endif

    switch (pitch) {
        case 16:
            putPixel_16x32bpp(surface, x, y, rgb);
            break;
        case 24:
            putPixel_24x32bpp(surface, x, y, rgb);
            break;
        case 32:
            putPixel_32x32bpp(surface, x, y, rgb);
            break;
        case 48:
            putPixel_48x32bpp(surface, x, y, rgb);
            break;
        case 64:
            putPixel_64x32bpp(surface, x, y, rgb);
            break;
        case 128:
            putPixel_128x32bpp(surface, x, y, rgb);
            break;
        case 256:
            putPixel_256x32bpp(surface, x, y, rgb);
            break;
        case 320:
            putPixel_320x32bpp(surface, x, y, rgb);
            break;
        case 640:
            putPixel_640x32bpp(surface, x, y, rgb);
            break;
        case 800:
            putPixel_800x32bpp(surface, x, y, rgb);
            break;
        case 1024:
            putPixel_1024x32bpp(surface, x, y, rgb);
            break;
        default:
            putPixel_32bpp(surface, x, y, rgb);
            break;
    }

    unlock(surface);
}

//
// This function sets the specified color on a SDL_Surface. Sanity checks are
// performed on the co-ordinates and the SDL_Surface is locked for you.
// Safe, but slow. For more speed, try the lower level access function.
//
static inline color getPixel (SDL_Surface * surface, uint32_t x, uint32_t y)
{
    uint8_t   bpp = surface->format->BytesPerPixel;
    uint16_t pitch = surface->pitch/bpp;
    uint32_t rgb;
    color     col;

    if ((x >= (uint32_t)surface->w) || (y >= (uint32_t)surface->h)) {
        DIE("getPixel out of range, pix %d,%d in size %d,%d",
            x, y, surface->w, surface->h);
    }

    lock(surface);

    switch (pitch) {
        case 16:
            getPixel_16x32bpp(surface, x, y, &rgb);
            break;
        case 24:
            getPixel_24x32bpp(surface, x, y, &rgb);
            break;
        case 32:
            getPixel_32x32bpp(surface, x, y, &rgb);
            break;
        case 48:
            getPixel_48x32bpp(surface, x, y, &rgb);
            break;
        case 64:
            getPixel_64x32bpp(surface, x, y, &rgb);
            break;
        case 128:
            getPixel_128x32bpp(surface, x, y, &rgb);
            break;
        case 256:
            getPixel_256x32bpp(surface, x, y, &rgb);
            break;
        case 320:
            getPixel_320x32bpp(surface, x, y, &rgb);
            break;
        case 640:
            getPixel_640x32bpp(surface, x, y, &rgb);
            break;
        case 800:
            getPixel_800x32bpp(surface, x, y, &rgb);
            break;
        case 1024:
            getPixel_1024x32bpp(surface, x, y, &rgb);
            break;
        default:
            getPixel_32bpp(surface, x, y, &rgb);
            break;
    }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    col.r = (rgb & 0xff000000) >> 24;
    col.g = (rgb & 0x00ff0000) >> 16;
    col.b = (rgb & 0x0000ff00) >> 8;
    col.a = (rgb & 0x000000ff);
#else
    col.r = (rgb & 0x000000ff);
    col.g = (rgb & 0x0000ff00) >> 8;
    col.b = (rgb & 0x00ff0000) >> 16;
    col.a = (rgb & 0xff000000) >> 24;
#endif

    unlock(surface);

    return (col);
}
#endif
