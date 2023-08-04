import my
import tp


def on_born(me, x, y):
    my.thing_friend(me, "iceman")


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
    my.spawn_at_my_position(me, "water")
    my.thing_msg(me, "The iceman cries hoarsely and shatters!")

    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_want_to_shoot_at(me, target, target_x, target_y):  # Return True on doing an action
    if my.py_pcg_random_range_inclusive(1, 100) < 20:
        sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)
        my.thing_shoot_at(me, "projectile_cold", target)
        return True
    return False


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.chance_d1000_shooting(self, 500)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.distance_avoid(self, 4)
    my.distance_vision(self, 10)
    my.dmg_chance_d1000_cold(self, 0, 1000)
    my.dmg_chance_d1000_nat_att(self, 0, 100)
    my.dmg_cold_dice(self, "1d8")
    my.environ_hates_fire(self, 100)
    my.gfx_anim_use(self, "attack_red")
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
    my.gfx_pixelart_show_asleep_anim(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "10d8")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at(self, True)
    my.is_able_to_sleep(self, True)
    my.is_able_to_tire(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_ice(self, True)
    my.is_cold_elemental(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_fearless(self, True)
    my.is_hittable(self, True)
    my.is_humanoid(self, True)
    my.is_iceman(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_red_blooded(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 5)
    my.noise_on_moving(self, 5)
    my.normal_placement_rules(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_want_to_shoot_at_do(self, "me.on_want_to_shoot_at()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.spawn_group_radius(self, 4)
    my.spawn_group_size_dice(self, "1d3")
    my.stamina(self, 100)
    my.stat_con(self, 11)
    my.stat_def(self, 12)
    my.stat_dex(self, 8)
    my.stat_int(self, 14)
    my.stat_luck(self, 8)
    my.stat_psi(self, 14)
    my.stat_str(self, 14)
    my.temperature_max(self, 0)
    my.temperature_min(self, -100)
    my.temperature(self, -20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Icemen are deadly hunters and prefer their prey cold and frozen. Watch out for their deadly ice blast attack and touch of death.")
    my.text_description_short(self, "A frosty iceman.")
    my.text_hits(self, "gores")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 400
    my.tile(self,
            ascii_fg_char="I", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="I", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self,
            ascii_fg_char="I", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self,
            ascii_fg_char="I", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_fg_char="I", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".5", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_fg_char="I", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".6", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_fg_char="I", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".7", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_fg_char="I", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".8", delay_ms=delay, frame=4)

    my.tp_update(self)


def init():
    tp_init(name="iceman", text_long_name="iceman")


init()
