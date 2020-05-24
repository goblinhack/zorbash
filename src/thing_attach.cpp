//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"

void Thing::attach (void)
{_
    detach();
    level->put_thing((int)mid_at.x, (int)mid_at.y, id);
    auto mx = (int16_t)(int)mid_at.x;
    auto my = (int16_t)(int)mid_at.y;
    is_attached = true;
    last_attached = spoint(mx, my);

    if (is_wall()) {
        level->set_wall(mx, my);
    }
    if (is_floor()) {
        level->set_floor(mx, my);
    }
    if (is_hazard()) {
        level->set_hazard(mx, my);
    }
    if (is_secret_door()) {
        level->set_secret_door(mx, my);
    }
    if (is_corpse()) {
        level->set_corpse(mx, my);
    }
    if (is_lava()) {
        level->set_lava(mx, my);
    }
    if (is_chasm()) {
        level->set_chasm(mx, my);
    }
    if (is_blood()) {
        level->set_blood(mx, my);
    }
    if (is_water()) {
        level->set_water(mx, my);
    }
    if (is_deep_water()) {
        level->set_water(mx, my);
        level->set_deep_water(mx, my);
    }
    if (is_corridor()) {
        level->set_corridor(mx, my);
    }
    if (is_dirt()) {
        level->set_dirt(mx, my);
    }
    if (gfx_large_shadow()) {
        level->set_gfx_large_shadow(mx, my);
    }
}

void Thing::detach (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;

    auto mx = (int16_t)(int)last_attached.x;
    auto my = (int16_t)(int)last_attached.y;

    if (is_wall()) {
        level->unset_wall(mx, my);
    }
    if (is_floor()) {
        level->unset_floor(mx, my);
    }
    if (is_hazard()) {
        level->unset_hazard(mx, my);
    }
    if (is_secret_door()) {
        level->unset_secret_door(mx, my);
    }
    if (is_corpse()) {
        level->unset_corpse(mx, my);
    }
    if (is_lava()) {
        level->unset_lava(mx, my);
    }
    if (is_chasm()) {
        level->unset_chasm(mx, my);
    }
    if (is_blood()) {
        level->unset_blood(mx, my);
    }
    if (is_water()) {
        level->unset_water(mx, my);
    }
    if (is_deep_water()) {
        level->unset_water(mx, my);
        level->unset_deep_water(mx, my);
    }
    if (is_corridor()) {
        level->unset_corridor(mx, my);
    }
    if (is_dirt()) {
        level->unset_dirt(mx, my);
    }
    if (gfx_large_shadow()) {
        level->unset_gfx_large_shadow(mx, my);
    }

    level->remove_thing((int)last_attached.x, (int)last_attached.y, id);
}
