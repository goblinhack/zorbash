/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_game.h"
#include "my_thing.h"
#include "my_tile_info.h"

Tpp Thing::get_weapon ()
{
    if (weapon_tp_id) {
        return (tp_find(weapon_tp_id));
    }

    return (nullptr);
}

void Thing::set_weapon_carry_anim_id (uint32_t weapon_carry_anim_id)
{
    Thingp weapon_carry_anim;

    if (!weapon_carry_anim_id) {
        set_weapon_carry_anim(nullptr);
        return;
    }

    weapon_carry_anim = thing_find(weapon_carry_anim_id);

    set_weapon_carry_anim(weapon_carry_anim);
}

void Thing::set_weapon_carry_anim (Thingp new_weapon_carry_anim)
{
    if (new_weapon_carry_anim) {
        verify(new_weapon_carry_anim);
    }

    auto old_weapon_carry_anim = get_weapon_carry_anim();
    if (old_weapon_carry_anim) {
        if (old_weapon_carry_anim == new_weapon_carry_anim) {
            return;
        }

        if (new_weapon_carry_anim) {
            log("set-weapon-carry change, %s->%s",
                old_weapon_carry_anim->logname().c_str(),
                new_weapon_carry_anim->logname().c_str());
        } else {
            log("set-weapon-carry remove , %s",
                old_weapon_carry_anim->logname().c_str());
        }
    } else {
        if (new_weapon_carry_anim) {
            log("set-weapon-carry , %s",
                new_weapon_carry_anim->logname().c_str());
        }
    }

    if (new_weapon_carry_anim) {
        weapon_carry_anim_thing_id = new_weapon_carry_anim->id;
    } else {
        weapon_carry_anim_thing_id = 0;
    }
}

void Thing::set_weapon_swing_anim_id (uint32_t weapon_swing_anim_id)
{
    Thingp weapon_swing_anim;

    if (!weapon_swing_anim_id) {
        set_weapon_swing_anim(nullptr);
        return;
    }

    weapon_swing_anim = thing_find(weapon_swing_anim_id);

    set_weapon_swing_anim(weapon_swing_anim);
}

void Thing::set_weapon_swing_anim (Thingp weapon_swing_anim)
{
    if (weapon_swing_anim) {
        verify(weapon_swing_anim);
    }

    auto old_weapon_swing_anim = get_weapon_swing_anim();

    if (old_weapon_swing_anim) {
        if (old_weapon_swing_anim == weapon_swing_anim) {
            return;
        }

        if (weapon_swing_anim) {
            log("set-weapon-swing change %s->%s",
                old_weapon_swing_anim->logname().c_str(),
                weapon_swing_anim->logname().c_str());
        } else {
            log("set-weapon-swing remove %s", 
                old_weapon_swing_anim->logname().c_str());
        }
    } else {
        if (weapon_swing_anim) {
            log("set-weapon-swing %s", weapon_swing_anim->logname().c_str());
        }
    }

    if (weapon_swing_anim) {
        weapon_swing_anim_thing_id = weapon_swing_anim->id;
    } else {
        weapon_swing_anim_thing_id = 0;
    }
}

void Thing::get_weapon_swing_offset (double *dx, double *dy)
{
    auto weapon = get_weapon();
    if (!weapon) {
        return;
    }

    *dx = 0;
    *dy = 0;

    double dist_from_wielder = 
        ((double)tp_weapon_swing_distance(weapon)) / 10.0;

    /*
     * Try current direction.
     */
    if (is_dir_tl()) {
        *dx = -dist_from_wielder;
        *dy = -dist_from_wielder;
        return;
    }

    /*
     * Careful here - change dy too much and you hit through walls
     */

    if (is_dir_tr()) {
        *dx = dist_from_wielder;
        *dy = -dist_from_wielder;
        return;
    }

    if (is_dir_bl()) {
        *dx = -dist_from_wielder;
        *dy = dist_from_wielder;
        return;
    }

    if (is_dir_br()) {
        *dx = dist_from_wielder;
        *dy = dist_from_wielder;
        return;
    }

    if (is_dir_down()) {
        *dy = dist_from_wielder;
        return;
    }

    if (is_dir_up()) {
        *dy = -dist_from_wielder;
        return;
    }

    if (is_dir_right()) {
        *dx = dist_from_wielder;
        return;
    }

    if (is_dir_left()) {
        *dx = -dist_from_wielder;
        return;
    }

    *dy = dist_from_wielder + 0.3;
}

Thingp Thing::get_weapon_carry_anim (void)
{
    Thingp weapon_carry_anim = 0;

    if (weapon_carry_anim_thing_id) {
        weapon_carry_anim = thing_find(weapon_carry_anim_thing_id);
    }

    return (weapon_carry_anim);
}

Thingp Thing::get_weapon_swing_anim (void)
{
    /*
     * If this weapon_swing_anim has its own thing id for animations then 
     * destroy that.
     */
    Thingp weapon_swing_anim = 0;

    if (weapon_swing_anim_thing_id) {
        weapon_swing_anim = thing_find(weapon_swing_anim_thing_id);
    }

    return (weapon_swing_anim);
}

void Thing::wield_next_weapon (void)
{
    if (weapon_tp_id) {
        wield(tp_find(weapon_tp_id));
    }
}

void Thing::unwield (const char *why)
{
    auto weapon = get_weapon();
    if (!weapon) {
        return;
    }

    log("unwielding current weapon %s, why: %s", 
        tp_short_name(weapon).c_str(), why);

    sheath();
}

void Thing::sheath (void)
{
    auto weapon = get_weapon();
    if (!weapon) {
        return;
    }

    log("sheathing %s", tp_short_name(weapon).c_str());

    /*
     * If this weapon has its own thing id for animations then destroy that.
     */
    auto weapon_carry_anim = get_weapon_carry_anim();
    if (weapon_carry_anim) {
        weapon_carry_anim->dead(nullptr, "owner weapon");
        set_weapon_carry_anim(nullptr);
    }

    auto weapon_swing_anim = get_weapon_swing_anim();
    if (weapon_swing_anim) {
        weapon_swing_anim->dead(nullptr, "owner weapon");
        set_weapon_swing_anim(nullptr);
    }
}

void Thing::wield (Tpp weapon)
{
    if (get_weapon() == weapon) {
        log("already wiedling: %s", tp_short_name(weapon).c_str());
        return;
    }

    log("want to wield: %s", tp_short_name(weapon).c_str());

    unwield("wield new weapon");

    auto carry_as = tp_weapon_carry_anim(weapon);
    if (carry_as == "") {
        err("Could not wield weapon %s", tp_short_name(weapon).c_str());
        return;
    }

    auto what = tp_find(carry_as);
    if (!what) {
        err("Could not find %s to wield", carry_as.c_str());
        return;
    }

    weapon_tp_id = tp_to_id(weapon);

#if 0
    /*
     * Save the thing id so the client wid can keep track of the weapon.
     */
    //Thingp child = wid_get_thing(weapon_carry_anim_wid);
    //set_weapon_carry_anim(level, t, child);
    //child->dir = t->dir;

    /*
     * Attach to the thing.
     */
    //set_owner(level, child, t);
#endif
}

void Thing::swing (void)
{
    if (weapon_swing_anim_thing_id) {
        /*
         * Still swinging.
         */
        return;
    }

    auto weapon = get_weapon();
    if (!weapon) {
        err("no weapon to swing");
        return;
    }

    auto swung_as = tp_weapon_swing_anim(weapon);
    if (swung_as == "") {
        err("could not swing %s", tp_short_name(weapon).c_str());
        return;
    }

#if 0
    tpp what = tp_find(swung_as);
    if (!what) {
        err("could not find %s to wield", swung_as.c_str());
        return;
    }

    /*
     * Put the swing anim on the map
     */
    widp weapon_swing_anim_wid;

    weapon_swing_anim_wid = wid_game_map_replace_tile(
                                    level,
                                    t->x,
                                    t->y,
                                    0, /* thing */
                                    what,
                                    0 /* tpp data */);

    /*
     * Save the thing id so the client wid can keep track of the weapon.
     */
    Thingp child = wid_get_thing(weapon_swing_anim_wid);

    /*
     * Attach to the parent thing.
     */
    set_owner(level, child, t);

    child->dir = t->dir;

    set_weapon_swing_anim(level, t, child);

    thing_destroy_in(level, child, 500);

    /*
     * Hide the weapon too or it just floats in the air.
     */
    Thingp weapon_carry_anim = thing_weapon_carry_anim(level, t);
    if (weapon_carry_anim) {
        thing_hide(level, weapon_carry_anim);
    }
#endif
}
