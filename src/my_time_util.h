/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_TIME_UTIL_H_
#define _MY_TIME_UTIL_H_

#include <assert.h>
#ifdef NOT_NEEDED
#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif
#include <unistd.h>
#include <sys/time.h>
#include "my_main.h"
#include "my_sdl.h"

/*
 * Misc
 */
#undef ONESEC
#define ONESEC                          1000

uint8_t time_have_x_thousandths_passed_since(uint32_t tenths, uint32_t since);
uint8_t time_have_x_hundredths_passed_since(uint32_t tenths, uint32_t since);
uint8_t time_have_x_tenths_passed_since(uint32_t tenths, uint32_t since);
uint8_t time_have_x_secs_passed_since(uint32_t tenths, uint32_t since);
const char *time2str(uint32_t ms, char *buf, int32_t len);
const char *timestamp(char *buf, int32_t len);

extern uint32_t time_now;
#ifdef NOT_NEEDED
extern uint32_t base_time_in_mill;
#endif

extern uint32_t SDL_GetTicks(void);
static uint32_t time_update_time_milli(void);

static inline uint32_t time_get_time_ms (void)
{
    time_update_time_milli();

    return (time_now);
}

static inline uint32_t time_get_time_ms_cached (void)
{
    return (time_now);
}

static inline uint32_t time_update_time_milli (void)
{
#ifdef NOT_NEEDED
    //
    // Some macos specific way of getting the time that looks like it could
    // be useful, so leaving around
    //
    uint64_t abs_time = mach_absolute_time();
    Nanoseconds nano_time = AbsoluteToNanoseconds( *(AbsoluteTime *) &abs_time );
    uint64_t nano_val = * (uint64_t *) &nano_time;;
    uint32_t time_in_mill = nano_val / 1000000LLU;

    if (!base_time_in_mill) {
        base_time_in_mill = time_in_mill;
    }

    time_now = (time_in_mill - base_time_in_mill);

    return (time_now);
#endif
#ifdef NOT_NEEDED
    extern uint8_t sdl_main_loop_running;
    extern uint8_t sdl_init_video;

    if (unlikely(!sdl_main_loop_running || !sdl_init_video)) {
        struct timeval  tv;

        gettimeofday(&tv, NULL);

        uint32_t time_in_mill =
                ((uint32_t)(tv.tv_sec) * 1000) + (tv.tv_usec) / 1000;

        if (!base_time_in_mill) {
            base_time_in_mill = time_in_mill;
        }

        time_now = (time_in_mill - base_time_in_mill);

        return (time_now);
    }
#endif

    time_now = SDL_GetTicks();

    return (time_now);
}
#endif
