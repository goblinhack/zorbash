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
#include "my_level.h"
#include "my_thing.h"

bool Thing::exit_tick (void)
{_
    if (level->is_exit(mid_at.x, mid_at.y)) {
        return descend();
    }
    return false;
}

bool Thing::descend (void)
{_
    auto next_level = level->world_at + point3d(0, 0, 1);

    if (is_player()) {
        game->current_level = next_level;
        game->init_levels();
    }

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (!l) {
        if (is_player()) {
            UI_MINICON("The exit is permanently blocked!");
        }
        return false;
    }

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (l->is_entrance(x, y)) {
                if (is_player()) {
                    game->level = l;
                    UI_MINICON("You bravely descend");
                }

                log("move to new level entrance");
                move_to_immediately(fpoint(x, y));
                level_change(l);
                if (is_player()) {
                    l->player = this;
                    l->scroll_map_to_player();
                    l->minimap_valid = false;
                }
                update_light();

                log("moved to new level entrance");
                return true;
            }
        }
    }

    log("moved to new level entrance");
    return true;
}
