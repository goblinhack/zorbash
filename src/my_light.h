//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
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

    Levelp             level {};
    Thingp             owner {}; // The owner, so we don't block our own light.
    color              col;
    int                fbo;
    float              flicker_radius {};
    float              strength {};
    fpoint             at;
    fpoint             offset;
    point              cached_light_pos;
    std::vector<Ray>   ray;
    std::vector<float> cached_gl_cmds;
    uint16_t           max_light_rays {};
    uint8_t            flicker {0};
    uint8_t            is_being_destroyed:1 {};

    void destroy();
    void destroyed(void);
    void reset(void);
    void calculate(int last);
    void render_triangle_fans(int last, int count);
    void render(int last, int count);

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
                        color col,
                        int fbo);

#endif // LIGHT_H
