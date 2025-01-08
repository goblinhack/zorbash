import my
import tp


def on_born(me, x, y):
    my.thing_friend(me, "is_sluud")
    my.thing_enemy(me, "dogman")
    my.thing_enemy(me, "gnoll")
    my.thing_carry(me, "dart_poison")
    my.thing_carry(me, "dart_poison")
    my.thing_carry(me, "dart")


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
    my.thing_msg(me, "The sluud curses and dies!")

    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 90)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.capacity_height(self, 6)
    my.capacity_width(self, 6)
    my.chance_d1000_carrier_of_treasure_class_A(self, 20)
    my.chance_d1000_carrier_of_weapon_class_A(self, 1000)
    my.chance_d1000_shooting(self, 500)
    my.chance_d1000_tameable(self, 50)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 10)
    my.distance_avoid(self, 5)
    my.distance_throw(self, 10)
    my.distance_vision(self, 10)
    my.dmg_chance_d1000_nat_att(self, 0, 100)
    my.dmg_limited_per_tick(self, True)
    my.dmg_nat_att_dice(self, "1d4+1")
    my.dmg_nat_att_type(self, "bite")
    my.dmg_rcv_doubled_from_fire(self, True)
    my.environ_dislikes_acid(self, 100)
    my.environ_dislikes_cold(self, 100)
    my.environ_hates_fire(self, 10)
    my.gfx_anim_use(self, "attack_red")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.has_a_head(self, True)
    my.health_initial_dice(self, "2d6")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_learn_skills(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rage(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at(self, True)
    my.is_able_to_swim(self, True)
    my.is_able_to_tire(self, True)
    my.is_able_to_use_amulet(self, True)
    my.is_able_to_use_cloak(self, True)
    my.is_able_to_use_ranged_weapons(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_buffable(self, True)
    my.is_burnable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_daring(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_hittable(self, True)
    my.is_humanoid(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_item_collector(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_monst(self, True)
    my.is_monst_class_B(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_red_blooded(self, True)
    my.is_shootable(self, True)
    my.is_shovable(self, True)
    my.is_sluud(self, True)
    my.is_swimmer(self, True)
    my.is_swimmer_but_land_dweller(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 10)
    my.noise_on_moving(self, 50)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stamina(self, 100)
    my.stat_con(self, 11)
    my.stat_def(self, 12)
    my.stat_dex(self, 12)
    my.stat_int(self, 8)
    my.stat_psi(self, 8)
    my.stat_str(self, 8)
    my.temperature(self, 20)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "The Sluud are are proud and slimy race of warriors that rarely leave their swampy domain. Highly sociable, the Sluud live in large groups that are best avoided. Beware the dark sluuds.")
    my.text_description_short(self, "A sluud.")
    my.text_hits(self, "gores")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="s", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="s", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self,
            ascii_fg_char="s", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self,
            ascii_fg_char="s", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_fg_char="s", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="sluud.dead.1", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="sluud", text_long_name="sluud")


init()
