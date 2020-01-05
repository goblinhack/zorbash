//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#ifndef _MY_PY_TP_H_
#define _MY_PY_TP_H_
#include <Python.h>

PyObject *tp_load_(PyObject *obj, PyObject *args, PyObject *keywds);

#define TP_SET_PROTO(__field__)                                                     \
PyObject *tp_set_ ## __field__ (PyObject *obj, PyObject *args, PyObject *keywds);

#define TP_SET_DECL(__field__)                                                      \
    {"tp_set_" #__field__,                                                      \
        (PyCFunction)tp_set_ ## __field__,                                      \
        METH_VARARGS | METH_KEYWORDS,                                           \
        "set a " #__field__ " in a thing template"},                            \

PyObject *tp_update_(PyObject *obj, PyObject *args, PyObject *keywds);

TP_SET_PROTO(ai_delay_after_moving_ms)
TP_SET_PROTO(ai_scent_distance)
TP_SET_PROTO(blit_bot_off)
TP_SET_PROTO(blit_left_off)
TP_SET_PROTO(blit_right_off)
TP_SET_PROTO(blit_top_off)
TP_SET_PROTO(collision_attack)
TP_SET_PROTO(collision_box)
TP_SET_PROTO(collision_check)
TP_SET_PROTO(collision_circle)
TP_SET_PROTO(collision_hit_priority)
TP_SET_PROTO(collision_radius)
TP_SET_PROTO(gfx_animated)
TP_SET_PROTO(gfx_animated_can_vflip)
TP_SET_PROTO(gfx_animated_no_dir)
TP_SET_PROTO(gfx_bounce_on_move)
TP_SET_PROTO(gfx_can_hflip)
TP_SET_PROTO(gfx_dead_anim)
TP_SET_PROTO(gfx_is_an_animation_only)
TP_SET_PROTO(gfx_is_floor_deco)
TP_SET_PROTO(gfx_is_wall_deco)
TP_SET_PROTO(gfx_is_weapon_carry_anim)
TP_SET_PROTO(gfx_is_weapon_use_anim)
TP_SET_PROTO(gfx_large_shadow_caster)
TP_SET_PROTO(gfx_oversized_but_sitting_on_the_ground)
TP_SET_PROTO(gfx_show_hiddend)
TP_SET_PROTO(gfx_small_shadow_caster)
TP_SET_PROTO(hunger_clock_freq_ms)
TP_SET_PROTO(is_active)
TP_SET_PROTO(is_armor)
TP_SET_PROTO(is_attackable)
TP_SET_PROTO(is_bleeder)
TP_SET_PROTO(is_blood)
TP_SET_PROTO(is_bridge)
TP_SET_PROTO(is_chasm_smoke)
TP_SET_PROTO(is_combustable)
TP_SET_PROTO(is_corpse_on_death)
TP_SET_PROTO(is_corridor)
TP_SET_PROTO(is_cursor)
TP_SET_PROTO(is_cursor_hover)
TP_SET_PROTO(is_deep_water)
TP_SET_PROTO(is_dirt)
TP_SET_PROTO(is_door)
TP_SET_PROTO(is_entrance)
TP_SET_PROTO(is_exit)
TP_SET_PROTO(is_explosion)
TP_SET_PROTO(is_floor)
TP_SET_PROTO(is_food)
TP_SET_PROTO(is_healing)
TP_SET_PROTO(is_hidden)
TP_SET_PROTO(is_hunger_insatiable)
TP_SET_PROTO(is_interesting)
TP_SET_PROTO(is_key)
TP_SET_PROTO(is_lava)
TP_SET_PROTO(is_light_strength)
TP_SET_PROTO(is_loggable)
TP_SET_PROTO(is_made_of_meat)
TP_SET_PROTO(is_magical)
TP_SET_PROTO(is_meat_eater)
TP_SET_PROTO(is_monst)
TP_SET_PROTO(is_movable)
TP_SET_PROTO(is_movement_blocking)
TP_SET_PROTO(is_nutrition_hd)
TP_SET_PROTO(is_obstacle)
TP_SET_PROTO(is_plant)
TP_SET_PROTO(is_player)
TP_SET_PROTO(is_projectile)
TP_SET_PROTO(is_ripple)
TP_SET_PROTO(is_rock)
TP_SET_PROTO(is_rrr1)
TP_SET_PROTO(is_rrr10)
TP_SET_PROTO(is_rrr11)
TP_SET_PROTO(is_rrr12)
TP_SET_PROTO(is_rrr13)
TP_SET_PROTO(is_rrr14)
TP_SET_PROTO(is_rrr15)
TP_SET_PROTO(is_rrr16)
TP_SET_PROTO(is_rrr17)
TP_SET_PROTO(is_rrr18)
TP_SET_PROTO(is_rrr19)
TP_SET_PROTO(is_rrr2)
TP_SET_PROTO(is_rrr20)
TP_SET_PROTO(is_rrr21)
TP_SET_PROTO(is_rrr22)
TP_SET_PROTO(is_rrr23)
TP_SET_PROTO(is_rrr24)
TP_SET_PROTO(is_rrr25)
TP_SET_PROTO(is_rrr26)
TP_SET_PROTO(is_rrr28)
TP_SET_PROTO(is_rrr29)
TP_SET_PROTO(is_rrr3)
TP_SET_PROTO(is_rrr30)
TP_SET_PROTO(is_rrr31)
TP_SET_PROTO(is_rrr32)
TP_SET_PROTO(is_rrr33)
TP_SET_PROTO(is_rrr34)
TP_SET_PROTO(is_rrr35)
TP_SET_PROTO(is_rrr36)
TP_SET_PROTO(is_rrr37)
TP_SET_PROTO(is_rrr38)
TP_SET_PROTO(is_rrr39)
TP_SET_PROTO(is_rrr4)
TP_SET_PROTO(is_rrr41)
TP_SET_PROTO(is_rrr42)
TP_SET_PROTO(is_rrr43)
TP_SET_PROTO(is_rrr44)
TP_SET_PROTO(is_rrr5)
TP_SET_PROTO(is_rrr6)
TP_SET_PROTO(is_rrr7)
TP_SET_PROTO(is_rrr8)
TP_SET_PROTO(is_rrr9)
TP_SET_PROTO(is_sand)
TP_SET_PROTO(is_secret_corridor)
TP_SET_PROTO(is_secret_door)
TP_SET_PROTO(is_sleeping)
TP_SET_PROTO(is_undead)
TP_SET_PROTO(is_wall)
TP_SET_PROTO(is_water)
TP_SET_PROTO(is_water_dweller)
TP_SET_PROTO(is_water_hater)
TP_SET_PROTO(is_weapon)
TP_SET_PROTO(name)
TP_SET_PROTO(stats_attack)
TP_SET_PROTO(stats_attack_bite_hd)
TP_SET_PROTO(stats_defence)
TP_SET_PROTO(stats_health_hunger_pct)
TP_SET_PROTO(stats_health_initial)
TP_SET_PROTO(stats_health_starving_pct)
TP_SET_PROTO(stats_move_speed_ms)
TP_SET_PROTO(str_light_color)
TP_SET_PROTO(str_zzz1)
TP_SET_PROTO(str_zzz10)
TP_SET_PROTO(str_zzz11)
TP_SET_PROTO(str_zzz12)
TP_SET_PROTO(str_zzz13)
TP_SET_PROTO(str_zzz14)
TP_SET_PROTO(str_zzz15)
TP_SET_PROTO(str_zzz16)
TP_SET_PROTO(str_zzz17)
TP_SET_PROTO(str_zzz2)
TP_SET_PROTO(str_zzz3)
TP_SET_PROTO(str_zzz4)
TP_SET_PROTO(str_zzz5)
TP_SET_PROTO(str_zzz6)
TP_SET_PROTO(str_zzz7)
TP_SET_PROTO(str_zzz8)
TP_SET_PROTO(str_zzz9)
TP_SET_PROTO(tile)
TP_SET_PROTO(tile_bl)
TP_SET_PROTO(tile_bot)
TP_SET_PROTO(tile_br)
TP_SET_PROTO(tile_left)
TP_SET_PROTO(tile_right)
TP_SET_PROTO(tile_tl)
TP_SET_PROTO(tile_top)
TP_SET_PROTO(tile_tr)
TP_SET_PROTO(weapon_carry_anim)
TP_SET_PROTO(weapon_damage)
TP_SET_PROTO(weapon_use_anim)
TP_SET_PROTO(weapon_use_delay_hundredths)
TP_SET_PROTO(weapon_use_distance)
TP_SET_PROTO(z_depth)
#endif
