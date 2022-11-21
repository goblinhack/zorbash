//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

#include "my_game_defs.hpp"
// REMOVED #include <array>

using FovMap = struct FovMap_ {
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > can_see {};
};
