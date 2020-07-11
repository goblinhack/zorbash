//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::entrance_tick (void)
{_
    if (owner_get()) {
        return false;
    }

    if (!is_able_to_change_levels()) {
        return false;
    }

    if (level->world_at.z > 1) {
        if (level->is_entrance(mid_at.x, mid_at.y)) {
            return ascend();
        }
    }
    return false;
}

bool Thing::ascend (void)
{_
    if (!monstp) {
        return false;
    }

    //
    // No level change if too rapid
    //
    if (get_tick() - get_tick_last_level_change() <= 1) {
        return false;
    }

    auto next_level = level->world_at + point3d(0, 0, -1);
    game->init_level(next_level);

    if (is_player()) {
        game->current_level = next_level;
    }

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (!l) {
        if (is_player()) {
            MINICON("The entrance is permanently blocked!");
        }
        return false;
    }

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (l->is_exit(x, y)) {
                if (is_player()) {
                    game->level = l;
                    MINICON("You bravely ascend");
                }

                log("move to previous level exit");
                level_change(l);
                set_tick_last_level_change(get_tick());
                move_to_immediately(fpoint(x, y));
                if (is_player()) {
                    l->player = this;
                    l->scroll_map_to_player();
                    l->minimap_valid = false;
                    //
                    // Make sure all monsts on the new level are at the
                    // same tick or they will get lots of free attacks
                    //
                    l->update_all_ticks();
                }
                location_check();
                update_light();

                log("moved to previous level exit");
                return true;
            }
        }
    }

    log("moved to new level entrance");
    return true;
}
