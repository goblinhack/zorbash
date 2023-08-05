//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals_extra.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_py_sdl.hpp"

PyObject *con_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  wchar_t *a = nullptr;

  if (! PyArg_ParseTuple(args, "u", &a)) {
    ERR("con: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    con(a);
  }

  Py_RETURN_TRUE;
}

PyObject *topcon_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  wchar_t *a = nullptr;

  if (! PyArg_ParseTuple(args, "u", &a)) {
    ERR("topcon: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    topcon(a);
  }

  Py_RETURN_TRUE;
}

PyObject *puts_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *a = nullptr;

  if (! PyArg_ParseTuple(args, "s", &a)) {
    ERR("puts: Bad args");
    Py_RETURN_FALSE;
  }

  fputs(a, MY_STDOUT);
  fflush(MY_STDOUT);
  printf("%s", a);

  Py_RETURN_TRUE;
}

PyObject *log_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *a = nullptr;

  if (! PyArg_ParseTuple(args, "s", &a)) {
    ERR("log: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    LOG("%s", a);
  }

  Py_RETURN_TRUE;
}

PyObject *err_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *a = nullptr;

  if (! PyArg_ParseTuple(args, "s", &a)) {
    ERR("err: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    ERR("%s", a);
  }

  Py_RETURN_TRUE;
}

PyObject *die_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *a = nullptr;

  if (! PyArg_ParseTuple(args, "s", &a)) {
    ERR("die: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    ERR("%s", a);
  }

  Py_RETURN_TRUE;
}

void py_err(void)
{
  TRACE_AND_INDENT();

  if (! my_mod) {
    return;
  }

  PyObject *err = PyErr_Occurred();
  if (! err) {
    return;
  }

  PyObject *ptype, *pvalue, *pbacktrace, *pyobj_str;
  PyObject *ret, *list, *string;
  PyObject *mod;
  char     *py_str;

  PyErr_Fetch(&ptype, &pvalue, &pbacktrace);
  PyErr_NormalizeException(&ptype, &pvalue, &pbacktrace);
  PyErr_Display(ptype, pvalue, pbacktrace);
  PyTraceBack_Print(pbacktrace, pvalue);

  pyobj_str = PyObject_Str(pvalue);
  py_str    = py_obj_to_string(pyobj_str);
  ERR("%s", py_str);
  myfree(py_str);

  mod  = PyImport_ImportModule("traceback");
  list = PyObject_CallMethod(mod, "format_exception", "OOO", ptype, pvalue, pbacktrace);
  if (list) {
    string = PyUnicode_FromString("\n");
    ret    = PyUnicode_Join(string, list);
    Py_DECREF(list);
    Py_DECREF(string);

    py_str = py_obj_to_string(ret);
    ERR("%s", py_str);
    myfree(py_str);

    Py_DECREF(ret);
  }

  PyErr_Clear();

  ERR("Python error");
}

void py_trace(void)
{
  TRACE_AND_INDENT();

  //
  // Calling py_err seems to suffice
  //
  // py_exec("import traceback\nprint(traceback.format_exc())\n");
  //
  py_err();
}
