//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_MATH_UTIL_HPP_
#define _MY_MATH_UTIL_HPP_

double gaussrand(double mean, double stddev);

#ifdef __APPLE__
#define sincos(x, s, c)  __sincos(x, s, c)
#define sincosf(x, s, c) __sincosf(x, s, c)
#define sincos(x, s, c)  __sincos(x, s, c)
#endif

#undef SQUARED
#define SQUARED(x) ((x) * (x))

#define ROUNDUP(x, r) ((r) * floor(((x) + (r)) / (r)))

#undef DISTANCE
#define DISTANCE(xa, ya, xb, yb) sqrt((double) (SQUARED((xb) - (xa)) + SQUARED((yb) - (ya))))

#undef DISTANCE3f
#define DISTANCE3f(xa, ya, za, xb, yb, zb)                                                                           \
  sqrt((double) (SQUARED((xb) - (xa)) + SQUARED((yb) - (ya)) + SQUARED((zb) - (za))))

#define PI      3.14159265358979323846f          // pi
#define RAD_45  0.78539816339744830962f          // pi/4
#define RAD_90  1.57079632679489661923f          // pi/2
#define RAD_180 3.14159265358979323846f          // pi
#define RAD_360 (2.0f * 3.14159265358979323846f) // 2pi
#define RAD_270 (RAD_180 + RAD_90)
#endif
