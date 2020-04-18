//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_LIGHT_H
#define _MY_LIGHT_H

#include "my_thing_template.h"

typedef struct {
    float depth_closest;
    float depth_furthest;
    float sinr;
    float cosr;
} Ray;

class Light
{
private:

public:
    Light (void);
    ~Light (void);
    //
    // Where the light is. Rays are calculated at this point and invalidated
    // if the light moves.
    //
    fpoint             at;
    fpoint             offset;

    //
    // The owner of the light, so we don't block our own light.
    //
    Thingp             owner;

    float              flicker_radius;
    uint8_t            flicker {0};

    //
    // Precalculated light rays.
    //
    float               strength;
    uint16_t            max_light_rays;
    std::vector<Ray>    ray;
    std::vector<float>  cached_gl_cmds;
    fpoint              cached_light_pos;

    color               col;

    uint8_t             is_being_destroyed:1 {};

    void destroy();
    void destroyed(void);
    void reset(void);
    void calculate(void);
    void render_triangle_fans(int last, int count);
    void render(int fbo, int last, int count);

    void log_(const char *fmt, va_list args); // compile error without
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void die_(const char *fmt, va_list args); // compile error without
    void die(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void minicon_(const char *fmt, va_list args); // compile error without
    void minicon(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
};

extern Lightp light_new(Thingp owner,
                        fpoint at,
                        fpoint offset,
                        float strength,
                        color col);
extern void lights_render(int minx, int miny, int maxx, int maxy, int fbo);

#endif // LIGHT_H
