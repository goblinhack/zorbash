//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Thing::update_light (bool force)
{_
    if (!is_player()) {
        return;
    }

    if (!is_blit_pos) {
        return;
    }

    if (is_hidden) {
        return;
    }

    if (!level) {
        return;
    }

    fpoint interp = get_interpolated_mid_at();
    point lit_at = make_point((int)(interp.x * TILE_WIDTH),
                              (int)(interp.y * TILE_HEIGHT)
                             );
    if (!force) {
        if (get_last_lit_at() == lit_at) {
            return;
        }
    }
    set_last_lit_at(lit_at);

    //
    // Alow distant lights to fade
    //
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            auto l = level->is_lit_no_check(x, y);
            if (l) {
                level->set_is_lit_no_check(x, y, l - 1);
            }
        }
    }

#if 0
    auto lc = get_light_count();
    size_t c = 0;
    for (auto l : get_light()) {
        l->calculate(c == lc - 1);
        c++;
    }

    level->lighting_valid = true;
#endif
}
