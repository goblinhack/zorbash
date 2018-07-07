/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_TIMER_H_
#define _MY_TIMER_H_
typedef void (*action_timer_callback)(void *);
typedef void (*action_timer_destroy_callback)(void *);

class action_timer_key {
public:
    action_timer_key (void)
    {
        newptr(this, "action_timer_key");
    }

    ~action_timer_key (void)
    {
        oldptr(this);
    }

    bool operator <(const action_timer_key& rhs) const
    {
        return (key1 < rhs.key1) && (key2 < rhs.key2);
    }

    int key1 {};
    int key2 {};
};

class action_timer {
public:
    action_timer (void)
    {
        newptr(this, "action_timer_key");
    }

    ~action_timer (void)
    {
        oldptr(this);
    }

    action_timer_key key;

    /*
     * Expires when ?
     */
    uint32_t expires_when {};

    /*
     * What to do on callback.
     */
    action_timer_callback callback {};

    /*
     * What to do on timer free.
     */
    action_timer_destroy_callback destroy_callback {};

    void *context {};
};

typedef std::shared_ptr< class action_timer > action_timerp;
typedef std::map< class action_timer_key, action_timerp > action_timers;

/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */
#pragma once

extern action_timers action_timer_map;

void action_timer_destroy(action_timers *t, action_timerp p);
action_timerp action_timer_create(action_timers *action_timer_map,
                    action_timer_callback,
                    action_timer_destroy_callback,
                    void *context,
                    const char *name,
                    uint32_t duration_m_s,
                    uint32_t jitter);
void action_timers_tick(action_timers *action_timer_map);
#endif
