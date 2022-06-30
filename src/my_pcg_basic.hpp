//
// PCG Random Number Generation for C.
//
// Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// For additional information about the PCG random number generation scheme,
// including its license and other licensing options, visit
//
//     http://www.pcg-random.org
//

//
// This code is derived from the full C implementation, which is in turn
// derived from the canonical C++ PCG implementation. The C++ version
// has many additional features and is preferable if you can use C++ in
// your project.
//

#pragma once
#ifndef _MY_PCG_BASIC_HPP_INCLUDED
#define _MY_PCG_BASIC_HPP_INCLUDED 1

#include <inttypes.h>

typedef struct pcg_state_setseq_64 pcg32_random_t;

extern int pcg_random_allowed;

extern uint32_t pcg32_random_r(pcg32_random_t *rng);
extern void     pcg32_srandom_r(pcg32_random_t *rng, uint64_t initstate, uint64_t initseq);
extern void     pcg32_srandom(uint64_t seed, uint64_t seq);
extern uint32_t pcg32_random(void);
extern uint32_t pcg32_boundedrand_r(pcg32_random_t *rng, uint32_t bound);
extern uint32_t pcg32_boundedrand(uint32_t bound);

#endif // PCG_BASIC_HPP_INCLUDED
