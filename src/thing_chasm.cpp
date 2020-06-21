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

bool Thing::chasm_tick (void)
{_
    if (is_falling) {
        return true;
    }

    if (level->is_chasm(mid_at.x, mid_at.y)) {
        return fall();
    }

    fall(10, 1000);
    return false;
}

bool Thing::fall_to_next_level (void)
{_
    if (!monstp) {
        return false;
    }

    auto next_level = level->world_at + point3d(0, 0, 1);

    if (is_player()) {
        game->current_level = next_level;
        game->init_levels();
    }

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (!l) {
        if (is_player()) {
            UI_MINICON("The chasm is permanently blocked!");
        }
        return false;
    }

    for (;;) {
        auto x = random_range(MAP_BORDER, MAP_WIDTH - MAP_BORDER);
        auto y = random_range(MAP_BORDER, MAP_HEIGHT - MAP_BORDER);

        if (level->is_entrance(x, y) ||
            level->is_monst(x, y)    ||
            level->is_rock(x, y)     ||
            level->is_wall(x, y)     ||
            level->is_exit(x, y)) {
            continue;
        }

        if (level->is_floor(x, y) ||
            level->is_lava(x, y)) {

            if (is_player()) {
                game->level = l;
                UI_MINICON("You tumble into the void!");
            }

            log("fall to next level");
            move_to_immediately(fpoint(x, y));
            level_change(l);
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
            update_light();

            log("finish fall to next level");
            return true;
        }
    }
}
