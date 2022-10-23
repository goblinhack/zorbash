//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_py_tp.hpp"
#include "my_python.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

PyObject *tp_load_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  PyObject *py_class = nullptr;

  static char *kwlist[] = {(char *) "tp", nullptr};

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

  char *tp_text_long_name = py_obj_attr_str(py_class, "text_long_name");
  if (! tp_text_long_name) {
    ERR("tp_load: Missing tp text_long_name");
    Py_RETURN_FALSE;
  }

  char *tp_text_short_name = py_obj_attr_str(py_class, "text_short_name");
  if (! tp_text_short_name) {
    ERR("tp_load: Missing tp text_short_name");
    Py_RETURN_FALSE;
  }

  int id;
  tp_get_id(tp_name, &id);
  tp_load(id, tp_name, tp_text_long_name, tp_text_short_name);

  myfree(tp_name);
  myfree(tp_text_long_name);
  myfree(tp_text_short_name);

  Py_RETURN_TRUE;
}

#define TP_BODY_SET_STRING(__field__)                                                                                \
  PyObject *__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
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
    tp->__field__##_set(std::string(value ? value : ""));                                                            \
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
  PyObject *__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
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
    tp->__field__(std::string(value ? value : ""));                                                                  \
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
  PyObject *__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
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
    tp->__field__((__str2val__) (value));                                                                            \
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
  PyObject *__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
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
    tp->__field__##_set(value);                                                                                      \
                                                                                                                     \
  done:                                                                                                              \
    if (tp_name) {                                                                                                   \
      myfree(tp_name);                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define TP_BODY_SET_INT_INT(__field__)                                                                               \
  PyObject *__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
  {                                                                                                                  \
    PyObject *py_class = 0;                                                                                          \
    char     *tp_name  = 0;                                                                                          \
    int       value    = 0;                                                                                          \
    int       value2   = 0;                                                                                          \
    Tpp       tp;                                                                                                    \
                                                                                                                     \
    static char *kwlist[] = {(char *) "class", (char *) "value", (char *) "value2", 0};                              \
                                                                                                                     \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "O|ii", kwlist, &py_class, &value, &value2)) {                   \
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
    tp->__field__##_set(value, value2);                                                                              \
                                                                                                                     \
  done:                                                                                                              \
    if (tp_name) {                                                                                                   \
      myfree(tp_name);                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define TP_BODY_SET_DOUBLE(__field__)                                                                                \
  PyObject *__field__(PyObject *obj, PyObject *args, PyObject *keywds)                                               \
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
    tp->__field__##_set(value);                                                                                      \
  done:                                                                                                              \
    if (tp_name) {                                                                                                   \
      myfree(tp_name);                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Py_RETURN_TRUE;                                                                                                  \
  }

PyObject *tp_update_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  PyObject *py_class = nullptr;
  char     *tp_name  = nullptr;
  int       value    = 0;
  Tpp       tp;

  static char *kwlist[] = {(char *) "class", (char *) "value", nullptr};

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

PyObject *spawn_next_to_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", nullptr};

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

  PY_DBG("%s(%X, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->spawn_next_to(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_next_to_or_on_monst_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", nullptr};

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

  PY_DBG("%s(%X, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->spawn_next_to_or_on_monst(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_using_items_radius_range_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what       = nullptr;
  uint32_t id         = 0;
  uint32_t parent_id  = 0;
  uint32_t victim_id  = 0;
  uint32_t radius_min = 0;
  uint32_t radius_max = 0;

  static char *kwlist[] = {(char *) "id",   (char *) "parent_id", (char *) "victim_id",
                           (char *) "what", (char *) "min",       (char *) "max",
                           nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIIs|ii", kwlist, &id, &parent_id, &victim_id, &what, &radius_min,
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

  if (! victim_id) {
    ERR("%s: Missing 'victim_id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: Missing 'what'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%X, %s, %u, %u)", __FUNCTION__, id, what, radius_min, radius_max);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find 'me' thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  auto parent = level->thing_find(ThingId(parent_id));
  if (! parent) {
    ERR("%s: Cannot find parent thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  auto target = level->thing_find(ThingId(victim_id));
  if (! target) {
    ERR("%s: Cannot find target thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  //
  // This is intentionally 0,0 to use the items range unless overridden
  //
  if (! radius_max) {
    if (t->blast_max_radius()) {
      radius_max = t->blast_max_radius();
    }
  }

  if (t->spawn_radius_range(parent, target, std::string(what), radius_min,
                            radius_max)) { // + parent->enchant_get())) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_radius_range_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what       = nullptr;
  uint32_t id         = 0;
  uint32_t radius_min = 0;
  uint32_t radius_max = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", (char *) "min", (char *) "max", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is|ii", kwlist, &id, &what, &radius_min, &radius_max)) {
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

  PY_DBG("%s(%X, %s, %u, %u)", __FUNCTION__, id, what, radius_min, radius_max);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find 'me' thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->spawn_radius_range(std::string(what), radius_min,
                            radius_max)) { // + parent->enchant_get())) {
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

  static char *kwlist[] = {(char *) "id", (char *) "what", (char *) "x", (char *) "y", nullptr};

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

  PY_DBG("%s(%X, %s, %d, %d)", __FUNCTION__, id, what, x, y);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
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

  static char *kwlist[] = {(char *) "id", (char *) "what", nullptr};

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

  PY_DBG("%s(%X, %s)", __FUNCTION__, id, what);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->matches(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_at(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;
  int      x    = -1;
  int      y    = -1;

  static char *kwlist[] = {(char *) "id", (char *) "what", (char *) "x", (char *) "y", nullptr};

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

  PY_DBG("%s(%X, %s, %d, %d)", __FUNCTION__, id, what, x, y);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->place(std::string(what), point(x, y))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

// begin sort marker1 {
TP_BODY_SET_INT(aggression_pct)
TP_BODY_SET_INT(ai_detect_secret_doors)
TP_BODY_SET_INT(ai_obstacle)
TP_BODY_SET_INT(ai_resent_count)
TP_BODY_SET_INT(ai_shove_chance_d1000)
TP_BODY_SET_INT(ai_wanderer)
TP_BODY_SET_INT(appearing_chance_d1000)
TP_BODY_SET_INT(attack_eater)
TP_BODY_SET_INT(attack_engulf_chance_d1000)
TP_BODY_SET_INT(attack_humanoid)
TP_BODY_SET_INT(attack_living)
TP_BODY_SET_INT(attack_lunge)
TP_BODY_SET_INT(attack_meat)
TP_BODY_SET_INT(attack_no_msg)
TP_BODY_SET_INT(attacks_per_round)
TP_BODY_SET_INT(attack_undead)
TP_BODY_SET_INT(bite_amount)
TP_BODY_SET_INT(blast_max_radius)
TP_BODY_SET_INT(blast_min_radius)
TP_BODY_SET_INT(blit_bot_off)
TP_BODY_SET_INT(blit_left_off)
TP_BODY_SET_INT(blit_right_off)
TP_BODY_SET_INT(blit_top_off)
TP_BODY_SET_INT(capacity_height)
TP_BODY_SET_INT(capacity_width)
TP_BODY_SET_INT(charge_count)
TP_BODY_SET_INT(collateral_damage_pct)
TP_BODY_SET_INT(collision_check)
TP_BODY_SET_INT(collision_hit_180)
TP_BODY_SET_INT(collision_hit_360)
TP_BODY_SET_INT(collision_hit_adj)
TP_BODY_SET_INT(collision_hit_priority)
TP_BODY_SET_INT(collision_hit_two_tiles_ahead)
TP_BODY_SET_INT(crit_chance_d10000)
TP_BODY_SET_INT(damaged_chance_d10000)
TP_BODY_SET_INT(damage_received_doubled_from_acid)
TP_BODY_SET_INT(damage_received_doubled_from_cold)
TP_BODY_SET_INT(damage_received_doubled_from_fire)
TP_BODY_SET_INT(damage_received_doubled_from_necrosis)
TP_BODY_SET_INT(damage_received_doubled_from_poison)
TP_BODY_SET_INT(damage_received_doubled_from_water)
TP_BODY_SET_INT(distance_avoid)
TP_BODY_SET_INT(distance_leader_max)
TP_BODY_SET_INT(distance_minion_vision_shared)
TP_BODY_SET_INT(distance_mob_max)
TP_BODY_SET_INT(distance_recruitment_max)
TP_BODY_SET_INT(distance_throw)
TP_BODY_SET_INT(distance_vision)
TP_BODY_SET_INT(enchant_max)
TP_BODY_SET_INT(environ_avoids_acid)
TP_BODY_SET_INT(environ_avoids_cold)
TP_BODY_SET_INT(environ_avoids_fire)
TP_BODY_SET_INT(environ_avoids_necrosis)
TP_BODY_SET_INT(environ_avoids_poison)
TP_BODY_SET_INT(environ_avoids_water)
TP_BODY_SET_INT(gfx_ascii_animated)
TP_BODY_SET_INT(gfx_ascii_bg_color_spread_alpha)
TP_BODY_SET_INT(gfx_ascii_bg_color_spread_blue)
TP_BODY_SET_INT(gfx_ascii_bg_color_spread_green)
TP_BODY_SET_INT(gfx_ascii_bg_color_spread_hue)
TP_BODY_SET_INT(gfx_ascii_bg_color_spread_red)
TP_BODY_SET_INT(gfx_ascii_color_is_animated)
TP_BODY_SET_INT(gfx_ascii_fade_with_dist)
TP_BODY_SET_INT(gfx_ascii_fg_color_spread_alpha)
TP_BODY_SET_INT(gfx_ascii_fg_color_spread_blue)
TP_BODY_SET_INT(gfx_ascii_fg_color_spread_green)
TP_BODY_SET_INT(gfx_ascii_fg_color_spread_hue)
TP_BODY_SET_INT(gfx_ascii_fg_color_spread_red)
TP_BODY_SET_INT(gfx_ascii_shown)
TP_BODY_SET_INT(gfx_ascii_shown_as_gray_in_shadow)
TP_BODY_SET_INT(gfx_ascii_shown_in_bg)
TP_BODY_SET_INT(gfx_glows)
TP_BODY_SET_INT(gfx_on_fire_anim)
TP_BODY_SET_INT(gfx_oversized_and_on_floor)
TP_BODY_SET_INT(gfx_pixelart_animated)
TP_BODY_SET_INT(gfx_pixelart_animated_can_hflip)
TP_BODY_SET_INT(gfx_pixelart_animated_can_vflip)
TP_BODY_SET_INT(gfx_pixelart_animated_no_dir)
TP_BODY_SET_INT(gfx_pixelart_anim_synced_with_owner)
TP_BODY_SET_INT(gfx_pixelart_attack_anim)
TP_BODY_SET_INT(gfx_pixelart_bounce_always)
TP_BODY_SET_INT(gfx_pixelart_bounce_on_move)
TP_BODY_SET_INT(gfx_pixelart_equip_carry_anim)
TP_BODY_SET_INT(gfx_pixelart_flickers)
TP_BODY_SET_INT(gfx_pixelart_health_bar_autohide)
TP_BODY_SET_INT(gfx_pixelart_health_bar_only_when_awake)
TP_BODY_SET_INT(gfx_pixelart_health_bar_shown)
TP_BODY_SET_INT(gfx_pixelart_reflection)
TP_BODY_SET_INT(gfx_pixelart_shadow)
TP_BODY_SET_INT(gfx_pixelart_shadow_long)
TP_BODY_SET_INT(gfx_pixelart_shadow_short)
TP_BODY_SET_INT(gfx_pixelart_shadow_solid)
TP_BODY_SET_INT(gfx_pixelart_shadow_very_short)
TP_BODY_SET_INT(gfx_pixelart_show_asleep_anim)
TP_BODY_SET_INT(gfx_pixelart_shown_in_bg)
TP_BODY_SET_INT(gfx_pixelart_show_outlined)
TP_BODY_SET_INT(gfx_pixelart_wobbles_when_hit)
TP_BODY_SET_INT(gfx_water)
TP_BODY_SET_INT(hunger_clock_tick_freq)
TP_BODY_SET_INT(hunger_is_hunger_level_hungry_at_pct)
TP_BODY_SET_INT(hunger_is_hunger_level_starving_at_pct)
TP_BODY_SET_INT(hunger_is_insatiable)
TP_BODY_SET_INT_INT(damage_acid_chance_d1000)
TP_BODY_SET_INT_INT(damage_bite_chance_d1000)
TP_BODY_SET_INT_INT(damage_claw_chance_d1000)
TP_BODY_SET_INT_INT(damage_cold_chance_d1000)
TP_BODY_SET_INT_INT(damage_crush_chance_d1000)
TP_BODY_SET_INT_INT(damage_digest_chance_d1000)
TP_BODY_SET_INT_INT(damage_draining_chance_d1000)
TP_BODY_SET_INT_INT(damage_energy_chance_d1000)
TP_BODY_SET_INT_INT(damage_fire_chance_d1000)
TP_BODY_SET_INT_INT(damage_future1_chance_d1000)
TP_BODY_SET_INT_INT(damage_lightning_chance_d1000)
TP_BODY_SET_INT_INT(damage_melee_chance_d1000)
TP_BODY_SET_INT_INT(damage_nat_att_chance_d1000)
TP_BODY_SET_INT_INT(damage_necrosis_chance_d1000)
TP_BODY_SET_INT_INT(damage_poison_chance_d1000)
TP_BODY_SET_INT_INT(damage_water_chance_d1000)
TP_BODY_SET_INT(is_able_to_attack_mobs)
TP_BODY_SET_INT(is_able_to_attack_owner)
TP_BODY_SET_INT(is_able_to_be_surprised)
TP_BODY_SET_INT(is_able_to_break_down_doors)
TP_BODY_SET_INT(is_able_to_break_out_of_ice)
TP_BODY_SET_INT(is_able_to_break_out_of_webs)
TP_BODY_SET_INT(is_able_to_burn)
TP_BODY_SET_INT(is_able_to_change_levels)
TP_BODY_SET_INT(is_able_to_collect_keys)
TP_BODY_SET_INT(is_able_to_enchant_items)
TP_BODY_SET_INT(is_able_to_fall)
TP_BODY_SET_INT(is_able_to_fire_at)
TP_BODY_SET_INT(is_able_to_follow)
TP_BODY_SET_INT(is_able_to_freeze)
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
TP_BODY_SET_INT(is_able_to_move_diagonally)
TP_BODY_SET_INT(is_able_to_open_doors)
TP_BODY_SET_INT(is_able_to_rest)
TP_BODY_SET_INT(is_able_to_see_in_the_dark)
TP_BODY_SET_INT(is_able_to_see_through_doors)
TP_BODY_SET_INT(is_able_to_shove)
TP_BODY_SET_INT(is_able_to_sleep)
TP_BODY_SET_INT(is_able_to_swim)
TP_BODY_SET_INT(is_able_to_teleport_attack)
TP_BODY_SET_INT(is_able_to_teleport_attack_chance_d1000)
TP_BODY_SET_INT(is_able_to_teleport_escape)
TP_BODY_SET_INT(is_able_to_teleport_without_tiring)
TP_BODY_SET_INT(is_able_to_tire)
TP_BODY_SET_INT(is_able_to_use_amulet)
TP_BODY_SET_INT(is_able_to_use_armor)
TP_BODY_SET_INT(is_able_to_use_boots)
TP_BODY_SET_INT(is_able_to_use_cloak)
TP_BODY_SET_INT(is_able_to_use_gauntlet)
TP_BODY_SET_INT(is_able_to_use_helmet)
TP_BODY_SET_INT(is_able_to_use_rings)
TP_BODY_SET_INT(is_able_to_use_shield)
TP_BODY_SET_INT(is_able_to_use_wands_or_staffs)
TP_BODY_SET_INT(is_able_to_use_weapons)
TP_BODY_SET_INT(is_able_to_walk_through_walls)
TP_BODY_SET_INT(is_acid)
TP_BODY_SET_INT(is_air_breather)
TP_BODY_SET_INT(is_alive_on_end_of_anim)
TP_BODY_SET_INT(is_always_hit)
TP_BODY_SET_INT(is_amulet)
TP_BODY_SET_INT(is_aquatic)
TP_BODY_SET_INT(is_armor)
TP_BODY_SET_INT(is_ascend_dungeon)
TP_BODY_SET_INT(is_ascend_sewer)
TP_BODY_SET_INT(is_asleep_initially)
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
TP_BODY_SET_INT(is_basalt)
TP_BODY_SET_INT(is_biome_dungeon)
TP_BODY_SET_INT(is_biome_sewer)
TP_BODY_SET_INT(is_biome_swamp)
TP_BODY_SET_INT(is_biome_unused)
TP_BODY_SET_INT(is_bleeder)
TP_BODY_SET_INT(is_block_of_ice)
TP_BODY_SET_INT(is_bones)
TP_BODY_SET_INT(is_boots)
TP_BODY_SET_INT(is_brazier)
TP_BODY_SET_INT(is_bridge)
TP_BODY_SET_INT(is_brittle)
TP_BODY_SET_INT(is_buff)
TP_BODY_SET_INT(is_carnivorous_plant)
TP_BODY_SET_INT(is_carrier_of_treasure_class_a)
TP_BODY_SET_INT(is_carrier_of_treasure_class_b)
TP_BODY_SET_INT(is_carrier_of_treasure_class_c)
TP_BODY_SET_INT(is_carrier_of_weapon_class_a)
TP_BODY_SET_INT(is_carrier_of_weapon_class_b)
TP_BODY_SET_INT(is_carrier_of_weapon_class_c)
TP_BODY_SET_INT(is_chasm)
TP_BODY_SET_INT(is_cloak)
TP_BODY_SET_INT(is_cold)
TP_BODY_SET_INT(is_collectable)
TP_BODY_SET_INT(is_collected_as_gold)
TP_BODY_SET_INT(is_collected_as_keys)
TP_BODY_SET_INT(is_combustible)
TP_BODY_SET_INT(is_corpse_on_death)
TP_BODY_SET_INT(is_corpse_with_bones)
TP_BODY_SET_INT(is_corridor)
TP_BODY_SET_INT(is_cowardly)
TP_BODY_SET_INT(is_critical_to_level)
TP_BODY_SET_INT(is_crushable)
TP_BODY_SET_INT(is_crystal)
TP_BODY_SET_INT(is_cursor)
TP_BODY_SET_INT(is_cursor_can_hover_over)
TP_BODY_SET_INT(is_cursor_can_hover_over_x2_click)
TP_BODY_SET_INT(is_cursor_path)
TP_BODY_SET_INT(is_cursor_path_blocker)
TP_BODY_SET_INT(is_cursor_path_hazard)
TP_BODY_SET_INT(is_dagger)
TP_BODY_SET_INT(is_dead_on_end_of_anim)
TP_BODY_SET_INT(is_dead_on_falling)
TP_BODY_SET_INT(is_dead_on_shove)
TP_BODY_SET_INT(is_debuff)
TP_BODY_SET_INT(is_debug_path)
TP_BODY_SET_INT(is_debug_type)
TP_BODY_SET_INT(is_deep_water)
TP_BODY_SET_INT(is_deep_water_swimmer)
TP_BODY_SET_INT(is_descend_dungeon)
TP_BODY_SET_INT(is_descend_sewer)
TP_BODY_SET_INT(is_described_when_hovering_over)
TP_BODY_SET_INT(is_destroyed_on_hit_or_miss)
TP_BODY_SET_INT(is_destroyed_on_hitting)
TP_BODY_SET_INT(is_dirt)
TP_BODY_SET_INT(is_door)
TP_BODY_SET_INT(is_droppable)
TP_BODY_SET_INT(is_dry_grass)
TP_BODY_SET_INT(is_dry_grass_trampled)
TP_BODY_SET_INT(is_eater_of_amulets)
TP_BODY_SET_INT(is_eater_of_armor)
TP_BODY_SET_INT(is_eater_of_boots)
TP_BODY_SET_INT(is_eater_of_cloaks)
TP_BODY_SET_INT(is_eater_of_food)
TP_BODY_SET_INT(is_eater_of_gauntlets)
TP_BODY_SET_INT(is_eater_of_green_blood)
TP_BODY_SET_INT(is_eater_of_helmets)
TP_BODY_SET_INT(is_eater_of_jelly)
TP_BODY_SET_INT(is_eater_of_magical_items)
TP_BODY_SET_INT(is_eater_of_meat)
TP_BODY_SET_INT(is_eater_of_potions)
TP_BODY_SET_INT(is_eater_of_red_blood)
TP_BODY_SET_INT(is_eater_of_rings)
TP_BODY_SET_INT(is_eater_of_shields)
TP_BODY_SET_INT(is_eater_of_staffs)
TP_BODY_SET_INT(is_eater_of_treasure)
TP_BODY_SET_INT(is_eater_of_wands)
TP_BODY_SET_INT(is_eater_of_weapons)
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
TP_BODY_SET_INT(is_flat)
TP_BODY_SET_INT(is_floating)
TP_BODY_SET_INT(is_floor)
TP_BODY_SET_INT(is_floor_deco)
TP_BODY_SET_INT(is_flying)
TP_BODY_SET_INT(is_foilage)
TP_BODY_SET_INT(is_food)
TP_BODY_SET_INT(is_gas_blocker)
TP_BODY_SET_INT(is_gauntlet)
TP_BODY_SET_INT(is_gelatinous)
TP_BODY_SET_INT(is_glass)
TP_BODY_SET_INT(is_gold)
TP_BODY_SET_INT(is_green_blood)
TP_BODY_SET_INT(is_green_blooded)
TP_BODY_SET_INT(is_green_splatter)
TP_BODY_SET_INT(is_hard)
TP_BODY_SET_INT(is_hazard)
TP_BODY_SET_INT(is_health_booster)
TP_BODY_SET_INT(is_heavy)
TP_BODY_SET_INT(is_helmet)
TP_BODY_SET_INT(is_hittable)
TP_BODY_SET_INT(is_humanoid)
TP_BODY_SET_INT(is_immune_to_acid)
TP_BODY_SET_INT(is_immune_to_cold)
TP_BODY_SET_INT(is_immune_to_draining)
TP_BODY_SET_INT(is_immune_to_fire)
TP_BODY_SET_INT(is_immune_to_necrosis)
TP_BODY_SET_INT(is_immune_to_poison)
TP_BODY_SET_INT(is_immune_to_spiderwebs)
TP_BODY_SET_INT(is_immune_to_water)
TP_BODY_SET_INT(is_intelligent)
TP_BODY_SET_INT(is_interesting)
TP_BODY_SET_INT(is_internal)
TP_BODY_SET_INT(is_item)
TP_BODY_SET_INT(is_item_carrier)
TP_BODY_SET_INT(is_item_collector)
TP_BODY_SET_INT(is_item_organic)
TP_BODY_SET_INT(is_item_targetted)
TP_BODY_SET_INT(is_jelly)
TP_BODY_SET_INT(is_jump_blocker)
TP_BODY_SET_INT(is_key)
TP_BODY_SET_INT(is_key_special)
TP_BODY_SET_INT(is_laser)
TP_BODY_SET_INT(is_lava)
TP_BODY_SET_INT(is_lifeless)
TP_BODY_SET_INT(is_light_blocker)
TP_BODY_SET_INT(is_light_blocker_for_monst)
TP_BODY_SET_INT(is_living)
TP_BODY_SET_INT(is_loggable)
TP_BODY_SET_INT(is_magical)
TP_BODY_SET_INT(is_map_beast)
TP_BODY_SET_INT(is_map_treasure)
TP_BODY_SET_INT(is_meat)
TP_BODY_SET_INT(is_meltable)
TP_BODY_SET_INT(is_metal)
TP_BODY_SET_INT(is_minion)
TP_BODY_SET_INT(is_mob)
TP_BODY_SET_INT(is_mob_challenge_class_a)
TP_BODY_SET_INT(is_mob_challenge_class_b)
TP_BODY_SET_INT(is_monst)
TP_BODY_SET_INT(is_monst_class_a)
TP_BODY_SET_INT(is_monst_class_b)
TP_BODY_SET_INT(is_monst_class_c)
TP_BODY_SET_INT(is_monst_class_d)
TP_BODY_SET_INT(is_monst_class_e)
TP_BODY_SET_INT(is_monst_pack)
TP_BODY_SET_INT(is_moveable)
TP_BODY_SET_INT(is_msg)
TP_BODY_SET_INT(is_msg_allowed_is_seen)
TP_BODY_SET_INT(is_msg_allowed_is_surprised)
TP_BODY_SET_INT(is_msg_allowed_is_wounded)
TP_BODY_SET_INT(is_necrotic_danger_level)
TP_BODY_SET_INT(is_no_tile)
TP_BODY_SET_INT(is_obs_destructable)
TP_BODY_SET_INT(is_obs_for_jump_landing)
TP_BODY_SET_INT(is_obs_for_shoving)
TP_BODY_SET_INT(is_obstacle_when_dead)
TP_BODY_SET_INT(is_obs_wall_or_door)
TP_BODY_SET_INT(is_openable)
TP_BODY_SET_INT(is_organic)
TP_BODY_SET_INT(is_pillar)
TP_BODY_SET_INT(is_plant)
TP_BODY_SET_INT(is_player)
TP_BODY_SET_INT(is_poisonous_danger_level)
TP_BODY_SET_INT(is_potion)
TP_BODY_SET_INT(is_projectile)
TP_BODY_SET_INT(is_red_blood)
TP_BODY_SET_INT(is_red_blooded)
TP_BODY_SET_INT(is_red_splatter)
TP_BODY_SET_INT(is_removeable_if_out_of_slots)
TP_BODY_SET_INT(is_resurrectable)
TP_BODY_SET_INT(is_ring)
TP_BODY_SET_INT(is_ripple)
TP_BODY_SET_INT(is_rock)
TP_BODY_SET_INT(is_rusty)
TP_BODY_SET_INT(is_secret_door)
TP_BODY_SET_INT(is_sewer_wall)
TP_BODY_SET_INT(is_shallow_water)
TP_BODY_SET_INT(is_shallow_water_swimmer)
TP_BODY_SET_INT(is_shield)
TP_BODY_SET_INT(is_shovable)
TP_BODY_SET_INT(is_shovable_and_sticky)
TP_BODY_SET_INT(is_skill)
TP_BODY_SET_INT(is_skillstone)
TP_BODY_SET_INT(is_slippery)
TP_BODY_SET_INT(is_smoke)
TP_BODY_SET_INT(is_snake)
TP_BODY_SET_INT(is_soft)
TP_BODY_SET_INT(is_spawner)
TP_BODY_SET_INT(is_spider)
TP_BODY_SET_INT(is_spiderweb)
TP_BODY_SET_INT(is_staff)
TP_BODY_SET_INT(is_steal_item_chance_d1000)
TP_BODY_SET_INT(is_steam)
TP_BODY_SET_INT(is_sticky)
TP_BODY_SET_INT(is_stone)
TP_BODY_SET_INT(is_submerged)
TP_BODY_SET_INT(is_swimmer)
TP_BODY_SET_INT(is_sword)
TP_BODY_SET_INT(is_target_radial)
TP_BODY_SET_INT(is_target_select)
TP_BODY_SET_INT(is_temperature_change_sensitive)
TP_BODY_SET_INT(is_temperature_sensitive)
TP_BODY_SET_INT(is_the_grid)
TP_BODY_SET_INT(is_thief)
TP_BODY_SET_INT(is_throwable)
TP_BODY_SET_INT(is_throw_blocker)
TP_BODY_SET_INT(is_tickable)
TP_BODY_SET_INT(is_tireless)
TP_BODY_SET_INT(is_tmp_thing)
TP_BODY_SET_INT(is_torch)
TP_BODY_SET_INT(is_treasure)
TP_BODY_SET_INT(is_treasure_chest)
TP_BODY_SET_INT(is_treasure_class_a)
TP_BODY_SET_INT(is_treasure_class_b)
TP_BODY_SET_INT(is_treasure_class_c)
TP_BODY_SET_INT(is_treasure_type)
TP_BODY_SET_INT(is_undead)
TP_BODY_SET_INT(is_usable)
TP_BODY_SET_INT(is_used_when_thrown)
TP_BODY_SET_INT(is_very_combustible)
TP_BODY_SET_INT(is_very_hard)
TP_BODY_SET_INT(is_very_heavy)
TP_BODY_SET_INT(is_wall)
TP_BODY_SET_INT(is_wall_dungeon)
TP_BODY_SET_INT(is_wand)
TP_BODY_SET_INT(is_weapon)
TP_BODY_SET_INT(is_weapon_class_a)
TP_BODY_SET_INT(is_weapon_class_b)
TP_BODY_SET_INT(is_weapon_class_c)
TP_BODY_SET_INT(is_wet_grass)
TP_BODY_SET_INT(is_wooden)
TP_BODY_SET_INT(item_height)
TP_BODY_SET_INT(item_width)
TP_BODY_SET_INT(jump_distance)
TP_BODY_SET_INT(jump_distance_mod)
TP_BODY_SET_INT(light_dist)
TP_BODY_SET_INT(melting_chance_d1000)
TP_BODY_SET_INT(minion_limit)
TP_BODY_SET_INT(move_speed)
TP_BODY_SET_INT(move_speed_mod)
TP_BODY_SET_INT(noise_additional_on_jump_end)
TP_BODY_SET_INT(noise_additional_on_teleporting)
TP_BODY_SET_INT(noise_blocker)
TP_BODY_SET_INT(noise_decibels_hearing)
TP_BODY_SET_INT(noise_on_born)
TP_BODY_SET_INT(noise_on_dropping)
TP_BODY_SET_INT(noise_on_moving)
TP_BODY_SET_INT(noise_on_open)
TP_BODY_SET_INT(noise_on_you_are_hit_and_now_dead)
TP_BODY_SET_INT(noise_on_you_are_hit_but_still_alive)
TP_BODY_SET_INT(normal_placement_rules)
TP_BODY_SET_INT(on_death_drop_all_items)
TP_BODY_SET_INT(on_death_is_open)
TP_BODY_SET_INT(range_max)
TP_BODY_SET_INT(rarity)
TP_BODY_SET_INT(shove_strength)
TP_BODY_SET_INT(shove_strength_mod)
TP_BODY_SET_INT(spawn_group_radius)
TP_BODY_SET_INT(stamina)
TP_BODY_SET_INT(stamina_drain_on_attacking)
TP_BODY_SET_INT(stamina_drain_on_using)
TP_BODY_SET_INT(stat_att)
TP_BODY_SET_INT(stat_att_mod)
TP_BODY_SET_INT(stat_att_penalty_when_idle)
TP_BODY_SET_INT(stat_att_penalty_when_idle_max)
TP_BODY_SET_INT(stat_att_penalty_when_in_deep_water)
TP_BODY_SET_INT(stat_att_penalty_when_in_shallow_water)
TP_BODY_SET_INT(stat_att_penalty_when_stuck)
TP_BODY_SET_INT(stat_att_penalty_when_stuck_max)
TP_BODY_SET_INT(stat_con)
TP_BODY_SET_INT(stat_con_mod)
TP_BODY_SET_INT(stat_def)
TP_BODY_SET_INT(stat_def_mod)
TP_BODY_SET_INT(stat_def_penalty_when_idle)
TP_BODY_SET_INT(stat_def_penalty_when_idle_max)
TP_BODY_SET_INT(stat_def_penalty_when_in_deep_water)
TP_BODY_SET_INT(stat_def_penalty_when_in_shallow_water)
TP_BODY_SET_INT(stat_def_penalty_when_stuck)
TP_BODY_SET_INT(stat_def_penalty_when_stuck_max)
TP_BODY_SET_INT(stat_dex)
TP_BODY_SET_INT(stat_dex_mod)
TP_BODY_SET_INT(stat_luck)
TP_BODY_SET_INT(stat_luck_mod)
TP_BODY_SET_INT(stats02)
TP_BODY_SET_INT(stats03)
TP_BODY_SET_INT(stats04)
TP_BODY_SET_INT(stats05)
TP_BODY_SET_INT(stats06)
TP_BODY_SET_INT(stats07)
TP_BODY_SET_INT(stats09)
TP_BODY_SET_INT(stat_str)
TP_BODY_SET_INT(stat_str_mod)
TP_BODY_SET_INT(teleport_distance)
TP_BODY_SET_INT(temperature)
TP_BODY_SET_INT(thing_size)
TP_BODY_SET_INT(tick_prio)
TP_BODY_SET_INT(unused_chance1_d1000)
TP_BODY_SET_INT(unused_chance2_d1000)
TP_BODY_SET_INT(unused_chance3_d1000)
TP_BODY_SET_INT(unused_chance4_d1000)
TP_BODY_SET_INT(unused_chance5_d1000)
TP_BODY_SET_INT(unused_chance6_d1000)
TP_BODY_SET_INT(unused_flag1)
TP_BODY_SET_INT(unused_flag10)
TP_BODY_SET_INT(unused_flag103)
TP_BODY_SET_INT(unused_flag11)
TP_BODY_SET_INT(unused_flag12)
TP_BODY_SET_INT(unused_flag123)
TP_BODY_SET_INT(unused_flag13)
TP_BODY_SET_INT(unused_flag14)
TP_BODY_SET_INT(unused_flag15)
TP_BODY_SET_INT(unused_flag16)
TP_BODY_SET_INT(unused_flag17)
TP_BODY_SET_INT(unused_flag18)
TP_BODY_SET_INT(unused_flag19)
TP_BODY_SET_INT(unused_flag2)
TP_BODY_SET_INT(unused_flag20)
TP_BODY_SET_INT(unused_flag21)
TP_BODY_SET_INT(unused_flag22)
TP_BODY_SET_INT(unused_flag23)
TP_BODY_SET_INT(unused_flag24)
TP_BODY_SET_INT(unused_flag25)
TP_BODY_SET_INT(unused_flag26)
TP_BODY_SET_INT(unused_flag27)
TP_BODY_SET_INT(unused_flag28)
TP_BODY_SET_INT(unused_flag29)
TP_BODY_SET_INT(unused_flag3)
TP_BODY_SET_INT(unused_flag30)
TP_BODY_SET_INT(unused_flag31)
TP_BODY_SET_INT(unused_flag32)
TP_BODY_SET_INT(unused_flag33)
TP_BODY_SET_INT(unused_flag34)
TP_BODY_SET_INT(unused_flag35)
TP_BODY_SET_INT(unused_flag36)
TP_BODY_SET_INT(unused_flag37)
TP_BODY_SET_INT(unused_flag38)
TP_BODY_SET_INT(unused_flag39)
TP_BODY_SET_INT(unused_flag4)
TP_BODY_SET_INT(unused_flag40)
TP_BODY_SET_INT(unused_flag41)
TP_BODY_SET_INT(unused_flag48)
TP_BODY_SET_INT(unused_flag5)
TP_BODY_SET_INT(unused_flag56)
TP_BODY_SET_INT(unused_flag6)
TP_BODY_SET_INT(unused_flag7)
TP_BODY_SET_INT(unused_flag8)
TP_BODY_SET_INT(unused_flag87)
TP_BODY_SET_INT(unused_flag9)
TP_BODY_SET_INT(weapon_damage)
TP_BODY_SET_INT(z_depth)
TP_BODY_SET_INT(z_prio)
TP_BODY_SET_STRING(damage_acid_dice)
TP_BODY_SET_STRING(damage_bite_dice)
TP_BODY_SET_STRING(damage_claw_dice)
TP_BODY_SET_STRING(damage_cold_dice)
TP_BODY_SET_STRING(damage_crush_dice)
TP_BODY_SET_STRING(damage_digest_dice)
TP_BODY_SET_STRING(damage_draining_dice)
TP_BODY_SET_STRING(damage_energy_dice)
TP_BODY_SET_STRING(damage_fire_dice)
TP_BODY_SET_STRING(damage_future1_dice)
TP_BODY_SET_STRING(damage_lightning_dice)
TP_BODY_SET_STRING(damage_melee_dice)
TP_BODY_SET_STRING(damage_nat_att_dice)
TP_BODY_SET_STRING(damage_nat_att_type)
TP_BODY_SET_STRING(damage_necrosis_dice)
TP_BODY_SET_STRING(damage_poison_dice)
TP_BODY_SET_STRING(damage_water_dice)
TP_BODY_SET_STRING(equip_carry_anim)
TP_BODY_SET_STRING(gfx_anim_use)
TP_BODY_SET_STRING(gold_value_dice)
TP_BODY_SET_STRING(health_initial_dice)
TP_BODY_SET_STRING(is_allied_with)
TP_BODY_SET_STRING(lifespan_dice)
TP_BODY_SET_STRING(light_color)
TP_BODY_SET_STRING(name)
TP_BODY_SET_STRING(nutrition_dice)
TP_BODY_SET_STRING(on_attacking_dmg_acid_do)
TP_BODY_SET_STRING(on_attacking_dmg_bite_do)
TP_BODY_SET_STRING(on_attacking_dmg_claw_do)
TP_BODY_SET_STRING(on_attacking_dmg_cold_do)
TP_BODY_SET_STRING(on_attacking_dmg_crush_do)
TP_BODY_SET_STRING(on_attacking_dmg_digest_do)
TP_BODY_SET_STRING(on_attacking_dmg_draining_do)
TP_BODY_SET_STRING(on_attacking_dmg_energy_do)
TP_BODY_SET_STRING(on_attacking_dmg_fire_do)
TP_BODY_SET_STRING(on_attacking_dmg_future1_do)
TP_BODY_SET_STRING(on_attacking_dmg_lightning_do)
TP_BODY_SET_STRING(on_attacking_dmg_melee_do)
TP_BODY_SET_STRING(on_attacking_dmg_nat_att_do)
TP_BODY_SET_STRING(on_attacking_dmg_necrosis_do)
TP_BODY_SET_STRING(on_attacking_dmg_poison_do)
TP_BODY_SET_STRING(on_attacking_dmg_stat_att_do)
TP_BODY_SET_STRING(on_attacking_dmg_stat_con_do)
TP_BODY_SET_STRING(on_attacking_dmg_stat_str_do)
TP_BODY_SET_STRING(on_attacking_dmg_water_do)
TP_BODY_SET_STRING(on_awake_do)
TP_BODY_SET_STRING(on_born_do)
TP_BODY_SET_STRING(on_death_do)
TP_BODY_SET_STRING(on_death_of_a_follower_do)
TP_BODY_SET_STRING(on_death_of_my_leader_do)
TP_BODY_SET_STRING(on_dropped_do)
TP_BODY_SET_STRING(on_enchant_do)
TP_BODY_SET_STRING(on_equip_do)
TP_BODY_SET_STRING(on_fall_do)
TP_BODY_SET_STRING(on_final_use_do)
TP_BODY_SET_STRING(on_firing_at_something_do)
TP_BODY_SET_STRING(on_get_text_long_description_do)
TP_BODY_SET_STRING(on_idle_tick_freq_dice)
TP_BODY_SET_STRING(on_jump_do)
TP_BODY_SET_STRING(on_lifespan_tick_do)
TP_BODY_SET_STRING(on_move_do)
TP_BODY_SET_STRING(on_open_do)
TP_BODY_SET_STRING(on_owner_add_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_acid_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_bite_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_claw_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_cold_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_crush_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_digest_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_draining_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_energy_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_fire_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_future1_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_lightning_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_melee_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_nat_att_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_necrosis_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_poison_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_stat_att_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_stat_con_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_stat_str_do)
TP_BODY_SET_STRING(on_owner_attack_dmg_water_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_acid_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_bite_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_claw_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_cold_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_crush_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_digest_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_draining_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_energy_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_fire_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_future1_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_lightning_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_melee_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_nat_att_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_necrosis_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_poison_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_stat_att_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_stat_con_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_stat_str_do)
TP_BODY_SET_STRING(on_owner_receive_dmg_water_do)
TP_BODY_SET_STRING(on_owner_remove_do)
TP_BODY_SET_STRING(on_polymorphed_do)
TP_BODY_SET_STRING(on_receiving_dmg_acid_do)
TP_BODY_SET_STRING(on_receiving_dmg_bite_do)
TP_BODY_SET_STRING(on_receiving_dmg_claw_do)
TP_BODY_SET_STRING(on_receiving_dmg_cold_do)
TP_BODY_SET_STRING(on_receiving_dmg_crush_do)
TP_BODY_SET_STRING(on_receiving_dmg_digest_do)
TP_BODY_SET_STRING(on_receiving_dmg_draining_do)
TP_BODY_SET_STRING(on_receiving_dmg_energy_do)
TP_BODY_SET_STRING(on_receiving_dmg_fire_do)
TP_BODY_SET_STRING(on_receiving_dmg_future1_do)
TP_BODY_SET_STRING(on_receiving_dmg_lightning_do)
TP_BODY_SET_STRING(on_receiving_dmg_melee_do)
TP_BODY_SET_STRING(on_receiving_dmg_nat_att_do)
TP_BODY_SET_STRING(on_receiving_dmg_necrosis_do)
TP_BODY_SET_STRING(on_receiving_dmg_poison_do)
TP_BODY_SET_STRING(on_receiving_dmg_stat_att_do)
TP_BODY_SET_STRING(on_receiving_dmg_stat_con_do)
TP_BODY_SET_STRING(on_receiving_dmg_stat_str_do)
TP_BODY_SET_STRING(on_receiving_dmg_water_do)
TP_BODY_SET_STRING(on_resting_do)
TP_BODY_SET_STRING(on_stuck_do)
TP_BODY_SET_STRING(on_swing_do)
TP_BODY_SET_STRING(on_teleport_do)
TP_BODY_SET_STRING(on_thrown_do)
TP_BODY_SET_STRING(on_tick_do)
TP_BODY_SET_STRING(on_unequip_do)
TP_BODY_SET_STRING(on_use_do)
TP_BODY_SET_STRING(on_waiting_do)
TP_BODY_SET_STRING(on_you_are_declared_a_follower_do)
TP_BODY_SET_STRING(on_you_are_declared_leader_do)
TP_BODY_SET_STRING(on_you_are_hit_and_now_dead_do)
TP_BODY_SET_STRING(on_you_are_hit_but_dodge_it_do)
TP_BODY_SET_STRING(on_you_are_hit_but_still_alive_do)
TP_BODY_SET_STRING(on_you_are_on_fire_do)
TP_BODY_SET_STRING(on_you_nat_att_do)
TP_BODY_SET_STRING(resurrect_dice)
TP_BODY_SET_STRING(spawn_group_size_dice)
TP_BODY_SET_STRING(spawn_on_shoved)
TP_BODY_SET_STRING(str1)
TP_BODY_SET_STRING(str2)
TP_BODY_SET_STRING(str4)
TP_BODY_SET_STRING(target_name_laser)
TP_BODY_SET_STRING(target_name_projectile)
TP_BODY_SET_STRING(target_name_radial)
TP_BODY_SET_STRING(text_a_or_an)
TP_BODY_SET_STRING(text_debuff)
TP_BODY_SET_STRING(text_enchant)
TP_BODY_SET_STRING(text_hits)
TP_BODY_SET_STRING(text_long_description)
TP_BODY_SET_STRING(text_long_description2)
TP_BODY_SET_STRING(text_long_description3)
TP_BODY_SET_STRING(text_long_name)
TP_BODY_SET_STRING(text_short_description)
TP_BODY_SET_STRING(text_skill)
TP_BODY_SET_STRING(text_title)
TP_BODY_SET_STRING(text_unused)
TP_BODY_SET_STRING(text_unused1)
TP_BODY_SET_STRING(text_unused2)
TP_BODY_SET_STRING(text_unused3)
// end sort marker1 {
