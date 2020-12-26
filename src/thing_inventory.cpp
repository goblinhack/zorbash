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
    if (game->moving_items) {
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

    if (what->is_item_collected_as_gold()) {
        std::string name = "gold";
        auto w = wid_find(name);
        if (!w) {
            log("could not find wid %s", name.c_str());
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
        std::string name = "key";
        auto w = wid_find(name);
        if (!w) {
            log("could not find wid %s", name.c_str());
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
            log("could not find wid %s", name.c_str());
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
    if (game->moving_items) {
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
        log("could not find wid %s", name.c_str());
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
                if (!game->moving_items) {
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

    wid_inventory_init();
    if (!game->moving_items) {
        wid_thing_info_fini();
    }
    inventory_particle(what, item_slot);
    level->inventory_describe(item_slot);
    return true;
}

bool Thing::inventory_id_remove (Thingp what)
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
            inventory_particle(what, i, this);

            auto cnt = inventory_id_slot_count(i);
            log("remove slot %d, count %d", i, cnt);
            if (cnt > 1) {_
                log("decrement slot count");
            } else {_
                log("remove slot");
//                monstp->inventory_id.erase(monstp->inventory_id.begin() + i);
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
            if (!game->moving_items) {
                wid_thing_info_fini();
            }
            return true;
        }
    }
    return false;
}

bool Thing::inventory_id_remove (Thingp what, Thingp particle_target)
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
            if (particle_target) {
                inventory_particle(what, i, particle_target);
            }

            auto cnt = inventory_id_slot_count(i);
            log("remove slot %d, count %d", i, cnt);
            if (cnt > 1) {_
                log("decrement slot count");
            } else {_
                log("remove slot");
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
            if (!game->moving_items) {
                wid_thing_info_fini();
            }
            return true;
        }
    }

    return false;
}

int Thing::inventory_id_slot_count (const uint32_t slot)
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
    if (!player) {
        return 0;
    }

    auto monstp = player->monstp;
    if (!monstp) {
        return 0;
    }

    if (slot >= monstp->inventory_id.size()) {
        return nullptr;
    }

    auto tp_id = get(monstp->inventory_id, slot);
    if (!tp_id) {
        return nullptr;
    }

    auto tpp = tp_find(tp_id);
    if (!tpp) {
        return nullptr;
    }

    for (auto oid : monstp->carrying) {
        auto o = thing_find(oid);
        if (o->tp() == tpp) {
            return o;
        }
    }

    return nullptr;
}

Thingp Level::inventory_get (void)
{_
    return inventory_get(game->inventory_highlight_slot);
}

bool Level::inventory_over (const uint32_t slot)
{_
    if (!player) {
        return false;
    }

    if (slot >= player->monstp->inventory_id.size()) {
        return false;
    }

    auto oid = get(player->monstp->inventory_id, slot);
    if (!oid) {
        return false;
    }

    Thingp what;

    if (slot != game->inventory_highlight_slot) {
        game->remake_inventory = true;
        game->inventory_highlight_slot = slot;
        what = inventory_describe(slot);
    } else {
        what = inventory_describe(game->inventory_highlight_slot);
    }

    if (!what) {
        return false;
    }

    return true;
}

bool Level::inventory_chosen (const uint32_t slot)
{_
    if (!player) {
        return false;
    }

    if (slot >= player->monstp->inventory_id.size()) {
        return false;
    }

    game->remake_inventory = true;
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

    if (what->is_weapon()) {
        player->wield(what);
        if (changed_highlight_slot) {
            game->tick_begin("player wielded a new weapon");
        }
    }

    if (what->is_bag()) {
        game->wid_thing_info_create(what);
    }

    return true;
}

Thingp Level::inventory_describe (const uint32_t slot)
{_
    auto what = inventory_get(game->inventory_highlight_slot);
    if (what) {
        what->describe_when_in_inventory();
    }
    return what;
}
