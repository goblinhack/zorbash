//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"

Thingp Thing::weapon_get () const
{_
    auto id = get_weapon_id();
    if (id.ok()) {
        return (level->thing_find(id));
    }

    return (nullptr);
}

void Thing::weapon_set_carry_anim_id (ThingId weapon_carry_anim_id)
{_
    Thingp weapon_carry_anim;

    if (!weapon_carry_anim_id) {
        weapon_set_carry_anim(nullptr);
        return;
    }

    weapon_carry_anim = level->thing_find(weapon_carry_anim_id);
    if (!weapon_carry_anim) {
        return;
    }

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
            new_weapon_carry_anim->set_owner(this);
        } else {
            log("remove weapon carry_anim, %s",
                old_weapon_carry_anim->to_string().c_str());
        }
        old_weapon_carry_anim->remove_owner();
    } else {
        if (new_weapon_carry_anim) {
            log("set weapon carry_anim, %s",
                new_weapon_carry_anim->to_string().c_str());
            new_weapon_carry_anim->set_owner(this);
        }
    }

    if (new_weapon_carry_anim) {
        set_weapon_id_carry_anim(new_weapon_carry_anim->id);
    } else {
        set_weapon_id_carry_anim(0);
    }
}

void Thing::weapon_set_use_anim_id (ThingId gfx_anim_attack_id)
{_
    Thingp gfx_anim_attack;

    if (!gfx_anim_attack_id) {
        weapon_set_use_anim(nullptr);
        return;
    }

    gfx_anim_attack = level->thing_find(gfx_anim_attack_id);
    if (!gfx_anim_attack) {
        return;
    }

    weapon_set_use_anim(gfx_anim_attack);
}

void Thing::weapon_set_use_anim (Thingp new_gfx_anim_attack)
{_
    if (new_gfx_anim_attack) {
        verify(new_gfx_anim_attack);
    }

    auto old_gfx_anim_attack = weapon_get_use_anim();

    if (old_gfx_anim_attack) {
        if (old_gfx_anim_attack == new_gfx_anim_attack) {
            return;
        }

        if (new_gfx_anim_attack) {
            log("change weapon use-anim %s->%s",
                old_gfx_anim_attack->to_string().c_str(),
                new_gfx_anim_attack->to_string().c_str());
            new_gfx_anim_attack->set_owner(this);
        } else {
            log("remove weapon use-anim %s",
                old_gfx_anim_attack->to_string().c_str());
        }
        old_gfx_anim_attack->remove_owner();
    } else {
        if (new_gfx_anim_attack) {
            log("set weapon use-anim %s",
                new_gfx_anim_attack->to_string().c_str());
            new_gfx_anim_attack->set_owner(this);
        }
    }

    if (new_gfx_anim_attack) {
        set_weapon_id_use_anim(new_gfx_anim_attack->id);
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
    if (id.ok()) {
        weapon_carry_anim = level->thing_find(id);
    }

    return (weapon_carry_anim);
}

Thingp Thing::weapon_get_use_anim (void) const
{_
    //
    // If this gfx_anim_attack has its own thing id for animations then
    // destroy that.
    //
    Thingp gfx_anim_attack = 0;

    auto id = get_weapon_id_use_anim();
    if (id.ok()) {
        gfx_anim_attack = level->thing_find(id);
    }

    return (gfx_anim_attack);
}

void Thing::unwield (const char *why)
{_
    if (!get_weapon_id()) {
        return;
    }

    log("unwielding %" PRIx32 ", why: %s", get_weapon_id().id, why);

    auto weapon = weapon_get();
    if (!weapon) {
        log("could not unwield %" PRIx32 ", why: %s", get_weapon_id().id, why);
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
_
    //
    // If this weapon has its own thing id for animations then destroy that.
    //
    auto weapon_carry_anim = weapon_get_carry_anim();
    if (weapon_carry_anim) {
        log("remove carry anim");
        weapon_carry_anim->dead("owner sheathed weapon, remove carry_anim");
        weapon_set_carry_anim(nullptr);
    } else {
        log("weapon had no carry anim");
    }

    auto gfx_anim_attack = weapon_get_use_anim();
    if (gfx_anim_attack) {
        log("remove carry anim");
        gfx_anim_attack->dead("owner sheathed weapon, remove use-anim");
        weapon_set_use_anim(nullptr);
    } else {
        log("weapon had no use/attack anim");
    }
}

void Thing::wield (Thingp weapon)
{_
    auto weapon_tp = weapon->tp();

    if (weapon_get() == weapon) {
        log("re-wielding: %s", weapon_tp->name().c_str());
        return;
    } else {
        log("is wielding: %s", weapon_tp->name().c_str());
        unwield("wield new weapon");
    }

    auto carry_anim_as = weapon_tp->weapon_carry_anim();
    if (carry_anim_as == "") {
        err("could not wield weapon %s", weapon_tp->name().c_str());
        return;
    }

    auto carry_anim = level->thing_new(carry_anim_as, this);

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

void Thing::use_weapon (void)
{_
    log("use something");
_
    if (get_weapon_id_use_anim().ok()) {
        //
        // Still using.
        //
        return;
    }

    if (is_stamina_check()) {
        if (!get_stats_stamina()) {
            if (is_player()) {
                MINICON("You are too tired to attack. You need to rest.");
            }
            return;
        }
    }

    std::string swung_as;

    auto weapon = weapon_get();
    if (!weapon) {
        if (is_player()) {
            MINICON("You attack with bare fists!");
        }
        swung_as = gfx_anim_attack();
    } else {
        auto weapon_tp = weapon->tp();

        swung_as = weapon_tp->gfx_anim_attack();
        if (swung_as == "") {
            die("could not use %s/%" PRIx32 " has no 'use' animation frame",
                weapon_tp->name().c_str(), weapon->id.id);
            return;
        }

        auto what = tp_find(swung_as);
        if (!what) {
            err("could not find %s to wield", swung_as.c_str());
            return;
        }
    }

    //
    // Save the thing id so the client wid can keep track of the weapon.
    //
    auto use_anim = level->thing_new(swung_as, this);

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
    if (!weapon) {
        auto d = dir_to_direction();
        dx = d.x;
        dy = d.y;
    } else {
        weapon_get_use_offset(&dx, &dy);
    }

    bool target_attacked = false;
    bool target_overlaps = false;
    auto hit_at = mid_at + fpoint(dx, dy);

    log("attack at %f,%f delta %f,%f",hit_at.x, hit_at.y, dx, dy);
_
    //
    // Lunge at the target
    //
    lunge(hit_at);

    decr_stats_stamina();

    if (weapon) {
        if (weapon->collision_check_and_handle_at(hit_at,
                                                  &target_attacked,
                                                  &target_overlaps)) {
            return;
        }
    } else {
        if (collision_check_and_handle_at(hit_at,
                                          &target_attacked,
                                          &target_overlaps)) {
            return;
        }
    }
}
