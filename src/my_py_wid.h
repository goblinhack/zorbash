/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_PY_WID_H_
#define _MY_PY_WID_H_

#include <Python.h>

PyObject *wid_new_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_destroy_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_new_scrollbar_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_tooltip_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_tooltip2_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_tiles_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_pos_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_pos_pct_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_text_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_color_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_name_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_tex_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_raise_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_lower_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_update_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_cursor_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_do_not_lower_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_do_not_raise_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_ignore_events_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_focusable_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_movable_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_movable_bounded_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_movable_no_user_scroll_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_movable_horiz_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_set_movable_vert_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_get_size_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_get_size_pct_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_get_pos_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_get_pos_pct_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_get_parent_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *wid_get_top_parent_(PyObject *obj, PyObject *args, PyObject *keywds);

#define WID_PROTO(__fn__)                                                   \
PyObject *__fn__ ## _ (PyObject *obj, PyObject *args, PyObject *keywds);

#define WID_DECL(__fn__)                                                    \
    {#__fn__,                                                               \
     (PyCFunction)__fn__ ## _,                                              \
     METH_VARARGS | METH_KEYWORDS,                                          \
     "call " #__fn__ " in a wid"},                                          \

WID_PROTO(wid_move_to_horiz_vert_pct_in)
WID_PROTO(wid_move_to_abs_centered_in)
WID_PROTO(wid_move_to_centered_in)
WID_PROTO(wid_move_delta_pct_in)
WID_PROTO(wid_move_to_abs_in)
WID_PROTO(wid_move_delta_in)
WID_PROTO(wid_move_to_pct_centered_in)
WID_PROTO(wid_move_to_abs_poffset_in)
WID_PROTO(wid_move_to_pct_in)

WID_PROTO(wid_move_delta)
WID_PROTO(wid_move_delta_pct)
WID_PROTO(wid_move_to_abs)
WID_PROTO(wid_move_to_abs_centered)
WID_PROTO(wid_move_to_pct)
WID_PROTO(wid_move_to_pct_centered)
WID_PROTO(wid_move_to_vert_pct_in)
WID_PROTO(wid_move_to_horiz_pct_in)

WID_PROTO(wid_move_to_vert_pct)
WID_PROTO(wid_move_to_horiz_pct)

WID_PROTO(wid_move_to_bottom)
WID_PROTO(wid_move_to_left)
WID_PROTO(wid_move_to_right)
WID_PROTO(wid_move_to_top)
WID_PROTO(wid_move_end)

WID_PROTO(wid_destroy_in)
WID_PROTO(wid_visible)
WID_PROTO(wid_hide)
WID_PROTO(wid_toggle_hidden)
WID_PROTO(wid_mouse_hide)

WID_PROTO(wid_update)
WID_PROTO(wid_raise)
WID_PROTO(wid_lower)
WID_PROTO(wid_scroll_text)
WID_PROTO(wid_set_focus)
WID_PROTO(wid_set_shape_square);
WID_PROTO(wid_set_shape_none);
WID_PROTO(wid_set_shape_box);
WID_PROTO(wid_set_active)
WID_PROTO(wid_focus_lock)
WID_PROTO(wid_animate)

WID_PROTO(wid_set_on_key_down)
WID_PROTO(wid_set_on_key_up)
WID_PROTO(wid_set_on_joy_button)
WID_PROTO(wid_set_on_m_down)
WID_PROTO(wid_set_on_m_motion)
WID_PROTO(wid_set_on_m_focus_b)
WID_PROTO(wid_set_on_m_focus_e)
WID_PROTO(wid_set_on_m_over_b)
WID_PROTO(wid_set_on_m_over_e)
WID_PROTO(wid_set_on_m_up)
WID_PROTO(wid_set_on_destroy)
WID_PROTO(wid_set_on_destroy_b)
WID_PROTO(wid_set_on_tick)
#endif
