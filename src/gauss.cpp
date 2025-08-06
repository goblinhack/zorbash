//
// Copyright goblinhack@gmail.com
//

#include "my_random.hpp"
#include <math.h> // do not remove

double gaussrand(double mean, double stddev)
{
  static double V1, V2, S;
  static int    phase = 0;
  double        val;

  if (phase == 0) {
    do {
      double U1 = pcg32_boundedrand((((uint32_t) -1)));
      double U2 = pcg32_boundedrand((((uint32_t) -1)));

      U1 /= (double) (((uint32_t) -1));
      U2 /= (double) (((uint32_t) -1));

      V1 = 2 * U1 - 1;
      V2 = 2 * U2 - 1;
      S  = V1 * V1 + V2 * V2;
    } while (S >= 1 || S == 0);

    val = V1 * sqrt(-2 * log(S) / S);
  } else {
    val = V2 * sqrt(-2 * log(S) / S);
  }

  phase = 1 - phase;

  val *= stddev;
  val += mean;

  return val;
}
