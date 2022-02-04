import my
import tp


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "squelch")


def on_death(me, x, y):
    my.level_spawn_next_to(me, "jelly_baby")
    my.level_spawn_next_to(me, "jelly_baby")
    my.level_spawn_next_to(me, "jelly_baby")
    my.level_spawn_next_to(me, "jelly_baby")
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, f"slime{my.non_pcg_randint(1, 9)}")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_aggression_level_pct(100)
    mytp.set_ai_resent_count(10)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_eater(True)
    mytp.set_attack_lunge(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_natural_attack_type("bite")
    mytp.set_damage_natural_dice("1d5")
    mytp.set_damage_received_doubled_from_fire(True)
    mytp.set_distance_avoid(3)
    mytp.set_distance_jump(2)
    mytp.set_distance_vision(7)
    mytp.set_environ_avoids_fire(100)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("green_splatter")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("10")
    mytp.set_hunger_clock_tick_frequency(50)
    mytp.set_hunger_health_pct(95)
    mytp.set_hunger_is_insatiable(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_jump_attack_chance_d1000(200)
    mytp.set_is_able_to_jump_attack(True)
    mytp.set_is_able_to_jump_escape(True)
    mytp.set_is_able_to_jump_on_low_hp_chance_d1000(500)
    mytp.set_is_able_to_jump_randomly_chance_d1000(2)
    mytp.set_is_able_to_jump(True)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_acid(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_biome_swamp(True)
    mytp.set_is_bleeder(True)
    mytp.set_is_burnable(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_fearless(500)
    mytp.set_is_hittable(True)
    mytp.set_is_immune_to_acid(True)
    mytp.set_is_immune_to_necrosis(True)
    mytp.set_is_jelly_baby_eater(True)
    mytp.set_is_jelly_eater(True)
    mytp.set_is_jelly_parent(True)
    mytp.set_is_jelly(True)
    mytp.set_is_living(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_monst_class_a(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_pink_blood_eater(True)
    mytp.set_is_pink_blooded(True)
    mytp.set_is_red_blood_eater(True)
    mytp.set_is_tickable(True)
    mytp.set_is_toughness_soft(True)
    mytp.set_long_text_description("Jelly jumpers are numerous, bouncy and carnivorous. They will eat almost anything, including their own. They have the annoying habit of jumping when threatened and dividing when defeated . This is an adult. It will eat its own children!")
    mytp.set_monst_size(my.MONST_SIZE_LARGE)
    mytp.set_noise_level_hearing(50)
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("1d4")
    mytp.set_on_death_do("me.on_death()")
    mytp.set_on_you_are_hit_but_still_alive_do("me.on_you_are_hit_but_still_alive()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stat_con(14)
    mytp.set_stat_def(8)
    mytp.set_stat_dex(10)
    mytp.set_stat_str(15)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A gargantuan pile of sentient jelly.")
    mytp.set_text_hits("splats")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.25", is_hp_25_percent=True, delay_ms=delay)

    mytp.update()


def init():
    tp_init(name="jelly_parent", text_name="jelly jumper")


init()
