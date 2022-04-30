import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated_can_vflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_attack_anim(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.text_a_or_an(self, "a")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 20
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.1", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.2", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.3", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.4", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.5", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            tile=name + "_left.6",
            delay_ms=delay,
            is_dir_left=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.1", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.2", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.3", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.4", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_left.5", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            tile=name + "_left.6",
            delay_ms=delay,
            is_dir_right=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.1", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.2", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.3", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.4", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.5", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            tile=name + "_up.6",
            delay_ms=delay,
            is_dir_up=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.1", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.2", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.3", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.4", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + "_up.5", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            tile=name + "_up.6",
            delay_ms=delay,
            is_dir_down=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="sword_plutonium_swing")


init()
