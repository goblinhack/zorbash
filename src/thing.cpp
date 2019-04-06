//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
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

Thingp thing_new (std::string tp_name, fpoint at, fpoint jitter)
{_
    auto id = ++next_thing_id;

    auto t = new Thing(); // std::make_shared< class Thing >();
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

    point new_at((int)at.x, (int)at.y);
    if ((new_at.x >= MAP_WIDTH) || (new_at.y >= MAP_HEIGHT)) {
        DIE("new thing is oob at %d, %d", new_at.x, new_at.y);
    }

    t->at             = at;
    t->last_at        = at;
    t->depth          = tp_z_depth(tp);

    if (tp_gfx_can_hflip(tp)) {
        t->dir            = THING_DIR_RIGHT;
    } else {
        t->dir            = THING_DIR_NONE;
    }

    t->is_hungry          = false;
    t->is_starving        = false;
    t->is_dead            = false;
    t->is_bloodied        = false;
    t->is_player          = false;
    t->is_hidden          = false;
    t->is_sleeping        = false;
    t->is_moving          = false;
    t->has_ever_moved     = false;
    t->is_open            = false;
    t->is_bouncing        = false;
    t->is_attached        = false;
    t->is_lit             = false;
    t->is_waiting_for_ai  = tp_is_active(tp);

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
                game.state.player->at.x,
                game.state.player->at.y,
                t->at.x,
                t->at.y);
        }
        game.state.player = t;

        color col = WHITE;
        //
        // keep the light strength half the tiles drawn or we get artifacts
        // at the edges of the fbo
        // 
        col.a = 100;
        t->light = light_new(MAX_LIGHT_RAYS, (TILE_WIDTH / 2) + 4, at, 
                             LIGHT_QUALITY_HIGH, col);

        t->log("player created");
    }

    if (tp_is_wall(tp)) {
        game.state.map.is_wall[new_at.x][new_at.y] = true;
    }
    if (tp_is_rock(tp)) {
        game.state.map.is_rock[new_at.x][new_at.y] = true;
    }
    if (tp_is_wall(tp) || tp_is_rock(tp)) {
        game.state.map.is_solid[new_at.x][new_at.y] = true;
    }
    if (tp_is_floor(tp)) {
        game.state.map.is_floor[new_at.x][new_at.y] = true;
    }
    if (tp_is_lava(tp)) {
        game.state.map.is_lava[new_at.x][new_at.y] = true;
    }
    if (tp_is_blood(tp)) {
        game.state.map.is_blood[new_at.x][new_at.y] = true;
    }
    if (tp_is_water(tp)) {
        game.state.map.is_water[new_at.x][new_at.y] = true;
    }
    if (tp_is_deep_water(tp)) {
        game.state.map.is_deep_water[new_at.x][new_at.y] = true;
        game.state.map.is_water[new_at.x][new_at.y] = true;
    }
    if (tp_is_corridor(tp)) {
        game.state.map.is_corridor[new_at.x][new_at.y] = true;
    }
    if (tp_is_dirt(tp)) {
        game.state.map.is_dirt[new_at.x][new_at.y] = true;
    }
    if (tp_is_monst(tp)) {
        game.state.map.is_monst[new_at.x][new_at.y] = true;
    }
    if (tp_is_key(tp)) {
        game.state.map.is_key[new_at.x][new_at.y] = true;
    }
    if (tp_gfx_large_shadow_caster(tp)) {
        game.state.map.gfx_large_shadow_caster[new_at.x][new_at.y] = true;
    }
    if (tp_is_door(tp)) {
        game.state.map.is_door[new_at.x][new_at.y] = true;
    }

    if (tp_is_player(tp)) {
        t->is_player = true;
    }

    if (!tp_is_active(tp)) {
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

        t->move_to(fpoint(t->at.x + dx, t->at.y + dy));
    }

    t->update_coordinates();
    t->attach();

    if (tp_is_light_strength(tp)) {
        std::string l = tp_str_light_color(tp);
        color c = string2color(l);
        t->light = light_new((double) tp_is_light_strength(tp), 
                          t->at, LIGHT_QUALITY_POINT, c);
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
        log("Remove remaining %u owned things", owned_count);

        for (auto i : game.state.map.all_things) {
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
#ifdef ENABLE_THING_DEBUG
    log("destroy");
#else
    if (!tp_is_active(tp)) {
        log("destroy");
    }
#endif

    detach();

    {
        auto a = &game.state.map.all_things;
        auto iter = a->find(id);
        if (iter != a->end()) {
            if (!tp_is_active(tp)) {
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
            if (!tp_is_active(tp)) {
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
    point old_at((int)at.x, (int)at.y);

    if (tp_is_wall(tp)) {
        game.state.map.is_wall[old_at.x][old_at.y] = false;
    }
    if (tp_is_rock(tp)) {
        game.state.map.is_rock[old_at.x][old_at.y] = false;
    }
    if (tp_is_wall(tp) || tp_is_rock(tp)) {
        game.state.map.is_solid[old_at.x][old_at.y] = false;
    }
    if (tp_is_floor(tp)) {
        game.state.map.is_floor[old_at.x][old_at.y] = false;
    }
    if (tp_is_lava(tp)) {
        game.state.map.is_lava[old_at.x][old_at.y] = false;
    }
    if (tp_is_blood(tp)) {
        game.state.map.is_blood[old_at.x][old_at.y] = false;
    }
    if (tp_is_water(tp)) {
        game.state.map.is_water[old_at.x][old_at.y] = false;
    }
    if (tp_is_deep_water(tp)) {
        game.state.map.is_deep_water[old_at.x][old_at.y] = false;
    }
    if (tp_is_corridor(tp)) {
        game.state.map.is_corridor[old_at.x][old_at.y] = false;
    }
    if (tp_is_dirt(tp)) {
        game.state.map.is_dirt[old_at.x][old_at.y] = false;
    }
    if (tp_is_monst(tp)) {
        game.state.map.is_monst[old_at.x][old_at.y] = false;
    }
    if (tp_is_key(tp)) {
        game.state.map.is_key[old_at.x][old_at.y] = false;
    }
    if (tp_gfx_large_shadow_caster(tp)) {
        game.state.map.gfx_large_shadow_caster[old_at.x][old_at.y] = false;
    }
    if (tp_is_door(tp)) {
        game.state.map.is_door[old_at.x][old_at.y] = false;
    }
    if (tp_is_player(tp)) {
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
        light->move_to(interpolated_at);
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
        w->move_to(at);
        w->dir = dir;
    }

    if (weapon_use_anim_thing_id) {
        auto w = thing_find(weapon_use_anim_thing_id);
        if (!w) {
            die("weapon_use_anim_thing_id set to %d but not found",
                weapon_use_anim_thing_id);
        }
        w->move_to(at);
        w->dir = dir;
    }

    //
    // Not really an item...
    //
    if (tp_is_monst(tp) || tp_is_player(tp)) {
        if (game.state.map.is_water[(int)at.x][(int)at.y]) {
            thing_new(tp_name(tp_random_ripple()), at);
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
    //
    // Return constant strings from a small pool.
    //
    static char tmp[10][MAXSTR];
    static int loop;

    if (loop >= 10) {
        loop = 0;
    }

    snprintf(tmp[loop], sizeof(tmp[loop]) - 1, "%u(%s) at (%g,%g)",
             id, tp->short_name.c_str(), at.x, at.y);

    return (tmp[loop++]);
}

void Thing::kill (void)
{_
    if (is_dead) {
        return;
    }
    is_dead = true;

    if (tp_is_corpse_on_death(tp)) {
        return;
    }

    remove_hooks();
    things_to_delete.push_back(id);
}

void Thing::set_dir_none (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_NONE) {
        dir = THING_DIR_NONE;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_none (void)
{_
    return (dir == THING_DIR_NONE);
}

void Thing::set_dir_down (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_DOWN) {
        dir = THING_DIR_DOWN;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_down (void)
{_
    return (dir == THING_DIR_DOWN);
}

void Thing::set_dir_up (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_UP) {
        dir = THING_DIR_UP;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_up (void)
{_
    return (dir == THING_DIR_UP);
}

void Thing::set_dir_left (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_LEFT) {
        if (dir == THING_DIR_RIGHT) {
            if (tp_gfx_can_hflip(tp)) {
                flip_start_ms = time_get_time_ms_cached();
            }
        }
        dir = THING_DIR_LEFT;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_left (void)
{_
    return (dir == THING_DIR_LEFT);
}

void Thing::set_dir_right (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_RIGHT) {
        if (dir == THING_DIR_LEFT) {
            if (tp_gfx_can_hflip(tp)) {
                flip_start_ms = time_get_time_ms_cached();
            }
        }
        dir = THING_DIR_RIGHT;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_right (void)
{_
    return (dir == THING_DIR_RIGHT);
}

void Thing::set_dir_tl (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_TL) {
        dir = THING_DIR_TL;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_tl (void)
{_
    return (dir == THING_DIR_TL);
}

void Thing::set_dir_bl (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_BL) {
        dir = THING_DIR_BL;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_bl (void)
{_
    return (dir == THING_DIR_BL);
}

void Thing::set_dir_tr (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_TR) {
        dir = THING_DIR_TR;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_tr (void)
{_
    return (dir == THING_DIR_TR);
}

void Thing::set_dir_br (void)
{_
    if (tp_gfx_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_BR) {
        dir = THING_DIR_BR;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_br (void)
{_
    return (dir == THING_DIR_BR);
}
