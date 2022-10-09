//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_PARTICLE_HPP_
#define _MY_PARTICLE_HPP_

#include "my_callback.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_size.hpp"
#include "my_thing_id.hpp"

using Particle = class Particle_
{
public:
  Particle_(ThingId thing_id, point start, point stop, point pixel_map_at, isize sz, uint32_t ts_start,
            uint32_t ts_stop, class Tile *tile, bool hflip, MyCallback callback_in)
      : id(thing_id), start(start), stop(stop), pixel_map_at(pixel_map_at), sz(sz), ts_start(ts_start),
        ts_stop(ts_stop), tile(tile), hflip(hflip), callback(callback_in)
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
  bool        removed {};
  int         height {};
  MyCallback  callback;
};

#endif // _MY_PARTICLE_HPP_
