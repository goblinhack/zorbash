import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_animated_can_vflip(True)
    x.set_gfx_attack_anim(True)
    x.set_gfx_dead_anim(False)
    x.set_gfx_show_outlined(True)
    x.set_is_able_to_fall(False)
    x.set_is_active(True) # for lifespan tick
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_moveable(True)
    x.set_is_removeable_if_out_of_slots(True)
    x.set_lifespan_dice("1d10+10")
    x.set_text_a_or_an("a")
    x.set_text_description("Splat attack.")
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 10
    x.set_tile("pink_splatter.1", delay_ms=delay)
    x.set_tile("pink_splatter.2", delay_ms=delay)
    x.set_tile("pink_splatter.3", delay_ms=delay)
    x.set_tile("pink_splatter.4", delay_ms=delay)
    x.set_tile("pink_splatter.5", delay_ms=delay)
    x.set_tile("pink_splatter.6", delay_ms=delay)
    x.set_tile("pink_splatter.7", delay_ms=delay)
    x.set_tile("pink_splatter.8", delay_ms=delay)
    x.set_tile("pink_splatter.9", delay_ms=delay)
    x.set_tile("pink_splatter.10", delay_ms=delay)
    x.set_tile("pink_splatter.11", delay_ms=delay)
    x.set_tile("pink_splatter.12", delay_ms=delay)
    x.set_tile("pink_splatter.13", delay_ms=delay)
    x.set_tile("pink_splatter.14", delay_ms=delay, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="pink_splatter", text_name="pink slime splatter")

init()
