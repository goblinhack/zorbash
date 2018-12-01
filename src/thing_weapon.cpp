/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
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
            log("set-weapon-carry remove, %s",
                old_weapon_carry_anim->logname().c_str());
        }
    } else {
        if (new_weapon_carry_anim) {
            log("set-weapon-carry, %s",
                new_weapon_carry_anim->logname().c_str());
        }
    }

    if (new_weapon_carry_anim) {
        weapon_carry_anim_thing_id = new_weapon_carry_anim->id;
    } else {
        weapon_carry_anim_thing_id = 0;
    }
}

void Thing::set_weapon_use_anim_id (uint32_t weapon_use_anim_id)
{
    Thingp weapon_use_anim;

    if (!weapon_use_anim_id) {
        set_weapon_use_anim(nullptr);
        return;
    }

    weapon_use_anim = thing_find(weapon_use_anim_id);

    set_weapon_use_anim(weapon_use_anim);
}

void Thing::set_weapon_use_anim (Thingp weapon_use_anim)
{
    if (weapon_use_anim) {
        verify(weapon_use_anim);
    }

    auto old_weapon_use_anim = get_weapon_use_anim();

    if (old_weapon_use_anim) {
        if (old_weapon_use_anim == weapon_use_anim) {
            return;
        }

        if (weapon_use_anim) {
            log("set-weapon-use change %s->%s",
                old_weapon_use_anim->logname().c_str(),
                weapon_use_anim->logname().c_str());
        } else {
            log("set-weapon-use remove %s", 
                old_weapon_use_anim->logname().c_str());
        }
    } else {
        if (weapon_use_anim) {
            log("set-weapon-use %s", weapon_use_anim->logname().c_str());
        }
    }

    if (weapon_use_anim) {
        weapon_use_anim_thing_id = weapon_use_anim->id;
    } else {
        weapon_use_anim_thing_id = 0;
    }
}

void Thing::get_weapon_use_offset (double *dx, double *dy)
{
    auto weapon = get_weapon();
    if (!weapon) {
        return;
    }

    *dx = 0;
    *dy = 0;

    double dist_from_wielder = 
        ((double)tp_weapon_use_distance(weapon)) / 10.0;

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

Thingp Thing::get_weapon_use_anim (void)
{
    /*
     * If this weapon_use_anim has its own thing id for animations then 
     * destroy that.
     */
    Thingp weapon_use_anim = 0;

    if (weapon_use_anim_thing_id) {
        weapon_use_anim = thing_find(weapon_use_anim_thing_id);
    }

    return (weapon_use_anim);
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
        weapon_carry_anim->dead("owner weapon");
        set_weapon_carry_anim(nullptr);
    }

    auto weapon_use_anim = get_weapon_use_anim();
    if (weapon_use_anim) {
        weapon_use_anim->dead("owner weapon");
        set_weapon_use_anim(nullptr);
    }
}

void Thing::wield (Tpp weapon)
{
    if (get_weapon() == weapon) {
        log("already wiedling: %s", tp_short_name(weapon).c_str());
        return;
    }

    log("is wielding: %s", tp_short_name(weapon).c_str());

    unwield("wield new weapon");

    auto carry_as = tp_weapon_carry_anim(weapon);
    if (carry_as == "") {
        err("could not wield weapon %s", tp_short_name(weapon).c_str());
        return;
    }

    auto carry_anim = thing_new(carry_as, at);

    /*
     * Set the weapon so we can use it later
     */
    weapon_tp_id = weapon->id;

    /*
     * Save the thing id so the client wid can keep track of the weapon.
     */
    set_weapon_carry_anim(carry_anim);

    /*
     * Attach to the thing.
     */
    carry_anim->set_owner(this);

    update();
}

void Thing::use (void)
{
    if (weapon_use_anim_thing_id) {
        /*
         * Still using.
         */
        return;
    }

    auto weapon = get_weapon();
    if (!weapon) {
        err("no weapon to use");
        return;
    }

    auto swung_as = tp_weapon_use_anim(weapon);
    if (swung_as == "") {
        err("could not use %s, has no use anim", 
            tp_short_name(weapon).c_str());
        return;
    }

    auto what = tp_find(swung_as);
    if (!what) {
        err("could not find %s to wield", swung_as.c_str());
        return;
    }

    /*
     * Save the thing id so the client wid can keep track of the weapon.
     */
    auto use_anim = thing_new(swung_as, at);

    /*
     * Attach to the parent thing.
     */
    use_anim->set_owner(this);

    set_weapon_use_anim(use_anim);

    /*
     * Hide the carry anim while using.
     */
    auto c = get_weapon_carry_anim();
    if (c) {
        c->hide();
    }

    update();
}
