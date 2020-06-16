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

bool Thing::open_exit (Thingp it)
{_
    if (!it->is_exit()) {
        return false;
    }

    auto next_level = level->world_at + point3d(0, 0, 1);

    if (is_player()) {
        game->current_level = next_level;
        game->init_levels();
    }

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (l->is_entrance(x, y)) {
                if (is_player()) {
                    game->level = l;
                    MINICON("You bravely descend");
                }
                change_level(l);

                move_to_immediately(fpoint(x, y));
                if (is_player()) {
                    l->scroll_map_to_player();
                    l->player = this;
                }

                return true;
            }
        }
    }

    MINICON("The exit is forever blocked!");
    return false;
}
