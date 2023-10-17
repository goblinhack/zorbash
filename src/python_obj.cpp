//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_level.hpp"

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"

char *py_obj_to_string(const PyObject *py_str)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  char     *outstr = nullptr;
  char     *str;

  py_encstr = nullptr;
  str       = nullptr;

  if (! PyUnicode_Check((PyObject *) py_str)) {
    PY_ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_str)->tp_name);
    goto err_out;
  }

  py_encstr = PyUnicode_AsEncodedString((PyObject *) py_str, "utf-8", nullptr);
  if (! py_encstr) {
    goto err_out;
  }

  str = PyBytes_AS_STRING(py_encstr);
  if (! str) {
    goto err_out;
  }

  outstr = dupstr(str, __FUNCTION__);

err_out:

  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  return outstr;
}

int py_obj_to_int(PyObject *py_obj)
{
  TRACE_AND_INDENT();
  int val;

  val = 0;

  if (! PyLong_Check((PyObject *) py_obj)) {
    PY_ERR("Object is a %s, not a int object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsLong(py_obj);

err_out:
  if (PyErr_Occurred()) {
    PY_ERR("Int conversion failed");
  }

  return val;
}

int py_obj_to_bool(PyObject *py_obj)
{
  TRACE_AND_INDENT();
  int val;

  val = 0;

  if (! PyLong_Check((PyObject *) py_obj)) {
    PY_ERR("Object is a %s, not a int object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsLong(py_obj);

err_out:
  if (PyErr_Occurred()) {
    PY_ERR("Int(bool) conversion failed");
  }

  return (val != 0);
}

uint64_t py_obj_to_uint64(PyObject *py_obj)
{
  TRACE_AND_INDENT();
  uint64_t val;

  val = 0;

  if (! PyLong_Check((PyObject *) py_obj)) {
    PY_ERR("Object is a %s, not a uint64 object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsUnsignedLongLong(py_obj);

err_out:

  if (PyErr_Occurred()) {
    PY_ERR("Int conversion failed");
  }

  return val;
}

double py_obj_to_double(PyObject *py_obj)
{
  TRACE_AND_INDENT();
  double val;

  val = 0;

  if (PyLong_Check((PyObject *) py_obj)) {
    val = PyLong_AsDouble(py_obj);
  } else if (PyFloat_Check((PyObject *) py_obj)) {
    val = PyFloat_AsDouble(py_obj);
  } else {
    PY_ERR("Object is a %s, not a double object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

err_out:

  if (PyErr_Occurred()) {
    PY_ERR("Int conversion failed");
  }

  return val;
}

int py_obj_attr_int(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  int       i = 0;

  py_encstr = nullptr;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    PY_ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *) py_obj, attr);
  if (! py_encstr) {
    goto err_out;
  }

  i = py_obj_to_int(py_encstr);

err_out:
  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  if (PyErr_Occurred()) {
    PY_ERR("Int conversion failed");
  }

  return i;
}

uint64_t py_obj_attr_uint64(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  uint64_t  i = 0;

  py_encstr = nullptr;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    PY_ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *) py_obj, attr);
  if (! py_encstr) {
    goto err_out;
  }

  i = py_obj_to_uint64(py_encstr);

err_out:
  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  if (PyErr_Occurred()) {
    PY_ERR("Int conversion failed");
  }

  return i;
}

double py_obj_attr_double(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  double    i = 0;

  py_encstr = nullptr;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    PY_ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *) py_obj, attr);
  if (! py_encstr) {
    goto err_out;
  }

  i = py_obj_to_double(py_encstr);

err_out:
  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  if (PyErr_Occurred()) {
    PY_ERR("Int conversion failed");
  }

  return i;
}

char *py_obj_attr_str(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  char     *outstr = nullptr;
  char     *str;

  py_encstr = nullptr;
  str       = nullptr;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    PY_ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *) py_obj, attr);
  if (! py_encstr) {
    goto err_out;
  }

  str = py_obj_to_string(py_encstr);
  if (! str) {
    goto err_out;
  }

  outstr = str;

err_out:

  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  return outstr;
}

PyObject *py_obj_attr(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;

  py_encstr = nullptr;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    PY_ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *) py_obj, attr);
  if (! py_encstr) {
    goto err_out;
  }

  return (py_encstr);

err_out:
  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  if (PyErr_Occurred()) {
    PY_ERR("Obj lookup conversion failed");
  }

  Py_RETURN_NONE;
}
