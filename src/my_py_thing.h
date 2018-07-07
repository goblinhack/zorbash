/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_PY_THING_H_
#define _MY_PY_THING_H_

#include <Python.h>

PyObject *thing_new_python(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_set_tilename(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_set_tp(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_destroyed(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_push(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_pop(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_move_to(PyObject *obj, PyObject *args, PyObject *keywds);

#endif
