//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once

#include "my_thing_defs.hpp"

typedef struct FovMap_ {
  std::array< std::array< bool, MAP_HEIGHT >, MAP_WIDTH > can_see {};
} FovMap;
