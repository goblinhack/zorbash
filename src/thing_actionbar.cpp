//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_game_status.h"

void Thing::actionbar_particle (Thingp what, int slot)
{_
    //
    // No animations at the start
    //
    if (level->is_starting) {
        return;
    }

    if (what->is_collected_as_gold()) {
        std::string name = "gold";
        auto w = wid_find(name);
        if (!w) {
            con("could not find wid %s", name.c_str());
            return;
        }

        auto p = (w->abs_tl + w->abs_br) / 2;
        p.x = (game->config.inner_pix_width / ASCII_WIDTH) * p.x;
        p.y = (game->config.inner_pix_height / ASCII_HEIGHT) * p.y;

        int cnt = random_range(1, 10);
        for (int c = 0; c < cnt; c++) {
            point s = (last_blit_tl + last_blit_br) / 2;
            point j(random_range(0, TILE_WIDTH) - TILE_WIDTH / 2,
                    random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);
            std::string name = "gold1." + std::to_string(random_range(1, 8));
            level->new_external_particle(
                     s + j, p,
                     size(TILE_WIDTH / 2, TILE_HEIGHT / 2), 500,
                     tile_find_mand(name));
        }
    } else {
        std::string name = "actionbar icon" + std::to_string(slot);
        auto w = wid_find(name);
        if (!w) {
            con("could not find wid %s", name.c_str());
            return;
        }

        auto p = (w->abs_tl + w->abs_br) / 2;
        p.x = (game->config.inner_pix_width / ASCII_WIDTH) * p.x;
        p.y = (game->config.inner_pix_height / ASCII_HEIGHT) * p.y;

        level->new_external_particle(
                 (last_blit_tl + last_blit_br) / 2, p,
                 size(TILE_WIDTH, TILE_HEIGHT), 500,
                 tile_index_to_tile(what->tile_curr));
    }
}

//
// Particle from the actionbar to a target
//
void Thing::actionbar_particle (Thingp what, int slot, Thingp target)
{_
    //
    // No animations at the start
    //
    if (level->is_starting) {
        return;
    }

    point where_to = (target->last_blit_tl + target->last_blit_br) / 2;

    std::string name = "actionbar icon" + std::to_string(slot);
    auto w = wid_find(name);
    if (!w) {
        con("could not find wid %s", name.c_str());
        return;
    }

    auto p = (w->abs_tl + w->abs_br) / 2;
    p.x = (game->config.inner_pix_width / ASCII_WIDTH) * p.x;
    p.y = (game->config.inner_pix_height / ASCII_HEIGHT) * p.y;

    level->new_external_particle(p, where_to,
                                 size(TILE_WIDTH, TILE_HEIGHT), 500,
                                 tile_index_to_tile(what->tile_curr));
}

bool Thing::actionbar_id_insert (Thingp what)
{_
    auto player = level->player;
    if (!player) {
        return false;
    }

    if (!is_player()) {
        return false;
    }

    if (!monstp) {
        return false;
    }

    if (what->is_collected_as_gold()) {
        game_status_wid_init();
        incr_gold(what->get_gold_value());
        actionbar_particle(what, monstp->actionbar_id.size() - 1);
        what->dead("collected");
        return false;
    }

    auto actionbar_items = player->monstp->actionbar_id.size();
    for (auto i = 0U; i < actionbar_items; i++) {
        auto a = monstp->actionbar_id[i];
        if (!a) {
            continue;
        }
        auto t = level->thing_find(a);
        if (t->tp() == what->tp()) {
            game_status_wid_init();
            actionbar_particle(what, i);
            return true;
        }
    }

    if (actionbar_items >= UI_ACTIONBAR_MAX_ITEMS) {
        MINICON("No space to carry %s which is not carried",
                what->text_the().c_str());
        return false;
    }

    monstp->actionbar_id.push_back(what->id);
    game_status_wid_init();
    actionbar_particle(what, monstp->actionbar_id.size() - 1);
    return true;
}

bool Thing::actionbar_id_remove (Thingp what)
{_
    auto player = level->player;
    if (!player) {
        return false;
    }

    if (!is_player()) {
        return false;
    }

    if (!monstp) {
        return false;
    }

    auto actionbar_items = player->monstp->actionbar_id.size();
    for (auto i = 0U; i < actionbar_items; i++) {
        auto a = monstp->actionbar_id[i];
        if (!a) {
            continue;
        }
        auto t = level->thing_find(a);
        if (t->tp() == what->tp()) {
            monstp->actionbar_id.erase(monstp->actionbar_id.begin() + i);
            game_status_wid_init();
            return true;
        }
    }
    return false;
}

bool Thing::actionbar_id_remove (Thingp what, Thingp target)
{_
    auto player = level->player;
    if (!player) {
        return false;
    }

    if (!is_player()) {
        return false;
    }

    if (!monstp) {
        return false;
    }

    auto actionbar_items = player->monstp->actionbar_id.size();
    for (auto i = 0U; i < actionbar_items; i++) {
        auto a = monstp->actionbar_id[i];
        if (!a) {
            continue;
        }
        auto t = level->thing_find(a);
        if (t->tp() == what->tp()) {
            monstp->actionbar_id.erase(monstp->actionbar_id.begin() + i);
            game_status_wid_init();
            actionbar_particle(what, i, target);
            return true;
        }
    }
    return false;
}

int Thing::actionbar_id_slot_count (const int slot)
{_
    auto a = monstp->actionbar_id[slot];
    if (!a) {
        return 0;
    }

    if (!monstp) {
        return 0;
    }

    auto t = level->thing_find(a);
    if (!t) {
        return 0;
    }

    auto count = 0;
    for (auto oid : monstp->carrying) {
        auto o = level->thing_find(oid);
        if (o->tp() == t->tp()) {
            count++;
        }
    }

    return count;
}
