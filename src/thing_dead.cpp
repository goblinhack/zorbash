//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_log.h"

void Thing::kill (Thingp killer, const char *reason)
{_
    if (is_dead) {
        return;
    }

    //
    // Unwield weapons
    //
    unwield("owner is dead");

    if (is_player()) {
        MINICON("RIP: %s", reason);
        MINICON("%%fg=red$Congratulations, you are dead!%%fg=reset$");
        game->dead_select(reason);
        level->map_follow_player = false;
    } else if (is_loggable_for_important_stuff()) {
        if (!killer) {
            MINICON("%s is dead, %s", text_The().c_str(), reason);
        } else if (killer != this) {
            MINICON("%s is dead, %s", text_The().c_str(), reason);
        }
    }

    //
    // Set is_dead after the log message or we print it as dead
    //
    is_dead = true;

    if (is_resurrectable()) {
        set_tick_resurrect_when(game->tick_current + get_resurrect());
    }

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
                            id.id, (int)mid_at.x, (int)mid_at.y);
        } else {
            ERR("bad on_death call [%s] expected mod:function, got %d elems",
                on_death.c_str(), (int)on_death.size());
        }
    }

    const auto tpp = tp();
    if (unlikely(!tpp)) {
        ERR("no tp");
    } else {
        if (is_corpse_on_death()) {
            if (tpp->is_loggable_for_important_stuff()) {
                log("killed, leaves corpse");
            }

            level->set_is_corpse(mid_at.x, mid_at.y);

            if (tpp->is_bleeder()) {
                int splatters = random_range(2, 10);
                for (int splatter = 0; splatter < splatters; splatter++) {
                    auto tpp = tp_random_blood();
                    (void) level->thing_new(tpp->name(),
                                            mid_at, fpoint(0.25, 0.25));
                }
            }
            return;
        }

        if (tpp->is_loggable_for_important_stuff()) {
            log("killed");
        }
    }

    dbg("need to gc");
    auto result = level->all_gc_things.insert(std::pair(id, this));
    if (result.second == false) {
        err("failed to insert into gc thing map");
    }
}

void Thing::kill (Thingp killer, std::string &reason)
{_
    kill(killer, reason.c_str());
}

void Thing::dead_ (Thingp killer, const char *fmt, va_list args)
{
    verify(this);

    if (tp()->is_loggable_for_unimportant_stuff()) {
        auto t = this;
        char buf[MAXSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSTR);
        len = (int)strlen(buf);

        if (killer) {
            snprintf(buf + len, MAXSTR - len, "%s: killed by %s: ",
                     t->to_string().c_str(),
                     killer->to_string().c_str());
        } else {
            snprintf(buf + len, MAXSTR - len, "%s: killed: ",
                     t->to_string().c_str());
        }

        len = (int)strlen(buf);
        vsnprintf(buf + len, MAXSTR - len, fmt, args);

        putf(MY_STDOUT, buf);

        char reason[MAXSTR];
        vsnprintf(reason, MAXSTR, fmt, args);
        kill(killer, reason);
    } else {
        kill(killer, "no reason");
    }
}

void Thing::dead (Thingp killer, const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->dead_(killer, fmt, args);
    va_end(args);
}

void Thing::dead_ (const char *fmt, va_list args)
{
    verify(this);

    if (tp()->is_loggable_for_unimportant_stuff()) {
        auto t = this;
        char buf[MAXSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSTR);
        len = (int)strlen(buf);
        snprintf(buf + len, MAXSTR - len, "%s: dead: ",
                 t->to_string().c_str());

        len = (int)strlen(buf);
        vsnprintf(buf + len, MAXSTR - len, fmt, args);

        putf(MY_STDOUT, buf);
        char reason[MAXSTR];
        vsnprintf(reason, MAXSTR, fmt, args);
        kill(nullptr, reason);
    } else {
        kill(nullptr, "no reason");
    }
}

void Thing::dead (Thingp killer, std::string &reason)
{
    verify(this);

    if (tp()->is_loggable_for_unimportant_stuff()) {
        auto t = this;
        char buf[MAXSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSTR);
        len = (int)strlen(buf);

        if (killer) {
            snprintf(buf + len, MAXSTR - len, "%s: killed by %s: ",
                    t->to_string().c_str(),
                    killer->to_string().c_str());
        } else {
            snprintf(buf + len, MAXSTR - len, "%s: killed: ",
                    t->to_string().c_str());
        }

        putf(MY_STDOUT, reason.c_str());
        kill(killer, reason);
    } else {
        kill(killer, "no reason");
    }
}

void Thing::dead (std::string &reason)
{
    verify(this);

    if (tp()->is_loggable_for_unimportant_stuff()) {
        auto t = this;
        char buf[MAXSTR];
        int len;

        buf[0] = '\0';
        get_timestamp(buf, MAXSTR);
        len = (int)strlen(buf);
        snprintf(buf + len, MAXSTR - len, "%s: dead: ",
                 t->to_string().c_str());

        putf(MY_STDOUT, reason.c_str());
        kill(nullptr, reason);
    } else {
        kill(nullptr, "no reason");
    }
}

void Thing::dead (const char *fmt, ...)
{
    verify(this);
    auto t = this;
    va_list args;

    va_start(args, fmt);
    t->dead_(fmt, args);
    va_end(args);
}
