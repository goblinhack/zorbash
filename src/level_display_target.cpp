//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"

void Level::display_target (void)
{_
    if (!game->request_to_laser_item) {
        return;
    }

    if (!cursor) {
        return;
    }

    if (!player) {
        return;
    }

    auto start = player->last_blit_at;
    auto end = cursor->last_blit_at;

    if (!start.x && !start.y) {
        return;
    }
    if (!end.x && !end.y) {
        return;
    }

    start -= pixel_map_at;
    end -= pixel_map_at;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo_bind(FBO_MAP_VISIBLE);
    glLineWidth(5.0);
    glcolor(RED);
    glDisable(GL_TEXTURE_2D);
    gl_blitline(start.x, start.y, end.x, end.y);
    glEnable(GL_TEXTURE_2D);
    glcolor(WHITE);
}
