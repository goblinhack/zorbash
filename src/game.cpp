/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_light.h"

class Game game;

static void game_place_blocks (class Dungeon *d,
                               std::string what,
                               int variant,
                               int block_width,
                               int block_height,
                               int tries)
{_
    while (tries--) {
        auto x = random_range(0, MAP_WIDTH - block_width + 1);
        auto y = random_range(0, MAP_HEIGHT - block_height + 1);

        auto can_place_wall_here = true;
        for (auto dx = 0; dx < block_width; dx++) {
            auto X = x + dx;
            for (auto dy = 0; dy < block_height; dy++) {
                auto Y = y + dy;

                if (d->is_oob(X, Y)) {
                    continue;
                }

                if (!d->is_wall_at(X, Y)) {
                    can_place_wall_here = false;
                    break;
                }

                /*
                 * We place large blocks and avoid splatting them with
                 * smaller ones here.
                 */
                if (game.state.map.is_wall[X][Y]) {
                    can_place_wall_here = false;
                    continue;
                }
            }

            if (!can_place_wall_here) {
                break;
            }
        }

        if (!can_place_wall_here) {
            continue;
        }

        auto cnt = 1;
        for (auto dy = 0; dy < block_height; dy++) {
            auto Y = y + dy;
            for (auto dx = 0; dx < block_width; dx++) {
                auto X = x + dx;
                game.state.map.is_wall[X][Y] = 1;

                auto s = what;
                s += ".";
                s += std::to_string(variant);
                s += ".";
                s += std::to_string(block_width);
                s += "x";
                s += std::to_string(block_height);
                s += ".";
                s += std::to_string(cnt);
                cnt++;

                auto t = thing_new(what, fpoint(X, Y));
                auto tile = tile_find(s);
                t->current_tileinfo = nullptr;
                t->current_tile = tile;
            }
        }
    }
}

static void game_place_lights (class Dungeon *d,
                               std::string what,
                               int variant,
                               int block_width,
                               int block_height,
                               int tries)
{_
    while (tries--) {
        auto x = random_range(0, MAP_WIDTH);
        auto y = random_range(0, MAP_HEIGHT);

        auto can_place_light_here = true;
        for (auto dx = 0; dx < block_width; dx++) {
            auto X = x + dx;
            for (auto dy = 0; dy < block_height; dy++) {
                auto Y = y + dy;

                if (d->is_wall_at(X, Y)) {
                    can_place_light_here = false;
                    break;
                }
            }
            if (!can_place_light_here) {
                break;
            }
        }

        if (!can_place_light_here) {
            continue;
        }

        if (random_range(0, 100) > 50) {
            continue;
        }

        color col;

        auto r = random_range(0, 100);
        if (r < 75) {
            col = GREEN;
        } else if (r < 95) {
            col = BLUE;
        } else {
            col = RED;
        }
        col.a = 50;

        (void) light_new(100, 2, fpoint(x, y), LIGHT_QUALITY_LOW, col);
    }
}

static void game_ramaining_place_blocks (class Dungeon *d,
                                         std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (game.state.map.is_wall[x][y]) {
                continue;
            }

            if (d->is_wall_at(x, y)) {
                (void) thing_new(what, fpoint(x, y));
            }
        }
    }
}

void game_display (void)
{_
    static int first = true;
    if (first) {
        int seed = 663;
        //seed = myrand();
        mysrand(seed);
        LOG("dungeon: create dungeon %u", seed);

        auto dungeon = new Dungeon(MAP_WIDTH, MAP_HEIGHT, 
                                   GRID_WIDTH, GRID_HEIGHT, seed);
_
        LOG("dungeon: create blocks");
        auto tries = 1000;
        game_place_blocks(dungeon, "wall1", 1, 6, 6, tries);
        game_place_blocks(dungeon, "wall1", 2, 6, 6, tries);

        game_place_blocks(dungeon, "wall1", 1, 6, 3, tries);
        game_place_blocks(dungeon, "wall1", 2, 6, 3, tries);

        game_place_blocks(dungeon, "wall1", 1, 3, 6, tries);
        game_place_blocks(dungeon, "wall1", 2, 3, 6, tries);

        game_place_blocks(dungeon, "wall1", 1, 3, 3, tries);
        game_place_blocks(dungeon, "wall1", 2, 3, 3, tries);
        game_place_blocks(dungeon, "wall1", 3, 3, 3, tries);
        game_place_blocks(dungeon, "wall1", 4, 3, 3, tries);

        game_place_blocks(dungeon, "wall1", 1, 2, 2, tries);
        game_place_blocks(dungeon, "wall1", 2, 2, 2, tries);

        game_place_blocks(dungeon, "wall1", 1, 2, 1, tries);
        game_place_blocks(dungeon, "wall1", 2, 2, 1, tries);
        game_place_blocks(dungeon, "wall1", 3, 2, 1, tries);
        game_place_blocks(dungeon, "wall1", 4, 2, 1, tries);

        game_place_blocks(dungeon, "wall1", 1, 1, 2, tries);
        game_place_blocks(dungeon, "wall1", 2, 1, 2, tries);
        game_place_blocks(dungeon, "wall1", 3, 2, 1, tries);
        game_place_blocks(dungeon, "wall1", 4, 2, 1, tries);
_
        game_place_lights(dungeon, "wall1", 4, 2, 1, tries);
_
        game_ramaining_place_blocks(dungeon, "wall1");
_
        for (auto x = 0; x < MAP_WIDTH; x++) {
            for (auto y = 0; y < MAP_HEIGHT; y++) {
                if (dungeon->is_monst_at(x, y)) {
                    (void) thing_new("monst1", fpoint(x, y));
                }

                if (dungeon->is_entrance_at(x, y)) {
                    (void) thing_new("player1", fpoint(x, y));
                }
            }
        }
_
        lights_calculate();
_
        LOG("dungeon: placed all blocks");
        thing_map_scroll_to_player();
    }
_
    first = false;

    /*
     * thing_render_all must come before thing_move_all as it populates
     * all the things into the map for collisions.
     */
    thing_render_all();
_
#if 0
    if (!game.editor_mode) {
        thing_move_all();
    }
#endif
}

uint8_t
game_mouse_motion (int32_t x, int32_t y,
                   int32_t wheelx, int32_t wheely)
{_
//    int mouse_held = mouse_down &&
//        time_have_x_tenths_passed_since(1, mouse_down_when);

CON("TBD %s", __FUNCTION__);
    return (false);
}

void
game_mouse_over (int32_t x, int32_t y,
                 int32_t wheelx, int32_t wheely)
{_
//    int mouse_held = mouse_down &&
//        time_have_x_tenths_passed_since(1, mouse_down_when);

CON("TBD %s", __FUNCTION__);
}

uint8_t
game_mouse_down (int32_t x, int32_t y, uint32_t button)
{_
CON("TBD %s", __FUNCTION__);
    return (false);
}

uint8_t
game_key_down (const struct SDL_KEYSYM *key)
{_
    if (game.state.player) {
        double d = 0.2;
        switch (key->sym) {
            case SDLK_LEFT:
              game.state.player->move_delta(fpoint(-d, 0));
              return (true);
            case SDLK_RIGHT:
              game.state.player->move_delta(fpoint(d, 0));
              return (true);
            case SDLK_UP:
              game.state.player->move_delta(fpoint(0, -d));
              return (true);
            case SDLK_DOWN:
              game.state.player->move_delta(fpoint(0, d));
              return (true);
        }
    }
    return (false);
}
