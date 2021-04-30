//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <array>
#include "my_sys.h"
#include "my_main.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_depth.h"
#include "my_charmap.h"
#include "my_python.h"
#include "my_level_static.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

PyObject *level_add_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *level_name = 0;
    PyObject *py_level_data = 0;

    static char *kwlist[] = {
        (char*) "level_data",
        (char*) "level_name",
        0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds,
                                     "|Os",
                                     kwlist,
                                     &py_level_data,
                                     &level_name)) {
        ERR("map_load: bad args");
        Py_RETURN_FALSE;
    }

    if (!py_level_data) {
        ERR("Map_load_level, missing floor data");
        Py_RETURN_FALSE;
    }

    int level_data_elems = PyList_Size(py_level_data);
    if (level_data_elems % MAP_HEIGHT) {
        ERR("map_load: level elems needs to be evenly dividable by level height %d, got %d elems when loading %s",
            (int) MAP_HEIGHT, (int) PyList_Size(py_level_data), level_name);
        Py_RETURN_FALSE;
    }

    auto l = LevelStatic::level_new();
    for (auto n=0; n < MAP_WIDTH; n++) {
        for (auto y=0; y<MAP_HEIGHT; y++) {
            auto o = PyList_GetItem(py_level_data, y); /* Can't fail */
            if (!o) {
                continue;
            }

            std::string floor_string;
            std::string water_string;
            std::string lava_string;
            std::string chasm_string;
            std::string walls_string;
            std::string obj_strings;

            for (auto& c : py_obj_to_string(o)) {
                auto m = get(Charmap::all_charmaps, c);

                if (m.is_floor ||
                    m.is_secret_corridor ||
                    m.is_dirt) {
                    floor_string += c;
                } else if (m.is_blood                 ||
                           m.is_deep_water            ||
                           m.is_door                  ||
                           m.is_ascend_dungeon        ||
                           m.is_descend_dungeon       ||
                           m.is_descend_sewer         ||
                           m.is_floor_deco            ||
                           m.is_food                  ||
                           m.is_minion_generator_easy ||
                           m.is_minion_generator_hard ||
                           m.is_gold                  ||
                           m.is_key                   ||
                           m.is_lava                  ||
                           m.is_monst_easy            ||
                           m.is_monst_hard            ||
                           m.is_treasure_class_a      ||
                           m.is_treasure_class_b      ||
                           m.is_treasure_class_c      ||
                           m.is_potion                ||
                           m.is_wand                  ||
                           m.is_secret_door           ||
                           m.is_brazier               ||
                           m.is_barrel                ||
                           m.is_trap                  ||
                           m.is_shallow_water         ||
                           m.is_deep_water            ||
                           m.is_floor_deco) {
                    floor_string += Charmap::FLOOR;
                } else {
                    floor_string += Charmap::SPACE;
                }

                if (m.is_shallow_water || m.is_deep_water) {
                    water_string += c;
                } else {
                    water_string += Charmap::SPACE;
                }

                if (m.is_lava) {
                    lava_string += c;
                } else {
                    lava_string += Charmap::SPACE;
                }

                if (m.is_chasm) {
                    chasm_string += c;
                } else {
                    chasm_string += Charmap::SPACE;
                }

                if (m.is_wall ||
                    m.is_secret_door ||
                    m.is_door) {
                    walls_string += c;
                } else if (m.is_descend_sewer) {
                    walls_string += Charmap::WALL;
                } else {
                    walls_string += Charmap::SPACE;
                }

                if (m.is_blood                 ||
                    m.is_ascend_dungeon        ||
                    m.is_descend_dungeon       ||
                    m.is_descend_sewer         ||
                    m.is_floor_deco            ||
                    m.is_food                  ||
                    m.is_minion_generator_easy ||
                    m.is_minion_generator_hard ||
                    m.is_gold                  ||
                    m.is_key                   ||
                    m.is_monst_easy            ||
                    m.is_monst_hard            ||
                    m.is_treasure_class_a      ||
                    m.is_treasure_class_b      ||
                    m.is_treasure_class_c      ||
                    m.is_potion                ||
                    m.is_wand                  ||
                    m.is_brazier               ||
                    m.is_barrel                ||
                    m.is_trap                  ||
                    m.is_descend_sewer) {
                    obj_strings += c;
                } else {
                    obj_strings += Charmap::SPACE;
                }
            }

            if (floor_string.size() != MAP_WIDTH){
                ERR("Level floor width mismatch, %d, expected %d",
                    (int)floor_string.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }
            if (water_string.size() != MAP_WIDTH){
                ERR("Level water width mismatch, %d, expected %d",
                    (int)water_string.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }
            if (lava_string.size() != MAP_WIDTH){
                ERR("Level lava width mismatch, %d, expected %d",
                    (int)lava_string.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }
            if (chasm_string.size() != MAP_WIDTH){
                ERR("Level chasm width mismatch, %d, expected %d",
                    (int)chasm_string.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }
            if (walls_string.size() != MAP_WIDTH){
                ERR("Level walls width mismatch, %d, expected %d",
                    (int)walls_string.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }
            if (obj_strings.size() != MAP_WIDTH){
                ERR("Level items width mismatch, %d, expected %d",
                    (int)obj_strings.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }

            for (auto x = 0; x < MAP_WIDTH; x++) {
                if (floor_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_FLOOR, floor_string[x]);
                }
                if (water_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_WATER, water_string[x]);
                }
                if (lava_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_LAVA,  lava_string[x]);
                }
                if (chasm_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_CHASM, chasm_string[x]);
                }
                if (walls_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_OBJ,  walls_string[x]);
                }
                if (obj_strings[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_OBJ,  obj_strings[x]);
                }
            }

            if (floor_string.size() != MAP_WIDTH){
                ERR("Level floor width mismatch, %d, expected %d",
                    (int)floor_string.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }
            if (water_string.size() != MAP_WIDTH){
                ERR("Level water width mismatch, %d, expected %d",
                    (int)water_string.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }
            if (walls_string.size() != MAP_WIDTH){
                ERR("Level walls width mismatch, %d, expected %d",
                    (int)walls_string.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }
            if (obj_strings.size() != MAP_WIDTH){
                ERR("Level items width mismatch, %d, expected %d",
                    (int)obj_strings.size(), MAP_WIDTH);
                Py_RETURN_FALSE;
            }

            for (auto x = 0; x < MAP_WIDTH; x++) {
                set(l->data, x, y, MAP_DEPTH_FLOOR, floor_string[x]);
                set(l->data, x, y, MAP_DEPTH_WATER, water_string[x]);
                set(l->data, x, y, MAP_DEPTH_LAVA,  lava_string[x]);
                set(l->data, x, y, MAP_DEPTH_CHASM, chasm_string[x]);
                set(l->data, x, y, MAP_DEPTH_OBJ,   walls_string[x]);
            }
        }
    }
    l->finalize();

    Py_RETURN_TRUE;
}

PyObject *level_get_all (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    uint32_t id = 0;
    int x = -1;
    int y = -1;
    static char *kwlist[] = {(char*)"id", (char*)"x", (char*)"y", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Iii", kwlist, &id, &x, &y)) {
        ERR("%s: failed parsing keywords", __FUNCTION__);	
        Py_RETURN_FALSE;	
    }	
	
    if (!id) {
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	
        Py_RETURN_FALSE;	
    }

    Thingp t = game->thing_find(id);	
    if (!t) {	
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);
        Py_RETURN_NONE;	
    }	

    if (t->level->is_oob(x, y)) {
        PyObject *lst = PyList_New(0);
        return (lst);
    }

    auto items = 0;
    FOR_ALL_THINGS(t->level, t, x, y) {
        //
        // Don't include carried things else lasers will destroy all items carried!
        //
        if (t->get_immediate_owner()) {
            continue;
        }
        items++;
    } FOR_ALL_THINGS_END()

    PyObject *lst = PyList_New(items);
    auto item = 0;
    FOR_ALL_THINGS(t->level, t, x, y) {
        //
        // Don't include carried things else lasers will destroy all items carried!
        //
        if (t->get_immediate_owner()) {
            continue;
        }
        PyList_SetItem(lst, item, Py_BuildValue("I", t->id));
        item++;
    } FOR_ALL_THINGS_END()

    return (lst);
}

PyObject *level_flood_fill_get_all_things (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    uint32_t id = 0;
    int x = -1;
    int y = -1;
    static char *kwlist[] = {(char*)"id", (char*)"x", (char*)"y", (char*)"filter", 0};	
    char *filter = nullptr;
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Iiis", kwlist, &id, &x, &y, &filter)) {
        ERR("%s: failed parsing keywords", __FUNCTION__);	
        Py_RETURN_FALSE;	
    }	
	
    if (!id) {
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	
        Py_RETURN_FALSE;	
    }

    if (!filter) {
        ERR("%s: no filter specified %u", __FUNCTION__, id);	
        Py_RETURN_FALSE;	
    }

    Thingp t = game->thing_find(id);	
    if (!t) {	
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);
        Py_RETURN_NONE;	
    }	

    if (t->level->is_oob(x, y)) {
        PyObject *lst = PyList_New(0);
        return (lst);
    }

    auto things = t->level->flood_fill_things(point(x, y), Thing::matches_to_func(filter));
    auto items = things.size();
    PyObject *lst = PyList_New(items);
    auto item = 0;
    for (auto t : things) {
        PyList_SetItem(lst, item, Py_BuildValue("I", t->id));
        item++;
    }

    return (lst);
}

#define LEVEL_BODY_GET_BOOL_AT(__func__, __api__)                                   \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{_	                                                                            \
    uint32_t id = 0;	                                                            \
    int x = -1;                                                                     \
    int y = -1;                                                                     \
    static char *kwlist[] = {(char*)"id", (char*)"x", (char*)"y", 0};	            \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Iii", kwlist, &id, &x, &y)) {   \
        ERR("%s: failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!id) {	                                                                    \
        ERR("%s: no thing ID set", __FUNCTION__);	                            \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->thing_find(id);	                                            \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (t->level->is_oob(x, y)) { Py_RETURN_FALSE; }                             \
	                                                                            \
    if (t->__api__()) {                                                             \
        Py_RETURN_TRUE;	                                                            \
    } else {                                                                        \
        Py_RETURN_FALSE;	                                                    \
    }                                                                               \
}

LEVEL_BODY_GET_BOOL_AT(level_is_able_to_change_levels_at, is_able_to_change_levels)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_fall_at, is_able_to_fall)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_fire_at_at, is_able_to_fire_at)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_see_through_doors_at, is_able_to_see_through_doors)
LEVEL_BODY_GET_BOOL_AT(level_is_able_to_walk_through_walls_at, is_able_to_walk_through_walls)
LEVEL_BODY_GET_BOOL_AT(level_is_acid_at, is_acid)
LEVEL_BODY_GET_BOOL_AT(level_is_acid_lover_at, is_acid_lover)
LEVEL_BODY_GET_BOOL_AT(level_is_active_at, is_active)
LEVEL_BODY_GET_BOOL_AT(level_is_alive_monst_at, is_alive_monst)
LEVEL_BODY_GET_BOOL_AT(level_is_always_hit_at, is_always_hit)
LEVEL_BODY_GET_BOOL_AT(level_is_ascend_dungeon_at, is_ascend_dungeon)
LEVEL_BODY_GET_BOOL_AT(level_is_ascend_sewer_at, is_ascend_sewer)
LEVEL_BODY_GET_BOOL_AT(level_is_attackable_by_monst_at, is_attackable_by_monst)
LEVEL_BODY_GET_BOOL_AT(level_is_attackable_by_player_at, is_attackable_by_player)
LEVEL_BODY_GET_BOOL_AT(level_is_auto_collect_item_at, is_auto_collect_item)
LEVEL_BODY_GET_BOOL_AT(level_is_bag_at, is_bag)
LEVEL_BODY_GET_BOOL_AT(level_is_bleeder_at, is_bleeder)
LEVEL_BODY_GET_BOOL_AT(level_is_blood_at, is_blood)
LEVEL_BODY_GET_BOOL_AT(level_is_blood_splatter_at, is_blood_splatter)
LEVEL_BODY_GET_BOOL_AT(level_is_bloodied_at, is_bloodied)
LEVEL_BODY_GET_BOOL_AT(level_is_brazier_at, is_brazier)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr99_at, is_rrr99)
LEVEL_BODY_GET_BOOL_AT(level_is_carrier_of_treasure_class_a_at, is_carrier_of_treasure_class_a)
LEVEL_BODY_GET_BOOL_AT(level_is_carrier_of_treasure_class_b_at, is_carrier_of_treasure_class_b)
LEVEL_BODY_GET_BOOL_AT(level_is_carrier_of_treasure_class_c_at, is_carrier_of_treasure_class_c)
LEVEL_BODY_GET_BOOL_AT(level_is_carrying_item_at, is_carrying_item)
LEVEL_BODY_GET_BOOL_AT(level_is_carrying_treasure_at, is_carrying_treasure)
LEVEL_BODY_GET_BOOL_AT(level_is_chasm_at, is_chasm)
LEVEL_BODY_GET_BOOL_AT(level_is_collect_as_keys_at, is_collect_as_keys)
LEVEL_BODY_GET_BOOL_AT(level_is_collectable_at, is_collectable)
LEVEL_BODY_GET_BOOL_AT(level_is_combustible_at, is_combustible)
LEVEL_BODY_GET_BOOL_AT(level_is_corpse_at, is_corpse)
LEVEL_BODY_GET_BOOL_AT(level_is_corpse_on_death_at, is_corpse_on_death)
LEVEL_BODY_GET_BOOL_AT(level_is_corridor_at, is_corridor)
LEVEL_BODY_GET_BOOL_AT(level_is_critical_to_level_at, is_critical_to_level)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_at, is_cursor)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_can_hover_over_at, is_cursor_can_hover_over)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_can_hover_over_but_needs_double_click_at, is_cursor_can_hover_over_but_needs_double_click)
LEVEL_BODY_GET_BOOL_AT(level_is_cursor_path_at, is_cursor_path)
LEVEL_BODY_GET_BOOL_AT(level_is_dead_on_shove_at, is_dead_on_shove)
LEVEL_BODY_GET_BOOL_AT(level_is_deep_water_at, is_deep_water)
LEVEL_BODY_GET_BOOL_AT(level_is_descend_dungeon_at, is_descend_dungeon)
LEVEL_BODY_GET_BOOL_AT(level_is_descend_sewer_at, is_descend_sewer)
LEVEL_BODY_GET_BOOL_AT(level_is_described_when_hovering_over_at, is_described_when_hovering_over)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_bl_at, is_dir_bl)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_br_at, is_dir_br)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_down_at, is_dir_down)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_left_at, is_dir_left)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_none_at, is_dir_none)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_right_at, is_dir_right)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_tl_at, is_dir_tl)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_tr_at, is_dir_tr)
LEVEL_BODY_GET_BOOL_AT(level_is_dir_up_at, is_dir_up)
LEVEL_BODY_GET_BOOL_AT(level_is_dirt_at, is_dirt)
LEVEL_BODY_GET_BOOL_AT(level_is_door_at, is_door)
LEVEL_BODY_GET_BOOL_AT(level_is_droppable_at, is_droppable)
LEVEL_BODY_GET_BOOL_AT(level_is_ethereal_at, is_ethereal)
LEVEL_BODY_GET_BOOL_AT(level_is_ethereal_minion_generator_at, is_ethereal_minion_generator)
LEVEL_BODY_GET_BOOL_AT(level_is_explosion_at, is_explosion)
LEVEL_BODY_GET_BOOL_AT(level_is_extreme_hazard_at, is_extreme_hazard)
LEVEL_BODY_GET_BOOL_AT(level_is_fearless_at, is_fearless)
LEVEL_BODY_GET_BOOL_AT(level_is_fire_at, is_fire)
LEVEL_BODY_GET_BOOL_AT(level_is_very_combustible_at, is_very_combustible)
LEVEL_BODY_GET_BOOL_AT(level_is_floating_at, is_floating)
LEVEL_BODY_GET_BOOL_AT(level_is_floor_at, is_floor)
LEVEL_BODY_GET_BOOL_AT(level_is_floor_deco_at, is_floor_deco)
LEVEL_BODY_GET_BOOL_AT(level_is_food_at, is_food)
LEVEL_BODY_GET_BOOL_AT(level_is_food_eater_at, is_food_eater)
LEVEL_BODY_GET_BOOL_AT(level_gfx_water_at, gfx_water)
LEVEL_BODY_GET_BOOL_AT(level_is_gold_at, is_gold)
LEVEL_BODY_GET_BOOL_AT(level_is_hazard_at, is_hazard)
LEVEL_BODY_GET_BOOL_AT(level_is_humanoid_at, is_humanoid)
LEVEL_BODY_GET_BOOL_AT(level_is_hunger_insatiable_at, is_hunger_insatiable)
LEVEL_BODY_GET_BOOL_AT(level_is_intelligent_at, is_intelligent)
LEVEL_BODY_GET_BOOL_AT(level_is_interesting_at, is_interesting)
LEVEL_BODY_GET_BOOL_AT(level_is_item_at, is_item)
LEVEL_BODY_GET_BOOL_AT(level_is_item_carrier_at, is_item_carrier)
LEVEL_BODY_GET_BOOL_AT(level_is_item_collected_as_gold_at, is_item_collected_as_gold)
LEVEL_BODY_GET_BOOL_AT(level_is_item_eater_at, is_item_eater)
LEVEL_BODY_GET_BOOL_AT(level_is_item_not_stackable_at, is_item_not_stackable)
LEVEL_BODY_GET_BOOL_AT(level_is_jelly_at, is_jelly)
LEVEL_BODY_GET_BOOL_AT(level_is_jelly_baby_at, is_jelly_baby)
LEVEL_BODY_GET_BOOL_AT(level_is_jelly_baby_eater_at, is_jelly_baby_eater)
LEVEL_BODY_GET_BOOL_AT(level_is_jelly_eater_at, is_jelly_eater)
LEVEL_BODY_GET_BOOL_AT(level_is_jelly_parent_at, is_jelly_parent)
LEVEL_BODY_GET_BOOL_AT(level_is_jumper_at, is_jumper)
LEVEL_BODY_GET_BOOL_AT(level_is_jumper_chance_d1000_at, is_jumper_chance_d1000)
LEVEL_BODY_GET_BOOL_AT(level_is_jumper_distance_at, is_jumper_distance)
LEVEL_BODY_GET_BOOL_AT(level_is_jumper_on_low_hp_chance_d1000_at, is_jumper_on_low_hp_chance_d1000)
LEVEL_BODY_GET_BOOL_AT(level_is_key_at, is_key)
LEVEL_BODY_GET_BOOL_AT(level_is_killed_on_hit_or_miss_at, is_killed_on_hit_or_miss)
LEVEL_BODY_GET_BOOL_AT(level_is_killed_on_hitting_at, is_killed_on_hitting)
LEVEL_BODY_GET_BOOL_AT(level_is_laser_at, is_laser)
LEVEL_BODY_GET_BOOL_AT(level_is_target_select_automatically_when_chosen_at, is_target_select_automatically_when_chosen)
LEVEL_BODY_GET_BOOL_AT(level_is_lava_at, is_lava)
LEVEL_BODY_GET_BOOL_AT(level_is_light_blocker_at, is_light_blocker)
LEVEL_BODY_GET_BOOL_AT(level_is_living_at, is_living)
LEVEL_BODY_GET_BOOL_AT(level_is_loggable_for_important_stuff_at, is_loggable_for_important_stuff)
LEVEL_BODY_GET_BOOL_AT(level_is_loggable_for_unimportant_stuff_at, is_loggable_for_unimportant_stuff)
LEVEL_BODY_GET_BOOL_AT(level_is_meat_at, is_meat)
LEVEL_BODY_GET_BOOL_AT(level_is_meat_eater_at, is_meat_eater)
LEVEL_BODY_GET_BOOL_AT(level_is_minion_at, is_minion)
LEVEL_BODY_GET_BOOL_AT(level_is_minion_generator_at, is_minion_generator)
LEVEL_BODY_GET_BOOL_AT(level_is_monst_at, is_monst)
LEVEL_BODY_GET_BOOL_AT(level_is_moveable_at, is_moveable)
LEVEL_BODY_GET_BOOL_AT(level_is_movement_blocking_hard_at, is_movement_blocking_hard)
LEVEL_BODY_GET_BOOL_AT(level_is_movement_blocking_soft_at, is_movement_blocking_soft)
LEVEL_BODY_GET_BOOL_AT(level_is_msg_at, is_msg)
LEVEL_BODY_GET_BOOL_AT(level_is_no_tile_at, is_no_tile)
LEVEL_BODY_GET_BOOL_AT(level_is_on_fire_at, is_on_fire)
LEVEL_BODY_GET_BOOL_AT(level_is_player_at, is_player)
LEVEL_BODY_GET_BOOL_AT(level_is_poison_at, is_poison)
LEVEL_BODY_GET_BOOL_AT(level_loves_poison_at, loves_poison)
LEVEL_BODY_GET_BOOL_AT(level_is_potion_at, is_potion)
LEVEL_BODY_GET_BOOL_AT(level_is_potion_eater_at, is_potion_eater)
LEVEL_BODY_GET_BOOL_AT(level_is_projectile_at, is_projectile)
LEVEL_BODY_GET_BOOL_AT(level_is_removeable_if_out_of_slots_at, is_removeable_if_out_of_slots)
LEVEL_BODY_GET_BOOL_AT(level_is_resurrectable_at, is_resurrectable)
LEVEL_BODY_GET_BOOL_AT(level_is_ripple_at, is_ripple)
LEVEL_BODY_GET_BOOL_AT(level_is_rock_at, is_rock)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr10_at, is_rrr10)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr11_at, is_rrr11)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr12_at, is_rrr12)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr13_at, is_rrr13)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr14_at, is_rrr14)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr15_at, is_rrr15)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr16_at, is_rrr16)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr17_at, is_rrr17)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr18_at, is_rrr18)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr19_at, is_rrr19)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr1_at, is_rrr1)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr20_at, is_rrr20)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr21_at, is_rrr21)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr22_at, is_rrr22)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr23_at, is_rrr23)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr24_at, is_rrr24)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr25_at, is_rrr25)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr26_at, is_rrr26)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr27_at, is_rrr27)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr28_at, is_rrr28)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr29_at, is_rrr29)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr2_at, is_rrr2)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr30_at, is_rrr30)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr31_at, is_rrr31)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr32_at, is_rrr32)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr33_at, is_rrr33)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr34_at, is_rrr34)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr35_at, is_rrr35)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr36_at, is_rrr36)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr37_at, is_rrr37)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr38_at, is_rrr38)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr39_at, is_rrr39)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr3_at, is_rrr3)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr40_at, is_rrr40)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr41_at, is_rrr41)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr42_at, is_rrr42)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr43_at, is_rrr43)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr44_at, is_rrr44)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr45_at, is_rrr45)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr46_at, is_rrr46)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr47_at, is_rrr47)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr48_at, is_rrr48)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr49_at, is_rrr49)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr4_at, is_rrr4)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr50_at, is_rrr50)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr51_at, is_rrr51)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr52_at, is_rrr52)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr53_at, is_rrr53)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr54_at, is_rrr54)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr55_at, is_rrr55)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr56_at, is_rrr56)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr57_at, is_rrr57)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr58_at, is_rrr58)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr59_at, is_rrr59)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr5_at, is_rrr5)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr60_at, is_rrr60)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr61_at, is_rrr61)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr62_at, is_rrr62)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr63_at, is_rrr63)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr64_at, is_rrr64)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr65_at, is_rrr65)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr66_at, is_rrr66)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr67_at, is_rrr67)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr68_at, is_rrr68)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr69_at, is_rrr69)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr6_at, is_rrr6)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr70_at, is_rrr70)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr71_at, is_rrr71)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr72_at, is_rrr72)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr73_at, is_rrr73)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr74_at, is_rrr74)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr75_at, is_rrr75)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr76_at, is_rrr76)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr77_at, is_rrr77)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr78_at, is_rrr78)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr79_at, is_rrr79)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr7_at, is_rrr7)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr80_at, is_rrr80)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr81_at, is_rrr81)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr82_at, is_rrr82)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr83_at, is_rrr83)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr84_at, is_rrr84)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr85_at, is_rrr85)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr86_at, is_rrr86)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr87_at, is_rrr87)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr88_at, is_rrr88)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr89_at, is_rrr89)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr8_at, is_rrr8)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr90_at, is_rrr90)
LEVEL_BODY_GET_BOOL_AT(level_is_barrel_at, is_barrel)
LEVEL_BODY_GET_BOOL_AT(level_is_burnable_at, is_burnable)
LEVEL_BODY_GET_BOOL_AT(level_is_wand_eater_at, is_wand_eater)
LEVEL_BODY_GET_BOOL_AT(level_loves_fire_at, loves_fire)
LEVEL_BODY_GET_BOOL_AT(level_gfx_flickers_at, gfx_flickers)
LEVEL_BODY_GET_BOOL_AT(level_is_rrr9_at, is_rrr9)
LEVEL_BODY_GET_BOOL_AT(level_is_secret_door_at, is_secret_door)
LEVEL_BODY_GET_BOOL_AT(level_is_sewer_wall_at, is_sewer_wall)
LEVEL_BODY_GET_BOOL_AT(level_is_shallow_water_at, is_shallow_water)
LEVEL_BODY_GET_BOOL_AT(level_is_shovable_at, is_shovable)
LEVEL_BODY_GET_BOOL_AT(level_is_shown_on_leftbar_at, is_shown_on_leftbar)
LEVEL_BODY_GET_BOOL_AT(level_is_shown_uniquely_on_leftbar_at, is_shown_uniquely_on_leftbar)
LEVEL_BODY_GET_BOOL_AT(level_is_skill_at, is_skill)
LEVEL_BODY_GET_BOOL_AT(level_is_smoke_at, is_smoke)
LEVEL_BODY_GET_BOOL_AT(level_is_spawner_at, is_spawner)
LEVEL_BODY_GET_BOOL_AT(level_is_stamina_check_at, is_stamina_check)
LEVEL_BODY_GET_BOOL_AT(level_is_steal_item_chance_d1000_at, is_steal_item_chance_d1000)
LEVEL_BODY_GET_BOOL_AT(level_is_temporary_bag_at, is_temporary_bag)
LEVEL_BODY_GET_BOOL_AT(level_is_throwable_at, is_throwable)
LEVEL_BODY_GET_BOOL_AT(level_is_thrown_automatically_when_chosen_at, is_thrown_automatically_when_chosen)
LEVEL_BODY_GET_BOOL_AT(level_is_torch_at, is_torch)
LEVEL_BODY_GET_BOOL_AT(level_is_treasure_at, is_treasure)
LEVEL_BODY_GET_BOOL_AT(level_is_treasure_class_a_at, is_treasure_class_a)
LEVEL_BODY_GET_BOOL_AT(level_is_treasure_class_b_at, is_treasure_class_b)
LEVEL_BODY_GET_BOOL_AT(level_is_treasure_class_c_at, is_treasure_class_c)
LEVEL_BODY_GET_BOOL_AT(level_is_treasure_eater_at, is_treasure_eater)
LEVEL_BODY_GET_BOOL_AT(level_is_undead_at, is_undead)
LEVEL_BODY_GET_BOOL_AT(level_is_usable_at, is_usable)
LEVEL_BODY_GET_BOOL_AT(level_is_used_automatically_when_selected_at, is_used_automatically_when_selected)
LEVEL_BODY_GET_BOOL_AT(level_is_used_when_thrown_at, is_used_when_thrown)
LEVEL_BODY_GET_BOOL_AT(level_is_visible_at, is_visible)
LEVEL_BODY_GET_BOOL_AT(level_is_wall_at, is_wall)
LEVEL_BODY_GET_BOOL_AT(level_is_wall_dungeon_at, is_wall_dungeon)
LEVEL_BODY_GET_BOOL_AT(level_is_wand_at, is_wand)
LEVEL_BODY_GET_BOOL_AT(level_is_water_at, is_water)
LEVEL_BODY_GET_BOOL_AT(level_is_water_lover_at, is_water_lover)
LEVEL_BODY_GET_BOOL_AT(level_is_weapon_at, is_weapon)
LEVEL_BODY_GET_BOOL_AT(level_is_weapon_wielder_at, is_weapon_wielder)
