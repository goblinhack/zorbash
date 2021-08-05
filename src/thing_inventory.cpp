//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"
#include "my_random.h"
#include "my_monst.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ui.h"

void Thing::inventory_particle (Thingp item, uint32_t slot)
{_
    dbg("Create inventory particle? %s", item->to_string().c_str());
_
    //
    // No animations at the start
    //
    if (level->is_starting) {
        dbg("Not while starting the level");
        return;
    }

    if (item->is_collected_as_gold()) {
        dbg("Inventory particle %s is collected as gold",
            item->to_string().c_str());

        std::string name = "gold and keys";
        auto w = wid_find(name);
        if (!w) {
            log("Could not find wid %s", name.c_str());
            return;
        }

        auto p = (w->abs_tl + w->abs_br) / 2;
        p.x = (int)(((float)game->config.game_pix_width /
                     (float)TERM_WIDTH) * (float)p.x);
        p.y = (int)(((float)game->config.game_pix_height /
                     (float)TERM_HEIGHT) * (float)p.y);

        int value = item->get_gold_value();
        int particle_count;
        if (item->is_gold()) {
            particle_count = value;
        } else {
            particle_count = 1;
        }

        auto player = level->player;
        if (player) {
            player->incr_score(value * 10);
            player->incr_gold(value);

            if (value > 1) {
                TOPCON("You collect %d gold coins.", value);
            } else {
                TOPCON("You collect a lone piece of gold.");
            }
        }

        dbg("Yes; create inventory particles");
        for (int c = 0; c < particle_count; c++) {
            point s = (last_blit_tl + last_blit_br) / 2;
            point j(pcq_random_range(0, TILE_WIDTH) - TILE_WIDTH / 2,
                    pcq_random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);
            std::string name = "gold1." + std::to_string(pcq_random_range(1, 8));
            level->new_external_particle(
                     s + j, p,
                     isize(TILE_WIDTH / 2, TILE_HEIGHT / 2),
                     2 * PARTICLE_SPEED_MS + c,
                     tile_find_mand(name), false,
                     false /* make_visible_at_end */);
        }
        return;
    }

    if (item->is_collect_as_keys()) {
        dbg("Inventory particle %s is collected as key",
            item->to_string().c_str());

        std::string name = "gold and keys";
        auto w = wid_find(name);
        if (!w) {
            log("Could not find wid %s", name.c_str());
            return;
        }

        TOPCON("You collect the key.");

        auto p = (w->abs_tl + w->abs_br) / 2;
	p.x = (int)(((float)game->config.game_pix_width /
                     (float)TERM_WIDTH) * (float)p.x);
	p.y = (int)(((float)game->config.game_pix_height /
                     (float)TERM_HEIGHT) * (float)p.y);

        point s = (last_blit_tl + last_blit_br) / 2;
        point j(pcq_random_range(0, TILE_WIDTH) - TILE_WIDTH / 2,
                pcq_random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);

        dbg("Yes; create inventory particle");
        std::string tile_name = "key.1";
        level->new_external_particle(
                 s + j, p,
                 isize(TILE_WIDTH / 2, TILE_HEIGHT / 2),
                 PARTICLE_SPEED_MS,
                 tile_find_mand(tile_name), false,
                 false /* make_visible_at_end */);
        return;
    }

    {
        std::string name = "inventory slot" + std::to_string(slot);
        auto w = wid_find(name);
        if (!w) {
            log("Could not find wid %s", name.c_str());
            return;
        }

        auto p = (w->abs_tl + w->abs_br) / 2;
        p.x = (int)(((float)game->config.game_pix_width /
                     (float)TERM_WIDTH) * (float)p.x);
        p.y = (int)(((float)game->config.game_pix_height /
                     (float)TERM_HEIGHT) * (float)p.y);

        dbg("Yes; create inventory particle");
        level->new_external_particle(
                 item->id,
                 (last_blit_tl + last_blit_br) / 2, p,
                 isize(TILE_WIDTH, TILE_HEIGHT),
                 PARTICLE_SPEED_MS,
                 tile_index_to_tile(item->tile_curr),
                 (item->is_dir_br() || item->is_dir_right() || item->is_dir_tr()),
                 false /* make_visible_at_end */);
    }
}

//
// Particle from the inventory to tp_id target
//
void Thing::inventory_particle (Thingp item,
                                uint32_t slot,
                                Thingp particle_target)
{_
    dbg("Create inventory particle %s with target %s",
        item->to_string().c_str(), particle_target->to_string().c_str());
_
    if (game->in_transit_item) {
        dbg("No; not while moving an item");
        return;
    }

    if (item->is_being_dropped) {
        //
        // Always show
        //
    } else {
        if ((game->state == Game::STATE_MOVING_ITEMS) ||
            (game->state == Game::STATE_WIELDING_ITEMS) ||
            (game->state == Game::STATE_COLLECTING_ITEMS)) {
            //
            // No animations when moving stuff around
            //
            dbg("No; not whil moving items");
            return;
        }
    }

    //
    // No animations at the start
    //
    if (level->is_starting) {
        dbg("No; not while level is starting");
        return;
    }

    //
    // We can throw from the inventory or from the player. I think it
    // looks better to throw from the player.
    //
    bool throw_from_inventory = false;
    point where_from;

    if (throw_from_inventory) {
        std::string name = "inventory slot" + std::to_string(slot);
        auto w = wid_find(name);
        if (!w) {
            log("Could not find wid %s", name.c_str());
            return;
        }

        where_from = (w->abs_tl + w->abs_br) / 2;
        where_from.x = (int)(((float)game->config.game_pix_width /
                             (float)TERM_WIDTH) * (float)where_from.x);
        where_from.y = (int)(((float)game->config.game_pix_height /
                             (float)TERM_HEIGHT) * (float)where_from.y);
    } else {
        where_from = (last_blit_tl + last_blit_br) / 2;
    }

    point where_to = (particle_target->last_blit_tl +
                      particle_target->last_blit_br) / 2;


    level->new_external_particle(item->id, where_from, where_to,
                                 isize(TILE_WIDTH, TILE_HEIGHT),
                                 PARTICLE_SPEED_MS,
                                 tile_index_to_tile(item->tile_curr),
                                 (item->is_dir_br() ||
                                  item->is_dir_right() ||
                                  item->is_dir_tr()),
                                 true /* make_visible_at_end */);
}

bool Thing::inventory_id_insert (Thingp item)
{_
    dbg("Inventory insert %s", item->to_string().c_str());
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

    if (item->is_collected_as_gold()) {
        wid_inventory_init();
        wid_thing_info_fini();
        inventory_particle(item, monstp->inventory_id.size() - 1);
        item->dead("by being collected");

        //
        // If we just picked up some gold snd other items are on the
        // ground that are not auto collected, then describe them
        //
        if (game->state == Game::STATE_NORMAL) {
            if (is_player() && check_anything_to_carry()) {
                level->describe(mid_at);
            }
        }

        return true;
    }

    if (item->is_collect_as_keys()) {
        wid_inventory_init();
        wid_thing_info_fini();
        incr_keys(1);
        inventory_particle(item, monstp->inventory_id.size() - 1);
        item->dead("by being collected");

        //
        // If we just picked up some keys and other items are on the
        // ground that are not auto collected, then describe them
        //
        if (game->state == Game::STATE_NORMAL) {
            if (is_player() && check_anything_to_carry()) {
                level->describe(mid_at);
            }
        }

        return true;
    }

    int free_slot = -1;
    auto inventory_items = player->monstp->inventory_id.size();
    for (auto i = 0U; i < inventory_items; i++) {
        auto tp_id = monstp->inventory_id[i];
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

        if (item->tp() == tpp) {
            if (item->is_bag_item_not_stackable()) {
                //
                // Needs its own slot
                //
            } else {
                wid_inventory_init();
                if ((game->state != Game::STATE_CHOOSING_TARGET) &&
                    (game->state != Game::STATE_MOVING_ITEMS) &&
                    (game->state != Game::STATE_WIELDING_ITEMS) &&
                    (game->state != Game::STATE_COLLECTING_ITEMS)) {
                    wid_thing_info_fini();
                }
                if (game->state != Game::STATE_CHOOSING_TARGET &&
                    game->state != Game::STATE_MOVING_ITEMS) {
                    inventory_particle(item, i);
                } else {
                    // no particle, too noisy
                }
                return true;
            }
        }
    }

    int item_slot = -1;
    if (free_slot != -1) {
        monstp->inventory_id[free_slot] = item->tp_id;
        item_slot = free_slot;
        game->previous_slot = item_slot;
    } else {
        if (inventory_items < UI_ACTIONBAR_MAX_ITEMS) {
            monstp->inventory_id.push_back(item->tp_id);
            item_slot = monstp->inventory_id.size() - 1;
            game->previous_slot = item_slot;
        }
    }

    wid_inventory_init();
    if ((game->state != Game::STATE_CHOOSING_TARGET) &&
        (game->state != Game::STATE_MOVING_ITEMS) &&
        (game->state != Game::STATE_WIELDING_ITEMS) &&
        (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini();
    }

    if (game->state != Game::STATE_CHOOSING_TARGET &&
        game->state != Game::STATE_MOVING_ITEMS) {
        inventory_particle(item, item_slot);
    } else {
        // no particle, too noisy
    }

    level->inventory_describe(item_slot);

    return true;
}

bool Thing::inventory_id_remove (Thingp item)
{_
    dbg("Inventory remove %s", item->to_string().c_str());
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

    auto immediate_owner = item->get_immediate_owner();
    if (immediate_owner) {
        immediate_owner->bag_remove(item);
    }

    auto inventory_items = player->monstp->inventory_id.size();
    for (auto i = 0U; i < inventory_items; i++) {
        auto tp_id = monstp->inventory_id[i];
        if (!tp_id) {
            continue;
        }
        auto tpp = tp_find(tp_id);
        if (!tpp) {
            continue;
        }

        if (item->tp() == tpp) {
            game->request_remake_inventory = true;

            inventory_particle(item, i, this);

            auto cnt = item_slot_count(i);
            dbg("Remove slot %d, count %d", i, cnt);
            if (cnt > 1) {_
                dbg("Decrement slot count");
            } else {_
                dbg("Remove slot");
                monstp->inventory_id[i] = 0;

                if (!monstp->inventory_id.size()) {
                    game->inventory_highlight_slot = {};
                } else {
                    while (game->inventory_highlight_slot >=
                        monstp->inventory_id.size()) {
                        game->inventory_highlight_slot--;
                    }
                }
            }

            level->inventory_describe(game->inventory_highlight_slot);
            wid_inventory_init();
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

bool Thing::inventory_id_remove (Thingp item, Thingp particle_target)
{_
    dbg("Inventory remove %s with target %s",
        item->to_string().c_str(), particle_target->to_string().c_str());
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

    auto immediate_owner = item->get_immediate_owner();
    if (immediate_owner) {
        immediate_owner->bag_remove(item);
    }

    auto inventory_items = player->monstp->inventory_id.size();
    for (auto i = 0U; i < inventory_items; i++) {
        auto tp_id = monstp->inventory_id[i];
        if (!tp_id) {
            continue;
        }
        auto tpp = tp_find(tp_id);
        if (!tpp) {
            continue;
        }

        if (item->tp() == tpp) {
            game->request_remake_inventory = true;

            if (particle_target) {
                inventory_particle(item, i, particle_target);
            }

            auto cnt = item_slot_count(i);
            dbg("Remove slot %d, count %d", i, cnt);
            if (cnt > 1) {_
                dbg("Decrement slot count");
            } else {_
                dbg("Remove slot");
                monstp->inventory_id.erase(monstp->inventory_id.begin() + i);

                if (!monstp->inventory_id.size()) {
                    game->inventory_highlight_slot = {};
                } else {
                    while (game->inventory_highlight_slot >=
                        monstp->inventory_id.size()) {
                        game->inventory_highlight_slot--;
                    }

                    level->inventory_describe(game->inventory_highlight_slot);
                }
            }

            wid_inventory_init();
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

int Thing::item_slot_charge_count (const uint32_t slot)
{_
    if (!monstp) {
        return 0;
    }

    auto tp_id = get(monstp->inventory_id, slot);
    if (!tp_id) {
        return 0;
    }

    auto tpp = tp_find(tp_id);
    if (!tpp) {
        return 0;
    }

    return item_count_including_charges(tpp);
}

int Thing::item_enchant_count (const uint32_t slot)
{_
    if (!monstp) {
        return 0;
    }

    auto tp_id = get(monstp->inventory_id, slot);
    if (!tp_id) {
        return 0;
    }

    for (auto oid : monstp->carrying) {
        auto o = game->level->thing_find(oid);
        if (o) {
            if (o->tp()->id == tp_id) {
                return o->get_enchant();
            }
        }
    }

    return 0;
}

int Thing::item_slot_count (const uint32_t slot)
{_
    auto tp_id = get(monstp->inventory_id, slot);
    if (!tp_id) {
        return 0;
    }

    if (!monstp) {
        return 0;
    }

    auto tpp = tp_find(tp_id);
    if (!tpp) {
        return 0;
    }

    return item_count_excluding_charges(tpp);
}

Thingp Level::inventory_get (const uint32_t slot)
{_
    dbg("Inventory get slot %d", slot);
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

    if (slot >= monstp->inventory_id.size()) {
        LOG("Slot %d out of range, max %d", slot, (int)monstp->inventory_id.size());
        return nullptr;
    }

    auto tp_id = get(monstp->inventory_id, slot);
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

    //
    // If stackable, then get the nth item
    //
    int nth = 0;
    if (tpp->is_bag_item_not_stackable()) {
        for (auto i = 0U; i < slot; i++) {
            auto tp_id = player->monstp->inventory_id[i];
            if (!tp_id) {
                continue;
            }
            auto otpp = tp_find(tp_id);
            if (otpp == tpp) {
                nth++;
            }
        }
    }

    for (auto oid : monstp->carrying) {
        auto o = thing_find(oid);
        if (o) {
            if (o->tp() == tpp) {
                if (unlikely(g_opt_debug2)) {
                    o->log("Got inventory item %s", tpp->name().c_str());
                }

                if (nth) {
                    nth--;
                    continue;
                }
                return o;
            }
        }
    }

    LOG("Slot %d has tp %s that is not carried", slot, tpp->name().c_str());
    return nullptr;
}

Thingp Level::inventory_get (void)
{
    LOG("Inventory: get highlight slot %d", game->inventory_highlight_slot);
    return inventory_get(game->inventory_highlight_slot);
}

bool Level::inventory_over (const uint32_t slot)
{_
    LOG("Inventory: over inventory slot %d", slot);
_
    if (!player) {
        LOG("Inventory: ignore; no player");
        return false;
    }

    if (slot >= player->monstp->inventory_id.size()) {
        LOG("Inventory: ignore; slot out of range");
        return false;
    }

    auto oid = get(player->monstp->inventory_id, slot);
    if (!oid) {
        LOG("Inventory: ignore; nothing at that slot");
        return false;
    }

    Thingp item;

    if (slot != game->inventory_highlight_slot) {
        LOG("Inventory: request to remake inventory");
        game->request_remake_inventory = true;
        game->inventory_highlight_slot = slot;
        LOG("Inventory: highlight slot %d", slot);
        item = inventory_describe(slot);
    } else {
        item = inventory_describe(game->inventory_highlight_slot);
    }

    if (!item) {
        return false;
    }

    if (unlikely(g_opt_debug2)) {
        item->log("Over inventory item");
    }
    return true;
}

bool Level::inventory_chosen (const uint32_t slot)
{_
    LOG("Inventory: chosen inventory slot %d", slot);
_
    if (!player) {
        return false;
    }

    if (slot >= player->monstp->inventory_id.size()) {
        return false;
    }

    LOG("Inventory: request to remake inventory");
    game->request_remake_inventory = true;

    auto oid = get(player->monstp->inventory_id, slot);
    if (!oid) {
        return false;
    }

    Thingp item;
    bool changed_highlight_slot = false;

    if (slot != game->inventory_highlight_slot) {
        game->inventory_highlight_slot = slot;
        changed_highlight_slot = true;
        LOG("Inventory: highlight slot %d", slot);

        item = inventory_describe(slot);
    } else {
        item = inventory_describe(game->inventory_highlight_slot);
    }

    if (!item) {
        return false;
    }

    if (unlikely(g_opt_debug2)) {
        item->log("Chosen inventory item");
    }

    describe(item);

    return true;
}

bool Level::inventory_assign (const uint32_t slot, Thingp item)
{_
    LOG("Inventory: assign inventory slot %d", slot);
_
    if (!player) {
        return false;
    }

    if (slot >= player->monstp->inventory_id.size()) {
        player->monstp->inventory_id.resize(slot + 1);
    }

    LOG("Inventory: request to remake inventory");
    game->request_remake_inventory = true;

    auto inventory_items = player->monstp->inventory_id.size();
    for (auto i = 0U; i < inventory_items; i++) {
        auto tp_id = player->monstp->inventory_id[i];
        if (!tp_id) {
            continue;
        }
        auto tpp = tp_find(tp_id);
        if (!tpp) {
            continue;
        }

        if (item->tp() == tpp) {
            player->monstp->inventory_id[i] = 0;
            if (i == game->inventory_highlight_slot) {
                game->inventory_highlight_slot = slot;
                LOG("Inventory: highlight slot %d", slot);
            }
        }
    }

    player->monstp->inventory_id[slot] = item->tp_id;
    game->request_remake_inventory = true;

    return true;
}

int Level::inventory_get_slot (Thingp item)
{_
    auto inventory_items = player->monstp->inventory_id.size();
    for (auto i = 0U; i < inventory_items; i++) {
        auto tp_id = player->monstp->inventory_id[i];
        if (!tp_id) {
            continue;
        }
        auto tpp = tp_find(tp_id);
        if (!tpp) {
            continue;
        }

        if (item->tp() == tpp) {
            return i;
        }
    }

    return -1;
}

Thingp Level::inventory_describe (const uint32_t slot)
{_
    LOG("Inventory: describe slot %d", slot);
_
    auto item = inventory_get(slot);
    if (item) {
        if (unlikely(g_opt_debug2)) {
            item->log("Inventory: describe slot %d", slot);
        }
        item->describe_when_hovered_over_in_rightbar();
    } else {
        LOG("Inventory: describe slot %d => nothing there", slot);
    }
    return item;
}
