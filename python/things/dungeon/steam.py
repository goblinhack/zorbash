import my
import tp


def on_fall(me, x, y):
    my.thing_dead(me, "dissipated")


def tp_init(name):
    self = tp.Tp(name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_steam(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.lifespan_dice(self, "1d5+3")
    my.on_fall_do(self, "me.on_fall()")
    my.temperature(self, 100)
    my.text_a_or_an(self, "")
    my.text_short_description(self, "Scalding steam.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".15", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".16", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".17", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".18", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="=", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".19", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="steam")


init()
