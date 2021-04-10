import zx
import tp

def on_death(me, x, y):
    zx.if_matches_then_kill(me, "is_floor", x, y)
    zx.if_matches_then_kill(me, "is_corridor", x, y)
    zx.if_matches_then_kill(me, "is_dirt", x, y)
    zx.tp_place(me, "chasm1", x, y)

def tp_init(name):
    x = tp.Tp(name)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(False)
    x.set_is_floating(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_on_death_do("wand_descent_effect.on_death()")
    x.set_z_depth(zx.MAP_DEPTH_EXPLOSION_MINOR)
    x.set_z_prio(zx.MAP_PRIO_INFRONT)

    x.set_tile(tile="nothing")
    x.set_tile("blue_explosion_effect.1", delay_ms=50)
    x.set_tile("blue_explosion_effect.2", delay_ms=50)
    x.set_tile("blue_explosion_effect.3", delay_ms=50)
    x.set_tile("blue_explosion_effect.4", delay_ms=50, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="wand_descent_effect")

init()
