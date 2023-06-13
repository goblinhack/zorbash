import my
import tp


def init1(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.collision_check(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated_can_vflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_attack_anim(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_only_one_per_tile(self, True)
    my.is_removable_if_out_of_slots(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_short(self, "Punch out.")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 20
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4",
            delay_ms=delay,
            is_dir_down=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4",
            delay_ms=delay,
            is_dir_up=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4",
            delay_ms=delay,
            is_dir_left=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4",
            delay_ms=delay,
            is_dir_right=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=delay, is_dir_none=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=delay, is_dir_none=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=delay, is_dir_none=True)
    my.tile(self,
            ascii_bg_char="", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4",
            delay_ms=delay,
            is_dir_none=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    init1(name="attack_punch", text_long_name="punch attack")


init()
