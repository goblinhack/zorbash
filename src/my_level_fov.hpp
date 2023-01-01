//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

#include "my_game_defs.hpp"

using FovMap = struct FovMap_ {
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > can_see {};
};
