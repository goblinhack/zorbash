//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::health_boost (int v)
{_
    if (!v) {
        return;
    }

    auto old_health = get_stats_health();
    auto new_health = old_health + v;
    auto max_health = get_stats_health_max();
    new_health = std::min(new_health, max_health);
    set_stats_health(new_health);

    if (new_health >= max_health) {
        log("health boost not possible, maxxed at %d", new_health);
    } else {
        log("health boost by %d from %d to %d", v, old_health, new_health);
    }
}

bool Thing::is_bloodied (void)
{_
    return get_stats_health_pct() <= THING_HEALTH_BLOODIED_PCT1;
}

float Thing::get_stats_health_pct (void)
{_
    float pct =
        ((float)get_stats_health() / (float)get_stats_health_max()) * 100;
    return pct;
}
