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

#define myrand()                     pcg32_random()
#define mysrand(a)                   pcg32_srandom(a, a)

#define random_range(a, b)           (pcg32_boundedrand((b) - (a)) + (a))
#define random_range_inclusive(a, b) (pcg32_boundedrand((b) - (a) + 1) + (a))

//
// Use this for display related randomness, not things
//
#define sysrand()                    rand()

#endif
