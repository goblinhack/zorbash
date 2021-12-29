import my
import tp


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.topcon("The map glows. It seems full of knowledge.")


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_hit_priority(0)
    mytp.set_enchant_max(1)
    mytp.set_environ_avoids_fire(100)
    mytp.set_gold_value_dice("300")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_burnable(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure_map(True)
    mytp.set_is_treasure_type(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("When carrying this magical map you are able to see all the treasure, food and keys on the current level.")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_enchant_do("me.on_enchant()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("An aged treasure map.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name, delay_ms=100)

    mytp.update()


def init():
    tp_init(name="treasure_map", text_name="treasure map", short_text_name="treasure map")


init()
