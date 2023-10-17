//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

static PyObject *thing_hit_common(PyObject *obj, PyObject *args, PyObject *keywds, ThingAttack type)
{
  TRACE_NO_INDENT();
  uint32_t     owner_id  = 0;
  uint32_t     hitter_id = 0;
  uint32_t     victim_id = 0;
  int          damage    = 0;
  int          thrown    = 0;
  int          crit      = 0;
  static char *kwlist[]  = {
      (char *) "owner", (char *) "hitter", (char *) "target", (char *) "damage", (char *) "crit", (char *) "thrown",
      nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "III|iii", kwlist, &owner_id, &hitter_id, &victim_id, &damage,
                                    &crit, &thrown)) {
    PY_ERR("%s: Failed parsing keywords", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp real_hitter = game->thing_find_optional(owner_id);

  if (! hitter_id) {
    PY_ERR("%s: No real_hitter thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp hitter = game->thing_find(hitter_id);
  if (! hitter) {
    PY_ERR("%s: Cannot find hitter thing ID %u", __FUNCTION__, hitter_id);
    Py_RETURN_FALSE;
  }

  if (! victim_id) {
    PY_ERR("%s: No target thing ID set", __FUNCTION__);
    Py_RETURN_FALSE;
  }

  Thingp target = game->thing_find(victim_id);
  if (! target) {
    PY_ERR("%s: Cannot find target thing ID %u", __FUNCTION__, victim_id);
    Py_RETURN_FALSE;
  }

  ThingAttackOptions attack_options {};

  if (damage) {
    attack_options.dmg_set = true;
    attack_options.damage  = damage;
  }

  attack_options.thrown = thrown ? true : false;
  attack_options.crit   = crit ? true : false;
  if (type != THING_ATTACK_NONE) {
    attack_options.attack_type_set = true;
    attack_options.attack[ type ]  = true;
  }
  attack_options.real_hitter = real_hitter;

  if (attack_options.real_hitter) {
    if (damage) {
      IF_DEBUG { attack_options.real_hitter->log("Attack for %d", damage); }
    } else {
      IF_DEBUG { attack_options.real_hitter->log("Attack"); }
    }
  } else {
    if (damage) {
      IF_DEBUG { hitter->log("Attack for %d", damage); }
    } else {
      IF_DEBUG { hitter->log("Attack"); }
    }
  }
  TRACE_AND_INDENT();

  if (hitter->attack(target, &attack_options)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *thing_hit(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_NONE);
}

PyObject *thing_hit_dmg_melee(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_MELEE);
}

PyObject *thing_hit_dmg_stamina(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_STAMINA_DRAIN);
}

PyObject *thing_hit_dmg_magic_drain(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_MAGIC_DRAIN);
}

PyObject *thing_hit_dmg_acid(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_ACID);
}

PyObject *thing_hit_dmg_water(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_WATER);
}

PyObject *thing_hit_dmg_cold(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_COLD);
}

PyObject *thing_hit_dmg_crush(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_CRUSH);
}

PyObject *thing_hit_dmg_impact(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_IMPACT);
}

PyObject *thing_hit_dmg_missile(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_MISSILE);
}

PyObject *thing_hit_dmg_digest(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_DIGEST);
}

PyObject *thing_hit_dmg_energy(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_ENERGY);
}

PyObject *thing_hit_dmg_negation(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_NEGATION);
}

PyObject *thing_hit_dmg_fire(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_FIRE);
}

PyObject *thing_hit_dmg_heat(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_HEAT);
}

PyObject *thing_hit_dmg_drown(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_DROWN);
}

PyObject *thing_hit_dmg_bite(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_BITE);
}

PyObject *thing_hit_dmg_claw(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_CLAW);
}

PyObject *thing_hit_dmg_lightning(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_LIGHTNING);
}

PyObject *thing_hit_dmg_necrosis(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_NECROSIS);
}

PyObject *thing_hit_dmg_poison(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  return thing_hit_common(obj, args, keywds, THING_ATTACK_POISON);
}
