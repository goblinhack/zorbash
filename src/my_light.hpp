//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LIGHT_H
#define _MY_LIGHT_H

#include "my_format_str_attribute.hpp"
#include "my_fwd.hpp"
#include "my_point.hpp"
#include "my_thing_defs.hpp"

typedef struct {
  int16_t depth_furthest;
} Ray;

typedef struct {
  point p;
  float distance;
} RayPoint;

class Light
{
public:
  Light(void);
  ~Light(void);

  Levelp level {};
  Thingp owner {}; // The owner, so we don't block our own light.
  color  col;
  int    fbo {-1};

  point offset;
  point cached_light_pos;
  point cached_pixel_map_at;

  //
  // How often lights flicker.
  //
  float flicker {};
  int   flicker_count {};

  float light_power {}; // Light_scale
  int   light_dist {};
  int   light_dist_prev {};

  uint32_t tick {}; // Last time the light was updated

  uint16_t max_light_rays {};

  bool is_being_destroyed : 1 {};
  bool ray_cast_only      : 1 {};

  std::vector< Ray >                                        ray;
  std::vector< float >                                      cached_gl_cmds;
  std::array< std::vector< RayPoint >, LIGHT_MAX_RAYS_MAX > points;

  bool calculate(void);
  void con(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void con_(const char *fmt, va_list args); // compile error without
  void destroy();
  void destroyed(void);
  void die(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void die_(const char *fmt, va_list args); // compile error without
  void draw_line(const int16_t index, const point p0, const point p1);
  void draw_pixel(const int16_t index, const point p0, const point p1);
  void err(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void err_(const char *fmt, va_list args); // compile error without
  void log(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void log_(const char *fmt, va_list args); // compile error without
  void render(int ray_cast_only);
  void render_triangle_fans(void);
  void reset(void);
  void topcon(const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
  void topcon_(const char *fmt, va_list args); // compile error without
  void update(void);
};

extern Lightp light_new(Thingp owner, point offset, int light_dist, color col, int fbo);

extern Lightp light_new(Thingp owner, point offset, int light_dist);

#endif // LIGHT_H
