import zx
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_capacity_height(12)
    mytp.set_capacity_width(12)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(False)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item_container(True)
    mytp.set_is_bag_item_not_stackable(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_bag(True)
    mytp.set_is_burnable(True)
    mytp.set_is_carrier_of_treasure_class_a(True)
    mytp.set_is_carrier_of_treasure_class_b(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item_carrier(True)
    mytp.set_is_item(True)
    mytp.set_is_organic(True)
    mytp.set_is_organic(True)
    mytp.set_is_moveable(True)
    mytp.set_is_treasure_class_a(True)
    mytp.set_item_height(8)
    mytp.set_item_width(8)
    mytp.set_long_text_description("A large leathery brown bag.")
    mytp.set_normal_placement_rules(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A large brown bag.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile="bag_large", delay_ms=1000)
    mytp.update()

def init():
    tp_init(name="bag_large", text_name="huge sack")

init()
