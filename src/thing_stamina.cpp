//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::stamina_boost (int v)
{_
    if (!v) {
        return;
    }

    auto old_stamina = get_stats_stamina();
    auto new_stamina = old_stamina + v;
    auto max_stamina = get_stats_stamina_max();
    new_stamina = std::min(new_stamina, max_stamina);
    set_stats_stamina(new_stamina);

    if (new_stamina >= max_stamina) {
        log("Stamina boost not possible, maxxed at %d", new_stamina);
    } else {
        log("Stamina boost by %d from %d to %d", v, old_stamina, new_stamina);
    }
}
