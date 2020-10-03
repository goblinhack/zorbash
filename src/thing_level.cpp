//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_gl.h"

//
// Find an existing thing.
//
Thingp Level::thing_find (const ThingId id)
{_
    return game->world.find_thing_ptr(id);
}

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::level_change (Levelp l)
{_
    if (level == l) {
        return;
    }

    auto old_level = level;

    log("change level");
    level_leave();
    level = l;
    level_enter();

    if (monstp) {
        monstp->move_path = {};
        clear_age_map();
        clear_dmap_scent();
        move_finish();
    }

    if (is_player()) {
        old_level->player = nullptr;
        level->player = this;
    }

    {
        auto it = owner_get();
        if (it) {
            it->level_change(l);
        }
    }

    {
        auto it = weapon_get();
        if (it) {
            it->level_change(l);
        }
    }

    {
        auto it = weapon_get_carry_anim();
        if (it) {
            it->level_change(l);
        }
    }

    {
        auto it = weapon_get_use_anim();
        if (it) {
            it->level_change(l);
        }
    }

    {
        auto id = get_on_fire_anim_id();
        if (id.ok()) {
            auto it = level->thing_find(id);
            if (it) {
                it->level_change(l);
            }
        }
    }

    if (monstp) {
        for (auto id : monstp->carrying) {
            auto it = level->thing_find(id);
            if (it) {
                it->level_change(l);
            }
        }
    }

    for (auto l : get_light()) {
        l->level = level;
        l->reset();
    }

    log("changed level");

    if (is_player()) {
        l->scroll_map_to_player();
    }
}

void Thing::level_enter (void)
{_
    auto result = level->all_things.insert(std::pair(id, this));
    if (result.second == false) {
        err("failed to insert into thing map");
    }

    if (is_active()) {
        auto result = level->all_active_things.insert(std::pair(id, this));
        if (result.second == false) {
            err("failed to insert into active thing map");
        }
    }

    //
    // If this is the player create a new cursor for us.
    // If this is something else, do not, else the cursor winds up
    // following whatever fell in.
    //
    if (is_player()) {
        if (!level->cursor) {
            if (!is_cursor()) {
                level->cursor = level->thing_new("cursor", mid_at);
                level->cursor->hide();
            }
        }

        //
        // Flush the persistent light map
        // 
        blit_fbo_bind(FBO_FULLMAP_LIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        level->_is_lit = {};
    }
    level_push();

    if (is_player() || is_monst()) {
        set_where_i_dropped_an_item_last(point(-1, -1));
    }

    //
    // Make sure the light is refreshed.
    //
    if (is_player()) {
        update_light();
    }

    //
    // Blit location is now invalid
    //
    is_blitted = false;

    //
    // Can be shown on screen again.
    //
    is_changing_level     = false;
    is_waiting_to_ascend  = false;
    is_waiting_to_descend = false;
    is_waiting_to_fall    = false;
}

void Thing::level_leave (void)
{_
    level_pop();
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
}

//
// push/pop are for things moving on the same level
//
void Thing::level_push (void)
{_
    level_pop();

#if 0
    if (is_loggable_for_unimportant_stuff()) {
        log("push");
    }
#endif

    level->put_thing((int)mid_at.x, (int)mid_at.y, id);
    auto mx = (int16_t)(int)mid_at.x;
    auto my = (int16_t)(int)mid_at.y;
    is_attached = true;
    last_attached = point(mx, my);

    if (is_acid())                               { level->set_is_acid(mx, my); }
    if (is_blood())                              { level->set_is_blood(mx, my); }
    if (is_chasm())                              { level->set_is_chasm(mx, my); }
    if (is_corpse())                             { level->set_is_corpse(mx, my); }
    if (is_corridor())                           { level->set_is_corridor(mx, my); }
    if (is_deep_water())                         { level->set_is_deep_water(mx, my); }
    if (is_deep_water())                         { level->set_is_water(mx, my); }
    if (is_dirt())                               { level->set_is_dirt(mx, my); }
    if (is_door() && !is_open)                   { level->set_is_door(mx, my); }
    if (is_entrance())                           { level->set_is_entrance(mx, my); }
    if (is_exit())                               { level->set_is_exit(mx, my); }
    if (is_fire())                               { level->set_is_fire(mx, my); }
    if (is_floor())                              { level->set_is_floor(mx, my); }
    if (is_food())                               { level->set_is_food(mx, my); }
    if (is_generator())                          { level->set_is_generator(mx, my); }
    if (is_gold())                               { level->set_is_gold(mx, my); }
    if (is_hazard())                             { level->set_is_hazard(mx, my); }
    if (is_item_class_a())                       { level->set_is_item_class_a(mx, my); }
    if (is_item_class_b())                       { level->set_is_item_class_b(mx, my); }
    if (is_key())                                { level->set_is_key(mx, my); }
    if (is_lava())                               { level->set_is_lava(mx, my); }
    if (is_light_blocker() && !is_open)          { level->set_is_light_blocker(mx, my); }
    if (is_monst())                              { level->set_is_monst(mx, my); }
    if (is_movement_blocking_hard() && !is_open) { level->set_is_movement_blocking_hard(mx, my); }
    if (is_movement_blocking_soft() && !is_open) { level->set_is_movement_blocking_soft(mx, my); }
    if (is_potion())                             { level->set_is_potion(mx, my); }
    if (is_ripple())                             { level->set_is_ripple(mx, my); }
    if (is_rock())                               { level->set_is_rock(mx, my); }
    if (is_secret_door())                        { level->set_is_secret_door(mx, my); }
    if (is_smoke())                              { level->set_is_smoke(mx, my); }
    if (is_torch())                              { level->set_is_torch(mx, my); }
    if (is_treasure())                           { level->set_is_treasure(mx, my); }
    if (is_wall())                               { level->set_is_wall(mx, my); }
    if (is_water())                              { level->set_is_water(mx, my); }

    if (is_lava() || is_fire()) { level->heatmap_valid = false; }

    if (!is_hidden) {
        if (is_gfx_shown_in_bg()) { level->bg_valid = false; }
    }
    log("is_monst count %d (after push) at %d,%d", level->is_monst(mx, my), mx, my);
}

void Thing::level_pop (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;

#if 0
    if (is_loggable_for_unimportant_stuff()) {
        log("pop");
    }
#endif

    auto mx = (int16_t)(int)last_attached.x;
    auto my = (int16_t)(int)last_attached.y;

    if (is_acid())                               { level->unset_is_acid(mx, my); }
    if (is_blood())                              { level->unset_is_blood(mx, my); }
    if (is_chasm())                              { level->unset_is_chasm(mx, my); }
    if (is_corpse())                             { level->unset_is_corpse(mx, my); }
    if (is_corridor())                           { level->unset_is_corridor(mx, my); }
    if (is_deep_water())                         { level->unset_is_deep_water(mx, my); }
    if (is_deep_water())                         { level->unset_is_water(mx, my); }
    if (is_dirt())                               { level->unset_is_dirt(mx, my); }
    if (is_door() && !is_open)                   { level->unset_is_door(mx, my); }
    if (is_entrance())                           { level->unset_is_entrance(mx, my); }
    if (is_exit())                               { level->unset_is_exit(mx, my); }
    if (is_fire())                               { level->unset_is_fire(mx, my); }
    if (is_floor())                              { level->unset_is_floor(mx, my); }
    if (is_food())                               { level->unset_is_food(mx, my); }
    if (is_generator())                          { level->unset_is_generator(mx, my); }
    if (is_gold())                               { level->unset_is_gold(mx, my); }
    if (is_hazard())                             { level->unset_is_hazard(mx, my); }
    if (is_item_class_a())                       { level->unset_is_item_class_a(mx, my); }
    if (is_item_class_b())                       { level->unset_is_item_class_b(mx, my); }
    if (is_key())                                { level->unset_is_key(mx, my); }
    if (is_lava())                               { level->unset_is_lava(mx, my); }
    if (is_light_blocker() && !is_open)          { level->unset_is_light_blocker(mx, my); }
    if (is_monst())                              { level->unset_is_monst(mx, my); }
    if (is_movement_blocking_hard() && !is_open) { level->unset_is_movement_blocking_hard(mx, my); }
    if (is_movement_blocking_soft() && !is_open) { level->unset_is_movement_blocking_soft(mx, my); }
    if (is_potion())                             { level->unset_is_potion(mx, my); }
    if (is_ripple())                             { level->unset_is_ripple(mx, my); }
    if (is_rock())                               { level->unset_is_rock(mx, my); }
    if (is_secret_door())                        { level->unset_is_secret_door(mx, my); }
    if (is_smoke())                              { level->unset_is_smoke(mx, my); }
    if (is_torch())                              { level->unset_is_torch(mx, my); }
    if (is_treasure())                           { level->unset_is_treasure(mx, my); }
    if (is_wall())                               { level->unset_is_wall(mx, my); }
    if (is_water())                              { level->unset_is_water(mx, my); }

    level->remove_thing((int)last_attached.x, (int)last_attached.y, id);

    if (is_lava() || is_fire()) { level->heatmap_valid = false; }

    if (!is_hidden) {
        if (is_gfx_shown_in_bg()) { level->bg_valid = false; }
    }
    log("is_monst count %d (after pop) at %d,%d", level->is_monst(mx, my), mx, my);
}
