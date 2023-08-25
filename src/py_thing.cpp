//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"

static int NO_VALUE = -99999;

PyObject *thing_coords_get(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "id", nullptr};

  TRACE_NO_INDENT();
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

PyObject *thing_possible_to_attack(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &hitter_id, &victim_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! hitter_id) {
    ERR("%s: No hitter thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp hitter = game->thing_find(hitter_id);
  if (! hitter) {
    ERR("%s: Cannot find hitter thing ID %u", __FUNCTION__, hitter_id);
    Py_RETURN_FALSE;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    Py_RETURN_FALSE;
  }

  IF_DEBUG { hitter->log("Check if possible to attack target %s", target->to_short_string().c_str()); }

  if (hitter->possible_to_attack(target)) {
    IF_DEBUG { hitter->log("Check if possible to target %s; yes", target->to_short_string().c_str()); }
    Py_RETURN_TRUE;
  }
  IF_DEBUG { hitter->log("Check if possible to attack %s; no", target->to_short_string().c_str()); }
  Py_RETURN_FALSE;
}

PyObject *thing_shoot_projectile_or_laser_at(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id  = 0;
  char        *item      = nullptr;
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "owner", (char *) "item", (char *) "target", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &owner_id, &item, &victim_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! item) {
    ERR("%s: No item thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    Py_RETURN_FALSE;
  }

  IF_DEBUG { owner->log("Fire %s at %s", item, target->to_short_string().c_str()); }

  auto what     = std::string(item);
  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what.c_str());
    Py_RETURN_FALSE;
  }

  auto itemp = pcg_one_of(tp_cands);
  if (! itemp) {
    ERR("%s: Cannot find item to shoot %s", __FUNCTION__, item);
    Py_RETURN_FALSE;
  }

  if (itemp->is_projectile()) {
    if (owner->projectile_shoot_at(nullptr /* staff */, std::string(item), target)) {
      Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
  }
  if (itemp->is_laser()) {
    if (owner->laser_shoot_at(nullptr /* staff */, std::string(item), target)) {
      Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
  }
  if (itemp->is_usable()) {
    if (owner->item_targeted_use_at(nullptr /* staff */, target)) {
      Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
  }
  owner->err("Cannot shoot %s at %s", item, target->to_short_string().c_str());
  Py_RETURN_FALSE;
}

PyObject *thing_throw_at(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id  = 0;
  char        *item      = nullptr;
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "owner", (char *) "item", (char *) "target", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &owner_id, &item, &victim_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! item) {
    ERR("%s: No item thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    Py_RETURN_FALSE;
  }

  IF_DEBUG { owner->log("Throw %s at %s", item, target->to_short_string().c_str()); }

  auto tp_cands = tp_find_wildcard(item);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", item);
    Py_RETURN_FALSE;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("Could not find to throw %s", item);
    Py_RETURN_FALSE;
  }

  auto what = owner->level->thing_new(tp, target->curr_at);
  if (! what) {
    ERR("Could not create to throw %s", item);
    Py_RETURN_FALSE;
  }

  if (! owner->throw_at(what, target)) {
    owner->err("Cannot throw %s at %s", item, target->to_short_string().c_str());
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}

PyObject *thing_spell_cast_at(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id  = 0;
  char        *item      = nullptr;
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "owner", (char *) "item", (char *) "target", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &owner_id, &item, &victim_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! item) {
    ERR("%s: No item thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! victim_id) {
    ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    Py_RETURN_FALSE;
  }

  IF_DEBUG { owner->log("Throw %s at %s", item, target->to_short_string().c_str()); }

  auto tp_cands = tp_find_wildcard(item);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", item);
    Py_RETURN_FALSE;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("Could not find to spell_cast %s", item);
    Py_RETURN_FALSE;
  }

  auto what = owner->level->thing_new(tp, target->curr_at);
  if (! what) {
    ERR("Could not create to spell_cast %s", item);
    Py_RETURN_FALSE;
  }

  if (! owner->spell_cast_at(what, target)) {
    owner->err("Cannot spell_cast %s at %s", item, target->to_short_string().c_str());
    Py_RETURN_FALSE;
  }

  what->dead("used");

  Py_RETURN_TRUE;
}

PyObject *thing_death_by(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id        = 0;
  char        *reason    = nullptr;
  uint32_t     killer_id = 0;
  static char *kwlist[]  = {(char *) "t", (char *) "reason", (char *) "defeater", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &id, &reason, &killer_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find t thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! killer_id) {
    ERR("%s: No defeater thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp defeater = game->thing_find(killer_id);
  if (! defeater) {
    ERR("%s: Cannot find defeater thing ID %u", __FUNCTION__, killer_id);
    Py_RETURN_FALSE;
  }

  IF_DEBUG { t->log("Killed by %s, reason %s", defeater->to_string().c_str(), reason); }
  t->dead(defeater, "%s", reason);

  Py_RETURN_TRUE;
}

PyObject *thing_dead(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "reason", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find t thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  IF_DEBUG { t->log("Perma killed: reason %s", reason); }
  t->dead("%s", reason);
  t->is_resurrection_blocked = true;
  Py_RETURN_TRUE;
}

PyObject *thing_freeze(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "t", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find t thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  t->frozen_set();
  Py_RETURN_TRUE;
}

PyObject *thing_unfreeze(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "t", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  t->frozen_unset();
  Py_RETURN_TRUE;
}

PyObject *thing_perma_death(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "reason", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  IF_DEBUG { t->log("Killed: reason %s", reason); }
  t->dead("%s", reason);
  Py_RETURN_TRUE;
}

PyObject *thing_resurrect(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "reason", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  IF_DEBUG { t->log("Resurrect attempt: reason %s", reason); }
  if (t->resurrect_forced()) {
    Py_RETURN_FALSE;
  } else {
    Py_RETURN_TRUE;
  }
}

PyObject *thing_carry(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "what", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! what) {
    t->err("Could not carry nameless object");
    Py_RETURN_FALSE;
  }

  auto cands = tp_find_wildcard(what);
  auto tp    = pcg_one_of(cands);
  if (unlikely(! tp)) {
    t->err("Could not find to carry %s", what);
    Py_RETURN_FALSE;
  }

  auto item = t->level->thing_new(tp, t->curr_at);
  if (! item) {
    t->err("Could not create to carry %s", what);
    Py_RETURN_FALSE;
  }

  CarryOptions carry_options;
  carry_options.is_able_to_be_equipped = true;

  if (! t->carry(item, carry_options)) {
    t->err("Could not carry %s", what);
    Py_RETURN_FALSE;
  }

  return Py_BuildValue("I", item->id);
}

PyObject *thing_new(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "what", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! what) {
    t->err("Could not carry nameless object");
    Py_RETURN_FALSE;
  }

  auto cands = tp_find_wildcard(what);
  auto tp    = pcg_one_of(cands);
  if (unlikely(! tp)) {
    t->err("Could not find to carry %s", what);
    Py_RETURN_FALSE;
  }

  auto item = t->level->thing_new(tp, t->curr_at);
  if (! item) {
    t->err("Could not create to carry %s", what);
    Py_RETURN_FALSE;
  }

  return Py_BuildValue("I", item->id);
}

PyObject *thing_enemy(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "what", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! what) {
    t->err("Could not enemy nameless object");
    Py_RETURN_FALSE;
  }

  bool got_one = false;
  for (auto tp : tp_find_wildcard(what)) {
    t->add_enemy(tp);
    got_one = true;
  }

  if (! got_one) {
    t->err("Could not find template to add as enemy %s", what);
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}

PyObject *thing_friend(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "me", (char *) "what", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (! what) {
    t->err("Could not friend nameless object");
    Py_RETURN_FALSE;
  }

  bool got_one = false;
  for (auto tp : tp_find_wildcard(what)) {
    t->add_friend(tp);
    got_one = true;
  }

  if (! got_one) {
    t->err("Could not find template to add as friend %s", what);
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}

PyObject *thing_friend_add(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  uint32_t     it_id    = 0;
  static char *kwlist[] = {(char *) "me", (char *) "it", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &it_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! it_id) {
    ERR("%s: No friend thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  Thingp it = game->thing_find(it_id);
  if (! it) {
    ERR("%s: Cannot find friend thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  t->add_friend(it);

  Py_RETURN_TRUE;
}

PyObject *thing_polymorph(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *into     = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "into", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &into)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  auto cands = tp_find_wildcard(into);
  auto tp    = pcg_one_of(cands);
  if (unlikely(! tp)) {
    ERR("%s: No polymorph into %s found", __FUNCTION__, into);
    Py_RETURN_FALSE;
  }

  t->polymorph(tp);
  Py_RETURN_TRUE;
}

PyObject *thing_teleport_randomly(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "t", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  TeleportOptions options;
  options.teleport_self  = true;
  options.teleport_limit = true;
  t->teleport_randomly(options);
  Py_RETURN_TRUE;
}

PyObject *thing_teleport(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  int          x        = NO_VALUE;
  int          y        = NO_VALUE;
  static char *kwlist[] = {(char *) "id", (char *) "x", (char *) "y", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Iii", kwlist, &id, &x, &y)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (x == NO_VALUE) {
    ERR("%s: Missing 'x'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (y == NO_VALUE) {
    ERR("%s: Missing 'y'", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  if (t->level->is_oob(x, y)) {
    PyObject *lst = PyList_New(0);
    return lst;
  }

  bool too_far = false;

  TeleportOptions teleport_options;
  teleport_options.teleport_self  = true;
  teleport_options.teleport_limit = false;
  t->teleport_carefree(teleport_options, point(x, y), &too_far);
  Py_RETURN_TRUE;
}

PyObject *thing_set_mob(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  uint32_t     owner_id = 0;
  static char *kwlist[] = {(char *) "t", (char *) "owner", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &owner_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  t->mob_set(owner);
  Py_RETURN_TRUE;
}

PyObject *thing_is_same_mob(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  uint32_t     owner_id = 0;
  static char *kwlist[] = {(char *) "t", (char *) "owner", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &owner_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (t->same_mob(owner)) {
    Py_RETURN_TRUE;
  }

  Py_RETURN_FALSE;
}

PyObject *thing_set_leader(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  uint32_t     owner_id = 0;
  static char *kwlist[] = {(char *) "t", (char *) "owner", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &owner_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  t->leader_set(owner);
  Py_RETURN_TRUE;
}

PyObject *thing_buff_add(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: No buff name set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what);
    Py_RETURN_FALSE;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("%s: No buff tp called %s found", __FUNCTION__, what);
    Py_RETURN_FALSE;
  }

  TRACE_NO_INDENT();
  owner->buff_add(tp);
  Py_RETURN_TRUE;
}

PyObject *thing_debuff_add(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: No debuff name set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what);
    Py_RETURN_FALSE;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("%s: No debuff tp called %s found", __FUNCTION__, what);
    Py_RETURN_FALSE;
  }

  owner->debuff_add(tp);
  Py_RETURN_TRUE;
}

PyObject *thing_buff_remove(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: No buff name set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what);
    Py_RETURN_FALSE;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("%s: No buff tp called %s found", __FUNCTION__, what);
    Py_RETURN_FALSE;
  }

  owner->buff_remove(tp);
  Py_RETURN_TRUE;
}

PyObject *thing_debuff_remove(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! what) {
    ERR("%s: No debuff name set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  auto tp_cands = tp_find_wildcard(what);
  if (! tp_cands.size()) {
    ERR("Cannot find any %s to spawn", what);
    Py_RETURN_FALSE;
  }

  auto tp = pcg_one_of(tp_cands);
  if (unlikely(! tp)) {
    ERR("%s: No debuff tp called %s found", __FUNCTION__, what);
    Py_RETURN_FALSE;
  }

  owner->debuff_remove(tp);
  Py_RETURN_TRUE;
}

PyObject *thing_speaks(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *msg      = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "msg", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &msg)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! msg) {
    ERR("%s: No msg thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (owner->is_monst()) {
    owner->msg("%s says '%s'", owner->text_The().c_str(), msg);
  } else {
    owner->msg("%s", msg);
  }

  Py_RETURN_TRUE;
}

PyObject *thing_msg(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *msg      = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "msg", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &msg)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! msg) {
    ERR("%s: No msg thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  owner->msg("%s", msg);

  Py_RETURN_TRUE;
}

PyObject *thing_msg_if_not_dead_or_dying(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *msg      = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "msg", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &msg)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  //
  // To avoid logs when unequipping when dying, for example.
  //
  if (owner->is_dead_or_dying()) {
    Py_RETURN_FALSE;
  }

  if (! msg) {
    ERR("%s: No msg thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  owner->msg("%s", msg);

  Py_RETURN_TRUE;
}

PyObject *thing_popup(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *msg      = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "msg", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &msg)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! msg) {
    ERR("%s: No popup msg thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  //
  // If not reachable, suppress the popup
  //
  if (owner->distance_to_player() < DMAP_IS_PASSABLE) {
    owner->popup(msg);
  }

  Py_RETURN_TRUE;
}

PyObject *thing_sound_play_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char    *name     = nullptr;
  uint32_t owner_id = 0;

  static char *kwlist[] = {(char *) "owner", (char *) "name", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &owner_id, &name)) {
    ERR("thing_sound_play: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! name) {
    ERR("thing_sound_play: Missing name attr");
    Py_RETURN_FALSE;
  }

  if (g_opt_test_dungeon_gen) {
    Py_RETURN_TRUE;
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
  TRACE_NO_INDENT();
  uint32_t owner_id = 0;
  char    *name     = nullptr;
  int      channel  = 0;

  static char *kwlist[] = {(char *) "owner", (char *) "channel", (char *) "name", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Iis", kwlist, &owner_id, &channel, &name)) {
    ERR("thing_sound_play_channel: Bad arguments");
    Py_RETURN_FALSE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_FALSE;
  }

  if (! name) {
    ERR("thing_sound_play: Missing name attr");
    Py_RETURN_FALSE;
  }
  if (! name) {
    ERR("thing_sound_play_channel: Missing name attr");
    Py_RETURN_FALSE;
  }

  if (g_opt_test_dungeon_gen) {
    Py_RETURN_TRUE;
  }

  PY_DBG("sound_play_channel(channel=%d, name=%s)", channel, name);

  std::string alias = name;
  if (! owner->thing_sound_play_channel(channel, alias)) {
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}

PyObject *spawn_set_fire_to_things_around_me(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", nullptr};

  TRACE_NO_INDENT();
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

  if (t->spawn_set_fire_to_things_around_me(std::string(what), 1)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_things_around_me(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char    *what   = nullptr;
  uint32_t id     = 0;
  int      radius = 1;

  static char *kwlist[] = {(char *) "id", (char *) "what", (char *) "radius", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Isi", kwlist, &id, &what, &radius)) {
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

  if (t->spawn_things_around_me(std::string(what), radius)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_gas_poison_around_thing(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t id     = 0;
  uint32_t radius = 0;

  static char *kwlist[] = {(char *) "id", (char *) "radius", nullptr};

  TRACE_NO_INDENT();
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

  if (t->spawn_gas_poison_around_thing(radius)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_gas_healing_around_thing(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t id     = 0;
  uint32_t radius = 0;

  static char *kwlist[] = {(char *) "id", (char *) "radius", nullptr};

  TRACE_NO_INDENT();
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

  if (t->spawn_gas_healing_around_thing(radius)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_at_my_position(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", nullptr};

  TRACE_NO_INDENT();
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

PyObject *spawn_owned_thing_at_my_position(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", nullptr};

  TRACE_NO_INDENT();
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

  auto it = t->spawn_owned_thing_at_my_position(std::string(what));
  if (it) {
    return Py_BuildValue("I", it->id);
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_minion_at_my_position(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", nullptr};

  TRACE_NO_INDENT();
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

  auto it = t->spawn_minion_at_my_position(std::string(what));
  if (it) {
    return Py_BuildValue("I", it->id);
  }
  Py_RETURN_FALSE;
}

PyObject *spawn_minion_next_to(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char    *what = nullptr;
  uint32_t id   = 0;

  static char *kwlist[] = {(char *) "id", (char *) "what", nullptr};

  TRACE_NO_INDENT();
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

  auto it = t->spawn_minion_next_to(std::string(what));
  if (it) {
    return Py_BuildValue("I", it->id);
  }
  Py_RETURN_FALSE;
}

PyObject *thing_get_followers(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "id", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  if (! id) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_FALSE;
  }

  Thingp t = game->thing_find(id);
  if (unlikely(! t)) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  auto items = 0;

  PyObject *lst  = PyList_New(items);
  auto      item = 0;

  if (! t->maybe_infop()) {
    PyObject *lst = PyList_New(0);
    return lst;
  }

  for (auto f : t->infop()->followers) {
    PyList_SetItem(lst, item, Py_BuildValue("I", f.id));
    item++;
  }

  return lst;
}
