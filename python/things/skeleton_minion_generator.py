import zx
import tp
import random

def on_idle_dice(me, x, y):
    if random.randint(1, 100) < 10:
        zx.level_spawn_next_to(me, "skeleton_minion_fire")
    else:
        zx.level_spawn_next_to(me, "skeleton_minion")

def on_death(me, x, y):
    zx.level_spawn_at_thing(me, "generator_explosion")

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_attack_shove_chance_d1000(200)
    x.set_is_attackable_by_player(True)
    x.set_hates_acid(True)
    x.set_hates_fire(100)
    x.set_hates_water(100)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(5)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_damage_doubled_from_water(True)
    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_initial_dice("6d6")
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_always_hit(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_minion_generator(True)
    x.set_is_movement_blocking_soft(True)
    x.set_is_resurrectable(True)
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_light_color("cyan")
    x.set_light_strength(1)
    x.set_long_text_description("A grave portal from which the dead crawl out.")
    x.set_minion_limit(4)
    x.set_normal_placement_rules(True)
    x.set_on_death_do("ghost_minion_generator.on_death()")
    x.set_on_idle_dice("1d10+10:skeleton_minion_generator.on_idle_dice()")
    x.set_stat_attack(10) # 10, means no bonus
    x.set_stat_constitution(0)
    x.set_stat_defence(0)
    x.set_stat_strength(0)
    x.set_text_a_or_an("a")
    x.set_text_description("The dead rise again here.")
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="skeleton_minion_generator", text_name="pile of bones")

init()

