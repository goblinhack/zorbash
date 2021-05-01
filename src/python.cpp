//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <map>
#include "my_py_tp.h"
#include "my_py_thing.h"
#include "my_py_level.h"
#include <frameobject.h>

#include "my_main.h"
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

void py_call_void_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4)
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

void py_call_void_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4, unsigned int val5)
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

void py_call_void_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4, unsigned int val5,
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

void py_call_void_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4, unsigned int val5,
                      unsigned int val6, unsigned int val7)
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

void py_call_void_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4, unsigned int val5,
                      unsigned int val6, unsigned int val7, unsigned int val8)
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

bool py_call_bool_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4)
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

bool py_call_bool_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4, unsigned int val5)
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

bool py_call_bool_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4, unsigned int val5,
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

bool py_call_bool_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4, unsigned int val5,
                      unsigned int val6, unsigned int val7)
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

bool py_call_bool_fn (const char *module, const char *name, unsigned int val1, unsigned int val2, unsigned int val3, unsigned int val4, unsigned int val5,
                      unsigned int val6, unsigned int val7, unsigned int val8)
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
        ERR("con: bad args");
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
        ERR("topcon: bad args");
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
        ERR("puts: bad args");
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
        ERR("log: bad args");
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
        ERR("err: bad args");
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
        ERR("die: bad args");
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
    TP_SET_DECL(ai_avoid_distance)
    TP_SET_DECL(ai_obstacle)
    TP_SET_DECL(ai_scent_distance)
    TP_SET_DECL(attack_eater)
    TP_SET_DECL(attack_humanoid)
    TP_SET_DECL(attack_living)
    TP_SET_DECL(attack_lunge)
    TP_SET_DECL(attack_meat)
    TP_SET_DECL(attack_shove)
    TP_SET_DECL(attack_shove_chance_d1000)
    TP_SET_DECL(hates_acid)
    TP_SET_DECL(hates_fire)
    TP_SET_DECL(hates_poison)
    TP_SET_DECL(hates_water)
    TP_SET_DECL(bag_height)
    TP_SET_DECL(bag_item_height)
    TP_SET_DECL(bag_item_width)
    TP_SET_DECL(bag_width)
    TP_SET_DECL(bl1_tile)
    TP_SET_DECL(bl2_tile)
    TP_SET_DECL(blast_max_radius)
    TP_SET_DECL(blast_min_radius)
    TP_SET_DECL(blit_bot_off)
    TP_SET_DECL(blit_left_off)
    TP_SET_DECL(blit_right_off)
    TP_SET_DECL(blit_top_off)
    TP_SET_DECL(bot1_tile)
    TP_SET_DECL(bot2_tile)
    TP_SET_DECL(bot3_tile)
    TP_SET_DECL(br1_tile)
    TP_SET_DECL(br2_tile)
    TP_SET_DECL(charge_count)
    TP_SET_DECL(collision_attack)
    TP_SET_DECL(collision_attack_radius)
    TP_SET_DECL(collision_box)
    TP_SET_DECL(collision_check)
    TP_SET_DECL(collision_circle)
    TP_SET_DECL(collision_hit_priority)
    TP_SET_DECL(collision_radius)
    TP_SET_DECL(damage_bite_dice)
    TP_SET_DECL(damage_doubled_from_acid)
    TP_SET_DECL(damage_doubled_from_fire)
    TP_SET_DECL(damage_doubled_from_poison)
    TP_SET_DECL(damage_doubled_from_water)
    TP_SET_DECL(damage_melee_dice)
    TP_SET_DECL(gfx_an_animation_only)
    TP_SET_DECL(gfx_anim_attack)
    TP_SET_DECL(gfx_animated)
    TP_SET_DECL(gfx_animated_can_hflip)
    TP_SET_DECL(gfx_animated_can_vflip)
    TP_SET_DECL(gfx_animated_no_dir)
    TP_SET_DECL(gfx_attack_anim)
    TP_SET_DECL(gfx_bounce_always)
    TP_SET_DECL(gfx_bounce_on_move)
    TP_SET_DECL(gfx_dead_anim)
    TP_SET_DECL(gfx_glows)
    TP_SET_DECL(gfx_health_bar_shown)
    TP_SET_DECL(gfx_health_bar_shown_only_when_injured)
    TP_SET_DECL(gfx_on_fire_anim)
    TP_SET_DECL(gfx_oversized_but_sitting_on_the_ground)
    TP_SET_DECL(gfx_show_outlined)
    TP_SET_DECL(gfx_shown_in_bg)
    TP_SET_DECL(gfx_small_shadow_caster)
    TP_SET_DECL(gfx_weapon_carry_anim)
    TP_SET_DECL(gold_value_dice)
    TP_SET_DECL(health_hunger_pct)
    TP_SET_DECL(health_initial_dice)
    TP_SET_DECL(health_starving_pct)
    TP_SET_DECL(hunger_clock_freq_ms)
    TP_SET_DECL(is_able_to_change_levels)
    TP_SET_DECL(is_able_to_fall)
    TP_SET_DECL(is_able_to_see_through_doors)
    TP_SET_DECL(is_able_to_walk_through_walls)
    TP_SET_DECL(is_acid)
    TP_SET_DECL(is_acid_lover)
    TP_SET_DECL(is_active)
    TP_SET_DECL(is_always_hit)
    TP_SET_DECL(is_ascend_dungeon)
    TP_SET_DECL(is_ascend_sewer)
    TP_SET_DECL(is_attackable_by_monst)
    TP_SET_DECL(is_attackable_by_player)
    TP_SET_DECL(is_auto_collect_item)
    TP_SET_DECL(is_bag)
    TP_SET_DECL(is_bleeder)
    TP_SET_DECL(is_blood)
    TP_SET_DECL(is_blood_splatter)
    TP_SET_DECL(is_brazier)
    TP_SET_DECL(is_rrr99)
    TP_SET_DECL(is_carrier_of_treasure_class_a)
    TP_SET_DECL(is_carrier_of_treasure_class_b)
    TP_SET_DECL(is_carrier_of_treasure_class_c)
    TP_SET_DECL(is_chasm)
    TP_SET_DECL(is_collect_as_keys)
    TP_SET_DECL(is_collectable)
    TP_SET_DECL(is_combustible)
    TP_SET_DECL(is_corpse_on_death)
    TP_SET_DECL(is_corridor)
    TP_SET_DECL(is_critical_to_level)
    TP_SET_DECL(is_cursor)
    TP_SET_DECL(is_cursor_can_hover_over)
    TP_SET_DECL(is_cursor_can_hover_over_but_needs_double_click)
    TP_SET_DECL(is_cursor_path)
    TP_SET_DECL(is_dead_on_shove)
    TP_SET_DECL(is_deep_water)
    TP_SET_DECL(is_descend_dungeon)
    TP_SET_DECL(is_descend_sewer)
    TP_SET_DECL(is_described_when_hovering_over)
    TP_SET_DECL(is_dirt)
    TP_SET_DECL(is_door)
    TP_SET_DECL(is_droppable)
    TP_SET_DECL(is_ethereal)
    TP_SET_DECL(is_explosion)
    TP_SET_DECL(is_extreme_hazard)
    TP_SET_DECL(is_fearless)
    TP_SET_DECL(is_fire)
    TP_SET_DECL(is_very_combustible)
    TP_SET_DECL(is_floating)
    TP_SET_DECL(is_floor)
    TP_SET_DECL(is_floor_deco)
    TP_SET_DECL(is_food)
    TP_SET_DECL(is_food_eater)
    TP_SET_DECL(gfx_water)
    TP_SET_DECL(is_gold)
    TP_SET_DECL(is_hazard)
    TP_SET_DECL(is_humanoid)
    TP_SET_DECL(is_hunger_insatiable)
    TP_SET_DECL(is_intelligent)
    TP_SET_DECL(is_interesting)
    TP_SET_DECL(is_item)
    TP_SET_DECL(is_item_carrier)
    TP_SET_DECL(is_item_collected_as_gold)
    TP_SET_DECL(is_item_eater)
    TP_SET_DECL(is_item_not_stackable)
    TP_SET_DECL(is_jelly)
    TP_SET_DECL(is_jelly_baby)
    TP_SET_DECL(is_jelly_baby_eater)
    TP_SET_DECL(is_jelly_eater)
    TP_SET_DECL(is_jelly_parent)
    TP_SET_DECL(is_jumper)
    TP_SET_DECL(is_jumper_chance_d1000)
    TP_SET_DECL(is_jumper_distance)
    TP_SET_DECL(is_jumper_on_low_hp_chance_d1000)
    TP_SET_DECL(is_key)
    TP_SET_DECL(is_killed_on_hit_or_miss)
    TP_SET_DECL(is_killed_on_hitting)
    TP_SET_DECL(is_target_select_automatically_when_chosen)
    TP_SET_DECL(is_lava)
    TP_SET_DECL(is_light_blocker)
    TP_SET_DECL(is_living)
    TP_SET_DECL(is_loggable_for_important_stuff)
    TP_SET_DECL(is_loggable_for_unimportant_stuff)
    TP_SET_DECL(is_meat)
    TP_SET_DECL(is_meat_eater)
    TP_SET_DECL(is_minion)
    TP_SET_DECL(is_minion_generator)
    TP_SET_DECL(is_monst)
    TP_SET_DECL(is_moveable)
    TP_SET_DECL(is_movement_blocking_hard)
    TP_SET_DECL(is_movement_blocking_soft)
    TP_SET_DECL(is_msg)
    TP_SET_DECL(is_no_tile)
    TP_SET_DECL(is_player)
    TP_SET_DECL(is_poison)
    TP_SET_DECL(loves_poison)
    TP_SET_DECL(is_potion)
    TP_SET_DECL(is_potion_eater)
    TP_SET_DECL(is_projectile)
    TP_SET_DECL(is_removeable_if_out_of_slots)
    TP_SET_DECL(is_resurrectable)
    TP_SET_DECL(is_ripple)
    TP_SET_DECL(is_rock)
    TP_SET_DECL(is_rrr1)
    TP_SET_DECL(is_rrr2)
    TP_SET_DECL(is_rrr3)
    TP_SET_DECL(is_rrr4)
    TP_SET_DECL(is_rrr5)
    TP_SET_DECL(is_rrr6)
    TP_SET_DECL(is_rrr7)
    TP_SET_DECL(is_rrr8)
    TP_SET_DECL(is_rrr9)
    TP_SET_DECL(is_rrr10)
    TP_SET_DECL(is_rrr11)
    TP_SET_DECL(is_rrr12)
    TP_SET_DECL(is_rrr13)
    TP_SET_DECL(is_rrr14)
    TP_SET_DECL(is_rrr15)
    TP_SET_DECL(is_rrr16)
    TP_SET_DECL(is_rrr17)
    TP_SET_DECL(is_rrr18)
    TP_SET_DECL(is_rrr19)
    TP_SET_DECL(is_rrr20)
    TP_SET_DECL(is_rrr21)
    TP_SET_DECL(is_rrr22)
    TP_SET_DECL(is_rrr23)
    TP_SET_DECL(is_rrr24)
    TP_SET_DECL(is_rrr25)
    TP_SET_DECL(is_rrr26)
    TP_SET_DECL(is_rrr27)
    TP_SET_DECL(is_rrr28)
    TP_SET_DECL(is_rrr29)
    TP_SET_DECL(is_rrr30)
    TP_SET_DECL(is_rrr31)
    TP_SET_DECL(is_rrr32)
    TP_SET_DECL(is_rrr33)
    TP_SET_DECL(is_rrr34)
    TP_SET_DECL(is_rrr35)
    TP_SET_DECL(is_rrr36)
    TP_SET_DECL(is_rrr37)
    TP_SET_DECL(is_rrr38)
    TP_SET_DECL(is_rrr39)
    TP_SET_DECL(is_rrr40)
    TP_SET_DECL(is_rrr41)
    TP_SET_DECL(is_rrr42)
    TP_SET_DECL(is_rrr43)
    TP_SET_DECL(is_rrr44)
    TP_SET_DECL(is_rrr45)
    TP_SET_DECL(is_rrr46)
    TP_SET_DECL(is_rrr47)
    TP_SET_DECL(is_rrr48)
    TP_SET_DECL(is_rrr49)
    TP_SET_DECL(is_rrr50)
    TP_SET_DECL(is_rrr51)
    TP_SET_DECL(is_rrr52)
    TP_SET_DECL(is_rrr53)
    TP_SET_DECL(is_rrr54)
    TP_SET_DECL(is_rrr55)
    TP_SET_DECL(is_rrr56)
    TP_SET_DECL(is_rrr57)
    TP_SET_DECL(is_rrr58)
    TP_SET_DECL(is_rrr59)
    TP_SET_DECL(is_rrr60)
    TP_SET_DECL(is_rrr61)
    TP_SET_DECL(is_rrr62)
    TP_SET_DECL(is_rrr63)
    TP_SET_DECL(is_rrr64)
    TP_SET_DECL(is_rrr65)
    TP_SET_DECL(is_rrr66)
    TP_SET_DECL(is_rrr67)
    TP_SET_DECL(is_rrr68)
    TP_SET_DECL(is_rrr69)
    TP_SET_DECL(is_rrr70)
    TP_SET_DECL(is_rrr71)
    TP_SET_DECL(is_rrr72)
    TP_SET_DECL(is_rrr73)
    TP_SET_DECL(is_rrr74)
    TP_SET_DECL(is_rrr75)
    TP_SET_DECL(is_rrr76)
    TP_SET_DECL(is_rrr77)
    TP_SET_DECL(is_rrr78)
    TP_SET_DECL(is_rrr79)
    TP_SET_DECL(is_rrr80)
    TP_SET_DECL(is_rrr81)
    TP_SET_DECL(is_rrr82)
    TP_SET_DECL(is_rrr83)
    TP_SET_DECL(is_rrr84)
    TP_SET_DECL(is_rrr85)
    TP_SET_DECL(is_rrr86)
    TP_SET_DECL(is_rrr87)
    TP_SET_DECL(is_rrr88)
    TP_SET_DECL(is_rrr89)
    TP_SET_DECL(is_bridge)
    TP_SET_DECL(is_barrel)
    TP_SET_DECL(is_burnable)
    TP_SET_DECL(is_wand_eater)
    TP_SET_DECL(loves_fire)
    TP_SET_DECL(is_projectile)
    TP_SET_DECL(gfx_flickers)
    TP_SET_DECL(is_laser)
    TP_SET_DECL(is_able_to_fire_at)
    TP_SET_DECL(ai_vision_distance)
    TP_SET_DECL(is_ethereal_minion_generator)
    TP_SET_DECL(is_secret_door)
    TP_SET_DECL(is_sewer_wall)
    TP_SET_DECL(is_shallow_water)
    TP_SET_DECL(is_shovable)
    TP_SET_DECL(is_shown_on_leftbar)
    TP_SET_DECL(is_shown_uniquely_on_leftbar)
    TP_SET_DECL(is_skill)
    TP_SET_DECL(is_smoke)
    TP_SET_DECL(is_spawner)
    TP_SET_DECL(is_stamina_check)
    TP_SET_DECL(is_steal_item_chance_d1000)
    TP_SET_DECL(is_temporary_bag)
    TP_SET_DECL(is_the_grid)
    TP_SET_DECL(is_throwable)
    TP_SET_DECL(is_thrown_automatically_when_chosen)
    TP_SET_DECL(is_torch)
    TP_SET_DECL(is_treasure)
    TP_SET_DECL(is_treasure_class_a)
    TP_SET_DECL(is_treasure_class_b)
    TP_SET_DECL(is_treasure_class_c)
    TP_SET_DECL(is_treasure_eater)
    TP_SET_DECL(is_undead)
    TP_SET_DECL(is_usable)
    TP_SET_DECL(is_used_automatically_when_selected)
    TP_SET_DECL(is_used_when_thrown)
    TP_SET_DECL(is_wall)
    TP_SET_DECL(is_wall_dungeon)
    TP_SET_DECL(is_wand)
    TP_SET_DECL(is_water_lover)
    TP_SET_DECL(is_weapon)
    TP_SET_DECL(is_weapon_wielder)
    TP_SET_DECL(laser_name)
    TP_SET_DECL(left1_tile)
    TP_SET_DECL(left2_tile)
    TP_SET_DECL(lifespan_dice)
    TP_SET_DECL(light_color)
    TP_SET_DECL(light_strength)
    TP_SET_DECL(long_text_description)
    TP_SET_DECL(minion_leash_distance)
    TP_SET_DECL(minion_limit)
    TP_SET_DECL(monst_size)
    TP_SET_DECL(move_speed_ms)
    TP_SET_DECL(name)
    TP_SET_DECL(normal_placement_rules)
    TP_SET_DECL(nutrition_dice)
    TP_SET_DECL(on_birth_do)
    TP_SET_DECL(on_bite_do)
    TP_SET_DECL(on_born_do)
    TP_SET_DECL(on_death_do)
    TP_SET_DECL(on_death_drop_all_items)
    TP_SET_DECL(on_death_is_open)
    TP_SET_DECL(on_hit_do)
    TP_SET_DECL(on_idle_dice)
    TP_SET_DECL(on_lifespan_do)
    TP_SET_DECL(on_miss_do)
    TP_SET_DECL(on_fire_do)
    TP_SET_DECL(on_fall_do)
    TP_SET_DECL(on_fire_at_do)
    TP_SET_DECL(on_tick_do)
    TP_SET_DECL(on_move_do)
    TP_SET_DECL(on_open_do)
    TP_SET_DECL(on_use_do)
    TP_SET_DECL(range_max)
    TP_SET_DECL(rarity)
    TP_SET_DECL(resurrect_dice)
    TP_SET_DECL(right1_tile)
    TP_SET_DECL(right2_tile)
    TP_SET_DECL(spawn_on_shoved)
    TP_SET_DECL(stamina)
    TP_SET_DECL(stat_attack)
    TP_SET_DECL(stat_constitution)
    TP_SET_DECL(stat_defence)
    TP_SET_DECL(stat_strength)
    TP_SET_DECL(stats01)
    TP_SET_DECL(stats02)
    TP_SET_DECL(stats03)
    TP_SET_DECL(stats04)
    TP_SET_DECL(stats05)
    TP_SET_DECL(stats06)
    TP_SET_DECL(stats07)
    TP_SET_DECL(stats08)
    TP_SET_DECL(stats09)
    TP_SET_DECL(stats10)
    TP_SET_DECL(stats11)
    TP_SET_DECL(stats12)
    TP_SET_DECL(stats17)
    TP_SET_DECL(str1)
    TP_SET_DECL(str2)
    TP_SET_DECL(str3)
    TP_SET_DECL(str4)
    TP_SET_DECL(str5)
    TP_SET_DECL(projectile_name)
    TP_SET_DECL(text_a_or_an)
    TP_SET_DECL(text_description)
    TP_SET_DECL(text_hits)
    TP_SET_DECL(text_name)
    TP_SET_DECL(text_title)
    TP_SET_DECL(text_unused)
    TP_SET_DECL(throw_distance)
    TP_SET_DECL(tick_catches_up_on_attack)
    TP_SET_DECL(tick_rate_tenths)
    TP_SET_DECL(tile)
    TP_SET_DECL(tl1_tile)
    TP_SET_DECL(tl2_tile)
    TP_SET_DECL(top1_tile)
    TP_SET_DECL(top2_tile)
    TP_SET_DECL(tr1_tile)
    TP_SET_DECL(tr2_tile)
    TP_SET_DECL(weapon_carry_anim)
    TP_SET_DECL(weapon_damage)
    TP_SET_DECL(weapon_use_delay_hundredths)
    TP_SET_DECL(weapon_use_distance)
    TP_SET_DECL(z_depth)
    TP_SET_DECL(z_prio)

    {"abs_to_pct",                                             (PyCFunction)abs_to_pct_,                                            METH_VARARGS | METH_KEYWORDS, "abs to pct "},
    {"con",                                                    (PyCFunction)con_,                                                   METH_VARARGS,                 "log to the console"},
    {"die",                                                    (PyCFunction)die_,                                                   METH_VARARGS,                 "exit game with error"},
    {"err",                                                    (PyCFunction)err_,                                                   METH_VARARGS,                 "error to the log file"},
    {"if_matches",                                             (PyCFunction)if_matches_,                                            METH_VARARGS | METH_KEYWORDS, "if matches"},
    {"if_matches_then_kill",                                   (PyCFunction)if_matches_then_kill_,                                  METH_VARARGS | METH_KEYWORDS, "if matches then kill"},
    {"level_add",                                              (PyCFunction)level_add_,                                        METH_VARARGS | METH_KEYWORDS, "load a level"},
    {"level_flood_fill_get_all_things",                        (PyCFunction)level_flood_fill_get_all_things,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_get_all",                                          (PyCFunction)level_get_all,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_gfx_flickers_at",                                  (PyCFunction)level_gfx_flickers_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_gfx_water_at",                                     (PyCFunction)level_gfx_water_at,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_able_to_change_levels_at",                      (PyCFunction)level_is_able_to_change_levels_at,                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_able_to_fall_at",                               (PyCFunction)level_is_able_to_fall_at,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_able_to_fire_at",                               (PyCFunction)level_is_able_to_fire_at,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_able_to_fire_at_at",                            (PyCFunction)level_is_able_to_fire_at_at,                            METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_able_to_see_through_doors_at",                  (PyCFunction)level_is_able_to_see_through_doors_at,                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_able_to_walk_through_walls_at",                 (PyCFunction)level_is_able_to_walk_through_walls_at,                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_acid_at",                                       (PyCFunction)level_is_acid_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_acid_lover_at",                                 (PyCFunction)level_is_acid_lover_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_active_at",                                     (PyCFunction)level_is_active_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_alive_monst_at",                                (PyCFunction)level_is_alive_monst_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_always_hit_at",                                 (PyCFunction)level_is_always_hit_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_ascend_dungeon_at",                             (PyCFunction)level_is_ascend_dungeon_at,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_ascend_sewer_at",                               (PyCFunction)level_is_ascend_sewer_at,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_attackable_by_monst_at",                        (PyCFunction)level_is_attackable_by_monst_at,                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_attackable_by_player_at",                       (PyCFunction)level_is_attackable_by_player_at,                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_auto_collect_item_at",                          (PyCFunction)level_is_auto_collect_item_at,                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_bag_at",                                        (PyCFunction)level_is_bag_at,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_barrel_at",                                     (PyCFunction)level_is_barrel_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_bleeder_at",                                    (PyCFunction)level_is_bleeder_at,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_blood_at",                                      (PyCFunction)level_is_blood_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_blood_splatter_at",                             (PyCFunction)level_is_blood_splatter_at,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_bloodied_at",                                   (PyCFunction)level_is_bloodied_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_brazier_at",                                    (PyCFunction)level_is_brazier_at,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_burnable_at",                                   (PyCFunction)level_is_burnable_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_carrier_of_treasure_class_a_at",                (PyCFunction)level_is_carrier_of_treasure_class_a_at,                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_carrier_of_treasure_class_b_at",                (PyCFunction)level_is_carrier_of_treasure_class_b_at,                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_carrier_of_treasure_class_c_at",                (PyCFunction)level_is_carrier_of_treasure_class_c_at,                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_carrying_item_at",                              (PyCFunction)level_is_carrying_item_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_carrying_treasure_at",                          (PyCFunction)level_is_carrying_treasure_at,                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_chasm_at",                                      (PyCFunction)level_is_chasm_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_collect_as_keys_at",                            (PyCFunction)level_is_collect_as_keys_at,                            METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_collectable_at",                                (PyCFunction)level_is_collectable_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_combustible_at",                                (PyCFunction)level_is_combustible_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_corpse_at",                                     (PyCFunction)level_is_corpse_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_corpse_on_death_at",                            (PyCFunction)level_is_corpse_on_death_at,                            METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_corridor_at",                                   (PyCFunction)level_is_corridor_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_critical_to_level_at",                          (PyCFunction)level_is_critical_to_level_at,                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_cursor_at",                                     (PyCFunction)level_is_cursor_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_cursor_can_hover_over_at",                      (PyCFunction)level_is_cursor_can_hover_over_at,                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_cursor_path_at",                                (PyCFunction)level_is_cursor_path_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dead_on_shove_at",                              (PyCFunction)level_is_dead_on_shove_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_deep_water_at",                                 (PyCFunction)level_is_deep_water_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_descend_dungeon_at",                            (PyCFunction)level_is_descend_dungeon_at,                            METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_descend_sewer_at",                              (PyCFunction)level_is_descend_sewer_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_described_when_hovering_over_at",               (PyCFunction)level_is_described_when_hovering_over_at,               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_bl_at",                                     (PyCFunction)level_is_dir_bl_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_br_at",                                     (PyCFunction)level_is_dir_br_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_down_at",                                   (PyCFunction)level_is_dir_down_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_left_at",                                   (PyCFunction)level_is_dir_left_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_none_at",                                   (PyCFunction)level_is_dir_none_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_right_at",                                  (PyCFunction)level_is_dir_right_at,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_tl_at",                                     (PyCFunction)level_is_dir_tl_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_tr_at",                                     (PyCFunction)level_is_dir_tr_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dir_up_at",                                     (PyCFunction)level_is_dir_up_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_dirt_at",                                       (PyCFunction)level_is_dirt_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_door_at",                                       (PyCFunction)level_is_door_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_droppable_at",                                  (PyCFunction)level_is_droppable_at,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_ethereal_at",                                   (PyCFunction)level_is_ethereal_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_ethereal_minion_generator_at",                  (PyCFunction)level_is_ethereal_minion_generator_at,                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_explosion_at",                                  (PyCFunction)level_is_explosion_at,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_extreme_hazard_at",                             (PyCFunction)level_is_extreme_hazard_at,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_fearless_at",                                   (PyCFunction)level_is_fearless_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_fire_at",                                       (PyCFunction)level_is_fire_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_floating_at",                                   (PyCFunction)level_is_floating_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_floor_at",                                      (PyCFunction)level_is_floor_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_floor_deco_at",                                 (PyCFunction)level_is_floor_deco_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_food_at",                                       (PyCFunction)level_is_food_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_food_eater_at",                                 (PyCFunction)level_is_food_eater_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_gold_at",                                       (PyCFunction)level_is_gold_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_hazard_at",                                     (PyCFunction)level_is_hazard_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_humanoid_at",                                   (PyCFunction)level_is_humanoid_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_hunger_insatiable_at",                          (PyCFunction)level_is_hunger_insatiable_at,                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_intelligent_at",                                (PyCFunction)level_is_intelligent_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_interesting_at",                                (PyCFunction)level_is_interesting_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_item_at",                                       (PyCFunction)level_is_item_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_item_carrier_at",                               (PyCFunction)level_is_item_carrier_at,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_item_collected_as_gold_at",                     (PyCFunction)level_is_item_collected_as_gold_at,                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_item_eater_at",                                 (PyCFunction)level_is_item_eater_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_item_not_stackable_at",                         (PyCFunction)level_is_item_not_stackable_at,                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jelly_at",                                      (PyCFunction)level_is_jelly_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jelly_baby_at",                                 (PyCFunction)level_is_jelly_baby_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jelly_baby_eater_at",                           (PyCFunction)level_is_jelly_baby_eater_at,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jelly_eater_at",                                (PyCFunction)level_is_jelly_eater_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jelly_parent_at",                               (PyCFunction)level_is_jelly_parent_at,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jumper_at",                                     (PyCFunction)level_is_jumper_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jumper_chance_d1000_at",                        (PyCFunction)level_is_jumper_chance_d1000_at,                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jumper_distance_at",                            (PyCFunction)level_is_jumper_distance_at,                            METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_jumper_on_low_hp_chance_d1000_at",              (PyCFunction)level_is_jumper_on_low_hp_chance_d1000_at,              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_key_at",                                        (PyCFunction)level_is_key_at,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_killed_on_hit_or_miss_at",                      (PyCFunction)level_is_killed_on_hit_or_miss_at,                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_killed_on_hitting_at",                          (PyCFunction)level_is_killed_on_hitting_at,                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_laser_at",                                      (PyCFunction)level_is_laser_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_lava_at",                                       (PyCFunction)level_is_lava_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_light_blocker_at",                              (PyCFunction)level_is_light_blocker_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_living_at",                                     (PyCFunction)level_is_living_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_meat_at",                                       (PyCFunction)level_is_meat_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_meat_eater_at",                                 (PyCFunction)level_is_meat_eater_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_minion_at",                                     (PyCFunction)level_is_minion_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_minion_generator_at",                           (PyCFunction)level_is_minion_generator_at,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_monst_at",                                      (PyCFunction)level_is_monst_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_moveable_at",                                   (PyCFunction)level_is_moveable_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_movement_blocking_hard_at",                     (PyCFunction)level_is_movement_blocking_hard_at,                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_movement_blocking_soft_at",                     (PyCFunction)level_is_movement_blocking_soft_at,                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_msg_at",                                        (PyCFunction)level_is_msg_at,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_no_tile_at",                                    (PyCFunction)level_is_no_tile_at,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_on_fire_at",                                    (PyCFunction)level_is_on_fire_at,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_player_at",                                     (PyCFunction)level_is_player_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_poison_at",                                     (PyCFunction)level_is_poison_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_potion_at",                                     (PyCFunction)level_is_potion_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_potion_eater_at",                               (PyCFunction)level_is_potion_eater_at,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_projectile_at",                                 (PyCFunction)level_is_projectile_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_removeable_if_out_of_slots_at",                 (PyCFunction)level_is_removeable_if_out_of_slots_at,                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_resurrectable_at",                              (PyCFunction)level_is_resurrectable_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_ripple_at",                                     (PyCFunction)level_is_ripple_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rock_at",                                       (PyCFunction)level_is_rock_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr10_at",                                      (PyCFunction)level_is_rrr10_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr11_at",                                      (PyCFunction)level_is_rrr11_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr12_at",                                      (PyCFunction)level_is_rrr12_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr13_at",                                      (PyCFunction)level_is_rrr13_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr14_at",                                      (PyCFunction)level_is_rrr14_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr15_at",                                      (PyCFunction)level_is_rrr15_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr16_at",                                      (PyCFunction)level_is_rrr16_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr17_at",                                      (PyCFunction)level_is_rrr17_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr18_at",                                      (PyCFunction)level_is_rrr18_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr19_at",                                      (PyCFunction)level_is_rrr19_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr1_at",                                       (PyCFunction)level_is_rrr1_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr20_at",                                      (PyCFunction)level_is_rrr20_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr21_at",                                      (PyCFunction)level_is_rrr21_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr22_at",                                      (PyCFunction)level_is_rrr22_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr23_at",                                      (PyCFunction)level_is_rrr23_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr24_at",                                      (PyCFunction)level_is_rrr24_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr25_at",                                      (PyCFunction)level_is_rrr25_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr26_at",                                      (PyCFunction)level_is_rrr26_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr27_at",                                      (PyCFunction)level_is_rrr27_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr28_at",                                      (PyCFunction)level_is_rrr28_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr29_at",                                      (PyCFunction)level_is_rrr29_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr2_at",                                       (PyCFunction)level_is_rrr2_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr30_at",                                      (PyCFunction)level_is_rrr30_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr31_at",                                      (PyCFunction)level_is_rrr31_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr32_at",                                      (PyCFunction)level_is_rrr32_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr33_at",                                      (PyCFunction)level_is_rrr33_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr34_at",                                      (PyCFunction)level_is_rrr34_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr35_at",                                      (PyCFunction)level_is_rrr35_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr36_at",                                      (PyCFunction)level_is_rrr36_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr37_at",                                      (PyCFunction)level_is_rrr37_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr38_at",                                      (PyCFunction)level_is_rrr38_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr39_at",                                      (PyCFunction)level_is_rrr39_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr3_at",                                       (PyCFunction)level_is_rrr3_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr40_at",                                      (PyCFunction)level_is_rrr40_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr41_at",                                      (PyCFunction)level_is_rrr41_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr42_at",                                      (PyCFunction)level_is_rrr42_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr43_at",                                      (PyCFunction)level_is_rrr43_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr44_at",                                      (PyCFunction)level_is_rrr44_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr45_at",                                      (PyCFunction)level_is_rrr45_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr46_at",                                      (PyCFunction)level_is_rrr46_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr47_at",                                      (PyCFunction)level_is_rrr47_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr48_at",                                      (PyCFunction)level_is_rrr48_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr49_at",                                      (PyCFunction)level_is_rrr49_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr4_at",                                       (PyCFunction)level_is_rrr4_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr50_at",                                      (PyCFunction)level_is_rrr50_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr51_at",                                      (PyCFunction)level_is_rrr51_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr52_at",                                      (PyCFunction)level_is_rrr52_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr53_at",                                      (PyCFunction)level_is_rrr53_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr54_at",                                      (PyCFunction)level_is_rrr54_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr55_at",                                      (PyCFunction)level_is_rrr55_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr56_at",                                      (PyCFunction)level_is_rrr56_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr57_at",                                      (PyCFunction)level_is_rrr57_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr58_at",                                      (PyCFunction)level_is_rrr58_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr59_at",                                      (PyCFunction)level_is_rrr59_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr5_at",                                       (PyCFunction)level_is_rrr5_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr60_at",                                      (PyCFunction)level_is_rrr60_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr61_at",                                      (PyCFunction)level_is_rrr61_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr62_at",                                      (PyCFunction)level_is_rrr62_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr63_at",                                      (PyCFunction)level_is_rrr63_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr64_at",                                      (PyCFunction)level_is_rrr64_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr65_at",                                      (PyCFunction)level_is_rrr65_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr66_at",                                      (PyCFunction)level_is_rrr66_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr67_at",                                      (PyCFunction)level_is_rrr67_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr68_at",                                      (PyCFunction)level_is_rrr68_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr69_at",                                      (PyCFunction)level_is_rrr69_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr6_at",                                       (PyCFunction)level_is_rrr6_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr70_at",                                      (PyCFunction)level_is_rrr70_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr71_at",                                      (PyCFunction)level_is_rrr71_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr72_at",                                      (PyCFunction)level_is_rrr72_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr73_at",                                      (PyCFunction)level_is_rrr73_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr74_at",                                      (PyCFunction)level_is_rrr74_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr75_at",                                      (PyCFunction)level_is_rrr75_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr76_at",                                      (PyCFunction)level_is_rrr76_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr77_at",                                      (PyCFunction)level_is_rrr77_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr78_at",                                      (PyCFunction)level_is_rrr78_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr79_at",                                      (PyCFunction)level_is_rrr79_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr7_at",                                       (PyCFunction)level_is_rrr7_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr80_at",                                      (PyCFunction)level_is_rrr80_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr81_at",                                      (PyCFunction)level_is_rrr81_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr82_at",                                      (PyCFunction)level_is_rrr82_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr83_at",                                      (PyCFunction)level_is_rrr83_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr84_at",                                      (PyCFunction)level_is_rrr84_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr85_at",                                      (PyCFunction)level_is_rrr85_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr86_at",                                      (PyCFunction)level_is_rrr86_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr87_at",                                      (PyCFunction)level_is_rrr87_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr88_at",                                      (PyCFunction)level_is_rrr88_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr89_at",                                      (PyCFunction)level_is_rrr89_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr8_at",                                       (PyCFunction)level_is_rrr8_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_bridge_at",                                      (PyCFunction)level_is_bridge_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr99_at",                                      (PyCFunction)level_is_rrr99_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_rrr9_at",                                       (PyCFunction)level_is_rrr9_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_secret_door_at",                                (PyCFunction)level_is_secret_door_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_sewer_wall_at",                                 (PyCFunction)level_is_sewer_wall_at,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_shallow_water_at",                              (PyCFunction)level_is_shallow_water_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_shovable_at",                                   (PyCFunction)level_is_shovable_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_shown_on_leftbar_at",                           (PyCFunction)level_is_shown_on_leftbar_at,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_shown_uniquely_on_leftbar_at",                  (PyCFunction)level_is_shown_uniquely_on_leftbar_at,                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_skill_at",                                      (PyCFunction)level_is_skill_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_smoke_at",                                      (PyCFunction)level_is_smoke_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_spawner_at",                                    (PyCFunction)level_is_spawner_at,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_stamina_check_at",                              (PyCFunction)level_is_stamina_check_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_steal_item_chance_d1000_at",                    (PyCFunction)level_is_steal_item_chance_d1000_at,                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_temporary_bag_at",                              (PyCFunction)level_is_temporary_bag_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_throwable_at",                                  (PyCFunction)level_is_throwable_at,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_torch_at",                                      (PyCFunction)level_is_torch_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_treasure_at",                                   (PyCFunction)level_is_treasure_at,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_treasure_class_a_at",                           (PyCFunction)level_is_treasure_class_a_at,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_treasure_class_b_at",                           (PyCFunction)level_is_treasure_class_b_at,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_treasure_class_c_at",                           (PyCFunction)level_is_treasure_class_c_at,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_treasure_eater_at",                             (PyCFunction)level_is_treasure_eater_at,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_undead_at",                                     (PyCFunction)level_is_undead_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_usable_at",                                     (PyCFunction)level_is_usable_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_used_when_thrown_at",                           (PyCFunction)level_is_used_when_thrown_at,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_very_combustible_at",                           (PyCFunction)level_is_very_combustible_at,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_visible_at",                                    (PyCFunction)level_is_visible_at,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_wall_at",                                       (PyCFunction)level_is_wall_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_wall_dungeon_at",                               (PyCFunction)level_is_wall_dungeon_at,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_wand_at",                                       (PyCFunction)level_is_wand_at,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_wand_eater_at",                                 (PyCFunction)level_is_wand_eater_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_water_at",                                      (PyCFunction)level_is_water_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_water_lover_at",                                (PyCFunction)level_is_water_lover_at,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_weapon_at",                                     (PyCFunction)level_is_weapon_at,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_is_weapon_wielder_at",                             (PyCFunction)level_is_weapon_wielder_at,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_loves_fire_at",                                    (PyCFunction)level_loves_fire_at,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_loves_poison_at",                                  (PyCFunction)level_loves_poison_at,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"level_place_at",                                         (PyCFunction)level_place_at,                                               METH_VARARGS | METH_KEYWORDS, "kill place"},
    {"level_spawn_at_thing",                                   (PyCFunction)level_spawn_at_thing,                                            METH_VARARGS | METH_KEYWORDS, "spawn under"},
    {"level_spawn_at_thing_if_possible",                       (PyCFunction)level_spawn_at_thing_if_possible,                                METH_VARARGS | METH_KEYWORDS, "spawn under"},
    {"level_spawn_fire_around_thing",                          (PyCFunction)level_spawn_fire_around_thing,                                          METH_VARARGS | METH_KEYWORDS, "spawn fire"},
    {"level_spawn_next_to",                                    (PyCFunction)level_spawn_next_to_,                                      METH_VARARGS | METH_KEYWORDS, "spawn thing"},
    {"level_spawn_next_to_or_on_monst",                        (PyCFunction)level_spawn_next_to_or_on_monst_,                          METH_VARARGS | METH_KEYWORDS, "spawn thing"},
    {"level_spawn_using_items_radius_range",                   (PyCFunction)level_spawn_using_items_radius_range_,                                 METH_VARARGS | METH_KEYWORDS, "spawn things"},
    {"log",                                                    (PyCFunction)log_,                                                   METH_VARARGS,                 "log to the log file"},
    {"map_load_room",                                          (PyCFunction)map_load_room_,                                         METH_VARARGS | METH_KEYWORDS, "load a room"},
    {"music_load",                                             (PyCFunction)music_load_,                                            METH_VARARGS | METH_KEYWORDS, "load a sound"},
    {"music_play",                                             (PyCFunction)music_play_,                                            METH_VARARGS | METH_KEYWORDS, "play a sound"},
    {"pct_to_abs",                                             (PyCFunction)pct_to_abs_,                                            METH_VARARGS | METH_KEYWORDS, "pct to abs"},
    {"puts",                                                   (PyCFunction)puts_,                                                  METH_VARARGS,                 "log to the console"},
    {"sound_load",                                             (PyCFunction)sound_load_,                                            METH_VARARGS | METH_KEYWORDS, "load a sound"},
    {"sound_play",                                             (PyCFunction)sound_play_,                                            METH_VARARGS | METH_KEYWORDS, "play a sound"},
    {"sound_play_channel",                                     (PyCFunction)sound_play_channel_,                                    METH_VARARGS | METH_KEYWORDS, "play a sound"},
    {"tex_load",                                               (PyCFunction)tex_load_,                                              METH_VARARGS | METH_KEYWORDS, "load a texture"},
    {"text_size",                                              (PyCFunction)text_size_,                                             METH_VARARGS | METH_KEYWORDS, "text size in pixels"},
    {"thing_decr_current_damage",                              (PyCFunction)thing_decr_current_damage,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_decr_health",                                      (PyCFunction)thing_decr_health,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_decr_health_max",                                  (PyCFunction)thing_decr_health_max,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_decr_stamina",                                     (PyCFunction)thing_decr_stamina,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_decr_stamina_max",                                 (PyCFunction)thing_decr_stamina_max,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_fire_at",                                          (PyCFunction)thing_fire_at,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_coords",                                       (PyCFunction)thing_get_coords,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_current_damage",                               (PyCFunction)thing_get_current_damage,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_health",                                       (PyCFunction)thing_get_health,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_health_max",                                   (PyCFunction)thing_get_health_max,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_immediate_minion_owner_id",                    (PyCFunction)thing_get_immediate_minion_owner_id,                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_immediate_owner_id",                           (PyCFunction)thing_get_immediate_owner_id,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_immediate_spawned_owner_id",                   (PyCFunction)thing_get_immediate_spawned_owner_id,                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_name",                                         (PyCFunction)thing_get_name,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_stamina",                                      (PyCFunction)thing_get_stamina,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_get_stamina_max",                                  (PyCFunction)thing_get_stamina_max,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_gfx_flickers",                                     (PyCFunction)thing_gfx_flickers,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_gfx_water",                                        (PyCFunction)thing_gfx_water,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_hit",                                              (PyCFunction)thing_hit,                                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_incr_current_damage",                              (PyCFunction)thing_incr_current_damage,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_incr_health",                                      (PyCFunction)thing_incr_health,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_incr_health_max",                                  (PyCFunction)thing_incr_health_max,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_incr_stamina",                                     (PyCFunction)thing_incr_stamina,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_incr_stamina_max",                                 (PyCFunction)thing_incr_stamina_max,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_able_to_change_levels",                         (PyCFunction)thing_is_able_to_change_levels,                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_able_to_fall",                                  (PyCFunction)thing_is_able_to_fall,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_able_to_see_through_doors",                     (PyCFunction)thing_is_able_to_see_through_doors,                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_able_to_walk_through_walls",                    (PyCFunction)thing_is_able_to_walk_through_walls,                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_acid",                                          (PyCFunction)thing_is_acid,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_acid_lover",                                    (PyCFunction)thing_is_acid_lover,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_active",                                        (PyCFunction)thing_is_active,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_alive_monst",                                   (PyCFunction)thing_is_alive_monst,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_always_hit",                                    (PyCFunction)thing_is_always_hit,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_ascend_dungeon",                                (PyCFunction)thing_is_ascend_dungeon,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_ascend_sewer",                                  (PyCFunction)thing_is_ascend_sewer,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_auto_collect_item",                             (PyCFunction)thing_is_auto_collect_item,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_bag",                                           (PyCFunction)thing_is_bag,                                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_barrel",                                        (PyCFunction)thing_is_barrel,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_bleeder",                                       (PyCFunction)thing_is_bleeder,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_blood",                                         (PyCFunction)thing_is_blood,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_blood_splatter",                                (PyCFunction)thing_is_blood_splatter,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_bloodied",                                      (PyCFunction)thing_is_bloodied,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_brazier",                                       (PyCFunction)thing_is_brazier,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_burnable",                                      (PyCFunction)thing_is_burnable,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_carrier_of_treasure_class_a",                   (PyCFunction)thing_is_carrier_of_treasure_class_a,                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_carrier_of_treasure_class_b",                   (PyCFunction)thing_is_carrier_of_treasure_class_b,                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_carrier_of_treasure_class_c",                   (PyCFunction)thing_is_carrier_of_treasure_class_c,                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_carrying_item",                                 (PyCFunction)thing_is_carrying_item,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_carrying_treasure",                             (PyCFunction)thing_is_carrying_treasure,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_chasm",                                         (PyCFunction)thing_is_chasm,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_collect_as_keys",                               (PyCFunction)thing_is_collect_as_keys,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_collectable",                                   (PyCFunction)thing_is_collectable,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_combustible",                                   (PyCFunction)thing_is_combustible,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_corpse",                                        (PyCFunction)thing_is_corpse,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_corpse_on_death",                               (PyCFunction)thing_is_corpse_on_death,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_corridor",                                      (PyCFunction)thing_is_corridor,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_critical_to_level",                             (PyCFunction)thing_is_critical_to_level,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_cursor",                                        (PyCFunction)thing_is_cursor,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_cursor_can_hover_over",                         (PyCFunction)thing_is_cursor_can_hover_over,                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_cursor_can_hover_over_but_needs_double_click",  (PyCFunction)thing_is_cursor_can_hover_over_but_needs_double_click,  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_cursor_path",                                   (PyCFunction)thing_is_cursor_path,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dead_on_shove",                                 (PyCFunction)thing_is_dead_on_shove,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_deep_water",                                    (PyCFunction)thing_is_deep_water,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_descend_dungeon",                               (PyCFunction)thing_is_descend_dungeon,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_descend_sewer",                                 (PyCFunction)thing_is_descend_sewer,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_described_when_hovering_over",                  (PyCFunction)thing_is_described_when_hovering_over,                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_bl",                                        (PyCFunction)thing_is_dir_bl,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_br",                                        (PyCFunction)thing_is_dir_br,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_down",                                      (PyCFunction)thing_is_dir_down,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_left",                                      (PyCFunction)thing_is_dir_left,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_none",                                      (PyCFunction)thing_is_dir_none,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_right",                                     (PyCFunction)thing_is_dir_right,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_tl",                                        (PyCFunction)thing_is_dir_tl,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_tr",                                        (PyCFunction)thing_is_dir_tr,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dir_up",                                        (PyCFunction)thing_is_dir_up,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_dirt",                                          (PyCFunction)thing_is_dirt,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_door",                                          (PyCFunction)thing_is_door,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_droppable",                                     (PyCFunction)thing_is_droppable,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_ethereal",                                      (PyCFunction)thing_is_ethereal,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_ethereal_minion_generator",                     (PyCFunction)thing_is_ethereal_minion_generator,                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_explosion",                                     (PyCFunction)thing_is_explosion,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_extreme_hazard",                                (PyCFunction)thing_is_extreme_hazard,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_fearless",                                      (PyCFunction)thing_is_fearless,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_fire",                                          (PyCFunction)thing_is_fire,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_floating",                                      (PyCFunction)thing_is_floating,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_floor",                                         (PyCFunction)thing_is_floor,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_floor_deco",                                    (PyCFunction)thing_is_floor_deco,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_food",                                          (PyCFunction)thing_is_food,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_food_eater",                                    (PyCFunction)thing_is_food_eater,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_gold",                                          (PyCFunction)thing_is_gold,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_hazard",                                        (PyCFunction)thing_is_hazard,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_humanoid",                                      (PyCFunction)thing_is_humanoid,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_hunger_insatiable",                             (PyCFunction)thing_is_hunger_insatiable,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_intelligent",                                   (PyCFunction)thing_is_intelligent,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_interesting",                                   (PyCFunction)thing_is_interesting,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_item",                                          (PyCFunction)thing_is_item,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_item_carrier",                                  (PyCFunction)thing_is_item_carrier,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_item_collected_as_gold",                        (PyCFunction)thing_is_item_collected_as_gold,                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_item_eater",                                    (PyCFunction)thing_is_item_eater,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_item_not_stackable",                            (PyCFunction)thing_is_item_not_stackable,                            METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jelly",                                         (PyCFunction)thing_is_jelly,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jelly_baby",                                    (PyCFunction)thing_is_jelly_baby,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jelly_baby_eater",                              (PyCFunction)thing_is_jelly_baby_eater,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jelly_eater",                                   (PyCFunction)thing_is_jelly_eater,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jelly_parent",                                  (PyCFunction)thing_is_jelly_parent,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jumper",                                        (PyCFunction)thing_is_jumper,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jumper_chance_d1000",                           (PyCFunction)thing_is_jumper_chance_d1000,                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jumper_distance",                               (PyCFunction)thing_is_jumper_distance,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_jumper_on_low_hp_chance_d1000",                 (PyCFunction)thing_is_jumper_on_low_hp_chance_d1000,                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_key",                                           (PyCFunction)thing_is_key,                                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_killed_on_hit_or_miss",                         (PyCFunction)thing_is_killed_on_hit_or_miss,                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_killed_on_hitting",                             (PyCFunction)thing_is_killed_on_hitting,                             METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_laser",                                         (PyCFunction)thing_is_laser,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_lava",                                          (PyCFunction)thing_is_lava,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_light_blocker",                                 (PyCFunction)thing_is_light_blocker,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_living",                                        (PyCFunction)thing_is_living,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_loggable_for_important_stuff",                  (PyCFunction)thing_is_loggable_for_important_stuff,                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_loggable_for_unimportant_stuff",                (PyCFunction)thing_is_loggable_for_unimportant_stuff,                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_meat",                                          (PyCFunction)thing_is_meat,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_meat_eater",                                    (PyCFunction)thing_is_meat_eater,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_minion",                                        (PyCFunction)thing_is_minion,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_minion_generator",                              (PyCFunction)thing_is_minion_generator,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_monst",                                         (PyCFunction)thing_is_monst,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_moveable",                                      (PyCFunction)thing_is_moveable,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_movement_blocking_hard",                        (PyCFunction)thing_is_movement_blocking_hard,                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_movement_blocking_soft",                        (PyCFunction)thing_is_movement_blocking_soft,                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_msg",                                           (PyCFunction)thing_is_msg,                                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_no_tile",                                       (PyCFunction)thing_is_no_tile,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_on_fire",                                       (PyCFunction)thing_is_on_fire,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_player",                                        (PyCFunction)thing_is_player,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_poison",                                        (PyCFunction)thing_is_poison,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_potion",                                        (PyCFunction)thing_is_potion,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_potion_eater",                                  (PyCFunction)thing_is_potion_eater,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_projectile",                                    (PyCFunction)thing_is_projectile,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_removeable_if_out_of_slots",                    (PyCFunction)thing_is_removeable_if_out_of_slots,                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_resurrectable",                                 (PyCFunction)thing_is_resurrectable,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_ripple",                                        (PyCFunction)thing_is_ripple,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rock",                                          (PyCFunction)thing_is_rock,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr1",                                          (PyCFunction)thing_is_rrr1,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr10",                                         (PyCFunction)thing_is_rrr10,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr11",                                         (PyCFunction)thing_is_rrr11,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr12",                                         (PyCFunction)thing_is_rrr12,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr13",                                         (PyCFunction)thing_is_rrr13,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr14",                                         (PyCFunction)thing_is_rrr14,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr15",                                         (PyCFunction)thing_is_rrr15,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr16",                                         (PyCFunction)thing_is_rrr16,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr17",                                         (PyCFunction)thing_is_rrr17,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr18",                                         (PyCFunction)thing_is_rrr18,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr19",                                         (PyCFunction)thing_is_rrr19,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr2",                                          (PyCFunction)thing_is_rrr2,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr20",                                         (PyCFunction)thing_is_rrr20,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr21",                                         (PyCFunction)thing_is_rrr21,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr22",                                         (PyCFunction)thing_is_rrr22,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr23",                                         (PyCFunction)thing_is_rrr23,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr24",                                         (PyCFunction)thing_is_rrr24,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr25",                                         (PyCFunction)thing_is_rrr25,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr26",                                         (PyCFunction)thing_is_rrr26,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr27",                                         (PyCFunction)thing_is_rrr27,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr28",                                         (PyCFunction)thing_is_rrr28,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr29",                                         (PyCFunction)thing_is_rrr29,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr3",                                          (PyCFunction)thing_is_rrr3,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr30",                                         (PyCFunction)thing_is_rrr30,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr31",                                         (PyCFunction)thing_is_rrr31,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr32",                                         (PyCFunction)thing_is_rrr32,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr33",                                         (PyCFunction)thing_is_rrr33,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr34",                                         (PyCFunction)thing_is_rrr34,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr35",                                         (PyCFunction)thing_is_rrr35,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr36",                                         (PyCFunction)thing_is_rrr36,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr37",                                         (PyCFunction)thing_is_rrr37,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr38",                                         (PyCFunction)thing_is_rrr38,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr39",                                         (PyCFunction)thing_is_rrr39,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr4",                                          (PyCFunction)thing_is_rrr4,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr40",                                         (PyCFunction)thing_is_rrr40,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr41",                                         (PyCFunction)thing_is_rrr41,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr42",                                         (PyCFunction)thing_is_rrr42,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr43",                                         (PyCFunction)thing_is_rrr43,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr44",                                         (PyCFunction)thing_is_rrr44,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr45",                                         (PyCFunction)thing_is_rrr45,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr46",                                         (PyCFunction)thing_is_rrr46,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr47",                                         (PyCFunction)thing_is_rrr47,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr48",                                         (PyCFunction)thing_is_rrr48,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr49",                                         (PyCFunction)thing_is_rrr49,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr5",                                          (PyCFunction)thing_is_rrr5,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr50",                                         (PyCFunction)thing_is_rrr50,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr51",                                         (PyCFunction)thing_is_rrr51,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr52",                                         (PyCFunction)thing_is_rrr52,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr53",                                         (PyCFunction)thing_is_rrr53,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr54",                                         (PyCFunction)thing_is_rrr54,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr55",                                         (PyCFunction)thing_is_rrr55,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr56",                                         (PyCFunction)thing_is_rrr56,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr57",                                         (PyCFunction)thing_is_rrr57,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr58",                                         (PyCFunction)thing_is_rrr58,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr59",                                         (PyCFunction)thing_is_rrr59,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr6",                                          (PyCFunction)thing_is_rrr6,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr60",                                         (PyCFunction)thing_is_rrr60,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr61",                                         (PyCFunction)thing_is_rrr61,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr62",                                         (PyCFunction)thing_is_rrr62,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr63",                                         (PyCFunction)thing_is_rrr63,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr64",                                         (PyCFunction)thing_is_rrr64,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr65",                                         (PyCFunction)thing_is_rrr65,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr66",                                         (PyCFunction)thing_is_rrr66,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr67",                                         (PyCFunction)thing_is_rrr67,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr68",                                         (PyCFunction)thing_is_rrr68,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr69",                                         (PyCFunction)thing_is_rrr69,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr7",                                          (PyCFunction)thing_is_rrr7,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr70",                                         (PyCFunction)thing_is_rrr70,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr71",                                         (PyCFunction)thing_is_rrr71,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr72",                                         (PyCFunction)thing_is_rrr72,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr73",                                         (PyCFunction)thing_is_rrr73,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr74",                                         (PyCFunction)thing_is_rrr74,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr75",                                         (PyCFunction)thing_is_rrr75,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr76",                                         (PyCFunction)thing_is_rrr76,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr77",                                         (PyCFunction)thing_is_rrr77,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr78",                                         (PyCFunction)thing_is_rrr78,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr79",                                         (PyCFunction)thing_is_rrr79,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr8",                                          (PyCFunction)thing_is_rrr8,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr80",                                         (PyCFunction)thing_is_rrr80,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr81",                                         (PyCFunction)thing_is_rrr81,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr82",                                         (PyCFunction)thing_is_rrr82,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr83",                                         (PyCFunction)thing_is_rrr83,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr84",                                         (PyCFunction)thing_is_rrr84,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr85",                                         (PyCFunction)thing_is_rrr85,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr86",                                         (PyCFunction)thing_is_rrr86,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr87",                                         (PyCFunction)thing_is_rrr87,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr88",                                         (PyCFunction)thing_is_rrr88,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr89",                                         (PyCFunction)thing_is_rrr89,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr9",                                          (PyCFunction)thing_is_rrr9,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_bridge",                                         (PyCFunction)thing_is_bridge,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_rrr99",                                         (PyCFunction)thing_is_rrr99,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_secret_door",                                   (PyCFunction)thing_is_secret_door,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_sewer_wall",                                    (PyCFunction)thing_is_sewer_wall,                                    METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_shallow_water",                                 (PyCFunction)thing_is_shallow_water,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_shovable",                                      (PyCFunction)thing_is_shovable,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_shown_on_leftbar",                              (PyCFunction)thing_is_shown_on_leftbar,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_shown_uniquely_on_leftbar",                     (PyCFunction)thing_is_shown_uniquely_on_leftbar,                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_skill",                                         (PyCFunction)thing_is_skill,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_smoke",                                         (PyCFunction)thing_is_smoke,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_spawner",                                       (PyCFunction)thing_is_spawner,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_stamina_check",                                 (PyCFunction)thing_is_stamina_check,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_steal_item_chance_d1000",                       (PyCFunction)thing_is_steal_item_chance_d1000,                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_target_select_automatically_when_chosen",       (PyCFunction)thing_is_target_select_automatically_when_chosen, METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_temporary_bag",                                 (PyCFunction)thing_is_temporary_bag,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_throwable",                                     (PyCFunction)thing_is_throwable,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_thrown_automatically_when_chosen",              (PyCFunction)thing_is_thrown_automatically_when_chosen,              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_torch",                                         (PyCFunction)thing_is_torch,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_treasure",                                      (PyCFunction)thing_is_treasure,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_treasure_class_a",                              (PyCFunction)thing_is_treasure_class_a,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_treasure_class_b",                              (PyCFunction)thing_is_treasure_class_b,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_treasure_class_c",                              (PyCFunction)thing_is_treasure_class_c,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_treasure_eater",                                (PyCFunction)thing_is_treasure_eater,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_undead",                                        (PyCFunction)thing_is_undead,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_usable",                                        (PyCFunction)thing_is_usable,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_used_automatically_when_selected",              (PyCFunction)thing_is_used_automatically_when_selected,              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_used_when_thrown",                              (PyCFunction)thing_is_used_when_thrown,                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_very_combustible",                              (PyCFunction)thing_is_very_combustible,                                     METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_visible",                                       (PyCFunction)thing_is_visible,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_wall",                                          (PyCFunction)thing_is_wall,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_wall_dungeon",                                  (PyCFunction)thing_is_wall_dungeon,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_wand",                                          (PyCFunction)thing_is_wand,                                          METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_wand_eater",                                    (PyCFunction)thing_is_wand_eater,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_water",                                         (PyCFunction)thing_is_water,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_water_lover",                                   (PyCFunction)thing_is_water_lover,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_weapon",                                        (PyCFunction)thing_is_weapon,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_is_weapon_wielder",                                (PyCFunction)thing_is_weapon_wielder,                                METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_killed",                                           (PyCFunction)thing_killed,                                           METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_killed_by",                                        (PyCFunction)thing_killed_by,                                        METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_loves_fire",                                       (PyCFunction)thing_loves_fire,                                         METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_loves_poison",                                     (PyCFunction)thing_loves_poison,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_msg",                                              (PyCFunction)thing_msg,                                              METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_possible_to_attack",                               (PyCFunction)thing_possible_to_attack,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_set_current_damage",                               (PyCFunction)thing_set_current_damage,                               METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_set_health",                                       (PyCFunction)thing_set_health,                                       METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_set_health_max",                                   (PyCFunction)thing_set_health_max,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_set_stamina",                                      (PyCFunction)thing_set_stamina,                                      METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_set_stamina_max",                                  (PyCFunction)thing_set_stamina_max,                                  METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_skill_activate",                                   (PyCFunction)thing_skill_activate,                                   METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_skill_deactivate",                                 (PyCFunction)thing_skill_deactivate,                                 METH_VARARGS | METH_KEYWORDS, "thing api"},
    {"thing_sound_play",                                       (PyCFunction)thing_sound_play_,                                         METH_VARARGS | METH_KEYWORDS, "play a sound"},
    {"thing_sound_play_channel",                               (PyCFunction)thing_sound_play_channel_,                                 METH_VARARGS | METH_KEYWORDS, "play a sound"},
    {"tile_load_arr",                                          (PyCFunction)tile_load_arr_,                                         METH_VARARGS | METH_KEYWORDS, "load a tile array"},
    {"tile_load_arr_sprites",                                  (PyCFunction)tile_load_arr_sprites_,                                 METH_VARARGS | METH_KEYWORDS, "load a tile array in color and black and white"},
    {"topcon",                                                 (PyCFunction)topcon_,                                                METH_VARARGS,                 "log to the mini console"},
    {"tp_load",                                                (PyCFunction)tp_load_,                                               METH_VARARGS | METH_KEYWORDS, "load a thing template"},
    {"tp_update",                                              (PyCFunction)tp_update_,                                             METH_VARARGS | METH_KEYWORDS, "update template"},

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

    LOG("Current system python path: (adding %s)", path);

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

        LOG("  %s", item);

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

    LOG("Set python path: %s", new_path);

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
    PyModule_AddIntConstant(zx_mod, "MAP_HEIGHT", MAP_HEIGHT);
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
    PyModule_AddStringConstant(zx_mod, "VERSION", VERSION);

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
    CON("INI: PYTHONVERSION %s", PYTHONVERSION);
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
    newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYTHONVERSION;
    newpath += PATHSEP;
    newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYTHONVERSION DIR_SEP "lib-dynload";
    newpath += PATHSEP;
    newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYTHONVERSION DIR_SEP "site-packages";
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

    LOG("INI: Calling PyImport_ImportModule for zx module");

    zx_mod = PyImport_ImportModule("zx");
    if (!zx_mod) {
        py_err();
        ERR("Module zx import failed");
        return;
    }

    python_add_consts();

    LOG("INI: Calling PyImport_ImportModule for init module");

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
