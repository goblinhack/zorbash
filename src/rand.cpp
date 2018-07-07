/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_main.h"
#include "my_math_util.h"

double gaussrand (double mean, double stddev)
{_
    static double V1, V2, S;
    static int phase = 0;
    double val;

    if (phase == 0) {
        do {
            double U1 = pcg32_boundedrand((((uint32_t)-1)));
            double U2 = pcg32_boundedrand((((uint32_t)-1)));

            U1 /= (double) (((uint32_t)-1));
            U2 /= (double) (((uint32_t)-1));

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while (S >= 1 || S == 0);

        val = V1 * sqrt(-2 * log(S) / S);
    } else {
        val = V2 * sqrt(-2 * log(S) / S);
    }

    phase = 1 - phase;

    val *= stddev;
    val += mean;

    return (val);
}

double gauss (const double m, const double s)
{_
    static int use_last = 0;
    static double y2;
    double x1, x2, w, y1;

    if (use_last) {
        y1 = y2;
    } else {
        do { // ming don't have random
            x1 = 2.0 * ((double)myrand() / (double)(((uint32_t)-1))) - 1.0;
            x2 = 2.0 * ((double)myrand() / (double)(((uint32_t)-1))) - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);

        w = sqrt((-2.0 * log(w)) / w);
        y1 = x1 * w;
        y2 = x2 * w;
    }

    use_last = !use_last;

    return (m + y1 * s);
}
