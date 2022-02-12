//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_hiscore.hpp"
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

#define THING_BODY_SET_THING(__func__, __api__)                                                                      \
  PyObject *__func__(PyObject * obj, PyObject * args, PyObject * keywds)                                             \
  {                                                                                                                  \
    TRACE_AND_INDENT();                                                                                              \
    uint32_t     id       = 0;                                                                                       \
    uint32_t     oid      = 0;                                                                                       \
    static char *kwlist[] = {(char *) "id", (char *) "oid", 0};                                                      \
                                                                                                                     \
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

THING_BODY_SET_INT(thing_charge_count_decr, charge_count_decr)
THING_BODY_SET_INT(thing_current_damage_decr, current_damage_decr)
THING_BODY_SET_INT(thing_enchant_decr, enchant_decr)
THING_BODY_SET_INT(thing_enchant_max_decr, enchant_max_decr)
THING_BODY_SET_INT(thing_health_decr, health_decr)
THING_BODY_SET_INT(thing_necrotized_amount_decr, necrotized_amount_decr)
THING_BODY_SET_INT(thing_poisoned_amount_decr, poisoned_amount_decr)
THING_BODY_SET_INT(thing_stamina_decr, stamina_decr)
THING_BODY_SET_INT(thing_stamina_max_decr, stamina_max_decr)
THING_BODY_SET_INT(thing_stat_con_decr, stat_con_decr)
THING_BODY_SET_INT(thing_charge_count_incr, charge_count_incr)
THING_BODY_SET_INT(thing_current_damage_incr, current_damage_incr)
THING_BODY_SET_INT(thing_enchant_incr, enchant_incr)
THING_BODY_SET_INT(thing_enchant_max_incr, enchant_max_incr)
THING_BODY_SET_INT(thing_health_incr, health_incr)
THING_BODY_SET_INT(thing_necrotized_amount_incr, necrotized_amount_incr)
THING_BODY_SET_INT(thing_poisoned_amount_incr, poisoned_amount_incr)
THING_BODY_SET_INT(thing_stamina_incr, stamina_incr)
THING_BODY_SET_INT(thing_stamina_max_incr, stamina_max_incr)
THING_BODY_SET_INT(thing_stat_con_incr, stat_con_incr)
THING_BODY_SET_INT(thing_stat_def_incr, stat_def_incr)
THING_BODY_SET_INT(thing_stat_str_incr, stat_str_incr)
THING_BODY_SET_INT(thing_set_current_damage, set_current_damage)
THING_BODY_SET_INT(thing_set_enchant_max, set_enchant_max)
THING_BODY_SET_INT(thing_set_enchant, set_enchant)
THING_BODY_SET_INT(thing_set_health, set_health)
THING_BODY_SET_INT(thing_set_necrotized_amount, set_necrotized_amount)
THING_BODY_SET_INT(thing_set_poisoned_amount, set_poisoned_amount)
THING_BODY_SET_INT(thing_set_stamina_max, set_stamina_max)
THING_BODY_SET_INT(thing_set_stamina, set_stamina)
THING_BODY_SET_INT(thing_set_stat_con, set_stat_con)

THING_BODY_SET_INT(thing_health_max_decr, health_max_decr)
THING_BODY_SET_INT(thing_health_max_incr, health_max_incr)
THING_BODY_SET_INT(thing_set_health_max, set_health_max)

THING_BODY_SET_INT(thing_noise_incr, noise_incr)
THING_BODY_SET_INT(thing_noise_decr, noise_decr)
THING_BODY_SET_INT(thing_set_noise, set_noise)

THING_BODY_SET_THING(thing_skill_activate, skill_activate)
THING_BODY_SET_THING(thing_skill_deactivate, skill_deactivate)
