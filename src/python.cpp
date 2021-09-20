//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <map>
#include "my_py_tp.h"
#include "my_py_thing.h"
#include "my_py_level.h"
#include <frameobject.h>

#include "my_main.h"
#include "my_random.h"
#include "my_callstack.h"
#include "my_depth.h"
#include "my_python.h"
#include "my_py_sdl.h"
#include "my_ascii.h"
#include "my_thing_template.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_sdl.h"
#include "my_string.h"
#include "my_sound.h"

static std::map<std::string, PyObject *> py_mods;
PyObject *zx_mod;
PyMODINIT_FUNC python_mouse_y_module_create(void);

void py_call_void (const char *name)
{_
  if (!zx_mod) {
    ERR("Python module not inited yet");
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(zx_mod, name);
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

void py_call_void_fn (const char *module, const char *name, int val1)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(i)", val1);
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

void py_call_void_fn (const char *module, const char *name, int val1, int val2)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(ii)", val1, val2);
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

void py_call_void_fn (const char *module, const char *name, int val1, int val2, int val3)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iii)", val1, val2, val3);
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

void py_call_void_fn (const char *module, const char *name, int val1, int val2, int val3, int val4)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiii)", val1, val2, val3, val4);
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

void py_call_void_fn (const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiii)", val1, val2, val3, val4, val5);
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

void py_call_void_fn (const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
            int val6)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiiii)", val1, val2, val3, val4, val5, val6);
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

void py_call_void_fn (const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
            int val6, int val7)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiiiii)", val1, val2, val3, val4, val5, val6, val7);
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

void py_call_void_fn (const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
            int val6, int val7, int val8)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
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

void py_call_void_fn (const char *module, const char *name, unsigned int val1)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(I)", val1);
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

void py_call_void_fn (const char *module, const char *name, unsigned int val1, unsigned int val2)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(II)", val1, val2);
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

void py_call_void_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(III)", val1, val2, val3);
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

void py_call_void_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(IIII)", val1, val2, val3, val4);
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

void py_call_void_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4,
    unsigned int val5)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(IIIII)", val1, val2, val3, val4, val5);
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

void py_call_void_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4,
    unsigned int val5,
   unsigned int val6)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(IIIIII)", val1, val2, val3, val4, val5, val6);
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

void py_call_void_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4,
    unsigned int val5,
    unsigned int val6,
    unsigned int val7)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(IIIIIII)", val1, val2, val3, val4, val5, val6, val7);
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

void py_call_void_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4,
    unsigned int val5,
    unsigned int val6,
    unsigned int val7,
    unsigned int val8)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
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

bool py_call_bool (const char *name)
{_
  if (!zx_mod) {
    ERR("Python module not inited yet");
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(zx_mod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pValue = PyObject_CallObject(pFunc, 0);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s", name);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, int val1)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(i)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, int val1, int val2)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(ii)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, int val1, int val2, int val3)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iii)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, int val1, int val2, int val3, int val4)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiii)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, int val1, int val2, int val3, int val4, int val5)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiii)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
            int val6)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiiii)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
            int val6, int val7)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiiiii)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, int val1, int val2, int val3, int val4, int val5,
            int val6, int val7, int val8)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, unsigned int val1)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(I)", val1);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, unsigned int val1, unsigned int val2)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(II)", val1, val2);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(III)", val1, val2, val3);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(IIII)", val1, val2, val3, val4);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4,
    unsigned int val5)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(IIIII)", val1, val2, val3, val4, val5);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4,
    unsigned int val5,
    unsigned int val6)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(IIIIII)", val1, val2, val3, val4, val5, val6);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4,
    unsigned int val5,
    unsigned int val6,
    unsigned int val7)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(IIIIIII)", val1, val2, val3, val4, val5, val6, val7);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

bool py_call_bool_fn (const char *module,
    const char *name,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3,
    unsigned int val4,
    unsigned int val5,
    unsigned int val6,
    unsigned int val7,
    unsigned int val8)
{_
  auto pmod = py_add_module(module);
  if (!pmod) {
    return false;
  }

  PyObject *pFunc = PyObject_GetAttrString(pmod, name);
  if (PyCallable_Check(pFunc)) {
    PyObject *pArgs = Py_BuildValue("(iiiiiiii)", val1, val2, val3, val4, val5, val6, val7, val8);
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    bool out = false;
    if (pValue) {
      out = py_obj_to_bool(pValue);
      Py_DECREF(pValue);
    }
    return out;
  } else {
    ERR("Cannot call python function %s(%d)", name, val1);
  }

  py_err();
  return false;
}

char *py_obj_to_str (const PyObject *py_str)
{_
  PyObject *py_encstr;
  char *outstr = 0;
  char *str;

  py_encstr = 0;
  str = 0;

  if (!PyUnicode_Check((PyObject *)py_str)) {
    ERR("Object is a %s, not a string object.",
      Py_TYPE((PyObject *)py_str)->tp_name);
    goto err_out;
  }

  py_encstr = PyUnicode_AsEncodedString((PyObject *)py_str, "utf-8", 0);
  if (!py_encstr) {
    goto err_out;
  }

  str = PyBytes_AS_STRING(py_encstr);
  if (!str) {
    goto err_out;
  }

  outstr = dupstr(str, __FUNCTION__);

err_out:

  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  return (outstr);
}

std::string py_obj_to_string (const PyObject *py_str)
{_
  PyObject *py_encstr;
  std::string outstr;
  char *str;

  py_encstr = 0;
  str = 0;

  if (!PyUnicode_Check((PyObject *)py_str)) {
    ERR("Object is a %s, not a string object.",
      Py_TYPE((PyObject *)py_str)->tp_name);
    goto err_out;
  }

  py_encstr = PyUnicode_AsEncodedString((PyObject *)py_str, "utf-8", 0);
  if (!py_encstr) {
    goto err_out;
  }

  str = PyBytes_AS_STRING(py_encstr);
  if (!str) {
    goto err_out;
  }

  outstr = std::string(str);

err_out:

  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  return (outstr);
}

int py_obj_to_int (PyObject *py_obj)
{_
  int val;

  val = 0;

  if (!PyLong_Check((PyObject *)py_obj)) {
    ERR("Object is a %s, not a int object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsLong(py_obj);

err_out:
  if (PyErr_Occurred()) {
    ERR("Int conversion failed");
  }

  return (val);
}

int py_obj_to_bool (PyObject *py_obj)
{_
  int val;

  val = 0;

  if (!PyLong_Check((PyObject *)py_obj)) {
    ERR("Object is a %s, not a int object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsLong(py_obj);

err_out:
  if (PyErr_Occurred()) {
    ERR("Int(bool) conversion failed");
  }

  return (val == 0 ? false : true);
}

uint64_t py_obj_to_uint64 (PyObject *py_obj)
{_
  uint64_t val;

  val = 0;

  if (!PyLong_Check((PyObject *)py_obj)) {
    ERR("Object is a %s, not a uint64 object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

  val = PyLong_AsUnsignedLongLong(py_obj);

err_out:

  if (PyErr_Occurred()) {
    ERR("Int conversion failed");
  }

  return (val);
}

double py_obj_to_double (PyObject *py_obj)
{_
  double val;

  val = 0;

  if (PyLong_Check((PyObject *)py_obj)) {
    val = PyLong_AsDouble(py_obj);
  } else if (PyFloat_Check((PyObject *)py_obj)) {
    val = PyFloat_AsDouble(py_obj);
  } else {
    ERR("Object is a %s, not a double object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

err_out:

  if (PyErr_Occurred()) {
    ERR("Int conversion failed");
  }

  return (val);
}

int py_obj_attr_int (const PyObject *py_obj, const char *attr)
{_
  PyObject *py_encstr;
  int i = 0;

  py_encstr = 0;

  if (!PyObject_HasAttrString((PyObject *)py_obj, attr)) {
    ERR("Object is a %s, not a string object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *)py_obj, attr);
  if (!py_encstr) {
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

uint64_t py_obj_attr_uint64 (const PyObject *py_obj, const char *attr)
{_
  PyObject *py_encstr;
  uint64_t i = 0;

  py_encstr = 0;

  if (!PyObject_HasAttrString((PyObject *)py_obj, attr)) {
    ERR("Object is a %s, not a string object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *)py_obj, attr);
  if (!py_encstr) {
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

double py_obj_attr_double (const PyObject *py_obj, const char *attr)
{_
  PyObject *py_encstr;
  double i = 0;

  py_encstr = 0;

  if (!PyObject_HasAttrString((PyObject *)py_obj, attr)) {
    ERR("Object is a %s, not a string object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *)py_obj, attr);
  if (!py_encstr) {
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

char *py_obj_attr_str (const PyObject *py_obj, const char *attr)
{_
  PyObject *py_encstr;
  char *outstr = 0;
  char *str;

  py_encstr = 0;
  str = 0;

  if (!PyObject_HasAttrString((PyObject *)py_obj, attr)) {
    ERR("Object is a %s, not a string object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *)py_obj, attr);
  if (!py_encstr) {
    goto err_out;
  }

  str = py_obj_to_str(py_encstr);
  if (!str) {
    goto err_out;
  }

  outstr = str;

err_out:

  if (py_encstr) {
    Py_XDECREF(py_encstr);
  }

  return (outstr);
}

PyObject *py_obj_attr (const PyObject *py_obj, const char *attr)
{_
  PyObject *py_encstr;

  py_encstr = 0;

  if (!PyObject_HasAttrString((PyObject *)py_obj, attr)) {
    ERR("Object is a %s, not a string object.",
      Py_TYPE((PyObject *)py_obj)->tp_name);
    goto err_out;
  }

  py_encstr = PyObject_GetAttrString((PyObject *)py_obj, attr);
  if (!py_encstr) {
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

static PyObject *con_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  wchar_t *a = 0;

  if (!PyArg_ParseTuple(args, "u", &a)) {
    ERR("con: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    con(a);
  }

  Py_RETURN_TRUE;
}

static PyObject *topcon_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  wchar_t *a = 0;

  if (!PyArg_ParseTuple(args, "u", &a)) {
    ERR("topcon: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    topcon(a);
  }

  Py_RETURN_TRUE;
}

static PyObject *puts_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  char *a = 0;

  if (!PyArg_ParseTuple(args, "s", &a)) {
    ERR("puts: Bad args");
    Py_RETURN_FALSE;
  }

  fputs(a, MY_STDOUT);
  fflush(MY_STDOUT);
  printf("%s", a);

  Py_RETURN_TRUE;
}

static PyObject *log_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  char *a = 0;

  if (!PyArg_ParseTuple(args, "s", &a)) {
    ERR("log: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    LOG("%s", a);
  }

  Py_RETURN_TRUE;
}

static PyObject *err_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  char *a = 0;

  if (!PyArg_ParseTuple(args, "s", &a)) {
    ERR("err: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    ERR("%s", a);
  }

  Py_RETURN_TRUE;
}

static PyObject *die_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  char *a = 0;

  if (!PyArg_ParseTuple(args, "s", &a)) {
    ERR("die: Bad args");
    Py_RETURN_FALSE;
  }

  if (a) {
    ERR("%s", a);
  }

  Py_RETURN_TRUE;
}

static PyMethodDef python_c_METHODS[] = {
  /*
   * The cast of the function is necessary since PyCFunction values
   * only take two PyObject *parameters, and some take three.
   */

  #define ZX_ADD_PYTHON_FUNCTION(__func__) \
    { #__func__, (PyCFunction)__func__, METH_VARARGS | METH_KEYWORDS, #__func__ },

  #define ZX_ADD_WRAPPED_PYTHON_FUNCTION(__func__) \
    { #__func__, (PyCFunction)__func__ ## _, METH_VARARGS | METH_KEYWORDS, #__func__ },

  ZX_ADD_PYTHON_TP_FUNCTION(ai_avoid_distance)
  ZX_ADD_PYTHON_TP_FUNCTION(ai_enemy_memory)
  ZX_ADD_PYTHON_TP_FUNCTION(ai_obstacle)
  ZX_ADD_PYTHON_TP_FUNCTION(ai_scent_distance)
  ZX_ADD_PYTHON_TP_FUNCTION(ai_vision_distance)
  ZX_ADD_PYTHON_TP_FUNCTION(attack_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(attack_humanoid)
  ZX_ADD_PYTHON_TP_FUNCTION(attack_living)
  ZX_ADD_PYTHON_TP_FUNCTION(attack_lunge)
  ZX_ADD_PYTHON_TP_FUNCTION(attack_meat)
  ZX_ADD_PYTHON_TP_FUNCTION(attack_shove)
  ZX_ADD_PYTHON_TP_FUNCTION(attack_shove_chance_d1000)
  ZX_ADD_PYTHON_TP_FUNCTION(bl1_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(bl2_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(blast_max_radius)
  ZX_ADD_PYTHON_TP_FUNCTION(blast_min_radius)
  ZX_ADD_PYTHON_TP_FUNCTION(blit_bot_off)
  ZX_ADD_PYTHON_TP_FUNCTION(blit_left_off)
  ZX_ADD_PYTHON_TP_FUNCTION(blit_right_off)
  ZX_ADD_PYTHON_TP_FUNCTION(blit_top_off)
  ZX_ADD_PYTHON_TP_FUNCTION(bot1_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(bot2_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(bot3_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(br1_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(br2_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(capacity_height)
  ZX_ADD_PYTHON_TP_FUNCTION(capacity_width)
  ZX_ADD_PYTHON_TP_FUNCTION(charge_count)
  ZX_ADD_PYTHON_TP_FUNCTION(collision_attack)
  ZX_ADD_PYTHON_TP_FUNCTION(collision_attack_radius)
  ZX_ADD_PYTHON_TP_FUNCTION(collision_box)
  ZX_ADD_PYTHON_TP_FUNCTION(collision_check)
  ZX_ADD_PYTHON_TP_FUNCTION(collision_circle)
  ZX_ADD_PYTHON_TP_FUNCTION(collision_hit_priority)
  ZX_ADD_PYTHON_TP_FUNCTION(collision_radius)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_bite_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_crush_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_doubled_from_acid)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_doubled_from_fire)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_doubled_from_poison)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_doubled_from_water)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_melee_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_poison_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(damage_swallow_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(enchant_level)
  ZX_ADD_PYTHON_TP_FUNCTION(enchant_max)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_an_animation_only)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_anim_attack)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_animated)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_animated_can_hflip)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_animated_can_vflip)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_animated_no_dir)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_attack_anim)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_bounce_always)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_bounce_on_move)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_dead_anim)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_flickers)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_glows)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_health_bar_shown)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_health_bar_autohide)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_long_shadow_caster)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_on_fire_anim)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_oversized_and_on_floor)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_short_shadow_caster)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_show_outlined)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_shown_in_bg)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_solid_shadow)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_very_short_shadow_caster)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_water)
  ZX_ADD_PYTHON_TP_FUNCTION(gfx_weapon_carry_anim)
  ZX_ADD_PYTHON_TP_FUNCTION(gold_value_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(hates_acid)
  ZX_ADD_PYTHON_TP_FUNCTION(hates_fire)
  ZX_ADD_PYTHON_TP_FUNCTION(hates_poison)
  ZX_ADD_PYTHON_TP_FUNCTION(hates_water)
  ZX_ADD_PYTHON_TP_FUNCTION(health_hunger_pct)
  ZX_ADD_PYTHON_TP_FUNCTION(health_initial_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(health_starving_pct)
  ZX_ADD_PYTHON_TP_FUNCTION(is_able_to_change_levels)
  ZX_ADD_PYTHON_TP_FUNCTION(is_able_to_fall)
  ZX_ADD_PYTHON_TP_FUNCTION(is_able_to_fire_at)
  ZX_ADD_PYTHON_TP_FUNCTION(is_able_to_see_through_doors)
  ZX_ADD_PYTHON_TP_FUNCTION(is_able_to_walk_through_walls)
  ZX_ADD_PYTHON_TP_FUNCTION(is_acid)
  ZX_ADD_PYTHON_TP_FUNCTION(is_acid_lover)
  ZX_ADD_PYTHON_TP_FUNCTION(is_ai_wanderer)
  ZX_ADD_PYTHON_TP_FUNCTION(is_alive_on_end_of_anim)
  ZX_ADD_PYTHON_TP_FUNCTION(is_always_hit)
  ZX_ADD_PYTHON_TP_FUNCTION(is_ascend_dungeon)
  ZX_ADD_PYTHON_TP_FUNCTION(is_ascend_sewer)
  ZX_ADD_PYTHON_TP_FUNCTION(is_attackable_by_monst)
  ZX_ADD_PYTHON_TP_FUNCTION(is_attackable_by_player)
  ZX_ADD_PYTHON_TP_FUNCTION(is_auto_collect_item)
  ZX_ADD_PYTHON_TP_FUNCTION(is_bag)
  ZX_ADD_PYTHON_TP_FUNCTION(is_bag_item)
  ZX_ADD_PYTHON_TP_FUNCTION(is_bag_item_container)
  ZX_ADD_PYTHON_TP_FUNCTION(is_bag_item_not_stackable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_barrel)
  ZX_ADD_PYTHON_TP_FUNCTION(is_bleeder)
  ZX_ADD_PYTHON_TP_FUNCTION(is_blood)
  ZX_ADD_PYTHON_TP_FUNCTION(is_blood_splatter)
  ZX_ADD_PYTHON_TP_FUNCTION(is_bones)
  ZX_ADD_PYTHON_TP_FUNCTION(is_brazier)
  ZX_ADD_PYTHON_TP_FUNCTION(is_bridge)
  ZX_ADD_PYTHON_TP_FUNCTION(is_burnable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_carrier_of_treasure_class_a)
  ZX_ADD_PYTHON_TP_FUNCTION(is_carrier_of_treasure_class_b)
  ZX_ADD_PYTHON_TP_FUNCTION(is_carrier_of_treasure_class_c)
  ZX_ADD_PYTHON_TP_FUNCTION(is_chasm)
  ZX_ADD_PYTHON_TP_FUNCTION(is_collect_as_keys)
  ZX_ADD_PYTHON_TP_FUNCTION(is_collectable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_collected_as_gold)
  ZX_ADD_PYTHON_TP_FUNCTION(is_combustible)
  ZX_ADD_PYTHON_TP_FUNCTION(is_corpse_on_death)
  ZX_ADD_PYTHON_TP_FUNCTION(is_corridor)
  ZX_ADD_PYTHON_TP_FUNCTION(is_critical_to_level)
  ZX_ADD_PYTHON_TP_FUNCTION(is_cursor)
  ZX_ADD_PYTHON_TP_FUNCTION(is_cursor_can_hover_over)
  ZX_ADD_PYTHON_TP_FUNCTION(is_cursor_can_hover_over_2x_click)
  ZX_ADD_PYTHON_TP_FUNCTION(is_cursor_path)
  ZX_ADD_PYTHON_TP_FUNCTION(is_dead_on_end_of_anim)
  ZX_ADD_PYTHON_TP_FUNCTION(is_dead_on_shove)
  ZX_ADD_PYTHON_TP_FUNCTION(is_debug_path)
  ZX_ADD_PYTHON_TP_FUNCTION(is_debug_type)
  ZX_ADD_PYTHON_TP_FUNCTION(is_deep_water)
  ZX_ADD_PYTHON_TP_FUNCTION(is_descend_dungeon)
  ZX_ADD_PYTHON_TP_FUNCTION(is_descend_sewer)
  ZX_ADD_PYTHON_TP_FUNCTION(is_described_when_hovering_over)
  ZX_ADD_PYTHON_TP_FUNCTION(is_dirt)
  ZX_ADD_PYTHON_TP_FUNCTION(is_door)
  ZX_ADD_PYTHON_TP_FUNCTION(is_droppable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_dry_grass)
  ZX_ADD_PYTHON_TP_FUNCTION(is_enchantable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_enchantstone)
  ZX_ADD_PYTHON_TP_FUNCTION(is_engulf_chance_d1000)
  ZX_ADD_PYTHON_TP_FUNCTION(is_engulfer)
  ZX_ADD_PYTHON_TP_FUNCTION(is_ethereal)
  ZX_ADD_PYTHON_TP_FUNCTION(is_ethereal_minion_generator)
  ZX_ADD_PYTHON_TP_FUNCTION(is_explosion)
  ZX_ADD_PYTHON_TP_FUNCTION(is_extreme_hazard)
  ZX_ADD_PYTHON_TP_FUNCTION(is_fearless)
  ZX_ADD_PYTHON_TP_FUNCTION(is_fire)
  ZX_ADD_PYTHON_TP_FUNCTION(is_floating)
  ZX_ADD_PYTHON_TP_FUNCTION(is_floor)
  ZX_ADD_PYTHON_TP_FUNCTION(is_floor_deco)
  ZX_ADD_PYTHON_TP_FUNCTION(is_foilage)
  ZX_ADD_PYTHON_TP_FUNCTION(is_food)
  ZX_ADD_PYTHON_TP_FUNCTION(is_food_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(is_glass)
  ZX_ADD_PYTHON_TP_FUNCTION(is_gold)
  ZX_ADD_PYTHON_TP_FUNCTION(is_hazard)
  ZX_ADD_PYTHON_TP_FUNCTION(is_health_booster)
  ZX_ADD_PYTHON_TP_FUNCTION(is_hittable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_humanoid)
  ZX_ADD_PYTHON_TP_FUNCTION(is_hunger_insatiable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_indestructible)
  ZX_ADD_PYTHON_TP_FUNCTION(is_intelligent)
  ZX_ADD_PYTHON_TP_FUNCTION(is_interesting)
  ZX_ADD_PYTHON_TP_FUNCTION(is_item)
  ZX_ADD_PYTHON_TP_FUNCTION(is_item_carrier)
  ZX_ADD_PYTHON_TP_FUNCTION(is_item_collector)
  ZX_ADD_PYTHON_TP_FUNCTION(is_item_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(is_item_organic)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jelly)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jelly_baby)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jelly_baby_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jelly_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jelly_parent)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jumper)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jumper_chance_d1000)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jumper_distance)
  ZX_ADD_PYTHON_TP_FUNCTION(is_jumper_on_low_hp_chance_d1000)
  ZX_ADD_PYTHON_TP_FUNCTION(is_key)
  ZX_ADD_PYTHON_TP_FUNCTION(is_key_collector)
  ZX_ADD_PYTHON_TP_FUNCTION(is_killed_on_hit_or_miss)
  ZX_ADD_PYTHON_TP_FUNCTION(is_killed_on_hitting)
  ZX_ADD_PYTHON_TP_FUNCTION(is_laser)
  ZX_ADD_PYTHON_TP_FUNCTION(is_lava)
  ZX_ADD_PYTHON_TP_FUNCTION(is_light_blocker)
  ZX_ADD_PYTHON_TP_FUNCTION(is_living)
  ZX_ADD_PYTHON_TP_FUNCTION(is_loggable_for_important_stuff)
  ZX_ADD_PYTHON_TP_FUNCTION(is_loggable_for_unimportant_stuff)
  ZX_ADD_PYTHON_TP_FUNCTION(is_meat)
  ZX_ADD_PYTHON_TP_FUNCTION(is_meat_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(is_metal)
  ZX_ADD_PYTHON_TP_FUNCTION(is_minion)
  ZX_ADD_PYTHON_TP_FUNCTION(is_minion_generator)
  ZX_ADD_PYTHON_TP_FUNCTION(is_monst)
  ZX_ADD_PYTHON_TP_FUNCTION(is_moveable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_msg)
  ZX_ADD_PYTHON_TP_FUNCTION(is_no_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(is_obs_destructable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_obs_wall_or_door)
  ZX_ADD_PYTHON_TP_FUNCTION(is_openable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_organic)
  ZX_ADD_PYTHON_TP_FUNCTION(is_player)
  ZX_ADD_PYTHON_TP_FUNCTION(is_poison)
  ZX_ADD_PYTHON_TP_FUNCTION(is_potion)
  ZX_ADD_PYTHON_TP_FUNCTION(is_potion_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(is_projectile)
  ZX_ADD_PYTHON_TP_FUNCTION(is_removeable_if_out_of_slots)
  ZX_ADD_PYTHON_TP_FUNCTION(is_resurrectable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_ripple)
  ZX_ADD_PYTHON_TP_FUNCTION(is_rock)
  ZX_ADD_PYTHON_TP_FUNCTION(is_rusty)
  ZX_ADD_PYTHON_TP_FUNCTION(is_secret_door)
  ZX_ADD_PYTHON_TP_FUNCTION(is_sewer_wall)
  ZX_ADD_PYTHON_TP_FUNCTION(is_shallow_water)
  ZX_ADD_PYTHON_TP_FUNCTION(is_shovable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_skill)
  ZX_ADD_PYTHON_TP_FUNCTION(is_skillstone)
  ZX_ADD_PYTHON_TP_FUNCTION(is_smoke)
  ZX_ADD_PYTHON_TP_FUNCTION(is_soft_body)
  ZX_ADD_PYTHON_TP_FUNCTION(is_spawner)
  ZX_ADD_PYTHON_TP_FUNCTION(is_spiderweb)
  ZX_ADD_PYTHON_TP_FUNCTION(is_stamina_check)
  ZX_ADD_PYTHON_TP_FUNCTION(is_steal_item_chance_d1000)
  ZX_ADD_PYTHON_TP_FUNCTION(is_sticky)
  ZX_ADD_PYTHON_TP_FUNCTION(is_stone)
  ZX_ADD_PYTHON_TP_FUNCTION(is_sword)
  ZX_ADD_PYTHON_TP_FUNCTION(is_target_auto_select)
  ZX_ADD_PYTHON_TP_FUNCTION(is_the_grid)
  ZX_ADD_PYTHON_TP_FUNCTION(is_throwable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_auto_throw)
  ZX_ADD_PYTHON_TP_FUNCTION(is_tickable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_tmp_thing)
  ZX_ADD_PYTHON_TP_FUNCTION(is_torch)
  ZX_ADD_PYTHON_TP_FUNCTION(is_treasure_class_a)
  ZX_ADD_PYTHON_TP_FUNCTION(is_treasure_class_b)
  ZX_ADD_PYTHON_TP_FUNCTION(is_treasure_class_c)
  ZX_ADD_PYTHON_TP_FUNCTION(is_treasure_type)
  ZX_ADD_PYTHON_TP_FUNCTION(is_treasure_type_chest)
  ZX_ADD_PYTHON_TP_FUNCTION(is_treasure_type_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(is_undead)
  ZX_ADD_PYTHON_TP_FUNCTION(is_usable)
  ZX_ADD_PYTHON_TP_FUNCTION(is_auto_use)
  ZX_ADD_PYTHON_TP_FUNCTION(is_used_when_thrown)
  ZX_ADD_PYTHON_TP_FUNCTION(is_very_combustible)
  ZX_ADD_PYTHON_TP_FUNCTION(is_wall)
  ZX_ADD_PYTHON_TP_FUNCTION(is_wall_dungeon)
  ZX_ADD_PYTHON_TP_FUNCTION(is_wand)
  ZX_ADD_PYTHON_TP_FUNCTION(is_wand_eater)
  ZX_ADD_PYTHON_TP_FUNCTION(is_water_lover)
  ZX_ADD_PYTHON_TP_FUNCTION(is_weapon)
  ZX_ADD_PYTHON_TP_FUNCTION(is_weapon_wielder)
  ZX_ADD_PYTHON_TP_FUNCTION(is_wooden)
  ZX_ADD_PYTHON_TP_FUNCTION(item_height)
  ZX_ADD_PYTHON_TP_FUNCTION(item_width)
  ZX_ADD_PYTHON_TP_FUNCTION(laser_name)
  ZX_ADD_PYTHON_TP_FUNCTION(left1_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(left2_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(lifespan_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(light_color)
  ZX_ADD_PYTHON_TP_FUNCTION(light_strength)
  ZX_ADD_PYTHON_TP_FUNCTION(long_text_description)
  ZX_ADD_PYTHON_TP_FUNCTION(loves_fire)
  ZX_ADD_PYTHON_TP_FUNCTION(loves_poison)
  ZX_ADD_PYTHON_TP_FUNCTION(loves_spiderwebs)
  ZX_ADD_PYTHON_TP_FUNCTION(minion_leash_distance)
  ZX_ADD_PYTHON_TP_FUNCTION(minion_limit)
  ZX_ADD_PYTHON_TP_FUNCTION(monst_size)
  ZX_ADD_PYTHON_TP_FUNCTION(name)
  ZX_ADD_PYTHON_TP_FUNCTION(normal_placement_rules)
  ZX_ADD_PYTHON_TP_FUNCTION(nutrition_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(on_birth_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_bite_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_born_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_death_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_death_drop_all_items)
  ZX_ADD_PYTHON_TP_FUNCTION(on_death_is_open)
  ZX_ADD_PYTHON_TP_FUNCTION(on_enchant_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_fall_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_fire_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_firing_at_something_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_hit_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_idle_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(on_lifespan_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_miss_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_move_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_open_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_tick_do)
  ZX_ADD_PYTHON_TP_FUNCTION(on_use_do)
  ZX_ADD_PYTHON_TP_FUNCTION(projectile_name)
  ZX_ADD_PYTHON_TP_FUNCTION(range_max)
  ZX_ADD_PYTHON_TP_FUNCTION(rarity)
  ZX_ADD_PYTHON_TP_FUNCTION(resurrect_dice)
  ZX_ADD_PYTHON_TP_FUNCTION(right1_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(right2_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(spawn_on_shoved)
  ZX_ADD_PYTHON_TP_FUNCTION(stamina)
  ZX_ADD_PYTHON_TP_FUNCTION(stat_attack)
  ZX_ADD_PYTHON_TP_FUNCTION(stat_constitution)
  ZX_ADD_PYTHON_TP_FUNCTION(stat_defence)
  ZX_ADD_PYTHON_TP_FUNCTION(stat_strength)
  ZX_ADD_PYTHON_TP_FUNCTION(stats01)
  ZX_ADD_PYTHON_TP_FUNCTION(stats02)
  ZX_ADD_PYTHON_TP_FUNCTION(stats03)
  ZX_ADD_PYTHON_TP_FUNCTION(stats04)
  ZX_ADD_PYTHON_TP_FUNCTION(stats05)
  ZX_ADD_PYTHON_TP_FUNCTION(stats06)
  ZX_ADD_PYTHON_TP_FUNCTION(stats07)
  ZX_ADD_PYTHON_TP_FUNCTION(stats08)
  ZX_ADD_PYTHON_TP_FUNCTION(stats09)
  ZX_ADD_PYTHON_TP_FUNCTION(stats10)
  ZX_ADD_PYTHON_TP_FUNCTION(stats11)
  ZX_ADD_PYTHON_TP_FUNCTION(stats12)
  ZX_ADD_PYTHON_TP_FUNCTION(stats17)
  ZX_ADD_PYTHON_TP_FUNCTION(str1)
  ZX_ADD_PYTHON_TP_FUNCTION(str2)
  ZX_ADD_PYTHON_TP_FUNCTION(str4)
  ZX_ADD_PYTHON_TP_FUNCTION(str5)
  ZX_ADD_PYTHON_TP_FUNCTION(text_a_or_an)
  ZX_ADD_PYTHON_TP_FUNCTION(text_description)
  ZX_ADD_PYTHON_TP_FUNCTION(text_enchant)
  ZX_ADD_PYTHON_TP_FUNCTION(text_hits)
  ZX_ADD_PYTHON_TP_FUNCTION(text_name)
  ZX_ADD_PYTHON_TP_FUNCTION(text_skill)
  ZX_ADD_PYTHON_TP_FUNCTION(text_title)
  ZX_ADD_PYTHON_TP_FUNCTION(text_unused)
  ZX_ADD_PYTHON_TP_FUNCTION(throw_distance)
  ZX_ADD_PYTHON_TP_FUNCTION(tile)
  ZX_ADD_PYTHON_TP_FUNCTION(tl1_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(tl2_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(top1_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(top2_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(tr1_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(tr2_tile)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag1)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag10)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag11)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag12)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag13)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag14)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag15)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag16)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag17)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag18)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag19)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag2)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag20)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag21)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag22)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag23)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag24)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag25)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag26)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag27)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag28)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag29)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag3)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag30)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag31)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag32)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag33)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag34)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag35)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag36)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag37)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag38)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag39)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag4)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag40)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag41)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag42)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag43)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag44)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag45)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag46)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag47)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag48)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag5)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag50)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag51)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag52)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag6)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag7)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag8)
  ZX_ADD_PYTHON_TP_FUNCTION(unused_flag9)
  ZX_ADD_PYTHON_TP_FUNCTION(weapon_carry_anim)
  ZX_ADD_PYTHON_TP_FUNCTION(weapon_damage)
  ZX_ADD_PYTHON_TP_FUNCTION(weapon_use_distance)
  ZX_ADD_PYTHON_TP_FUNCTION(z_depth)
  ZX_ADD_PYTHON_TP_FUNCTION(z_prio)
  ZX_ADD_PYTHON_FUNCTION(level_ai_enemy_memory_at)
  ZX_ADD_PYTHON_FUNCTION(level_enchant_level_at)
  ZX_ADD_PYTHON_FUNCTION(level_enchant_max_at)
  ZX_ADD_PYTHON_FUNCTION(level_flood_fill_get_all_things)
  ZX_ADD_PYTHON_FUNCTION(level_get_all)
  ZX_ADD_PYTHON_FUNCTION(level_gfx_flickers_at)
  ZX_ADD_PYTHON_FUNCTION(level_gfx_long_shadow_caster_at)
  ZX_ADD_PYTHON_FUNCTION(level_gfx_solid_shadow_at)
  ZX_ADD_PYTHON_FUNCTION(level_gfx_very_short_shadow_caster_at)
  ZX_ADD_PYTHON_FUNCTION(level_gfx_water_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_able_to_change_levels_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_able_to_fall_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_able_to_fire_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_able_to_fire_at_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_able_to_see_through_doors_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_able_to_walk_through_walls_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_acid_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_acid_lover_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_ai_wanderer_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_alive_monst_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_alive_on_end_of_anim_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_always_hit_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_ascend_dungeon_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_ascend_sewer_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_attackable_by_monst_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_attackable_by_player_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_auto_collect_item_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_bag_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_bag_item_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_bag_item_container_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_bag_item_not_stackable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_barrel_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_bleeder_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_blood_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_blood_splatter_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_bloodied_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_bones_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_brazier_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_bridge_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_burnable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_carrier_of_treasure_class_a_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_carrier_of_treasure_class_b_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_carrier_of_treasure_class_c_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_carrying_item_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_carrying_treasure_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_chasm_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_collect_as_keys_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_collectable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_collected_as_gold_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_combustible_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_corpse_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_corpse_on_death_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_corridor_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_critical_to_level_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_cursor_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_cursor_can_hover_over_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_cursor_path_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dead_on_end_of_anim_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dead_on_shove_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_debug_path_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_debug_type_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_deep_water_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_descend_dungeon_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_descend_sewer_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_described_when_hovering_over_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_bl_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_br_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_down_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_left_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_none_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_right_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_tl_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_tr_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dir_up_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dirt_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_door_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_droppable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_dry_grass_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_enchantable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_enchantstone_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_engulf_chance_d1000_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_engulfer_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_ethereal_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_ethereal_minion_generator_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_explosion_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_extreme_hazard_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_fearless_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_fire_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_floating_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_floor_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_floor_deco_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_foilage_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_food_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_food_eater_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_glass_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_gold_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_hazard_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_health_booster_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_hittable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_humanoid_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_hunger_insatiable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_indestructible_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_intelligent_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_interesting_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_item_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_item_carrier_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_item_collector_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_item_eater_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_item_organic_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jelly_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jelly_baby_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jelly_baby_eater_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jelly_eater_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jelly_parent_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jumper_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jumper_chance_d1000_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jumper_distance_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_jumper_on_low_hp_chance_d1000_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_key_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_key_collector_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_killed_on_hit_or_miss_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_killed_on_hitting_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_laser_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_lava_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_light_blocker_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_living_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_meat_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_meat_eater_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_metal_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_minion_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_minion_generator_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_monst_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_moveable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_msg_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_no_tile_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_obs_destructable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_obs_wall_or_door_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_on_firing_at_something)
  ZX_ADD_PYTHON_FUNCTION(level_is_openable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_organic_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_player_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_poison_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_potion_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_potion_eater_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_projectile_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_removeable_if_out_of_slots_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_resurrectable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_ripple_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_rock_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_rusty_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_secret_door_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_sewer_wall_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_shallow_water_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_shovable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_skill_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_skillstone_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_smoke_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_soft_body_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_spawner_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_spiderweb_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_stamina_check_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_steal_item_chance_d1000_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_sticky_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_stone_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_sword_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_throwable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_tickable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_tmp_thing_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_torch_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_treasure_class_a_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_treasure_class_b_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_treasure_class_c_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_treasure_type_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_treasure_type_chest_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_treasure_type_eater_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_undead_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_usable_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_used_when_thrown_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_very_combustible_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_visible_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_wall_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_wall_dungeon_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_wand_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_wand_eater_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_water_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_water_lover_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_weapon_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_weapon_wielder_at)
  ZX_ADD_PYTHON_FUNCTION(level_is_wooden_at)
  ZX_ADD_PYTHON_FUNCTION(level_loves_fire_at)
  ZX_ADD_PYTHON_FUNCTION(level_loves_poison_at)
  ZX_ADD_PYTHON_FUNCTION(level_loves_spiderwebs_at)
  ZX_ADD_PYTHON_FUNCTION(level_place_at)
  ZX_ADD_PYTHON_FUNCTION(level_spawn_at_thing)
  ZX_ADD_PYTHON_FUNCTION(level_spawn_at_thing_if_possible)
  ZX_ADD_PYTHON_FUNCTION(level_spawn_fire_around_thing)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag10_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag11_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag12_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag13_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag14_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag15_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag16_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag17_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag18_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag19_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag1_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag20_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag21_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag22_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag23_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag24_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag25_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag26_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag27_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag28_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag29_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag2_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag30_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag31_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag32_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag33_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag34_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag35_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag36_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag37_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag38_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag39_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag3_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag40_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag41_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag42_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag43_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag44_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag45_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag46_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag47_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag48_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag4_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag50_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag51_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag52_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag5_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag6_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag7_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag8_at)
  ZX_ADD_PYTHON_FUNCTION(level_unused_flag9_at)
  ZX_ADD_PYTHON_FUNCTION(non_pcg_randint)
  ZX_ADD_PYTHON_FUNCTION(pcg_randint)
  ZX_ADD_PYTHON_FUNCTION(sound_play)
  ZX_ADD_PYTHON_FUNCTION(sound_play_channel)
  ZX_ADD_PYTHON_FUNCTION(thing_ai_enemy_memory)
  ZX_ADD_PYTHON_FUNCTION(thing_decr_charge_count)
  ZX_ADD_PYTHON_FUNCTION(thing_decr_current_damage)
  ZX_ADD_PYTHON_FUNCTION(thing_decr_enchant)
  ZX_ADD_PYTHON_FUNCTION(thing_decr_enchant_max)
  ZX_ADD_PYTHON_FUNCTION(thing_decr_health)
  ZX_ADD_PYTHON_FUNCTION(thing_decr_health_max)
  ZX_ADD_PYTHON_FUNCTION(thing_decr_stamina)
  ZX_ADD_PYTHON_FUNCTION(thing_decr_stamina_max)
  ZX_ADD_PYTHON_FUNCTION(thing_enchant_level)
  ZX_ADD_PYTHON_FUNCTION(thing_enchant_max)
  ZX_ADD_PYTHON_FUNCTION(thing_fire_at)
  ZX_ADD_PYTHON_FUNCTION(thing_get_charge_count)
  ZX_ADD_PYTHON_FUNCTION(thing_get_coords)
  ZX_ADD_PYTHON_FUNCTION(thing_get_current_damage)
  ZX_ADD_PYTHON_FUNCTION(thing_get_damage_bite)
  ZX_ADD_PYTHON_FUNCTION(thing_get_damage_crush)
  ZX_ADD_PYTHON_FUNCTION(thing_get_damage_melee)
  ZX_ADD_PYTHON_FUNCTION(thing_get_damage_swallow)
  ZX_ADD_PYTHON_FUNCTION(thing_get_enchant)
  ZX_ADD_PYTHON_FUNCTION(thing_get_enchant_max)
  ZX_ADD_PYTHON_FUNCTION(thing_get_health)
  ZX_ADD_PYTHON_FUNCTION(thing_get_health_max)
  ZX_ADD_PYTHON_FUNCTION(thing_get_immediate_minion_owner_id)
  ZX_ADD_PYTHON_FUNCTION(thing_get_immediate_owner_id)
  ZX_ADD_PYTHON_FUNCTION(thing_get_immediate_spawned_owner_id)
  ZX_ADD_PYTHON_FUNCTION(thing_get_initial_charge_count)
  ZX_ADD_PYTHON_FUNCTION(thing_get_name)
  ZX_ADD_PYTHON_FUNCTION(thing_get_stamina)
  ZX_ADD_PYTHON_FUNCTION(thing_get_stamina_max)
  ZX_ADD_PYTHON_FUNCTION(thing_get_top_owner_id)
  ZX_ADD_PYTHON_FUNCTION(thing_gfx_flickers)
  ZX_ADD_PYTHON_FUNCTION(thing_gfx_long_shadow_caster)
  ZX_ADD_PYTHON_FUNCTION(thing_gfx_solid_shadow)
  ZX_ADD_PYTHON_FUNCTION(thing_gfx_very_short_shadow_caster)
  ZX_ADD_PYTHON_FUNCTION(thing_gfx_water)
  ZX_ADD_PYTHON_FUNCTION(thing_hit)
  ZX_ADD_PYTHON_FUNCTION(thing_incr_charge_count)
  ZX_ADD_PYTHON_FUNCTION(thing_incr_current_damage)
  ZX_ADD_PYTHON_FUNCTION(thing_incr_enchant)
  ZX_ADD_PYTHON_FUNCTION(thing_incr_enchant_max)
  ZX_ADD_PYTHON_FUNCTION(thing_incr_health)
  ZX_ADD_PYTHON_FUNCTION(thing_incr_health_max)
  ZX_ADD_PYTHON_FUNCTION(thing_incr_stamina)
  ZX_ADD_PYTHON_FUNCTION(thing_incr_stamina_max)
  ZX_ADD_PYTHON_FUNCTION(thing_is_able_to_change_levels)
  ZX_ADD_PYTHON_FUNCTION(thing_is_able_to_fall)
  ZX_ADD_PYTHON_FUNCTION(thing_is_able_to_see_through_doors)
  ZX_ADD_PYTHON_FUNCTION(thing_is_able_to_walk_through_walls)
  ZX_ADD_PYTHON_FUNCTION(thing_is_acid)
  ZX_ADD_PYTHON_FUNCTION(thing_is_acid_lover)
  ZX_ADD_PYTHON_FUNCTION(thing_is_ai_wanderer)
  ZX_ADD_PYTHON_FUNCTION(thing_is_alive_monst)
  ZX_ADD_PYTHON_FUNCTION(thing_is_alive_on_end_of_anim)
  ZX_ADD_PYTHON_FUNCTION(thing_is_always_hit)
  ZX_ADD_PYTHON_FUNCTION(thing_is_ascend_dungeon)
  ZX_ADD_PYTHON_FUNCTION(thing_is_ascend_sewer)
  ZX_ADD_PYTHON_FUNCTION(thing_is_auto_collect_item)
  ZX_ADD_PYTHON_FUNCTION(thing_is_bag)
  ZX_ADD_PYTHON_FUNCTION(thing_is_bag_item)
  ZX_ADD_PYTHON_FUNCTION(thing_is_bag_item_container)
  ZX_ADD_PYTHON_FUNCTION(thing_is_bag_item_not_stackable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_barrel)
  ZX_ADD_PYTHON_FUNCTION(thing_is_bleeder)
  ZX_ADD_PYTHON_FUNCTION(thing_is_blood)
  ZX_ADD_PYTHON_FUNCTION(thing_is_blood_splatter)
  ZX_ADD_PYTHON_FUNCTION(thing_is_bloodied)
  ZX_ADD_PYTHON_FUNCTION(thing_is_bones)
  ZX_ADD_PYTHON_FUNCTION(thing_is_brazier)
  ZX_ADD_PYTHON_FUNCTION(thing_is_bridge)
  ZX_ADD_PYTHON_FUNCTION(thing_is_burnable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_carrier_of_treasure_class_a)
  ZX_ADD_PYTHON_FUNCTION(thing_is_carrier_of_treasure_class_b)
  ZX_ADD_PYTHON_FUNCTION(thing_is_carrier_of_treasure_class_c)
  ZX_ADD_PYTHON_FUNCTION(thing_is_carrying_item)
  ZX_ADD_PYTHON_FUNCTION(thing_is_carrying_treasure)
  ZX_ADD_PYTHON_FUNCTION(thing_is_chasm)
  ZX_ADD_PYTHON_FUNCTION(thing_is_collect_as_keys)
  ZX_ADD_PYTHON_FUNCTION(thing_is_collectable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_collected_as_gold)
  ZX_ADD_PYTHON_FUNCTION(thing_is_combustible)
  ZX_ADD_PYTHON_FUNCTION(thing_is_corpse)
  ZX_ADD_PYTHON_FUNCTION(thing_is_corpse_on_death)
  ZX_ADD_PYTHON_FUNCTION(thing_is_corridor)
  ZX_ADD_PYTHON_FUNCTION(thing_is_critical_to_level)
  ZX_ADD_PYTHON_FUNCTION(thing_is_cursor)
  ZX_ADD_PYTHON_FUNCTION(thing_is_cursor_can_hover_over)
  ZX_ADD_PYTHON_FUNCTION(thing_is_cursor_can_hover_over_2x_click)
  ZX_ADD_PYTHON_FUNCTION(thing_is_cursor_path)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dead_on_end_of_anim)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dead_or_dying)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dead_or_dying_on_shove)
  ZX_ADD_PYTHON_FUNCTION(thing_is_debug_path)
  ZX_ADD_PYTHON_FUNCTION(thing_is_debug_type)
  ZX_ADD_PYTHON_FUNCTION(thing_is_deep_water)
  ZX_ADD_PYTHON_FUNCTION(thing_is_descend_dungeon)
  ZX_ADD_PYTHON_FUNCTION(thing_is_descend_sewer)
  ZX_ADD_PYTHON_FUNCTION(thing_is_described_when_hovering_over)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_bl)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_br)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_down)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_left)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_none)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_right)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_tl)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_tr)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dir_up)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dirt)
  ZX_ADD_PYTHON_FUNCTION(thing_is_door)
  ZX_ADD_PYTHON_FUNCTION(thing_is_droppable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_dry_grass)
  ZX_ADD_PYTHON_FUNCTION(thing_is_enchantable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_enchantstone)
  ZX_ADD_PYTHON_FUNCTION(thing_is_engulf_chance_d1000)
  ZX_ADD_PYTHON_FUNCTION(thing_is_engulfer)
  ZX_ADD_PYTHON_FUNCTION(thing_is_ethereal)
  ZX_ADD_PYTHON_FUNCTION(thing_is_ethereal_minion_generator)
  ZX_ADD_PYTHON_FUNCTION(thing_is_explosion)
  ZX_ADD_PYTHON_FUNCTION(thing_is_extreme_hazard)
  ZX_ADD_PYTHON_FUNCTION(thing_is_fearless)
  ZX_ADD_PYTHON_FUNCTION(thing_is_fire)
  ZX_ADD_PYTHON_FUNCTION(thing_is_floating)
  ZX_ADD_PYTHON_FUNCTION(thing_is_floor)
  ZX_ADD_PYTHON_FUNCTION(thing_is_floor_deco)
  ZX_ADD_PYTHON_FUNCTION(thing_is_foilage)
  ZX_ADD_PYTHON_FUNCTION(thing_is_food)
  ZX_ADD_PYTHON_FUNCTION(thing_is_food_eater)
  ZX_ADD_PYTHON_FUNCTION(thing_is_glass)
  ZX_ADD_PYTHON_FUNCTION(thing_is_gold)
  ZX_ADD_PYTHON_FUNCTION(thing_is_hazard)
  ZX_ADD_PYTHON_FUNCTION(thing_is_health_booster)
  ZX_ADD_PYTHON_FUNCTION(thing_is_hittable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_humanoid)
  ZX_ADD_PYTHON_FUNCTION(thing_is_hunger_insatiable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_indestructible)
  ZX_ADD_PYTHON_FUNCTION(thing_is_intelligent)
  ZX_ADD_PYTHON_FUNCTION(thing_is_interesting)
  ZX_ADD_PYTHON_FUNCTION(thing_is_item)
  ZX_ADD_PYTHON_FUNCTION(thing_is_item_carrier)
  ZX_ADD_PYTHON_FUNCTION(thing_is_item_collector)
  ZX_ADD_PYTHON_FUNCTION(thing_is_item_eater)
  ZX_ADD_PYTHON_FUNCTION(thing_is_item_organic)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jelly)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jelly_baby)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jelly_baby_eater)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jelly_eater)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jelly_parent)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jumper)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jumper_chance_d1000)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jumper_distance)
  ZX_ADD_PYTHON_FUNCTION(thing_is_jumper_on_low_hp_chance_d1000)
  ZX_ADD_PYTHON_FUNCTION(thing_is_key)
  ZX_ADD_PYTHON_FUNCTION(thing_is_key_collector)
  ZX_ADD_PYTHON_FUNCTION(thing_is_killed_on_hit_or_miss)
  ZX_ADD_PYTHON_FUNCTION(thing_is_killed_on_hitting)
  ZX_ADD_PYTHON_FUNCTION(thing_is_laser)
  ZX_ADD_PYTHON_FUNCTION(thing_is_lava)
  ZX_ADD_PYTHON_FUNCTION(thing_is_light_blocker)
  ZX_ADD_PYTHON_FUNCTION(thing_is_living)
  ZX_ADD_PYTHON_FUNCTION(thing_is_loggable_for_important_stuff)
  ZX_ADD_PYTHON_FUNCTION(thing_is_loggable_for_unimportant_stuff)
  ZX_ADD_PYTHON_FUNCTION(thing_is_meat)
  ZX_ADD_PYTHON_FUNCTION(thing_is_meat_eater)
  ZX_ADD_PYTHON_FUNCTION(thing_is_metal)
  ZX_ADD_PYTHON_FUNCTION(thing_is_minion)
  ZX_ADD_PYTHON_FUNCTION(thing_is_minion_generator)
  ZX_ADD_PYTHON_FUNCTION(thing_is_monst)
  ZX_ADD_PYTHON_FUNCTION(thing_is_moveable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_msg)
  ZX_ADD_PYTHON_FUNCTION(thing_is_no_tile)
  ZX_ADD_PYTHON_FUNCTION(thing_is_obs_destructable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_obs_wall_or_door)
  ZX_ADD_PYTHON_FUNCTION(thing_is_on_fire)
  ZX_ADD_PYTHON_FUNCTION(thing_is_openable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_organic)
  ZX_ADD_PYTHON_FUNCTION(thing_is_player)
  ZX_ADD_PYTHON_FUNCTION(thing_is_poison)
  ZX_ADD_PYTHON_FUNCTION(thing_is_potion)
  ZX_ADD_PYTHON_FUNCTION(thing_is_potion_eater)
  ZX_ADD_PYTHON_FUNCTION(thing_is_projectile)
  ZX_ADD_PYTHON_FUNCTION(thing_is_removeable_if_out_of_slots)
  ZX_ADD_PYTHON_FUNCTION(thing_is_resurrectable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_ripple)
  ZX_ADD_PYTHON_FUNCTION(thing_is_rock)
  ZX_ADD_PYTHON_FUNCTION(thing_is_rusty)
  ZX_ADD_PYTHON_FUNCTION(thing_is_secret_door)
  ZX_ADD_PYTHON_FUNCTION(thing_is_sewer_wall)
  ZX_ADD_PYTHON_FUNCTION(thing_is_shallow_water)
  ZX_ADD_PYTHON_FUNCTION(thing_is_shovable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_skill)
  ZX_ADD_PYTHON_FUNCTION(thing_is_skillstone)
  ZX_ADD_PYTHON_FUNCTION(thing_is_smoke)
  ZX_ADD_PYTHON_FUNCTION(thing_is_soft_body)
  ZX_ADD_PYTHON_FUNCTION(thing_is_spawner)
  ZX_ADD_PYTHON_FUNCTION(thing_is_spiderweb)
  ZX_ADD_PYTHON_FUNCTION(thing_is_stamina_check)
  ZX_ADD_PYTHON_FUNCTION(thing_is_steal_item_chance_d1000)
  ZX_ADD_PYTHON_FUNCTION(thing_is_sticky)
  ZX_ADD_PYTHON_FUNCTION(thing_is_stone)
  ZX_ADD_PYTHON_FUNCTION(thing_is_sword)
  ZX_ADD_PYTHON_FUNCTION(thing_is_target_auto_select)
  ZX_ADD_PYTHON_FUNCTION(thing_is_throwable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_auto_throw)
  ZX_ADD_PYTHON_FUNCTION(thing_is_tickable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_tmp_thing)
  ZX_ADD_PYTHON_FUNCTION(thing_is_torch)
  ZX_ADD_PYTHON_FUNCTION(thing_is_treasure_class_a)
  ZX_ADD_PYTHON_FUNCTION(thing_is_treasure_class_b)
  ZX_ADD_PYTHON_FUNCTION(thing_is_treasure_class_c)
  ZX_ADD_PYTHON_FUNCTION(thing_is_treasure_type)
  ZX_ADD_PYTHON_FUNCTION(thing_is_treasure_type_chest)
  ZX_ADD_PYTHON_FUNCTION(thing_is_treasure_type_eater)
  ZX_ADD_PYTHON_FUNCTION(thing_is_undead)
  ZX_ADD_PYTHON_FUNCTION(thing_is_usable)
  ZX_ADD_PYTHON_FUNCTION(thing_is_auto_use)
  ZX_ADD_PYTHON_FUNCTION(thing_is_used_when_thrown)
  ZX_ADD_PYTHON_FUNCTION(thing_is_very_combustible)
  ZX_ADD_PYTHON_FUNCTION(thing_is_visible)
  ZX_ADD_PYTHON_FUNCTION(thing_is_wall)
  ZX_ADD_PYTHON_FUNCTION(thing_is_wall_dungeon)
  ZX_ADD_PYTHON_FUNCTION(thing_is_wand)
  ZX_ADD_PYTHON_FUNCTION(thing_is_wand_eater)
  ZX_ADD_PYTHON_FUNCTION(thing_is_water)
  ZX_ADD_PYTHON_FUNCTION(thing_is_water_lover)
  ZX_ADD_PYTHON_FUNCTION(thing_is_weapon)
  ZX_ADD_PYTHON_FUNCTION(thing_is_weapon_wielder)
  ZX_ADD_PYTHON_FUNCTION(thing_is_wooden)
  ZX_ADD_PYTHON_FUNCTION(thing_killed)
  ZX_ADD_PYTHON_FUNCTION(thing_killed_by)
  ZX_ADD_PYTHON_FUNCTION(thing_loves_fire)
  ZX_ADD_PYTHON_FUNCTION(thing_loves_poison)
  ZX_ADD_PYTHON_FUNCTION(thing_loves_spiderwebs)
  ZX_ADD_PYTHON_FUNCTION(thing_msg)
  ZX_ADD_PYTHON_FUNCTION(thing_possible_to_attack)
  ZX_ADD_PYTHON_FUNCTION(thing_set_current_damage)
  ZX_ADD_PYTHON_FUNCTION(thing_set_enchant)
  ZX_ADD_PYTHON_FUNCTION(thing_set_enchant_max)
  ZX_ADD_PYTHON_FUNCTION(thing_set_health)
  ZX_ADD_PYTHON_FUNCTION(thing_set_health_max)
  ZX_ADD_PYTHON_FUNCTION(thing_set_stamina)
  ZX_ADD_PYTHON_FUNCTION(thing_set_stamina_max)
  ZX_ADD_PYTHON_FUNCTION(thing_skill_activate)
  ZX_ADD_PYTHON_FUNCTION(thing_skill_deactivate)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag1)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag10)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag11)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag12)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag13)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag14)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag15)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag16)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag17)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag18)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag19)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag2)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag20)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag21)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag22)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag23)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag24)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag25)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag26)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag27)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag28)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag29)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag3)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag30)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag31)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag32)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag33)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag34)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag35)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag36)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag37)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag38)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag39)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag4)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag40)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag41)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag42)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag43)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag44)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag45)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag46)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag47)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag48)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag5)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag50)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag51)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag52)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag6)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag7)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag8)
  ZX_ADD_PYTHON_FUNCTION(thing_unused_flag9)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(abs_to_pct)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(con)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(die)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(err)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(if_matches)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(if_matches_then_kill)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(level_add)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(level_spawn_next_to)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(level_spawn_next_to_or_on_monst)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(level_spawn_using_items_radius_range)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(log)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(map_load_room)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(music_load)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(music_play)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(pct_to_abs)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(puts)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(sound_load)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(tex_load)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(text_size)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(thing_sound_play)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(thing_sound_play_channel)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(tile_load_arr)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(tile_load_arr_sprites)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(topcon)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(tp_load)
  ZX_ADD_WRAPPED_PYTHON_FUNCTION(tp_update)

  PYFUNC_REF(SDLGetKeyState),

  {0, 0, 0, 0}   /* sentinel */
};

static struct PyModuleDef python_c_MODULE = {
  PyModuleDef_HEAD_INIT,
  "zx",
  0,
  -1,
  python_c_METHODS,
  0, 0, 0, 0
};

PyMODINIT_FUNC
python_mouse_y_module_create (void)
{_
   PyObject *m = PyModule_Create(&python_c_MODULE);
   if (! m) {
    PyErr_Print();
    ERR("Python init");
    return (0);
   }

   return (m);
}

void py_err (void)
{_
  PyObject *err = PyErr_Occurred();
  if (!err) {
    return;
  }

  PyObject *ptype, *pvalue, *ptraceback, *pyobj_str;
  PyObject *ret, *list, *string;
  PyObject *mod;
  char *py_str;

  PyErr_Fetch(&ptype, &pvalue, &ptraceback);
  PyErr_NormalizeException(&ptype, &pvalue, &ptraceback);
  PyErr_Display(ptype, pvalue, ptraceback);
  PyTraceBack_Print(ptraceback, pvalue);

  pyobj_str = PyObject_Str(pvalue);
  py_str = py_obj_to_str(pyobj_str);
  ERR("%s", py_str);
  myfree(py_str);

  mod = PyImport_ImportModule("traceback");
  list = PyObject_CallMethod(mod, "format_exception", "OOO", ptype, pvalue, ptraceback);
  if (list) {
    string = PyUnicode_FromString("\n");
    ret = PyUnicode_Join(string, list);
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
      int line = frame->f_lineno;
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

void py_trace (void)
{_
  PyThreadState *tstate = PyThreadState_GET();

  if (tstate && tstate->frame) {
    PyFrameObject *frame = tstate->frame;

    CON("Python stack trace:");

    int cnt = 1;

    while (frame) {
      int line = frame->f_lineno;
      char *filename = py_obj_to_str(frame->f_code->co_filename);
      char *funcname = py_obj_to_str(frame->f_code->co_name);
      CON(">>> %d. %s, line %d, %s()", cnt++, filename, line, funcname);
      frame = frame->f_back;
      myfree(filename);
      myfree(funcname);
    }
  }
}

void py_exec (const char *str)
{_
  char stdOutErr[] =
"import sys\n\
import zx\n\
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

static void py_add_to_path (const char *path)
{_
  PyObject *py_cur_path, *py_item;
  char *new_path;
  int wc_len, i;
  wchar_t *wc_new_path;
  char *item;

  DBG3("Current system python path: (adding %s)", path);

  new_path = dupstr(path, __FUNCTION__);
  py_cur_path = PySys_GetObject("path");

  for (i = 0; i < PyList_Size(py_cur_path); i++) {
    char *tmp = strappend(new_path, PATHSEP);
    myfree(new_path);
    new_path = tmp;

    py_item = PyList_GetItem(py_cur_path, i);

    if (!PyUnicode_Check(py_item)) {
      continue;
    }

    item = py_obj_to_str(py_item);
    if (!item) {
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
  if (!wc_new_path) {
    ERR("Path alloc fail");
  }

  DBG3("Set python path: %s", new_path);

  mbstowcs(wc_new_path, new_path, wc_len);
  PySys_SetPath(wc_new_path);
  myfree(new_path);
  myfree(wc_new_path);
}

PyObject *abs_to_pct_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  double x = 0;
  double y = 0;

  static char *kwlist[] = {
    (char*) "x",
    (char*) "y",
    0};

  if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &x, &y)) {
    return (0);
  }

  x /= (double) TERM_WIDTH;
  y /= (double) TERM_HEIGHT;

  return (Py_BuildValue("dd", x, y));
}

PyObject *pcg_randint (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  int x = 0;
  int y = 0;

  static char *kwlist[] = {
    (char*) "x",
    (char*) "y",
    0};

  if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &x, &y)) {
    return (0);
  }

  //
  // Python style. We don't use pythons so we can get consistent random
  // numbers with the one C uses.
  //
  return (Py_BuildValue("i", pcg_random_range_inclusive(x, y)));
}

PyObject *non_pcg_randint (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  int x = 0;
  int y = 0;

  static char *kwlist[] = {
    (char*) "x",
    (char*) "y",
    0};

  if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &x, &y)) {
    return (0);
  }

  //
  // Python style. We don't use pythons so we can get consistent random
  // numbers with the one C uses.
  //
  return (Py_BuildValue("i", non_pcg_random_range_inclusive(x, y)));
}

PyObject *pct_to_abs_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  double x = 0;
  double y = 0;

  static char *kwlist[] = {
    (char*) "x",
    (char*) "y",
    0};

  if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &x, &y)) {
    return (0);
  }

  x *= (double) TERM_WIDTH;
  y *= (double) TERM_HEIGHT;

  return (Py_BuildValue("dd", x, y));
}

static void python_add_consts (void)
{_
  PyModule_AddIntConstant(zx_mod, "TERM_HEIGHT", TERM_HEIGHT);
  PyModule_AddIntConstant(zx_mod, "TERM_WIDTH", TERM_WIDTH);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_CHASM", MAP_DEPTH_CHASM);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_FLOOR", MAP_DEPTH_FLOOR);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_FLOOR2", MAP_DEPTH_FLOOR2);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_THE_GRID", MAP_DEPTH_THE_GRID);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_LAVA", MAP_DEPTH_LAVA);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_OBJ", MAP_DEPTH_OBJ);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_WATER", MAP_DEPTH_WATER);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_WEAPON", MAP_DEPTH_WEAPON);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_EXPLOSION_MAJOR", MAP_DEPTH_EXPLOSION_MAJOR);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_EXPLOSION_MINOR", MAP_DEPTH_EXPLOSION_MINOR);
  PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_MESSAGE", MAP_DEPTH_MESSAGE);
  PyModule_AddIntConstant(zx_mod, "CHANNEL_FOOTSTEPS", CHANNEL_FOOTSTEPS);
  PyModule_AddIntConstant(zx_mod, "CHANNEL_MISC", CHANNEL_MISC);
  PyModule_AddIntConstant(zx_mod, "CHANNEL_IMPACT", CHANNEL_IMPACT);
  PyModule_AddIntConstant(zx_mod, "CHANNEL_WEAPON", CHANNEL_WEAPON);
  PyModule_AddIntConstant(zx_mod, "CHANNEL_EXPLOSION", CHANNEL_EXPLOSION);
  PyModule_AddIntConstant(zx_mod, "CHANNEL_MONST", CHANNEL_MONST);
  PyModule_AddIntConstant(zx_mod, "CHANNEL_MONST_DEATH", CHANNEL_MONST_DEATH);
  PyModule_AddIntConstant(zx_mod, "CHANNEL_MONST_BIRTH", CHANNEL_MONST_BIRTH);
  PyModule_AddIntConstant(zx_mod, "MAP_HEIGHT", MAP_HEIGHT);
  PyModule_AddIntConstant(zx_mod, "MAP_PRIO_ALWAYS_BEHIND", MAP_PRIO_ALWAYS_BEHIND);
  PyModule_AddIntConstant(zx_mod, "MAP_PRIO_BEHIND", MAP_PRIO_BEHIND);
  PyModule_AddIntConstant(zx_mod, "MAP_PRIO_INFRONT", MAP_PRIO_INFRONT);
  PyModule_AddIntConstant(zx_mod, "MAP_PRIO_NORMAL", MAP_PRIO_NORMAL);
  PyModule_AddIntConstant(zx_mod, "RARITY_COMMON", THING_RARITY_COMMON);
  PyModule_AddIntConstant(zx_mod, "RARITY_UNCOMMON", THING_RARITY_UNCOMMON);
  PyModule_AddIntConstant(zx_mod, "RARITY_RARE", THING_RARITY_RARE);
  PyModule_AddIntConstant(zx_mod, "RARITY_VERY_RARE", THING_RARITY_VERY_RARE);
  PyModule_AddIntConstant(zx_mod, "RARITY_UNIQUE", THING_RARITY_UNIQUE);
  PyModule_AddIntConstant(zx_mod, "MAP_WIDTH", MAP_WIDTH);
  PyModule_AddIntConstant(zx_mod, "MONST_SIZE_TINY", MONST_SIZE_TINY);
  PyModule_AddIntConstant(zx_mod, "MONST_SIZE_SMALL", MONST_SIZE_SMALL);
  PyModule_AddIntConstant(zx_mod, "MONST_SIZE_NORMAL", MONST_SIZE_NORMAL);
  PyModule_AddIntConstant(zx_mod, "MONST_SIZE_LARGE", MONST_SIZE_LARGE);
  PyModule_AddIntConstant(zx_mod, "MONST_SIZE_GIANT", MONST_SIZE_GIANT);
  PyModule_AddIntConstant(zx_mod, "MONST_SIZE_GARGANTUAN", MONST_SIZE_GARGANTUAN);
  PyModule_AddStringConstant(zx_mod, "MYVER", MYVER);

  PyModule_AddIntConstant(zx_mod, "KMOD_LSHIFT", KMOD_LSHIFT);
  PyModule_AddIntConstant(zx_mod, "KMOD_RSHIFT", KMOD_RSHIFT);
  PyModule_AddIntConstant(zx_mod, "KMOD_LALT", KMOD_LALT);
  PyModule_AddIntConstant(zx_mod, "KMOD_RALT", KMOD_RALT);
  PyModule_AddIntConstant(zx_mod, "KMOD_LCTRL", KMOD_LCTRL);
  PyModule_AddIntConstant(zx_mod, "KMOD_RCTRL", KMOD_RCTRL);

  PyModule_AddIntConstant(zx_mod, "SDLK_0", SDLK_0);
  PyModule_AddIntConstant(zx_mod, "SDLK_1", SDLK_1);
  PyModule_AddIntConstant(zx_mod, "SDLK_2", SDLK_2);
  PyModule_AddIntConstant(zx_mod, "SDLK_3", SDLK_3);
  PyModule_AddIntConstant(zx_mod, "SDLK_4", SDLK_4);
  PyModule_AddIntConstant(zx_mod, "SDLK_5", SDLK_5);
  PyModule_AddIntConstant(zx_mod, "SDLK_6", SDLK_6);
  PyModule_AddIntConstant(zx_mod, "SDLK_7", SDLK_7);
  PyModule_AddIntConstant(zx_mod, "SDLK_8", SDLK_8);
  PyModule_AddIntConstant(zx_mod, "SDLK_9", SDLK_9);
  PyModule_AddIntConstant(zx_mod, "SDLK_AMPERSAND", SDLK_AMPERSAND);
  PyModule_AddIntConstant(zx_mod, "SDLK_ASTERISK", SDLK_ASTERISK);
  PyModule_AddIntConstant(zx_mod, "SDLK_AT", SDLK_AT);
  PyModule_AddIntConstant(zx_mod, "SDLK_BACKQUOTE", SDLK_BACKQUOTE);
  PyModule_AddIntConstant(zx_mod, "SDLK_BACKSLASH", SDLK_BACKSLASH);
  PyModule_AddIntConstant(zx_mod, "SDLK_BACKSPACE", SDLK_BACKSPACE);
  PyModule_AddIntConstant(zx_mod, "SDLK_CARET", SDLK_CARET);
  PyModule_AddIntConstant(zx_mod, "SDLK_COLON", SDLK_COLON);
  PyModule_AddIntConstant(zx_mod, "SDLK_COMMA", SDLK_COMMA);
  PyModule_AddIntConstant(zx_mod, "SDLK_DELETE", SDLK_DELETE);
  PyModule_AddIntConstant(zx_mod, "SDLK_DOLLAR", SDLK_DOLLAR);
  PyModule_AddIntConstant(zx_mod, "SDLK_EQUALS", SDLK_EQUALS);
  PyModule_AddIntConstant(zx_mod, "SDLK_ESCAPE", SDLK_ESCAPE);
  PyModule_AddIntConstant(zx_mod, "SDLK_EXCLAIM", SDLK_EXCLAIM);
  PyModule_AddIntConstant(zx_mod, "SDLK_GREATER", SDLK_GREATER);
  PyModule_AddIntConstant(zx_mod, "SDLK_HASH", SDLK_HASH);
  PyModule_AddIntConstant(zx_mod, "SDLK_LEFTBRACKET", SDLK_LEFTBRACKET);
  PyModule_AddIntConstant(zx_mod, "SDLK_LEFTPAREN", SDLK_LEFTPAREN);
  PyModule_AddIntConstant(zx_mod, "SDLK_LESS", SDLK_LESS);
  PyModule_AddIntConstant(zx_mod, "SDLK_MINUS", SDLK_MINUS);
  PyModule_AddIntConstant(zx_mod, "SDLK_PERIOD", SDLK_PERIOD);
  PyModule_AddIntConstant(zx_mod, "SDLK_PLUS", SDLK_PLUS);
  PyModule_AddIntConstant(zx_mod, "SDLK_QUESTION", SDLK_QUESTION);
  PyModule_AddIntConstant(zx_mod, "SDLK_QUOTE", SDLK_QUOTE);
  PyModule_AddIntConstant(zx_mod, "SDLK_QUOTEDBL", SDLK_QUOTEDBL);
  PyModule_AddIntConstant(zx_mod, "SDLK_RETURN", SDLK_RETURN);
  PyModule_AddIntConstant(zx_mod, "SDLK_RIGHTBRACKET", SDLK_RIGHTBRACKET);
  PyModule_AddIntConstant(zx_mod, "SDLK_RIGHTPAREN", SDLK_RIGHTPAREN);
  PyModule_AddIntConstant(zx_mod, "SDLK_SEMICOLON", SDLK_SEMICOLON);
  PyModule_AddIntConstant(zx_mod, "SDLK_SLASH", SDLK_SLASH);
  PyModule_AddIntConstant(zx_mod, "SDLK_SPACE", SDLK_SPACE);
  PyModule_AddIntConstant(zx_mod, "SDLK_TAB", SDLK_TAB);
  PyModule_AddIntConstant(zx_mod, "SDLK_UNDERSCORE", SDLK_UNDERSCORE);
  PyModule_AddIntConstant(zx_mod, "SDLK_a", SDLK_a);
  PyModule_AddIntConstant(zx_mod, "SDLK_b", SDLK_b);
  PyModule_AddIntConstant(zx_mod, "SDLK_c", SDLK_c);
  PyModule_AddIntConstant(zx_mod, "SDLK_d", SDLK_d);
  PyModule_AddIntConstant(zx_mod, "SDLK_e", SDLK_e);
  PyModule_AddIntConstant(zx_mod, "SDLK_f", SDLK_f);
  PyModule_AddIntConstant(zx_mod, "SDLK_g", SDLK_g);
  PyModule_AddIntConstant(zx_mod, "SDLK_h", SDLK_h);
  PyModule_AddIntConstant(zx_mod, "SDLK_i", SDLK_i);
  PyModule_AddIntConstant(zx_mod, "SDLK_j", SDLK_j);
  PyModule_AddIntConstant(zx_mod, "SDLK_k", SDLK_k);
  PyModule_AddIntConstant(zx_mod, "SDLK_l", SDLK_l);
  PyModule_AddIntConstant(zx_mod, "SDLK_m", SDLK_m);
  PyModule_AddIntConstant(zx_mod, "SDLK_n", SDLK_n);
  PyModule_AddIntConstant(zx_mod, "SDLK_o", SDLK_o);
  PyModule_AddIntConstant(zx_mod, "SDLK_p", SDLK_p);
  PyModule_AddIntConstant(zx_mod, "SDLK_q", SDLK_q);
  PyModule_AddIntConstant(zx_mod, "SDLK_r", SDLK_r);
  PyModule_AddIntConstant(zx_mod, "SDLK_s", SDLK_s);
  PyModule_AddIntConstant(zx_mod, "SDLK_t", SDLK_t);
  PyModule_AddIntConstant(zx_mod, "SDLK_u", SDLK_u);
  PyModule_AddIntConstant(zx_mod, "SDLK_v", SDLK_v);
  PyModule_AddIntConstant(zx_mod, "SDLK_w", SDLK_w);
  PyModule_AddIntConstant(zx_mod, "SDLK_x", SDLK_x);
  PyModule_AddIntConstant(zx_mod, "SDLK_y", SDLK_y);
  PyModule_AddIntConstant(zx_mod, "SDLK_z", SDLK_z);

#if SDL_MAJOR_VERSION == 1 /* { */
  PyModule_AddIntConstant(zx_mod, "SDLK_KP0", SDLK_KP0);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP1", SDLK_KP1);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP2", SDLK_KP2);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP3", SDLK_KP3);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP4", SDLK_KP4);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP5", SDLK_KP5);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP6", SDLK_KP6);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP7", SDLK_KP7);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP8", SDLK_KP8);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP9", SDLK_KP9);
#else
  PyModule_AddIntConstant(zx_mod, "SDLK_KP0", SDLK_KP_0);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP1", SDLK_KP_1);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP2", SDLK_KP_2);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP3", SDLK_KP_3);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP4", SDLK_KP_4);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP5", SDLK_KP_5);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP6", SDLK_KP_6);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP7", SDLK_KP_7);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP8", SDLK_KP_8);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP9", SDLK_KP_9);
#endif

  PyModule_AddIntConstant(zx_mod, "SDLK_KP_PERIOD", SDLK_KP_PERIOD);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP_DIVIDE", SDLK_KP_DIVIDE);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP_MULTIPLY", SDLK_KP_MULTIPLY);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP_MINUS", SDLK_KP_MINUS);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP_PLUS", SDLK_KP_PLUS);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP_ENTER", SDLK_KP_ENTER);
  PyModule_AddIntConstant(zx_mod, "SDLK_KP_EQUALS", SDLK_KP_EQUALS);
  PyModule_AddIntConstant(zx_mod, "SDLK_UP", SDLK_UP);
  PyModule_AddIntConstant(zx_mod, "SDLK_DOWN", SDLK_DOWN);
  PyModule_AddIntConstant(zx_mod, "SDLK_RIGHT", SDLK_RIGHT);
  PyModule_AddIntConstant(zx_mod, "SDLK_LEFT", SDLK_LEFT);
  PyModule_AddIntConstant(zx_mod, "SDLK_INSERT", SDLK_INSERT);
  PyModule_AddIntConstant(zx_mod, "SDLK_HOME", SDLK_HOME);
  PyModule_AddIntConstant(zx_mod, "SDLK_END", SDLK_END);
  PyModule_AddIntConstant(zx_mod, "SDLK_PAGEUP", SDLK_PAGEUP);
  PyModule_AddIntConstant(zx_mod, "SDLK_PAGEDOWN", SDLK_PAGEDOWN);
  PyModule_AddIntConstant(zx_mod, "SDLK_F1", SDLK_F1);
  PyModule_AddIntConstant(zx_mod, "SDLK_F2", SDLK_F2);
  PyModule_AddIntConstant(zx_mod, "SDLK_F3", SDLK_F3);
  PyModule_AddIntConstant(zx_mod, "SDLK_F4", SDLK_F4);
  PyModule_AddIntConstant(zx_mod, "SDLK_F5", SDLK_F5);
  PyModule_AddIntConstant(zx_mod, "SDLK_F6", SDLK_F6);
  PyModule_AddIntConstant(zx_mod, "SDLK_F7", SDLK_F7);
  PyModule_AddIntConstant(zx_mod, "SDLK_F8", SDLK_F8);
  PyModule_AddIntConstant(zx_mod, "SDLK_F9", SDLK_F9);
  PyModule_AddIntConstant(zx_mod, "SDLK_F10", SDLK_F10);
  PyModule_AddIntConstant(zx_mod, "SDLK_F11", SDLK_F11);
  PyModule_AddIntConstant(zx_mod, "SDLK_F12", SDLK_F12);
  PyModule_AddIntConstant(zx_mod, "SDLK_F13", SDLK_F13);
  PyModule_AddIntConstant(zx_mod, "SDLK_F14", SDLK_F14);
  PyModule_AddIntConstant(zx_mod, "SDLK_F15", SDLK_F15);
  PyModule_AddIntConstant(zx_mod, "SDLK_CAPSLOCK", SDLK_CAPSLOCK);
  PyModule_AddIntConstant(zx_mod, "SDLK_RSHIFT", SDLK_RSHIFT);
  PyModule_AddIntConstant(zx_mod, "SDLK_LSHIFT", SDLK_LSHIFT);
  PyModule_AddIntConstant(zx_mod, "SDLK_RCTRL", SDLK_RCTRL);
  PyModule_AddIntConstant(zx_mod, "SDLK_LCTRL", SDLK_LCTRL);
#if SDL_MAJOR_VERSION > 1
  PyModule_AddIntConstant(zx_mod, "SDLK_RGUI", SDLK_RGUI);
  PyModule_AddIntConstant(zx_mod, "SDLK_LGUI", SDLK_LGUI);
#else
  PyModule_AddIntConstant(zx_mod, "SDLK_RGUI", -1);
  PyModule_AddIntConstant(zx_mod, "SDLK_LGUI", -1);
#endif
  PyModule_AddIntConstant(zx_mod, "SDLK_RALT", SDLK_RALT);
  PyModule_AddIntConstant(zx_mod, "SDLK_LALT", SDLK_LALT);
  PyModule_AddIntConstant(zx_mod, "SDLK_MODE", SDLK_MODE);
  PyModule_AddIntConstant(zx_mod, "SDLK_HELP", SDLK_HELP);
  PyModule_AddIntConstant(zx_mod, "SDLK_SYSREQ", SDLK_SYSREQ);
  PyModule_AddIntConstant(zx_mod, "SDLK_MENU", SDLK_MENU);
  PyModule_AddIntConstant(zx_mod, "SDLK_POWER", SDLK_POWER);
  PyModule_AddIntConstant(zx_mod, "SDLK_UNDO", SDLK_UNDO);


#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_0", SDLK_0);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_0", SDL_SCANCODE_0);
#endif

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_1", SDLK_1);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_1", SDL_SCANCODE_1);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_2", SDLK_2);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_2", SDL_SCANCODE_2);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_3", SDLK_3);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_3", SDL_SCANCODE_3);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_4", SDLK_4);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_4", SDL_SCANCODE_4);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_5", SDLK_5);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_5", SDL_SCANCODE_5);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_6", SDLK_6);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_6", SDL_SCANCODE_6);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_7", SDLK_7);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_7", SDL_SCANCODE_7);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_8", SDLK_8);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_8", SDL_SCANCODE_8);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_9", SDLK_9);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_9", SDL_SCANCODE_9);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_AMPERSAND", SDLK_AMPERSAND);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_AMPERSAND", SDL_SCANCODE_KP_AMPERSAND);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_AT", SDLK_AT);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_AT", SDL_SCANCODE_KP_AT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_BACKSLASH", SDLK_BACKSLASH);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_BACKSLASH", SDL_SCANCODE_BACKSLASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_BACKSPACE", SDLK_BACKSPACE);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_BACKSPACE", SDL_SCANCODE_BACKSPACE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_COMMA", SDLK_COMMA);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_COMMA", SDL_SCANCODE_COMMA);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_DELETE", SDLK_DELETE);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_DELETE", SDL_SCANCODE_DELETE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_EQUALS", SDLK_EQUALS);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_EQUALS", SDL_SCANCODE_EQUALS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_ESCAPE", SDLK_ESCAPE);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_ESCAPE", SDL_SCANCODE_ESCAPE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_GREATER", SDLK_GREATER);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_GREATER", SDL_SCANCODE_KP_GREATER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_HASH", SDLK_HASH);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_HASH", SDL_SCANCODE_KP_HASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LEFTBRACKET", SDLK_LEFTBRACKET);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LEFTBRACKET", SDL_SCANCODE_LEFTBRACKET);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LEFTPAREN", SDLK_LEFTPAREN);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LEFTPAREN", SDL_SCANCODE_KP_LEFTPAREN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LESS", SDLK_LESS);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LESS", SDL_SCANCODE_KP_LESS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_MINUS", SDLK_MINUS);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_MINUS", SDL_SCANCODE_MINUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_PERIOD", SDLK_PERIOD);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_PERIOD", SDL_SCANCODE_PERIOD);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_PLUS", SDLK_PLUS);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_PLUS", SDL_SCANCODE_KP_PLUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RETURN", SDLK_RETURN);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RETURN", SDL_SCANCODE_RETURN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RIGHTBRACKET", SDLK_RIGHTBRACKET);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RIGHTBRACKET", SDL_SCANCODE_RIGHTBRACKET);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RIGHTPAREN", SDLK_RIGHTPAREN);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RIGHTPAREN", SDL_SCANCODE_KP_RIGHTPAREN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_SEMICOLON", SDLK_SEMICOLON);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_SEMICOLON", SDL_SCANCODE_SEMICOLON);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_SLASH", SDLK_SLASH);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_SLASH", SDL_SCANCODE_SLASH);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_SPACE", SDLK_SPACE);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_SPACE", SDL_SCANCODE_SPACE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_TAB", SDLK_TAB);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_TAB", SDL_SCANCODE_TAB);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_A", SDLK_a);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_A", SDL_SCANCODE_A);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_B", SDLK_b);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_B", SDL_SCANCODE_B);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_C", SDLK_c);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_C", SDL_SCANCODE_C);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_D", SDLK_d);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_D", SDL_SCANCODE_D);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_E", SDLK_e);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_E", SDL_SCANCODE_E);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F", SDLK_f);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F", SDL_SCANCODE_F);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_G", SDLK_g);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_G", SDL_SCANCODE_G);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_H", SDLK_h);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_H", SDL_SCANCODE_H);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_I", SDLK_i);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_I", SDL_SCANCODE_I);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_J", SDLK_j);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_J", SDL_SCANCODE_J);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_K", SDLK_k);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_K", SDL_SCANCODE_K);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_L", SDLK_l);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_L", SDL_SCANCODE_L);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_M", SDLK_m);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_M", SDL_SCANCODE_M);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_N", SDLK_n);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_N", SDL_SCANCODE_N);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_O", SDLK_o);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_O", SDL_SCANCODE_O);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_P", SDLK_p);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_P", SDL_SCANCODE_P);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_Q", SDLK_q);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_Q", SDL_SCANCODE_Q);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_R", SDLK_r);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_R", SDL_SCANCODE_R);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_S", SDLK_s);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_S", SDL_SCANCODE_S);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_T", SDLK_t);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_T", SDL_SCANCODE_T);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_U", SDLK_u);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_U", SDL_SCANCODE_U);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_V", SDLK_v);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_V", SDL_SCANCODE_V);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_W", SDLK_w);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_W", SDL_SCANCODE_W);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_X", SDLK_x);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_X", SDL_SCANCODE_X);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_Y", SDLK_y);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_Y", SDL_SCANCODE_Y);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_Z", SDLK_z);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_Z", SDL_SCANCODE_Z);
#endif /* } */


#if SDL_MAJOR_VERSION == 1 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP0", SDLk_KP0);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP1", SDLK_KP1);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP2", SDLk_KP2);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP3", SDLK_KP3);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP4", SDLK_KP4);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP5", SDLK_KP5);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP6", SDLK_KP6);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP7", SDLK_KP7);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP8", SDLK_KP8);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP9", SDLK_KP9);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP0", SDLK_KP_0);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP1", SDLK_KP_1);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP2", SDLK_KP_2);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP3", SDLK_KP_3);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP4", SDLK_KP_4);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP5", SDLK_KP_5);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP6", SDLK_KP_6);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP7", SDLK_KP_7);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP8", SDLK_KP_8);
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP9", SDLK_KP_9);
#endif

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_PERIOD", SDLK_KP_PERIOD);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_PERIOD", SDL_SCANCODE_KP_PERIOD);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_DIVIDE", SDLK_KP_DIVIDE);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_DIVIDE", SDL_SCANCODE_KP_DIVIDE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_MULTIPLY", SDLK_KP_MULTIPLY);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_MULTIPLY", SDL_SCANCODE_KP_MULTIPLY);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_MINUS", SDLK_KP_MINUS);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_MINUS", SDL_SCANCODE_KP_MINUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_PLUS", SDLK_KP_PLUS);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_PLUS", SDL_SCANCODE_KP_PLUS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_ENTER", SDLK_KP_ENTER);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_ENTER", SDL_SCANCODE_KP_ENTER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_EQUALS", SDLK_KP_EQUALS);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_KP_EQUALS", SDL_SCANCODE_KP_EQUALS);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_UP", SDLK_UP);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_UP", SDL_SCANCODE_UP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_DOWN", SDLK_DOWN);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_DOWN", SDL_SCANCODE_DOWN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RIGHT", SDLK_RIGHT);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RIGHT", SDL_SCANCODE_RIGHT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LEFT", SDLK_LEFT);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LEFT", SDL_SCANCODE_LEFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_INSERT", SDLK_INSERT);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_INSERT", SDL_SCANCODE_INSERT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_HOME", SDLK_HOME);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_HOME", SDL_SCANCODE_HOME);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_END", SDLK_END);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_END", SDL_SCANCODE_END);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_PAGEUP", SDLK_PAGEUP);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_PAGEUP", SDL_SCANCODE_PAGEUP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_PAGEDOWN", SDLK_PAGEDOWN);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_PAGEDOWN", SDL_SCANCODE_PAGEDOWN);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F1", SDLK_F1);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F1", SDL_SCANCODE_F1);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F2", SDLK_F2);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F2", SDL_SCANCODE_F2);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F3", SDLK_F3);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F3", SDL_SCANCODE_F3);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F4", SDLK_F4);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F4", SDL_SCANCODE_F4);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F5", SDLK_F5);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F5", SDL_SCANCODE_F5);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F6", SDLK_F6);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F6", SDL_SCANCODE_F6);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F7", SDLK_F7);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F7", SDL_SCANCODE_F7);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F8", SDLK_F8);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F8", SDL_SCANCODE_F8);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F9", SDLK_F9);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F9", SDL_SCANCODE_F9);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F10", SDLK_F10);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F10", SDL_SCANCODE_F10);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F11", SDLK_F11);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F11", SDL_SCANCODE_F11);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F12", SDLK_F12);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F12", SDL_SCANCODE_F12);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F13", SDLK_F13);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F13", SDL_SCANCODE_F13);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F14", SDLK_F14);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F14", SDL_SCANCODE_F14);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F15", SDLK_F15);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_F15", SDL_SCANCODE_F15);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_CAPSLOCK", SDLK_CAPSLOCK);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_CAPSLOCK", SDL_SCANCODE_CAPSLOCK);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RSHIFT", SDLK_RSHIFT);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RSHIFT", SDL_SCANCODE_RSHIFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LSHIFT", SDLK_LSHIFT);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LSHIFT", SDL_SCANCODE_LSHIFT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RCTRL", SDLK_RCTRL);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RCTRL", SDL_SCANCODE_RCTRL);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LCTRL", SDLK_LCTRL);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LCTRL", SDL_SCANCODE_LCTRL);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RALT", SDLK_RALT);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_RALT", SDL_SCANCODE_RALT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LALT", SDLK_LALT);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_LALT", SDL_SCANCODE_LALT);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_MODE", SDLK_MODE);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_MODE", SDL_SCANCODE_MODE);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_HELP", SDLK_HELP);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_HELP", SDL_SCANCODE_HELP);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_SYSREQ", SDLK_SYSREQ);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_SYSREQ", SDL_SCANCODE_SYSREQ);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_MENU", SDLK_MENU);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_MENU", SDL_SCANCODE_MENU);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_POWER", SDLK_POWER);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_POWER", SDL_SCANCODE_POWER);
#endif /* } */

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_UNDO", SDLK_UNDO);
#else
  PyModule_AddIntConstant(zx_mod, "SDL_SCANCODE_UNDO", SDL_SCANCODE_UNDO);
#endif /* } */

}

static std::string get_env(const char* env)
{
  auto t = std::getenv(env);
  if (t) return t;
  return "";
}

void python_init (char *argv[])
{_
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
  PyImport_AppendInittab("zx", python_mouse_y_module_create);
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  CON("INI: Calling Py_Initialize");
  Py_Initialize();
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  py_add_to_path("python");
  py_add_to_path(GFX_PATH);
  py_add_to_path(DATA_PATH);
  py_add_to_path(EXEC_PYTHONPATH);
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  DBG3("INI: Calling PyImport_ImportModule for zx module");

  zx_mod = PyImport_ImportModule("zx");
  if (!zx_mod) {
    py_err();
    ERR("Module zx import failed");
    return;
  }

  python_add_consts();

  DBG3("INI: Calling PyImport_ImportModule for init module");

  zx_mod = PyImport_ImportModule("init");
  if (!zx_mod) {
    py_err();
    ERR("Module init import failed");
    return;
  }

  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////
}

PyObject *py_add_module (const char *mod)
{
  auto name = std::string(mod);
  auto pmod = py_mods[name];
  if (pmod != nullptr) {
    return pmod;
  }

  pmod = PyImport_ImportModule(mod);
  if (pmod == nullptr) {
    py_err();
    ERR("Module init '%s' import failed", mod);
    return (nullptr);
  }
  py_mods[name] = pmod;

  return pmod;
}

void python_fini (void)
{_
  Py_Finalize();
}
