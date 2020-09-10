import zx
import tp


def init1(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_animated_can_vflip(True)
    x.set_gfx_attack_anim(True)
    x.set_gfx_dead_anim(False)
    x.set_gfx_show_outlined(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_movable(True)
    x.set_is_removable_if_out_of_slots(True)
    x.set_lifespan_dice("1d30+10")
    x.set_text_a_or_an("a");
    x.set_text_description("A splatter of slime stuff. Don't look closely")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 10
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay)
    x.set_tile(tile=name + ".9", delay_ms=delay)
    x.set_tile(tile=name + ".10", delay_ms=delay)
    x.set_tile(tile=name + ".11", delay_ms=delay)
    x.set_tile(tile=name + ".12", delay_ms=delay)
    x.set_tile(tile=name + ".13", delay_ms=delay)
    x.set_tile(tile=name + ".14", delay_ms=delay, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.update()


def init():
    init1(name="attack_slime", text_name="attack_slime attack")

init()
