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

//
// New or loaded level
//
void Level::update_new_level (void)
{_
    minimap_valid = false;
    heatmap_valid = false;

    scroll_map_to_player_immediately();
    lights_update_new_level();
    player_dmap_update();

    //
    // Load what we were able to see previously
    //
    sdl_fbo_load(FBO_FULLMAP_LIGHT, fbo_light);
}

//
// Something changed on the level
//
void Level::update_same_level (void)
{_
    minimap_valid = false;
    heatmap_valid = false;

    lights_update_same_level();
    player_dmap_update();
}

// 
// For example, a zoom change
//
void Level::update_same_level_immediately (void)
{_
    minimap_valid = false;
    heatmap_valid = false;

    scroll_map_to_player_immediately();
    lights_update_new_level();
    player_dmap_update();
}
