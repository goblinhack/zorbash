import my
import tp


def on_you_natural_attack(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_miss_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    my.sound_play("squeaky_toy")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_aggression_level_pct(20)
    mytp.set_ai_resent_count(10)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_eater(True)
    mytp.set_attack_lunge(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_natural_attack_type("bite")
    mytp.set_damage_natural_dice("1d6+2")
    mytp.set_damage_received_doubled_from_fire(True)
    mytp.set_damage_received_doubled_from_poison(True)
    mytp.set_distance_avoid(5)
    mytp.set_distance_jump(2)
    mytp.set_distance_vision(5)
    mytp.set_environ_avoids_acid(100)
    mytp.set_environ_avoids_fire(10)
    mytp.set_environ_avoids_poison(100)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_claws")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_asleep(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("2d6")
    mytp.set_hunger_clock_tick_frequency(50)
    mytp.set_hunger_health_pct(95)
    mytp.set_hunger_is_insatiable(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_jump_escape(True)
    mytp.set_is_able_to_jump_randomly_chance_d1000(50)
    mytp.set_is_able_to_jump(True)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_able_to_sleep(True)
    mytp.set_is_able_to_tire(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_biome_swamp(True)
    mytp.set_is_bleeder(True)
    mytp.set_is_bony(True)
    mytp.set_is_breather(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_food_eater(True)
    mytp.set_is_hittable(True)
    mytp.set_is_immune_to_water(True)
    mytp.set_is_living(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_meat(True)
    mytp.set_is_monst_class_a(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_red_blood_eater(True)
    mytp.set_is_red_blooded(True)
    mytp.set_is_shovable(True)
    mytp.set_is_tickable(True)
    mytp.set_long_text_description("An enormous giant dwarf rat... Blood drips from its teeth. Will eat almost anything, especially you. Sometimes answers to the name of Mr Squeakles.")
    mytp.set_monst_size(my.MONST_SIZE_LARGE)
    mytp.set_noise_decibels_hearing(10)
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("1d6")
    mytp.set_on_death_do("me.on_death()")
    mytp.set_on_you_are_hit_but_still_alive_do("me.on_you_are_hit_but_still_alive()")
    mytp.set_on_you_miss_do("me.on_you_miss_do()")
    mytp.set_on_you_natural_attack_do("me.on_you_natural_attack()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stamina(100)
    mytp.set_stat_con(11)
    mytp.set_stat_def(12)
    mytp.set_stat_dex(10)
    mytp.set_stat_luck(10)
    mytp.set_stat_str(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A rat, no more, no less. Slightly cute. Likely rabid.")
    mytp.set_text_hits("gores")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 150
    mytp.set_tile("rat_giant.1", delay_ms=delay)
    mytp.set_tile("rat_giant.2", delay_ms=delay)
    mytp.set_tile("rat_giant.3", delay_ms=delay)
    mytp.set_tile("rat_giant.4", delay_ms=delay)
    mytp.set_tile("rat_giant.sleeping.1", is_sleeping=True, delay_ms=delay)
    mytp.set_tile("rat_giant.sleeping.2", is_sleeping=True, delay_ms=delay)
    mytp.set_tile("rat_giant.dead", is_dead=True, delay_ms=delay)

    mytp.update()


def init():
    tp_init(name="rat_giant", text_name="giant dwarf rat")


init()
