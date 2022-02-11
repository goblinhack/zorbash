import my
import tp


def spawn(me, x, y):
    my.level_spawn_fire_around_thing(me, "fire")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_collision_check(self, True)
    my.tp_set_damage_fire_chance_d1000(self, 1000)
    my.tp_set_damage_fire_dice(self, "1d3+1")
    my.tp_set_damage_natural_attack_type(self, "burn")
    my.tp_set_environ_avoids_water(self, 100)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_flickers(self, True)
    my.tp_set_gfx_on_fire_anim(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "5")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_fire(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_lifespan_dice(self, "1d10+10")
    my.tp_set_light_color(self, "yellow")
    my.tp_set_light_power(self, 3)
    my.tp_set_on_idle_tick_frequency_dice(self, "1d10+10:me.spawn()")
    my.tp_set_temperature(self, 100)
    my.tp_set_text_a_or_an(self, "")
    my.tp_set_text_description(self, "Fire embers.")
    my.tp_set_text_hits(self, "burns")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)

    delay = 75
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".7", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".8", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".9", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".10", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".11", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".12", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".13", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".14", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".15", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".16", delay_ms=delay)
    my.tp_update(self)


def init():
    tp_init(name="small_fire", text_name="burning fire")


init()
