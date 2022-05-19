import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated_can_vflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_attack_anim(self, True)
    my.gfx_show_outlined(self, True)
    my.is_moveable(self, True)
    my.is_pink_splatter(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Splat attack.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 5
    my.tile(self,
            tile="pink_splatter.1",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.2",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.3",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.4",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.5",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.6",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.7",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.8",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.9",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.10",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.11",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.12",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.13",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay)
    my.tile(self,
            tile="pink_splatter.14",
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="pink_splatter", text_name="pink slime splatter")


init()
