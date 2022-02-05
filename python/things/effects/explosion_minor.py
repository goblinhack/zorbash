import my
import tp


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_a")


def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_damage_fire_chance_d1000(1000)
    mytp.set_damage_fire_dice("1d6")  # This is the damage when the monst fires
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_explosion(True)
    mytp.set_is_fire(True)
    mytp.set_is_floating(True)
    mytp.set_is_loggable(True)
    mytp.set_is_tickable(True)
    mytp.set_is_tickable(True)  # So it can interact with fire
    mytp.set_noise_decibels_on_born(70)
    mytp.set_on_death_do("me.on_death()")
    mytp.set_z_depth(my.MAP_DEPTH_EXPLOSION_MINOR)
    mytp.set_z_prio(my.MAP_PRIO_IN_FRONT)

    mytp.set_tile(tile="nothing")
    delay = 25
    mytp.set_tile("explosion_minor.1", delay_ms=delay)
    mytp.set_tile("explosion_minor.2", delay_ms=delay)
    mytp.set_tile("explosion_minor.3", delay_ms=delay)
    mytp.set_tile(
        "explosion_minor.4",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    mytp.update()


def init():
    tp_init(name="explosion_minor")


init()
