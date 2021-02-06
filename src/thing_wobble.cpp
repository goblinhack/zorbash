//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::wobble (float wobble)
{
    set_wobble(wobble);
}

float Thing::update_wobble (void)
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
