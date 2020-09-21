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

bool Thing::chasm_tick (void)
{_
    if (owner_get()) {
        return false;
    }

    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_jumping) { 
        return true;
    }

    if (is_floating()) {
        return false;
    }

    if (level->is_chasm(mid_at.x, mid_at.y)) {
        log("over a chasm");
        fall(1, 750);
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

    auto where_to = level->world_at + point3d(0, 0, 1);
    game->init_level(where_to);
    if (is_player()) {
        game->current_level = where_to;
    }

    auto next_level = get(game->world.levels, where_to.x, where_to.y, where_to.z);
    if (!next_level) {
        MINICON("The chasm is permanently blocked!");
        return false;
    }

    auto tries = 0;
    for (;;) {
        int x;
        int y;

        //
        // Try close to where we are first; failing that anywhere will do.
        //
        if (tries < 1) {
            x = mid_at.x;
            y = mid_at.y;
        } else if (tries < 10) {
            x = mid_at.x + random_range(-MAP_BORDER, MAP_BORDER);
            y = mid_at.y + random_range(-MAP_BORDER, MAP_BORDER);
        } else if (tries < 100) {
            x = mid_at.x + random_range(-MAP_BORDER * 2, MAP_BORDER * 2);
            y = mid_at.y + random_range(-MAP_BORDER * 2, MAP_BORDER * 2);
        } else if (tries < 1000) {
            x = mid_at.x + random_range(-MAP_BORDER * 4, MAP_BORDER * 4);
            y = mid_at.y + random_range(-MAP_BORDER * 4, MAP_BORDER * 4);
        } else {
            x = random_range(MAP_BORDER, MAP_WIDTH - MAP_BORDER);
            y = random_range(MAP_BORDER, MAP_HEIGHT - MAP_BORDER);
        }
        tries++;

        if (next_level->is_oob(x, y)) {_
            continue;
        }

        log("try to fall to %d,%d", x, y);
        if (!next_level->is_dungeon(x, y)) {_
            log("no, out of dungeon");
            continue;
        }

        if (next_level->is_entrance(x, y)    ||
            next_level->is_monst(x, y)       ||
            next_level->is_rock(x, y)        ||
            next_level->is_door(x, y)        ||
            next_level->is_secret_door(x, y) ||
            next_level->is_generator(x, y)   ||
            next_level->is_chasm(x, y)       ||
            next_level->is_wall(x, y)        ||
            next_level->is_exit(x, y)) {_
            log("no, special tile");
            continue;
        }

        if (next_level->is_floor(x, y) ||
            next_level->is_lava(x, y)) {

            if (is_player()) {
                game->level = next_level;
                MINICON("%%fg=red$You tumble into the void!%%fg=reset$");
            } else {
                MINICON("%s tumbles into the void!", text_The().c_str());
            }

            log("land on the next level, change level then move to %d,%d", x, y);
            level_change(next_level);

            log("land on the next level, move to %d,%d", x, y);
            move_to_immediately(fpoint(x, y));

            if (is_player()) {
                next_level->player = this;
                next_level->scroll_map_to_player();
                next_level->update();
                //
                // Make sure all monsts on the new level are at the
                // same tick or they will get lots of free attacks
                //
                next_level->update_all_ticks();
            }

            set_fall_height(0);
            wobble(90);
            visible();

            //
            // Allow generators to fall without damage
            //
            int fall_damage = 0;
            if (is_player()) {
                fall_damage = random_range(20, 50);
            }

            if (is_potion() || is_generator() || is_monst()) {
                fall_damage = get_stats_health() / 2;
            }

            auto new_pos = make_point(mid_at);
            if (next_level->is_lava(new_pos)) {
                if (is_player()) {
                    MINICON("%%fg=orange$You plunge into lava! This must be the end for you!%%fg=reset$");
                }
                fall_damage *= 2;
            } else if (next_level->is_deep_water(new_pos)) {
                if (is_player()) {
                    MINICON("%%fg=yellow$The deep water lessens the fall!%%fg=reset$");
                }
                fall_damage /= 4;
            } else if (next_level->is_water(new_pos)) {
                if (is_player()) {
                    MINICON("%%fg=yellow$The water lessens the fall!%%fg=reset$");
                }
                fall_damage /= 2;
            }

            auto h = decr_stats_health(fall_damage);
            if (is_player()) {
                MINICON("%%fg=red$You take %u fall damage!%%fg=reset$", fall_damage);
            }

            bounce(2.0 /* height */, 0.5 /* fade */, 100, 3);
            next_level->thing_new(tp_random_attack_blood()->name(), mid_at);
            if (h <= 0) {
                h = set_stats_health(0);
                auto reason = std::string("killed by falling");
                dead(nullptr, reason);
            }

            next_level->scroll_map_to_player();
            update_light(true);

            log("finished fall to next level");
            return true;
        }

        log("no, not floor or lava");
    }
}
