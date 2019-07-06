//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_tile_info.h"
#include "my_color.h"
#include "my_dmap.h"

static uint32_t next_thing_id;

#undef ENABLE_THING_DEBUG

static std::list<uint32_t> things_to_delete;

void thing_gc (void)
{
    for (auto id : things_to_delete) {
        auto t = thing_find(id);
        if (!t) {
            ERR("thing %u not found to garbage collect", id);
            continue;
        }

        t->log("garbage collect");
        delete t;
    }

    //
    // No need to call remove as we did the safe destroy above.
    //
    things_to_delete.clear();
}

Thingp thing_new (std::string tp_name, Thingp owner)
{_
    return thing_new(tp_name, owner->mid_at - fpoint(0.5, 0.5));
}

Thingp thing_new (std::string tp_name, fpoint at, fpoint jitter)
{_
    auto id = ++next_thing_id;

    auto t = new Thing;
    auto tp = t->tp = tp_find(tp_name);
    if (!t->tp) {
        DIE("thing [%s] not found", tp_name.c_str());
    }

    t->id = id;

    auto p = std::make_pair(t->id, t);
    auto result = game.state.map.all_things.insert(p);
    if (result.second == false) {
        DIE("thing insert [%d] failed", id);
    }

    if (tp_is_active(tp)) {
        auto result = game.state.map.all_active_things.insert(p);
        if (result.second == false) {
            DIE("thing insert active [%d] failed", id);
        }
    }

    auto sz = fsize(1.0, 1.0);
    at += fpoint(sz.w / 2, sz.h / 2);

    point new_at((int)at.x, (int)at.y);
    if ((new_at.x >= MAP_WIDTH) || (new_at.y >= MAP_HEIGHT)) {
        DIE("new thing is oob at %d, %d", new_at.x, new_at.y);
    }

    //
    // Find which wall is the closest to cling onto if this is a wall clinger
    //
    t->ground_at          = at;
    t->mid_at             = at;
    t->last_mid_at        = t->mid_at;
    t->depth              = tp_z_depth(tp);

    if (tp_gfx_can_hflip(tp)) {
        t->dir            = THING_DIR_LEFT;
        t->is_facing_left = true;
    } else {
        t->dir            = THING_DIR_NONE;
        t->is_facing_left = false;
    }

    t->is_hungry          = tp_hunger_constant(tp);
    t->is_starving        = false;
    t->is_dead            = false;
    t->is_bloodied        = false;
    t->is_hidden          = false;
    t->is_sleeping        = false;
    t->is_moving          = false;
    t->has_ever_moved     = false;
    t->is_open            = false;
    t->is_bouncing        = false;
    t->is_attached        = false;
    t->is_lit             = false;
    t->is_being_destroyed = false;
    t->is_waiting_for_ai  = tp_is_active(tp);
    t->is_submerged       = tp_is_active(tp);

    t->health         = tp_hunger_initial_health_at(tp);
    t->max_health     = t->health;

    t->timestamp_born = time_get_time_ms_cached();

    auto tiles = tp_left_tiles(tp);
    auto tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->left_tile = tinfo->tile;
    }

    tiles = tp_right_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->right_tile = tinfo->tile;
    }

    tiles = tp_top_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->top_tile = tinfo->tile;
    }

    tiles = tp_bot_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->bot_tile = tinfo->tile;
    }

    tiles = tp_tl_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->tl_tile = tinfo->tile;
    }

    tiles = tp_tr_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->tr_tile = tinfo->tile;
    }

    tiles = tp_br_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->br_tile = tinfo->tile;
    }

    tiles = tp_bl_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->bl_tile = tinfo->tile;
    }

    tiles = tp_tiles(tp);
    if (tp->gfx_animated) {
        tinfo = tile_info_first(tiles);
    } else {
        tinfo = tile_info_random(tiles);
    }

    if (tinfo) {
        t->current_tileinfo = tinfo;
        t->current_tile = tinfo->tile;
    }

    if (tp_is_player(tp)) {
        if (game.state.player && (game.state.player != t)) {
            DIE("player exists in multiple places on map, %f, %f and %f, %f",
                game.state.player->mid_at.x,
                game.state.player->mid_at.y,
                t->mid_at.x,
                t->mid_at.y);
        }
        game.state.player = t;

        color col = WHITE;
        //
        // keep the light strength half the tiles drawn or we get artifacts
        // at the edges of the fbo
        //
        col.a = 250;
        t->light = light_new(t, MAX_LIGHT_RAYS, (TILE_WIDTH / 2) + 4, at,
                             LIGHT_QUALITY_HIGH, col);

        t->log("player created");
    }

    if (tp_is_wall(tp)) {
        game.state.map.set_wall(new_at.x, new_at.y);
    }
    if (tp_is_wall(tp)) {
        game.state.map.set_solid(new_at.x, new_at.y);
    }
    if (tp_is_floor(tp)) {
        game.state.map.set_floor(new_at.x, new_at.y);
    }
    if (tp_is_lava(tp)) {
        game.state.map.set_lava(new_at.x, new_at.y);
    }
    if (tp_is_blood(tp)) {
        game.state.map.set_blood(new_at.x, new_at.y);
    }
    if (tp_is_water(tp)) {
        game.state.map.set_water(new_at.x, new_at.y);
    }
    if (tp_is_deep_water(tp)) {
        game.state.map.set_deep_water(new_at.x, new_at.y);
        game.state.map.set_water(new_at.x, new_at.y);
    }
    if (tp_is_corridor(tp)) {
        game.state.map.set_corridor(new_at.x, new_at.y);
    }
    if (tp_is_dirt(tp)) {
        game.state.map.set_dirt(new_at.x, new_at.y);
    }
    if (tp_is_grass(tp)) {
        game.state.map.set_grass(new_at.x, new_at.y);
    }
    if (tp_is_soil(tp)) {
        game.state.map.set_soil(new_at.x, new_at.y);
    }
    if (tp_is_gravel(tp)) {
        game.state.map.set_gravel(new_at.x, new_at.y);
    }
    if (tp_is_snow(tp)) {
        game.state.map.set_snow(new_at.x, new_at.y);
    }
    if (tp_is_monst(tp)) {
        game.state.map.set_monst(new_at.x, new_at.y);
    }
    if (tp_is_food(tp)) {
        game.state.map.set_food(new_at.x, new_at.y);
    }
    if (tp_is_rock(tp)) {
        game.state.map.set_rock(new_at.x, new_at.y);
    }
    if (tp_is_key(tp)) {
        game.state.map.set_key(new_at.x, new_at.y);
    }
    if (tp_gfx_large_shadow_caster(tp)) {
        game.state.map.set_gfx_large_shadow_caster(new_at.x, new_at.y);
    }
    if (tp_is_door(tp)) {
        game.state.map.set_door(new_at.x, new_at.y);
    }

    if (!tp_does_nothing(tp)) {
        t->log("created");
    }

    if (jitter != fpoint(0.0, 0.0)) {
        double dx = random_range(0, TILE_WIDTH);
        double dy = random_range(0, TILE_WIDTH);

        dx -= TILE_WIDTH / 2;
        dy -= TILE_WIDTH / 2;

        dx /= TILE_WIDTH;
        dy /= TILE_WIDTH;

        dx *= jitter.x;
        dy *= jitter.y;

        t->move_to(fpoint(t->mid_at.x + dx, t->mid_at.y + dy));
    }

    t->update_coordinates();
    t->attach();

    if (tp_is_light_strength(tp)) {
        std::string l = tp_str_light_color(tp);
        color c = string2color(l);
        c.a = 100;
        t->light = light_new(t, MAX_LIGHT_RAYS / 8,
                             (double) tp_is_light_strength(tp),
                             t->mid_at, LIGHT_QUALITY_LOW, c);
    }

    if (tp_is_monst(tp)) {
        t->dmap_scent = (__typeof__(t->dmap_scent))
                          mymalloc(sizeof(*t->dmap_scent), "dmap scent");
    } else {
        t->dmap_scent = nullptr;
    }

    if (tp_is_monst(tp)) {
        t->dmap_goals = (__typeof__(t->dmap_goals))
                          mymalloc(sizeof(*t->dmap_goals), "dmap goals");
    } else {
        t->dmap_goals = nullptr;
    }

    if (tp_is_monst(tp)) {
        t->age_map = (__typeof__(t->age_map)) mymalloc(sizeof(*t->age_map), "cell age_map");
        memset(t->age_map, 0, sizeof(*t->age_map));
    } else {
        t->age_map = nullptr;
    }

    return (t);
}

void Thing::hide (void)
{_
    is_hidden = true;

    //
    // Hide the weapon too or it just floats in the air.
    //
    auto weapon_carry_anim = get_weapon_carry_anim();
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
    auto owner = get_owner();
    if (owner) {
        if (this == owner->get_weapon_carry_anim()) {
            if (owner->get_weapon_use_anim()) {
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
    auto weapon_carry_anim = get_weapon_carry_anim();
    if (weapon_carry_anim) {
        weapon_carry_anim->visible();
    }
}

uint8_t Thing::is_visible (void)
{
    return (!is_hidden);
}

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::remove_hooks ()
{_
    //
    // We are owned by something. i.e. we are a sword.
    //
    Thingp owner = 0;

    if (owner_thing_id) {
        owner = get_owner();
    }

    if (owner_thing_id && owner) {
#ifdef ENABLE_THING_DEBUG
        log("detach %d from owner %s", id, owner->to_string().c_str());
#endif
        if (id == owner->weapon_carry_anim_thing_id) {
            unwield("remove hooks");

#ifdef ENABLE_THING_DEBUG
            log("detach from carry anim owner %s", owner->to_string().c_str());
#endif

            owner->set_weapon_carry_anim(nullptr);
        }

        if (id == owner->weapon_use_anim_thing_id) {
#ifdef ENABLE_THING_DEBUG
            log("detach from use anim owner %s", owner->to_string().c_str());
#endif
            owner->set_weapon_use_anim(nullptr);

            //
            // End of the use animation, make the sword visible again.
            //
            auto carrying = owner->get_weapon_carry_anim();
            if (carrying) {
                //
                // But only if the owner is visible. They may have reached the
                // level.
                //
                if (owner->is_visible()) {
                    carrying->visible();
                }
            }
        }

        set_owner(nullptr);
    }

    //
    // We own things like a sword. i.e. we are a player.
    //
    if (weapon_carry_anim_thing_id) {
        auto item = get_weapon_carry_anim();
        set_weapon_carry_anim(nullptr);
        verify(item);
        item->set_owner(nullptr);
        item->dead("weapon carry anim owner killed");
    }

    if (weapon_use_anim_thing_id) {
        auto item = get_weapon_use_anim();
        set_weapon_use_anim(nullptr);
        verify(item);
        item->set_owner(nullptr);
        item->dead("weapon use anim owner killed");
    }

    //
    // Some things have lots of things they own
    //
    if (owned_count) {
        log("remove remaining %u owned things", owned_count);

        for (auto i : game.state.map.all_active_things) {
            Thingp t = i.second;
            auto o = t->get_owner();
            if (o && (o == t)) {
                t->set_owner(nullptr);
            }
        }
    }
}

Thingp Thing::get_owner (void)
{
    if (owner_thing_id) {
        return (thing_find(owner_thing_id));
    } else {
        return (nullptr);
    }
}

void Thing::set_owner (Thingp owner)
{
    if (owner) {
        verify(owner);
    }

    auto old_owner = get_owner();
    if (old_owner) {
        if (old_owner == owner) {
            return;
        }

        if (owner) {
            log("set-owner change %s->%s", old_owner->to_string().c_str(),
                owner->to_string().c_str());
        } else {
            log("set-owner remove owner %s", old_owner->to_string().c_str());
        }
    } else {
        if (owner) {
            log("set-owner %s", owner->to_string().c_str());
        }
    }

    if (owner) {
        owner_thing_id = owner->id;

        owner->owned_count++;
    } else {
        owner_thing_id = 0;

        if (old_owner) {
            old_owner->owned_count--;
        }
    }
}

void Thing::destroy (void)
{_
    verify(this);
#ifdef ENABLE_THING_DEBUG
    log("destroy");
#else
    if (!does_nothing()) {
        log("destroy");
    }
#endif

    detach();

    {
        auto a = &game.state.map.all_things;
        auto iter = a->find(id);
        if (iter != a->end()) {
            if (is_active()) {
                log("erasing from all things");
            }
            game.state.map.all_things.erase(iter);
        } else {
            //
            // May have been removed already in cleanup. Ignore.
            //
        }
    }

    {
        auto a = &game.state.map.all_active_things;
        auto iter = a->find(id);
        if (iter != a->end()) {
            if (is_active()) {
                log("erasing from active things");
            }
            game.state.map.all_active_things.erase(iter);
        } else {
            //
            // May have been removed already in cleanup. Ignore.
            //
        }
    }

    //
    // Pop from the map
    //
    point old_at((int)mid_at.x, (int)mid_at.y);

    if (is_wall()) {
        game.state.map.unset_wall(old_at.x, old_at.y);
    }
    if (is_wall() || is_rock()) {
        game.state.map.unset_solid(old_at.x, old_at.y);
    }
    if (is_floor()) {
        game.state.map.unset_floor(old_at.x, old_at.y);
    }
    if (is_lava()) {
        game.state.map.unset_lava(old_at.x, old_at.y);
    }
    if (is_blood()) {
        game.state.map.unset_blood(old_at.x, old_at.y);
    }
    if (is_water()) {
        game.state.map.unset_water(old_at.x, old_at.y);
    }
    if (is_deep_water()) {
        game.state.map.unset_deep_water(old_at.x, old_at.y);
    }
    if (is_corridor()) {
        game.state.map.unset_corridor(old_at.x, old_at.y);
    }
    if (is_dirt()) {
        game.state.map.unset_dirt(old_at.x, old_at.y);
    }
    if (is_grass()) {
        game.state.map.unset_grass(old_at.x, old_at.y);
    }
    if (is_soil()) {
        game.state.map.unset_soil(old_at.x, old_at.y);
    }
    if (is_gravel()) {
        game.state.map.unset_gravel(old_at.x, old_at.y);
    }
    if (is_snow()) {
        game.state.map.unset_snow(old_at.x, old_at.y);
    }
    if (is_monst()) {
        game.state.map.unset_monst(old_at.x, old_at.y);
    }
    if (is_food()) {
        game.state.map.unset_food(old_at.x, old_at.y);
    }
    if (is_rock()) {
        game.state.map.unset_rock(old_at.x, old_at.y);
    }
    if (is_key()) {
        game.state.map.unset_key(old_at.x, old_at.y);
    }
    if (tp_gfx_large_shadow_caster(tp)) {
        game.state.map.unset_gfx_large_shadow_caster(old_at.x, old_at.y);
    }
    if (is_door()) {
        game.state.map.unset_door(old_at.x, old_at.y);
    }
    if (is_player()) {
        game.state.player = nullptr;
    }

    if (dmap_scent) {
        myfree(dmap_scent);
        dmap_scent = nullptr;
    }

    if (dmap_goals) {
        myfree(dmap_goals);
        dmap_goals = nullptr;
    }

    if (age_map) {
        myfree(age_map);
        age_map = nullptr;
    }
}

void Thing::update_light (void)
{_
    //
    // Light source follows the thing.
    //
    if (light) {
        light->move_to(interpolated_mid_at);
        light->calculate();
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
    if (weapon_carry_anim_thing_id) {
        auto w = thing_find(weapon_carry_anim_thing_id);
        if (!w) {
            die("weapon_carry_anim_thing_id set to %d but not found",
                weapon_carry_anim_thing_id);
        }
        w->move_to(mid_at);
        w->dir = dir;
    }

    if (weapon_use_anim_thing_id) {
        auto w = thing_find(weapon_use_anim_thing_id);
        if (!w) {
            die("weapon_use_anim_thing_id set to %d but not found",
                weapon_use_anim_thing_id);
        }
        w->move_to(mid_at);
        w->dir = dir;
    }

    //
    // If something moves on the water, make a ripple
    //
    if (is_monst() || is_player()) {
        if (game.state.map.is_water((int)mid_at.x, (int)mid_at.y)) {
            fpoint at(mid_at.x - 0.5, mid_at.y - 0.5);
            if (random_range(0, 1000) > 500) {
                thing_new(tp_name(tp_random_ripple()), at);
            }
        }
    }
}

//
// Find an existing thing.
//
Thingp thing_find (uint32_t id)
{_
    auto result = game.state.map.all_things.find(id);
    if (result == game.state.map.all_things.end()) {
        return (0);
    }

    return (result->second);
}

std::string Thing::to_string (void)
{_
    verify(this);
    verify(tp);
    return (string_sprintf("%u(%s%s) at (%g,%g)",
                           id, tp->name.c_str(),
                           is_dead ? "/dead" : "",
                           mid_at.x, mid_at.y));
}

const char * Thing::to_cstring (void)
{
    return (to_string().c_str());
}

void Thing::kill (void)
{_
    if (is_dead) {
        return;
    }
    is_dead = true;

    if (is_corpse_on_death()) {
        return;
    }

    remove_hooks();
    things_to_delete.push_back(id);
}
