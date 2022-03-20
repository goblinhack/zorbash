import my
import tp


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_e")
    my.if_matches_then_dead(me, "is_floor", x, y)
    my.if_matches_then_dead(me, "is_corridor", x, y)
    my.if_matches_then_dead(me, "is_dirt", x, y)
    my.level_place_at(me, "chasm1", x, y)


def tp_init(name):
    self = tp.Tp(name)
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.is_explosion(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.noise_on_born(self, 100)
    my.on_death_do(self, "me.on_death()")
    my.z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    delay = 50
    my.tile(self, tile="nothing")
    my.tile(self, "explosion_fire.1", delay_ms=delay)
    my.tile(self, "explosion_fire.2", delay_ms=delay)
    my.tile(self, "explosion_fire.3", delay_ms=delay)
    my.tile(self,
        "explosion_fire.4",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="explosion_destroy_floor")


init()
