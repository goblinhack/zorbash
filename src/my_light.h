/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file.
 */

#pragma once

#ifndef _MY_LIGHT_H
#define _MY_LIGHT_H

#include <map>
#include <memory>
#include "my_point.h"
#include "my_ptrcheck.h"

typedef std::shared_ptr< class Light > Lightp;
typedef std::map< uint32_t, Lightp > Lights;

class Light
{
private:

public:
    Light (void)
    {
        newptr(this, "light");
    }

    ~Light (void)
    {
        destroyed();
        oldptr(this);
    }

    template <class Archive>
    void serialize (Archive & archive )
    {
        archive(cereal::make_nvp("id",               id),
                cereal::make_nvp("at",               at),
                cereal::make_nvp("max_light_rays",   max_light_rays),
                cereal::make_nvp("ray_depth_buffer", ray_depth_buffer),
                cereal::make_nvp("ray_rad",          ray_rad),
                cereal::make_nvp("is_on_map",        is_on_map));
    }

    /*
     * Unique per light.
     */
    uint32_t           id {};

    /*
     * Where the light is. Rays are calculated at this point and invalidated
     * if the light moves.
     */
    fpoint             at;
    bool               is_on_map;

    /*
     * Precalculated light rays.
     */
    uint16_t           max_light_rays;
    std::vector<float> ray_depth_buffer;
    std::vector<float> ray_rad;

    std::string logname(void);
    void destroyed(void);
    void reset(void);
    void move_delta(fpoint);
    void move_to(fpoint to);
    void pop(void);

    void log_(const char *fmt, va_list args); // compile error without
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void die_(const char *fmt, va_list args); // compile error without
    void die(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
};

extern Lightp light_new(uint16_t max_light_arrays);

#endif /* LIGHT_H */
