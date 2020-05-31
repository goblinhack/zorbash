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
    last_attached = point(mx, my);

    if (is_blood())         { level->set_is_blood(mx, my); }
    if (is_chasm())         { level->set_is_chasm(mx, my); }
    if (is_corpse())        { level->set_is_corpse(mx, my); }
    if (is_corridor())      { level->set_is_corridor(mx, my); }
    if (is_deep_water())    { level->set_is_deep_water(mx, my); }
    if (is_deep_water())    { level->set_is_water(mx, my); }
    if (is_dirt())          { level->set_is_dirt(mx, my); }
    if (is_door())          { level->set_is_door(mx, my); }
    if (is_floor())         { level->set_is_floor(mx, my); }
    if (is_food())          { level->set_is_food(mx, my); }
    if (is_hazard())        { level->set_is_hazard(mx, my); }
    if (is_key())           { level->set_is_key(mx, my); }
    if (is_large())         { level->set_is_large(mx, my); }
    if (is_lava())          { level->set_is_lava(mx, my); }
    if (is_monst())         { level->set_is_monst(mx, my); }
    if (is_rock())          { level->set_is_rock(mx, my); }
    if (is_secret_door())   { level->set_is_secret_door(mx, my); }
    if (is_wall())          { level->set_is_wall(mx, my); }
    if (is_water())         { level->set_is_water(mx, my); }

    if (is_lava() || is_fire()) { level->heatmap_valid = false; }
}

void Thing::detach (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;

    auto mx = (int16_t)(int)last_attached.x;
    auto my = (int16_t)(int)last_attached.y;

    if (is_blood())         { level->unset_is_blood(mx, my); }
    if (is_chasm())         { level->unset_is_chasm(mx, my); }
    if (is_corpse())        { level->unset_is_corpse(mx, my); }
    if (is_corridor())      { level->unset_is_corridor(mx, my); }
    if (is_deep_water())    { level->unset_is_deep_water(mx, my); }
    if (is_deep_water())    { level->unset_is_water(mx, my); }
    if (is_dirt())          { level->unset_is_dirt(mx, my); }
    if (is_door())          { level->unset_is_door(mx, my); }
    if (is_floor())         { level->unset_is_floor(mx, my); }
    if (is_food())          { level->unset_is_food(mx, my); }
    if (is_hazard())        { level->unset_is_hazard(mx, my); }
    if (is_key())           { level->unset_is_key(mx, my); }
    if (is_large())         { level->unset_is_large(mx, my); }
    if (is_lava())          { level->unset_is_lava(mx, my); }
    if (is_monst())         { level->unset_is_monst(mx, my); }
    if (is_rock())          { level->unset_is_rock(mx, my); }
    if (is_secret_door())   { level->unset_is_secret_door(mx, my); }
    if (is_wall())          { level->unset_is_wall(mx, my); }
    if (is_water())         { level->unset_is_water(mx, my); }

    if (is_deep_water()) {
        level->unset_is_water(mx, my);
        level->unset_is_deep_water(mx, my);
    }

    level->remove_thing((int)last_attached.x, (int)last_attached.y, id);

    if (is_lava() || is_fire()) { level->heatmap_valid = false; }
}










