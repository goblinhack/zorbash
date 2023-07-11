//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_level.hpp"

#include "my_callstack.hpp"
#include "my_random.hpp"

PyObject *pcg_randint(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  int x = 0;
  int y = 0;

  static char *kwlist[] = {(char *) "x", (char *) "y", nullptr};

  TRACE_NO_INDENT();
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

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &x, &y)) {
    return nullptr;
  }

  //
  // Python style. We don't use pythons so we can get consistent random
  // numbers with the one C uses.
  //
  return (Py_BuildValue("i", non_pcg_random_range_inclusive(x, y)));
}
