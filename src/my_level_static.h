//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#include <memory> // do not remove
#include <vector> // do not remove
#include "my_fwd.h"
#include "my_thing_defs.h"

typedef std::vector<LevelStaticp> LevelsStatic;

class LevelStatic
{
private:
public:
  static LevelsStatic all_static_levels;

  LevelStatic (void);
  ~LevelStatic (void);

  //
  // Unique per level.
  //
  uint32_t                levelno {0};
  uint8_t                 width  {MAP_WIDTH};
  uint8_t                 height {MAP_HEIGHT};
  uint8_t                 depth  {0};

  std::array<
    std::array<
    std::array<char, MAP_DEPTH>, MAP_HEIGHT>, MAP_WIDTH> data {};

  static LevelStaticp level_new(void);
  void finalize(void);
  void dump(void);
};
void level_fini(void);
