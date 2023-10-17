//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_thing_template.hpp"
#include "my_unicode.hpp"

PyObject *tile_load_arr_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char     *file   = nullptr;
  char     *name   = nullptr;
  int       width  = 0;
  int       height = 0;
  PyObject *e      = nullptr;

  static char *kwlist[]
      = {(char *) "file", (char *) "name", (char *) "width", (char *) "height", (char *) "arr", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ssiiO", kwlist, &file, &name, &width, &height, &e)) {
    PY_ERR("tile_load_arr: Bad args");
    Py_RETURN_FALSE;
  }

  if (! file) {
    PY_ERR("tile_load_arr: Missing file attr");
    Py_RETURN_FALSE;
  }

  if (! name) {
    PY_ERR("tile_load_arr: Missing name attr");
    Py_RETURN_FALSE;
  }

  if (! width) {
    PY_ERR("tile_load_arr: Missing width attr");
    Py_RETURN_FALSE;
  }

  if (! height) {
    PY_ERR("tile_load_arr: Missing height attr");
    Py_RETURN_FALSE;
  }

  if (! e) {
    PY_ERR("tile_load_arr: Missing arr attr");
    Py_RETURN_FALSE;
  }

  int         numLines = PyList_Size(e);
  const char *arr[ numLines + 1 ];
  int         i;

  memset(arr, 0, sizeof(arr));

  PY_DBG("tile_load_arr:file=%s, name=%s, width=%d, height=%d, ...)", file, name, width, height);

  for (i = 0; i < numLines; i++) {
    PyObject *strObj;
    strObj = PyList_GetItem(e, i); /* Can't fail */
    if (! strObj) {
      continue;
    }

    arr[ i ] = py_obj_to_string(strObj);
  }

  tile_load_arr(std::string(file ? file : ""), std::string(name ? name : ""), width, height, numLines, arr);

  for (i = 0; i < numLines; i++) {
    if (! arr[ i ]) {
      continue;
    }

    myfree((char *) arr[ i ]);
  }

  Py_RETURN_TRUE;
}

PyObject *tile_load_arr_sprites_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char     *file   = nullptr;
  char     *name   = nullptr;
  int       width  = 0;
  int       height = 0;
  PyObject *e      = nullptr;

  static char *kwlist[]
      = {(char *) "file", (char *) "name", (char *) "width", (char *) "height", (char *) "arr", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "ssiiO", kwlist, &file, &name, &width, &height, &e)) {
    PY_ERR("tile_load_arr: Bad args");
    Py_RETURN_FALSE;
  }

  if (! file) {
    PY_ERR("tile_load_arr: Sprites, missing file attr");
    Py_RETURN_FALSE;
  }

  if (! name) {
    PY_ERR("tile_load_arr: Sprites, missing name attr");
    Py_RETURN_FALSE;
  }

  if (! width) {
    PY_ERR("tile_load_arr: Sprites, missing width attr");
    Py_RETURN_FALSE;
  }

  if (! height) {
    PY_ERR("tile_load_arr: Sprites, missing height attr");
    Py_RETURN_FALSE;
  }

  if (! e) {
    PY_ERR("tile_load_arr: Sprites, missing arr attr");
    Py_RETURN_FALSE;
  }

  int         numLines = PyList_Size(e);
  const char *arr[ numLines + 1 ];
  int         i;

  memset(arr, 0, sizeof(arr));

  PY_DBG("tile_load_arr:sprites(file=%s, name=%s, width=%d, height=%d, ...)", file, name, width, height);

  for (i = 0; i < numLines; i++) {
    PyObject *strObj;
    strObj = PyList_GetItem(e, i); /* Can't fail */
    if (! strObj) {
      continue;
    }

    arr[ i ] = py_obj_to_string(strObj);
    PY_DBG("tile_load_arr:sprites(\"%s\")", arr[ i ]);
  }

  tile_load_arr_sprites(std::string(file ? file : ""), std::string(name ? name : ""), width, height, numLines, arr);

  for (i = 0; i < numLines; i++) {
    if (! arr[ i ]) {
      continue;
    }

    myfree((char *) arr[ i ]);
  }

  Py_RETURN_TRUE;
}

static PyObject *tile_dir(PyObject *obj, PyObject *args, PyObject *keywds, int dir, int level)
{
  PyObject *py_class = nullptr;
  char     *tp_name  = nullptr;

  int delay_ms                      = 0;
  int ascii_fg_alpha                = 255;
  int ascii_bg_alpha                = 255;
  int frame                         = 0;
  int is_moving                     = 0;
  int is_jumping                    = 0;
  int begin_jump                    = 0;
  int is_outline                    = 0;
  int left                          = 0;
  int right                         = 0;
  int up                            = 0;
  int down                          = 0;
  int none                          = 0;
  int is_yyy5                       = 0;
  int is_yyy6                       = 0;
  int is_yyy7                       = 0;
  int is_yyy8                       = 0;
  int is_yyy9                       = 0;
  int is_invisible                  = 0;
  int is_hp_25_percent              = 0;
  int is_hp_50_percent              = 0;
  int is_hp_75_percent              = 0;
  int is_hp_100_percent             = 0;
  int is_in_water                   = 0;
  int is_sleeping                   = 0;
  int is_open                       = 0;
  int is_dead                       = 0;
  int is_end_of_anim                = 0;
  int is_end_of_ascii_anim          = 0;
  int is_dead_on_end_of_anim        = 0;
  int is_dead_on_end_of_ascii_anim  = 0;
  int is_alive_on_end_of_anim       = 0;
  int is_alive_on_end_of_ascii_anim = 0;
  int is_resurrecting               = 0;

  char *tile_name         = nullptr;
  char *ascii_fg_char_str = nullptr;
  char *ascii_bg_char_str = nullptr;
  char *ascii_bg_col_name = nullptr;
  char *ascii_fg_col_name = nullptr;

  static char *kwlist[] = {(char *) "class",
                           (char *) "tile",
                           (char *) "ascii_fg_char",
                           (char *) "ascii_bg_char",
                           (char *) "ascii_bg_col_name",
                           (char *) "ascii_fg_col_name",
                           (char *) "ascii_bg_alpha",
                           (char *) "ascii_fg_alpha",
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
                           (char *) "is_end_of_ascii_anim",
                           (char *) "is_dead_on_end_of_anim",
                           (char *) "is_dead_on_end_of_ascii_anim",
                           (char *) "is_alive_on_end_of_anim",
                           (char *) "is_alive_on_end_of_ascii_anim",
                           (char *) "is_resurrecting",
                           nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(
          args, keywds, "O|sssssiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii", kwlist, &py_class, &tile_name,
          &ascii_fg_char_str, &ascii_bg_char_str, &ascii_bg_col_name, &ascii_fg_col_name, &ascii_bg_alpha,
          &ascii_fg_alpha, &delay_ms, &frame, &is_moving, &is_jumping, &begin_jump, &is_outline, &left, &right, &up,
          &down, &none, &is_yyy5, &is_yyy6, &is_yyy7, &is_yyy8, &is_yyy9, &is_invisible, &is_hp_25_percent,
          &is_hp_50_percent, &is_hp_75_percent, &is_hp_100_percent, &is_in_water, &is_sleeping, &is_open, &is_dead,
          &is_end_of_anim, &is_end_of_ascii_anim, &is_dead_on_end_of_anim, &is_dead_on_end_of_ascii_anim,
          &is_alive_on_end_of_anim, &is_alive_on_end_of_ascii_anim, &is_resurrecting)) {
    PY_ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! py_class) {
    PY_ERR("%s: Missing class", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Tpp tp;

  tp_name = py_obj_attr_str(py_class, "name");
  if (! tp_name) {
    PY_ERR("%s: Missing tp name", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%s -> \"%s\")", __FUNCTION__, tp_name, tile_name);

  tp = tp_find(tp_name);
  if (unlikely(! tp)) {
    PY_ERR("%s: Cannot find tp %s", __FUNCTION__, tp_name);
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
    PY_ERR("No tiles for [%s]", tile_name);
    Py_RETURN_FALSE;
  }

  {
    if (tile_name && *tile_name) {
      Tilep tile;

      tile = tile_find(std::string(tile_name));
      if (unlikely(! tile)) {
        DIE("%s: Cannot find tile '%s' for tp %s", __FUNCTION__, tile_name, tp_name);
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

      tile->ascii_bg_alpha = ascii_bg_alpha;
      tile->ascii_fg_alpha = ascii_fg_alpha;

      if (ascii_fg_char_str) {
        tile->ascii_set     = true;
        tile->ascii_fg_char = unicode_alias_to_char(ascii_fg_char_str);
      }

      if (ascii_bg_char_str) {
        tile->ascii_set     = true;
        tile->ascii_bg_char = unicode_alias_to_char(ascii_bg_char_str);
      }

      tile->ascii_bg_col_value = COLOR_NONE;
      tile->ascii_fg_col_value = WHITE;

      if (ascii_bg_col_name && *ascii_bg_col_name) {
        tile->ascii_set          = true;
        tile->ascii_bg_col_name  = ascii_bg_col_name;
        tile->ascii_bg_col_value = color_find(ascii_bg_col_name);
      }

      if (ascii_fg_col_name && *ascii_fg_col_name) {
        tile->ascii_set          = true;
        tile->ascii_fg_col_name  = ascii_fg_col_name;
        tile->ascii_fg_col_value = color_find(ascii_fg_col_name);
      }

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
      tile->is_end_of_ascii_anim   = is_end_of_ascii_anim;
      tile->is_dead_on_end_of_anim = is_dead_on_end_of_anim;
      if (is_dead_on_end_of_anim) {
        tp->is_dead_on_end_of_anim_set(true);
      }
      tile->is_dead_on_end_of_ascii_anim = is_dead_on_end_of_ascii_anim;
      if (is_alive_on_end_of_anim) {
        tp->is_alive_on_end_of_anim_set(true);
      }
      tile->is_alive_on_end_of_anim       = is_alive_on_end_of_anim;
      tile->is_alive_on_end_of_ascii_anim = is_alive_on_end_of_ascii_anim;
      tile->is_resurrecting               = is_resurrecting;

      if (tile->is_hp_25_percent || tile->is_hp_50_percent || tile->is_hp_75_percent || tile->is_hp_100_percent) {
        tp->internal_has_hp_anim_set(true);
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
        tp->internal_has_dir_anim_set(true);
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

PyObject *tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_NONE, 1));
}
PyObject *top1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_UP, 1));
}
PyObject *bot1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_DOWN, 1));
}
PyObject *left1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_LEFT, 1));
}
PyObject *right1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_RIGHT, 1));
}
PyObject *tl1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_TL, 1));
}
PyObject *tr1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_TR, 1));
}
PyObject *bl1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_BL, 1));
}
PyObject *br1_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_BR, 1));
}
PyObject *top2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_UP, 2));
}
PyObject *bot2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_DOWN, 2));
}
PyObject *bot3_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_DOWN, 3));
}
PyObject *left2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_LEFT, 2));
}
PyObject *right2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_RIGHT, 2));
}
PyObject *tl2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_TL, 2));
}
PyObject *tr2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_TR, 2));
}
PyObject *bl2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_BL, 2));
}
PyObject *br2_tile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  return (tile_dir(obj, args, keywds, THING_DIR_BR, 2));
}
