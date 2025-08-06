//
// Copyright goblinhack@gmail.com
//

#pragma once

using LevelsStatic = std::vector< LevelStaticp >;

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
  uint8_t  width {MAP_WIDTH_MAX};
  uint8_t  height {MAP_HEIGHT_MAX};
  uint8_t  depth {0};

  std::array< std::array< std::array< char, MAP_DEPTH >, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > data {};

  static LevelStaticp level_new(void);
  void                finalize(void);
  void                dump(void);
};
void level_fini(void);
