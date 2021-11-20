import my
import tp

def on_you_bite_attack(me, x, y):
    sound = "growl{}".format(my.non_pcg_randint(1, 10))
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)

def on_you_are_hit(me, hitter, real_hitter, x, y, crit, bite, poison, damage):
    sound = "hiss{}".format(my.non_pcg_randint(1, 10))
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)

def on_you_miss_do(me, hitter, x, y):
    sound = "hiss{}".format(my.non_pcg_randint(1, 10))
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)

def on_death(me, x, y):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")

def on_firing_at_something(me, target, x, y): # Return True on doing an action
    if my.pcg_randint(1, 10) < 3:
        my.thing_fire_at(me, "laser_energy", target)
        return True
    return False


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_aggression_level(100)
    mytp.set_ai_avoid_distance(4)
    mytp.set_ai_resent_count(100)
    mytp.set_ai_scent_distance(14)
    mytp.set_ai_unprovoked_attack_chance_d1000(900)
    mytp.set_ai_vision_distance(8)
    mytp.set_ai_vision_distance(9)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_eater(True)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_lunge(True)
    mytp.set_attack_meat(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_melee_dice("2d6")
    mytp.set_environ_damage_doubled_from_fire(True)
    mytp.set_environ_dislikes_fire(100)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_claws")
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_hunger_pct(95)
    mytp.set_health_initial_dice("10d10")
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_fire_at(True)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_able_to_tire(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_floating(True)
    mytp.set_is_hittable(True)
    mytp.set_is_hunger_insatiable(True)
    mytp.set_is_intelligent(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_meat(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_shovable(True)
    mytp.set_is_tickable(True)
    mytp.set_is_undead(True)
    mytp.set_long_text_description("A floating mass of tentacles and eyeballs. These creatures are often employed to monitor the dark and dank dungeons with their impressive vision. Beware their lightning gaze...")
    mytp.set_monst_size(my.MONST_SIZE_NORMAL)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("tentacleye.on_death()")
    mytp.set_on_firing_at_something_do("tentacleye.on_firing_at_something()")
    mytp.set_on_you_are_hit_do("tentacleye.on_you_are_hit()")
    mytp.set_on_you_bite_attack_do("tentacleye.on_you_bite_attack()")
    mytp.set_on_you_miss_do_do("tentacleye.on_you_miss_do()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stamina(100)
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(10)
    mytp.set_stat_defence(14)
    mytp.set_stat_strength(12)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A writhing mass of tentacles and eyeballs.")
    mytp.set_text_hits("slashes")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    delay = 300
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_25_percent=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.dead", is_dead=True, is_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="tentacleye", text_name="lesser tentacleye")

init()

