import my
import tp


def tp_init(name):
    self = tp.Tp(name, "ominous large ripple", "ominous large ripple")
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_ripple(self, True)
    my.is_tmp_thing(self, True)
    my.noise_on_born(self, 50)
    my.text_a_or_an(self, "a")
    my.text_short_description(self, "An ominous large ripple.")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 25
    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            tile=name + ".8",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="ripple_large1")
    tp_init(name="ripple_large2")


init()
