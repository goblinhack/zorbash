//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_py_thing.hpp"
#include "my_thing.hpp"

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
THING_BODY_SET_INT(thing_charge_count_incr, charge_count_incr)

THING_BODY_SET_INT(thing_dmg_current_decr, dmg_current_decr)
THING_BODY_SET_INT(thing_dmg_current_incr, dmg_current_incr)
THING_BODY_SET_INT(thing_dmg_current_set, dmg_current_set)

THING_BODY_SET_INT(thing_enchant_decr, enchant_decr)
THING_BODY_SET_INT(thing_enchant_incr, enchant_incr)
THING_BODY_SET_INT(thing_enchant_max_current_decr, enchant_max_current_decr)
THING_BODY_SET_INT(thing_enchant_max_current_incr, enchant_max_current_incr)
THING_BODY_SET_INT(thing_enchant_max_set, enchant_set)
THING_BODY_SET_INT(thing_enchant_max_current_set, enchant_max_current_set)

THING_BODY_SET_INT(thing_health_decr, health_decr)
THING_BODY_SET_INT(thing_health_incr, health_incr)
THING_BODY_SET_INT(thing_health_set, health_set)

THING_BODY_SET_INT(thing_necrotized_amount_decr, necrotized_amount_decr)
THING_BODY_SET_INT(thing_necrotized_amount_incr, necrotized_amount_incr)
THING_BODY_SET_INT(thing_necrotized_amount_set, necrotized_amount_set)

THING_BODY_SET_INT(thing_poisoned_amount_decr, poisoned_amount_decr)
THING_BODY_SET_INT(thing_poisoned_amount_incr, poisoned_amount_incr)
THING_BODY_SET_INT(thing_poisoned_amount_set, poisoned_amount_set)

THING_BODY_SET_INT(thing_stamina_decr, stamina_decr)
THING_BODY_SET_INT(thing_stamina_incr, stamina_incr)
THING_BODY_SET_INT(thing_stamina_max_decr, stamina_max_decr)
THING_BODY_SET_INT(thing_stamina_max_incr, stamina_max_incr)
THING_BODY_SET_INT(thing_stamina_max_set, stamina_max_set)
THING_BODY_SET_INT(thing_stamina_set, stamina_set)

THING_BODY_SET_INT(thing_stat_att_incr, stat_att_incr)
THING_BODY_SET_INT(thing_stat_att_decr, stat_att_decr)
THING_BODY_SET_INT(thing_stat_att_set, stat_att_set)
THING_BODY_SET_INT(thing_stat_att_mod_decr, stat_att_mod_decr)
THING_BODY_SET_INT(thing_stat_att_mod_incr, stat_att_mod_incr)
THING_BODY_SET_INT(thing_stat_att_mod_set, stat_att_mod_set)

THING_BODY_SET_INT(thing_stat_def_incr, stat_def_incr)
THING_BODY_SET_INT(thing_stat_def_decr, stat_def_decr)
THING_BODY_SET_INT(thing_stat_def_set, stat_def_set)
THING_BODY_SET_INT(thing_stat_def_mod_decr, stat_def_mod_decr)
THING_BODY_SET_INT(thing_stat_def_mod_incr, stat_def_mod_incr)
THING_BODY_SET_INT(thing_stat_def_mod_set, stat_def_mod_set)

THING_BODY_SET_INT(thing_stat_con_incr, stat_con_incr)
THING_BODY_SET_INT(thing_stat_con_decr, stat_con_decr)
THING_BODY_SET_INT(thing_stat_con_set, stat_con_set)
THING_BODY_SET_INT(thing_stat_con_mod_decr, stat_con_mod_decr)
THING_BODY_SET_INT(thing_stat_con_mod_incr, stat_con_mod_incr)
THING_BODY_SET_INT(thing_stat_con_mod_set, stat_con_mod_set)

THING_BODY_SET_INT(thing_stat_dex_incr, stat_dex_incr)
THING_BODY_SET_INT(thing_stat_dex_decr, stat_dex_decr)
THING_BODY_SET_INT(thing_stat_dex_set, stat_dex_set)
THING_BODY_SET_INT(thing_stat_dex_mod_decr, stat_dex_mod_decr)
THING_BODY_SET_INT(thing_stat_dex_mod_incr, stat_dex_mod_incr)
THING_BODY_SET_INT(thing_stat_dex_mod_set, stat_dex_mod_set)

THING_BODY_SET_INT(thing_stat_str_incr, stat_str_incr)
THING_BODY_SET_INT(thing_stat_str_decr, stat_str_decr)
THING_BODY_SET_INT(thing_stat_str_set, stat_str_set)
THING_BODY_SET_INT(thing_stat_str_mod_decr, stat_str_mod_decr)
THING_BODY_SET_INT(thing_stat_str_mod_incr, stat_str_mod_incr)
THING_BODY_SET_INT(thing_stat_str_mod_set, stat_str_mod_set)

THING_BODY_SET_INT(thing_stat_luck_incr, stat_luck_incr)
THING_BODY_SET_INT(thing_stat_luck_decr, stat_luck_decr)
THING_BODY_SET_INT(thing_stat_luck_set, stat_luck_set)
THING_BODY_SET_INT(thing_stat_luck_mod_decr, stat_luck_mod_decr)
THING_BODY_SET_INT(thing_stat_luck_mod_incr, stat_luck_mod_incr)
THING_BODY_SET_INT(thing_stat_luck_mod_set, stat_luck_mod_set)

THING_BODY_SET_INT(thing_move_speed_mod_decr, move_speed_mod_decr)
THING_BODY_SET_INT(thing_move_speed_mod_incr, move_speed_mod_incr)
THING_BODY_SET_INT(thing_move_speed_mod_set, move_speed_mod_set)

THING_BODY_SET_INT(thing_shove_strength_mod_decr, shove_strength_mod_decr)
THING_BODY_SET_INT(thing_shove_strength_mod_incr, shove_strength_mod_incr)
THING_BODY_SET_INT(thing_shove_strength_mod_set, shove_strength_mod_set)

THING_BODY_SET_INT(thing_jump_distance_mod_decr, jump_distance_mod_decr)
THING_BODY_SET_INT(thing_jump_distance_mod_incr, jump_distance_mod_incr)
THING_BODY_SET_INT(thing_jump_distance_mod_set, jump_distance_mod_set)

THING_BODY_SET_INT(thing_health_max_decr, health_max_decr)
THING_BODY_SET_INT(thing_health_max_incr, health_max_incr)
THING_BODY_SET_INT(thing_health_set_max, health_max_set)

THING_BODY_SET_INT(thing_noise_incr, noise_incr)
THING_BODY_SET_INT(thing_noise_decr, noise_decr)
THING_BODY_SET_INT(thing_noise_set, noise_set)

THING_BODY_SET_THING(thing_skill_activate, skill_activate)
THING_BODY_SET_THING(thing_skill_deactivate, skill_deactivate)
