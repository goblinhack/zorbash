//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_python.h"
#include "my_tile.h"

PyObject *tile_load_arr_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *file = 0;
    char *name = 0;
    int width = 0;
    int height = 0;
    PyObject *e = 0;

    static char *kwlist[] = {
        (char*) "file",
        (char*) "name", (char*) "width", (char*) "height", (char*) "arr", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ssiiO", kwlist, &file, &name, &width, &height, &e)) {
        Py_RETURN_NONE;
    }

    if (!file) {
        ERR("tile_load_arr, missing file attr");
        Py_RETURN_NONE;
    }

    if (!name) {
        ERR("tile_load_arr, missing name attr");
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

    DBG("Python: tile_load_arr(file=%s, name=%s, width=%d, height=%d, ...)", file, name, width, height);

    for (i=0; i<numLines; i++){
        PyObject * strObj;
        strObj = PyList_GetItem(e, i); /* Can't fail */
        if (!strObj) {
            continue;
        }

        arr[i] = py_obj_to_str(strObj);
    }

    tile_load_arr(std::string(file ? file : ""),
                  std::string(name ? name : ""),
                  width, height, numLines, arr);

    for (i=0; i<numLines; i++){
        if (!arr[i]) {
            continue;
        }

        myfree((char*) arr[i]);
    }

    Py_RETURN_NONE;
}

PyObject *tile_load_arr_color_and_black_and_white_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *file = 0;
    char *name = 0;
    int width = 0;
    int height = 0;
    PyObject *e = 0;

    static char *kwlist[] = {
        (char*) "file",
        (char*) "name", (char*) "width", (char*) "height", (char*) "arr", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ssiiO", kwlist, &file, &name, &width, &height, &e)) {
        Py_RETURN_NONE;
    }

    if (!file) {
        ERR("tile_load_arr, missing file attr");
        Py_RETURN_NONE;
    }

    if (!name) {
        ERR("tile_load_arr_color_and_black_and_white, missing name attr");
        Py_RETURN_NONE;
    }

    if (!width) {
        ERR("tile_load_arr_color_and_black_and_white, missing width attr");
        Py_RETURN_NONE;
    }

    if (!height) {
        ERR("tile_load_arr_color_and_black_and_white, missing height attr");
        Py_RETURN_NONE;
    }

    if (!e) {
        ERR("tile_load_arr_color_and_black_and_white, missing arr attr");
        Py_RETURN_NONE;
    }

    int numLines = PyList_Size(e);
    const char *arr[numLines + 1];
    int i;

    memset(arr, 0, sizeof(arr));

    DBG("Python: tile_load_arr_color_and_black_and_white(file=%s, name=%s, width=%d, height=%d, ...)", file, name, width, height);

    for (i=0; i<numLines; i++){
        PyObject * strObj;
        strObj = PyList_GetItem(e, i); /* Can't fail */
        if (!strObj) {
            continue;
        }

        arr[i] = py_obj_to_str(strObj);
    }

    tile_load_arr_color_and_black_and_white(
            std::string(file ? file : ""),
            std::string(name ? name : ""),
            width, height, numLines, arr);

    for (i=0; i<numLines; i++){
        if (!arr[i]) {
            continue;
        }

        myfree((char*) arr[i]);
    }

    Py_RETURN_NONE;
}
