import my
import tp


def attack(me, thing):
    if my.thing_possible_to_attack(me, thing):
        if thing != me:
            my.thing_hit(me, thing)


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_d")

    target_x, target_y = my.thing_get_coords(me)
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            for thing in my.level_get_all(me, target_x + dx, target_y + dy):
                attack(me, thing)


def tp_init(name):
    self = tp.Tp(name, "huge explosion")
    my.tp_set_damage_fire_chance_d1000(self, 1000)
    my.tp_set_damage_fire_dice(self, "2d6")
    my.tp_set_damage_natural_attack_type(self, "blast")
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_is_explosion(self, True)
    my.tp_set_is_fire(self, True)
    my.tp_set_is_floating(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_tickable(self, True)  # So it can interact with fire
    my.tp_set_light_color(self, "yellow")
    my.tp_set_light_power(self, 4)
    my.tp_set_noise_on_born(self, 100)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_temperature(self, 100)
    my.tp_set_text_hits(self, "blasts")
    my.tp_set_z_depth(self, my.MAP_DEPTH_EXPLOSION_MAJOR)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)

    delay = 50
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
    self.set_tile(
        tile=name + ".16",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="explosion_major")


init()
