import my
import tp


def on_born(me, x, y):
    my.thing_carry(me, "gold1")


def on_you_nat_attack_attempt(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_hit_dodge_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    sound = "squeaky_toy"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, -10)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 1)
    my.distance_avoid(self, 5)
    my.distance_vision(self, 5)
    my.dmg_bite_dice(self, "1d1+1")
    my.dmg_chance_d1000_bite(self, 0, 50)
    my.dmg_chance_d1000_nat_att(self, 0, 100)
    my.dmg_nat_att_dice(self, "1d1+2")
    my.dmg_nat_att_type(self, "nibble")
    my.environ_likes_shallow_water(self, True)
    my.gfx_anim_use(self, "attack_red")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.gold_value_dice(self, "1")
    my.health_initial_dice(self, "1d10")
    my.hunger_clock_tick_freq(self, 50)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_live_out_of_water(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_tire(self, True)
    my.is_always_submerged_in_water(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_sewer(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_monst_class_A(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_red_blooded(self, True)
    my.is_soft(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stamina(self, 100)
    my.stat_con(self, 1)
    my.stat_def(self, 1)
    my.stat_dex(self, 15)
    my.stat_luck(self, 10)
    my.stat_str(self, 1)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A tiny little goldfish.")
    my.text_description_short(self, "A goldfish.")
    my.text_hits(self, "nibbles")
    my.thing_size(self, my.THING_SIZE_TINY)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".15", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="goldfish", text_long_name="goldfish")


init()
