import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated_can_vflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_attack_anim(self, True)
    my.gfx_show_outlined(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Claw attack.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 5
    my.tile(self, tile=name + ".1", delay_ms=delay, is_dir_left=True)
    my.tile(self, tile=name + ".2", delay_ms=delay, is_dir_left=True)
    my.tile(self, tile=name + ".3", delay_ms=delay, is_dir_left=True)
    my.tile(self, tile=name + ".4", delay_ms=delay, is_dir_left=True)
    my.tile(self, tile=name + ".5", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            tile=name + ".6",
            delay_ms=delay,
            is_dir_left=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self, tile=name + ".1", delay_ms=delay, is_dir_right=True)
    my.tile(self, tile=name + ".2", delay_ms=delay, is_dir_right=True)
    my.tile(self, tile=name + ".3", delay_ms=delay, is_dir_right=True)
    my.tile(self, tile=name + ".4", delay_ms=delay, is_dir_right=True)
    my.tile(self, tile=name + ".5", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            tile=name + ".6",
            delay_ms=delay,
            is_dir_right=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self, tile=name + ".1", delay_ms=delay, is_dir_up=True)
    my.tile(self, tile=name + ".2", delay_ms=delay, is_dir_up=True)
    my.tile(self, tile=name + ".3", delay_ms=delay, is_dir_up=True)
    my.tile(self, tile=name + ".4", delay_ms=delay, is_dir_up=True)
    my.tile(self, tile=name + ".5", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            tile=name + ".6",
            delay_ms=delay,
            is_dir_up=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self, tile=name + ".1", delay_ms=delay, is_dir_down=True)
    my.tile(self, tile=name + ".2", delay_ms=delay, is_dir_down=True)
    my.tile(self, tile=name + ".3", delay_ms=delay, is_dir_down=True)
    my.tile(self, tile=name + ".4", delay_ms=delay, is_dir_down=True)
    my.tile(self, tile=name + ".5", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            tile=name + ".6",
            delay_ms=delay,
            is_dir_down=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="attack_claws", text_name="claw attack")


init()