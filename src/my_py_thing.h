//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PY_THING_H_
#define _MY_PY_THING_H_
#include <Python.h>

PyObject *thing_set_health(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_health(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_health(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_health(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_health_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_health_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_health_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_health_max(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_stamina(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_stamina(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_stamina(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_stamina(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_stamina_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_stamina_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_stamina_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_stamina_max(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_enchant(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_enchant(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_enchant(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_enchant(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_enchant_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_enchant_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_enchant_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_enchant_max(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_set_current_damage(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_incr_current_damage(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_decr_current_damage(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_current_damage(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_incr_charge_count(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_get_name(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_skill_activate(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_skill_deactivate(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_msg(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_get_immediate_spawned_owner_id(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_immediate_minion_owner_id(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_immediate_owner_id(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_is_able_to_change_levels(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_able_to_fall(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_able_to_see_through_doors(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_able_to_walk_through_walls(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_acid(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_acid_lover(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_active(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_alive_monst(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_always_hit(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_ascend_dungeon(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_ascend_sewer(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_auto_collect_item(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_bag(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_bleeder(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_blood(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_blood_splatter(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_bloodied(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_brazier(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr99(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_carrier_of_treasure_class_a(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_carrier_of_treasure_class_b(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_carrier_of_treasure_class_c(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_carrying_item(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_carrying_treasure(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_chasm(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_collect_as_keys(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_collectable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_combustible(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_corpse(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_corpse_on_death(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_corridor(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_critical_to_level(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_cursor(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_cursor_can_hover_over(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_cursor_can_hover_over_but_needs_double_click(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_cursor_path(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dead_or_dying_on_shove(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dead_or_dying(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_deep_water(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_descend_dungeon(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_descend_sewer(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_described_when_hovering_over(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_bl(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_br(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_down(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_left(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_none(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_right(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_tl(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_tr(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dir_up(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dirt(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_door(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_droppable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_ethereal(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_explosion(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_extreme_hazard(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_fearless(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_fire(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_very_combustible(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_floating(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_floor(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_floor_deco(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_food(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_food_eater(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_gfx_water(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_gold(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_hazard(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_humanoid(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_hunger_insatiable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_intelligent(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_interesting(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_item(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_item_carrier(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_item_collected_as_gold(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_item_eater(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_item_not_stackable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jelly(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jelly_baby(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jelly_baby_eater(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jelly_eater(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jelly_parent(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jumper(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jumper_chance_d1000(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jumper_distance(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_jumper_on_low_hp_chance_d1000(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_key(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_killed_on_hit_or_miss(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_killed_on_hitting(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_target_select_automatically_when_chosen(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_lava(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_light_blocker(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_living(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_loggable_for_important_stuff(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_loggable_for_unimportant_stuff(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_meat(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_meat_eater(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_minion(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_minion_generator(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_monst(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_moveable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_movement_blocking_hard(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_movement_blocking_soft(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_msg(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_no_tile(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_on_fire(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_player(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_poison(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_loves_poison(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_potion(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_potion_eater(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_projectile(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_removeable_if_out_of_slots(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_resurrectable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_ripple(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rock(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr1(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr2(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr3(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr4(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr5(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr6(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr7(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr8(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr9(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr10(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr11(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr12(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr13(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr14(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr15(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr16(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr17(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr18(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr19(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr20(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr21(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr22(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr23(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr24(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr25(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr26(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr27(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr28(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr29(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr30(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr31(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr32(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr33(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr34(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr35(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr36(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr37(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr38(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr39(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr40(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr41(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr42(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr43(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr44(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr45(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr46(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr47(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr48(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr49(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr50(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr51(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr52(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr53(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr54(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr55(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr56(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr57(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr58(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr59(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr60(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr61(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr62(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr63(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr64(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr65(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr66(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr67(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr68(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr69(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr70(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr71(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr72(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr73(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr74(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr75(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_rrr76(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_sticky(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_sword(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_skillstone(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_enchant_level(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_enchant_max(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_enchantstone(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_enchantable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_indestructible(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_bones(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_soft_body(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_foilage(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_spiderweb(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_gfx_very_small_shadow_caster(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_dry_fungus(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_bridge(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_barrel(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_burnable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_wand_eater(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_loves_fire(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_projectile(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_gfx_flickers(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_laser(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_fire_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_ethereal_minion_generator(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_secret_door(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_sewer_wall(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_shallow_water(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_water(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_shovable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_shown_on_leftbar(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_shown_uniquely_on_leftbar(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_skill(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_smoke(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_spawner(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_stamina_check(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_steal_item_chance_d1000(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_temporary_bag(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_throwable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_thrown_automatically_when_chosen(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_torch(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_treasure(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_treasure_class_a(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_treasure_class_b(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_treasure_class_c(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_treasure_eater(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_undead(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_usable(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_used_automatically_when_selected(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_used_when_thrown(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_visible(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_wall(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_wall_dungeon(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_wand(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_water_lover(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_weapon(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_is_weapon_wielder(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_get_coords(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_killed(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_killed_by(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_hit(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_fire_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_possible_to_attack(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *thing_get_damage_crush(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_damage_bite(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *thing_get_damage_melee(PyObject *obj, PyObject *args, PyObject *keywds);

#endif
