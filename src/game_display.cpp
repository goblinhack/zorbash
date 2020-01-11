//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

void Game::update_minimap (void)
{_
    thing_render_minimap();
}

void Game::display (void)
{_
    if (!game->world.minimap_valid) {
        thing_render_minimap();
    }

    blit_fbo_bind(FBO_MAIN);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    // thing_render_all must come before thing_move_all as it populates
    // all the things into the map for collisions.
    //
    thing_render_all();
    blit_fbo_unbind();

    thing_gc();
}
