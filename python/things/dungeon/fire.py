import my
import tp


def spawn(me, x, y):
    my.level_spawn_fire_around_thing(me, "small_fire")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_damage_fire_chance_d1000(mytp, 1000)
    my.tp_set_damage_fire_dice(mytp, "1d6+1")
    my.tp_set_damage_natural_attack_type(mytp, "fire")
    my.tp_set_environ_avoids_water(mytp, 100)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_flickers(mytp, True)
    my.tp_set_gfx_on_fire_anim(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "10")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_always_hit(mytp, True)
    my.tp_set_is_fire(mytp, True)
    my.tp_set_is_hazard(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_lifespan_dice(mytp, "1d20+20")
    my.tp_set_light_color(mytp, "yellow")
    my.tp_set_light_power(mytp, 3)
    my.tp_set_on_idle_tick_frequency_dice(mytp, "1d5+5:me.spawn()")
    my.tp_set_temperature(mytp, 100)
    my.tp_set_text_a_or_an(mytp, "")
    my.tp_set_text_description(mytp, "Fire.")
    my.tp_set_text_hits(mytp, "burns")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_IN_FRONT)

    delay = 75
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".7", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".8", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".9", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".10", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".11", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".12", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".13", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".14", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".15", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".16", delay_ms=delay)
    my.tp_update(mytp, )


def init():
    tp_init(name="fire", text_name="fire")


init()
