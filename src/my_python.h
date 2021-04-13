//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PYTHON_H_
#define _MY_PYTHON_H_

#include "my_point.h"
#include <Python.h>

PyObject *abs_to_pct_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *map_load_level_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *map_load_room_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *pct_to_abs_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_add_module(const char *mod);
PyObject *py_obj_attr(const PyObject *py_str, const char *attr);
PyObject *sound_load_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *music_load_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *sound_play_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *sound_play_channel_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *music_play_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tex_load_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *text_size_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tile_load_arr_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tile_load_arr_sprites_(PyObject *obj, PyObject *args, PyObject *keywds);
char *py_obj_attr_str(const PyObject *py_obj, const char *attr);
char *py_obj_to_str(const PyObject *py_str);
double py_obj_attr_double(const PyObject *py_obj, const char *attr);
double py_obj_to_double(PyObject *py_obj);
void py_call_void(const char *name);
void py_call_void_fn(const char *module, const char *name, int v1);
void py_call_void_fn(const char *module, const char *name, int v1, int v2);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8);
void py_call_void_fn(const char *module, const char *name, unsigned int v1);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int v5);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int v5, unsigned int v6);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7, unsigned int v8);
int py_obj_attr_int(const PyObject *py_obj, const char *attr);
int py_obj_to_int(PyObject *py_obj);
std::string py_obj_to_string(const PyObject *py_str);
uint64_t py_obj_attr_uint64(const PyObject *py_obj, const char *attr);
uint64_t py_obj_to_uint64(PyObject *py_obj);
void py_err(void);
void py_exec(const char *str);
void py_trace(void);
void python_fini(void);
void python_init(char *argv[]);

#define PY_PROTO(__fn__)                                                    \
PyObject *__fn__ ## _ (PyObject *obj, PyObject *args, PyObject *keywds);

#define PY_DECL(__fn__)                                                     \
    {#__fn__,                                                               \
     (PyCFunction)__fn__ ## _,                                              \
     METH_VARARGS | METH_KEYWORDS,                                          \
     "call " #__fn__ " "},                                                  \

#define PY_BODY_DOUBLE_DOUBLE_INT_FN(__fn__, n1, n2, n3)                        \
PyObject *__fn__ ## _ (PyObject *obj, PyObject *args, PyObject *keywds)         \
{	                                                                        \
    double d1 = 0;                                                              \
    double d2 = 0;                                                              \
    int i1 = 0;                                                                 \
	                                                                        \
    static char *kwlist[] = {#n1, #n2, #n3, 0};                                 \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddi", kwlist,               \
                                     &d1, &d2, &i1)) {	                        \
        Py_RETURN_FALSE;                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        ERR("%s, missing class", __FUNCTION__);	                                \
        Py_RETURN_FALSE;                                                        \
    }	                                                                        \
	                                                                        \
    (__fn__)(d1, d2, i1);                                                       \
	                                                                        \
    Py_RETURN_TRUE;	                                                        \
}	                                                                        \

#define PY_BODY_DOUBLE_DOUBLE_FN(__fn__, n1, n2)                                \
PyObject *__fn__ ## _ (PyObject *obj, PyObject *args, PyObject *keywds)         \
{	                                                                        \
    double d1 = 0;                                                              \
    double d2 = 0;                                                              \
	                                                                        \
    static char *kwlist[] = {#n1, #n2, 0};                                      \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist,                \
                                     &d1, &d2)) {	                        \
        Py_RETURN_FALSE;                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        ERR("%s, missing class", __FUNCTION__);	                                \
        Py_RETURN_FALSE;                                                        \
    }	                                                                        \
	                                                                        \
    (__fn__)(d1, d2);                                                           \
	                                                                        \
    Py_RETURN_TRUE;	                                                        \
}	                                                                        \

#define PY_BODY_DOUBLE_FN(__fn__, n1)                                           \
PyObject *__fn__ ## _ (PyObject *obj, PyObject *args, PyObject *keywds)         \
{	                                                                        \
    double d1 = 0;                                                              \
	                                                                        \
    static char *kwlist[] = {"wid_id", #n1, 0};                                 \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,                 \
                                     &d1)) {	                                \
        Py_RETURN_FALSE;                                                        \
    }	                                                                        \
	                                                                        \
    (__fn__)(d1);                                                               \
	                                                                        \
    Py_RETURN_TRUE;	                                                        \
}	                                                                        \

#define PY_BODY_INT_INT_INT_FN(__fn__, n1, n2, n3)                              \
PyObject *__fn__ ## _ (PyObject *obj, PyObject *args, PyObject *keywds)         \
{	                                                                        \
    int n1 = 0;                                                                 \
    int n2 = 0;                                                                 \
    int n3 = 0;                                                                 \
	                                                                        \
    static char *kwlist[] = {#n1, #n2, #n3, 0};                                 \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iii", kwlist,               \
                                     &n1, &n2, &n3)) {	                        \
        Py_RETURN_FALSE;                                                        \
    }	                                                                        \
	                                                                        \
    (__fn__)(n1, n2, n3);                                                       \
	                                                                        \
    Py_RETURN_TRUE;	                                                        \
}	                                                                        \

#define PY_BODY_INT_FN(__fn__, n1)                                              \
PyObject *__fn__ ## _ (PyObject *obj, PyObject *args, PyObject *keywds)         \
{	                                                                        \
    int n1 = 0;                                                                 \
	                                                                        \
    static char *kwlist[] = {(char*) #n1, 0};                                   \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist,                 \
                                     &n1)) {	                                \
        Py_RETURN_FALSE;                                                        \
    }	                                                                        \
	                                                                        \
    (__fn__)(n1);                                                               \
	                                                                        \
    Py_RETURN_TRUE;	                                                        \
}	                                                                        \

#define PY_BODY_VOID_FN(__fn__)                                                 \
PyObject *__fn__ ## _ (PyObject *obj, PyObject *args, PyObject *keywds)         \
{	                                                                        \
    (__fn__)();                                                                 \
	                                                                        \
    Py_RETURN_TRUE;	                                                        \
}	                                                                        \

//
// Borrowed from https://github.com/holtrop/pysdl2
//
#define PYFUNC(name, desc) \
    const char name ## _doc[] = desc; \
    PyObject *pysdl_ ## name(PyObject *self, PyObject *args)

#define PYDECL(name) \
    extern const char name ## _doc[]; \
    extern PyObject *pysdl_ ## name(PyObject *self, PyObject *args);

#define PYFUNC_REF(name) {#name, pysdl_ ## name, METH_VARARGS, name ## _doc}

void PY_LOG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
void PY_DBG(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
#endif
