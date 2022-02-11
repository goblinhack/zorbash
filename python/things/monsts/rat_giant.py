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
    my.tp_set_aggression_level_pct(mytp, 20)
    my.tp_set_ai_resent_count(mytp, 10)
    my.tp_set_ai_wanderer(mytp, True)
    my.tp_set_attack_eater(mytp, True)
    my.tp_set_attack_lunge(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_natural_attack_type(mytp, "bite")
    my.tp_set_damage_natural_dice(mytp, "1d6+2")
    my.tp_set_damage_received_doubled_from_fire(mytp, True)
    my.tp_set_damage_received_doubled_from_poison(mytp, True)
    my.tp_set_distance_avoid(mytp, 5)
    my.tp_set_distance_jump(mytp, 2)
    my.tp_set_distance_vision(mytp, 5)
    my.tp_set_environ_avoids_acid(mytp, 100)
    my.tp_set_environ_avoids_fire(mytp, 10)
    my.tp_set_environ_avoids_poison(mytp, 100)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "attack_claws")
    my.tp_set_gfx_bounce_on_move(mytp, True)
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_asleep(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "2d6")
    my.tp_set_hunger_clock_tick_frequency(mytp, 50)
    my.tp_set_hunger_health_pct(mytp, 95)
    my.tp_set_hunger_is_insatiable(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_able_to_jump_escape(mytp, True)
    my.tp_set_is_able_to_jump_randomly_chance_d1000(mytp, 50)
    my.tp_set_is_able_to_jump(mytp, True)
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_able_to_sleep(mytp, True)
    my.tp_set_is_able_to_tire(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_bleeder(mytp, True)
    my.tp_set_is_bony(mytp, True)
    my.tp_set_is_breather(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_food_eater(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_immune_to_water(mytp, True)
    my.tp_set_is_living(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_meat_eater(mytp, True)
    my.tp_set_is_meat(mytp, True)
    my.tp_set_is_monst_class_a(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_red_blood_eater(mytp, True)
    my.tp_set_is_red_blooded(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_long_text_description(mytp, "An enormous giant dwarf rat... Blood drips from its teeth. Will eat almost anything, especially you. Sometimes answers to the name of Mr Squeakles.")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_LARGE)
    my.tp_set_noise_decibels_hearing(mytp, 10)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_nutrition_dice(mytp, "1d6")
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(mytp, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(mytp, "me.on_you_natural_attack()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stamina(mytp, 100)
    my.tp_set_stat_con(mytp, 11)
    my.tp_set_stat_def(mytp, 12)
    my.tp_set_stat_dex(mytp, 10)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 7)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A rat, no more, no less. Slightly cute. Likely rabid.")
    my.tp_set_text_hits(mytp, "gores")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 150
    my.tp_set_tile(mytp, "rat_giant.1", delay_ms=delay)
    my.tp_set_tile(mytp, "rat_giant.2", delay_ms=delay)
    my.tp_set_tile(mytp, "rat_giant.3", delay_ms=delay)
    my.tp_set_tile(mytp, "rat_giant.4", delay_ms=delay)
    my.tp_set_tile(mytp, "rat_giant.sleeping.1", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(mytp, "rat_giant.sleeping.2", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(mytp, "rat_giant.dead", is_dead=True, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="rat_giant", text_name="giant dwarf rat")


init()
