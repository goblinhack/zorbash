//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_WID_TILES_H_
#define _MY_WID_TILES_H_

#include <memory>
typedef std::shared_ptr< class WidTiles > wid_tilesp;

#include "my_tile.h"

class WidTiles {
public:
    WidTiles (void)
    {
    }

    ~WidTiles (void)
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
#endif
