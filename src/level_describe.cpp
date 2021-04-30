//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"
#include "my_wid_bag.h"
#include "my_globals.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"
#include "my_sdl.h"
#include "my_template.h"

void Level::describe (fpoint p)
{
    if (game->state == Game::STATE_MOVING_ITEMS || 
        game->state == Game::STATE_COLLECTING_ITEMS) {
        return;
    }

    BOTCON(" ");

    std::vector<Thingp> hover_over_things;
    hover_over = nullptr;

    FOR_ALL_ACTIVE_THINGS(this, t, p.x, p.y) {
        int x = p.x;
        int y = p.y;
        if (!is_lit(x, y) && !is_visited(x, y)) {_
            continue;
        }

        if (t->is_fire()) { t->topcon("XXX describe"); }

        if (t->get_immediate_owner() ||
            t->is_cursor() ||
            t->is_player() ||
            t->is_cursor_path() ||
            t->is_the_grid) {
            continue;
        }

        if (t->is_described_when_hovering_over()) {
            t->describe_when_hovering_over();

            if (t->long_text_description() != "") {
                push_back_if_unique(hover_over_things, t);
            }
        }

        if (!hover_over) {
            hover_over = t;
        }
    } FOR_ALL_THINGS_END()

    FOR_ALL_INTERESTING_THINGS(this, t, p.x, p.y) {
        int x = p.x;
        int y = p.y;
        if (!is_lit(x, y) && !is_visited(x, y)) {_
            continue;
        }

        if (t->get_immediate_owner() ||
            t->is_cursor() ||
            t->is_cursor_path() ||
            t->is_the_grid) {
            continue;
        }

        if (t->is_described_when_hovering_over()) {
            t->describe_when_hovering_over();

            if (t->long_text_description() != "") {
                push_back_if_unique(hover_over_things, t);
            }
        }

        if (!hover_over) {
            hover_over = t;
        }
    } FOR_ALL_THINGS_END()

    FOR_ALL_THINGS(this, t, p.x, p.y) {
        int x = p.x;
        int y = p.y;
        if (!is_lit(x, y) && !is_visited(x, y)) {_
            continue;
        }

        if (t->get_immediate_owner() ||
            t->is_cursor() ||
            t->is_cursor_path() ||
            t->is_the_grid) {
            continue;
        }

        if (t->is_described_when_hovering_over()) {
            t->describe_when_hovering_over();

            if (t->long_text_description() != "") {
                push_back_if_unique(hover_over_things, t);
            }
        }

        if (!hover_over) {
            hover_over = t;
        }
    } FOR_ALL_THINGS_END()

    if (hover_over_things.size()) {
        game->wid_thing_info_create_when_hovering_over(hover_over_things);
    }
}

void Level::describe (Thingp t)
{
    if (game->state == Game::STATE_MOVING_ITEMS || 
        game->state == Game::STATE_COLLECTING_ITEMS) {
        return;
    }

    if (!t->is_described_when_hovering_over()) {
        return;
    }

    if (t->long_text_description() == "") {
        t->show_botcon_description();
        return;
    }

    wid_thing_info_fini();
    std::vector<Thingp> hover_over_things;
    hover_over_things.push_back(t);
    game->wid_thing_info_create_when_hovering_over(hover_over_things);
}
