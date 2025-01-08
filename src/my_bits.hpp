//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_BITS_HPP_
#define _MY_BITS_HPP_

//
// Bit routines
//
#define ROUND64(x) (((x) + 0x3F) & ~0x3F)
#define ROUND32(x) (((x) + 0x1F) & ~0x1F)
#define ROUND16(x) (((x) + 0xF) & ~0xF)
#define ROUND8(x)  (((x) + 0x7) & ~0x7)
#define ROUND4(x)  (((x) + 0x3) & ~0x3)
#define ROUND2(x)  (((x) + 0x1) & ~0x1)

#define MULTIPLE_BITS(bitmask) ((bitmask) & ((bitmask) - 1))

#define BITS_PER_SLOT(_array_) (sizeof(_array_[ 0 ]) * 8)

#define BIT_SET(bit, _array_)                                                                                        \
  ((_array_)[ (bit) / BITS_PER_SLOT(_array_) ] |= ((unsigned) 1 << ((bit) % BITS_PER_SLOT(_array_))))

#define BIT_CLR(bit, _array_)                                                                                        \
  ((_array_)[ (bit) / BITS_PER_SLOT(_array_) ] &= ~((unsigned) 1 << ((bit) % BITS_PER_SLOT(_array_))))

#define BIT_ISSET(bit, _array_)                                                                                      \
  ((_array_)[ (bit) / BITS_PER_SLOT(_array_) ] & ((unsigned) 1 << ((bit) % BITS_PER_SLOT(_array_))))

#define FIRST_BIT_IN_4BIT(_bitarr_)                                                                                  \
  (((_bitarr_) & 0x0F) ? (((_bitarr_) & 0x03) ? (((_bitarr_) & 0x01) ? 0 : 1) : (((_bitarr_) & 0x04) ? 2 : 3)) : 4)

#define FIRST_BIT_IN_8BIT(_bitarr_)                                                                                  \
  (((_bitarr_) & 0xFF)                                                                                               \
       ? (((_bitarr_) & 0x0F) ? FIRST_BIT_IN_4BIT(_bitarr_) : FIRST_BIT_IN_4BIT((_bitarr_) >> 4) + 4)                \
       : 8)

#define FIRST_BIT_IN_16BIT(_bitarr_)                                                                                 \
  (((_bitarr_) & 0xFFFF)                                                                                             \
       ? (((_bitarr_) & 0x00FF) ? FIRST_BIT_IN_8BIT(_bitarr_) : FIRST_BIT_IN_8BIT((_bitarr_) >> 8) + 8)              \
       : 16)

#define FIRST_BIT_IN_32BIT(_bitarr_)                                                                                 \
  ((_bitarr_ & 0xFFFFFFFF)                                                                                           \
       ? (((_bitarr_) & 0x0000FFFF) ? FIRST_BIT_IN_16BIT(_bitarr_) : FIRST_BIT_IN_16BIT((_bitarr_) >> 16) + 16)      \
       : 32)

#define FIRST_BIT_IN_64BIT(_bitarr_)                                                                                 \
  ((_bitarr_)                                                                                                        \
       ? (((_bitarr_) & 0xFFFFFFFF) ? FIRST_BIT_IN_32BIT(_bitarr_) : FIRST_BIT_IN_32BIT((_bitarr_) >> 32) + 32)      \
       : 64)

#define FIRST_FREEBIT_IN_4BIT(_bitarr_) FIRST_BIT_IN_4BIT(~(_bitarr_))

#define FIRST_FREEBIT_IN_8BIT(_bitarr_) FIRST_BIT_IN_8BIT(~(_bitarr_))

#define FIRST_FREEBIT_IN_16BIT(_bitarr_) FIRST_BIT_IN_16BIT(~(_bitarr_))

#define FIRST_FREEBIT_IN_32BIT(_bitarr_) FIRST_BIT_IN_32BIT(~(_bitarr_))

#define FIRST_FREEBIT_IN_64BIT(_bitarr_) FIRST_BIT_IN_64BIT(~(_bitarr_))

//
// bitcount
//
#define BITCOUNT(w)                                                                                                  \
  w = (0x55555555LU & w) + (0x55555555LU & (w >> 1));                                                                \
  w = (0x33333333LU & w) + (0x33333333LU & (w >> 2));                                                                \
  w = (0x0f0f0f0fLU & w) + (0x0f0f0f0fLU & (w >> 4));                                                                \
  w = (0x00ff00ffLU & w) + (0x00ff00ffLU & (w >> 8));                                                                \
  w = (0x0000ffffLU & w) + (0x0000ffffLU & (w >> 16));

static inline int bitcount(int w)
{
  w = (0x55555555LU & w) + (0x55555555LU & (w >> 1));
  w = (0x33333333LU & w) + (0x33333333LU & (w >> 2));
  w = (0x0f0f0f0fLU & w) + (0x0f0f0f0fLU & (w >> 4));
  w = (0x00ff00ffLU & w) + (0x00ff00ffLU & (w >> 8));
  w = (0x0000ffffLU & w) + (0x0000ffffLU & (w >> 16));

  return w;
}
#endif
