#pragma once
#ifndef _MY_RANDOM_HPP_
#define _MY_RANDOM_HPP_

////////////////////////////////////////////////////////////////////////////
// Random numbers
////////////////////////////////////////////////////////////////////////////

//
// Enhanced random number mob.
//
#include "my_pcg_basic.hpp"

//
// For randomness that matters for reproducability.
//
#define pcg_rand()                       pcg32_random()
#define pcg_srand(a)                     pcg32_srandom(a, a)
#define pcg_random_range(a, b)           (pcg32_boundedrand((b) - (a)) + (a))
#define pcg_random_range_inclusive(a, b) (pcg32_boundedrand((b) - (a) + 1) + (a))

//
// For randomness that does not matter for reproducability.
//
#define non_pcg_rand()                       rand()
#define non_pcg_srand(a)                     srand(a)
#define non_pcg_random_range(a, b)           (rand() % ((b) - (a)) + (a))
#define non_pcg_random_range_inclusive(a, b) (rand() % ((b) - (a) + 1) + (a))

#define d10000() ((int) pcg_random_range_inclusive(1, 10000))
#define d1000()  ((int) pcg_random_range_inclusive(1, 1000))
#define d100()   ((int) pcg_random_range_inclusive(1, 100))
#define d10()    ((int) pcg_random_range_inclusive(1, 10))
#define d11()    ((int) pcg_random_range_inclusive(1, 11))
#define d12()    ((int) pcg_random_range_inclusive(1, 12))
#define d13()    ((int) pcg_random_range_inclusive(1, 13))
#define d14()    ((int) pcg_random_range_inclusive(1, 14))
#define d15()    ((int) pcg_random_range_inclusive(1, 15))
#define d16()    ((int) pcg_random_range_inclusive(1, 16))
#define d17()    ((int) pcg_random_range_inclusive(1, 17))
#define d18()    ((int) pcg_random_range_inclusive(1, 18))
#define d19()    ((int) pcg_random_range_inclusive(1, 19))
#define d20()    ((int) pcg_random_range_inclusive(1, 20))
#define d2()     ((int) pcg_random_range_inclusive(1, 2))
#define d3()     ((int) pcg_random_range_inclusive(1, 3))
#define d4()     ((int) pcg_random_range_inclusive(1, 4))
#define d50()    ((int) pcg_random_range_inclusive(1, 50))
#define d5()     ((int) pcg_random_range_inclusive(1, 5))
#define d6()     ((int) pcg_random_range_inclusive(1, 6))
#define d7()     ((int) pcg_random_range_inclusive(1, 7))
#define d8()     ((int) pcg_random_range_inclusive(1, 8))
#define d9()     ((int) pcg_random_range_inclusive(1, 9))

#endif
