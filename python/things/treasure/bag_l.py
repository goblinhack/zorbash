import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_capacity_height(mytp, 12)
    my.tp_set_capacity_width(mytp, 12)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bag_item_container(mytp, True)
    my.tp_set_is_bag_item_not_stackable(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_bag(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_carrier_of_treasure_class_a(mytp, True)
    my.tp_set_is_carrier_of_treasure_class_b(mytp, True)
    my.tp_set_is_carrier_of_weapon_class_a(mytp, True)
    my.tp_set_is_carrier_of_weapon_class_b(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item_carrier(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_organic(mytp, True)
    my.tp_set_is_treasure_class_a(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_item_height(mytp, 8)
    my.tp_set_item_width(mytp, 8)
    my.tp_set_long_text_description(mytp, "A large leathery brown bag.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 1)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_drop_all_items(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A large brown bag.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile="bag_l", delay_ms=1000)
    my.tp_update(mytp, )


def init():
    tp_init(name="bag_l", text_name="large bag")


init()
