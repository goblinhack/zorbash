import my
import tp


def on_you_nat_attack_attempt(me, x, y):
    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_dodge_do(me, hitter, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def on_awake(me, x, y):
    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)
    my.thing_speaks(me, "Who dares wake me?")
    my.thing_popup(me, "Tiny roar!")


def on_want_to_shoot_at(me, target, x, y):  # Return True on doing an action
    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)
    my.thing_shoot_projectile_or_laser_at(me, "projectile_fire", target)
    return True


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.chance_d1000_shooting(self, 250)
    my.chance_d1000_tameable(self, 0)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.distance_vision(self, 10)
    my.dmg_nat_att_dice(self, "1d6")
    my.dmg_nat_att_type(self, "gore")
    my.gfx_anim_use(self, "attack_red")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_health_bar_only_when_awake(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d8+20")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at(self, True)
    my.is_able_to_sleep(self, True)
    my.is_asleep_initially(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_corpse_on_death(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_stamina_drain(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_C(self, True)
    my.is_monst(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_shootable(self, True)
    my.is_shovable(self, True)
    my.is_stone(self, True)
    my.is_tickable(self, True)
    my.is_very_hard(self, True)
    my.is_very_heavy(self, True)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 50)
    my.noise_on_moving(self, 5)
    my.normal_placement_rules(self, True)
    my.on_awake_do(self, "me.on_awake()")
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_want_to_shoot_at_do(self, "me.on_want_to_shoot_at()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stat_con(self, 16)
    my.stat_def(self, 10)
    my.stat_dex(self, 0)
    my.stat_int(self, 14)
    my.stat_luck(self, 10)
    my.stat_psi(self, 14)
    my.stat_str(self, 12)
    my.temperature(self, 20)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "This particular gargoyle is just starting out in its career, hence the diminutive stature. It is not as capable as its mature form, but is still to be feared...")
    my.text_description_long(self, "This small creature guards the dungeon from the likes of you. Gargoyles lurk amongst the ruins and delight in the art of surprise...")
    my.text_description_short(self, "A fearsome gargoyle.")
    my.text_hits(self, "slashes")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    delay = 10000
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle_baby.sleeping", is_sleeping=True, delay_ms=delay)
    delay = 300
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle_baby.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle_baby.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle_baby.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="gargoyle_baby.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="gargoyle_baby", text_long_name="gargoyle baby")


init()
