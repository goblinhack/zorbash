/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_LIGHT_H
#define _MY_LIGHT_H

#include <unordered_map>
#include <memory>
#include "my_game.h"
#include "my_point.h"
#include "my_thing.h"

typedef enum {
    LIGHT_QUALITY_POINT,
    LIGHT_QUALITY_LOW,
    LIGHT_QUALITY_HIGH,
} LightQuality;

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
        // log("destroyed");
        oldptr(this);
    }

    template <class Archive>
    void serialize (Archive & archive )
    {
        archive(cereal::make_nvp("id",               id),
                cereal::make_nvp("at",               at),
                cereal::make_nvp("strength",         strength),
                cereal::make_nvp("max_light_rays",   max_light_rays),
                cereal::make_nvp("ray_depth_buffer", ray_depth_buffer),
                cereal::make_nvp("ray_rad",          ray_rad));
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

    /*
     * The owner of the light, so we don't block our own light.
     */
    Thingp             owner;

    double             flicker_radius;
    uint8_t            flicker {0};

 /*
     * Precalculated light rays.
     */
    double              strength;
    uint16_t            max_light_rays;
    std::vector<float>  ray_depth_buffer;
    std::vector<float>  ray_rad;
//    std::vector<Thingp> ray_thing;
    std::vector<float>  glbuf;
    LightQuality        quality;
    color               col;

    void pop();
    std::string logname(void);
    void destroyed(void);
    void reset(void);
    void move_delta(fpoint);
    void move_to(fpoint to);

    void add_z_depth(Thingp, fpoint &light_pos, 
                     fpoint &light_end, double rad, int deg);
    bool calculate_for_obstacle(Thingp t, int x, int y);
    void calculate(void);

    void render_triangle_fans(void);
    void render_point_light(void);
    void render(int fbo);

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

extern Lightp light_new(uint16_t max_light_arrays, 
                        double strength, 
                        fpoint at,
                        LightQuality quality,
                        color col);
extern Lightp light_new(Thingp owner, 
                        uint16_t max_light_arrays, 
                        double strength,
                        fpoint at,
                        LightQuality quality,
                        color col);
extern void lights_calculate(void);
extern void lights_render(int minx, int miny, int maxx, int maxy, int fbo);

#endif /* LIGHT_H */
