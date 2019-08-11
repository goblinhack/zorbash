//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"

void Thing::hunger_clock (void)
{
    //
    // Does this thing hunger?
    //
    if (!tp_hunger_clock_freq_ms(tp)) {
        return;
    }

    //
    // Update the hunger clock.
    //
    if (!time_have_x_ms_passed_since(tp_hunger_clock_freq_ms(tp),
                                    hunger_tick_last_ms)) {
        return;
    }

    hunger_tick_last_ms = time_get_time_ms_cached();

    if (get_health() > 1) {
        decr_health();
    } else {
        //
        // starvation is just annoying for players
        //
        // dead("starved to death");
    }

    int hungry_at =
      (int) ((double) get_health_max() *
             ((double) tp_hunger_at_health_pct(tp) / 100.0));

    auto old_is_hungry = is_hungry;
    is_hungry = get_health() < hungry_at;

    int starving_at =
      (int) ((double) get_health_max() *
             ((double) tp_hunger_starving_at_health_pct(tp) / 100.0));

    auto old_is_starving = is_starving;
    is_starving = get_health() < starving_at;

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
