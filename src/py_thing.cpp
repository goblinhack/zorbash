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
#include "my_ptrcheck.h"

#define THING_BODY_SET_INT(__func__, __api__)                                       \
PyObject *__func__ (PyObject *obj, PyObject *args, PyObject *keywds)                \
{	                                                                            \
    uint32_t id = 0;	                                                            \
    uint32_t value = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", (char*)"value", 0};	                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Ii", kwlist, &id, &value)) {    \
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
{	                                                                            \
    uint32_t id = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", 0};	                                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {             \
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
{	                                                                            \
    uint32_t id = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", 0};	                                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {             \
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
{	                                                                            \
    uint32_t id = 0;	                                                            \
    uint32_t oid = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", (char*)"oid", 0};	                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &oid)) {      \
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
{	                                                                            \
    uint32_t id = 0;	                                                            \
    static char *kwlist[] = {(char*)"id", 0};	                                    \
	                                                                            \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {             \
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

THING_BODY_SET_INT(thing_set_health, set_health)
THING_BODY_SET_INT(thing_incr_health, incr_health)
THING_BODY_SET_INT(thing_decr_health, decr_health)
THING_BODY_GET_INT(thing_get_health, get_health)

THING_BODY_SET_INT(thing_set_health_max, set_health_max)
THING_BODY_SET_INT(thing_incr_health_max, incr_health_max)
THING_BODY_SET_INT(thing_decr_health_max, decr_health_max)
THING_BODY_GET_INT(thing_get_health_max, get_health_max)

THING_BODY_SET_INT(thing_set_stamina, set_stamina)
THING_BODY_SET_INT(thing_incr_stamina, incr_stamina)
THING_BODY_SET_INT(thing_decr_stamina, decr_stamina)
THING_BODY_GET_INT(thing_get_stamina, get_stamina)

THING_BODY_SET_INT(thing_set_stamina_max, set_stamina_max)
THING_BODY_SET_INT(thing_incr_stamina_max, incr_stamina_max)
THING_BODY_SET_INT(thing_decr_stamina_max, decr_stamina_max)
THING_BODY_GET_INT(thing_get_stamina_max, get_stamina_max)

THING_BODY_SET_INT(thing_set_current_damage, set_current_damage)
THING_BODY_SET_INT(thing_incr_current_damage, incr_current_damage)
THING_BODY_SET_INT(thing_decr_current_damage, decr_current_damage)
THING_BODY_GET_INT(thing_get_current_damage, get_current_damage)

THING_BODY_SET_THING(thing_skill_activate, skill_activate)
THING_BODY_SET_THING(thing_skill_deactivate, skill_deactivate)

THING_BODY_GET_STRING(thing_get_name, text_name)

THING_BODY_GET_THING(thing_get_immediate_spawned_owner_id, get_immediate_spawned_owner_id)
THING_BODY_GET_THING(thing_get_immediate_minion_owner_id, get_immediate_minion_owner_id)
THING_BODY_GET_THING(thing_get_immediate_owner_id, get_immediate_owner_id)
