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
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 20)
    my.tp_set_ai_resent_count(self, 10)
    my.tp_set_ai_wanderer(self, True)
    my.tp_set_attack_eater(self, True)
    my.tp_set_attack_lunge(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_damage_natural_attack_type(self, "bite")
    my.tp_set_damage_natural_dice(self, "1d6+2")
    my.tp_set_damage_received_doubled_from_fire(self, True)
    my.tp_set_damage_received_doubled_from_poison(self, True)
    my.tp_set_distance_avoid(self, 5)
    my.tp_set_distance_jump(self, 2)
    my.tp_set_distance_vision(self, 5)
    my.tp_set_environ_avoids_acid(self, 100)
    my.tp_set_environ_avoids_fire(self, 10)
    my.tp_set_environ_avoids_poison(self, 100)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "attack_claws")
    my.tp_set_gfx_bounce_on_move(self, True)
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_asleep(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "2d6")
    my.tp_set_hunger_clock_tick_frequency(self, 50)
    my.tp_set_hunger_health_pct(self, 95)
    my.tp_set_hunger_is_insatiable(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_able_to_jump_escape(self, True)
    my.tp_set_is_able_to_jump_randomly_chance_d1000(self, 50)
    my.tp_set_is_able_to_jump(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_able_to_sleep(self, True)
    my.tp_set_is_able_to_tire(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_bleeder(self, True)
    my.tp_set_is_bony(self, True)
    my.tp_set_is_breather(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_food_eater(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_immune_to_water(self, True)
    my.tp_set_is_living(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_meat_eater(self, True)
    my.tp_set_is_meat(self, True)
    my.tp_set_is_monst_class_a(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_red_blood_eater(self, True)
    my.tp_set_is_red_blooded(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_long_text_description(self, "An enormous giant dwarf rat... Blood drips from its teeth. Will eat almost anything, especially you. Sometimes answers to the name of Mr Squeakles.")
    my.tp_set_monst_size(self, my.MONST_SIZE_LARGE)
    my.tp_set_noise_decibels_hearing(self, 10)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_nutrition_dice(self, "1d6")
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(self, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stamina(self, 100)
    my.tp_set_stat_con(self, 11)
    my.tp_set_stat_def(self, 12)
    my.tp_set_stat_dex(self, 10)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 7)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A rat, no more, no less. Slightly cute. Likely rabid.")
    my.tp_set_text_hits(self, "gores")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 150
    my.tp_set_tile(self, "rat_giant.1", delay_ms=delay)
    my.tp_set_tile(self, "rat_giant.2", delay_ms=delay)
    my.tp_set_tile(self, "rat_giant.3", delay_ms=delay)
    my.tp_set_tile(self, "rat_giant.4", delay_ms=delay)
    my.tp_set_tile(self, "rat_giant.sleeping.1", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(self, "rat_giant.sleeping.2", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(self, "rat_giant.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="rat_giant", text_name="giant dwarf rat")


init()
