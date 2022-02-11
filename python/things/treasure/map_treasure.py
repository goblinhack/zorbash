import my
import tp


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The map glows. It seems full of knowledge.")


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_hit_priority(self, 0)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_enchant_max(self, 1)
    my.tp_set_environ_avoids_fire(self, 100)
    my.tp_set_gold_value_dice(self, "300")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_enchantable(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_map_treasure(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_treasure_class_b(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "When carrying this magical map you are able to see all the treasure, food and keys on the current level.")
    my.tp_set_noise_on_moving_or_being_carried(self, 15)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_enchant_do(self, "me.on_enchant()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "An aged treasure map.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="map_treasure", text_name="treasure map", short_text_name="treasure map")


init()
