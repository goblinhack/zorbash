//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"

void Thing::torch_tick (void)
{_
    //
    // This is for if you land on a torch
    //
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

            if (t->is_dead) {
                continue;
            }

            for (auto i = 0; i < 9; i++) {
                auto delta = get(all_deltas, random_range(0, (int)all_deltas.size()));
                if (try_to_shove(t, delta)) {
                    if (!is_dead) {
                        if (is_player()) {
                            MINICON("You knock over the torch!");
                        }
                    }
                    return;
                }
            }

            if (!is_dead) {
                if (random_range(0, 100) < 20) {
                    MINICON("You stumble into the flames!");
                    set_on_fire("stumedled into flames");
                }
            }
        } FOR_ALL_THINGS_END()
    }
}
