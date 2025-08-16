//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_log.hpp"
#include "my_main.hpp"
#include "my_python.hpp"

static void py_call_void_(const char *name)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1, int val2)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                             int val6)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                             int val6, int val7)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                             int val6, int val7, int val8)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                             int val6, int val7, int val8, int val9)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5, uint32_t val6)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5, uint32_t val6, uint32_t val7)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8, uint32_t val9)
{
  TRACE_NO_INDENT();
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

static void py_call_void_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8, uint32_t val9,
                             uint32_t val10)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_(const char *name)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, int val1)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, int val1, int val2)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                             int val6)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                             int val6, int val7)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                             int val6, int val7, int val8)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, uint32_t val1)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5, uint32_t val6)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5, uint32_t val6, uint32_t val7)
{
  TRACE_NO_INDENT();
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

static bool py_call_bool_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                             uint32_t val4, uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8)
{
  TRACE_NO_INDENT();
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

static int py_call_int_(const char *name)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, int val1)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, int val1, int val2)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                           int val6)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                           int val6, int val7)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
                           int val6, int val7, int val8)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, uint32_t val1)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                           uint32_t val4)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                           uint32_t val4, uint32_t val5)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                           uint32_t val4, uint32_t val5, uint32_t val6)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                           uint32_t val4, uint32_t val5, uint32_t val6, uint32_t val7)
{
  TRACE_NO_INDENT();
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

static int py_call_int_fn_(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3,
                           uint32_t val4, uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8)
{
  TRACE_NO_INDENT();
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

void py_call_void(const char *name)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_(name);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6, val7);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7, int val8)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7, int val8, int val9)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8, val9);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5, uint32_t val6)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5, uint32_t val6, uint32_t val7)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6, val7);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8, uint32_t val9)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8, val9);
  big_lock.unlock();
}

void py_call_void_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8, uint32_t val9, uint32_t val10)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  py_call_void_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10);
  big_lock.unlock();
}

bool py_call_bool(const char *name)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_(name);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, int val1)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4, val5);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4, val5, val6);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4, val5, val6, val7);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                     int val7, int val8)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, uint32_t val1)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, uint32_t val1, uint32_t val2)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4, val5);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5, uint32_t val6)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4, val5, val6);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5, uint32_t val6, uint32_t val7)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4, val5, val6, val7);
  big_lock.unlock();
  return ret;
}

bool py_call_bool_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                     uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_bool_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8);
  big_lock.unlock();
  return ret;
}

int py_call_int(const char *name)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_(name);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, int val1)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4, val5);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4, val5, val6);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                   int val7)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4, val5, val6, val7);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, int val1, int val2, int val3, int val4, int val5, int val6,
                   int val7, int val8)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, uint32_t val1)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, uint32_t val1, uint32_t val2)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                   uint32_t val5)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4, val5);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                   uint32_t val5, uint32_t val6)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4, val5, val6);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                   uint32_t val5, uint32_t val6, uint32_t val7)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4, val5, val6, val7);
  big_lock.unlock();
  return ret;
}

int py_call_int_fn(const char *module, const char *name, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4,
                   uint32_t val5, uint32_t val6, uint32_t val7, uint32_t val8)
{
  TRACE_NO_INDENT();
  big_lock.lock();
  auto ret = py_call_int_fn_(module, name, val1, val2, val3, val4, val5, val6, val7, val8);
  big_lock.unlock();
  return ret;
}
