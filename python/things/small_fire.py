import builtins
import zx
import tp

def spawn(me, x, y):
    zx.level_spawn_fire_around_thing(me, "fire")

def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_melee_dice("1d3+1")
    mytp.set_gfx_animated(True)
    mytp.set_gfx_flickers(True)
    mytp.set_gfx_on_fire_anim(True)
    mytp.set_gfx_oversized_but_sitting_on_the_ground(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_hates_water(100)
    mytp.set_health_initial_dice("5")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_active(True)
    mytp.set_is_fire(True)
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_is_moveable(True)
    mytp.set_lifespan_dice("1d10+10")
    mytp.set_light_color("yellow")
    mytp.set_light_strength(3)
    mytp.set_on_idle_dice("1d30+20:small_fire.spawn()")
    mytp.set_text_a_or_an("")
    mytp.set_text_description("Fire embers.")
    mytp.set_text_hits("burns")
    mytp.set_tick_rate_tenths(3)
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_INFRONT)

    delay = 75
    mytp.set_tile(tile=name + ".1", delay_ms=delay)
    mytp.set_tile(tile=name + ".2", delay_ms=delay)
    mytp.set_tile(tile=name + ".3", delay_ms=delay)
    mytp.set_tile(tile=name + ".4", delay_ms=delay)
    mytp.set_tile(tile=name + ".5", delay_ms=delay)
    mytp.set_tile(tile=name + ".6", delay_ms=delay)
    mytp.set_tile(tile=name + ".7", delay_ms=delay)
    mytp.set_tile(tile=name + ".8", delay_ms=delay)
    mytp.set_tile(tile=name + ".9", delay_ms=delay)
    mytp.set_tile(tile=name + ".10", delay_ms=delay)
    mytp.set_tile(tile=name + ".11", delay_ms=delay)
    mytp.set_tile(tile=name + ".12", delay_ms=delay)
    mytp.set_tile(tile=name + ".13", delay_ms=delay)
    mytp.set_tile(tile=name + ".14", delay_ms=delay)
    mytp.set_tile(tile=name + ".15", delay_ms=delay)
    mytp.set_tile(tile=name + ".16", delay_ms=delay)
    mytp.update()

def init():
    tp_init(name="small_fire", text_name="burning fire")

init()
