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
    auto out = t->__api__(value);                                                                                    \
    return Py_BuildValue("i", (int) out);                                                                            \
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
THING_BODY_SET_INT(thing_enchant_count_decr, enchant_count_decr)
THING_BODY_SET_INT(thing_enchant_count_incr, enchant_count_incr)
THING_BODY_SET_INT(thing_enchant_max_current_decr, enchant_max_current_decr)
THING_BODY_SET_INT(thing_enchant_max_current_incr, enchant_max_current_incr)
THING_BODY_SET_INT(thing_enchant_max_current_set, enchant_max_current_set)
THING_BODY_SET_INT(thing_enchant_max_set, enchant_count_set)
THING_BODY_SET_INT(thing_gold_decr, gold_decr)
THING_BODY_SET_INT(thing_gold_incr, gold_incr)
THING_BODY_SET_INT(thing_gold_set, gold_set)
THING_BODY_SET_INT(thing_health_decr, health_decr)
THING_BODY_SET_INT(thing_health_incr, health_incr)
THING_BODY_SET_INT(thing_health_max_decr, health_max_decr)
THING_BODY_SET_INT(thing_health_max_incr, health_max_incr)
THING_BODY_SET_INT(thing_health_set, health_set)
THING_BODY_SET_INT(thing_health_set_max, health_max_set)
THING_BODY_SET_INT(thing_jump_distance_bonus_decr, jump_distance_bonus_decr)
THING_BODY_SET_INT(thing_jump_distance_bonus_incr, jump_distance_bonus_incr)
THING_BODY_SET_INT(thing_jump_distance_bonus_set, jump_distance_bonus_set)
THING_BODY_SET_INT(thing_magic_decr, magic_decr)
THING_BODY_SET_INT(thing_magic_incr, magic_incr)
THING_BODY_SET_INT(thing_magic_max_decr, magic_max_decr)
THING_BODY_SET_INT(thing_magic_max_incr, magic_max_incr)
THING_BODY_SET_INT(thing_magic_max_set, magic_max_set)
THING_BODY_SET_INT(thing_magic_set, magic_set)
THING_BODY_SET_INT(thing_move_speed_bonus_decr, move_speed_bonus_decr)
THING_BODY_SET_INT(thing_move_speed_bonus_incr, move_speed_bonus_incr)
THING_BODY_SET_INT(thing_move_speed_bonus_set, move_speed_bonus_set)
THING_BODY_SET_INT(thing_move_penalty_decr, move_penalty_decr)
THING_BODY_SET_INT(thing_move_penalty_incr, move_penalty_incr)
THING_BODY_SET_INT(thing_move_penalty_set, move_penalty_set)
THING_BODY_SET_INT(thing_necrotized_amount_decr, necrotized_amount_decr)
THING_BODY_SET_INT(thing_necrotized_amount_incr, necrotized_amount_incr)
THING_BODY_SET_INT(thing_necrotized_amount_set, necrotized_amount_set)
THING_BODY_SET_INT(thing_noise_decr, noise_decr)
THING_BODY_SET_INT(thing_noise_incr, noise_incr)
THING_BODY_SET_INT(thing_noise_set, noise_set)
THING_BODY_SET_INT(thing_paralysis_count_decr, paralysis_count_decr)
THING_BODY_SET_INT(thing_paralysis_count_incr, paralysis_count_incr)
THING_BODY_SET_INT(thing_paralysis_count_set, paralysis_count_set)
THING_BODY_SET_INT(thing_blinded_count_decr, blinded_count_decr)
THING_BODY_SET_INT(thing_blinded_count_incr, blinded_count_incr)
THING_BODY_SET_INT(thing_blinded_count_set, blinded_count_set)
THING_BODY_SET_INT(thing_poisoned_amount_decr, poisoned_amount_decr)
THING_BODY_SET_INT(thing_poisoned_amount_incr, poisoned_amount_incr)
THING_BODY_SET_INT(thing_poisoned_amount_set, poisoned_amount_set)
THING_BODY_SET_INT(thing_raging_set, raging_set)
THING_BODY_SET_INT(thing_score_decr, score_decr)
THING_BODY_SET_INT(thing_score_incr, score_incr)
THING_BODY_SET_INT(thing_score_set, score_set)
THING_BODY_SET_INT(thing_shove_bonus_decr, shove_bonus_decr)
THING_BODY_SET_INT(thing_shove_bonus_incr, shove_bonus_incr)
THING_BODY_SET_INT(thing_shove_bonus_set, shove_bonus_set)
THING_BODY_SET_INT(thing_stamina_decr, stamina_decr)
THING_BODY_SET_INT(thing_stamina_incr, stamina_incr)
THING_BODY_SET_INT(thing_stamina_max_decr, stamina_max_decr)
THING_BODY_SET_INT(thing_stamina_max_incr, stamina_max_incr)
THING_BODY_SET_INT(thing_stamina_max_set, stamina_max_set)
THING_BODY_SET_INT(thing_stamina_set, stamina_set)
THING_BODY_SET_INT(thing_stat_att_bonus_decr, stat_att_bonus_decr)
THING_BODY_SET_INT(thing_stat_att_bonus_incr, stat_att_bonus_incr)
THING_BODY_SET_INT(thing_stat_att_bonus_set, stat_att_bonus_set)
THING_BODY_SET_INT(thing_stat_att_decr, stat_att_decr)
THING_BODY_SET_INT(thing_stat_att_incr, stat_att_incr)
THING_BODY_SET_INT(thing_stat_att_set, stat_att_set)
THING_BODY_SET_INT(thing_stat_con_bonus_decr, stat_con_bonus_decr)
THING_BODY_SET_INT(thing_stat_con_bonus_incr, stat_con_bonus_incr)
THING_BODY_SET_INT(thing_stat_con_bonus_set, stat_con_bonus_set)
THING_BODY_SET_INT(thing_stat_con_decr, stat_con_decr)
THING_BODY_SET_INT(thing_stat_con_incr, stat_con_incr)
THING_BODY_SET_INT(thing_stat_con_set, stat_con_set)
THING_BODY_SET_INT(thing_stat_def_bonus_decr, stat_def_bonus_decr)
THING_BODY_SET_INT(thing_stat_def_bonus_incr, stat_def_bonus_incr)
THING_BODY_SET_INT(thing_stat_def_bonus_set, stat_def_bonus_set)
THING_BODY_SET_INT(thing_stat_def_decr, stat_def_decr)
THING_BODY_SET_INT(thing_stat_def_incr, stat_def_incr)
THING_BODY_SET_INT(thing_stat_def_set, stat_def_set)
THING_BODY_SET_INT(thing_stat_dex_bonus_decr, stat_dex_bonus_decr)
THING_BODY_SET_INT(thing_stat_dex_bonus_incr, stat_dex_bonus_incr)
THING_BODY_SET_INT(thing_stat_dex_bonus_set, stat_dex_bonus_set)
THING_BODY_SET_INT(thing_stat_dex_decr, stat_dex_decr)
THING_BODY_SET_INT(thing_stat_dex_incr, stat_dex_incr)
THING_BODY_SET_INT(thing_stat_dex_set, stat_dex_set)
THING_BODY_SET_INT(thing_stat_int_bonus_decr, stat_int_bonus_decr)
THING_BODY_SET_INT(thing_stat_int_bonus_incr, stat_int_bonus_incr)
THING_BODY_SET_INT(thing_stat_int_bonus_set, stat_int_bonus_set)
THING_BODY_SET_INT(thing_stat_int_decr, stat_int_decr)
THING_BODY_SET_INT(thing_stat_int_incr, stat_int_incr)
THING_BODY_SET_INT(thing_stat_int_set, stat_int_set)
THING_BODY_SET_INT(thing_stat_luck_bonus_decr, stat_luck_bonus_decr)
THING_BODY_SET_INT(thing_stat_luck_bonus_incr, stat_luck_bonus_incr)
THING_BODY_SET_INT(thing_stat_luck_bonus_set, stat_luck_bonus_set)
THING_BODY_SET_INT(thing_stat_luck_decr, stat_luck_decr)
THING_BODY_SET_INT(thing_stat_luck_incr, stat_luck_incr)
THING_BODY_SET_INT(thing_stat_luck_set, stat_luck_set)
THING_BODY_SET_INT(thing_stat_psi_bonus_decr, stat_psi_bonus_decr)
THING_BODY_SET_INT(thing_stat_psi_bonus_incr, stat_psi_bonus_incr)
THING_BODY_SET_INT(thing_stat_psi_bonus_set, stat_psi_bonus_set)
THING_BODY_SET_INT(thing_stat_psi_decr, stat_psi_decr)
THING_BODY_SET_INT(thing_stat_psi_incr, stat_psi_incr)
THING_BODY_SET_INT(thing_stat_psi_set, stat_psi_set)
THING_BODY_SET_INT(thing_stat_str_bonus_decr, stat_str_bonus_decr)
THING_BODY_SET_INT(thing_stat_str_bonus_incr, stat_str_bonus_incr)
THING_BODY_SET_INT(thing_stat_str_bonus_set, stat_str_bonus_set)
THING_BODY_SET_INT(thing_stat_str_decr, stat_str_decr)
THING_BODY_SET_INT(thing_stat_str_incr, stat_str_incr)
THING_BODY_SET_INT(thing_stat_str_set, stat_str_set)
THING_BODY_SET_INT(thing_stat_thv_bonus_decr, stat_thv_bonus_decr)
THING_BODY_SET_INT(thing_stat_thv_bonus_incr, stat_thv_bonus_incr)
THING_BODY_SET_INT(thing_stat_thv_bonus_set, stat_thv_bonus_set)
THING_BODY_SET_INT(thing_stat_thv_decr, stat_thv_decr)
THING_BODY_SET_INT(thing_stat_thv_incr, stat_thv_incr)
THING_BODY_SET_INT(thing_stat_thv_set, stat_thv_set)
THING_BODY_SET_INT(thing_stuck_count_decr, stuck_count_decr)
THING_BODY_SET_INT(thing_stuck_count_incr, stuck_count_incr)
THING_BODY_SET_INT(thing_stuck_count_set, stuck_count_set)
THING_BODY_SET_THING(thing_skill_activate, skill_activate)
THING_BODY_SET_THING(thing_skill_deactivate, skill_deactivate)
THING_BODY_SET_THING(thing_spell_activate, spell_activate)
THING_BODY_SET_THING(thing_spell_deactivate, spell_deactivate)
