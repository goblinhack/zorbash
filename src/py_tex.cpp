//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_python.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include <string.h>  // do not remove
#include <strings.h> // do not remove

PyObject *tex_load_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *file = nullptr;
  char *name = nullptr;

  static char *kwlist[] = {(char *) "file", (char *) "name", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ss", kwlist, &file, &name)) {
    ERR("tex_load: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (! file) {
    ERR("tex_load: Missing file attr");
    Py_RETURN_FALSE;
  }

  if (! name) {
    ERR("tex_load: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("tex_load(file=%s, name=%s)", file, name);

  tex_load(file, name, GL_NEAREST);

  Py_RETURN_TRUE;
}
