import my
import tp


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_e")
    my.if_matches_then_dead(me, "is_floor", x, y)
    my.if_matches_then_dead(me, "is_corridor", x, y)
    my.if_matches_then_dead(me, "is_dirt", x, y)
    my.level_place_at(me, "chasm1", x, y)


def tp_init(name):
    mytp = tp.Tp(name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_explosion(mytp, True)
    my.tp_set_is_floating(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_noise_on_born(mytp, 100)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_IN_FRONT)

    delay = 50
    my.tp_set_tile(mytp, tile="nothing")
    my.tp_set_tile(mytp, "explosion_minor.1", delay_ms=delay)
    my.tp_set_tile(mytp, "explosion_minor.2", delay_ms=delay)
    my.tp_set_tile(mytp, "explosion_minor.3", delay_ms=delay)
    mytp.set_tile(
        "explosion_minor.4",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(mytp, )


def init():
    tp_init(name="explosion_destroy_floor")


init()
