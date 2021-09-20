//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <strings.h> // do not remove
#include <string.h> // do not remove
#include "my_sys.h"
#include "my_gl.h"
#include "my_python.h"
#include "my_tex.h"
#include "my_main.h"

PyObject *tex_load_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  char *file = 0;
  char *name = 0;

  static char *kwlist[] = {(char*) "file", (char*) "name", 0};

  if (!PyArg_ParseTupleAndKeywords(args, keywds, "ss", kwlist, &file, &name)) {
    ERR("tex_load: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (!file) {
    ERR("tex_load: Missing file attr");
    Py_RETURN_FALSE;
  }

  if (!name) {
    ERR("tex_load: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("tex_load(file=%s, name=%s)", file, name);

  tex_load(file, name, GL_NEAREST);

  Py_RETURN_TRUE;
}
