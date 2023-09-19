//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_PY_GAME_HPP_
#define _MY_PY_GAME_HPP_

#include <Python.h>

// begin sort marker1 {
PyObject *game_set_currently_saving_snapshot(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_reset_state_change(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_remake_actionbar(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_remake_buffbox(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_remake_debuffbox(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_remake_inventory(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_remake_rightbar(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_remake_skillbox(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_remake_spellbox(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_save_snapshot(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_update_inventory_thing_over(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_update_inventory_thing_select(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_set_request_to_update_same_level(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_currently_saving_snapshot(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_reset_state_change(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_remake_actionbar(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_remake_buffbox(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_remake_debuffbox(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_remake_inventory(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_remake_rightbar(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_remake_skillbox(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_remake_spellbox(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_save_snapshot(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_update_inventory_thing_over(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_update_inventory_thing_select(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *game_unset_request_to_update_same_level(PyObject *obj, PyObject *args, PyObject *keywds);
// end sort marker1 }

#endif
