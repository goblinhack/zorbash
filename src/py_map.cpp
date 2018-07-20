/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_python.h"
#include "my_tile.h"

PyObject *map_load_chunk_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *chunk_name = 0;
    int width = 0;
    int height = 0;
    PyObject *e = 0;

    static char *kwlist[] = {(char*) "chunk_name", (char*) "width", (char*) "height", (char*) "data", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "siiO", kwlist, &chunk_name, &width, &height, &e)) {
        Py_RETURN_NONE;
    }

    if (!chunk_name) {
        ERR("map_load_chunk, missing chunk_name attr");
        Py_RETURN_NONE;
    }

    if (!width) {
        ERR("map_load_chunk, missing width attr");
        Py_RETURN_NONE;
    }

    if (!height) {
        ERR("map_load_chunk, missing height attr");
        Py_RETURN_NONE;
    }

    if (!e) {
        ERR("map_load_chunk, missing data attr");
        Py_RETURN_NONE;
    }

    int numLines = PyList_Size(e);
    const char *data[numLines + 1];
    int i;

    memset(data, 0, sizeof(data));
printf("%ld",sizeof(data));

    DBG("Python: map_load_chunk(chunk_name=%s, width=%d, height=%d, ...)", 
        chunk_name, width, height);

    std::string s;

    for (i=0; i<numLines; i++){
        PyObject * strObj;
        strObj = PyList_GetItem(e, i); /* Can't fail */
        if (!strObj) {
            continue;
        }

        s += std::string(py_obj_to_str(strObj));
    }

//    map_load_chunk(std::string(chunk_name ? chunk_name : ""),
//                        width, height, numLines, s);

    for (i=0; i<numLines; i++){
        if (!data[i]) {
            continue;
        }

        myfree((char*) data[i]);
    }

    Py_RETURN_NONE;
}
