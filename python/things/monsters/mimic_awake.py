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
    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def tp_init(name, test_short_name, text_long_name):
    self = tp.Tp(name, test_short_name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.capacity_height(self, 6)
    my.capacity_width(self, 6)
    my.chance_d1000_carrier_of_treasure_class_A(self, 500)
    my.chance_d1000_carrier_of_treasure_class_B(self, 100)
    my.chance_d1000_carrier_of_treasure_class_C(self, 20)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 10)
    my.distance_avoid(self, 2)
    my.distance_vision(self, 5)
    my.dmg_chance_d1000_nat_att(self, 0, 100)
    my.dmg_nat_att_dice(self, "1d8+4")
    my.dmg_nat_att_type(self, "bite")
    my.dmg_received_doubled_from_fire(self, True)
    my.environ_hates_fire(self, 10)
    my.gfx_anim_use(self, "attack_red")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_only_when_awake(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_asleep_anim(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "8d6")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_sleep(self, True)
    my.is_able_to_swim(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_burnable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_hittable(self, True)
    my.is_humanoid(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_item_collector(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_mimic(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.is_wooden(self, True)
    my.move_speed(self, 200)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stamina(self, 100)
    my.stat_con(self, 18)
    my.stat_def(self, 14)
    my.stat_dex(self, 8)
    my.stat_luck(self, 8)
    my.stat_psi(self, 0)
    my.stat_str(self, 8)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A ravenous living treasure chest mimic!")
    my.text_description_short(self, "A hungry mimic.")
    my.text_hits(self, "gores")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="chest1", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="mimic.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="mimic.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="mimic.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="mimic.4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="mimic.5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="mimic.6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="mimic.7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="mimic.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="mimic_awake", test_short_name="mimic", text_long_name="hungry treasure chest mimic")


init()
