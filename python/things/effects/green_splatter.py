import my
import tp


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated_can_vflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_attack_anim(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_animation(self, True)
    my.is_green_splatter(self, True)
    my.is_moveable(self, True)
    my.is_only_one_per_tile(self, True)
    my.is_removable_if_out_of_slots(self, True)
    my.is_splatter(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_short(self, "Splat attack.")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_EFFECT)
    # end sort marker

    delay = 5
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            is_end_of_ascii_anim=True,
            is_dead_on_end_of_ascii_anim=True,
            tile="green_splatter.1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.12", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.13", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="middle_dot", ascii_bg_col_name="limegreen",
            tile="green_splatter.14",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="green_splatter", text_long_name="green slime splatter")


init()
