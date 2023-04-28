//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_level.hpp"
#include <map>
// REMOVED #include <string>

#include "my_callstack.hpp"
#include "my_main.hpp"

std::string py_obj_to_std_string(const PyObject *py_str)
{
  TRACE_AND_INDENT();
  PyObject   *py_encstr;
  std::string outstr;
  char       *str;

  py_encstr = nullptr;
  str       = nullptr;

  if (! PyUnicode_Check((PyObject *) py_str)) {
    ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_str)->tp_name);
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

  outstr = std::string(str);

err_out:

  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  return outstr;
}
