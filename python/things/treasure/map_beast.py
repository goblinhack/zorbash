import my
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_hit_priority(mytp, 0)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_environ_avoids_fire(mytp, 100)
    my.tp_set_gold_value_dice(mytp, "600")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_map_beast(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_treasure_class_c(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "This magical map can show you the position of all monsters on the level as they move around.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 15)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "An aged beast map.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name, delay_ms=100)

    my.tp_update(mytp, )


def init():
    tp_init(name="map_beast", text_name="beast map", short_text_name="beast map")


init()
