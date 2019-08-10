//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"

static uint32_t next_thing_id;

#undef ENABLE_THING_DEBUG

static std::list<uint32_t> things_to_delete;

void thing_gc (Worldp world)
{
    for (auto id : things_to_delete) {
        auto t = thing_find(world, id);
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

Thingp thing_new (Worldp world, std::string tp_name, Thingp owner)
{_
    return thing_new(world, tp_name, owner->mid_at - fpoint(0.5, 0.5));
}

Thingp thing_new (Worldp world,
                  std::string tp_name, fpoint at, fpoint jitter)
{_
    auto id = ++next_thing_id;

    auto t = new Thing;

    t->age_map = 0;
    t->dmap_goals = 0;
    t->dmap_scent = 0;
    t->light = 0;
    t->tp = 0;
    t->world = 0;
    t->bounce_fade = 0;
    t->bounce_height = 0;
    t->rot = 0;
    t->submerged_offset = 0;
    t->gold = 0;
    t->health = 0;
    t->health_max = 0;
    t->bounce_count = 0;
    t->owned_count = 0;
    t->tile_bl = 0;
    t->tile_bot = 0;
    t->tile_br = 0;
    t->tile_curr = 0;
    t->tile_left = 0;
    t->tile_right = 0;
    t->tile_tl = 0;
    t->tile_top = 0;
    t->tile_tr = 0;
    t->weapon_tp_id = 0;
    t->hunger_tick_last_ms = 0;
    t->id = 0;
    t->id_owner = 0;
    t->id_weapon_carry_anim = 0;
    t->id_weapon_use_anim = 0;
    t->light_iterator = 0;
    t->timestamp_ai_next = 0;
    t->timestamp_born = 0;
    t->timestamp_bounce_begin = 0;
    t->timestamp_bounce_end = 0;
    t->timestamp_collision = 0;
    t->timestamp_flip_start = 0;
    t->timestamp_last_attacked = 0;
    t->timestamp_last_i_was_hit = 0;
    t->timestamp_move_begin = 0;
    t->timestamp_move_end = 0;
    t->timestamp_move_start = 0;
    t->timestamp_next_frame = 0;
    t->depth = 0;
    t->dir = 0;
    t->has_ever_moved = 0;
    t->is_attached = 0;
    t->is_being_destroyed = 0;
    t->is_bloodied = 0;
    t->is_bouncing = 0;
    t->is_dead = 0;
    t->is_facing_left = 0;
    t->is_hidden = 0;
    t->is_hungry = 0;
    t->is_init = 0;
    t->is_lit = 0;
    t->is_moving = 0;
    t->is_open = 0;
    t->is_sleeping = 0;
    t->is_starving = 0;
    t->is_submerged = 0;
    t->is_waiting_for_ai = 0;

    auto tp = t->tp = tp_find(tp_name);
    if (!t->tp) {
        DIE("thing [%s] not found", tp_name.c_str());
    }


    auto p = std::make_pair(t->id, t);
    auto result = world->all_things.insert(p);
    if (result.second == false) {
        DIE("thing insert [%d] failed", id);
    }

    if (tp_is_active(tp)) {
        auto result = world->all_active_things.insert(p);
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

    t->is_init               = true;
    t->is_hungry             = tp_hunger_constant(tp);
    t->is_starving           = false;
    t->is_dead               = false;
    t->is_bloodied           = false;
    t->is_hidden             = false;
    t->is_sleeping           = false;
    t->is_moving             = false;
    t->has_ever_moved        = false;
    t->is_open               = false;
    t->is_bouncing           = false;
    t->is_attached           = false;
    t->is_lit                = false;
    t->is_being_destroyed    = false;
    t->is_waiting_for_ai     = tp_is_active(tp);
    t->is_submerged          = tp_is_active(tp);

    t->health         = tp_hunger_initial_health_at(tp);
    t->health_max     = t->health;

    t->timestamp_born = time_get_time_ms_cached();

    auto tiles = tp_tile_lefts(tp);
    auto tile = tile_random(tiles);
    if (tile) {
        t->tile_left = tile->global_index;
    }

    tiles = tp_tile_rights(tp);
    tile = tile_random(tiles);
    if (tile) {
        t->tile_right = tile->global_index;
    }

    tiles = tp_tile_tops(tp);
    tile = tile_random(tiles);
    if (tile) {
        t->tile_top = tile->global_index;
    }

    tiles = tp_tile_bots(tp);
    tile = tile_random(tiles);
    if (tile) {
        t->tile_bot = tile->global_index;
    }

    tiles = tp_tile_tls(tp);
    tile = tile_random(tiles);
    if (tile) {
        t->tile_tl = tile->global_index;
    }

    tiles = tp_tile_trs(tp);
    tile = tile_random(tiles);
    if (tile) {
        t->tile_tr = tile->global_index;
    }

    tiles = tp_tile_brs(tp);
    tile = tile_random(tiles);
    if (tile) {
        t->tile_br = tile->global_index;
    }

    tiles = tp_tile_bls(tp);
    tile = tile_random(tiles);
    if (tile) {
        t->tile_bl = tile->global_index;
    }

    tiles = tp_tiles(tp);
    if (tp->gfx_animated) {
        tile = tile_first(tiles);
    } else {
        tile = tile_random(tiles);
    }

    if (tile) {
        t->tile_curr = tile->global_index;
    }

    if (tp_is_player(tp)) {
        if (world->player && (world->player != t)) {
            DIE("player exists in multiple places on map, %f, %f and %f, %f",
                world->player->mid_at.x,
                world->player->mid_at.y,
                t->mid_at.x,
                t->mid_at.y);
        }
        world->player = t;

        color col = WHITE;
        //
        // keep the light strength half the tiles drawn or we get artifacts
        // at the edges of the fbo
        //
        col.a = 250;
        t->light = light_new(world, t,
                             MAX_LIGHT_RAYS, (TILE_WIDTH / 2) + 4, at,
                             LIGHT_QUALITY_HIGH, col);

        t->log("player created");
    }

    if (tp_is_wall(tp)) {
        world->set_wall(new_at.x, new_at.y);
    }
    if (tp_is_wall(tp)) {
        world->set_solid(new_at.x, new_at.y);
    }
    if (tp_is_floor(tp)) {
        world->set_floor(new_at.x, new_at.y);
    }
    if (tp_is_lava(tp)) {
        world->set_lava(new_at.x, new_at.y);
    }
    if (tp_is_blood(tp)) {
        world->set_blood(new_at.x, new_at.y);
    }
    if (tp_is_water(tp)) {
        world->set_water(new_at.x, new_at.y);
    }
    if (tp_is_deep_water(tp)) {
        world->set_deep_water(new_at.x, new_at.y);
        world->set_water(new_at.x, new_at.y);
    }
    if (tp_is_corridor(tp)) {
        world->set_corridor(new_at.x, new_at.y);
    }
    if (tp_is_dirt(tp)) {
        world->dir_sett(new_at.x, new_at.y);
    }
    if (tp_is_grass(tp)) {
        world->set_grass(new_at.x, new_at.y);
    }
    if (tp_is_soil(tp)) {
        world->set_soil(new_at.x, new_at.y);
    }
    if (tp_is_gravel(tp)) {
        world->set_gravel(new_at.x, new_at.y);
    }
    if (tp_is_snow(tp)) {
        world->set_snow(new_at.x, new_at.y);
    }
    if (tp_is_monst(tp)) {
        world->set_monst(new_at.x, new_at.y);
    }
    if (tp_is_food(tp)) {
        world->set_food(new_at.x, new_at.y);
    }
    if (tp_is_rock(tp)) {
        world->set_rock(new_at.x, new_at.y);
    }
    if (tp_is_key(tp)) {
        world->set_key(new_at.x, new_at.y);
    }
    if (tp_gfx_large_shadow_caster(tp)) {
        world->set_gfx_large_shadow_caster(new_at.x, new_at.y);
    }
    if (tp_is_door(tp)) {
        world->set_door(new_at.x, new_at.y);
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
        t->light = light_new(world, t, MAX_LIGHT_RAYS / 8,
                             (double) tp_is_light_strength(tp),
                             t->mid_at, LIGHT_QUALITY_LOW, c);
    }

    if (tp_is_monst(tp)) {
        t->dmap_scent = new Dmap();
    } else {
        t->dmap_scent = nullptr;
    }

    if (tp_is_monst(tp)) {
        t->dmap_goals = new Dmap();
    } else {
        t->dmap_goals = nullptr;
    }

    if (tp_is_monst(tp)) {
        t->age_map = new AgeMap();
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
{
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
    Thingp owner = 0;

    if (id_owner) {
        owner = owner_get();
    }

    if (id_owner && owner) {
#ifdef ENABLE_THING_DEBUG
        log("detach %d from owner %s", id, owner->to_string().c_str());
#endif
        if (id == owner->id_weapon_carry_anim) {
            unwield("remove hooks");

#ifdef ENABLE_THING_DEBUG
            log("detach from carry anim owner %s", owner->to_string().c_str());
#endif

            owner->weapon_set_carry_anim(nullptr);
        }

        if (id == owner->id_weapon_use_anim) {
#ifdef ENABLE_THING_DEBUG
            log("detach from use anim owner %s", owner->to_string().c_str());
#endif
            owner->weapon_set_use_anim(nullptr);

            //
            // End of the use animation, make the sword visible again.
            //
            auto carrying = owner->weapon_get_carry_anim();
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
    if (id_weapon_carry_anim) {
        auto item = weapon_get_carry_anim();
        weapon_set_carry_anim(nullptr);
        verify(item);
        item->set_owner(nullptr);
        item->dead("weapon carry anim owner killed");
    }

    if (id_weapon_use_anim) {
        auto item = weapon_get_use_anim();
        weapon_set_use_anim(nullptr);
        verify(item);
        item->set_owner(nullptr);
        item->dead("weapon use anim owner killed");
    }

    //
    // Some things have lots of things they own
    //
    if (owned_count) {
        log("remove remaining %u owned things", owned_count);

        for (auto i : world->all_active_things) {
            Thingp t = i.second;
            auto o = t->owner_get();
            if (o && (o == t)) {
                t->set_owner(nullptr);
            }
        }
    }
}

Thingp Thing::owner_get (void)
{
    if (id_owner) {
        return (thing_find(world, id_owner));
    } else {
        return (nullptr);
    }
}

void Thing::set_owner (Thingp owner)
{
    if (owner) {
        verify(owner);
    }

    auto old_owner = owner_get();
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
        id_owner = owner->id;

        owner->owned_count++;
    } else {
        id_owner = 0;

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
        auto a = &world->all_things;
        auto iter = a->find(id);
        if (iter != a->end()) {
            if (is_active()) {
                log("erasing from all things");
            }
            world->all_things.erase(iter);
        } else {
            //
            // May have been removed already in cleanup. Ignore.
            //
        }
    }

    {
        auto a = &world->all_active_things;
        auto iter = a->find(id);
        if (iter != a->end()) {
            if (is_active()) {
                log("erasing from active things");
            }
            world->all_active_things.erase(iter);
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
        world->unset_wall(old_at.x, old_at.y);
    }
    if (is_wall() || is_rock()) {
        world->unset_solid(old_at.x, old_at.y);
    }
    if (is_floor()) {
        world->unset_floor(old_at.x, old_at.y);
    }
    if (is_lava()) {
        world->unset_lava(old_at.x, old_at.y);
    }
    if (is_blood()) {
        world->unset_blood(old_at.x, old_at.y);
    }
    if (is_water()) {
        world->unset_water(old_at.x, old_at.y);
    }
    if (is_deep_water()) {
        world->unset_deep_water(old_at.x, old_at.y);
    }
    if (is_corridor()) {
        world->unset_corridor(old_at.x, old_at.y);
    }
    if (is_dirt()) {
        world->undir_sett(old_at.x, old_at.y);
    }
    if (is_grass()) {
        world->unset_grass(old_at.x, old_at.y);
    }
    if (is_soil()) {
        world->unset_soil(old_at.x, old_at.y);
    }
    if (is_gravel()) {
        world->unset_gravel(old_at.x, old_at.y);
    }
    if (is_snow()) {
        world->unset_snow(old_at.x, old_at.y);
    }
    if (is_monst()) {
        world->unset_monst(old_at.x, old_at.y);
    }
    if (is_food()) {
        world->unset_food(old_at.x, old_at.y);
    }
    if (is_rock()) {
        world->unset_rock(old_at.x, old_at.y);
    }
    if (is_key()) {
        world->unset_key(old_at.x, old_at.y);
    }
    if (tp_gfx_large_shadow_caster(tp)) {
        world->unset_gfx_large_shadow_caster(old_at.x, old_at.y);
    }
    if (is_door()) {
        world->unset_door(old_at.x, old_at.y);
    }
    if (is_player()) {
        world->player = nullptr;
    }

    if (dmap_scent) {
        delete(dmap_scent);
        dmap_scent = nullptr;
    }

    if (dmap_goals) {
        delete(dmap_goals);
        dmap_goals = nullptr;
    }

    if (age_map) {
        delete(age_map);
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
    if (id_weapon_carry_anim) {
        auto w = thing_find(world, id_weapon_carry_anim);
        if (!w) {
            die("id_weapon_carry_anim set to %d but not found",
                id_weapon_carry_anim);
        }
        w->move_to(mid_at);
        w->dir = dir;
    }

    if (id_weapon_use_anim) {
        auto w = thing_find(world, id_weapon_use_anim);
        if (!w) {
            die("id_weapon_use_anim set to %d but not found",
                id_weapon_use_anim);
        }
        w->move_to(mid_at);
        w->dir = dir;
    }

    //
    // If something moves on the water, make a ripple
    //
    if (is_monst() || is_player()) {
        if (world->is_water((int)mid_at.x, (int)mid_at.y)) {
            fpoint at(mid_at.x - 0.5, mid_at.y - 0.5);
            if (random_range(0, 1000) > 500) {
                thing_new(world, tp_name(tp_random_ripple()), at);
            }
        }
    }
}

//
// Find an existing thing.
//
Thingp thing_find (Worldp world, uint32_t id)
{_
    auto result = world->all_things.find(id);
    if (result == world->all_things.end()) {
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

    hooks_remove();
    things_to_delete.push_back(id);
}
