//
// Copyright goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::discord(void)
{
  dbg("Discord");

  release_followers();
  unleash_minions();
  leader_unset();

  if (maybe_aip()) {
    aip()->thing_friends.clear();
    aip()->perma_friends.clear();
  }

  is_discorded = true;
}
