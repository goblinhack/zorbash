import zx
import tp
import random

def on_bite(me, x, y):
    sound = "growl{}".format(random.randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    sound = "hiss{}".format(random.randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_miss(me, hitter, x, y):
    sound = "hiss{}".format(random.randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_death(me, x, y):
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, "monst_death1"):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, "monst_death1")

def on_tick(me, x, y): # Return True on doing an action
    zx.topcon("tic")
    return False

def on_firing_at_something(me, target, x, y): # Return True on doing an action
    if random.randint(1, 10) < 3:
        zx.thing_fire_at(me, "laser_energy", target)
        return True
    return False


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_avoid_distance(4)
    x.set_ai_scent_distance(14)
    x.set_ai_vision_distance(8)
    x.set_attack_lunge(True)
    x.set_attack_meat(True)
    x.set_hates_fire(100)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_damage_melee_dice("2d6")
    x.set_gfx_anim_attack("attack_claws")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_health_bar_shown(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_hunger_pct(95)
    x.set_health_initial_dice("100+10d8")
    x.set_is_able_to_change_levels(True)
    x.set_is_able_to_fall(False)
    x.set_is_able_to_fire_at(True)
    x.set_is_active(True)
    x.set_is_attackable_by_player(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_fearless(True)
    x.set_is_floating(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_intelligent(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_moveable(True)
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_undead(True)
    x.set_attack_humanoid(True)
    x.set_attack_living(False)
    x.set_long_text_description("A floating mass of tentacles and eyeballs. These creatures are often employed to monitor the dark and dank dungeons with their impressive vision. Beware their lightning gaze...")
    x.set_monst_size(zx.MONST_SIZE_NORMAL)
    x.set_move_speed_ms(150)
    x.set_normal_placement_rules(True)
    x.set_on_bite_do("tentacleye.on_bite()")
    x.set_on_death_do("tentacleye.on_death()")
    x.set_on_firing_at_something_do("tentacleye.on_firing_at_something()")
    x.set_on_hit_do("tentacleye.on_hit()")
    x.set_on_miss_do("tentacleye.on_miss()")
    #x.set_on_tick_do("tentacleye.on_tick()")
    x.set_rarity(zx.RARITY_COMMON)
    x.set_stat_attack(10) # 10, means no bonus
    x.set_stat_constitution(10)
    x.set_stat_defence(14)
    x.set_stat_strength(12)
    x.set_text_a_or_an("a")
    x.set_text_description("A writhing mass of tentacles and eyeballs.")
    x.set_text_hits("slashes")
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 300
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.100", is_hp_25_percent=True, delay_ms=delay)

    x.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.dead", is_dead=True, is_end_of_anim=True)

    x.update()

def init():
    tp_init(name="tentacleye", text_name="lesser tentacleye")

init()

