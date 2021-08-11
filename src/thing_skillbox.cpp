//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_wid_skillbox.h"
#include "my_wid_thing_info.h"
#include "my_random.h"
#include "my_monst.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ui.h"

bool Thing::skillbox_id_insert (Thingp what)
{_
    dbg("Skillbox insert %s", what->to_string().c_str());
_
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

    int free_slot = -1;
    auto skillbox_items = player->monstp->skillbox_id.size();
    for (auto i = 0U; i < skillbox_items; i++) {
        auto tp_id = monstp->skillbox_id[i];
        if (!tp_id) {
            if (free_slot == -1) {
                free_slot = i;
            }
            continue;
        }

        auto tpp = tp_find(tp_id);
        if (!tpp) {
            continue;
        }

        if (what->tp() == tpp) {
            if (what->is_bag_item_not_stackable()) {
                //
                // Needs its own slot
                //
            } else {
                wid_skillbox_init();
                if ((game->state != Game::STATE_CHOOSING_TARGET) &&
                    (game->state != Game::STATE_MOVING_ITEMS) &&
                    (game->state != Game::STATE_WIELDING_ITEMS) &&
                    (game->state != Game::STATE_COLLECTING_ITEMS)) {
                    wid_thing_info_fini();
                }
                return true;
            }
        }
    }

    int item_slot = -1;
    if (free_slot != -1) {
        monstp->skillbox_id[free_slot] = what->tp_id;
        item_slot = free_slot;
    } else {
        if (skillbox_items >= UI_ACTIONBAR_MAX_ITEMS) {
            TOPCON("No space to carry %s which is not carried.",
                    what->text_the().c_str());
            return false;
        }

        monstp->skillbox_id.push_back(what->tp_id);
        item_slot = monstp->skillbox_id.size() - 1;
    }

    game->previous_slot = item_slot;

    wid_skillbox_init();
    if ((game->state != Game::STATE_CHOOSING_TARGET) &&
        (game->state != Game::STATE_MOVING_ITEMS) &&
        (game->state != Game::STATE_WIELDING_ITEMS) &&
        (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini();
    }
    level->skillbox_describe(item_slot);
    return true;
}

bool Thing::skillbox_id_remove (Thingp what)
{_
    dbg("Skillbox remove %s", what->to_string().c_str());
_
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

    auto immediate_owner = what->get_immediate_owner();
    if (immediate_owner) {
        immediate_owner->bag_remove(what);
    }

    auto skillbox_items = player->monstp->skillbox_id.size();
    for (auto i = 0U; i < skillbox_items; i++) {
        auto tp_id = monstp->skillbox_id[i];
        if (!tp_id) {
            continue;
        }
        auto tpp = tp_find(tp_id);
        if (!tpp) {
            continue;
        }

        if (what->tp() == tpp) {
            game->request_remake_skillbox = true;

            dbg("Remove slot");
            monstp->skillbox_id[i] = 0;

            if (!monstp->skillbox_id.size()) {
                game->skillbox_highlight_slot = {};
            } else {
                while (game->skillbox_highlight_slot >=
                    monstp->skillbox_id.size()) {
                    game->skillbox_highlight_slot--;
                }
            }

            level->skillbox_describe(game->skillbox_highlight_slot);
            wid_skillbox_init();
            if ((game->state != Game::STATE_CHOOSING_TARGET) &&
                (game->state != Game::STATE_MOVING_ITEMS) &&
                (game->state != Game::STATE_WIELDING_ITEMS) &&
                (game->state != Game::STATE_COLLECTING_ITEMS)) {
                wid_thing_info_fini();
            }
            return true;
        }
    }
    return false;
}

Thingp Level::skillbox_get (const uint32_t slot)
{_
    dbg("Skillbox get slot %d", slot);
_
    if (!player) {
        ERR("No player");
        return nullptr;
    }

    auto monstp = player->monstp;
    if (!monstp) {
        ERR("No monstp for player");
        return nullptr;
    }

    if (slot >= monstp->skillbox_id.size()) {
        LOG("Slot %d out of range, max %d", slot, (int)monstp->skillbox_id.size());
        return nullptr;
    }

    auto tp_id = get(monstp->skillbox_id, slot);
    if (!tp_id) {
        LOG("Slot %d has no tp", slot);
        return nullptr;
    }

    auto tpp = tp_find(tp_id);
    if (!tpp) {
        LOG("Slot %d has no valid tp", slot);
        return nullptr;
    }

    LOG("Slot %d has %s", slot, tpp->name().c_str());

    for (auto oid : monstp->skills) {
        auto o = thing_find(oid);
        if (o) {
            if (o->tp() == tpp) {
                if (DEBUG2) {
                    o->log("Got skillbox item %s", tpp->name().c_str());
                }
                return o;
            }
        }
    }

    LOG("Slot %d has skill tp %s that is not carried", slot,
        tpp->name().c_str());
    return nullptr;
}

Thingp Level::skillbox_get (void)
{
    return skillbox_get(game->skillbox_highlight_slot);
}

bool Level::skillbox_over (const uint32_t slot)
{_
    LOG("Skillbox: over skillbox slot %d", slot);
_
    if (!player) {
        LOG("Skillbox: ignore; no player");
        return false;
    }

    if (slot >= player->monstp->skillbox_id.size()) {
        LOG("Skillbox: ignore; slot out of range");
        return false;
    }

    auto oid = get(player->monstp->skillbox_id, slot);
    if (!oid) {
        LOG("Skillbox: ignore; nothing at that slot");
        return false;
    }

    Thingp what;

    if (slot != game->skillbox_highlight_slot) {
        LOG("Skillbox: request to remake skillbox due to highlight");
        game->request_remake_skillbox = true;
        game->skillbox_highlight_slot = slot;
        what = skillbox_describe(slot);
    } else {
        what = skillbox_describe(game->skillbox_highlight_slot);
    }

    if (!what) {
        LOG("Skillbox: no skill chosen");
        return false;
    }

    if (DEBUG2) {
        what->log("Over skillbox item");
    }
    return true;
}

bool Level::skillbox_chosen (const uint32_t slot)
{_
    LOG("Skillbox: chosen skillbox slot %d", slot);
_
    if (!player) {
        return false;
    }

    if (slot >= player->monstp->skillbox_id.size()) {
        LOG("Skillbox: nothing in slot %d", slot);
        return false;
    }

    LOG("Skillbox: request to remake skillbox");
    game->request_remake_skillbox = true;

    auto oid = get(player->monstp->skillbox_id, slot);
    if (!oid) {
        LOG("Skillbox: no skill at slot %d", slot);
        return false;
    }

    Thingp what;
    if (slot != game->skillbox_highlight_slot) {
        game->skillbox_highlight_slot = slot;
        what = skillbox_describe(slot);
    } else {
        what = skillbox_describe(game->skillbox_highlight_slot);
    }

    if (!what) {
        LOG("Skillbox: no thing at slot %d", slot);
        return false;
    }

    what->is_activated = !what->is_activated;
    if (DEBUG2) {
        what->log("Chosen skillbox item");
    }

    if (what->is_activated) {
        TOPCON("You activate %s skill.", what->text_the().c_str());
    } else {
        TOPCON("You deactivate %s skill.", what->text_the().c_str());
    }

    return true;
}

Thingp Level::skillbox_describe (const uint32_t slot)
{_
    LOG("Skillbox: describe slot %d", slot);
_
    auto what = skillbox_get(slot);
    if (what) {
        if (DEBUG2) {
            what->log("Skillbox: describe slot %d", slot);
        }
        what->describe_when_hovered_over_in_rightbar();
    } else {
        LOG("Skillbox: describe slot %d => nothing there", slot);
    }
    return what;
}
