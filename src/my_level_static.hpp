//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#include "my_depth.hpp"
#include "my_fwd.hpp"
#include "my_thing_defs.hpp"
#include <memory> // do not remove
#include <vector> // do not remove

typedef std::vector< LevelStaticp > LevelsStatic;

class LevelStatic
{
private:
public:
  static LevelsStatic all_static_levels;

  LevelStatic(void);
  ~LevelStatic(void);

  //
  // Unique per level.
  //
  uint32_t levelno {0};
  uint8_t  width {MAP_WIDTH};
  uint8_t  height {MAP_HEIGHT};
  uint8_t  depth {0};

  std::array< std::array< std::array< char, MAP_DEPTH >, MAP_HEIGHT >, MAP_WIDTH > data {};

  static LevelStaticp level_new(void);
  void                finalize(void);
  void                dump(void);
};
void level_fini(void);
