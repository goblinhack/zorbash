import my
import tp


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_a")


def tp_init(name):
    self = tp.Tp(name)
    my.tp_set_damage_fire_chance_d1000(self, 1000)
    my.tp_set_damage_fire_dice(self, "1d6")  # This is the damage when the monst fires
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_explosion(self, True)
    my.tp_set_is_fire(self, True)
    my.tp_set_is_floating(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_tickable(self, True)  # So it can interact with fire
    my.tp_set_noise_on_born(self, 70)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_temperature(self, 100)
    my.tp_set_z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)

    my.tp_set_tile(self, tile="nothing")
    delay = 25
    my.tp_set_tile(self, "explosion_minor.1", delay_ms=delay)
    my.tp_set_tile(self, "explosion_minor.2", delay_ms=delay)
    my.tp_set_tile(self, "explosion_minor.3", delay_ms=delay)
    self.set_tile(
        "explosion_minor.4",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="explosion_minor")


init()
