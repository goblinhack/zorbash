//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_tile.h"
#include "my_thing.h"

int Thing::health_boost (int v)
{_
    if (!v) {
        return false;
    }

    auto old_health = get_health();
    auto new_health = old_health + v;
    auto max_health = get_health_max();

    if (old_health >= max_health) {
        dbg("Health boost not possible, maxxed out already");
        return false;
    }

    new_health = std::min(new_health, max_health);
    set_health(new_health);

    if (new_health >= max_health) {
        dbg("Health boost not possible, maxxed at %d", new_health);
    } else {
        dbg("Health boost by %d from %d to %d", v, old_health, new_health);
    }
    return new_health - old_health;
}

bool Thing::health_boost_would_occur (int v)
{_
    if (!v) {
        return false;
    }

    auto old_health = get_health();
    auto max_health = get_health_max();

    if (old_health >= max_health) {
        return false;
    }

    return true;
}

bool Thing::is_bloodied (void)
{_
    return get_health_pct() <= THING_HEALTH_BLOODIED_PCT1;
}

float Thing::get_health_pct (void)
{_
    float pct =
        ((float)get_health() / (float)get_health_max()) * 100;
    return pct;
}
