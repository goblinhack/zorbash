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

void thing_gc (void)
{_
    if (!level) {
        return;
    }

    for (;;) {
        auto i = level->all_gc_things.begin();
        if (i == level->all_gc_things.end()) {
            break;
        }
        auto id = i->first;
        level->all_gc_things.erase(i);

        auto t = thing_find(id);
        if (!t) {
            ERR("thing %08X not found to garbage collect", id);
            continue;
        }

        if (t->is_loggable()) {
            t->log("garbage collect");
        }
        delete t;
    }

    level->all_gc_things.clear();
}

Thingp thing_new (std::string tp_name, Thingp owner)
{_
    return thing_new(tp_name, owner->mid_at);
}

Thingp thing_new (std::string name, fpoint at, fpoint jitter)
{_
    auto t = new struct Thing_();
    t->init(name, at, jitter);
    return (t);
}

Thing::Thing_ (void)
{_
    newptr(this, "thing");
}

Thing::~Thing_ (void)
{_
    verify(this);
    destroy();
    oldptr(this);
}

void Thing::init (std::string name, fpoint born, fpoint jitter)
{_
    verify(this);

    mid_at      = born;
    last_mid_at = born;

    timestamp_next_frame = 0;
    const auto tpp = tp_find(name);
    if (unlikely(!tpp)) {
        ERR("thing template [%s] not found", name.c_str());
        return;
    }

    tp_id = tpp->id;
    tp_or_update();

    //
    // Must do this after TP assignment or logging will fail
    //
    level->alloc_thing_id(this);

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

    if (tpp->is_monst()) {
        new_dmap_scent();
        new_age_map();
    }

    if (tpp->is_player()) {
        player = this;
    }

    if (tpp->is_monst() || tpp->is_player() || tpp->is_movable()) {
        set_timestamp_born(time_get_time_ms_cached());
    }

    if (tpp->is_gfx_animated_can_hflip()) {
        dir            = THING_DIR_LEFT;
        is_facing_left = true;
    } else {
        dir            = THING_DIR_NONE;
        is_facing_left = false;
    }
    is_waiting_to_move = true;

    is_hungry = tpp->is_hunger_insatiable();

    {_
        auto v = tpp->stats_health_initial();
        if (unlikely(v)) {
            set_stats_health(v);
            set_stats_health_max(v);
        }
    }

    {_
        auto v = tpp->stats_defence();
        if (unlikely(v)) {
            set_stats_defence(v);
            set_stats_defence_max(v);
        }
    }

    {_
        auto v = tpp->stats_attack_rate_tenths();
        if (unlikely(v)) {
            set_stats_attack_rate_tenths(v);
        }
    }

    {_
        auto v = tpp->lifespan_count();
        if (unlikely(v)) {
            set_lifespan_count(v);
        }
    }

    {_
        auto v = tpp->stats01();
        if (unlikely(v)) {
            set_stats01(v);
        }
    }

    {_
        auto v = tpp->stats02();
        if (unlikely(v)) {
            set_stats02(v);
        }
    }

    {_
        auto v = tpp->stats03();
        if (unlikely(v)) {
            set_stats03(v);
        }
    }

    {_
        auto v = tpp->stats04();
        if (unlikely(v)) {
            set_stats04(v);
        }
    }

    {_
        auto v = tpp->stats05();
        if (unlikely(v)) {
            set_stats05(v);
        }
    }

    {_
        auto v = tpp->stats06();
        if (unlikely(v)) {
            set_stats06(v);
        }
    }

    {_
        auto v = tpp->stats07();
        if (unlikely(v)) {
            set_stats07(v);
        }
    }

    {_
        auto v = tpp->stats08();
        if (unlikely(v)) {
            set_stats08(v);
        }
    }

    {_
        auto v = tpp->stats09();
        if (unlikely(v)) {
            set_stats09(v);
        }
    }

    {_
        auto v = tpp->stats10();
        if (unlikely(v)) {
            set_stats10(v);
        }
    }

    {_
        auto v = tpp->stats11();
        if (unlikely(v)) {
            set_stats11(v);
        }
    }

    {_
        auto v = tpp->stats12();
        if (unlikely(v)) {
            set_stats12(v);
        }
    }

    {_
        auto v = tpp->stats13();
        if (unlikely(v)) {
            set_stats13(v);
        }
    }

    {_
        auto v = tpp->stats14();
        if (unlikely(v)) {
            set_stats14(v);
        }
    }

    {_
        auto v = tpp->stats15();
        if (unlikely(v)) {
            set_stats15(v);
        }
    }

    {_
        auto v = tpp->stats16();
        if (unlikely(v)) {
            set_stats16(v);
        }
    }

    {_
        auto v = tpp->stats17();
        if (unlikely(v)) {
            set_stats17(v);
        }
    }

    {_
        auto v = tpp->stats18();
        if (unlikely(v)) {
            set_stats18(v);
        }
    }

    {_
        auto v = tpp->stats19();
        if (unlikely(v)) {
            set_stats19(v);
        }
    }

    {_
        auto v = tpp->stats_strength();
        if (unlikely(v)) {
            set_stats_strength(v);
        }
    }

    auto tiles = &tpp->tiles;
    if (tpp->is_gfx_animated()) {
        auto tile = tile_first(tiles);
        if (tile) {
            tile_curr = tile->global_index;
        } else {
            tile_curr = 0;
        }
    } else {
        auto tile = tile_random(tiles);
        if (tile) {
            tile_curr = tile->global_index;
        } else {
            tile_curr = 0;
        }
    }

    if (unlikely(tpp->is_player())) {
        if (level->player && (level->player != this)) {
            ERR("player exists in multiple places on map, %f, %f and %f, %f",
                level->player->mid_at.x, level->player->mid_at.y, 
                mid_at.x, mid_at.y);
            return;
        }
        level->player = this;

        //
        // keep the light strength half the tiles drawn or we get artifacts
        // at the edges of the fbo
        //
        color col = WHITE;
        new_light(mid_at, TILE_WIDTH, col);

        float d1 = 0.2;
        float d2 = 0.15;
        new_light(mid_at, fpoint(d1, d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d1, d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d2, d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d2, d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d1, -d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d1, -d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d2, -d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d2, -d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d1, d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d1, d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d2, d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d2, d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d1, -d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d1, -d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d2, -d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d2, -d2), TILE_WIDTH, col);

        has_light = true;
        log("player created");
    }

    point new_at((int)mid_at.x, (int)mid_at.y);
    if ((new_at.x >= MAP_WIDTH) || (new_at.y >= MAP_HEIGHT)) {
        ERR("new thing is oob at %d, %d", new_at.x, new_at.y);
        return;
    }

    if (tpp->is_blood())       { level->set_blood(new_at.x, new_at.y); }
    if (tpp->is_corridor())    { level->set_corridor(new_at.x, new_at.y); }
    if (tpp->is_dirt())        { level->set_dirt(new_at.x, new_at.y); }
    if (tpp->is_floor())       { level->set_floor(new_at.x, new_at.y); }
    if (tpp->is_hazard())      { level->set_hazard(new_at.x, new_at.y); }
    if (tpp->is_lava())        { level->set_lava(new_at.x, new_at.y); }
    if (tpp->is_chasm())        { level->set_chasm(new_at.x, new_at.y); }
    if (tpp->is_hazard())      { level->set_hazard(new_at.x, new_at.y); }
    if (tpp->is_rock())        { level->set_rock(new_at.x, new_at.y); }
    if (tpp->is_secret_door()) { level->set_secret_door(new_at.x, new_at.y); }
    if (tpp->is_wall())        { level->set_wall(new_at.x, new_at.y); }
    if (tpp->is_water())       { level->set_water(new_at.x, new_at.y); }
    if (tpp->is_deep_water())  { level->set_water(new_at.x, new_at.y); }
    if (tpp->is_deep_water())  { level->set_deep_water(new_at.x, new_at.y); }

    if (tpp->is_gfx_large_shadow()) {
        level->set_is_gfx_large_shadow(new_at.x, new_at.y);
    }

    if (tpp->is_loggable()) {
        log("created");
    }

    if (unlikely(jitter != fpoint(0.0, 0.0))) {
        double dx = random_range(0, TILE_WIDTH);
        double dy = random_range(0, TILE_WIDTH);

        dx -= TILE_WIDTH / 2;
        dy -= TILE_WIDTH / 2;

        dx /= TILE_WIDTH;
        dy /= TILE_WIDTH;

        dx *= jitter.x;
        dy *= jitter.y;

        move_to_immediately(fpoint(mid_at.x + dx, mid_at.y + dy));
    }

    //
    // Set position prior to attach
    //
    set_interpolated_mid_at(mid_at);
    attach();

    //
    // If not the player and has a light source, create the ligh
    //
    if (unlikely(!tpp->is_player())) {
        if (unlikely(tpp->is_light_strength())) {
            std::string l = tpp->light_color();
            bool add_light = true;
            if (random_range(0, 100) < 50) {
                add_light = false;
            }
            if (add_light) {
                color c = string2color(l);
                new_light(mid_at, (double) tpp->is_light_strength(), c);
                has_light = true;
            }
        }
    }
    update_light();

    if (is_gfx_bounce_always()) {
        bounce(0.2, 1.0, 500, 99999);
    }
}

void Thing::reinit (void)
{_
    verify(this);

    level->realloc_thing_id(this);
    const auto tpp = tp();
    if (unlikely(!tpp)) {
        ERR("no tp");
        return;
    }

    auto result = level->all_things.insert(std::pair(id, this));
    if (result.second == false) {
        err("failed to reinsert into thing map");
    }

    if (is_active()) {
        auto result = level->all_active_things.insert(std::pair(id, this));
        if (result.second == false) {
            err("failed to reinsert into active thing map");
        }
    }

    //
    // Probably safest to reset this else things might expire on load
    //
    timestamp_next_frame = 0;
    if (tpp->is_monst() || tpp->is_player()) {
        set_timestamp_born(time_get_time_ms_cached());
    }

    if (unlikely(tpp->is_player())) {
        if (level->player && (level->player != this)) {
            ERR("player exists in multiple places on map, %f, %f and %f, %f",
                level->player->mid_at.x, level->player->mid_at.y,
                mid_at.x, mid_at.y);
            return;
        }
        level->player = this;
        log("player recreated");
    }

    point new_at((int)mid_at.x, (int)mid_at.y);
    if ((new_at.x >= MAP_WIDTH) || (new_at.y >= MAP_HEIGHT)) {
        ERR("new thing is oob at %d, %d", new_at.x, new_at.y);
        return;
    }

    if (tpp->is_blood())       { level->set_blood(new_at.x, new_at.y); }
    if (tpp->is_corridor())    { level->set_corridor(new_at.x, new_at.y); }
    if (tpp->is_dirt())        { level->set_dirt(new_at.x, new_at.y); }
    if (tpp->is_floor())       { level->set_floor(new_at.x, new_at.y); }
    if (tpp->is_hazard())      { level->set_hazard(new_at.x, new_at.y); }
    if (tpp->is_lava())        { level->set_lava(new_at.x, new_at.y); }
    if (tpp->is_chasm())       { level->set_chasm(new_at.x, new_at.y); }
    if (tpp->is_rock())        { level->set_rock(new_at.x, new_at.y); }
    if (tpp->is_secret_door()) { level->set_secret_door(new_at.x, new_at.y); }
    if (tpp->is_wall())        { level->set_wall(new_at.x, new_at.y); }
    if (tpp->is_water())       { level->set_water(new_at.x, new_at.y); }
    if (tpp->is_deep_water())  { level->set_water(new_at.x, new_at.y); }
    if (tpp->is_deep_water())  { level->set_deep_water(new_at.x, new_at.y); }

    if (tpp->is_gfx_large_shadow()) {
        level->set_is_gfx_large_shadow(new_at.x, new_at.y);
    }

    if (tpp->is_loggable()) {
        log("recreated");
    }

    //
    // Upon a load it was attached at save time but not now
    //
    if (is_attached) {
        attach();
    }

    update_light();

    //
    // Relearn the cursor after loading.
    //
    if (is_cursor()) {
        level->cursor = this;
    }
    if (is_player()) {
        level->player = this;
    }
}

void Thing::destroy (void)
{_
    verify(this);

    if (is_loggable()) {
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

    if (is_blood())       { level->unset_blood(old_at.x, old_at.y); }
    if (is_corpse())      { level->unset_corpse(old_at.x, old_at.y); }
    if (is_corridor())    { level->unset_corridor(old_at.x, old_at.y); }
    if (is_dirt())        { level->unset_dirt(old_at.x, old_at.y); }
    if (is_floor())       { level->unset_floor(old_at.x, old_at.y); }
    if (is_hazard())      { level->unset_hazard(old_at.x, old_at.y); }
    if (is_lava())        { level->unset_lava(old_at.x, old_at.y); }
    if (is_chasm())       { level->unset_chasm(old_at.x, old_at.y); }
    if (is_rock())        { level->unset_rock(old_at.x, old_at.y); }
    if (is_secret_door()) { level->unset_secret_door(old_at.x, old_at.y); }
    if (is_wall())        { level->unset_wall(old_at.x, old_at.y); }
    if (is_water())       { level->unset_water(old_at.x, old_at.y); }
    if (is_deep_water())  { level->unset_water(old_at.x, old_at.y); }
    if (is_deep_water())  { level->unset_deep_water(old_at.x, old_at.y); }

    auto tpp = tp();
    if (unlikely(!tpp)) {
        ERR("no tp");
    } else {
        if (tpp->is_gfx_large_shadow()) {
            level->unset_is_gfx_large_shadow(old_at.x, old_at.y);
        }
    }

    if (is_player()) {
        level->player = nullptr;
    }

    delete_dmap_scent();
    delete_age_map();
    delete_light();

    if (is_loggable()) {
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

void Thing::hide (void)
{_
    is_hidden = true;

    //
    // Hide the weapon too or it just floats in the air.
    //
    auto weapon_carry_anim = weapon_get_carry_anim();
    if (weapon_carry_anim) {
        weapon_carry_anim->hide();
    }
}

void Thing::visible (void)
{_
    is_hidden = false;

    //
    // If this thing has an owner, should the thing stay hidden?
    //
    auto owner = owner_get();
    if (owner) {
        if (this == owner->weapon_get_carry_anim()) {
            if (owner->weapon_get_use_anim()) {
                //
                // Stay hidden until the weapon use is done.
                //
                return;
            }
        }
    }

    //
    // Reveal the weapon again too.
    //
    auto weapon_carry_anim = weapon_get_carry_anim();
    if (weapon_carry_anim) {
        weapon_carry_anim->visible();
    }
}

uint8_t Thing::is_visible (void) const
{_
    return (!is_hidden);
}

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::hooks_remove ()
{_
    //
    // We are owned by something. i.e. we are a sword.
    //
    Thingp owner = nullptr;

    if (get_owner_id()) {
        owner = owner_get();
    }

    if (owner) {
        log("detach %08X from owner %s", id, owner->to_string().c_str());

        if (id == owner->get_weapon_id()) {
            owner->unwield("remove hooks");

            log("detach from owner %s", owner->to_string().c_str());
            owner->set_weapon_id(0);
        }

        if (id == owner->get_weapon_id_carry_anim()) {
            owner->unwield("remove hooks");

            log("detach from carry_anim owner %s", owner->to_string().c_str());
            owner->weapon_set_carry_anim_id(0);
        }

        if (id == owner->get_weapon_id_use_anim()) {
            owner->unwield("remove hooks");

            log("detach from use-anim owner %s", owner->to_string().c_str());
            owner->weapon_set_use_anim_id(0);

            //
            // End of the use-animation, make the sword visible again.
            //
            auto carrying = owner->weapon_get_carry_anim();
            if (carrying) {
                //
                // But only if the owner is visible.
                //
                if (owner->is_visible()) {
                    log("reapply carry_anim for owner %s",
                        owner->to_string().c_str());
                    carrying->visible();
                } else {
                    log("do not reapply carry_anim for invisible owner %s",
                        owner->to_string().c_str());
                }
            } else {
                log("no carry_anim for owner %s", owner->to_string().c_str());
                auto id = owner->get_weapon_id();
                if (id) {
                    owner->wield(owner->weapon_get());
                }
            }
        }

        remove_owner();
    }

    //
    // We own things like a sword. i.e. we are a player.
    //
    {_
        auto item = weapon_get_carry_anim();
        if (item) {
            weapon_set_carry_anim(nullptr);
            verify(item);
            item->remove_owner();
            item->dead("weapon carry_anim owner killed");
        }
    }

    {_
        auto item = weapon_get_use_anim();
        if (item) {
            weapon_set_use_anim(nullptr);
            verify(item);
            item->remove_owner();
            item->dead("weapon use-anim owner killed");
        }
    }

    //
    // Some things have lots of things they own
    //
    if (get_owned_count()) {
        log("remove remaining %08X owned things", get_owned_count());

        //
        // Slow, but not used too often
        //
        for (auto slot = 0; slot < MAX_THINGS; slot++) {
            auto p = getptr(level->all_thing_ptrs, slot);
            auto t = p->ptr;
            if (!t) {
                continue;
            }
            verify(t);
            auto o = t->owner_get();
            if (o && (o == this)) {
                t->remove_owner();
            }
        }
    }
}

Thingp Thing::owner_get (void) const
{_
    auto id = get_owner_id();
    if (id) {
        return (thing_find(id));
    } else {
        return (nullptr);
    }
}

void Thing::set_owner (Thingp owner)
{_
    if (owner) {
        verify(owner);
    }

    auto old_owner = owner_get();
    if (old_owner) {
        if (old_owner == owner) {
            return;
        }

        if (tp()->is_loggable()) {
            if (owner) {
                log("set owner change %s->%s", old_owner->to_string().c_str(),
                    owner->to_string().c_str());
            } else {
                log("remove owner %s", old_owner->to_string().c_str());
            }
        }
    } else {
        if (tp()->is_loggable()) {
            if (owner) {
                log("set owner %s", owner->to_string().c_str());
            }
        }
    }

    if (owner) {
        set_owner_id(owner->id);
        owner->incr_owned_count();
    } else {
        set_owner_id(0);
        if (old_owner) {
            old_owner->decr_owned_count();
        }
    }
}

void Thing::remove_owner (void)
{_
    auto old_owner = owner_get();
    if (!old_owner) {
        return;
    }

    if (tp()->is_loggable()) {
        log("remove owner %s", old_owner->to_string().c_str());
    }

    set_owner_id(0);
    old_owner->decr_owned_count();
}

void Thing::update_light (void)
{_
    //
    // Light source follows the thing.
    //
    auto lc = get_light_count();
    size_t c = 0;
    for (auto l : get_light()) {
        fpoint mid_at = l->owner->get_interpolated_mid_at();
        l->at = mid_at;
        l->calculate(c == lc - 1);
        c++;
    }
}

void Thing::update_all (void)
{_
    for (auto slot = 0; slot < MAX_THINGS; slot++) {
        auto p = getptr(level->all_thing_ptrs, slot);
        auto t = p->ptr;
        if (t) {
            verify(t);
            t->update_light();
        }
    }
}
