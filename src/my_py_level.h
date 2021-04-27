//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PY_LEVEL_H_
#define _MY_PY_LEVEL_H_
#include <Python.h>

PyObject *level_get_all(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_add_(PyObject *obj, PyObject *args, PyObject *keywds);
#endif
