//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_level_static.hpp"
#include "my_ptrcheck.hpp"

static int debug_enabled = false;

std::vector< LevelStaticp > LevelStatic::all_static_levels;

LevelStatic::LevelStatic(void)
{
  this->levelno = all_static_levels.size();

  newptr(MTYPE_LEVEL, this, "level");
}

LevelStatic::~LevelStatic(void) { oldptr(MTYPE_LEVEL, this); }

void level_fini(void)
{
  TRACE_AND_INDENT();
  LevelStatic::all_static_levels.clear();
}

LevelStaticp LevelStatic::level_new(void)
{
  TRACE_AND_INDENT();
  auto r = new LevelStatic();
  LevelStatic::all_static_levels.push_back(r);
  return r;
}

void LevelStatic::finalize(void)
{
  if (debug_enabled) {
    dump();
  }
}

void LevelStatic::dump(void)
{
  std::array< std::array< char, MAP_HEIGHT >, MAP_WIDTH > tmp;
  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      set(tmp, x, y, ' ');
    }
  }

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      auto c = get(data, x, y, MAP_DEPTH_OBJ);
      if (! c || (c == ' ')) {
        c = get(data, x, y, MAP_DEPTH_FLOOR);
      }
      set(tmp, x, y, c);
    }
  }

  LOG("LEVEL(%d):", levelno);
  for (auto y = 0; y < height; y++) {
    std::string s;
    for (auto x = 0; x < width; x++) {
      s += get(tmp, x, y);
    }
    LOG("LEVEL(%d): %s", levelno, s.c_str());
  }
  LOG("-");
}
