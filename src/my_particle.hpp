//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_PARTICLE_HPP_
#define _MY_PARTICLE_HPP_

#include "my_main.hpp"
#include "my_point.hpp"
#include "my_size.hpp"
#include "my_thing_id.hpp"

typedef class Particle_
{
public:
  Particle_(ThingId thing_id, point start, point stop, point pixel_map_at, isize sz, uint32_t ts_start,
            uint32_t ts_stop, class Tile *tile, bool hflip, bool make_visible_at_end)
      : id(thing_id), start(start), stop(stop), pixel_map_at(pixel_map_at), sz(sz), ts_start(ts_start),
        ts_stop(ts_stop), tile(tile), hflip(hflip), make_visible_at_end(make_visible_at_end)
  {
  }

  Particle_(point start, point stop, point pixel_map_at, isize sz, uint32_t ts_start, uint32_t ts_stop,
            class Tile *tile, bool hflip, bool make_visible_at_end)
      : start(start), stop(stop), pixel_map_at(pixel_map_at), sz(sz), ts_start(ts_start), ts_stop(ts_stop),
        tile(tile), hflip(hflip), make_visible_at_end(make_visible_at_end)
  {
  }

  ThingId     id {};
  point       start;
  point       stop;
  point       pixel_map_at;
  isize       sz;
  uint32_t    ts_start {};
  uint32_t    ts_stop {};
  class Tile *tile {};
  bool        hflip {};
  bool        make_visible_at_end {};
  bool        removed {};
  int         height {};
} Particle;

#endif // _MY_PARTICLE_HPP_
