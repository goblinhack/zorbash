//
// Copyright goblinhack@gmail.com
//

#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::aggression_pct(void)
{
  TRACE_NO_INDENT();

  int aggression = tp()->aggression_pct();

  if (is_able_to_follow()) {
    //
    // Followers are more cockey if they have a leader
    //
    auto l = leader();
    if (l) {
      //
      // If the leader is dead, be timid
      //
      if (l->is_dead) {
        return (aggression / 4);
      }

      //
      // If the leader is weak, be timid
      //
      if (l->health() < l->health_max() / 3) {
        return (aggression / 2);
      }

      //
      // A strong leader
      //
      aggression += 20;
    } else {
      aggression += 10 * follower_count();
    }
  }

  if (aggression > 100) {
    aggression = 100;
  }

  return aggression;
}
