//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_globals.h"
#include "my_wid_thing_info.h"
#include "my_game.h"

Thing::~Thing_ (void)
{_
    verify(this);
    destroy();
    oldptr(this);
}

void Thing::destroy (void)
{_
    verify(this);

    if (is_loggable_for_important_stuff()) {
        dbg2("Is being destroyed");
    }

    if (is_being_destroyed) {
        err("Death recursion in thing destroy");
        return;
    }
    is_being_destroyed = true;

    level_pop();
    level_leave();

    unwield("owner is destroyed");

    //
    // hooks remove must be after unwield
    //
    hooks_remove();

    //
    // Remove any references still to this item
    //
    remove_all_references();

    //
    // Pop from the map
    //
    point old_at((int)mid_at.x, (int)mid_at.y);

    delete_dmap_can_see();
    delete_dmap_unused();
    delete_age_map();
    delete_seen_map();
    delete_lights();
    delete_particle();

    {
        auto f = level->all_gc_things.find(id);
        if (f != level->all_gc_things.end()) {
            dbg2("Remove from gc");
            level->all_gc_things.erase(f);
        }
    }

    if (level->hover_over == this) {
        level->hover_over = nullptr;
    }

    if (level->highlight == this) {
        level->highlight = nullptr;
    }

    if (level->player == this) {
        level->player = nullptr;
    }

    if (level->cursor == this) {
        level->cursor = nullptr;
    }

    if (game->request_to_throw_item == this) {
        game->request_to_throw_item = nullptr;
    }

    if (game->request_to_fire_item == this) {
        game->request_to_fire_item = nullptr;
    }

    if (game->current_wid_thing_info == this) {
        game->current_wid_thing_info = nullptr;
    }

    for (const auto w : wid_thing_info_window) {
        if (w->t == this) {
            game->wid_thing_info_destroy_immediate();
            break;
        }
    }

    if (has_external_particle) {
        err("Still has external particle");
    }

    if (has_internal_particle) {
        err("Still has external particle");
    }

    game->world.free_thing_id(this);

    if (monstp) {
        oldptr(monstp);
        delete monstp;
    }
}
