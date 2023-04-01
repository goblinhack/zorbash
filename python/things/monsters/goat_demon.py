import my
import tp


def on_born(me, x, y):
    my.thing_friend(me, "is_goat")


def on_you_nat_att(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_dodge_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_death(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_want_to_shoot_at(me, target, target_x, target_y):  # Return True on doing an action
    if my.pcg_randint(1, 10) < 3:
        my.thing_shoot_at(me, "staff_fire_projectile", target)
        return True
    return False


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.chance_d1000_jump_randomly(self, 20)
    my.chance_d1000_shove(self, 1000)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 2)
    my.distance_avoid(self, 5)
    my.distance_vision(self, 7)
    my.dmg_nat_att_dice(self, "2d6+2")
    my.dmg_nat_att_type(self, "rutt")
    my.dmg_received_doubled_from_cold(self, True)
    my.dmg_received_doubled_from_water(self, True)
    my.environ_avoids_cold(self, 100)
    my.environ_avoids_water(self, 100)
    my.gfx_anim_use(self, "attack_green")
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
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "6d6")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at(self, True)
    my.is_able_to_swim(self, True)
    my.is_able_to_tire(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_sewer(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_daring(self, True)
    my.is_demon(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_fire_elemental(self, True)
    my.is_goat(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_interesting(self, True)
    my.is_lifeless(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 2)
    my.move_speed(self, 150)
    my.noise_decibels_hearing(self, 10)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d6")
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_want_to_shoot_at_do(self, "me.on_want_to_shoot_at()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_RARE)  # how rare within this monster class
    my.shove_strength_mod(self, 3)
    my.stamina(self, 100)
    my.stat_con(self, 12)
    my.stat_def(self, 10)
    my.stat_dex(self, 12)
    my.stat_luck(self, 6)
    my.stat_str(self, 12)
    my.temperature_min(self, 50)
    my.temperature(self, 100)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A creature from the darkest depths of the dungeon, the demon goat is not to be trifled with. Watch out for its flaming nostril attack.")
    my.text_description_short(self, "A flaming mad demon goat.")
    my.text_hits(self, "gores")
    my.thing_size(self, my.THING_SIZE_GIANT)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 150
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile="goat_demon.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile="goat_demon.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile="goat_demon.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile="goat_demon.4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile="goat_demon.5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile="goat_demon.6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile="goat_demon.7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile="goat_demon.8", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile="goat_demon.9", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="goat_demon.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="goat_demon", text_long_name="demon goat")


init()
