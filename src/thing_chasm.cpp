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
    if (owner_get()) {
        return false;
    }

    if (is_falling) {
        return true;
    }

    if (level->is_chasm(mid_at.x, mid_at.y)) {
        fall(10, 750);
        wobble(360);
        return true;
    }

    return false;
}

bool Thing::fall_to_next_level (void)
{_
    if (!monstp) {
        return false;
    }

    log("fall to next level");

    auto next_level = level->world_at + point3d(0, 0, 1);
    game->init_level(next_level);
    if (is_player()) {
        game->current_level = next_level;
    }

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (!l) {
        MINICON("The chasm is permanently blocked!");
        return false;
    }

    for (;;) {
        auto x = random_range(MAP_BORDER, MAP_WIDTH - MAP_BORDER);
        auto y = random_range(MAP_BORDER, MAP_HEIGHT - MAP_BORDER);

        if (!level->is_dungeon(x, y)) {
            continue;
        }

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
                MINICON("You tumble into the void!");
            } else {
                MINICON("%s tumbles into the void!", text_The().c_str());
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
            set_fall_height(0);
            wobble(90);
            visible();

            auto damage = random_range(20, 50);
            auto h = decr_stats_health(damage);
            if (is_player()) {
                MINICON("%%fg=red$You take %u fall damage!%%fg=reset$", damage);
            }
            bounce(2.0 /* height */, 0.5 /* fade */, 100, 3);
            level->thing_new(tp_random_blood_splatter()->name(), mid_at);
            if (h <= 0) {
                h = set_stats_health(0);
                auto reason = std::string("Killed by falling");
                dead(nullptr, reason);
            }

            log("finish fall to next level");
            return true;
        }
    }
}
