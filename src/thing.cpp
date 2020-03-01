//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include <list>

void thing_gc (void)
{_
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

        if (tp_is_loggable(t->tp())) {
            t->log("garbage collect");
        }
        delete t;

    }

    level->all_gc_things.clear();
}

Thingp thing_new (std::string tp_name, Thingp owner)
{_
    return thing_new(tp_name, owner->mid_at - fpoint(0.5, 0.5));
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

void Thing::init (std::string name, fpoint at, fpoint jitter)
{_
    verify(this);
_
    timestamp_next_frame = 0;
    const auto tpp = tp_find(name);
    if (unlikely(!tpp)) {
        ERR("thing template [%s] not found", name.c_str());
        return;
    }

    tp_id = tpp->id;

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

    if (tp_is_monst(tpp)) {
        new_dmap_scent();
        new_age_map();
    }

    if (tp_is_monst(tpp) || tp_is_player(tpp) || tp_is_movable(tpp)) {
        set_timestamp_born(time_get_time_ms_cached());
    }

    static const auto sz = fsize(1.0, 1.0);
    at += fpoint(sz.w / 2, sz.h / 2);

    //
    // Find which wall is the closest to cling onto if this is a wall clinger
    //
    mid_at             = at;
    last_mid_at        = mid_at;

    if (tp_gfx_animated_can_hflip(tpp)) {
        dir            = THING_DIR_LEFT;
        is_facing_left = true;
    } else {
        dir            = THING_DIR_NONE;
        is_facing_left = false;
    }
    is_waiting_to_move = true;

    is_hungry = tp_is_hunger_insatiable(tpp);

    {_
        auto v = tp_stats_health_initial(tpp);
        if (unlikely(v)) {
            set_stats_health(v);
            set_stats_health_max(v);
        }
    }

    {_
        auto v = tp_stats_defence(tpp);
        if (unlikely(v)) {
            set_stats_defence(v);
            set_stats_defence_max(v);
        }
    }

    {_
        auto v = tp_stats_attack(tpp);
        if (unlikely(v)) {
            set_stats_attack(v);
            set_stats_attack_max(v);
        }
    }

    {_
        auto v = tp_stats_attack_rate_tenths(tpp);
        if (unlikely(v)) {
            set_stats_attack_rate_tenths(v);
        }
    }

    {_
        auto v = tp_stats_attacked_rate_tenths(tpp);
        if (unlikely(v)) {
            set_stats_attacked_rate_tenths(v);
        }
    }

    {_
        auto v = tp_stats01(tpp);
        if (unlikely(v)) {
            set_stats01(v);
        }
    }

    {_
        auto v = tp_stats02(tpp);
        if (unlikely(v)) {
            set_stats02(v);
        }
    }

    {_
        auto v = tp_stats03(tpp);
        if (unlikely(v)) {
            set_stats03(v);
        }
    }

    {_
        auto v = tp_stats04(tpp);
        if (unlikely(v)) {
            set_stats04(v);
        }
    }

    {_
        auto v = tp_stats05(tpp);
        if (unlikely(v)) {
            set_stats05(v);
        }
    }

    {_
        auto v = tp_stats06(tpp);
        if (unlikely(v)) {
            set_stats06(v);
        }
    }

    {_
        auto v = tp_stats07(tpp);
        if (unlikely(v)) {
            set_stats07(v);
        }
    }

    {_
        auto v = tp_stats08(tpp);
        if (unlikely(v)) {
            set_stats08(v);
        }
    }

    {_
        auto v = tp_stats09(tpp);
        if (unlikely(v)) {
            set_stats09(v);
        }
    }

    {_
        auto v = tp_stats10(tpp);
        if (unlikely(v)) {
            set_stats10(v);
        }
    }

    {_
        auto v = tp_stats11(tpp);
        if (unlikely(v)) {
            set_stats11(v);
        }
    }

    {_
        auto v = tp_stats12(tpp);
        if (unlikely(v)) {
            set_stats12(v);
        }
    }

    {_
        auto v = tp_stats13(tpp);
        if (unlikely(v)) {
            set_stats13(v);
        }
    }

    {_
        auto v = tp_stats14(tpp);
        if (unlikely(v)) {
            set_stats14(v);
        }
    }

    {_
        auto v = tp_stats15(tpp);
        if (unlikely(v)) {
            set_stats15(v);
        }
    }

    {_
        auto v = tp_stats16(tpp);
        if (unlikely(v)) {
            set_stats16(v);
        }
    }

    {_
        auto v = tp_stats17(tpp);
        if (unlikely(v)) {
            set_stats17(v);
        }
    }

    {_
        auto v = tp_stats18(tpp);
        if (unlikely(v)) {
            set_stats18(v);
        }
    }

    {_
        auto v = tp_stats19(tpp);
        if (unlikely(v)) {
            set_stats19(v);
        }
    }

    {_
        auto v = tp_stats_strength(tpp);
        if (unlikely(v)) {
            set_stats_strength(v);
        }
    }

    auto tiles = tp_tiles(tpp);
    if (tpp->gfx_animated) {
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

    if (unlikely(tp_is_player(tpp))) {
        if (level->player && (level->player != this)) {
            ERR("player exists in multiple places on map, %f, %f and %f, %f",
                level->player->mid_at.x,
                level->player->mid_at.y,
                mid_at.x,
                mid_at.y);
            return;
        }
        level->player = this;

        //
        // keep the light strength half the tiles drawn or we get artifacts
        // at the edges of the fbo
        //
        color col = WHITE;
        new_light(mid_at, (TILE_WIDTH / 2) + 4, LIGHT_QUALITY_HIGH, col);

        has_light = true;
        log("player created");
    }

    point new_at((int)at.x, (int)at.y);
    if ((new_at.x >= MAP_WIDTH) || (new_at.y >= MAP_HEIGHT)) {
        ERR("new thing is oob at %d, %d", new_at.x, new_at.y);
        return;
    }

    if (tp_is_blood(tpp))       { level->set_blood(new_at.x, new_at.y); }
    if (tp_is_chasm(tpp))       { level->set_chasm(new_at.x, new_at.y); }
    if (tp_is_corridor(tpp))    { level->set_corridor(new_at.x, new_at.y); }
    if (tp_is_dirt(tpp))        { level->set_dirt(new_at.x, new_at.y); }
    if (tp_is_floor(tpp))       { level->set_floor(new_at.x, new_at.y); }
    if (tp_is_hazard(tpp))      { level->set_hazard(new_at.x, new_at.y); }
    if (tp_is_lava(tpp))        { level->set_lava(new_at.x, new_at.y); }
    if (tp_is_rock(tpp))        { level->set_rock(new_at.x, new_at.y); }
    if (tp_is_secret_door(tpp)) { level->set_secret_door(new_at.x, new_at.y); }
    if (tp_is_wall(tpp))        { level->set_wall(new_at.x, new_at.y); }
    if (tp_is_water(tpp))       { level->set_water(new_at.x, new_at.y); }

    if (tp_is_deep_water(tpp)) {
        level->set_deep_water(new_at.x, new_at.y);
        level->set_water(new_at.x, new_at.y);
    }
    if (tp_gfx_large_shadow(tpp)) {
        level->set_gfx_large_shadow(new_at.x, new_at.y);
    }

    if (tp_is_loggable(tpp)) {
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

    update_coordinates();
    attach();

    if (unlikely(!tp_is_player(tpp))) {
        if (unlikely(tp_is_light_strength(tpp))) {
            std::string l = tp_str_light_color(tpp);
            color c = string2color(l);
            new_light(mid_at,
                      (double) tp_is_light_strength(tpp),
                      LIGHT_QUALITY_HIGH, c);
            has_light = true;
        }
    }
    update_light();
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
    if (tp_is_monst(tpp) || tp_is_player(tpp)) {
        set_timestamp_born(time_get_time_ms_cached());
    }

    if (unlikely(tp_is_player(tpp))) {
        if (level->player && (level->player != this)) {
            ERR("player exists in multiple places on map, %f, %f and %f, %f",
                level->player->mid_at.x,
                level->player->mid_at.y,
                mid_at.x,
                mid_at.y);
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

    if (tp_is_blood(tpp))       { level->set_blood(new_at.x, new_at.y); }
    if (tp_is_chasm(tpp))       { level->set_chasm(new_at.x, new_at.y); }
    if (tp_is_corridor(tpp))    { level->set_corridor(new_at.x, new_at.y); }
    if (tp_is_dirt(tpp))        { level->set_dirt(new_at.x, new_at.y); }
    if (tp_is_floor(tpp))       { level->set_floor(new_at.x, new_at.y); }
    if (tp_is_hazard(tpp))      { level->set_hazard(new_at.x, new_at.y); }
    if (tp_is_lava(tpp))        { level->set_lava(new_at.x, new_at.y); }
    if (tp_is_rock(tpp))        { level->set_rock(new_at.x, new_at.y); }
    if (tp_is_secret_door(tpp)) { level->set_secret_door(new_at.x, new_at.y); }
    if (tp_is_wall(tpp))        { level->set_wall(new_at.x, new_at.y); }
    if (tp_is_water(tpp))       { level->set_water(new_at.x, new_at.y); }

    if (tp_is_deep_water(tpp)) {
        level->set_deep_water(new_at.x, new_at.y);
        level->set_water(new_at.x, new_at.y);
    }
    if (tp_gfx_large_shadow(tpp)) {
        level->set_gfx_large_shadow(new_at.x, new_at.y);
    }

    if (tp_is_loggable(tpp)) {
        log("recreated");
    }

    update_coordinates();

    //
    // Upon a load it was attached at save time but not now
    //
    if (is_attached) {
        attach();
    }

    update_light();
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
    if (is_chasm())       { level->unset_chasm(old_at.x, old_at.y); }
    if (is_corpse())      { level->unset_corpse(old_at.x, old_at.y); }
    if (is_corridor())    { level->unset_corridor(old_at.x, old_at.y); }
    if (is_deep_water())  { level->unset_deep_water(old_at.x, old_at.y); }
    if (is_dirt())        { level->unset_dirt(old_at.x, old_at.y); }
    if (is_floor())       { level->unset_floor(old_at.x, old_at.y); }
    if (is_hazard())      { level->unset_hazard(old_at.x, old_at.y); }
    if (is_lava())        { level->unset_lava(old_at.x, old_at.y); }
    if (is_rock())        { level->unset_rock(old_at.x, old_at.y); }
    if (is_secret_door()) { level->unset_secret_door(old_at.x, old_at.y); }
    if (is_wall())        { level->unset_wall(old_at.x, old_at.y); }
    if (is_water())       { level->unset_water(old_at.x, old_at.y); }

    auto tpp = tp();
    if (unlikely(!tpp)) {
        ERR("no tp");
    } else {
        if (tp_gfx_large_shadow(tpp)) {
            level->unset_gfx_large_shadow(old_at.x, old_at.y);
        }
    }

    if (is_player()) {
        level->player = nullptr;
    }

    delete_dmap_scent();
    delete_age_map();
    delete_light();
_
    if (is_loggable()) {
        log("destroyed");
    }
_
    {
        auto f = level->all_things.find(id);
        if (f != level->all_things.end()) {
            level->all_things.erase(f);
        }
    }
_
    if (is_active()) {
        auto f = level->all_active_things.find(id);
        if (f != level->all_active_things.end()) {
            level->all_active_things.erase(f);
        }
    }
_
    {
        auto f = level->all_gc_things.find(id);
        if (f != level->all_gc_things.end()) {
            level->all_gc_things.erase(f);
        }
    }
_
    level->free_thing_id(this);
_
    if (monst) {
        oldptr(monst);
        delete monst;
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

uint8_t Thing::is_visible (void)
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

            log("detach from carry-anim owner %s", owner->to_string().c_str());
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
                    log("reapply carry-anim for owner %s",
                        owner->to_string().c_str());
                    carrying->visible();
                } else {
                    log("do not reapply carry-anim for invisible owner %s",
                        owner->to_string().c_str());
                }
            } else {
                log("no carry-anim for owner %s", owner->to_string().c_str());
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
            item->dead("weapon carry-anim owner killed");
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

Thingp Thing::owner_get (void)
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

        if (owner) {
            log("set owner change %s->%s", old_owner->to_string().c_str(),
                owner->to_string().c_str());
        } else {
            log("remove owner %s", old_owner->to_string().c_str());
        }
    } else {
        if (owner) {
            log("set owner %s", owner->to_string().c_str());
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

    log("remove owner %s", old_owner->to_string().c_str());

    set_owner_id(0);
    old_owner->decr_owned_count();
}

void Thing::update_light (void)
{_
    //
    // Light source follows the thing.
    //
    auto l = get_light();
    if (l) {
        verify(l);
        l->at = get_interpolated_mid_at();
        l->calculate();
    }
}

void Thing::move_carried_items (void)
{_
    //
    // Light source follows the thing.
    //
    update_light();

    //
    // Weapons follow also.
    //
    if (get_weapon_id_carry_anim()) {
        auto w = thing_find(get_weapon_id_carry_anim());
        if (!w) {
            err("weapon_id_carry_anim set to %08X but not found",
                get_weapon_id_carry_anim());
            return;
        }
        w->move_to(mid_at);
        w->dir = dir;
    }

    if (get_weapon_id_use_anim()) {
        auto w = thing_find(get_weapon_id_use_anim());
        if (!w) {
            err("weapon_id_use_anim set to %08X but not found",
                get_weapon_id_use_anim());
            return;
        }
        w->move_to(mid_at);
        w->dir = dir;
    }

    //
    // If something moves on the water, make a ripple
    //
    if (is_monst() || is_player()) {
        if (level->is_water((int)mid_at.x, (int)mid_at.y)) {
            fpoint at(mid_at.x - 0.5, mid_at.y - 0.5);
            if (random_range(0, 1000) > 500) {
                thing_new(tp_name(tp_random_ripple()), at);
            }
        }
    }
}

std::string Thing::to_string (void)
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return (string_sprintf("%08X(<no tp>%s hp %d/%d @%g,%g)",
                               id,
                               is_dead ? "/dead" : "",
                               get_stats_health(),
                               get_stats_health_max(),
                               mid_at.x, mid_at.y));
    } else if (get_stats_health_max()) {
        return (string_sprintf("%08X(%s%s hp %d/%d @%g,%g)",
                               id, tpp->name.c_str(),
                               is_dead ? "/dead" : "",
                               get_stats_health(),
                               get_stats_health_max(),
                               mid_at.x, mid_at.y));
    } else {
        return (string_sprintf("%08X(%s%s @%g,%g)",
                               id, tpp->name.c_str(),
                               is_dead ? "/dead" : "",
                               mid_at.x, mid_at.y));
    }
}

std::string Thing::to_name (void)
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no tp>");
    }

    std::string real_name = "";

    if (is_undead()) {
        if (is_dead) {
            real_name += "inanimate ";
        } else {
            real_name += "undead ";
        }
    } else {
        if (is_dead) {
            real_name += "dead ";
        }
    }

    real_name += tpp->real_name;

    return (real_name);
}

const char * Thing::to_cstring (void)
{_
    return (to_string().c_str());
}

void Thing::kill (void)
{_
    if (is_dead) {
        return;
    }
    is_dead = true;

    //
    // Unwield weapons
    //
    unwield("owner is dead");

    if (is_player()) {
        MINICON("%%fg=red$Congratulations, you are dead!%%fg=reset$");
        game->dead_select();
    }

    const auto tpp = tp();
    if (unlikely(!tpp)) {
        ERR("no tp");
    } else {
        if (is_corpse_on_death()) {
            if (tp_is_loggable(tpp)) {
                log("killed, leaves corpse");
            }

            level->set_corpse(mid_at.x, mid_at.y);

            if (tp_is_bleeder(tpp)) {
                int splatters = random_range(2, 10);
                for (int splatter = 0; splatter < splatters; splatter++) {
                    auto tpp = tp_random_blood();
                    (void) thing_new(tp_name(tpp),
                                     fpoint(mid_at.x, mid_at.y),
                                     fpoint(0.25, 0.25));
                }
            }
            return;
        }

        if (tp_is_loggable(tpp)) {
            log("killed");
        }
    }

    auto result = level->all_gc_things.insert(std::pair(id, this));
    if (result.second == false) {
        err("failed to insert into gc thing map");
    }
}

void Thing::update_all (void)
{_
    for (auto slot = 0; slot < MAX_THINGS; slot++) {
        auto p = getptr(level->all_thing_ptrs, slot);
        auto t = p->ptr;
        if (t) {
            verify(t);
            t->update_coordinates();
            t->update_light();
        }
    }
}
