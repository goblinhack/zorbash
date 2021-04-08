//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PY_TP_H_
#define _MY_PY_TP_H_
#include <Python.h>

PyObject *tp_update_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_load_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_spawn_next_to_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_spawn_next_to_or_on_monst_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_spawn_radius_range_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_spawn_fire(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_spawn_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_spawn_at_if_possible(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_kill_if(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *tp_place(PyObject *obj, PyObject *args, PyObject *keywds);

#define TP_SET_PROTO(__field__)                                                     \
PyObject *tp_set_ ## __field__ (PyObject *obj, PyObject *args, PyObject *keywds);

#define TP_SET_DECL(__field__)                                                      \
    {"tp_set_" #__field__,                                                      \
        (PyCFunction)tp_set_ ## __field__,                                      \
        METH_VARARGS | METH_KEYWORDS,                                           \
        "set a " #__field__ " in a thing template"},                            \

TP_SET_PROTO(unused_rrr98)
TP_SET_PROTO(ai_obstacle)
TP_SET_PROTO(ai_scent_distance)
TP_SET_PROTO(attack_eater)
TP_SET_PROTO(attack_lunge)
TP_SET_PROTO(attack_meat)
TP_SET_PROTO(attack_shove)
TP_SET_PROTO(attack_shove_chance_d1000)
TP_SET_PROTO(is_attackable_by_monst)
TP_SET_PROTO(is_attackable_by_player)
TP_SET_PROTO(avoids_acid)
TP_SET_PROTO(avoids_fire)
TP_SET_PROTO(avoids_poison)
TP_SET_PROTO(avoids_water)
TP_SET_PROTO(bag_height)
TP_SET_PROTO(bag_item_height)
TP_SET_PROTO(bag_item_width)
TP_SET_PROTO(bag_width)
TP_SET_PROTO(bl1_tile)
TP_SET_PROTO(bl2_tile)
TP_SET_PROTO(blit_bot_off)
TP_SET_PROTO(blit_left_off)
TP_SET_PROTO(blit_right_off)
TP_SET_PROTO(blit_top_off)
TP_SET_PROTO(bot1_tile)
TP_SET_PROTO(bot2_tile)
TP_SET_PROTO(bot3_tile)
TP_SET_PROTO(br1_tile)
TP_SET_PROTO(br2_tile)
TP_SET_PROTO(collision_attack)
TP_SET_PROTO(collision_attack_radius)
TP_SET_PROTO(collision_box)
TP_SET_PROTO(collision_check)
TP_SET_PROTO(collision_circle)
TP_SET_PROTO(collision_hit_priority)
TP_SET_PROTO(collision_radius)
TP_SET_PROTO(damage_doubled_from_acid)
TP_SET_PROTO(damage_doubled_from_fire)
TP_SET_PROTO(damage_doubled_from_poison)
TP_SET_PROTO(damage_doubled_from_water)
TP_SET_PROTO(damage_melee_dice)
TP_SET_PROTO(damage_bite_dice)
TP_SET_PROTO(gfx_an_animation_only)
TP_SET_PROTO(gfx_anim_attack)
TP_SET_PROTO(gfx_animated)
TP_SET_PROTO(gfx_animated_can_hflip)
TP_SET_PROTO(gfx_animated_can_vflip)
TP_SET_PROTO(gfx_animated_no_dir)
TP_SET_PROTO(gfx_attack_anim)
TP_SET_PROTO(gfx_bounce_always)
TP_SET_PROTO(gfx_bounce_on_move)
TP_SET_PROTO(gfx_dead_anim)
TP_SET_PROTO(gfx_health_bar_shown)
TP_SET_PROTO(gfx_health_bar_shown_only_when_injured)
TP_SET_PROTO(gfx_is_rrr99)
TP_SET_PROTO(gfx_glows)
TP_SET_PROTO(gfx_on_fire_anim)
TP_SET_PROTO(gfx_oversized_but_sitting_on_the_ground)
TP_SET_PROTO(gfx_show_outlined)
TP_SET_PROTO(gfx_shown_in_bg)
TP_SET_PROTO(gfx_small_shadow_caster)
TP_SET_PROTO(gfx_weapon_carry_anim)
TP_SET_PROTO(gold_value_dice)
TP_SET_PROTO(health_hunger_pct)
TP_SET_PROTO(health_initial_dice)
TP_SET_PROTO(health_starving_pct)
TP_SET_PROTO(hunger_clock_freq_ms)
TP_SET_PROTO(is_able_to_change_levels)
TP_SET_PROTO(is_able_to_fall)
TP_SET_PROTO(is_acid)
TP_SET_PROTO(is_acid_lover)
TP_SET_PROTO(is_active)
TP_SET_PROTO(is_armor)
TP_SET_PROTO(is_auto_collect_item)
TP_SET_PROTO(is_bag)
TP_SET_PROTO(is_bleeder)
TP_SET_PROTO(is_blood)
TP_SET_PROTO(is_blood_splatter)
TP_SET_PROTO(is_bridge)
TP_SET_PROTO(is_chasm)
TP_SET_PROTO(is_collect_as_keys)
TP_SET_PROTO(is_collectable)
TP_SET_PROTO(is_combustible)
TP_SET_PROTO(is_corridor)
TP_SET_PROTO(is_critical_to_level)
TP_SET_PROTO(is_cursor)
TP_SET_PROTO(is_cursor_can_hover_over)
TP_SET_PROTO(is_cursor_can_hover_over_but_needs_double_click)
TP_SET_PROTO(is_cursor_path)
TP_SET_PROTO(is_dead_on_shove)
TP_SET_PROTO(is_deep_water)
TP_SET_PROTO(is_dirt)
TP_SET_PROTO(is_door)
TP_SET_PROTO(is_droppable)
TP_SET_PROTO(is_ascend_dungeon)
TP_SET_PROTO(is_ethereal)
TP_SET_PROTO(is_descend_dungeon)
TP_SET_PROTO(is_explosion)
TP_SET_PROTO(is_extreme_hazard)
TP_SET_PROTO(is_fire)
TP_SET_PROTO(is_flammable)
TP_SET_PROTO(is_floating)
TP_SET_PROTO(is_floor)
TP_SET_PROTO(is_floor_deco)
TP_SET_PROTO(is_food)
TP_SET_PROTO(is_food_eater)
TP_SET_PROTO(is_minion_generator)
TP_SET_PROTO(is_gold)
TP_SET_PROTO(is_hazard)
TP_SET_PROTO(is_healing)
TP_SET_PROTO(is_hidden)
TP_SET_PROTO(is_hunger_insatiable)
TP_SET_PROTO(is_intelligent)
TP_SET_PROTO(is_interesting)
TP_SET_PROTO(is_item)
TP_SET_PROTO(is_item_collected_as_gold)
TP_SET_PROTO(is_item_eater)
TP_SET_PROTO(blast_max_radius)
TP_SET_PROTO(blast_min_radius)
TP_SET_PROTO(is_item_not_stackable)
TP_SET_PROTO(is_jelly)
TP_SET_PROTO(is_jelly_baby)
TP_SET_PROTO(is_jelly_baby_eater)
TP_SET_PROTO(is_jelly_eater)
TP_SET_PROTO(is_jelly_parent)
TP_SET_PROTO(is_jumper)
TP_SET_PROTO(is_jumper_chance_d1000)
TP_SET_PROTO(is_jumper_distance)
TP_SET_PROTO(is_jumper_on_low_hp_chance_d1000)
TP_SET_PROTO(is_key)
TP_SET_PROTO(is_killed_on_hit_or_miss)
TP_SET_PROTO(is_killed_on_hitting)
TP_SET_PROTO(is_lava)
TP_SET_PROTO(is_light_blocker)
TP_SET_PROTO(light_strength)
TP_SET_PROTO(is_loggable_for_important_stuff)
TP_SET_PROTO(is_loggable_for_unimportant_stuff)
TP_SET_PROTO(is_magical)
TP_SET_PROTO(is_meat)
TP_SET_PROTO(is_meat_eater)
TP_SET_PROTO(is_monst)
TP_SET_PROTO(is_moveable)
TP_SET_PROTO(is_movement_blocking_hard)
TP_SET_PROTO(is_movement_blocking_soft)
TP_SET_PROTO(is_msg)
TP_SET_PROTO(is_no_tile)
TP_SET_PROTO(is_plant)
TP_SET_PROTO(is_player)
TP_SET_PROTO(is_poison)
TP_SET_PROTO(is_poison_immune)
TP_SET_PROTO(is_potion)
TP_SET_PROTO(is_potion_eater)
TP_SET_PROTO(is_projectile)
TP_SET_PROTO(is_removeable_if_out_of_slots)
TP_SET_PROTO(is_resurrectable)
TP_SET_PROTO(is_ripple)
TP_SET_PROTO(is_rock)
TP_SET_PROTO(is_rrr1)
TP_SET_PROTO(is_rrr10)
TP_SET_PROTO(is_rrr11)
TP_SET_PROTO(is_rrr12)
TP_SET_PROTO(is_rrr13)
TP_SET_PROTO(is_torch)
TP_SET_PROTO(range_max)
TP_SET_PROTO(is_laser_target_select_automatically_when_chosen)
TP_SET_PROTO(is_wand)
TP_SET_PROTO(charge_count)
TP_SET_PROTO(minion_leash_distance)
TP_SET_PROTO(is_rrr2)
TP_SET_PROTO(is_skill)
TP_SET_PROTO(is_sewer_wall)
TP_SET_PROTO(is_wall_dungeon)
TP_SET_PROTO(is_descend_sewer)
TP_SET_PROTO(is_burnable)
TP_SET_PROTO(is_shallow_water)
TP_SET_PROTO(minion_limit)
TP_SET_PROTO(is_living)
TP_SET_PROTO(attack_living)
TP_SET_PROTO(is_minion)
TP_SET_PROTO(is_rrr3)
TP_SET_PROTO(is_described_when_hovering_over)
TP_SET_PROTO(is_always_hit)
TP_SET_PROTO(is_fearless)
TP_SET_PROTO(is_able_to_see_through_doors)
TP_SET_PROTO(is_able_to_walk_through_walls)
TP_SET_PROTO(is_humanoid)
TP_SET_PROTO(is_rrr4)
TP_SET_PROTO(attack_humanoid)
TP_SET_PROTO(is_rrr5)
TP_SET_PROTO(is_rrr6)
TP_SET_PROTO(is_rrr7)
TP_SET_PROTO(is_rrr8)
TP_SET_PROTO(is_rrr9)
TP_SET_PROTO(is_sand)
TP_SET_PROTO(is_secret_corridor)
TP_SET_PROTO(is_secret_door)
TP_SET_PROTO(is_shovable)
TP_SET_PROTO(is_shown_on_leftbar)
TP_SET_PROTO(is_shown_uniquely_on_leftbar)
TP_SET_PROTO(is_sleeping)
TP_SET_PROTO(is_smoke)
TP_SET_PROTO(is_stamina_check)
TP_SET_PROTO(is_steal_item_chance_d1000)
TP_SET_PROTO(is_temporary_bag)
TP_SET_PROTO(is_the_grid)
TP_SET_PROTO(is_throwable)
TP_SET_PROTO(is_thrown_automatically_when_chosen)
TP_SET_PROTO(is_brazier)
TP_SET_PROTO(is_treasure)
TP_SET_PROTO(is_treasure_class_a)
TP_SET_PROTO(is_treasure_class_b)
TP_SET_PROTO(is_treasure_class_c)
TP_SET_PROTO(is_treasure_eater)
TP_SET_PROTO(is_undead)
TP_SET_PROTO(is_usable)
TP_SET_PROTO(is_used_automatically_when_selected)
TP_SET_PROTO(is_used_when_thrown)
TP_SET_PROTO(is_wall)
TP_SET_PROTO(is_ascend_sewer)
TP_SET_PROTO(is_gfx_water)
TP_SET_PROTO(is_water_lover)
TP_SET_PROTO(is_weapon)
TP_SET_PROTO(is_weapon_wielder)
TP_SET_PROTO(left1_tile)
TP_SET_PROTO(left2_tile)
TP_SET_PROTO(lifespan_dice)
TP_SET_PROTO(light_color)
TP_SET_PROTO(long_text_description)
TP_SET_PROTO(modifier_attack)
TP_SET_PROTO(modifier_constitution)
TP_SET_PROTO(modifier_defence)
TP_SET_PROTO(modifier_strength)
TP_SET_PROTO(move_speed_ms)
TP_SET_PROTO(name)
TP_SET_PROTO(normal_placement_rules)
TP_SET_PROTO(nutrition_dice)
TP_SET_PROTO(on_birth_do)
TP_SET_PROTO(on_death_do)
TP_SET_PROTO(on_open_do)
TP_SET_PROTO(on_death_drop_all_items)
TP_SET_PROTO(is_corpse_on_death)
TP_SET_PROTO(on_death_is_open)
TP_SET_PROTO(on_idle_dice)
TP_SET_PROTO(on_use_do)
TP_SET_PROTO(on_hit_do)
TP_SET_PROTO(on_miss_do)
TP_SET_PROTO(on_bite_do)
TP_SET_PROTO(on_born_do)
TP_SET_PROTO(on_move_do)
TP_SET_PROTO(rarity)
TP_SET_PROTO(resurrect_dice)
TP_SET_PROTO(right1_tile)
TP_SET_PROTO(right2_tile)
TP_SET_PROTO(monst_size)
TP_SET_PROTO(spawn_on_shoved)
TP_SET_PROTO(stamina)
TP_SET_PROTO(stats01)
TP_SET_PROTO(stats02)
TP_SET_PROTO(stats03)
TP_SET_PROTO(stats04)
TP_SET_PROTO(stats05)
TP_SET_PROTO(stats06)
TP_SET_PROTO(stats07)
TP_SET_PROTO(stats08)
TP_SET_PROTO(stats09)
TP_SET_PROTO(stats10)
TP_SET_PROTO(stats11)
TP_SET_PROTO(stats12)
TP_SET_PROTO(stats17)
TP_SET_PROTO(str1)
TP_SET_PROTO(str2)
TP_SET_PROTO(str3)
TP_SET_PROTO(str4)
TP_SET_PROTO(str5)
TP_SET_PROTO(str6)
TP_SET_PROTO(laser_name)
TP_SET_PROTO(text_a_or_an)
TP_SET_PROTO(text_description)
TP_SET_PROTO(text_unused)
TP_SET_PROTO(text_hits)
TP_SET_PROTO(text_name)
TP_SET_PROTO(text_title)
TP_SET_PROTO(throw_distance)
TP_SET_PROTO(tick_catches_up_on_attack)
TP_SET_PROTO(tick_rate_tenths)
TP_SET_PROTO(tile)
TP_SET_PROTO(tl1_tile)
TP_SET_PROTO(tl2_tile)
TP_SET_PROTO(top1_tile)
TP_SET_PROTO(top2_tile)
TP_SET_PROTO(tr1_tile)
TP_SET_PROTO(tr2_tile)
TP_SET_PROTO(weapon_carry_anim)
TP_SET_PROTO(weapon_damage)
TP_SET_PROTO(weapon_use_delay_hundredths)
TP_SET_PROTO(weapon_use_distance)
TP_SET_PROTO(z_depth)
TP_SET_PROTO(z_prio)
#endif
