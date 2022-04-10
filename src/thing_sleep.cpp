//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"

void Thing::sleep(void)
{
  change_state(MONST_STATE_SLEEPING, "time to sleep");
  auto followers = all_followers_get();
  for (auto f : followers) {
    f->sleep();
  }
}
