import zx
import tp


def potion_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_has_capacity(20)
    x.set_is_bag(True)
    x.set_is_collectable(True)
    x.set_is_combustible(True)
    x.set_is_droppable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_item_class_a(True)
    x.set_is_item_not_stackable(True)
    x.set_is_light_strength(2)
    x.set_is_movable(True)
    x.set_is_shown_on_monstbar(True)
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=brown$A small brown bag")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name, delay_ms=1000)

    x.update()

def init():
    potion_init(name="bag_small", text_name="small bag")

init()
