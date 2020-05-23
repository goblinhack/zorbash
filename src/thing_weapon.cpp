//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_thing.h"

Thingp Thing::weapon_get () const
{_
    auto id = get_weapon_id();
    if (id) {
        return (thing_find(id));
    }

    return (nullptr);
}

void Thing::weapon_set_carry_anim_id (uint32_t weapon_carry_anim_id)
{_
    Thingp weapon_carry_anim;

    if (!weapon_carry_anim_id) {
        weapon_set_carry_anim(nullptr);
        return;
    }

    weapon_carry_anim = thing_find(weapon_carry_anim_id);

    weapon_set_carry_anim(weapon_carry_anim);
}

void Thing::weapon_set_carry_anim (Thingp new_weapon_carry_anim)
{_
    if (new_weapon_carry_anim) {
        verify(new_weapon_carry_anim);
    }

    auto old_weapon_carry_anim = weapon_get_carry_anim();
    if (old_weapon_carry_anim) {
        if (old_weapon_carry_anim == new_weapon_carry_anim) {
            return;
        }

        if (new_weapon_carry_anim) {
            log("change weapon carry_anim, %s->%s",
                old_weapon_carry_anim->to_string().c_str(),
                new_weapon_carry_anim->to_string().c_str());
        } else {
            log("remove weapon carry_anim, %s",
                old_weapon_carry_anim->to_string().c_str());
        }
    } else {
        if (new_weapon_carry_anim) {
            log("set weapon carry_anim, %s",
                new_weapon_carry_anim->to_string().c_str());
        }
    }

    if (new_weapon_carry_anim) {
        set_weapon_id_carry_anim(new_weapon_carry_anim->id);
    } else {
        set_weapon_id_carry_anim(0);
    }
}

void Thing::weapon_set_use_anim_id (uint32_t weapon_use_anim_id)
{_
    Thingp weapon_use_anim;

    if (!weapon_use_anim_id) {
        weapon_set_use_anim(nullptr);
        return;
    }

    weapon_use_anim = thing_find(weapon_use_anim_id);

    weapon_set_use_anim(weapon_use_anim);
}

void Thing::weapon_set_use_anim (Thingp weapon_use_anim)
{_
    if (weapon_use_anim) {
        verify(weapon_use_anim);
    }

    auto old_weapon_use_anim = weapon_get_use_anim();

    if (old_weapon_use_anim) {
        if (old_weapon_use_anim == weapon_use_anim) {
            return;
        }

        if (weapon_use_anim) {
            log("change weapon use-anim %s->%s",
                old_weapon_use_anim->to_string().c_str(),
                weapon_use_anim->to_string().c_str());
        } else {
            log("remove weapon use-anim %s",
                old_weapon_use_anim->to_string().c_str());
        }
    } else {
        if (weapon_use_anim) {
            log("set weapon use-anim %s",
                weapon_use_anim->to_string().c_str());
        }
    }

    if (weapon_use_anim) {
        set_weapon_id_use_anim(weapon_use_anim->id);
    } else {
        set_weapon_id_use_anim(0);
    }
}

void Thing::weapon_get_use_offset (float *dx, float *dy) const
{_
    *dx = 0;
    *dy = 0;

    auto weapon = weapon_get();
    if (!weapon) {
        return;
    }

    float dist_from_wielder = weapon->tp()->weapon_use_distance();

    //
    // Try current direction.
    //
    if (is_dir_tl()) {
        *dx = -dist_from_wielder;
        *dy = -dist_from_wielder;
        return;
    }

    //
    // Careful here - change dy too much and you hit through walls
    //

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

Thingp Thing::weapon_get_carry_anim (void)
{_
    Thingp weapon_carry_anim = 0;

    auto id = get_weapon_id_carry_anim();
    if (id) {
        weapon_carry_anim = thing_find(id);
    }

    return (weapon_carry_anim);
}

Thingp Thing::weapon_get_use_anim (void) const
{_
    //
    // If this weapon_use_anim has its own thing id for animations then
    // destroy that.
    //
    Thingp weapon_use_anim = 0;

    auto id = get_weapon_id_use_anim();
    if (id) {
        weapon_use_anim = thing_find(id);
    }

    return (weapon_use_anim);
}

void Thing::unwield (const char *why)
{_
    if (!get_weapon_id()) {
        return;
    }

    log("unwielding %08X, why: %s", get_weapon_id(), why);

    auto weapon = weapon_get();
    if (!weapon) {
        log("could not unwield %08X, why: %s", get_weapon_id(), why);
        return;
    }

    log("unwielding current weapon %s, why: %s",
        weapon->tp()->name().c_str(), why);

    sheath();
}

void Thing::sheath (void)
{_
    auto weapon = weapon_get();
    if (!weapon) {
        return;
    }

    log("sheathing %s", weapon->tp()->name().c_str());

    //
    // If this weapon has its own thing id for animations then destroy that.
    //
    auto weapon_carry_anim = weapon_get_carry_anim();
    if (weapon_carry_anim) {
        weapon_carry_anim->dead("owner sheathed weapon, remove carry_anim");
        weapon_set_carry_anim(nullptr);
    }

    auto weapon_use_anim = weapon_get_use_anim();
    if (weapon_use_anim) {
        weapon_use_anim->dead("owner sheathed weapon, remove use-anim");
        weapon_set_use_anim(nullptr);
    }
}

void Thing::wield (Thingp weapon)
{_
    auto weapon_tp = weapon->tp();

    if (weapon_get() == weapon) {
        log("re-wielding: %s", weapon_tp->name().c_str());
    } else {
        log("is wielding: %s", weapon_tp->name().c_str());

        unwield("wield new weapon");
    }

    auto carry_anim_as = weapon_tp->weapon_carry_anim();
    if (carry_anim_as == "") {
        err("could not wield weapon %s", weapon_tp->name().c_str());
        return;
    }

    auto carry_anim = thing_new(carry_anim_as, this);

    //
    // Set the weapon so we can use it later
    //
    set_weapon_id(weapon->id);

    //
    // Save the thing id so the client wid can keep track of the weapon.
    //
    weapon_set_carry_anim(carry_anim);

    //
    // Attach to the thing.
    //
    carry_anim->set_owner(this);

    // Needed?
    // move_carried_items();
}

void Thing::use (void)
{_
    if (get_weapon_id_use_anim()) {
        //
        // Still using.
        //
        return;
    }

    auto weapon = weapon_get();
    if (!weapon) {
        err("no weapon to use");
        return;
    }

    auto weapon_tp = weapon->tp();

    auto swung_as = weapon_tp->weapon_use_anim();
    if (swung_as == "") {
        die("could not use %s/%08X has no 'use' animation frame",
            weapon_tp->name().c_str(), weapon->id);
        return;
    }

    auto what = tp_find(swung_as);
    if (!what) {
        err("could not find %s to wield", swung_as.c_str());
        return;
    }

    //
    // Save the thing id so the client wid can keep track of the weapon.
    //
    auto use_anim = thing_new(swung_as, this);

    //
    // Attach to the parent thing.
    //
    use_anim->set_owner(this);

    weapon_set_use_anim(use_anim);

    //
    // Hide the carry_anim while using.
    //
    auto c = weapon_get_carry_anim();
    if (c) {
        c->hide();
    }

    move_carried_items();

    float dx, dy;
    weapon_get_use_offset(&dx, &dy);

    bool target_attacked = false;
    bool target_overlaps = false;
    auto hit_at = mid_at + fpoint(dx, dy);

    log("attack @%f,%f",hit_at.x, hit_at.y);
    lunge(hit_at);
    if (collision_check_and_handle_at(hit_at,
                                      &target_attacked,
                                      &target_overlaps)) {
        return;
    }
}
