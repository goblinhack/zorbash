//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::fall (float fall_height, timestamp_t ms)
{
    auto t = set_timestamp_bounce_begin(time_get_time_ms_cached());
    set_timestamp_bounce_end(t + ms);

    set_fall_height(fall_height);
    is_falling = true;
}

float Thing::get_fall (void)
{
    if (!is_falling) {
        return (0.0);
    }

    auto t = time_get_time_ms_cached();

    if (t >= get_timestamp_bounce_end()) {
        is_falling = false;
        log("end of falling");
        hide();
        fall_to_next_level();
        return (0);
    }

    float time_step =
        (float)(t - get_timestamp_bounce_begin()) /
        (float)(get_timestamp_bounce_end() - get_timestamp_bounce_begin());

    if (time_step > 0.8) {
        hide();
    }

    float height = get_fall_height() * time_step;

    return (height);
}
