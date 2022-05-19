import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.gfx_animated(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_show_outlined(self, True)
    my.is_able_to_fall(self, True)
    my.is_loggable(self, True)
    my.is_red_splatter(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "An artwork comprised mainly of blood.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 5
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".14",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="red_splatter", text_name="blood splatter")


init()
