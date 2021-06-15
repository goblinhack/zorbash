//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

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

    if (get_immediate_owner_id().ok()) {
        owner = get_immediate_owner();
    }

    if (owner) {
        if (is_loggable_for_unimportant_stuff()) {
            dbg("Detach %" PRIx32 " from owner %s", id.id, owner->to_string().c_str());
        }

        if (id == owner->get_on_fire_anim_id()) {
            if (is_loggable_for_unimportant_stuff()) {
                dbg("Detach on_fire_anim_id from owner %s", owner->to_string().c_str());
            }
            owner->set_on_fire_anim_id(0);
        }

        if (id == owner->get_weapon_id()) {
            owner->unwield("remove hooks for weapon id");

            if (is_loggable_for_unimportant_stuff()) {
                dbg("Detach weapon_id from owner %s", owner->to_string().c_str());
            }
            owner->set_weapon_id(0);
        }

        if (id == owner->get_weapon_id_carry_anim()) {
            owner->unwield("remove hooks for carry-anim");

            if (is_loggable_for_unimportant_stuff()) {
                dbg("Detach carry-anim from owner %s", owner->to_string().c_str());
            }
            owner->weapon_set_carry_anim_id(0);
        }

        if (id == owner->get_weapon_id_use_anim()) {
            if (is_loggable_for_unimportant_stuff()) {
                dbg("Detach use_anim from owner %s", owner->to_string().c_str());
            }
            owner->weapon_set_use_anim_id(0);

            //
            // End of the use-animation, make the sword visible again.
            //
            auto carry_anim = owner->weapon_get_carry_anim();
            if (carry_anim) {
                dbg("Make carry weapon visible %s", owner->to_string().c_str());
_
                //
                // But only if the owner is visible.
                //
                if (owner->is_visible()) {
                    if (is_loggable_for_unimportant_stuff()) {
                        dbg("Reapply carry-anim for owner %s",
                             owner->to_string().c_str());
                    }
                    carry_anim->visible();
                } else {
                    if (is_loggable_for_unimportant_stuff()) {
                        dbg("Do not reapply carry-anim for invisible owner %s",
                             owner->to_string().c_str());
                    }
                }
            } else {
                if (is_loggable_for_unimportant_stuff()) {
                    dbg("No carry-anim for owner %s", owner->to_string().c_str());
                }
                auto id = owner->get_weapon_id();
                if (id.ok()) {
                    owner->wield(owner->weapon_get());
                }
            }
        }
    }

    //
    // Remove from inventory and remove from ownership
    //
    if (get_immediate_owner_id().ok()) {
        owner->drop_into_ether(this);
    }

    if (get_immediate_minion_owner_id().ok()) {
        remove_minion_owner();
    }

    if (get_immediate_spawned_owner_id().ok()) {
        remove_spawner_owner();
    }

    //
    // We own things like a sword. i.e. we are a player.
    //
    {_
        auto item = weapon_get_carry_anim();
        if (item) {
            if (is_loggable_for_unimportant_stuff()) {
                dbg("Hooks remove carry-anim");
            }
            weapon_set_carry_anim(nullptr);
            verify(item);
            item->remove_owner();
            item->dead("weapon carry-anim owner killed");
        }
    }

    {_
        auto item = weapon_get_use_anim();
        if (item) {
            if (is_loggable_for_unimportant_stuff()) {
                dbg("Hooks remove use-anim");
            }
            weapon_set_use_anim(nullptr);
            verify(item);
            item->remove_owner();
            item->dead("weapon use-anim owner killed");
        }
    }
}

void Thing::remove_all_references ()
{_
    //
    // Some things have lots of things they own
    //
    if (get_owned_count()) {
        dbg("Remove all owner references, total %d", get_owned_count());

        //
        // Slow, but not used too often
        //
        for (auto p : level->all_things) {
            auto t = p.second;
            auto o = t->get_immediate_owner();
            if (o == this) {
                t->remove_owner();
            }
        }
    }

    if (get_minion_count()) {
        dbg("Remove all minion references, total %d", get_minion_count());

        //
        // Slow, but not used too often
        //
        for (auto p : level->all_things) {
            auto t = p.second;
            auto o = t->get_immediate_minion_owner();
            if (o == this) {
                t->remove_minion_owner();
            }
        }
    }

    if (get_spawned_count()) {
        dbg("Remove all spawner references, total %d", get_spawned_count());

        //
        // Slow, but not used too often
        //
        for (auto p : level->all_things) {
            auto t = p.second;
            auto o = t->get_immediate_spawned_owner();
            if (o == this) {
                t->remove_spawner_owner();
            }
        }
    }
}
