//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GETPUT_PIXEL_MACROS_HPP_
#define _MY_GETPUT_PIXEL_MACROS_HPP_

#include "my_sys.hpp"
#include <SDL.h>

#define pixel_ANYw(s, y)             ((y) * (s->pitch / s->format->BytesPerPixel))
#define pixel_32bpp(s, x, y)         ((uint32_t *) s->pixels + (x) + pixel_ANYw(s, y))
#define putPixel_32bpp(s, x, y, rgb) *pixel_32bpp(s, x, y) = rgb
#define getPixel_32bpp(s, x, y, rgb) *(rgb) = *pixel_32bpp(s, x, y)

//
// Lock a SDL_Surface for safe color access
//
static inline void lock(SDL_Surface *surface)
{
  //
  // Is this needed? unlocking seems slow
  //
  if (SDL_MUSTLOCK(surface)) {
    SDL_LockSurface(surface);
  }
}

//
// Unlock a SDL_Surface, after lock()
//
static inline void unlock(SDL_Surface *surface)
{
  //
  // Is this needed? unlocking seems slow
  //
  if (SDL_MUSTLOCK(surface)) {
    SDL_UnlockSurface(surface);
  }
}

//
// This function sets the specified color on a SDL_Surface. Sanity checks are
// performed on the co-ordinates and the SDL_Surface is locked for you.
// Safe, but slow. For more speed, try the lower level access function.
//
static void inline putPixel(SDL_Surface *surface, uint16_t x, uint16_t y, const color &col)
{
  uint32_t rgb;

#if 0
  //
  // Optimize these out
  //
  if (x >= (uint32_t)surface->w) {
    ERR("out of range x %u, max %u", x, surface->w);
  }

  if (y >= (uint32_t)surface->h) {
    ERR("out of range y %u, max %u", y, surface->h);
  }
#endif

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rgb = ((col.r << 24) | (col.g << 16) | (col.b << 8) | col.a);
#else
  rgb   = (col.r | (col.g << 8) | (col.b << 16) | (col.a << 24));
#endif

  putPixel_32bpp(surface, x, y, rgb);
}

//
// This function sets the specified color on a SDL_Surface. Sanity checks are
// performed on the co-ordinates and the SDL_Surface is locked for you.
// Safe, but slow. For more speed, try the lower level access function.
//
static inline void getPixel(SDL_Surface *surface, uint16_t x, uint16_t y, color &col)
{
  uint32_t rgb;

  if (DEBUG2) {
    if (unlikely((x >= (uint32_t) surface->w) || (y >= (uint32_t) surface->h))) {
      DIE("getPixel out of range, pix %d,%d in size %d,%d", x, y, surface->w, surface->h);
    }
  }

  lock(surface);
  getPixel_32bpp(surface, x, y, &rgb);

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
}

static inline void getPixelFast(SDL_Surface *surface, uint16_t x, uint16_t y, color &col)
{
  uint32_t rgb;
  getPixel_32bpp(surface, x, y, &rgb);

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
}
#endif
