//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_python.h"
#include "my_callstack.h"
#include "my_main.h"
#include "my_tile.h"
#include "my_ptrcheck.h"

PyObject *tile_load_arr_(PyObject *obj, PyObject *args, PyObject *keywds) {
  TRACE_AND_INDENT();
  char *    file   = 0;
  char *    name   = 0;
  int       width  = 0;
  int       height = 0;
  PyObject *e      = 0;

  static char *kwlist[] = {(char *) "file", (char *) "name", (char *) "width", (char *) "height", (char *) "arr", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ssiiO", kwlist, &file, &name, &width, &height, &e)) {
    ERR("tile_load_arr: Bad args");
    Py_RETURN_FALSE;
  }

  if (! file) {
    ERR("tile_load_arr: Missing file attr");
    Py_RETURN_FALSE;
  }

  if (! name) {
    ERR("tile_load_arr: Missing name attr");
    Py_RETURN_FALSE;
  }

  if (! width) {
    ERR("tile_load_arr: Missing width attr");
    Py_RETURN_FALSE;
  }

  if (! height) {
    ERR("tile_load_arr: Missing height attr");
    Py_RETURN_FALSE;
  }

  if (! e) {
    ERR("tile_load_arr: Missing arr attr");
    Py_RETURN_FALSE;
  }

  int         numLines = PyList_Size(e);
  const char *arr[numLines + 1];
  int         i;

  memset(arr, 0, sizeof(arr));

  PY_DBG("tile_load_arr:file=%s, name=%s, width=%d, height=%d, ...)", file, name, width, height);

  for (i = 0; i < numLines; i++) {
    PyObject *strObj;
    strObj = PyList_GetItem(e, i); /* Can't fail */
    if (! strObj) {
      continue;
    }

    arr[i] = py_obj_to_str(strObj);
  }

  tile_load_arr(std::string(file ? file : ""), std::string(name ? name : ""), width, height, numLines, arr);

  for (i = 0; i < numLines; i++) {
    if (! arr[i]) {
      continue;
    }

    myfree((char *) arr[i]);
  }

  Py_RETURN_TRUE;
}

PyObject *tile_load_arr_sprites_(PyObject *obj, PyObject *args, PyObject *keywds) {
  TRACE_AND_INDENT();
  char *    file   = 0;
  char *    name   = 0;
  int       width  = 0;
  int       height = 0;
  PyObject *e      = 0;

  static char *kwlist[] = {(char *) "file", (char *) "name", (char *) "width", (char *) "height", (char *) "arr", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ssiiO", kwlist, &file, &name, &width, &height, &e)) {
    ERR("tile_load_arr: Bad args");
    Py_RETURN_FALSE;
  }

  if (! file) {
    ERR("tile_load_arr: Sprites, missing file attr");
    Py_RETURN_FALSE;
  }

  if (! name) {
    ERR("tile_load_arr: Sprites, missing name attr");
    Py_RETURN_FALSE;
  }

  if (! width) {
    ERR("tile_load_arr: Sprites, missing width attr");
    Py_RETURN_FALSE;
  }

  if (! height) {
    ERR("tile_load_arr: Sprites, missing height attr");
    Py_RETURN_FALSE;
  }

  if (! e) {
    ERR("tile_load_arr: Sprites, missing arr attr");
    Py_RETURN_FALSE;
  }

  int         numLines = PyList_Size(e);
  const char *arr[numLines + 1];
  int         i;

  memset(arr, 0, sizeof(arr));

  PY_DBG("tile_load_arr:sprites(file=%s, name=%s, width=%d, height=%d, ...)", file, name, width, height);

  for (i = 0; i < numLines; i++) {
    PyObject *strObj;
    strObj = PyList_GetItem(e, i); /* Can't fail */
    if (! strObj) {
      continue;
    }

    arr[i] = py_obj_to_str(strObj);
    PY_DBG("tile_load_arr:sprites(\"%s\")", arr[i]);
  }

  tile_load_arr_sprites(std::string(file ? file : ""), std::string(name ? name : ""), width, height, numLines, arr);

  for (i = 0; i < numLines; i++) {
    if (! arr[i]) {
      continue;
    }

    myfree((char *) arr[i]);
  }

  Py_RETURN_TRUE;
}
