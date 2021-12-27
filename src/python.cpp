//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_py_level.hpp"
#include "my_py_thing.hpp"
#include "my_py_tp.hpp"
#include <frameobject.h>
#include <map>

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_depth.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_py_sdl.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

static std::map< std::string, PyObject * > py_mods;
PyObject                                  *my_mod;
PyMODINIT_FUNC                             python_mouse_y_module_create(void);

void py_call_void(const char *name)
{
  TRACE_AND_INDENT();
  if (! my_mod) {
    DIE("Python module not inited yet");
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(my_mod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pValue = PyObject_CallObject(pFunc, 0);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s", name);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(i)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(ii)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iii)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiii)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiii)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiii)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiii)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7, int val8)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7, int val8, int val9)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8, val9);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(I)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(II)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(III)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIII)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIII)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5, unsigned int val6)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIII)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5, unsigned int val6, unsigned int val7)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIII)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5, unsigned int val6, unsigned int val7, unsigned int val8)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIIII)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5, unsigned int val6, unsigned int val7, unsigned int val8,
                     unsigned int val9)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIIIII)", val1, val2, val3, val4, val5, val6, val7, val8, val9);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

void py_call_void_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5, unsigned int val6, unsigned int val7, unsigned int val8,
                     unsigned int val9, unsigned int val10)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIIIIII)", val1, val2, val3, val4, val5, val6, val7, val8, val9, val10);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
}

bool py_call_bool(const char *name)
{
  TRACE_AND_INDENT();
  if (! my_mod) {
    ERR("Python module not inited yet");
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(my_mod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pValue = PyObject_CallObject(pFunc, 0);
    bool      out    = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s", name);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, int val1)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(i)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(ii)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iii)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiii)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiii)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiii)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiii)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7, int val8)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, unsigned int val1)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(I)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, unsigned int val1, unsigned int val2)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(II)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(III)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIII)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIII)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5, unsigned int val6)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIII)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5, unsigned int val6, unsigned int val7)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIII)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                     unsigned int val4, unsigned int val5, unsigned int val6, unsigned int val7, unsigned int val8)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int(const char *name)
{
  TRACE_AND_INDENT();
  if (! my_mod) {
    ERR("Python module not inited yet");
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(my_mod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pValue = PyObject_CallObject(pFunc, 0);
    int       out    = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s", name);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, int val1)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(i)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(ii)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iii)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiii)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiii)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiii)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                   int val7)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiii)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                   int val7, int val8)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, unsigned int val1)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(I)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, unsigned int val1, unsigned int val2)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(II)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(III)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                   unsigned int val4)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIII)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                   unsigned int val4, unsigned int val5)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIII)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                   unsigned int val4, unsigned int val5, unsigned int val6)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIII)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                   unsigned int val4, unsigned int val5, unsigned int val6, unsigned int val7)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIII)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

int py_call_int_fn(const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3,
                   unsigned int val4, unsigned int val5, unsigned int val6, unsigned int val7, unsigned int val8)
{
  TRACE_AND_INDENT();
  auto pmod = py_add_module(module);
  if (! pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    int out = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

char *py_obj_to_str(const PyObject *py_str)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  char     *outstr = 0;
  char     *str;

  py_encstr = 0;
  str       = 0;

  if (! PyUnicode_Check((PyObject *) py_str)) {
    ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_str)->tp_name);
    goto err_out;
  }

  py_encstr = PyUnicode_AsEncodedString((PyObject *) py_str, "utf-8", 0);
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

  return (outstr);
}

std::string py_obj_to_string(const PyObject *py_str)
{
  TRACE_AND_INDENT();
  PyObject   *py_encstr;
  std::string outstr;
  char       *str;

  py_encstr = 0;
  str       = 0;

  if (! PyUnicode_Check((PyObject *) py_str)) {
    ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_str)->tp_name);
    goto err_out;
  }

  py_encstr = PyUnicode_AsEncodedString((PyObject *) py_str, "utf-8", 0);
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

  return (outstr);
}

int py_obj_to_int(PyObject *py_obj)
{
  TRACE_AND_INDENT();
  int val;

  val = 0;

  if (! PyLong_Check((PyObject *) py_obj)) {
    ERR("Object is a %s, not a int object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsLong(py_obj);

err_out:
  if (PyErr_Occurred()) {
    ERR("Int conversion failed");
  }

  return (val);
}

int py_obj_to_bool(PyObject *py_obj)
{
  TRACE_AND_INDENT();
  int val;

  val = 0;

  if (! PyLong_Check((PyObject *) py_obj)) {
    ERR("Object is a %s, not a int object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsLong(py_obj);

err_out:
  if (PyErr_Occurred()) {
    ERR("Int(bool) conversion failed");
  }

  return (val == 0 ? false : true);
}

uint64_t py_obj_to_uint64(PyObject *py_obj)
{
  TRACE_AND_INDENT();
  uint64_t val;

  val = 0;

  if (! PyLong_Check((PyObject *) py_obj)) {
    ERR("Object is a %s, not a uint64 object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsUnsignedLongLong(py_obj);

err_out:

  if (PyErr_Occurred()) {
    ERR("Int conversion failed");
  }

  return (val);
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
    ERR("Object is a %s, not a double object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

err_out:

  if (PyErr_Occurred()) {
    ERR("Int conversion failed");
  }

  return (val);
}

int py_obj_attr_int(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  int       i = 0;

  py_encstr = 0;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
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
    ERR("Int conversion failed");
  }

  return (i);
}

uint64_t py_obj_attr_uint64(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  uint64_t  i = 0;

  py_encstr = 0;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
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
    ERR("Int conversion failed");
  }

  return (i);
}

double py_obj_attr_double(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  double    i = 0;

  py_encstr = 0;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
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
    ERR("Int conversion failed");
  }

  return (i);
}

char *py_obj_attr_str(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;
  char     *outstr = 0;
  char     *str;

  py_encstr = 0;
  str       = 0;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *) py_obj, attr);
  if (! py_encstr) {
    goto err_out;
  }

  str = py_obj_to_str(py_encstr);
  if (! str) {
    goto err_out;
  }

  outstr = str;

err_out:

  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  return (outstr);
}

PyObject *py_obj_attr(const PyObject *py_obj, const char *attr)
{
  TRACE_AND_INDENT();
  PyObject *py_encstr;

  py_encstr = 0;

  if (! PyObject_HasAttrString((PyObject *) py_obj, attr)) {
    ERR("Object is a %s, not a string object.", Py_TYPE((PyObject *) py_obj)->tp_name);
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
    ERR("Obj lookup conversion failed");
  }

  Py_RETURN_NONE;
}

static PyObject *con_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  wchar_t *a = 0;

  if (! PyArg_ParseTuple(args, "u", &a)) {
    ERR("con: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    con(a);
  }

  Py_RETURN_TRUE;
}

static PyObject *topcon_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  wchar_t *a = 0;

  if (! PyArg_ParseTuple(args, "u", &a)) {
    ERR("topcon: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    topcon(a);
  }

  Py_RETURN_TRUE;
}

static PyObject *puts_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *a = 0;

  if (! PyArg_ParseTuple(args, "s", &a)) {
    ERR("puts: Bad args");
    Py_RETURN_FALSE;
  }

  fputs(a, MY_STDOUT);
  fflush(MY_STDOUT);
  printf("%s", a);

  Py_RETURN_TRUE;
}

static PyObject *log_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *a = 0;

  if (! PyArg_ParseTuple(args, "s", &a)) {
    ERR("log: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    LOG("%s", a);
  }

  Py_RETURN_TRUE;
}

static PyObject *err_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *a = 0;

  if (! PyArg_ParseTuple(args, "s", &a)) {
    ERR("err: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    ERR("%s", a);
  }

  Py_RETURN_TRUE;
}

static PyObject *die_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *a = 0;

  if (! PyArg_ParseTuple(args, "s", &a)) {
    ERR("die: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    ERR("%s", a);
  }

  Py_RETURN_TRUE;
}

static PyMethodDef python_c_METHODS[] = {
    MY_ADD_PYTHON_FUNCTION(level_ai_detect_secret_doors_at),
    MY_ADD_PYTHON_FUNCTION(level_ai_resent_count_at),
    MY_ADD_PYTHON_FUNCTION(level_ai_wanderer_at),
    MY_ADD_PYTHON_FUNCTION(level_attack_blood_at),
    MY_ADD_PYTHON_FUNCTION(level_attack_engulf_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_attack_undead_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_acid_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_crush_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_digest_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_energy_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_fire_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_future1_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_future2_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_future3_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_future4_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_lightning_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_necrosis_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_damage_poison_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_enchant_level_at),
    MY_ADD_PYTHON_FUNCTION(level_enchant_max_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_avoids_acid_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_avoids_fire_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_avoids_necrosis_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_avoids_poison_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_avoids_water_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_prefers_acid_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_prefers_fire_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_prefers_necrosis_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_prefers_poison_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_prefers_spiderwebs_at),
    MY_ADD_PYTHON_FUNCTION(level_environ_prefers_water_at),
    MY_ADD_PYTHON_FUNCTION(level_flood_fill_get_all_things),
    MY_ADD_PYTHON_FUNCTION(level_get_all),
    MY_ADD_PYTHON_FUNCTION(level_gfx_flickers_at),
    MY_ADD_PYTHON_FUNCTION(level_gfx_long_shadow_caster_at),
    MY_ADD_PYTHON_FUNCTION(level_gfx_solid_shadow_at),
    MY_ADD_PYTHON_FUNCTION(level_gfx_very_short_shadow_caster_at),
    MY_ADD_PYTHON_FUNCTION(level_gfx_water_at),
    MY_ADD_PYTHON_FUNCTION(level_hunger_clock_tick_frequency_at),
    MY_ADD_PYTHON_FUNCTION(level_hunger_is_insatiable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_attack_mobs_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_break_down_doors_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_break_out_of_webs_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_change_levels_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_collect_keys_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_enchant_items_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_fall_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_fire_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_fire_at_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_follow_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_attack_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_attack_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_escape_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_on_low_hp_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_onto_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_onto_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_randomly_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_jump_without_tiring_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_learn_skills_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_open_doors_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_see_in_the_dark_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_see_through_doors_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_tire_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_use_rings_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_use_wands_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_use_weapons_at),
    MY_ADD_PYTHON_FUNCTION(level_is_able_to_walk_through_walls_at),
    MY_ADD_PYTHON_FUNCTION(level_is_acid_at),
    MY_ADD_PYTHON_FUNCTION(level_is_alive_monst_at),
    MY_ADD_PYTHON_FUNCTION(level_is_alive_on_end_of_anim_at),
    MY_ADD_PYTHON_FUNCTION(level_is_always_hit_at),
    MY_ADD_PYTHON_FUNCTION(level_is_aquatic_at),
    MY_ADD_PYTHON_FUNCTION(level_is_ascend_dungeon_at),
    MY_ADD_PYTHON_FUNCTION(level_is_ascend_sewer_at),
    MY_ADD_PYTHON_FUNCTION(level_is_attackable_by_monst_at),
    MY_ADD_PYTHON_FUNCTION(level_is_attackable_by_player_at),
    MY_ADD_PYTHON_FUNCTION(level_is_auto_collect_item_at),
    MY_ADD_PYTHON_FUNCTION(level_is_auto_equipped_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bag_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bag_item_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bag_item_container_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bag_item_not_stackable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_barrel_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bleeder_at),
    MY_ADD_PYTHON_FUNCTION(level_is_blood_at),
    MY_ADD_PYTHON_FUNCTION(level_is_blood_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bloodied_at),
    MY_ADD_PYTHON_FUNCTION(level_is_blood_splatter_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bones_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bony_at),
    MY_ADD_PYTHON_FUNCTION(level_is_brazier_at),
    MY_ADD_PYTHON_FUNCTION(level_is_bridge_at),
    MY_ADD_PYTHON_FUNCTION(level_is_buff_at),
    MY_ADD_PYTHON_FUNCTION(level_is_burnable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_carrier_of_treasure_class_a_at),
    MY_ADD_PYTHON_FUNCTION(level_is_carrier_of_treasure_class_b_at),
    MY_ADD_PYTHON_FUNCTION(level_is_carrier_of_treasure_class_c_at),
    MY_ADD_PYTHON_FUNCTION(level_is_carrying_item_at),
    MY_ADD_PYTHON_FUNCTION(level_is_carrying_treasure_at),
    MY_ADD_PYTHON_FUNCTION(level_is_chasm_at),
    MY_ADD_PYTHON_FUNCTION(level_is_collectable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_collect_as_keys_at),
    MY_ADD_PYTHON_FUNCTION(level_is_collected_as_gold_at),
    MY_ADD_PYTHON_FUNCTION(level_is_combustible_at),
    MY_ADD_PYTHON_FUNCTION(level_is_corpse_at),
    MY_ADD_PYTHON_FUNCTION(level_is_corpse_on_death_at),
    MY_ADD_PYTHON_FUNCTION(level_is_corridor_at),
    MY_ADD_PYTHON_FUNCTION(level_is_critical_to_level_at),
    MY_ADD_PYTHON_FUNCTION(level_is_crushable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_cursor_at),
    MY_ADD_PYTHON_FUNCTION(level_is_cursor_can_hover_over_at),
    MY_ADD_PYTHON_FUNCTION(level_is_cursor_path_at),
    MY_ADD_PYTHON_FUNCTION(level_is_cursor_path_hazard_for_player_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dead_on_end_of_anim_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dead_on_shove_at),
    MY_ADD_PYTHON_FUNCTION(level_is_debuff_at),
    MY_ADD_PYTHON_FUNCTION(level_is_debug_path_at),
    MY_ADD_PYTHON_FUNCTION(level_is_debug_type_at),
    MY_ADD_PYTHON_FUNCTION(level_is_deep_water_at),
    MY_ADD_PYTHON_FUNCTION(level_is_descend_dungeon_at),
    MY_ADD_PYTHON_FUNCTION(level_is_descend_sewer_at),
    MY_ADD_PYTHON_FUNCTION(level_is_described_when_hovering_over_at),
    MY_ADD_PYTHON_FUNCTION(level_is_destroyed_on_hit_or_miss_at),
    MY_ADD_PYTHON_FUNCTION(level_is_destroyed_on_hitting_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_bl_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_br_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_down_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_left_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_none_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_right_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dirt_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_tl_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_tr_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dir_up_at),
    MY_ADD_PYTHON_FUNCTION(level_is_door_at),
    MY_ADD_PYTHON_FUNCTION(level_is_droppable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_dry_grass_at),
    MY_ADD_PYTHON_FUNCTION(level_is_enchantable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_enchantstone_at),
    MY_ADD_PYTHON_FUNCTION(level_is_engulfer_at),
    MY_ADD_PYTHON_FUNCTION(level_is_ethereal_at),
    MY_ADD_PYTHON_FUNCTION(level_is_ethereal_mob_at),
    MY_ADD_PYTHON_FUNCTION(level_is_exit_finder_at),
    MY_ADD_PYTHON_FUNCTION(level_is_explorer_at),
    MY_ADD_PYTHON_FUNCTION(level_is_explosion_at),
    MY_ADD_PYTHON_FUNCTION(level_is_fearless_at),
    MY_ADD_PYTHON_FUNCTION(level_is_fire_at),
    MY_ADD_PYTHON_FUNCTION(level_is_floating_at),
    MY_ADD_PYTHON_FUNCTION(level_is_floor_at),
    MY_ADD_PYTHON_FUNCTION(level_is_floor_deco_at),
    MY_ADD_PYTHON_FUNCTION(level_is_foilage_at),
    MY_ADD_PYTHON_FUNCTION(level_is_food_at),
    MY_ADD_PYTHON_FUNCTION(level_is_food_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_gfx_anim_synced_with_owner_at),
    MY_ADD_PYTHON_FUNCTION(level_is_glass_at),
    MY_ADD_PYTHON_FUNCTION(level_is_gold_at),
    MY_ADD_PYTHON_FUNCTION(level_is_green_blooded_at),
    MY_ADD_PYTHON_FUNCTION(level_is_green_splatter_at),
    MY_ADD_PYTHON_FUNCTION(level_is_hazard_at),
    MY_ADD_PYTHON_FUNCTION(level_is_health_booster_at),
    MY_ADD_PYTHON_FUNCTION(level_is_heavy_at),
    MY_ADD_PYTHON_FUNCTION(level_is_hittable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_humanoid_at),
    MY_ADD_PYTHON_FUNCTION(level_is_indestructible_at),
    MY_ADD_PYTHON_FUNCTION(level_is_intelligent_at),
    MY_ADD_PYTHON_FUNCTION(level_is_interesting_at),
    MY_ADD_PYTHON_FUNCTION(level_is_item_at),
    MY_ADD_PYTHON_FUNCTION(level_is_item_carrier_at),
    MY_ADD_PYTHON_FUNCTION(level_is_item_collector_at),
    MY_ADD_PYTHON_FUNCTION(level_is_item_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_item_magical_at),
    MY_ADD_PYTHON_FUNCTION(level_is_item_magical_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_item_organic_at),
    MY_ADD_PYTHON_FUNCTION(level_is_jelly_at),
    MY_ADD_PYTHON_FUNCTION(level_is_jelly_baby_at),
    MY_ADD_PYTHON_FUNCTION(level_is_jelly_baby_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_jelly_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_jelly_parent_at),
    MY_ADD_PYTHON_FUNCTION(level_is_key_at),
    MY_ADD_PYTHON_FUNCTION(level_is_lava_at),
    MY_ADD_PYTHON_FUNCTION(level_is_light_blocker_at),
    MY_ADD_PYTHON_FUNCTION(level_is_living_at),
    MY_ADD_PYTHON_FUNCTION(level_is_meat_at),
    MY_ADD_PYTHON_FUNCTION(level_is_meat_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_metal_at),
    MY_ADD_PYTHON_FUNCTION(level_is_minion_at),
    MY_ADD_PYTHON_FUNCTION(level_is_mob_at),
    MY_ADD_PYTHON_FUNCTION(level_is_monst_at),
    MY_ADD_PYTHON_FUNCTION(level_is_moveable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_msg_at),
    MY_ADD_PYTHON_FUNCTION(level_is_necrotic_danger_level_at),
    MY_ADD_PYTHON_FUNCTION(level_is_no_tile_at),
    MY_ADD_PYTHON_FUNCTION(level_is_obs_destructable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_obs_wall_or_door_at),
    MY_ADD_PYTHON_FUNCTION(level_is_on_firing_at_something),
    MY_ADD_PYTHON_FUNCTION(level_is_openable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_organic_at),
    MY_ADD_PYTHON_FUNCTION(level_is_pink_blooded_at),
    MY_ADD_PYTHON_FUNCTION(level_is_pink_splatter_at),
    MY_ADD_PYTHON_FUNCTION(level_is_player_at),
    MY_ADD_PYTHON_FUNCTION(level_is_poisonous_danger_level_at),
    MY_ADD_PYTHON_FUNCTION(level_is_potion_at),
    MY_ADD_PYTHON_FUNCTION(level_is_potion_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_red_blooded_at),
    MY_ADD_PYTHON_FUNCTION(level_is_removeable_if_out_of_slots_at),
    MY_ADD_PYTHON_FUNCTION(level_is_resurrectable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_ring_at),
    MY_ADD_PYTHON_FUNCTION(level_is_ripple_at),
    MY_ADD_PYTHON_FUNCTION(level_is_rock_at),
    MY_ADD_PYTHON_FUNCTION(level_is_rusty_at),
    MY_ADD_PYTHON_FUNCTION(level_is_secret_door_at),
    MY_ADD_PYTHON_FUNCTION(level_is_sewer_wall_at),
    MY_ADD_PYTHON_FUNCTION(level_is_shallow_water_at),
    MY_ADD_PYTHON_FUNCTION(level_is_shovable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_skill_at),
    MY_ADD_PYTHON_FUNCTION(level_is_skillstone_at),
    MY_ADD_PYTHON_FUNCTION(level_is_smoke_at),
    MY_ADD_PYTHON_FUNCTION(level_is_soft_body_at),
    MY_ADD_PYTHON_FUNCTION(level_is_spawner_at),
    MY_ADD_PYTHON_FUNCTION(level_is_spider_at),
    MY_ADD_PYTHON_FUNCTION(level_is_spiderweb_at),
    MY_ADD_PYTHON_FUNCTION(level_is_steal_item_chance_d1000_at),
    MY_ADD_PYTHON_FUNCTION(level_is_sticky_at),
    MY_ADD_PYTHON_FUNCTION(level_is_stone_at),
    MY_ADD_PYTHON_FUNCTION(level_is_sword_at),
    MY_ADD_PYTHON_FUNCTION(level_is_throwable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_tickable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_tmp_thing_at),
    MY_ADD_PYTHON_FUNCTION(level_is_torch_at),
    MY_ADD_PYTHON_FUNCTION(level_is_treasure_chest_at),
    MY_ADD_PYTHON_FUNCTION(level_is_treasure_class_a_at),
    MY_ADD_PYTHON_FUNCTION(level_is_treasure_class_b_at),
    MY_ADD_PYTHON_FUNCTION(level_is_treasure_class_c_at),
    MY_ADD_PYTHON_FUNCTION(level_is_treasure_eater_at),
    MY_ADD_PYTHON_FUNCTION(level_is_treasure_map_at),
    MY_ADD_PYTHON_FUNCTION(level_is_treasure_type_at),
    MY_ADD_PYTHON_FUNCTION(level_is_undead_at),
    MY_ADD_PYTHON_FUNCTION(level_is_usable_at),
    MY_ADD_PYTHON_FUNCTION(level_is_used_when_thrown_at),
    MY_ADD_PYTHON_FUNCTION(level_is_very_combustible_at),
    MY_ADD_PYTHON_FUNCTION(level_is_visible_at),
    MY_ADD_PYTHON_FUNCTION(level_is_wall_at),
    MY_ADD_PYTHON_FUNCTION(level_is_wall_dungeon_at),
    MY_ADD_PYTHON_FUNCTION(level_is_wand_at),
    MY_ADD_PYTHON_FUNCTION(level_is_water_at),
    MY_ADD_PYTHON_FUNCTION(level_is_weapon_at),
    MY_ADD_PYTHON_FUNCTION(level_is_wooden_at),
    MY_ADD_PYTHON_FUNCTION(level_place_at),
    MY_ADD_PYTHON_FUNCTION(level_spawn_at_thing),
    MY_ADD_PYTHON_FUNCTION(level_spawn_at_thing_if_possible),
    MY_ADD_PYTHON_FUNCTION(level_spawn_fire_around_thing),
    MY_ADD_PYTHON_FUNCTION(level_unused_flag1_at),
    MY_ADD_PYTHON_FUNCTION(level_unused_flag2_at),
    MY_ADD_PYTHON_FUNCTION(level_unused_flag3_at),
    MY_ADD_PYTHON_FUNCTION(level_unused_flag4_at),
    MY_ADD_PYTHON_FUNCTION(level_unused_flag5_at),
    MY_ADD_PYTHON_FUNCTION(level_unused_flag6_at),
    MY_ADD_PYTHON_FUNCTION(non_pcg_randint),
    MY_ADD_PYTHON_FUNCTION(pcg_randint),
    MY_ADD_PYTHON_FUNCTION(thing_aggression_level_pct),
    MY_ADD_PYTHON_FUNCTION(thing_ai_detect_secret_doors),
    MY_ADD_PYTHON_FUNCTION(thing_ai_resent_count),
    MY_ADD_PYTHON_FUNCTION(thing_ai_wanderer),
    MY_ADD_PYTHON_FUNCTION(thing_attack_blood),
    MY_ADD_PYTHON_FUNCTION(thing_attack_engulf_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_attack_undead),
    MY_ADD_PYTHON_FUNCTION(thing_buff_add),
    MY_ADD_PYTHON_FUNCTION(thing_buff_remove),
    MY_ADD_PYTHON_FUNCTION(thing_carry),
    MY_ADD_PYTHON_FUNCTION(thing_collateral_damage_pct),
    MY_ADD_PYTHON_FUNCTION(thing_damage_acid_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_crush_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_digest_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_energy_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_fire_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_future1_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_future2_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_future3_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_future4_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_lightning_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_necrosis_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_damage_poison_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_debuff_add),
    MY_ADD_PYTHON_FUNCTION(thing_debuff_remove),
    MY_ADD_PYTHON_FUNCTION(thing_decr_charge_count),
    MY_ADD_PYTHON_FUNCTION(thing_decr_current_damage),
    MY_ADD_PYTHON_FUNCTION(thing_decr_enchant),
    MY_ADD_PYTHON_FUNCTION(thing_decr_enchant_max),
    MY_ADD_PYTHON_FUNCTION(thing_decr_health),
    MY_ADD_PYTHON_FUNCTION(thing_decr_health_max),
    MY_ADD_PYTHON_FUNCTION(thing_decr_poisoned_amount),
    MY_ADD_PYTHON_FUNCTION(thing_decr_stamina),
    MY_ADD_PYTHON_FUNCTION(thing_decr_stamina_max),
    MY_ADD_PYTHON_FUNCTION(thing_distance_jump),
    MY_ADD_PYTHON_FUNCTION(thing_distance_leader_max),
    MY_ADD_PYTHON_FUNCTION(thing_distance_recruitment_max),
    MY_ADD_PYTHON_FUNCTION(thing_enchant_level),
    MY_ADD_PYTHON_FUNCTION(thing_enchant_max),
    MY_ADD_PYTHON_FUNCTION(thing_environ_avoids_acid),
    MY_ADD_PYTHON_FUNCTION(thing_environ_avoids_fire),
    MY_ADD_PYTHON_FUNCTION(thing_environ_avoids_necrosis),
    MY_ADD_PYTHON_FUNCTION(thing_environ_avoids_poison),
    MY_ADD_PYTHON_FUNCTION(thing_environ_avoids_water),
    MY_ADD_PYTHON_FUNCTION(thing_environ_prefers_acid),
    MY_ADD_PYTHON_FUNCTION(thing_environ_prefers_fire),
    MY_ADD_PYTHON_FUNCTION(thing_environ_prefers_necrosis),
    MY_ADD_PYTHON_FUNCTION(thing_environ_prefers_poison),
    MY_ADD_PYTHON_FUNCTION(thing_environ_prefers_spiderwebs),
    MY_ADD_PYTHON_FUNCTION(thing_environ_prefers_water),
    MY_ADD_PYTHON_FUNCTION(thing_fire_at),
    MY_ADD_PYTHON_FUNCTION(thing_get_charge_count),
    MY_ADD_PYTHON_FUNCTION(thing_get_coords),
    MY_ADD_PYTHON_FUNCTION(thing_get_current_damage),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_acid),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_bite),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_crush),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_digest),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_energy),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_fire),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_future1),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_future2),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_future3),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_future4),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_lightning),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_melee),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_necrosis),
    MY_ADD_PYTHON_FUNCTION(thing_get_damage_poison),
    MY_ADD_PYTHON_FUNCTION(thing_get_distance_minion_vision_shared),
    MY_ADD_PYTHON_FUNCTION(thing_get_enchant),
    MY_ADD_PYTHON_FUNCTION(thing_get_enchant_max),
    MY_ADD_PYTHON_FUNCTION(thing_get_health),
    MY_ADD_PYTHON_FUNCTION(thing_get_health_max),
    MY_ADD_PYTHON_FUNCTION(thing_get_immediate_manifestor_id),
    MY_ADD_PYTHON_FUNCTION(thing_get_immediate_owner_id),
    MY_ADD_PYTHON_FUNCTION(thing_get_immediate_spawned_owner_id),
    MY_ADD_PYTHON_FUNCTION(thing_get_initial_charge_count),
    MY_ADD_PYTHON_FUNCTION(thing_get_leader_id),
    MY_ADD_PYTHON_FUNCTION(thing_get_name),
    MY_ADD_PYTHON_FUNCTION(thing_get_necrotized_amount),
    MY_ADD_PYTHON_FUNCTION(thing_get_poisoned_amount),
    MY_ADD_PYTHON_FUNCTION(thing_get_stamina),
    MY_ADD_PYTHON_FUNCTION(thing_get_stamina_max),
    MY_ADD_PYTHON_FUNCTION(thing_get_top_owner_id),
    MY_ADD_PYTHON_FUNCTION(thing_gfx_flickers),
    MY_ADD_PYTHON_FUNCTION(thing_gfx_long_shadow_caster),
    MY_ADD_PYTHON_FUNCTION(thing_gfx_solid_shadow),
    MY_ADD_PYTHON_FUNCTION(thing_gfx_very_short_shadow_caster),
    MY_ADD_PYTHON_FUNCTION(thing_gfx_water),
    MY_ADD_PYTHON_FUNCTION(thing_hit),
    MY_ADD_PYTHON_FUNCTION(thing_hunger_clock_tick_frequency),
    MY_ADD_PYTHON_FUNCTION(thing_hunger_is_insatiable),
    MY_ADD_PYTHON_FUNCTION(thing_incr_charge_count),
    MY_ADD_PYTHON_FUNCTION(thing_incr_current_damage),
    MY_ADD_PYTHON_FUNCTION(thing_incr_enchant),
    MY_ADD_PYTHON_FUNCTION(thing_incr_enchant_max),
    MY_ADD_PYTHON_FUNCTION(thing_incr_health),
    MY_ADD_PYTHON_FUNCTION(thing_incr_health_max),
    MY_ADD_PYTHON_FUNCTION(thing_incr_poisoned_amount),
    MY_ADD_PYTHON_FUNCTION(thing_incr_stamina),
    MY_ADD_PYTHON_FUNCTION(thing_incr_stamina_max),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_attack_mobs),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_break_down_doors),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_break_out_of_webs),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_change_levels),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_collect_keys),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_enchant_items),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_fall),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_follow),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump_attack),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump_attack_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump_escape),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump_on_low_hp_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump_onto),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump_onto_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump_randomly_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_jump_without_tiring),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_learn_skills),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_open_doors),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_see_in_the_dark),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_see_through_doors),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_tire),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_use_rings),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_use_wands),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_use_weapons),
    MY_ADD_PYTHON_FUNCTION(thing_is_able_to_walk_through_walls),
    MY_ADD_PYTHON_FUNCTION(thing_is_acid),
    MY_ADD_PYTHON_FUNCTION(thing_is_alive_monst),
    MY_ADD_PYTHON_FUNCTION(thing_is_alive_on_end_of_anim),
    MY_ADD_PYTHON_FUNCTION(thing_is_always_hit),
    MY_ADD_PYTHON_FUNCTION(thing_is_aquatic),
    MY_ADD_PYTHON_FUNCTION(thing_is_ascend_dungeon),
    MY_ADD_PYTHON_FUNCTION(thing_is_ascend_sewer),
    MY_ADD_PYTHON_FUNCTION(thing_is_auto_collect_item),
    MY_ADD_PYTHON_FUNCTION(thing_is_auto_equipped),
    MY_ADD_PYTHON_FUNCTION(thing_is_auto_throw),
    MY_ADD_PYTHON_FUNCTION(thing_is_auto_use),
    MY_ADD_PYTHON_FUNCTION(thing_is_bag),
    MY_ADD_PYTHON_FUNCTION(thing_is_bag_item),
    MY_ADD_PYTHON_FUNCTION(thing_is_bag_item_container),
    MY_ADD_PYTHON_FUNCTION(thing_is_bag_item_not_stackable),
    MY_ADD_PYTHON_FUNCTION(thing_is_barrel),
    MY_ADD_PYTHON_FUNCTION(thing_is_bleeder),
    MY_ADD_PYTHON_FUNCTION(thing_is_blood),
    MY_ADD_PYTHON_FUNCTION(thing_is_blood_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_bloodied),
    MY_ADD_PYTHON_FUNCTION(thing_is_blood_splatter),
    MY_ADD_PYTHON_FUNCTION(thing_is_bones),
    MY_ADD_PYTHON_FUNCTION(thing_is_bony),
    MY_ADD_PYTHON_FUNCTION(thing_is_brazier),
    MY_ADD_PYTHON_FUNCTION(thing_is_bridge),
    MY_ADD_PYTHON_FUNCTION(thing_is_buff),
    MY_ADD_PYTHON_FUNCTION(thing_is_burnable),
    MY_ADD_PYTHON_FUNCTION(thing_is_carrier_of_treasure_class_a),
    MY_ADD_PYTHON_FUNCTION(thing_is_carrier_of_treasure_class_b),
    MY_ADD_PYTHON_FUNCTION(thing_is_carrier_of_treasure_class_c),
    MY_ADD_PYTHON_FUNCTION(thing_is_carrying_item),
    MY_ADD_PYTHON_FUNCTION(thing_is_carrying_treasure),
    MY_ADD_PYTHON_FUNCTION(thing_is_chasm),
    MY_ADD_PYTHON_FUNCTION(thing_is_collectable),
    MY_ADD_PYTHON_FUNCTION(thing_is_collect_as_keys),
    MY_ADD_PYTHON_FUNCTION(thing_is_collected_as_gold),
    MY_ADD_PYTHON_FUNCTION(thing_is_combustible),
    MY_ADD_PYTHON_FUNCTION(thing_is_corpse),
    MY_ADD_PYTHON_FUNCTION(thing_is_corpse_on_death),
    MY_ADD_PYTHON_FUNCTION(thing_is_corridor),
    MY_ADD_PYTHON_FUNCTION(thing_is_critical_to_level),
    MY_ADD_PYTHON_FUNCTION(thing_is_crushable),
    MY_ADD_PYTHON_FUNCTION(thing_is_cursor),
    MY_ADD_PYTHON_FUNCTION(thing_is_cursor_can_hover_over),
    MY_ADD_PYTHON_FUNCTION(thing_is_cursor_can_hover_over_x2_click),
    MY_ADD_PYTHON_FUNCTION(thing_is_cursor_path),
    MY_ADD_PYTHON_FUNCTION(thing_is_cursor_path_hazard_for_player),
    MY_ADD_PYTHON_FUNCTION(thing_is_dead_on_end_of_anim),
    MY_ADD_PYTHON_FUNCTION(thing_is_dead_or_dying),
    MY_ADD_PYTHON_FUNCTION(thing_is_dead_or_dying_on_shove),
    MY_ADD_PYTHON_FUNCTION(thing_is_debuff),
    MY_ADD_PYTHON_FUNCTION(thing_is_debug_path),
    MY_ADD_PYTHON_FUNCTION(thing_is_debug_type),
    MY_ADD_PYTHON_FUNCTION(thing_is_deep_water),
    MY_ADD_PYTHON_FUNCTION(thing_is_descend_dungeon),
    MY_ADD_PYTHON_FUNCTION(thing_is_descend_sewer),
    MY_ADD_PYTHON_FUNCTION(thing_is_described_when_hovering_over),
    MY_ADD_PYTHON_FUNCTION(thing_is_destroyed_on_hit_or_miss),
    MY_ADD_PYTHON_FUNCTION(thing_is_destroyed_on_hitting),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_bl),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_br),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_down),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_left),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_none),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_right),
    MY_ADD_PYTHON_FUNCTION(thing_is_dirt),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_tl),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_tr),
    MY_ADD_PYTHON_FUNCTION(thing_is_dir_up),
    MY_ADD_PYTHON_FUNCTION(thing_is_door),
    MY_ADD_PYTHON_FUNCTION(thing_is_droppable),
    MY_ADD_PYTHON_FUNCTION(thing_is_dry_grass),
    MY_ADD_PYTHON_FUNCTION(thing_is_enchantable),
    MY_ADD_PYTHON_FUNCTION(thing_is_enchantstone),
    MY_ADD_PYTHON_FUNCTION(thing_is_engulfer),
    MY_ADD_PYTHON_FUNCTION(thing_is_ethereal),
    MY_ADD_PYTHON_FUNCTION(thing_is_ethereal_mob),
    MY_ADD_PYTHON_FUNCTION(thing_is_exit_finder),
    MY_ADD_PYTHON_FUNCTION(thing_is_explorer),
    MY_ADD_PYTHON_FUNCTION(thing_is_explosion),
    MY_ADD_PYTHON_FUNCTION(thing_is_fearless),
    MY_ADD_PYTHON_FUNCTION(thing_is_fire),
    MY_ADD_PYTHON_FUNCTION(thing_is_floating),
    MY_ADD_PYTHON_FUNCTION(thing_is_floor),
    MY_ADD_PYTHON_FUNCTION(thing_is_floor_deco),
    MY_ADD_PYTHON_FUNCTION(thing_is_foilage),
    MY_ADD_PYTHON_FUNCTION(thing_is_food),
    MY_ADD_PYTHON_FUNCTION(thing_is_food_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_gfx_anim_synced_with_owner),
    MY_ADD_PYTHON_FUNCTION(thing_is_glass),
    MY_ADD_PYTHON_FUNCTION(thing_is_gold),
    MY_ADD_PYTHON_FUNCTION(thing_is_green_blooded),
    MY_ADD_PYTHON_FUNCTION(thing_is_green_splatter),
    MY_ADD_PYTHON_FUNCTION(thing_is_hazard),
    MY_ADD_PYTHON_FUNCTION(thing_is_health_booster),
    MY_ADD_PYTHON_FUNCTION(thing_is_heavy),
    MY_ADD_PYTHON_FUNCTION(thing_is_hittable),
    MY_ADD_PYTHON_FUNCTION(thing_is_humanoid),
    MY_ADD_PYTHON_FUNCTION(thing_is_indestructible),
    MY_ADD_PYTHON_FUNCTION(thing_is_intelligent),
    MY_ADD_PYTHON_FUNCTION(thing_is_interesting),
    MY_ADD_PYTHON_FUNCTION(thing_is_item),
    MY_ADD_PYTHON_FUNCTION(thing_is_item_carrier),
    MY_ADD_PYTHON_FUNCTION(thing_is_item_collector),
    MY_ADD_PYTHON_FUNCTION(thing_is_item_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_item_magical),
    MY_ADD_PYTHON_FUNCTION(thing_is_item_magical_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_item_organic),
    MY_ADD_PYTHON_FUNCTION(thing_is_jelly),
    MY_ADD_PYTHON_FUNCTION(thing_is_jelly_baby),
    MY_ADD_PYTHON_FUNCTION(thing_is_jelly_baby_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_jelly_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_jelly_parent),
    MY_ADD_PYTHON_FUNCTION(thing_is_key),
    MY_ADD_PYTHON_FUNCTION(thing_is_laser),
    MY_ADD_PYTHON_FUNCTION(thing_is_lava),
    MY_ADD_PYTHON_FUNCTION(thing_is_light_blocker),
    MY_ADD_PYTHON_FUNCTION(thing_is_living),
    MY_ADD_PYTHON_FUNCTION(thing_is_loggable),
    MY_ADD_PYTHON_FUNCTION(thing_is_meat),
    MY_ADD_PYTHON_FUNCTION(thing_is_meat_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_metal),
    MY_ADD_PYTHON_FUNCTION(thing_is_minion),
    MY_ADD_PYTHON_FUNCTION(thing_is_mob),
    MY_ADD_PYTHON_FUNCTION(thing_is_monst),
    MY_ADD_PYTHON_FUNCTION(thing_is_moveable),
    MY_ADD_PYTHON_FUNCTION(thing_is_msg),
    MY_ADD_PYTHON_FUNCTION(thing_is_necrotic_danger_level),
    MY_ADD_PYTHON_FUNCTION(thing_is_no_tile),
    MY_ADD_PYTHON_FUNCTION(thing_is_obs_destructable),
    MY_ADD_PYTHON_FUNCTION(thing_is_obs_wall_or_door),
    MY_ADD_PYTHON_FUNCTION(thing_is_on_fire),
    MY_ADD_PYTHON_FUNCTION(thing_is_openable),
    MY_ADD_PYTHON_FUNCTION(thing_is_organic),
    MY_ADD_PYTHON_FUNCTION(thing_is_pink_blooded),
    MY_ADD_PYTHON_FUNCTION(thing_is_pink_splatter),
    MY_ADD_PYTHON_FUNCTION(thing_is_player),
    MY_ADD_PYTHON_FUNCTION(thing_is_poisonous_danger_level),
    MY_ADD_PYTHON_FUNCTION(thing_is_potion),
    MY_ADD_PYTHON_FUNCTION(thing_is_potion_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_projectile),
    MY_ADD_PYTHON_FUNCTION(thing_is_red_blooded),
    MY_ADD_PYTHON_FUNCTION(thing_is_removeable_if_out_of_slots),
    MY_ADD_PYTHON_FUNCTION(thing_is_resurrectable),
    MY_ADD_PYTHON_FUNCTION(thing_is_ring),
    MY_ADD_PYTHON_FUNCTION(thing_is_ripple),
    MY_ADD_PYTHON_FUNCTION(thing_is_rock),
    MY_ADD_PYTHON_FUNCTION(thing_is_rusty),
    MY_ADD_PYTHON_FUNCTION(thing_is_secret_door),
    MY_ADD_PYTHON_FUNCTION(thing_is_sewer_wall),
    MY_ADD_PYTHON_FUNCTION(thing_is_shallow_water),
    MY_ADD_PYTHON_FUNCTION(thing_is_shovable),
    MY_ADD_PYTHON_FUNCTION(thing_is_skill),
    MY_ADD_PYTHON_FUNCTION(thing_is_skillstone),
    MY_ADD_PYTHON_FUNCTION(thing_is_smoke),
    MY_ADD_PYTHON_FUNCTION(thing_is_soft_body),
    MY_ADD_PYTHON_FUNCTION(thing_is_spawner),
    MY_ADD_PYTHON_FUNCTION(thing_is_spider),
    MY_ADD_PYTHON_FUNCTION(thing_is_spiderweb),
    MY_ADD_PYTHON_FUNCTION(thing_is_steal_item_chance_d1000),
    MY_ADD_PYTHON_FUNCTION(thing_is_sticky),
    MY_ADD_PYTHON_FUNCTION(thing_is_stone),
    MY_ADD_PYTHON_FUNCTION(thing_is_sword),
    MY_ADD_PYTHON_FUNCTION(thing_is_target_auto_select),
    MY_ADD_PYTHON_FUNCTION(thing_is_throwable),
    MY_ADD_PYTHON_FUNCTION(thing_is_tickable),
    MY_ADD_PYTHON_FUNCTION(thing_is_tmp_thing),
    MY_ADD_PYTHON_FUNCTION(thing_is_torch),
    MY_ADD_PYTHON_FUNCTION(thing_is_treasure_chest),
    MY_ADD_PYTHON_FUNCTION(thing_is_treasure_class_a),
    MY_ADD_PYTHON_FUNCTION(thing_is_treasure_class_b),
    MY_ADD_PYTHON_FUNCTION(thing_is_treasure_class_c),
    MY_ADD_PYTHON_FUNCTION(thing_is_treasure_eater),
    MY_ADD_PYTHON_FUNCTION(thing_is_treasure_map),
    MY_ADD_PYTHON_FUNCTION(thing_is_treasure_type),
    MY_ADD_PYTHON_FUNCTION(thing_is_undead),
    MY_ADD_PYTHON_FUNCTION(thing_is_usable),
    MY_ADD_PYTHON_FUNCTION(thing_is_used_when_thrown),
    MY_ADD_PYTHON_FUNCTION(thing_is_very_combustible),
    MY_ADD_PYTHON_FUNCTION(thing_is_visible),
    MY_ADD_PYTHON_FUNCTION(thing_is_wall),
    MY_ADD_PYTHON_FUNCTION(thing_is_wall_dungeon),
    MY_ADD_PYTHON_FUNCTION(thing_is_wand),
    MY_ADD_PYTHON_FUNCTION(thing_is_water),
    MY_ADD_PYTHON_FUNCTION(thing_is_weapon),
    MY_ADD_PYTHON_FUNCTION(thing_is_wooden),
    MY_ADD_PYTHON_FUNCTION(thing_kill),
    MY_ADD_PYTHON_FUNCTION(thing_killed_by),
    MY_ADD_PYTHON_FUNCTION(thing_msg),
    MY_ADD_PYTHON_FUNCTION(thing_polymorph),
    MY_ADD_PYTHON_FUNCTION(thing_possible_to_attack),
    MY_ADD_PYTHON_FUNCTION(thing_set_current_damage),
    MY_ADD_PYTHON_FUNCTION(thing_set_enchant),
    MY_ADD_PYTHON_FUNCTION(thing_set_enchant_max),
    MY_ADD_PYTHON_FUNCTION(thing_set_health),
    MY_ADD_PYTHON_FUNCTION(thing_set_health_max),
    MY_ADD_PYTHON_FUNCTION(thing_set_leader),
    MY_ADD_PYTHON_FUNCTION(thing_set_manifestor),
    MY_ADD_PYTHON_FUNCTION(thing_set_poisoned_amount),
    MY_ADD_PYTHON_FUNCTION(thing_set_stamina),
    MY_ADD_PYTHON_FUNCTION(thing_set_stamina_max),
    MY_ADD_PYTHON_FUNCTION(thing_skill_activate),
    MY_ADD_PYTHON_FUNCTION(thing_skill_deactivate),
    MY_ADD_PYTHON_FUNCTION(thing_spawn_group_radius),
    MY_ADD_PYTHON_FUNCTION(thing_unused_flag1),
    MY_ADD_PYTHON_FUNCTION(thing_unused_flag2),
    MY_ADD_PYTHON_FUNCTION(thing_unused_flag3),
    MY_ADD_PYTHON_FUNCTION(thing_unused_flag4),
    MY_ADD_PYTHON_FUNCTION(thing_unused_flag5),
    MY_ADD_PYTHON_FUNCTION(thing_unused_flag6),
    MY_ADD_PYTHON_TP_FUNCTION(aggression_level_pct),
    MY_ADD_PYTHON_TP_FUNCTION(ai_detect_secret_doors),
    MY_ADD_PYTHON_TP_FUNCTION(ai_obstacle),
    MY_ADD_PYTHON_TP_FUNCTION(ai_resent_count),
    MY_ADD_PYTHON_TP_FUNCTION(ai_shove_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(ai_wanderer),
    MY_ADD_PYTHON_TP_FUNCTION(attack_blood),
    MY_ADD_PYTHON_TP_FUNCTION(attack_eater),
    MY_ADD_PYTHON_TP_FUNCTION(attack_engulf_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(attack_humanoid),
    MY_ADD_PYTHON_TP_FUNCTION(attack_living),
    MY_ADD_PYTHON_TP_FUNCTION(attack_lunge),
    MY_ADD_PYTHON_TP_FUNCTION(attack_meat),
    MY_ADD_PYTHON_TP_FUNCTION(attack_undead),
    MY_ADD_PYTHON_TP_FUNCTION(bl1_tile),
    MY_ADD_PYTHON_TP_FUNCTION(bl2_tile),
    MY_ADD_PYTHON_TP_FUNCTION(blast_max_radius),
    MY_ADD_PYTHON_TP_FUNCTION(blast_min_radius),
    MY_ADD_PYTHON_TP_FUNCTION(blit_bot_off),
    MY_ADD_PYTHON_TP_FUNCTION(blit_left_off),
    MY_ADD_PYTHON_TP_FUNCTION(blit_right_off),
    MY_ADD_PYTHON_TP_FUNCTION(blit_top_off),
    MY_ADD_PYTHON_TP_FUNCTION(bot1_tile),
    MY_ADD_PYTHON_TP_FUNCTION(bot2_tile),
    MY_ADD_PYTHON_TP_FUNCTION(bot3_tile),
    MY_ADD_PYTHON_TP_FUNCTION(br1_tile),
    MY_ADD_PYTHON_TP_FUNCTION(br2_tile),
    MY_ADD_PYTHON_TP_FUNCTION(capacity_height),
    MY_ADD_PYTHON_TP_FUNCTION(capacity_width),
    MY_ADD_PYTHON_TP_FUNCTION(charge_count),
    MY_ADD_PYTHON_TP_FUNCTION(collateral_damage_pct),
    MY_ADD_PYTHON_TP_FUNCTION(collision_check),
    MY_ADD_PYTHON_TP_FUNCTION(collision_hit_priority),
    MY_ADD_PYTHON_TP_FUNCTION(damage_acid_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_acid_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_bite_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_bite_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_crush_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_crush_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_digest_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_digest_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_energy_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_energy_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_fire_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_fire_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_future1_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_future1_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_future2_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_future2_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_future3_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_future3_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_future4_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_future4_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_lightning_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_lightning_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_melee_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_melee_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_necrosis_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_necrosis_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_poison_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(damage_poison_dice),
    MY_ADD_PYTHON_TP_FUNCTION(damage_received_doubled_from_acid),
    MY_ADD_PYTHON_TP_FUNCTION(damage_received_doubled_from_fire),
    MY_ADD_PYTHON_TP_FUNCTION(damage_received_doubled_from_necrosis),
    MY_ADD_PYTHON_TP_FUNCTION(damage_received_doubled_from_poison),
    MY_ADD_PYTHON_TP_FUNCTION(damage_received_doubled_from_water),
    MY_ADD_PYTHON_TP_FUNCTION(distance_avoid),
    MY_ADD_PYTHON_TP_FUNCTION(distance_jump),
    MY_ADD_PYTHON_TP_FUNCTION(distance_leader_max),
    MY_ADD_PYTHON_TP_FUNCTION(distance_manifestor_max),
    MY_ADD_PYTHON_TP_FUNCTION(distance_minion_vision_shared),
    MY_ADD_PYTHON_TP_FUNCTION(distance_recruitment_max),
    MY_ADD_PYTHON_TP_FUNCTION(distance_throw),
    MY_ADD_PYTHON_TP_FUNCTION(distance_vision),
    MY_ADD_PYTHON_TP_FUNCTION(enchant_level),
    MY_ADD_PYTHON_TP_FUNCTION(enchant_max),
    MY_ADD_PYTHON_TP_FUNCTION(environ_avoids_acid),
    MY_ADD_PYTHON_TP_FUNCTION(environ_avoids_fire),
    MY_ADD_PYTHON_TP_FUNCTION(environ_avoids_necrosis),
    MY_ADD_PYTHON_TP_FUNCTION(environ_avoids_poison),
    MY_ADD_PYTHON_TP_FUNCTION(environ_avoids_water),
    MY_ADD_PYTHON_TP_FUNCTION(environ_prefers_acid),
    MY_ADD_PYTHON_TP_FUNCTION(environ_prefers_fire),
    MY_ADD_PYTHON_TP_FUNCTION(environ_prefers_necrosis),
    MY_ADD_PYTHON_TP_FUNCTION(environ_prefers_poison),
    MY_ADD_PYTHON_TP_FUNCTION(environ_prefers_spiderwebs),
    MY_ADD_PYTHON_TP_FUNCTION(environ_prefers_water),
    MY_ADD_PYTHON_TP_FUNCTION(equip_carry_anim),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_an_animation_only),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_animated),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_animated_can_hflip),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_animated_can_vflip),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_animated_no_dir),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_anim_use),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_attack_anim),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_bounce_always),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_bounce_on_move),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_dead_anim),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_equip_carry_anim),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_flickers),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_glows),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_health_bar_autohide),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_health_bar_shown),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_long_shadow_caster),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_on_fire_anim),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_oversized_and_on_floor),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_short_shadow_caster),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_shown_in_bg),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_show_outlined),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_solid_shadow),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_very_short_shadow_caster),
    MY_ADD_PYTHON_TP_FUNCTION(gfx_water),
    MY_ADD_PYTHON_TP_FUNCTION(gold_value_dice),
    MY_ADD_PYTHON_TP_FUNCTION(health_initial_dice),
    MY_ADD_PYTHON_TP_FUNCTION(health_starving_pct),
    MY_ADD_PYTHON_TP_FUNCTION(hunger_clock_tick_frequency),
    MY_ADD_PYTHON_TP_FUNCTION(hunger_health_pct),
    MY_ADD_PYTHON_TP_FUNCTION(hunger_is_insatiable),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_attack_mobs),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_break_down_doors),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_break_out_of_webs),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_change_levels),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_collect_keys),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_enchant_items),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_fall),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_fire_at),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_follow),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump_attack),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump_attack_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump_escape),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump_on_low_hp_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump_onto),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump_onto_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump_randomly_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_jump_without_tiring),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_learn_skills),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_open_doors),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_see_in_the_dark),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_see_through_doors),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_shove),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_tire),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_use_rings),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_use_wands),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_use_weapons),
    MY_ADD_PYTHON_TP_FUNCTION(is_able_to_walk_through_walls),
    MY_ADD_PYTHON_TP_FUNCTION(is_acid),
    MY_ADD_PYTHON_TP_FUNCTION(is_alive_on_end_of_anim),
    MY_ADD_PYTHON_TP_FUNCTION(is_allied_with),
    MY_ADD_PYTHON_TP_FUNCTION(is_always_hit),
    MY_ADD_PYTHON_TP_FUNCTION(is_aquatic),
    MY_ADD_PYTHON_TP_FUNCTION(is_ascend_dungeon),
    MY_ADD_PYTHON_TP_FUNCTION(is_ascend_sewer),
    MY_ADD_PYTHON_TP_FUNCTION(is_attackable_by_monst),
    MY_ADD_PYTHON_TP_FUNCTION(is_attackable_by_player),
    MY_ADD_PYTHON_TP_FUNCTION(is_auto_collect_item),
    MY_ADD_PYTHON_TP_FUNCTION(is_auto_equipped),
    MY_ADD_PYTHON_TP_FUNCTION(is_auto_throw),
    MY_ADD_PYTHON_TP_FUNCTION(is_auto_use),
    MY_ADD_PYTHON_TP_FUNCTION(is_bag),
    MY_ADD_PYTHON_TP_FUNCTION(is_bag_item),
    MY_ADD_PYTHON_TP_FUNCTION(is_bag_item_container),
    MY_ADD_PYTHON_TP_FUNCTION(is_bag_item_not_stackable),
    MY_ADD_PYTHON_TP_FUNCTION(is_barrel),
    MY_ADD_PYTHON_TP_FUNCTION(is_bleeder),
    MY_ADD_PYTHON_TP_FUNCTION(is_blood),
    MY_ADD_PYTHON_TP_FUNCTION(is_blood_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_blood_splatter),
    MY_ADD_PYTHON_TP_FUNCTION(is_bones),
    MY_ADD_PYTHON_TP_FUNCTION(is_bony),
    MY_ADD_PYTHON_TP_FUNCTION(is_brazier),
    MY_ADD_PYTHON_TP_FUNCTION(is_bridge),
    MY_ADD_PYTHON_TP_FUNCTION(is_buff),
    MY_ADD_PYTHON_TP_FUNCTION(is_burnable),
    MY_ADD_PYTHON_TP_FUNCTION(is_carrier_of_treasure_class_a),
    MY_ADD_PYTHON_TP_FUNCTION(is_carrier_of_treasure_class_b),
    MY_ADD_PYTHON_TP_FUNCTION(is_carrier_of_treasure_class_c),
    MY_ADD_PYTHON_TP_FUNCTION(is_chasm),
    MY_ADD_PYTHON_TP_FUNCTION(is_collectable),
    MY_ADD_PYTHON_TP_FUNCTION(is_collect_as_keys),
    MY_ADD_PYTHON_TP_FUNCTION(is_collected_as_gold),
    MY_ADD_PYTHON_TP_FUNCTION(is_combustible),
    MY_ADD_PYTHON_TP_FUNCTION(is_corpse_on_death),
    MY_ADD_PYTHON_TP_FUNCTION(is_corridor),
    MY_ADD_PYTHON_TP_FUNCTION(is_critical_to_level),
    MY_ADD_PYTHON_TP_FUNCTION(is_crushable),
    MY_ADD_PYTHON_TP_FUNCTION(is_cursor),
    MY_ADD_PYTHON_TP_FUNCTION(is_cursor_can_hover_over),
    MY_ADD_PYTHON_TP_FUNCTION(is_cursor_can_hover_over_x2_click),
    MY_ADD_PYTHON_TP_FUNCTION(is_cursor_path),
    MY_ADD_PYTHON_TP_FUNCTION(is_cursor_path_hazard_for_player),
    MY_ADD_PYTHON_TP_FUNCTION(is_dead_on_end_of_anim),
    MY_ADD_PYTHON_TP_FUNCTION(is_dead_on_shove),
    MY_ADD_PYTHON_TP_FUNCTION(is_debuff),
    MY_ADD_PYTHON_TP_FUNCTION(is_debug_path),
    MY_ADD_PYTHON_TP_FUNCTION(is_debug_type),
    MY_ADD_PYTHON_TP_FUNCTION(is_deep_water),
    MY_ADD_PYTHON_TP_FUNCTION(is_descend_dungeon),
    MY_ADD_PYTHON_TP_FUNCTION(is_descend_sewer),
    MY_ADD_PYTHON_TP_FUNCTION(is_described_when_hovering_over),
    MY_ADD_PYTHON_TP_FUNCTION(is_destroyed_on_hit_or_miss),
    MY_ADD_PYTHON_TP_FUNCTION(is_destroyed_on_hitting),
    MY_ADD_PYTHON_TP_FUNCTION(is_dirt),
    MY_ADD_PYTHON_TP_FUNCTION(is_door),
    MY_ADD_PYTHON_TP_FUNCTION(is_droppable),
    MY_ADD_PYTHON_TP_FUNCTION(is_dry_grass),
    MY_ADD_PYTHON_TP_FUNCTION(is_enchantable),
    MY_ADD_PYTHON_TP_FUNCTION(is_enchantstone),
    MY_ADD_PYTHON_TP_FUNCTION(is_engulfer),
    MY_ADD_PYTHON_TP_FUNCTION(is_ethereal),
    MY_ADD_PYTHON_TP_FUNCTION(is_ethereal_mob),
    MY_ADD_PYTHON_TP_FUNCTION(is_exit_finder),
    MY_ADD_PYTHON_TP_FUNCTION(is_explorer),
    MY_ADD_PYTHON_TP_FUNCTION(is_explosion),
    MY_ADD_PYTHON_TP_FUNCTION(is_fearless),
    MY_ADD_PYTHON_TP_FUNCTION(is_fire),
    MY_ADD_PYTHON_TP_FUNCTION(is_floating),
    MY_ADD_PYTHON_TP_FUNCTION(is_floor),
    MY_ADD_PYTHON_TP_FUNCTION(is_floor_deco),
    MY_ADD_PYTHON_TP_FUNCTION(is_foilage),
    MY_ADD_PYTHON_TP_FUNCTION(is_food),
    MY_ADD_PYTHON_TP_FUNCTION(is_food_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_gfx_anim_synced_with_owner),
    MY_ADD_PYTHON_TP_FUNCTION(is_glass),
    MY_ADD_PYTHON_TP_FUNCTION(is_gold),
    MY_ADD_PYTHON_TP_FUNCTION(is_green_blooded),
    MY_ADD_PYTHON_TP_FUNCTION(is_green_splatter),
    MY_ADD_PYTHON_TP_FUNCTION(is_hazard),
    MY_ADD_PYTHON_TP_FUNCTION(is_health_booster),
    MY_ADD_PYTHON_TP_FUNCTION(is_heavy),
    MY_ADD_PYTHON_TP_FUNCTION(is_hittable),
    MY_ADD_PYTHON_TP_FUNCTION(is_humanoid),
    MY_ADD_PYTHON_TP_FUNCTION(is_indestructible),
    MY_ADD_PYTHON_TP_FUNCTION(is_intelligent),
    MY_ADD_PYTHON_TP_FUNCTION(is_interesting),
    MY_ADD_PYTHON_TP_FUNCTION(is_item),
    MY_ADD_PYTHON_TP_FUNCTION(is_item_carrier),
    MY_ADD_PYTHON_TP_FUNCTION(is_item_collector),
    MY_ADD_PYTHON_TP_FUNCTION(is_item_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_item_magical),
    MY_ADD_PYTHON_TP_FUNCTION(is_item_magical_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_item_organic),
    MY_ADD_PYTHON_TP_FUNCTION(is_jelly),
    MY_ADD_PYTHON_TP_FUNCTION(is_jelly_baby),
    MY_ADD_PYTHON_TP_FUNCTION(is_jelly_baby_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_jelly_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_jelly_parent),
    MY_ADD_PYTHON_TP_FUNCTION(is_key),
    MY_ADD_PYTHON_TP_FUNCTION(is_laser),
    MY_ADD_PYTHON_TP_FUNCTION(is_lava),
    MY_ADD_PYTHON_TP_FUNCTION(is_light_blocker),
    MY_ADD_PYTHON_TP_FUNCTION(is_living),
    MY_ADD_PYTHON_TP_FUNCTION(is_loggable),
    MY_ADD_PYTHON_TP_FUNCTION(is_meat),
    MY_ADD_PYTHON_TP_FUNCTION(is_meat_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_metal),
    MY_ADD_PYTHON_TP_FUNCTION(is_minion),
    MY_ADD_PYTHON_TP_FUNCTION(is_mob),
    MY_ADD_PYTHON_TP_FUNCTION(is_monst),
    MY_ADD_PYTHON_TP_FUNCTION(is_moveable),
    MY_ADD_PYTHON_TP_FUNCTION(is_msg),
    MY_ADD_PYTHON_TP_FUNCTION(is_necrotic_danger_level),
    MY_ADD_PYTHON_TP_FUNCTION(is_no_tile),
    MY_ADD_PYTHON_TP_FUNCTION(is_obs_destructable),
    MY_ADD_PYTHON_TP_FUNCTION(is_obs_wall_or_door),
    MY_ADD_PYTHON_TP_FUNCTION(is_openable),
    MY_ADD_PYTHON_TP_FUNCTION(is_organic),
    MY_ADD_PYTHON_TP_FUNCTION(is_pink_blooded),
    MY_ADD_PYTHON_TP_FUNCTION(is_pink_splatter),
    MY_ADD_PYTHON_TP_FUNCTION(is_player),
    MY_ADD_PYTHON_TP_FUNCTION(is_poisonous_danger_level),
    MY_ADD_PYTHON_TP_FUNCTION(is_potion),
    MY_ADD_PYTHON_TP_FUNCTION(is_potion_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_projectile),
    MY_ADD_PYTHON_TP_FUNCTION(is_red_blooded),
    MY_ADD_PYTHON_TP_FUNCTION(is_removeable_if_out_of_slots),
    MY_ADD_PYTHON_TP_FUNCTION(is_resurrectable),
    MY_ADD_PYTHON_TP_FUNCTION(is_ring),
    MY_ADD_PYTHON_TP_FUNCTION(is_ripple),
    MY_ADD_PYTHON_TP_FUNCTION(is_rock),
    MY_ADD_PYTHON_TP_FUNCTION(is_rusty),
    MY_ADD_PYTHON_TP_FUNCTION(is_secret_door),
    MY_ADD_PYTHON_TP_FUNCTION(is_sewer_wall),
    MY_ADD_PYTHON_TP_FUNCTION(is_shallow_water),
    MY_ADD_PYTHON_TP_FUNCTION(is_shovable),
    MY_ADD_PYTHON_TP_FUNCTION(is_skill),
    MY_ADD_PYTHON_TP_FUNCTION(is_skillstone),
    MY_ADD_PYTHON_TP_FUNCTION(is_smoke),
    MY_ADD_PYTHON_TP_FUNCTION(is_soft_body),
    MY_ADD_PYTHON_TP_FUNCTION(is_spawner),
    MY_ADD_PYTHON_TP_FUNCTION(is_spider),
    MY_ADD_PYTHON_TP_FUNCTION(is_spiderweb),
    MY_ADD_PYTHON_TP_FUNCTION(is_steal_item_chance_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(is_sticky),
    MY_ADD_PYTHON_TP_FUNCTION(is_stone),
    MY_ADD_PYTHON_TP_FUNCTION(is_sword),
    MY_ADD_PYTHON_TP_FUNCTION(is_target_auto_select),
    MY_ADD_PYTHON_TP_FUNCTION(is_the_grid),
    MY_ADD_PYTHON_TP_FUNCTION(is_throwable),
    MY_ADD_PYTHON_TP_FUNCTION(is_tickable),
    MY_ADD_PYTHON_TP_FUNCTION(is_tmp_thing),
    MY_ADD_PYTHON_TP_FUNCTION(is_torch),
    MY_ADD_PYTHON_TP_FUNCTION(is_treasure_chest),
    MY_ADD_PYTHON_TP_FUNCTION(is_treasure_class_a),
    MY_ADD_PYTHON_TP_FUNCTION(is_treasure_class_b),
    MY_ADD_PYTHON_TP_FUNCTION(is_treasure_class_c),
    MY_ADD_PYTHON_TP_FUNCTION(is_treasure_eater),
    MY_ADD_PYTHON_TP_FUNCTION(is_treasure_map),
    MY_ADD_PYTHON_TP_FUNCTION(is_treasure_type),
    MY_ADD_PYTHON_TP_FUNCTION(is_undead),
    MY_ADD_PYTHON_TP_FUNCTION(is_usable),
    MY_ADD_PYTHON_TP_FUNCTION(is_used_when_thrown),
    MY_ADD_PYTHON_TP_FUNCTION(is_very_combustible),
    MY_ADD_PYTHON_TP_FUNCTION(is_wall),
    MY_ADD_PYTHON_TP_FUNCTION(is_wall_dungeon),
    MY_ADD_PYTHON_TP_FUNCTION(is_wand),
    MY_ADD_PYTHON_TP_FUNCTION(is_weapon),
    MY_ADD_PYTHON_TP_FUNCTION(is_wooden),
    MY_ADD_PYTHON_TP_FUNCTION(item_height),
    MY_ADD_PYTHON_TP_FUNCTION(item_width),
    MY_ADD_PYTHON_TP_FUNCTION(laser_name),
    MY_ADD_PYTHON_TP_FUNCTION(left1_tile),
    MY_ADD_PYTHON_TP_FUNCTION(left2_tile),
    MY_ADD_PYTHON_TP_FUNCTION(lifespan_dice),
    MY_ADD_PYTHON_TP_FUNCTION(light_color),
    MY_ADD_PYTHON_TP_FUNCTION(light_strength),
    MY_ADD_PYTHON_TP_FUNCTION(long_text_description),
    MY_ADD_PYTHON_TP_FUNCTION(long_text_description_extra),
    MY_ADD_PYTHON_TP_FUNCTION(minion_limit),
    MY_ADD_PYTHON_TP_FUNCTION(monst_size),
    MY_ADD_PYTHON_TP_FUNCTION(name),
    MY_ADD_PYTHON_TP_FUNCTION(normal_placement_rules),
    MY_ADD_PYTHON_TP_FUNCTION(nutrition_dice),
    MY_ADD_PYTHON_TP_FUNCTION(on_born_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_acid_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_bite_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_constitution_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_crush_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_digest_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_energy_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_fire_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_future1_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_future2_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_future3_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_future4_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_lightning_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_melee_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_necrosis_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_poison_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_damage_strength_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_death_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_death_drop_all_items),
    MY_ADD_PYTHON_TP_FUNCTION(on_death_is_open),
    MY_ADD_PYTHON_TP_FUNCTION(on_death_of_a_follower_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_death_of_my_leader_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_enchant_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_equip_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_fall_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_final_use_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_firing_at_something_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_idle_tick_frequency_dice),
    MY_ADD_PYTHON_TP_FUNCTION(on_lifespan_tick_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_move_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_open_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_acid_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_bite_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_constitution_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_crush_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_digest_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_energy_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_fire_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_future1_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_future2_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_future3_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_future4_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_lightning_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_melee_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_necrosis_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_poison_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_damage_strength_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_set_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_owner_unset_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_polymorphed_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_tick_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_unequip_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_use_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_you_are_declared_a_follower_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_you_are_declared_leader_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_you_are_hit_and_now_dead_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_you_are_hit_but_still_alive_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_you_are_on_fire_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_you_bite_attack_do),
    MY_ADD_PYTHON_TP_FUNCTION(on_you_miss_do),
    MY_ADD_PYTHON_TP_FUNCTION(projectile_name),
    MY_ADD_PYTHON_TP_FUNCTION(range_max),
    MY_ADD_PYTHON_TP_FUNCTION(rarity),
    MY_ADD_PYTHON_TP_FUNCTION(resurrect_dice),
    MY_ADD_PYTHON_TP_FUNCTION(right1_tile),
    MY_ADD_PYTHON_TP_FUNCTION(right2_tile),
    MY_ADD_PYTHON_TP_FUNCTION(spawn_group_radius),
    MY_ADD_PYTHON_TP_FUNCTION(spawn_group_size_dice),
    MY_ADD_PYTHON_TP_FUNCTION(spawn_on_shoved),
    MY_ADD_PYTHON_TP_FUNCTION(stamina),
    MY_ADD_PYTHON_TP_FUNCTION(stat_armor_class),
    MY_ADD_PYTHON_TP_FUNCTION(stat_attack_bonus),
    MY_ADD_PYTHON_TP_FUNCTION(stat_constitution),
    MY_ADD_PYTHON_TP_FUNCTION(stat_dexterity),
    MY_ADD_PYTHON_TP_FUNCTION(stats02),
    MY_ADD_PYTHON_TP_FUNCTION(stats03),
    MY_ADD_PYTHON_TP_FUNCTION(stats04),
    MY_ADD_PYTHON_TP_FUNCTION(stats05),
    MY_ADD_PYTHON_TP_FUNCTION(stats06),
    MY_ADD_PYTHON_TP_FUNCTION(stats07),
    MY_ADD_PYTHON_TP_FUNCTION(stats08),
    MY_ADD_PYTHON_TP_FUNCTION(stats09),
    MY_ADD_PYTHON_TP_FUNCTION(stats10),
    MY_ADD_PYTHON_TP_FUNCTION(stats11),
    MY_ADD_PYTHON_TP_FUNCTION(stats12),
    MY_ADD_PYTHON_TP_FUNCTION(stats17),
    MY_ADD_PYTHON_TP_FUNCTION(stat_strength),
    MY_ADD_PYTHON_TP_FUNCTION(str1),
    MY_ADD_PYTHON_TP_FUNCTION(str2),
    MY_ADD_PYTHON_TP_FUNCTION(str4),
    MY_ADD_PYTHON_TP_FUNCTION(text_a_or_an),
    MY_ADD_PYTHON_TP_FUNCTION(text_buff),
    MY_ADD_PYTHON_TP_FUNCTION(text_debuff),
    MY_ADD_PYTHON_TP_FUNCTION(text_description),
    MY_ADD_PYTHON_TP_FUNCTION(text_enchant),
    MY_ADD_PYTHON_TP_FUNCTION(text_hits),
    MY_ADD_PYTHON_TP_FUNCTION(text_name),
    MY_ADD_PYTHON_TP_FUNCTION(text_skill),
    MY_ADD_PYTHON_TP_FUNCTION(text_title),
    MY_ADD_PYTHON_TP_FUNCTION(text_unused),
    MY_ADD_PYTHON_TP_FUNCTION(text_unused1),
    MY_ADD_PYTHON_TP_FUNCTION(text_unused2),
    MY_ADD_PYTHON_TP_FUNCTION(tile),
    MY_ADD_PYTHON_TP_FUNCTION(tl1_tile),
    MY_ADD_PYTHON_TP_FUNCTION(tl2_tile),
    MY_ADD_PYTHON_TP_FUNCTION(top1_tile),
    MY_ADD_PYTHON_TP_FUNCTION(top2_tile),
    MY_ADD_PYTHON_TP_FUNCTION(tr1_tile),
    MY_ADD_PYTHON_TP_FUNCTION(tr2_tile),
    MY_ADD_PYTHON_TP_FUNCTION(unused_chance1_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(unused_chance2_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(unused_chance3_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(unused_chance4_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(unused_chance5_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(unused_chance6_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(unused_chance7_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(unused_chance8_d1000),
    MY_ADD_PYTHON_TP_FUNCTION(unused_flag1),
    MY_ADD_PYTHON_TP_FUNCTION(unused_flag2),
    MY_ADD_PYTHON_TP_FUNCTION(unused_flag3),
    MY_ADD_PYTHON_TP_FUNCTION(unused_flag4),
    MY_ADD_PYTHON_TP_FUNCTION(unused_flag5),
    MY_ADD_PYTHON_TP_FUNCTION(unused_flag6),
    MY_ADD_PYTHON_TP_FUNCTION(weapon_damage),
    MY_ADD_PYTHON_TP_FUNCTION(z_depth),
    MY_ADD_PYTHON_TP_FUNCTION(z_prio),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(abs_to_pct),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(con),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(die),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(err),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(if_matches),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(if_matches_then_dead),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(level_add),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(level_spawn_next_to),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(level_spawn_next_to_or_on_monst),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(level_spawn_using_items_radius_range),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(log),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(map_load_room),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(music_load),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(music_play),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(pct_to_abs),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(puts),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(sound_load),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(sound_play),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(sound_play_channel),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(tex_load),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(text_size),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(thing_sound_play),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(thing_sound_play_channel),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(tile_load_arr),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(tile_load_arr_sprites),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(topcon),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(tp_load),
    MY_ADD_WRAPPED_PYTHON_FUNCTION(tp_update),

    PYFUNC_REF(SDLGetKeyState),

    {0, 0, 0, 0} /* sentinel */
};

static struct PyModuleDef python_c_MODULE = {PyModuleDef_HEAD_INIT, "my", 0, -1, python_c_METHODS, 0, 0, 0, 0};

PyMODINIT_FUNC python_mouse_y_module_create(void)
{
  TRACE_AND_INDENT();
  PyObject *m = PyModule_Create(&python_c_MODULE);
  if (! m) {
    PyErr_Print();
    DIE("Python init");
    return 0;
  }

  return (m);
}

void py_err(void)
{
  TRACE_AND_INDENT();
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
  py_str    = py_obj_to_str(pyobj_str);
  ERR("%s", py_str);
  myfree(py_str);

  mod  = PyImport_ImportModule("backtrace");
  list = PyObject_CallMethod(mod, "format_exception", "OOO", ptype, pvalue, pbacktrace);
  if (list) {
    string = PyUnicode_FromString("\n");
    ret    = PyUnicode_Join(string, list);
    Py_DECREF(list);
    Py_DECREF(string);

    py_str = py_obj_to_str(ret);
    ERR("%s", py_str);
    myfree(py_str);

    Py_DECREF(ret);
  }

  PyErr_Clear();

  PyThreadState *tstate = PyThreadState_GET();

  if (tstate && tstate->frame) {
    PyFrameObject *frame = tstate->frame;

    ERR("Python stack trace:\n");

    while (frame) {
      int   line     = frame->f_lineno;
      char *filename = py_obj_to_str(frame->f_code->co_filename);
      char *funcname = py_obj_to_str(frame->f_code->co_name);
      ERR("    %s(%d): %s\n", filename, line, funcname);
      frame = frame->f_back;
      myfree(filename);
      myfree(funcname);
    }
  }
  ERR("Python error");
}

void py_trace(void)
{
  TRACE_AND_INDENT();
  PyThreadState *tstate = PyThreadState_GET();

  if (tstate && tstate->frame) {
    PyFrameObject *frame = tstate->frame;

    CON("Python stack trace:");

    int cnt = 1;

    while (frame) {
      int   line     = frame->f_lineno;
      char *filename = py_obj_to_str(frame->f_code->co_filename);
      char *funcname = py_obj_to_str(frame->f_code->co_name);
      CON(">>> %d. %s, line %d, %s()", cnt++, filename, line, funcname);
      frame = frame->f_back;
      myfree(filename);
      myfree(funcname);
    }
  }
}

void py_exec(const char *str)
{
  TRACE_AND_INDENT();
  char stdOutErr[] =
      "import sys\n\
import my\n\
class CatchOutErr:\n\
  def __init__(self):\n\
    self.value = ''\n\
  def write(self, txt):\n\
    self.value += txt\n\
catchOutErr = CatchOutErr()\n\
sys.stdout = catchOutErr\n\
sys.stderr = catchOutErr\n\
";

  PyObject *pModule = PyImport_AddModule("__main__");
  py_err();

  LOG("EXEC: [%s]", str);
  PyRun_SimpleString(stdOutErr);
  py_err();

  PyRun_SimpleString(str);
  py_err();

  PyObject *catcher = PyObject_GetAttrString(pModule, "catchOutErr");
  py_err();

  if (catcher) {
    PyObject *output = PyObject_GetAttrString(catcher, "value");
    py_err();

    char *text = py_obj_to_str(output);
    if (text) {
      strchopc(text, '\n');
      CON("%s", text);
      myfree(text);
    }
  } else {
    CON("no output");
  }
}

static void py_add_to_path(const char *path)
{
  TRACE_AND_INDENT();
  PyObject *py_cur_path, *py_item;
  char     *new_path;
  int       wc_len, i;
  wchar_t  *wc_new_path;
  char     *item;

  DBG3("Current system python path: (adding %s)", path);

  new_path    = dupstr(path, __FUNCTION__);
  py_cur_path = PySys_GetObject("path");

  for (i = 0; i < PyList_Size(py_cur_path); i++) {
    char *tmp = strappend(new_path, PATHSEP);
    myfree(new_path);
    new_path = tmp;

    py_item = PyList_GetItem(py_cur_path, i);

    if (! PyUnicode_Check(py_item)) {
      continue;
    }

    item = py_obj_to_str(py_item);
    if (! item) {
      continue;
    }

    DBG3("  %s", item);

    tmp = strappend(new_path, item);
    myfree(new_path);
    new_path = tmp;

    myfree(item);
  }

  /* Convert to wide chars. */
  wc_len = sizeof(wchar_t) * (strlen(new_path) + 1);

  wc_new_path = (wchar_t *) myzalloc(wc_len, "wchar str");
  if (! wc_new_path) {
    ERR("Path alloc fail");
  }

  DBG3("Set python path: %s", new_path);

  mbstowcs(wc_new_path, new_path, wc_len);
  PySys_SetPath(wc_new_path);
  myfree(new_path);
  myfree(wc_new_path);
}

PyObject *abs_to_pct_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  double x = 0;
  double y = 0;

  static char *kwlist[] = {(char *) "x", (char *) "y", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &x, &y)) {
    return 0;
  }

  x /= (double) TERM_WIDTH;
  y /= (double) TERM_HEIGHT;

  return (Py_BuildValue("dd", x, y));
}

PyObject *pcg_randint(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  int x = 0;
  int y = 0;

  static char *kwlist[] = {(char *) "x", (char *) "y", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &x, &y)) {
    return 0;
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

  static char *kwlist[] = {(char *) "x", (char *) "y", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &x, &y)) {
    return 0;
  }

  //
  // Python style. We don't use pythons so we can get consistent random
  // numbers with the one C uses.
  //
  return (Py_BuildValue("i", non_pcg_random_range_inclusive(x, y)));
}

PyObject *pct_to_abs_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  double x = 0;
  double y = 0;

  static char *kwlist[] = {(char *) "x", (char *) "y", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &x, &y)) {
    return 0;
  }

  x *= (double) TERM_WIDTH;
  y *= (double) TERM_HEIGHT;

  return (Py_BuildValue("dd", x, y));
}

static void python_add_consts(void)
{
  TRACE_AND_INDENT();
  PyModule_AddIntConstant(my_mod, "TERM_HEIGHT", TERM_HEIGHT);
  PyModule_AddIntConstant(my_mod, "TERM_WIDTH", TERM_WIDTH);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_CHASM", MAP_DEPTH_CHASM);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_FLOOR", MAP_DEPTH_FLOOR);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_FLOOR2", MAP_DEPTH_FLOOR2);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_THE_GRID", MAP_DEPTH_THE_GRID);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_LAVA", MAP_DEPTH_LAVA);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_OBJ", MAP_DEPTH_OBJ);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_WATER", MAP_DEPTH_WATER);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_EQUIP", MAP_DEPTH_EQUIP);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_EXPLOSION_MAJOR", MAP_DEPTH_EXPLOSION_MAJOR);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_EXPLOSION_MINOR", MAP_DEPTH_EXPLOSION_MINOR);
  PyModule_AddIntConstant(my_mod, "MAP_DEPTH_MESSAGE", MAP_DEPTH_MESSAGE);
  PyModule_AddIntConstant(my_mod, "CHANNEL_FOOTSTEPS", CHANNEL_FOOTSTEPS);
  PyModule_AddIntConstant(my_mod, "CHANNEL_MISC", CHANNEL_MISC);
  PyModule_AddIntConstant(my_mod, "CHANNEL_IMPACT", CHANNEL_IMPACT);
  PyModule_AddIntConstant(my_mod, "CHANNEL_WEAPON", CHANNEL_WEAPON);
  PyModule_AddIntConstant(my_mod, "CHANNEL_EXPLOSION", CHANNEL_EXPLOSION);
  PyModule_AddIntConstant(my_mod, "CHANNEL_MONST", CHANNEL_MONST);
  PyModule_AddIntConstant(my_mod, "CHANNEL_MONST_DEATH", CHANNEL_MONST_DEATH);
  PyModule_AddIntConstant(my_mod, "CHANNEL_MONST_BIRTH", CHANNEL_MONST_BIRTH);
  PyModule_AddIntConstant(my_mod, "MAP_HEIGHT", MAP_HEIGHT);
  PyModule_AddIntConstant(my_mod, "MAP_PRIO_ALWAYS_BEHIND", MAP_PRIO_ALWAYS_BEHIND);
  PyModule_AddIntConstant(my_mod, "MAP_PRIO_BEHIND", MAP_PRIO_BEHIND);
  PyModule_AddIntConstant(my_mod, "MAP_PRIO_IN_FRONT", MAP_PRIO_IN_FRONT);
  PyModule_AddIntConstant(my_mod, "MAP_PRIO_NORMAL", MAP_PRIO_NORMAL);
  PyModule_AddIntConstant(my_mod, "RARITY_COMMON", THING_RARITY_COMMON);
  PyModule_AddIntConstant(my_mod, "RARITY_UNCOMMON", THING_RARITY_UNCOMMON);
  PyModule_AddIntConstant(my_mod, "RARITY_RARE", THING_RARITY_RARE);
  PyModule_AddIntConstant(my_mod, "RARITY_VERY_RARE", THING_RARITY_VERY_RARE);
  PyModule_AddIntConstant(my_mod, "RARITY_UNIQUE", THING_RARITY_UNIQUE);
  PyModule_AddIntConstant(my_mod, "MAP_WIDTH", MAP_WIDTH);
  PyModule_AddIntConstant(my_mod, "MONST_SIZE_TINY", MONST_SIZE_TINY);
  PyModule_AddIntConstant(my_mod, "MONST_SIZE_SMALL", MONST_SIZE_SMALL);
  PyModule_AddIntConstant(my_mod, "MONST_SIZE_NORMAL", MONST_SIZE_NORMAL);
  PyModule_AddIntConstant(my_mod, "MONST_SIZE_LARGE", MONST_SIZE_LARGE);
  PyModule_AddIntConstant(my_mod, "MONST_SIZE_GIANT", MONST_SIZE_GIANT);
  PyModule_AddIntConstant(my_mod, "MONST_SIZE_GARGANTUAN", MONST_SIZE_GARGANTUAN);
  PyModule_AddStringConstant(my_mod, "MYVER", MYVER);

  PyModule_AddIntConstant(my_mod, "KMOD_LSHIFT", KMOD_LSHIFT);
  PyModule_AddIntConstant(my_mod, "KMOD_RSHIFT", KMOD_RSHIFT);
  PyModule_AddIntConstant(my_mod, "KMOD_LALT", KMOD_LALT);
  PyModule_AddIntConstant(my_mod, "KMOD_RALT", KMOD_RALT);
  PyModule_AddIntConstant(my_mod, "KMOD_LCTRL", KMOD_LCTRL);
  PyModule_AddIntConstant(my_mod, "KMOD_RCTRL", KMOD_RCTRL);

  PyModule_AddIntConstant(my_mod, "SDLK_0", SDLK_0);
  PyModule_AddIntConstant(my_mod, "SDLK_1", SDLK_1);
  PyModule_AddIntConstant(my_mod, "SDLK_2", SDLK_2);
  PyModule_AddIntConstant(my_mod, "SDLK_3", SDLK_3);
  PyModule_AddIntConstant(my_mod, "SDLK_4", SDLK_4);
  PyModule_AddIntConstant(my_mod, "SDLK_5", SDLK_5);
  PyModule_AddIntConstant(my_mod, "SDLK_6", SDLK_6);
  PyModule_AddIntConstant(my_mod, "SDLK_7", SDLK_7);
  PyModule_AddIntConstant(my_mod, "SDLK_8", SDLK_8);
  PyModule_AddIntConstant(my_mod, "SDLK_9", SDLK_9);
  PyModule_AddIntConstant(my_mod, "SDLK_AMPERSAND", SDLK_AMPERSAND);
  PyModule_AddIntConstant(my_mod, "SDLK_ASTERISK", SDLK_ASTERISK);
  PyModule_AddIntConstant(my_mod, "SDLK_AT", SDLK_AT);
  PyModule_AddIntConstant(my_mod, "SDLK_BACKQUOTE", SDLK_BACKQUOTE);
  PyModule_AddIntConstant(my_mod, "SDLK_BACKSLASH", SDLK_BACKSLASH);
  PyModule_AddIntConstant(my_mod, "SDLK_BACKSPACE", SDLK_BACKSPACE);
  PyModule_AddIntConstant(my_mod, "SDLK_CARET", SDLK_CARET);
  PyModule_AddIntConstant(my_mod, "SDLK_COLON", SDLK_COLON);
  PyModule_AddIntConstant(my_mod, "SDLK_COMMA", SDLK_COMMA);
  PyModule_AddIntConstant(my_mod, "SDLK_DELETE", SDLK_DELETE);
  PyModule_AddIntConstant(my_mod, "SDLK_DOLLAR", SDLK_DOLLAR);
  PyModule_AddIntConstant(my_mod, "SDLK_EQUALS", SDLK_EQUALS);
  PyModule_AddIntConstant(my_mod, "SDLK_ESCAPE", SDLK_ESCAPE);
  PyModule_AddIntConstant(my_mod, "SDLK_EXCLAIM", SDLK_EXCLAIM);
  PyModule_AddIntConstant(my_mod, "SDLK_GREATER", SDLK_GREATER);
  PyModule_AddIntConstant(my_mod, "SDLK_HASH", SDLK_HASH);
  PyModule_AddIntConstant(my_mod, "SDLK_LEFTBRACKET", SDLK_LEFTBRACKET);
  PyModule_AddIntConstant(my_mod, "SDLK_LEFTPAREN", SDLK_LEFTPAREN);
  PyModule_AddIntConstant(my_mod, "SDLK_LESS", SDLK_LESS);
  PyModule_AddIntConstant(my_mod, "SDLK_MINUS", SDLK_MINUS);
  PyModule_AddIntConstant(my_mod, "SDLK_PERIOD", SDLK_PERIOD);
  PyModule_AddIntConstant(my_mod, "SDLK_PLUS", SDLK_PLUS);
  PyModule_AddIntConstant(my_mod, "SDLK_QUESTION", SDLK_QUESTION);
  PyModule_AddIntConstant(my_mod, "SDLK_QUOTE", SDLK_QUOTE);
  PyModule_AddIntConstant(my_mod, "SDLK_QUOTEDBL", SDLK_QUOTEDBL);
  PyModule_AddIntConstant(my_mod, "SDLK_RETURN", SDLK_RETURN);
  PyModule_AddIntConstant(my_mod, "SDLK_RIGHTBRACKET", SDLK_RIGHTBRACKET);
  PyModule_AddIntConstant(my_mod, "SDLK_RIGHTPAREN", SDLK_RIGHTPAREN);
  PyModule_AddIntConstant(my_mod, "SDLK_SEMICOLON", SDLK_SEMICOLON);
  PyModule_AddIntConstant(my_mod, "SDLK_SLASH", SDLK_SLASH);
  PyModule_AddIntConstant(my_mod, "SDLK_SPACE", SDLK_SPACE);
  PyModule_AddIntConstant(my_mod, "SDLK_TAB", SDLK_TAB);
  PyModule_AddIntConstant(my_mod, "SDLK_UNDERSCORE", SDLK_UNDERSCORE);
  PyModule_AddIntConstant(my_mod, "SDLK_a", SDLK_a);
  PyModule_AddIntConstant(my_mod, "SDLK_b", SDLK_b);
  PyModule_AddIntConstant(my_mod, "SDLK_c", SDLK_c);
  PyModule_AddIntConstant(my_mod, "SDLK_d", SDLK_d);
  PyModule_AddIntConstant(my_mod, "SDLK_e", SDLK_e);
  PyModule_AddIntConstant(my_mod, "SDLK_f", SDLK_f);
  PyModule_AddIntConstant(my_mod, "SDLK_g", SDLK_g);
  PyModule_AddIntConstant(my_mod, "SDLK_h", SDLK_h);
  PyModule_AddIntConstant(my_mod, "SDLK_i", SDLK_i);
  PyModule_AddIntConstant(my_mod, "SDLK_j", SDLK_j);
  PyModule_AddIntConstant(my_mod, "SDLK_k", SDLK_k);
  PyModule_AddIntConstant(my_mod, "SDLK_l", SDLK_l);
  PyModule_AddIntConstant(my_mod, "SDLK_m", SDLK_m);
  PyModule_AddIntConstant(my_mod, "SDLK_n", SDLK_n);
  PyModule_AddIntConstant(my_mod, "SDLK_o", SDLK_o);
  PyModule_AddIntConstant(my_mod, "SDLK_p", SDLK_p);
  PyModule_AddIntConstant(my_mod, "SDLK_q", SDLK_q);
  PyModule_AddIntConstant(my_mod, "SDLK_r", SDLK_r);
  PyModule_AddIntConstant(my_mod, "SDLK_s", SDLK_s);
  PyModule_AddIntConstant(my_mod, "SDLK_t", SDLK_t);
  PyModule_AddIntConstant(my_mod, "SDLK_u", SDLK_u);
  PyModule_AddIntConstant(my_mod, "SDLK_v", SDLK_v);
  PyModule_AddIntConstant(my_mod, "SDLK_w", SDLK_w);
  PyModule_AddIntConstant(my_mod, "SDLK_x", SDLK_x);
  PyModule_AddIntConstant(my_mod, "SDLK_y", SDLK_y);
  PyModule_AddIntConstant(my_mod, "SDLK_z", SDLK_z);

#if SDL_MAJOR_VERSION == 1 /* { */
  PyModule_AddIntConstant(my_mod, "SDLK_KP0", SDLK_KP0);
  PyModule_AddIntConstant(my_mod, "SDLK_KP1", SDLK_KP1);
  PyModule_AddIntConstant(my_mod, "SDLK_KP2", SDLK_KP2);
  PyModule_AddIntConstant(my_mod, "SDLK_KP3", SDLK_KP3);
  PyModule_AddIntConstant(my_mod, "SDLK_KP4", SDLK_KP4);
  PyModule_AddIntConstant(my_mod, "SDLK_KP5", SDLK_KP5);
  PyModule_AddIntConstant(my_mod, "SDLK_KP6", SDLK_KP6);
  PyModule_AddIntConstant(my_mod, "SDLK_KP7", SDLK_KP7);
  PyModule_AddIntConstant(my_mod, "SDLK_KP8", SDLK_KP8);
  PyModule_AddIntConstant(my_mod, "SDLK_KP9", SDLK_KP9);
#else
  PyModule_AddIntConstant(my_mod, "SDLK_KP0", SDLK_KP_0);
  PyModule_AddIntConstant(my_mod, "SDLK_KP1", SDLK_KP_1);
  PyModule_AddIntConstant(my_mod, "SDLK_KP2", SDLK_KP_2);
  PyModule_AddIntConstant(my_mod, "SDLK_KP3", SDLK_KP_3);
  PyModule_AddIntConstant(my_mod, "SDLK_KP4", SDLK_KP_4);
  PyModule_AddIntConstant(my_mod, "SDLK_KP5", SDLK_KP_5);
  PyModule_AddIntConstant(my_mod, "SDLK_KP6", SDLK_KP_6);
  PyModule_AddIntConstant(my_mod, "SDLK_KP7", SDLK_KP_7);
  PyModule_AddIntConstant(my_mod, "SDLK_KP8", SDLK_KP_8);
  PyModule_AddIntConstant(my_mod, "SDLK_KP9", SDLK_KP_9);
#endif

  PyModule_AddIntConstant(my_mod, "SDLK_KP_PERIOD", SDLK_KP_PERIOD);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_DIVIDE", SDLK_KP_DIVIDE);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_MULTIPLY", SDLK_KP_MULTIPLY);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_MINUS", SDLK_KP_MINUS);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_PLUS", SDLK_KP_PLUS);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_ENTER", SDLK_KP_ENTER);
  PyModule_AddIntConstant(my_mod, "SDLK_KP_EQUALS", SDLK_KP_EQUALS);
  PyModule_AddIntConstant(my_mod, "SDLK_UP", SDLK_UP);
  PyModule_AddIntConstant(my_mod, "SDLK_DOWN", SDLK_DOWN);
  PyModule_AddIntConstant(my_mod, "SDLK_RIGHT", SDLK_RIGHT);
  PyModule_AddIntConstant(my_mod, "SDLK_LEFT", SDLK_LEFT);
  PyModule_AddIntConstant(my_mod, "SDLK_INSERT", SDLK_INSERT);
  PyModule_AddIntConstant(my_mod, "SDLK_HOME", SDLK_HOME);
  PyModule_AddIntConstant(my_mod, "SDLK_END", SDLK_END);
  PyModule_AddIntConstant(my_mod, "SDLK_PAGEUP", SDLK_PAGEUP);
  PyModule_AddIntConstant(my_mod, "SDLK_PAGEDOWN", SDLK_PAGEDOWN);
  PyModule_AddIntConstant(my_mod, "SDLK_F1", SDLK_F1);
  PyModule_AddIntConstant(my_mod, "SDLK_F2", SDLK_F2);
  PyModule_AddIntConstant(my_mod, "SDLK_F3", SDLK_F3);
  PyModule_AddIntConstant(my_mod, "SDLK_F4", SDLK_F4);
  PyModule_AddIntConstant(my_mod, "SDLK_F5", SDLK_F5);
  PyModule_AddIntConstant(my_mod, "SDLK_F6", SDLK_F6);
  PyModule_AddIntConstant(my_mod, "SDLK_F7", SDLK_F7);
  PyModule_AddIntConstant(my_mod, "SDLK_F8", SDLK_F8);
  PyModule_AddIntConstant(my_mod, "SDLK_F9", SDLK_F9);
  PyModule_AddIntConstant(my_mod, "SDLK_F10", SDLK_F10);
  PyModule_AddIntConstant(my_mod, "SDLK_F11", SDLK_F11);
  PyModule_AddIntConstant(my_mod, "SDLK_F12", SDLK_F12);
  PyModule_AddIntConstant(my_mod, "SDLK_F13", SDLK_F13);
  PyModule_AddIntConstant(my_mod, "SDLK_F14", SDLK_F14);
  PyModule_AddIntConstant(my_mod, "SDLK_F15", SDLK_F15);
  PyModule_AddIntConstant(my_mod, "SDLK_CAPSLOCK", SDLK_CAPSLOCK);
  PyModule_AddIntConstant(my_mod, "SDLK_RSHIFT", SDLK_RSHIFT);
  PyModule_AddIntConstant(my_mod, "SDLK_LSHIFT", SDLK_LSHIFT);
  PyModule_AddIntConstant(my_mod, "SDLK_RCTRL", SDLK_RCTRL);
  PyModule_AddIntConstant(my_mod, "SDLK_LCTRL", SDLK_LCTRL);
#if SDL_MAJOR_VERSION > 1
  PyModule_AddIntConstant(my_mod, "SDLK_RGUI", SDLK_RGUI);
  PyModule_AddIntConstant(my_mod, "SDLK_LGUI", SDLK_LGUI);
#else
  PyModule_AddIntConstant(my_mod, "SDLK_RGUI", -1);
  PyModule_AddIntConstant(my_mod, "SDLK_LGUI", -1);
#endif
  PyModule_AddIntConstant(my_mod, "SDLK_RALT", SDLK_RALT);
  PyModule_AddIntConstant(my_mod, "SDLK_LALT", SDLK_LALT);
  PyModule_AddIntConstant(my_mod, "SDLK_MODE", SDLK_MODE);
  PyModule_AddIntConstant(my_mod, "SDLK_HELP", SDLK_HELP);
  PyModule_AddIntConstant(my_mod, "SDLK_SYSREQ", SDLK_SYSREQ);
  PyModule_AddIntConstant(my_mod, "SDLK_MENU", SDLK_MENU);
  PyModule_AddIntConstant(my_mod, "SDLK_POWER", SDLK_POWER);
  PyModule_AddIntConstant(my_mod, "SDLK_UNDO", SDLK_UNDO);

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_0", SDLK_0);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_0", SDL_SCANCODE_0);
#endif

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_1", SDLK_1);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_1", SDL_SCANCODE_1);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_2", SDLK_2);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_2", SDL_SCANCODE_2);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_3", SDLK_3);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_3", SDL_SCANCODE_3);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_4", SDLK_4);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_4", SDL_SCANCODE_4);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_5", SDLK_5);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_5", SDL_SCANCODE_5);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_6", SDLK_6);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_6", SDL_SCANCODE_6);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_7", SDLK_7);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_7", SDL_SCANCODE_7);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_8", SDLK_8);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_8", SDL_SCANCODE_8);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_9", SDLK_9);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_9", SDL_SCANCODE_9);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_AMPERSAND", SDLK_AMPERSAND);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_AMPERSAND", SDL_SCANCODE_KP_AMPERSAND);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_AT", SDLK_AT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_AT", SDL_SCANCODE_KP_AT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_BACKSLASH", SDLK_BACKSLASH);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_BACKSLASH", SDL_SCANCODE_BACKSLASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_BACKSPACE", SDLK_BACKSPACE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_BACKSPACE", SDL_SCANCODE_BACKSPACE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_COMMA", SDLK_COMMA);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_COMMA", SDL_SCANCODE_COMMA);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_DELETE", SDLK_DELETE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_DELETE", SDL_SCANCODE_DELETE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_EQUALS", SDLK_EQUALS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_EQUALS", SDL_SCANCODE_EQUALS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_ESCAPE", SDLK_ESCAPE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_ESCAPE", SDL_SCANCODE_ESCAPE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_GREATER", SDLK_GREATER);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_GREATER", SDL_SCANCODE_KP_GREATER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HASH", SDLK_HASH);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HASH", SDL_SCANCODE_KP_HASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFTBRACKET", SDLK_LEFTBRACKET);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFTBRACKET", SDL_SCANCODE_LEFTBRACKET);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFTPAREN", SDLK_LEFTPAREN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFTPAREN", SDL_SCANCODE_KP_LEFTPAREN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LESS", SDLK_LESS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LESS", SDL_SCANCODE_KP_LESS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MINUS", SDLK_MINUS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MINUS", SDL_SCANCODE_MINUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PERIOD", SDLK_PERIOD);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PERIOD", SDL_SCANCODE_PERIOD);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PLUS", SDLK_PLUS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PLUS", SDL_SCANCODE_KP_PLUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RETURN", SDLK_RETURN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RETURN", SDL_SCANCODE_RETURN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHTBRACKET", SDLK_RIGHTBRACKET);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHTBRACKET", SDL_SCANCODE_RIGHTBRACKET);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHTPAREN", SDLK_RIGHTPAREN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHTPAREN", SDL_SCANCODE_KP_RIGHTPAREN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SEMICOLON", SDLK_SEMICOLON);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SEMICOLON", SDL_SCANCODE_SEMICOLON);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SLASH", SDLK_SLASH);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SLASH", SDL_SCANCODE_SLASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SPACE", SDLK_SPACE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SPACE", SDL_SCANCODE_SPACE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_TAB", SDLK_TAB);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_TAB", SDL_SCANCODE_TAB);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_A", SDLK_a);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_A", SDL_SCANCODE_A);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_B", SDLK_b);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_B", SDL_SCANCODE_B);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_C", SDLK_c);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_C", SDL_SCANCODE_C);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_D", SDLK_d);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_D", SDL_SCANCODE_D);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_E", SDLK_e);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_E", SDL_SCANCODE_E);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F", SDLK_f);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F", SDL_SCANCODE_F);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_G", SDLK_g);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_G", SDL_SCANCODE_G);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_H", SDLK_h);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_H", SDL_SCANCODE_H);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_I", SDLK_i);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_I", SDL_SCANCODE_I);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_J", SDLK_j);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_J", SDL_SCANCODE_J);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_K", SDLK_k);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_K", SDL_SCANCODE_K);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_L", SDLK_l);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_L", SDL_SCANCODE_L);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_M", SDLK_m);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_M", SDL_SCANCODE_M);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_N", SDLK_n);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_N", SDL_SCANCODE_N);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_O", SDLK_o);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_O", SDL_SCANCODE_O);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_P", SDLK_p);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_P", SDL_SCANCODE_P);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Q", SDLK_q);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Q", SDL_SCANCODE_Q);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_R", SDLK_r);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_R", SDL_SCANCODE_R);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_S", SDLK_s);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_S", SDL_SCANCODE_S);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_T", SDLK_t);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_T", SDL_SCANCODE_T);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_U", SDLK_u);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_U", SDL_SCANCODE_U);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_V", SDLK_v);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_V", SDL_SCANCODE_V);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_W", SDLK_w);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_W", SDL_SCANCODE_W);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_X", SDLK_x);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_X", SDL_SCANCODE_X);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Y", SDLK_y);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Y", SDL_SCANCODE_Y);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Z", SDLK_z);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_Z", SDL_SCANCODE_Z);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP0", SDLk_KP0);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP1", SDLK_KP1);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP2", SDLk_KP2);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP3", SDLK_KP3);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP4", SDLK_KP4);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP5", SDLK_KP5);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP6", SDLK_KP6);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP7", SDLK_KP7);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP8", SDLK_KP8);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP9", SDLK_KP9);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP0", SDLK_KP_0);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP1", SDLK_KP_1);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP2", SDLK_KP_2);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP3", SDLK_KP_3);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP4", SDLK_KP_4);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP5", SDLK_KP_5);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP6", SDLK_KP_6);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP7", SDLK_KP_7);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP8", SDLK_KP_8);
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP9", SDLK_KP_9);
#endif

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_PERIOD", SDLK_KP_PERIOD);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_PERIOD", SDL_SCANCODE_KP_PERIOD);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_DIVIDE", SDLK_KP_DIVIDE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_DIVIDE", SDL_SCANCODE_KP_DIVIDE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_MULTIPLY", SDLK_KP_MULTIPLY);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_MULTIPLY", SDL_SCANCODE_KP_MULTIPLY);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_MINUS", SDLK_KP_MINUS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_MINUS", SDL_SCANCODE_KP_MINUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_PLUS", SDLK_KP_PLUS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_PLUS", SDL_SCANCODE_KP_PLUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_ENTER", SDLK_KP_ENTER);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_ENTER", SDL_SCANCODE_KP_ENTER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_EQUALS", SDLK_KP_EQUALS);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_KP_EQUALS", SDL_SCANCODE_KP_EQUALS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_UP", SDLK_UP);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_UP", SDL_SCANCODE_UP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_DOWN", SDLK_DOWN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_DOWN", SDL_SCANCODE_DOWN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHT", SDLK_RIGHT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RIGHT", SDL_SCANCODE_RIGHT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFT", SDLK_LEFT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LEFT", SDL_SCANCODE_LEFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_INSERT", SDLK_INSERT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_INSERT", SDL_SCANCODE_INSERT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HOME", SDLK_HOME);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HOME", SDL_SCANCODE_HOME);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_END", SDLK_END);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_END", SDL_SCANCODE_END);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PAGEUP", SDLK_PAGEUP);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PAGEUP", SDL_SCANCODE_PAGEUP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PAGEDOWN", SDLK_PAGEDOWN);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_PAGEDOWN", SDL_SCANCODE_PAGEDOWN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F1", SDLK_F1);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F1", SDL_SCANCODE_F1);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F2", SDLK_F2);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F2", SDL_SCANCODE_F2);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F3", SDLK_F3);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F3", SDL_SCANCODE_F3);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F4", SDLK_F4);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F4", SDL_SCANCODE_F4);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F5", SDLK_F5);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F5", SDL_SCANCODE_F5);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F6", SDLK_F6);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F6", SDL_SCANCODE_F6);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F7", SDLK_F7);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F7", SDL_SCANCODE_F7);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F8", SDLK_F8);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F8", SDL_SCANCODE_F8);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F9", SDLK_F9);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F9", SDL_SCANCODE_F9);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F10", SDLK_F10);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F10", SDL_SCANCODE_F10);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F11", SDLK_F11);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F11", SDL_SCANCODE_F11);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F12", SDLK_F12);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F12", SDL_SCANCODE_F12);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F13", SDLK_F13);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F13", SDL_SCANCODE_F13);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F14", SDLK_F14);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F14", SDL_SCANCODE_F14);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F15", SDLK_F15);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_F15", SDL_SCANCODE_F15);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_CAPSLOCK", SDLK_CAPSLOCK);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_CAPSLOCK", SDL_SCANCODE_CAPSLOCK);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RSHIFT", SDLK_RSHIFT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RSHIFT", SDL_SCANCODE_RSHIFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LSHIFT", SDLK_LSHIFT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LSHIFT", SDL_SCANCODE_LSHIFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RCTRL", SDLK_RCTRL);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RCTRL", SDL_SCANCODE_RCTRL);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LCTRL", SDLK_LCTRL);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LCTRL", SDL_SCANCODE_LCTRL);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RALT", SDLK_RALT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_RALT", SDL_SCANCODE_RALT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LALT", SDLK_LALT);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_LALT", SDL_SCANCODE_LALT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MODE", SDLK_MODE);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MODE", SDL_SCANCODE_MODE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HELP", SDLK_HELP);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_HELP", SDL_SCANCODE_HELP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SYSREQ", SDLK_SYSREQ);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_SYSREQ", SDL_SCANCODE_SYSREQ);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MENU", SDLK_MENU);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_MENU", SDL_SCANCODE_MENU);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_POWER", SDLK_POWER);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_POWER", SDL_SCANCODE_POWER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_UNDO", SDLK_UNDO);
#else
  PyModule_AddIntConstant(my_mod, "SDL_SCANCODE_UNDO", SDL_SCANCODE_UNDO);
#endif /* } */
}

static std::string get_env(const char *env)
{
  auto t = std::getenv(env);
  if (t)
    return t;
  return "";
}

void python_init(char *argv[])
{
  TRACE_AND_INDENT();
  CON("INI: PYVER %s", PYVER);
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  auto pythonpath = get_env("PYTHONPATH");
  CON("INI: PYTHONPATH is currently '%s'", pythonpath.c_str());
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  auto newpath = pythonpath;
  if (pythonpath.size()) {
    newpath += PATHSEP;
  }
  newpath += EXEC_PYTHONPATH;
  newpath += PATHSEP;
  newpath += EXEC_DIR;
  newpath += PATHSEP;
#ifdef INIT
  newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYVER;
  newpath += PATHSEP;
  newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYVER DIR_SEP "lib-dynload";
  newpath += PATHSEP;
  newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYVER DIR_SEP "site-packages";
  newpath += PATHSEP;
  newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "bin";
#endif

  // Attempt to append to path.
  CON("INI: PYTHONPATH is now '%s'", newpath.c_str());
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //
#ifdef _WIN32
  _putenv_s("PYTHONPATH", newpath.c_str());
#else
  setenv("PYTHONPATH", newpath.c_str(), 1);
#endif

  CON("INI: Calling PyImport_AppendInittab");
  PyImport_AppendInittab("my", python_mouse_y_module_create);
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  CON("INI: Calling Py_Initialize");
  Py_Initialize();
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  py_add_to_path("python");
  py_add_to_path(".." DIR_SEP "python");
  py_add_to_path(GFX_PATH);
  py_add_to_path(DATA_PATH);
  py_add_to_path(EXEC_PYTHONPATH);
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  DBG3("INI: Calling PyImport_ImportModule for my module");

  my_mod = PyImport_ImportModule("my");
  if (! my_mod) {
    py_err();
    ERR("Module my import failed");
    return;
  }

  python_add_consts();

  DBG3("INI: Calling PyImport_ImportModule for init module");

  my_mod = PyImport_ImportModule("init");
  if (! my_mod) {
    py_err();
    ERR("Module init import failed");
    return;
  }

  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////
}

PyObject *py_add_module(const char *mod)
{
  auto name = std::string(mod);
  auto pmod = py_mods[ name ];
  if (pmod != nullptr) {
    return pmod;
  }

  pmod = PyImport_ImportModule(mod);
  if (pmod == nullptr) {
    py_err();
    ERR("Module init '%s' import failed", mod);
    return nullptr;
  }
  py_mods[ name ] = pmod;

  return pmod;
}

void python_fini(void)
{
  TRACE_AND_INDENT();
  Py_Finalize();
}
