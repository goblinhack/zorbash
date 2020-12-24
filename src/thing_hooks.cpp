//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::hooks_remove ()
{_
    //log("hooks remove");

    //
    // We are owned by something. i.e. we are a sword.
    //
    Thingp owner = nullptr;

    if (get_immediate_owner_id().ok()) {
        owner = get_immediate_owner();
    }

    if (owner) {
        if (is_loggable_for_unimportant_stuff()) {
            log("detach %" PRIx32 " from owner %s", id.id, owner->to_string().c_str());
        }

        if (id == owner->get_on_fire_anim_id()) {
            if (is_loggable_for_unimportant_stuff()) {
                log("detach on_fire_anim_id from owner %s", owner->to_string().c_str());
            }
            owner->set_on_fire_anim_id(0);
        }

        if (id == owner->get_weapon_id()) {
            owner->unwield("remove hooks");

            if (is_loggable_for_unimportant_stuff()) {
                log("detach weapon_id from owner %s", owner->to_string().c_str());
            }
            owner->set_weapon_id(0);
        }

        if (id == owner->get_weapon_id_carry_anim()) {
            owner->unwield("remove hooks");

            if (is_loggable_for_unimportant_stuff()) {
                log("detach carry_anim from owner %s", owner->to_string().c_str());
            }
            owner->weapon_set_carry_anim_id(0);
        }

        if (id == owner->get_weapon_id_use_anim()) {
            owner->unwield("remove hooks");

            if (is_loggable_for_unimportant_stuff()) {
                log("detach use_anim from owner %s", owner->to_string().c_str());
            }
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
                    if (is_loggable_for_unimportant_stuff()) {
                        log("reapply carry_anim for owner %s",
                             owner->to_string().c_str());
                    }
                    carrying->visible();
                } else {
                    if (is_loggable_for_unimportant_stuff()) {
                        log("do not reapply carry_anim for invisible owner %s",
                             owner->to_string().c_str());
                    }
                }
            } else {
                if (is_loggable_for_unimportant_stuff()) {
                    log("no carry_anim for owner %s", owner->to_string().c_str());
                }
                auto id = owner->get_weapon_id();
                if (id.ok()) {
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
            if (is_loggable_for_unimportant_stuff()) {
                log("hooks remove carry anim");
            }
            weapon_set_carry_anim(nullptr);
            verify(item);
            item->remove_owner();
            item->dead("weapon carry_anim owner killed");
        }
    }

    {_
        auto item = weapon_get_use_anim();
        if (item) {
            if (is_loggable_for_unimportant_stuff()) {
                log("hooks remove use anim");
            }
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
        //
        // Slow, but not used too often
        //
        for (auto p : level->all_things) {
            auto t = p.second;
            auto o = t->get_immediate_owner();
            if (o && (o == this)) {
                t->remove_owner();
            }
        }
    }
}
