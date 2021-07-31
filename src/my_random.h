#pragma once
#ifndef _MY_RANDOM_H_
#define _MY_RANDOM_H_

////////////////////////////////////////////////////////////////////////////
// Random numbers
////////////////////////////////////////////////////////////////////////////

//
// Enhanced random number generator.
//
#include "my_pcg_basic.h"

//
// For randomness that matters for reproducability.
//
#define pcq_rand()                        pcg32_random()
#define pcq_srand(a)                      pcg32_srandom(a, a)
#define pcq_random_range(a, b)           (pcg32_boundedrand((b) - (a)) + (a))
#define pcq_random_range_inclusive(a, b) (pcg32_boundedrand((b) - (a) + 1) + (a))

//
// For randomness that does not matter for reproducability.
//
#define non_pcq_rand()                       rand()
#define non_pcq_srand(a)                     srand(a)
#define non_pcq_random_range(a, b)           (rand() % ((b) - (a)) + (a))
#define non_pcq_random_range_inclusive(a, b) (rand() % ((b) - (a) + 1) + (a))

#endif
