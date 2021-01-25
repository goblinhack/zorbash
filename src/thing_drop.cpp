//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"
#include "my_main.h"
#include "my_game.h"
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"
#include "my_level.h"

bool Thing::drop (Thingp what, Thingp target)
{_
    if (target) {
        log("Drop %s at %s", what->to_string().c_str(),
            target->to_string().c_str());
    } else {
        log("Drop %s", what->to_string().c_str());
    }
_
    auto existing_owner = what->get_immediate_owner();
    if (existing_owner != this) {
        err("Attempt to drop %s which is not carried", 
            what->to_string().c_str());
        return false;
    }

    if (is_player()) {
        if (target) {
            inventory_id_remove(what, target);
        } else {
            inventory_id_remove(what);
        }
    }

    what->hooks_remove();
    what->remove_owner();

    //
    // Hide as the particle drop will reveal it
    //
    if (is_player()) {
        what->hide();
    } else {
        what->visible();
    }

    if (target) {
        what->move_to_immediately(target->mid_at);
    } else {
        what->move_to_immediately(mid_at);
    }

    monstp->carrying.remove(what->id);

    //
    // Prevent too soon re-carry
    //
    set_where_i_dropped_an_item_last(make_point(mid_at));

    if (is_bag() || is_player()) {
        log("Update bag with drop of: %s", what->to_string().c_str());
        bag_remove(what);
        while (bag_compress()) { }
    }

    if (is_player()) {
        wid_inventory_init();
        wid_thing_info_fini();
    }

    log("Dropped %s", what->to_string().c_str());

    return true;
}

//
// An item in between bags
//
bool Thing::drop_into_ether (Thingp what)
{_
    log("Dropping %s into the ether", what->to_string().c_str());
_
    auto existing_owner = what->get_immediate_owner();
    if (existing_owner != this) {
        err("Attempt to drop %s which is not carried", 
            what->to_string().c_str());
        return false;
    }

    Thingp top_owner;
    if (is_player()) {
        top_owner = this;
    } else {
        top_owner = get_top_owner();
    }

    if (top_owner) {
        if (what == top_owner->weapon_get()) {
            top_owner->unwield("moved into ether");
        }

        if (top_owner->is_player()) {
            top_owner->inventory_id_remove(what);
        }
    } else {
        //
        // This is ok, if we are moving items from a temporary bag
        //
    }

    log("Update bag with drop of: %s", what->to_string().c_str());
    bag_remove(what);
    while (bag_compress()) { }

    what->remove_owner();
    monstp->carrying.remove(what->id);
    game->request_remake_inventory = true;

    log("Dropped %s into the ether", what->to_string().c_str());

    return true;
}

//
// An item in between bags
//
bool Thing::drop_from_ether (Thingp what)
{_
    auto player = game->level->player;

    log("Drop from ether %s", what->to_string().c_str());
_
    what->hooks_remove();
    what->remove_owner();
    what->hide();
    what->visible();
    what->move_to_immediately(player->mid_at);

    //
    // Prevent too soon re-carry
    //
    set_where_i_dropped_an_item_last(make_point(player->mid_at));

    wid_inventory_init();
    wid_thing_info_fini();

    point e = (player->last_blit_tl + player->last_blit_br) / 2;

    auto w = game->in_transit_item;
    if (!w) {
        ERR("No in transit item");
        return false;
    }

    auto s = (w->abs_tl + w->abs_br) / 2;
    s.x = (int)(((float)game->config.inner_pix_width / (float)TERM_WIDTH) * (float)s.x);
    s.y = (int)(((float)game->config.inner_pix_height / (float)TERM_HEIGHT) * (float)s.y);

    game->level->new_external_particle(
                id,
                s, e,
                isize(TILE_WIDTH, TILE_HEIGHT), 
                PARTICLE_SPEED_MS,
                tile_index_to_tile(what->tile_curr),
                (is_dir_br() || is_dir_right() || is_dir_tr()),
                true /* make_visible_at_end */);

    log("Dropped from ether %s", what->to_string().c_str());

    return true;
}

bool Thing::drop (Thingp what)
{_
    return drop(what, nullptr);
}

void Thing::drop_all (void)
{_
    if (!monstp) {
        return;
    }

    while (!monstp->carrying.empty()) {
        auto id = *monstp->carrying.begin();
        auto t = level->thing_find(id);
        if (!t) {
            return;
        }
        drop(t);
    }
}
