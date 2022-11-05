import my
import tp


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.capacity_height(self, 12)
    my.capacity_width(self, 12)
    my.collision_hit_priority(self, 6)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item_container(self, True)
    my.is_bag_item_not_stackable(self, True)
    my.is_bag_item(self, True)
    my.is_bag(self, True)
    my.is_biome_dungeon(self, True)
    my.is_carrier_of_treasure_class_a_d1000(self, 1000)
    my.is_carrier_of_treasure_class_b_d1000(self, 200)
    my.is_carrier_of_treasure_class_c_d1000(self, 50)
    my.is_carrier_of_weapon_class_a(self, 1000)
    my.is_carrier_of_weapon_class_b(self, 200)
    my.is_carrier_of_weapon_class_c(self, 50)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item_carrier(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_organic(self, True)
    my.is_throwable(self, True)
    my.is_treasure_class_a(self, True)
    my.is_treasure(self, True)
    my.item_height(self, 8)
    my.item_width(self, 8)
    my.noise_on_dropping(self, 1)
    my.normal_placement_rules(self, True)
    my.on_death_drop_all_items(self, True)
    my.text_a_or_an(self, "a")
    my.text_long_description(self, "A large leathery brown bag.")
    my.text_short_description(self, "A large brown bag.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="down_triangle", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="bag_l", delay_ms=1000)
    my.tp_update(self)


def init():
    tp_init(name="bag_l", text_long_name="large bag")


init()
