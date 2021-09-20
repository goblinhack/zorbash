//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#ifndef _MY_PARTICLE_H_
#define _MY_PARTICLE_H_

#include "my_main.h"
#include "my_point.h"
#include "my_size.h"
#include "my_thing_id.h"

typedef class Particle_ {
public:
  Particle_(ThingId thing_id,
        point start, point stop,
        point pixel_map_at,
        isize sz,
        uint32_t ts_start, uint32_t ts_stop,
        class Tile* tile,
        bool hflip,
        bool make_visible_at_end) :
    id(thing_id),
    start(start),
    stop(stop),
    pixel_map_at(pixel_map_at),
    sz(sz),
    ts_start(ts_start),
    ts_stop(ts_stop),
    tile(tile),
    hflip(hflip),
    make_visible_at_end(make_visible_at_end) { }

  Particle_(point start, point stop,
        point pixel_map_at,
        isize sz,
        uint32_t ts_start, uint32_t ts_stop,
        class Tile* tile,
        bool hflip,
        bool make_visible_at_end) :
    start(start),
    stop(stop),
    pixel_map_at(pixel_map_at),
    sz(sz),
    ts_start(ts_start),
    ts_stop(ts_stop),
    tile(tile),
    hflip(hflip),
    make_visible_at_end(make_visible_at_end) { }

  ThingId id {};
  point start;
  point stop;
  point pixel_map_at;
  isize sz;
  uint32_t ts_start {};
  uint32_t ts_stop {};
  class Tile* tile {};
  bool hflip {};
  bool make_visible_at_end {};
  bool removed {};
  int height {};
} Particle;

#endif // _MY_PARTICLE_H_
