import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated_can_vflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_attack_anim(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_tmp_thing(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Thy shining pointy mechanism of justice.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_EQUIP)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 10
    my.tp_set_tile(self, tile=name + "_left.1", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(self, tile=name + "_left.2", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(self, tile=name + "_left.3", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(self, tile=name + "_left.4", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(self, tile=name + "_left.5", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(self,
        tile=name + "_left.6",
        delay_ms=delay,
        is_dir_left=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    my.tp_set_tile(self, tile=name + "_left.1", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(self, tile=name + "_left.2", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(self, tile=name + "_left.3", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(self, tile=name + "_left.4", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(self, tile=name + "_left.5", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(self,
        tile=name + "_left.6",
        delay_ms=delay,
        is_dir_right=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    my.tp_set_tile(self, tile=name + "_up.1", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(self, tile=name + "_up.2", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(self, tile=name + "_up.3", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(self, tile=name + "_up.4", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(self, tile=name + "_up.5", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(self,
        tile=name + "_up.6",
        delay_ms=delay,
        is_dir_up=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    my.tp_set_tile(self, tile=name + "_up.1", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(self, tile=name + "_up.2", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(self, tile=name + "_up.3", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(self, tile=name + "_up.4", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(self, tile=name + "_up.5", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(self,
        tile=name + "_up.6",
        delay_ms=delay,
        is_dir_down=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="sword1_swing")


init()
