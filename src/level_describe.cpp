//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_main.h"
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
{_
    bool got_one_with_long_text = false;

    if (!player) {
        return;
    }

    if (player->is_dead) {
        return;
    }

    if (game->robot_mode) {
        return;
    }

    if (is_starting) {
        return;
    }

    dbg3("Describe %f,%f", p.x, p.y);
_
    if ((game->state == Game::STATE_MOVING_ITEMS) ||
        (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
        (game->state == Game::STATE_COLLECTING_ITEMS) ||
        (game->state == Game::STATE_WIELDING_ITEMS) ||
        (game->state == Game::STATE_ENCHANTING_ITEMS) ||
        (game->state == Game::STATE_SAVE_MENU) ||
        (game->state == Game::STATE_LOAD_MENU) ||
        (game->state == Game::STATE_QUIT_MENU) ||
        (game->state == Game::STATE_CHOOSING_SKILLS)) {
        dbg3("Describe %f,%f; no wrong state", p.x, p.y);
        return;
    }

    std::vector<Thingp> hover_over_things;
    hover_over = nullptr;

    FOR_ALL_THINGS_THAT_DO_STUFF(this, t, p.x, p.y) {
        int x = p.x;
        int y = p.y;
        IF_DEBUG3 {
            t->log("Active thing cand for describe");
        }
_
        if (!is_lit_currently(x, y) && !is_lit_ever(x, y)) {_
            IF_DEBUG3 {
                t->log("Ignore for describe, not lit or visited");
            }
            continue;
        }

        if (t->is_cursor() ||
            t->is_player() ||
            t->is_cursor_path() ||
            t->is_the_grid) {
            IF_DEBUG3 {
                t->log("Ignore for describe, boring");
            }
            continue;
        }

        //
        // Dead monst clog up the screen
        //
        if (t->is_monst() && t->is_dead) {
            IF_DEBUG3 {
                t->log("Ignore for describe, monst or dead");
            }
            continue;
        }

        if (t->get_immediate_owner()) {
            IF_DEBUG3 {
                t->log("Ignore for describe, has owner");
            }
            continue;
        }

        if (t->is_described_when_hovering_over()) {
            if (!t->text_description().empty() ||
                !t->long_text_description().empty()) {

                IF_DEBUG3 {
                    t->log("Add to describe");
                }
                got_one_with_long_text |= !t->long_text_description().empty();
                push_back_if_unique(hover_over_things, t);
            } else {
                IF_DEBUG3 {
                    t->log("Ignore for describe, no text");
                }
            }
        } else {
            IF_DEBUG3 {
                t->log("Ignore for describe, not described");
            }
        }

        if (!hover_over) {
            hover_over = t;
        }
    } FOR_ALL_THINGS_END()

    FOR_ALL_THINGS_THAT_INTERACT(this, t, p.x, p.y) {
        int x = p.x;
        int y = p.y;
        IF_DEBUG3 {
            t->log("Interesting thing cand for describe");
        }
_
        if (!is_lit_currently(x, y) && !is_lit_ever(x, y)) {_
            IF_DEBUG3 {
                t->log("Ignore for describe, not lit or visited");
            }
            continue;
        }

        if (t->is_cursor() ||
            t->is_player() ||
            t->is_cursor_path() ||
            t->is_the_grid) {
            IF_DEBUG3 {
                t->log("Ignore for describe, boring");
            }
            continue;
        }

        //
        // Dead monst clog up the screen
        //
        if (t->is_monst() && t->is_dead) {
            IF_DEBUG3 {
                t->log("Ignore for describe, monst or dead");
            }
            continue;
        }

        if (t->get_immediate_owner()) {
            IF_DEBUG3 {
                t->log("Ignore for describe, has owner");
            }
            continue;
        }

        if (t->is_described_when_hovering_over()) {
            if (!t->text_description().empty() ||
                !t->long_text_description().empty()) {
                IF_DEBUG3 {
                    t->log("Add to describe");
                }
                got_one_with_long_text |= !t->long_text_description().empty();
                push_back_if_unique(hover_over_things, t);
            } else {
                IF_DEBUG3 {
                    t->log("Ignore for describe, no text");
                }
            }
        } else {
            IF_DEBUG3 {
                t->log("Ignore for describe, not described");
            }
        }

        if (!hover_over) {
            hover_over = t;
        }
    } FOR_ALL_THINGS_END()

    FOR_ALL_THINGS(this, t, p.x, p.y) {
        int x = p.x;
        int y = p.y;
        IF_DEBUG3 {
            t->log("All thing cand for describe");
        }
_
        if (!is_lit_currently(x, y) && !is_lit_ever(x, y)) {_
            IF_DEBUG3 {
                t->log("Ignore for describe, not lit or visited");
            }
            continue;
        }

        if (t->get_immediate_owner() ||
            t->is_player() ||
            t->is_cursor() ||
            t->is_cursor_path() ||
            t->is_the_grid) {
            IF_DEBUG3 {
                t->log("Ignore for describe, boring");
            }
            continue;
        }

        //
        // Only show the player as fallback if we have nothing else
        //
        if (hover_over_things.size()) {
            if(t->is_player()) {
                IF_DEBUG3 {
                    t->log("Ignore for describe, showing something better");
                }
                continue;
            }

            //
            // Dead monst clog up the screen. Unless we have nothing else.
            //
            if (t->is_monst() && t->is_dead) {
                IF_DEBUG3 {
                    t->log("Ignore for describe, showing something better");
                }
                continue;
            }
        }

        if (t->is_described_when_hovering_over()) {
            if (!t->text_description().empty() ||
                !t->long_text_description().empty()) {
                got_one_with_long_text |= !t->long_text_description().empty();
                IF_DEBUG3 {
                    t->log("Add to describe");
                }
                push_back_if_unique(hover_over_things, t);
            } else {
                IF_DEBUG3 {
                    t->log("Ignore for describe, no text");
                }
            }
        } else {
            IF_DEBUG3 {
                t->log("Ignore for describe, not described");
            }
        }

        if (!hover_over) {
            hover_over = t;
        }
    } FOR_ALL_THINGS_END()

    if (!got_one_with_long_text) {
        dbg3("Describe %f,%f; found nothing with long text", p.x, p.y);
    }

    dbg3("Describe %f,%f; found %d things", p.x, p.y,
         (int)hover_over_things.size());

    if (!got_one_with_long_text || !hover_over_things.size()) {
        //
        // If we found nothing, then check to see if we are already showing
        // something of interest and if so, keep it.
        //
        auto o = game->current_wid_thing_info;
        if (o) {
            dbg3("Currently describing %s", o->to_string().c_str());
            if (o->is_hidden) {
                dbg3("Currently describing %s; prefer me over current1",
                    o->to_string().c_str());
            }

            //
            // If showing something under the player, then prefer
            // to keep showing that if nothing else.
            //
            if (o->mid_at == player->mid_at) {
                dbg3("Describe %s; prefer me over current2", o->to_string().c_str());
                return;
            }
        }

        if (wid_thing_info_window.size()) {
            auto o = wid_thing_info_window.front()->t;
            if (o) {
                dbg3("Currently describing %s", o->to_string().c_str());
                if (o->is_hidden) {
                    dbg3("Describe %s; prefer me over current3", o->to_string().c_str());
                    return;
                }

                if (o->mid_at == player->mid_at) {
                    dbg3("Describe %s; prefer me over current4", o->to_string().c_str());
                    return;
                }
            }
        }

        wid_thing_info_fini();
    }

    if (hover_over_things.size() > 1) {
        dbg3("Describe %f,%f; found %d things", p.x, p.y, (int) hover_over_things.size());
        game->wid_thing_info_create_when_hovering_over_list(hover_over_things);
        if (hover_over_things.size() > 1) {
            auto k = std::string(
                SDL_GetScancodeName(
                    (SDL_Scancode)game->config.key_wait_or_collect));
            std::string text;
            if (k == ".") {
                text = "Multiple things here. Press %%fg=yellow$" + k + "%%fg=reset$ to collect.";
            } else {
                text = "Multiple things here. %%fg=yellow$" + k + "%%fg=reset$ to collect.";
            }
            BOTCON("%s", text.c_str());
        }
    } else if (hover_over_things.size()) {
        dbg3("Describe %f,%f; found %d thing", p.x, p.y, (int) hover_over_things.size());
        game->wid_thing_info_create_when_hovering_over_list(hover_over_things);
        if (hover_over_things.size() > 1) {
            auto k = std::string(
                SDL_GetScancodeName(
                    (SDL_Scancode)game->config.key_wait_or_collect));
            std::string text;
            if (k == ".") {
                text = "Something is here. Press %%fg=yellow$" + k + "%%fg=reset$ to collect.";
            } else {
                text = "Something is here. %%fg=yellow$" + k + "%%fg=reset$ to collect.";
            }
            BOTCON("%s", text.c_str());
        }
    }
}

void Level::describe (Thingp t)
{_
    if (!player) {
        return;
    }

    if (player->is_dead) {
        return;
    }

    if (game->robot_mode) {
        return;
    }

    if (is_starting) {
        return;
    }

    if (!t) {
        err("Null thing");
        return;
    }

    dbg3("Describe %s", t->to_string().c_str());

    if ((game->state == Game::STATE_MOVING_ITEMS) ||
        (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
        (game->state == Game::STATE_COLLECTING_ITEMS) ||
        (game->state == Game::STATE_WIELDING_ITEMS) ||
        (game->state == Game::STATE_SAVE_MENU) ||
        (game->state == Game::STATE_LOAD_MENU) ||
        (game->state == Game::STATE_QUIT_MENU) ||
        (game->state == Game::STATE_ENCHANTING_ITEMS)) {
        dbg3("Describe %s; no wrong state", t->to_string().c_str());
        return;
    }

    if (!t->is_described_when_hovering_over()) {
        dbg3("Describe %s; no not described", t->to_string().c_str());
        return;
    }

    //
    // If we're trying to show the player, then don't do that
    // if we're showing something more interesting from the
    // inventory.
    //
    auto o = game->current_wid_thing_info;
    if (o) {
        dbg3("Currently Describe %s", o->to_string().c_str());
        if (o->is_hidden) {
            dbg3("Currently Describe %s; prefer me over current5",
                o->to_string().c_str());
        }

        //
        // If showing something under the player, then prefer
        // to keep showing that if nothing else.
        //
        if (o->mid_at == player->mid_at) {
            dbg3("Describe %s; prefer me over current6", o->to_string().c_str());
            return;
        }
    }

    if (wid_thing_info_window.size()) {
        auto o = wid_thing_info_window.front()->t;
        if (o) {
            dbg3("Describe %s", o->to_string().c_str());
            if (o->is_hidden) {
                dbg3("Describe %s; prefer me over current7", o->to_string().c_str());
                return;
            }

            if (o->mid_at == player->mid_at) {
                dbg3("Describe %s; prefer me over current8", o->to_string().c_str());
                return;
            }
        }
    }

    wid_thing_info_fini();

    if (t->long_text_description().empty()) {
        dbg3("Describe %s; has no text", t->to_string().c_str());
        t->show_botcon_description();
        return;
    }

    std::vector<Thingp> hover_over_things;
    hover_over_things.push_back(t);
    game->wid_thing_info_create_when_hovering_over_list(hover_over_things);
}
