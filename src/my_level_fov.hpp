//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once

#include "my_game_defs.hpp"
#include <array>

typedef struct FovMap_ {
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > can_see {};
} FovMap;
