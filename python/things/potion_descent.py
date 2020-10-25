import zx
import tp


def potion_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_ascii_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_collectable(True)
    x.set_is_combustible(True)
    x.set_is_droppable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_item_class_b(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_movable(True)
    x.set_is_potion(True)
    x.set_is_shown_on_monstbar(True)
    x.set_is_throwable(True)
    x.set_is_usable(True)
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=cyan$A swirling milky blue potion of descent")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".1", delay_ms=1000)
    x.set_tile(tile=name + ".2", delay_ms=1000)
    x.set_tile(tile=name + ".3", delay_ms=1000)
    x.set_tile(tile=name + ".4", delay_ms=1000)
    x.set_tile(tile=name + ".5", delay_ms=1000)
    x.set_tile(tile=name + ".6", delay_ms=1000)

    x.update()

def init():
    potion_init(name="potion_blue", text_name="potion of descent")

init()
