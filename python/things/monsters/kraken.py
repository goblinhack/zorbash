import my
import tp


def on_born(me, x, y):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    my.place_at(me, "random_treasure_class_C", x, y)


def on_you_nat_attack_attempt(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_hit_dodge_do(me, hitter, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death_epic")


def spawn_tentacle(me, x, y, dx, dy):
    if my.level_is_monst_at(me, x + dx, y + dy) or \
       my.level_is_lava_at(me, x + dx, y + dy) or \
       my.level_is_chasm_at(me, x + dx, y + dy) or \
       my.level_is_brazier_at(me, x + dx, y + dy) or \
       my.level_is_fire_at(me, x + dx, y + dy) or \
       my.level_is_wall_at(me, x + dx, y + dy):
        return

    if not my.level_is_water_at(me, x + dx, y + dy):
        return

    my.spawn_at(me, "kraken_tentacle", x + dx, y + dy)


def on_awake(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar_epic")
    my.thing_popup(me, "Deafening roar!")

    spawn_tentacle(me, x, y, -1, 1)
    spawn_tentacle(me, x, y, -1, 0)
    spawn_tentacle(me, x, y, -1, -1)

    spawn_tentacle(me, x, y, 1, 1)
    spawn_tentacle(me, x, y, 1, 0)
    spawn_tentacle(me, x, y, 1, -1)

    spawn_tentacle(me, x, y, 0, 1)
    spawn_tentacle(me, x, y, 0, -1)


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.chance_d1000_tameable(self, 0)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 100)
    my.distance_vision(self, 10)
    my.dmg_bite_dice(self, "3d8+10")
    my.dmg_chance_d1000_bite(self, 0, 200)
    my.dmg_chance_d1000_digest(self, 0, 200)
    my.dmg_chance_d1000_drown(self, 0, 800)
    my.dmg_digest_dice(self, "1d20")
    my.dmg_drown_dice(self, "1d20")
    my.environ_likes_deep_water(self, True)
    my.gfx_anim_use(self, "attack_major_green")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_health_bar_only_when_awake(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_oversized_and_centered(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "8d10")
    my.hunger_clock_tick_freq(self, 50)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_spawn_things(self, True)
    my.is_able_to_tire(self, True)
    my.is_always_submerged_in_water(self, True)
    my.is_asleep_initially(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_engulfer(self, True)
    my.is_green_blooded(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_monst_class_D(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_obs_when_dead(self, True)
    my.is_shootable(self, True)
    my.is_soft(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "green")
    my.light_dist(self, 4)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 40)
    my.noise_on_moving(self, 25)
    my.normal_placement_rules(self, True)
    my.on_awake_do(self, "me.on_awake()")
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_RARE)  # how rare within this monster class
    my.stamina(self, 100)
    my.stat_con(self, 18)
    my.stat_def(self, 18)
    my.stat_dex(self, 8)
    my.stat_int(self, 18)
    my.stat_luck(self, 10)
    my.stat_psi(self, 12)
    my.stat_str(self, 20)
    my.temperature_max(self, 50)
    my.temperature_min(self, -20)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A mighty baby kraken. Beware the grasp of its tentacles and intoxicating fishy breath.")
    my.text_description_short(self, "A baby kraken.")
    my.text_hits(self, "bites")
    my.thing_size(self, my.THING_SIZE_GARGANTUAN)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 500
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".8", delay_ms=delay)

    delay = 5000
    my.tile(self,
            ascii_fg_char="", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile="kraken.sleeping.1", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="o", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile="kraken.sleeping.2", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile="kraken.sleeping.3", is_sleeping=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="kraken.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="kraken", text_long_name="baby kraken")


init()
