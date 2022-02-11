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
    my.tp_set_aggression_level_pct(mytp, 100)
    my.tp_set_ai_resent_count(mytp, 100)
    my.tp_set_attack_humanoid(mytp, True)
    my.tp_set_attack_meat(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_natural_attack_type(mytp, "claws")
    my.tp_set_damage_natural_dice(mytp, "1d6+2")
    my.tp_set_distance_jump(mytp, 2)
    my.tp_set_distance_vision(mytp, 10)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "attack_claws")
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "7d8+20")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_able_to_jump_attack_chance_d1000(mytp, 100)
    my.tp_set_is_able_to_jump_attack(mytp, True)
    my.tp_set_is_able_to_jump_escape(mytp, True)
    my.tp_set_is_able_to_jump_on_low_hp_chance_d1000(mytp, 500)
    my.tp_set_is_able_to_jump(mytp, True)
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_immune_to_necrosis(mytp, True)
    my.tp_set_is_immune_to_poison(mytp, True)
    my.tp_set_is_immune_to_water(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_monst_class_c(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_stone(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_is_toughness_very_hard(mytp, True)
    my.tp_set_is_undead(mytp, True)
    my.tp_set_is_very_heavy(mytp, True)
    my.tp_set_long_text_description(mytp, "These monstrous creatures guard the dungeon from the likes of you. This particular gargoyle has been unleashed, to roam the dungeon with impunitiy.")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(mytp, 60)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_firing_at_something_do(mytp, "me.on_firing_at_something()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(mytp, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(mytp, "me.on_you_natural_attack()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stat_att_mod(mytp, 4)
    my.tp_set_stat_con(mytp, 16)
    my.tp_set_stat_def(mytp, 17)
    my.tp_set_stat_dex(mytp, 11)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 15)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A fearsome gargoyle.")
    my.tp_set_text_hits(mytp, "slashes")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    delay = 300
    my.tp_set_tile(mytp, "gargoyle.moving.1", delay_ms=delay)
    my.tp_set_tile(mytp, "gargoyle.moving.2", delay_ms=delay)
    my.tp_set_tile(mytp, "gargoyle.moving.3", delay_ms=delay)
    my.tp_set_tile(mytp, "gargoyle.moving.4", delay_ms=delay)
    my.tp_set_tile(mytp, "gargoyle.moving.5", delay_ms=delay)
    my.tp_set_tile(mytp, "gargoyle.moving.6", delay_ms=delay)
    my.tp_set_tile(mytp, "gargoyle.moving.7", delay_ms=delay)
    my.tp_set_tile(mytp, "gargoyle.moving.dead", is_dead=True, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="gargoyle_moving", text_name="gargoyle, unleashed")


init()
