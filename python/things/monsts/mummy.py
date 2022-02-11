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
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 100)
    my.tp_set_ai_resent_count(self, 100)
    my.tp_set_ai_shove_chance_d1000(self, 200)
    my.tp_set_ai_wanderer(self, True)
    my.tp_set_attack_eater(self, True)
    my.tp_set_attack_humanoid(self, True)
    my.tp_set_attack_living(self, True)
    my.tp_set_attack_lunge(self, True)
    my.tp_set_attack_meat(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_damage_natural_attack_chance_d1000(self, 950)
    my.tp_set_damage_natural_attack_type(self, "claw")
    my.tp_set_damage_natural_dice(self, "1d6+10")
    my.tp_set_damage_necrosis_chance_d1000(self, 50)
    my.tp_set_damage_necrosis_dice(self, "1")
    my.tp_set_damage_received_doubled_from_fire(self, True)
    my.tp_set_damage_received_doubled_from_water(self, True)
    my.tp_set_distance_vision(self, 5)
    my.tp_set_environ_avoids_fire(self, 100)
    my.tp_set_environ_avoids_water(self, 100)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "attack_claws")
    my.tp_set_gfx_bounce_on_move(self, True)
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "2d20")
    my.tp_set_hunger_clock_tick_frequency(self, 50)
    my.tp_set_hunger_health_pct(self, 95)
    my.tp_set_hunger_is_insatiable(self, True)
    my.tp_set_is_able_to_change_levels(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_able_to_shove(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_fearless(self, True)
    my.tp_set_is_green_blooded(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_immune_to_cold(self, True)
    my.tp_set_is_immune_to_necrosis(self, True)
    my.tp_set_is_immune_to_poison(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_monst_class_b(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_necrotic_danger_level(self, 1)  # danger level
    my.tp_set_is_red_blood_eater(self, True)
    my.tp_set_is_resurrectable(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_undead(self, True)
    my.tp_set_long_text_description(self, "Possibly the corpse of one who ventured into this dungeon before. All life is gone now, and what remains is a corpse wrapped in rags. Death is no release for this poor creature. Watch out for its necrotic touch!")
    my.tp_set_monst_size(self, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(self, 50)
    my.tp_set_noise_on_moving_or_being_carried(self, 5)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(self, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_resurrect_dice(self, "1d10+30")
    my.tp_set_stat_con(self, 15)
    my.tp_set_stat_def(self, 11)
    my.tp_set_stat_dex(self, 10)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 16)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A staggering corpse, covered in tissue paper.")
    my.tp_set_text_hits(self, "claws")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 200
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)

    delay = 50
    my.tp_set_tile(self, tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    delay = 200
    my.tp_set_tile(self, tile=name + ".5.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self,
        tile=name + ".1.dead",
        is_resurrecting=True,
        is_end_of_anim=True,
        is_alive_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="mummy", text_name="mummy")


init()
