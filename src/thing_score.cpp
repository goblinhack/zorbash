//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_log.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_string.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

//
// Lower level function than dead. Adds the thing to gc.
//
void Thing::score_add (Thingp victim)
{_
    if (victim->is_monst()) {
        auto score = get_danger_initial_level(victim);
        if (score > 0) {
            if (get_health() < get_health_initial() / 10) {
                TOPCON("%%fg=red$Glory kill x10 score!%%fg=reset$");
                incr_score(score * 10);
            } else {
                incr_score(score);
            }
        } else {
            //
            // Give something, but not a lot as it was not a challenge
            //
            incr_score(victim->get_health_initial());
        }
    }
}
