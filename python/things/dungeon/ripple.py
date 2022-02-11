import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_is_removeable_if_out_of_slots(self, True)
    my.tp_set_is_ripple(self, True)
    my.tp_set_is_tmp_thing(self, True)
    my.tp_set_noise_on_born(self, 50)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "An ominous ripple.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 25
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".7", delay_ms=delay)
    my.tp_set_tile(self,
        tile=name + ".8",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="ripple1")
    tp_init(name="ripple2")


init()
