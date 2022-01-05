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

char *py_obj_to_string(const PyObject *py_str)
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

std::string py_obj_to_stringing(const PyObject *py_str)
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

  str = py_obj_to_string(py_encstr);
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

    char *text = py_obj_to_string(output);
    if (text) {
      strchopc(text, '\n');
      CON("%s", text);
      myfree(text);
    }
  } else {
    CON("no output");
  }
}

void py_add_to_path(const char *path)
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

    item = py_obj_to_string(py_item);
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
