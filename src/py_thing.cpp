//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"

PyObject *thing_coords_get(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "id", nullptr};

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
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", nullptr};

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

  AttackOptions attack_options {};

  hitter->log("Attack hit");
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_draining(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set         = true;
  attack_options.damage          = damage;
  attack_options.attack_draining = true;

  hitter->log("Attack with stamina damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_acid(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set     = true;
  attack_options.damage      = damage;
  attack_options.attack_acid = true;

  hitter->log("Attack with acid damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_water(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set      = true;
  attack_options.damage       = damage;
  attack_options.attack_water = true;

  hitter->log("Attack with water damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_cold(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set     = true;
  attack_options.damage      = damage;
  attack_options.attack_cold = true;

  hitter->log("Attack with cold damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_crush(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set      = true;
  attack_options.damage       = damage;
  attack_options.attack_crush = true;

  hitter->log("Attack with crush damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_digest(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set       = true;
  attack_options.damage        = damage;
  attack_options.attack_digest = true;

  hitter->log("Attack with digest damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_energy(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set       = true;
  attack_options.damage        = damage;
  attack_options.attack_energy = true;

  hitter->log("Attack with energy damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_negation(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set         = true;
  attack_options.damage          = damage;
  attack_options.attack_negation = true;

  hitter->log("Attack with negation damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_fire(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set     = true;
  attack_options.damage      = damage;
  attack_options.attack_fire = true;

  hitter->log("Attack with fire damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_drown(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set      = true;
  attack_options.damage       = damage;
  attack_options.attack_drown = true;

  hitter->log("Attack with drown damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_bite(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set     = true;
  attack_options.damage      = damage;
  attack_options.attack_bite = true;

  hitter->log("Attack with bite damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_claw(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set     = true;
  attack_options.damage      = damage;
  attack_options.attack_claw = true;

  hitter->log("Attack with claw damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_lightning(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set          = true;
  attack_options.damage           = damage;
  attack_options.attack_lightning = true;

  hitter->log("Attack with lightning damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_necrosis(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set         = true;
  attack_options.damage          = damage;
  attack_options.attack_necrosis = true;

  hitter->log("Attack with necrosis damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit_dmg_poison(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", (char *) "damage", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IIi", kwlist, &hitter_id, &victim_id, &damage)) {
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

  AttackOptions attack_options {};
  attack_options.dmg_set       = true;
  attack_options.damage        = damage;
  attack_options.attack_poison = true;

  hitter->log("Attack with poison damage, %d", damage);
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_possible_to_attack(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "hitter", (char *) "target", nullptr};

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

  IF_DEBUG { hitter->log("Check if possible to attack target %s", target->to_short_string().c_str()); }

  if (hitter->possible_to_attack(target)) {
    IF_DEBUG { hitter->log("Check if possible to target %s; yes", target->to_short_string().c_str()); }
    Py_RETURN_TRUE;
  }
  IF_DEBUG { hitter->log("Check if possible to attack %s; no", target->to_short_string().c_str()); }
  Py_RETURN_FALSE;
}

PyObject *thing_fire_at(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id  = 0;
  char        *item      = nullptr;
  uint32_t     victim_id = 0;
  static char *kwlist[]  = {(char *) "owner", (char *) "item", (char *) "target", nullptr};

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

  IF_DEBUG { owner->log("Fire %s at %s", item, target->to_short_string().c_str()); }

  auto what  = std::string(item);
  auto itemp = tp_find(what);
  if (! itemp) {
    ERR("%s: Cannot find item to fire %s", __FUNCTION__, item);
    Py_RETURN_NONE;
  }

  if (itemp->is_projectile()) {
    if (owner->fire_projectile_at(nullptr /* staff */, std::string(item), target)) {
      Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
  }
  if (itemp->is_laser()) {
    if (owner->laser_fire_at(nullptr /* staff */, std::string(item), target)) {
      Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
  }
  if (itemp->is_usable()) {
    if (owner->item_targetted_use_at(nullptr /* staff */, target)) {
      Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
  }
  owner->err("Cannot fire %s at %s", item, target->to_short_string().c_str());
  Py_RETURN_FALSE;
}

PyObject *thing_death_by(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id        = 0;
  char        *reason    = nullptr;
  uint32_t     killer_id = 0;
  static char *kwlist[]  = {(char *) "t", (char *) "reason", (char *) "defeater", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "IsI", kwlist, &id, &reason, &killer_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find t thing ID %u", __FUNCTION__, id);
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

  IF_DEBUG { t->log("Killed by %s, reason %s", defeater->to_string().c_str(), reason); }
  t->dead(defeater, "%s", reason);

  Py_RETURN_NONE;
}

PyObject *thing_dead(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "reason", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find t thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  IF_DEBUG { t->log("Perma killed: reason %s", reason); }
  t->dead("%s", reason);
  t->is_resurrection_blocked = true;
  Py_RETURN_NONE;
}

PyObject *thing_freeze(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "t", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find t thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  t->frozen_set();
  Py_RETURN_NONE;
}

PyObject *thing_unfreeze(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "t", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No t thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  t->frozen_unset();
  Py_RETURN_NONE;
}

PyObject *thing_perma_death(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "reason", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  IF_DEBUG { t->log("Killed: reason %s", reason); }
  t->dead("%s", reason);
  Py_RETURN_NONE;
}

PyObject *thing_resurrect(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *reason   = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "reason", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &reason)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  if (! reason) {
    ERR("%s: No reason thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  IF_DEBUG { t->log("Resurrected: reason %s", reason); }
  t->resurrect_forced();
  Py_RETURN_NONE;
}

PyObject *thing_carry(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "what", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  if (! what) {
    t->err("Could not carry nameless object");
    Py_RETURN_NONE;
  }

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    t->err("Could not find to carry %s", what);
    Py_RETURN_NONE;
  }

  auto item = t->level->thing_new(tp, t->curr_at);
  if (! item) {
    t->err("Could not create to carry %s", what);
    Py_RETURN_NONE;
  }

  if (! t->carry(item)) {
    t->err("Could not carry %s", what);
    Py_RETURN_NONE;
  }

  return Py_BuildValue("I", item->id);
}

PyObject *thing_enemy(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "what", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  if (! what) {
    t->err("Could not enemy nameless object");
    Py_RETURN_NONE;
  }

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    t->err("Could not find to enemy %s", what);
    Py_RETURN_NONE;
  }

  t->add_enemy(tp);

  Py_RETURN_TRUE;
}

PyObject *thing_friend(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "what", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &what)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  if (! what) {
    t->err("Could not friend nameless object");
    Py_RETURN_NONE;
  }

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    t->err("Could not find to friend %s", what);
    Py_RETURN_NONE;
  }

  t->add_friend(tp);

  Py_RETURN_TRUE;
}

PyObject *thing_polymorph(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  char        *into     = nullptr;
  static char *kwlist[] = {(char *) "t", (char *) "into", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Is", kwlist, &id, &into)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  auto tp = tp_find(into);
  if (unlikely(! tp)) {
    ERR("%s: No polymorph into %s found", __FUNCTION__, into);
    Py_RETURN_NONE;
  }

  t->polymorph(tp);
  Py_RETURN_NONE;
}

PyObject *thing_teleport_randomly(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  static char *kwlist[] = {(char *) "t", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "I", kwlist, &id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  t->teleport_randomly();
  Py_RETURN_NONE;
}

PyObject *thing_teleport(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  int          x        = -1;
  int          y        = -1;
  static char *kwlist[] = {(char *) "id", (char *) "x", (char *) "y", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Iii", kwlist, &id, &x, &y)) {
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

  if (t->level->is_oob(x, y)) {
    PyObject *lst = PyList_New(0);
    return lst;
  }

  bool too_far = false;
  t->teleport_carefree(point(x, y), &too_far);
  Py_RETURN_NONE;
}

PyObject *thing_set_mob(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  uint32_t     owner_id = 0;
  static char *kwlist[] = {(char *) "t", (char *) "owner", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &owner_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  t->mob_set(owner);
  Py_RETURN_NONE;
}

PyObject *thing_set_leader(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     id       = 0;
  uint32_t     owner_id = 0;
  static char *kwlist[] = {(char *) "t", (char *) "owner", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "II", kwlist, &id, &owner_id)) {
    ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! id) {
    ERR("%s: No thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  if (! owner_id) {
    ERR("%s: No owner thing ID set", __FUNCTION__);
    Py_RETURN_NONE;
  }

  Thingp t = game->thing_find(id);
  if (! t) {
    ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);
    Py_RETURN_NONE;
  }

  Thingp owner = game->thing_find(owner_id);
  if (! owner) {
    ERR("%s: Cannot find owner thing ID %u", __FUNCTION__, owner_id);
    Py_RETURN_NONE;
  }

  t->leader_set(owner);
  Py_RETURN_NONE;
}

PyObject *thing_buff_add(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", nullptr};

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
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", nullptr};

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
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", nullptr};

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
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *what     = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "what", nullptr};

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

PyObject *thing_speaks(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *msg      = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "msg", nullptr};

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

  if (owner->is_monst()) {
    owner->topcon("%s says '%s'", owner->text_The().c_str(), msg);
  } else {
    owner->topcon("%s", msg);
  }

  Py_RETURN_NONE;
}

PyObject *thing_msg(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *msg      = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "msg", nullptr};

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

  owner->msg("%s", msg);

  Py_RETURN_NONE;
}

PyObject *thing_popup(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id = 0;
  char        *msg      = nullptr;
  static char *kwlist[] = {(char *) "owner", (char *) "msg", nullptr};

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
  TRACE_NO_INDENT();
  char    *name     = nullptr;
  uint32_t owner_id = 0;

  static char *kwlist[] = {(char *) "owner", (char *) "name", nullptr};

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
  TRACE_NO_INDENT();
  uint32_t owner_id = 0;
  char    *name     = nullptr;
  int      channel  = 0;

  static char *kwlist[] = {(char *) "owner", (char *) "channel", (char *) "name", nullptr};

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

PyObject *spawn_set_fire_to_things_around_me(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
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

PyObject *spawn_at_my_position(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
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

PyObject *spawn_at_if_possible(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
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

  if (t->spawn_at_if_possible(std::string(what))) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}
