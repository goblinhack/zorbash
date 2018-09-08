/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_python.h"
#include "my_tile.h"

PyObject *tile_load_arr_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *tex_name = 0;
    int width = 0;
    int height = 0;
    PyObject *e = 0;

    static char *kwlist[] = {(char*) "tex_name", (char*) "width", (char*) "height", (char*) "arr", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "siiO", kwlist, &tex_name, &width, &height, &e)) {
        Py_RETURN_NONE;
    }

    if (!tex_name) {
        ERR("tile_load_arr, missing tex_name attr");
        Py_RETURN_NONE;
    }

    if (!width) {
        ERR("tile_load_arr, missing width attr");
        Py_RETURN_NONE;
    }

    if (!height) {
        ERR("tile_load_arr, missing height attr");
        Py_RETURN_NONE;
    }

    if (!e) {
        ERR("tile_load_arr, missing arr attr");
        Py_RETURN_NONE;
    }

    int numLines = PyList_Size(e);
    const char *arr[numLines + 1];
    int i;

    memset(arr, 0, sizeof(arr));

    DBG("Python: tile_load_arr(tex_name=%s, width=%d, height=%d, ...)", tex_name, width, height);

    for (i=0; i<numLines; i++){
        PyObject * strObj;
        strObj = PyList_GetItem(e, i); /* Can't fail */
        if (!strObj) {
            continue;
        }

        arr[i] = py_obj_to_str(strObj);
    }

    tile_load_arr(std::string(tex_name ? tex_name : ""),
                  width, height, numLines, arr);

    for (i=0; i<numLines; i++){
        if (!arr[i]) {
            continue;
        }

        myfree((char*) arr[i]);
    }

    Py_RETURN_NONE;
}

PyObject *tile_get_size_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *name = 0;
    Tilep tile = 0;

    static char *kwlist[] = {
        (char*) "name",
        0
    };

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist,
                                     &name)) {
        Py_RETURN_NONE;
    }

    if (!name) {
        DIE("no tile name");
    }

    tile = tile_find(name);
    if (!tile) {
        DIE("no tile named %s", name);
    }

    double w = tile_get_width(tile);
    double h = tile_get_height(tile);

    return (Py_BuildValue("dd", w, h));
}

