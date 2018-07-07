/*
 * Copyright (C) 2011-2017 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_python.h"
#include "my_tile.h"
#include "my_dmap.h"

PyObject *dmap_process_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    dmap d;

    PyObject *e = 0;

    static char *kwlist[] = {(char*) "arr", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", kwlist, &e)) {
        Py_RETURN_NONE;
    }

    if (!e) {
        ERR("tile_load_arr, missing arr attr");
        Py_RETURN_NONE;
    }

    int x;
    int y;

    for (x=0; x<MAP_WIDTH; x++) {
        PyObject * o;
        o = PyList_GetItem(e, x);
        if (!o) {
            continue;
        }

        for (y=0; y<MAP_HEIGHT; y++) {
            PyObject * i;
            i = PyList_GetItem(o, y);
            if (!i) {
                continue;
            }

            int val = py_obj_to_int(i);

            d.val[x][y] = val;
        }
    }

#ifdef DMAP_DEBUG
    for (y=0; y<MAP_HEIGHT; y++) {
        for (x=0; x<MAP_WIDTH; x++) {
            int val = d.val[x][y];

            if (val == 64) {
                printf("+");
            } else if (val == 63) {
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("--------\n");
#endif

    dmap_process(&d);

#ifdef DMAP_DEBUG
    dmap_print(&d);
#endif

    for (x=0; x<MAP_WIDTH; x++) {
        PyObject * o;
        o = PyList_GetItem(e, x);
        if (!o) {
            continue;
        }

        for (y=0; y<MAP_HEIGHT; y++) {
            PyObject *val = Py_BuildValue("i", d.val[x][y]);

            if (PyList_SetItem(o, y, val) == -1) {
                DIE("set dmap item %d,%d failed", x, y)
            }
        }
    }

    Py_RETURN_NONE;
}
