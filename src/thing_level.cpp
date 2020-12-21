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
        auto it = get_owner();
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
        set_where_i_failed_to_collect_last(point(-1, -1));
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

    if (is_torch()) {
        log("push");
    }

    level->put_thing((int)mid_at.x, (int)mid_at.y, id);
    auto mx = (int16_t)(int)mid_at.x;
    auto my = (int16_t)(int)mid_at.y;
    is_attached = true;
    last_attached = point(mx, my);

    if (is_acid())                               { i_set_is_acid = true;
                                                   level->set_is_acid(mx, my); }
    if (is_blood())                              { i_set_is_blood = true;
                                                   level->set_is_blood(mx, my); }
    if (is_chasm())                              { i_set_is_chasm = true;
                                                   level->set_is_chasm(mx, my); }
    if (is_corpse())                             { i_set_is_corpse = true;
                                                   level->set_is_corpse(mx, my); }
    if (is_corridor())                           { i_set_is_corridor = true;
                                                   level->set_is_corridor(mx, my); }
    if (is_deep_water())                         { i_set_is_deep_water = true;
                                                   level->set_is_deep_water(mx, my); }
    if (is_deep_water())                         { i_set_is_water = true;
                                                   level->set_is_water(mx, my); }
    if (is_dirt())                               { i_set_is_dirt = true;
                                                   level->set_is_dirt(mx, my); }
    if (is_door() && !is_open)                   { i_set_is_door = true;
                                                   level->set_is_door(mx, my); }
    if (is_entrance())                           { i_set_is_entrance = true;
                                                   level->set_is_entrance(mx, my); }
    if (is_exit())                               { i_set_is_exit = true;
                                                   level->set_is_exit(mx, my); }
    if (is_fire() && !is_dead)                   { i_set_is_fire = true;
                                                   level->set_is_fire(mx, my); }
    if (is_floor())                              { i_set_is_floor = true;
                                                   level->set_is_floor(mx, my); }
    if (is_food())                               { i_set_is_food = true;
                                                   level->set_is_food(mx, my); }
    if (is_generator())                          { i_set_is_generator = true;
                                                   level->set_is_generator(mx, my); }
    if (is_gold())                               { i_set_is_gold = true;
                                                   level->set_is_gold(mx, my); }
    if (is_hazard())                             { i_set_is_hazard = true;
                                                   level->set_is_hazard(mx, my); }
    if (is_treasure_class_a())                   { i_set_is_treasure_class_a = true;
                                                   level->set_is_treasure_class_a(mx, my); }
    if (is_treasure_class_b())                   { i_set_is_treasure_class_b = true;
                                                   level->set_is_treasure_class_b(mx, my); }
    if (is_treasure_class_c())                   { i_set_is_treasure_class_c = true;
                                                   level->set_is_treasure_class_c(mx, my); }
    if (is_key())                                { i_set_is_key = true;
                                                   level->set_is_key(mx, my); }
    if (is_lava())                               { i_set_is_lava = true;
                                                   level->set_is_lava(mx, my); }
    if (is_light_blocker() && !is_open)          { i_set_is_light_blocker = true;
                                                   level->set_is_light_blocker(mx, my); }
    if (is_monst())                              { i_set_is_monst = true;
                                                   level->set_is_monst(mx, my); }
    if (is_movement_blocking_hard() && !is_open) { i_set_is_movement_blocking_hard = true;
                                                   level->set_is_movement_blocking_hard(mx, my); }
    if (is_movement_blocking_soft() && !is_open) { i_set_is_movement_blocking_soft = true;
                                                   level->set_is_movement_blocking_soft(mx, my); }
    if (is_potion())                             { i_set_is_potion = true;
                                                   level->set_is_potion(mx, my); }
    if (is_ripple())                             { i_set_is_ripple = true;
                                                   level->set_is_ripple(mx, my); }
    if (is_rock())                               { i_set_is_rock = true;
                                                   level->set_is_rock(mx, my); }
    if (is_secret_door())                        { i_set_is_secret_door = true;
                                                   level->set_is_secret_door(mx, my); }
    if (is_smoke())                              { i_set_is_smoke = true;
                                                   level->set_is_smoke(mx, my); }
    if (is_torch())                              { i_set_is_torch = true;
                                                   level->set_is_torch(mx, my); }
    if (is_treasure())                           { i_set_is_treasure = true;
                                                   level->set_is_treasure(mx, my); }
    if (is_wall())                               { i_set_is_wall = true;
                                                   level->set_is_wall(mx, my); }
    if (is_water())                              { i_set_is_water = true;
                                                   level->set_is_water(mx, my); }

    if (is_lava() || is_fire()) { level->heatmap_valid = false; }

    if (!is_hidden) {
        if (gfx_shown_in_bg()) { level->bg_valid = false; }
    }
    // log("is_monst count %d (after push) at %d,%d", level->is_monst(mx, my), mx, my);
}

void Thing::level_pop (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;

    if (is_torch()) {
        log("pop");
    }

    auto mx = (int16_t)(int)last_attached.x;
    auto my = (int16_t)(int)last_attached.y;

    if (i_set_is_acid)                                 { i_set_is_acid = false;
                                                         level->unset_is_acid(mx, my); }
    if (i_set_is_blood)                                { i_set_is_blood = false;
                                                         level->unset_is_blood(mx, my); }
    if (i_set_is_chasm)                                { i_set_is_chasm = false;
                                                         level->unset_is_chasm(mx, my); }
    if (i_set_is_corpse)                               { i_set_is_corpse = false;
                                                         level->unset_is_corpse(mx, my); }
    if (i_set_is_corridor)                             { i_set_is_corridor = false;
                                                         level->unset_is_corridor(mx, my); }
    if (i_set_is_deep_water)                           { i_set_is_water = false;
                                                         level->unset_is_water(mx, my); }
    if (i_set_is_dirt)                                 { i_set_is_dirt = false;
                                                         level->unset_is_dirt(mx, my); }
    if (i_set_is_door)                                 { i_set_is_door = false;
                                                         level->unset_is_door(mx, my); }
    if (i_set_is_entrance)                             { i_set_is_entrance = false;
                                                         level->unset_is_entrance(mx, my); }
    if (i_set_is_exit)                                 { i_set_is_exit = false;
                                                         level->unset_is_exit(mx, my); }
    if (i_set_is_fire)                                 { i_set_is_fire = false;
                                                         level->unset_is_fire(mx, my); }
    if (i_set_is_floor)                                { i_set_is_floor = false;
                                                         level->unset_is_floor(mx, my); }
    if (i_set_is_food)                                 { i_set_is_food = false;
                                                         level->unset_is_food(mx, my); }
    if (i_set_is_generator)                            { i_set_is_generator = false;
                                                         level->unset_is_generator(mx, my); }
    if (i_set_is_gold)                                 { i_set_is_gold = false;
                                                         level->unset_is_gold(mx, my); }
    if (i_set_is_hazard)                               { i_set_is_hazard = false;
                                                         level->unset_is_hazard(mx, my); }
    if (i_set_is_treasure_class_a)                     { i_set_is_treasure_class_a = false;
                                                         level->unset_is_treasure_class_a(mx, my); }
    if (i_set_is_treasure_class_b)                     { i_set_is_treasure_class_b = false;
                                                         level->unset_is_treasure_class_b(mx, my); }
    if (i_set_is_treasure_class_c)                     { i_set_is_treasure_class_c = false;
                                                         level->unset_is_treasure_class_c(mx, my); }
    if (i_set_is_key)                                  { i_set_is_key = false;
                                                         level->unset_is_key(mx, my); }
    if (i_set_is_lava)                                 { i_set_is_lava = false;
                                                         level->unset_is_lava(mx, my); }
    if (i_set_is_light_blocker)                        { i_set_is_light_blocker = false;
                                                         level->unset_is_light_blocker(mx, my); }
    if (i_set_is_monst)                                { i_set_is_monst = false;
                                                         level->unset_is_monst(mx, my); }
    if (i_set_is_movement_blocking_hard)               { i_set_is_movement_blocking_hard = false;
                                                         level->unset_is_movement_blocking_hard(mx, my); }
    if (i_set_is_movement_blocking_soft)               { i_set_is_movement_blocking_soft = false;
                                                         level->unset_is_movement_blocking_soft(mx, my); }
    if (i_set_is_potion)                               { i_set_is_potion = false;
                                                         level->unset_is_potion(mx, my); }
    if (i_set_is_ripple)                               { i_set_is_ripple = false;
                                                         level->unset_is_ripple(mx, my); }
    if (i_set_is_rock)                                 { i_set_is_rock = false;
                                                         level->unset_is_rock(mx, my); }
    if (i_set_is_secret_door)                          { i_set_is_secret_door = false;
                                                         level->unset_is_secret_door(mx, my); }
    if (i_set_is_smoke)                                { i_set_is_smoke = false;
                                                         level->unset_is_smoke(mx, my); }
    if (i_set_is_torch)                                { i_set_is_torch = false;
                                                         level->unset_is_torch(mx, my); }
    if (i_set_is_treasure)                             { i_set_is_treasure = false;
                                                         level->unset_is_treasure(mx, my); }
    if (i_set_is_wall)                                 { i_set_is_wall = false;
                                                         level->unset_is_wall(mx, my); }
    if (i_set_is_water)                                { i_set_is_water = false;
                                                         level->unset_is_water(mx, my); }

    level->remove_thing((int)last_attached.x, (int)last_attached.y, id);

    if (is_lava() || is_fire()) { level->heatmap_valid = false; }

    if (!is_hidden) {
        if (gfx_shown_in_bg()) { level->bg_valid = false; }
    }
    // log("is_monst count %d (after pop) at %d,%d", level->is_monst(mx, my), mx, my);
}
