import my
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_hit_priority(0)
    mytp.set_environ_avoids_fire(100)
    mytp.set_gold_value_dice("600")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_beast_map(True)
    mytp.set_is_burnable(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure_type(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("This magical map can show you the position of all monsters on the level as they move around.")
    mytp.set_normal_placement_rules(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("An aged beast map.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name, delay_ms=100)

    mytp.update()


def init():
    tp_init(name="beast_map", text_name="beast map", short_text_name="beast map")


init()
