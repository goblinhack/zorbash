/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_python.h"
#include "my_wid_tiles.h"

PyObject *wid_tiles_load_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *a = 0;
    double scale = 1.0;

    static char *kwlist[] = {(char*) "name", (char*) "scale", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "sd", kwlist, &a, &scale)) {
        Py_RETURN_NONE;
    }

    if (!a) {
        ERR("wid_tiles_load, missing file attr");
        Py_RETURN_NONE;
    }

    /*
    LOG("wid_tiles_load(name=%s, scale=%g)", a, scale);
     */

    wid_tiles_load(a, scale);

    Py_RETURN_NONE;
}

