import my
import tp


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_a")


def tp_init(name):
    self = tp.Tp(name)
    my.damage_cold_chance_d1000(self, 1000)
    my.damage_cold_dice(self, "1d6")  # This is the damage when the monst fires
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.is_explosion(self, True)
    my.is_cold(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.noise_on_born(self, 70)
    my.on_death_do(self, "me.on_death()")
    my.temperature(self, 100)
    my.z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    my.tile(self, tile="nothing")
    delay = 25
    my.tile(self, "explosion_fire.1", delay_ms=delay)
    my.tile(self, "explosion_fire.2", delay_ms=delay)
    my.tile(self, "explosion_fire.3", delay_ms=delay)
    my.tile(self,
            "explosion_fire.4",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="explosion_cold")


init()
