/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_py_tp.h"
#include "my_python.h"
#include "my_py_sdl.h"
#include "frameobject.h"
#include "my_string.h"
#include "my_ascii.h"
#include "my_game.h"

static PyObject *zx_mod;
PyMODINIT_FUNC python_m_y_module_create(void);

void py_call_void_module_int (const char *module, const char *name, int val1)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(i)", val1);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();
}

void py_call_void_int (const char *name, int val1)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *pFunc = PyObject_GetAttrString(zx_mod, name);
    if (PyCallable_Check(pFunc)) {
        PyObject *pArgs = Py_BuildValue("(i)", val1);
        PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python function %s(%d)", name, val1);
    }

    py_err();
}

void py_call_void (const char *name)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *pFunc = PyObject_GetAttrString(zx_mod, name);
    if (PyCallable_Check(pFunc)) {
        PyObject *pValue = PyObject_CallObject(pFunc, 0);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python function %s", name);
    }

    py_err();
}

int py_call_int_module_ptr_iiiiii (const char *module, const char *name, void *val1, int val2, int val3, int val4, int val5, int val6, int val7)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiiiii)", (uintptr_t) val1, val2, val3, val4, val5, val6, val7);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

int py_call_int_module_ptr_iiiii (const char *module, const char *name, void *val1, int val2, int val3, int val4, int val5, int val6)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiiii)", (uintptr_t) val1, val2, val3, val4, val5, val6);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

int py_call_int_module_ptr_iiii (const char *module, const char *name, void *val1, int val2, int val3, int val4, int val5)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiii)", (uintptr_t) val1, val2, val3, val4, val5);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

int py_call_int_module_ptr_iii (const char *module, const char *name, void *val1, int val2, int val3, int val4)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiii)", (uintptr_t) val1, val2, val3, val4);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

int py_call_int_module_ptr_ii (const char *module, const char *name, void *val1, int val2, int val3)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kii)", (uintptr_t) val1, val2, val3);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

int py_call_int_module_ptr_int (const char *module, const char *name, void *val1, int val2)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Ki)", (uintptr_t) val1, val2);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

void py_call_void_module_ptr_iiiiiiiiiiiiiiiiiii (const char *module,
                                                  const char *name,
                                                  void *val1,
                                                  int val2,
                                                  int val3,
                                                  int val4,
                                                  int val5,
                                                  int val6,
                                                  int val7,
                                                  int val8,
                                                  int val9,
                                                  int val10,
                                                  int val11,
                                                  int val12,
                                                  int val13,
                                                  int val14,
                                                  int val15,
                                                  int val16,
                                                  int val17,
                                                  int val18,
                                                  int val19,
                                                  int val20)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiiiiiiiiiiiiiiiiii)",
                                        (uintptr_t) val1,
                                        val2,
                                        val3,
                                        val4,
                                        val5,
                                        val6,
                                        val7,
                                        val8,
                                        val9,
                                        val10,
                                        val11,
                                        val12,
                                        val13,
                                        val14,
                                        val15,
                                        val16,
                                        val17,
                                        val18,
                                        val19,
                                        val20);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

void py_call_void_module_ptr_iiiiiiii (const char *module, const char *name, void *val1, int val2, int val3, int val4, int val5, int val6, int val7, int val8, int val9)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiiiiiii)", (uintptr_t) val1, val2, val3, val4, val5, val6, val7, val8, val9);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

void py_call_void_module_ptr_iiiiiii (const char *module, const char *name, void *val1, int val2, int val3, int val4, int val5, int val6, int val7, int val8)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiiiiii)", (uintptr_t) val1, val2, val3, val4, val5, val6, val7, val8);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

void py_call_void_module_ptr_iiiiii (const char *module, const char *name, void *val1, int val2, int val3, int val4, int val5, int val6, int val7)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiiiii)", (uintptr_t) val1, val2, val3, val4, val5, val6, val7);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

void py_call_void_module_ptr_iiiii (const char *module, const char *name, void *val1, int val2, int val3, int val4, int val5, int val6)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiiii)", (uintptr_t) val1, val2, val3, val4, val5, val6);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

void py_call_void_module_ptr_iiii (const char *module, const char *name, void *val1, int val2, int val3, int val4, int val5)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiiii)", (uintptr_t) val1, val2, val3, val4, val5);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

void py_call_void_module_ptr_iii (const char *module, const char *name, void *val1, int val2, int val3, int val4)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kiii)", (uintptr_t) val1, val2, val3, val4);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

void py_call_void_module_ptr_ii (const char *module, const char *name, void *val1, int val2, int val3)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Kii)", (uintptr_t) val1, val2, val3);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

void py_call_void_module_ptr_int (const char *module, const char *name, void *val1, int val2)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(Ki)", (uintptr_t) val1, val2);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

int py_call_int_module_ptr (const char *module, const char *name, void *val1)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(K)", (uintptr_t) val1);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

void py_call_void_module_ptr (const char *module, const char *name, void *val1)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(K)", (uintptr_t) val1);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

int py_call_int_module_ptr_ptr (const char *module, const char *name, void *val1, void *val2)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(KK)",
                                        (uintptr_t) val1,
                                        (uintptr_t) val2);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

void py_call_void_module_ptr_ptr (const char *module, const char *name, void *val1, void *val2)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(KK)",
                                        (uintptr_t) val1,
                                        (uintptr_t) val2);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return;
}

int py_call_int_module_int (const char *module, const char *name, int val1)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pArgs = Py_BuildValue("(i)", val1);
        PyObject *pValue = PyObject_CallObject(fn, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

int py_call_int_module_void (const char *module, const char *name)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return (ret);
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return (ret);
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return (ret);
    }

    if (PyCallable_Check(fn)) {
        PyObject *pValue = PyObject_CallObject(fn, 0);
        if (pValue) {
            ret = py_obj_to_int(pValue);

            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();

    return (ret);
}

void py_call_void_module_void (const char *module, const char *name)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *pValue = PyObject_CallObject(fn, 0);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();
}

int py_call_ii (const char *name, int val1)
{_
    int ret = -1;

    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *pFunc = PyObject_GetAttrString(zx_mod, name);
    if (PyCallable_Check(pFunc)) {
        PyObject *pArgs = Py_BuildValue("(i)", val1);
        PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs);
        if (pValue) {
            ret = py_obj_to_int(pValue);
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python function %s(%d)", name, val1);
    }

    py_err();

    return (ret);
}

void py_call_void_module_with_list_of_points (const char *module, 
                                              const char *name, 
                                              std::vector<point> points)
{_
    if (!zx_mod) {
        DIE("python module not inited yet");
    }

    PyObject *v = PyObject_GetAttrString(zx_mod, module);
    if (!v) {
        DIE("cannot find python module %s", module);
        return;
    }

    PyObject *dict = PyModule_GetDict(v);
    if (!dict) {
        DIE("cannot find python module %s dict", module);
        return;
    }

    PyObject *fn = PyDict_GetItemString(dict, name);
    if (!fn) {
        DIE("cannot find python module %s fn %s", module, name);
        return;
    }

    if (PyCallable_Check(fn)) {
        PyObject *my_list = PyList_New(points.size());

        int i = 0;
        for (auto p = points.begin(); p != points.end(); p++, i++) {
            PyObject *x = Py_BuildValue("i", p->x);
            PyObject *y = Py_BuildValue("i", p->y);

            PyObject *my_tuple = PyTuple_New(2);
            PyTuple_SetItem(my_tuple, 0, x);
            PyTuple_SetItem(my_tuple, 1, y);

            if (PyList_SetItem(my_list, i, my_tuple) == -1) {
                DIE("set dmap item %d,%d failed", p->x, p->y)
            }
        }

        PyObject *obj = Py_BuildValue("(O)", my_list);
        PyObject *pValue = PyObject_CallObject(fn, obj);
        Py_DECREF(my_list);
        if (pValue) {
            Py_DECREF(pValue);
        }
    } else {
        ERR("cannot call python module %s fn %s", module, name);
    }

    py_err();
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
        ERR("int conversion failed");
    }

    return (val);
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
        ERR("int conversion failed");
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
        ERR("int conversion failed");
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
        ERR("int conversion failed");
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
        ERR("int conversion failed");
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
        ERR("int conversion failed");
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
        ERR("obj lookup conversion failed");
    }

    Py_RETURN_NONE;
}

static PyObject *con_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    wchar_t *a = 0;

    if (!PyArg_ParseTuple(args, "u", &a)) {
        return (0);
    }

    if (a) {
        con(a);
    }

    Py_RETURN_NONE;
}

static PyObject *tip_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    wchar_t *a = 0;

    if (!PyArg_ParseTuple(args, "u", &a)) {
        return (0);
    }

    if (a) {
        tip(a);
    }

    Py_RETURN_NONE;
}

static PyObject *tip2_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    wchar_t *a = 0;

    if (!PyArg_ParseTuple(args, "u", &a)) {
        return (0);
    }

    if (a) {
        tip2(a);
    }

    Py_RETURN_NONE;
}

static PyObject *puts_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *a = 0;

    if (!PyArg_ParseTuple(args, "s", &a)) {
        return (0);
    }

    fputs(a, MY_STDOUT);
    fflush(MY_STDOUT);
    printf("%s", a);

    Py_RETURN_NONE;
}

static PyObject *log_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *a = 0;

    if (!PyArg_ParseTuple(args, "s", &a)) {
        return (0);
    }

    if (a) {
        LOG("%s", a);
    }

    Py_RETURN_NONE;
}

static PyObject *err_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *a = 0;

    if (!PyArg_ParseTuple(args, "s", &a)) {
        return (0);
    }

    if (a) {
        ERR("%s", a);
    }

    Py_RETURN_NONE;
}

static PyObject *die_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *a = 0;

    if (!PyArg_ParseTuple(args, "s", &a)) {
        return (0);
    }

    if (a) {
        DIE("%s", a);
    }

    Py_RETURN_NONE;
}

static PyMethodDef python_c_METHODS[] = {
 /*
     * The cast of the function is necessary since PyCFunction values
     * only take two PyObject *parameters, and some take three.
     */
    {"con",
        (PyCFunction)con_,
        METH_VARARGS,
        "log to the console"},

    {"tip",
        (PyCFunction)tip_,
        METH_VARARGS,
        "tooltip"},

    {"tip2",
        (PyCFunction)tip2_,
        METH_VARARGS,
        "tooltip2"},

    {"puts",
        (PyCFunction)puts_,
        METH_VARARGS,
        "log to the console"},

    {"err",
        (PyCFunction)err_,
        METH_VARARGS,
        "error to the log file"},

    {"log",
        (PyCFunction)log_,
        METH_VARARGS,
        "log to the log file"},

    {"die",
        (PyCFunction)die_,
        METH_VARARGS,
        "exit game with error"},

    {"text_size",
        (PyCFunction)text_size_,
        METH_VARARGS | METH_KEYWORDS,
        "text size in pixels"},

    {"abs_to_pct",
        (PyCFunction)abs_to_pct_,
        METH_VARARGS | METH_KEYWORDS,
        "abs to pct "},

    {"pct_to_abs",
        (PyCFunction)pct_to_abs_,
        METH_VARARGS | METH_KEYWORDS,
        "pct to abs"},

    {"tex_load",
        (PyCFunction)tex_load_,
        METH_VARARGS | METH_KEYWORDS,
        "load a texture"},

    {"tex_size",
        (PyCFunction)tex_size_,
        METH_VARARGS | METH_KEYWORDS,
        "tex info"},

    {"tex_pixel",
        (PyCFunction)tex_pixel_,
        METH_VARARGS | METH_KEYWORDS,
        "get pixels"},

    {"tile_load_arr",
        (PyCFunction)tile_load_arr_,
        METH_VARARGS | METH_KEYWORDS,
        "load a tile array"},

    {"tile_size",
        (PyCFunction)tile_get_size_,
        METH_VARARGS | METH_KEYWORDS,
        "tile size in pixels"},

    {"tp_load",
        (PyCFunction)tp_load_,
        METH_VARARGS | METH_KEYWORDS,
        "load a thing template"},

    {"map_load_room",
        (PyCFunction)map_load_room_,
        METH_VARARGS | METH_KEYWORDS,
        "load a room"},

    TP_SET_DECL(tile)
    TP_SET_DECL(left_tile)
    TP_SET_DECL(right_tile)
    TP_SET_DECL(top_tile)
    TP_SET_DECL(bot_tile)
    TP_SET_DECL(bl_tile)
    TP_SET_DECL(br_tile)
    TP_SET_DECL(tl_tile)
    TP_SET_DECL(tr_tile)
    TP_SET_DECL(blit_top_off)
    TP_SET_DECL(blit_bot_off)
    TP_SET_DECL(blit_left_off)
    TP_SET_DECL(blit_right_off)
    TP_SET_DECL(short_name)
    TP_SET_DECL(raw_name)
    TP_SET_DECL(str_zzz1)
    TP_SET_DECL(str_zzz2)
    TP_SET_DECL(str_zzz3)
    TP_SET_DECL(str_zzz4)
    TP_SET_DECL(str_zzz5)
    TP_SET_DECL(str_zzz6)
    TP_SET_DECL(str_zzz7)
    TP_SET_DECL(str_zzz8)
    TP_SET_DECL(str_zzz9)
    TP_SET_DECL(str_zzz10)
    TP_SET_DECL(str_zzz11)
    TP_SET_DECL(str_zzz12)
    TP_SET_DECL(str_zzz13)
    TP_SET_DECL(str_zzz14)
    TP_SET_DECL(str_zzz15)
    TP_SET_DECL(str_zzz16)
    TP_SET_DECL(str_zzz17)
    TP_SET_DECL(str_zzz18)
    TP_SET_DECL(weapon_carry_anim)
    TP_SET_DECL(weapon_use_anim)
    TP_SET_DECL(is_animated)
    TP_SET_DECL(is_animated_no_dir)
    TP_SET_DECL(is_animation)
    TP_SET_DECL(is_monst)
    TP_SET_DECL(is_player)
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
    TP_SET_DECL(is_animated_can_vflip)
    TP_SET_DECL(is_blit_y_offset)
    TP_SET_DECL(is_small_shadow_caster)
    TP_SET_DECL(is_corridor)
    TP_SET_DECL(is_blit_off_center)
    TP_SET_DECL(is_boring)
    TP_SET_DECL(is_exit)
    TP_SET_DECL(is_entrance)
    TP_SET_DECL(move_delay_hundredths)
    TP_SET_DECL(weapon_use_delay_hundredths)
    TP_SET_DECL(for_collision_use_box)
    TP_SET_DECL(for_collision_use_circle)
    TP_SET_DECL(weapon_damage)
    TP_SET_DECL(is_projectile)
    TP_SET_DECL(is_explosion)
    TP_SET_DECL(is_combustable)
    TP_SET_DECL(is_spikes)
    TP_SET_DECL(collision_priority)
    TP_SET_DECL(weapon_use_distance)
    TP_SET_DECL(is_weapon_carry_anim)
    TP_SET_DECL(is_weapon_use_effect)
    TP_SET_DECL(is_weapon)
    TP_SET_DECL(is_outlined)
    TP_SET_DECL(is_shadow_caster)
    TP_SET_DECL(is_animated_can_hflip)
    TP_SET_DECL(z_depth)
    TP_SET_DECL(is_movable)
    TP_SET_DECL(is_movement_blocking)
    TP_SET_DECL(is_key)
    TP_SET_DECL(is_wall)
    TP_SET_DECL(is_floor)
    TP_SET_DECL(is_water)
    TP_SET_DECL(is_lava)

    {"tp_update",
        (PyCFunction)tp_update_,
        METH_VARARGS | METH_KEYWORDS,
        ""},

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
python_m_y_module_create (void)
{_
   PyObject *m = PyModule_Create(&python_c_MODULE);
   if (! m) {
        PyErr_Print();
        DIE("python init");
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
    DIE("python error");
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

    PyRun_SimpleString(stdOutErr);
    PyRun_SimpleString(str);

    PyObject *catcher = PyObject_GetAttrString(pModule, "catchOutErr");
    PyObject *output = PyObject_GetAttrString(catcher, "value");

    char *text = py_obj_to_str(output);
    if (text) {
        strchopc(text, '\n');
        CON("%s", text);
        myfree(text);
    }
    py_err();
}

static void py_add_to_path (const char *path)
{_
    PyObject *py_cur_path, *py_item;
    char *new_path;
    int wc_len, i;
    wchar_t *wc_new_path;
    char *item;

    LOG("- %s", path);

 /*
    LOG("Current system python path:");
     */

    new_path = dupstr(path, __FUNCTION__);
    py_cur_path = PySys_GetObject("path");

    for (i = 0; i < PyList_Size(py_cur_path); i++) {
#ifdef _WIN32
        char *tmp = strappend(new_path, ";");
#else
        char *tmp = strappend(new_path, ":");
#endif
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

        //LOG("  %s", item);

        tmp = strappend(new_path, item);
        myfree(new_path);
        new_path = tmp;

        myfree(item);
    }

    /* Convert to wide chars. */
    wc_len = sizeof(wchar_t) * (strlen(new_path) + 1);

    wc_new_path = (wchar_t *) myzalloc(wc_len, "wchar str");
    if (!wc_new_path) {
        DIE("path alloc fail");
    }

    // LOG("Set python path: %s", new_path);

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

    x /= (double) ASCII_WIDTH;
    y /= (double) ASCII_HEIGHT;

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

    x *= (double) ASCII_WIDTH;
    y *= (double) ASCII_HEIGHT;

    return (Py_BuildValue("dd", x, y));
}

static void python_add_consts (void)
{_
    PyModule_AddStringConstant(zx_mod, "VERSION", VERSION);

    PyModule_AddIntConstant(zx_mod, "ASCII_WIDTH", ASCII_WIDTH);
    PyModule_AddIntConstant(zx_mod, "ASCII_HEIGHT", ASCII_HEIGHT);

    PyModule_AddIntConstant(zx_mod, "MAP_WIDTH", MAP_WIDTH);
    PyModule_AddIntConstant(zx_mod, "MAP_HEIGHT", MAP_HEIGHT);

    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_FLOOR", MAP_DEPTH_FLOOR);
    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_LAVA", MAP_DEPTH_LAVA);
    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_WATER", MAP_DEPTH_WATER);
    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_WALLS", MAP_DEPTH_WALLS);
    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_MONST", MAP_DEPTH_MONST);
    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_ITEM", MAP_DEPTH_ITEM);
    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_EXIT", MAP_DEPTH_EXIT);
    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_PLAYER", MAP_DEPTH_PLAYER);
    PyModule_AddIntConstant(zx_mod, "MAP_DEPTH_WEAPON", MAP_DEPTH_WEAPON);

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

void python_init (char *argv[])
{_
#if 0
    PyRun_SimpleString("import sys; sys.path.append('./python3.5/')\n");
    PyRun_SimpleString("import sys; sys.path.append('./python3.5/lib-dynload')\n");
#endif
#ifdef __WIN32
     _putenv_s("PYTHONPATH", "python/;python3.5/;python3.5/lib-dynload;python3.5/site-packages");

    {
        int wc_len;
        wchar_t *wc_new_str;
        const char *str = argv[0];

        /* Convert to wide chars. */
        wc_len = sizeof(wchar_t) * (strlen(str) + 1);

        wc_new_str = (wchar_t *) myzalloc(wc_len, "wchar str");
        if (!wc_new_str) {
            DIE("program name alloc fail");
        }

        LOG("Calling Py_SetProgramName: \"%s\"", str);

        mbstowcs(wc_new_str, str, wc_len);
        Py_SetProgramName(wc_new_str);
        myfree(wc_new_str);
    }
#endif

    LOG("Calling PyImport_AppendInittab zx module");
    PyImport_AppendInittab("zx", python_m_y_module_create);

    LOG("Calling Py_Initialize");
    Py_Initialize();

    LOG("Adding to python path:");
    py_add_to_path(GFX_PATH);
    py_add_to_path(DATA_PATH);
    py_add_to_path(PYTHON_PATH);

#ifdef __APPLE__
    py_add_to_path("/Library/Frameworks/Python.framework/Versions/3.5/lib/python3.5/site-packages/");
#endif

    LOG("Calling PyImport_ImportModule for zx module");

    zx_mod = PyImport_ImportModule("zx");
    if (!zx_mod) {
        py_err();
        DIE("module zx import failed");
    }

    python_add_consts();

    LOG("Calling PyImport_ImportModule for init module");

    zx_mod = PyImport_ImportModule("init");
    if (!zx_mod) {
        py_err();
        DIE("module init import failed");
    }
}

void python_fini (void)
{_
   Py_Finalize();
}
