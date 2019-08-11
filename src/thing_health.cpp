//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"

void Thing::health_boost (int v)
{
    auto old_health = get_health();
    auto new_health = old_health + v;
    new_health = std::min(new_health, get_health_max());
    set_health(new_health);
    log("health boost %d, %d -> %d", v, old_health, new_health);
}
