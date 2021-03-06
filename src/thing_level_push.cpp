//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_gl.h"

//
// push/pop are for things moving on the same level
//
void Thing::level_push (void)
{_
    level_pop();

    level->put_thing((int)mid_at.x, (int)mid_at.y, id);
    auto mx = (int16_t)(int)mid_at.x;
    auto my = (int16_t)(int)mid_at.y;
    is_attached = true;
    last_attached = point(mx, my);

#if 0
    if (is_torch()) {
        con("push at %d,%d", last_attached.x, last_attached.y);
    }
#endif

    if (is_acid())                               { i_set_is_acid = true;
                                                   level->set_is_acid(mx, my); }
    if (is_poison())                             { i_set_is_poison = true;
                                                   level->set_is_poison(mx, my); }
    if (is_blood())                              { i_set_is_blood = true;
                                                   level->set_is_blood(mx, my); }
    if (is_chasm())                              { i_set_is_chasm = true;
                                                   level->set_is_chasm(mx, my); }
    if (is_corpse())                             { i_set_is_corpse = true;
                                                   level->set_is_corpse(mx, my); }
    if (is_corridor())                           { i_set_is_corridor = true;
                                                   level->set_is_corridor(mx, my); }
    if (is_bridge())                             { i_set_is_bridge = true;
                                                   level->set_is_bridge(mx, my); }
    if (is_dirt())                               { i_set_is_dirt = true;
                                                   level->set_is_dirt(mx, my); }
    if (is_dry_grass())                          { i_set_is_dry_grass = true;
                                                   level->set_is_dry_grass(mx, my); }
    if (is_enchantstone())                       { i_set_is_enchantstone = true;
                                                   level->set_is_enchantstone(mx, my); }
    if (is_skillstone())                         { i_set_is_skillstone = true;
                                                   level->set_is_skillstone(mx, my); }
    if (is_foilage())                            { i_set_is_foilage = true;
                                                   level->set_is_foilage(mx, my); }
    if (is_spiderweb())                          { i_set_is_spiderweb = true;
                                                   level->set_is_spiderweb(mx, my); }
    if (is_sticky())                             { i_set_is_sticky = true;
                                                   level->set_is_sticky(mx, my); }
    if (is_door() && !is_open)                   { i_set_is_door = true;
                                                   level->set_is_door(mx, my); }
    if (is_ascend_dungeon())                     { i_set_is_ascend_dungeon = true;
                                                   level->set_is_ascend_dungeon(mx, my); }
    if (is_descend_dungeon())                    { i_set_is_descend_dungeon = true;
                                                   level->set_is_descend_dungeon(mx, my); }
    if (is_ascend_sewer())                       { i_set_is_ascend_sewer = true;
                                                   level->set_is_ascend_sewer(mx, my); }
    if (is_descend_sewer())                      { i_set_is_descend_sewer = true;
                                                   level->set_is_descend_sewer(mx, my); }
    if (is_fire() && !is_dead)                   { i_set_is_fire = true;
                                                   level->set_is_fire(mx, my); }
    if (is_floor())                              { i_set_is_floor = true;
                                                   level->set_is_floor(mx, my); }
    if (is_food())                               { i_set_is_food = true;
                                                   level->set_is_food(mx, my); }
    if (is_minion_generator())                   { i_set_is_minion_generator = true;
                                                   level->set_is_minion_generator(mx, my); }
    if (is_gold())                               { i_set_is_gold = true;
                                                   level->set_is_gold(mx, my); }
    if (is_hazard())                             { i_set_is_hazard = true;
                                                   level->set_is_hazard(mx, my); }
    if (is_extreme_hazard())                     { i_set_is_extreme_hazard = true;
                                                   level->set_is_extreme_hazard(mx, my); }
    if (is_treasure_class_a())                   { i_set_is_treasure_class_a = true;
                                                   level->set_is_treasure_class_a(mx, my); }
    if (is_treasure_class_b())                   { i_set_is_treasure_class_b = true;
                                                   level->set_is_treasure_class_b(mx, my); }
    if (is_treasure_class_c())                   { i_set_is_treasure_class_c = true;
                                                   level->set_is_treasure_class_c(mx, my); }
    if (is_key())                                { i_set_is_key = true;
                                                   level->set_is_key(mx, my); }
    if (is_lava())                               { i_set_is_lava = true;
                                                   level->set_is_lava(mx, my); }
    if (is_light_blocker() && !is_open && !is_dead) {
                                                   i_set_is_light_blocker = true;
                                                   level->set_is_light_blocker(mx, my); }
    if (is_monst())                              { i_set_is_monst = true;
                                                   level->set_is_monst(mx, my); }
    if (is_movement_blocking_hard() && !is_open && !is_dead) {
                                                   i_set_is_movement_blocking_hard = true;
                                                   level->set_is_movement_blocking_hard(mx, my); }
    if (is_movement_blocking_soft() && !is_open && !is_dead) {
                                                   i_set_is_movement_blocking_soft = true;
                                                   level->set_is_movement_blocking_soft(mx, my); }
    if (is_potion())                             { i_set_is_potion = true;
                                                   level->set_is_potion(mx, my); }
    if (is_wand())                               { i_set_is_wand = true;
                                                   level->set_is_wand(mx, my); }
    if (is_ripple())                             { i_set_is_ripple = true;
                                                   level->set_is_ripple(mx, my); }
    if (is_rock())                               { i_set_is_rock = true;
                                                   level->set_is_rock(mx, my); }
    if (is_secret_door())                        { i_set_is_secret_door = true;
                                                   level->set_is_secret_door(mx, my); }
    if (is_smoke())                              { i_set_is_smoke = true;
                                                   level->set_is_smoke(mx, my); }
    if (is_brazier())                            { i_set_is_brazier = true;
                                                   level->set_is_brazier(mx, my); }
    if (is_barrel())                             { i_set_is_barrel = true;
                                                   level->set_is_barrel(mx, my); }
    if (is_treasure())                           { i_set_is_treasure = true;
                                                   level->set_is_treasure(mx, my); }
    if (is_wall())                               { i_set_is_wall = true;
                                                   level->set_is_wall(mx, my); }
    if (is_shallow_water() || is_deep_water()) {
        i_set_gfx_water = true;
        level->set_gfx_water(mx, my);
    }

    if (is_shallow_water()) {
        if (!is_falling) {
            i_set_is_shallow_water = true;
            level->set_is_shallow_water(mx, my);
        }
    }

    if (is_deep_water()) { 
        if (!is_falling) {
            i_set_is_deep_water = true;
            level->set_is_deep_water(mx, my);
        }
    }

    if (is_lava() || is_fire()) { level->heatmap_valid = false; }

    if (!is_hidden) {
        if (gfx_shown_in_bg()) { level->timestamp_redraw_bg = time_get_time_ms_cached() + 1000; }
    }

    if (gfx_shown_in_bg()) {
        level->timestamp_redraw_bg = time_get_time_ms_cached() + 500;
    }

    // dbg("Is_monst count %d (after push) at %d,%d", level->is_monst(mx, my), mx, my);
}
