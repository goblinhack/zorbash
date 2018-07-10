/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_python.h"
#include "my_thing.h"
#include "my_py_thing.h"

PyObject *thing_new_python (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    PyObject *py_class = 0;
    const char *tp_name;
    long int thing_id = 0;

    static char *kwlist[] = {(char*) "thing", (char*) "thing_id", (char*) "tp", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|ls", kwlist,
                                     &py_class,
                                     &thing_id,
                                     &tp_name)) {
        return (0);
    }

    if (!py_class) {
        DIE("thing_new, missing name attr");
        return (0);
    }

    char *thing_name = py_obj_attr_str(py_class, "name");
    if (!thing_name) {
        DIE("thing_new, missing tp name");
        return (0);
    }

    thing_new(thing_name, thing_id, tp_name);

    myfree(thing_name);

    Py_RETURN_NONE;
}

#define THING_BODY_STRING_FN(__fn__)                                            \
PyObject *thing_ ## __fn__ (PyObject *obj, PyObject *args, PyObject *keywds)    \
{	                                                                        \
    PyObject *py_class = 0;	                                                \
    char *thing_name = 0;	                                                \
    const char *value = 0;	                                                \
    thingp t;                                                                   \
	                                                                        \
    static char *kwlist[] = {(char*) "class", (char*) "value", 0};	        \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|s", kwlist, &py_class,    \
                                     &value)) {	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        DIE("%s, missing class", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!value) {	                                                        \
        DIE("%s, missing value", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    thing_name = py_obj_attr_str(py_class, "name");	                        \
    if (!thing_name) {	                                                        \
        DIE("%s, missing tp name", __FUNCTION__);	                        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    /* LOG("python-to-c: %s(%s -> \"%s\")", __FUNCTION__, thing_name, value); */	\
	                                                                        \
    t = thing_find(thing_name);	                                                \
    if (!t) {	                                                                \
        DIE("%s, cannot find thing %s", __FUNCTION__, thing_name);	        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    t->__fn__(value);                                                           \
	                                                                        \
done:	                                                                        \
    if (thing_name) {	                                                        \
        myfree(thing_name);	                                                \
    }	                                                                        \
	                                                                        \
    Py_RETURN_NONE;	                                                        \
}	                                                                        \

#define THING_BODY_DOUBLE_DOUBLE_FN(__fn__)                                     \
PyObject *thing_ ## __fn__ (PyObject *obj, PyObject *args, PyObject *keywds)    \
{	                                                                        \
    PyObject *py_class = 0;	                                                \
    char *thing_name = 0;	                                                \
    const double x = 0;	                                                        \
    const double y = 0;	                                                        \
    thingp t;                                                                   \
	                                                                        \
    static char *kwlist[] = {(char*) "class",                                   \
                             (char*) "x",                                       \
                             (char*) "y",                                       \
                             0 };	                                        \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|ii", kwlist, &py_class,   \
                                     &x, &y)) {	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        DIE("%s, missing class", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!value) {	                                                        \
        DIE("%s, missing value", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    thing_name = py_obj_attr_str(py_class, "name");	                        \
    if (!thing_name) {	                                                        \
        DIE("%s, missing tp name", __FUNCTION__);	                        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    /* LOG("python-to-c: %s(%s -> \"%s\")", __FUNCTION__, thing_name, value); */	\
	                                                                        \
    t = thing_find(thing_name);	                                                \
    if (!t) {	                                                                \
        DIE("%s, cannot find thing %s", __FUNCTION__, thing_name);	        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    t->__fn__(x, y);                                                            \
	                                                                        \
done:	                                                                        \
    if (thing_name) {	                                                        \
        myfree(thing_name);	                                                \
    }	                                                                        \
	                                                                        \
    Py_RETURN_NONE;	                                                        \
}	                                                                        \

#define THING_BODY_VOID_FN(__fn__)                                              \
PyObject *thing_ ## __fn__ (PyObject *obj, PyObject *args, PyObject *keywds)    \
{	                                                                        \
    PyObject *py_class = 0;	                                                \
    char *thing_name = 0;	                                                \
    thingp t;                                                                   \
	                                                                        \
    static char *kwlist[] = {(char*) "class", 0};	                        \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", kwlist, &py_class)) {   \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        DIE("%s, missing class", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    thing_name = py_obj_attr_str(py_class, "name");	                        \
    if (!thing_name) {	                                                        \
        DIE("%s, missing tp name", __FUNCTION__);	                        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    /* LOG("python-to-c: %s(%s)", __FUNCTION__, thing_name); */	                \
	                                                                        \
    t = thing_find(thing_name);	                                                \
    if (!t) {	                                                                \
        DIE("%s, cannot find thing %s", __FUNCTION__, thing_name);	        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    t->__fn__();                                                                \
	                                                                        \
done:	                                                                        \
    if (thing_name) {	                                                        \
        myfree(thing_name);	                                                \
    }	                                                                        \
	                                                                        \
    Py_RETURN_NONE;	                                                        \
}	                                                                        \

PyObject *thing_push (PyObject *obj, PyObject *args, PyObject *keywds)
{	
    PyObject *py_class = 0;	
    char *thing_name = 0;	
    PyObject *o = 0;
    fpoint3d p;
    thingp t;
	
    static char *kwlist[] = {(char*) "class", 0};
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O",
                                     kwlist, &py_class)) {
        return (0);	
    }	
	
    if (!py_class) {	
        DIE("%s, missing class", __FUNCTION__);	
        return (0);	
    }	
	
    thing_name = py_obj_attr_str(py_class, "name");	
    if (!thing_name) {	
        DIE("%s, missing tp name", __FUNCTION__);	

        if (thing_name) {	
            myfree(thing_name);	
        }	
        return (o);	
    }	
	
    PyObject *P = py_obj_attr(py_class, "at");	
    p.x = py_obj_attr_double(P, "x");	
    p.y = py_obj_attr_double(P, "y");	
    p.z = py_obj_attr_double(P, "z");	
	
    /*
    lOG("python-to-c: %s(%s -> %f, %f, %f)", __FUNCTION__,
        thing_name, p.x, p.y, p.z);	
     */
	
    t = thing_find(thing_name);	
    if (!t) {	
        DIE("%s, cannot find thing %s", __FUNCTION__, thing_name);	
        goto done;	
    }	
	
    CON("TBD thing_push");
//    o = t->push(p);
	
done:	
    if (thing_name) {	
        myfree(thing_name);	
    }	
	
    return (o);	
}	

PyObject *thing_move_to (PyObject *obj, PyObject *args, PyObject *keywds) 
{	
    PyObject *py_class = 0;	
    char *thing_name = 0;	
    double x = -1;	
    double y = -1;	
    thingp t;
	
    static char *kwlist[] = {(char*) "class",
                             (char*) "x",
                             (char*) "y",
                             0 };	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|dd", kwlist, &py_class,
                                     &x, &y)) {	
        DIE("%s, parse arguments failed", __FUNCTION__);	
    }	

    if (x == -1) {
        DIE("%s, missing mandatory argument x", __FUNCTION__);	
    }

    if (y == -1) {
        DIE("%s, missing mandatory argument y", __FUNCTION__);	
    }
	
	
    if (!py_class) {	
        DIE("%s, missing class", __FUNCTION__);	
    }	
	
    thing_name = py_obj_attr_str(py_class, "name");	
    if (!thing_name) {	
        DIE("%s, missing tp name", __FUNCTION__);	
    }	
	
    // LOG("python-to-c: %s(%s ->(%f, %f))", __FUNCTION__, thing_name, x, y); 
	
    t = thing_find(thing_name);	
    if (!t) {	
        DIE("%s, cannot find thing %s", __FUNCTION__, thing_name);	
        goto done;	
    }	
	
    t->move_to(fpoint3d(x, y, 0));
	
done:	
    if (thing_name) {	
        myfree(thing_name);	
    }	
	
    Py_RETURN_NONE;
}	

THING_BODY_STRING_FN(destroyed)
THING_BODY_STRING_FN(set_tilename)
THING_BODY_STRING_FN(set_tp)
THING_BODY_VOID_FN(pop)
