import my
import tp


def on_born(me, x, y):
    my.thing_enemy(me, "is_ogre")
    my.thing_friend(me, "troll_fire")
    my.thing_enemy(me, "troll_stone")
    my.thing_enemy(me, "is_ettin")


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
    my.thing_msg(me, "The troll howls mournfully and then turns to stone!")
    my.spawn_at_my_position(me, "fire")

    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_want_to_shoot_at(me, target, target_x, target_y):  # Return True on doing an action
    my.thing_shoot_projectile_or_laser_at(me, "projectile_fire", target)
    return True


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.chance_d1000_regenerate(self, 100)
    my.chance_d1000_shooting(self, 300)
    my.chance_d1000_shove(self, 200)
    my.chance_d1000_tameable(self, 0)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 10)
    my.distance_vision(self, 3)
    my.dmg_chance_d1000_nat_att(self, 0, 1000)
    my.dmg_nat_att_dice(self, "1d12+4")
    my.dmg_nat_att_type(self, "bludgeon")
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
    my.health_initial_dice(self, "10d8")
    my.health_regenerate_amount_dice(self, "1d2")
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_break_out_of_crystal(self, True)
    my.is_able_to_break_out_of_ice(self, True)
    my.is_able_to_break_out_of_webs(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_regenerate(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_lava(self, True)
    my.is_buffable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_daring(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_fire_elemental(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_humanoid(self, True)
    my.is_immune_to_fire(self, True)
    my.is_immune_to_poison(self, True)
    my.is_interesting(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_monst_class_B(self, True)
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
    my.is_troll(self, True)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 50)
    my.noise_on_moving(self, 45)
    my.normal_placement_rules(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_death_is_stone(self, True)
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_want_to_shoot_at_do(self, "me.on_want_to_shoot_at()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_UNCOMMON)  # how rare within this monster class
    my.shove_bonus(self, 1)
    my.stamina(self, 100)
    my.stat_con(self, 18)
    my.stat_def(self, 12)
    my.stat_dex(self, 8)
    my.stat_int(self, 6)
    my.stat_luck(self, 8)
    my.stat_psi(self, 6)
    my.stat_str(self, 18)
    my.text_a_or_an(self, "a")
    my.text_pluralize(self, "fire trolls")
    my.text_apostrophize(self, "fire troll's")
    my.text_description_long2(self, "This fire troll likes the heat of battle and does not appreciate comments that he looks like Iron Man.")
    my.text_description_long3(self, "Trolls can naturally regenerate health. You have been warned.")
    my.text_description_long(self, "An enormous creature that seems to be a collection of burning boulders strung together and brought to life.")
    my.text_description_short(self, "A hot fire troll.")
    my.text_hits(self, "gores")
    my.thing_size(self, my.THING_SIZE_GIANT)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 35
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".15", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="troll_fire.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="troll_fire",
            text_long_name="fire troll")


init()
