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
#include "my_ptrcheck.h"

void Thing::brazier_tick (void)
{_
    //
    // This is for if you land on a brazier
    //
    if (!level->is_brazier(mid_at.x, mid_at.y)) {
        return;
    }

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
        if (!t->is_brazier()) {
            continue;
        }

        //
        // Ignore knocked over braziers.
        //
        if (t->is_dead) {
            continue;
        }

        for (auto i = 0; i < 9; i++) {
            auto delta = get(all_deltas, pcg_random_range(0, (int)all_deltas.size()));
            if (try_to_shove(t, delta)) {
                if (!is_dead) {
                    if (is_player()) {
                        TOPCON("You knock over the brazier!");
                    }
                }
                return;
            }
        }

        if (!is_dead) {
            if (pcg_random_range(0, 100) < 20) {
                TOPCON("You stumble into the flames!");
                set_on_fire("stumbled into flames");
            }
        }
    } FOR_ALL_THINGS_END()
}
