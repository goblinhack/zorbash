//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"

void Thing::inventory_particle (Thingp what, uint32_t slot)
{_
    log("Inventory particle %s", what->to_string().c_str());
_
    //
    // No animations at the start
    //
    if (level->is_starting) {
        log("Not while starting the level");
        return;
    }

    if (what->is_item_collected_as_gold()) {
        std::string name = "gold";
        auto w = wid_find(name);
        if (!w) {
            err("Could not find wid %s", name.c_str());
            return;
        }

        auto p = (w->abs_tl + w->abs_br) / 2;
        p.x = (int)(((float)game->config.inner_pix_width / (float)TERM_WIDTH) * (float)p.x);
        p.y = (int)(((float)game->config.inner_pix_height / (float)TERM_HEIGHT) * (float)p.y);

        int cnt = random_range(1, 10);
        for (int c = 0; c < cnt; c++) {
            point s = (last_blit_tl + last_blit_br) / 2;
            point j(random_range(0, TILE_WIDTH) - TILE_WIDTH / 2,
                    random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);
            std::string name = "gold1." + std::to_string(random_range(1, 8));
            level->new_external_particle(
                     s + j, p,
                     isize(TILE_WIDTH / 2, TILE_HEIGHT / 2), 
                     PARTICLE_SPEED_MS,
                     tile_find_mand(name), false,
                     false /* make_visible_at_end */);
        }
        return;
    }

    if (what->is_collect_as_keys()) {
        std::string name = "keys";
        auto w = wid_find(name);
        if (!w) {
            err("Could not find wid %s", name.c_str());
            return;
        }

        auto p = (w->abs_tl + w->abs_br) / 2;
	p.x = (int)(((float)game->config.inner_pix_width / (float)TERM_WIDTH) * (float)p.x);
	p.y = (int)(((float)game->config.inner_pix_height / (float)TERM_HEIGHT) * (float)p.y);

        point s = (last_blit_tl + last_blit_br) / 2;
        point j(random_range(0, TILE_WIDTH) - TILE_WIDTH / 2,
                random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);

        std::string tile_name = "key1.1";
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
        p.x = (int)(((float)game->config.inner_pix_width / (float)TERM_WIDTH) * (float)p.x);
        p.y = (int)(((float)game->config.inner_pix_height / (float)TERM_HEIGHT) * (float)p.y);

        level->new_external_particle(
                 what->id,
                 (last_blit_tl + last_blit_br) / 2, p,
                 isize(TILE_WIDTH, TILE_HEIGHT), 
                 PARTICLE_SPEED_MS,
                 tile_index_to_tile(what->tile_curr),
                 (what->is_dir_br() || what->is_dir_right() || what->is_dir_tr()),
                 false /* make_visible_at_end */);
    }
}

//
// Particle from the inventory to tp_id target
//
void Thing::inventory_particle (Thingp what, uint32_t slot,
                                Thingp particle_target)
{_
    log("Inventory particle %s with target %s",
        what->to_string().c_str(), particle_target->to_string().c_str());
_
    if (game->state == Game::STATE_MOVING_ITEMS || 
        game->state == Game::STATE_COLLECTING_ITEMS) {
        //
        // No animations when moving stuff around
        //
        return;
    }

    //
    // No animations at the start
    //
    if (level->is_starting) {
        return;
    }

    point where_to = (particle_target->last_blit_tl +
                      particle_target->last_blit_br) / 2;

    std::string name = "inventory slot" + std::to_string(slot);
    auto w = wid_find(name);
    if (!w) {
        log("Could not find wid %s", name.c_str());
        return;
    }

    auto p = (w->abs_tl + w->abs_br) / 2;
    p.x = (int)(((float)game->config.inner_pix_width / (float)TERM_WIDTH) * (float)p.x);
    p.y = (int)(((float)game->config.inner_pix_height / (float)TERM_HEIGHT) * (float)p.y);

    level->new_external_particle(what->id, p, where_to,
                                 isize(TILE_WIDTH, TILE_HEIGHT), 
                                 PARTICLE_SPEED_MS,
                                 tile_index_to_tile(what->tile_curr),
                                 (what->is_dir_br() || what->is_dir_right() || what->is_dir_tr()),
                                 true /* make_visible_at_end */);
}

bool Thing::inventory_id_insert (Thingp what)
{_
    log("Inventory insert %s", what->to_string().c_str());
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

    if (what->is_item_collected_as_gold()) {
        wid_inventory_init();
        wid_thing_info_fini();
        incr_gold(what->get_gold_value());
        inventory_particle(what, monstp->inventory_id.size() - 1);
        what->dead("collected");
        return false;
    }

    if (what->is_collect_as_keys()) {
        wid_inventory_init();
        wid_thing_info_fini();
        incr_keys(1);
        inventory_particle(what, monstp->inventory_id.size() - 1);
        what->dead("collected");
        return false;
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

        if (what->tp() == tpp) {
            if (what->is_item_not_stackable()) {
                //
                // Needs its own slot
                //
            } else {
                wid_inventory_init();
                if (game->state != Game::STATE_CHOOSING_TARGET &&
                    game->state != Game::STATE_MOVING_ITEMS &&
                    game->state != Game::STATE_COLLECTING_ITEMS) {
                    wid_thing_info_fini();
                }
                inventory_particle(what, i);
                return true;
            }
        }
    }

    int item_slot = -1;
    if (free_slot != -1) {
        monstp->inventory_id[free_slot] = what->tp_id;
        item_slot = free_slot;
    } else {
        if (inventory_items >= UI_ACTIONBAR_MAX_ITEMS) {
            MINICON("No space to carry %s which is not carried",
                    what->text_the().c_str());
            return false;
        }

        monstp->inventory_id.push_back(what->tp_id);
        item_slot = monstp->inventory_id.size() - 1;
    }

    game->previous_slot = item_slot;

    wid_inventory_init();
    if (game->state != Game::STATE_CHOOSING_TARGET &&
        game->state != Game::STATE_MOVING_ITEMS &&
        game->state != Game::STATE_COLLECTING_ITEMS) {
        wid_thing_info_fini();
    }
    inventory_particle(what, item_slot);
    level->inventory_describe(item_slot);
    return true;
}

bool Thing::inventory_id_remove (Thingp what)
{_
    log("Inventory remove %s", what->to_string().c_str());
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

        if (what->tp() == tpp) {
            game->request_remake_inventory = true;

            inventory_particle(what, i, this);

            auto cnt = inventory_id_slot_count(i);
            log("Remove slot %d, count %d", i, cnt);
            if (cnt > 1) {_
                log("Decrement slot count");
            } else {_
                log("Remove slot");
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
            if (game->state != Game::STATE_CHOOSING_TARGET &&
                game->state != Game::STATE_MOVING_ITEMS && 
                game->state != Game::STATE_COLLECTING_ITEMS) {
                wid_thing_info_fini();
            }
            return true;
        }
    }
    return false;
}

bool Thing::inventory_id_remove (Thingp what, Thingp particle_target)
{_
    log("Inventory remove %s with target %s",
        what->to_string().c_str(), particle_target->to_string().c_str());
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

        if (what->tp() == tpp) {
            game->request_remake_inventory = true;

            if (particle_target) {
                inventory_particle(what, i, particle_target);
            }

            auto cnt = inventory_id_slot_count(i);
            log("Remove slot %d, count %d", i, cnt);
            if (cnt > 1) {_
                log("Decrement slot count");
            } else {_
                log("Remove slot");
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
            if (game->state != Game::STATE_CHOOSING_TARGET &&
                game->state != Game::STATE_MOVING_ITEMS &&
                game->state != Game::STATE_COLLECTING_ITEMS) {
                wid_thing_info_fini();
            }
            return true;
        }
    }

    return false;
}

int Thing::inventory_id_slot_count (const uint32_t slot)
{_
    log("Inventory get slot count %d", slot);
_
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

    auto count = 0;
    for (auto oid : monstp->carrying) {
        auto o = level->thing_find(oid);
        if (!o) {
            continue;
        }

        if (o->tp() == tpp) {
            count++;
            if (o->is_item_not_stackable()) {
                count = 1;
            }
        }
    }

    return count;
}

Thingp Level::inventory_get (const uint32_t slot)
{_
    log("Inventory get slot %d", slot);
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

    for (auto oid : monstp->carrying) {
        auto o = thing_find(oid);
        if (o) {
            if (o->tp() == tpp) {
                o->log("Got inventory item %s", tpp->name().c_str());
                return o;
            }
        }
    }

    LOG("Slot %d has tp %s that is not carried", slot, tpp->name().c_str());
    return nullptr;
}

Thingp Level::inventory_get (void)
{
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

    Thingp what;

    if (slot != game->inventory_highlight_slot) {
        LOG("Inventory: request to remake inventory");
        game->request_remake_inventory = true;
        game->inventory_highlight_slot = slot;
        what = inventory_describe(slot);
    } else {
        what = inventory_describe(game->inventory_highlight_slot);
    }

    if (!what) {
        return false;
    }

    what->log("Over inventory item");
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

    Thingp what;
    bool changed_highlight_slot = false;

    if (slot != game->inventory_highlight_slot) {
        game->inventory_highlight_slot = slot;
        changed_highlight_slot = true;

        what = inventory_describe(slot);
    } else {
        what = inventory_describe(game->inventory_highlight_slot);
    }

    if (!what) {
        return false;
    }

    what->log("Chosen inventory item");
    if (what->is_weapon()) {
        player->wield(what);
        if (changed_highlight_slot) {
            game->tick_begin("player wielded a new weapon");
        }
        game->change_state(Game::STATE_MOVING_ITEMS);
    } else if (what->is_bag()) {
        game->wid_thing_info_create(what);
        what->log("Moving items flag set");
        game->change_state(Game::STATE_MOVING_ITEMS);
    } else if (what->is_thrown_automatically_when_selected()) {
        player->throw_item(what);
    } else if (what->is_used_automatically_when_selected()) {
        player->use(what);
    }

    return true;
}

Thingp Level::inventory_describe (const uint32_t slot)
{_
    LOG("Inventory: describe slot %d", slot);
_
    auto what = inventory_get(game->inventory_highlight_slot);
    if (what) {
        what->log("Inventory: describe slot %d", slot);
        what->describe_when_in_inventory();
    } else {
        LOG("Inventory: describe slot %d => nothing there", slot);
    }
    return what;
}
