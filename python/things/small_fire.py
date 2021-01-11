import builtins
import zx
import tp

def spawn(me, x, y):
    zx.tp_spawn_fire(me, "fire")

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(100)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_on_fire_anim(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_fire(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(1)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_movable(True)
    x.set_is_water_hater(100)
    x.set_lifespan_dice("1d30+10")
    x.set_light_color("yellow")
    x.set_on_idle_dice_do("1d10+20:small_fire.spawn()")
    x.set_stats_attack_dice("1d3+1")
    x.set_stats_health_initial_dice("5")
    x.set_text_a_or_an("");
    x.set_text_description("Fire embers")
    x.set_text_hits("burns");
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_INFRONT)

    delay = 75
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay)
    x.set_tile(tile=name + ".9", delay_ms=delay)
    x.set_tile(tile=name + ".10", delay_ms=delay)
    x.set_tile(tile=name + ".11", delay_ms=delay)
    x.set_tile(tile=name + ".12", delay_ms=delay)
    x.set_tile(tile=name + ".13", delay_ms=delay)
    x.set_tile(tile=name + ".14", delay_ms=delay)
    x.set_tile(tile=name + ".15", delay_ms=delay)
    x.set_tile(tile=name + ".16", delay_ms=delay)
    x.update()

def init():
    tp_init(name="small_fire", text_name="burning fire")

init()
