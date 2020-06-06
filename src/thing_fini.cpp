//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

Thing::~Thing_ (void)
{_
    verify(this);
    destroy();
    oldptr(this);
}

void Thing::destroy (void)
{_
    verify(this);

    if (is_loggable_for_unimportant_stuff()) {
        log("destroy");
    }

    if (is_being_destroyed) {
        err("death recursion in thing destroy");
        return;
    }
    is_being_destroyed = true;

    detach();

    unwield("owner is destroyed");

    //
    // hooks remove must be after unwield
    //
    hooks_remove();

    //
    // Pop from the map
    //
    point old_at((int)mid_at.x, (int)mid_at.y);

    if (is_blood())         { level->unset_is_blood(old_at.x, old_at.y); }
    if (is_chasm())         { level->unset_is_chasm(old_at.x, old_at.y); }
    if (is_corpse())        { level->unset_is_corpse(old_at.x, old_at.y); }
    if (is_corridor())      { level->unset_is_corridor(old_at.x, old_at.y); }
    if (is_deep_water())    { level->unset_is_deep_water(old_at.x, old_at.y); }
    if (is_deep_water())    { level->unset_is_water(old_at.x, old_at.y); }
    if (is_dirt())          { level->unset_is_dirt(old_at.x, old_at.y); }
    if (is_door())          { level->unset_is_door(old_at.x, old_at.x); }
    if (is_fire())          { level->unset_is_fire(old_at.x, old_at.y); }
    if (is_floor())         { level->unset_is_floor(old_at.x, old_at.y); }
    if (is_food())          { level->unset_is_food(old_at.x, old_at.y); }
    if (is_hazard())        { level->unset_is_hazard(old_at.x, old_at.y); }
    if (is_key())           { level->unset_is_key(old_at.x, old_at.x); }
    if (is_large())         { level->unset_is_large(old_at.x, old_at.x); }
    if (is_lava())          { level->unset_is_lava(old_at.x, old_at.y); }
    if (is_monst())         { level->unset_is_monst(old_at.x, old_at.y); }
    if (is_rock())          { level->unset_is_rock(old_at.x, old_at.y); }
    if (is_secret_door())   { level->unset_is_secret_door(old_at.x, old_at.y); }
    if (is_smoke())         { level->unset_is_smoke(old_at.x, old_at.x); }
    if (is_wall())          { level->unset_is_wall(old_at.x, old_at.y); }
    if (is_water())         { level->unset_is_water(old_at.x, old_at.y); }

    if (is_player()) {
        level->player = nullptr;
    }

    delete_dmap_scent();
    delete_age_map();
    delete_light();

    if (is_loggable_for_unimportant_stuff()) {
        log("destroyed");
    }

    {
        auto f = level->all_things.find(id);
        if (f != level->all_things.end()) {
            level->all_things.erase(f);
        }
    }

    if (is_active()) {
        auto f = level->all_active_things.find(id);
        if (f != level->all_active_things.end()) {
            level->all_active_things.erase(f);
        }
    }

    {
        auto f = level->all_gc_things.find(id);
        if (f != level->all_gc_things.end()) {
            level->all_gc_things.erase(f);
        }
    }

    level->free_thing_id(this);

    if (this == player) {
        player = nullptr;
    }

    if (monstp) {
        oldptr(monstp);
        delete monstp;
    }
}
