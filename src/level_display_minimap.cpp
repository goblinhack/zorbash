//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"

void Level::display_minimap (void)
{
    if (unlikely(!game->config.gfx_minimap)) {
        return;
    }

    float mx = UI_MINIMAP_SIZE;
    float my = mx * game->config.video_w_h_ratio;
    mx *= game->config.outer_pix_width;
    my *= game->config.outer_pix_height;
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glTranslatef(game->config.outer_pix_width - mx,
                    game->config.outer_pix_height - my, 0);
    blit_init();
    blit(fbo_tex_id[FBO_MINIMAP], 0.0, 1.0, 1.0, 0.0, 0, my, mx, 0.0);
    blit_flush();
    glPopMatrix();

    //
    // Over minimap?
    //
    auto old_minimap_over = game->minimap_over;
    if ((mouse_x >= game->config.outer_pix_width - mx) &&
        (mouse_y >= game->config.outer_pix_height - my)) {
        game->minimap_over =
            make_point(
            ((float)(mouse_x - (game->config.outer_pix_width - mx))
                / mx) * MAP_WIDTH,
            ((float)(mouse_y - (game->config.outer_pix_height - my))
                / my) * MAP_HEIGHT
            );
        fpoint to(game->minimap_over.x, game->minimap_over.y);
        if (cursor) {_
            verify(cursor);
            cursor_at = to;
            if (cursor_at != cursor_at_old) {
                cursor_at_old = to;
                cursor->move(make_fpoint(game->minimap_over));
                cursor_recreate();
            }
        }
    } else {
        game->minimap_over = point(-1, -1);
    }

    if (old_minimap_over != game->minimap_over) {
        minimap_valid = false;
    }
}
