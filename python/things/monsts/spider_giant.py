import my
import tp


def on_you_nat_attack(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_are_hit_but_dodge_it_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "squelch")


def on_born(me, x, y):
    it = my.level_spawn_at_thing(me, "spiderweb")
    if it != 0:
        my.thing_set_mob(me, it)


def on_firing_at_something(me, target, x, y):  # Return True on doing an action
    if my.pcg_randint(1, 100) < 10:
        my.thing_fire_at(me, "projectile_web", target)
        my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "slime1")
        return True
    return False


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.aggression_level_pct(self, 100)
    my.ai_resent_count(self, 10)
    my.attack_eater(self, True)
    my.attack_lunge(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_nat_attack_chance_d1000(self, 0, 900)
    my.damage_nat_attack_type(self, "gore")
    my.damage_natural_dice(self, "1d8+3")
    my.damage_poison_chance_d1000(self, 0, 100)
    my.damage_poison_dice(self, "2d8+2")
    my.damage_received_doubled_from_fire(self, True)
    my.distance_avoid(self, 5)
    my.distance_mob_max(self, 5)
    my.distance_vision(self, 5)
    my.environ_avoids_fire(self, 10)
    my.environ_avoids_poison(self, 100)
    my.environ_avoids_water(self, 100)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.health_initial_dice(self, "4d15+4")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_fire_at(self, True)
    my.is_able_to_jump_attack_chance_d1000(self, 800)
    my.is_able_to_jump_attack(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump_onto_chance_d1000(self, 100)
    my.is_able_to_jump_onto(self, True)
    my.is_able_to_jump_randomly_chance_d1000(self, 20)
    my.is_able_to_jump(self, True)
    my.is_able_to_jump_without_tiring(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_tire(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_bleeder(self, True)
    my.is_breather(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_food_eater(self, True)
    my.is_green_blooded(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_spiderwebs(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_monst_class_b(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_poisonous_danger_level(self, 1)
    my.is_poisonous_danger_level(self, 2)  # danger level
    my.is_shovable(self, True)
    my.is_spider(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 2)
    my.monst_size(self, my.MONST_SIZE_GIANT)
    my.move_speed(self, 200)
    my.noise_decibels_hearing(self, 0)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d6")
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina(self, 100)
    my.stat_con(self, 12)
    my.stat_def(self, 14)
    my.stat_dex(self, 16)
    my.stat_luck(self, 10)
    my.stat_str(self, 14)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "bites")
    my.text_long_description(self, "An enormous spider. Ichor drips from its glistening fangs. Watch out for its web and poisonous bite.")
    my.text_short_description(self, "A giant spider.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 150
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="gray40",
            tile="spider_giant.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="gray40",
            tile="spider_giant.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="gray40",
            tile="spider_giant.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="gray40",
            tile="spider_giant.4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="gray40",
            tile="spider_giant.5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="S", ascii_bg_col_name="", ascii_fg_col_name="gray20",
            tile="spider_giant.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="spider_giant", text_long_name="giant spider")


init()
