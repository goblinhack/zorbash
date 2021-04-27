//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_python.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_py_thing.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

#define THING_BODY_SET_INT(__func__, __api__)                                       \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{_	                                                                            \
    uint32_t id = 0;	                                                            \
    uint32_t value = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", (char*)"value", 0};	                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Ii", kwlist, &id, &value)) {    \
        ERR("%s: failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->level->thing_find(id);	                                    \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    t->__api__(value);                                                              \
    Py_RETURN_TRUE;	                                                            \
}

#define THING_BODY_GET_INT(__func__, __api__)                                       \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{_	                                                                            \
    uint32_t id = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", 0};	                                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {             \
        ERR("%s: failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->level->thing_find(id);	                                    \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    auto value = t->__api__();                                                      \
    return Py_BuildValue("i", (int) value);                                         \
}

#define THING_BODY_GET_STRING(__func__, __api__)                                    \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{_	                                                                            \
    uint32_t id = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", 0};	                                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {             \
        ERR("%s: failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->level->thing_find(id);	                                    \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    auto value = t->__api__();                                                      \
    return Py_BuildValue("s", value.c_str());                                       \
}

#define THING_BODY_SET_THING(__func__, __api__)                                     \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{_	                                                                            \
    uint32_t id = 0;	                                                            \
    uint32_t oid = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", (char*)"oid", 0};	                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &oid)) {      \
        ERR("%s: failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!id) {	                                                                    \
        ERR("%s: no thing ID set", __FUNCTION__);	                            \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!oid) {	                                                                    \
        ERR("%s: no oid thing ID set", __FUNCTION__);	                            \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->level->thing_find(id);	                                    \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
                                                                                    \
    Thingp o = game->level->thing_find(oid);	                                    \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, oid);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    t->__api__(o);                                                                  \
    Py_RETURN_TRUE;                                                                 \
}

#define THING_BODY_GET_THING(__func__, __api__)                                     \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{_	                                                                            \
    uint32_t id = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", 0};	                                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {             \
        ERR("%s: failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!id) {	                                                                    \
        ERR("%s: no thing ID set", __FUNCTION__);	                            \
        return Py_BuildValue("I", 0);                                               \
    }	                                                                            \
	                                                                            \
    Thingp t = game->level->thing_find(id);	                                    \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	                    \
        return Py_BuildValue("I", 0);                                               \
    }	                                                                            \
	                                                                            \
    ThingId found = t->__api__();                                                   \
    return Py_BuildValue("I", found.id);                                            \
}

#define THING_BODY_GET_BOOL(__func__, __api__)                                      \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{_	                                                                            \
    uint32_t id = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", 0};	                                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {             \
        ERR("%s: failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!id) {	                                                                    \
        ERR("%s: no thing ID set", __FUNCTION__);	                            \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->level->thing_find(id);	                                    \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (t->__api__()) {                                                             \
        Py_RETURN_TRUE;	                                                            \
    } else {                                                                        \
        Py_RETURN_FALSE;	                                                    \
    }                                                                               \
}

#define THING_BODY_GET_BOOL_AT(__func__, __api__)                                   \
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
    if (game->level->is_oob(x, y)) { Py_RETURN_FALSE; }                             \
	                                                                            \
    Thingp t = game->level->thing_find(id);	                                    \
    if (!t) {	                                                                    \
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (t->__api__()) {                                                             \
        Py_RETURN_TRUE;	                                                            \
    } else {                                                                        \
        Py_RETURN_FALSE;	                                                    \
    }                                                                               \
}

PyObject *thing_get_coords (PyObject *obj, PyObject *args, PyObject *keywds)
{_	
    uint32_t id = 0;	
    static char *kwlist[] = {(char*)"id", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {
        ERR("%s: failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!id) {	
        ERR("%s: no thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp t = game->level->thing_find(id);	
    if (!t) {	
        ERR("%s: cannot find thing ID %u", __FUNCTION__, id);	
        Py_RETURN_NONE;	
    }	
	
    Py_ssize_t size = 2;
    auto the_tuple = PyTuple_New(size); // this line crashes the program
    if (!the_tuple) {
        ERR("%s: cannot create tuple for ID %u", __FUNCTION__, id);	
        Py_RETURN_NONE;	
    }	

    auto err = PyTuple_SetItem(the_tuple, (Py_ssize_t) 0, PyLong_FromLong((long) t->mid_at.x));
    if (err < 0) {
        ERR("%s: cannot create tuple (a) for ID %u", __FUNCTION__, id);	
        Py_RETURN_NONE;	
    }

    err = PyTuple_SetItem(the_tuple, (Py_ssize_t) 1, PyLong_FromLong((long) t->mid_at.y));
    if (err < 0) {
        ERR("%s: cannot create tuple (a) for ID %u", __FUNCTION__, id);	
        Py_RETURN_NONE;	
    }

    return the_tuple;
}

PyObject *thing_hit (PyObject *obj, PyObject *args, PyObject *keywds)
{_	
    uint32_t owner_id = 0;	
    uint32_t item_id = 0;	
    uint32_t target_id = 0;	
    static char *kwlist[] = {(char*)"owner", (char*)"item", (char*)"target", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "III", kwlist, &owner_id, &item_id, &target_id)) {
        ERR("%s: failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!owner_id) {	
        ERR("%s: no owner thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp owner = game->level->thing_find(owner_id);	
    if (!owner) {	
        ERR("%s: cannot find owner thing ID %u", __FUNCTION__, owner_id);	
        Py_RETURN_NONE;	
    }	

    if (!item_id) {	
        ERR("%s: no item thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp item = game->level->thing_find(item_id);	
    if (!item) {	
        ERR("%s: cannot find item thing ID %u", __FUNCTION__, item_id);	
        Py_RETURN_NONE;	
    }	

    if (!target_id) {	
        ERR("%s: no target thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp target = game->level->thing_find(target_id);	
    if (!target) {	
        ERR("%s: cannot find target thing ID %u", __FUNCTION__, target_id);	
        Py_RETURN_NONE;	
    }	

    owner->log("hit with %s target %s", item->to_string().c_str(), target->to_string().c_str());

    if (target->is_hit_by(item)) {
        Py_RETURN_TRUE;	
    } else {
        Py_RETURN_FALSE;	
    }
}

PyObject *thing_fire_at (PyObject *obj, PyObject *args, PyObject *keywds)
{_	
    uint32_t owner_id = 0;	
    char *item = nullptr;
    uint32_t target_id = 0;	
    static char *kwlist[] = {(char*)"owner", (char*)"item", (char*)"target", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &owner_id, &item, &target_id)) {
        ERR("%s: failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!owner_id) {	
        ERR("%s: no owner thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp owner = game->level->thing_find(owner_id);	
    if (!owner) {	
        ERR("%s: cannot find owner thing ID %u", __FUNCTION__, owner_id);	
        Py_RETURN_NONE;	
    }	

    if (!item) {	
        ERR("%s: no item thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!target_id) {	
        ERR("%s: no target thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp target = game->level->thing_find(target_id);	
    if (!target) {	
        ERR("%s: cannot find target thing ID %u", __FUNCTION__, target_id);	
        Py_RETURN_NONE;	
    }	

    owner->log("fire %s at %s", item, target->to_string().c_str());

    if (owner->laser_fire_monst(std::string(item), target)) {
        Py_RETURN_TRUE;	
    } else {
        Py_RETURN_FALSE;	
    }
}

THING_BODY_GET_BOOL(thing_ai_vision_distance, ai_vision_distance)
THING_BODY_GET_BOOL(thing_is_able_to_change_levels, is_able_to_change_levels)
THING_BODY_GET_BOOL(thing_is_able_to_fall, is_able_to_fall)
THING_BODY_GET_BOOL(thing_is_able_to_fire_at, is_able_to_fire_at)
THING_BODY_GET_BOOL(thing_is_able_to_see_through_doors, is_able_to_see_through_doors)
THING_BODY_GET_BOOL(thing_is_able_to_walk_through_walls, is_able_to_walk_through_walls)
THING_BODY_GET_BOOL(thing_is_acid, is_acid)
THING_BODY_GET_BOOL(thing_is_acid_lover, is_acid_lover)
THING_BODY_GET_BOOL(thing_is_active, is_active)
THING_BODY_GET_BOOL(thing_is_alive_monst, is_alive_monst)
THING_BODY_GET_BOOL(thing_is_always_hit, is_always_hit)
THING_BODY_GET_BOOL(thing_is_ascend_dungeon, is_ascend_dungeon)
THING_BODY_GET_BOOL(thing_is_ascend_sewer, is_ascend_sewer)
THING_BODY_GET_BOOL(thing_is_attackable_by_monst, is_attackable_by_monst)
THING_BODY_GET_BOOL(thing_is_attackable_by_player, is_attackable_by_player)
THING_BODY_GET_BOOL(thing_is_auto_collect_item, is_auto_collect_item)
THING_BODY_GET_BOOL(thing_is_bag, is_bag)
THING_BODY_GET_BOOL(thing_is_bleeder, is_bleeder)
THING_BODY_GET_BOOL(thing_is_blood, is_blood)
THING_BODY_GET_BOOL(thing_is_blood_splatter, is_blood_splatter)
THING_BODY_GET_BOOL(thing_is_bloodied, is_bloodied)
THING_BODY_GET_BOOL(thing_is_brazier, is_brazier)
THING_BODY_GET_BOOL(thing_is_burnable, is_burnable)
THING_BODY_GET_BOOL(thing_is_carrier_of_treasure_class_a, is_carrier_of_treasure_class_a)
THING_BODY_GET_BOOL(thing_is_carrier_of_treasure_class_b, is_carrier_of_treasure_class_b)
THING_BODY_GET_BOOL(thing_is_carrier_of_treasure_class_c, is_carrier_of_treasure_class_c)
THING_BODY_GET_BOOL(thing_is_carrying_item, is_carrying_item)
THING_BODY_GET_BOOL(thing_is_carrying_treasure, is_carrying_treasure)
THING_BODY_GET_BOOL(thing_is_chasm, is_chasm)
THING_BODY_GET_BOOL(thing_is_collect_as_keys, is_collect_as_keys)
THING_BODY_GET_BOOL(thing_is_collectable, is_collectable)
THING_BODY_GET_BOOL(thing_is_combustible, is_combustible)
THING_BODY_GET_BOOL(thing_is_corpse, is_corpse)
THING_BODY_GET_BOOL(thing_is_corpse_on_death, is_corpse_on_death)
THING_BODY_GET_BOOL(thing_is_corridor, is_corridor)
THING_BODY_GET_BOOL(thing_is_critical_to_level, is_critical_to_level)
THING_BODY_GET_BOOL(thing_is_cursor, is_cursor)
THING_BODY_GET_BOOL(thing_is_cursor_can_hover_over, is_cursor_can_hover_over)
THING_BODY_GET_BOOL(thing_is_cursor_can_hover_over_but_needs_double_click, is_cursor_can_hover_over_but_needs_double_click)
THING_BODY_GET_BOOL(thing_is_cursor_path, is_cursor_path)
THING_BODY_GET_BOOL(thing_is_dead_on_shove, is_dead_on_shove)
THING_BODY_GET_BOOL(thing_is_deep_water, is_deep_water)
THING_BODY_GET_BOOL(thing_is_descend_dungeon, is_descend_dungeon)
THING_BODY_GET_BOOL(thing_is_descend_sewer, is_descend_sewer)
THING_BODY_GET_BOOL(thing_is_described_when_hovering_over, is_described_when_hovering_over)
THING_BODY_GET_BOOL(thing_is_dir_bl, is_dir_bl)
THING_BODY_GET_BOOL(thing_is_dir_br, is_dir_br)
THING_BODY_GET_BOOL(thing_is_dir_down, is_dir_down)
THING_BODY_GET_BOOL(thing_is_dir_left, is_dir_left)
THING_BODY_GET_BOOL(thing_is_dir_none, is_dir_none)
THING_BODY_GET_BOOL(thing_is_dir_right, is_dir_right)
THING_BODY_GET_BOOL(thing_is_dir_tl, is_dir_tl)
THING_BODY_GET_BOOL(thing_is_dir_tr, is_dir_tr)
THING_BODY_GET_BOOL(thing_is_dir_up, is_dir_up)
THING_BODY_GET_BOOL(thing_is_dirt, is_dirt)
THING_BODY_GET_BOOL(thing_is_door, is_door)
THING_BODY_GET_BOOL(thing_is_droppable, is_droppable)
THING_BODY_GET_BOOL(thing_is_ethereal, is_ethereal)
THING_BODY_GET_BOOL(thing_is_ethereal_minion_generator, is_ethereal_minion_generator)
THING_BODY_GET_BOOL(thing_is_explosion, is_explosion)
THING_BODY_GET_BOOL(thing_is_extreme_hazard, is_extreme_hazard)
THING_BODY_GET_BOOL(thing_is_fearless, is_fearless)
THING_BODY_GET_BOOL(thing_is_fire, is_fire)
THING_BODY_GET_BOOL(thing_is_flammable, is_flammable)
THING_BODY_GET_BOOL(thing_is_floating, is_floating)
THING_BODY_GET_BOOL(thing_is_floor, is_floor)
THING_BODY_GET_BOOL(thing_is_floor_deco, is_floor_deco)
THING_BODY_GET_BOOL(thing_is_food, is_food)
THING_BODY_GET_BOOL(thing_is_food_eater, is_food_eater)
THING_BODY_GET_BOOL(thing_is_gfx_water, is_gfx_water)
THING_BODY_GET_BOOL(thing_is_gold, is_gold)
THING_BODY_GET_BOOL(thing_is_hazard, is_hazard)
THING_BODY_GET_BOOL(thing_is_humanoid, is_humanoid)
THING_BODY_GET_BOOL(thing_is_hunger_insatiable, is_hunger_insatiable)
THING_BODY_GET_BOOL(thing_is_intelligent, is_intelligent)
THING_BODY_GET_BOOL(thing_is_interesting, is_interesting)
THING_BODY_GET_BOOL(thing_is_item, is_item)
THING_BODY_GET_BOOL(thing_is_item_carrier, is_item_carrier)
THING_BODY_GET_BOOL(thing_is_item_collected_as_gold, is_item_collected_as_gold)
THING_BODY_GET_BOOL(thing_is_item_eater, is_item_eater)
THING_BODY_GET_BOOL(thing_is_item_not_stackable, is_item_not_stackable)
THING_BODY_GET_BOOL(thing_is_jelly, is_jelly)
THING_BODY_GET_BOOL(thing_is_jelly_baby, is_jelly_baby)
THING_BODY_GET_BOOL(thing_is_jelly_baby_eater, is_jelly_baby_eater)
THING_BODY_GET_BOOL(thing_is_jelly_eater, is_jelly_eater)
THING_BODY_GET_BOOL(thing_is_jelly_parent, is_jelly_parent)
THING_BODY_GET_BOOL(thing_is_jumper, is_jumper)
THING_BODY_GET_BOOL(thing_is_jumper_chance_d1000, is_jumper_chance_d1000)
THING_BODY_GET_BOOL(thing_is_jumper_distance, is_jumper_distance)
THING_BODY_GET_BOOL(thing_is_jumper_on_low_hp_chance_d1000, is_jumper_on_low_hp_chance_d1000)
THING_BODY_GET_BOOL(thing_is_key, is_key)
THING_BODY_GET_BOOL(thing_is_killed_on_hit_or_miss, is_killed_on_hit_or_miss)
THING_BODY_GET_BOOL(thing_is_killed_on_hitting, is_killed_on_hitting)
THING_BODY_GET_BOOL(thing_is_laser, is_laser)
THING_BODY_GET_BOOL(thing_is_laser_target_select_automatically_when_chosen, is_laser_target_select_automatically_when_chosen)
THING_BODY_GET_BOOL(thing_is_lava, is_lava)
THING_BODY_GET_BOOL(thing_is_light_blocker, is_light_blocker)
THING_BODY_GET_BOOL(thing_is_living, is_living)
THING_BODY_GET_BOOL(thing_is_loggable_for_important_stuff, is_loggable_for_important_stuff)
THING_BODY_GET_BOOL(thing_is_loggable_for_unimportant_stuff, is_loggable_for_unimportant_stuff)
THING_BODY_GET_BOOL(thing_is_meat, is_meat)
THING_BODY_GET_BOOL(thing_is_meat_eater, is_meat_eater)
THING_BODY_GET_BOOL(thing_is_minion, is_minion)
THING_BODY_GET_BOOL(thing_is_minion_generator, is_minion_generator)
THING_BODY_GET_BOOL(thing_is_monst, is_monst)
THING_BODY_GET_BOOL(thing_is_moveable, is_moveable)
THING_BODY_GET_BOOL(thing_is_movement_blocking_hard, is_movement_blocking_hard)
THING_BODY_GET_BOOL(thing_is_movement_blocking_soft, is_movement_blocking_soft)
THING_BODY_GET_BOOL(thing_is_msg, is_msg)
THING_BODY_GET_BOOL(thing_is_no_tile, is_no_tile)
THING_BODY_GET_BOOL(thing_is_on_fire, is_on_fire)
THING_BODY_GET_BOOL(thing_is_player, is_player)
THING_BODY_GET_BOOL(thing_is_poison, is_poison)
THING_BODY_GET_BOOL(thing_is_poison_immune, is_poison_immune)
THING_BODY_GET_BOOL(thing_is_potion, is_potion)
THING_BODY_GET_BOOL(thing_is_potion_eater, is_potion_eater)
THING_BODY_GET_BOOL(thing_is_projectile, is_projectile)
THING_BODY_GET_BOOL(thing_is_removeable_if_out_of_slots, is_removeable_if_out_of_slots)
THING_BODY_GET_BOOL(thing_is_resurrectable, is_resurrectable)
THING_BODY_GET_BOOL(thing_is_ripple, is_ripple)
THING_BODY_GET_BOOL(thing_is_rock, is_rock)
THING_BODY_GET_BOOL(thing_is_rrr1, is_rrr1)
THING_BODY_GET_BOOL(thing_is_rrr10, is_rrr10)
THING_BODY_GET_BOOL(thing_is_rrr11, is_rrr11)
THING_BODY_GET_BOOL(thing_is_rrr12, is_rrr12)
THING_BODY_GET_BOOL(thing_is_rrr13, is_rrr13)
THING_BODY_GET_BOOL(thing_is_rrr14, is_rrr14)
THING_BODY_GET_BOOL(thing_is_rrr15, is_rrr15)
THING_BODY_GET_BOOL(thing_is_rrr16, is_rrr16)
THING_BODY_GET_BOOL(thing_is_rrr17, is_rrr17)
THING_BODY_GET_BOOL(thing_is_rrr18, is_rrr18)
THING_BODY_GET_BOOL(thing_is_rrr19, is_rrr19)
THING_BODY_GET_BOOL(thing_is_rrr2, is_rrr2)
THING_BODY_GET_BOOL(thing_is_rrr20, is_rrr20)
THING_BODY_GET_BOOL(thing_is_rrr21, is_rrr21)
THING_BODY_GET_BOOL(thing_is_rrr22, is_rrr22)
THING_BODY_GET_BOOL(thing_is_rrr23, is_rrr23)
THING_BODY_GET_BOOL(thing_is_rrr24, is_rrr24)
THING_BODY_GET_BOOL(thing_is_rrr25, is_rrr25)
THING_BODY_GET_BOOL(thing_is_rrr26, is_rrr26)
THING_BODY_GET_BOOL(thing_is_rrr27, is_rrr27)
THING_BODY_GET_BOOL(thing_is_rrr28, is_rrr28)
THING_BODY_GET_BOOL(thing_is_rrr29, is_rrr29)
THING_BODY_GET_BOOL(thing_is_rrr3, is_rrr3)
THING_BODY_GET_BOOL(thing_is_rrr30, is_rrr30)
THING_BODY_GET_BOOL(thing_is_rrr31, is_rrr31)
THING_BODY_GET_BOOL(thing_is_rrr32, is_rrr32)
THING_BODY_GET_BOOL(thing_is_rrr33, is_rrr33)
THING_BODY_GET_BOOL(thing_is_rrr34, is_rrr34)
THING_BODY_GET_BOOL(thing_is_rrr35, is_rrr35)
THING_BODY_GET_BOOL(thing_is_rrr36, is_rrr36)
THING_BODY_GET_BOOL(thing_is_rrr37, is_rrr37)
THING_BODY_GET_BOOL(thing_is_rrr38, is_rrr38)
THING_BODY_GET_BOOL(thing_is_rrr39, is_rrr39)
THING_BODY_GET_BOOL(thing_is_rrr4, is_rrr4)
THING_BODY_GET_BOOL(thing_is_rrr40, is_rrr40)
THING_BODY_GET_BOOL(thing_is_rrr41, is_rrr41)
THING_BODY_GET_BOOL(thing_is_rrr42, is_rrr42)
THING_BODY_GET_BOOL(thing_is_rrr43, is_rrr43)
THING_BODY_GET_BOOL(thing_is_rrr44, is_rrr44)
THING_BODY_GET_BOOL(thing_is_rrr45, is_rrr45)
THING_BODY_GET_BOOL(thing_is_rrr46, is_rrr46)
THING_BODY_GET_BOOL(thing_is_rrr47, is_rrr47)
THING_BODY_GET_BOOL(thing_is_rrr48, is_rrr48)
THING_BODY_GET_BOOL(thing_is_rrr49, is_rrr49)
THING_BODY_GET_BOOL(thing_is_rrr5, is_rrr5)
THING_BODY_GET_BOOL(thing_is_rrr50, is_rrr50)
THING_BODY_GET_BOOL(thing_is_rrr51, is_rrr51)
THING_BODY_GET_BOOL(thing_is_rrr52, is_rrr52)
THING_BODY_GET_BOOL(thing_is_rrr53, is_rrr53)
THING_BODY_GET_BOOL(thing_is_rrr54, is_rrr54)
THING_BODY_GET_BOOL(thing_is_rrr55, is_rrr55)
THING_BODY_GET_BOOL(thing_is_rrr56, is_rrr56)
THING_BODY_GET_BOOL(thing_is_rrr57, is_rrr57)
THING_BODY_GET_BOOL(thing_is_rrr58, is_rrr58)
THING_BODY_GET_BOOL(thing_is_rrr59, is_rrr59)
THING_BODY_GET_BOOL(thing_is_rrr6, is_rrr6)
THING_BODY_GET_BOOL(thing_is_rrr60, is_rrr60)
THING_BODY_GET_BOOL(thing_is_rrr61, is_rrr61)
THING_BODY_GET_BOOL(thing_is_rrr62, is_rrr62)
THING_BODY_GET_BOOL(thing_is_rrr63, is_rrr63)
THING_BODY_GET_BOOL(thing_is_rrr64, is_rrr64)
THING_BODY_GET_BOOL(thing_is_rrr65, is_rrr65)
THING_BODY_GET_BOOL(thing_is_rrr66, is_rrr66)
THING_BODY_GET_BOOL(thing_is_rrr67, is_rrr67)
THING_BODY_GET_BOOL(thing_is_rrr68, is_rrr68)
THING_BODY_GET_BOOL(thing_is_rrr69, is_rrr69)
THING_BODY_GET_BOOL(thing_is_rrr7, is_rrr7)
THING_BODY_GET_BOOL(thing_is_rrr70, is_rrr70)
THING_BODY_GET_BOOL(thing_is_rrr71, is_rrr71)
THING_BODY_GET_BOOL(thing_is_rrr72, is_rrr72)
THING_BODY_GET_BOOL(thing_is_rrr73, is_rrr73)
THING_BODY_GET_BOOL(thing_is_rrr74, is_rrr74)
THING_BODY_GET_BOOL(thing_is_rrr75, is_rrr75)
THING_BODY_GET_BOOL(thing_is_rrr76, is_rrr76)
THING_BODY_GET_BOOL(thing_is_rrr77, is_rrr77)
THING_BODY_GET_BOOL(thing_is_rrr78, is_rrr78)
THING_BODY_GET_BOOL(thing_is_rrr79, is_rrr79)
THING_BODY_GET_BOOL(thing_is_rrr8, is_rrr8)
THING_BODY_GET_BOOL(thing_is_rrr80, is_rrr80)
THING_BODY_GET_BOOL(thing_is_rrr81, is_rrr81)
THING_BODY_GET_BOOL(thing_is_rrr82, is_rrr82)
THING_BODY_GET_BOOL(thing_is_rrr83, is_rrr83)
THING_BODY_GET_BOOL(thing_is_rrr84, is_rrr84)
THING_BODY_GET_BOOL(thing_is_rrr85, is_rrr85)
THING_BODY_GET_BOOL(thing_is_rrr86, is_rrr86)
THING_BODY_GET_BOOL(thing_is_rrr87, is_rrr87)
THING_BODY_GET_BOOL(thing_is_rrr88, is_rrr88)
THING_BODY_GET_BOOL(thing_is_rrr89, is_rrr89)
THING_BODY_GET_BOOL(thing_is_rrr9, is_rrr9)
THING_BODY_GET_BOOL(thing_is_rrr90, is_rrr90)
THING_BODY_GET_BOOL(thing_is_rrr91, is_rrr91)
THING_BODY_GET_BOOL(thing_is_rrr92, is_rrr92)
THING_BODY_GET_BOOL(thing_is_rrr93, is_rrr93)
THING_BODY_GET_BOOL(thing_is_rrr94, is_rrr94)
THING_BODY_GET_BOOL(thing_is_rrr95, is_rrr95)
THING_BODY_GET_BOOL(thing_is_rrr96, is_rrr96)
THING_BODY_GET_BOOL(thing_is_secret_door, is_secret_door)
THING_BODY_GET_BOOL(thing_is_sewer_wall, is_sewer_wall)
THING_BODY_GET_BOOL(thing_is_shallow_water, is_shallow_water)
THING_BODY_GET_BOOL(thing_is_shovable, is_shovable)
THING_BODY_GET_BOOL(thing_is_shown_on_leftbar, is_shown_on_leftbar)
THING_BODY_GET_BOOL(thing_is_shown_uniquely_on_leftbar, is_shown_uniquely_on_leftbar)
THING_BODY_GET_BOOL(thing_is_skill, is_skill)
THING_BODY_GET_BOOL(thing_is_smoke, is_smoke)
THING_BODY_GET_BOOL(thing_is_spawner, is_spawner)
THING_BODY_GET_BOOL(thing_is_stamina_check, is_stamina_check)
THING_BODY_GET_BOOL(thing_is_steal_item_chance_d1000, is_steal_item_chance_d1000)
THING_BODY_GET_BOOL(thing_is_temporary_bag, is_temporary_bag)
THING_BODY_GET_BOOL(thing_is_throwable, is_throwable)
THING_BODY_GET_BOOL(thing_is_thrown_automatically_when_chosen, is_thrown_automatically_when_chosen)
THING_BODY_GET_BOOL(thing_is_torch, is_torch)
THING_BODY_GET_BOOL(thing_is_treasure, is_treasure)
THING_BODY_GET_BOOL(thing_is_treasure_class_a, is_treasure_class_a)
THING_BODY_GET_BOOL(thing_is_treasure_class_b, is_treasure_class_b)
THING_BODY_GET_BOOL(thing_is_treasure_class_c, is_treasure_class_c)
THING_BODY_GET_BOOL(thing_is_treasure_eater, is_treasure_eater)
THING_BODY_GET_BOOL(thing_is_undead, is_undead)
THING_BODY_GET_BOOL(thing_is_usable, is_usable)
THING_BODY_GET_BOOL(thing_is_used_automatically_when_selected, is_used_automatically_when_selected)
THING_BODY_GET_BOOL(thing_is_used_when_thrown, is_used_when_thrown)
THING_BODY_GET_BOOL(thing_is_visible, is_visible)
THING_BODY_GET_BOOL(thing_is_wall, is_wall)
THING_BODY_GET_BOOL(thing_is_wall_dungeon, is_wall_dungeon)
THING_BODY_GET_BOOL(thing_is_wand, is_wand)
THING_BODY_GET_BOOL(thing_is_water, is_water)
THING_BODY_GET_BOOL(thing_is_water_lover, is_water_lover)
THING_BODY_GET_BOOL(thing_is_weapon, is_weapon)
THING_BODY_GET_BOOL(thing_is_weapon_wielder, is_weapon_wielder)
THING_BODY_GET_BOOL_AT(thing_ai_vision_distance_at, ai_vision_distance)
THING_BODY_GET_BOOL_AT(thing_is_able_to_change_levels_at, is_able_to_change_levels)
THING_BODY_GET_BOOL_AT(thing_is_able_to_fall_at, is_able_to_fall)
THING_BODY_GET_BOOL_AT(thing_is_able_to_fire_at_at, is_able_to_fire_at)
THING_BODY_GET_BOOL_AT(thing_is_able_to_see_through_doors_at, is_able_to_see_through_doors)
THING_BODY_GET_BOOL_AT(thing_is_able_to_walk_through_walls_at, is_able_to_walk_through_walls)
THING_BODY_GET_BOOL_AT(thing_is_acid_at, is_acid)
THING_BODY_GET_BOOL_AT(thing_is_acid_lover_at, is_acid_lover)
THING_BODY_GET_BOOL_AT(thing_is_active_at, is_active)
THING_BODY_GET_BOOL_AT(thing_is_alive_monst_at, is_alive_monst)
THING_BODY_GET_BOOL_AT(thing_is_always_hit_at, is_always_hit)
THING_BODY_GET_BOOL_AT(thing_is_ascend_dungeon_at, is_ascend_dungeon)
THING_BODY_GET_BOOL_AT(thing_is_ascend_sewer_at, is_ascend_sewer)
THING_BODY_GET_BOOL_AT(thing_is_attackable_by_monst_at, is_attackable_by_monst)
THING_BODY_GET_BOOL_AT(thing_is_attackable_by_player_at, is_attackable_by_player)
THING_BODY_GET_BOOL_AT(thing_is_auto_collect_item_at, is_auto_collect_item)
THING_BODY_GET_BOOL_AT(thing_is_bag_at, is_bag)
THING_BODY_GET_BOOL_AT(thing_is_bleeder_at, is_bleeder)
THING_BODY_GET_BOOL_AT(thing_is_blood_at, is_blood)
THING_BODY_GET_BOOL_AT(thing_is_blood_splatter_at, is_blood_splatter)
THING_BODY_GET_BOOL_AT(thing_is_bloodied_at, is_bloodied)
THING_BODY_GET_BOOL_AT(thing_is_brazier_at, is_brazier)
THING_BODY_GET_BOOL_AT(thing_is_burnable_at, is_burnable)
THING_BODY_GET_BOOL_AT(thing_is_carrier_of_treasure_class_a_at, is_carrier_of_treasure_class_a)
THING_BODY_GET_BOOL_AT(thing_is_carrier_of_treasure_class_b_at, is_carrier_of_treasure_class_b)
THING_BODY_GET_BOOL_AT(thing_is_carrier_of_treasure_class_c_at, is_carrier_of_treasure_class_c)
THING_BODY_GET_BOOL_AT(thing_is_carrying_item_at, is_carrying_item)
THING_BODY_GET_BOOL_AT(thing_is_carrying_treasure_at, is_carrying_treasure)
THING_BODY_GET_BOOL_AT(thing_is_chasm_at, is_chasm)
THING_BODY_GET_BOOL_AT(thing_is_collect_as_keys_at, is_collect_as_keys)
THING_BODY_GET_BOOL_AT(thing_is_collectable_at, is_collectable)
THING_BODY_GET_BOOL_AT(thing_is_combustible_at, is_combustible)
THING_BODY_GET_BOOL_AT(thing_is_corpse_at, is_corpse)
THING_BODY_GET_BOOL_AT(thing_is_corpse_on_death_at, is_corpse_on_death)
THING_BODY_GET_BOOL_AT(thing_is_corridor_at, is_corridor)
THING_BODY_GET_BOOL_AT(thing_is_critical_to_level_at, is_critical_to_level)
THING_BODY_GET_BOOL_AT(thing_is_cursor_at, is_cursor)
THING_BODY_GET_BOOL_AT(thing_is_cursor_can_hover_over_at, is_cursor_can_hover_over)
THING_BODY_GET_BOOL_AT(thing_is_cursor_can_hover_over_but_needs_double_click_at, is_cursor_can_hover_over_but_needs_double_click)
THING_BODY_GET_BOOL_AT(thing_is_cursor_path_at, is_cursor_path)
THING_BODY_GET_BOOL_AT(thing_is_dead_on_shove_at, is_dead_on_shove)
THING_BODY_GET_BOOL_AT(thing_is_deep_water_at, is_deep_water)
THING_BODY_GET_BOOL_AT(thing_is_descend_dungeon_at, is_descend_dungeon)
THING_BODY_GET_BOOL_AT(thing_is_descend_sewer_at, is_descend_sewer)
THING_BODY_GET_BOOL_AT(thing_is_described_when_hovering_over_at, is_described_when_hovering_over)
THING_BODY_GET_BOOL_AT(thing_is_dir_bl_at, is_dir_bl)
THING_BODY_GET_BOOL_AT(thing_is_dir_br_at, is_dir_br)
THING_BODY_GET_BOOL_AT(thing_is_dir_down_at, is_dir_down)
THING_BODY_GET_BOOL_AT(thing_is_dir_left_at, is_dir_left)
THING_BODY_GET_BOOL_AT(thing_is_dir_none_at, is_dir_none)
THING_BODY_GET_BOOL_AT(thing_is_dir_right_at, is_dir_right)
THING_BODY_GET_BOOL_AT(thing_is_dir_tl_at, is_dir_tl)
THING_BODY_GET_BOOL_AT(thing_is_dir_tr_at, is_dir_tr)
THING_BODY_GET_BOOL_AT(thing_is_dir_up_at, is_dir_up)
THING_BODY_GET_BOOL_AT(thing_is_dirt_at, is_dirt)
THING_BODY_GET_BOOL_AT(thing_is_door_at, is_door)
THING_BODY_GET_BOOL_AT(thing_is_droppable_at, is_droppable)
THING_BODY_GET_BOOL_AT(thing_is_ethereal_at, is_ethereal)
THING_BODY_GET_BOOL_AT(thing_is_ethereal_minion_generator_at, is_ethereal_minion_generator)
THING_BODY_GET_BOOL_AT(thing_is_explosion_at, is_explosion)
THING_BODY_GET_BOOL_AT(thing_is_extreme_hazard_at, is_extreme_hazard)
THING_BODY_GET_BOOL_AT(thing_is_fearless_at, is_fearless)
THING_BODY_GET_BOOL_AT(thing_is_fire_at, is_fire)
THING_BODY_GET_BOOL_AT(thing_is_flammable_at, is_flammable)
THING_BODY_GET_BOOL_AT(thing_is_floating_at, is_floating)
THING_BODY_GET_BOOL_AT(thing_is_floor_at, is_floor)
THING_BODY_GET_BOOL_AT(thing_is_floor_deco_at, is_floor_deco)
THING_BODY_GET_BOOL_AT(thing_is_food_at, is_food)
THING_BODY_GET_BOOL_AT(thing_is_food_eater_at, is_food_eater)
THING_BODY_GET_BOOL_AT(thing_is_gfx_water_at, is_gfx_water)
THING_BODY_GET_BOOL_AT(thing_is_gold_at, is_gold)
THING_BODY_GET_BOOL_AT(thing_is_hazard_at, is_hazard)
THING_BODY_GET_BOOL_AT(thing_is_humanoid_at, is_humanoid)
THING_BODY_GET_BOOL_AT(thing_is_hunger_insatiable_at, is_hunger_insatiable)
THING_BODY_GET_BOOL_AT(thing_is_intelligent_at, is_intelligent)
THING_BODY_GET_BOOL_AT(thing_is_interesting_at, is_interesting)
THING_BODY_GET_BOOL_AT(thing_is_item_at, is_item)
THING_BODY_GET_BOOL_AT(thing_is_item_carrier_at, is_item_carrier)
THING_BODY_GET_BOOL_AT(thing_is_item_collected_as_gold_at, is_item_collected_as_gold)
THING_BODY_GET_BOOL_AT(thing_is_item_eater_at, is_item_eater)
THING_BODY_GET_BOOL_AT(thing_is_item_not_stackable_at, is_item_not_stackable)
THING_BODY_GET_BOOL_AT(thing_is_jelly_at, is_jelly)
THING_BODY_GET_BOOL_AT(thing_is_jelly_baby_at, is_jelly_baby)
THING_BODY_GET_BOOL_AT(thing_is_jelly_baby_eater_at, is_jelly_baby_eater)
THING_BODY_GET_BOOL_AT(thing_is_jelly_eater_at, is_jelly_eater)
THING_BODY_GET_BOOL_AT(thing_is_jelly_parent_at, is_jelly_parent)
THING_BODY_GET_BOOL_AT(thing_is_jumper_at, is_jumper)
THING_BODY_GET_BOOL_AT(thing_is_jumper_chance_d1000_at, is_jumper_chance_d1000)
THING_BODY_GET_BOOL_AT(thing_is_jumper_distance_at, is_jumper_distance)
THING_BODY_GET_BOOL_AT(thing_is_jumper_on_low_hp_chance_d1000_at, is_jumper_on_low_hp_chance_d1000)
THING_BODY_GET_BOOL_AT(thing_is_key_at, is_key)
THING_BODY_GET_BOOL_AT(thing_is_killed_on_hit_or_miss_at, is_killed_on_hit_or_miss)
THING_BODY_GET_BOOL_AT(thing_is_killed_on_hitting_at, is_killed_on_hitting)
THING_BODY_GET_BOOL_AT(thing_is_laser_at, is_laser)
THING_BODY_GET_BOOL_AT(thing_is_laser_target_select_automatically_when_chosen_at, is_laser_target_select_automatically_when_chosen)
THING_BODY_GET_BOOL_AT(thing_is_lava_at, is_lava)
THING_BODY_GET_BOOL_AT(thing_is_light_blocker_at, is_light_blocker)
THING_BODY_GET_BOOL_AT(thing_is_living_at, is_living)
THING_BODY_GET_BOOL_AT(thing_is_loggable_for_important_stuff_at, is_loggable_for_important_stuff)
THING_BODY_GET_BOOL_AT(thing_is_loggable_for_unimportant_stuff_at, is_loggable_for_unimportant_stuff)
THING_BODY_GET_BOOL_AT(thing_is_meat_at, is_meat)
THING_BODY_GET_BOOL_AT(thing_is_meat_eater_at, is_meat_eater)
THING_BODY_GET_BOOL_AT(thing_is_minion_at, is_minion)
THING_BODY_GET_BOOL_AT(thing_is_minion_generator_at, is_minion_generator)
THING_BODY_GET_BOOL_AT(thing_is_monst_at, is_monst)
THING_BODY_GET_BOOL_AT(thing_is_moveable_at, is_moveable)
THING_BODY_GET_BOOL_AT(thing_is_movement_blocking_hard_at, is_movement_blocking_hard)
THING_BODY_GET_BOOL_AT(thing_is_movement_blocking_soft_at, is_movement_blocking_soft)
THING_BODY_GET_BOOL_AT(thing_is_msg_at, is_msg)
THING_BODY_GET_BOOL_AT(thing_is_no_tile_at, is_no_tile)
THING_BODY_GET_BOOL_AT(thing_is_on_fire_at, is_on_fire)
THING_BODY_GET_BOOL_AT(thing_is_player_at, is_player)
THING_BODY_GET_BOOL_AT(thing_is_poison_at, is_poison)
THING_BODY_GET_BOOL_AT(thing_is_poison_immune_at, is_poison_immune)
THING_BODY_GET_BOOL_AT(thing_is_potion_at, is_potion)
THING_BODY_GET_BOOL_AT(thing_is_potion_eater_at, is_potion_eater)
THING_BODY_GET_BOOL_AT(thing_is_projectile_at, is_projectile)
THING_BODY_GET_BOOL_AT(thing_is_removeable_if_out_of_slots_at, is_removeable_if_out_of_slots)
THING_BODY_GET_BOOL_AT(thing_is_resurrectable_at, is_resurrectable)
THING_BODY_GET_BOOL_AT(thing_is_ripple_at, is_ripple)
THING_BODY_GET_BOOL_AT(thing_is_rock_at, is_rock)
THING_BODY_GET_BOOL_AT(thing_is_rrr10_at, is_rrr10)
THING_BODY_GET_BOOL_AT(thing_is_rrr11_at, is_rrr11)
THING_BODY_GET_BOOL_AT(thing_is_rrr12_at, is_rrr12)
THING_BODY_GET_BOOL_AT(thing_is_rrr13_at, is_rrr13)
THING_BODY_GET_BOOL_AT(thing_is_rrr14_at, is_rrr14)
THING_BODY_GET_BOOL_AT(thing_is_rrr15_at, is_rrr15)
THING_BODY_GET_BOOL_AT(thing_is_rrr16_at, is_rrr16)
THING_BODY_GET_BOOL_AT(thing_is_rrr17_at, is_rrr17)
THING_BODY_GET_BOOL_AT(thing_is_rrr18_at, is_rrr18)
THING_BODY_GET_BOOL_AT(thing_is_rrr19_at, is_rrr19)
THING_BODY_GET_BOOL_AT(thing_is_rrr1_at, is_rrr1)
THING_BODY_GET_BOOL_AT(thing_is_rrr20_at, is_rrr20)
THING_BODY_GET_BOOL_AT(thing_is_rrr21_at, is_rrr21)
THING_BODY_GET_BOOL_AT(thing_is_rrr22_at, is_rrr22)
THING_BODY_GET_BOOL_AT(thing_is_rrr23_at, is_rrr23)
THING_BODY_GET_BOOL_AT(thing_is_rrr24_at, is_rrr24)
THING_BODY_GET_BOOL_AT(thing_is_rrr25_at, is_rrr25)
THING_BODY_GET_BOOL_AT(thing_is_rrr26_at, is_rrr26)
THING_BODY_GET_BOOL_AT(thing_is_rrr27_at, is_rrr27)
THING_BODY_GET_BOOL_AT(thing_is_rrr28_at, is_rrr28)
THING_BODY_GET_BOOL_AT(thing_is_rrr29_at, is_rrr29)
THING_BODY_GET_BOOL_AT(thing_is_rrr2_at, is_rrr2)
THING_BODY_GET_BOOL_AT(thing_is_rrr30_at, is_rrr30)
THING_BODY_GET_BOOL_AT(thing_is_rrr31_at, is_rrr31)
THING_BODY_GET_BOOL_AT(thing_is_rrr32_at, is_rrr32)
THING_BODY_GET_BOOL_AT(thing_is_rrr33_at, is_rrr33)
THING_BODY_GET_BOOL_AT(thing_is_rrr34_at, is_rrr34)
THING_BODY_GET_BOOL_AT(thing_is_rrr35_at, is_rrr35)
THING_BODY_GET_BOOL_AT(thing_is_rrr36_at, is_rrr36)
THING_BODY_GET_BOOL_AT(thing_is_rrr37_at, is_rrr37)
THING_BODY_GET_BOOL_AT(thing_is_rrr38_at, is_rrr38)
THING_BODY_GET_BOOL_AT(thing_is_rrr39_at, is_rrr39)
THING_BODY_GET_BOOL_AT(thing_is_rrr3_at, is_rrr3)
THING_BODY_GET_BOOL_AT(thing_is_rrr40_at, is_rrr40)
THING_BODY_GET_BOOL_AT(thing_is_rrr41_at, is_rrr41)
THING_BODY_GET_BOOL_AT(thing_is_rrr42_at, is_rrr42)
THING_BODY_GET_BOOL_AT(thing_is_rrr43_at, is_rrr43)
THING_BODY_GET_BOOL_AT(thing_is_rrr44_at, is_rrr44)
THING_BODY_GET_BOOL_AT(thing_is_rrr45_at, is_rrr45)
THING_BODY_GET_BOOL_AT(thing_is_rrr46_at, is_rrr46)
THING_BODY_GET_BOOL_AT(thing_is_rrr47_at, is_rrr47)
THING_BODY_GET_BOOL_AT(thing_is_rrr48_at, is_rrr48)
THING_BODY_GET_BOOL_AT(thing_is_rrr49_at, is_rrr49)
THING_BODY_GET_BOOL_AT(thing_is_rrr4_at, is_rrr4)
THING_BODY_GET_BOOL_AT(thing_is_rrr50_at, is_rrr50)
THING_BODY_GET_BOOL_AT(thing_is_rrr51_at, is_rrr51)
THING_BODY_GET_BOOL_AT(thing_is_rrr52_at, is_rrr52)
THING_BODY_GET_BOOL_AT(thing_is_rrr53_at, is_rrr53)
THING_BODY_GET_BOOL_AT(thing_is_rrr54_at, is_rrr54)
THING_BODY_GET_BOOL_AT(thing_is_rrr55_at, is_rrr55)
THING_BODY_GET_BOOL_AT(thing_is_rrr56_at, is_rrr56)
THING_BODY_GET_BOOL_AT(thing_is_rrr57_at, is_rrr57)
THING_BODY_GET_BOOL_AT(thing_is_rrr58_at, is_rrr58)
THING_BODY_GET_BOOL_AT(thing_is_rrr59_at, is_rrr59)
THING_BODY_GET_BOOL_AT(thing_is_rrr5_at, is_rrr5)
THING_BODY_GET_BOOL_AT(thing_is_rrr60_at, is_rrr60)
THING_BODY_GET_BOOL_AT(thing_is_rrr61_at, is_rrr61)
THING_BODY_GET_BOOL_AT(thing_is_rrr62_at, is_rrr62)
THING_BODY_GET_BOOL_AT(thing_is_rrr63_at, is_rrr63)
THING_BODY_GET_BOOL_AT(thing_is_rrr64_at, is_rrr64)
THING_BODY_GET_BOOL_AT(thing_is_rrr65_at, is_rrr65)
THING_BODY_GET_BOOL_AT(thing_is_rrr66_at, is_rrr66)
THING_BODY_GET_BOOL_AT(thing_is_rrr67_at, is_rrr67)
THING_BODY_GET_BOOL_AT(thing_is_rrr68_at, is_rrr68)
THING_BODY_GET_BOOL_AT(thing_is_rrr69_at, is_rrr69)
THING_BODY_GET_BOOL_AT(thing_is_rrr6_at, is_rrr6)
THING_BODY_GET_BOOL_AT(thing_is_rrr70_at, is_rrr70)
THING_BODY_GET_BOOL_AT(thing_is_rrr71_at, is_rrr71)
THING_BODY_GET_BOOL_AT(thing_is_rrr72_at, is_rrr72)
THING_BODY_GET_BOOL_AT(thing_is_rrr73_at, is_rrr73)
THING_BODY_GET_BOOL_AT(thing_is_rrr74_at, is_rrr74)
THING_BODY_GET_BOOL_AT(thing_is_rrr75_at, is_rrr75)
THING_BODY_GET_BOOL_AT(thing_is_rrr76_at, is_rrr76)
THING_BODY_GET_BOOL_AT(thing_is_rrr77_at, is_rrr77)
THING_BODY_GET_BOOL_AT(thing_is_rrr78_at, is_rrr78)
THING_BODY_GET_BOOL_AT(thing_is_rrr79_at, is_rrr79)
THING_BODY_GET_BOOL_AT(thing_is_rrr7_at, is_rrr7)
THING_BODY_GET_BOOL_AT(thing_is_rrr80_at, is_rrr80)
THING_BODY_GET_BOOL_AT(thing_is_rrr81_at, is_rrr81)
THING_BODY_GET_BOOL_AT(thing_is_rrr82_at, is_rrr82)
THING_BODY_GET_BOOL_AT(thing_is_rrr83_at, is_rrr83)
THING_BODY_GET_BOOL_AT(thing_is_rrr84_at, is_rrr84)
THING_BODY_GET_BOOL_AT(thing_is_rrr85_at, is_rrr85)
THING_BODY_GET_BOOL_AT(thing_is_rrr86_at, is_rrr86)
THING_BODY_GET_BOOL_AT(thing_is_rrr87_at, is_rrr87)
THING_BODY_GET_BOOL_AT(thing_is_rrr88_at, is_rrr88)
THING_BODY_GET_BOOL_AT(thing_is_rrr89_at, is_rrr89)
THING_BODY_GET_BOOL_AT(thing_is_rrr8_at, is_rrr8)
THING_BODY_GET_BOOL_AT(thing_is_rrr90_at, is_rrr90)
THING_BODY_GET_BOOL_AT(thing_is_rrr91_at, is_rrr91)
THING_BODY_GET_BOOL_AT(thing_is_rrr92_at, is_rrr92)
THING_BODY_GET_BOOL_AT(thing_is_rrr93_at, is_rrr93)
THING_BODY_GET_BOOL_AT(thing_is_rrr94_at, is_rrr94)
THING_BODY_GET_BOOL_AT(thing_is_rrr95_at, is_rrr95)
THING_BODY_GET_BOOL_AT(thing_is_rrr96_at, is_rrr96)
THING_BODY_GET_BOOL_AT(thing_is_rrr9_at, is_rrr9)
THING_BODY_GET_BOOL_AT(thing_is_secret_door_at, is_secret_door)
THING_BODY_GET_BOOL_AT(thing_is_sewer_wall_at, is_sewer_wall)
THING_BODY_GET_BOOL_AT(thing_is_shallow_water_at, is_shallow_water)
THING_BODY_GET_BOOL_AT(thing_is_shovable_at, is_shovable)
THING_BODY_GET_BOOL_AT(thing_is_shown_on_leftbar_at, is_shown_on_leftbar)
THING_BODY_GET_BOOL_AT(thing_is_shown_uniquely_on_leftbar_at, is_shown_uniquely_on_leftbar)
THING_BODY_GET_BOOL_AT(thing_is_skill_at, is_skill)
THING_BODY_GET_BOOL_AT(thing_is_smoke_at, is_smoke)
THING_BODY_GET_BOOL_AT(thing_is_spawner_at, is_spawner)
THING_BODY_GET_BOOL_AT(thing_is_stamina_check_at, is_stamina_check)
THING_BODY_GET_BOOL_AT(thing_is_steal_item_chance_d1000_at, is_steal_item_chance_d1000)
THING_BODY_GET_BOOL_AT(thing_is_temporary_bag_at, is_temporary_bag)
THING_BODY_GET_BOOL_AT(thing_is_throwable_at, is_throwable)
THING_BODY_GET_BOOL_AT(thing_is_thrown_automatically_when_chosen_at, is_thrown_automatically_when_chosen)
THING_BODY_GET_BOOL_AT(thing_is_torch_at, is_torch)
THING_BODY_GET_BOOL_AT(thing_is_treasure_at, is_treasure)
THING_BODY_GET_BOOL_AT(thing_is_treasure_class_a_at, is_treasure_class_a)
THING_BODY_GET_BOOL_AT(thing_is_treasure_class_b_at, is_treasure_class_b)
THING_BODY_GET_BOOL_AT(thing_is_treasure_class_c_at, is_treasure_class_c)
THING_BODY_GET_BOOL_AT(thing_is_treasure_eater_at, is_treasure_eater)
THING_BODY_GET_BOOL_AT(thing_is_undead_at, is_undead)
THING_BODY_GET_BOOL_AT(thing_is_usable_at, is_usable)
THING_BODY_GET_BOOL_AT(thing_is_used_automatically_when_selected_at, is_used_automatically_when_selected)
THING_BODY_GET_BOOL_AT(thing_is_used_when_thrown_at, is_used_when_thrown)
THING_BODY_GET_BOOL_AT(thing_is_visible_at, is_visible)
THING_BODY_GET_BOOL_AT(thing_is_wall_at, is_wall)
THING_BODY_GET_BOOL_AT(thing_is_wall_dungeon_at, is_wall_dungeon)
THING_BODY_GET_BOOL_AT(thing_is_wand_at, is_wand)
THING_BODY_GET_BOOL_AT(thing_is_water_at, is_water)
THING_BODY_GET_BOOL_AT(thing_is_water_lover_at, is_water_lover)
THING_BODY_GET_BOOL_AT(thing_is_weapon_at, is_weapon)
THING_BODY_GET_BOOL_AT(thing_is_weapon_wielder_at, is_weapon_wielder)
THING_BODY_GET_INT(thing_get_current_damage, get_current_damage)
THING_BODY_GET_INT(thing_get_health, get_health)
THING_BODY_GET_INT(thing_get_health_max, get_health_max)
THING_BODY_GET_INT(thing_get_stamina, get_stamina)
THING_BODY_GET_INT(thing_get_stamina_max, get_stamina_max)
THING_BODY_GET_STRING(thing_get_name, text_name)
THING_BODY_GET_THING(thing_get_immediate_minion_owner_id, get_immediate_minion_owner_id)
THING_BODY_GET_THING(thing_get_immediate_owner_id, get_immediate_owner_id)
THING_BODY_GET_THING(thing_get_immediate_spawned_owner_id, get_immediate_spawned_owner_id)
THING_BODY_SET_INT(thing_decr_current_damage, decr_current_damage)
THING_BODY_SET_INT(thing_decr_health, decr_health)
THING_BODY_SET_INT(thing_decr_health_max, decr_health_max)
THING_BODY_SET_INT(thing_decr_stamina, decr_stamina)
THING_BODY_SET_INT(thing_decr_stamina_max, decr_stamina_max)
THING_BODY_SET_INT(thing_incr_current_damage, incr_current_damage)
THING_BODY_SET_INT(thing_incr_health, incr_health)
THING_BODY_SET_INT(thing_incr_health_max, incr_health_max)
THING_BODY_SET_INT(thing_incr_stamina, incr_stamina)
THING_BODY_SET_INT(thing_incr_stamina_max, incr_stamina_max)
THING_BODY_SET_INT(thing_set_current_damage, set_current_damage)
THING_BODY_SET_INT(thing_set_health, set_health)
THING_BODY_SET_INT(thing_set_health_max, set_health_max)
THING_BODY_SET_INT(thing_set_stamina, set_stamina)
THING_BODY_SET_INT(thing_set_stamina_max, set_stamina_max)
THING_BODY_SET_THING(thing_skill_activate, skill_activate)
THING_BODY_SET_THING(thing_skill_deactivate, skill_deactivate)
