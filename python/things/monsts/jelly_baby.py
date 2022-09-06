import my
import tp


def on_you_nat_att(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "squelch")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, f"slime{my.non_pcg_randint(1, 9)}")


def on_jump(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "squelch")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 3)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_lunge(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_nat_att_dice(self, "1")
    my.damage_nat_att_type(self, "bite")
    my.damage_received_doubled_from_cold(self, True)
    my.damage_received_doubled_from_fire(self, True)
    my.distance_avoid(self, 2)
    my.distance_vision(self, 5)
    my.environ_avoids_fire(self, 100)
    my.gfx_anim_use(self, "green_splatter")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_jump_attack_chance_d1000(self, 100)
    my.is_able_to_jump_attack(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump_on_low_hp_chance_d1000(self, 500)
    my.is_able_to_jump_randomly_chance_d1000(self, 20)
    my.is_able_to_jump(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_fearless(self, 500)
    my.is_acid(self, True)
    my.is_green_blood_eater(self, True)
    my.is_green_blooded(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_jelly_baby_eater(self, True)
    my.is_jelly_baby(self, True)
    my.is_jelly_eater(self, True)
    my.is_jelly(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_monst_class_a(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_red_blood_eater(self, True)
    my.is_soft(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 2)
    my.move_speed(self, 150)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_death_do(self, "me.on_death()")
    my.on_jump_do(self, "me.on_jump()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_con(self, 10)
    my.stat_def(self, 5)
    my.stat_dex(self, 10)
    my.stat_luck(self, 10)
    my.stat_str(self, 5)
    my.temperature(self, 20)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "splats")
    my.text_long_description2(self, "This one is a baby jelly. It tends to avoid adults of its kind. So should you.")
    my.text_long_description(self, "Jelly jumpers are numerous, bouncy and lots of fun! They will eat almost anything, including their own. They have the annoying habit of jumping when threatened.")
    my.text_short_description(self, "A small pile of semi sentient jelly.")
    my.thing_size(self, my.THING_SIZE_TINY)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="j", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="j", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="j", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="j", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="j", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="j", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="j", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="j", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".8", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="jelly_baby", text_long_name="baby jelly jumper")


init()
