import my
import tp


def spawn(me, x, y):
    my.level_spawn_fire_around_thing(me, "fire")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.collision_check(self, True)
    my.damage_fire_chance_d1000(self, 0, 1000)
    my.damage_fire_dice(self, "1d3+1")
    my.damage_nat_attack_type(self, "burn")
    my.environ_avoids_water(self, 100)
    my.gfx_animated(self, True)
    my.gfx_flickers(self, True)
    my.gfx_on_fire_anim(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.health_initial_dice(self, "5")
    my.is_able_to_fall(self, True)
    my.is_dead_on_falling(self, True)
    my.is_fire(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_tickable(self, True)
    my.lifespan_dice(self, "1d10+10")
    my.light_color(self, "yellow")
    my.light_dist(self, 3)
    my.on_idle_tick_freq_dice(self, "1d10+10:me.spawn()")
    my.temperature(self, 100)
    my.text_a_or_an(self, "")
    my.text_description(self, "Fire embers.")
    my.text_hits(self, "burns")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    delay = 75
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".15", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".16", delay_ms=delay)
    my.tp_update(self)


def init():
    tp_init(name="small_fire", text_name="burning fire")


init()
