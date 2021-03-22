//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PY_THING_H_
#define _MY_PY_THING_H_
#include <Python.h>

PyObject *thing_set_health(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_health(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_health(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_health(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_health_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_health_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_health_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_health_max(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_stamina(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_stamina(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_stamina(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_stamina(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_stamina_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_stamina_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_stamina_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_stamina_max(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_current_damage(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_current_damage(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_current_damage(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_current_damage(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_get_name(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_skill_activate(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_skill_deactivate(PyObject *obj, PyObject *args, PyObject *keywds);

#endif
