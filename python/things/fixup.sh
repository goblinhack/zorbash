#!/bin/bash
#
# Adds default flags to all the templates and sorts them so it is easier to
# see what is missing or needs added.
#
# Use "do" as the first arg if the output looks sane.
#

PRE=$(mktemp) || exit 1
PAYLOAD=$(mktemp) || exit 1
POST=$(mktemp) || exit 1
OUT=$(mktemp) || exit 1

for IN in \
  skeleton.py \
  bat_lesser.py \
  chest1.py \
  chest1.py \
  cleaner.py \
  cleaner.py \
  cleaner.py \
  enchantstone.py \
  food_apple1.py \
  food_apple2.py \
  food_apple_cider.py \
  food_applepie.py \
  food_aubergine.py \
  food_bacon.py \
  food_baguette.py \
  food_beer1.py \
  food_beer2.py \
  food_cheesecake.py \
  food_cherry.py \
  food_chicken.py \
  food_chocolate_bar.py \
  food_cookie.py \
  food_custardpie.py \
  food_durian.py \
  food_eggs.py \
  food_fish.py \
  food_flagon_ale.py \
  food_frog.py \
  food_gherkin.py \
  food_ginger.py \
  food_greenpepper.py \
  food_honey.py \
  food_hotsauce.py \
  food_lemonpie.py \
  food_melon1.py \
  food_melon2.py \
  food_onion.py \
  food_orange_slices.py \
  food_peach.py \
  food_pickled_eggs.py \
  food_pickledeyes.py \
  food_pineapple.py \
  food_potato.py \
  food_pottedmeat.py \
  food_pretzel.py \
  food_redpepper.py \
  food_roastchicken.py \
  food_salami.py \
  food_salmon.py \
  food_sardines.py \
  food_sirloin.py \
  food_somekindofmeat.py \
  food_steak.py \
  food_strawberry.py \
  food_sushi1.py \
  food_sushi2.py \
  food_tomato.py \
  food_turnip.py \
  food_watermelon.py \
  food_wine.py \
  gem_amber.py \
  gem_amethyst.py \
  gem_aventurine.py \
  gem_diamond.py \
  gem_emerald.py \
  gem_ruby.py \
  gem_sapphire.py \
  gem_topaz.py \
  ghost_minion.py \
  ghost.py \
  goblin.py \
  goblin.py \
  goblin.py \
  gold1.py \
  gold2.py \
  gold3.py \
  gold4.py \
  gold5.py \
  gold6.py \
  jelly_baby.py \
  jelly_parent.py \
  key.py \
  mummy.py \
  player.py \
  potion_health.py \
  rat_giant.py \
  reaper.py \
  skeleton_fire.py \
  skeleton_giant.py \
  skeleton_minion_fire.py \
  skeleton_minion.py \
  skeleton.py \
  skeleton.py \
  skeleton.py \
  skeleton.py \
  skeleton.py \
  skeleton.py \
  skillstone.py \
  spider_giant.py \
  tentacleye.py \
  thunderstone.py \
  torch.py \
  wand_descent.py \
  wand_energy.py \
  wand_fire.py \
  wand_lightning.py
do
    echo $IN

    sed '1,/mytp = tp.Tp(/!d' $IN > $PRE
    sed '/mytp = tp.Tp(/,/mytp.set_z_prio(/!d' $IN | tail -n +2 - | sort > $PAYLOAD
    sed '/mytp.set_z_prio(/,$!d' $IN | tail -n +2 - > $POST

    for arg in \
      set_ai_enemy_memory \
      set_ai_obstacle \
      set_attack_eater \
      set_attack_humanoid \
      set_attack_living \
      set_attack_lunge \
      set_attack_meat \
      set_attack_shove \
      set_collision_attack \
      set_collision_box \
      set_collision_check \
      set_collision_circle \
      set_collision_hit_priority \
      set_damage_doubled_from_acid \
      set_damage_doubled_from_fire \
      set_damage_doubled_from_poison \
      set_damage_doubled_from_water \
      set_enchant_level \
      set_enchant_max \
      set_gfx_an_animation_only \
      set_gfx_animated \
      set_gfx_animated_can_hflip \
      set_gfx_animated_can_vflip \
      set_gfx_animated_no_dir \
      set_gfx_attack_anim \
      set_gfx_bounce_always \
      set_gfx_bounce_on_move \
      set_gfx_dead_anim \
      set_gfx_flickers \
      set_gfx_glows \
      set_gfx_health_bar_shown \
      set_gfx_health_bar_shown_only_when_injured \
      set_gfx_long_shadow_caster \
      set_gfx_on_fire_anim \
      set_gfx_oversized_but_sitting_on_the_ground \
      set_gfx_shown_in_bg \
      set_gfx_show_outlined \
      set_gfx_solid_shadow \
      set_gfx_very_short_shadow_caster \
      set_gfx_water \
      set_gfx_weapon_carry_anim \
      set_hates_acid \
      set_hates_fire \
      set_hates_poison \
      set_hates_water \
      set_is_able_to_change_levels \
      set_is_able_to_fall \
      set_is_able_to_fire_at \
      set_is_able_to_see_through_doors \
      set_is_able_to_walk_through_walls \
      set_is_acid \
      set_is_acid_lover \
      set_is_ai_wanderer \
      set_is_alive_on_end_of_anim \
      set_is_always_hit \
      set_is_ascend_dungeon \
      set_is_ascend_sewer \
      set_is_attackable_by_monst \
      set_is_attackable_by_player \
      set_is_auto_collect_item \
      set_is_bag \
      set_is_bag_item \
      set_is_bag_item_container \
      set_is_bag_item_not_stackable \
      set_is_barrel \
      set_is_bleeder \
      set_is_blood \
      set_is_blood_splatter \
      set_is_bones \
      set_is_brazier \
      set_is_bridge \
      set_is_burnable \
      set_is_carrier_of_treasure_class_a \
      set_is_carrier_of_treasure_class_b \
      set_is_carrier_of_treasure_class_c \
      set_is_chasm \
      set_is_collectable \
      set_is_collect_as_keys \
      set_is_collected_as_gold \
      set_is_combustible \
      set_is_corpse_on_death \
      set_is_corridor \
      set_is_critical_to_level \
      set_is_cursor \
      set_is_cursor_can_hover_over \
      set_is_cursor_can_hover_over_but_needs_double_click \
      set_is_cursor_path \
      set_is_dead_on_end_of_anim \
      set_is_dead_on_shove \
      set_is_debug_path \
      set_is_debug_type \
      set_is_deep_water \
      set_is_descend_dungeon \
      set_is_descend_sewer \
      set_is_described_when_hovering_over \
      set_is_dirt \
      set_is_door \
      set_is_droppable \
      set_is_dry_grass \
      set_is_enchantable \
      set_is_enchantstone \
      set_is_engulfer \
      set_is_ethereal \
      set_is_ethereal_minion_generator \
      set_is_explosion \
      set_is_extreme_hazard \
      set_is_fearless \
      set_is_fire \
      set_is_floating \
      set_is_floor \
      set_is_floor_deco \
      set_is_foilage \
      set_is_food \
      set_is_food_eater \
      set_is_glass \
      set_is_gold \
      set_is_hazard \
      set_is_health_booster \
      set_is_hittable \
      set_is_humanoid \
      set_is_hunger_insatiable \
      set_is_indestructible \
      set_is_intelligent \
      set_is_interesting \
      set_is_item \
      set_is_item_carrier \
      set_is_item_collector \
      set_is_item_eater \
      set_is_item_organic \
      set_is_jelly \
      set_is_jelly_baby \
      set_is_jelly_baby_eater \
      set_is_jelly_eater \
      set_is_jelly_parent \
      set_is_jumper \
      set_is_key \
      set_is_key_collector \
      set_is_killed_on_hit_or_miss \
      set_is_killed_on_hitting \
      set_is_laser \
      set_is_lava \
      set_is_light_blocker \
      set_is_living \
      set_is_loggable_for_important_stuff \
      set_is_loggable_for_unimportant_stuff \
      set_is_meat \
      set_is_meat_eater \
      set_is_metal \
      set_is_minion \
      set_is_minion_generator \
      set_is_monst \
      set_is_moveable \
      set_is_movement_blocking_but_destructable \
      set_is_movement_blocking_wall_or_locked_door \
      set_is_msg \
      set_is_no_tile \
      set_is_openable \
      set_is_organic \
      set_is_player \
      set_is_poison \
      set_is_potion \
      set_is_potion_eater \
      set_is_projectile \
      set_is_removeable_if_out_of_slots \
      set_is_resurrectable \
      set_is_ripple \
      set_is_rock \
      set_is_rrr1 \
      set_is_rrr10 \
      set_is_rrr11 \
      set_is_rrr12 \
      set_is_rrr13 \
      set_is_rrr14 \
      set_is_rrr15 \
      set_is_rrr16 \
      set_is_rrr17 \
      set_is_rrr18 \
      set_is_rrr19 \
      set_is_rrr2 \
      set_is_rrr20 \
      set_is_rrr21 \
      set_is_rrr22 \
      set_is_rrr23 \
      set_is_rrr24 \
      set_is_rrr25 \
      set_is_rrr26 \
      set_is_rrr27 \
      set_is_rrr28 \
      set_is_rrr29 \
      set_is_rrr3 \
      set_is_rrr30 \
      set_is_rrr31 \
      set_is_rrr32 \
      set_is_rrr33 \
      set_is_rrr34 \
      set_is_rrr35 \
      set_is_rrr36 \
      set_is_rrr37 \
      set_is_rrr38 \
      set_is_rrr39 \
      set_is_rrr4 \
      set_is_rrr40 \
      set_is_rrr41 \
      set_is_rrr42 \
      set_is_rrr43 \
      set_is_rrr44 \
      set_is_rrr45 \
      set_is_rrr46 \
      set_is_rrr47 \
      set_is_rrr48 \
      set_is_rrr49 \
      set_is_rrr5 \
      set_is_rrr50 \
      set_is_rrr51 \
      set_is_rrr52 \
      set_is_rrr6 \
      set_is_rrr7 \
      set_is_rrr8 \
      set_is_rrr9 \
      set_is_secret_door \
      set_is_sewer_wall \
      set_is_shallow_water \
      set_is_shovable \
      set_is_skill \
      set_is_skillstone \
      set_is_smoke \
      set_is_soft_body \
      set_is_spawner \
      set_is_spiderweb \
      set_is_stamina_check \
      set_is_sticky \
      set_is_stone \
      set_is_sword \
      set_is_target_select_automatically_when_chosen \
      set_is_the_grid \
      set_is_throwable \
      set_is_thrown_automatically_when_chosen \
      set_is_tickable \
      set_is_tmp_thing \
      set_is_torch \
      set_is_treasure_class_a \
      set_is_treasure_class_b \
      set_is_treasure_class_c \
      set_is_treasure_type \
      set_is_treasure_type_chest \
      set_is_treasure_type_eater \
      set_is_undead \
      set_is_usable \
      set_is_used_automatically_when_selected \
      set_is_used_when_thrown \
      set_is_very_combustible \
      set_is_wall \
      set_is_wall_dungeon \
      set_is_wand \
      set_is_wand_eater \
      set_is_water_lover \
      set_is_weapon \
      set_is_weapon_wielder \
      set_is_wooden \
      set_loves_fire \
      set_loves_poison \
      set_loves_spiderwebs \
      set_normal_placement_rules \
      set_on_death_drop_all_items \
      set_on_death_is_open
    do
        grep -q $arg $PAYLOAD
        if [ $? -ne 0 ]; then
            echo "    mytp.$arg(False)" >> $PAYLOAD
        fi
    done

    sort -o $PAYLOAD $PAYLOAD

    cat $PRE $PAYLOAD $POST > $OUT

    diff $OUT $IN

    if [ "$1" = "do" ]; then
        mv $OUT $IN
    fi

done
