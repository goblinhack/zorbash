import my
import tp


def on_you_nat_attack_attempt(me, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
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


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker

    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 90)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.chance_d1000_jump_attack(self, 800)
    my.chance_d1000_jump_onto(self, 100)
    my.chance_d1000_jump_randomly(self, 20)
    my.chance_d1000_teleport_self(self, 100)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 1)
    my.distance_avoid(self, 2)
    my.distance_vision(self, 3)
    my.dmg_chance_d1000_nat_att(self, 0, 100)
    my.dmg_nat_att_dice(self, "1d3+1")
    my.dmg_nat_att_type(self, "bite")
    my.dmg_received_doubled_from_fire(self, True)
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_cold(self, 100)
    my.environ_avoids_fire(self, 10)
    my.environ_avoids_poison(self, 10)
    my.gfx_anim_use(self, "attack_red")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "2d6")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_jump_attack(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump_onto(self, True)
    my.is_able_to_jump(self, True)
    my.is_able_to_jump_without_tiring(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_teleport_escape(self, True)
    my.is_able_to_teleport_self(self, True)
    my.is_able_to_teleport_without_tiring(self, True)
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
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_red_blooded(self, True)
    my.is_shovable(self, True)
    my.is_soft(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 3)
    my.move_speed(self, 150)
    my.noise_decibels_hearing(self, 10)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "-10")
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stamina(self, 100)
    my.stat_con(self, 10)
    my.stat_def(self, 12)
    my.stat_dex(self, 18)
    my.stat_luck(self, 18)
    my.stat_str(self, 7)
    my.teleport_distance(self, 5)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "Blinkcats have amazing hearing, but terrible taste in music and is a fan of early 2000s pop music")
    my.text_description_long(self, "The agility of a cat with teleport capabilities, the blink cat is able to avoid your attacks with ease.")
    my.text_description_short(self, "A blinkcat.")
    my.text_hits(self, "splats")
    my.thing_size(self, my.THING_SIZE_SMALL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 150
    my.tile(self,
            ascii_fg_char="c", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile="blinkcat.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="c", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile="blinkcat.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="c", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile="blinkcat.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="c", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile="blinkcat.4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="c", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile="blinkcat.5", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="c", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="blinkcat.dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="blinkcat", text_long_name="blinkcat")


init()
