//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"

int Thing::get_danger_level (void)
{_
    int danger_level = 0;

    danger_level = get_health() / 10;

    if (is_resurrectable()) {
        danger_level *= 2;
    }
    if (attack_shove()) {
        danger_level ++;
    }
    if (is_carrying_item()) {
        danger_level ++;
    }
    if (is_acid()) {
        danger_level ++;
    }
    if (is_poison()) {
        danger_level ++;
    }
    if (is_fire()) {
        danger_level ++;
    }
    if (is_lava()) {
        danger_level ++;
    }
    if (is_floating()) {
        danger_level += 2;
    }
    if (is_jumper()) {
        danger_level += 2;
    }
    if (is_item_eater()) {
        danger_level += 20;
    }

    danger_level += get_damage_melee_dice().max_roll();

    // minicon("level %d", danger_level);
    return danger_level;
}

int Thing::is_dangerous(Thingp it)
{
    if (is_fearless()) {
        return false;
    }

    int a = get_danger_level();
    int b = it->get_danger_level();

    //
    // So giant rats will attack each other if at the same danger level
    //
    return b > a;
}

std::string Thing::get_danger_level(Thingp it)
{
    auto a = get_danger_level();
    auto b = it->get_danger_level();
    auto delta = b - a;

    if (delta > 20) {
        return "%%fg=red$Deadly. Avoid!";
    } else if (delta > 10) {
        return "%%fg=red$Dangerous";
    } else if (delta >= 0) {
        return "%%fg=orange$Caution advised";
    } else if (delta <= -10) {
        return "%%fg=green$Harmless";
    } else {
        return "%%fg=green$Mostly harmless";
    }
}
