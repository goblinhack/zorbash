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
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 100)
    my.tp_set_ai_resent_count(self, 100)
    my.tp_set_attack_humanoid(self, True)
    my.tp_set_attack_meat(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_damage_natural_attack_type(self, "claws")
    my.tp_set_damage_natural_dice(self, "1d6+2")
    my.tp_set_distance_jump(self, 2)
    my.tp_set_distance_vision(self, 10)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "attack_claws")
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "7d8+20")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_able_to_jump_attack_chance_d1000(self, 100)
    my.tp_set_is_able_to_jump_attack(self, True)
    my.tp_set_is_able_to_jump_escape(self, True)
    my.tp_set_is_able_to_jump_on_low_hp_chance_d1000(self, 500)
    my.tp_set_is_able_to_jump(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_immune_to_necrosis(self, True)
    my.tp_set_is_immune_to_poison(self, True)
    my.tp_set_is_immune_to_water(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_monst_class_c(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_stone(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_toughness_very_hard(self, True)
    my.tp_set_is_undead(self, True)
    my.tp_set_is_very_heavy(self, True)
    my.tp_set_long_text_description(self, "These monstrous creatures guard the dungeon from the likes of you. This particular gargoyle has been unleashed, to roam the dungeon with impunitiy.")
    my.tp_set_monst_size(self, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(self, 60)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(self, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stat_att_mod(self, 4)
    my.tp_set_stat_con(self, 16)
    my.tp_set_stat_def(self, 17)
    my.tp_set_stat_dex(self, 11)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 15)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A fearsome gargoyle.")
    my.tp_set_text_hits(self, "slashes")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 300
    my.tp_set_tile(self, "gargoyle.moving.1", delay_ms=delay)
    my.tp_set_tile(self, "gargoyle.moving.2", delay_ms=delay)
    my.tp_set_tile(self, "gargoyle.moving.3", delay_ms=delay)
    my.tp_set_tile(self, "gargoyle.moving.4", delay_ms=delay)
    my.tp_set_tile(self, "gargoyle.moving.5", delay_ms=delay)
    my.tp_set_tile(self, "gargoyle.moving.6", delay_ms=delay)
    my.tp_set_tile(self, "gargoyle.moving.7", delay_ms=delay)
    my.tp_set_tile(self, "gargoyle.moving.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="gargoyle_moving", text_name="gargoyle, unleashed")


init()
