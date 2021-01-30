import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_is_attackable_by_player(True)
    x.set_bag_height(6)
    x.set_bag_item_height(4)
    x.set_bag_item_width(4)
    x.set_bag_width(8)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_bag(True)
    x.set_is_burnable(True)
    x.set_is_collectable(True)
    x.set_is_combustible(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_droppable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_item_not_stackable(True)
    x.set_is_moveable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_treasure_class_a(True)
    x.set_long_text_description("A very small leathery brown bag.")
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("a");
    x.set_text_description("A small brown bag")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile="bag", delay_ms=1000)
    x.update()

def init():
    tp_init(name="bag_small", text_name="wee bag")

init()
