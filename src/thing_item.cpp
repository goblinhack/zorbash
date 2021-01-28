//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::move_carried_items (void)
{_
    //
    // Light source follows the thing.
    //
    update_light();

    //
    // Weapons follow also.
    //
    if (get_weapon_id_carry_anim().ok()) {
        auto w = level->thing_find(get_weapon_id_carry_anim());
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        }
    }

    if (get_weapon_id_use_anim().ok()) {
        auto w = level->thing_find(get_weapon_id_use_anim());
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        }
    }

    //
    // Move carried items too as when we attack, we will use say the
    // carried sword and so it had better be in the same location.
    //
    for (auto oid : monstp->carrying) {
        auto o = level->thing_find(oid);
        if (o) {
            o->move_to(mid_at);
            o->dir = dir;
        }
    }

    //
    // If something moves on the water, make a ripple
    //
    if (is_monst() || is_player()) {
        if (!is_floating()) {
            if (level->is_shallow_water((int)mid_at.x, (int)mid_at.y) &&
                !level->is_ripple((int)mid_at.x, (int)mid_at.y)) {
                fpoint at(mid_at.x, mid_at.y);
                log("Causes ripples");
                if (random_range(0, 1000) > 500) {
                    level->thing_new(tp_random_ripple()->name(), at);
                }
            }
        }
    }

    auto on_fire_anim_id = get_on_fire_anim_id();
    if (on_fire_anim_id.ok()) {_
        auto w = level->thing_find(on_fire_anim_id);
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        }
    }
}

void Thing::move_carried_items_immediately (void)
{_
    //
    // Light source follows the thing.
    //
    update_light();

    //
    // Weapons follow also.
    //
    if (get_weapon_id_carry_anim().ok()) {
        auto w = level->thing_find(get_weapon_id_carry_anim());
        if (w) {
            w->move_to_immediately(mid_at);
            w->dir = dir;
        }
    }

    if (get_weapon_id_use_anim().ok()) {
        auto w = level->thing_find(get_weapon_id_use_anim());
        if (w) {
            w->move_to_immediately(mid_at);
            w->dir = dir;
        }
    }

    //
    // Move carried items too as when we attack, we will use say the
    // carried sword and so it had better be in the same location.
    //
    for (auto oid : monstp->carrying) {
        auto o = level->thing_find(oid);
        if (o) {
            o->move_to_immediately(mid_at);
            o->dir = dir;
        }
    }

    auto on_fire_anim_id = get_on_fire_anim_id();
    if (on_fire_anim_id.ok()) {_
        auto w = level->thing_find(on_fire_anim_id);
        if (w) {
            w->move_to_immediately(mid_at);
            w->dir = dir;
        }
    }
}

bool Thing::is_carrying_item (void)
{_
    if (!monstp) {
        return false;
    }

    if (monstp->carrying.size()){
        return true;
    }

    auto owner = get_top_owner();
    if (owner) {
        return owner->is_carrying_item();
    }

    return false;
}

std::vector<Thingp> Thing::get_item_list (void)
{_
    std::vector<Thingp> tr;
    log("Carried items:");
_
    if (!monstp) {
        log("Not carrying");
        return tr;
    }

    for (const auto& item : monstp->carrying) {
        auto t = level->thing_find(item.id);
        if (!t) {
            continue;
        }

        log("Item %s", t->to_string().c_str());
        if (t->monstp && t->monstp->carrying.size()) {
            auto tr2 = t->get_item_list();
            std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
        }

        if (t->is_item()) {
            tr.push_back(t);
        }
    }

    auto owner = get_immediate_owner();
    if (owner) {
        auto tr2 = owner->get_item_list();
        std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
    }

    return tr;
}
