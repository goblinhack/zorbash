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


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(mytp, 100)
    my.tp_set_ai_resent_count(mytp, 10)
    my.tp_set_attack_eater(mytp, True)
    my.tp_set_attack_lunge(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_natural_attack_chance_d1000(mytp, 900)
    my.tp_set_damage_natural_attack_type(mytp, "gore")
    my.tp_set_damage_natural_dice(mytp, "1d8+3")
    my.tp_set_damage_poison_chance_d1000(mytp, 100)
    my.tp_set_damage_poison_dice(mytp, "2d8+2")
    my.tp_set_damage_received_doubled_from_fire(mytp, True)
    my.tp_set_distance_avoid(mytp, 5)
    my.tp_set_distance_jump(mytp, 2)
    my.tp_set_distance_mob_max(mytp, 5)
    my.tp_set_distance_vision(mytp, 5)
    my.tp_set_environ_avoids_fire(mytp, 10)
    my.tp_set_environ_avoids_poison(mytp, 100)
    my.tp_set_environ_avoids_water(mytp, 100)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "attack_claws")
    my.tp_set_gfx_bounce_on_move(mytp, True)
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "4d15+4")
    my.tp_set_hunger_clock_tick_frequency(mytp, 50)
    my.tp_set_hunger_health_pct(mytp, 95)
    my.tp_set_hunger_is_insatiable(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_able_to_fire_at(mytp, True)
    my.tp_set_is_able_to_jump_attack_chance_d1000(mytp, 800)
    my.tp_set_is_able_to_jump_attack(mytp, True)
    my.tp_set_is_able_to_jump_onto_chance_d1000(mytp, 100)
    my.tp_set_is_able_to_jump_onto(mytp, True)
    my.tp_set_is_able_to_jump_randomly_chance_d1000(mytp, 20)
    my.tp_set_is_able_to_jump(mytp, True)
    my.tp_set_is_able_to_jump_without_tiring(mytp, True)
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_able_to_tire(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_bleeder(mytp, True)
    my.tp_set_is_breather(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_food_eater(mytp, True)
    my.tp_set_is_green_blooded(mytp, True)
    my.tp_set_is_heavy(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_immune_to_spiderwebs(mytp, True)
    my.tp_set_is_living(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_meat_eater(mytp, True)
    my.tp_set_is_monst_class_b(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_poisonous_danger_level(mytp, 2)  # danger level
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_spider(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_long_text_description(mytp, "An enormous spider. Ichor drips from its glistening fangs. Watch out for its web and poisonous bite.")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_GIANT)
    my.tp_set_noise_decibels_hearing(mytp, 0)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_nutrition_dice(mytp, "1d6")
    my.tp_set_on_born_do(mytp, "me.on_born()")
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_firing_at_something_do(mytp, "me.on_firing_at_something()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(mytp, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(mytp, "me.on_you_natural_attack()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stamina(mytp, 100)
    my.tp_set_stat_con(mytp, 12)
    my.tp_set_stat_def(mytp, 14)
    my.tp_set_stat_dex(mytp, 16)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 14)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A giant spider.")
    my.tp_set_text_hits(mytp, "bites")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 150
    my.tp_set_tile(mytp, "spider_giant.1", delay_ms=delay)
    my.tp_set_tile(mytp, "spider_giant.2", delay_ms=delay)
    my.tp_set_tile(mytp, "spider_giant.3", delay_ms=delay)
    my.tp_set_tile(mytp, "spider_giant.4", delay_ms=delay)
    my.tp_set_tile(mytp, "spider_giant.5", delay_ms=delay)
    my.tp_set_tile(mytp, "spider_giant.dead", is_dead=True, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="spider_giant", text_name="giant spider")


init()
