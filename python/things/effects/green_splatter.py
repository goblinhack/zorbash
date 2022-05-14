import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated_can_vflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_attack_anim(self, True)
    my.gfx_show_outlined(self, True)
    my.is_green_splatter(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Splat attack.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 5
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.12", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.13", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="green", ascii_fg_col_name="",
            tile="green_splatter.14",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="green_splatter", text_name="green slime splatter")


init()
