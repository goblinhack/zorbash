//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_python.hpp"

void py_call_void(const char *name)
{
  TRACE_AND_INDENT();
  if (! my_mod) {
    DIE("Python module not inited yet");
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(my_mod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pValue = PyObject_CallObject(pFunc, nullptr);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%d)", module, name, val1);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(i)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%d, %d)", module, name, val1, val2);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(ii)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%d, %d, %d)", module, name, val1, val2, val3);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iii)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%d, %d, %d, %d)", module, name, val1, val2, val3, val4);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiii)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%d, %d, %d, %d, %d)", module, name, val1, val2, val3, val4, val5);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiii)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%d, %d, %d, %d, %d, %d)", module, name, val1, val2, val3, val4, val5, val6);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiii)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%d, %d, %d, %d, %d, %d, %d)", module, name, val1, val2, val3, val4, val5, val6, val7);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiii)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%d, %d, %d, %d, %d, %d, %d, %d)", module, name, val1, val2, val3, val4, val5, val6, val7, val8);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u, %u, %u, %u, %u, %u, %u)", module, name, val1, val2, val3, val4, val5, val6, val7, val8,
         val9);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(iiiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8, val9);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u)", module, name, val1);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(I)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u)", module, name, val1, val2);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(II)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u)", module, name, val1, val2, val3);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(III)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u, %u)", module, name, val1, val2, val3, val4);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIII)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u, %u, %u)", module, name, val1, val2, val3, val4, val5);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIII)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u, %u, %u, %u)", module, name, val1, val2, val3, val4, val5, val6);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIII)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u, %u, %u, %u, %u)", module, name, val1, val2, val3, val4, val5, val6, val7);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIII)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u, %u, %u, %u, %u, %u)", module, name, val1, val2, val3, val4, val5, val6, val7, val8);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIIII)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u, %u, %u, %u, %u, %u, %u)", module, name, val1, val2, val3, val4, val5, val6, val7, val8,
         val9);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIIIII)", val1, val2, val3, val4, val5, val6, val7, val8, val9);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
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

  PY_DBG("%s:%s(%u, %u, %u, %u, %u, %u, %u, %u, %u, %u)", module, name, val1, val2, val3, val4, val5, val6, val7,
         val8, val9, val10);
  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs  = Py_BuildValue("(IIIIIIIIII)", val1, val2, val3, val4, val5, val6, val7, val8, val9, val10);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (pValue) {
      Py_DECREF(pValue);
    }
  } else {
    PY_ERR("Cannot call python function: %s", name);
  }

  py_err();
}

bool py_call_bool(const char *name)
{
  TRACE_AND_INDENT();
  if (! my_mod) {
    PY_ERR("Python module not inited yet");
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(my_mod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pValue = PyObject_CallObject(pFunc, nullptr);
    bool      out    = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
  }

  py_err();
  return false;
}

int py_call_int(const char *name)
{
  TRACE_AND_INDENT();
  if (! my_mod) {
    PY_ERR("Python module not inited yet");
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(my_mod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pValue = PyObject_CallObject(pFunc, nullptr);
    int       out    = false;
    if (pValue) {
      out = py_obj_to_int(pValue);
      Py_DECREF(pValue);
    }
    py_err();
    return out;
  } else {
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
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
    PY_ERR("Cannot call python function: %s", name);
  }

  py_err();
  return false;
}
