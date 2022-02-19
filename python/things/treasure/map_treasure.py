import my
import tp


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The map glows. It seems full of knowledge.")


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.collision_hit_priority(self, 0)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 1)
    my.environ_avoids_fire(self, 100)
    my.gold_value_dice(self, "300")
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_map_treasure(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "When carrying this magical map you are able to see all the treasure, food and keys on the current level.")
    my.noise_on_moving_or_being_carried(self, 1)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.text_a_or_an(self, "a")
    my.text_description(self, "An aged treasure map.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="map_treasure", text_name="treasure map", short_text_name="treasure map")


init()
