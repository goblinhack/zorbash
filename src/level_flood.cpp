//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

std::deque< point > Level::flood_fill(point p) const
{
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > walked = {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > pushed = {};
  std::deque< point >                                             in;
  std::deque< point >                                             out;

  in.push_back(p);
  set(pushed, p.x, p.y, true);

  while (! in.empty()) {
    auto p = in.front();
    in.pop_front();

    if (get(walked, p.x, p.y)) {
      continue;
    }
    set(walked, p.x, p.y, true);

    if (is_obs_wall_or_door(p)) {
      continue;
    }

    out.push_back(p);

    if (p.x <= MAP_WIDTH - MAP_BORDER_ROCK) {
      if (! get(pushed, p.x + 1, p.y)) {
        set(pushed, p.x + 1, p.y, true);
        in.push_back(point(p.x + 1, p.y));
      }
    }

    if (p.x >= MAP_BORDER_ROCK) {
      if (! get(pushed, p.x - 1, p.y)) {
        set(pushed, p.x - 1, p.y, true);
        in.push_back(point(p.x - 1, p.y));
      }
    }

    if (p.y <= MAP_HEIGHT - MAP_BORDER_ROCK) {
      if (! get(pushed, p.x, p.y + 1)) {
        set(pushed, p.x, p.y + 1, true);
        in.push_back(point(p.x, p.y + 1));
      }
    }

    if (p.y >= MAP_BORDER_ROCK) {
      if (! get(pushed, p.x, p.y - 1)) {
        set(pushed, p.x, p.y - 1, true);
        in.push_back(point(p.x, p.y - 1));
      }
    }
  }

  return out;
}

std::deque< point > Level::flood_fill_points(point p, std::function< int(Thingp) > filter)
{
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > walked = {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > pushed = {};
  std::deque< point >                                             in;
  std::deque< point >                                             out;

  in.push_back(p);
  set(pushed, p.x, p.y, true);

  while (! in.empty()) {
    auto p = in.front();
    in.pop_front();

    if (get(walked, p.x, p.y)) {
      continue;
    }
    set(walked, p.x, p.y, true);

    if (is_obs_wall_or_door(p)) {
      continue;
    }

    bool got_one = false;
    FOR_ALL_NON_INTERNAL_THINGS(this, t, p.x, p.y)
    {
      if (filter(t)) {
        got_one = true;
        break;
      }
    }
    FOR_ALL_THINGS_END()

    if (! got_one) {
      continue;
    }

    out.push_back(p);

    if (p.x <= MAP_WIDTH - MAP_BORDER_ROCK) {
      if (! get(pushed, p.x + 1, p.y)) {
        set(pushed, p.x + 1, p.y, true);
        in.push_back(point(p.x + 1, p.y));
      }
    }

    if (p.x >= MAP_BORDER_ROCK) {
      if (! get(pushed, p.x - 1, p.y)) {
        set(pushed, p.x - 1, p.y, true);
        in.push_back(point(p.x - 1, p.y));
      }
    }

    if (p.y <= MAP_HEIGHT - MAP_BORDER_ROCK) {
      if (! get(pushed, p.x, p.y + 1)) {
        set(pushed, p.x, p.y + 1, true);
        in.push_back(point(p.x, p.y + 1));
      }
    }

    if (p.y >= MAP_BORDER_ROCK) {
      if (! get(pushed, p.x, p.y - 1)) {
        set(pushed, p.x, p.y - 1, true);
        in.push_back(point(p.x, p.y - 1));
      }
    }
  }

  return out;
}

std::deque< Thingp > Level::flood_fill_things(point p, std::function< int(Thingp) > filter)
{
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > walked = {};
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > pushed = {};
  std::deque< point >                                             in;
  std::deque< Thingp >                                            out;

  in.push_back(p);
  set(pushed, p.x, p.y, true);

  while (! in.empty()) {
    auto p = in.front();
    in.pop_front();

    if (get(walked, p.x, p.y)) {
      continue;
    }
    set(walked, p.x, p.y, true);

    if (is_obs_wall_or_door(p)) {
      continue;
    }

    bool got_one = false;
    FOR_ALL_NON_INTERNAL_THINGS(this, t, p.x, p.y)
    {
      if (filter(t)) {
        out.push_back(t);
        got_one = true;
        break;
      }
    }
    FOR_ALL_THINGS_END()

    if (! got_one) {
      continue;
    }

    if (p.x <= MAP_WIDTH - MAP_BORDER_ROCK) {
      if (! get(pushed, p.x + 1, p.y)) {
        set(pushed, p.x + 1, p.y, true);
        in.push_back(point(p.x + 1, p.y));
      }
    }

    if (p.x >= MAP_BORDER_ROCK) {
      if (! get(pushed, p.x - 1, p.y)) {
        set(pushed, p.x - 1, p.y, true);
        in.push_back(point(p.x - 1, p.y));
      }
    }

    if (p.y <= MAP_HEIGHT - MAP_BORDER_ROCK) {
      if (! get(pushed, p.x, p.y + 1)) {
        set(pushed, p.x, p.y + 1, true);
        in.push_back(point(p.x, p.y + 1));
      }
    }

    if (p.y >= MAP_BORDER_ROCK) {
      if (! get(pushed, p.x, p.y - 1)) {
        set(pushed, p.x, p.y - 1, true);
        in.push_back(point(p.x, p.y - 1));
      }
    }
  }

  return out;
}
