//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

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
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &hitter_id, &victim_id)) {
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

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
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
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &hitter_id, &victim_id)) {
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

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
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
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "owner", (char *) "item", (char *) "target", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &owner_id, &item, &victim_id)) {
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

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
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

PyObject *thing_set_mob(PyObject *obj, PyObject *args, PyObject *keywds)
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

  me->mob_set(owner);
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

  me->leader_set(owner);
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
  if (owner->distance_to_player() < DMAP_IS_PASSABLE) {
    if (owner->is_monst()) {
      owner->msg("%s says '%s'", owner->text_The().c_str(), msg);
    } else {
      owner->msg("%s", msg);
    }
  }

  Py_RETURN_NONE;
}

PyObject *thing_popup(PyObject *obj, PyObject *args, PyObject *keywds)
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
    ERR("%s: No popup msg thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  //
  // If not reachable, suppress the popup
  //
  if (owner->distance_to_player() < DMAP_IS_PASSABLE) {
    owner->popup(msg);
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

  if (t->spawn_fire(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *level_spawn_gas_poison_around_thing(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t id     = 0;
  uint32_t radius = 0;

  static char *kwlist[] = {(char *) "id", (char *) "radius", 0};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &radius)) {
    ERR("%s: Bad args", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Missing 'id'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  PY_DBG("%s(%X, %d)", __FUNCTION__, id, radius);

  auto level = game->get_current_level();
  if (! level) {
    Py_RETURN_FALSE;
  }

  auto t = level->thing_find(ThingId(id));
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing %08" PRIX32 "", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->spawn_gas_poison(radius)) {
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

  if (t->spawn_at_if_possible(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}
