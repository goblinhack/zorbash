//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Thing::kill (const char *reason)
{_
    if (is_dead) {
        return;
    }
    is_dead = true;

    //
    // Unwield weapons
    //
    unwield("owner is dead");

    if (is_player()) {
        MINICON("%s", reason);
        MINICON("%%fg=red$Congratulations, you are dead!%%fg=reset$");
        game->dead_select(reason);
    } else if (is_loggable_for_important_stuff()) {
        MINICON("%s is dead, %s", text_The().c_str(), reason);
    }

    const auto tpp = tp();
    if (unlikely(!tpp)) {
        ERR("no tp");
    } else {
        if (is_corpse_on_death()) {
            if (tpp->is_loggable_for_important_stuff()) {
                log("killed, leaves corpse");
            }

            level->set_is_corpse(mid_at.x, mid_at.y);

            if (tpp->is_bleeder()) {
                int splatters = random_range(2, 10);
                for (int splatter = 0; splatter < splatters; splatter++) {
                    auto tpp = tp_random_blood();
                    (void) thing_new(tpp->name(),
                                     fpoint(mid_at.x, mid_at.y),
                                     fpoint(0.25, 0.25));
                }
            }
            return;
        }

        if (tpp->is_loggable_for_important_stuff()) {
            log("killed");
        }
    }

    auto result = level->all_gc_things.insert(std::pair(id, this));
    if (result.second == false) {
        err("failed to insert into gc thing map");
    }
}

void Thing::kill (std::string &reason)
{_
    kill(reason.c_str());
}
