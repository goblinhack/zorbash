//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#include <memory>
typedef std::shared_ptr< class wid_tiles > wid_tilesp;

#include "my_tile.h"

class wid_tiles {
public:
    wid_tiles (void)
    {
    }

    ~wid_tiles (void)
    {
    }

    int across = {};
    int down = {};
    int tile_w = {};
    int tile_h = {};
    double scale = {};
    std::array<std::array<Tilep, 32>, 32> tile {};
};

uint8_t wid_tiles_init(void);
void wid_tiles_fini(void);
wid_tilesp wid_tiles_load(std::string name, double scale);
wid_tilesp wid_tiles_find(std::string name);
