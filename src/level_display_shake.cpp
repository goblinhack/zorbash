//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_gl.h"
#include "my_thing.h"

float Level::update_wobble (void)
{
    auto w = get_wobble();
    if (w == 0.0) {
        return 0.0;
    }

    if (fabs(w) < 0.01) {
        return 0.0;
    }

    auto new_w = w;
    new_w *= 0.75;
    new_w = -new_w;
    set_wobble(new_w);

    return (w);
}

float Level::get_wobble (void) const
{_
    return (wobble);
}

void Level::set_wobble (float v)
{_
    wobble = v;
}

bool Level::screen_shake_begin (void)
{_
    if (!player || !player->is_bloodied()) {
        return false;
    }

    auto wobble = update_wobble();
    if (wobble != 0.0) {
        glPushMatrix();
        glTranslatef(-game->config.inner_pix_width / 2,
                     -game->config.inner_pix_height / 2, 0);
        glRotatef(wobble * 5, 0.0f, 0.0f, 1.0f);
        glTranslatef(game->config.inner_pix_width / 2,
                     game->config.inner_pix_height / 2, 0);
        return true;
    }
    return false;
}

void Level::screen_shake_end (void)
{_
    glPopMatrix();
}
