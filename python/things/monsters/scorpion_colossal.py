import my
import tp


def on_born(me, x, y):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    my.place_at(me, "random_treasure_class_C", x, y)


def on_you_nat_att(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_hit_dodge_do(me, hitter, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death_epic")


def on_awake(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar_epic")
    my.thing_popup(me, "Deafening roar!")


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
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 100)
    my.distance_vision(self, 3)
    my.dmg_bite_dice(self, "3d8+10")
    my.dmg_chance_d1000_bite(self, 0, 200)
    my.dmg_chance_d1000_digest(self, 0, 200)
    my.dmg_chance_d1000_poison(self, 0, 800)
    my.dmg_digest_dice(self, "1d40")
    my.dmg_poison_dice(self, "1d20+10")
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_cold(self, 100)
    my.environ_avoids_fire(self, 10)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_only_when_awake(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_show_asleep_anim(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "8d10")
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
    my.is_able_to_see_invisible(self, True)
    my.is_able_to_tire(self, True)
    my.is_air_breather(self, True)
    my.is_asleep_initially(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_green_blood(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_green_blooded(self, True)
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
    my.is_msg_allowed_is_wounded(self, True)
    my.is_poisonous_danger_level(self, 10)
    my.is_tickable(self, True)
    my.jump_distance(self, 2)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 10)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "-10")
    my.on_awake_do(self, "me.on_awake()")
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_RARE)  # how rare within this monster class
    my.stamina(self, 100)
    my.stat_con(self, 18)
    my.stat_def(self, 18)
    my.stat_dex(self, 8)
    my.stat_luck(self, 10)
    my.stat_str(self, 20)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A frankly ginormous scorpion. It's stinger alone is larger than your body. Do I have to advise, stay away?")
    my.text_description_short(self, "A colossal scorpion.")
    my.text_hits(self, "splats")
    my.thing_size(self, my.THING_SIZE_GARGANTUAN)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 150
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile="scorpion_colossal.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile="scorpion_colossal.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile="scorpion_colossal.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile="scorpion_colossal.4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="red",
            is_sleeping=True,
            tile="scorpion_colossal.sleeping", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="scorpion.dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="scorpion_colossal", text_long_name="colossal scorpion")


init()
