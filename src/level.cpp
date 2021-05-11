//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_array_bounds_check.h"

std::string Level::to_string (void)
{_
    return ("L" + world_at.to_string());
}

uint8_t Level::is_lava (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_lava, p.x, p.y));
}

uint8_t Level::is_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_lava, x, y));
}

void Level::set_is_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_lava, x, y, (uint8_t)1);
}

void Level::unset_is_lava (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_lava, x, y, (uint8_t)1);
}

uint8_t Level::is_acid (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_acid, p.x, p.y));
}

uint8_t Level::is_acid (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_acid, x, y));
}

void Level::set_is_acid (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_acid, x, y, (uint8_t)1);
}

void Level::unset_is_acid (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_acid, x, y, (uint8_t)1);
}

uint8_t Level::is_poison (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_poison, p.x, p.y));
}

uint8_t Level::is_poison (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_poison, x, y));
}

void Level::set_is_poison (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_poison, x, y, (uint8_t)1);
}

void Level::unset_is_poison (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_poison, x, y, (uint8_t)1);
}

uint8_t Level::is_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_chasm, x, y));
}

uint8_t Level::is_chasm (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_chasm, p.x, p.y));
}

void Level::set_is_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_chasm, x, y, (uint8_t)1);
}

void Level::unset_is_chasm (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_chasm, x, y, (uint8_t)1);
}

uint8_t Level::is_hazard (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_hazard, p.x, p.y));
}

uint8_t Level::is_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_hazard, x, y));
}

void Level::set_is_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_hazard, x, y, (uint8_t)1);
}

void Level::unset_is_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_hazard, x, y, (uint8_t)1);
}

uint8_t Level::is_extreme_hazard (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_extreme_hazard, p.x, p.y));
}

uint8_t Level::is_extreme_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_extreme_hazard, x, y));
}

void Level::set_is_extreme_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_extreme_hazard, x, y, (uint8_t)1);
}

void Level::unset_is_extreme_hazard (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_extreme_hazard, x, y, (uint8_t)1);
}

uint8_t Level::is_secret_door (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_secret_door, p.x, p.y));
}

uint8_t Level::is_secret_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_secret_door, x, y));
}

void Level::set_is_secret_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_secret_door, x, y, (uint8_t)1);
}

void Level::unset_is_secret_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_secret_door, x, y, (uint8_t)1);
}

uint8_t Level::is_ripple (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_ripple, p.x, p.y));
}

uint8_t Level::is_ripple (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_ripple, x, y));
}

void Level::set_is_ripple (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_ripple, x, y, (uint8_t)1);
}

void Level::unset_is_ripple (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_ripple, x, y, (uint8_t)1);
}

uint8_t Level::is_brazier (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_brazier, p.x, p.y));
}

uint8_t Level::is_brazier (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_brazier, x, y));
}

void Level::set_is_brazier (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_brazier, x, y, (uint8_t)1);
}

void Level::unset_is_brazier (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_brazier, x, y, (uint8_t)1);
}

uint8_t Level::is_barrel (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_barrel, p.x, p.y));
}

uint8_t Level::is_barrel (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_barrel, x, y));
}

void Level::set_is_barrel (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_barrel, x, y, (uint8_t)1);
}

void Level::unset_is_barrel (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_barrel, x, y, (uint8_t)1);
}

uint8_t Level::is_minion_generator (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_minion_generator, p.x, p.y));
}

uint8_t Level::is_minion_generator (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_minion_generator, x, y));
}

void Level::set_is_minion_generator (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_minion_generator, x, y, (uint8_t)1);
}

void Level::unset_is_minion_generator (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_minion_generator, x, y, (uint8_t)1);
}

uint8_t Level::is_potion (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_potion, p.x, p.y));
}

uint8_t Level::is_potion (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_potion, x, y));
}

void Level::set_is_potion (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_potion, x, y, (uint8_t)1);
}

void Level::unset_is_potion (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_potion, x, y, (uint8_t)1);
}

uint8_t Level::is_wand (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_wand, p.x, p.y));
}

uint8_t Level::is_wand (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_wand, x, y));
}

void Level::set_is_wand (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_wand, x, y, (uint8_t)1);
}

void Level::unset_is_wand (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_wand, x, y, (uint8_t)1);
}

uint8_t Level::is_blood (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_blood, p.x, p.y));
}

uint8_t Level::is_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_blood, x, y));
}

void Level::set_is_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_blood, x, y, (uint8_t)1);
}

void Level::unset_is_blood (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_blood, x, y, (uint8_t)1);
}

uint8_t Level::gfx_water (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_gfx_water, p.x, p.y));
}

uint8_t Level::gfx_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_gfx_water, x, y));
}

void Level::set_gfx_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_gfx_water, x, y, (uint8_t)1);
}

void Level::unset_gfx_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_gfx_water, x, y, (uint8_t)1);
}

uint8_t Level::is_deep_water (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_deep_water, p.x, p.y));
}

uint8_t Level::is_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_deep_water, x, y));
}

void Level::set_is_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_deep_water, x, y, (uint8_t)1);
}

void Level::unset_is_deep_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_deep_water, x, y, (uint8_t)1);
}

uint8_t Level::is_shallow_water (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_shallow_water, p.x, p.y));
}

uint8_t Level::is_shallow_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_shallow_water, x, y));
}

void Level::set_is_shallow_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_shallow_water, x, y, (uint8_t)1);
}

void Level::unset_is_shallow_water (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_shallow_water, x, y, (uint8_t)1);
}

uint8_t Level::is_water (const point &p)
{_
    return is_shallow_water(p) || is_deep_water(p);
}

uint8_t Level::is_water (const int x, const int y)
{_
    return is_shallow_water(x, y) || is_deep_water(x, y);
}

uint8_t Level::is_wall (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_wall, p.x, p.y));
}

uint8_t Level::is_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_wall, x, y));
}

void Level::set_is_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_wall, x, y, (uint8_t)1);
}

void Level::unset_is_wall (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_wall, x, y, (uint8_t)1);
}

uint8_t Level::is_corridor (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_corridor, p.x, p.y));
}

uint8_t Level::is_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_corridor, x, y));
}

void Level::set_is_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_corridor, x, y, (uint8_t)1);
}

void Level::unset_is_corridor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_corridor, x, y, (uint8_t)1);
}

uint8_t Level::is_bridge (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_bridge, p.x, p.y));
}

uint8_t Level::is_bridge (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_bridge, x, y));
}

void Level::set_is_bridge (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_bridge, x, y, (uint8_t)1);
}

void Level::unset_is_bridge (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_bridge, x, y, (uint8_t)1);
}

uint8_t Level::is_dirt (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dirt, p.x, p.y));
}

uint8_t Level::is_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dirt, x, y));
}

void Level::set_is_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_dirt, x, y, (uint8_t)1);
}

void Level::unset_is_dirt (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_dirt, x, y, (uint8_t)1);
}

uint8_t Level::is_dry_fungus (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dry_fungus, p.x, p.y));
}

uint8_t Level::is_dry_fungus (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dry_fungus, x, y));
}

void Level::set_is_dry_fungus (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_dry_fungus, x, y, (uint8_t)1);
}

void Level::unset_is_dry_fungus (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_dry_fungus, x, y, (uint8_t)1);
}

uint8_t Level::is_enchantstone (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_enchantstone, p.x, p.y));
}

uint8_t Level::is_enchantstone (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_enchantstone, x, y));
}

void Level::set_is_enchantstone (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_enchantstone, x, y, (uint8_t)1);
}

void Level::unset_is_enchantstone (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_enchantstone, x, y, (uint8_t)1);
}

uint8_t Level::is_skillstone (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_skillstone, p.x, p.y));
}

uint8_t Level::is_skillstone (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_skillstone, x, y));
}

void Level::set_is_skillstone (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_skillstone, x, y, (uint8_t)1);
}

void Level::unset_is_skillstone (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_skillstone, x, y, (uint8_t)1);
}

uint8_t Level::is_foilage (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_foilage, p.x, p.y));
}

uint8_t Level::is_foilage (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_foilage, x, y));
}

void Level::set_is_foilage (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_foilage, x, y, (uint8_t)1);
}

void Level::unset_is_foilage (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_foilage, x, y, (uint8_t)1);
}

uint8_t Level::is_spiderweb (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_spiderweb, p.x, p.y));
}

uint8_t Level::is_spiderweb (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_spiderweb, x, y));
}

void Level::set_is_spiderweb (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_spiderweb, x, y, (uint8_t)1);
}

void Level::unset_is_spiderweb (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_spiderweb, x, y, (uint8_t)1);
}

uint8_t Level::is_sticky (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_sticky, p.x, p.y));
}

uint8_t Level::is_sticky (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_sticky, x, y));
}

void Level::set_is_sticky (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_sticky, x, y, (uint8_t)1);
}

void Level::unset_is_sticky (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_sticky, x, y, (uint8_t)1);
}

uint8_t Level::is_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_floor, x, y));
}

void Level::set_is_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_floor, x, y, (uint8_t)1);
}

void Level::unset_is_floor (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_floor, x, y, (uint8_t)1);
}

uint8_t Level::is_rock (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_rock, p.x, p.y));
}

uint8_t Level::is_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_rock, x, y));
}

void Level::set_is_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_rock, x, y, (uint8_t)1);
}

void Level::unset_is_rock (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_rock, x, y, (uint8_t)1);
}

uint8_t Level::is_dungeon (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_dungeon, p.x, p.y));
}

uint8_t Level::is_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_dungeon, x, y));
}

void Level::set_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    incr(_is_dungeon, x, y, (uint8_t)1);
}

void Level::unset_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    map_changed = true;
    decr(_is_dungeon, x, y, (uint8_t)1);
}

uint8_t Level::is_corpse (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_corpse, p.x, p.y));
}

uint8_t Level::is_corpse (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_corpse, x, y));
}

void Level::set_is_corpse (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_corpse, x, y, (uint8_t)1);
}

void Level::unset_is_corpse (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_corpse, x, y, (uint8_t)1);
}

uint8_t Level::is_fire (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_fire, p.x, p.y));
}

uint8_t Level::is_fire (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_fire, x, y));
}

void Level::set_is_fire (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_fire, x, y, (uint8_t)1);
}

void Level::unset_is_fire (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_fire, x, y, (uint8_t)1);
}

uint8_t Level::is_monst (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_monst, p.x, p.y));
}

uint8_t Level::is_monst (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_monst, x, y));
}

void Level::set_is_monst (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_monst, x, y, (uint8_t)1);
}

void Level::unset_is_monst (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_monst, x, y, (uint8_t)1);
}

uint8_t Level::is_door (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_door, p.x, p.y));
}

uint8_t Level::is_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_door, x, y));
}

void Level::set_is_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_door, x, y, (uint8_t)1);
}

void Level::unset_is_door (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_door, x, y, (uint8_t)1);
}

uint8_t Level::is_key (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_key, p.x, p.y));
}

uint8_t Level::is_key (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_key, x, y));
}

void Level::set_is_key (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_key, x, y, (uint8_t)1);
}

void Level::unset_is_key (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_key, x, y, (uint8_t)1);
}

uint8_t Level::is_food (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_food, p.x, p.y));
}

uint8_t Level::is_food (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_food, x, y));
}

void Level::set_is_food (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_food, x, y, (uint8_t)1);
}

void Level::unset_is_food (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_food, x, y, (uint8_t)1);
}

uint8_t Level::is_treasure (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_treasure, p.x, p.y));
}

uint8_t Level::is_treasure (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_treasure, x, y));
}

void Level::set_is_treasure (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_treasure, x, y, (uint8_t)1);
}

void Level::unset_is_treasure (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_treasure, x, y, (uint8_t)1);
}

uint8_t Level::is_treasure_class_a (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_treasure_class_a, p.x, p.y));
}

uint8_t Level::is_treasure_class_a (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_treasure_class_a, x, y));
}

void Level::set_is_treasure_class_a (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_treasure_class_a, x, y, (uint8_t)1);
}

void Level::unset_is_treasure_class_a (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_treasure_class_a, x, y, (uint8_t)1);
}

uint8_t Level::is_treasure_class_b (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_treasure_class_b, p.x, p.y));
}

uint8_t Level::is_treasure_class_b (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_treasure_class_b, x, y));
}

void Level::set_is_treasure_class_b (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_treasure_class_b, x, y, (uint8_t)1);
}

void Level::unset_is_treasure_class_b (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_treasure_class_b, x, y, (uint8_t)1);
}

uint8_t Level::is_treasure_class_c (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_treasure_class_c, p.x, p.y));
}

uint8_t Level::is_treasure_class_c (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_treasure_class_c, x, y));
}

void Level::set_is_treasure_class_c (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_treasure_class_c, x, y, (uint8_t)1);
}

void Level::unset_is_treasure_class_c (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_treasure_class_c, x, y, (uint8_t)1);
}

uint8_t Level::is_gold (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_gold, p.x, p.y));
}

uint8_t Level::is_gold (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_gold, x, y));
}

void Level::set_is_gold (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_gold, x, y, (uint8_t)1);
}

void Level::unset_is_gold (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_gold, x, y, (uint8_t)1);
}

uint8_t Level::is_ascend_dungeon (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_ascend_dungeon, p.x, p.y));
}

uint8_t Level::is_ascend_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_ascend_dungeon, x, y));
}

void Level::set_is_ascend_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_ascend_dungeon, x, y, (uint8_t)1);
}

void Level::unset_is_ascend_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_ascend_dungeon, x, y, (uint8_t)1);
}

uint8_t Level::is_descend_dungeon (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_descend_dungeon, p.x, p.y));
}

uint8_t Level::is_descend_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_descend_dungeon, x, y));
}

void Level::set_is_descend_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_descend_dungeon, x, y, (uint8_t)1);
}

void Level::unset_is_descend_dungeon (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_descend_dungeon, x, y, (uint8_t)1);
}

uint8_t Level::is_ascend_sewer (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_ascend_sewer, p.x, p.y));
}

uint8_t Level::is_ascend_sewer (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_ascend_sewer, x, y));
}

void Level::set_is_ascend_sewer (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_ascend_sewer, x, y, (uint8_t)1);
}

void Level::unset_is_ascend_sewer (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_ascend_sewer, x, y, (uint8_t)1);
}

uint8_t Level::is_descend_sewer (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_descend_sewer, p.x, p.y));
}

uint8_t Level::is_descend_sewer (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_descend_sewer, x, y));
}

void Level::set_is_descend_sewer (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_descend_sewer, x, y, (uint8_t)1);
}

void Level::unset_is_descend_sewer (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_descend_sewer, x, y, (uint8_t)1);
}

uint8_t Level::is_smoke (const point &p)
{_
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_smoke, p.x, p.y));
}

uint8_t Level::is_smoke (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_smoke, x, y));
}

void Level::set_is_smoke (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    incr(_is_smoke, x, y, (uint8_t)1);
}

void Level::unset_is_smoke (const int x, const int y)
{_
    if (unlikely(is_oob(x, y))) {
        return;
    }
    decr(_is_smoke, x, y, (uint8_t)1);
}

//
// Used in lighting, so inlined
//
bool Level::is_oob (const int x, const int y, const int z) const
{
    return ((x < 0) || (x >= MAP_WIDTH) ||
            (y < 0) || (y >= MAP_HEIGHT) ||
            (z < 0) || (z >= MAP_DEPTH));
}

bool Level::is_oob (const int x, const int y) const
{
    return ((x < 0) || (x >= MAP_WIDTH) ||
            (y < 0) || (y >= MAP_HEIGHT));
}

bool Level::is_oob (const fpoint p) const
{
    return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
            (p.y < 0) || (p.y >= MAP_HEIGHT));
}

bool Level::is_oob (const point p) const
{
    return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
            (p.y < 0) || (p.y >= MAP_HEIGHT));
}

uint8_t Level::fade_in_map (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_fade_in_map, p.x, p.y));
}

uint8_t Level::fade_in_map_no_check (const point &p)
{
    return (get_no_check(_fade_in_map, p.x, p.y));
}

uint8_t Level::fade_in_map (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_fade_in_map, x, y));
}

uint8_t Level::fade_in_map_no_check (const int x, const int y)
{
    return (get_no_check(_fade_in_map, x, y));
}

void Level::incr_fade_in (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    auto v = get(_fade_in_map, x, y);
    if (v < 255) {
        v+=1;
        set(_fade_in_map, x, y, v);
    } else {
        set(_fade_in_map, x, y, (uint8_t)255);
    }
}

void Level::incr_fade_in_no_check (const int x, const int y)
{
    auto v = get_no_check(_fade_in_map, x, y);
    if (v < 255) {
        v+=1;
        set_no_check(_fade_in_map, x, y, v);
    } else {
        set(_fade_in_map, x, y, (uint8_t)255);
    }
}

void Level::unset_fade_in (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_fade_in_map, x, y, (uint8_t)0);
}

void Level::unset_fade_in_no_check (const int x, const int y)
{
    set_no_check(_fade_in_map, x, y, (uint8_t)0);
}

uint8_t Level::is_visited (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_visited, p.x, p.y));
}

uint8_t Level::is_visited_no_check (const point &p)
{
    return (get_no_check(_is_visited, p.x, p.y));
}

uint8_t Level::is_visited (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_visited, x, y));
}

uint8_t Level::is_visited_no_check (const int x, const int y)
{
    return (get_no_check(_is_visited, x, y));
}

void Level::set_visited (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }

    if (!get(_is_visited, x, y)) {
        set(_fade_in_map, x, y, (uint8_t)1);
    }
}

void Level::set_visited_no_check (const int x, const int y)
{
    if (!get_no_check(_is_visited, x, y)) {
        set_no_check(_fade_in_map, x, y, (uint8_t)1);
    }
    set_no_check(_is_visited, x, y, true);
}

void Level::unset_visited (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_visited, x, y, false);
}

void Level::unset_visited_no_check (const int x, const int y)
{
    set_no_check(_is_visited, x, y, false);
}

//
// Used in lighting, so inlined
//
bool Level::is_light_blocker (const point &p) const
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_light_blocker, p.x, p.y));
}

bool Level::is_light_blocker_no_check (const point &p) const
{
    return (get_no_check(_is_light_blocker, p.x, p.y));
}

bool Level::is_light_blocker (const int x, const int y) const
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_light_blocker, x, y));
}

bool Level::is_light_blocker_no_check (const int x, const int y) const
{
    return (get_no_check(_is_light_blocker, x, y));
}

void Level::set_is_light_blocker (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_light_blocker, x, y, true);
}

void Level::set_is_light_blocker_no_check (const int x, const int y)
{
    set_no_check(_is_light_blocker, x, y, true);
}

void Level::unset_is_light_blocker (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_light_blocker, x, y, false);
}

void Level::unset_is_light_blocker_no_check (const int x, const int y)
{
    set_no_check(_is_light_blocker, x, y, false);
}

//
// Used in lighting, so inlined
//
bool Level::is_movement_blocking_hard (const point &p) const
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_movement_blocking_hard, p.x, p.y));
}

bool Level::is_movement_blocking_hard_no_check (const point &p) const
{
    return (get_no_check(_is_movement_blocking_hard, p.x, p.y));
}

bool Level::is_movement_blocking_hard (const int x, const int y) const
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_movement_blocking_hard, x, y));
}

bool Level::is_movement_blocking_hard_no_check (const int x, const int y) const
{
    return (get_no_check(_is_movement_blocking_hard, x, y));
}

void Level::set_is_movement_blocking_hard (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_movement_blocking_hard, x, y, true);
}

void Level::set_is_movement_blocking_hard_no_check (const int x, const int y)
{
    set_no_check(_is_movement_blocking_hard, x, y, true);
}

void Level::unset_is_movement_blocking_hard (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_movement_blocking_hard, x, y, false);
}

void Level::unset_is_movement_blocking_hard_no_check (const int x, const int y)
{
    set_no_check(_is_movement_blocking_hard, x, y, false);
}

//
// Used in lighting, so inlined
//
bool Level::is_movement_blocking_soft (const point &p) const
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_movement_blocking_soft, p.x, p.y));
}

bool Level::is_movement_blocking_soft_no_check (const point &p) const
{
    return (get_no_check(_is_movement_blocking_soft, p.x, p.y));
}

bool Level::is_movement_blocking_soft (const int x, const int y) const
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_movement_blocking_soft, x, y));
}

bool Level::is_movement_blocking_soft_no_check (const int x, const int y) const
{
    return (get_no_check(_is_movement_blocking_soft, x, y));
}

void Level::set_is_movement_blocking_soft (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_movement_blocking_soft, x, y, true);
}

void Level::set_is_movement_blocking_soft_no_check (const int x, const int y)
{
    set_no_check(_is_movement_blocking_soft, x, y, true);
}

void Level::unset_is_movement_blocking_soft (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_movement_blocking_soft, x, y, false);
}

void Level::unset_is_movement_blocking_soft_no_check (const int x, const int y)
{
    set_no_check(_is_movement_blocking_soft, x, y, false);
}

uint8_t Level::is_lit (const point &p)
{
    if (unlikely(is_oob(p.x, p.y))) {
        return (false);
    }
    return (get(_is_lit, p.x, p.y));
}

uint8_t Level::is_lit_no_check (const point &p)
{
    return (get_no_check(_is_lit, p.x, p.y));
}

uint8_t Level::is_lit (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return (false);
    }
    return (get(_is_lit, x, y));
}

uint8_t Level::is_lit_no_check (const int x, const int y)
{
    return (get_no_check(_is_lit, x, y));
}

void Level::set_is_lit_no_check (const int x, const int y)
{
    auto l = getptr_no_check(_is_lit, x, y);
    if (*l == 0) {
        *l = 255;
    } else if (*l < 255) {
        (*l)++;
    }
}

void Level::set_is_lit (const int x, const int y)
{
    auto l = getptr(_is_lit, x, y);
    if (*l == 0) {
        *l = 255;
    } else if (*l < 255) {
        (*l)++;
    }
}

void Level::set_is_lit_no_check (const int x, const int y, uint8_t v)
{
    set_no_check(_is_lit, x, y, v);
}

void Level::unset_is_lit (const int x, const int y)
{
    if (unlikely(is_oob(x, y))) {
        return;
    }
    set(_is_lit, x, y, (uint8_t)0);
}

void Level::unset_is_lit_no_check (const int x, const int y)
{
    set_no_check(_is_lit, x, y, (uint8_t)0);
}
