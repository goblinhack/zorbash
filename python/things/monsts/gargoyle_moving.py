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
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")
    my.thing_polymorph(me, "gargoyle_moving")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_aggression_level_pct(100)
    mytp.set_ai_resent_count(100)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_meat(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_damage_natural_attack_type("claws")
    mytp.set_damage_natural_dice("1d6+2")
    mytp.set_is_moveable(True)
    mytp.set_is_heavy(True)
    mytp.set_distance_vision(10)
    mytp.set_is_shovable(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_claws")
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("7d8+20")
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_hittable(True)
    mytp.set_is_immune_to_poison(True)
    mytp.set_is_immune_to_water(True)
    mytp.set_is_immune_to_fire(True)
    mytp.set_is_immune_to_necrosis(True)
    mytp.set_is_immune_to_cold(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_loggable(True)
    mytp.set_is_monst_class_c(True)
    mytp.set_is_monst(True)
    mytp.set_is_tickable(True)
    mytp.set_is_toughness_very_tough(True)
    mytp.set_is_undead(True)
    mytp.set_long_text_description("These monstrous creatures guard the dungeon from the likes of you. This particular gargoyle has been unleashed, to roam the dungeon with impunitiy.")
    mytp.set_monst_size(my.MONST_SIZE_NORMAL)
    mytp.set_noise_decibels_hearing(50)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("me.on_death()")
    mytp.set_on_firing_at_something_do("me.on_firing_at_something()")
    mytp.set_on_you_are_hit_but_still_alive_do("me.on_you_are_hit_but_still_alive()")
    mytp.set_on_you_miss_do("me.on_you_miss_do()")
    mytp.set_on_you_natural_attack_do("me.on_you_natural_attack()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stat_att_mod(4)
    mytp.set_stat_con(16)
    mytp.set_stat_def(17)
    mytp.set_stat_dex(11)
    mytp.set_stat_str(15)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A fearsome gargoyle.")
    mytp.set_text_hits("slashes")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    delay = 300
    mytp.set_tile("gargoyle.moving.1", delay_ms=delay)
    mytp.set_tile("gargoyle.moving.2", delay_ms=delay)
    mytp.set_tile("gargoyle.moving.3", delay_ms=delay)
    mytp.set_tile("gargoyle.moving.4", delay_ms=delay)
    mytp.set_tile("gargoyle.moving.5", delay_ms=delay)
    mytp.set_tile("gargoyle.moving.6", delay_ms=delay)
    mytp.set_tile("gargoyle.moving.7", delay_ms=delay)
    mytp.set_tile("gargoyle.dead", is_dead=True, delay_ms=delay)

    mytp.update()


def init():
    tp_init(name="gargoyle_moving", text_name="gargoyle, unleashed")


init()
