import my
import tp


def on_you_nat_attack_attempt(me, x, y):
    sound = f"hiss{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_dodge_do(me, hitter, x, y):
    sound = f"hiss{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_death(me, x, y):
    my.thing_msg(me, "The ogre howls mournfully and dies!")

    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.chance_d1000_shove(self, 500)
    my.chance_d1000_tameable(self, 100)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 10)
    my.distance_vision(self, 10)
    my.dmg_chance_d1000_nat_att(self, 0, 1000)
    my.dmg_chance_d1000_nat_att(self, 1, 200)
    my.dmg_nat_att_dice(self, "2d8+5")
    my.dmg_nat_att_type(self, "beak")
    my.dmg_num_of_attacks(self, 2)
    my.dmg_rcv_doubled_from_fire(self, True)
    my.gfx_anim_use(self, "sword_plutonium_swing")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.has_a_head(self, True)
    my.health_initial_dice(self, "8d10+20")
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_break_out_of_crystal(self, True)
    my.is_able_to_break_out_of_ice(self, True)
    my.is_able_to_break_out_of_webs(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_bearowl(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_swamp(self, True)
    my.is_buffable(self, True)
    my.is_burnable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_daring(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_C(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_obs_when_dead(self, True)
    my.is_shootable(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 120)
    my.noise_decibels_hearing(self, 1)
    my.noise_on_moving(self, 25)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.shove_bonus(self, 1)
    my.stamina(self, 100)
    my.stat_con(self, 17)
    my.stat_def(self, 14)
    my.stat_dex(self, 12)
    my.stat_int(self, 12)
    my.stat_luck(self, 10)
    my.stat_psi(self, 12)
    my.stat_str(self, 20)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Not to be confused with the owlbear, the bearowl is a vastly different creature. Armed with its formidable multi beak attack per round, the owlbear, I mean bearowl is not to be trifled with.")
    my.text_description_short(self, "A bearowl.")
    my.text_hits(self, "gores")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 900
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="O", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="bearowl.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="bearowl", text_long_name="bearowl")


init()
