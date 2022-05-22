import my
import tp


def on_you_nat_attack(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_dodge_it_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_death(me, x, y):
    my.sound_play("squeaky_toy")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.aggression_level_pct(self, 20)
    my.ai_resent_count(self, 10)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_lunge(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_nat_attack_type(self, "bite")
    my.damage_natural_dice(self, "1d6+2")
    my.damage_received_doubled_from_fire(self, True)
    my.damage_received_doubled_from_poison(self, True)
    my.distance_avoid(self, 5)
    my.distance_vision(self, 5)
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_fire(self, 10)
    my.environ_avoids_poison(self, 100)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_asleep_anim(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.health_initial_dice(self, "2d6")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump_randomly_chance_d1000(self, 20)
    my.is_able_to_jump(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_sleep(self, True)
    my.is_able_to_tire(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_breather(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_food_eater(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_water(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_meat(self, True)
    my.is_monst_class_a(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_red_blood_eater(self, True)
    my.is_red_blooded(self, True)
    my.is_shovable(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 2)
    my.long_text_description(self, "An enormous giant dwarf rat... Blood drips from its teeth. Will eat almost anything, especially you. Sometimes answers to the name of Mr Squeakles.")
    my.monst_size(self, my.MONST_SIZE_NORMAL)
    my.move_speed(self, 200)
    my.noise_decibels_hearing(self, 10)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d6")
    my.on_death_do(self, "me.on_death()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina(self, 100)
    my.stat_con(self, 11)
    my.stat_def(self, 12)
    my.stat_dex(self, 10)
    my.stat_luck(self, 10)
    my.stat_str(self, 7)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A giant dwarf rat, no more, no less. Slightly cute. Rabid.")
    my.text_hits(self, "gores")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 150
    my.tile(self,
            ascii_fg_char="r", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile="rat_giant.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="r", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile="rat_giant.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="r", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile="rat_giant.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="r", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile="rat_giant.4", delay_ms=delay)
    delay = 1500
    my.tile(self,
            ascii_fg_char="r", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile="rat_giant.sleeping.1", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="r", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile="rat_giant.sleeping.2", is_sleeping=True, delay_ms=delay)
    delay = 150
    my.tile(self,
            ascii_fg_char="r", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile="rat_giant.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="rat_giant", text_name="giant dwarf rat")


init()
