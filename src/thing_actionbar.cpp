//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_game_status.h"

void Thing::actionbar_particle (Thingp what, uint32_t slot)
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
                     tile_find_mand(name), false);
        }
        return;
    }

    if (what->is_collect_as_keys()) {
        std::string name = "key";
        auto w = wid_find(name);
        if (!w) {
            con("could not find wid %s", name.c_str());
            return;
        }

        auto p = (w->abs_tl + w->abs_br) / 2;
        p.x = (game->config.inner_pix_width / ASCII_WIDTH) * p.x;
        p.y = (game->config.inner_pix_height / ASCII_HEIGHT) * p.y;

        point s = (last_blit_tl + last_blit_br) / 2;
        point j(random_range(0, TILE_WIDTH) - TILE_WIDTH / 2,
                random_range(0, TILE_HEIGHT) - TILE_HEIGHT / 2);
        level->new_external_particle(
                 s + j, p,
                 size(TILE_WIDTH / 2, TILE_HEIGHT / 2), 500,
                 tile_find_mand("key1.1"), false);
        return;
    }

    {
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
                 tile_index_to_tile(what->tile_curr),
                 (what->is_dir_br() || what->is_dir_right() || what->is_dir_tr()));
    }
}

//
// Particle from the actionbar to a target
//
void Thing::actionbar_particle (Thingp what, uint32_t slot,
                                Thingp particle_target)
{_
    //
    // No animations at the start
    //
    if (level->is_starting) {
        return;
    }

    point where_to = (particle_target->last_blit_tl +
                      particle_target->last_blit_br) / 2;

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
                                 tile_index_to_tile(what->tile_curr),
                                 (what->is_dir_br() || what->is_dir_right() || what->is_dir_tr()));
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

    if (what->is_collect_as_keys()) {
        game_status_wid_init();
        incr_keys(1);
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
            if (t->is_not_stackable()) {
                //
                // Needs its own slot
                //
            } else {
                game_status_wid_init();
                actionbar_particle(what, i);
                return true;
            }
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
    level->actionbar_describe(game->actionbar_highlight_slot);
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

            while (game->actionbar_highlight_slot >= monstp->actionbar_id.size()) {
                game->actionbar_highlight_slot--;
            }

            level->actionbar_describe(game->actionbar_highlight_slot);
            return true;
        }
    }
    return false;
}

bool Thing::actionbar_id_remove (Thingp what, Thingp particle_target)
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
            if (particle_target) {
                actionbar_particle(what, i, particle_target);
            }

            while (game->actionbar_highlight_slot >= monstp->actionbar_id.size()) {
                game->actionbar_highlight_slot--;
            }

            level->actionbar_describe(game->actionbar_highlight_slot);
            return true;
        }
    }

    return false;
}

int Thing::actionbar_id_slot_count (const uint32_t slot)
{_
    auto a = get(monstp->actionbar_id, slot);
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
            if (o->is_not_stackable()) {
                count = 1;
            }
        }
    }

    return count;
}

Thingp Level::actionbar_get (const uint32_t slot)
{_
    if (!player) {
        return nullptr;
    }

    auto oid = get(player->monstp->actionbar_id, slot);
    if (!oid) {
        return nullptr;
    }

    return thing_find(oid);
}

Thingp Level::actionbar_get (void)
{_
    return actionbar_get(game->actionbar_highlight_slot);
}

bool Level::actionbar_select (const uint32_t slot)
{_
    if (!player) {
        return false;
    }

    auto oid = get(player->monstp->actionbar_id, slot);
    if (!oid) {
        return false;
    }

    if (slot != game->actionbar_highlight_slot) {
        game->actionbar_highlight_slot = slot;
        actionbar_describe(slot);
        game_status_wid_init();
    } else {
        actionbar_describe(game->actionbar_highlight_slot);
    }

    return true;
}

bool Level::actionbar_describe (const uint32_t slot)
{_
    auto t = actionbar_get(game->actionbar_highlight_slot);
    if (!t) {
        return false;
    }
    auto s = t->text_name();

    if (t->is_droppable()){
        s += ", %%fg=orange$d%%fg=reset$rop";
    }
    if (t->is_usable()){
        if (t->is_food()){
            s += ", %%fg=green$e%%fg=reset$at";
        } else if (t->is_potion()){
            s += ", %%fg=green$u%%fg=reset$ drink";
        } else {
            s += ", %%fg=cyan$u%%fg=reset$se";
        }
    }
    if (t->is_throwable()){
        s += ", %%fg=purple$t%%fg=reset$hrow";
    }

    BOTCON("%s", s.c_str());

    return true;
}
