/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */


#include "my_main.h"
#include "my_timer.h"
#include "my_time_util.h"

static void action_timer_free (action_timerp p)
{_
    verify(p.get());

    LOG("%p: Final free of action timer", p.get());

    if (p->destroy_callback) {
        (p->destroy_callback)(p->context);
    }
}

void action_timer_destroy (action_timers *t, action_timerp p)
{_
    verify(p.get());

    LOG("%p: Destroy action timer destroyed", p.get());

    if (!t) {
        return;
    }

    auto result = t->find(p->key);
    if (result == t->end()) {
        DIE("timer not found");
    }

    t->erase(p->key);
}

action_timerp action_timer_create (action_timers *action_timer_map,
                                   action_timer_callback callback,
                                   action_timer_destroy_callback destroy_callback,
                                   void *context,
                                   const char *name,
                                   uint32_t duration_m_s,
                                   uint32_t jitter)
{_
    static uint32_t tiebreak;

    auto t = std::make_shared< class action_timer >();
    t->expires_when = time_get_time_ms() + duration_m_s;
    if (jitter) {
        t->expires_when += myrand() % jitter;
    }

    t->context = context;
    t->callback = callback;
    t->destroy_callback = destroy_callback;
    t->key.key1 = t->expires_when;
    t->key.key2 = tiebreak++;

    auto key = t->key;

    auto result = action_timer_map->insert(std::make_pair(key, t));
    if (result.second == false) {
        DIE("timer insert name [%s] failed", name);
    }

    LOG("%p: Action timer (%s) created, fires in %3.2f secs",
        t.get(),
        name,
        ((float)(t->expires_when - time_get_time_ms())) /
        (float)ONESEC);

    return (t);
}

void action_timers_tick (action_timers *action_timer_map)
{_
    if (action_timer_map == nullptr) {
        return;
    }

    for (;/*ever*/;) {
        auto iter = action_timer_map->begin();
        if (iter == action_timer_map->end()) {
            return;
        }

        auto t = iter->second;
        if (!t) {
            return;
        }

        verify(t.get());

        if (t->expires_when > time_get_time_ms()) {
            return;
        }

        (t->callback)(t->context);

        verify(t.get());

        action_timer_free(t);

        action_timer_map->erase(iter);
    }
}
