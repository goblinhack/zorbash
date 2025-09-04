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
#define pcg_random_range(a, b)           ((b) > (a) ? pcg32_boundedrand((b) - (a)) + (a) : (a))
#define pcg_random_range_inclusive(a, b) ((b) > (a) ? pcg32_boundedrand((b) - (a) + 1) + (a) : (a))

//
// For randomness that does not matter for reproducability.
//
#define non_pcg_rand()                       rand()
#define non_pcg_srand(a)                     srand(a)
#define non_pcg_random_range(a, b)           ((b) > (a) ? rand() % ((b) - (a)) + (a) : (a))
#define non_pcg_random_range_inclusive(a, b) ((b) > (a) ? rand() % ((b) - (a) + 1) + (a) : (a))

#endif
