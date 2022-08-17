import my
import tp


def on_you_nat_att(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_are_hit_but_dodge_it_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_lunge(self, True)
    my.attack_meat(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_nat_att_dice(self, "1d4")
    my.damage_nat_att_type(self, "bite")
    my.distance_avoid(self, 3)
    my.distance_minion_vision_shared(self, True)
    my.distance_mob_max(self, 12)
    my.distance_vision(self, 13)
    my.environ_avoids_poison(self, 100)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.health_initial_dice(self, "1d6")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_tire(self, True)
    my.is_air_breathher(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flying(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_water(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_meat(self, True)
    my.is_minion(self, True)
    my.is_monst_class_a(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_red_blooded(self, True)
    my.is_soft(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 300)
    my.noise_decibels_hearing(self, 0)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina(self, 100)
    my.stat_con(self, 10)
    my.stat_def(self, 12)
    my.stat_dex(self, 15)
    my.stat_luck(self, 10)
    my.stat_str(self, 2)
    my.temperature(self, 20)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "claws")
    my.text_long_description(self, "A friendly little blood sucking bat.")
    my.text_short_description(self, "A little bat.")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 70
    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".1.100", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".2.100", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".3.100", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".4.100", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".5.100", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".6.100", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="b", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.3", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="bat_minion", text_long_name="little fluffy bat")


init()
