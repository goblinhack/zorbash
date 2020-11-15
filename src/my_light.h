//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_LIGHT_H
#define _MY_LIGHT_H

#include "my_thing_template.h"

typedef struct {
    int16_t depth_furthest;
} Ray;

typedef struct {
    point p;
    float distance;
} RayPoint;

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
    point              offset;
    point              cached_light_pos;
    point              cached_pixel_map_at;
    std::vector<Ray>   ray;
    std::vector<float> cached_gl_cmds;
    std::array< std::vector<RayPoint>, LIGHT_MAX_RAYS > points;
    int16_t            orig_strength {};
    int16_t            strength {};
    uint16_t           max_light_rays {};
    uint8_t            flicker {0};
    uint8_t            is_being_destroyed:1 {};

    void destroy();
    void destroyed(void);
    void reset(void);
    void update(void);
    bool calculate(int last);
    void render_triangle_fans(int last, int count);
    void render(int last, int count);
    void draw_line(const int16_t index, const point &p0, const point &p1);                                    \
    void draw_pixel(const int16_t index, const point &p0, const point &p1);                                    \

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
                        point offset,
                        int strength,
                        color col,
                        int fbo);

#endif // LIGHT_H
