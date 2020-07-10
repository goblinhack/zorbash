//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::hunger_clock (void)
{_
    auto tpp = tp();

    //
    // Does this thing hunger?
    //
    if (!tpp->hunger_clock_freq_ms()) {
        return;
    }

    //
    // Update the hunger clock.
    //
    if (!time_have_x_ms_passed_since(tpp->hunger_clock_freq_ms(),
                                     get_timestamp_hunger_tick())) {
        return;
    }

    set_timestamp_hunger_tick(time_get_time_ms_cached());

    if (get_stats_health() > 1) {
        decr_stats_health();
    } else {
        //
        // starvation is just annoying for players
        //
        // dead("starved to death");
    }

    int hungry_at =
      (int) ((double) get_stats_health_max() *
             ((double) tpp->stats_health_hunger_pct() / 100.0));

    auto old_is_hungry = is_hungry;
    is_hungry = get_stats_health() < hungry_at;

    int starving_at =
      (int) ((double) get_stats_health_max() *
             ((double) tpp->stats_health_starving_pct() / 100.0));

    auto old_is_starving = is_starving;
    is_starving = get_stats_health() < starving_at;

    if (old_is_starving != is_starving) {
        if (is_starving) {
            log("is starving");
        } else {
            log("is no longer starving");
        }
    } else if (old_is_hungry != is_hungry) {
        if (is_hungry) {
            log("is hungry");
        } else {
            log("is no longer hungry");
        }
    }
}
