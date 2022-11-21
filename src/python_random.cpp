//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_level.hpp"
// REMOVED #include "my_py_thing.hpp"
// REMOVED #include "my_py_tp.hpp"
// REMOVED #include <frameobject.h>
// REMOVED #include <map>

// REMOVED #include "my_ascii.hpp"
#include "my_callstack.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_python.hpp"
#include "my_random.hpp"

PyObject *pcg_randint(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  int x = 0;
  int y = 0;

  static char *kwlist[] = {(char *) "x", (char *) "y", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &x, &y)) {
    return nullptr;
  }

  //
  // Python style. We don't use pythons so we can get consistent random
  // numbers with the one C uses.
  //
  return (Py_BuildValue("i", pcg_random_range_inclusive(x, y)));
}

PyObject *non_pcg_randint(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  int x = 0;
  int y = 0;

  static char *kwlist[] = {(char *) "x", (char *) "y", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &x, &y)) {
    return nullptr;
  }

  //
  // Python style. We don't use pythons so we can get consistent random
  // numbers with the one C uses.
  //
  return (Py_BuildValue("i", non_pcg_random_range_inclusive(x, y)));
}
