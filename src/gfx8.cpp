//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"

void gfx_init8(void)
{
  {
    std::initializer_list< std::string > tiles = {
        "ui.pixelart.8,0,0",   "ui.pixelart.8,1,0",   "ui.pixelart.8,2,0",   "ui.pixelart.8,3,0",
        "ui.pixelart.8,4,0",   "ui.pixelart.8,5,0",   "ui.pixelart.8,6,0",   "ui.pixelart.8,7,0",
        "ui.pixelart.8,8,0",   "ui.pixelart.8,9,0",   "ui.pixelart.8,10,0",  "ui.pixelart.8,11,0",
        "ui.pixelart.8,12,0",  "ui.pixelart.8,13,0",  "ui.pixelart.8,14,0",  "ui.pixelart.8,15,0",
        "ui.pixelart.8,0,1",   "ui.pixelart.8,1,1",   "ui.pixelart.8,2,1",   "ui.pixelart.8,3,1",
        "ui.pixelart.8,4,1",   "ui.pixelart.8,5,1",   "ui.pixelart.8,6,1",   "ui.pixelart.8,7,1",
        "ui.pixelart.8,8,1",   "ui.pixelart.8,9,1",   "ui.pixelart.8,10,1",  "ui.pixelart.8,11,1",
        "ui.pixelart.8,12,1",  "ui.pixelart.8,13,1",  "ui.pixelart.8,14,1",  "ui.pixelart.8,15,1",
        "ui.pixelart.8,0,2",   "ui.pixelart.8,1,2",   "ui.pixelart.8,2,2",   "ui.pixelart.8,3,2",
        "ui.pixelart.8,4,2",   "ui.pixelart.8,5,2",   "ui.pixelart.8,6,2",   "ui.pixelart.8,7,2",
        "ui.pixelart.8,8,2",   "ui.pixelart.8,9,2",   "ui.pixelart.8,10,2",  "ui.pixelart.8,11,2",
        "ui.pixelart.8,12,2",  "ui.pixelart.8,13,2",  "ui.pixelart.8,14,2",  "ui.pixelart.8,15,2",
        "ui.pixelart.8,0,3",   "ui.pixelart.8,1,3",   "ui.pixelart.8,2,3",   "ui.pixelart.8,3,3",
        "ui.pixelart.8,4,3",   "ui.pixelart.8,5,3",   "ui.pixelart.8,6,3",   "ui.pixelart.8,7,3",
        "ui.pixelart.8,8,3",   "ui.pixelart.8,9,3",   "ui.pixelart.8,10,3",  "ui.pixelart.8,11,3",
        "ui.pixelart.8,12,3",  "ui.pixelart.8,13,3",  "ui.pixelart.8,14,3",  "ui.pixelart.8,15,3",
        "ui.pixelart.8,0,4",   "ui.pixelart.8,1,4",   "ui.pixelart.8,2,4",   "ui.pixelart.8,3,4",
        "ui.pixelart.8,4,4",   "ui.pixelart.8,5,4",   "ui.pixelart.8,6,4",   "ui.pixelart.8,7,4",
        "ui.pixelart.8,8,4",   "ui.pixelart.8,9,4",   "ui.pixelart.8,10,4",  "ui.pixelart.8,11,4",
        "ui.pixelart.8,12,4",  "ui.pixelart.8,13,4",  "ui.pixelart.8,14,4",  "ui.pixelart.8,15,4",
        "ui.pixelart.8,0,5",   "ui.pixelart.8,1,5",   "ui.pixelart.8,2,5",   "ui.pixelart.8,3,5",
        "ui.pixelart.8,4,5",   "ui.pixelart.8,5,5",   "ui.pixelart.8,6,5",   "ui.pixelart.8,7,5",
        "ui.pixelart.8,8,5",   "ui.pixelart.8,9,5",   "ui.pixelart.8,10,5",  "ui.pixelart.8,11,5",
        "ui.pixelart.8,12,5",  "ui.pixelart.8,13,5",  "ui.pixelart.8,14,5",  "ui.pixelart.8,15,5",
        "ui.pixelart.8,0,6",   "ui.pixelart.8,1,6",   "ui.pixelart.8,2,6",   "ui.pixelart.8,3,6",
        "ui.pixelart.8,4,6",   "ui.pixelart.8,5,6",   "ui.pixelart.8,6,6",   "ui.pixelart.8,7,6",
        "ui.pixelart.8,8,6",   "ui.pixelart.8,9,6",   "ui.pixelart.8,10,6",  "ui.pixelart.8,11,6",
        "ui.pixelart.8,12,6",  "ui.pixelart.8,13,6",  "ui.pixelart.8,14,6",  "ui.pixelart.8,15,6",
        "ui.pixelart.8,0,7",   "ui.pixelart.8,1,7",   "ui.pixelart.8,2,7",   "ui.pixelart.8,3,7",
        "ui.pixelart.8,4,7",   "ui.pixelart.8,5,7",   "ui.pixelart.8,6,7",   "ui.pixelart.8,7,7",
        "ui.pixelart.8,8,7",   "ui.pixelart.8,9,7",   "ui.pixelart.8,10,7",  "ui.pixelart.8,11,7",
        "ui.pixelart.8,12,7",  "ui.pixelart.8,13,7",  "ui.pixelart.8,14,7",  "ui.pixelart.8,15,7",
        "ui.pixelart.8,0,8",   "ui.pixelart.8,1,8",   "ui.pixelart.8,2,8",   "ui.pixelart.8,3,8",
        "ui.pixelart.8,4,8",   "ui.pixelart.8,5,8",   "ui.pixelart.8,6,8",   "ui.pixelart.8,7,8",
        "ui.pixelart.8,8,8",   "ui.pixelart.8,9,8",   "ui.pixelart.8,10,8",  "ui.pixelart.8,11,8",
        "ui.pixelart.8,12,8",  "ui.pixelart.8,13,8",  "ui.pixelart.8,14,8",  "ui.pixelart.8,15,8",
        "ui.pixelart.8,0,9",   "ui.pixelart.8,1,9",   "ui.pixelart.8,2,9",   "ui.pixelart.8,3,9",
        "ui.pixelart.8,4,9",   "ui.pixelart.8,5,9",   "ui.pixelart.8,6,9",   "ui.pixelart.8,7,9",
        "ui.pixelart.8,8,9",   "ui.pixelart.8,9,9",   "ui.pixelart.8,10,9",  "ui.pixelart.8,11,9",
        "ui.pixelart.8,12,9",  "ui.pixelart.8,13,9",  "ui.pixelart.8,14,9",  "ui.pixelart.8,15,9",
        "ui.pixelart.8,0,10",  "ui.pixelart.8,1,10",  "ui.pixelart.8,2,10",  "ui.pixelart.8,3,10",
        "ui.pixelart.8,4,10",  "ui.pixelart.8,5,10",  "ui.pixelart.8,6,10",  "ui.pixelart.8,7,10",
        "ui.pixelart.8,8,10",  "ui.pixelart.8,9,10",  "ui.pixelart.8,10,10", "ui.pixelart.8,11,10",
        "ui.pixelart.8,12,10", "ui.pixelart.8,13,10", "ui.pixelart.8,14,10", "ui.pixelart.8,15,10",
        "ui.pixelart.8,0,11",  "ui.pixelart.8,1,11",  "ui.pixelart.8,2,11",  "ui.pixelart.8,3,11",
        "ui.pixelart.8,4,11",  "ui.pixelart.8,5,11",  "ui.pixelart.8,6,11",  "ui.pixelart.8,7,11",
        "ui.pixelart.8,8,11",  "ui.pixelart.8,9,11",  "ui.pixelart.8,10,11", "ui.pixelart.8,11,11",
        "ui.pixelart.8,12,11", "ui.pixelart.8,13,11", "ui.pixelart.8,14,11", "ui.pixelart.8,15,11",
        "ui.pixelart.8,0,12",  "ui.pixelart.8,1,12",  "ui.pixelart.8,2,12",  "ui.pixelart.8,3,12",
        "ui.pixelart.8,4,12",  "ui.pixelart.8,5,12",  "ui.pixelart.8,6,12",  "ui.pixelart.8,7,12",
        "ui.pixelart.8,8,12",  "ui.pixelart.8,9,12",  "ui.pixelart.8,10,12", "ui.pixelart.8,11,12",
        "ui.pixelart.8,12,12", "ui.pixelart.8,13,12", "ui.pixelart.8,14,12", "ui.pixelart.8,15,12",
        "ui.pixelart.8,0,13",  "ui.pixelart.8,1,13",  "ui.pixelart.8,2,13",  "ui.pixelart.8,3,13",
        "ui.pixelart.8,4,13",  "ui.pixelart.8,5,13",  "ui.pixelart.8,6,13",  "ui.pixelart.8,7,13",
        "ui.pixelart.8,8,13",  "ui.pixelart.8,9,13",  "ui.pixelart.8,10,13", "ui.pixelart.8,11,13",
        "ui.pixelart.8,12,13", "ui.pixelart.8,13,13", "ui.pixelart.8,14,13", "ui.pixelart.8,15,13",
        "ui.pixelart.8,0,14",  "ui.pixelart.8,1,14",  "ui.pixelart.8,2,14",  "ui.pixelart.8,3,14",
        "ui.pixelart.8,4,14",  "ui.pixelart.8,5,14",  "ui.pixelart.8,6,14",  "ui.pixelart.8,7,14",
        "ui.pixelart.8,8,14",  "ui.pixelart.8,9,14",  "ui.pixelart.8,10,14", "ui.pixelart.8,11,14",
        "ui.pixelart.8,12,14", "ui.pixelart.8,13,14", "ui.pixelart.8,14,14", "ui.pixelart.8,15,14",
        "ui.pixelart.8,0,15",  "ui.pixelart.8,1,15",  "ui.pixelart.8,2,15",  "ui.pixelart.8,3,15",
        "ui.pixelart.8,4,15",  "ui.pixelart.8,5,15",  "ui.pixelart.8,6,15",  "ui.pixelart.8,7,15",
        "ui.pixelart.8,8,15",  "ui.pixelart.8,9,15",  "ui.pixelart.8,10,15", "ui.pixelart.8,11,15",
        "ui.pixelart.8,12,15", "ui.pixelart.8,13,15", "ui.pixelart.8,14,15", "ui.pixelart.8,15,15",
    };
    const std::vector< std::string > arr(tiles);
    tile_load_arr("data/gfx/ui/pixelart/ui_vert1.tga", "ui_pixelart_box8", 8, 8, arr);
  }

  {
    std::initializer_list< std::string > tiles = {
        "ui.ascii.8,0,0",   "ui.ascii.8,1,0",   "ui.ascii.8,2,0",   "ui.ascii.8,3,0",   "ui.ascii.8,4,0",
        "ui.ascii.8,5,0",   "ui.ascii.8,6,0",   "ui.ascii.8,7,0",   "ui.ascii.8,8,0",   "ui.ascii.8,9,0",
        "ui.ascii.8,10,0",  "ui.ascii.8,11,0",  "ui.ascii.8,12,0",  "ui.ascii.8,13,0",  "ui.ascii.8,14,0",
        "ui.ascii.8,15,0",  "ui.ascii.8,0,1",   "ui.ascii.8,1,1",   "ui.ascii.8,2,1",   "ui.ascii.8,3,1",
        "ui.ascii.8,4,1",   "ui.ascii.8,5,1",   "ui.ascii.8,6,1",   "ui.ascii.8,7,1",   "ui.ascii.8,8,1",
        "ui.ascii.8,9,1",   "ui.ascii.8,10,1",  "ui.ascii.8,11,1",  "ui.ascii.8,12,1",  "ui.ascii.8,13,1",
        "ui.ascii.8,14,1",  "ui.ascii.8,15,1",  "ui.ascii.8,0,2",   "ui.ascii.8,1,2",   "ui.ascii.8,2,2",
        "ui.ascii.8,3,2",   "ui.ascii.8,4,2",   "ui.ascii.8,5,2",   "ui.ascii.8,6,2",   "ui.ascii.8,7,2",
        "ui.ascii.8,8,2",   "ui.ascii.8,9,2",   "ui.ascii.8,10,2",  "ui.ascii.8,11,2",  "ui.ascii.8,12,2",
        "ui.ascii.8,13,2",  "ui.ascii.8,14,2",  "ui.ascii.8,15,2",  "ui.ascii.8,0,3",   "ui.ascii.8,1,3",
        "ui.ascii.8,2,3",   "ui.ascii.8,3,3",   "ui.ascii.8,4,3",   "ui.ascii.8,5,3",   "ui.ascii.8,6,3",
        "ui.ascii.8,7,3",   "ui.ascii.8,8,3",   "ui.ascii.8,9,3",   "ui.ascii.8,10,3",  "ui.ascii.8,11,3",
        "ui.ascii.8,12,3",  "ui.ascii.8,13,3",  "ui.ascii.8,14,3",  "ui.ascii.8,15,3",  "ui.ascii.8,0,4",
        "ui.ascii.8,1,4",   "ui.ascii.8,2,4",   "ui.ascii.8,3,4",   "ui.ascii.8,4,4",   "ui.ascii.8,5,4",
        "ui.ascii.8,6,4",   "ui.ascii.8,7,4",   "ui.ascii.8,8,4",   "ui.ascii.8,9,4",   "ui.ascii.8,10,4",
        "ui.ascii.8,11,4",  "ui.ascii.8,12,4",  "ui.ascii.8,13,4",  "ui.ascii.8,14,4",  "ui.ascii.8,15,4",
        "ui.ascii.8,0,5",   "ui.ascii.8,1,5",   "ui.ascii.8,2,5",   "ui.ascii.8,3,5",   "ui.ascii.8,4,5",
        "ui.ascii.8,5,5",   "ui.ascii.8,6,5",   "ui.ascii.8,7,5",   "ui.ascii.8,8,5",   "ui.ascii.8,9,5",
        "ui.ascii.8,10,5",  "ui.ascii.8,11,5",  "ui.ascii.8,12,5",  "ui.ascii.8,13,5",  "ui.ascii.8,14,5",
        "ui.ascii.8,15,5",  "ui.ascii.8,0,6",   "ui.ascii.8,1,6",   "ui.ascii.8,2,6",   "ui.ascii.8,3,6",
        "ui.ascii.8,4,6",   "ui.ascii.8,5,6",   "ui.ascii.8,6,6",   "ui.ascii.8,7,6",   "ui.ascii.8,8,6",
        "ui.ascii.8,9,6",   "ui.ascii.8,10,6",  "ui.ascii.8,11,6",  "ui.ascii.8,12,6",  "ui.ascii.8,13,6",
        "ui.ascii.8,14,6",  "ui.ascii.8,15,6",  "ui.ascii.8,0,7",   "ui.ascii.8,1,7",   "ui.ascii.8,2,7",
        "ui.ascii.8,3,7",   "ui.ascii.8,4,7",   "ui.ascii.8,5,7",   "ui.ascii.8,6,7",   "ui.ascii.8,7,7",
        "ui.ascii.8,8,7",   "ui.ascii.8,9,7",   "ui.ascii.8,10,7",  "ui.ascii.8,11,7",  "ui.ascii.8,12,7",
        "ui.ascii.8,13,7",  "ui.ascii.8,14,7",  "ui.ascii.8,15,7",  "ui.ascii.8,0,8",   "ui.ascii.8,1,8",
        "ui.ascii.8,2,8",   "ui.ascii.8,3,8",   "ui.ascii.8,4,8",   "ui.ascii.8,5,8",   "ui.ascii.8,6,8",
        "ui.ascii.8,7,8",   "ui.ascii.8,8,8",   "ui.ascii.8,9,8",   "ui.ascii.8,10,8",  "ui.ascii.8,11,8",
        "ui.ascii.8,12,8",  "ui.ascii.8,13,8",  "ui.ascii.8,14,8",  "ui.ascii.8,15,8",  "ui.ascii.8,0,9",
        "ui.ascii.8,1,9",   "ui.ascii.8,2,9",   "ui.ascii.8,3,9",   "ui.ascii.8,4,9",   "ui.ascii.8,5,9",
        "ui.ascii.8,6,9",   "ui.ascii.8,7,9",   "ui.ascii.8,8,9",   "ui.ascii.8,9,9",   "ui.ascii.8,10,9",
        "ui.ascii.8,11,9",  "ui.ascii.8,12,9",  "ui.ascii.8,13,9",  "ui.ascii.8,14,9",  "ui.ascii.8,15,9",
        "ui.ascii.8,0,10",  "ui.ascii.8,1,10",  "ui.ascii.8,2,10",  "ui.ascii.8,3,10",  "ui.ascii.8,4,10",
        "ui.ascii.8,5,10",  "ui.ascii.8,6,10",  "ui.ascii.8,7,10",  "ui.ascii.8,8,10",  "ui.ascii.8,9,10",
        "ui.ascii.8,10,10", "ui.ascii.8,11,10", "ui.ascii.8,12,10", "ui.ascii.8,13,10", "ui.ascii.8,14,10",
        "ui.ascii.8,15,10", "ui.ascii.8,0,11",  "ui.ascii.8,1,11",  "ui.ascii.8,2,11",  "ui.ascii.8,3,11",
        "ui.ascii.8,4,11",  "ui.ascii.8,5,11",  "ui.ascii.8,6,11",  "ui.ascii.8,7,11",  "ui.ascii.8,8,11",
        "ui.ascii.8,9,11",  "ui.ascii.8,10,11", "ui.ascii.8,11,11", "ui.ascii.8,12,11", "ui.ascii.8,13,11",
        "ui.ascii.8,14,11", "ui.ascii.8,15,11", "ui.ascii.8,0,12",  "ui.ascii.8,1,12",  "ui.ascii.8,2,12",
        "ui.ascii.8,3,12",  "ui.ascii.8,4,12",  "ui.ascii.8,5,12",  "ui.ascii.8,6,12",  "ui.ascii.8,7,12",
        "ui.ascii.8,8,12",  "ui.ascii.8,9,12",  "ui.ascii.8,10,12", "ui.ascii.8,11,12", "ui.ascii.8,12,12",
        "ui.ascii.8,13,12", "ui.ascii.8,14,12", "ui.ascii.8,15,12", "ui.ascii.8,0,13",  "ui.ascii.8,1,13",
        "ui.ascii.8,2,13",  "ui.ascii.8,3,13",  "ui.ascii.8,4,13",  "ui.ascii.8,5,13",  "ui.ascii.8,6,13",
        "ui.ascii.8,7,13",  "ui.ascii.8,8,13",  "ui.ascii.8,9,13",  "ui.ascii.8,10,13", "ui.ascii.8,11,13",
        "ui.ascii.8,12,13", "ui.ascii.8,13,13", "ui.ascii.8,14,13", "ui.ascii.8,15,13", "ui.ascii.8,0,14",
        "ui.ascii.8,1,14",  "ui.ascii.8,2,14",  "ui.ascii.8,3,14",  "ui.ascii.8,4,14",  "ui.ascii.8,5,14",
        "ui.ascii.8,6,14",  "ui.ascii.8,7,14",  "ui.ascii.8,8,14",  "ui.ascii.8,9,14",  "ui.ascii.8,10,14",
        "ui.ascii.8,11,14", "ui.ascii.8,12,14", "ui.ascii.8,13,14", "ui.ascii.8,14,14", "ui.ascii.8,15,14",
        "ui.ascii.8,0,15",  "ui.ascii.8,1,15",  "ui.ascii.8,2,15",  "ui.ascii.8,3,15",  "ui.ascii.8,4,15",
        "ui.ascii.8,5,15",  "ui.ascii.8,6,15",  "ui.ascii.8,7,15",  "ui.ascii.8,8,15",  "ui.ascii.8,9,15",
        "ui.ascii.8,10,15", "ui.ascii.8,11,15", "ui.ascii.8,12,15", "ui.ascii.8,13,15", "ui.ascii.8,14,15",
        "ui.ascii.8,15,15",
    };
    const std::vector< std::string > arr(tiles);
    tile_load_arr("data/gfx/ui/ascii/ui_vert1.tga", "ui_ascii_box8", 8, 8, arr);
  }
}
