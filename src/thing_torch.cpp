//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::torch_tick (void)
{_
    if (level->is_torch(mid_at.x, mid_at.y)) {
        static const std::vector<fpoint> all_deltas = {
            fpoint(-1, -1),
            fpoint( 1, -1),
            fpoint(-1,  1),
            fpoint( 1,  1),
            fpoint(0, -1),
            fpoint(-1, 0),
            fpoint(1, 0),
            fpoint(0, 1),
        };

        FOR_ALL_THINGS_AT_DEPTH(level, t, mid_at.x, mid_at.y, MAP_DEPTH_OBJ) {
            auto tpp = t->tp();
            if (!tpp->is_torch()) {
                continue;
            }

            for (auto i = 0; i < 9; i++) {
                auto delta = get(all_deltas, random_range(0, (int)all_deltas.size()));
                if (try_to_shove(t, delta)) {
                    if (is_player()) {
                        MINICON("You knock over the torch!");
                    }
                    return;
                }
            }

            if (random_range(0, 100) < 20) {
                MINICON("You stumble into the flames!");
                set_on_fire();
            }
        } FOR_ALL_THINGS_END()
    }
}
