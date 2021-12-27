import my
import tp


def spawn(me, x, y):
    my.topcon("fire spawn")
    my.level_spawn_fire_around_thing(me, "small_fire")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_collision_check(True)
    mytp.set_damage_fire_chance_d1000(1000)
    mytp.set_damage_fire_dice("1d6+1")
    mytp.set_environ_avoids_water(100)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_flickers(True)
    mytp.set_gfx_on_fire_anim(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("10")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_always_hit(True)
    mytp.set_is_fire(True)
    mytp.set_is_hazard(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_is_tickable(True)
    mytp.set_lifespan_dice("1d20+20")
    mytp.set_light_color("yellow")
    mytp.set_light_strength(3)
    mytp.set_on_idle_tick_frequency_dice("1d10+10:me.spawn()")
    mytp.set_text_a_or_an("")
    mytp.set_text_description("Fire.")
    mytp.set_text_hits("burns")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_IN_FRONT)

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
    tp_init(name="fire", text_name="fire")


init()
