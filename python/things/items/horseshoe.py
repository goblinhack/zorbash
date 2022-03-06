import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.gold_value_dice(self, "1")
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_immune_to_cold(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_a(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "Lucky for you, not so much for the horse.")
    my.noise_on_moving_or_being_carried(self, 1)
    my.normal_placement_rules(self, True)
    my.rarity(self, my.RARITY_COMMON)
    my.stat_luck_mod(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A lucky horseshoe.")
    my.text_enchant(self, "+1 LUCK")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="horseshoe", text_name="horseshoe", short_text_name="horseshoe")


init()
