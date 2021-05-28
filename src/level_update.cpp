//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_sdl.h"
#include "my_gl.h"

void Level::update_new_level (void)
{_
    minimap_valid = false;
    heatmap_valid = false;

    lights_update_new_level();
    scroll_map_to_player();
    player_dmap_update();
    sdl_fbo_load(FBO_FULLMAP_LIGHT, fbo_light);
}

void Level::update_same_level (void)
{_
    minimap_valid = false;
    heatmap_valid = false;

    lights_update_same_level();
    player_dmap_update();
}
