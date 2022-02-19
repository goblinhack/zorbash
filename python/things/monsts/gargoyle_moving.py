import my
import tp


def on_you_natural_attack(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


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
    my.aggression_level_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_natural_attack_type(self, "gore")
    my.damage_natural_dice(self, "1d6+2")
    my.distance_jump(self, 2)
    my.distance_vision(self, 10)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_health_bar_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.health_initial_dice(self, "7d8+20")
    my.is_able_to_fall(self, True)
    my.is_able_to_jump_attack_chance_d1000(self, 100)
    my.is_able_to_jump_attack(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump_on_low_hp_chance_d1000(self, 500)
    my.is_able_to_jump(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_corpse_on_death(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_water(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_c(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_shovable(self, True)
    my.is_stone(self, True)
    my.is_temperature_change_sensitive(self, True)
    my.is_tickable(self, True)
    my.is_toughness_very_hard(self, True)
    my.is_undead(self, True)
    my.is_very_heavy(self, True)
    my.long_text_description(self, "These monstrous creatures guard the dungeon from the likes of you. This particular gargoyle has been unleashed, to roam the dungeon with impunitiy.")
    my.monst_size(self, my.MONST_SIZE_NORMAL)
    my.move_speed(self, 200)
    my.noise_decibels_hearing(self, 60)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_miss_do(self, "me.on_you_miss_do()")
    my.on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_att_mod(self, 4)
    my.stat_con(self, 16)
    my.stat_def(self, 17)
    my.stat_dex(self, 11)
    my.stat_luck(self, 10)
    my.stat_str(self, 15)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A fearsome gargoyle.")
    my.text_hits(self, "slashes")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 300
    my.tile(self, "gargoyle.moving.1", delay_ms=delay)
    my.tile(self, "gargoyle.moving.2", delay_ms=delay)
    my.tile(self, "gargoyle.moving.3", delay_ms=delay)
    my.tile(self, "gargoyle.moving.4", delay_ms=delay)
    my.tile(self, "gargoyle.moving.5", delay_ms=delay)
    my.tile(self, "gargoyle.moving.6", delay_ms=delay)
    my.tile(self, "gargoyle.moving.7", delay_ms=delay)
    my.tile(self, "gargoyle.moving.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="gargoyle_moving", text_name="gargoyle, unleashed")


init()
