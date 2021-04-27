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
#include "my_thing_template.h"

void Level::display_target (void)
{_
    auto what = game->request_to_fire_item;
    if (!what) {
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

    glPushAttrib(GL_ENABLE_BIT); 
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo_bind(FBO_MAP_VISIBLE);
    glLineWidth(1.0);

    auto mid_at = cursor->mid_at;
    bool too_far = false;
    if (DISTANCE(player->mid_at.x, player->mid_at.y, mid_at.x, mid_at.y) >
        what->tp()->range_max()) {
        too_far = true;
    }

    if (too_far) {
        glcolor(GRAY50);
    } else {
        glcolor(RED);
    }

    glDisable(GL_TEXTURE_2D);
    gl_blitline(start.x, start.y, end.x, end.y);
    glEnable(GL_TEXTURE_2D);
    glcolor(WHITE);

    glPopAttrib();
}
