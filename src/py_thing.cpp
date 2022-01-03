//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_hiscore.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_py_thing.hpp"
#include "my_python.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

#define THING_BODY_SET_INT(__func__, __api__)                                                                        \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    uint32_t     id       = 0;                                                                                       \
    uint32_t     value    = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", (char *) "value", 0};                                                    \
                                                                                                                     \
    LOG("Called %s", __FUNCTION__);                                                                                  \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "Ii", kwlist, &id, &value)) {                                    \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    t->__api__(value);                                                                                               \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define THING_BODY_GET_INT(__func__, __api__)                                                                        \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    uint32_t     id       = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", 0};                                                                      \
                                                                                                                     \
    LOG("Called %s", __FUNCTION__);                                                                                  \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {                                             \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    auto value = t->__api__();                                                                                       \
    return Py_BuildValue("i", (int) value);                                                                          \
  }

#define THING_BODY_GET_STRING(__func__, __api__)                                                                     \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    uint32_t     id       = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", 0};                                                                      \
                                                                                                                     \
    LOG("Called %s", __FUNCTION__);                                                                                  \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {                                             \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    auto value = t->__api__();                                                                                       \
    return Py_BuildValue("s", value.c_str());                                                                        \
  }

#define THING_BODY_SET_THING(__func__, __api__)                                                                      \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    uint32_t     id       = 0;                                                                                       \
    uint32_t     oid      = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", (char *) "oid", 0};                                                      \
                                                                                                                     \
    LOG("Called %s", __FUNCTION__);                                                                                  \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &oid)) {                                      \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! oid) {                                                                                                     \
      ERR("%s: No oid thing ID set", __FUNCTION__);                                                                  \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp o = game->thing_find(oid);                                                                                \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, oid);                                                         \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    t->__api__(o);                                                                                                   \
    Py_RETURN_TRUE;                                                                                                  \
  }

#define THING_BODY_GET_THING(__func__, __api__)                                                                      \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    uint32_t     id       = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", 0};                                                                      \
                                                                                                                     \
    LOG("Called %s", __FUNCTION__);                                                                                  \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {                                             \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return Py_BuildValue("I", 0);                                                                                  \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return Py_BuildValue("I", 0);                                                                                  \
    }                                                                                                                \
                                                                                                                     \
    ThingId found = t->__api__();                                                                                    \
    return Py_BuildValue("I", found.id);                                                                             \
  }

#define THING_BODY_GET_BOOL(__func__, __api__)                                                                       \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    uint32_t     id       = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", 0};                                                                      \
                                                                                                                     \
    LOG("Called %s", __FUNCTION__);                                                                                  \
    if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {                                             \
      ERR("%s: Failed parsing keywords", __FUNCTION__);                                                              \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
                                                                                                                     \
    if (t->__api__()) {                                                                                              \
      Py_RETURN_TRUE;                                                                                                \
    } else {                                                                                                         \
      Py_RETURN_FALSE;                                                                                               \
    }                                                                                                                \
  }

PyObject *thing_get_coords(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "id", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  Py_ssize_t size      = 2;
  auto       the_tuple = PyTuple_New(size);
  if (! the_tuple) {
    ERR("%s: Cannot create tuple for ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  auto err = PyTuple_SetItem(the_tuple, (Py_ssize_t) 0, PyLong_FromLong((long) t->curr_at.x));
  if (err < 0) {
    ERR("%s: Cannot create tuple (a) for ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  err = PyTuple_SetItem(the_tuple, (Py_ssize_t) 1, PyLong_FromLong((long) t->curr_at.y));
  if (err < 0) {
    ERR("%s: Cannot create tuple (a) for ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  return the_tuple;
}

PyObject *thing_hit(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     target_id = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &hitter_id, &target_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! hitter_id) {
    ERR("%s: No hitter thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp hitter = game->thing_find(hitter_id);
  if (! hitter) {
    ERR("%s: Cannot find hitter thing ID %u", __FUNCTION__, hitter_id);
    Py_RETURN_NONE;
  }

  if (! target_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp target = game->thing_find(target_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, target_id);
    Py_RETURN_NONE;
  }

  if (hitter->attack(target)) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

PyObject *thing_possible_to_attack(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     target_id = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &hitter_id, &target_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! hitter_id) {
    ERR("%s: No hitter thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp hitter = game->thing_find(hitter_id);
  if (! hitter) {
    ERR("%s: Cannot find hitter thing ID %u", __FUNCTION__, hitter_id);
    Py_RETURN_NONE;
  }

  if (! target_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp target = game->thing_find(target_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, target_id);
    Py_RETURN_NONE;
  }

  IF_DEBUG { hitter->log("Check if possible to attack target %s", target->to_string().c_str()); }

  if (hitter->possible_to_attack(target)) {
    IF_DEBUG { hitter->log("Check if possible to target %s; yes", target->to_string().c_str()); }
    Py_RETURN_TRUE;
  } else {
    IF_DEBUG { hitter->log("Check if possible to attack %s; no", target->to_string().c_str()); }
    Py_RETURN_FALSE;
  }
}

PyObject *thing_fire_at(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     owner_id  = 0;
  char        *item      = nullptr;
  uint32_t     target_id = 0;
  static char *kwlist[]  = {(char *) "owner", (char *) "item", (char *) "target", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &owner_id, &item, &target_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  if (! item) {
    ERR("%s: No item thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! target_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp target = game->thing_find(target_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, target_id);
    Py_RETURN_NONE;
  }

  IF_DEBUG { owner->log("Fire %s at %s", item, target->to_string().c_str()); }

  auto what      = std::string(item);
  auto fire_what = tp_find(what);
  if (fire_what->is_projectile()) {
    if (owner->projectile_fire_at(std::string(item), target)) {
      Py_RETURN_TRUE;
    } else {
      Py_RETURN_FALSE;
    }
  } else if (fire_what->is_laser()) {
    if (owner->laser_fire_at(std::string(item), target)) {
      Py_RETURN_TRUE;
    } else {
      Py_RETURN_FALSE;
    }
  } else {
    owner->err("Cannot fire %s at %s", item, target->to_string().c_str());
    Py_RETURN_FALSE;
  }
}

PyObject *thing_death_by(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     me_id     = 0;
  char        *reason    = nullptr;
  uint32_t     killer_id = 0;
  static char *kwlist[]  = {(char *) "me", (char *) "reason", (char *) "defeater", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &me_id, &reason, &killer_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! me_id) {
    ERR("%s: No me thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    Py_RETURN_NONE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! killer_id) {
    ERR("%s: No defeater thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp defeater = game->thing_find(killer_id);
  if (! defeater) {
    ERR("%s: Cannot find defeater thing ID %u", __FUNCTION__, killer_id);
    Py_RETURN_NONE;
  }

  IF_DEBUG { me->log("Killed by %s, reason %s", defeater->to_string().c_str(), reason); }
  me->dead(defeater, "%s", reason);

  Py_RETURN_NONE;
}

PyObject *thing_dead(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     me_id    = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "me", (char *) "reason", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &me_id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! me_id) {
    ERR("%s: No me thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    Py_RETURN_NONE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  IF_DEBUG { me->log("Perma killed: reason %s", reason); }
  me->dead("%s", reason);
  me->is_resurrection_blocked = true;
  Py_RETURN_NONE;
}

PyObject *thing_perma_death(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     me_id    = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "me", (char *) "reason", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &me_id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! me_id) {
    ERR("%s: No me thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    Py_RETURN_NONE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  IF_DEBUG { me->log("Killed: reason %s", reason); }
  me->dead("%s", reason);
  Py_RETURN_NONE;
}

PyObject *thing_resurrect(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     me_id    = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "me", (char *) "reason", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &me_id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! me_id) {
    ERR("%s: No me thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    Py_RETURN_NONE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  IF_DEBUG { me->log("Resurrected: reason %s", reason); }
  me->resurrect_forced();
  Py_RETURN_NONE;
}

PyObject *thing_carry(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     me_id    = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "me", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &me_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! me_id) {
    ERR("%s: No me thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    Py_RETURN_NONE;
  }

  if (! what) {
    me->err("Could not carry nameless object");
    Py_RETURN_NONE;
  }

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    me->err("Could not find to carry %s", what);
    Py_RETURN_NONE;
  }

  auto item = me->level->thing_new(tp, me->curr_at);
  if (! item) {
    me->err("Could not create to carry %s", what);
    Py_RETURN_NONE;
  }

  if (! me->carry(item)) {
    me->err("Could not carry %s", what);
    Py_RETURN_NONE;
  }

  return Py_BuildValue("I", item->id);
}

PyObject *thing_polymorph(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     me_id    = 0;
  char        *into     = nullptr;
  static char *kwlist[] = {(char *) "me", (char *) "into", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &me_id, &into)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! me_id) {
    ERR("%s: No me thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    Py_RETURN_NONE;
  }

  auto tp = tp_find(into);
  if (unlikely(! tp)) {
    ERR("%s: No polymorph into %s found", __FUNCTION__, into);
    Py_RETURN_NONE;
  }

  me->polymorph(tp);
  Py_RETURN_NONE;
}

PyObject *thing_set_mob_spawner(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     me_id    = 0;
  uint32_t     owner_id = 0;
  static char *kwlist[] = {(char *) "me", (char *) "owner", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &me_id, &owner_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! me_id) {
    ERR("%s: No me thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  me->set_mob_spawner(owner);
  Py_RETURN_NONE;
}

PyObject *thing_set_leader(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     me_id    = 0;
  uint32_t     owner_id = 0;
  static char *kwlist[] = {(char *) "me", (char *) "owner", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &me_id, &owner_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! me_id) {
    ERR("%s: No me thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp me = game->thing_find(me_id);
  if (! me) {
    ERR("%s: Cannot find me thing ID %u", __FUNCTION__, me_id);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  me->set_leader(owner);
  Py_RETURN_NONE;
}

PyObject *thing_buff_add(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  if (! what) {
    ERR("%s: No buff name set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    ERR("%s: No buff tp called %s found", __FUNCTION__, what);
    Py_RETURN_NONE;
  }

  owner->buff_add(tp);
  Py_RETURN_NONE;
}

PyObject *thing_debuff_add(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  if (! what) {
    ERR("%s: No debuff name set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    ERR("%s: No debuff tp called %s found", __FUNCTION__, what);
    Py_RETURN_NONE;
  }

  owner->debuff_add(tp);
  Py_RETURN_NONE;
}

PyObject *thing_buff_remove(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  if (! what) {
    ERR("%s: No buff name set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    ERR("%s: No buff tp called %s found", __FUNCTION__, what);
    Py_RETURN_NONE;
  }

  owner->buff_remove(tp);
  Py_RETURN_NONE;
}

PyObject *thing_debuff_remove(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  if (! what) {
    ERR("%s: No debuff name set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    ERR("%s: No debuff tp called %s found", __FUNCTION__, what);
    Py_RETURN_NONE;
  }

  owner->debuff_remove(tp);
  Py_RETURN_NONE;
}

PyObject *thing_msg(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     owner_id = 0;
  char        *msg      = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "msg", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &msg)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  if (! msg) {
    ERR("%s: No msg thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  //
  // If not reachable, suppress the msg
  //
  if (owner->get_distance_to_player() < DMAP_IS_PASSABLE) {
    if (owner->is_monst()) {
      TOPCON("%s says '%s'", owner->text_The().c_str(), msg);
    } else {
      TOPCON("%s", msg);
    }
    owner->msg(msg);
  }

  Py_RETURN_NONE;
}

PyObject *thing_sound_play_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char    *name     = 0;
  uint32_t owner_id = 0;

  static char *kwlist[] = {(char *) "owner", (char *) "name", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &name)) {
    ERR("thing_sound_play: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  if (! name) {
    ERR("thing_sound_play: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("thing_sound_play(name=%s)", name);

  std::string alias = name;
  if (! owner->thing_sound_play(alias)) {
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}

PyObject *thing_sound_play_channel_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t owner_id = 0;
  char    *name     = 0;
  int      channel  = 0;

  static char *kwlist[] = {(char *) "owner", (char *) "channel", (char *) "name", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Iis", kwlist, &owner_id, &channel, &name)) {
    ERR("thing_sound_play_channel: Bad arguments");
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  if (! name) {
    ERR("thing_sound_play: Missing name attr");
    Py_RETURN_FALSE;
  }
  if (! name) {
    ERR("thing_sound_play_channel: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("sound_play_channel(channel=%d, name=%s)", channel, name);

  std::string alias = name;
  if (! owner->thing_sound_play_channel(channel, alias)) {
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}

THING_BODY_GET_BOOL(level_is_able_to_fire_at, is_able_to_fire_at)
THING_BODY_GET_BOOL(level_is_attackable_by_monst, is_attackable_by_monst)
THING_BODY_GET_BOOL(level_is_attackable_by_player, is_attackable_by_player)
THING_BODY_GET_BOOL(thing_aggression_level_pct, aggression_level_pct)
THING_BODY_GET_BOOL(thing_ai_detect_secret_doors, ai_detect_secret_doors)
THING_BODY_GET_BOOL(thing_ai_resent_count, ai_resent_count)
THING_BODY_GET_BOOL(thing_ai_wanderer, ai_wanderer)
THING_BODY_GET_BOOL(thing_attack_blood, attack_blood)
THING_BODY_GET_BOOL(thing_attack_engulf_chance_d1000, attack_engulf_chance_d1000)
THING_BODY_GET_BOOL(thing_attack_undead, attack_undead)
THING_BODY_GET_BOOL(thing_collateral_damage_pct, collateral_damage_pct)
THING_BODY_GET_BOOL(thing_damage_acid_chance_d1000, damage_acid_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_crush_chance_d1000, damage_crush_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_digest_chance_d1000, damage_digest_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_energy_chance_d1000, damage_energy_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_fire_chance_d1000, damage_fire_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_future1_chance_d1000, damage_future1_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_future2_chance_d1000, damage_future2_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_future3_chance_d1000, damage_future3_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_future4_chance_d1000, damage_future4_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_lightning_chance_d1000, damage_lightning_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_necrosis_chance_d1000, damage_necrosis_chance_d1000)
THING_BODY_GET_BOOL(thing_damage_poison_chance_d1000, damage_poison_chance_d1000)
THING_BODY_GET_BOOL(thing_distance_jump, distance_jump)
THING_BODY_GET_BOOL(thing_distance_leader_max, distance_leader_max)
THING_BODY_GET_BOOL(thing_distance_recruitment_max, distance_recruitment_max)
THING_BODY_GET_BOOL(thing_enchant_level, enchant_level)
THING_BODY_GET_BOOL(thing_enchant_max, enchant_max)
THING_BODY_GET_BOOL(thing_environ_avoids_acid, environ_avoids_acid)
THING_BODY_GET_BOOL(thing_environ_avoids_fire, environ_avoids_fire)
THING_BODY_GET_BOOL(thing_environ_avoids_necrosis, environ_avoids_necrosis)
THING_BODY_GET_BOOL(thing_environ_avoids_poison, environ_avoids_poison)
THING_BODY_GET_BOOL(thing_environ_avoids_water, environ_avoids_water)
THING_BODY_GET_BOOL(thing_environ_prefers_acid, environ_prefers_acid)
THING_BODY_GET_BOOL(thing_environ_prefers_fire, environ_prefers_fire)
THING_BODY_GET_BOOL(thing_environ_prefers_necrosis, environ_prefers_necrosis)
THING_BODY_GET_BOOL(thing_environ_prefers_poison, environ_prefers_poison)
THING_BODY_GET_BOOL(thing_environ_prefers_spiderwebs, environ_prefers_spiderwebs)
THING_BODY_GET_BOOL(thing_environ_prefers_water, environ_prefers_water)
THING_BODY_GET_BOOL(thing_get_distance_minion_vision_shared, distance_minion_vision_shared)
THING_BODY_GET_BOOL(thing_get_distance_vision, get_distance_vision)
THING_BODY_GET_BOOL(thing_gfx_flickers, gfx_flickers)
THING_BODY_GET_BOOL(thing_gfx_long_shadow_caster, gfx_long_shadow_caster)
THING_BODY_GET_BOOL(thing_gfx_solid_shadow, gfx_solid_shadow)
THING_BODY_GET_BOOL(thing_gfx_very_short_shadow_caster, gfx_very_short_shadow_caster)
THING_BODY_GET_BOOL(thing_gfx_water, gfx_water)
THING_BODY_GET_BOOL(thing_hunger_clock_tick_frequency, get_hunger_clock_tick_frequency)
THING_BODY_GET_BOOL(thing_hunger_is_insatiable, hunger_is_insatiable)
THING_BODY_GET_BOOL(thing_is_able_to_attack_mobs, is_able_to_attack_mobs)
THING_BODY_GET_BOOL(thing_is_able_to_break_down_doors, is_able_to_break_down_doors)
THING_BODY_GET_BOOL(thing_is_able_to_break_out_of_webs, is_able_to_break_out_of_webs)
THING_BODY_GET_BOOL(thing_is_able_to_change_levels, is_able_to_change_levels)
THING_BODY_GET_BOOL(thing_is_able_to_collect_keys, is_able_to_collect_keys)
THING_BODY_GET_BOOL(thing_is_able_to_enchant_items, is_able_to_enchant_items)
THING_BODY_GET_BOOL(thing_is_able_to_fall, is_able_to_fall)
THING_BODY_GET_BOOL(thing_is_able_to_follow, is_able_to_follow)
THING_BODY_GET_BOOL(thing_is_able_to_jump_attack_chance_d1000, is_able_to_jump_attack_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_jump_attack, is_able_to_jump_attack)
THING_BODY_GET_BOOL(thing_is_able_to_jump_escape, is_able_to_jump_escape)
THING_BODY_GET_BOOL(thing_is_able_to_jump, is_able_to_jump)
THING_BODY_GET_BOOL(thing_is_able_to_jump_on_low_hp_chance_d1000, is_able_to_jump_on_low_hp_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_jump_onto_chance_d1000, is_able_to_jump_onto_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_jump_onto, is_able_to_jump_onto)
THING_BODY_GET_BOOL(thing_is_able_to_jump_randomly_chance_d1000, is_able_to_jump_randomly_chance_d1000)
THING_BODY_GET_BOOL(thing_is_able_to_jump_without_tiring, is_able_to_jump_without_tiring)
THING_BODY_GET_BOOL(thing_is_able_to_learn_skills, is_able_to_learn_skills)
THING_BODY_GET_BOOL(thing_is_able_to_open_doors, is_able_to_open_doors)
THING_BODY_GET_BOOL(thing_is_able_to_see_in_the_dark, is_able_to_see_in_the_dark)
THING_BODY_GET_BOOL(thing_is_able_to_see_through_doors, is_able_to_see_through_doors)
THING_BODY_GET_BOOL(thing_is_able_to_tire, is_able_to_tire)
THING_BODY_GET_BOOL(thing_is_able_to_use_armor, is_able_to_use_armor)
THING_BODY_GET_BOOL(thing_is_able_to_use_boots, is_able_to_use_boots)
THING_BODY_GET_BOOL(thing_is_able_to_use_cloak, is_able_to_use_cloak)
THING_BODY_GET_BOOL(thing_is_able_to_use_gauntlet, is_able_to_use_gauntlet)
THING_BODY_GET_BOOL(thing_is_able_to_use_helmet, is_able_to_use_helmet)
THING_BODY_GET_BOOL(thing_is_able_to_use_rings, is_able_to_use_rings)
THING_BODY_GET_BOOL(thing_is_able_to_use_shield, is_able_to_use_shield)
THING_BODY_GET_BOOL(thing_is_able_to_use_wands, is_able_to_use_wands)
THING_BODY_GET_BOOL(thing_is_able_to_use_weapons, is_able_to_use_weapons)
THING_BODY_GET_BOOL(thing_is_able_to_walk_through_walls, is_able_to_walk_through_walls)
THING_BODY_GET_BOOL(thing_is_acid, is_acid)
THING_BODY_GET_BOOL(thing_is_alive_monst, is_alive_monst)
THING_BODY_GET_BOOL(thing_is_alive_on_end_of_anim, is_alive_on_end_of_anim)
THING_BODY_GET_BOOL(thing_is_always_hit, is_always_hit)
THING_BODY_GET_BOOL(thing_is_aquatic, is_aquatic)
THING_BODY_GET_BOOL(thing_is_armor, is_armor)
THING_BODY_GET_BOOL(thing_is_ascend_dungeon, is_ascend_dungeon)
THING_BODY_GET_BOOL(thing_is_ascend_sewer, is_ascend_sewer)
THING_BODY_GET_BOOL(thing_is_auto_collect_item, is_auto_collect_item)
THING_BODY_GET_BOOL(thing_is_auto_equipped, is_auto_equipped)
THING_BODY_GET_BOOL(thing_is_auto_throw, is_auto_throw)
THING_BODY_GET_BOOL(thing_is_auto_use, is_auto_use)
THING_BODY_GET_BOOL(thing_is_bag, is_bag)
THING_BODY_GET_BOOL(thing_is_bag_item_container, is_bag_item_container)
THING_BODY_GET_BOOL(thing_is_bag_item, is_bag_item)
THING_BODY_GET_BOOL(thing_is_bag_item_not_stackable, is_bag_item_not_stackable)
THING_BODY_GET_BOOL(thing_is_barrel, is_barrel)
THING_BODY_GET_BOOL(thing_is_bleeder, is_bleeder)
THING_BODY_GET_BOOL(thing_is_blood_eater, is_blood_eater)
THING_BODY_GET_BOOL(thing_is_bloodied, is_bloodied)
THING_BODY_GET_BOOL(thing_is_blood, is_blood)
THING_BODY_GET_BOOL(thing_is_blood_splatter, is_blood_splatter)
THING_BODY_GET_BOOL(thing_is_bones, is_bones)
THING_BODY_GET_BOOL(thing_is_bony, is_bony)
THING_BODY_GET_BOOL(thing_is_boots, is_boots)
THING_BODY_GET_BOOL(thing_is_brazier, is_brazier)
THING_BODY_GET_BOOL(thing_is_bridge, is_bridge)
THING_BODY_GET_BOOL(thing_is_buff, is_buff)
THING_BODY_GET_BOOL(thing_is_burnable, is_burnable)
THING_BODY_GET_BOOL(thing_is_carrying_item, is_carrying_item)
THING_BODY_GET_BOOL(thing_is_carrying_treasure, is_carrying_treasure)
THING_BODY_GET_BOOL(thing_is_chasm, is_chasm)
THING_BODY_GET_BOOL(thing_is_cloak, is_cloak)
THING_BODY_GET_BOOL(thing_is_collectable, is_collectable)
THING_BODY_GET_BOOL(thing_is_collect_as_keys, is_collect_as_keys)
THING_BODY_GET_BOOL(thing_is_collected_as_gold, is_collected_as_gold)
THING_BODY_GET_BOOL(thing_is_combustible, is_combustible)
THING_BODY_GET_BOOL(thing_is_corpse, is_corpse)
THING_BODY_GET_BOOL(thing_is_corpse_on_death, is_corpse_on_death)
THING_BODY_GET_BOOL(thing_is_corridor, is_corridor)
THING_BODY_GET_BOOL(thing_is_critical_to_level, is_critical_to_level)
THING_BODY_GET_BOOL(thing_is_crushable, is_crushable)
THING_BODY_GET_BOOL(thing_is_cursor_can_hover_over, is_cursor_can_hover_over)
THING_BODY_GET_BOOL(thing_is_cursor_can_hover_over_x2_click, is_cursor_can_hover_over_x2_click)
THING_BODY_GET_BOOL(thing_is_cursor, is_cursor)
THING_BODY_GET_BOOL(thing_is_cursor_path_hazard_for_player, is_cursor_path_hazard_for_player)
THING_BODY_GET_BOOL(thing_is_cursor_path, is_cursor_path)
THING_BODY_GET_BOOL(thing_is_dead_on_end_of_anim, is_dead_on_end_of_anim)
THING_BODY_GET_BOOL(thing_is_dead_or_dying, is_dead_or_dying)
THING_BODY_GET_BOOL(thing_is_dead_or_dying_on_shove, is_dead_on_shove)
THING_BODY_GET_BOOL(thing_is_debuff, is_debuff)
THING_BODY_GET_BOOL(thing_is_debug_path, is_debug_path)
THING_BODY_GET_BOOL(thing_is_debug_type, is_debug_type)
THING_BODY_GET_BOOL(thing_is_deep_water, is_deep_water)
THING_BODY_GET_BOOL(thing_is_descend_dungeon, is_descend_dungeon)
THING_BODY_GET_BOOL(thing_is_descend_sewer, is_descend_sewer)
THING_BODY_GET_BOOL(thing_is_described_when_hovering_over, is_described_when_hovering_over)
THING_BODY_GET_BOOL(thing_is_destroyed_on_hit_or_miss, is_destroyed_on_hit_or_miss)
THING_BODY_GET_BOOL(thing_is_destroyed_on_hitting, is_destroyed_on_hitting)
THING_BODY_GET_BOOL(thing_is_dir_bl, is_dir_bl)
THING_BODY_GET_BOOL(thing_is_dir_br, is_dir_br)
THING_BODY_GET_BOOL(thing_is_dir_down, is_dir_down)
THING_BODY_GET_BOOL(thing_is_dir_left, is_dir_left)
THING_BODY_GET_BOOL(thing_is_dir_none, is_dir_none)
THING_BODY_GET_BOOL(thing_is_dir_right, is_dir_right)
THING_BODY_GET_BOOL(thing_is_dirt, is_dirt)
THING_BODY_GET_BOOL(thing_is_dir_tl, is_dir_tl)
THING_BODY_GET_BOOL(thing_is_dir_tr, is_dir_tr)
THING_BODY_GET_BOOL(thing_is_dir_up, is_dir_up)
THING_BODY_GET_BOOL(thing_is_door, is_door)
THING_BODY_GET_BOOL(thing_is_droppable, is_droppable)
THING_BODY_GET_BOOL(thing_is_dry_grass, is_dry_grass)
THING_BODY_GET_BOOL(thing_is_enchantable, is_enchantable)
THING_BODY_GET_BOOL(thing_is_enchantstone, is_enchantstone)
THING_BODY_GET_BOOL(thing_is_engulfer, is_engulfer)
THING_BODY_GET_BOOL(thing_is_ethereal, is_ethereal)
THING_BODY_GET_BOOL(thing_is_ethereal_mob, is_ethereal_mob)
THING_BODY_GET_BOOL(thing_is_exit_finder, is_exit_finder)
THING_BODY_GET_BOOL(thing_is_explorer, is_explorer)
THING_BODY_GET_BOOL(thing_is_explosion, is_explosion)
THING_BODY_GET_BOOL(thing_is_fearless, is_fearless)
THING_BODY_GET_BOOL(thing_is_fire, is_fire)
THING_BODY_GET_BOOL(thing_is_floating, is_floating)
THING_BODY_GET_BOOL(thing_is_floor_deco, is_floor_deco)
THING_BODY_GET_BOOL(thing_is_floor, is_floor)
THING_BODY_GET_BOOL(thing_is_flying, is_flying)
THING_BODY_GET_BOOL(thing_is_foilage, is_foilage)
THING_BODY_GET_BOOL(thing_is_food_eater, is_food_eater)
THING_BODY_GET_BOOL(thing_is_food, is_food)
THING_BODY_GET_BOOL(thing_is_gauntlet, is_gauntlet)
THING_BODY_GET_BOOL(thing_is_gfx_anim_synced_with_owner, is_gfx_anim_synced_with_owner)
THING_BODY_GET_BOOL(thing_is_glass, is_glass)
THING_BODY_GET_BOOL(thing_is_gold, is_gold)
THING_BODY_GET_BOOL(thing_is_green_blooded, is_green_blooded)
THING_BODY_GET_BOOL(thing_is_green_splatter, is_green_splatter)
THING_BODY_GET_BOOL(thing_is_hazard, is_hazard)
THING_BODY_GET_BOOL(thing_is_health_booster, is_health_booster)
THING_BODY_GET_BOOL(thing_is_heavy, is_heavy)
THING_BODY_GET_BOOL(thing_is_helmet, is_helmet)
THING_BODY_GET_BOOL(thing_is_hittable, is_hittable)
THING_BODY_GET_BOOL(thing_is_humanoid, is_humanoid)
THING_BODY_GET_BOOL(thing_is_intelligent, is_intelligent)
THING_BODY_GET_BOOL(thing_is_interesting, is_interesting)
THING_BODY_GET_BOOL(thing_is_item_carrier, is_item_carrier)
THING_BODY_GET_BOOL(thing_is_item_collector, is_item_collector)
THING_BODY_GET_BOOL(thing_is_item_eater, is_item_eater)
THING_BODY_GET_BOOL(thing_is_item, is_item)
THING_BODY_GET_BOOL(thing_is_item_magical_eater, is_item_magical_eater)
THING_BODY_GET_BOOL(thing_is_item_magical, is_item_magical)
THING_BODY_GET_BOOL(thing_is_item_organic, is_item_organic)
THING_BODY_GET_BOOL(thing_is_jelly_baby_eater, is_jelly_baby_eater)
THING_BODY_GET_BOOL(thing_is_jelly_baby, is_jelly_baby)
THING_BODY_GET_BOOL(thing_is_jelly_eater, is_jelly_eater)
THING_BODY_GET_BOOL(thing_is_jelly, is_jelly)
THING_BODY_GET_BOOL(thing_is_jelly_parent, is_jelly_parent)
THING_BODY_GET_BOOL(thing_is_key, is_key)
THING_BODY_GET_BOOL(thing_is_laser, is_laser)
THING_BODY_GET_BOOL(thing_is_lava, is_lava)
THING_BODY_GET_BOOL(thing_is_light_blocker, is_light_blocker)
THING_BODY_GET_BOOL(thing_is_living, is_living)
THING_BODY_GET_BOOL(thing_is_loggable, is_loggable)
THING_BODY_GET_BOOL(thing_is_meat_eater, is_meat_eater)
THING_BODY_GET_BOOL(thing_is_meat, is_meat)
THING_BODY_GET_BOOL(thing_is_metal, is_metal)
THING_BODY_GET_BOOL(thing_is_minion, is_minion)
THING_BODY_GET_BOOL(thing_is_mob, is_mob)
THING_BODY_GET_BOOL(thing_is_monst, is_monst)
THING_BODY_GET_BOOL(thing_is_moveable, is_moveable)
THING_BODY_GET_BOOL(thing_is_msg, is_msg)
THING_BODY_GET_BOOL(thing_is_necrotic_danger_level, is_necrotic_danger_level)
THING_BODY_GET_BOOL(thing_is_no_tile, is_no_tile)
THING_BODY_GET_BOOL(thing_is_obs_destructable, is_obs_destructable)
THING_BODY_GET_BOOL(thing_is_obs_wall_or_door, is_obs_wall_or_door)
THING_BODY_GET_BOOL(thing_is_on_fire, is_on_fire)
THING_BODY_GET_BOOL(thing_is_openable, is_openable)
THING_BODY_GET_BOOL(thing_is_organic, is_organic)
THING_BODY_GET_BOOL(thing_is_pink_blooded, is_pink_blooded)
THING_BODY_GET_BOOL(thing_is_pink_splatter, is_pink_splatter)
THING_BODY_GET_BOOL(thing_is_player, is_player)
THING_BODY_GET_BOOL(thing_is_poisonous_danger_level, is_poisonous_danger_level)
THING_BODY_GET_BOOL(thing_is_potion_eater, is_potion_eater)
THING_BODY_GET_BOOL(thing_is_potion, is_potion)
THING_BODY_GET_BOOL(thing_is_projectile, is_projectile)
THING_BODY_GET_BOOL(thing_is_red_blooded, is_red_blooded)
THING_BODY_GET_BOOL(thing_is_removeable_if_out_of_slots, is_removeable_if_out_of_slots)
THING_BODY_GET_BOOL(thing_is_resurrectable, is_resurrectable)
THING_BODY_GET_BOOL(thing_is_resurrected_or_resurrecting, is_resurrected_or_resurrecting)
THING_BODY_GET_BOOL(thing_is_ring, is_ring)
THING_BODY_GET_BOOL(thing_is_ripple, is_ripple)
THING_BODY_GET_BOOL(thing_is_rock, is_rock)
THING_BODY_GET_BOOL(thing_is_rusty, is_rusty)
THING_BODY_GET_BOOL(thing_is_secret_door, is_secret_door)
THING_BODY_GET_BOOL(thing_is_sewer_wall, is_sewer_wall)
THING_BODY_GET_BOOL(thing_is_shallow_water, is_shallow_water)
THING_BODY_GET_BOOL(thing_is_shield, is_shield)
THING_BODY_GET_BOOL(thing_is_shovable, is_shovable)
THING_BODY_GET_BOOL(thing_is_skill, is_skill)
THING_BODY_GET_BOOL(thing_is_skillstone, is_skillstone)
THING_BODY_GET_BOOL(thing_is_slippery, is_slippery)
THING_BODY_GET_BOOL(thing_is_smoke, is_smoke)
THING_BODY_GET_BOOL(thing_is_spawner, is_spawner)
THING_BODY_GET_BOOL(thing_is_spider, is_spider)
THING_BODY_GET_BOOL(thing_is_spiderweb, is_spiderweb)
THING_BODY_GET_BOOL(thing_is_steal_item_chance_d1000, is_steal_item_chance_d1000)
THING_BODY_GET_BOOL(thing_is_sticky, is_sticky)
THING_BODY_GET_BOOL(thing_is_stone, is_stone)
THING_BODY_GET_BOOL(thing_is_sword, is_sword)
THING_BODY_GET_BOOL(thing_is_target_auto_select, is_target_auto_select)
THING_BODY_GET_BOOL(thing_is_throwable, is_throwable)
THING_BODY_GET_BOOL(thing_is_tickable, is_tickable)
THING_BODY_GET_BOOL(thing_is_tmp_thing, is_tmp_thing)
THING_BODY_GET_BOOL(thing_is_torch, is_torch)
THING_BODY_GET_BOOL(thing_is_toughness_hard, is_toughness_hard)
THING_BODY_GET_BOOL(thing_is_toughness_soft, is_toughness_soft)
THING_BODY_GET_BOOL(thing_is_toughness_very_tough, is_toughness_very_tough)
THING_BODY_GET_BOOL(thing_is_treasure_chest, is_treasure_chest)
THING_BODY_GET_BOOL(thing_is_treasure_eater, is_treasure_eater)
THING_BODY_GET_BOOL(thing_is_treasure_type, is_treasure_type)
THING_BODY_GET_BOOL(thing_is_undead, is_undead)
THING_BODY_GET_BOOL(thing_is_usable, is_usable)
THING_BODY_GET_BOOL(thing_is_used_when_thrown, is_used_when_thrown)
THING_BODY_GET_BOOL(thing_is_very_combustible, is_very_combustible)
THING_BODY_GET_BOOL(thing_is_visible, is_visible)
THING_BODY_GET_BOOL(thing_is_wall_dungeon, is_wall_dungeon)
THING_BODY_GET_BOOL(thing_is_wall, is_wall)
THING_BODY_GET_BOOL(thing_is_wand, is_wand)
THING_BODY_GET_BOOL(thing_is_water, is_water)
THING_BODY_GET_BOOL(thing_is_weapon, is_weapon)
THING_BODY_GET_BOOL(thing_is_wet_grass, is_wet_grass)
THING_BODY_GET_BOOL(thing_is_wooden, is_wooden)
THING_BODY_GET_BOOL(thing_spawn_group_radius, get_spawn_group_radius)
THING_BODY_GET_BOOL(thing_unused_flag100, unused_flag100)
THING_BODY_GET_BOOL(thing_unused_flag101, unused_flag101)
THING_BODY_GET_BOOL(thing_unused_flag102, unused_flag102)
THING_BODY_GET_BOOL(thing_unused_flag103, unused_flag103)
THING_BODY_GET_BOOL(thing_unused_flag104, unused_flag104)
THING_BODY_GET_BOOL(thing_unused_flag105, unused_flag105)
THING_BODY_GET_BOOL(thing_unused_flag106, unused_flag106)
THING_BODY_GET_BOOL(thing_unused_flag107, unused_flag107)
THING_BODY_GET_BOOL(thing_unused_flag108, unused_flag108)
THING_BODY_GET_BOOL(thing_unused_flag109, unused_flag109)
THING_BODY_GET_BOOL(thing_unused_flag10, unused_flag10)
THING_BODY_GET_BOOL(thing_unused_flag110, unused_flag110)
THING_BODY_GET_BOOL(thing_unused_flag111, unused_flag111)
THING_BODY_GET_BOOL(thing_unused_flag112, unused_flag112)
THING_BODY_GET_BOOL(thing_unused_flag113, unused_flag113)
THING_BODY_GET_BOOL(thing_unused_flag114, unused_flag114)
THING_BODY_GET_BOOL(thing_unused_flag115, unused_flag115)
THING_BODY_GET_BOOL(thing_unused_flag116, unused_flag116)
THING_BODY_GET_BOOL(thing_unused_flag117, unused_flag117)
THING_BODY_GET_BOOL(thing_unused_flag118, unused_flag118)
THING_BODY_GET_BOOL(thing_unused_flag119, unused_flag119)
THING_BODY_GET_BOOL(thing_unused_flag11, unused_flag11)
THING_BODY_GET_BOOL(thing_unused_flag120, unused_flag120)
THING_BODY_GET_BOOL(thing_unused_flag121, unused_flag121)
THING_BODY_GET_BOOL(thing_unused_flag122, unused_flag122)
THING_BODY_GET_BOOL(thing_unused_flag123, unused_flag123)
THING_BODY_GET_BOOL(thing_unused_flag124, unused_flag124)
THING_BODY_GET_BOOL(thing_unused_flag125, unused_flag125)
THING_BODY_GET_BOOL(thing_unused_flag126, unused_flag126)
THING_BODY_GET_BOOL(thing_unused_flag127, unused_flag127)
THING_BODY_GET_BOOL(thing_unused_flag128, unused_flag128)
THING_BODY_GET_BOOL(thing_unused_flag129, unused_flag129)
THING_BODY_GET_BOOL(thing_unused_flag12, unused_flag12)
THING_BODY_GET_BOOL(thing_unused_flag130, unused_flag130)
THING_BODY_GET_BOOL(thing_unused_flag131, unused_flag131)
THING_BODY_GET_BOOL(thing_unused_flag132, unused_flag132)
THING_BODY_GET_BOOL(thing_unused_flag133, unused_flag133)
THING_BODY_GET_BOOL(thing_unused_flag134, unused_flag134)
THING_BODY_GET_BOOL(thing_unused_flag135, unused_flag135)
THING_BODY_GET_BOOL(thing_unused_flag136, unused_flag136)
THING_BODY_GET_BOOL(thing_unused_flag137, unused_flag137)
THING_BODY_GET_BOOL(thing_unused_flag138, unused_flag138)
THING_BODY_GET_BOOL(thing_unused_flag139, unused_flag139)
THING_BODY_GET_BOOL(thing_unused_flag13, unused_flag13)
THING_BODY_GET_BOOL(thing_unused_flag140, unused_flag140)
THING_BODY_GET_BOOL(thing_unused_flag141, unused_flag141)
THING_BODY_GET_BOOL(thing_unused_flag142, unused_flag142)
THING_BODY_GET_BOOL(thing_unused_flag143, unused_flag143)
THING_BODY_GET_BOOL(thing_unused_flag144, unused_flag144)
THING_BODY_GET_BOOL(thing_unused_flag145, unused_flag145)
THING_BODY_GET_BOOL(thing_unused_flag146, unused_flag146)
THING_BODY_GET_BOOL(thing_unused_flag147, unused_flag147)
THING_BODY_GET_BOOL(thing_unused_flag148, unused_flag148)
THING_BODY_GET_BOOL(thing_unused_flag149, unused_flag149)
THING_BODY_GET_BOOL(thing_unused_flag14, unused_flag14)
THING_BODY_GET_BOOL(thing_unused_flag150, unused_flag150)
THING_BODY_GET_BOOL(thing_unused_flag151, unused_flag151)
THING_BODY_GET_BOOL(thing_unused_flag152, unused_flag152)
THING_BODY_GET_BOOL(thing_unused_flag153, unused_flag153)
THING_BODY_GET_BOOL(thing_unused_flag154, unused_flag154)
THING_BODY_GET_BOOL(thing_unused_flag155, unused_flag155)
THING_BODY_GET_BOOL(thing_unused_flag156, unused_flag156)
THING_BODY_GET_BOOL(thing_unused_flag157, unused_flag157)
THING_BODY_GET_BOOL(thing_unused_flag158, unused_flag158)
THING_BODY_GET_BOOL(thing_unused_flag159, unused_flag159)
THING_BODY_GET_BOOL(thing_unused_flag15, unused_flag15)
THING_BODY_GET_BOOL(thing_unused_flag160, unused_flag160)
THING_BODY_GET_BOOL(thing_unused_flag161, unused_flag161)
THING_BODY_GET_BOOL(thing_unused_flag162, unused_flag162)
THING_BODY_GET_BOOL(thing_unused_flag163, unused_flag163)
THING_BODY_GET_BOOL(thing_unused_flag164, unused_flag164)
THING_BODY_GET_BOOL(thing_unused_flag165, unused_flag165)
THING_BODY_GET_BOOL(thing_unused_flag166, unused_flag166)
THING_BODY_GET_BOOL(thing_unused_flag167, unused_flag167)
THING_BODY_GET_BOOL(thing_unused_flag168, unused_flag168)
THING_BODY_GET_BOOL(thing_unused_flag169, unused_flag169)
THING_BODY_GET_BOOL(thing_unused_flag16, unused_flag16)
THING_BODY_GET_BOOL(thing_unused_flag170, unused_flag170)
THING_BODY_GET_BOOL(thing_unused_flag171, unused_flag171)
THING_BODY_GET_BOOL(thing_unused_flag172, unused_flag172)
THING_BODY_GET_BOOL(thing_unused_flag173, unused_flag173)
THING_BODY_GET_BOOL(thing_unused_flag174, unused_flag174)
THING_BODY_GET_BOOL(thing_unused_flag175, unused_flag175)
THING_BODY_GET_BOOL(thing_unused_flag176, unused_flag176)
THING_BODY_GET_BOOL(thing_unused_flag177, unused_flag177)
THING_BODY_GET_BOOL(thing_unused_flag178, unused_flag178)
THING_BODY_GET_BOOL(thing_unused_flag179, unused_flag179)
THING_BODY_GET_BOOL(thing_unused_flag17, unused_flag17)
THING_BODY_GET_BOOL(thing_unused_flag180, unused_flag180)
THING_BODY_GET_BOOL(thing_unused_flag181, unused_flag181)
THING_BODY_GET_BOOL(thing_unused_flag182, unused_flag182)
THING_BODY_GET_BOOL(thing_unused_flag183, unused_flag183)
THING_BODY_GET_BOOL(thing_unused_flag184, unused_flag184)
THING_BODY_GET_BOOL(thing_unused_flag185, unused_flag185)
THING_BODY_GET_BOOL(thing_is_meltable, is_meltable)
THING_BODY_GET_BOOL(thing_is_amulet, is_amulet)
THING_BODY_GET_BOOL(thing_is_able_to_use_amulet, is_able_to_use_amulet)
THING_BODY_GET_BOOL(thing_unused_flag18, unused_flag18)
THING_BODY_GET_BOOL(thing_unused_flag19, unused_flag19)
THING_BODY_GET_BOOL(thing_unused_flag1, unused_flag1)
THING_BODY_GET_BOOL(thing_unused_flag20, unused_flag20)
THING_BODY_GET_BOOL(thing_unused_flag21, unused_flag21)
THING_BODY_GET_BOOL(thing_unused_flag22, unused_flag22)
THING_BODY_GET_BOOL(thing_unused_flag23, unused_flag23)
THING_BODY_GET_BOOL(thing_unused_flag24, unused_flag24)
THING_BODY_GET_BOOL(thing_unused_flag25, unused_flag25)
THING_BODY_GET_BOOL(thing_unused_flag26, unused_flag26)
THING_BODY_GET_BOOL(thing_unused_flag27, unused_flag27)
THING_BODY_GET_BOOL(thing_unused_flag28, unused_flag28)
THING_BODY_GET_BOOL(thing_unused_flag29, unused_flag29)
THING_BODY_GET_BOOL(thing_unused_flag2, unused_flag2)
THING_BODY_GET_BOOL(thing_unused_flag30, unused_flag30)
THING_BODY_GET_BOOL(thing_unused_flag31, unused_flag31)
THING_BODY_GET_BOOL(thing_unused_flag32, unused_flag32)
THING_BODY_GET_BOOL(thing_unused_flag33, unused_flag33)
THING_BODY_GET_BOOL(thing_unused_flag34, unused_flag34)
THING_BODY_GET_BOOL(thing_unused_flag35, unused_flag35)
THING_BODY_GET_BOOL(thing_unused_flag36, unused_flag36)
THING_BODY_GET_BOOL(thing_unused_flag37, unused_flag37)
THING_BODY_GET_BOOL(thing_unused_flag38, unused_flag38)
THING_BODY_GET_BOOL(thing_unused_flag39, unused_flag39)
THING_BODY_GET_BOOL(thing_unused_flag3, unused_flag3)
THING_BODY_GET_BOOL(thing_unused_flag40, unused_flag40)
THING_BODY_GET_BOOL(thing_unused_flag41, unused_flag41)
THING_BODY_GET_BOOL(thing_unused_flag42, unused_flag42)
THING_BODY_GET_BOOL(thing_unused_flag43, unused_flag43)
THING_BODY_GET_BOOL(thing_unused_flag44, unused_flag44)
THING_BODY_GET_BOOL(thing_unused_flag45, unused_flag45)
THING_BODY_GET_BOOL(thing_unused_flag46, unused_flag46)
THING_BODY_GET_BOOL(thing_unused_flag47, unused_flag47)
THING_BODY_GET_BOOL(thing_unused_flag48, unused_flag48)
THING_BODY_GET_BOOL(thing_unused_flag49, unused_flag49)
THING_BODY_GET_BOOL(thing_unused_flag4, unused_flag4)
THING_BODY_GET_BOOL(thing_unused_flag50, unused_flag50)
THING_BODY_GET_BOOL(thing_unused_flag51, unused_flag51)
THING_BODY_GET_BOOL(thing_unused_flag52, unused_flag52)
THING_BODY_GET_BOOL(thing_unused_flag53, unused_flag53)
THING_BODY_GET_BOOL(thing_unused_flag54, unused_flag54)
THING_BODY_GET_BOOL(thing_unused_flag55, unused_flag55)
THING_BODY_GET_BOOL(thing_unused_flag56, unused_flag56)
THING_BODY_GET_BOOL(thing_unused_flag57, unused_flag57)
THING_BODY_GET_BOOL(thing_unused_flag58, unused_flag58)
THING_BODY_GET_BOOL(thing_unused_flag59, unused_flag59)
THING_BODY_GET_BOOL(thing_unused_flag5, unused_flag5)
THING_BODY_GET_BOOL(thing_unused_flag60, unused_flag60)
THING_BODY_GET_BOOL(thing_unused_flag61, unused_flag61)
THING_BODY_GET_BOOL(thing_unused_flag62, unused_flag62)
THING_BODY_GET_BOOL(thing_unused_flag63, unused_flag63)
THING_BODY_GET_BOOL(thing_unused_flag64, unused_flag64)
THING_BODY_GET_BOOL(thing_unused_flag65, unused_flag65)
THING_BODY_GET_BOOL(thing_unused_flag66, unused_flag66)
THING_BODY_GET_BOOL(thing_unused_flag67, unused_flag67)
THING_BODY_GET_BOOL(thing_unused_flag68, unused_flag68)
THING_BODY_GET_BOOL(thing_unused_flag69, unused_flag69)
THING_BODY_GET_BOOL(thing_unused_flag6, unused_flag6)
THING_BODY_GET_BOOL(thing_unused_flag70, unused_flag70)
THING_BODY_GET_BOOL(thing_unused_flag71, unused_flag71)
THING_BODY_GET_BOOL(thing_unused_flag72, unused_flag72)
THING_BODY_GET_BOOL(thing_unused_flag73, unused_flag73)
THING_BODY_GET_BOOL(thing_unused_flag74, unused_flag74)
THING_BODY_GET_BOOL(thing_unused_flag75, unused_flag75)
THING_BODY_GET_BOOL(thing_unused_flag76, unused_flag76)
THING_BODY_GET_BOOL(thing_unused_flag77, unused_flag77)
THING_BODY_GET_BOOL(thing_unused_flag78, unused_flag78)
THING_BODY_GET_BOOL(thing_unused_flag79, unused_flag79)
THING_BODY_GET_BOOL(thing_unused_flag7, unused_flag7)
THING_BODY_GET_BOOL(thing_unused_flag80, unused_flag80)
THING_BODY_GET_BOOL(thing_unused_flag81, unused_flag81)
THING_BODY_GET_BOOL(thing_unused_flag82, unused_flag82)
THING_BODY_GET_BOOL(thing_unused_flag83, unused_flag83)
THING_BODY_GET_BOOL(thing_unused_flag84, unused_flag84)
THING_BODY_GET_BOOL(thing_unused_flag85, unused_flag85)
THING_BODY_GET_BOOL(thing_unused_flag86, unused_flag86)
THING_BODY_GET_BOOL(thing_unused_flag87, unused_flag87)
THING_BODY_GET_BOOL(thing_unused_flag88, unused_flag88)
THING_BODY_GET_BOOL(thing_unused_flag89, unused_flag89)
THING_BODY_GET_BOOL(thing_unused_flag8, unused_flag8)
THING_BODY_GET_BOOL(thing_unused_flag90, unused_flag90)
THING_BODY_GET_BOOL(thing_unused_flag91, unused_flag91)
THING_BODY_GET_BOOL(thing_unused_flag92, unused_flag92)
THING_BODY_GET_BOOL(thing_unused_flag93, unused_flag93)
THING_BODY_GET_BOOL(thing_unused_flag94, unused_flag94)
THING_BODY_GET_BOOL(thing_unused_flag95, unused_flag95)
THING_BODY_GET_BOOL(thing_unused_flag96, unused_flag96)
THING_BODY_GET_BOOL(thing_unused_flag97, unused_flag97)
THING_BODY_GET_BOOL(thing_unused_flag98, unused_flag98)
THING_BODY_GET_BOOL(thing_unused_flag99, unused_flag99)
THING_BODY_GET_BOOL(thing_unused_flag9, unused_flag9)
THING_BODY_GET_INT(thing_get_charge_count, get_charge_count)
THING_BODY_GET_INT(thing_get_current_damage, get_current_damage)
THING_BODY_GET_INT(thing_get_damage_acid, get_damage_acid)
THING_BODY_GET_INT(thing_get_damage_crush, get_damage_crush)
THING_BODY_GET_INT(thing_get_damage_digest, get_damage_digest)
THING_BODY_GET_INT(thing_get_damage_energy, get_damage_energy)
THING_BODY_GET_INT(thing_get_damage_fire, get_damage_fire)
THING_BODY_GET_INT(thing_get_damage_future1, get_damage_future1)
THING_BODY_GET_INT(thing_get_damage_future2, get_damage_future2)
THING_BODY_GET_INT(thing_get_damage_future3, get_damage_future3)
THING_BODY_GET_INT(thing_get_damage_future4, get_damage_future4)
THING_BODY_GET_INT(thing_get_damage_lightning, get_damage_lightning)
THING_BODY_GET_INT(thing_get_damage_melee, get_damage_melee)
THING_BODY_GET_INT(thing_get_damage_natural_attack, get_damage_natural_attack)
THING_BODY_GET_INT(thing_get_damage_necrosis, get_damage_necrosis)
THING_BODY_GET_INT(thing_get_damage_poison, get_damage_poison)
THING_BODY_GET_INT(thing_get_enchant, get_enchant)
THING_BODY_GET_INT(thing_get_enchant_max, get_enchant_max)
THING_BODY_GET_INT(thing_get_health, get_health)
THING_BODY_GET_INT(thing_get_health_max, get_health_max)
THING_BODY_GET_INT(thing_get_initial_charge_count, get_initial_charge_count)
THING_BODY_GET_INT(thing_get_necrotized_amount, get_necrotized_amount)
THING_BODY_GET_INT(thing_get_poisoned_amount, get_poisoned_amount)
THING_BODY_GET_INT(thing_get_stamina, get_stamina)
THING_BODY_GET_INT(thing_get_stamina_max, get_stamina_max)
THING_BODY_GET_INT(thing_get_stat_con, get_stat_con)
THING_BODY_GET_STRING(thing_get_name, text_name)
THING_BODY_GET_THING(thing_get_immediate_mob_spawner_id, get_immediate_mob_spawner_id)
THING_BODY_GET_THING(thing_get_immediate_owner_id, get_immediate_owner_id)
THING_BODY_GET_THING(thing_get_immediate_spawned_owner_id, get_immediate_spawned_owner_id)
THING_BODY_GET_THING(thing_get_leader_id, get_leader_id)
THING_BODY_GET_THING(thing_get_top_owner_id, get_top_owner_id)
THING_BODY_SET_INT(thing_decr_charge_count, decr_charge_count)
THING_BODY_SET_INT(thing_decr_current_damage, decr_current_damage)
THING_BODY_SET_INT(thing_decr_enchant, decr_enchant)
THING_BODY_SET_INT(thing_decr_enchant_max, decr_enchant_max)
THING_BODY_SET_INT(thing_decr_health, decr_health)
THING_BODY_SET_INT(thing_decr_health_max, decr_health_max)
THING_BODY_SET_INT(thing_decr_necrotized_amount, decr_necrotized_amount)
THING_BODY_SET_INT(thing_decr_poisoned_amount, decr_poisoned_amount)
THING_BODY_SET_INT(thing_decr_stamina, decr_stamina)
THING_BODY_SET_INT(thing_decr_stamina_max, decr_stamina_max)
THING_BODY_SET_INT(thing_decr_stat_con, decr_stat_con)
THING_BODY_SET_INT(thing_incr_charge_count, incr_charge_count)
THING_BODY_SET_INT(thing_incr_current_damage, incr_current_damage)
THING_BODY_SET_INT(thing_incr_enchant, incr_enchant)
THING_BODY_SET_INT(thing_incr_enchant_max, incr_enchant_max)
THING_BODY_SET_INT(thing_incr_health, incr_health)
THING_BODY_SET_INT(thing_incr_health_max, incr_health_max)
THING_BODY_SET_INT(thing_incr_necrotized_amount, incr_necrotized_amount)
THING_BODY_SET_INT(thing_incr_poisoned_amount, incr_poisoned_amount)
THING_BODY_SET_INT(thing_incr_stamina, incr_stamina)
THING_BODY_SET_INT(thing_incr_stamina_max, incr_stamina_max)
THING_BODY_SET_INT(thing_incr_stat_con, incr_stat_con)
THING_BODY_SET_INT(thing_set_current_damage, set_current_damage)
THING_BODY_SET_INT(thing_set_enchant_max, set_enchant_max)
THING_BODY_SET_INT(thing_set_enchant, set_enchant)
THING_BODY_SET_INT(thing_set_health_max, set_health_max)
THING_BODY_SET_INT(thing_set_health, set_health)
THING_BODY_SET_INT(thing_set_necrotized_amount, set_necrotized_amount)
THING_BODY_SET_INT(thing_set_poisoned_amount, set_poisoned_amount)
THING_BODY_SET_INT(thing_set_stamina_max, set_stamina_max)
THING_BODY_SET_INT(thing_set_stamina, set_stamina)
THING_BODY_SET_INT(thing_set_stat_con, set_stat_con)
THING_BODY_SET_THING(thing_skill_activate, skill_activate)
THING_BODY_SET_THING(thing_skill_deactivate, skill_deactivate)
