//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_PYTHON_HPP_
#define _MY_PYTHON_HPP_

#include <Python.h>
#include <list>
#include <string>
#include <vector>

#include "my_format_str_attribute.hpp"

PyObject *con_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *die_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *err_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *log_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *map_load_room_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *map_load_skill_tree_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *map_load_spell_tree_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *music_load_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *music_play_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *music_halt_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_non_pcg_random_range_inclusive(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_pcg_random_range_inclusive(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *puts_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_add_module(const char *mod);
PyObject *py_obj_attr(const PyObject *py_str, const char *attr);
PyObject *sound_load_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *sound_play_channel_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *sound_play_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tex_load_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *text_size_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_sound_play_channel_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_sound_play_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tile_load_arr_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tile_load_arr_sprites_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *topcon_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d10000(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d1000(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d100(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d10(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d11(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d12(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d13(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d14(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d15(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d16(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d17(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d18(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d19(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d20(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d2(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d3(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d4(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d50(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d5(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d6(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d7(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d8(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *py_d9(PyObject *obj, PyObject *args, PyObject *keywds);

char *py_obj_attr_str(const PyObject *py_obj, const char *attr);
char *py_obj_to_string(const PyObject *py_str);

double py_obj_attr_double(const PyObject *py_obj, const char *attr);
double py_obj_to_double(PyObject *py_obj);

int py_obj_attr_int(const PyObject *py_obj, const char *attr);
int py_obj_to_bool(PyObject *py_obj);
int py_obj_to_int(PyObject *py_obj);

PyMODINIT_FUNC py_my_module_create(void);

std::string py_obj_to_std_string(const PyObject *py_str);

uint64_t py_obj_attr_uint64(const PyObject *py_obj, const char *attr);
uint64_t py_obj_to_uint64(PyObject *py_obj);

void py_add_to_path(const char *path);
void py_err(void);
void py_exec(const char *str);
void py_fini(void);
void py_init(char *argv[]);
void py_my_module_add_stat_consts(void);
void py_trace(void);

void py_call_void(const char *name);
void py_call_void_fn(const char *module, const char *name, int v1);
void py_call_void_fn(const char *module, const char *name, int v1, int v2);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6);

void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7,
                     int v8);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7,
                     int v8, int v9);
void py_call_void_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7,
                     int v8, int v9, int v10);
void py_call_void_fn(const char *module, const char *name, unsigned int v1);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5, unsigned int v6);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7, unsigned int v8);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7, unsigned int v8,
                     unsigned int v9);
void py_call_void_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7, unsigned int v8,
                     unsigned int v9, unsigned int v10);

bool py_call_bool(const char *name);
bool py_call_bool_fn(const char *module, const char *name, int v1);
bool py_call_bool_fn(const char *module, const char *name, int v1, int v2);
bool py_call_bool_fn(const char *module, const char *name, int v1, int v2, int v3);
bool py_call_bool_fn(const char *module, const char *name, int v1, int v2, int v3, int v4);
bool py_call_bool_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5);
bool py_call_bool_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6);
bool py_call_bool_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7);
bool py_call_bool_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7,
                     int v8);
bool py_call_bool_fn(const char *module, const char *name, unsigned int v1);
bool py_call_bool_fn(const char *module, const char *name, unsigned int v1, unsigned int v2);
bool py_call_bool_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3);
bool py_call_bool_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4);
bool py_call_bool_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5);
bool py_call_bool_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5, unsigned int v6);
bool py_call_bool_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7);
bool py_call_bool_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                     unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7, unsigned int v8);

int py_call_int(const char *name);
int py_call_int_fn(const char *module, const char *name, int v1);
int py_call_int_fn(const char *module, const char *name, int v1, int v2);
int py_call_int_fn(const char *module, const char *name, int v1, int v2, int v3);
int py_call_int_fn(const char *module, const char *name, int v1, int v2, int v3, int v4);
int py_call_int_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5);
int py_call_int_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6);
int py_call_int_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7);
int py_call_int_fn(const char *module, const char *name, int v1, int v2, int v3, int v4, int v5, int v6, int v7,
                   int v8);
int py_call_int_fn(const char *module, const char *name, unsigned int v1);
int py_call_int_fn(const char *module, const char *name, unsigned int v1, unsigned int v2);
int py_call_int_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3);
int py_call_int_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                   unsigned int v4);
int py_call_int_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                   unsigned int v4, unsigned int v5);
int py_call_int_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                   unsigned int v4, unsigned int v5, unsigned int v6);
int py_call_int_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                   unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7);
int py_call_int_fn(const char *module, const char *name, unsigned int v1, unsigned int v2, unsigned int v3,
                   unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7, unsigned int v8);

std::list< std::string > py_call_std_list_string_fn(const char *module, const char *name, int val1, int val2,
                                                    int val3, int val4);

std::vector< std::string > py_call_std_vector_string_fn(const char *module, const char *name, int val1, int val2,
                                                        int val3, int val4);

#define PY_PROTO(__fn__) PyObject *__fn__##_(PyObject *obj, PyObject *args, PyObject *keywds);

#define PY_DECL(__fn__) {#__fn__, (PyCFunction) __fn__##_, METH_VARARGS | METH_KEYWORDS, "call " #__fn__ " "},

#define PY_BODY_DOUBLE_DOUBLE_INT_FN(__fn__, n1, n2, n3)                                                             \
  PyObject *__fn__##_(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
  {                                                                                                                  \
    double d1 = 0;                                                                                                   \
    double d2 = 0;                                                                                                   \
    int    i1 = 0;                                                                                                   \
                                                                                                                     \
    static char *kwlist[] = {#n1, #n2, #n3, 0};                                                                      \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "ddi", kwlist, &d1, &d2, &i1)) {                                 \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! py_class) {                                                                                                \
      ERR("%s, missing class", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    (__fn__)(d1, d2, i1);                                                                                            \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define PY_BODY_DOUBLE_DOUBLE_FN(__fn__, n1, n2)                                                                     \
  PyObject *__fn__##_(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
  {                                                                                                                  \
    double d1 = 0;                                                                                                   \
    double d2 = 0;                                                                                                   \
                                                                                                                     \
    static char *kwlist[] = {#n1, #n2, 0};                                                                           \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &d1, &d2)) {                                       \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! py_class) {                                                                                                \
      ERR("%s, missing class", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    (__fn__)(d1, d2);                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define PY_BODY_DOUBLE_FN(__fn__, n1)                                                                                \
  PyObject *__fn__##_(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
  {                                                                                                                  \
    double d1 = 0;                                                                                                   \
                                                                                                                     \
    static char *kwlist[] = {"wid_id", #n1, 0};                                                                      \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &d1)) {                                             \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    (__fn__)(d1);                                                                                                    \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define PY_BODY_INT_INT_INT_FN(__fn__, n1, n2, n3)                                                                   \
  PyObject *__fn__##_(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
  {                                                                                                                  \
    int n1 = 0;                                                                                                      \
    int n2 = 0;                                                                                                      \
    int n3 = 0;                                                                                                      \
                                                                                                                     \
    static char *kwlist[] = {#n1, #n2, #n3, 0};                                                                      \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "iii", kwlist, &n1, &n2, &n3)) {                                 \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    (__fn__)(n1, n2, n3);                                                                                            \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define PY_BODY_INT_FN(__fn__, n1)                                                                                   \
  PyObject *__fn__##_(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
  {                                                                                                                  \
    int n1 = 0;                                                                                                      \
                                                                                                                     \
    static char *kwlist[] = {(char *) #n1, 0};                                                                       \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &n1)) {                                             \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    TRACE_NO_INDENT();                                                                                               \
    (__fn__)(n1);                                                                                                    \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define PY_BODY_VOID_FN(__fn__)                                                                                      \
  PyObject *__fn__##_(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    (__fn__)();                                                                                                      \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

//
// Borrowed from https://github.com/holtrop/pysdl2
//
#define PYFUNC(name, desc)                                                                                           \
  const char name##_doc[] = desc;                                                                                    \
  PyObject  *pysdl_##name(PyObject *self, PyObject *args)

#define PYDECL(name)                                                                                                 \
  extern const char name##_doc[];                                                                                    \
  extern PyObject  *pysdl_##name(PyObject *self, PyObject *args);

#define PYFUNC_REF(name)                                                                                             \
  {                                                                                                                  \
#name, pysdl_##name, METH_VARARGS, name##_doc                                                                    \
  }

void PY_LOG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void PY_DBG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

extern PyObject *my_mod;
#endif
