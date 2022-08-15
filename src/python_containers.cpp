//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_level.hpp"
#include "my_py_thing.hpp"
#include "my_py_tp.hpp"
#include <frameobject.h>
#include <map>

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_string.hpp"

std::vector< std::string > py_call_std_vector_string_fn(const char *module, const char *name, int val1, int val2,
                                                        int val3, int val4)
{
  std::vector< std::string > out;

  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return out;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    auto *pArgs  = Py_BuildValue("(iiii)", val1, val2, val3, val4);
    auto *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);

    for (auto i = 0; i < PyList_Size(pValue); i++) {
      auto py_item = PyList_GetItem(pValue, i);
      if (PyUnicode_Check(py_item)) {
        auto item = py_obj_to_std_string(py_item);
        out.push_back(item);
      }

      Py_DECREF(pValue);
      py_err();
    }
  } else {
    ERR("Cannot call python function: %s", name);
  }

  py_err();
  return out;
}

std::list< std::string > py_call_std_list_string_fn(const char *module, const char *name, int val1, int val2,
                                                    int val3, int val4)
{
  std::list< std::string > out;

  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return out;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    auto *pArgs  = Py_BuildValue("(iiii)", val1, val2, val3, val4);
    auto *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);

    for (auto i = 0; i < PyList_Size(pValue); i++) {
      auto py_item = PyList_GetItem(pValue, i);
      if (PyUnicode_Check(py_item)) {
        auto item = py_obj_to_std_string(py_item);
        out.push_back(item);
      }

      Py_DECREF(pValue);
      py_err();
    }
  } else {
    ERR("Cannot call python function: %s", name);
  }

  py_err();
  return out;
}
