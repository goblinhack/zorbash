import my
import tp


def on_you_nat_attack(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "squelch")


def on_death(me, x, y):
    if my.pcg_randint(1, 100) < 40:
        my.level_spawn_next_to(me, "jelly_baby")
    if my.pcg_randint(1, 100) < 40:
        my.level_spawn_next_to(me, "jelly_baby")
    if my.pcg_randint(1, 100) < 40:
        my.level_spawn_next_to(me, "jelly_baby")
    if my.pcg_randint(1, 100) < 40:
        my.level_spawn_next_to(me, "jelly_baby")
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, f"slime{my.non_pcg_randint(1, 9)}")


def on_jump(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "squelch")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.gfx_ascii_mode_shown(self, True)
    my.aggression_level_pct(self, 100)
    my.ai_resent_count(self, 10)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_lunge(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_nat_attack_type(self, "bite")
    my.damage_natural_dice(self, "1d5")
    my.damage_received_doubled_from_cold(self, True)
    my.damage_received_doubled_from_fire(self, True)
    my.distance_avoid(self, 3)
    my.distance_vision(self, 7)
    my.environ_avoids_fire(self, 100)
    my.gfx_anim_use(self, "green_splatter")
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "10")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_jump_attack_chance_d1000(self, 200)
    my.is_able_to_jump_attack(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump_on_low_hp_chance_d1000(self, 500)
    my.is_able_to_jump_randomly_chance_d1000(self, 2)
    my.is_able_to_jump(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_acid(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_burnable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_fearless(self, 500)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_jelly_baby_eater(self, True)
    my.is_jelly_eater(self, True)
    my.is_jelly_parent(self, True)
    my.is_jelly(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_monst_class_a(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_pink_blood_eater(self, True)
    my.is_pink_blooded(self, True)
    my.is_red_blood_eater(self, True)
    my.is_soft(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 2)
    my.long_text_description2(self, "This is an adult. It will eat its own children, and you!")
    my.long_text_description(self, "Jelly jumpers are numerous, bouncy and carnivorous. They will eat almost anything, including their own. They have the annoying habit of jumping when threatened and dividing when defeated.")
    my.monst_size(self, my.MONST_SIZE_LARGE)
    my.move_speed(self, 80)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_death_do(self, "me.on_death()")
    my.on_jump_do(self, "me.on_jump()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_con(self, 14)
    my.stat_def(self, 8)
    my.stat_dex(self, 10)
    my.stat_luck(self, 10)
    my.stat_str(self, 15)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A gargantuan pile of sentient jelly.")
    my.text_hits(self, "splats")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_MONST)

    delay = 200
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".7.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".8.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".3.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".4.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".5.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".6.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".7.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".8.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".3.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".4.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".5.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".6.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".7.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".8.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".3.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".4.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".5.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".6.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".7.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="J", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".8.25", is_hp_25_percent=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="jelly_parent", text_name="jelly jumper")


init()
