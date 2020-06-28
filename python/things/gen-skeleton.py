import zx
import tp

def spawn(me, x, y):
    zx.tp_spawn_next_to(me, "skeleton1")

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_acid_hater(True)
    x.set_is_active(True)
    x.set_is_attack_shove_chance_d1000(200)
    x.set_is_attackable(True)
    x.set_is_combustible(True)
    x.set_is_double_damage_from_fire(True)
    x.set_is_double_damage_from_water(True)
    x.set_is_fire_hater(100)
    x.set_is_generator(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(1)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_movement_blocking(True)
    x.set_is_resurrectable(True)
    x.set_is_shovable(True)
    x.set_is_water_hater(100)
    x.set_light_color("cyan")
    x.set_normal_placement_rules(True)
    x.set_on_idle_dice_do("1d1+2:gen-skeleton.spawn()")
    x.set_stats_defence(1)
    x.set_stats_health_initial(30)
    x.set_stats_strength(15)
    x.set_text_a_or_an("a");
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
    tp_init(name="gen-skeleton", text_name="pile of bones")

init()

