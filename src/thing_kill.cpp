//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_log.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_string.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

//
// Lower level function than dead. Adds the thing to gc.
//
void Thing::kill (Thingp killer, const char *reason)
{_
    if (is_dead) {
        return;
    }

    //
    // Call a python function on death? It's ok to do this on death,
    // but if being destroyed then its being garbage collected, like
    // at the end of the level.
    //
    if (!level->is_being_destroyed) {
        auto on_death = on_death_do();
        if (!std::empty(on_death)) {
            auto t = split_tokens(on_death, '.');
            if (t.size() == 2) {
                auto mod = t[0];
                auto fn = t[1];
                std::size_t found = fn.find("()");
                if (found != std::string::npos) {
                    fn = fn.replace(found, 2, "");
                }
                py_call_void_fn(mod.c_str(), fn.c_str(),
                                id.id, (unsigned int)mid_at.x, (unsigned int)mid_at.y);
            } else {
                ERR("Bad on_death call [%s] expected mod:function, got %d elems",
                    on_death.c_str(), (int)on_death.size());
            }
        }
    }

    //
    // Unwield weapons
    //
    unwield("owner is dead");

    //
    // If in a bag, get out of there!
    //
    auto immediate_owner = get_immediate_owner();
    if (immediate_owner) {
        immediate_owner->bag_remove(this);
    }

    //
    // If a minion generator dies, kill all minions
    //
    if (is_minion_generator()) {
        kill_minions(killer);
    }

    if (is_spawner()) {
        kill_spawned(killer);
    }

    if (is_player()) {
        TOPCON("RIP: Killed %s.", reason);
        TOPCON("%%fg=red$Congratulations, you are dead!%%fg=reset$");
        game->dead_select(reason);
        level->map_follow_player = false;
    } else if (is_loggable_for_important_stuff()) {
        log("%s is dead, %s", text_The().c_str(), reason);
        if (killer && (killer != this)) {
            if (killer->is_player()) {
                if (is_monst()) {
                    TOPCON("%s is dead, %s.", text_The().c_str(), reason);
                } else {
                    TOPCON("%s is destroyed %s.", text_The().c_str(), reason);
                }
            }
        }
    }

    //
    // Set is_dead after the log message or we print it as dead
    //
    is_dead = true;

    //
    // Resurrect unless say this was a minion and its master died
    //
    if (!is_resurrection_blocked) {
        if (is_resurrectable()) {
            set_tick_resurrect_when(game->tick_current + get_resurrect());
        }
    }

    if (monstp) {
        //
        // So that slimes don't keep moving when dead
        //
        move_finish();

        //
        // Drop everything!
        //
        if (on_death_drop_all_items()) {
            log("Drop all items on death");
            drop_all();
        }

        skill_remove_all();
    }

    if (on_death_is_open()) {
        log("Killed, now open");
        level_pop();
        is_open = true;
        level_push();
        auto p = level->player;
        if (p) {
            TOPCON("The door crashes open.");
            p->update_light();
        }
    }

    if (is_corpse_on_death()) {
        if (is_loggable_for_important_stuff()) {
            log("Killed, leaves corpse");
        }

        level->set_is_corpse(mid_at.x, mid_at.y);

        if (is_bleeder()) {
            int splatters = random_range(2, 10);
            for (int splatter = 0; splatter < splatters; splatter++) {
                auto tpp = tp_random_blood();
                (void) level->thing_new(tpp->name(),
                                        mid_at, fpoint(0.25, 0.25));
            }
        }
        return;
    }

    level_pop();

    if (is_loggable_for_important_stuff()) {
        log("Killed, need to garbage collect");
    }

    gc();
}

void Thing::kill (Thingp killer, std::string &reason)
{_
    kill(killer, reason.c_str());
}

bool Thing::if_matches_then_kill (const std::string& what, const point &p)
{_
    //
    // Don't destroy the floor under critical items
    //
    if ((what == "is_floor") || (what == "is_corridor")) {
        FOR_ALL_THINGS(level, t, p.x, p.y) {
            if (t->is_critical_to_level()) {
                return true;
            }
        } FOR_ALL_THINGS_END()
    }

    FOR_ALL_THINGS(level, t, p.x, p.y) {
        if (t->matches(what)) {
            t->dead(this, "killed");
        }
    } FOR_ALL_THINGS_END()

    return true;
}
