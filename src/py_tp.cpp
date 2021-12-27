//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_py_tp.hpp"
#include "my_python.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

PyObject *tp_load_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  PyObject *py_class = 0;

  static char *kwlist[] = {(char *) "tp", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "O", kwlist, &py_class)) {
    ERR("tp_load: Bad args");
    Py_RETURN_FALSE;
  }

  if (! py_class) {
    ERR("tp_load: Missing name attr");
    Py_RETURN_FALSE;
  }

  char *tp_name = py_obj_attr_str(py_class, "name");
  if (! tp_name) {
    ERR("tp_load: Missing tp name");
    Py_RETURN_FALSE;
  }

  char *tp_text_name = py_obj_attr_str(py_class, "text_name");
  if (! tp_text_name) {
    ERR("tp_load: Missing tp text_name");
    Py_RETURN_FALSE;
  }

  char *tp_short_text_name = py_obj_attr_str(py_class, "short_text_name");
  if (! tp_short_text_name) {
    ERR("tp_load: Missing tp short_text_name");
    Py_RETURN_FALSE;
  }

  static int id;
  id++;
  tp_load(id, tp_name, tp_text_name, tp_short_text_name);

  myfree(tp_name);
  myfree(tp_text_name);
  myfree(tp_short_text_name);

  Py_RETURN_TRUE;
}

#define TP_BODY_SET_STRING(__field__)                                                                                \
  PyObject *tp_set_##__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                      \
  {                                                                                                                  \
    PyObject *py_class = 0;                                                                                          \
    char     *tp_name  = 0;                                                                                          \
    char     *value    = 0;                                                                                          \
    Tpp       tp;                                                                                                    \
                                                                                                                     \
    static char *kwlist[] = {(char *) "class", (char *) "value", 0};                                                 \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "O|s", kwlist, &py_class, &value)) {                             \
      ERR("%s: Bad args", __FUNCTION__);                                                                             \
      return 0;                                                                                                      \
    }                                                                                                                \
                                                                                                                     \
    if (! py_class) {                                                                                                \
      ERR("%s: Missing class", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! value) {                                                                                                   \
      ERR("%s: Missing value", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    tp_name = py_obj_attr_str(py_class, "name");                                                                     \
    if (! tp_name) {                                                                                                 \
      ERR("%s: Missing tp name", __FUNCTION__);                                                                      \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    PY_DBG("%s(%s -> \"%s\")", __FUNCTION__, tp_name, value);                                                        \
                                                                                                                     \
    tp = tp_find(tp_name);                                                                                           \
    if (unlikely(! tp)) {                                                                                            \
      ERR("%s: Cannot find tp %s", __FUNCTION__, tp_name);                                                           \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    tp->set_##__field__(std::string(value ? value : ""));                                                            \
    value = 0;                                                                                                       \
                                                                                                                     \
  done:                                                                                                              \
    if (tp_name) {                                                                                                   \
      myfree(tp_name);                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define TP_BODY_SET_STRING_FN(__field__, __fn__)                                                                     \
  PyObject *tp_set_##__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                      \
  {                                                                                                                  \
    PyObject *py_class = 0;                                                                                          \
    char     *tp_name  = 0;                                                                                          \
    char     *value    = 0;                                                                                          \
    Tpp       tp;                                                                                                    \
                                                                                                                     \
    static char *kwlist[] = {(char *) "class", (char *) "value", 0};                                                 \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "O|s", kwlist, &py_class, &value)) {                             \
      ERR("%s: Bad args", __FUNCTION__);                                                                             \
      return 0;                                                                                                      \
    }                                                                                                                \
                                                                                                                     \
    if (! py_class) {                                                                                                \
      ERR("%s: Missing class", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! value) {                                                                                                   \
      ERR("%s: Missing value", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    tp_name = py_obj_attr_str(py_class, "name");                                                                     \
    if (! tp_name) {                                                                                                 \
      ERR("%s: Missing tp name", __FUNCTION__);                                                                      \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    PY_DBG("%s(%s -> \"%s\")", __FUNCTION__, tp_name, value);                                                        \
                                                                                                                     \
    tp = tp_find(tp_name);                                                                                           \
    if (unlikely(! tp)) {                                                                                            \
      ERR("%s: Cannot find tp %s", __FUNCTION__, tp_name);                                                           \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    tp->set_##__field__(std::string(value ? value : ""));                                                            \
    value = 0;                                                                                                       \
    (__fn__)(tp);                                                                                                    \
                                                                                                                     \
  done:                                                                                                              \
    if (tp_name) {                                                                                                   \
      myfree(tp_name);                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define TP_BODY_SET_ENUM(__field__, __str2val__)                                                                     \
  PyObject *tp_set_##__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                      \
  {                                                                                                                  \
    PyObject *py_class = 0;                                                                                          \
    char     *tp_name  = 0;                                                                                          \
    char     *value    = 0;                                                                                          \
    Tpp       tp;                                                                                                    \
                                                                                                                     \
    static char *kwlist[] = {(char *) "class", (char *) "value", 0};                                                 \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "O|s", kwlist, &py_class, &value)) {                             \
      ERR("%s: Bad args", __FUNCTION__);                                                                             \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! py_class) {                                                                                                \
      ERR("%s: Missing class", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! value) {                                                                                                   \
      ERR("%s: Missing value", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    tp_name = py_obj_attr_str(py_class, "name");                                                                     \
    if (! tp_name) {                                                                                                 \
      ERR("%s: Missing tp name", __FUNCTION__);                                                                      \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    tp = tp_find(tp_name);                                                                                           \
    if (unlikely(! tp)) {                                                                                            \
      ERR("%s: Cannot find tp %s", __FUNCTION__, tp_name);                                                           \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    tp->set_##__field__((__str2val__) (value));                                                                      \
    if (tp->__field__() == (int) (tp->__field__()) - 1) {                                                            \
      ERR("%s: Cannot find enum %s", __FUNCTION__, value);                                                           \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    PY_DBG("%s(%s -> \"%s\"[%d])", __FUNCTION__, tp_name, value, tp->__field__());                                   \
                                                                                                                     \
    value = 0;                                                                                                       \
                                                                                                                     \
  done:                                                                                                              \
    if (tp_name) {                                                                                                   \
      myfree(tp_name);                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define TP_BODY_SET_INT(__field__)                                                                                   \
  PyObject *tp_set_##__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                      \
  {                                                                                                                  \
    PyObject *py_class = 0;                                                                                          \
    char     *tp_name  = 0;                                                                                          \
    int       value    = 0;                                                                                          \
    Tpp       tp;                                                                                                    \
                                                                                                                     \
    static char *kwlist[] = {(char *) "class", (char *) "value", 0};                                                 \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "O|i", kwlist, &py_class, &value)) {                             \
      ERR("%s: Bad args", __FUNCTION__);                                                                             \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! py_class) {                                                                                                \
      ERR("%s: Missing class", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    tp_name = py_obj_attr_str(py_class, "name");                                                                     \
    if (! tp_name) {                                                                                                 \
      ERR("%s: Missing tp name", __FUNCTION__);                                                                      \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    PY_DBG("%s(%s -> %d)", __FUNCTION__, tp_name, value);                                                            \
                                                                                                                     \
    tp = tp_find(tp_name);                                                                                           \
    if (unlikely(! tp)) {                                                                                            \
      ERR("%s: Cannot find tp %s", __FUNCTION__, tp_name);                                                           \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    tp->set_##__field__(value);                                                                                      \
                                                                                                                     \
  done:                                                                                                              \
    if (tp_name) {                                                                                                   \
      myfree(tp_name);                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define TP_BODY_SET_DOUBLE(__field__)                                                                                \
  PyObject *tp_set_##__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                      \
  {                                                                                                                  \
    PyObject *py_class = 0;                                                                                          \
    char     *tp_name  = 0;                                                                                          \
    double    value    = 0;                                                                                          \
    Tpp       tp;                                                                                                    \
                                                                                                                     \
    static char *kwlist[] = {(char *) "class", (char *) "value", 0};                                                 \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "O|d", kwlist, &py_class, &value)) {                             \
      ERR("%s: Bad args", __FUNCTION__);                                                                             \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! py_class) {                                                                                                \
      ERR("%s: Missing class", __FUNCTION__);                                                                        \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    tp_name = py_obj_attr_str(py_class, (char *) "name");                                                            \
    if (! tp_name) {                                                                                                 \
      ERR("%s: Missing tp name", __FUNCTION__);                                                                      \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    PY_DBG("%s(%s -> %g)", __FUNCTION__, tp_name, value);                                                            \
                                                                                                                     \
    tp = tp_find(tp_name);                                                                                           \
    if (unlikely(! tp)) {                                                                                            \
      ERR("%s: Cannot find tp %s", __FUNCTION__, tp_name);                                                           \
      goto done;                                                                                                     \
    }                                                                                                                \
                                                                                                                     \
    tp->set_##__field__(value);                                                                                      \
                                                                                                                     \
  done:                                                                                                              \
    if (tp_name) {                                                                                                   \
      myfree(tp_name);                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

static PyObject *tp_set_tile_dir(PyObject *obj, PyObject *args, PyObject *keywds, int dir, int level)
{
  PyObject *py_class = 0;
  char     *tp_name  = 0;
  char     *fg       = 0;
  char     *bg       = 0;
  char     *fg_color = 0;
  char     *bg_color = 0;

  int delay_ms                = 0;
  int frame                   = 0;
  int is_moving               = 0;
  int is_jumping              = 0;
  int begin_jump              = 0;
  int is_outline              = 0;
  int left                    = 0;
  int right                   = 0;
  int up                      = 0;
  int down                    = 0;
  int none                    = 0;
  int is_yyy5                 = 0;
  int is_yyy6                 = 0;
  int is_yyy7                 = 0;
  int is_yyy8                 = 0;
  int is_yyy9                 = 0;
  int is_invisible            = 0;
  int is_hp_25_percent        = 0;
  int is_hp_50_percent        = 0;
  int is_hp_75_percent        = 0;
  int is_hp_100_percent       = 0;
  int is_in_water             = 0;
  int is_sleeping             = 0;
  int is_open                 = 0;
  int is_dead                 = 0;
  int is_end_of_anim          = 0;
  int is_dead_on_end_of_anim  = 0;
  int is_alive_on_end_of_anim = 0;
  int is_resurrecting         = 0;

  char *py_tile_name = nullptr;

  static char *kwlist[] = {(char *) "class",
                           (char *) "tile",
                           (char *) "fg",
                           (char *) "bg",
                           (char *) "fg_color",
                           (char *) "bg_color",
                           (char *) "delay_ms",
                           (char *) "frame",
                           (char *) "is_moving",
                           (char *) "is_jumping",
                           (char *) "begin_jump",
                           (char *) "is_outline",
                           (char *) "is_dir_left",
                           (char *) "is_dir_right",
                           (char *) "is_dir_up",
                           (char *) "is_dir_down",
                           (char *) "is_dir_none",
                           (char *) "is_yyy5",
                           (char *) "is_yyy6",
                           (char *) "is_yyy7",
                           (char *) "is_yyy8",
                           (char *) "is_yyy9",
                           (char *) "is_invisible",
                           (char *) "is_hp_25_percent",
                           (char *) "is_hp_50_percent",
                           (char *) "is_hp_75_percent",
                           (char *) "is_hp_100_percent",
                           (char *) "is_in_water",
                           (char *) "is_sleeping",
                           (char *) "is_open",
                           (char *) "is_dead",
                           (char *) "is_end_of_anim",
                           (char *) "is_dead_on_end_of_anim",
                           (char *) "is_resurrecting",
                           (char *) "is_alive_on_end_of_anim",
                           0};

  if (! PyArg_ParseTupleAndKeywords(
          args, keywds, "O|sssssiiisiiiiiiiiiiiiiiiiiiiiiiiii", kwlist, &py_class, &py_tile_name, &fg, &bg, &fg_color,
          &bg_color, &delay_ms, &frame, &is_moving, &is_jumping, &begin_jump, &is_outline, &left, &right, &up, &down,
          &none, &is_yyy5, &is_yyy6, &is_yyy7, &is_yyy8, &is_yyy9, &is_invisible, &is_hp_25_percent,
          &is_hp_50_percent, &is_hp_75_percent, &is_hp_100_percent, &is_in_water, &is_sleeping, &is_open, &is_dead,
          &is_end_of_anim, &is_dead_on_end_of_anim, &is_resurrecting, &is_alive_on_end_of_anim)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! py_class) {
    ERR("%s: Missing class", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Tpp tp;

  tp_name = py_obj_attr_str(py_class, "name");
  if (! tp_name) {
    ERR("%s: Missing tp name", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%s -> \"%s\")", __FUNCTION__, tp_name, py_tile_name);

  tp = tp_find(tp_name);
  if (unlikely(! tp)) {
    ERR("%s: Cannot find tp %s", __FUNCTION__, tp_name);
    Py_RETURN_FALSE;
  }

  Tilemap *tiles = nullptr;
  switch (dir) {
    case THING_DIR_NONE : tiles = &tp->tiles; break;
    case THING_DIR_DOWN :
      if (level == 1) {
        tiles = &tp->bot1_tiles;
      } else if (level == 2) {
        tiles = &tp->bot2_tiles;
      } else if (level == 3) {
        tiles = &tp->bot3_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_UP :
      if (level == 1) {
        tiles = &tp->top1_tiles;
      } else if (level == 2) {
        tiles = &tp->top2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_LEFT :
      if (level == 1) {
        tiles = &tp->left1_tiles;
      } else if (level == 2) {
        tiles = &tp->left2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_RIGHT :
      if (level == 1) {
        tiles = &tp->right1_tiles;
      } else if (level == 2) {
        tiles = &tp->right2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_TL :
      if (level == 1) {
        tiles = &tp->tl1_tiles;
      } else if (level == 2) {
        tiles = &tp->tl2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_BL :
      if (level == 1) {
        tiles = &tp->bl1_tiles;
      } else if (level == 2) {
        tiles = &tp->bl2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_TR :
      if (level == 1) {
        tiles = &tp->tr1_tiles;
      } else if (level == 2) {
        tiles = &tp->tr2_tiles;
      } else {
        DIE("Bug");
      }
      break;
    case THING_DIR_BR :
      if (level == 1) {
        tiles = &tp->br1_tiles;
      } else if (level == 2) {
        tiles = &tp->br2_tiles;
      } else {
        DIE("Bug");
      }
      break;
  }

  if (! tiles) {
    ERR("No tiles for [%s]", py_tile_name);
    Py_RETURN_FALSE;
  }

  {
    if (py_tile_name && *py_tile_name) {
      Tilep tile;

      tile = tile_find(std::string(py_tile_name));
      if (unlikely(! tile)) {
        ERR("%s: Cannot find tile '%s' for tp %s", __FUNCTION__, py_tile_name, tp_name);
        Py_RETURN_FALSE;
      }

      //
      // Copy thie tile and make a unique copy if someone has grabbed it.
      //
      if (tile->in_use) {
        tile = new Tile(tile);
      }

      tile->index = (*tiles).size();
      (*tiles).push_back(tile);
      tile->in_use = true;

      tile->delay_ms  = delay_ms;
      tile->frame     = frame;
      tile->is_moving = is_moving;

      tile->is_yyy5                = is_yyy5;
      tile->is_yyy6                = is_yyy6;
      tile->is_yyy7                = is_yyy7;
      tile->is_yyy8                = is_yyy8;
      tile->is_yyy9                = is_yyy9;
      tile->is_invisible           = is_invisible;
      tile->is_hp_25_percent       = is_hp_25_percent;
      tile->is_hp_50_percent       = is_hp_50_percent;
      tile->is_hp_75_percent       = is_hp_75_percent;
      tile->is_hp_100_percent      = is_hp_100_percent;
      tile->is_sleeping            = is_sleeping;
      tile->is_open                = is_open;
      tile->is_dead                = is_dead;
      tile->is_end_of_anim         = is_end_of_anim;
      tile->is_dead_on_end_of_anim = is_dead_on_end_of_anim;
      if (is_dead_on_end_of_anim) {
        tp->set_is_dead_on_end_of_anim(true);
      }
      tile->is_alive_on_end_of_anim = is_alive_on_end_of_anim;
      if (is_alive_on_end_of_anim) {
        tp->set_is_alive_on_end_of_anim(true);
      }
      tile->is_resurrecting = is_resurrecting;

      if (tile->is_hp_25_percent || tile->is_hp_50_percent || tile->is_hp_75_percent || tile->is_hp_100_percent) {
        tp->set_internal_has_hp_anim(true);
      }

      if (up) {
        if (left) {
          tile->dir                   = THING_DIR_TL;
          tile->internal_has_dir_anim = true;
        } else if (right) {
          tile->dir                   = THING_DIR_TR;
          tile->internal_has_dir_anim = true;
        } else {
          tile->dir                   = THING_DIR_UP;
          tile->internal_has_dir_anim = true;
        }
      } else if (down) {
        if (left) {
          tile->dir                   = THING_DIR_BL;
          tile->internal_has_dir_anim = true;
        } else if (right) {
          tile->dir                   = THING_DIR_BR;
          tile->internal_has_dir_anim = true;
        } else {
          tile->dir                   = THING_DIR_DOWN;
          tile->internal_has_dir_anim = true;
        }
      } else if (left) {
        tile->dir                   = THING_DIR_LEFT;
        tile->internal_has_dir_anim = true;
      } else if (right) {
        tile->dir                   = THING_DIR_RIGHT;
        tile->internal_has_dir_anim = true;
      } else if (none) {
        tile->dir = THING_DIR_NONE;
      }

      if (tile->internal_has_dir_anim) {
        tp->set_internal_has_dir_anim(true);
      }
    } else {
      (*tiles).push_back(nullptr);
    }
  }

  if (tp_name) {
    myfree(tp_name);
  }

  Py_RETURN_TRUE;
}

PyObject *tp_set_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_NONE, 1));
}
PyObject *tp_set_top1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_UP, 1));
}
PyObject *tp_set_bot1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_DOWN, 1));
}
PyObject *tp_set_left1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_LEFT, 1));
}
PyObject *tp_set_right1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_RIGHT, 1));
}
PyObject *tp_set_tl1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_TL, 1));
}
PyObject *tp_set_tr1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_TR, 1));
}
PyObject *tp_set_bl1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_BL, 1));
}
PyObject *tp_set_br1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_BR, 1));
}
PyObject *tp_set_top2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_UP, 2));
}
PyObject *tp_set_bot2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_DOWN, 2));
}
PyObject *tp_set_bot3_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_DOWN, 3));
}
PyObject *tp_set_left2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_LEFT, 2));
}
PyObject *tp_set_right2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_RIGHT, 2));
}
PyObject *tp_set_tl2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_TL, 2));
}
PyObject *tp_set_tr2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_TR, 2));
}
PyObject *tp_set_bl2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_BL, 2));
}
PyObject *tp_set_br2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tp_set_tile_dir(obj, args, keywds, THING_DIR_BR, 2));
}

PyObject *tp_update_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  PyObject *py_class = 0;
  char     *tp_name  = 0;
  int       value    = 0;
  Tpp       tp;

  static char *kwlist[] = {(char *) "class", (char *) "value", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "O|i", kwlist, &py_class, &value)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! py_class) {
    ERR("%s: Missing class", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  tp_name = py_obj_attr_str(py_class, "name");
  if (! tp_name) {
    ERR("%s: Missing tp name", __FUNCTION__);
    goto done;
  }

  PY_DBG("%s(%s -> %d)", __FUNCTION__, tp_name, value);

  tp = tp_find(tp_name);
  if (unlikely(! tp)) {
    ERR("%s: Cannot find tp %s", __FUNCTION__, tp_name);
    goto done;
  }

done:
  if (tp_name) {
    myfree(tp_name);
  }

  Py_RETURN_TRUE;
}

PyObject *level_spawn_next_to_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->spawn_next_to(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *level_spawn_next_to_or_on_monst_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->spawn_next_to_or_on_monst(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *level_spawn_using_items_radius_range_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what       = nullptr;
  uint32_t id         = 0;
  uint32_t parent_id  = 0;
  uint32_t target_id  = 0;
  uint32_t radius_min = 0;
  uint32_t radius_max = 0;

  static char *kwlist[] = {
      (char *) "id", (char *) "parent_id", (char *) "target_id", (char *) "what", (char *) "min", (char *) "max", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIIs|ii", kwlist, &id, &parent_id, &target_id, &what, &radius_min,
                                    &radius_max)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! parent_id) {
    ERR("%s: Missing 'parent_id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! target_id) {
    ERR("%s: Missing 'target_id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s, %u, %u)", __FUNCTION__, id, what, radius_min, radius_max);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find 'me' thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  auto parent = level->thing_find(ThingId(parent_id));
  if (! parent) {
    ERR("%s: Cannot find parent thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  auto target = level->thing_find(ThingId(target_id));
  if (! target) {
    ERR("%s: Cannot find target thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  //
  // This is intentionally 0,0 to use the items range unless overridden
  //
  if (t->spawn_radius_range(parent, target, std::string(what), radius_min, radius_max)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *level_spawn_fire_around_thing(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->spawn_fire(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *level_spawn_at_thing(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  auto it = t->spawn_at(std::string(what));
  if (it) {
    return Py_BuildValue("I", it->id);
  }
  Py_RETURN_FALSE;
}

PyObject *level_spawn_at_thing_if_possible(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->spawn_at_if_possible(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *if_matches_then_dead_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;
  int      x    = -1;
  int      y    = -1;

  static char *kwlist[] = {(char *) "id", (char *) "what", (char *) "x", (char *) "y", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Isii", kwlist, &id, &what, &x, &y)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (x == -1) {
    ERR("%s: Missing 'x'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (y == -1) {
    ERR("%s: Missing 'y'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s, %d, %d)", __FUNCTION__, id, what, x, y);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->if_matches_then_dead(std::string(what), point(x, y))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *if_matches_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->matches(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *level_place_at(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;
  int      x    = -1;
  int      y    = -1;

  static char *kwlist[] = {(char *) "id", (char *) "what", (char *) "x", (char *) "y", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Isii", kwlist, &id, &what, &x, &y)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (x == -1) {
    ERR("%s: Missing 'x'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (y == -1) {
    ERR("%s: Missing 'y'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%x, %s, %d, %d)", __FUNCTION__, id, what, x, y);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIx32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->place(std::string(what), point(x, y))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

TP_BODY_SET_INT(aggression_level_pct)
TP_BODY_SET_INT(collateral_damage_pct)
TP_BODY_SET_INT(ai_detect_secret_doors)
TP_BODY_SET_INT(ai_obstacle)
TP_BODY_SET_INT(ai_resent_count)
TP_BODY_SET_INT(ai_shove_chance_d1000)
TP_BODY_SET_INT(ai_wanderer)
TP_BODY_SET_INT(attack_blood)
TP_BODY_SET_INT(attack_eater)
TP_BODY_SET_INT(attack_engulf_chance_d1000)
TP_BODY_SET_INT(attack_humanoid)
TP_BODY_SET_INT(attack_living)
TP_BODY_SET_INT(attack_lunge)
TP_BODY_SET_INT(attack_meat)
TP_BODY_SET_INT(attack_undead)
TP_BODY_SET_INT(blast_max_radius)
TP_BODY_SET_INT(blast_min_radius)
TP_BODY_SET_INT(blit_bot_off)
TP_BODY_SET_INT(blit_left_off)
TP_BODY_SET_INT(blit_right_off)
TP_BODY_SET_INT(blit_top_off)
TP_BODY_SET_INT(capacity_height)
TP_BODY_SET_INT(capacity_width)
TP_BODY_SET_INT(charge_count)
TP_BODY_SET_INT(collision_check)
TP_BODY_SET_INT(collision_hit_priority)
TP_BODY_SET_INT(damage_acid_chance_d1000)
TP_BODY_SET_INT(damage_bite_chance_d1000)
TP_BODY_SET_INT(damage_crush_chance_d1000)
TP_BODY_SET_INT(damage_digest_chance_d1000)
TP_BODY_SET_INT(damage_energy_chance_d1000)
TP_BODY_SET_INT(damage_fire_chance_d1000)
TP_BODY_SET_INT(damage_future1_chance_d1000)
TP_BODY_SET_INT(damage_future2_chance_d1000)
TP_BODY_SET_INT(damage_future3_chance_d1000)
TP_BODY_SET_INT(damage_future4_chance_d1000)
TP_BODY_SET_INT(damage_lightning_chance_d1000)
TP_BODY_SET_INT(damage_melee_chance_d1000)
TP_BODY_SET_INT(damage_necrosis_chance_d1000)
TP_BODY_SET_INT(damage_poison_chance_d1000)
TP_BODY_SET_INT(damage_received_doubled_from_acid)
TP_BODY_SET_INT(damage_received_doubled_from_fire)
TP_BODY_SET_INT(damage_received_doubled_from_necrosis)
TP_BODY_SET_INT(damage_received_doubled_from_poison)
TP_BODY_SET_INT(damage_received_doubled_from_water)
TP_BODY_SET_INT(distance_avoid)
TP_BODY_SET_INT(distance_jump)
TP_BODY_SET_INT(distance_leader_max)
TP_BODY_SET_INT(distance_manifestor_max)
TP_BODY_SET_INT(distance_minion_vision_shared)
TP_BODY_SET_INT(distance_recruitment_max)
TP_BODY_SET_INT(distance_throw)
TP_BODY_SET_INT(distance_vision)
TP_BODY_SET_INT(enchant_level)
TP_BODY_SET_INT(enchant_max)
TP_BODY_SET_INT(environ_avoids_acid)
TP_BODY_SET_INT(environ_avoids_fire)
TP_BODY_SET_INT(environ_avoids_necrosis)
TP_BODY_SET_INT(environ_avoids_poison)
TP_BODY_SET_INT(environ_avoids_water)
TP_BODY_SET_INT(environ_prefers_acid)
TP_BODY_SET_INT(environ_prefers_fire)
TP_BODY_SET_INT(environ_prefers_necrosis)
TP_BODY_SET_INT(environ_prefers_poison)
TP_BODY_SET_INT(environ_prefers_spiderwebs)
TP_BODY_SET_INT(environ_prefers_water)
TP_BODY_SET_INT(gfx_an_animation_only)
TP_BODY_SET_INT(gfx_animated)
TP_BODY_SET_INT(gfx_animated_can_hflip)
TP_BODY_SET_INT(gfx_animated_can_vflip)
TP_BODY_SET_INT(gfx_animated_no_dir)
TP_BODY_SET_INT(gfx_attack_anim)
TP_BODY_SET_INT(gfx_bounce_always)
TP_BODY_SET_INT(gfx_bounce_on_move)
TP_BODY_SET_INT(gfx_dead_anim)
TP_BODY_SET_INT(gfx_equip_carry_anim)
TP_BODY_SET_INT(gfx_flickers)
TP_BODY_SET_INT(gfx_glows)
TP_BODY_SET_INT(gfx_health_bar_autohide)
TP_BODY_SET_INT(gfx_health_bar_shown)
TP_BODY_SET_INT(gfx_long_shadow_caster)
TP_BODY_SET_INT(gfx_on_fire_anim)
TP_BODY_SET_INT(gfx_oversized_and_on_floor)
TP_BODY_SET_INT(gfx_short_shadow_caster)
TP_BODY_SET_INT(gfx_shown_in_bg)
TP_BODY_SET_INT(gfx_show_outlined)
TP_BODY_SET_INT(gfx_solid_shadow)
TP_BODY_SET_INT(gfx_very_short_shadow_caster)
TP_BODY_SET_INT(gfx_water)
TP_BODY_SET_INT(health_starving_pct)
TP_BODY_SET_INT(hunger_clock_tick_frequency)
TP_BODY_SET_INT(hunger_health_pct)
TP_BODY_SET_INT(hunger_is_insatiable)
TP_BODY_SET_INT(is_able_to_attack_mobs)
TP_BODY_SET_INT(is_able_to_break_down_doors)
TP_BODY_SET_INT(is_able_to_break_out_of_webs)
TP_BODY_SET_INT(is_able_to_change_levels)
TP_BODY_SET_INT(is_able_to_collect_keys)
TP_BODY_SET_INT(is_able_to_enchant_items)
TP_BODY_SET_INT(is_able_to_fall)
TP_BODY_SET_INT(is_able_to_fire_at)
TP_BODY_SET_INT(is_able_to_follow)
TP_BODY_SET_INT(is_able_to_jump)
TP_BODY_SET_INT(is_able_to_jump_attack)
TP_BODY_SET_INT(is_able_to_jump_attack_chance_d1000)
TP_BODY_SET_INT(is_able_to_jump_escape)
TP_BODY_SET_INT(is_able_to_jump_on_low_hp_chance_d1000)
TP_BODY_SET_INT(is_able_to_jump_onto)
TP_BODY_SET_INT(is_able_to_jump_onto_chance_d1000)
TP_BODY_SET_INT(is_able_to_jump_randomly_chance_d1000)
TP_BODY_SET_INT(is_able_to_jump_without_tiring)
TP_BODY_SET_INT(is_able_to_learn_skills)
TP_BODY_SET_INT(is_able_to_open_doors)
TP_BODY_SET_INT(is_able_to_see_in_the_dark)
TP_BODY_SET_INT(is_able_to_see_through_doors)
TP_BODY_SET_INT(is_able_to_shove)
TP_BODY_SET_INT(is_able_to_tire)
TP_BODY_SET_INT(is_able_to_use_wands)
TP_BODY_SET_INT(is_able_to_use_weapons)
TP_BODY_SET_INT(is_able_to_walk_through_walls)
TP_BODY_SET_INT(is_acid)
TP_BODY_SET_INT(is_alive_on_end_of_anim)
TP_BODY_SET_INT(is_always_hit)
TP_BODY_SET_INT(is_aquatic)
TP_BODY_SET_INT(is_ascend_dungeon)
TP_BODY_SET_INT(is_ascend_sewer)
TP_BODY_SET_INT(is_attackable_by_monst)
TP_BODY_SET_INT(is_attackable_by_player)
TP_BODY_SET_INT(is_auto_collect_item)
TP_BODY_SET_INT(is_auto_equipped)
TP_BODY_SET_INT(is_auto_throw)
TP_BODY_SET_INT(is_auto_use)
TP_BODY_SET_INT(is_bag)
TP_BODY_SET_INT(is_bag_item)
TP_BODY_SET_INT(is_bag_item_container)
TP_BODY_SET_INT(is_bag_item_not_stackable)
TP_BODY_SET_INT(is_barrel)
TP_BODY_SET_INT(is_bleeder)
TP_BODY_SET_INT(is_blood)
TP_BODY_SET_INT(is_blood_eater)
TP_BODY_SET_INT(is_blood_splatter)
TP_BODY_SET_INT(is_bones)
TP_BODY_SET_INT(is_bony)
TP_BODY_SET_INT(is_brazier)
TP_BODY_SET_INT(is_bridge)
TP_BODY_SET_INT(is_buff)
TP_BODY_SET_INT(is_burnable)
TP_BODY_SET_INT(is_carrier_of_treasure_class_a)
TP_BODY_SET_INT(is_carrier_of_treasure_class_b)
TP_BODY_SET_INT(is_carrier_of_treasure_class_c)
TP_BODY_SET_INT(is_chasm)
TP_BODY_SET_INT(is_collectable)
TP_BODY_SET_INT(is_collect_as_keys)
TP_BODY_SET_INT(is_collected_as_gold)
TP_BODY_SET_INT(is_combustible)
TP_BODY_SET_INT(is_corpse_on_death)
TP_BODY_SET_INT(is_corridor)
TP_BODY_SET_INT(is_critical_to_level)
TP_BODY_SET_INT(is_crushable)
TP_BODY_SET_INT(is_cursor)
TP_BODY_SET_INT(is_cursor_can_hover_over)
TP_BODY_SET_INT(is_cursor_can_hover_over_x2_click)
TP_BODY_SET_INT(is_cursor_path)
TP_BODY_SET_INT(is_cursor_path_hazard_for_player)
TP_BODY_SET_INT(is_dead_on_end_of_anim)
TP_BODY_SET_INT(is_dead_on_shove)
TP_BODY_SET_INT(is_debuff)
TP_BODY_SET_INT(is_debug_path)
TP_BODY_SET_INT(is_debug_type)
TP_BODY_SET_INT(is_deep_water)
TP_BODY_SET_INT(is_descend_dungeon)
TP_BODY_SET_INT(is_descend_sewer)
TP_BODY_SET_INT(is_described_when_hovering_over)
TP_BODY_SET_INT(is_destroyed_on_hit_or_miss)
TP_BODY_SET_INT(is_destroyed_on_hitting)
TP_BODY_SET_INT(is_dirt)
TP_BODY_SET_INT(is_door)
TP_BODY_SET_INT(is_droppable)
TP_BODY_SET_INT(is_dry_grass)
TP_BODY_SET_INT(is_enchantable)
TP_BODY_SET_INT(is_enchantstone)
TP_BODY_SET_INT(is_engulfer)
TP_BODY_SET_INT(is_ethereal)
TP_BODY_SET_INT(is_ethereal_mob)
TP_BODY_SET_INT(is_exit_finder)
TP_BODY_SET_INT(is_explorer)
TP_BODY_SET_INT(is_explosion)
TP_BODY_SET_INT(is_fearless)
TP_BODY_SET_INT(is_fire)
TP_BODY_SET_INT(is_floating)
TP_BODY_SET_INT(is_floor)
TP_BODY_SET_INT(is_floor_deco)
TP_BODY_SET_INT(is_foilage)
TP_BODY_SET_INT(is_food)
TP_BODY_SET_INT(is_food_eater)
TP_BODY_SET_INT(is_gfx_anim_synced_with_owner)
TP_BODY_SET_INT(is_glass)
TP_BODY_SET_INT(is_gold)
TP_BODY_SET_INT(is_green_blooded)
TP_BODY_SET_INT(is_green_splatter)
TP_BODY_SET_INT(is_hazard)
TP_BODY_SET_INT(is_health_booster)
TP_BODY_SET_INT(is_heavy)
TP_BODY_SET_INT(is_hittable)
TP_BODY_SET_INT(is_humanoid)
TP_BODY_SET_INT(is_indestructible)
TP_BODY_SET_INT(is_intelligent)
TP_BODY_SET_INT(is_interesting)
TP_BODY_SET_INT(is_item)
TP_BODY_SET_INT(is_item_carrier)
TP_BODY_SET_INT(is_item_collector)
TP_BODY_SET_INT(is_item_eater)
TP_BODY_SET_INT(is_item_magical)
TP_BODY_SET_INT(is_item_magical_eater)
TP_BODY_SET_INT(is_item_organic)
TP_BODY_SET_INT(is_jelly)
TP_BODY_SET_INT(is_jelly_baby)
TP_BODY_SET_INT(is_jelly_baby_eater)
TP_BODY_SET_INT(is_jelly_eater)
TP_BODY_SET_INT(is_jelly_parent)
TP_BODY_SET_INT(is_key)
TP_BODY_SET_INT(is_laser)
TP_BODY_SET_INT(is_lava)
TP_BODY_SET_INT(is_light_blocker)
TP_BODY_SET_INT(is_living)
TP_BODY_SET_INT(is_loggable)
TP_BODY_SET_INT(is_meat)
TP_BODY_SET_INT(is_meat_eater)
TP_BODY_SET_INT(is_metal)
TP_BODY_SET_INT(is_minion)
TP_BODY_SET_INT(is_mob)
TP_BODY_SET_INT(is_monst)
TP_BODY_SET_INT(is_moveable)
TP_BODY_SET_INT(is_msg)
TP_BODY_SET_INT(is_necrotic_danger_level)
TP_BODY_SET_INT(is_no_tile)
TP_BODY_SET_INT(is_obs_destructable)
TP_BODY_SET_INT(is_obs_wall_or_door)
TP_BODY_SET_INT(is_openable)
TP_BODY_SET_INT(is_organic)
TP_BODY_SET_INT(is_pink_blooded)
TP_BODY_SET_INT(is_pink_splatter)
TP_BODY_SET_INT(is_player)
TP_BODY_SET_INT(is_poisonous_danger_level)
TP_BODY_SET_INT(is_potion)
TP_BODY_SET_INT(is_potion_eater)
TP_BODY_SET_INT(is_projectile)
TP_BODY_SET_INT(is_red_blooded)
TP_BODY_SET_INT(is_removeable_if_out_of_slots)
TP_BODY_SET_INT(is_resurrectable)
TP_BODY_SET_INT(is_ring)
TP_BODY_SET_INT(is_ripple)
TP_BODY_SET_INT(is_rock)
TP_BODY_SET_INT(is_rusty)
TP_BODY_SET_INT(is_secret_door)
TP_BODY_SET_INT(is_sewer_wall)
TP_BODY_SET_INT(is_shallow_water)
TP_BODY_SET_INT(is_shovable)
TP_BODY_SET_INT(is_skill)
TP_BODY_SET_INT(is_skillstone)
TP_BODY_SET_INT(is_smoke)
TP_BODY_SET_INT(is_soft_body)
TP_BODY_SET_INT(is_spawner)
TP_BODY_SET_INT(is_spider)
TP_BODY_SET_INT(is_spiderweb)
TP_BODY_SET_INT(is_steal_item_chance_d1000)
TP_BODY_SET_INT(is_sticky)
TP_BODY_SET_INT(is_stone)
TP_BODY_SET_INT(is_sword)
TP_BODY_SET_INT(is_target_auto_select)
TP_BODY_SET_INT(is_the_grid)
TP_BODY_SET_INT(is_throwable)
TP_BODY_SET_INT(is_tickable)
TP_BODY_SET_INT(is_tmp_thing)
TP_BODY_SET_INT(is_torch)
TP_BODY_SET_INT(is_treasure_chest)
TP_BODY_SET_INT(is_treasure_class_a)
TP_BODY_SET_INT(is_treasure_class_b)
TP_BODY_SET_INT(is_treasure_class_c)
TP_BODY_SET_INT(is_treasure_eater)
TP_BODY_SET_INT(is_treasure_type)
TP_BODY_SET_INT(is_undead)
TP_BODY_SET_INT(is_usable)
TP_BODY_SET_INT(is_used_when_thrown)
TP_BODY_SET_INT(is_very_combustible)
TP_BODY_SET_INT(is_wall)
TP_BODY_SET_INT(is_wall_dungeon)
TP_BODY_SET_INT(is_wand)
TP_BODY_SET_INT(is_weapon)
TP_BODY_SET_INT(is_wooden)
TP_BODY_SET_INT(item_height)
TP_BODY_SET_INT(item_width)
TP_BODY_SET_INT(light_strength)
TP_BODY_SET_INT(minion_limit)
TP_BODY_SET_INT(monst_size)
TP_BODY_SET_INT(normal_placement_rules)
TP_BODY_SET_INT(on_death_drop_all_items)
TP_BODY_SET_INT(on_death_is_open)
TP_BODY_SET_INT(range_max)
TP_BODY_SET_INT(rarity)
TP_BODY_SET_INT(spawn_group_radius)
TP_BODY_SET_INT(stamina)
TP_BODY_SET_INT(stat_armor_class)
TP_BODY_SET_INT(stat_attack_bonus)
TP_BODY_SET_INT(stat_constitution)
TP_BODY_SET_INT(stat_dexterity)
TP_BODY_SET_INT(stats02)
TP_BODY_SET_INT(stats03)
TP_BODY_SET_INT(stats04)
TP_BODY_SET_INT(stats05)
TP_BODY_SET_INT(stats06)
TP_BODY_SET_INT(stats07)
TP_BODY_SET_INT(stats08)
TP_BODY_SET_INT(stats09)
TP_BODY_SET_INT(stats10)
TP_BODY_SET_INT(stats11)
TP_BODY_SET_INT(stats12)
TP_BODY_SET_INT(stats17)
TP_BODY_SET_INT(stat_strength)
TP_BODY_SET_INT(unused_chance1_d1000)
TP_BODY_SET_INT(unused_chance2_d1000)
TP_BODY_SET_INT(unused_chance3_d1000)
TP_BODY_SET_INT(unused_chance4_d1000)
TP_BODY_SET_INT(unused_chance5_d1000)
TP_BODY_SET_INT(unused_chance6_d1000)
TP_BODY_SET_INT(unused_chance7_d1000)
TP_BODY_SET_INT(unused_chance8_d1000)
TP_BODY_SET_INT(unused_flag1)
TP_BODY_SET_INT(is_able_to_use_rings)
TP_BODY_SET_INT(unused_flag2)
TP_BODY_SET_INT(unused_flag3)
TP_BODY_SET_INT(unused_flag4)
TP_BODY_SET_INT(unused_flag5)
TP_BODY_SET_INT(unused_flag6)
TP_BODY_SET_INT(is_treasure_map)
TP_BODY_SET_INT(weapon_damage)
TP_BODY_SET_INT(z_depth)
TP_BODY_SET_INT(z_prio)
TP_BODY_SET_STRING(damage_acid_dice)
TP_BODY_SET_STRING(damage_bite_dice)
TP_BODY_SET_STRING(damage_crush_dice)
TP_BODY_SET_STRING(damage_digest_dice)
TP_BODY_SET_STRING(damage_energy_dice)
TP_BODY_SET_STRING(damage_fire_dice)
TP_BODY_SET_STRING(damage_future1_dice)
TP_BODY_SET_STRING(damage_future2_dice)
TP_BODY_SET_STRING(damage_future3_dice)
TP_BODY_SET_STRING(damage_future4_dice)
TP_BODY_SET_STRING(damage_lightning_dice)
TP_BODY_SET_STRING(damage_melee_dice)
TP_BODY_SET_STRING(damage_necrosis_dice)
TP_BODY_SET_STRING(damage_poison_dice)
TP_BODY_SET_STRING(equip_carry_anim)
TP_BODY_SET_STRING(gfx_anim_use)
TP_BODY_SET_STRING(gold_value_dice)
TP_BODY_SET_STRING(health_initial_dice)
TP_BODY_SET_STRING(is_allied_with)
TP_BODY_SET_STRING(laser_name)
TP_BODY_SET_STRING(lifespan_dice)
TP_BODY_SET_STRING(light_color)
TP_BODY_SET_STRING(long_text_description)
TP_BODY_SET_STRING(long_text_description_extra)
TP_BODY_SET_STRING(name)
TP_BODY_SET_STRING(nutrition_dice)
TP_BODY_SET_STRING(on_born_do)
TP_BODY_SET_STRING(on_damage_acid_do)
TP_BODY_SET_STRING(on_damage_bite_do)
TP_BODY_SET_STRING(on_damage_constitution_do)
TP_BODY_SET_STRING(on_damage_crush_do)
TP_BODY_SET_STRING(on_damage_digest_do)
TP_BODY_SET_STRING(on_damage_energy_do)
TP_BODY_SET_STRING(on_damage_fire_do)
TP_BODY_SET_STRING(on_damage_future1_do)
TP_BODY_SET_STRING(on_damage_future2_do)
TP_BODY_SET_STRING(on_damage_future3_do)
TP_BODY_SET_STRING(on_damage_future4_do)
TP_BODY_SET_STRING(on_damage_lightning_do)
TP_BODY_SET_STRING(on_damage_melee_do)
TP_BODY_SET_STRING(on_damage_necrosis_do)
TP_BODY_SET_STRING(on_damage_poison_do)
TP_BODY_SET_STRING(on_damage_strength_do)
TP_BODY_SET_STRING(on_death_do)
TP_BODY_SET_STRING(on_death_of_a_follower_do)
TP_BODY_SET_STRING(on_death_of_my_leader_do)
TP_BODY_SET_STRING(on_enchant_do)
TP_BODY_SET_STRING(on_equip_do)
TP_BODY_SET_STRING(on_fall_do)
TP_BODY_SET_STRING(on_final_use_do)
TP_BODY_SET_STRING(on_firing_at_something_do)
TP_BODY_SET_STRING(on_idle_tick_frequency_dice)
TP_BODY_SET_STRING(on_lifespan_tick_do)
TP_BODY_SET_STRING(on_move_do)
TP_BODY_SET_STRING(on_open_do)
TP_BODY_SET_STRING(on_owner_damage_acid_do)
TP_BODY_SET_STRING(on_owner_damage_bite_do)
TP_BODY_SET_STRING(on_owner_damage_constitution_do)
TP_BODY_SET_STRING(on_owner_damage_crush_do)
TP_BODY_SET_STRING(on_owner_damage_digest_do)
TP_BODY_SET_STRING(on_owner_damage_energy_do)
TP_BODY_SET_STRING(on_owner_damage_fire_do)
TP_BODY_SET_STRING(on_owner_damage_future1_do)
TP_BODY_SET_STRING(on_owner_damage_future2_do)
TP_BODY_SET_STRING(on_owner_damage_future3_do)
TP_BODY_SET_STRING(on_owner_damage_future4_do)
TP_BODY_SET_STRING(on_owner_damage_lightning_do)
TP_BODY_SET_STRING(on_owner_damage_melee_do)
TP_BODY_SET_STRING(on_owner_damage_necrosis_do)
TP_BODY_SET_STRING(on_owner_damage_poison_do)
TP_BODY_SET_STRING(on_owner_damage_strength_do)
TP_BODY_SET_STRING(on_owner_set_do)
TP_BODY_SET_STRING(on_owner_unset_do)
TP_BODY_SET_STRING(on_polymorphed_do)
TP_BODY_SET_STRING(on_tick_do)
TP_BODY_SET_STRING(on_unequip_do)
TP_BODY_SET_STRING(on_use_do)
TP_BODY_SET_STRING(on_you_are_declared_a_follower_do)
TP_BODY_SET_STRING(on_you_are_declared_leader_do)
TP_BODY_SET_STRING(on_you_are_hit_and_now_dead_do)
TP_BODY_SET_STRING(on_you_are_hit_but_still_alive_do)
TP_BODY_SET_STRING(on_you_are_on_fire_do)
TP_BODY_SET_STRING(on_you_bite_attack_do)
TP_BODY_SET_STRING(on_you_miss_do)
TP_BODY_SET_STRING(projectile_name)
TP_BODY_SET_STRING(resurrect_dice)
TP_BODY_SET_STRING(spawn_group_size_dice)
TP_BODY_SET_STRING(spawn_on_shoved)
TP_BODY_SET_STRING(str1)
TP_BODY_SET_STRING(str2)
TP_BODY_SET_STRING(str4)
TP_BODY_SET_STRING(text_a_or_an)
TP_BODY_SET_STRING(text_buff)
TP_BODY_SET_STRING(text_debuff)
TP_BODY_SET_STRING(text_description)
TP_BODY_SET_STRING(text_enchant)
TP_BODY_SET_STRING(text_hits)
TP_BODY_SET_STRING(text_name)
TP_BODY_SET_STRING(text_skill)
TP_BODY_SET_STRING(text_title)
TP_BODY_SET_STRING(text_unused)
TP_BODY_SET_STRING(text_unused1)
TP_BODY_SET_STRING(text_unused2)
