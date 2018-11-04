/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_game.h"
#include "my_thing.h"
#include "my_tile_info.h"

static uint32_t thing_id;

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

    /*
     * No need to call remove as we did the safe destroy above.
     */
    things_to_delete.clear();
}

Thingp thing_new (std::string tp_name, fpoint at)
{_
    auto id = ++thing_id;

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

    point new_at((int)at.x, (int)at.y);
    if ((new_at.x >= MAP_WIDTH) || (new_at.y >= MAP_HEIGHT)) {
        DIE("new thing is oob at %d, %d", new_at.x, new_at.y);
    }
    auto depth = t->depth = tp_z_depth(tp);
    auto n = &game.state.map.things[new_at.x][new_at.y][depth];
    result = n->insert(p);
    if (result.second == false) {
        DIE("thing insert into map [%d] failed", id);
    }

    t->at             = at;

    if (tp_is_animated_walk_flip(tp)) {
        t->dir            = THING_DIR_RIGHT;
    } else {
        t->dir            = THING_DIR_NONE;
    }

    t->is_dead        = false;
    t->is_bloodied    = false;
    t->is_player      = false;
    t->is_hidden      = false;
    t->is_sleeping    = false;
    t->is_moving      = false;
    t->has_ever_moved = false;
    t->is_open        = false;

    t->timestamp_born = time_get_time_ms();

    auto tiles = tp_get_left_tiles(tp);
    auto tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->left_tile = tinfo->tile;
    }

    tiles = tp_get_right_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->right_tile = tinfo->tile;
    }

    tiles = tp_get_top_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->top_tile = tinfo->tile;
    }

    tiles = tp_get_bot_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->bot_tile = tinfo->tile;
    }

    tiles = tp_get_tl_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->tl_tile = tinfo->tile;
    }

    tiles = tp_get_tr_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->tr_tile = tinfo->tile;
    }

    tiles = tp_get_br_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->br_tile = tinfo->tile;
    }

    tiles = tp_get_bl_tiles(tp);
    tinfo = tile_info_random(tiles);
    if (tinfo) {
        t->bl_tile = tinfo->tile;
    }

    tiles = tp_get_tiles(tp);
    if (tp->is_animated) {
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
        col.a = 50;
        t->light = light_new(MAX_LIGHT_RAYS, 8, at, LIGHT_QUALITY_HIGH, col);

        t->log("player created");
    }

    if (tp_is_wall(tp)) {
        game.state.map.is_wall[new_at.x][new_at.y] = true;
    }

    if (tp_is_player(tp)) {
        t->is_player = true;
    }

    //log("created");
    return (t);
}

void Thing::hide (void)
{_
    is_hidden = true;

    /*
     * Hide the weapon too or it just floats in the air.
     */
    auto weapon_carry_anim = get_weapon_carry_anim();
    if (weapon_carry_anim) {
        weapon_carry_anim->hide();
    }
}

void Thing::visible (void)
{_
    is_hidden = false;

    /*
     * If this thing has an owner, should the thing stay hidden?
     */
    auto owner = get_owner();
    if (owner) {
        if (this == owner->get_weapon_carry_anim()) {
            if (owner->get_weapon_use_anim()) {
                /*
                 * Stay hidden until the weapon use is done.
                 */
                return;
            }
        }
    }

    /*
     * Reveal the weapon again too.
     */
    auto weapon_carry_anim = get_weapon_carry_anim();
    if (weapon_carry_anim) {
        weapon_carry_anim->visible();
    }
}

uint8_t Thing::is_visible (void)
{
    return (!is_hidden);
}

/*
 * Get rid of all the hooks to other things that this thing has. e.g. the
 * weapons it carries etc.
 */
void Thing::remove_hooks ()
{_
    /*
     * We are owned by something. i.e. we are a sword.
     */
    Thingp owner = 0;

    if (owner_thing_id) {
        owner = get_owner();
    }
_
    if (owner_thing_id && owner) {
#ifdef THING_DEBUG
        log("detach from owner %s", owner->logname().c_str());
#endif
        if (thing_id == owner->weapon_carry_anim_thing_id) {
            unwield("remove hooks");

#ifdef THING_DEBUG
            log("detach from carry anim owner %s", owner->logname().c_str());
#endif

            owner->set_weapon_carry_anim(nullptr);
        }
_
        if (thing_id == owner->weapon_use_anim_thing_id) {
#ifdef THING_DEBUG
            log("detach from use anim owner %s", owner->logname().c_str());
#endif

            owner->set_weapon_use_anim(nullptr);

            /*
             * End of the use animation, make the sword visible again.
             */
            auto carrying = owner->get_weapon_carry_anim();
            if (carrying) {
                /*
                 * But only if the owner is visible. They may have reached the
                 * level.
                 */
                if (owner->is_visible()) {
                    carrying->visible();
                }
            }
        }

        set_owner(nullptr);
    }
_
    /*
     * We own things like a sword. i.e. we are a player.
     */
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

    /*
     * Some things have lots of things they own
     */
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
            log("set-owner change %s->%s", old_owner->logname().c_str(), 
                owner->logname().c_str());
        } else {
            log("set-owner remove owner %s", old_owner->logname().c_str());
        }
    } else {
        if (owner) {
            log("set-owner %s", owner->logname().c_str());
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
    {
        auto a = &game.state.map.all_things;
        auto iter = a->find(id);
        if (iter == a->end()) {
            die("thing not found to destroy from all things");
        }
        a->erase(id);
    }
_
    /*
     * Pop from the map
     */
    point old_at((int)at.x, (int)at.y);
    {
        auto o = &game.state.map.things[old_at.x][old_at.y][depth];
        auto iter = o->find(id);
        if (iter == o->end()) {
            die("thing not found to destroy");
        }
_    
        auto value = (*o)[id];
        o->erase(iter);
_
        if (tp_is_wall(tp)) {
            game.state.map.is_wall[old_at.x][old_at.y] = false;
        }
_
        if (tp_is_player(tp)) {
            if (game.state.player != value) {
                game.state.player = nullptr;
            }
        }
    }
}

void Thing::update (void)
{_
    /*
     * Light source follows the thing.
     */
    if (light) {
        light->move_to(at);
        light->calculate();
    }
_
    /*
     * Weapons follow also.
     */
    if (weapon_carry_anim_thing_id) {
        auto w = thing_find(weapon_carry_anim_thing_id);
        w->move_to(at);
        w->dir = dir;
    }
_
    if (weapon_use_anim_thing_id) {
        auto w = thing_find(weapon_use_anim_thing_id);
        w->move_to(at);
        w->dir = dir;
    }
}

void Thing::move_to (fpoint to)
{_
    last_move_ms = time_get_time_ms_cached();
    end_move_ms = last_move_ms + ONESEC / 10;
    has_ever_moved = true;

    if (!has_ever_moved) {
        last_at = to;
    } else {
        last_at = at;
    }
_
    point old_at((int)at.x, (int)at.y);
    point new_at((int)to.x, (int)to.y);

    /*
     * Keep track of where this thing is on the grid
     */
    if (old_at != new_at) {
        /*
         * Pop
         */
        auto o = &game.state.map.things[old_at.x][old_at.y][depth];
        auto iter = o->find(id);
        if (iter == o->end()) {
            die("not found on map move");
        }

        auto value = (*o)[id];
        o->erase(iter);

        /*
         * Add back
         */
        auto n = &game.state.map.things[new_at.x][new_at.y][depth];
        n->insert(std::make_pair(id, value));

        if (tp_is_wall(tp)) {
            game.state.map.is_wall[old_at.x][old_at.y] = false;
            game.state.map.is_wall[new_at.x][new_at.y] = true;
        }
    }
_
    /*
     * Moves are immediate, but we render the move in steps, hence keep
     * track of when we moved.
     */
    at = to;
    last_move_ms = time_get_time_ms_cached();
    end_move_ms = last_move_ms + ONESEC / 10;

    update();
}

void Thing::move_delta (fpoint delta)
{_
    /*
     * If not moving and this is the first move then break out of the
     * idle animation.
     */
    if (is_dir_none()) {
        next_frame_ms = time_get_time_ms_cached();
    }

    if (delta.x > 0) {
        set_dir_left();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.x < 0) {
        set_dir_right();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.y > 0) {
        set_dir_up();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.y < 0) {
        set_dir_down();
        is_moving = true;
        has_ever_moved = true;
    }

    move_to(at + delta);
}

/*
 * Find an existing thing.
 */
Thingp thing_find (uint32_t id)
{_
    auto result = game.state.map.all_things.find(id);
    if (result == game.state.map.all_things.end()) {
        return (0);
    }

    return (result->second);
}

std::string Thing::logname (void)
{_
    /*
     * Return constant strings from a small pool.
     */
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

    remove_hooks();
    things_to_delete.push_back(id);
}

void Thing::set_dir_none (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_NONE) {
        dir = THING_DIR_NONE;
        update();
    }
}

uint8_t Thing::is_dir_none (void)
{_
    return (dir == THING_DIR_NONE);
}

void Thing::set_dir_down (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_DOWN) {
        dir = THING_DIR_DOWN;
        update();
    }
}

uint8_t Thing::is_dir_down (void)
{_
    return (dir == THING_DIR_DOWN);
}

void Thing::set_dir_up (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_UP) {
        dir = THING_DIR_UP;
        update();
    }
}

uint8_t Thing::is_dir_up (void)
{_
    return (dir == THING_DIR_UP);
}

void Thing::set_dir_left (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_LEFT) {
        if (dir == THING_DIR_RIGHT) {
            if (tp_is_animated_walk_flip(tp)) {
                flip_start_ms = time_get_time_ms_cached();
            }
        }
        dir = THING_DIR_LEFT;
        update();
    }
}

uint8_t Thing::is_dir_left (void)
{_
    return (dir == THING_DIR_LEFT);
}

void Thing::set_dir_right (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_RIGHT) {
        if (dir == THING_DIR_LEFT) {
            if (tp_is_animated_walk_flip(tp)) {
                flip_start_ms = time_get_time_ms_cached();
            }
        }
        dir = THING_DIR_RIGHT;
        update();
    }
}

uint8_t Thing::is_dir_right (void)
{_
    return (dir == THING_DIR_RIGHT);
}

void Thing::set_dir_tl (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_TL) {
        dir = THING_DIR_TL;
        update();
    }
}

uint8_t Thing::is_dir_tl (void)
{_
    return (dir == THING_DIR_TL);
}

void Thing::set_dir_bl (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_BL) {
        dir = THING_DIR_BL;
        update();
    }
}

uint8_t Thing::is_dir_bl (void)
{_
    return (dir == THING_DIR_BL);
}

void Thing::set_dir_tr (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_TR) {
        dir = THING_DIR_TR;
        update();
    }
}

uint8_t Thing::is_dir_tr (void)
{_
    return (dir == THING_DIR_TR);
}

void Thing::set_dir_br (void)
{_
    if (tp_is_animated_no_dir(tp)) {
        return;
    }

    if (dir != THING_DIR_BR) {
        dir = THING_DIR_BR;
        update();
    }
}

uint8_t Thing::is_dir_br (void)
{_
    return (dir == THING_DIR_BR);
}

void Thing::to_coords (fpoint *P0, fpoint *P1, fpoint *P2, fpoint *P3)
{
    P0->x = tl.x;
    P0->y = tl.y;
    P1->x = br.x;
    P1->y = tl.y;
    P2->x = br.x;
    P2->y = br.y;
    P3->x = tl.x;
    P3->y = br.y;
}
