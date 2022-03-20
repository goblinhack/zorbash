import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.collision_hit_priority(self, 0)
    my.collision_hit_priority(self, 6)
    my.environ_avoids_fire(self, 100)
    my.gold_value_dice(self, "600")
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_flat(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_map_beast(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "This magical map can show you the position of all monsters on the level as they move around.")
    my.noise_on_dropping(self, 1)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "An aged beast map.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="map_beast", text_name="beast map", short_text_name="beast map")


init()
