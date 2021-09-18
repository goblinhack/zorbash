//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_python.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_py_thing.h"
#include "my_array_bounds_check.h"
#include "my_hiscore.h"
#include "my_ptrcheck.h"

#define THING_BODY_SET_INT(__func__, __api__)                                       \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{_	                                                                            \
    uint32_t id = 0;	                                                            \
    uint32_t value = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", (char*)"value", 0};	                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Ii", kwlist, &id, &value)) {    \
        ERR("%s: Failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->thing_find(id);	                                            \
    if (!t) {	                                                                    \
        ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);	                    \
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
        ERR("%s: Failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->thing_find(id);	                                            \
    if (!t) {	                                                                    \
        ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);	                    \
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
        ERR("%s: Failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->thing_find(id);	                                            \
    if (!t) {	                                                                    \
        ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);	                    \
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
        ERR("%s: Failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!id) {	                                                                    \
        ERR("%s: No thing ID set", __FUNCTION__);	                            \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!oid) {	                                                                    \
        ERR("%s: No oid thing ID set", __FUNCTION__);	                            \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->thing_find(id);	                                            \
    if (!t) {	                                                                    \
        ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
                                                                                    \
    Thingp o = game->thing_find(oid);	                                            \
    if (!t) {	                                                                    \
        ERR("%s: Cannot find thing ID %u", __FUNCTION__, oid);	                    \
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
        ERR("%s: Failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!id) {	                                                                    \
        ERR("%s: No thing ID set", __FUNCTION__);	                            \
        return Py_BuildValue("I", 0);                                               \
    }	                                                                            \
	                                                                            \
    Thingp t = game->thing_find(id);	                                            \
    if (!t) {	                                                                    \
        ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);	                    \
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
        ERR("%s: Failed parsing keywords", __FUNCTION__);	                    \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    if (!id) {	                                                                    \
        ERR("%s: No thing ID set", __FUNCTION__);	                            \
        Py_RETURN_FALSE;	                                                    \
    }	                                                                            \
	                                                                            \
    Thingp t = game->thing_find(id);	                                            \
    if (!t) {	                                                                    \
        ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);	                    \
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
        ERR("%s: Failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!id) {	
        ERR("%s: No thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp t = game->thing_find(id);	
    if (!t) {	
        ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);	
        Py_RETURN_NONE;	
    }	
	
    Py_ssize_t size = 2;
    auto the_tuple = PyTuple_New(size);
    if (!the_tuple) {
        ERR("%s: Cannot create tuple for ID %u", __FUNCTION__, id);	
        Py_RETURN_NONE;	
    }	

    auto err = PyTuple_SetItem(the_tuple, (Py_ssize_t) 0, PyLong_FromLong((long) t->mid_at.x));
    if (err < 0) {
        ERR("%s: Cannot create tuple (a) for ID %u", __FUNCTION__, id);	
        Py_RETURN_NONE;	
    }

    err = PyTuple_SetItem(the_tuple, (Py_ssize_t) 1, PyLong_FromLong((long) t->mid_at.y));
    if (err < 0) {
        ERR("%s: Cannot create tuple (a) for ID %u", __FUNCTION__, id);	
        Py_RETURN_NONE;	
    }

    return the_tuple;
}

PyObject *thing_hit (PyObject *obj, PyObject *args, PyObject *keywds)
{_	
    uint32_t hitter_id = 0;	
    uint32_t target_id = 0;	
    static char *kwlist[] = {(char*)"hitter", (char*)"target", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &hitter_id, &target_id)) {
        ERR("%s: Failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!hitter_id) {	
        ERR("%s: No hitter thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp hitter = game->thing_find(hitter_id);	
    if (!hitter) {	
        ERR("%s: Cannot find hitter thing ID %u", __FUNCTION__, hitter_id);	
        Py_RETURN_NONE;	
    }	

    if (!target_id) {	
        ERR("%s: No target thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp target = game->thing_find(target_id);	
    if (!target) {	
        ERR("%s: Cannot find target thing ID %u", __FUNCTION__, target_id);	
        Py_RETURN_NONE;	
    }	

    hitter->log("Hit with %s target %s", hitter->to_string().c_str(), target->to_string().c_str());

    if (target->is_hit_by(hitter)) {
        Py_RETURN_TRUE;	
    } else {
        Py_RETURN_FALSE;	
    }
}

PyObject *thing_possible_to_attack (PyObject *obj, PyObject *args, PyObject *keywds)
{_	
    uint32_t hitter_id = 0;	
    uint32_t target_id = 0;	
    static char *kwlist[] = {(char*)"hitter", (char*)"target", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &hitter_id, &target_id)) {
        ERR("%s: Failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!hitter_id) {	
        ERR("%s: No hitter thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp hitter = game->thing_find(hitter_id);	
    if (!hitter) {	
        ERR("%s: Cannot find hitter thing ID %u", __FUNCTION__, hitter_id);	
        Py_RETURN_NONE;	
    }	

    if (!target_id) {	
        ERR("%s: No target thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp target = game->thing_find(target_id);	
    if (!target) {	
        ERR("%s: Cannot find target thing ID %u", __FUNCTION__, target_id);	
        Py_RETURN_NONE;	
    }	

    hitter->log("Check if possible to attack target %s",
                target->to_string().c_str());

    if (hitter->possible_to_attack(target)) {
        hitter->log("Check if possible to target %s; yes",
                target->to_string().c_str());
        Py_RETURN_TRUE;	
    } else {
        hitter->log("Check if possible to attack %s; no",
                    target->to_string().c_str());
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
        ERR("%s: Failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!owner_id) {	
        ERR("%s: No owner thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp owner = game->thing_find(owner_id);	
    if (!owner) {	
        ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);	
        Py_RETURN_NONE;	
    }	

    if (!item) {	
        ERR("%s: No item thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!target_id) {	
        ERR("%s: No target thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp target = game->thing_find(target_id);	
    if (!target) {	
        ERR("%s: Cannot find target thing ID %u", __FUNCTION__, target_id);	
        Py_RETURN_NONE;	
    }	

    owner->log("Fire %s at %s", item, target->to_string().c_str());

    auto what = std::string(item);
    auto fire_what = tp_find(what);
    if (fire_what->is_projectile()) {
        if (owner->projectile_fire_at(std::string(item), target)) {
            Py_RETURN_TRUE;	
        } else {
            Py_RETURN_FALSE;	
        }
    } else if (fire_what->is_laser()) {
        if (owner->laser_fire_at(std::string(item), target)) {
            Py_RETURN_TRUE;	
        } else {
            Py_RETURN_FALSE;	
        }
    } else {
        owner->err("Cannot fire %s at %s", item, target->to_string().c_str());
        Py_RETURN_FALSE;	
    }
}

PyObject *thing_killed_by (PyObject *obj, PyObject *args, PyObject *keywds)
{_	
    uint32_t owner_id = 0;	
    char *reason = nullptr;
    uint32_t killer_id = 0;	
    static char *kwlist[] = {(char*)"owner", (char*)"reason", (char*)"killer", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &owner_id, &reason, &killer_id)) {
        ERR("%s: Failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!owner_id) {	
        ERR("%s: No owner thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp owner = game->thing_find(owner_id);	
    if (!owner) {	
        ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);	
        Py_RETURN_NONE;	
    }	

    if (!reason) {	
        ERR("%s: No reason thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!killer_id) {	
        ERR("%s: No killer thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp killer = game->thing_find(killer_id);	
    if (!killer) {	
        ERR("%s: Cannot find killer thing ID %u", __FUNCTION__, killer_id);	
        Py_RETURN_NONE;	
    }	

    owner->log("Killed by %s, reason %s", killer->to_string().c_str(), reason);
    owner->dead(killer, "%s", reason);

    Py_RETURN_NONE;	
}

PyObject *thing_killed (PyObject *obj, PyObject *args, PyObject *keywds)
{_	
    uint32_t owner_id = 0;	
    char *reason = nullptr;
    static char *kwlist[] = {(char*)"owner", (char*)"reason", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &reason)) {
        ERR("%s: Failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!owner_id) {	
        ERR("%s: No owner thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp owner = game->thing_find(owner_id);	
    if (!owner) {	
        ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);	
        Py_RETURN_NONE;	
    }	

    if (!reason) {	
        ERR("%s: No reason thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    owner->log("Killed: Reason %s", reason);
    owner->dead("%s", reason);
    Py_RETURN_NONE;	
}

PyObject *thing_msg (PyObject *obj, PyObject *args, PyObject *keywds)
{_	
    uint32_t owner_id = 0;	
    char *msg = nullptr;
    static char *kwlist[] = {(char*)"owner", (char*)"msg", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &msg)) {
        ERR("%s: Failed parsing keywords", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    if (!owner_id) {	
        ERR("%s: No owner thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp owner = game->thing_find(owner_id);	
    if (!owner) {	
        ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);	
        Py_RETURN_NONE;	
    }	

    if (!msg) {	
        ERR("%s: No msg thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    //
    // If not reachable, suppress the msg
    //
    if (owner->distance_to_player() < DMAP_IS_PASSABLE) {
        TOPCON("%s", msg);
    }

    Py_RETURN_NONE;	
}

PyObject *thing_sound_play_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *name = 0;
    uint32_t owner_id = 0;	

    static char *kwlist[] = {(char*)"owner", (char*) "name", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &name)) {
        ERR("thing_sound_play: Bad arguments");
        Py_RETURN_FALSE;
    }

    if (!owner_id) {	
        ERR("%s: No owner thing ID set", __FUNCTION__);	
        Py_RETURN_NONE;	
    }	
	
    Thingp owner = game->thing_find(owner_id);	
    if (!owner) {	
        ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);	
        Py_RETURN_NONE;	
    }	

    if (!name) {
        ERR("thing_sound_play: Missing name attr");
        Py_RETURN_FALSE;
    }

    PY_DBG("thing_sound_play(name=%s)", name);

    std::string alias = name;
    if (!owner->thing_sound_play(alias)) {
        Py_RETURN_FALSE;
    }

    Py_RETURN_TRUE;
}

PyObject *thing_sound_play_channel_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    uint32_t owner_id = 0;	
    char *name = 0;
    int channel = 0;

    static char *kwlist[] = {(char*)"owner", (char*) "channel", (char*) "name", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Iis", kwlist, &owner_id, &channel, &name)) {
        ERR("thing_sound_play_channel: Bad arguments");
        Py_RETURN_FALSE;
    }

    Thingp owner = game->thing_find(owner_id);	
    if (!owner) {	
        ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);	
        Py_RETURN_NONE;	
    }	

    if (!name) {
        ERR("thing_sound_play: Missing name attr");
        Py_RETURN_FALSE;
    }
    if (!name) {
        ERR("thing_sound_play_channel: Missing name attr");
        Py_RETURN_FALSE;
    }

    PY_DBG("sound_play_channel(channel=%d, name=%s)", channel, name);

    std::string alias = name;
    if (!owner->thing_sound_play_channel(channel, alias)) {
        Py_RETURN_FALSE;
    }

    Py_RETURN_TRUE;
}

THING_BODY_GET_BOOL(level_is_able_to_fire_at, is_able_to_fire_at)
THING_BODY_GET_BOOL(level_is_attackable_by_monst, is_attackable_by_monst)
THING_BODY_GET_BOOL(level_is_attackable_by_player, is_attackable_by_player)
THING_BODY_GET_BOOL(thing_ai_vision_distance, ai_vision_distance)
THING_BODY_GET_BOOL(thing_gfx_flickers, gfx_flickers)
THING_BODY_GET_BOOL(thing_gfx_water, gfx_water)
THING_BODY_GET_BOOL(thing_is_able_to_change_levels, is_able_to_change_levels)
THING_BODY_GET_BOOL(thing_is_able_to_fall, is_able_to_fall)
THING_BODY_GET_BOOL(thing_is_able_to_see_through_doors, is_able_to_see_through_doors)
THING_BODY_GET_BOOL(thing_is_able_to_walk_through_walls, is_able_to_walk_through_walls)
THING_BODY_GET_BOOL(thing_is_acid, is_acid)
THING_BODY_GET_BOOL(thing_is_acid_lover, is_acid_lover)
THING_BODY_GET_BOOL(thing_is_tickable, is_tickable)
THING_BODY_GET_BOOL(thing_is_alive_monst, is_alive_monst)
THING_BODY_GET_BOOL(thing_is_always_hit, is_always_hit)
THING_BODY_GET_BOOL(thing_is_ascend_dungeon, is_ascend_dungeon)
THING_BODY_GET_BOOL(thing_is_ascend_sewer, is_ascend_sewer)
THING_BODY_GET_BOOL(thing_is_auto_collect_item, is_auto_collect_item)
THING_BODY_GET_BOOL(thing_is_bag, is_bag)
THING_BODY_GET_BOOL(thing_is_barrel, is_barrel)
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
THING_BODY_GET_BOOL(thing_is_dead_or_dying_on_shove, is_dead_on_shove)
THING_BODY_GET_BOOL(thing_is_dead_or_dying, is_dead_or_dying)
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
THING_BODY_GET_BOOL(thing_is_floating, is_floating)
THING_BODY_GET_BOOL(thing_is_floor, is_floor)
THING_BODY_GET_BOOL(thing_is_floor_deco, is_floor_deco)
THING_BODY_GET_BOOL(thing_is_food, is_food)
THING_BODY_GET_BOOL(thing_is_food_eater, is_food_eater)
THING_BODY_GET_BOOL(thing_is_gold, is_gold)
THING_BODY_GET_BOOL(thing_is_hazard, is_hazard)
THING_BODY_GET_BOOL(thing_is_humanoid, is_humanoid)
THING_BODY_GET_BOOL(thing_is_hunger_insatiable, is_hunger_insatiable)
THING_BODY_GET_BOOL(thing_is_intelligent, is_intelligent)
THING_BODY_GET_BOOL(thing_is_interesting, is_interesting)
THING_BODY_GET_BOOL(thing_is_bag_item, is_bag_item)
THING_BODY_GET_BOOL(thing_is_item_carrier, is_item_carrier)
THING_BODY_GET_BOOL(thing_is_collected_as_gold, is_collected_as_gold)
THING_BODY_GET_BOOL(thing_is_item_eater, is_item_eater)
THING_BODY_GET_BOOL(thing_is_bag_item_not_stackable, is_bag_item_not_stackable)
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
THING_BODY_GET_BOOL(thing_is_movement_blocking_wall_or_locked_door, is_movement_blocking_wall_or_locked_door)
THING_BODY_GET_BOOL(thing_is_movement_blocking_but_destructable, is_movement_blocking_but_destructable)
THING_BODY_GET_BOOL(thing_is_msg, is_msg)
THING_BODY_GET_BOOL(thing_is_no_tile, is_no_tile)
THING_BODY_GET_BOOL(thing_is_on_fire, is_on_fire)
THING_BODY_GET_BOOL(thing_is_player, is_player)
THING_BODY_GET_BOOL(thing_is_poison, is_poison)
THING_BODY_GET_BOOL(thing_is_potion, is_potion)
THING_BODY_GET_BOOL(thing_is_potion_eater, is_potion_eater)
THING_BODY_GET_BOOL(thing_is_projectile, is_projectile)
THING_BODY_GET_BOOL(thing_is_removeable_if_out_of_slots, is_removeable_if_out_of_slots)
THING_BODY_GET_BOOL(thing_is_resurrectable, is_resurrectable)
THING_BODY_GET_BOOL(thing_is_ripple, is_ripple)
THING_BODY_GET_BOOL(thing_is_rock, is_rock)
THING_BODY_GET_BOOL(thing_unused_flag1, unused_flag1)
THING_BODY_GET_BOOL(thing_unused_flag10, unused_flag10)
THING_BODY_GET_BOOL(thing_unused_flag11, unused_flag11)
THING_BODY_GET_BOOL(thing_unused_flag12, unused_flag12)
THING_BODY_GET_BOOL(thing_unused_flag13, unused_flag13)
THING_BODY_GET_BOOL(thing_unused_flag14, unused_flag14)
THING_BODY_GET_BOOL(thing_unused_flag15, unused_flag15)
THING_BODY_GET_BOOL(thing_unused_flag16, unused_flag16)
THING_BODY_GET_BOOL(thing_unused_flag17, unused_flag17)
THING_BODY_GET_BOOL(thing_unused_flag18, unused_flag18)
THING_BODY_GET_BOOL(thing_unused_flag19, unused_flag19)
THING_BODY_GET_BOOL(thing_unused_flag2, unused_flag2)
THING_BODY_GET_BOOL(thing_unused_flag20, unused_flag20)
THING_BODY_GET_BOOL(thing_unused_flag21, unused_flag21)
THING_BODY_GET_BOOL(thing_unused_flag22, unused_flag22)
THING_BODY_GET_BOOL(thing_unused_flag23, unused_flag23)
THING_BODY_GET_BOOL(thing_unused_flag24, unused_flag24)
THING_BODY_GET_BOOL(thing_unused_flag25, unused_flag25)
THING_BODY_GET_BOOL(thing_unused_flag26, unused_flag26)
THING_BODY_GET_BOOL(thing_unused_flag27, unused_flag27)
THING_BODY_GET_BOOL(thing_unused_flag28, unused_flag28)
THING_BODY_GET_BOOL(thing_unused_flag29, unused_flag29)
THING_BODY_GET_BOOL(thing_unused_flag3, unused_flag3)
THING_BODY_GET_BOOL(thing_unused_flag30, unused_flag30)
THING_BODY_GET_BOOL(thing_unused_flag31, unused_flag31)
THING_BODY_GET_BOOL(thing_unused_flag32, unused_flag32)
THING_BODY_GET_BOOL(thing_unused_flag33, unused_flag33)
THING_BODY_GET_BOOL(thing_unused_flag34, unused_flag34)
THING_BODY_GET_BOOL(thing_unused_flag35, unused_flag35)
THING_BODY_GET_BOOL(thing_unused_flag36, unused_flag36)
THING_BODY_GET_BOOL(thing_unused_flag37, unused_flag37)
THING_BODY_GET_BOOL(thing_unused_flag38, unused_flag38)
THING_BODY_GET_BOOL(thing_unused_flag39, unused_flag39)
THING_BODY_GET_BOOL(thing_unused_flag4, unused_flag4)
THING_BODY_GET_BOOL(thing_unused_flag40, unused_flag40)
THING_BODY_GET_BOOL(thing_unused_flag41, unused_flag41)
THING_BODY_GET_BOOL(thing_unused_flag42, unused_flag42)
THING_BODY_GET_BOOL(thing_unused_flag43, unused_flag43)
THING_BODY_GET_BOOL(thing_unused_flag44, unused_flag44)
THING_BODY_GET_BOOL(thing_unused_flag45, unused_flag45)
THING_BODY_GET_BOOL(thing_unused_flag46, unused_flag46)
THING_BODY_GET_BOOL(thing_unused_flag47, unused_flag47)
THING_BODY_GET_BOOL(thing_unused_flag48, unused_flag48)
THING_BODY_GET_BOOL(thing_unused_flag49, unused_flag49)
THING_BODY_GET_BOOL(thing_unused_flag5, unused_flag5)
THING_BODY_GET_BOOL(thing_unused_flag50, unused_flag50)
THING_BODY_GET_BOOL(thing_unused_flag51, unused_flag51)
THING_BODY_GET_BOOL(thing_unused_flag52, unused_flag52)
THING_BODY_GET_BOOL(thing_is_ai_wanderer, is_ai_wanderer)
THING_BODY_GET_BOOL(thing_is_organic, is_organic)
THING_BODY_GET_BOOL(thing_is_glass, is_glass)
THING_BODY_GET_BOOL(thing_is_stone, is_stone)
THING_BODY_GET_BOOL(thing_is_item_organic, is_item_organic)
THING_BODY_GET_BOOL(thing_is_metal, is_metal)
THING_BODY_GET_BOOL(thing_is_wooden, is_wooden)
THING_BODY_GET_BOOL(thing_unused_flag6, unused_flag6)
THING_BODY_GET_BOOL(thing_is_engulfer, is_engulfer)
THING_BODY_GET_BOOL(thing_is_health_booster, is_health_booster)
THING_BODY_GET_BOOL(thing_is_tmp_thing, is_tmp_thing)
THING_BODY_GET_BOOL(thing_is_debug_type, is_debug_type)
THING_BODY_GET_BOOL(thing_is_hittable, is_hittable)
THING_BODY_GET_BOOL(thing_is_alive_on_end_of_anim, is_alive_on_end_of_anim)
THING_BODY_GET_BOOL(thing_is_dead_on_end_of_anim, is_dead_on_end_of_anim)
THING_BODY_GET_BOOL(thing_ai_enemy_memory, ai_enemy_memory)
THING_BODY_GET_BOOL(thing_is_debug_path, is_debug_path)
THING_BODY_GET_BOOL(thing_is_key_collector, is_key_collector)
THING_BODY_GET_BOOL(thing_unused_flag7, unused_flag7)
THING_BODY_GET_BOOL(thing_is_item_collector, is_item_collector)
THING_BODY_GET_BOOL(thing_is_item, is_item)
THING_BODY_GET_BOOL(thing_is_bag_item_container, is_bag_item_container)
THING_BODY_GET_BOOL(thing_is_treasure_type_chest, is_treasure_type_chest)
THING_BODY_GET_BOOL(thing_is_openable, is_openable)
THING_BODY_GET_BOOL(thing_gfx_long_shadow_caster, gfx_long_shadow_caster)
THING_BODY_GET_BOOL(thing_gfx_solid_shadow, gfx_solid_shadow)
THING_BODY_GET_BOOL(thing_is_sticky, is_sticky)
THING_BODY_GET_BOOL(thing_is_sword, is_sword)
THING_BODY_GET_BOOL(thing_is_skillstone, is_skillstone)
THING_BODY_GET_BOOL(thing_unused_flag8, unused_flag8)
THING_BODY_GET_BOOL(thing_enchant_level, enchant_level)
THING_BODY_GET_BOOL(thing_enchant_max, enchant_max)
THING_BODY_GET_BOOL(thing_is_enchantstone, is_enchantstone)
THING_BODY_GET_BOOL(thing_is_enchantable, is_enchantable)
THING_BODY_GET_BOOL(thing_is_indestructible, is_indestructible)
THING_BODY_GET_BOOL(thing_is_bones, is_bones)
THING_BODY_GET_BOOL(thing_is_soft_body, is_soft_body)
THING_BODY_GET_BOOL(thing_is_foilage, is_foilage)
THING_BODY_GET_BOOL(thing_is_spiderweb, is_spiderweb)
THING_BODY_GET_BOOL(thing_gfx_very_short_shadow_caster, gfx_very_short_shadow_caster)
THING_BODY_GET_BOOL(thing_is_dry_grass, is_dry_grass)
THING_BODY_GET_BOOL(thing_unused_flag9, unused_flag9)
THING_BODY_GET_BOOL(thing_is_bridge, is_bridge)
THING_BODY_GET_BOOL(thing_loves_spiderwebs, loves_spiderwebs)
THING_BODY_GET_BOOL(thing_is_secret_door, is_secret_door)
THING_BODY_GET_BOOL(thing_is_sewer_wall, is_sewer_wall)
THING_BODY_GET_BOOL(thing_is_shallow_water, is_shallow_water)
THING_BODY_GET_BOOL(thing_is_shovable, is_shovable)
THING_BODY_GET_BOOL(thing_is_skill, is_skill)
THING_BODY_GET_BOOL(thing_is_smoke, is_smoke)
THING_BODY_GET_BOOL(thing_is_spawner, is_spawner)
THING_BODY_GET_BOOL(thing_is_stamina_check, is_stamina_check)
THING_BODY_GET_BOOL(thing_is_steal_item_chance_d1000, is_steal_item_chance_d1000)
THING_BODY_GET_BOOL(thing_is_engulf_chance_d1000, is_engulf_chance_d1000)
THING_BODY_GET_BOOL(thing_is_target_select_automatically_when_chosen, is_target_select_automatically_when_chosen)
THING_BODY_GET_BOOL(thing_is_throwable, is_throwable)
THING_BODY_GET_BOOL(thing_is_thrown_automatically_when_chosen, is_thrown_automatically_when_chosen)
THING_BODY_GET_BOOL(thing_is_torch, is_torch)
THING_BODY_GET_BOOL(thing_is_treasure_type, is_treasure_type)
THING_BODY_GET_BOOL(thing_is_treasure_class_a, is_treasure_class_a)
THING_BODY_GET_BOOL(thing_is_treasure_class_b, is_treasure_class_b)
THING_BODY_GET_BOOL(thing_is_treasure_class_c, is_treasure_class_c)
THING_BODY_GET_BOOL(thing_is_treasure_type_eater, is_treasure_type_eater)
THING_BODY_GET_BOOL(thing_is_undead, is_undead)
THING_BODY_GET_BOOL(thing_is_usable, is_usable)
THING_BODY_GET_BOOL(thing_is_used_automatically_when_selected, is_used_automatically_when_selected)
THING_BODY_GET_BOOL(thing_is_used_when_thrown, is_used_when_thrown)
THING_BODY_GET_BOOL(thing_is_very_combustible, is_very_combustible)
THING_BODY_GET_BOOL(thing_is_visible, is_visible)
THING_BODY_GET_BOOL(thing_is_wall, is_wall)
THING_BODY_GET_BOOL(thing_is_wall_dungeon, is_wall_dungeon)
THING_BODY_GET_BOOL(thing_is_wand, is_wand)
THING_BODY_GET_BOOL(thing_is_wand_eater, is_wand_eater)
THING_BODY_GET_BOOL(thing_is_water, is_water)
THING_BODY_GET_BOOL(thing_is_water_lover, is_water_lover)
THING_BODY_GET_BOOL(thing_is_weapon, is_weapon)
THING_BODY_GET_BOOL(thing_is_weapon_wielder, is_weapon_wielder)
THING_BODY_GET_BOOL(thing_loves_fire, loves_fire)
THING_BODY_GET_BOOL(thing_loves_poison, loves_poison)
THING_BODY_GET_INT(thing_get_current_damage, get_current_damage)
THING_BODY_GET_INT(thing_get_health, get_health)
THING_BODY_GET_INT(thing_get_health_max, get_health_max)
THING_BODY_GET_INT(thing_get_stamina, get_stamina)
THING_BODY_GET_INT(thing_get_stamina_max, get_stamina_max)
THING_BODY_GET_INT(thing_get_enchant, get_enchant)
THING_BODY_GET_INT(thing_get_enchant_max, get_enchant_max)
THING_BODY_GET_STRING(thing_get_name, text_name)
THING_BODY_GET_THING(thing_get_immediate_minion_owner_id, get_immediate_minion_owner_id)
THING_BODY_GET_THING(thing_get_immediate_owner_id, get_immediate_owner_id)
THING_BODY_GET_THING(thing_get_top_owner_id, get_top_owner_id)
THING_BODY_GET_THING(thing_get_immediate_spawned_owner_id, get_immediate_spawned_owner_id)
THING_BODY_SET_INT(thing_decr_current_damage, decr_current_damage)
THING_BODY_SET_INT(thing_decr_health, decr_health)
THING_BODY_SET_INT(thing_decr_health_max, decr_health_max)
THING_BODY_SET_INT(thing_decr_stamina, decr_stamina)
THING_BODY_SET_INT(thing_decr_stamina_max, decr_stamina_max)
THING_BODY_SET_INT(thing_decr_enchant, decr_enchant)
THING_BODY_SET_INT(thing_decr_enchant_max, decr_enchant_max)
THING_BODY_SET_INT(thing_incr_current_damage, incr_current_damage)
THING_BODY_SET_INT(thing_incr_health, incr_health)
THING_BODY_SET_INT(thing_incr_health_max, incr_health_max)
THING_BODY_SET_INT(thing_incr_stamina, incr_stamina)
THING_BODY_SET_INT(thing_incr_stamina_max, incr_stamina_max)
THING_BODY_SET_INT(thing_incr_enchant, incr_enchant)
THING_BODY_SET_INT(thing_incr_enchant_max, incr_enchant_max)
THING_BODY_SET_INT(thing_incr_charge_count, incr_charge_count)
THING_BODY_SET_INT(thing_decr_charge_count, decr_charge_count)
THING_BODY_GET_INT(thing_get_charge_count, get_charge_count)
THING_BODY_GET_INT(thing_get_initial_charge_count, get_initial_charge_count)
THING_BODY_SET_INT(thing_set_current_damage, set_current_damage)
THING_BODY_SET_INT(thing_set_health, set_health)
THING_BODY_SET_INT(thing_set_health_max, set_health_max)
THING_BODY_SET_INT(thing_set_stamina, set_stamina)
THING_BODY_SET_INT(thing_set_stamina_max, set_stamina_max)
THING_BODY_SET_INT(thing_set_enchant, set_enchant)
THING_BODY_SET_INT(thing_set_enchant_max, set_enchant_max)
THING_BODY_SET_THING(thing_skill_activate, skill_activate)
THING_BODY_SET_THING(thing_skill_deactivate, skill_deactivate)
THING_BODY_GET_INT(thing_get_damage_crush, get_damage_crush)
THING_BODY_GET_INT(thing_get_damage_bite, get_damage_bite)
THING_BODY_GET_INT(thing_get_damage_swallow, get_damage_swallow)
THING_BODY_GET_INT(thing_get_damage_melee, get_damage_melee)
