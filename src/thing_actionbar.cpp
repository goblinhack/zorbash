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

    std::string name = "actionbar icon" + std::to_string(slot);
    auto w = wid_find(name);
    if (!w) {
        con("could not find wid %s", name.c_str());
        return;
    }

    auto p = (w->abs_tl + w->abs_br) / 2;

    p.x = (game->config.inner_pix_width / ASCII_WIDTH) * p.x;
    p.y = (game->config.inner_pix_height / ASCII_HEIGHT) * p.y;

    level->new_particle((last_blit_tl + last_blit_br) / 2, p, 200,
                        tile_index_to_tile(what->tile_curr));
}

bool Thing::actionbar_id_insert (Thingp what)
{_
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
        auto t = thing_find(a);
        if (t->tp() == what->tp()) {
            game_status_wid_init();
            actionbar_particle(what, i);
            return true;
        }
    }

    if (actionbar_items >= ACTIONBAR_MAX_ITEMS) {
        MINICON("No space to carry %s which is not carried",
                what->text_The().c_str());
        return false;
    }

    monstp->actionbar_id.push_back(what->id);
    game_status_wid_init();
    actionbar_particle(what, monstp->actionbar_id.size() - 1);
    return true;
}

bool Thing::actionbar_id_remove (Thingp what)
{_
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
        auto t = thing_find(a);
        if (t->tp() == what->tp()) {
            monstp->actionbar_id.erase(monstp->actionbar_id.begin() + i);
            game_status_wid_init();
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

    auto t = thing_find(a);
    if (!t) {
        return 0;
    }

    auto count = 0;
    for (auto oid : monstp->carrying) {
        auto o = thing_find(oid);
        if (o->tp() == t->tp()) {
            count++;
        }
    }

    return count;
}
