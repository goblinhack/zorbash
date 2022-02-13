//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"

int Thing::health_boost(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return false;
  }

  auto old_health = health_get();
  auto new_health = old_health + v;
  auto max_health = health_max();

  if (old_health >= max_health) {
    dbg("Health boost not possible, maxxed out already");
    return false;
  }

  new_health = std::min(new_health, max_health);
  health_set(new_health);

  if (new_health >= max_health) {
    dbg("Health boost not possible, maxxed at %d", new_health);
  } else {
    dbg("Health boost by %d from %d to %d", v, old_health, new_health);
  }
  return new_health - old_health;
}

bool Thing::health_boost_would_occur(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return false;
  }

  auto old_health = health_get();
  auto max_health = health_max();

  if (old_health >= max_health) {
    return false;
  }

  return true;
}

bool Thing::is_bloodied(void)
{
  TRACE_NO_INDENT();
  return health_pct_get() <= THING_HEALTH_BLOODIED_PCT1;
}

float Thing::health_pct_get(void)
{
  TRACE_NO_INDENT();
  float pct = ((float) health_get() / (float) health_max()) * 100;
  return pct;
}
