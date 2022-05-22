import my
import tp


def on_born(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_a")


def tp_init(name):
    self = tp.Tp(name)
    my.gfx_ascii_mode_shown(self, True)
    my.damage_cold_chance_d1000(self, 0, 1000)
    my.damage_cold_dice(self, "1d6")  # This is the damage when the monst fires
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_cold(self, True)
    my.is_explosion(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.noise_on_born(self, 70)
    my.on_born_do(self, "me.on_born()")
    my.temperature(self, 100)
    my.z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_fg_col_name="",
            tile="nothing")
    delay = 25
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_fg_col_name="",
            tile="explosion_fire.1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_fg_col_name="",
            tile="explosion_fire.2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_fg_col_name="",
            tile="explosion_fire.3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_fg_col_name="",
            tile="explosion_fire.4",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="explosion_cold")


init()
