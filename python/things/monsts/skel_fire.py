import my
import tp


def on_you_natural_attack(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_miss_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    if my.non_pcg_randint(1, 2) == 1:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones1"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones1")
    else:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones2"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones2")


def on_firing_at_something(me, target, x, y):  # Return True on doing an action
    if my.pcg_randint(1, 100) < 10:
        my.thing_fire_at(me, "projectile_fire", target)
        my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_b")
        return True
    return False


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 100)
    my.tp_set_ai_resent_count(self, 10)
    my.tp_set_ai_shove_chance_d1000(self, 200)
    my.tp_set_ai_wanderer(self, True)
    my.tp_set_attack_humanoid(self, True)
    my.tp_set_attack_lunge(self, True)
    my.tp_set_attack_meat(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 20)
    my.tp_set_damage_natural_attack_type(self, "claw")
    my.tp_set_damage_natural_dice(self, "1d3")
    my.tp_set_damage_received_doubled_from_water(self, True)
    my.tp_set_distance_avoid(self, 4)
    my.tp_set_distance_mob_max(self, 6)
    my.tp_set_distance_vision(self, 7)
    my.tp_set_distance_vision(self, 8)
    my.tp_set_environ_avoids_water(self, 100)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "attack_claws")
    my.tp_set_gfx_bounce_on_move(self, True)
    my.tp_set_gfx_glows(self, True)
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "2")
    my.tp_set_hunger_clock_tick_frequency(self, 50)
    my.tp_set_hunger_health_pct(self, 95)
    my.tp_set_hunger_is_insatiable(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_able_to_fire_at(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_able_to_shove(self, True)
    my.tp_set_is_able_to_use_weapons(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_bony(self, True)
    my.tp_set_is_carrier_of_treasure_class_a(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_immune_to_acid(self, True)
    my.tp_set_is_immune_to_cold(self, True)
    my.tp_set_is_immune_to_necrosis(self, True)
    my.tp_set_is_immune_to_poison(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_minion(self, True)
    my.tp_set_is_monst_class_b(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_red_blood_eater(self, True)
    my.tp_set_is_resurrectable(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_undead(self, True)
    my.tp_set_light_color(self, "yellow")
    my.tp_set_light_power(self, 2)
    my.tp_set_long_text_description(self, "A collection of tortured burning bones, driven to wander the dungeon forever. Or at least until you release them. Such creatures abhor the cleansing powers of water.")
    my.tp_set_monst_size(self, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(self, 50)
    my.tp_set_noise_on_moving_or_being_carried(self, 25)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(self, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_resurrect_dice(self, "1d20+30")
    my.tp_set_stat_con(self, 9)
    my.tp_set_stat_def(self, 13)
    my.tp_set_stat_dex(self, 10)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 10)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "The burning bones of one surprised to be moving again and literally on fire.")
    my.tp_set_text_hits(self, "claws")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 200
    my.tp_set_tile(self, "skel_fire.1", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_left=True, is_moving=True, delay_ms=delay)

    my.tp_set_tile(self, "skel_fire.1", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_up=True, is_moving=True, delay_ms=delay)

    my.tp_set_tile(self, "skel_fire.1", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_down=True, is_moving=True, delay_ms=delay)

    my.tp_set_tile(self, "skel_fire.1", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_right=True, is_moving=True, delay_ms=delay)

    my.tp_set_tile(self, "skel_fire.1", is_dir_left=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_left=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_left=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_left=True, delay_ms=delay)

    my.tp_set_tile(self, "skel_fire.1", is_dir_up=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_up=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_up=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_up=True, delay_ms=delay)

    my.tp_set_tile(self, "skel_fire.1", is_dir_down=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_down=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_down=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_down=True, delay_ms=delay)

    my.tp_set_tile(self, "skel_fire.1", is_dir_right=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_right=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_right=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_right=True, delay_ms=delay)

    my.tp_set_tile(self, "skel_fire.1", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4", is_dir_none=True, delay_ms=delay)

    delay = 20
    my.tp_set_tile(self, "skel_fire.1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.4.dead", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    my.tp_set_tile(self, "skel_fire.4.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.3.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self, "skel_fire.2.dead", is_resurrecting=True, delay_ms=delay)
    self.set_tile(
        "skel_fire.1.dead",
        is_resurrecting=True,
        is_end_of_anim=True,
        is_alive_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="skel_fire", text_name="burning skeleton")


init()
