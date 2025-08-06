//
// Copyright goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::physical_training_tick(void)
{
  //
  // Place a limit on how much we can gain from training
  //
  if (physical_training() > 5) {
    return;
  }

  //
  // Improvements get harder over time
  //
  int no_pain_no_gain = 100 + physical_training() * 100;

  if (pcg_random_range(1, no_pain_no_gain) <= 1) {
    msg("You feel healthy from all this training!");
    health_max_incr(10);
    physical_training_incr();
  }

  if (pcg_random_range(1, no_pain_no_gain) <= 1) {
    msg("You feel stronger from all this training!");
    stat_str_incr();
    physical_training_incr();
  }

  if (pcg_random_range(1, no_pain_no_gain) <= 1) {
    msg("You feel robust from all this training!");
    stat_con_incr();
    physical_training_incr();
  }
}

////////////////////////////////////////////////////////////////////////////
// physical_training
////////////////////////////////////////////////////////////////////////////
int Thing::physical_training(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->physical_training);
  }
  return 0;
}

int Thing::physical_training_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->physical_training = v);
  return n;
}

int Thing::physical_training_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->physical_training -= v);
  return n;
}

int Thing::physical_training_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->physical_training += v);
  return n;
}

int Thing::physical_training_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->physical_training--);
  return n;
}

int Thing::physical_training_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->physical_training++);
  return n;
}
