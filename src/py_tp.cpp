/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_python.h"
#include "my_py_tp.h"
#include "my_thing.h"

PyObject *tp_load_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    PyObject *py_class = 0;

    static char *kwlist[] = {(char*) "tp", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O", kwlist, &py_class)) {
        return (0);
    }

    if (!py_class) {
        ERR("tp_load, missing name attr");
        return (0);
    }

    char *tp_name = py_obj_attr_str(py_class, "name");
    if (!tp_name) {
        ERR("tp_load, missing tp name");
        return (0);
    }

    static int id;
    id++;
    tp_load(id, tp_name);

    myfree(tp_name);

    Py_RETURN_NONE;
}

#define TP_BODY_SET_STRING(__field__)                                           \
PyObject *tp_set_ ## __field__ (PyObject *obj, PyObject *args, PyObject *keywds)\
{	                                                                        \
    PyObject *py_class = 0;	                                                \
    char *tp_name = 0;	                                                        \
    char *value = 0;	                                                        \
    Tpp tp;                                                                  \
	                                                                        \
    static char *kwlist[] = {(char*) "class", (char*) "value", 0};	        \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|s", kwlist, &py_class,    \
                                     &value)) {	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        ERR("%s, missing class", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!value) {	                                                        \
        ERR("%s, missing value", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    tp_name = py_obj_attr_str(py_class, "name");	                        \
    if (!tp_name) {	                                                        \
        ERR("%s, missing tp name", __FUNCTION__);	                        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    DBG("python-to-c: %s(%s -> \"%s\")", __FUNCTION__, tp_name, value);	        \
	                                                                        \
    tp = tp_find(tp_name);	                                                \
    if (!tp) {	                                                                \
        ERR("%s, cannot find tp %s", __FUNCTION__, tp_name);	                \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    tp->__field__ = std::string(value ? value : "");	                        \
    value = 0;	                                                                \
	                                                                        \
done:	                                                                        \
    if (tp_name) {	                                                        \
        myfree(tp_name);	                                                \
    }	                                                                        \
	                                                                        \
    Py_RETURN_NONE;	                                                        \
}	                                                                        \

#define TP_BODY_SET_STRING_FN(__field__, __fn__)                                \
PyObject *tp_set_ ## __field__ (PyObject *obj, PyObject *args, PyObject *keywds)\
{	                                                                        \
    PyObject *py_class = 0;	                                                \
    char *tp_name = 0;	                                                        \
    char *value = 0;	                                                        \
    Tpp tp;                                                                     \
	                                                                        \
    static char *kwlist[] = {(char*) "class", (char*) "value", 0};	        \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|s", kwlist, &py_class,    \
                                     &value)) {	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        ERR("%s, missing class", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!value) {	                                                        \
        ERR("%s, missing value", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    tp_name = py_obj_attr_str(py_class, "name");	                        \
    if (!tp_name) {	                                                        \
        ERR("%s, missing tp name", __FUNCTION__);	                        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    DBG("python-to-c: %s(%s -> \"%s\")", __FUNCTION__, tp_name, value);	        \
	                                                                        \
    tp = tp_find(tp_name);	                                                \
    if (!tp) {	                                                                \
        ERR("%s, cannot find tp %s", __FUNCTION__, tp_name);	                \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    tp->__field__ = std::string(value ? value : "");	                        \
    value = 0;	                                                                \
    (__fn__)(tp);                                                               \
	                                                                        \
done:	                                                                        \
    if (tp_name) {	                                                        \
        myfree(tp_name);	                                                \
    }	                                                                        \
	                                                                        \
    Py_RETURN_NONE;	                                                        \
}	                                                                        \

#define TP_BODY_SET_ENUM(__field__, __str2val__)                                \
PyObject *tp_set_ ## __field__ (PyObject *obj, PyObject *args, PyObject *keywds)\
{	                                                                        \
    PyObject *py_class = 0;	                                                \
    char *tp_name = 0;	                                                        \
    char *value = 0;	                                                        \
    Tpp tp;                                                                     \
	                                                                        \
    static char *kwlist[] = {(char*) "class", (char*) "value", 0};	        \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|s", kwlist, &py_class,    \
                                     &value)) {	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        ERR("%s, missing class", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!value) {	                                                        \
        ERR("%s, missing value", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    tp_name = py_obj_attr_str(py_class, "name");	                        \
    if (!tp_name) {	                                                        \
        ERR("%s, missing tp name", __FUNCTION__);	                        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    tp = tp_find(tp_name);	                                                \
    if (!tp) {	                                                                \
        ERR("%s, cannot find tp %s", __FUNCTION__, tp_name);	                \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    tp->__field__ = (__str2val__)(value);                                       \
    if (tp->__field__ == (__typeof__(tp->__field__))-1) {                       \
        ERR("%s, cannot find enum %s", __FUNCTION__, value);	                \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    DBG("python-to-c: %s(%s -> \"%s\"[%d])", __FUNCTION__, tp_name, value,      \
        tp->__field__);	                                                        \
	                                                                        \
    value = 0;	                                                                \
	                                                                        \
done:	                                                                        \
    if (tp_name) {	                                                        \
        myfree(tp_name);	                                                \
    }	                                                                        \
	                                                                        \
    Py_RETURN_NONE;	                                                        \
}	                                                                        \

#define TP_BODY_SET_INT(__field__)                                              \
PyObject *tp_set_ ## __field__ (PyObject *obj, PyObject *args, PyObject *keywds)\
{	                                                                        \
    PyObject *py_class = 0;	                                                \
    char *tp_name = 0;	                                                        \
    int value = 0;	                                                        \
    Tpp tp;                                                                     \
	                                                                        \
    static char *kwlist[] = {(char*) "class", (char*) "value", 0};	        \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|i", kwlist, &py_class,    \
                                     &value)) {	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        ERR("%s, missing class", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    tp_name = py_obj_attr_str(py_class, "name");	                        \
    if (!tp_name) {	                                                        \
        ERR("%s, missing tp name", __FUNCTION__);	                        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    DBG("python-to-c: %s(%s -> %d)", __FUNCTION__, tp_name, value);	        \
	                                                                        \
    tp = tp_find(tp_name);	                                                \
    if (!tp) {	                                                                \
        ERR("%s, cannot find tp %s", __FUNCTION__, tp_name);	                \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    tp->__field__ = value;                                                      \
	                                                                        \
done:	                                                                        \
    if (tp_name) {	                                                        \
        myfree(tp_name);	                                                \
    }	                                                                        \
	                                                                        \
    Py_RETURN_NONE;	                                                        \
}	                                                                        \

#define TP_BODY_SET_DOUBLE(__field__)                                           \
PyObject *tp_set_ ## __field__ (PyObject *obj, PyObject *args, PyObject *keywds)\
{	                                                                        \
    PyObject *py_class = 0;	                                                \
    char *tp_name = 0;	                                                        \
    double value = 0;	                                                        \
    Tpp tp;                                                                     \
	                                                                        \
    static char *kwlist[] = {(char*) "class", (char*) "value", 0};	        \
	                                                                        \
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|d", kwlist, &py_class,    \
                                     &value)) {	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    if (!py_class) {	                                                        \
        ERR("%s, missing class", __FUNCTION__);	                                \
        return (0);	                                                        \
    }	                                                                        \
	                                                                        \
    tp_name = py_obj_attr_str(py_class, (char*) "name");	                \
    if (!tp_name) {	                                                        \
        ERR("%s, missing tp name", __FUNCTION__);	                        \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    DBG("python-to-c: %s(%s -> %g)", __FUNCTION__, tp_name, value);	        \
	                                                                        \
    tp = tp_find(tp_name);	                                                \
    if (!tp) {	                                                                \
        ERR("%s, cannot find tp %s", __FUNCTION__, tp_name);	                \
        goto done;	                                                        \
    }	                                                                        \
	                                                                        \
    tp->__field__ = value;                                                      \
	                                                                        \
done:	                                                                        \
    if (tp_name) {	                                                        \
        myfree(tp_name);	                                                \
    }	                                                                        \
	                                                                        \
    Py_RETURN_NONE;	                                                        \
}	                                                                        \

static PyObject *tp_set_tile_dir (PyObject *obj,
                                  PyObject *args,
                                  PyObject *keywds,
                                  int dir)
{	
    PyObject *py_class = 0;	
    char *tp_name = 0;	
    char *tile = 0;	
    char *fg = 0;	
    char *bg = 0;	
    char *fg_color = 0;	
    char *bg_color = 0;	
    int delay_ms = 0;
    int is_moving = 0;
    int is_jumping = 0;
    int begin_jump = 0;
    int is_join_lock = 0;
    int is_join_horiz = 0;
    int is_join_vert = 0;
    int is_join_node = 0;
    int is_join_left = 0;
    int is_join_right = 0;
    int is_join_top = 0;
    int is_join_bot = 0;
    int is_join_l90 = 0;
    int is_join_l180 = 0;
    int is_join_l = 0;
    int is_join_l270 = 0;
    int is_join_t = 0;
    int is_join_t90 = 0;
    int is_join_t180 = 0;
    int is_join_t270 = 0;
    int is_join_x = 0;
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;
    int none = 0;
    int is_yyy5 = 0;
    int is_yyy6 = 0;
    int is_yyy7 = 0;
    int is_yyy8 = 0;
    int is_yyy9 = 0;
    int is_yyy10 = 0;
    int is_hp_25_percent = 0;
    int is_hp_50_percent = 0;
    int is_hp_75_percent = 0;
    int is_hp_100_percent = 0;
    int is_submerged = 0;
    int is_sleeping = 0;
    int is_open = 0;
    int is_dead = 0;
    int is_bloodied = 0;
    int is_end_of_anim = 0;
    int is_dead_on_end_of_anim = 0;
	
    static char *kwlist[] = {
        (char*) "class",
        (char*) "tile",
        (char*) "fg",
        (char*) "bg",
        (char*) "fg_color",
        (char*) "bg_color",
        (char*) "delay_ms",
        (char*) "is_moving",
        (char*) "is_jumping",
        (char*) "begin_jump",
        (char*) "is_join_lock",
        (char*) "is_join_horiz",
        (char*) "is_join_vert",
        (char*) "is_join_node",
        (char*) "is_join_left",
        (char*) "is_join_right",
        (char*) "is_join_top",
        (char*) "is_join_bot",
        (char*) "is_join_l90",
        (char*) "is_join_l180",
        (char*) "is_join_l",
        (char*) "is_join_l270",
        (char*) "is_join_t",
        (char*) "is_join_t90",
        (char*) "is_join_t180",
        (char*) "is_join_t270",
        (char*) "is_join_x",
        (char*) "is_dir_left",
        (char*) "is_dir_right",
        (char*) "is_dir_up",
        (char*) "is_dir_down",
        (char*) "is_dir_none",
        (char*) "is_yyy5",
        (char*) "is_yyy6",
        (char*) "is_yyy7",
        (char*) "is_yyy8",
        (char*) "is_yyy9",
        (char*) "is_yyy10",
        (char*) "is_hp_25_percent",
        (char*) "is_hp_50_percent",
        (char*) "is_hp_75_percent",
        (char*) "is_hp_100_percent",
        (char*) "is_submerged",
        (char*) "is_sleeping",
        (char*) "is_open",
        (char*) "is_dead",
        (char*) "is_bloodied",
        (char*) "is_end_of_anim",
        (char*) "is_dead_on_end_of_anim",
        0
    };
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds,
                                     "O|sssssiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
                                     kwlist, &py_class,
                                     &tile,
                                     &fg,
                                     &bg,
                                     &fg_color,
                                     &bg_color,
                                     &delay_ms,
                                     &is_moving,
                                     &is_jumping,
                                     &begin_jump,
                                     &is_join_lock,
                                     &is_join_horiz,
                                     &is_join_vert,
                                     &is_join_node,
                                     &is_join_left,
                                     &is_join_right,
                                     &is_join_top,
                                     &is_join_bot,
                                     &is_join_l90,
                                     &is_join_l180,
                                     &is_join_l,
                                     &is_join_l270,
                                     &is_join_t,
                                     &is_join_t90,
                                     &is_join_t180,
                                     &is_join_t270,
                                     &is_join_x,
                                     &left,
                                     &right,
                                     &up,
                                     &down,
                                     &none,
                                     &is_yyy5,
                                     &is_yyy6,
                                     &is_yyy7,
                                     &is_yyy8,
                                     &is_yyy9,
                                     &is_yyy10,
                                     &is_hp_25_percent,
                                     &is_hp_50_percent,
                                     &is_hp_75_percent,
                                     &is_hp_100_percent,
                                     &is_submerged,
                                     &is_sleeping,
                                     &is_open,
                                     &is_dead,
                                     &is_bloodied,
                                     &is_end_of_anim,
                                     &is_dead_on_end_of_anim
                                     )) {	
        return (0);	
    }	

    if (!py_class) {	
        ERR("%s, missing class", __FUNCTION__);	
        return (0);	
    }	
	
    Tpp tp;

    tp_name = py_obj_attr_str(py_class, "name");	
    if (!tp_name) {	
        DIE("%s, missing tp name", __FUNCTION__);	
    }	
	
    DBG("python-to-c: %s(%s -> \"%s\")", __FUNCTION__, tp_name, tile);	
	
    tp = tp_find(tp_name);	
    if (!tp) {	
        DIE("%s, cannot find tp %s", __FUNCTION__, tp_name);	
    }	
	
    static unsigned int index;
    index++;

    Tileinfomap *tiles;
    switch (dir) {
    case THING_DIR_NONE:
        tiles = &tp->tiles;
        break;
    case THING_DIR_DOWN:
        tiles = &tp->bot_tiles;
        break;
    case THING_DIR_UP:
        tiles = &tp->top_tiles;
        break;
    case THING_DIR_LEFT:
        tiles = &tp->left_tiles;
        break;
    case THING_DIR_RIGHT:
        tiles = &tp->right_tiles;
        break;
    case THING_DIR_TL:
        tiles = &tp->tl_tiles;
        break;
    case THING_DIR_BL:
        tiles = &tp->bl_tiles;
        break;
    case THING_DIR_TR:
        tiles = &tp->tr_tiles;
        break;
    case THING_DIR_BR:
        tiles = &tp->br_tiles;
        break;
    }

    if (is_join_horiz) {
        tiles = &tp->horiz_tiles;
    }
    if (is_join_vert) {
        tiles = &tp->vert_tiles;
    }
    if (is_join_node) {
        tiles = &tp->tiles;
    }
    if (is_join_left) {
        tiles = &tp->left_tiles;
    }
    if (is_join_right) {
        tiles = &tp->right_tiles;
    }
    if (is_join_top) {
        tiles = &tp->top_tiles;
    }
    if (is_join_bot) {
        tiles = &tp->bot_tiles;
    }
    if (is_join_l90) {
        tiles = &tp->l90_tiles;
    }
    if (is_join_l180) {
        tiles = &tp->l180_tiles;
    }
    if (is_join_l) {
        tiles = &tp->l_tiles;
    }
    if (is_join_l270) {
        tiles = &tp->l270_tiles;
    }
    if (is_join_t) {
        tiles = &tp->t_tiles;
    }
    if (is_join_t90) {
        tiles = &tp->t90_tiles;
    }
    if (is_join_t180) {
        tiles = &tp->t180_tiles;
    }
    if (is_join_t270) {
        tiles = &tp->t270_tiles;
    }
    if (is_join_x) {
        tiles = &tp->x_tiles;
    }

    auto t = std::make_shared< class Tileinfo >();
    auto result = tiles->insert(std::make_pair(index, t));

    if (result.second == false) {
        DIE("tile insert name [%s] failed", tile);
    }

    if (tile && *tile) {
        t->tile = tile_find(tile);
        if (!t->tile) {
            DIE("%s, cannot find tile %s for tp %s", __FUNCTION__, tile, tp_name);
        }
    } else {
        t->tile = nullptr;
    }

    t->tilename = std::string(tile ? tile : "");
    t->index = index;
    t->delay_ms = delay_ms;
    t->is_moving = is_moving;

    t->is_join_horiz = is_join_horiz;
    t->is_join_vert = is_join_vert;
    t->is_join_node = is_join_node;
    t->is_join_left = is_join_left;
    t->is_join_right = is_join_right;
    t->is_join_top = is_join_top;
    t->is_join_bot = is_join_bot;
    t->is_join_l90 = is_join_l90;
    t->is_join_l180 = is_join_l180;
    t->is_join_l = is_join_l;
    t->is_join_l270 = is_join_l270;
    t->is_join_t = is_join_t;
    t->is_join_t90 = is_join_t90;
    t->is_join_t180 = is_join_t180;
    t->is_join_t270 = is_join_t270;
    t->is_join_x = is_join_x;

    t->is_yyy5 = is_yyy5;
    t->is_yyy6 = is_yyy6;
    t->is_yyy7 = is_yyy7;
    t->is_yyy8 = is_yyy8;
    t->is_yyy9 = is_yyy9;
    t->is_yyy10 = is_yyy10;
    t->is_hp_25_percent = is_hp_25_percent;
    t->is_hp_50_percent = is_hp_50_percent;
    t->is_hp_75_percent = is_hp_75_percent;
    t->is_hp_100_percent = is_hp_100_percent;
    t->is_sleeping = is_sleeping;
    t->is_open = is_open;
    t->is_dead = is_dead;
    t->is_end_of_anim = is_end_of_anim;
    t->is_dead_on_end_of_anim = is_dead_on_end_of_anim;

    if (t->is_hp_25_percent ||
        t->is_hp_50_percent ||
        t->is_hp_75_percent ||
        t->is_hp_100_percent ) {
        tp->internal_has_hp_anim = true;
    }

    if (up) {
        if (left) {
            t->dir = THING_DIR_TL;
            t->internal_has_dir_anim = true;
        } else if (right) {
            t->dir = THING_DIR_TR;
            t->internal_has_dir_anim = true;
        } else {
            t->dir = THING_DIR_UP;
            t->internal_has_dir_anim = true;
        }
    } else if (down) {
        if (left) {
            t->dir = THING_DIR_BL;
            t->internal_has_dir_anim = true;
        } else if (right) {
            t->dir = THING_DIR_BR;
            t->internal_has_dir_anim = true;
        } else {
            t->dir = THING_DIR_DOWN;
            t->internal_has_dir_anim = true;
        }
    } else if (left) {
        t->dir = THING_DIR_LEFT;
        t->internal_has_dir_anim = true;
    } else if (right) {
        t->dir = THING_DIR_RIGHT;
        t->internal_has_dir_anim = true;
    } else if (none) {
        t->dir = THING_DIR_NONE;
        t->internal_has_dir_anim = true;
    }

    if (t->internal_has_dir_anim) {
        tp->internal_has_dir_anim = true;
    }
	
    if (tp_name) {	
        myfree(tp_name);	
    }	
	
    Py_RETURN_NONE;	
}	

PyObject *tp_set_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_NONE));
}
PyObject *tp_set_top_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_UP));
}
PyObject *tp_set_bot_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_DOWN));
}
PyObject *tp_set_left_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_LEFT));
}
PyObject *tp_set_right_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_RIGHT));
}
PyObject *tp_set_tl_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_TL));
}
PyObject *tp_set_tr_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_TR));
}
PyObject *tp_set_bl_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_BL));
}
PyObject *tp_set_br_tile (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    return (tp_set_tile_dir(obj, args, keywds, THING_DIR_BR));
}

TP_BODY_SET_INT(blit_top_off)
TP_BODY_SET_INT(blit_bot_off)
TP_BODY_SET_INT(blit_left_off)
TP_BODY_SET_INT(blit_right_off)
TP_BODY_SET_INT(is_movement_blocking)
TP_BODY_SET_STRING(name)
TP_BODY_SET_STRING(str_zzz1)
TP_BODY_SET_STRING(str_zzz2)
TP_BODY_SET_STRING(str_zzz3)
TP_BODY_SET_STRING(str_zzz4)
TP_BODY_SET_STRING(str_zzz5)
TP_BODY_SET_STRING(str_zzz6)
TP_BODY_SET_STRING(str_zzz7)
TP_BODY_SET_STRING(str_zzz8)
TP_BODY_SET_STRING(str_zzz9)
TP_BODY_SET_STRING(str_zzz10)
TP_BODY_SET_STRING(str_zzz11)
TP_BODY_SET_STRING(str_zzz12)
TP_BODY_SET_STRING(str_zzz13)
TP_BODY_SET_STRING(str_zzz14)
TP_BODY_SET_STRING(str_zzz15)
TP_BODY_SET_STRING(str_zzz16)
TP_BODY_SET_STRING(str_zzz17)
TP_BODY_SET_STRING(str_light_color)
TP_BODY_SET_STRING(weapon_carry_anim)
TP_BODY_SET_STRING(weapon_use_anim)
TP_BODY_SET_INT(gfx_animated)
TP_BODY_SET_INT(gfx_animated_no_dir)
TP_BODY_SET_INT(gfx_is_an_animation_only)
TP_BODY_SET_INT(is_door)
TP_BODY_SET_INT(is_lava)
TP_BODY_SET_INT(is_water)
TP_BODY_SET_INT(is_deep_water)
TP_BODY_SET_INT(is_monst)
TP_BODY_SET_INT(is_player)
TP_BODY_SET_INT(is_rrr1)
TP_BODY_SET_INT(is_rrr2)
TP_BODY_SET_INT(is_rrr3)
TP_BODY_SET_INT(is_rrr4)
TP_BODY_SET_INT(is_rrr5)
TP_BODY_SET_INT(is_rrr6)
TP_BODY_SET_INT(is_rrr7)
TP_BODY_SET_INT(is_rrr8)
TP_BODY_SET_INT(is_rrr9)
TP_BODY_SET_INT(is_rrr10)
TP_BODY_SET_INT(is_rrr11)
TP_BODY_SET_INT(is_rrr12)
TP_BODY_SET_INT(is_rrr13)
TP_BODY_SET_INT(is_rrr14)
TP_BODY_SET_INT(is_rrr15)
TP_BODY_SET_INT(is_rrr16)
TP_BODY_SET_INT(is_rrr17)
TP_BODY_SET_STRING(nutrition_hd)
TP_BODY_SET_STRING(bite_damage_hd)
TP_BODY_SET_INT(collision_check)
TP_BODY_SET_INT(attack_on_collision)
TP_BODY_SET_INT(is_water_dweller)
TP_BODY_SET_INT(collision_hit_priority)
TP_BODY_SET_DOUBLE(collision_radius)
TP_BODY_SET_INT(ai_delay_after_moving_ms)
TP_BODY_SET_INT(gfx_bounce_on_move)
TP_BODY_SET_INT(is_corpse_on_death)
TP_BODY_SET_INT(is_bleeder)
TP_BODY_SET_INT(is_meat_eater)
TP_BODY_SET_INT(is_made_of_meat)
TP_BODY_SET_INT(is_active)
TP_BODY_SET_INT(hunger_starving_at_health_pct)
TP_BODY_SET_INT(hunger_initial_health_at)
TP_BODY_SET_INT(hunger_at_health_pct)
TP_BODY_SET_INT(hunger_clock_freq_ms)
TP_BODY_SET_INT(ai_scent_distance)
TP_BODY_SET_INT(is_ripple)
TP_BODY_SET_INT(is_light_strength)
TP_BODY_SET_INT(is_dirt)
TP_BODY_SET_INT(is_blood)
TP_BODY_SET_INT(gfx_animated_can_vflip)
TP_BODY_SET_INT(gfx_small_shadow_caster)
TP_BODY_SET_INT(is_corridor)
TP_BODY_SET_INT(gfx_oversized_but_sitting_on_the_ground)
TP_BODY_SET_INT(is_boring)
TP_BODY_SET_INT(is_exit)
TP_BODY_SET_INT(is_entrance)
TP_BODY_SET_INT(gfx_is_floor_deco)
TP_BODY_SET_INT(gfx_is_wall_deco)
TP_BODY_SET_INT(move_speed_ms)
TP_BODY_SET_INT(weapon_use_delay_hundredths)
TP_BODY_SET_INT(collision_box)
TP_BODY_SET_INT(collision_circle)
TP_BODY_SET_INT(weapon_damage)
TP_BODY_SET_INT(is_projectile)
TP_BODY_SET_INT(is_explosion)
TP_BODY_SET_INT(is_combustable)
TP_BODY_SET_INT(weapon_use_distance)
TP_BODY_SET_INT(gfx_is_weapon_carry_anim_only)
TP_BODY_SET_INT(gfx_is_weapon_use_anim)
TP_BODY_SET_INT(is_weapon)
TP_BODY_SET_INT(gfx_outlined)
TP_BODY_SET_INT(gfx_large_shadow_caster)
TP_BODY_SET_INT(gfx_can_hflip)
TP_BODY_SET_INT(z_depth)
TP_BODY_SET_INT(is_movable)
TP_BODY_SET_INT(is_key)
TP_BODY_SET_INT(is_wall)
TP_BODY_SET_INT(is_floor)

PyObject *tp_update_ (PyObject *obj, PyObject *args, PyObject *keywds)
{	
    PyObject *py_class = 0;	
    char *tp_name = 0;	
    int value = 0;	
    Tpp tp;
	
    static char *kwlist[] = {(char*) "class", (char*) "value", 0};	
	
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "O|i", kwlist, &py_class,
                                     &value)) {	
        return (0);	
    }	
	
    if (!py_class) {	
        ERR("%s, missing class", __FUNCTION__);	
        return (0);	
    }	
	
    tp_name = py_obj_attr_str(py_class, "name");	
    if (!tp_name) {	
        ERR("%s, missing tp name", __FUNCTION__);	
        goto done;	
    }	
	
    DBG("python-to-c: %s(%s -> %d)", __FUNCTION__, tp_name, value);	
	
    tp = tp_find(tp_name);	
    if (!tp) {	
        ERR("%s, cannot find tp %s", __FUNCTION__, tp_name);	
        goto done;	
    }	
	
    tp_update(tp);
	
done:	
    if (tp_name) {	
        myfree(tp_name);	
    }	
	
    Py_RETURN_NONE;	
}	
