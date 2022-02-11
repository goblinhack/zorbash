import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_capacity_height(self, 12)
    my.tp_set_capacity_width(self, 12)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bag_item_container(self, True)
    my.tp_set_is_bag_item_not_stackable(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_bag(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_carrier_of_treasure_class_a(self, True)
    my.tp_set_is_carrier_of_treasure_class_b(self, True)
    my.tp_set_is_carrier_of_weapon_class_a(self, True)
    my.tp_set_is_carrier_of_weapon_class_b(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item_carrier(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_organic(self, True)
    my.tp_set_is_treasure_class_a(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_item_height(self, 8)
    my.tp_set_item_width(self, 8)
    my.tp_set_long_text_description(self, "A large leathery brown bag.")
    my.tp_set_noise_on_moving_or_being_carried(self, 1)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_drop_all_items(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A large brown bag.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile="bag_l", delay_ms=1000)
    my.tp_update(self)


def init():
    tp_init(name="bag_l", text_name="large bag")


init()
